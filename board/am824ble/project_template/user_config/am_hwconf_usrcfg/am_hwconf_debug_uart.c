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
 * \brief ���Դ����û������ļ�
 * \sa am_hwconf_debug_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_uart.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_debug_uart
 * \copydoc am_hwconf_debug_uart.c
 * @{
 */

/** \brief ʹ�õĵ��Դ��� 0: UART0  1: UART1  2: UART2 */
#define __DEBUG_UART            0

/** \brief ���õ��Դ�������Ĳ����� */
#define __DEBUG_BAUDRATE        115200

/**
 * \brief ���Դ���ʵ����ʼ��
 */
am_uart_handle_t am_debug_uart_inst_init (void)
{
    am_uart_handle_t handle = NULL;

#if (__DEBUG_UART == 0)
    handle = am_lpc82x_usart0_inst_init();   /* ���ڳ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE); /* ���Գ�ʼ�� */
#elif (__DEBUG_UART == 1)
    handle = am_lpc82x_usart1_inst_init();   /* ���ڳ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE); /* ���Գ�ʼ�� */
#elif (__DEBUG_UART == 2)
    handle = am_lpc82x_usart2_inst_init();   /* ���ڳ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE); /* ���Գ�ʼ�� */
#endif

    return handle;
}

/**
 * @}
 */

/* end of file */
