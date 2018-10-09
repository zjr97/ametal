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
 * \brief MiniPort-LED �û������ļ�
 * \sa am_hwconf_miniport_led.c
 *
 * MiniPort-LED ���Ե���ʹ�ã�Ҳ���Ժ� MiniPort-595 ����ʹ�ã��Խ�ʡ��������
 *
 * ��ǰ֧�ֵ��÷��У�
 * 1. MiniPort-LED                : am_miniport_led_inst_init();
 * 2. MiniPort-LED + MiniPort-595 : am_miniport_led_595_inst_init();
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-25  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_led_gpio.h"
#include "am_led_hc595.h"
#include "am_hc595_spi.h"
#include "am_hc595_gpio.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_led
 * \copydoc am_hwconf_miniport_led.c
 * @{
 */

/*******************************************************************************
  MiniPort-LED ����ʹ��
*******************************************************************************/

/** \brief MiniPort-LED ���� */
am_local am_const int __g_miniport_led_pins[8] = {
    PIO0_8,     /* LED0 ���� */
    PIO0_9,     /* LED1 ���� */
    PIO0_10,    /* LED2 ���� */
    PIO0_11,    /* LED3 ���� */
    PIO0_12,    /* LED4 ���� */
    PIO0_13,    /* LED5 ���� */
    PIO0_14,    /* LED6 ���� */
    PIO0_15     /* LED7 ���� */
};

/** \brief MiniPort-LED �豸��Ϣ */
am_local am_const am_led_gpio_info_t __g_miniport_led_gpio_devinfo = {
    {
        0 + 2,                    /* ��ʼ��� 2 */
        7 + 2                     /* ������� 9������ 8 �� LED */
    },
    __g_miniport_led_pins,    /* LED ���� */
    AM_TRUE                   /* �͵�ƽ���� */
};

/** \brief MiniPort-LED �豸ʵ�� */
am_local am_led_gpio_dev_t __g_miniport_led_gpio_dev;

/**
 * \brief MiniPort-LED ʵ����ʼ��������ʹ�ã�
 */
int am_miniport_led_inst_init (void)
{
    return am_led_gpio_init(&__g_miniport_led_gpio_dev,
                            &__g_miniport_led_gpio_devinfo);
}

/*******************************************************************************
  MiniPort-LED �� MiniPort-595 ����ʹ��
*******************************************************************************/

/** \brief ���ݻ��棬��С�� HC595 �ļ���������ͬ */
am_local uint8_t __g_miniport_led_595_buf[1];

/** \brief MiniPort-595 + MiniPort-LED �豸��Ϣ */
am_local am_const am_led_hc595_info_t __g_miniport_led_595_devinfo = {
    {
        0 + 2,                       /* ��ʼ��� 2 */
        7 + 2                        /* ������� 9������ 8 �� LED */
    },
    1,                           /* HC595 �ļ�������  */
    __g_miniport_led_595_buf,    /* ���ݻ��棬��С�� HC595 �ļ���������ͬ */
    AM_TRUE                      /* �͵�ƽ���� */
};

/** \brief MiniPort-595 + MiniPort-LED �豸ʵ�� */
am_local am_led_hc595_dev_t __g_miniport_led_595_dev;

/**
 * \brief MiniPort-595 + MiniPort-LED ʵ����ʼ��
 */
int am_miniport_led_595_inst_init (void)
{
    return am_led_hc595_init(&__g_miniport_led_595_dev,
                             &__g_miniport_led_595_devinfo,
                              am_miniport_595_inst_init());
}

/**
 * @}
 */

/* end of file */
