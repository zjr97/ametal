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
 * \brief USART ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ������λ�����ڲ�����Ϊ 115200��8 λ���ݳ��� 1 λֹͣλ ����żУ�飻
 *   2. �� PC ����λ����������أ����� XON = 0x11�� XOFF = 0x13��
 *
 * - ʵ������
 *   1. ������� "USART flowctrl test:\r\n"��
 *   2. ����������յ����ַ�����
 *   3. ��������λ��ÿ 100 ����ֻ�ܴ��� 5 ���ַ������ͣ�����Ϊ������������أ�����
 *      PC �˴��ģ(ʹ�ô�������ص���λ��)��������Ҳ���ᶪʧ���ݣ�
 *      PC ���͵����������ڽ��յ���������
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc_std_usart_flowctrl.c src_lpc_std_usart_flowctrl
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_std_usart_flowctrl
 * \copydoc demo_lpc_std_usart_flowctrl.c
 */

/** [src_lpc_std_usart_flowctrl] */
#include "ametal.h"
#include "am_delay.h"
#include "am_uart_rngbuf.h"
#include "am_lpc_usart.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

#define __UART0_RX_BUF_SIZE  128  /**< \brief ���ջ��λ�������С��Ӧ��Ϊ 2^n */
#define __UART0_TX_BUF_SIZE  128  /**< \brief ���ͻ��λ�������С��Ӧ��Ϊ 2^n */

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief USART ���ջ��λ����� */
am_local uint8_t __g_usart0_rxbuf[__UART0_RX_BUF_SIZE];

/** \brief USART ���ͻ��λ����� */
am_local uint8_t __g_usart0_txbuf[__UART0_TX_BUF_SIZE];

/** \brief ���ڻ������豸 */
am_local am_uart_rngbuf_dev_t  __g_uart0_rngbuf_dev;

void demo_lpc_std_usart_flowctrl_entry (am_uart_handle_t  uart_handle)
{
    uint8_t                 usart0_buf[5];
    am_uart_rngbuf_handle_t handle;
  
    am_uart_poll_send(uart_handle,
                      (am_const uint8_t *)"USART flowctrl test:\r\n",
                      sizeof("USART flowctrl test:\r\n") - 1);

    /* USART ��ʼ��Ϊ���λ�����ģʽ */
    handle = am_uart_rngbuf_init(&__g_uart0_rngbuf_dev,
                                  uart_handle,
                                  __g_usart0_rxbuf,
                                  __UART0_RX_BUF_SIZE,
                                  __g_usart0_txbuf,
                                  __UART0_TX_BUF_SIZE);

    /* ����������� */
    am_uart_rngbuf_ioctl(handle,
                         AM_UART_FLOWMODE_SET,
                         (void *)AM_UART_FLOWCTL_SW);

    /* �������ط�ֵ��50 ���ֽ� */
    am_uart_rngbuf_ioctl(handle,
                         AM_UART_RNGBUF_RX_FLOW_OFF_THR,
                         (void *)50);

    /* ����������ֵ��10 ���ֽ� */
    am_uart_rngbuf_ioctl(handle,
                         AM_UART_RNGBUF_RX_FLOW_OFF_THR,
                         (void *)10);

    AM_FOREVER {

       /* ÿ 100 ms �ӽ��ջ��λ�������ȡ�� 5 �����ݷ��ص� PC ��
        * ��� PC ���·������ݹ��࣬�����λ������ﵽ���ط�ֵʱ��
        * MCU ���� PC ���������ź� XOFF��0x13����PC ��ֹͣ���͡�
        * �����ջ��λ������ڵ����ݱ�ȡ�����ٵ����շ�ֵʱ��MCU
        * ���� PC ���������ź� XON ��0x11����PC �˼����������ݡ�
        */

       /* ȡ�����ջ������ڵ����� */
       am_uart_rngbuf_receive(handle, usart0_buf, 5);

       /* д���ݵ����ͻ����� */
       am_uart_rngbuf_send(handle, usart0_buf, 5);

       am_mdelay(100);
    }
}
/** [src_lpc_std_usart_flowctrl] */

/* end of file */
