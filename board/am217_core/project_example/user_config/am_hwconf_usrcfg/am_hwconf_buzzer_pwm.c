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
 * \brief �������û������ļ���PWM������
 * \sa am_hwconf_buzzer_pwm.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_pwm.h"
#include "am_buzzer_pwm.h"
#include "am_zlg217_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_buzzer_pwm
 * \copydoc am_hwconf_buzzer_pwm.c
 * @{
 */

/** \brief �������� PWM Ƶ�ʣ�2500 ���� 2500Hz */
#define __BUZZER_PWM_FREQ       2500

/** \brief PWM ��ռ�ձȣ�50 ���� 50% */
#define __BUZZER_PWM_DUTY       50

/** \brief ʹ��ͨ��2 */
#define __BUZZER_TIMER_CHAN     2

/** \brief ������ʵ����ʼ�� */
am_pwm_handle_t am_buzzer_pwm_inst_init (void)
{
    am_pwm_handle_t handle = am_zlg217_tim3_pwm_inst_init();

    if (NULL != handle) {
        am_buzzer_pwm_init(handle,
                           __BUZZER_TIMER_CHAN,
                           10000000 * __BUZZER_PWM_DUTY / __BUZZER_PWM_FREQ,
                           1000000000 / __BUZZER_PWM_FREQ);
    }

    return handle;
}

/**
 * @}
 */

/* end of file */
