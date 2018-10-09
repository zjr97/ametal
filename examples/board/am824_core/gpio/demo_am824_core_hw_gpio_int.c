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
 * \snippet demo_am824_hw_gpio_int.c src_am824_hw_gpio_int
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_gpio_int
 * \copydoc demo_am824_hw_gpio_int.c
 */

/** [src_am824_hw_gpio_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_int.h"
#include "hw/amhw_lpc82x_gpio.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "hw/amhw_lpc82x_iocon.h"
#include "demo_nxp_entries.h"

/** \brief LED0 ���� */
#define __LED0_PIN  PIO0_20

/** \brief �������� */
#define __KEY_PIN  PIO0_1


/**
 * \brief �������
 */
void demo_am824_core_hw_gpio_int_entry (void)
{

    am_kprintf("demo am824 hw gpio int!\r\n");

    /* ���� LED ���ŷ���Ϊ��� */
    amhw_lpc82x_gpio_pin_dir_output(LPC82X_GPIO, __LED0_PIN);

    /* ���� KEY ���ŷ���Ϊ���� */
    amhw_lpc82x_gpio_pin_dir_input(LPC82X_GPIO, __KEY_PIN);

    /* ���� KEY ����Ϊ���� */
    amhw_lpc82x_iocon_mode_set(LPC82X_IOCON, __KEY_PIN,
                               AMHW_LPC82X_IOCON_MODE_PULLUP);

    /* ����Ϊ�½��ش��� */
    amhw_lpc82x_pint_trigger_set(LPC82X_PINT,
                                 AMHW_LPC82X_PINT_CHAN_0,
                                 AMHW_LPC82X_PINT_TRIGGER_FALL);

    demo_lpc824_hw_gpio_int_entry(__KEY_PIN,
                                  __LED0_PIN,
                                  AMHW_LPC82X_PINT_CHAN_0,
                                  PIN_INT0_IRQn);
}
/** [src_am824_hw_gpio_int] */

/* end of file */
