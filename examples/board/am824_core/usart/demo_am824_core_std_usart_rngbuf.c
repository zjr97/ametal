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
 * \brief USART ���λ��������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "USART ring buffer test:\r\n"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_std_usart_rngbuf.c src_am824_std_usart_rngbuf
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_usart_rngbuf
 * \copydoc demo_am824_std_usart_rngbuf.c
 */

/** [src_am824_std_usart_rngbuf] */
#include "ametal.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"
#include "am_vdebug.h"

/**
 * \brief �������
 */
void demo_am824_core_std_usart_rngbuf_entry (void)
{

    AM_DBG_INFO("demo am824_core std uart ringbuf!\r\n");

    demo_std_uart_ringbuf_entry(am_lpc82x_usart0_inst_init());
}
/** [src_am824_std_usart_rngbuf] */

/* end of file */
