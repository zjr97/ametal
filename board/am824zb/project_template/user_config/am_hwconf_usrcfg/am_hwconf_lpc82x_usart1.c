/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC82X USART1 �û������ļ�
 * \sa am_hwconf_lpc82x_usart1.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  bob, first implementation.
 * \endinternal
 */

#include "am_lpc82x.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "am_lpc_usart.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_usart1
 * \copydoc am_hwconf_lpc82x_usart1.c
 * @{
 */

/**
 * \brief ��������Ƶ�����ã���������Ƶ�ʱ���С��ϵͳʱ��Ƶ����ӦΪ�����ʵ���������
 *
 * Ϊ�����ò�����Ϊ115200,�����ô��ڻ�������Ƶ��Ϊ��
 * 11059200Hz(11059200 = 115200 * 96)��
 * ���ڻ�������Ƶ������Ϊ11.059200MHz�����������������ʵ�����(9600,4800,115200)
 * \note  USART0\1\2����һ����������Ƶ��,��Ҫ����Ķ���
 *
 */
#ifndef  __LPC82X_UASART_BASE_RATE

#define  __LPC82X_UASART_BASE_RATE  11059200

#endif

/** \brief USART1ƽ̨��ʼ�� */
static void __lpc82x_plfm_usart1_init (void)
{
    /* ���ô��ڻ���ʱ�� */
    amhw_lpc82x_clk_usart_baseclkrate_set(__LPC82X_UASART_BASE_RATE);

    /* ʹ��USART1ʱ�Ӳ���λ */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_UART1);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_UART1);

    am_gpio_pin_cfg(PIO0_26, PIO_FUNC_U1_RXD);
    am_gpio_pin_cfg(PIO0_27, PIO_FUNC_U1_TXD);
}

/** \brief ���USART1 ƽ̨��ʼ�� */
static void __lpc82x_plfm_usart1_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_UART1);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_UART1);

    am_gpio_pin_cfg(PIO0_26, PIO0_26_GPIO);
    am_gpio_pin_cfg(PIO0_27, PIO0_27_GPIO);
}

/** \brief USART1 �豸��Ϣ */
static const am_lpc_usart_devinfo_t __g_usart1_devinfo = {
    LPC82X_USART1_BASE,                 /**< \brief USART1�Ĵ�����ַ */
    INUM_USART1,                        /**< \brief USART1���жϱ�� */
    CLK_UART0,                          /**< \brief USART0��ʱ�ӱ�� */
    __lpc82x_plfm_usart1_init,          /**< \brief USART1��ƽ̨��ʼ�� */
    __lpc82x_plfm_usart1_deinit,        /**< \brief USART1��ƽ̨ȥ��ʼ�� */
    NULL                                /**< \brief USART1��ƽ̨��RS485�ܽ� */
};

static am_lpc_usart_dev_t  __g_usart1_dev;    /**< \brief ����USART1 �豸 */

/** \brief UART0 ʵ����ʼ�������ADC��׼������ */
am_uart_handle_t am_lpc82x_usart1_inst_init (void)
{
    return am_lpc_usart_init(&__g_usart1_dev, &__g_usart1_devinfo);
}

/** \brief USART1 ʵ�����ʼ�� */
void am_lpc82x_usart1_inst_deinit (am_uart_handle_t handle)
{
    am_lpc_usart_deinit(handle);
}

/**
 * @}
 */

/* end of file */
