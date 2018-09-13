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
 * \brief ��ʱ�� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOA_0(TIM2_CH1) ��� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \par Դ����
 * \snippet demo_am116_core_hw_tim_pwm.c src_am116_core_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_am116_core_hw_tim_pwm
 * \copydoc demo_am116_core_hw_tim_pwm.c
 */

/** [src_am116_core_hw_tim_pwm] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zlg116.h"
#include "am_zlg116_clk.h"
#include "demo_zlg_entries.h"

/**
 * \brief �������
 */
void demo_am116_core_hw_tim_pwm_entry (void)
{
    AM_DBG_INFO("demo am116_core hw tim pwm!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_AF_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λ��ʱ�� */
    am_zlg116_clk_reset(CLK_TIM2);

    demo_zlg_hw_tim_pwm_entry(ZLG116_TIM2,
                                 AMHW_ZLG_TIM_TYPE1,
                                 0,
                                 am_clk_rate_get(CLK_TIM2),
                                 INUM_TIM2);
}
/** [src_am116_core_hw_tim_pwm] */

/* end of file */
