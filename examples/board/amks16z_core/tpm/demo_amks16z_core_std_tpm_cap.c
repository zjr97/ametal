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
 * \brief TPMʵ�ֲ����ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� PWM ������ӵ������������š�
 *
 * - ʵ������
 *   1. ���Դ���������񵽵� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_tpm_cap.c src_amks16z_core_std_tpm_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_std_tpm_cap
 * \copydoc demo_amks16z_core_std_tpm_cap.c
 */

/** [src_amks16z_core_std_tpm_cap] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_kl26_inst_init.h"
#include "am_board.h"
#include "am_int.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_tpm_cap_entry (void)
{

    am_cap_handle_t cap_handle;

    cap_handle = am_kl26_tpm1_cap_inst_init();

    demo_std_timer_cap_entry(cap_handle, 1);
}

/** [src_amks16z_core_std_tpm_cap] */

/* end of file */
