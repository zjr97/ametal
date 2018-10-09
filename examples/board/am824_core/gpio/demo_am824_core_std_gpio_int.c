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
 * \brief GPIO �����ж����̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� J14 �� KEY �� PIO0_1 �̽���һ��
 *
 * - ʵ������
 *   1. PIO0_1 �ĵ�ƽ�ɸߵ�ƽ�ı�Ϊ�͵�ƽ������ KEY/RES ���£�ʱ��LED0 ״̬�ı䡣
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ������Ҫ�� J14 ����ñ�� KEY �� PIO0_1 �̽Ӳ���ʹ�á�
 *
 * \par Դ����
 * \snippet demo_am824_std_gpio_int.c src_am824_std_gpio_int
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-10  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_gpio_int
 * \copydoc demo_am824_std_gpio_int.c
 */

/** [src_am824_std_gpio_int] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_lpc82x.h"
#include "demo_std_entries.h"

/** \brief �������� */
#define __KEY_PIN  PIO0_1

/**
 * \brief �������
 */
void demo_am824_core_std_gpio_int_entry (void)
{
    AM_DBG_INFO("demo am824_core std gpio trigger!\r\n");

    demo_std_gpio_trigger_entry(__KEY_PIN);
}
/** [src_am824_std_gpio_int] */

/* end of file */
