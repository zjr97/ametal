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
 * \brief ���Դ����û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */
#ifndef __AM_HWCONF_DEBUG_UART_H
#define __AM_HWCONF_DEBUG_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_uart.h"

/**
 * \brief ���Դ���ʵ����ʼ��
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_debug_uart_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_HWCONF_DEBUG_UART_H */

/* end of file */
