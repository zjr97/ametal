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
 * \brief  BME��װʽ�洢ָ��ʵ������
 *
 * - ������
 *   1.PIOA_1 ��������PC���ڵ�TXD;
 *   2.PIOA_2 ��������PC���ڵ�RXD;
 *   3.������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *
 * -ʵ�����󣺴������δ�ӡ�������ַ���������C����ʵ����BMEָ��ִ��Ч���ϵĲ��
 *         ���Կ���BMEָ��ʵ�ֵ�ִ��Ч�ʸ���Ч
 *
 *         systick start value: 0xff9d6a
 *
 *         systick end value: 0xff9d63
 *
 *         systick current value read overhead: 0x7
 *
 *         systick start value: 0xff9cb3
 *
 *         systick end value: 0xff9c9b
 *
 *         actual execution cycle for xor operation with normal C code: 0x11
 *
 *         systick start value: 0xff9cb0
 *
 *         systick end value: 0xff9c9f
 *
 *         actual execution cycle for xor operation with BME macros: 0xa
 *
 *         systick start value: 0xff9d57
 *
 *         systick end value: 0xff9d22
 *
 *         actual execution cycle for BFI operation with normal C: 0x2e
 *
 *         systick start value: 0xff9d19
 *
 *         systick end value: 0xff9d03
 *
 *         actual execution cycle for BFI operation with BME macro: 0xf
 *
 * \note BME ָ�����GPIOģ��ģ�Ӧ��ʹ��KL26_GPIO_BASE�ı�����ַΪ 0x4000_F000
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_bme_deco_stores_gpio.c src_amks16z_core_hw_bme_deco_stores_gpio
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-18  nwt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_bme_deco_stores_gpio
 * \copydoc demo_amks16z_core_hw_bme_deco_stores_gpio.c
 */
 
/** [src_amks16z_core_hw_bme_deco_stores_gpio] */
#include "ametal.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_bme_deco_stores_gpio_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw bme deco stores gpio!\r\n");

    demo_kl26_hw_bme_deco_stores_gpio_entry();
}

/** [src_amks16z_core_hw_bme_deco_stores_gpio] */
 
/* end of file */
