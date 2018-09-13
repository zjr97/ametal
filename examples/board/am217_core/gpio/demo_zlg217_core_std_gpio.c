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
 * - �������裺
 *   1. �� J14 �� KEY �� PIOC_7 �̽���һ��
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ơ�
 *
 * \par Դ����
 * \snippet demo_zlg217_std_gpio.c src_zlg217_std_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-24  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_gpio
 * \copydoc demo_zlg217_std_gpio.c
 */

/** [src_zlg217_std_gpio] */
#include "am_vdebug.h"
#include "am_zlg217.h"
#include "am_board.h"
#include "demo_std_entries.h"

#define INPUT_PIN  PIOC_7 /**< \brief �������� */
#define OUTPUT_PIN PIOC_9 /**< \brief ������� PIOC_9��LED���� */

/**
 * \brief �������
 */
void demo_zlg217_core_std_gpio_entry (void)
{
    AM_DBG_INFO("demo am217_core std gpio!\r\n");

    demo_std_gpio_entry(INPUT_PIN, OUTPUT_PIN);
}
/** [src_zlg217_std_gpio] */

/* end of file */
