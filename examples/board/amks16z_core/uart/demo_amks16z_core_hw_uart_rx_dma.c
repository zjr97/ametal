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
 *   1. PIOC_3 ��������PC���ڵ�TXD;
 *   2. PIOC_4 ��������PC���ڵ�RXD;
 *   3. ������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *   4. ͨ����λ������һ������MCU����5���ַ���
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����յ�������;
 *   2. Ȼ�󴮿ڴ�ӡ����DMA transfer done!����

 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_uart_rx_dma.c src_amks16z_core_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-21  nwt, make some changes.
 * - 1.00 15-07-10  xym, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_uart_rx_dma
 * \copydoc demo_amks16z_core_hw_uart_rx_dma.c
 */

/** [src_amks16z_core_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_uart_rx_dma_entry (void)
{

    demo_kl26_hw_uart_rx_dma_entry();
}

/** [src_amks16z_core_hw_uart_rx_dma] */

/* end of file */
