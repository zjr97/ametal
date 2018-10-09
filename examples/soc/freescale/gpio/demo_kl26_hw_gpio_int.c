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
 * \brief GPIO�����ж����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ������
 * - 1.��J14��key��PIOC_0�̽���һ��;
 *   2.��J9��LED0��PIOC_4�̽���һ��;
 *   3.��J10��LED1��PIOC_8�̽���һ��;
 *   4.PIOA_1 ��������PC���ڵ�TXD;
 *   5.PIOA_2 ��������PC���ڵ�RXD;
 *   6.������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *
 *- ʵ�����󣺳������ص�demo��󣬰��°�����demo���ϵ�LED0����,
 *          ͬʱ������� "the gpio interrupt happen!"
 *
 * \par Դ����
 * \snippet demo_kl26_hw_gpio_int.c src_kl26_hw_gpio_int
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  nwt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_hw_gpio_int
 * \copydoc demo_kl26_hw_gpio_int.c
 */

/** [src_kl26_hw_gpio_int] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_gpio.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"


/** 
 * \brief �����жϷ�����
 */
static void hw_gpio_isr (void *p_arg)
{
    amhw_kl26_port_t *p_hw_port = (amhw_kl26_port_t *)p_arg;

    /* ����жϱ�־ */
    amhw_kl26_port_pin_isf_clr(p_hw_port, PIOC_0);
    /* �������״̬��ת */
    am_gpio_toggle(PIOC_4);

    AM_DBG_INFO("the gpio interrupt happen!\r\n");
}

/**
 * \brief �������
 */
void demo_kl26_hw_gpio_int_entry (void)
{
    /* ���� PORTC 0,4�Źܽ�ΪGPIO���� */
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_4, 0x1);
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_0, 0x1);

    /* ����GPIOC 4�Źܽ�Ϊ������� */
    amhw_kl26_gpio_pin_dir_output(KL26_GPIO, PIOC_4);
    /* ����GPIOC 0���ŷ���Ϊ���� */
    amhw_kl26_gpio_pin_dir_input(KL26_GPIO, PIOC_0);

    /* ����GPIOC 4�Źܽų�ʼ��ƽ */
    amhw_kl26_gpio_pin_init_out_low(KL26_GPIO, PIOC_4);

    /* ����GPIOC 0����Ϊ���� */
    amhw_kl26_port_pin_pull_enable(KL26_PORT, PIOC_0);
    amhw_kl26_port_pin_pull_up(KL26_PORT, PIOC_0);

    /* ����GPIOC 0Ϊ�½��ش��� */
    amhw_kl26_port_pin_irq_cfg(KL26_PORT, PIOC_0, AMHW_KL26_INT_FALLING);

    /* �����жϷ����� */
    am_gpio_trigger_connect(PIOC_0, hw_gpio_isr, (void *)KL26_PORT);

    while (1) {
        ;
    }
}

/** [src_kl26_hw_gpio_int] */

/* end of file */
