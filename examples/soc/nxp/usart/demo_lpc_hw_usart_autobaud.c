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
 * \brief USART �Զ�ƥ�䲨�������̣�ͨ��Ӳ����ӿ�ʵ��
 *
 * - �������裺
 *   1. ����λ�����յ� "please set a new baudrate and then input '5'"ʱ���ı�
 *      ��λ���Ĳ�����Ϊ 4800 �� 9600,Ȼ�������ַ� 'a' �� '5'��
 *
 * - ʵ������
 *   1. �Զ�������ƥ��ɹ��󣬴��ڴ�ӡ "The usart baudrate is xxx"���������룻
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    2. ����ԭ��MCU Ӳ��ͨ������ RXD ���Ž�������ʱ���������½���֮���ʱ��
 *       ����Զ����㲨���ʣ�����Ҫ����λ�����͵����ݣ�'a' �� '5'����
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_usart_autobaud.c src_lpc824_hw_usart_autobaud
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_usart_autobaud
 * \copydoc demo_lpc824_hw_usart_autobaud.c
 */

 /** [src_lpc824_hw_usart_autobaud] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc_usart.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \brief ��������Ƶ�����ã���������Ƶ�ʱ���С��ϵͳʱ��Ƶ����ӦΪ�����ʵ���������
 *
 * Ϊ�����ò�����Ϊ 115200�������ô��ڻ�������Ƶ��Ϊ��
 * 11059200Hz(11059200 = 115200 * 96)��
 * ���ڻ�������Ƶ������Ϊ 11.059200MHz�����������������ʵ����� (9600,4800,115200)
 *
 * \note  USART0\1\2 ����һ����������Ƶ��,��Ҫ���׸Ķ�
 */

void demo_lpc824_hw_usart_autobaud_entry(amhw_lpc_usart_t *p_hw_usart,
                                         uint32_t          uclk)
{
    uint8_t  tbuf[5];
    uint32_t baudrate;

    AM_DBG_INFO("Please set a new baudrate and then input '5'...\r\n");

    /* �Զ�������ģʽ */
    amhw_lpc_usart_ctl_set(p_hw_usart,
                           AMHW_LPC_USART_CTL_AUTOBAUD);

    /* �ȴ� PC �˷����ַ���ƥ�䲨���� */
    while (amhw_lpc_usart_ctl_get(p_hw_usart) &
           AMHW_LPC_USART_CTL_AUTOBAUD);

    /* ��ȡʵ�ʲ����� */
    baudrate = amhw_lpc_usart_baudrate_get(
                   p_hw_usart,
                   uclk);

    AM_DBG_INFO("\r\nThe usart baudrate is %d \r\n", baudrate);

    AM_FOREVER {

        /* �������� */
        amhw_lpc_usart_poll_receive (p_hw_usart, &tbuf[0], 1);

        /* �������� */
        amhw_lpc_usart_poll_send(p_hw_usart , &tbuf[0], 1);
    }
}
/** [src_lpc824_hw_usart_autobaud] */

/* end of file */
