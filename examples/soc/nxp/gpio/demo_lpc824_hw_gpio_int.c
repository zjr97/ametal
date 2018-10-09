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
 * - ʵ������
 *   1. PIO0_1 �ĵ�ƽ�ɸߵ�ƽ�ı�Ϊ�͵�ƽ������ KEY/RES ���£�ʱ��LED0 ״̬�ı䡣
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ������Ҫ�� J14 ����ñ�� KEY �� PIO0_1 �̽Ӳ���ʹ�á�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_gpio_int.c src_lpc824_hw_gpio_int
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_gpio_int
 * \copydoc demo_lpc824_hw_gpio_int.c
 */

/** [src_lpc824_hw_gpio_int] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_lpc82x_gpio.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_syscon.h"


/**
 * \brief �����жϷ�����
 */
am_local void __hw_pint_isr (void *p_arg)
{

    int led_pin = (int)p_arg;

    /* ����жϱ�־ */
    amhw_lpc82x_pint_edge_dec_clr(LPC82X_PINT, AMHW_LPC82X_PINT_CHAN_0);

    /* �������״̬��ת */
    amhw_lpc82x_gpio_pin_out_tog(LPC82X_GPIO, led_pin);
}

void demo_lpc824_hw_gpio_int_entry(int                 key_pin,
                                   int                 led_pin,
                                   int                 pint_sel,
                                   int                 inum)
{
    /* �����ж� 0 ѡ�� KEY ���� */
    amhw_lpc82x_syscon_pint_sel(pint_sel, key_pin);

    /* �����жϷ����� */
    am_int_connect(inum, __hw_pint_isr, (void *)led_pin);

    /* ʹ�������ж� */
    am_int_enable(inum);

    AM_FOREVER {
        ; /* VOID */
    }
}

/** [src_lpc824_hw_gpio_int] */

/* end of file */
