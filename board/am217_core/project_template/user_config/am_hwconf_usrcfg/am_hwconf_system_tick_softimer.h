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
 * \brief ϵͳ�δ������ʱ���û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */
#ifndef __AM_HWCONF_SYSTEM_TICK_SOFTIMER_H
#define __AM_HWCONF_SYSTEM_TICK_SOFTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_timer.h"

/**
 * \brief ϵͳ�δ�ʵ����ʼ��(��ʹ�������ʱ��)
 *
 * ��ʹ��ϵͳ�δ�ʱ��Ĭ��ʹ�� TIM4 ��ͨ�� 0 ��Ϊ������ʱ��Ԫ������Ѿ��� TIM4 ��ʼ��
 * Ϊ��ʱ������
 *
 * \param ��
 *
 * \return TIMER ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_system_tick_inst_init (void);

/**
 * \brief ϵͳ�δ�ʵ����ʼ��(ʹ�������ʱ��)
 *
 * ��ʹ��ϵͳ�δ�ʱ��Ĭ��ʹ�� TIM4 ��ͨ�� 0 ��Ϊ������ʱ��Ԫ������Ѿ��� TIM4 ��ʼ��
 * Ϊ��ʱ������
 *
 * \param ��
 *
 * \return TIMER ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_system_tick_softimer_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_HWCONF_SYSTEM_TICK_SOFTIMER_H */

/* end of file */
