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
 * \brief LPC82X ģ�幤��
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-07  nwt, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_led.h"

/**
 * \brief AMetal Ӧ�ó������
 */
void am_main (void) 
{
    AM_DBG_INFO("Start up successful!\r\n");
    /* ������� */

    AM_FOREVER {
        am_led_toggle(LED0);

        am_mdelay(500);
    }
}

/* end of file */
