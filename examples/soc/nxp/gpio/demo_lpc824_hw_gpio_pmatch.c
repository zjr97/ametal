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
 * \brief GPIO ģʽƥ��������ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �߼����ʽΪ:(/IN0) * IN1 + (/IN3) + (/IN4��*(/IN5)
 *      ���������κ�һ�����㴥���жϣ�
 *          - IN0 Ϊ�͵�ƽ�� IN1 ��Ϊ�ߵ�ƽ��
 *          - IN3 Ϊ�͵�ƽ
 *          - IN4 Ϊ�͵�ƽ�� IN5 �������½����¼�
 *   2. �ж�ͨ�������Ŷ�Ӧ��ϵ��
 *          - IN0 - PIO0_14
 *          - IN1 - PIO0_15
 *          - IN3 - PIO0_16
 *          - IN4 - PIO0_17
 *          - IN5 - PIO0_18
 *
 * - ʵ������
 *   1. �жϱ�����ʱ��LED0 ״̬��ת�����ڴ�ӡ "gpio pmatch count %d\r\n"��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_gpio_pmatch.c src_lpc824_hw_gpio_pmatch
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-24  mem, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_gpio_pmatch
 * \copydoc demo_lpc824_hw_gpio_pmatch.c
 */

/** [src_lpc824_hw_gpio_pmatch] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_swm.h"
#include "hw/amhw_lpc82x_gpio.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_iocon.h"
#include "hw/amhw_lpc82x_syscon.h"


/** \brief ƥ���������� */
#define __IN_PIN0 PIO0_14
#define __IN_PIN1 PIO0_15
#define __IN_PIN2 PIO0_16
#define __IN_PIN3 PIO0_17
#define __IN_PIN4 PIO0_18

/**
 * \brief �����жϷ�����
 */
am_local void __pint_isr (void *p_arg)
{
    am_local int i = 0;

    int pin = (int)p_arg;

    AM_DBG_INFO("gpio pmatch count %d\r\n", i++);
    
    /* �������״̬��ת */
    amhw_lpc82x_gpio_pin_out_tog(LPC82X_GPIO, pin);
}

/**
 * \brief ���ų�ʼ��
 */
void demo_lpc824_hw_gpio_pmatch_entry (int pin)
{

    /* �������⹦�� */
    amhw_lpc82x_swm_pin_fixed_func_disable(LPC82X_SWM, __IN_PIN0);
    amhw_lpc82x_swm_pin_fixed_func_disable(LPC82X_SWM, __IN_PIN1);
    amhw_lpc82x_swm_pin_fixed_func_disable(LPC82X_SWM, __IN_PIN2);
    amhw_lpc82x_swm_pin_fixed_func_disable(LPC82X_SWM, __IN_PIN3);
    amhw_lpc82x_swm_pin_fixed_func_disable(LPC82X_SWM, __IN_PIN4);

    /* ����Ϊ�������� */
    amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                               __IN_PIN0,
                               AMHW_LPC82X_IOCON_MODE_PULLUP);
    amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                               __IN_PIN1,
                               AMHW_LPC82X_IOCON_MODE_PULLUP);
    amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                               __IN_PIN2,
                               AMHW_LPC82X_IOCON_MODE_PULLUP);
    amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                               __IN_PIN3,
                               AMHW_LPC82X_IOCON_MODE_PULLUP);
    amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                               __IN_PIN4,
                               AMHW_LPC82X_IOCON_MODE_PULLUP);

    amhw_lpc82x_gpio_port_dir_input(LPC82X_GPIO, AM_SBF(0x1F,4));

    /* Ϊÿ��ͨ��ѡ������ */
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_0, __IN_PIN0);
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_1, __IN_PIN1);
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_3, __IN_PIN2);
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_4, __IN_PIN3);
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_5, __IN_PIN4);

    /* ����ÿ��λƬ */
    amhw_lpc82x_pint_pmatch_slice_cfg(
        LPC82X_PINT,
        AMHW_LPC82X_PINT_BITSLICE_0,            /* ����λƬ 0 */
        AMHW_LPC82X_PINT_CHAN_0,                /* ѡ��ͨ�� 0 */
        AMHW_LPC82X_PINT_SLICE_ARG_LOW_LEVEL,   /* �͵�ƽ��Ч */
        AM_FALSE);                              /* ���Ƕ˵� */

    amhw_lpc82x_pint_pmatch_slice_cfg(
        LPC82X_PINT,
        AMHW_LPC82X_PINT_BITSLICE_1,            /* ����λƬ 1 */
        AMHW_LPC82X_PINT_CHAN_1,                /* ѡ��ͨ�� 1 */
        AMHW_LPC82X_PINT_SLICE_ARG_HIGH_LEVEL,  /* �ߵ�ƽ��Ч */
        AM_TRUE);                               /* �Ƕ˵� */

    amhw_lpc82x_pint_pmatch_slice_cfg(
        LPC82X_PINT,
        AMHW_LPC82X_PINT_BITSLICE_3,            /* ����λƬ 3 */
        AMHW_LPC82X_PINT_CHAN_3,                /* ѡ��ͨ�� 3 */
        AMHW_LPC82X_PINT_SLICE_ARG_LOW_LEVEL,   /* �͵�ƽ��Ч */
        AM_TRUE);                               /* �Ƕ˵� */

    amhw_lpc82x_pint_pmatch_slice_cfg(
        LPC82X_PINT,
        AMHW_LPC82X_PINT_BITSLICE_4,            /* ����λƬ 4 */
        AMHW_LPC82X_PINT_CHAN_4,                /* ѡ��ͨ�� 4 */
        AMHW_LPC82X_PINT_SLICE_ARG_LOW_LEVEL,   /* �͵�ƽ��Ч */
        AM_FALSE);                              /* ���Ƕ˵� */

    amhw_lpc82x_pint_pmatch_slice_cfg(
        LPC82X_PINT,
        AMHW_LPC82X_PINT_BITSLICE_5,            /* ����λƬ 5 */
        AMHW_LPC82X_PINT_CHAN_5,                /* ѡ��ͨ�� 5 */
        AMHW_LPC82X_PINT_SLICE_ARG_STICKY_FALL, /* �������½��� */
        AM_TRUE);                               /* �Ƕ˵� */

    /* �����ж�ģʽΪģʽƥ�� */
    amhw_lpc82x_pint_pmatch_mode_set(LPC82X_PINT);

    /* ������Ӧ�˵���ж� */
    am_int_connect(INUM_PIN_INT1, __pint_isr, (void *)pin);
    am_int_connect(INUM_PIN_INT3, __pint_isr, (void *)pin);
    am_int_connect(INUM_PIN_INT5, __pint_isr, (void *)pin);

    am_int_enable(INUM_PIN_INT1);
    am_int_enable(INUM_PIN_INT3);
    am_int_enable(INUM_PIN_INT5);
}


/** [src_lpc824_hw_gpio_pmatch] */

/* end of file */
