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
 * \brief TPMʵ�ֲ����ܣ�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. ������ò����ܵõ���PWM�źŵ����ں�Ƶ�ʡ�
 *
 * - ע�⣺
 *   1. TPM1ͨ��PIOE_23�������PWM��
 *   2. TPM1��������ͨ��0ʹ��PIOE_20���ţ�
 *   3. ����PIOE_23���ź�PIOE_20���ţ�ʹ�ò������PWMƵ�ʡ�
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_tpm_cap.c src_amks16z_core_hw_tpm_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_amks16z_core_if_hw_tpm_cap
 * \copydoc demo_amks16z_core_hw_tpm_cap.c
 */
 
/** [src_amks16z_core_hw_tpm_cap] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_pwm.h"
#include "am_vdebug.h"
#include "am_kl26_clk.h"
#include "hw/amhw_fsl_tpm.h"
#include "hw/amhw_kl26_sim.h"
#include "am_kl26_inst_init.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_tpm_cap_entry (void)
{
    am_pwm_handle_t tpm2_pwm_handle;
    uint32_t        tpm_clock;

    /* ƽ̨��ʼ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TPM1);
    amhw_kl26_sim_tpm_src_set(KL26_SIM_TPMSRC_PLLFLLCLK);

    /* ������������ */
    am_gpio_pin_cfg(PIOE_20, PIOE_20_TPM1_CH0 | AM_GPIO_INPUT);

    tpm_clock = am_kl26_clk_periph_rate_get(KL26_TPM1);

    tpm2_pwm_handle = am_kl26_tpm2_pwm_inst_init();

    demo_fsl_hw_tpm_cap_entry(tpm2_pwm_handle,
                              KL26_TPM1,
                              INUM_TPM1,
                              tpm_clock);
}
 
/** [src_amks16z_core_hw_tpm_cap] */

/* end of file */
