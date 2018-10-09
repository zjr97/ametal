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
 * \brief TPMʵ��PWM��׼�ӿ����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��ʱ��ͨ����Ӧ���������Ƶ��Ϊ 2KHz��ռ�ձ�Ϊ 50% �� PWM ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_tpm_pwm.c src_amks16z_core_std_tpm_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_std_tpm_pwm
 * \copydoc demo_amks16z_core_std_tpm_pwm.c
 */

/** [src_amks16z_core_std_tpm_pwm] */
#include "am_kl26_inst_init.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_board.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_tpm_pwm_entry (void)
{

    /* ��ʼ����ʱ��0ΪPWM���� */
    am_pwm_handle_t tpm0_pwm_handle = am_kl26_tpm0_pwm_inst_init();

    demo_std_timer_pwm_entry(tpm0_pwm_handle, 0);
}

/** [src_amks16z_core_std_tpm_pwm] */

/* end of file */
