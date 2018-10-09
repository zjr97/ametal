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
 * \brief MicroPort-RX8025T ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort-RX8025T ��չ�����ӵ� AM824-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ���ڽ�ÿһ���ʱ����Ϣ��ӡ������
 *   2. ����ʱ��һ���ͻ�ִ�����ӻص�������
 *   3. ÿ���ӻ�ִ��ʱ������жϵĻص�������
 *   4. ÿ�����Ӿͻ�ִ�ж�ʱ���жϵĻص�������
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_microport_rx8025t.c src_microport_rx8025t
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-14  vir, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_rx8025t
 * \copydoc demo_microport_rx8025t.c
 */

/** [src_microport_rx8025t] */
#include "ametal.h"
#include "am_rtc.h"
#include "am_rx8025t.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_microport_rx8025t_entry (void)
{
    AM_DBG_INFO("demo am824_core microport rx8025t!\r\n");

    demo_std_rtc_entry(am_microport_rx8025t_rtc_inst_init());

}
/** [src_microport_rx8025t] */

/* end of file */
