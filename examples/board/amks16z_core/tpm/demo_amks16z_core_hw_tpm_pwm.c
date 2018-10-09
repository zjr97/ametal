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
 * \snippet demo_amks16z_core_hw_tpm_pwm.c src_amks16z_core_hw_tpm_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_hw_tpm_pwm
 * \copydoc demo_amks16z_core_hw_tpm_pwm.c
 */
 
/** [src_amks16z_core_hw_tpm_pwm] */
#include "ametal.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_kl26_clk.h"
#include "hw/amhw_fsl_tpm.h"
#include "hw/amhw_kl26_sim.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_tpm_pwm_entry (void)
{

    uint32_t tpm_clk;

    /* ƽ̨��ʼ�� */
    amhw_kl26_sim_tpm_src_set(KL26_SIM_TPMSRC_PLLFLLCLK);
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TPM0);

    am_gpio_pin_cfg(PIOD_0, PIOD_0_TPM0_CH0);
    am_gpio_pin_cfg(PIOD_1, PIOD_1_TPM0_CH1);

    tpm_clk = am_kl26_clk_periph_rate_get(KL26_TPM0);

    demo_fsl_hw_tpm_pwm_entry(KL26_TPM0, tpm_clk);

}

/** [src_amks16z_core_hw_tpm_pwm] */

/* end of file */
