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
 * \brief PLL ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��ӡ PLL ����Ƶ�ʡ�ʵ�����Ƶ�ʺ� CLKOUT �������Ƶ�ʣ�
 *   2. CLKOUT ����(PIO0_27 ����)��� __CLKOUT_DIV ��Ƶ�����ʱ��Ƶ�ʣ�
 *   3. LED0 �� 0.5s ��ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_pll.c src_lpc824_hw_pll
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-20  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_pll
 * \copydoc demo_lpc824_hw_pll.c
 */

/** [src_lpc824_hw_pll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "hw/amhw_lpc82x_iocon.h"
#include "hw/amhw_lpc82x_swm.h"
#include "hw/amhw_lpc82x_clk.h"
#include "am_lpc82x_inst_init.h"

/**
 * \brief PLL ʱ��Դ��Ϊ����һ�֣�
 *            AMHW_LPC82X_CLK_PLLIN_SRC_IRC
 *            AMHW_LPC82X_CLK_PLLIN_SRC_SYSOSC
 *            AMHW_LPC82X_CLK_PLLIN_SRC_CLKIN
 */
#define __PLL_CLKSRC                AMHW_LPC82X_CLK_PLLIN_SRC_IRC

/** \name PLL Ƶ�ʿ���
 *
 * M = AM_CFG_SYSPLLCTRL_M + 1
 * P = 2^(AM_CFG_SYSPLLCTRL_P)
 *
 * PLLOUT = M * PLLIN;
 * FCCO = 2 * P * PLLOUT;
 * @{
 */

/** \brief PLL ���ƼĴ��� PSEL ֵ */
#define __PLL_CFG_PSEL               1

/** \brief PLL ���ƼĴ��� MSEL ֵ */
#define __PLL_CFG_MSEL               3

/** \brief PLL ����Ƶ�� */
#define __PLL_DESIREDRATE            (48000000UL)

/** \brief ѡ�����ʱ��Դ */
#define __CLKOUT_SRC                 AMHW_LPC82X_CLK_CLKOUT_SRC_MAINCLK

/** \brief ���ʱ��Դ��Ƶ */
#define __CLKOUT_DIV                 48
/**
 * @}
 */

/**
 * \brief �������
 */
void demo_lpc824_hw_pll_entry (void)
{
    volatile uint32_t i = 0;

    /* �����ڲ� IRC */
    if (__CLKOUT_SRC == AMHW_LPC82X_CLK_CLKOUT_SRC_IRC) {
        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_IRC);
        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_IRC_OUT);

    /* ���� WDT ʱ������ */
    } else if (__CLKOUT_SRC == AMHW_LPC82X_CLK_CLKOUT_SRC_WDTOSC) {
        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_WDT_OSC);

    /* ����ϵͳ���� */
    } else if (__CLKOUT_SRC == AMHW_LPC82X_CLK_CLKOUT_SRC_SYSOSC) {
        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_SYS_OSC);
     }

    /* ���� PLL ֮ǰ���ı���ʱ��ԴΪ IRC */
    amhw_lpc82x_clk_main_src_set(AMHW_LPC82X_CLK_MAIN_SRC_IRC);

    /* ���� PLL ʱ��Դǰ��׼�� */
    if (__PLL_CLKSRC == AMHW_LPC82X_CLK_PLLIN_SRC_SYSOSC) {

        /* ϵͳ������Ϊ PLL ʱ��Դ */

        /* �� PIO0_8,��PIO0_9 ����Ϊ����ģʽ���������������� */
        amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                                   PIO0_8,
                                   AMHW_LPC82X_IOCON_MODE_INACTIVE);

        amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                                   PIO0_9,
                                   AMHW_LPC82X_IOCON_MODE_INACTIVE);

        /* ʹ�� PIO0_8_XTALIN��PIO0_9_XTALOUT ���ؾ���̶����Ź��� */
        amhw_lpc82x_swm_fixed_func_enable(LPC82X_SWM,
                                          AMHW_LPC82X_SWM_PIO0_8_XTALIN);

        amhw_lpc82x_swm_fixed_func_enable(LPC82X_SWM,
                                          AMHW_LPC82X_SWM_PIO0_9_XTALOUT);

        /* �ⲿ XTAL < 15MHz */
        amhw_lpc82x_clk_pll_bypass_set( AM_FALSE,  AM_FALSE);

         /* ʹ��ϵͳ OSC */
        amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_SYS_OSC);

        for (i = 0; i < 200; i++);
    }

    if (__PLL_CLKSRC == AMHW_LPC82X_CLK_PLLIN_SRC_CLKIN) {

        /* �ⲿ�ܽ�������Ϊʱ��Դ */

        /* �� PIO0_1 ����Ϊ����ģʽ���������������� */
        amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                                   PIO0_1,
                                   AMHW_LPC82X_IOCON_MODE_INACTIVE);

        /* ʹ�� PIO0_1 ���ؾ���̶����Ź��� CLKIN */
        amhw_lpc82x_swm_fixed_func_enable(LPC82X_SWM,
                                          AMHW_LPC82X_SWM_PIO0_1_CLKIN);
        for (i = 0; i < 200; i++);
    }

    /* ���� PLL ʱ��Դ */
    amhw_lpc82x_clk_pll_src_set(__PLL_CLKSRC);

    /* PLLOUT ʱ�� */
    amhw_lpc82x_clk_pllctrl_set(__PLL_CFG_MSEL, __PLL_CFG_PSEL);
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_SYS_PLL);

    /* �ȴ� PLL ���� */
    while (!amhw_lpc82x_clk_pll_locked_chk());

    /* ������ʱ��Ϊ PLL ��� */
    amhw_lpc82x_clk_main_src_set(AMHW_LPC82X_CLK_MAIN_SRC_PLLOUT);

    /* ϵͳʱ�ӷ�ƵΪ 48 */
    amhw_lpc82x_clk_system_clkdiv_set(__CLKOUT_DIV);

    am_bsp_delay_timer_init(am_arm_systick_inst_init(), 0);

    /* ��Ϊʱ�Ӹı��ˣ��������³�ʼ������ */
    am_debug_init(am_lpc82x_usart0_inst_init(), 115200);

    AM_DBG_INFO("PLL configure Success!\r\n");
    AM_DBG_INFO("The Desired rate is %8d Hz\r\n", __PLL_DESIREDRATE);
    AM_DBG_INFO("The Actual Desired rate is %8d Hz\r\n",
                amhw_lpc82x_clk_pllout_rate_get());

    /*  ��������Ϊʱ����� */
    am_gpio_pin_cfg(PIO0_27, PIO_FUNC_CLKOUT);

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
/** [src_lpc824_hw_pll] */

/* end of file */
