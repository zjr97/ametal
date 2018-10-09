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
 * \snippet demo_am824_hw_usart_poll.c src_am824_hw_usart_poll
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_usart_poll
 * \copydoc demo_am824_hw_usart_poll.c
 */

/** [src_am824_hw_usart_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "demo_nxp_entries.h"

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
  
/**
 * \brief �������
 */
void demo_am824_core_hw_usart_poll_entry (void)
{

    am_kprintf("demo am824 hw usart poll !\r\n");
    /* ���ô��ڻ���ʱ�� */
    amhw_lpc82x_clk_usart_baseclkrate_set(__LPC82X_UASART_BASE_RATE);

    /* ʹ�ܴ��� 0 ʱ�Ӳ���λ */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_UART0);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_UART0);

    /* �������Ÿ��� */
    am_gpio_pin_cfg(PIO0_4, PIO_FUNC_U0_TXD);
    am_gpio_pin_cfg(PIO0_0, PIO_FUNC_U0_RXD);

    demo_lpc_hw_usart_poll_entry(LPC82X_USART0, 
                                 amhw_lpc82x_clk_usart_baseclkrate_get(),
                                 115200);
}
/** [src_am824_hw_usart_poll] */

/* end of file */
