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
 * \brief ʱ��Ƶ��������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ "The CLKOUT  rate is  xxx Hz\r\n"��xxx Ϊ��ǰƵ�ʣ�
 *   2. PIO0_27 ���ţ�Ĭ������ CLKOUT ��������������ǰʱ��Ƶ�� 2.5MHz��
 *   3. LED0 �� 0.2s ��ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_hw_clkout.c src_am824_hw_clkout
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_clkout
 * \copydoc demo_am824_hw_clkout.c
 */

/** [src_am824_hw_clkout] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_clkout_entry (void)
{
    am_kprintf("demo am824 hw clkout!\r\n");
    /* ��������Ϊʱ����� */
    am_gpio_pin_cfg(PIO0_27, PIO_FUNC_CLKOUT);

    demo_lpc824_hw_clkout_entry();
}
/** [src_am824_hw_clkout] */

/* end of file */
