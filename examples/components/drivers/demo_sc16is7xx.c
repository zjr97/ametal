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
 * \brief SC16IS7XX ����
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����Խ����
 *
 * \par Դ����
 * \snippet demo_sc16is7xx.c src_sc16is7xx
 *
 * \internal
 * \par Modification history
 * - 1.00  18-09-14  wk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_sc16is7xx
 * \copydoc demo_sc16is7xx.c
 */

/** [src_sc16is7xx] */
#include "ametal.h"
#include "am_delay.h"
#include "am_sc16is7xx.h"
#include "am_hwconf_sc16is7xx.h"
#include "am_vdebug.h"

/**
 * \brief �������
 */
void demo_sc16is7xx_entry (void)
{  
    char get_char[64] = {0};
    am_sc16is7xx_handle_t handle;

    handle = am_sc16is7xx_inst_init();

    while (1) {
			
        am_sc16is7xx_uart_poll_receive(handle, 0, get_char, 64);

        am_sc16is7xx_uart_poll_send(handle, 0, get_char, 64);

    }
}
/** [src_sc16is7xx] */

/* end of file */
