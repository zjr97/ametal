/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief ADC drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-25  mkr, first implementation.
 * \endinternal
 */

#include "am_fsl_adc.h"
#include "am_int.h"
#include "math.h"
/*******************************************************************************
* ˽�ж���
*******************************************************************************/
#define __ADC_HW_DECL(p_hw_adc, p_drv)    \
        amhw_fsl_adc_t *p_hw_adc =               \
            ((am_fsl_adc_dev_t *)p_drv)->p_devinfo->p_hw_adc

#define __ADC_VREF_GET(p_drv)             \
        (((am_fsl_adc_dev_t *)p_drv)->p_devinfo->vref)


/*******************************************************************************
* ��������
*******************************************************************************/
/**
 * \brief DMA��������
 */
extern int am_fsl_adc_dma_tran_cfg (am_fsl_adc_dev_t *p_dev,
									am_adc_buf_desc_t *p_desc);

/** \brief ����ADCת��        */
static int __am_fsl_adc_adc_start  (void                   *p_drv,
                                     int                     chan,
                                     am_adc_buf_desc_t      *p_desc,
                                     uint32_t                desc_num,
                                     uint32_t                count,
                                     uint32_t                flags,
                                     am_adc_seq_cb_t  pfn_callback,
                                     void                   *p_arg);

/** \brief ֹͣADCת�� */
static int __am_fsl_adc_stop (void *p_drv, int chan);

/** \brief ��ȡADC�Ĳ�����    */
static int __am_fsl_adc_rate_get (void       *p_drv,
                                   int         chan,
                                   uint32_t   *p_rate);

/** \brief ����ADC�Ĳ����ʣ�ʵ�ʲ����ʿ��ܴ��ڲ��� */
static int __am_fsl_adc_rate_set (void     *p_drv,
                                   int       chan,
                                   uint32_t  rate);

/** \brief ��ȡADCת������ */
static uint32_t __am_fsl_adc_bits_get(void *p_drv, int chan);

/** \brief ��ȡADC�ο���ѹ */
static uint32_t __am_fsl_adc_vref_get(void *p_drv, int chan);

/**
 * \brief ADC������
 */
static const struct am_adc_drv_funcs __g_adc_drvfuncs = {

    __am_fsl_adc_adc_start,
    __am_fsl_adc_stop,
    __am_fsl_adc_rate_get,
    __am_fsl_adc_rate_set,
    __am_fsl_adc_bits_get,
    __am_fsl_adc_vref_get
};



/**
 * \brief ADC��ȡ����
 */
static void __adc_int(void *p_arg)
{
    am_fsl_adc_dev_t *p_dev = (am_fsl_adc_dev_t *)p_arg;
    uint16_t          dat = 0 ;

    uint8_t      *p_bufu8  = ( uint8_t *) p_dev->p_desc[p_dev->desc_pos].p_buf;
    uint16_t     *p_bufu16 = ( uint16_t *)p_dev->p_desc[p_dev->desc_pos].p_buf;
    int16_t      *p_buf16  = ( int16_t *) p_dev->p_desc[p_dev->desc_pos].p_buf;

    if ( p_bufu8 == NULL) {
        return;
    }

    /* ��ȡ���� */
    dat   = amhw_fsl_adc_dat_get(p_dev->p_devinfo->p_hw_adc, p_dev->p_devinfo->seq);


    if ( p_dev->p_devinfo->is_diff == AM_TRUE ) {
        /* 16λ��13λ��11λ��9λ��������ŵ�  int16_t ���͵�buf�� */
        p_buf16[p_dev->index] = dat;

    } else if ( p_dev->p_devinfo->bits == 8 ) {
        /* 8λ�������� ��ŵ�uint8_t���͵�buf�� */

        p_bufu8[p_dev->index] = (uint8_t)dat;
    } else {
        /* 16λ��12λ��10λ �������� ��ŵ� uint16_t ���͵�buf�� */

        if ( AM_ADC_DATA_ALIGN_LEFT &  p_dev->flags) {
            p_bufu16[p_dev->index] = dat << ( 16 - p_dev->p_devinfo->bits);
        } else {
            p_bufu16[p_dev->index] = dat;
        }
    }

    (p_dev->index)++;

    /* ���һ���������������Ľ���*/
    if (p_dev->index >= p_dev->p_desc[p_dev->desc_pos].length) {
        p_dev->index = 0;
        if (NULL != p_dev->p_desc[p_dev->desc_pos].pfn_complete) {
            p_dev->p_desc[p_dev->desc_pos].pfn_complete(p_dev->p_desc[p_dev->desc_pos].p_arg, AM_OK);
        }

        p_dev->desc_pos++;
        if (p_dev->desc_pos == p_dev->desc_num) { /* �Ѿ�������� */
            p_dev->desc_pos = 0;

            if (NULL != p_dev->pfn_callback) {
                p_dev->pfn_callback(p_dev->p_arg, AM_OK);
            }
            p_dev->count_pos++; /* ת�����б�׼ */
            if (p_dev->count != 0 && p_dev->count_pos == p_dev->count) {
                p_dev->count_pos = 0;
                __am_fsl_adc_stop(p_dev, p_dev->chan);  /* �ر�ģ�� */
                return ; /* ���� */
            }
        }
    }
}

