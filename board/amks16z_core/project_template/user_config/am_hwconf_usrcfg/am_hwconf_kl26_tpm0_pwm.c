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
 * \brief KL26 TPM0 ����PWM��� �û������ļ�
 * \sa am_fsl_hwconfig_tpm0_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-18  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_kl26.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_sim.h"
#include "am_fsl_tpm_pwm.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_tpm0_pwm
 * \copydoc am_kl26_hwconfig_tpm0_pwm.c
 * @{
 */

/** \brief TPM0����PWM��� ƽ̨��ʼ�� */
void __kl26_plfm_tpm0_pwm_init (void)
{
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TPM0);
    amhw_kl26_sim_tpm_src_set(KL26_SIM_TPMSRC_PLLFLLCLK);
}

/** \brief ���TPM0ƽ̨��ʼ�� */
void __kl26_plfm_tpm0_pwm_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_TPM0);
}

/** \brief TPM0����PWM���ܵ�����������Ϣ�б� */
am_fsl_tpm_pwm_ioinfo_t __g_tpm0_pwm_ioinfo_list[] = {
    {PIOD_0, PIOD_0_TPM0_CH0, PIOD_0_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��0 */
    {PIOD_1, PIOD_1_TPM0_CH1, PIOD_1_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��1 */
    {PIOC_3, PIOC_3_TPM0_CH2, PIOC_3_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��2 */
    {PIOD_3, PIOD_3_TPM0_CH3, PIOD_3_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��3 */
    {PIOD_4, PIOD_4_TPM0_CH4, PIOD_4_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��4 */
    {PIOD_5, PIOD_5_TPM0_CH5, PIOD_5_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��5 */
};

/** \brief TPM0����PWM�豸��Ϣ */
const am_fsl_tpm_pwm_devinfo_t  __g_tpm0_pwm_devinfo = {
    KL26_TPM0,                  /**< \brief ָ��TPM0�Ĵ������ָ�� */
    6,                               /**< \brief 6��PWM���ͨ�� */
    CLK_TPM0,                        /**< \brief ʱ�Ӻ� */
    &__g_tpm0_pwm_ioinfo_list[0],
    __kl26_plfm_tpm0_pwm_init,       /**< \brief ƽ̨��ʼ������ */
    __kl26_plfm_tpm0_pwm_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TPM0����PWM�豸���� */
am_fsl_tpm_pwm_dev_t  __g_tpm0_pwm_dev;

/** \brief tpm0 Timer ʵ����ʼ�������Timer��׼������ */
am_pwm_handle_t am_kl26_tpm0_pwm_inst_init (void)
{
    return am_fsl_tpm_pwm_init(&__g_tpm0_pwm_dev,
                               &__g_tpm0_pwm_devinfo);
}

/** \brief tpm0 pwm ʵ�����ʼ�� */
void am_kl26_tpm0_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_fsl_tpm_pwm_deinit(handle);
}

/**
 * @}
 */

/* end of file */
