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
 * - ʵ������
 *   1.���ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ�󴮿ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      uart tx dma test running
 *      uart tx dma test done
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *    3. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_zlg217_hw_uart_tx_dma.c src_zlg217_hw_uart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-10  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_hw_uart_tx_dma
 * \copydoc demo_zlg217_hw_uart_tx_dma.c
 */

/** [src_zlg217_hw_uart_tx_dma] */
#include "ametal.h"
#include "am_zlg217.h"
#include "demo_zlg_entries.h"
#include "am_zlg217_inst_init.h"

/**
 * \brief �������
 */
void demo_zlg217_core_hw_uart_tx_dma_entry (void)
{
    AM_DBG_INFO("demo am217_core hw uart tx dma!\r\n");

    /* �ȴ������������ */
    am_mdelay(100);

    demo_zlg_hw_uart_tx_dma_entry(ZLG217_UART1,
                                  am_clk_rate_get(CLK_UART1),
                                  DMA_CHAN_UART1_TX);
}

/** [src_zlg217_hw_uart_tx_dma] */

/* end of file */
