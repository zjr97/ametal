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
 * \brief KL26 TPM1 ����PWM��� �û������ļ�
 * \sa am_fsl_hwconfig_tpm1_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-18  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_sim.h"
#include "am_fsl_tpm_pwm.h"
#include "../../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_tpm1_pwm
 * \copydoc am_kl26_hwconfig_tpm1_pwm.c
 * @{
 */

/** \brief TPM1����PWM��� ƽ̨��ʼ�� */
void __kl26_plfm_tpm1_pwm_init (void)
{
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TPM1);
    amhw_kl26_sim_tpm_src_set(KL26_SIM_TPMSRC_PLLFLLCLK);
}

/** \brief ���TPM1ƽ̨��ʼ�� */
void __kl26_plfm_tpm1_pwm_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_TPM1);
}

/** \brief TPM1����PWM���ܵ�����������Ϣ�б� */
am_fsl_tpm_pwm_ioinfo_t __g_tpm1_pwm_ioinfo_list[] = {
    {PIOE_20, PIOE_20_TPM1_CH0, PIOE_20_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��0 */
    {PIOE_21, PIOE_21_TPM1_CH1, PIOE_21_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��1 */
};

/** \brief TPM1����PWM�豸��Ϣ */
const am_fsl_tpm_pwm_devinfo_t  __g_tpm1_pwm_devinfo = {
    KL26_TPM1,                       /**< \brief ָ��TPM1�Ĵ������ָ�� */
    2,                               /**< \brief 2��PWM���ͨ�� */
    CLK_TPM1,                        /**< \brief ʱ�Ӻ� */
    &__g_tpm1_pwm_ioinfo_list[0],
    __kl26_plfm_tpm1_pwm_init,       /**< \brief ƽ̨��ʼ������ */
    __kl26_plfm_tpm1_pwm_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TPM1����PWM�豸���� */
am_fsl_tpm_pwm_dev_t  __g_tpm1_pwm_dev;

/** \brief tpm2 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_kl26_tpm1_pwm_inst_init (void)
{
    return am_fsl_tpm_pwm_init(&__g_tpm1_pwm_dev,
                               &__g_tpm1_pwm_devinfo);
}

/** \brief tpm2 pwm ʵ�����ʼ�� */
void am_kl26_tpm1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_fsl_tpm_pwm_deinit(handle);
}

/**
 * @}
 */

/* end of file */
