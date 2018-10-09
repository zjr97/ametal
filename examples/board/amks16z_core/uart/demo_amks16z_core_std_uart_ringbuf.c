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
 * \brief UART���λ�������ʽ�½��շ����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOC_3 ��������PC���ڵ�TXD;
 *   2. PIOC_4 ��������PC���ڵ�RXD��
 *   3. ������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *
 * - ʵ������
 *   1. �������"UART interrupt mode(Add ring buffer) test:"��
 *   2. ����������յ����ַ�����
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_uart_ringbuf.c src_amks16z_core_std_uart_ringbuf
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-19  nwt, change interface function name.
 * - 1.00 15-10-27  xym, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_std_uart_ringbuf
 * \copydoc demo_amks16z_core_std_uart_ringbuf.c
 */

/** [src_amks16z_core_std_uart_ringbuf] */
#include "ametal.h"
#include "am_fsl_uart.h"
#include "am_uart_rngbuf.h"
#include "am_kl26_inst_init.h"
#include "am_board.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_uart_ringbuf_entry (void)
{
    am_uart_handle_t uart_handle;
    /* UART��ʼ�� */
    uart_handle = am_kl26_uart1_inst_init();

    demo_std_uart_ringbuf_entry(uart_handle);
}

/** [src_amks16z_core_std_uart_ringbuf] */

/* end of file */
