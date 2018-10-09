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
 * \brief USART ���̣���ѯ��ʽ����ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "USART poll mode test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_std_usart_poll.c src_am824_std_usart_poll
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_usart_poll
 * \copydoc demo_am824_std_usart_poll.c
 */

/** [src_am824_std_usart_poll] */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"
#include "am_vdebug.h"
/**
 * \brief �������
 */
void demo_am824_core_std_usart_poll_entry (void)
{

    AM_DBG_INFO("demo am824_core std uart polling!\r\n");
  
    demo_std_uart_polling_entry(am_lpc82x_usart0_inst_init());
}
/** [src_am824_std_usart_poll] */

/* end of file */
