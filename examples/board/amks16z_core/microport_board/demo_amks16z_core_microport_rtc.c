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
 * \brief MicroPort RTC(PCF85063) ���̣�ͨ�� PCF85063 оƬʵ��
 *        RTC�����ӵĹ��ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort RTC ������ӵ� AMKS16RFID �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ���ڽ�ÿһ���ʱ����Ϣ��ӡ������
 *   2. ����ʱ��һ���ͻ�ִ�����ӻص�������
 *   3. �жϲ���ʱ������жϻص�������
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_1 �������� PC ���ڵ� TXD��
 *    PIOA_2 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_microport_rtc.c src_microport_rtc
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_rtc
 * \copydoc demo_microport_rtc.c
 */

/** [src_microport_rtc] */
#include "am_vdebug.h"
#include "am_hwconf_microport.h"
#include "demo_std_entries.h"
/**
 * \brief MicroPort RTC ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_rtc_entry (void)
{
    AM_DBG_INFO("demo amks16z_core microport rtc!\r\n");

    demo_std_rtc_entry(am_microport_rtc_rtc_inst_init());
}

/** [src_microport_rtc] */

/* end of file */
