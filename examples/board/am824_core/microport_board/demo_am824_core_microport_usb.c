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
 * \brief MicroPort USB(XR21V141x) ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort USB ��չ�����ӵ� AM824-Core �� MicroPort �ӿڣ�
 *   2. ��  MicroPort USB ��չ���ϵ� USB �ӿ��� PC ���Ӳ�ͨ���������ִ򿪡�
 *
 * - ʵ������
 *   1. �������"MicroPort USB Test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *   1. XR21V141x Ϊ USB ת����оƬ��ʹ��ǰ��Ҫ��װ���������û������� EXAR
 *      �ٷ���վ(http://www.exarcorp.cn/design-tools/software-drivers)���أ�
 *   2. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ������۲촮�ڴ�ӡ�ĵ�����Ϣ����
 *      Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_microport_usb.c src_microport_usb
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_usb
 * \copydoc demo_microport_usb.c
 */

/** [src_microport_usb] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_microport_usb_entry (void)
{

    AM_DBG_INFO("demo am824_core microport usb!\r\n");

    demo_std_uart_polling_entry(am_lpc82x_usart0_inst_init());
}
/** [src_microport_usb] */

/* end of file */
