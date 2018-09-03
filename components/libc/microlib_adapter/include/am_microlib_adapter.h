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
 * \brief Micro LIB ������
 *
 * \par ˵��
 * 1. �ڴ����ӿ�ֻ����Micro LIB��ametalϵͳ�ӿ�֮��ѡ��һ��ʹ��
 *
 * ��ʹ��ǰ��������"Project->Options for Target xxx->Target"�й�ѡ"Use MicroLIB"
 * ����ʼ������������ʹ��UART�����Ϣ�����ʼ�������ĵ��÷������£�
 *
 * \code
 * static int __dbg_fputc (void *p_arg, const char ch)
 * {  
 *     while (-AM_EAGAIN == am_uart_poll_putchar(p_arg, ch)) {
 *         ;
 *     }
 * 
 *     return ch;
 * }
 * 
 * static int __dbg_fgetc (void *p_arg)
 * {  
 *     char ch;
 *     
 *     while (-AM_EAGAIN == am_uart_poll_getchar(p_arg, &ch)) {
 *         ;
 *     }
 * 
 *     return ch;
 * }
 * 
 * static am_microlib_adapter_ops_t g_microlib_adapter_ops = {
 *     __dbg_fputc,
 *     __dbg_fgetc
 * };
 * 
 * int am_microlib_init (am_uart_handle_t uart_handle)
 * {
 *     return am_microlib_adapter_init(&g_microlib_adapter_ops, uart_handle);
 * }
 * \endcode
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-17  pea, first implementation.
 * \endinternal
 */
 
#ifndef __AM_MICROLIB_ADAPTER_H
#define __AM_MICROLIB_ADAPTER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_microlib_adapter
 * \copydoc am_microlib_adapter.h
 * @{
 */

/**
 * \brief __FILE�ṹ,��<stdio.h>�б�typedefΪFILE����
 */
struct __FILE {
    
    int handle; /**< \brief �ļ���� */
    
};

/**
 * \brief ����ѡ�����ʵ��Ӳ��ƽ̨�ṩ
 */
typedef struct am_microlib_adapter_ops {
    
    int (*pfn_putc) (void *p_arg, const char ch); /**< ����ָ�룬���һ���ַ� */
    int (*pfn_getc) (void *p_arg);                /**< ����ָ�룬����һ���ַ� */
    
} am_microlib_adapter_ops_t;

/**
 * \brief ��������ʼ��
 *
 * \param[in] p_ops ��������
 * \param[in] p_arg ������������
 *
 * \return AM_OK
 */
int am_microlib_adapter_init (const am_microlib_adapter_ops_t *p_ops,
                              void                            *p_arg);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_MICROLIB_ADAPTER_H */

/* end of file */
