/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.03 18-04-24  pea, update standard interface
 * - 1.02 15-12-14  hgo, fix inaccurate samplerate and always generate interrput
 * - 1.01 15-11-25  hgo, modified bug when count=0
 * - 1.00 15-07-15  bob, first implementation
 * \endinternal
 */
#include "am_lpc82x_adc_dma.h"
#include "am_int.h"
#include "am_clk.h"
#include "hw/amhw_lpc82x_inmux.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_adc.h"
/*******************************************************************************
* ˽�ж���
*******************************************************************************/

#define __ADC_HW_DECL(p_hw_adc, p_drv)    \
        amhw_lpc82x_adc_t *p_hw_adc =            \
            ((am_lpc82x_adc_dma_dev_t *)p_drv)->p_devinfo->p_hw_adc

#define __ADC_VREF_GET(p_drv)             \
        (((am_lpc82x_adc_dma_dev_t *)p_drv)->p_devinfo->vref)


/*******************************************************************************
* ��������
*******************************************************************************/

/** \brief ADC DMA��������жϺ��� */
static void __adc_dma_int(void *p_arg, int state);

/** \brief ADC ʹ��DMAģʽʱ�������� */
static int __adc_dma_work_startup(am_lpc82x_adc_dma_dev_t *p_dev,
                                  uint32_t                 desc_num);

/** \brief ����ADCת��        */
static int __pfn_adc_start  (void                   *p_drv,
                             int                     chan,
                             am_adc_buf_desc_t      *p_desc,
                             uint32_t                desc_num,
                             uint32_t                count,
                             uint32_t                flags,
                             am_adc_seq_cb_t         pfn_callback,
                             void                   *p_arg);
 
/** \brief ֹͣת��           */
static int __pfn_adc_stop (void *p_drv, int chan);
                      
/** \brief ��ȡADC�Ĳ�����    */
static int __pfn_rate_get (void       *p_drv,
                           int         chan,
                           uint32_t   *p_rate);

/** \brief ����ADC�Ĳ����ʣ�ʵ�ʲ����ʿ��ܴ��ڲ��� */
static int __pfn_rate_set (void     *p_drv,
                           int       chan,
                           uint32_t  rate);

/** \brief ��ȡADCת������ */
static uint32_t __pfn_bits_get(void *p_drv, int chan);

/** \brief ��ȡADC�ο���ѹ */
static uint32_t __pfn_vref_get(void *p_drv, int chan);



/**
 * \brief ADC������ 
 */
static const struct am_adc_drv_funcs __g_adc_drvfuncs = {
    __pfn_adc_start,
    __pfn_adc_stop,
    __pfn_rate_get,
    __pfn_rate_set,
    __pfn_bits_get,
    __pfn_vref_get
};

/******************************************************************************/

/**
 * \brief ADC DMA
 */
