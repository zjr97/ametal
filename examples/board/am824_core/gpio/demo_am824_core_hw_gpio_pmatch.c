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
 * \snippet demo_am824_hw_gpio_pmatch.c src_am824_hw_gpio_pmatch
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-24  mem, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_gpio_pmatch
 * \copydoc demo_am824_hw_gpio_pmatch.c
 */

/** [src_am824_hw_gpio_pmatch] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_gpio.h"
#include "demo_nxp_entries.h"


/** \brief LED0 ���� */
#define __LED0_PIN  PIO0_20

/**
 * \brief �������
 */
void demo_am824_hw_gpio_pmatch_entry (void)
{

    am_kprintf("demo am824 hw gpio pmatch!\r\n");

    /* ���� LED0 ���ŷ���Ϊ��� */
    amhw_lpc82x_gpio_pin_dir_output(LPC82X_GPIO, __LED0_PIN);

    demo_lpc824_hw_gpio_pmatch_entry(__LED0_PIN);

}
/** [src_am824_hw_gpio_pmatch] */

/* end of file */
