/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC82X USART2 �û������ļ�
 * \sa am_hwconf_lpc82x_usart2.c
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
 * \addtogroup am_if_src_hwconf_lpc82x_usart2
 * \copydoc am_hwconf_lpc82x_usart2.c
 * @{
 */

/**
 * \brief ��������Ƶ�����ã���������Ƶ�ʱ���С��ϵͳʱ��Ƶ����ӦΪ�����ʵ���������
 *
 * Ϊ�����ò�����Ϊ 115200�������ô��ڻ�������Ƶ��Ϊ��
 * 11059200Hz(11059200 = 115200 * 96)
 * ���ڻ�������Ƶ������Ϊ 11.059200MHz�����������������ʵ����� (9600,4800,115200)
 *
 * \note USART2/1/2 ����һ����������Ƶ�ʣ���Ҫ����Ķ�
 */
#ifndef  __LPC82X_UASART_BASE_RATE
#define  __LPC82X_UASART_BASE_RATE  11059200
#endif

/**
 * \brief USART2 ƽ̨��ʼ��
 */
am_local void __lpc82x_usart2_plfm_init (void)
{

    /* ���ô��ڻ���ʱ�� */
    amhw_lpc82x_clk_usart_baseclkrate_set(__LPC82X_UASART_BASE_RATE);

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_UART2);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_UART2);

    am_gpio_pin_cfg(PIO0_27, PIO_FUNC_U2_RXD);
    am_gpio_pin_cfg(PIO0_26, PIO_FUNC_U2_TXD);
}

/**
 * \brief USART2 ƽ̨���ʼ��
 */
am_local void __lpc82x_usart2_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_UART2);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_UART2);

    am_gpio_pin_cfg(PIO0_27, PIO0_27_GPIO);
    am_gpio_pin_cfg(PIO0_26, PIO0_26_GPIO);
}

/** \brief USART2 �豸��Ϣ */
am_local am_const am_lpc_usart_devinfo_t __g_lpc82x_usart2_devinfo = {
    LPC82X_USART2_BASE,             /* USART2 �Ĵ��������ַ */
    INUM_USART2,                    /* USART2 �жϺ� */
    CLK_UART2,                      /* USART2 ʱ�Ӻ� */
    __lpc82x_usart2_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc82x_usart2_plfm_deinit,    /* ƽ̨���ʼ������ */
    NULL                            /* �� RS485 ������ƺ��� */
};

/** \brief USART2 �豸ʵ�� */
am_local am_lpc_usart_dev_t __g_lpc82x_usart2_dev;

/**
 * \brief USART2 ʵ����ʼ��
 */
am_uart_handle_t am_lpc82x_usart2_inst_init (void)
{
    return am_lpc_usart_init(&__g_lpc82x_usart2_dev,
                             &__g_lpc82x_usart2_devinfo);
}

/**
 * \brief USART2 ʵ�����ʼ��
 */
void am_lpc82x_usart2_inst_deinit (am_uart_handle_t handle)
{
    am_lpc_usart_deinit(handle);
}

/**
 * @}
 */

/* end of file */
