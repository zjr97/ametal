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
 * \brief AM824-Core ���İ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation
 * \endinternal
 */

#ifndef __AM_BOARD_H
#define __AM_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_led.h"
#include "am_pwm.h"
#include "am_timer.h"
#include "am_delay.h"
#include "am_bsp_delay_timer.h"
#include "am_prj_config.h"

/** \brief LED ���� ID �� */
#define LED0          0
#define LED1          1

#if (AM_CFG_BUZZER_ENABLE == 1)

/**
 * \brief ������ʹ�õĶ�ʱ���� handle
 *
 * ��ʹ�÷�����ʱ��Ĭ�Ͻ�ʹ�� SCT �� OUT1 ��� PWM ���Σ�����Ѿ��� SCT ��ʼ��Ϊ
 * PWM ���ܣ����� SCT ���������· PWM����˿���ʹ�ø� handle���Ա�ʹ������ 5 · PWM
 */
extern am_pwm_handle_t g_buzzer_pwm_handle;
#endif

#if (AM_CFG_SOFTIMER_ENABLE == 1)

/**
 * \brief ϵͳ�δ�ʹ�õĶ�ʱ���� handle
 *
 * ��ʹ��ϵͳ�δ�ʱ��Ĭ��ʹ�� MRT ��ͨ�� 0 ��Ϊ������ʱ��Ԫ������Ѿ��� MRT ��ʼ��Ϊ
 * ��ʱ�����ܣ����� MRT ����֧�� 4 ·��ʱ����˿���ʹ�ø� handle���Ա�ʹ������ 3 ·
 * ��ʱͨ��
 */
extern am_timer_handle_t g_system_tick_timer_handle;
#endif

/**
 * \brief �弶��ʼ��
 *
 * \return ��
 *
 * \note �ú������ʼ����ʱ������LED�����Դ��ڡ�C �⡢ϵͳ�δ������ʱ������������
 *       �������ж��ӳٴ���
 */
void am_board_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_BOARD_H */

/* end of file */
