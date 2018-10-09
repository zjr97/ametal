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
 * \brief SCT ��Ϊ 2 �� 16 λ��ʱ����� PWM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_23(SCT_OUT0) ��� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *   2. PIO0_27(SCT_OUT2) ��� 1KHz �� PWM��ռ�ձ�Ϊ 25%��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. SCT ʹ�� 32 λ��������ֻ�ܲ���һ������� PWM������ PWM ���ʹ��ͬһƵ�ʣ�
 *       �����������ƥ��ֵΪ 0xFFFFFFFF��
 *    3. SCT ʹ�� 16 λ�����������Բ��� 2 ������� PWM��ÿһ�� PWM �����ʹ��ͬһ
 *       Ƶ�ʣ������������ƥ��ֵΪ 0xFFFF��
 *    4. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_am824_hw_sct_2_16bit_pwm.c src_am824_hw_sct_2_16bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-19  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_sct_2_16bit_pwm
 * \copydoc demo_am824_hw_sct_2_16bit_pwm.c
 */

/** [src_am824_hw_sct_2_16bit_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_sct_2_16bit_pwm_entry (void)
{
    uint32_t frq = 0;
    am_kprintf("demo am824_core hw sct 2_16bit pwm \r\n");

    AM_DBG_INFO("The PIO0_23(SCT_OUT0) PWM: freq is 4kHz, "
                "The duty ratio is 50%% \r\n");
    AM_DBG_INFO("The PIO0_27(SCT_OUT4) PWM: freq is 1kHz, "
                "The duty ratio is 25%% \r\n");

    /* ƽ̨��ʼ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SCT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);

    /* PIO0_23 ������ SCT �����ͨ�� 0��PIO0_27 ������ SCT �����ͨ�� 2 */
    am_gpio_pin_cfg(PIO0_23, PIO_FUNC_SCT_OUT1);
    am_gpio_pin_cfg(PIO0_27, PIO_FUNC_SCT_OUT2);

    frq = amhw_lpc82x_clk_system_clkrate_get();
  
    demo_lpc_hw_sct_2_16bit_pwm_entry(LPC82X_SCT0, frq);
    
}
/** [src_am824_hw_sct_2_16bit_pwm] */

/* end of file */
