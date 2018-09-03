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
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ͨ����λ������һ������ MCU ���� 5 ���ַ���
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����յ������ݣ�
 *   2. Ȼ�󴮿ڴ�ӡ�� "DMA transfer done!"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zlg217_hw_uart_rx_dma.c src_zlg217_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 17-03-10  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_hw_uart_rx_dma
 * \copydoc demo_zlg217_hw_uart_rx_dma.c
 */

/** [src_zlg217_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_zlg217.h"
#include "demo_zlg_entries.h"
#include "am_zlg217_inst_init.h"

/**
 * \brief �������
 */
void demo_zlg217_core_hw_uart_rx_dma_entry (void)
{
    AM_DBG_INFO("demo am217_core hw uart rx dma!\r\n");

    /* �ȴ������������ */
    am_mdelay(100);

    demo_zlg_hw_uart_rx_dma_entry(ZLG217_UART1,
                                  am_clk_rate_get(CLK_UART1),
                                  DMA_CHAN_UART1_RX);
}

/** [src_zlg217_hw_uart_rx_dma] */

/* end of file */
