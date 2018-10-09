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
 * \brief LED �û������ļ���GPIO ������
 * \sa am_hwconf_led_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_input.h"
#include "am_led_gpio.h"
#include "am_lpc82x.h"

/**
 * \addtogroup am_if_src_hwconf_led_gpio
 * \copydoc am_hwconf_led_gpio.c
 * @{
 */

/** \brief LED ���ź� */
am_local am_const int __g_led_pins[] = {
    PIO0_20,    /* LED0 ���� */
    PIO0_21     /* LED1 ���� */
};

/** \brief LED �豸��Ϣ */
am_local am_const am_led_gpio_info_t __g_led_gpio_devinfo = {
    {
        0,                                /* LED ��ʼ��� */
        AM_NELEMENTS(__g_led_pins) - 1    /* LED ������� */
    },
    __g_led_pins,
    AM_TRUE
};

/** \brief LED �豸ʵ�� */
am_local am_led_gpio_dev_t __g_led_gpio_dev;

/**
 * \brief LED ʵ����ʼ����GPIO ������
 */
int am_led_gpio_inst_init (void)
{
    return am_led_gpio_init(&__g_led_gpio_dev, &__g_led_gpio_devinfo);
}

/**
 * @}
 */

/* end of file */
