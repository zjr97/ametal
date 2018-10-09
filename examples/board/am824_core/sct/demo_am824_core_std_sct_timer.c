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
 * \brief SCT ��ʱ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 ��״̬�� 3s Ϊ�����ڶ�ʱ��ת��ֹͣ��ת����״̬���л���
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_am824_std_sct_timer.c src_am824_std_sct_timer
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-15  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_sct_timer
 * \copydoc demo_am824_std_sct_timer.c
 */

/** [src_am824_std_sct_timer] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_std_sct_timer_entry (void)
{
    AM_DBG_INFO("The SCT demo for std timer service\r\n");
    demo_std_timer_timing_entry(am_lpc82x_sct0_timing_inst_init(), 0);
}
/** [src_am824_std_sct_timer] */

/* end of file */