/**
 * \brief ����ADCת��
 */
static int __am_fsl_adc_adc_start  (void                   *p_drv,
                                     int                     chan,
                                     am_adc_buf_desc_t      *p_desc,
                                     uint32_t                desc_num,
                                     uint32_t                count,
                                     uint32_t                flags,
                                     am_adc_seq_cb_t  pfn_callback,
                                     void                   *p_arg)
{
    am_fsl_adc_dev_t *p_dev = NULL;
    uint32_t cfg = 0;

    if (NULL == p_drv || p_desc == NULL) {
        return -AM_EINVAL;
    }

    p_dev = (am_fsl_adc_dev_t *)p_drv;

    p_dev->p_desc       = p_desc;
    p_dev->chan         = chan;
    p_dev->desc_num     = desc_num;
    p_dev->count        = count;
    p_dev->flags        = flags;
    p_dev->pfn_callback = pfn_callback;
    p_dev->p_arg        = p_arg;
    p_dev->index        = 0;
    p_dev->count_pos    = 0;

    cfg = 0;
    if (p_dev->p_devinfo->dma_chan == -1) { /* ��DMAģʽ��ʹ���ж� */
       cfg |= AMHW_FSL_ADC_SC1_INT_EN_CFG;
    } else {
       /* DMA�������� */
       am_fsl_adc_dma_tran_cfg(p_dev, &p_desc[0]);
       amhw_fsl_adc_dma_enable(p_dev->p_devinfo->p_hw_adc);
    }

    cfg |= AMHW_FSL_ADC_SC1_CHAN_SEL_CFG(p_dev->chan);
    if (p_dev->p_devinfo->is_diff && p_dev->chan < 3) {
        cfg |= AMHW_FSL_ADC_SC1_DIFF_EN_CFG;
    }

    /* ���õ��ˡ����ģʽ���Լ�ͨ���� ����ת��*/
    amhw_fsl_adc_sc1_cfg(p_dev->p_devinfo->p_hw_adc, p_dev->p_devinfo->seq, cfg);

    return AM_OK;
}

/**
 * \brief ֹͣת��
 */
static int __am_fsl_adc_stop (void *p_drv, int chan)
{
    am_fsl_adc_dev_t *p_dev = NULL;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev = (am_fsl_adc_dev_t *)p_drv;

    amhw_fsl_adc_chan_set(p_dev->p_devinfo->p_hw_adc,
                           p_dev->p_devinfo->seq,
                           AMHW_FSL_ADC_CHAN_CLOSE);

    amhw_fsl_adc_dma_disable(p_dev->p_devinfo->p_hw_adc);
    return AM_OK;
}

