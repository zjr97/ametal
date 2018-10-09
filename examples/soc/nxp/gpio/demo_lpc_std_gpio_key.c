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
 * \snippet demo_lpc82x_std_gpio_key.c src_lpc82x_std_gpio_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-11-25  mem, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc82x_std_gpio_key
 * \copydoc demo_lpc82x_std_gpio_key.c
 */

/** [src_lpc82x_std_gpio_key] */
#include "ametal.h"
#include "am_board.h"
#include "am_delay.h"
#include "am_gpio.h"

void demo_lpc_std_gpio_key_entry(int pin)
{
    am_gpio_pin_cfg(pin, AM_GPIO_INPUT);

    AM_FOREVER {

        /* �ȴ��������� */
        while (am_gpio_get(pin) == AM_GPIO_LEVEL_HIGH);

        /* �ӳ�ȥ�� */
        am_mdelay(200);

        /* �ȴ������ͷ� */
        while (am_gpio_get(pin) == AM_GPIO_LEVEL_LOW);

        am_led_toggle(LED0);
    }
}

/** [src_lpc82x_std_gpio_key] */

/* end of file */
