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
 * \snippet demo_amks16z_core_hw_gpio_int.c src_amks16z_core_hw_gpio_int
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  nwt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_gpio_int
 * \copydoc demo_amks16z_core_hw_gpio_int.c
 */

/** [src_amks16z_core_hw_gpio_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_fsl_entrys.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_gpio_int_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw gpio int!\r\n");

    demo_kl26_hw_gpio_int_entry();
}

/** [src_amks16z_core_hw_gpio_int] */

/* end of file */
