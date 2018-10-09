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
 * \brief KL26 ���İ�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-23  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_prj_config.h"

#include "am_delay.h"
#include "am_led.h"
#include "am_buzzer_pwm.h"
#include "am_timer.h"

/** \brief LED ����ID�� */
#define LED0          0
#define LED1          1

#if (AM_CFG_BUZZER_ENABLE == 1)

/** 
 * \brief TPM_PWM ��handle
 *
 * ��ʹ�÷�����ʱ��Ĭ�Ͻ�ʹ��TPM0��OUT2���PWM���Σ�����Ѿ���TPM0��ʼ��ΪPWM���ܣ�
 * ����TPM0�������·PWM����˿���ʹ�ø�handle���Ա�ʹ������5·PWM��
 */
extern am_pwm_handle_t g_sct0_pwm_handle;

#endif

#if (AM_CFG_SOFTIMER_ENABLE == 1)

/** 
 * \brief PIT ��handle
 *
 * ��ʹ�������ʱ��ʱ��Ĭ�Ͻ�ʹ��PIT��Ϊ������ʱ��Ԫ������Ѿ���PIT��ʼ��Ϊ��ʱ�����ܣ�

 */
extern am_timer_handle_t g_mrt_handle;

#endif


/**
 * \brief �弶��ʼ��(kl26)
 * \return ��
 * \note �ú������ʼ��ϵͳʱ�ӡ�GPIO���жϡ���������LED����ʱ����
 */
void am_board_init(void);
    
/* end of file */