/**
 * \brief ��ȡBCT��λ����FADCK��Ҫ��
 */
uint8_t __am_fsl_adc_rate_bct_get(uint8_t bits, uint8_t diff)
{
    uint8_t bct = 0;

    /* λ��Ӱ���FADCKʱ�Ӹ��� */
    switch (bits) {

    case 8:
        bct = 17;
        break;

    case 9:
        bct = 27;
        break;

    case 10:
    case 12:
        bct = 20;
        break;

    case 11:
    case 13:
        bct = 30;
        break;

    case 16:
        if (diff == AM_FSL_ADC_DIFF_DIS) {
            bct = 25;
        } else {
            bct = 34;
        }
        break;

    default:
        break;
    }

    return bct;
}

/**
 * \brief ��ȡADC�Ĳ�����
 */
static int __am_fsl_adc_rate_get (void       *p_drv,
                                  int         chan,
                                  uint32_t   *p_rate)
{
    uint8_t            adc_clkdiv;
    uint32_t           bus_clk;
    am_fsl_adc_dev_t *p_dev = NULL;
    uint32_t           fadck;

    if (NULL == p_drv || NULL == p_rate) {
        return -AM_EINVAL;
    }

    p_dev = (am_fsl_adc_dev_t *)p_drv;

    bus_clk = am_clk_rate_get(p_dev->p_devinfo->clk_id);

    adc_clkdiv = amhw_fsl_adc_clkdiv_get(p_dev->p_devinfo->p_hw_adc);
    adc_clkdiv = 0x1 << adc_clkdiv;

    /* ��ȡFADCʱ�� */
    bus_clk /= adc_clkdiv;

    /* ��ȡλ��Ӱ���FADCK���� */
    fadck  = __am_fsl_adc_rate_bct_get(p_dev->p_devinfo->bits,
                                        p_dev->p_devinfo->is_diff);
    /* ��ȡ����ģʽ��Ӱ���FADCK���� */
    if (amhw_fsl_adc_cfg2_get(p_dev->p_devinfo->p_hw_adc) &
                               AMHW_FSL_ADC_CFG2_HSC_EN_CFG) {
        fadck += 2;
    }

    /* ��ȡ������Ӱ���FADCK���� */
    if (amhw_fsl_adc_cfg1_get(p_dev->p_devinfo->p_hw_adc) &
                               AMHW_FSL_ADC_CFG1_LSMP_EN_CFG) {

        switch (amhw_fsl_adc_cfg2_get(p_dev->p_devinfo->p_hw_adc) &
                AMHW_FSL_ADC_CFG2_LSTS_MASK) {

        case AMHW_FSL_ADC_CFG2_LSTS_CFG(AMHW_FSL_ADC_LSTS_20ADCK):
            fadck += 20;
            break;

        case AMHW_FSL_ADC_CFG2_LSTS_CFG(AMHW_FSL_ADC_LSTS_12ADCK):
            fadck += 12;
            break;

        case AMHW_FSL_ADC_CFG2_LSTS_CFG(AMHW_FSL_ADC_LSTS_6ADCK):
            fadck += 6;
            break;

        case AMHW_FSL_ADC_CFG2_LSTS_CFG(AMHW_FSL_ADC_LSTS_2ADCK):
            fadck += 2;
            break;

        default:
            break;
        }
    }

    /* Ӳ��ƽ��Ӱ���FADCK���� */
    if (p_dev->p_devinfo->p_adc_avg_info != NULL) {
        if (p_dev->p_devinfo->p_adc_avg_info->enable == AM_FSL_ADC_AVG_EN) {
            fadck <<= ((uint8_t)(p_dev->p_devinfo->p_adc_avg_info->avgs_num) + 2);
        }
    }

    /* �״�ת����Ӱ�� */
    fadck += 5;
    if (amhw_fsl_adc_cfg1_get(p_dev->p_devinfo->p_hw_adc) &
                               AMHW_FSL_ADC_CFG1_LSMP_EN_CFG) {
        fadck -= 2; /* ������ʱ��ʱfadckΪ3��FADCK����˼�ȥ2�� */
    }

    *p_rate = bus_clk / fadck; /* �õ������� */

    return AM_OK;
}

