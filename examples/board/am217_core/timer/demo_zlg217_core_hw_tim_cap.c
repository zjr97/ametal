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
 * \brief ��ʱ�� CAP �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ��� PIOB_6 �� PIOA_6 ���ӡ�
 *
 * - ʵ������
 *   1. TIM4 ͨ�� PIOB_6 ������� 2KHz �� PWM��
 *   2. TIM3 ��������ͨ�� 1 ʹ�� PIOA_6 ���Ų���
 *   3. ���ڴ�ӡ�����ò����ܵõ��� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ���� TIM4 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *       am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SOFTIMER_ENABLE
 *       �� AM_CFG_SYSTEM_TICK_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_zlg217_hw_tim_cap.c src_zlg217_hw_tim_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-04  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_hw_tim_cap
 * \copydoc demo_zlg217_hw_tim_cap.c
 */

/** [src_zlg217_hw_tim_cap] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_zlg217.h"
#include "am_zlg217_clk.h"
#include "am_zlg217_inst_init.h"
#include "demo_zlg_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_hw_tim_cap_entry (void)
{
    am_pwm_handle_t tim4_pwm_handle = am_zlg217_tim4_pwm_inst_init();

    AM_DBG_INFO("demo am217_core hw tim cap!\r\n");

    /* TIM4 ���Ƶ��Ϊ 2KHz �� PWM */
    am_pwm_config(tim4_pwm_handle, 0, 500000 / 2, 500000);

    am_pwm_enable(tim4_pwm_handle, 0);

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_6, PIOA_6_TIM3_CH1_REMAP0 | PIOA_6_INPUT_FLOAT);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM3);

    /* ��λ��ʱ�� */
    am_zlg217_clk_reset(CLK_TIM3);

    demo_zlg_hw_tim_cap_entry(ZLG217_TIM3,
                              AMHW_ZLG_TIM_TYPE1,
                              0,
                              am_clk_rate_get(CLK_TIM3),
                              INUM_TIM3);    
}
/** [src_zlg217_hw_tim_cap] */

/* end of file */
