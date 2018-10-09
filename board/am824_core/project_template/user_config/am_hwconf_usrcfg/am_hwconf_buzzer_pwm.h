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
 * \brief �������û������ļ���PWM ������
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */

#ifndef __AM_HWCONF_BUZZER_PWM_H
#define __AM_HWCONF_BUZZER_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_pwm.h"

/**
 * \brief ������ʵ����ʼ��
 *
 * ��ʹ�÷�����ʱ��Ĭ�Ͻ�ʹ�� SCT �� OUT1 ��� PWM ���Σ�����Ѿ��� SCT ��ʼ��Ϊ PWM
 * ���ܣ����� SCT ���������· PWM����˿���ʹ�ñ��������ص� handle���Ա�ʹ������ 5
 * · PWM
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_buzzer_pwm_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_HWCONF_BUZZER_PWM_H */

/* end of file */