/**
 * \brief �����������ĳ˷���ϸ�ָ��ֵ�����ƥ��ʱ����������
 *
 * \param[in] p_nums   : ָ��ͬģʽʱADCK�����飬�����С��������
 * \param[in] nums_len : ADCK������Ԫ�ظ���
 * \param[in] p_divs   : ָ��ͬ��Ƶֵ�����飬�����С��������
 * \param[in] nums_len : ��ͬ��Ƶֵ������Ԫ�ظ���
 * \param[in] rate     : ָ��ƥ��ֵ��bus_clk/rate��
 * \param[in] bct      : ��ͬλ��ʱ��ADCK��
 * \param[in] avgs     : Ӳ��ƽ������������=ƽ��������0=1�� 2=4�� 3=8��4=16��5=32��
 * \param[in] base     : ��һ��ת���Ļ���ADCK��������������Ϊ3�� �̲���Ϊ5��
 * \param[out] p_nums_n : ��ѵ�nums�����е�����
 * \param[out] p_nums_n : ��ѵ�divs�����е�����
 *
 * \return ��С�����ADCK������
 */
uint32_t __find_minerr (const uint32_t *p_nums,   uint8_t  nums_len,
                        const uint32_t *p_divs,   uint8_t  divs_len,
                              uint32_t  rate,     uint8_t  bct,
                              uint8_t   avgs,     uint8_t  base,
                              uint8_t  *p_nums_n, uint8_t *p_divs_n)
{
    uint8_t first = 0 ;
    int     last  = divs_len - 1;
    int     yerr  = 0;

    uint32_t now;
    uint32_t minerr = 0xFFFFFFFF, err;


    *p_nums_n = first;
    *p_divs_n = last;

    for (first = 0; first < nums_len && last >= 0; ) {
        now = (base + ((p_nums[first] + bct) << avgs)) * p_divs[last];
        yerr = now - rate;
        if (yerr < 0) { /* �Ƿ�Ϊ���� */
            yerr = ~yerr + 1;      /* ȡ���� */
        }
        err = yerr;
        if (err < minerr || ((err == minerr) && (now < rate))) {
            minerr = err;
            *p_nums_n  = first;
            *p_divs_n  = last;
        }
        if (now > rate) {
            last--;
        } else if (now < rate){
            first++;
        } else {
            break;
        }
    }

    first = first >= nums_len ? nums_len - 1 : first;
    last  = last  < 0 ? 0 : last;
    *p_nums_n = first;
    *p_divs_n = last;

    return minerr;
}


/**
 * \brief ���ò�����
 * \note
 *       fadck = (BUS_CLK / BUS_DIV)  //�ó�ģ��ʱ��
 *       num   =  FSCAdder + AVGS * (BCT + LSTAdder + HSCAdder) //һ��ת����Ҫ��ģ��ʱ�Ӹ���
 *       rate  = fadck / num                                    //������
 *       ���װ�϶�㣬��Ѱַ�϶࣬Ӱ���˲ɼ�������ٶȣ��ٶ�Ҫ��ߣ�����ʹ��DMA����ģʽ��
 *       ���������÷�ΧΪ20~140kHz��������λ��������ģʽͨ�ã���DMAģʽ����ߴ�818kHz
 */