static void __adc_dma_int(void *p_arg, int state)
{
    am_lpc82x_adc_dma_dev_t *p_dev    = (am_lpc82x_adc_dma_dev_t *)p_arg;
    amhw_lpc82x_adc_t       *p_hw_adc = NULL;

    uint32_t       buf_pos = 0;
    uint32_t       i;

    uint16_t      *p_buf = NULL;

    /* �����ж� */
    if ( state & AM_LPC82X_DMA_STAT_INTERR) {

        __pfn_adc_stop (p_dev, p_dev->chan);

        if (NULL != p_dev->pfn_callback) {
            p_dev->pfn_callback(p_dev->p_arg, AM_ERROR);
        }
        return;
    }

    /* �жϲ������Ƿ���� */
    if ((state & AM_LPC82X_DMA_STAT_INTA) &&
        (state & AM_LPC82X_DMA_STAT_INTB)) {

        __pfn_adc_stop (p_dev, p_dev->chan);

        if (NULL != p_dev->p_desc[0].pfn_complete) {
            p_dev->p_desc[0].pfn_complete(p_dev->p_desc[0].p_arg, AM_ERROR);
        }

        if (NULL != p_dev->p_desc[1].pfn_complete) {
            p_dev->p_desc[1].pfn_complete(p_dev->p_desc[1].p_arg, AM_ERROR);
        }
        return;

    } else if (state & AM_LPC82X_DMA_STAT_INTA) {
        buf_pos = 0;
    } else if (state & AM_LPC82X_DMA_STAT_INTB) {
        buf_pos = 1;
    }

    /* ���ݸ�ʽ���� */
    if (AM_ADC_DATA_ALIGN_RIGHT == p_dev->flags) {

        p_buf = (uint16_t *)(p_dev->p_desc[buf_pos].p_buf);

        for (i = 0; i < p_dev->p_desc[buf_pos].length; i++ ) {
            p_buf[i] = p_buf[i] >> 4;
        }
    }

    /* �������ص�����  */
    if (NULL != p_dev->p_desc[buf_pos].pfn_complete) {
        p_dev->p_desc[buf_pos].pfn_complete(p_dev->p_desc[buf_pos].p_arg, 
                                            AM_OK);
    }

    /* ������ɵ���ϵ������ж� */
    if ((++p_dev->desc_index) == p_dev->desc_num) {

        p_dev->desc_index = 0;
        p_dev->seq_cnt++;

        if (p_dev->count != 0 && p_dev->seq_cnt >= p_dev->count) {

            /* �ﵽ���������Ҳ����� */
            p_dev->seq_cnt = 0;
            __pfn_adc_stop (p_dev, p_dev->chan);

        } else if (1 == p_dev->desc_num) {

            p_hw_adc = (amhw_lpc82x_adc_t *)(p_dev->p_devinfo->adc_regbase);

            {
                am_lpc82x_dma_controller_abort(p_dev->p_dma_ctr);   /* ֹͣDMA���� */
                am_lpc82x_dma_controller_release(p_dev->p_dma_ctr); /* �ͷ�DMA��Դ */

                /* ֹͣ��ǰ���䣬����������A */
                amhw_lpc82x_adc_seq_stop   (p_hw_adc, AMHW_LPC82X_ADC_SEQ_A);
                amhw_lpc82x_adc_seq_disable(p_hw_adc, AMHW_LPC82X_ADC_SEQ_A);

                /* ��������A�ж� */
                amhw_lpc82x_adc_int_disable(p_hw_adc,
                                            AMHW_LPC82X_ADC_INTEN_SEQA_ENABLE);
            }

            {
                amhw_lpc82x_adc_int_enable(p_hw_adc,
                                           AMHW_LPC82X_ADC_INTEN_SEQA_ENABLE);

                __adc_dma_work_startup(p_dev, p_dev->desc_num);
            }
        }

        if (NULL != p_dev->pfn_callback) {
            p_dev->pfn_callback(p_dev->p_arg, AM_OK);
        }
    }
}

/**
 * \brief ADC ʹ��DMAģʽʱ��������
 */
