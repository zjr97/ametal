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
 * \snippet demo_lpc824_hw_clkout.c src_lpc824_hw_clkout
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_clkout
 * \copydoc demo_lpc824_hw_clkout.c
 */

/** [src_lpc824_hw_clkout] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"


/** \brief ʱ��Դ���� */
#define __CLKOUT_SRC  AMHW_LPC82X_CLK_CLKOUT_SRC_MAINCLK

/** \brief ʱ�ӷ�Ƶ�������� */
#define __CLKOUT_DIV  24

/**
 * \brief �������
 */
void demo_lpc824_hw_clkout_entry (void)
{
    /* �����ڲ� IRC */
    if (__CLKOUT_SRC == AMHW_LPC82X_CLK_CLKOUT_SRC_IRC) {

        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_IRC);
        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_IRC_OUT);

    /* ���� WDT ʱ������ */
    } else if (__CLKOUT_SRC == AMHW_LPC82X_CLK_CLKOUT_SRC_WDTOSC) {

        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_WDT_OSC);

    /* ϵͳ���� */
    } else if (__CLKOUT_SRC == AMHW_LPC82X_CLK_CLKOUT_SRC_SYSOSC) {

        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_SYS_OSC);
    }

    /* �������ʱ��Դ��ʱ�ӷ�Ƶ���� */
    amhw_lpc82x_clk_clkout_config(__CLKOUT_SRC, __CLKOUT_DIV);

    AM_DBG_INFO("The CLKOUT  rate is  %8d Hz\r\n",
                 amhw_lpc82x_clk_main_clkrate_get() / __CLKOUT_DIV);

    AM_FOREVER {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}
/** [src_lpc824_hw_clkout] */

/* end of file */
