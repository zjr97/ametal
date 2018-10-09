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
 * \brief ��Ƶ�ʶ�ʱ����MRT�����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Դ��������ʱ���������Ϣ
 *   2. ��ʱ���ڵ���(Ĭ��Ϊ 10Hz)�����Դ��ڻ���� The timing frq is 10Hz;
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� MRT Ĭ����Ϊϵͳ�δ�ʹ�ã�ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_SOFTIMER_ENABLE�� AM_CFG_SYSTEM_TICK_ENABLE �Լ�
 *       AM_CFG_KEY_GPIO_ENABLE ����Ϊ 0����ʹ�������ʱ����ϵͳ��ડ����ض���������
 *
 * \par Դ����
 * \snippet demo_am824_std_mrt_timer.c src_am824_std_mrt_timer
 *
 * \internal
 * \par History
 * - 1.00 15-07-15  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_mrt_timer
 * \copydoc demo_am824_std_mrt_timer.c
 */

/** [src_am824_std_mrt_timer] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_std_mrt_timer_entry (void)
{
    AM_DBG_INFO("The MRT demo for standard timing service\r\n");

    demo_std_timer_timing_entry(am_lpc82x_mrt_inst_init(), 0);

}
/** [src_am824_std_mrt_timer] */

/* end of file */