static int __adc_dma_work_startup(am_lpc82x_adc_dma_dev_t *p_dev, uint32_t desc_num)
{
    uint32_t        dma_aflags = 0, dma_bflags = 0;
    uint32_t        seq_flags  = 0;
    
    am_lpc82x_dma_controller_t *p_dma_ctr = NULL;
    amhw_lpc82x_adc_t          *p_hw_adc  =  NULL;

    uint32_t trans_width_flag, trans_byte_one;

    p_hw_adc =  (amhw_lpc82x_adc_t *)(p_dev->p_devinfo->adc_regbase);

    p_dma_ctr = am_lpc82x_dma_controller_get(p_dev->p_devinfo->dma_chan,
                                             /* ͨ�����ȼ�Ϊ1 */
                                             DMA_CHAN_OPT_PRIO_1             |
                                             /* �����ش��� */
                                             DMA_CHAN_OPT_HWTRIG_MODE_RISE   |
                                             /* �����ش��� */
                                             DMA_CHAN_OPT_HWTRIG_BURST_EN    |
                                             /* ͻ�������СΪ1 */
                                             DMA_CHAN_OPT_HWTRIG_BURST_1     |
                                             /* ADC0����A�жϴ���DMA���� */
                                             DMA_CHAN_OPT_HWTRIG_SRC_ADC0_SEQA_IRQ);

    if (p_dma_ctr == NULL) {
        p_dev->p_dma_ctr = NULL;
        return -AM_EPERM;
    }
    p_dev->p_dma_ctr = p_dma_ctr;

    /* ���������� */
    trans_byte_one   = 2;
    trans_width_flag = AM_LPC82X_DMA_XFER_WIDTH_16BIT;

    /* DMA�������� */
    dma_aflags = AM_LPC82X_DMA_XFER_VALID           |  /* ��ǰͨ����������Ч */
                 AM_LPC82X_DMA_XFER_RELOAD          |  /* ����������ͨ�������� */
                 trans_width_flag                   |  /* �������ݿ�� */
                 AM_LPC82X_DMA_XFER_SRCINC_NOINC    |  /* Դ�����ݵ�ַ������ */
                 AM_LPC82X_DMA_XFER_DSTINC_1X       |  /* Ŀ���ַ��1x��ȵ��� */
                 AM_LPC82X_DMA_XFER_SETINTA;           /* ʹ���ж� A */

    /* ����ͨ��������A */
    am_lpc82x_dma_xfer_desc_build(&p_dev->dma_desc[0],                      /* A������������ */
                                  (uint32_t)(&p_hw_adc->dat[p_dev->chan]),  /* Դ�����ݵ�ַ  */
                                  (uint32_t)p_dev->p_desc[0].p_buf,         /* ��������ַ  */
                                  p_dev->p_desc[0].length * trans_byte_one, /* �����ֽ���  */
                                  dma_aflags);                              /* ��������    */

    if (desc_num == 2) {

        /* DMA�������� */
        dma_bflags = AM_LPC82X_DMA_XFER_VALID           |  /* ��ǰͨ����������Ч  */
                     AM_LPC82X_DMA_XFER_RELOAD          |  /* ����������ͨ�������� */
                     trans_width_flag                   |  /* �������ݿ�� */
                     AM_LPC82X_DMA_XFER_SRCINC_NOINC    |  /* Դ�����ݵ�ַ������   */
                     AM_LPC82X_DMA_XFER_DSTINC_1X       |  /* Ŀ���ַ��1x��ȵ��� */
                     AM_LPC82X_DMA_XFER_SETINTB;           /* ʹ���ж� B */

        /* ����ͨ��������B */
        am_lpc82x_dma_xfer_desc_build(&p_dev->dma_desc[1],                      /* B������������ */
                                      (uint32_t)(&p_hw_adc->dat[p_dev->chan]),  /* Դ�����ݵ�ַ  */
                                      (uint32_t)p_dev->p_desc[1].p_buf,         /* ��������ַ  */
                                      p_dev->p_desc[1].length * trans_byte_one, /* �����ֽ���  */
                                      dma_bflags);                              /* ��������    */

        am_lpc82x_dma_xfer_desc_link(&p_dev->dma_desc[0], &p_dev->dma_desc[1]);
        am_lpc82x_dma_xfer_desc_link(&p_dev->dma_desc[1], &p_dev->dma_desc[0]);
    }

    /* ����DMA���䣬���Ͽ�ʼ���� */
    am_lpc82x_dma_xfer_desc_startup(p_dma_ctr,
                                    &p_dev->dma_desc[0],
                                    __adc_dma_int,
                                    (void *)p_dev);

    seq_flags = AMHW_LPC82X_ADC_SEQ_CTRL_MODE_BURST   |          /* ����ͻ��ת��ģʽ */
                AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_POL_POS |          /* ʹ�������ش�����ʽ */
                AMHW_LPC82X_ADC_SEQ_CTRL_MODE_EOS     |          /* ����ת����󴥷�DMA */
                AMHW_LPC82X_ADC_SEQ_CTRL_ENA          |          /* ����Aʹ��          */
                AMHW_LPC82X_ADC_SEQ_CTRL_ENABLE_CH(p_dev->chan); /* ʹ��ADCͨ��    */

    /* ADC����A����(ADCʹ��DMA���䣬��������DMA���䣬������ADCת��)  */
    amhw_lpc82x_adc_seq_config(p_hw_adc,
                               AMHW_LPC82X_ADC_SEQ_A,
                               seq_flags);

    return AM_OK;
}
/**
 * \brief ����ADCת��
 */