static int __am_fsl_adc_rate_set(void     *p_drv,
                                 int       chan,
                                 uint32_t  rate)
{
    const uint32_t nums1[] = {2, 4, 6, 8, 12, 14, 20, 22}; /* ������*/
    const uint32_t nums2[] = {0, 2};                       /* �̲��� */
    const uint32_t divs[]  = {1, 2, 4, 8, 16};             /* ��Ƶ���� */

    uint8_t         bct = 0,   avgs = 0, sel = 0;
    uint8_t         nums_n[2], divs_n[2];
    uint32_t        bus_clk;
    uint32_t        err1, err2;
    am_fsl_adc_dev_t *p_dev = NULL;

    if (NULL == p_drv) {
        return -AM_ENXIO;
    }
    p_dev = (am_fsl_adc_dev_t *)p_drv;

    /* ������֧���ж� */
    if ((p_dev->p_devinfo->bits) == 16) {
        if (rate < 37037 || rate > 461467) {
            return -AM_EINVAL;
        }
    } else {
        if (rate < 20000 || rate > 818330) {
            return -AM_EINVAL;
        }
    }

    /* ��ȡBCT */
    bct = __am_fsl_adc_rate_bct_get(p_dev->p_devinfo->bits,
                                     p_dev->p_devinfo->is_diff);

    /* Ӳ��ƽ��Ӱ��һ�β���ֵ��ʱ�� */
    if (p_dev->p_devinfo->p_adc_avg_info != NULL) {
       if (p_dev->p_devinfo->p_adc_avg_info->enable == AM_FSL_ADC_AVG_EN) {
           avgs = (uint8_t)(p_dev->p_devinfo->p_adc_avg_info->avgs_num);
           if (avgs <= 3) {
               avgs += 2;
           }
       }
    }

    /* ʹ�ö̲���������ģʽ */
    bus_clk = am_clk_rate_get(p_dev->p_devinfo->clk_id);
    rate = bus_clk / rate; /* adc_clk_rate/div / num = rate*/
    /* �̲���ģʽ�£���������� */
    err1 = __find_minerr(nums2, sizeof(nums2)/sizeof(nums2[0]),
                         divs, sizeof(divs)/sizeof(divs[0]),
                         rate, bct, avgs, 5,
                         &nums_n[0], &divs_n[0]);
    /* ������ģʽ�£���������� */
    err2 = __find_minerr(nums1, sizeof(nums1)/sizeof(nums1[0]),
                         divs, sizeof(divs)/sizeof(divs[0]),
                         rate, bct, avgs, 3,
                         &nums_n[1], &divs_n[1]);

    /* ���ݲ�ͬ��ģʽ���üĴ��� */
    if (err1 > err2) {
        sel = 1;
        /* ʹ�ó�����ģʽ */
        amhw_fsl_adc_lsmp_enable(p_dev->p_devinfo->p_hw_adc);
        /* ���LSTS */
        if (nums1[nums_n[1]] <= 4) {
            amhw_fsl_adc_lsts_set(p_dev->p_devinfo->p_hw_adc,
                                   AMHW_FSL_ADC_LSTS_2ADCK);
        } else if (nums1[nums_n[1]] <= 8) {
            amhw_fsl_adc_lsts_set(p_dev->p_devinfo->p_hw_adc,
                                   AMHW_FSL_ADC_LSTS_6ADCK);
        } else if (nums1[nums_n[1]] <= 14) {
            amhw_fsl_adc_lsts_set(p_dev->p_devinfo->p_hw_adc,
                                   AMHW_FSL_ADC_LSTS_12ADCK);
        } else {
            amhw_fsl_adc_lsts_set(p_dev->p_devinfo->p_hw_adc,
                                   AMHW_FSL_ADC_LSTS_20ADCK);
        }
    } else {
        sel = 0;
        /* ʹ�ö̲���ģʽ */
        amhw_fsl_adc_lsmp_disable(p_dev->p_devinfo->p_hw_adc);
    }

    /* �����Ƿ�ʹ�ø��ٲ��� */
    if (nums_n[sel] % 2 == 0) {
        amhw_fsl_adc_hsc_disable(p_dev->p_devinfo->p_hw_adc);
    } else {
        amhw_fsl_adc_hsc_enable(p_dev->p_devinfo->p_hw_adc);
    }
    if (divs[divs_n[sel]] == 16) { /* ��Ҫѡ��bus/2ʱ��Դ����ƵֵΪ8 */
        amhw_fsl_adc_clksrc_set(p_dev->p_devinfo->p_hw_adc,
                                 AMHW_FSL_ADC_CLK_SRC_ALTCLK2);
        amhw_fsl_adc_clkdiv_set(p_dev->p_devinfo->p_hw_adc,
                                 AMHW_FSL_ADC_CLK_DIV_8);
    } else {
        /* ѡ������ʱ��Դ */
        amhw_fsl_adc_clksrc_set(p_dev->p_devinfo->p_hw_adc,
                                 AMHW_FSL_ADC_CLK_SRC_BUS);
        amhw_fsl_adc_clkdiv_set(p_dev->p_devinfo->p_hw_adc,
                                (amhw_fsl_adc_clk_div_t)divs_n[sel]);
    }
    /* ʹ�����Ƶ�ʣ�����������ʹ�ܣ���ʱ����Ҳ���������~*/
    bus_clk = bus_clk / divs[divs_n[sel]];
    if (bus_clk == 18000000UL || (bus_clk == 12000000UL &&
        p_dev->p_devinfo->bits == 16)) {
        amhw_fsl_adc_hsc_enable(p_dev->p_devinfo->p_hw_adc);
        amhw_fsl_adc_lowpower_disable(p_dev->p_devinfo->p_hw_adc);
    }

    return AM_OK;
}

