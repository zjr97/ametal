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
 * \brief GPIO �������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ������Ҫ�� J14 ����ñ�� KEY �� PIO0_1 �̽Ӳ���ʹ�á�
 *
 * \par Դ����
 * \snippet demo_am824_std_gpio_key.c src_am824_std_gpio_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-11-25  mem, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_gpio_key
 * \copydoc demo_am824_std_gpio_key.c
 */

/** [src_am824_std_gpio_key] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_lpc82x_gpio.h"
#include "demo_nxp_entries.h"

/** \brief �������� */
#define __KEY_PIN  PIO0_1

/**
 * \brief �������
 */
void demo_am824_core_std_gpio_key_entry (void)
{
    AM_DBG_INFO("demo am824_core std gpio key!\r\n");

    demo_lpc_std_gpio_key_entry(__KEY_PIN);
}
/** [src_am824_std_gpio_key] */

/* end of file */
