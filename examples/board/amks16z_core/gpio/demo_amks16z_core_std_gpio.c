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
 *   1. ʹ��������Ϊ�͵�ƽ��
 *
 * - ʵ������
 *   2. ��������Ϊ�͵�ƽʱ���������״̬��ת��
 *
 * \par Դ����
 * \par Դ����
 * \snippet demo_kl26_std_gpio.c src_kl26_std_gpio
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-18  nwt, make some changes.
 * - 1.00 15-10-16  wxj, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_kl26_if_std_gpio
 * \copydoc demo_kl26_std_gpio.c
 */
 
/** [src_kl26_std_gpio] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_gpio_entry (void)
{
    int input_pin, output_pin;

    AM_DBG_INFO("demo amks16z_core std gpio!\r\n");

    input_pin  = PIOC_0;
    output_pin = PIOC_4;

    demo_std_gpio_entry(input_pin, output_pin);
}

/** [src_kl26_std_gpio] */
 
/* end of file */
