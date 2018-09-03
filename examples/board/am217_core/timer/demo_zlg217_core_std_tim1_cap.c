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
 * \brief TIM1 ��ʱ�� CAP ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ��� PIOB_6 �� PIOA_11 ���ӡ�
 *
 * - ʵ������
 *   1. TIM4 ͨ�� PIOB_6 ������� 2KHz �� PWM��
 *   2. TIM1 ��������ͨ�� 4 ʹ�� PIOA_11 ���Ų���
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
 * \snippet demo_zlg217_std_tim1_cap.c src_zlg217_std_tim1_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-04  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_tim1_cap
 * \copydoc demo_zlg217_std_tim1_cap.c
 */

/** [src_zlg217_std_tim1_cap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg217_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_tim1_cap_entry (void)
{

    am_pwm_handle_t tim4_pwm_handle = am_zlg217_tim4_pwm_inst_init();
    am_cap_handle_t tim1_cap_handle = am_zlg217_tim1_cap_inst_init();
    
	  AM_DBG_INFO("demo am217_core std tim1 cap!\r\n");

    /* TIM2 ���Ƶ��Ϊ 2KHz �� PWM */
    am_pwm_config(tim4_pwm_handle, 0, 500000 / 2, 500000);
    am_pwm_enable(tim4_pwm_handle, 0);

    demo_std_timer_cap_entry(tim1_cap_handle, 3);
}
/** [src_zlg217_std_tim1_cap] */

/* end of file */
