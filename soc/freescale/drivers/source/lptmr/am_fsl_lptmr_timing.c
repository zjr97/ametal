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
 * \brief LPTMR ��ʱ����������ʵ��
 *
 * 1. LPTMR�͹��Ķ�ʱ����������ʵ����"��ʱ"����
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */

#include "am_fsl_lptmr_timing.h"
#include "am_int.h"
#include "am_clk.h"

/*******************************************************************************
  ��ʱ��������������
*******************************************************************************/

static const am_timer_info_t *__lptmr_timing_info_get (void *p_drv);

static int __lptmr_timing_clkin_freq_get (void *p_drv, uint32_t *p_freq);

static int __lptmr_timing_prescale_set (void    *p_drv,
                                        uint8_t  chan,
                                        uint32_t prescale);

static int __lptmr_timing_prescale_get (void     *p_drv,
                                        uint8_t   chan,
                                        uint32_t *p_prescale);

static int __lptmr_timing_count_get (void     *p_drv,
                                     uint8_t   chan,
                                     void     *p_count);

static int __lptmr_timing_rollover_get (void     *p_drv,
                                        uint8_t   chan,
                                        void     *p_rollover);

static int __lptmr_timing_disable (void *p_drv, uint8_t chan);

static int __lptmr_timing_enable (void      *p_drv,
                                  uint8_t    chan,
                                  void      *p_count);

static int __lptmr_timing_callback_set (void    *p_drv,
                                        uint8_t  chan,
                                        void   (*pfn_callback)(void *),
                                        void    *p_arg);

static void __lptmr_irq_handler (void *p_arg);

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/* ��ʱ����Ϣ */
static const am_timer_info_t __g_lptmr_timing_info = {
    16,                                      /* 16λ��ʱ��               */
    1,                                       /* ��ͨ��                   */
    AM_TIMER_CAN_INTERRUPT      |            /* ���Բ����ж� */
//    AM_TIMER_INTERMEDIATE_COUNT |            /* ����ʵʱ��������ֵ */
    AM_TIMER_AUTO_RELOAD,                    /* �Զ�װ�� */
    65536                                    /* Ԥ��Ƶ���ֵ��65536      */
};
/** \brief LPTMR��ʱ���������� */
static const struct am_timer_drv_funcs __g_lptmr_timing_drv_funcs = {
    __lptmr_timing_info_get,
    __lptmr_timing_clkin_freq_get,
    __lptmr_timing_prescale_set,
    __lptmr_timing_prescale_get,
    __lptmr_timing_count_get,
    __lptmr_timing_rollover_get,
    __lptmr_timing_enable,
    __lptmr_timing_disable,
    __lptmr_timing_callback_set,
};

/******************************************************************************/

void __lptmr_irq_handler (void *p_arg)
{
    am_fsl_lptmr_timing_dev_t *p_dev      = (am_fsl_lptmr_timing_dev_t *)p_arg;
    amhw_fsl_lptmr_t          *p_hw_lptmr =  p_dev->p_devinfo->p_hw_lptmr;

    if (amhw_fsl_lptmr_flag_check(p_hw_lptmr)) {

        if (p_dev->pfn_callback != NULL) {
            p_dev->pfn_callback(p_dev->p_arg);
        }

        /* ��������־��д1���� */
        amhw_fsl_lptmr_ctl_set(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TCF);
    }
}

/** \brief ��ȡLPTMR��Ϣ */
static const am_timer_info_t * __lptmr_timing_info_get (void *p_drv)
{
    return &__g_lptmr_timing_info;
}

