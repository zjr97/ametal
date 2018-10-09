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
 * \brief USART ���̣���ѯ��ʽ����ͨ��Ӳ����ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "USART hw_poll mode test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_usart_poll.c src_lpc824_hw_usart_poll
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_usart_poll
 * \copydoc demo_lpc824_hw_usart_poll.c
 */

/** [src_lpc824_hw_usart_poll] */
#include "ametal.h"
#include "hw/amhw_lpc_usart.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"

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

void demo_lpc_hw_usart_poll_entry(amhw_lpc_usart_t *p_hw_usart,
                                  uint32_t          u_clk,
                                  uint32_t          baudrate)
{
     uint8_t buf[5];
  
    /* USART0 8 λ���ݳ��� 1 λֹͣλ ����żУ�� */
    amhw_lpc_usart_config(p_hw_usart,
                          AMHW_LPC_USART_CFG_8BIT |
                          AMHW_LPC_USART_CFG_STOP_1 |
                          AMHW_LPC_USART_CFG_PARITY_NO);

   /* ������ 115200 */
    amhw_lpc_usart_baudrate_set(p_hw_usart,
                                u_clk,
                                baudrate);

    /* ʹ�ܴ��� */
    amhw_lpc_usart_enable(p_hw_usart);

    amhw_lpc_usart_poll_send(p_hw_usart,
                             (am_const uint8_t *)"USART hw_poll mode test:\r\n",
                             sizeof("USART hw_poll mode test:\r\n") - 1);

    AM_FOREVER {

        /* �������� */
        amhw_lpc_usart_poll_receive (p_hw_usart, &buf[0], 1);

        /* �������� */
        amhw_lpc_usart_poll_send(p_hw_usart, &buf[0], 1);
    }
}
/** [src_lpc824_hw_usart_poll] */

/* end of file */
