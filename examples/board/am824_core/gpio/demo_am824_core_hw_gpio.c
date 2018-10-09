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
 * \snippet demo_am824_hw_gpio.c src_am824_hw_gpio
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_gpio
 * \copydoc demo_am824_hw_gpio.c
 */

/** [src_am824_hw_gpio] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_gpio.h"
#include "demo_nxp_entries.h"

/** \brief LED0 ���� */
#define __LED0_PIN  PIO0_20

/**
 * \brief �������
 */
void demo_am824_core_hw_gpio_entry (void)
{
  
    am_kprintf("demo am824_core hw gpio!\r\n");
  
    /* �������ŷ���Ϊ��� */
    amhw_lpc82x_gpio_pin_dir_output(LPC82X_GPIO, __LED0_PIN);

    demo_lpc824_hw_gpio_entry(LPC82X_GPIO, __LED0_PIN);
}
/** [src_am824_hw_gpio] */

/* end of file */
