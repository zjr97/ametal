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
 * - �������裺
 *   1. ʹ��Ӧ���ж������ϲ����½��ء�
 *
 * - ʵ������
 *   1. �жϲ���ʱ���Դ������ "the gpio interrupt happen!"��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_gpio_trigger.c src_amks16z_core_std_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-18  nwt, make some changes.
 * - 1.00 15-10-16  wxj, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_std_gpio_trigger
 * \copydoc demo_amks16z_core_std_gpio_trigger.c
 */
 
/** [src_amks16z_core_std_gpio_trigger] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_led.h"
#include "am_gpio.h"
#include "demo_std_entries.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_gpio_trigger_entry (void)
{
    AM_DBG_INFO("demo amks16z_core std gpio trigger!\r\n");

    am_gpio_pin_cfg(PIOC_0, AM_GPIO_INPUT | AM_GPIO_PULLUP);

    demo_std_gpio_trigger_entry(PIOC_0);
}

/** [src_amks16z_core_std_gpio_trigger] */
 
/* end of file */
