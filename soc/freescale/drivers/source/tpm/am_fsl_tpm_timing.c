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
 * \brief TPM ��ʱ����������ʵ��
 *
 * 1. TPM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���"��ʱ"��׼���������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. һ��TPMģ�飬ֻ��һ����ʱͨ��
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */

#include "am_fsl_tpm_timing.h"
#include "am_int.h"
#include "am_clk.h"

/*******************************************************************************
  ��ʱ��������������
*******************************************************************************/

static const am_timer_info_t *__tpm_timing_info_get (void *p_drv);

static int __tmp_timing_clkin_freq_get (void *p_drv, uint32_t *p_freq);

static int __tpm_timing_count_get (void     *p_drv,
                                   uint8_t   chan,
                                   void     *p_count);

static int __tpm_timing_prescale_set (void    *p_drv,
                                      uint8_t  chan,
                                      uint32_t prescale);

static int __tpm_timing_prescale_get (void     *p_drv,
                                      uint8_t   chan,
                                      uint32_t *p_prescale);

static int __tpm_timing_rollover_get (void     *p_drv,
                                      uint8_t   chan,
                                      void     *p_rollover);

static int __tpm_timing_disable (void *p_drv, uint8_t chan);

static int __tpm_timing_enable (void     *p_drv,
                                uint8_t   chan,
                                void     *p_count);

static int __tpm_timing_callback_set (void    *p_drv,
                                      uint8_t  chan,
                                      void   (*pfn_callback)(void *),
                                      void    *p_arg);

static void __tpm_irq_handler (void *p_arg);

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/* ��ʱ����Ϣ */
static const am_timer_info_t __g_tpm_timing_info = {
    16,                                      /* 16λ��ʱ��               */
    1,                                       /* ��ͨ��                   */
    AM_TIMER_CAN_INTERRUPT      |            /* ���Բ����ж� */
    AM_TIMER_INTERMEDIATE_COUNT |            /* ����ʵʱ��������ֵ */
    AM_TIMER_AUTO_RELOAD,                    /* �Զ�װ�� */
    128                                      /* Ԥ��Ƶ���ֵ��128      */
};

/** \brief TPM��ʱ���������� */
static const struct am_timer_drv_funcs __g_tpm_timing_drv_funcs = {
    __tpm_timing_info_get,
    __tmp_timing_clkin_freq_get,
    __tpm_timing_prescale_set,
    __tpm_timing_prescale_get,
    __tpm_timing_count_get,
    __tpm_timing_rollover_get,
    __tpm_timing_enable,
    __tpm_timing_disable,
    __tpm_timing_callback_set,
};

/******************************************************************************/

void __tpm_irq_handler (void *p_arg)
{
    am_fsl_tpm_timing_dev_t *p_dev    = (am_fsl_tpm_timing_dev_t *)p_arg;
    amhw_fsl_tpm_t          *p_hw_tpm =  p_dev->p_devinfo->p_hw_tpm;

    /*
     * �ж��Ƿ��Ƕ�ʱ������ж�
     */
    if (amhw_fsl_tpm_stat_flag_get(p_hw_tpm) & AMHW_FSL_TPM_STAT_OV_FLAG ) {

        if (p_dev->pfn_callback != NULL) {
            p_dev->pfn_callback(p_dev->p_arg);
        }

        /* ��������־ */
        amhw_fsl_tpm_stat_flag_clear(p_hw_tpm, AMHW_FSL_TPM_STAT_OV_FLAG);
    }
}

/** \brief ��ȡTPM��Ϣ */
static const am_timer_info_t *__tpm_timing_info_get (void *p_drv)
{
    return &__g_tpm_timing_info;
}

