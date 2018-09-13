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
 * \brief Newlib ������
 *
 * \par ˵��
 * 1. ����ʹ�� newlib-nano�⣬�����������������Ӳ�����--specs=nano.specs
 * 2. ����Ҫʹ��printf��ӡ������������Ҫ���Ӳ����� -u _printf_float
 * 3. ����Ҫʹ��scanf���ո�����������Ҫ���Ӳ�����  -u _scanf_float
 * 4. ��ʹ����printf������ջ�ռ䲻С�� 1K
 *
 * ��ʹ��ǰ�������ʼ������������ʹ��UART�����Ϣ�����ʼ�������ĵ��÷������£�
 *
 * \code
 * static int __console_send (void *p_cookie, void *p_buf, size_t cnt)
 * {
 *    return am_uart_poll_send(p_cookie, p_buf, cnt);
 * }
 *
 * static int __console_receive (void *p_cookie, void *p_buf, size_t cnt)
 * {
 *     return am_uart_poll_receive(p_cookie, p_buf, cnt);
 * }
 *
 * static const am_newlib_adapter_ops_t  __g_newlib_adapter_ops = {
 *     __console_send,
 *     __console_receive
 * };
 *
 * void am_board_newlib_init (am_uart_handle_t handle)
 * {
 *     am_newlib_adapter_init(&__g_newlib_adapter_ops, handle);
 * }
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 17-07-24  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_NEWLIB_ADAPTER_H
#define __AM_NEWLIB_ADAPTER_H

#include "am_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_newlib_adapter
 * \copydoc am_newlib_adapter.h
 * @{
 */

/**
 * \brief ����ѡ�����ʵ��Ӳ��ƽ̨�ṩ
 */
typedef struct am_newlib_adapter_ops {
    int (*pfn_console_send) (void *p_cookie, const void *p_buf, size_t cnt);
    int (*pfn_console_receive) (void *p_cookie, void *p_buf, size_t cnt);
} am_newlib_adapter_ops_t;

/**
 * \brief ��������ʼ��
 *
 * \param[in] p_ops     : ��������
 * \param[in] p_cookie  : ������������
 *
 * \return AM_OK
 */
int am_newlib_adapter_init (const am_newlib_adapter_ops_t *p_ops,
                            void                          *p_cookie);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_NEWLIB_ADAPTER_H */

/* end of file */