/**
 * \brief ��ȡADCת������
 */
static uint32_t __am_fsl_adc_bits_get(void *p_drv, int chan)
{
    am_fsl_adc_dev_t *p_dev = NULL;

    if (NULL == p_drv) {
        return 0xFFFFFFFF;
    }

    p_dev = (am_fsl_adc_dev_t *)p_drv;



    return p_dev->p_devinfo->bits;
}

/**
 * \brief ����ADCת������
 */
static int __am_fsl_adc_bits_set(am_fsl_adc_dev_t *p_dev)
{
    uint32_t bits;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    bits = p_dev->p_devinfo->bits;
    if (p_dev->p_devinfo->is_diff == AM_TRUE) {
        if (bits == 9 || bits == 11 || bits == 13 || bits == 16) {
            switch ( p_dev->p_devinfo->bits ) {

            case 9:
                amhw_fsl_adc_mode_set(p_dev->p_devinfo->p_hw_adc,
                                       AMHW_FSL_ADC_BITS_9);
                break;

            case 11:
                amhw_fsl_adc_mode_set(p_dev->p_devinfo->p_hw_adc,
                                       AMHW_FSL_ADC_BITS_11);
                break;

            case 13:
                amhw_fsl_adc_mode_set(p_dev->p_devinfo->p_hw_adc,
                                       AMHW_FSL_ADC_BITS_13);
                break;

            case 16:
                amhw_fsl_adc_mode_set(p_dev->p_devinfo->p_hw_adc,
                                       AMHW_FSL_ADC_BITS_16);
                break;

            default:
                break;

            }
        } else {
            return -AM_EINVAL;
        }
    } else {
        if (bits == 8 || bits == 10 || bits == 12 || bits == 16) {
            switch ( p_dev->p_devinfo->bits ) {

            case 8:
                amhw_fsl_adc_mode_set(p_dev->p_devinfo->p_hw_adc,
                                       AMHW_FSL_ADC_BITS_8);
                break;

            case 10:
                amhw_fsl_adc_mode_set(p_dev->p_devinfo->p_hw_adc,
                                       AMHW_FSL_ADC_BITS_10);
                break;

            case 12:
                amhw_fsl_adc_mode_set(p_dev->p_devinfo->p_hw_adc,
                                       AMHW_FSL_ADC_BITS_12);
                break;

            case 16:
                amhw_fsl_adc_mode_set(p_dev->p_devinfo->p_hw_adc,
                                       AMHW_FSL_ADC_BITS_16);
                break;

            default:
                break;

            }
        } else {
            return -AM_EINVAL;
        }
    }
    return AM_OK;
}
/**
 * \brief ��ȡADC�ο���ѹ
 */