/** \brief ��ȡTPMʱ��Ƶ����Ϣ */
static int __tmp_timing_clkin_freq_get (void *p_drv, uint32_t *p_freq)
{
    am_fsl_tpm_timing_dev_t *p_dev    = (am_fsl_tpm_timing_dev_t *)p_drv;

    if ((p_dev == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ��ǰϵͳʱ��Ƶ�ʣ�systick ʹ�õ���ϵͳʱ�� */
    *p_freq =  am_clk_rate_get(p_dev->p_devinfo->clk_id);

    return AM_OK;
}

/**
 * \brief ��ȡTPM��ǰ����ֵ
 */
static int __tpm_timing_count_get (void     *p_drv,
                                   uint8_t   chan,
                                   void     *p_count)
{
    am_fsl_tpm_timing_dev_t *p_dev    = (am_fsl_tpm_timing_dev_t *)p_drv;
    amhw_fsl_tpm_t          *p_hw_tpm =  p_dev->p_devinfo->p_hw_tpm;

    *(uint32_t *)p_count = amhw_fsl_tpm_count_get(p_hw_tpm);

    return AM_OK;
}

/******************************************************************************/
static int __tpm_timing_prescale_set (void    *p_drv,
                                      uint8_t  chan,
                                      uint32_t prescale)
{
    am_fsl_tpm_timing_dev_t *p_dev      = (am_fsl_tpm_timing_dev_t *)p_drv;
    uint8_t                  pre_reg    = 0;
    amhw_fsl_tpm_t          *p_hw_tpm;

    if ((p_drv == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_tpm = (amhw_fsl_tpm_t *)p_dev->p_devinfo->p_hw_tpm;

    if ((prescale != 0) && (prescale <= 65536)) {

        /* ֻ֧�ַ�Ƶ��С1,2,4,8...128����ô��ڷ�Ƶ������С����2^n */
        for (pre_reg = 0; pre_reg < 8; pre_reg++) {
            if ((prescale >> pre_reg) == 1) {
                break;
            }
        }

        amhw_fsl_tpm_prescale_set(p_hw_tpm, (amhw_fsl_tpm_prescale_t)(pre_reg));

        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/******************************************************************************/
static int __tpm_timing_prescale_get (void     *p_drv,
                                      uint8_t   chan,
                                      uint32_t *p_prescale)
{
    am_fsl_tpm_timing_dev_t *p_dev      = (am_fsl_tpm_timing_dev_t *)p_drv;
    amhw_fsl_tpm_t          *p_hw_tim;
    amhw_fsl_tpm_prescale_t  prescale;

    if ((p_dev == NULL) || (p_prescale == NULL) || (chan != 0)) {
        return -AM_EINVAL;
    }

    p_hw_tim = (amhw_fsl_tpm_t *)p_dev->p_devinfo->p_hw_tpm;

    /* ��ȡ��Ƶֵ */
    prescale = amhw_tpm_prescale_get(p_hw_tim);

    *p_prescale = (uint32_t)1 << prescale;

    return AM_OK;
}

/**
 * \brief ��ȡTPM����ֵ
 */
static int __tpm_timing_rollover_get (void     *p_drv,
                                      uint8_t   chan,
                                      void     *p_rollover)
{
    am_fsl_tpm_timing_dev_t *p_dev    = (am_fsl_tpm_timing_dev_t *)p_drv;

    *(uint32_t *)p_rollover = 0xFFFF / am_clk_rate_get(p_dev->p_devinfo->clk_id);


    return AM_OK;
}

/**
 * \brief TPM����
 */
static int __tpm_timing_disable (void *p_drv, uint8_t chan)
{
    am_fsl_tpm_timing_dev_t *p_dev    = (am_fsl_tpm_timing_dev_t *)p_drv;
    amhw_fsl_tpm_t          *p_hw_tpm =  p_dev->p_devinfo->p_hw_tpm;

    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_NONE);

    return AM_OK;
}

/**
 * \brief TPMʹ�ܲ����ü���ֵ
 */
static int __tpm_timing_enable (void     *p_drv,
                                uint8_t   chan,
                                void     *p_count)
{
    am_fsl_tpm_timing_dev_t *p_dev    = (am_fsl_tpm_timing_dev_t *)p_drv;
    amhw_fsl_tpm_t          *p_hw_tpm =  p_dev->p_devinfo->p_hw_tpm;

    uint32_t match, temp;
    uint8_t  pre_real, pre_reg = 0;
    uint32_t tpm_count     = *(uint32_t *)p_count;

    /* 16λ���������ֵ65535,��Ƶ�����ֵ128 */
    if (tpm_count > (0xFFFFu * 128)) {
        return -AM_EINVAL;
    }

    temp = tpm_count / 0xFFFFu + 1;

    /* ֻ֧�ַ�Ƶ��С1,2,4,8...128����ô��ڷ�Ƶ������С����2^n */
    for (pre_real = 1; pre_real < temp; ) {
        pre_reg++;                   /* ����д��Ĵ����ķ�Ƶֵ0,1,2,... */
        pre_real = pre_real << 1;           /* ��Ƶ��2^n */
    }
    match = tpm_count / pre_real ;

    if (pre_real > 1) {    /* ��Ҫ��Ƶ */
        amhw_fsl_tpm_prescale_set(p_hw_tpm, (amhw_fsl_tpm_prescale_t)(pre_reg));
    }

    amhw_fsl_tpm_count_clear(p_hw_tpm);
    amhw_fsl_tpm_mod_set(p_hw_tpm, match - 1);
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_MODULE);

    return AM_OK;
}

/**
 * \brief �����жϻص�����
 */
static int __tpm_timing_callback_set (void     *p_drv,
                                      uint8_t   chan,
                                      void    (*pfn_callback)(void *),
                                      void     *p_arg)
{
    am_fsl_tpm_timing_dev_t *p_dev    = (am_fsl_tpm_timing_dev_t *)p_drv;
    amhw_fsl_tpm_t          *p_hw_tpm =  p_dev->p_devinfo->p_hw_tpm;


    /* ����Ҫ�����ж� */
    if (pfn_callback == NULL) {
        amhw_fsl_tpm_ctrl_clear(p_hw_tpm, AMHW_FSL_TPM_SC_TOI_EN);

    } else {
        p_dev->pfn_callback = pfn_callback;
        p_dev->p_arg   = p_arg;

        amhw_fsl_tpm_ctrl_set(p_hw_tpm, AMHW_FSL_TPM_SC_TOI_EN);
    }

    return AM_OK;
}

/**
 * \brief TPM��ʼ��
 */
am_timer_handle_t
am_fsl_tpm_timing_init (am_fsl_tpm_timing_dev_t           *p_dev,
                        const am_fsl_tpm_timing_devinfo_t *p_devinfo)
{

    if (NULL == p_dev || NULL == p_devinfo ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo          = p_devinfo;
    p_dev->timer_serv.p_funcs = (struct am_timer_drv_funcs *)&__g_tpm_timing_drv_funcs;
    p_dev->timer_serv.p_drv   = p_dev;

    p_dev->pfn_callback = NULL;
    p_dev->p_arg        = NULL;

    am_int_connect(p_dev->p_devinfo->inum, __tpm_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->timer_serv);
}

/**
 * \brief TPM���ʼ��
 */
void am_fsl_tpm_timing_deinit (am_timer_handle_t handle)
{

    am_fsl_tpm_timing_dev_t *p_dev    = (am_fsl_tpm_timing_dev_t *)handle;
    amhw_fsl_tpm_t          *p_hw_tpm = NULL;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    p_hw_tpm = p_dev->p_devinfo->p_hw_tpm;

    /* �ر�ʱ�ӣ�ֹͣ���� */
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_NONE);

    am_int_disable(p_dev->p_devinfo->inum);

    p_dev->timer_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
