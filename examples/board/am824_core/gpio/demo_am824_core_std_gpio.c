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
 * \brief GPIO ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��� 0.5s��LED0 ��˸ 5 �Σ�
 *   2. ֮��LED0 �� 0.2s �ļ��һֱ��˸��
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ơ�
 *
 * \par Դ����
 * \snippet demo_lpc82x_std_gpio.c src_lpc82x_std_gpio
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-10  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc82x_std_gpio
 * \copydoc demo_lpc82x_std_gpio.c
 */

/** [src_lpc82x_std_gpio] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_lpc82x_gpio.h"
#include "demo_std_entries.h"

/** \brief LED0 ���� */
#define __LED0_PIN  PIO0_11

/** \brief �������� */
#define __KEY_PIN  PIO0_1

/**
 * \brief �������
 */
void demo_am824_core_std_gpio_entry (void)
{

    AM_DBG_INFO("demo am824_core std gpio!\r\n");

    demo_std_gpio_entry(__KEY_PIN, __LED0_PIN);
}
/** [src_am824_std_gpio] */

/* end of file */
