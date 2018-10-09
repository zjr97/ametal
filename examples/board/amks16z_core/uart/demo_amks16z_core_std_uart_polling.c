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
 * \brief USART��ѯ��ʽ�½��շ����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOC_3 ��������PC���ڵ�TXD;
 *   2. PIOC_4 ��������PC���ڵ�RXD��
 *   3. ������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *
 * - ʵ������
 *   1. �������"HW example---UART test in polling mode:"��
 *   2. ����������յ����ַ�����
 *
 * \note ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_uart_polling.c src_amks16z_core_std_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-19  nwt, make some changes.
 * - 1.01 15-07-06  xym, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_std_uart_polling
 * \copydoc demo_amks16z_core_std_uart_polling.c
 */
 
/** [src_amks16z_core_std_uart_polling] */
#include "ametal.h"
#include "am_kl26_inst_init.h"
#include "am_board.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_uart_polling_entry (void)
{
    am_uart_handle_t handle;

    /* UART��ʼ��  */
    handle = am_kl26_uart1_inst_init();

    demo_std_uart_polling_entry(handle);
}


 /** [src_amks16z_core_std_uart_polling] */
 
/* end of file */

