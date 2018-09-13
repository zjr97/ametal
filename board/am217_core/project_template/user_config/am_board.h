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
 * \brief AM217_CORE
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation
 * \endinternal
 */
#ifndef __AM_BOARD_H
#define __AM_BOARD_H

#include "ametal.h"
#include "am_prj_config.h"
#include "am_delay.h"
#include "am_led.h"
#include "am_pwm.h"
#include "am_timer.h"
#include "am_vdebug.h"

/** \brief LED ���� ID �� */
#define LED0          0
#define LED1          1

#if (AM_CFG_BUZZER_ENABLE == 1)

/**
 * \brief ������ʹ�õĶ�ʱ���� handle
 *
 * ��ʹ�÷�����ʱ��Ĭ�Ͻ�ʹ�� TIM3 �� OUT1 ��� PWM ���Σ�����Ѿ��� TIM3 ��ʼ��Ϊ
 * PWM ����
 */
extern am_pwm_handle_t g_buzzer_pwm_handle;

#endif

#if (AM_CFG_SOFTIMER_ENABLE == 1)

/**
 * \brief ϵͳ�δ�ʹ�õĶ�ʱ���� handle
 *
 * ��ʹ��ϵͳ�δ�ʱ��Ĭ��ʹ�� TIM4 ��ͨ�� 0 ��Ϊ������ʱ��Ԫ������Ѿ��� TIM4 ��ʼ��
 * Ϊ��ʱ������
 */
extern am_timer_handle_t g_system_tick_timer_handle;

#endif

/**
 * \brief �弶��ʼ��
 *
 * \return ��
 *
 * \note �ú������ʼ��ϵͳʱ�ӡ�GPIO���жϡ���������LED ����ʱ����
 */
void am_board_init (void);

#endif /* __AM_BOARD_H */

/* end of file */
