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
 * \brief TPM������PWM������ʵ��
 *
 * 1. TPM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���"PWM���"��׼���������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 *
 * \note һ��TPM������ͨ������һ������ֵ��Ҳ����˵ͬһ��TPM��ͬ��ͨ����PWM������ͬ
 *          ��TPM0��6��ͨ����TPM1��TPM1����2��ͨ����
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */

#include "am_fsl_tpm_pwm.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"

/*******************************************************************************
* ��������
*******************************************************************************/

/** \brief ����PWM  */
static int __tpm_pwm_config (void          *p_drv,
                             int            chan,
                             unsigned long  duty_ns,
                             unsigned long  period_ns);

/** \brief ʹ��PWM��� */
static int __tpm_pwm_enable (void *p_drv, int chan);

/** \brief ����PWM��� */
static int __tpm_pwm_disable (void *p_drv, int chan);

/** \brief PWM�������� */
static const struct am_pwm_drv_funcs __g_tpm_pwm_drv_funcs = {
    __tpm_pwm_config,
    __tpm_pwm_enable,
    __tpm_pwm_disable,
};

/******************************************************************************/
/** \brief ����PWM  */
static int __tpm_pwm_config (void          *p_drv,
                             int            chan,
                             unsigned long  duty_ns,
                             unsigned long  period_ns)
{
    am_fsl_tpm_pwm_dev_t *p_dev    = (am_fsl_tpm_pwm_dev_t *)p_drv;
    amhw_fsl_tpm_t       *p_hw_tpm = p_dev->p_devinfo->p_hw_tpm;

    uint32_t clkfreq;
    uint32_t period_c, duty_c;
    uint8_t  pre_real, pre_reg = 0, temp;

    /* �������Ϸ� */
    if ((period_ns == 0) || (duty_ns > period_ns)) {
        return -AM_EINVAL;
    }

    /* ��Чͨ����Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    clkfreq = am_clk_rate_get(p_dev->p_devinfo->clk_id);

    period_c = (uint64_t)(period_ns) * (clkfreq) / (uint64_t)1000000000;
    duty_c   = (uint64_t)(duty_ns)   * (clkfreq) / (uint64_t)1000000000;

    /* 16λ��ʱ�������128��Ƶ */
    if (period_c > (0xffffu * 128)) {
        return -AM_EINVAL;
    }

    temp = period_c / 0xffffu + 1;          /* �����Ƶ��С */

    /* ֻ֧�ַ�Ƶ��С1,2,4,8...128����ô��ڷ�Ƶ������С����2^n */
    for (pre_real = 1; pre_real < temp; ) {
        pre_reg++;                        /* ����д��Ĵ����ķ�Ƶֵ0,1,2,... */
        pre_real = pre_real << 1;           /* ��Ƶ��2^n */
    }
    amhw_fsl_tpm_prescale_set(p_hw_tpm, (amhw_fsl_tpm_prescale_t)pre_reg);

    period_c = period_c / pre_real;

    /* ��������Ϊ1 */
    if (period_c == 0) {
        period_c = 1;
    }
    amhw_fsl_tpm_mod_set(p_hw_tpm, period_c - 1);

    if (duty_c == 0) {
        duty_c = 1;
    }
    duty_c = duty_c / pre_real;
    if (duty_c == period_c) {
        amhw_fsl_tpm_ch_value_set(p_hw_tpm, AMHW_FSL_TPM_CH(chan), duty_c);
    } else {
        amhw_fsl_tpm_ch_value_set(p_hw_tpm, AMHW_FSL_TPM_CH(chan), duty_c - 1);
    }

    return AM_OK;
}

/**
 * \brief ʹ��PWMͨ�����
 */
static int __tpm_pwm_enable (void *p_drv, int chan)
{
    am_fsl_tpm_pwm_dev_t    *p_dev    = (am_fsl_tpm_pwm_dev_t *)p_drv;
    amhw_fsl_tpm_t          *p_hw_tpm = p_dev->p_devinfo->p_hw_tpm;
    am_fsl_tpm_pwm_ioinfo_t *p_ioinfo = p_dev->p_devinfo->p_ioinfo;

    /* ��Чͨ����Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    /* ѡ�����ϼ��� */
    amhw_fsl_tpm_ch_mode(p_hw_tpm, chan, AMHW_FSL_TPM_COUNTING_UP,
                     AMHW_FSL_TPM_CHSC_MS(2) | AMHW_FSL_TPM_CHSC_EL_SEL(2));

    am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].func);

    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_MODULE);

    return AM_OK;
}

/**
 * \brief ����PWMͨ�����
 */
static int __tpm_pwm_disable (void *p_drv, int chan)
{
    am_fsl_tpm_pwm_dev_t    *p_dev      = (am_fsl_tpm_pwm_dev_t *)p_drv;
    amhw_fsl_tpm_t          *p_hw_tpm   = p_dev->p_devinfo->p_hw_tpm;
    am_fsl_tpm_pwm_ioinfo_t *p_ioinfo   = p_dev->p_devinfo->p_ioinfo;

    /* ��Чͨ����Χ 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_NONE);
    am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].dfunc);

    return AM_OK;
}

/**
  * \brief pwm��ʼ��
  */
void __tpm_pwm_init (amhw_fsl_tpm_t *p_hw_tpm)
{
    /* ��ͣ������ */
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_NONE);

    /* ʹ��ϵͳʱ�ӣ������з�Ƶ */
    amhw_fsl_tpm_prescale_set(p_hw_tpm, AMHW_FSL_TPM_DIVIDED_BY_1);
}

/**
  * \brief tpm pwm�����ʼ��
  */
am_pwm_handle_t am_fsl_tpm_pwm_init (am_fsl_tpm_pwm_dev_t           *p_dev,
                                     const am_fsl_tpm_pwm_devinfo_t *p_devinfo)
{
    amhw_fsl_tpm_t *p_hw_tpm;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_hw_tpm                = p_devinfo->p_hw_tpm;
    p_dev->p_devinfo        = p_devinfo;
    p_dev->pwm_serv.p_funcs = (struct am_pwm_drv_funcs *)&__g_tpm_pwm_drv_funcs;
    p_dev->pwm_serv.p_drv   = p_dev;

    __tpm_pwm_init(p_hw_tpm);

    return &(p_dev->pwm_serv);
}


void am_fsl_tpm_pwm_deinit (am_pwm_handle_t handle)
{

    am_fsl_tpm_pwm_dev_t *p_dev    = (am_fsl_tpm_pwm_dev_t *)handle;
    amhw_fsl_tpm_t       *p_hw_tpm = NULL;

    if (p_dev == NULL ) {
        return;
    }

    p_hw_tpm = p_dev->p_devinfo->p_hw_tpm;
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_NONE);

    p_dev->pwm_serv.p_drv = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