static uint32_t __am_fsl_adc_vref_get(void *p_drv, int chan)
{
    am_fsl_adc_dev_t *p_dev = NULL;

    if (NULL == p_drv) {
        return 0xFFFFFFFF;
    }

    p_dev = (am_fsl_adc_dev_t *)p_drv;

    return p_dev->p_devinfo->vref;
}

/**
 * \brief ADC��ʼ��
 */
am_adc_handle_t am_fsl_adc_init (am_fsl_adc_dev_t           *p_dev,
                                  const am_fsl_adc_devinfo_t *p_devinfo)
{
    uint32_t cfg = 0;
    uint16_t cv1, cv2;

    if (NULL == p_devinfo || NULL == p_dev ||
        p_devinfo->dma_chan > 3 || p_devinfo->dma_chan < -1
    		) { /* ������Ч�Լ�� */
        return NULL;
    }

    p_dev->p_devinfo         = p_devinfo;
    p_dev->adc_serv.p_funcs  = &__g_adc_drvfuncs;
    p_dev->adc_serv.p_drv    = p_dev;

    p_dev->pfn_callback      = NULL;
    p_dev->p_desc            = NULL;
    p_dev->p_arg             = NULL;
    p_dev->desc_num          = 0;
    p_dev->flags             = 0;
    p_dev->count             = 0;
    p_dev->chan              = AMHW_FSL_ADC_CHAN_CLOSE; /* Ĭ�Ϲر� */
    p_dev->desc_pos          = 0;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* Ĭ��100k������, ����ģ��ʱ�� */
    __am_fsl_adc_rate_set(p_dev, 0, 1000000); /* ������100K */

    /* ����ADC�ֱ��� */
    if (AM_OK != __am_fsl_adc_bits_set(p_dev)) {
        return NULL;
    }
    /* ѡ������ */
//    amhw_fsl_adc_seq_set(p_dev->p_devinfo->p_hw_adc, p_dev->p_devinfo->seq);

    /* Ӳ�������������� */
    if (p_dev->p_devinfo->mode_trg == AM_FSL_ADC_MODE_TRG_HW) {
        cfg |= AMHW_FSL_ADC_SC2_HWTRG_EN_CFG;
    }
    /* �ȽϹ������� */
    if (p_dev->p_devinfo->p_adc_cmp_info != NULL) {
        if (p_dev->p_devinfo->p_adc_cmp_info->enable == AM_FSL_ADC_CMP_EN) {
            cfg |= AMHW_FSL_ADC_SC2_CMP_EN_CFG; /* ʹ�ܱȽϹ��� */
            switch (p_dev->p_devinfo->p_adc_cmp_info->cmp_mode) {

            case AM_FSL_ADC_CMP_MODE_1:
                cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val1;
                break;

            case AM_FSL_ADC_CMP_MODE_2:
                cfg |= AMHW_FSL_ADC_SC2_CMPGT_EN_CFG;
                cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val1;
                break;

            case AM_FSL_ADC_CMP_MODE_3:
                cfg |= AMHW_FSL_ADC_SC2_CMPR_EN_CFG;
                cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val1;
                cv2 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val2;
                if (cv1 > cv2) {
                    cv2 = cv1;
                    cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val2;
                }
                break;

            case AM_FSL_ADC_CMP_MODE_4:
                cfg |= AMHW_FSL_ADC_SC2_CMPR_EN_CFG;
                cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val1;
                cv2 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val2;
                if (cv1 < cv2) {
                    cv2 = cv1;
                    cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val2;
                }
                break;

            case AM_FSL_ADC_CMP_MODE_5:
                cfg |= AMHW_FSL_ADC_SC2_CMPR_EN_CFG;
                cfg |= AMHW_FSL_ADC_SC2_CMPGT_EN_CFG;
                cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val1;
                cv2 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val2;
                if (cv1 > cv2) {
                    cv2 = cv1;
                    cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val2;
                }
                break;

            case AM_FSL_ADC_CMP_MODE_6:
                cfg |= AMHW_FSL_ADC_SC2_CMPR_EN_CFG;
                cfg |= AMHW_FSL_ADC_SC2_CMPGT_EN_CFG;
                cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val1;
                cv2 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val2;
                if (cv1 < cv2) {
                    cv2 = cv1;
                    cv1 = p_dev->p_devinfo->p_adc_cmp_info->cmp_val2;
                }
                break;

            default:
                break;

            }/* switch(mode) */
            amhw_fsl_adc_cv1_set(p_dev->p_devinfo->p_hw_adc, cv1);
            amhw_fsl_adc_cv2_set(p_dev->p_devinfo->p_hw_adc, cv2);
        }/* if enable */
    }/* if not CMP func NULL*/
    amhw_fsl_adc_sc2_cfg(p_dev->p_devinfo->p_hw_adc, cfg); /* ���ô���ģʽ�Լ��ȽϹ���*/

    if (p_dev->p_devinfo->mode_trg == AM_FSL_ADC_MODE_TRG_HW) {
        cfg = 0;
    } else {
        cfg = AMHW_FSL_ADC_SC3_CONT_EN_CFG;  /* ʹ������ת������ */
    }

    /* Ӳ��ƽ���������� */
    if (p_dev->p_devinfo->p_adc_avg_info != NULL) {
        if (p_dev->p_devinfo->p_adc_avg_info->enable == AM_FSL_ADC_AVG_EN) {
            cfg |= AMHW_FSL_ADC_SC3_AVG_EN_CFG; /* ʹ��Ӳ��ƽ������ */
            cfg |= AMHW_FSL_ADC_SC3_AVGS_CFG(p_dev->p_devinfo->p_adc_avg_info->avgs_num);
        }
    }
    amhw_fsl_adc_sc3_cfg(p_dev->p_devinfo->p_hw_adc, cfg); /* ����Ӳ��ƽ��������������ģʽ */

    cfg = 0;
    cfg |= AMHW_FSL_ADC_SC1_CHAN_SEL_CFG(p_dev->chan);
    if (p_dev->p_devinfo->is_diff && p_dev->chan < 3) {
        cfg |= AMHW_FSL_ADC_SC1_DIFF_EN_CFG;
    }

    if (p_dev->p_devinfo->dma_chan == -1) { /* ��DMAģʽ��ʹ���ж� */
        cfg |= AMHW_FSL_ADC_SC1_INT_EN_CFG;
        am_int_connect(p_dev->p_devinfo->inum, __adc_int, p_dev);
        am_int_enable(p_dev->p_devinfo->inum);
        cfg |= AMHW_FSL_ADC_SC1_INT_EN_CFG;
    }

    /* ���õ��ˡ����ģʽ���Լ�ͨ�� ����ʼ����ͨ��Ĭ�Ϲرգ�*/
    amhw_fsl_adc_sc1_cfg(p_dev->p_devinfo->p_hw_adc, p_dev->p_devinfo->seq, cfg);
    return (am_adc_handle_t)(&(p_dev->adc_serv));
}

/**
 * \brief ADCȥ��ʼ��
 */
void am_fsl_adc_deinit (am_adc_handle_t handle)
{
    am_fsl_adc_dev_t *p_dev = (am_fsl_adc_dev_t *)handle;

    if (NULL == p_dev) {
        return ;
    }

    __am_fsl_adc_stop(p_dev, p_dev->chan);
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum, __adc_int, p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }

}
/* end of file */
