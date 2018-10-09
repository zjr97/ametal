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
 * \brief TPMʵ��PWM���ܣ�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOD_0(TPM_OUT0)���4kHz��PWM��ռ�ձ�Ϊ50%��
 *   2. PIOD_1(TPM_OUT1)���4kHz��PWM��ռ�ձ�Ϊ25%��
 *
 * \par Դ����
 * \snippet demo_fsl_hw_tpm_pwm.c src_fsl_hw_tpm_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_fsl_if_hw_tpm_pwm
 * \copydoc demo_fsl_hw_tpm_pwm.c
 */
 
/** [src_fsl_hw_tpm_pwm] */
#include "ametal.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hw/amhw_fsl_tpm.h"
#include "am_board.h"


int tpm_pwm_config (amhw_fsl_tpm_t *p_hw_tpm,
                    int             chan,
                    unsigned long   duty_ns,
                    unsigned long   period_ns,
                    uint32_t        clkfreq)
{
    uint32_t period_c, duty_c;
    uint8_t  prescale, write_pre = 0, temp;

    /* �������Ϸ� */
    if ((period_ns == 0) || (duty_ns > period_ns)) {
        return -AM_EINVAL;
    }

    period_c = (uint64_t)(period_ns) * (clkfreq) / (uint64_t)1000000000;
    duty_c   = (uint64_t)(duty_ns)   * (clkfreq) / (uint64_t)1000000000;

    /* 16λ��ʱ�������128��Ƶ */
    if (period_c > (0xffffu * 128)) {
        return -AM_EINVAL;
    }

    temp = period_c / 0xffffu + 1;          /* �����Ƶ��С */

    /* ֻ֧�ַ�Ƶ��С1,2,4,8...128����ô��ڷ�Ƶ������С����2^n */
    for (prescale = 1; prescale < temp; ) {
        write_pre++;                        /* ����д��Ĵ����ķ�Ƶֵ0,1,2,... */
        prescale = prescale << 1;           /* ��Ƶ��2^n */
    }
    amhw_fsl_tpm_prescale_set(p_hw_tpm, (amhw_fsl_tpm_prescale_t)write_pre);

    period_c = period_c / prescale;

    /* ��������Ϊ1 */
    if (period_c == 0) {
        period_c = 1;
    }
    amhw_fsl_tpm_mod_set(p_hw_tpm, period_c - 1);

    if (duty_c == 0) {
        duty_c = 1;
    }
    duty_c = duty_c / prescale;
    amhw_fsl_tpm_ch_value_set(p_hw_tpm, AMHW_FSL_TPM_CH(chan), duty_c - 1);

    return AM_OK;
}

void tpm_pwm_enable (amhw_fsl_tpm_t *p_hw_tpm, int chan)
{
    /* ѡ�����ϼ���,PWMģʽ */
    amhw_fsl_tpm_ch_mode(p_hw_tpm, chan, AMHW_FSL_TPM_COUNTING_UP,
                          AMHW_FSL_TPM_CHSC_MS(2) | AMHW_FSL_TPM_CHSC_EL_SEL(2));

    /* ��ʼ���� */
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_MODULE);

    return;
}

/**
 * \brief �������
 */
void demo_fsl_hw_tpm_pwm_entry (amhw_fsl_tpm_t *p_hw_tpm,
                                uint32_t        clkfreq)
{
    
    AM_DBG_INFO("The demo for TPM output PWM:\r\n");
    AM_DBG_INFO("The PIOD_0(TPM_OUT0) PWM: freq is 4kHz, The duty ratio is 50% \r\n");
    AM_DBG_INFO("The PIOD_1(TPM_OUT1) PWM: freq is 4kHz, The duty ratio is 25% \r\n");

    tpm_pwm_config(p_hw_tpm,
                   AMHW_FSL_TPM_CH(0),      /* ͨ���� */
                   250000 / 2,              /* ռ�ձ�(ns) */
                   250000,                  /* ���ڣ�ns�� */
                   clkfreq);

    tpm_pwm_config(p_hw_tpm,
                   AMHW_FSL_TPM_CH(1),      /* ͨ���� */
                   250000 / 4,              /* ռ�ձ�(ns) */
                   250000,                  /* ���ڣ�ns�� */
                   clkfreq);

    tpm_pwm_enable(p_hw_tpm, AMHW_FSL_TPM_CH(0));
    tpm_pwm_enable(p_hw_tpm, AMHW_FSL_TPM_CH(1));
    
    while (1) {
        
        am_led_toggle(LED0);
        am_mdelay(500);
    }
}

/** [src_fsl_hw_tpm_pwm] */

/* end of file */
