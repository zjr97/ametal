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
 * \brief LPC82X USART0 �û������ļ�
 * \sa am_hwconf_lpc82x_usart0.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc_usart.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_usart0
 * \copydoc am_hwconf_lpc82x_usart0.c
 * @{
 */

/**
 * \brief ��������Ƶ�����ã���������Ƶ�ʱ���С��ϵͳʱ��Ƶ����ӦΪ�����ʵ���������
 *
 * Ϊ�����ò�����Ϊ 115200�������ô��ڻ�������Ƶ��Ϊ��
 * 11059200Hz(11059200 = 115200 * 96)
 * ���ڻ�������Ƶ������Ϊ 11.059200MHz�����������������ʵ����� (9600,4800,115200)
 *
 * \note USART0/1/2 ����һ����������Ƶ�ʣ���Ҫ����Ķ�
 */
#ifndef  __LPC82X_UASART_BASE_RATE
#define  __LPC82X_UASART_BASE_RATE  11059200
#endif

/**
 * \brief USART0 ƽ̨��ʼ��
 */
am_local void __lpc82x_usart0_plfm_init (void)
{

    /* ���ô��ڻ���ʱ�� */
    amhw_lpc82x_clk_usart_baseclkrate_set(__LPC82X_UASART_BASE_RATE);

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_UART0);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_UART0);

    am_gpio_pin_cfg(PIO0_4, PIO_FUNC_U0_TXD);
    am_gpio_pin_cfg(PIO0_0, PIO_FUNC_U0_RXD);
}

/**
 * \brief USART0 ƽ̨���ʼ��
 */
am_local void __lpc82x_usart0_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_UART0);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_UART0);

    am_gpio_pin_cfg(PIO0_4, PIO0_4_GPIO);
    am_gpio_pin_cfg(PIO0_0, PIO0_0_GPIO);
}

/** \brief USART0 �豸��Ϣ */
am_local am_const am_lpc_usart_devinfo_t __g_lpc82x_usart0_devinfo = {
    LPC82X_USART0_BASE,             /* USART0 �Ĵ��������ַ */
    INUM_USART0,                    /* USART0 �жϺ� */
    CLK_UART0,                      /* USART0 ʱ�Ӻ� */
    __lpc82x_usart0_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc82x_usart0_plfm_deinit,    /* ƽ̨���ʼ������ */
    NULL                            /* �� RS485 ������ƺ��� */
};

/** \brief USART0 �豸ʵ�� */
am_local am_lpc_usart_dev_t __g_lpc82x_usart0_dev;

/**
 * \brief USART0 ʵ����ʼ��
 */
am_uart_handle_t am_lpc82x_usart0_inst_init (void)
{
    return am_lpc_usart_init(&__g_lpc82x_usart0_dev,
                             &__g_lpc82x_usart0_devinfo);
}

/**
 * \brief USART0 ʵ�����ʼ��
 */
void am_lpc82x_usart0_inst_deinit (am_uart_handle_t handle)
{
    am_lpc_usart_deinit(handle);
}

/**
 * @}
 */

/* end of file */
