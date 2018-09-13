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
 * \brief GPIO ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ��������Ϊ�͵�ƽ��
 *
 * - ʵ������
 *   2. ��������Ϊ�͵�ƽʱ���������״̬��ת��
 *
 * \par Դ����
 * \snippet demo_std_gpio.c src_std_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_gpio
 * \copydoc demo_std_gpio.c
 */

/** [src_std_gpio] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_gpio_entry (int input_pin, int output_pin)
{
    uint8_t dir_input = 0;

    /* һ��Ĭ�ϰ�����Ӧ�� GPIO ������Ϊ���� */
    am_gpio_pin_cfg(input_pin, AM_GPIO_INPUT | AM_GPIO_PULLUP);

    /* һ��Ĭ�� LED ��Ӧ�� GPIO ������Ϊ��� */
    am_gpio_pin_cfg(output_pin, AM_GPIO_OUTPUT_INIT_LOW | AM_GPIO_PULLUP);

    while (1) {

         dir_input = am_gpio_get(input_pin);
         if (dir_input == 0) {

             /*  �������� */
             while (am_gpio_get(input_pin) == 0);
            
             /* ��תoutput_pin */
             am_gpio_toggle(output_pin);
         }
    }
}
/** [src_std_gpio] */

/* end of file */
