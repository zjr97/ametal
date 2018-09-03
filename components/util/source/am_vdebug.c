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
 * \brief ������Ϣ�����ʹ��UART����ʼ��
 *
 * \internal
 * \par Modification history
 * - 1.01 15-08-05  bob, USART std interface instead register operation.
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */
 
#include "ametal.h" 
#include "am_vdebug.h"
#include "am_uart.h"
#include "am_koutput.h"
 
/**
 * \brief ���һ���ַ�
 */
static int __dbg_fputc (const char c, void *fil)
{  
    
    /* line feed */
    if ('\n' == c) {
        while (-AM_EAGAIN == am_uart_poll_putchar(fil, '\r')) {
        }
    }
    
    while (-AM_EAGAIN == am_uart_poll_putchar(fil, c)) {
    }

    return 1;
}

/**
 * \brief ���һ���ַ���
 */
static int __dbg_fputs (const char *s, void *fil)
{    
    const char *ss;
    char        c;

    for (ss = s; (c = *ss) != '\0'; ss++) {
        (void)__dbg_fputc(c, fil);
    }

    return (ss - s);
}

am_uart_handle_t  g_dbg_handle;

/**
 * \brief debug��ʼ��
 */
void am_debug_init (am_uart_handle_t handle, uint32_t baudrate)
{   

    g_dbg_handle = handle;

    am_uart_ioctl(handle, AM_UART_BAUD_SET, (void *)baudrate);
    


    am_koutput_set ((void *)handle, __dbg_fputc, __dbg_fputs);
}

 

/* end of file */
