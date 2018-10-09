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
 * \brief KS16xx GPIO��PORT HW������
 *
 * \brief GPIO ���������������������
 * - ������
 *   1.��J14��key��PIOC_0�̽���һ��;
 *   2.��J9��LED0��PIOC_4�̽���һ��;
 *   3.��J10��LED1��PIOC_8�̽���һ��;
 *
 * -ʵ�����󣺳������ص�demo��󣬰���һ�ΰ���LED0�����һ�η�ת����������demo���ϵ�LED0������
 *
 * \par Դ����
 * \par Դ����
 * \snippet demo_kl26_hw_gpio.c src_kl26_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-18  nwt, make some changes.
 * - 1.00 15-10-16  wxj, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_kl26_if_hw_gpio
 * \copydoc demo_kl26_hw_gpio.c
 */
 
/** [src_kl26_hw_gpio] */
#include "ametal.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_gpio.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief �������
 */
void demo_kl26_hw_gpio_entry (void)
{
    int pin_val=0;

    /* ���� PORTC 0,4�Źܽ�ΪGPIO���� */
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_4, 0x1);
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_0, 0x1);

    /* GPIOC 0 �ܽ���/����ʹ�� */
    amhw_kl26_port_pin_pull_enable(KL26_PORT, PIOC_0);

    /* GPIOC 0 ������������ */
    amhw_kl26_port_pin_pull_up(KL26_PORT, PIOC_0);

    /* ����GPIOC 4�Źܽų�ʼ��ƽ */
    amhw_kl26_gpio_pin_init_out_low(KL26_GPIO, PIOC_4);

    /* ����GPIOC 4�Źܽ�Ϊ������� */
    amhw_kl26_gpio_pin_dir_output(KL26_GPIO, PIOC_4);

    /* ����GPIOC 0�Źܽ�Ϊ���뷽�� */
    amhw_kl26_gpio_pin_dir_input(KL26_GPIO, PIOC_0);

    while (1) {

        /* ��ȡ���������ƽ */
        pin_val = amhw_kl26_gpio_pin_input_get(KL26_GPIO, PIOC_0);

        if (pin_val == 0) {
            /* ��ת���������ƽ */
            amhw_kl26_gpio_pin_out_toggle (KL26_GPIO, PIOC_4);

            am_mdelay(200);

        }
    }
}

/** [src_kl26_hw_gpio] */
 
/* end of file */
