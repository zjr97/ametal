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
 * \brief MicroPort RX8025T ���̣�ͨ�� RX8025T оƬʵ��
 *        RTC�����ӵĹ��ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort RX8025T ������ӵ� AMKS16RFID �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ���Դ��ڽ�ÿһ���ʱ����Ϣ��ӡ������
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_1 �������� PC ���ڵ� TXD��
 *    PIOA_2 �������� PC ���ڵ� RXD��������Ҫ�鿴���Դ����Ƿ�ʹ����485��
 *    ���ʹ����485������485�����ݷ���������Ż�� MicroPort RX8025T����
 *    �����Ų�����ͻ��
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
#include "am_vdebug.h"
#include "am_hwconf_microport.h"
#include "demo_std_entries.h"

/**
 * \brief MicroPort RX8025T ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_rx8025t_entry (void)
{
    AM_DBG_INFO("demo am116_core microport rx8025t!\r\n");

    demo_std_rtc_entry(am_microport_rx8025t_rtc_inst_init());
}

/** [src_microport_rx8025t] */

/* end of file */
