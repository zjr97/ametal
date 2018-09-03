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
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽� J9 �� J10 ����ñ��PIOC_9 �� PIOA_8 �ֱ���� LED0 �� LED1��
 *
 * - ʵ������
 *   1. LED0 �� LED1 �� 0.3s ��ʱ������˸��
 *
 * \note
 *    ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_LED_ENABLE ����Ϊ 1
 *    ����Щ���Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *
 * \par Դ����
 * \snippet demo_zlg217_std_led.c src_std_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_led
 * \copydoc demo_zlg217_std_led.c
 */

/** [src_std_led] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_led_entry (void)
{
    AM_DBG_INFO("demo am217_core std led!\r\n");

    demo_std_led_entry(LED0);
}
/** [src_std_led] */

/* end of file */