/** \brief ��ȡLPTMRʱ��Ƶ����Ϣ */
static int __lptmr_timing_clkin_freq_get (void *p_drv, uint32_t *p_freq)
{
    am_fsl_lptmr_timing_dev_t *p_dev      = (am_fsl_lptmr_timing_dev_t *)p_drv;

    if ((p_dev == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ��ǰϵͳʱ��Ƶ�ʣ�systick ʹ�õ���ϵͳʱ�� */
    *p_freq =  am_clk_rate_get(p_dev->p_devinfo->clk_id);

    return AM_OK;
}

/******************************************************************************/
static int __lptmr_timing_prescale_set (void    *p_drv,
                                        uint8_t  chan,
                                        uint32_t prescale)
{
    am_fsl_lptmr_timing_dev_t *p_dev      = (am_fsl_lptmr_timing_dev_t *)p_drv;
    amhw_fsl_lptmr_t          *p_hw_tim;
    uint8_t                    pre_reg;

    if ((p_drv == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_fsl_lptmr_t *)p_dev->p_devinfo->p_hw_lptmr;

    if ((prescale != 0) && (prescale <= 65536)) {

        /* ֻ֧�ַ�Ƶ��С1,2,4,8...65536����ô��ڷ�Ƶ������С����2^n */
        for (pre_reg = 0; pre_reg < 0xf; pre_reg++) {
            if ((prescale >> pre_reg) == 1) {
                break;
            }
        }

        amhw_fsl_lptmr_prescaler_set(p_hw_tim, (amhw_fsl_lptmr_ps_t)(pre_reg));

        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/******************************************************************************/
static int __lptmr_timing_prescale_get (void     *p_drv,
                                        uint8_t   chan,
                                        uint32_t *p_prescale)
{
    am_fsl_lptmr_timing_dev_t *p_dev      = (am_fsl_lptmr_timing_dev_t *)p_drv;
    amhw_fsl_lptmr_t          *p_hw_tim;

    if ((p_dev == NULL) || (p_prescale == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_fsl_lptmr_t *)p_dev->p_devinfo->p_hw_lptmr;

    /* ��ȡ��Ƶֵ */
    *p_prescale = amhw_fsl_lptmr_ps_reg_get(p_hw_tim);

    return AM_OK;
}

/**
 * \brief ��ȡLPTMR��ǰ����ֵ
 */
static int __lptmr_timing_count_get (void     *p_drv,
                                     uint8_t   chan,
                                     void     *p_count)
{
    am_fsl_lptmr_timing_dev_t *p_dev      = (am_fsl_lptmr_timing_dev_t *)p_drv;
    amhw_fsl_lptmr_t          *p_hw_lptmr =  p_dev->p_devinfo->p_hw_lptmr;

    *(uint32_t *)p_count = amhw_fsl_lptmr_counter_get(p_hw_lptmr);

    return AM_OK;
}

/**
 * \brief ��ȡLPTMR����ֵ
 */
static int __lptmr_timing_rollover_get (void     *p_drv,
                                        uint8_t   chan,
                                        void     *p_rollover)
{
    am_fsl_lptmr_timing_dev_t *p_dev      = (am_fsl_lptmr_timing_dev_t *)p_drv;

    *(uint32_t *)p_rollover = 0xFFFFu / am_clk_rate_get(p_dev->p_devinfo->clk_id);

    return AM_OK;
}

/**
 * \brief LPTMR����
 */
static int __lptmr_timing_disable (void *p_drv, uint8_t chan)
{
    am_fsl_lptmr_timing_dev_t *p_dev    = (am_fsl_lptmr_timing_dev_t *)p_drv;
    amhw_fsl_lptmr_t        *p_hw_lptmr =  p_dev->p_devinfo->p_hw_lptmr;

    /* ����ʹ��λ������ */
    amhw_fsl_lptmr_ctl_clear(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TEN);

    return AM_OK;
}

/**
 * \brief LPTMRʹ�ܲ����ü���ֵ
 */
static int __lptmr_timing_enable (void     *p_drv,
                                  uint8_t   chan,
                                  void     *p_count)
{
    am_fsl_lptmr_timing_dev_t *p_dev    = (am_fsl_lptmr_timing_dev_t *)p_drv;
    amhw_fsl_lptmr_t        *p_hw_lptmr =  p_dev->p_devinfo->p_hw_lptmr;

    uint32_t pre_reg = 0, pre_real;
    uint32_t temp;
    uint32_t lptmr_count = *(uint32_t *)p_count;

    if (lptmr_count > (0xFFFFu * 65536)) {
        return -AM_EINVAL;
    }

    /* ����Ҫ��Ƶ�����ܷ�Ƶ�� */
    if (lptmr_count < 0xFFFF) {
        pre_real = 1;
        amhw_fsl_lptmr_prescaler_filter_set(p_hw_lptmr, AM_TRUE);
    } else {
        temp = lptmr_count / 0xFFFFu + 1;

        /* �����Ƶֵ 2^n */
        for (pre_real = 2; pre_real < temp;) {
            pre_reg++;
            pre_real = pre_real << 1;
        }

        /* ��Ƶ����Ч */
        amhw_fsl_lptmr_prescaler_filter_set(p_hw_lptmr, AM_FALSE);

        /* ����Ԥ��Ƶֵ */
        amhw_fsl_lptmr_prescaler_set(p_hw_lptmr, (amhw_fsl_lptmr_ps_t)pre_reg);
    }

    lptmr_count = lptmr_count / pre_real;

    /* ����װ��ֵ */
    amhw_fsl_lptmr_compare_set(p_hw_lptmr, lptmr_count - 1);

    /* ʹ��LPTMR */
    amhw_fsl_lptmr_ctl_set(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TEN);

    return AM_OK;
}

/**
 * \brief �����жϻص�����
 */
static int __lptmr_timing_callback_set (void     *p_drv,
                                        uint8_t   chan,
                                        void    (*pfn_callback)(void *),
                                        void     *p_arg)
{
    am_fsl_lptmr_timing_dev_t *p_dev      = (am_fsl_lptmr_timing_dev_t *)p_drv;
    amhw_fsl_lptmr_t          *p_hw_lptmr =  p_dev->p_devinfo->p_hw_lptmr;


    if (pfn_callback == NULL) {                     /* ����Ҫ�����ж� */
        amhw_fsl_lptmr_ctl_clear(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TIE);
    } else {                                        /* ��Ҫ�����ж� */
        p_dev->pfn_callback = pfn_callback;
        p_dev->p_arg        = p_arg;
        amhw_fsl_lptmr_ctl_set(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TIE);
    }

    return AM_OK;
}

/**
 * \brief LPTMR��ʼ��
 */
am_timer_handle_t am_fsl_lptmr_timing_init (am_fsl_lptmr_timing_dev_t           *p_dev,
                                            const am_fsl_lptmr_timing_devinfo_t *p_devinfo)
{
    amhw_fsl_lptmr_t *p_hw_lptmr;

    if (NULL == p_dev || NULL == p_devinfo ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_hw_lptmr                = p_devinfo->p_hw_lptmr;
    p_dev->p_devinfo          = p_devinfo;
    p_dev->timer_serv.p_funcs = (struct am_timer_drv_funcs *)&__g_lptmr_timing_drv_funcs;
    p_dev->timer_serv.p_drv   = p_dev;

    p_dev->pfn_callback = NULL;

    /* �ر�LPTMRģ�飬LMTMRԤ��Ƶ�Ĵ���ֻ���ڹر�״̬�²������޸� */
    amhw_fsl_lptmr_ctl_clear(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_MASK);

    am_int_connect(p_dev->p_devinfo->inum, __lptmr_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->timer_serv);
}

/**
 * \brief LPTMR���ʼ��
 */
void am_fsl_lptmr_timing_deinit (am_timer_handle_t handle)
{
    am_fsl_lptmr_timing_dev_t *p_dev      = (am_fsl_lptmr_timing_dev_t *)handle;
    amhw_fsl_lptmr_t          *p_hw_lptmr = NULL;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_lptmr = p_dev->p_devinfo->p_hw_lptmr;

    /* �ر�LPTMRģ�� */
    amhw_fsl_lptmr_ctl_clear(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TEN);

    /* �ر�LPTMR�ж� */
    am_int_disable(p_dev->p_devinfo->inum);

    p_dev->timer_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
