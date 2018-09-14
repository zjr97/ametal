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
 * \brief MicroPort SC16IS740 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ��  MicroPort SC16IS740 ������ӵ� AM116-Core �� MicroPort �ӿڣ�
 *   2. ��  MicroPort SC16IS740 ����ϵ� SC16IS740 �ӿ��� PC ���Ӳ�ͨ���������ִ򿪡�
 *
 * - ʵ������
 *   1. �������"MicroPort SC16IS740 Test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *   1. XR21V141x Ϊ SC16IS740 ת����оƬ��ʹ��ǰ��Ҫ��װ���������û������� EXAR
 *      �ٷ���վ(http://www.exarcorp.cn/design-tools/software-drivers)���أ�
 *   2. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *
 * \par Դ����
 * \snippet demo_am116_core_microport_sc16is740.c src_am116_core_microport_sc16is740
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am116_core_microport_sc16is740
 * \copydoc demo_am116_core_microport_sc16is740.c
 */

/** [src_am116_core_microport_sc16is740] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg116_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am116_core_microport_sc16is740_entry (void)
{
    AM_DBG_INFO("demo am116_core microport sc16is740!\r\n");

    demo_std_uart_polling_entry(am_zlg116_uart1_inst_init());
}
/** [src_am116_core_microport_sc16is740] */

/* end of file */
