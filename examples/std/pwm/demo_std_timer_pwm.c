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
 * \brief ��ʱ�� PWM ������ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��ʱ��ͨ����Ӧ���������Ƶ��Ϊ 2KHz��ռ�ձ�Ϊ 50% �� PWM ��
 *
 * \par Դ����
 * \snippet demo_std_timer_pwm.c src_std_timer_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_timer_pwm
 * \copydoc demo_std_timer_pwm.c
 */

/** [src_std_timer_pwm] */
#include "ametal.h"
#include "am_pwm.h"

/**
 * \brief �������
 */
void demo_std_timer_pwm_entry (am_pwm_handle_t pwm_handle, int pwm_chan)
{
    am_pwm_config(pwm_handle, pwm_chan, 250000 / 2, 250000); /* Ƶ��Ϊ 2KHz */
    am_pwm_enable(pwm_handle, pwm_chan);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_timer_pwm] */

/* end of file */
