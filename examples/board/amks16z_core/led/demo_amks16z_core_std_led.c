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
 * \brief LED���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽�J9/J10����ñ��PIOC_4/PIOC_8����LED0/LED1;
 *   2. ��Ҫ��am_prj_config.hͷ�ļ���ʹ��AM_CFG_LED_ENABLE��
 *
 * - ʵ������
 *   1. LED��0.3s��ʱ������˸��
 * 
 * \par Դ����
 * \snippet demo_amks16z_core_std_led.c src_amks16z_core_std_led
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-21  nwt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_std_led
 * \copydoc demo_amks16z_core_std_led.c
 */

/** [src_amks16z_core_std_led] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_led_entry (void)
{
    AM_DBG_INFO("demo amks16z_core std led!\r\n");

    demo_std_led_entry(LED0);
}

/** [src_amks16z_core_std_led] */

/* end of file */
