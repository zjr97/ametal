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
 * \brief UART0ͨ��DMA��ʽ�������ݣ�ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_1 ��������PC���ڵ�TXD;
 *   2. PIOA_2 ��������PC���ڵ�RXD;
 *   3. ������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *
 * - ʵ������
 *   1.���ڴ�ӡ��ʾ�ַ� DMA tx transfer start:
 *   2. Ȼ�󴮿ڽ����ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      uart tx dma test running
 *      uart tx dma test done
 *      
 *
 * \note ��DMA�����ڼ䲻Ҫ�Դ������ݼĴ���UART_D���в���
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_uart_tx_dma.c src_amks16z_core_hw_uart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-21  nwt, make some changes.
 * - 1.00 15-07-10  xym, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_uart_tx_dma
 * \copydoc demo_amks16z_core_hw_uart_tx_dma.c
 */

/** [src_amks16z_core_hw_uart_tx_dma] */
#include "ametal.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_uart_tx_dma_entry (void)
{
    demo_kl26_hw_uart_tx_dma_entry();
}

/** [src_amks16z_core_hw_uart_tx_dma] */

/* end of file */
