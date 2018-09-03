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
 * \brief ��Դ��������׼�ӿ�
 *
 * ��Դ������ʹ��PWM���� 
 *
 * \internal
 * \par Modification history
 * - 1.01 14-12-09  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_BUZZER_PWM_H
#define __AM_BUZZER_PWM_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"
#include "am_pwm.h"
    
/**
 * \addtogroup am_if_buzzer_pwm
 * \copydoc am_buzzer_pwm.h
 * @{
 */

/**
 * \brief ��ʼ����Դ������
  *
 * \param[in] pwm_handle : PWM��׼�ӿڲ������
 * \param[in] chan       : PWMͨ����
 * \param[in] duty_ns    : PWM����ʱ�䣨��λ�����룩
 * \param[in] period_ns  : PWM����ʱ�䣨��λ�����룩
 *
 * \return �����
 */ 
int am_buzzer_pwm_init (am_pwm_handle_t pwm_handle,
                        int             chan,
                        unsigned int    duty_ns,
                        unsigned int    period_ns);
 
/** 
 * @}  
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_BUZZER_PWM_H */

/* end of file */
