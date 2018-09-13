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
 * \brief TIM4 ��ʱ�� PWM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOB_6(TIM4_CH1)��� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \note
 *    ���� TIM4 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *    am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SOFTIMER_ENABLE
 *    �� AM_CFG_SYSTEM_TICK_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_zlg217_std_tim4_pwm.c src_zlg217_std_tim4_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-28  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_tim4_pwm
 * \copydoc demo_zlg217_std_tim4_pwm.c
 */

/** [src_zlg217_std_tim4_pwm] */

#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zlg217_inst_init.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_tim4_pwm_entry (void)
{
    AM_DBG_INFO("demo am217_core std tim14 pwm!\r\n");

    demo_std_timer_pwm_entry(am_zlg217_tim4_pwm_inst_init(), 0);
}
/** [src_zlg217_std_tim4_pwm] */

/* end of file */
