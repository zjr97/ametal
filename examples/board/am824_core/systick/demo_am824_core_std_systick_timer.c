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
 * \brief Systick ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���� �� 10Hz ��Ƶ�ʴ�ӡ��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� Systick Ĭ����Ϊϵͳ��ʱʹ�ã�ʹ�ò��Ա� Demo ǰ��Ҫ��
 *       am_prj_config.h �е� AM_CFG_DELAY_ENABLE ����Ϊ 0����ʹ��ϵͳ��ʱ��
 *
 * \par Դ����
 * \snippet demo_am824_std_systick_timer.c src_am824_std_systick_timer
 *
 * \internal
 * \par History
 * - 1.00 15-09-23  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_systick_timer
 * \copydoc demo_am824_std_systick_timer.c
 */

/** [src_am824_std_systick_timer] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_std_systick_timer_entry (void)
{
    am_timer_handle_t systick_handle;

    AM_DBG_INFO("demo am824 std systick timer\r\n");

    systick_handle = am_arm_systick_inst_init();
    demo_std_timer_timing_entry(systick_handle, 0);
}
/** [src_am824_std_systick_timer] */

/* end of file */