static int __pfn_adc_start  (void                   *p_drv,
                             int                     chan,
                             am_adc_buf_desc_t      *p_desc,
                             uint32_t                desc_num,
                             uint32_t                count,
                             uint32_t                flags,
                             am_adc_seq_cb_t         pfn_callback,
                             void                   *p_arg)
{
    am_lpc82x_adc_dma_dev_t *p_dev = NULL;
    amhw_lpc82x_adc_t   *p_hw_adc = NULL;

    if (NULL == p_drv || NULL == p_desc || 0 == desc_num) {
        return -AM_EINVAL;
    }

    p_dev    = (am_lpc82x_adc_dma_dev_t *)p_drv;
    p_hw_adc = (amhw_lpc82x_adc_t *)(p_dev->p_devinfo->adc_regbase);

    if (AM_TRUE != p_dev->is_idle) {
        return -AM_EBUSY;
    }

    p_dev->is_idle      = AM_FALSE;
    p_dev->p_desc       = p_desc;
    p_dev->chan         = chan;
    p_dev->desc_num     = desc_num;
    p_dev->count        = count;
    p_dev->flags        = flags;
    p_dev->pfn_callback = pfn_callback;
    p_dev->p_arg        = p_arg;
    p_dev->seq_cnt      = 0;
    p_dev->desc_index   = 0;
    p_dev->conv_cnt     = 0;

    /* ʹ������A�ж� */
    amhw_lpc82x_adc_int_enable(p_hw_adc,
                               AMHW_LPC82X_ADC_INTEN_SEQA_ENABLE);

   {
        /* DMA����ģʽ�£��������������֧��2�� */
        if (NULL == p_drv || desc_num > 2) {
            return -AM_EINVAL;
        }
        /* DMA�������� */
        if (-AM_EPERM == __adc_dma_work_startup(p_dev, desc_num)) {
            return -AM_EINVAL;
        }
    }

    return AM_OK;
}
 
/**
 * \brief ֹͣת��
 */
static int __pfn_adc_stop (void *p_drv, int chan)
{
    am_lpc82x_adc_dma_dev_t *p_dev    = NULL;
    amhw_lpc82x_adc_t   *p_hw_adc = NULL;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    p_dev    = (am_lpc82x_adc_dma_dev_t *)p_drv;
    p_hw_adc = (amhw_lpc82x_adc_t *)(p_dev->p_devinfo->adc_regbase);

    {
        am_lpc82x_dma_controller_abort(p_dev->p_dma_ctr);   /* ֹͣDMA���� */
        am_lpc82x_dma_controller_release(p_dev->p_dma_ctr); /* �ͷ�DMA��Դ */
    }
    /* ֹͣ��ǰ���䣬����������A */
    amhw_lpc82x_adc_seq_stop   (p_hw_adc, AMHW_LPC82X_ADC_SEQ_A);
    amhw_lpc82x_adc_seq_disable(p_hw_adc, AMHW_LPC82X_ADC_SEQ_A);

    /* ��������A�ж� */
    amhw_lpc82x_adc_int_disable(p_hw_adc,
                               AMHW_LPC82X_ADC_INTEN_SEQA_ENABLE);

    p_dev->is_idle = AM_TRUE;

    return AM_OK;
}

/**
 * \brief ��ȡADC�Ĳ�����
 */
static int __pfn_rate_get (void       *p_drv,
                           int         chan,
                           uint32_t   *p_rate)
{
    uint8_t              adc_clkdiv;
    uint32_t             sys_clk;
    am_lpc82x_adc_dma_dev_t *p_dev    = NULL;
    amhw_lpc82x_adc_t   *p_hw_adc = NULL;

    if (NULL == p_drv || NULL == p_rate) {
        return -AM_EINVAL;
    }

    p_dev    = (am_lpc82x_adc_dma_dev_t *)p_drv;
    p_hw_adc = (amhw_lpc82x_adc_t *)(p_dev->p_devinfo->adc_regbase);

    sys_clk  = am_clk_rate_get(p_dev->p_devinfo->clk_id);

    /* �õ�ʱ�ӷ�Ƶϵ�� */
    adc_clkdiv = amhw_lpc82x_adc_clkdiv_get(p_hw_adc);

    /* �õ���Ƶֵ */
    adc_clkdiv = (adc_clkdiv == 255) ? 255 : (adc_clkdiv + 1);

    /* LPC824��Ƶ��Ϊ�����ʵ�25�� */
    *p_rate = sys_clk / adc_clkdiv / 25;

    return AM_OK;
}

/**
 * \brief ����ADC�Ĳ����ʣ�ʵ�ʲ����ʿ��ܴ��ڲ���
 */
