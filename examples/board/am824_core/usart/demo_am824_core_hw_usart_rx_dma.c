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
 * \brief USART �����������̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ����λ�����յ� "DMA rx transfer start:" ʱ��ͨ����λ��һ������ MCU ����
 *      16 ���ַ���
 *
 * - ʵ������
 *   1  ���ڴ�ӡ "DMA rx transfer start:"��
 *   1. ���ڴ�ӡ�����յ������ݣ�
 *   2. ���ڴ�ӡ "DMA transfer done!"��
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_hw_usart_rx_dma.c src_am824_hw_usart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-15  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_usart_rx_dma
 * \copydoc demo_am824_hw_usart_rx_dma.c
 */

/** [src_am824_hw_usart_rx_dma] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/**
 * \brief ��������Ƶ�����ã���������Ƶ�ʱ���С��ϵͳʱ��Ƶ����ӦΪ�����ʵ���������
 *
 * Ϊ�����ò�����Ϊ 115200�������ô��ڻ�������Ƶ��Ϊ��
 * 11059200Hz(11059200 = 115200 * 96)��
 * ���ڻ�������Ƶ������Ϊ 11.059200MHz�����������������ʵ����� (9600,4800,115200)
 *
 * \note  USART0\1\2 ����һ����������Ƶ��,��Ҫ���׸Ķ�
 */
#define  __LPC82X_UASART_BASE_RATE  11059200

/** \brief ������ */
#define __USART_BAUDRATE            115200


/**
 * \brief �������
 */
void demo_am824_core_hw_usart_rx_dma_entry (void)
{
    am_kprintf("demo am824 hw usart rx dma!\r\n");
    /* �ȴ����ڷ��Ϳ��� */
    while ((amhw_lpc_usart_stat_get(LPC82X_USART0) &
            AMHW_LPC_USART_STAT_TXIDLE) == 0);

    /* ���ô��ڻ���ʱ�� */
    amhw_lpc82x_clk_usart_baseclkrate_set(__LPC82X_UASART_BASE_RATE);

    /* ʹ�ܴ��� 0 ʱ�Ӳ���λ */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_UART0);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_UART0);

    /* �������Ÿ��� */
    am_gpio_pin_cfg(PIO0_4, PIO_FUNC_U0_TXD);
    am_gpio_pin_cfg(PIO0_0, PIO_FUNC_U0_RXD);

    demo_lpc824_hw_usart_rx_dma_entry(LPC82X_USART0,
                                      amhw_lpc82x_clk_usart_baseclkrate_get(),
                                      __USART_BAUDRATE,
                                      DMA_CHAN_USART0_RX_REQ);

}
/** [src_am824_hw_usart_rx_dma] */

/* end of file */
