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
 * \brief UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 *
 * - ʵ������
 *   1. ������� "HW example---UART test in polling mode:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zlg217_hw_uart_polling.c src_zlg217_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  ari, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zlg217_hw_uart_polling
 * \copydoc demo_zlg217_hw_uart_polling.c
 */

/** [src_zlg217_hw_uart_polling] */
#include "ametal.h"
#include "am_board.h"
#include "am_zlg217.h"
#include "am_gpio.h"
#include "demo_zlg_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_hw_uart_polling_entry (void)
{
    AM_DBG_INFO("demo am217_core hw uart polling!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_9, PIOA_9_UART1_TX_REMAP0 | PIOA_9_AF_PP);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART1_RX_REMAP0| PIOA_10_INPUT_FLOAT);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_UART1);

    demo_zlg_hw_uart_polling_entry(ZLG217_UART1, am_clk_rate_get(CLK_UART1));
}
/** [src_zlg217_hw_uart_polling] */

/* end of file */