static int __pfn_rate_set (void     *p_drv,
                           int       chan,
                           uint32_t  rate)
{
    amhw_lpc82x_adc_t   *p_hw_adc = NULL;
    am_lpc82x_adc_dma_dev_t *p_dev = NULL;
    uint32_t             adc_clkdiv;
    uint32_t             sys_clk;

    if (NULL == p_drv || 0 == rate || 1200000 < rate) {
        return -AM_EINVAL;
    }

    p_dev    = (am_lpc82x_adc_dma_dev_t *)p_drv;
    p_hw_adc = (amhw_lpc82x_adc_t *)(p_dev->p_devinfo->adc_regbase);

    sys_clk = am_clk_rate_get(p_dev->p_devinfo->clk_id);

    /* LPC824��Ƶ��Ϊ�����ʵ�25�� */
    adc_clkdiv = sys_clk / rate / 25;
    
    /* ������̫�ͻ�̫��ʱ�����õ����� */
    if (adc_clkdiv != 0) {
        adc_clkdiv = adc_clkdiv > 256 ? 255 : adc_clkdiv - 1; 
    }
    
    amhw_lpc82x_adc_clkdiv_set (p_hw_adc, adc_clkdiv);

    return AM_OK;

}

/**
 * \brief ��ȡADCת������
 */
static uint32_t __pfn_bits_get (void *p_drv, int chan)
{
    return (uint32_t)12;
}

/**
 * \brief ��ȡADC�ο���ѹ
 */
static uint32_t __pfn_vref_get (void *p_drv, int chan)
{
    if (NULL == p_drv) {
        return 0;   /* ��Դ�Ѿ��ͷţ��ο���ѹδ֪ */
    }

    return (uint32_t)__ADC_VREF_GET(p_drv);
}

/**
 * \brief ADC��ʼ��
 */
am_adc_handle_t am_lpc82x_adc_dma_init (am_lpc82x_adc_dma_dev_t     *p_dev,
                              const am_lpc82x_adc_dma_devinfo_t *p_devinfo)
{

    if (NULL == p_devinfo || NULL == p_dev ) {
        return NULL;
    }
    
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }
    
    p_dev->p_devinfo         = p_devinfo;
    p_dev->adc_serve.p_funcs = &__g_adc_drvfuncs;
    p_dev->adc_serve.p_drv   = p_dev;

    p_dev->pfn_callback      = NULL;
    p_dev->p_desc            = NULL;
    p_dev->p_arg             = NULL;
    p_dev->desc_num          = 0;
    p_dev->flags             = 0;
    p_dev->count             = 0;
    p_dev->chan              = 0;
    p_dev->seq_cnt           = 0;
    p_dev->desc_index        = 0;
    p_dev->conv_cnt          = 0;
    p_dev->is_idle           = AM_TRUE;

    return (am_adc_handle_t)(&(p_dev->adc_serve));
}

/**
 * \brief ADCȥ��ʼ��
 */
void am_lpc82x_adc_dma_deinit (am_adc_handle_t handle)
{
    am_lpc82x_adc_dma_dev_t *p_dev    = (am_lpc82x_adc_dma_dev_t *)handle;
    amhw_lpc82x_adc_t   *p_hw_adc = NULL;

    if (NULL == p_dev) {
        return ;
    }

    p_hw_adc = (amhw_lpc82x_adc_t *)(p_dev->p_devinfo->adc_regbase);
    
    /* ֹͣ��ǰ���ڽ��е�ת��������ֹ����ת�� */
    amhw_lpc82x_adc_seq_stop   (p_hw_adc, AMHW_LPC82X_ADC_SEQ_A);
    amhw_lpc82x_adc_seq_disable(p_hw_adc,
                                AMHW_LPC82X_ADC_SEQ_A);

    /* ��������A�ж� */
    amhw_lpc82x_adc_int_disable(p_hw_adc,
                               AMHW_LPC82X_ADC_INTEN_SEQA_ENABLE);

    {
        am_lpc82x_dma_controller_abort(p_dev->p_dma_ctr);   /* ֹͣDMA���� */
        am_lpc82x_dma_controller_release(p_dev->p_dma_ctr); /* �ͷ�DMA��Դ */
    }

    p_dev->adc_serve.p_drv = NULL;
    
    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}
/* end of file */
