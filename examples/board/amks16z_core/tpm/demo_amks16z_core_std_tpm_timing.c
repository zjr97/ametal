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
 * \brief TPMʵ�ֱ�׼��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_tpm_timing.c src_amks16z_core_std_tpm_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_std_tpm_timing
 * \copydoc demo_amks16z_core_std_tpm_timing.c
 */

/** [src_amks16z_core_std_tpm_timing] */
#include "am_kl26_inst_init.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_board.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_tpm_timing_entry (void)
{

    am_timer_handle_t tpm_timing_handle;

    tpm_timing_handle = am_kl26_tpm0_timing_inst_init();

    demo_std_timer_timing_entry(tpm_timing_handle, 0);
}

/** [src_amks16z_core_std_tpm_timing] */

/* end of file */
