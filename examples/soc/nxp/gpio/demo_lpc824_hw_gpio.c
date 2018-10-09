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
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��� 0.5s��LED0 ��˸ 5 �Σ�
 *   2. ֮��LED0 �� 0.2s �ļ��һֱ��˸��
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ơ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_gpio.c src_lpc824_hw_gpio
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_gpio
 * \copydoc demo_lpc824_hw_gpio.c
 */

/** [src_lpc824_hw_gpio] */
#include "ametal.h"
#include "am_delay.h"
#include "hw/amhw_lpc82x_gpio.h"


void demo_lpc824_hw_gpio_entry (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                int                 pin)
{
    uint8_t i = 0;
  
    /* ��� 0.5s��LED0 ��˸ 5 �� */
    for (i = 0; i < 5; i++) {
        amhw_lpc82x_gpio_pin_out_low(p_hw_gpio, pin);
        am_mdelay(500);

        amhw_lpc82x_gpio_pin_out_high(p_hw_gpio, pin);
        am_mdelay(500);
    }

    AM_FOREVER {

        /* LED0 �� 0.2s �ļ��һֱ��˸ */
        amhw_lpc82x_gpio_pin_out_tog(p_hw_gpio, pin);
        am_mdelay(200);
    }
}

/** [src_lpc824_hw_gpio] */

/* end of file */
