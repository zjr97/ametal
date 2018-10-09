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
 * \brief LPC82X ʱ���û������ļ�
 * \sa am_hwconf_lpc82x_clk.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  lnk, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc82x_clk.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_swm.h"
#include "hw/amhw_lpc82x_iocon.h"
#include "hw/amhw_lpc82x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_clk
 * \copydoc am_hwconf_lpc82x_clk.c
 * @{
 */

/**
 * \brief PLL ʱ��Դ
 *
 * - �ڲ� IRC��12MHz��: AMHW_LPC82X_CLK_PLLIN_SRC_IRC
 * - �ⲿ����12MHz��: AMHW_LPC82X_CLK_PLLIN_SRC_SYSOSC
 * - �ⲿ��������ʱ��: AMHW_LPC82X_CLK_PLLIN_SRC_CLKIN
 *
 * \note Ĭ��ʹ���ڲ� IRC����Ҫʹ���ⲿ������Ҫ�ڿ������Ϻ��� 12MHz ����
 *       ���޸ĺ�ֵΪ AMHW_LPC82X_CLK_PLLIN_SRC_SYSOSC����ʹ���ⲿ����ʱ�����룬
 *       �� 12MHz ʱ�Ӵ� PIO0_1 ��������
 */
#define __LPC82X_CLK_PLL_SRC    AMHW_LPC82X_CLK_PLLIN_SRC_IRC

/**
 * \brief CLK ƽ̨��ʼ��
 */
am_local void __lpc82x_clk_plfm_init (void)
{
    if(__LPC82X_CLK_PLL_SRC == AMHW_LPC82X_CLK_PLLIN_SRC_SYSOSC) {

        /*
         * �ⲿ�����ϵͳ������Ϊʱ��Դ
         */

        /* �� PIO0_8,��PIO0_9 ����Ϊ����ģʽ���������������� */
        amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_IOCON);

        amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                                   PIO0_8,
                                   AMHW_LPC82X_IOCON_MODE_INACTIVE);

        amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,
                                   PIO0_9,
                                   AMHW_LPC82X_IOCON_MODE_INACTIVE);

        /* ʹ�� PIO0_8_XTALIN��PIO0_9_XTALOUT ���ؾ���̶����Ź��� */

        amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SWM);

        amhw_lpc82x_swm_fixed_func_enable(LPC82X_SWM,
                                          AMHW_LPC82X_SWM_PIO0_8_XTALIN);

        amhw_lpc82x_swm_fixed_func_enable(LPC82X_SWM,
                                          AMHW_LPC82X_SWM_PIO0_9_XTALOUT);

    } else if (__LPC82X_CLK_PLL_SRC == AMHW_LPC82X_CLK_PLLIN_SRC_CLKIN) {

        /*
         * �ⲿ�ܽ�������Ϊʱ��Դ
         */

        /* �� PIO0_1 ����Ϊ����ģʽ���������������� */

        amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_IOCON);

        amhw_lpc82x_iocon_mode_set(LPC82X_IOCON,PIO0_1,
                                   AMHW_LPC82X_IOCON_MODE_INACTIVE);

        /* ʹ�� PIO0_1 ���ؾ���̶����Ź��� CLKIN */

        amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SWM);

        amhw_lpc82x_swm_fixed_func_enable(LPC82X_SWM,
                                          AMHW_LPC82X_SWM_PIO0_1_CLKIN);
    } else {

        /*
         * ʹ���ڲ�IRC ��ʱ��Դ
         */
    }
}

/**
 * \brief CLK �豸��Ϣ
 *
 * Ĭ��ʹ���ڲ� IRC��12MHz), ���� PLL ��Ƶ���������ʱ�ӣ���ʱ��
 * main_rate = 60 MHz, ϵͳʱ�� system_clk = 30MHz
 *
 * \note ����ͨ���޸� __g_lpc82x_clk_devinfo ������ʱ��Դ��Ƶ�ʣ���ʱ��ʹ�� PLL
 *       ���ʱ���޸� MSEL��PSEL ʵ�֣���ϵͳʱ������ʱ�ӷ�Ƶ��õ���Ĭ�� 2 ��Ƶ
 */
am_local am_const am_lpc82x_clk_devinfo_t __g_lpc82x_clk_devinfo = {

    /*
     * PLL ʱ��Դ
     * �ڲ� IRC��12MHz��: AMHW_LPC82X_CLK_PLLIN_SRC_IRC
     * ϵͳ������12MHz��: AMHW_LPC82X_CLK_PLLIN_SRC_SYSOSC
     * �ⲿ��������ʱ��: AMHW_LPC82X_CLK_PLLIN_SRC_CLKIN
     */
    __LPC82X_CLK_PLL_SRC,

    /*
     * PLL ���ƼĴ��� MSEL��ʹ FCLKOUT �ڷ�Χ 100MHz ��
     * FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 5 = 60 MHz
     */
    4,

    /*
     * PLL ���ƼĴ��� PSEL��ʹ FCCO �ڷ�Χ 156MHz - 320MHz
     * FCCO = FCLKOUT * 2 * 2^(PSEL) = 60MHz * 2 * 2 = 240MHz
     */
    1,

    /*
     * ��ʱ��Դѡ�� main_clk = FCLKOUT = 60MHz
     * - �ڲ� IRC: AMHW_LPC82X_CLK_MAIN_SRC_IRC
     * - PLL ����: AMHW_LPC82X_CLK_MAIN_SRC_PLLIN
     * - ���Ź�����: AMHW_LPC82X_CLK_MAIN_SRC_WDTOSC
     * - PLL ���: AMHW_LPC82X_CLK_MAIN_SRC_PLLOUT
     */
    AMHW_LPC82X_CLK_MAIN_SRC_PLLOUT,

    /*
     * ϵͳʱ�ӷ�Ƶ�������� 1- 255 ֮�����ֵ
     * system_clk = main_clk / div = 60MHz / 2 = 30 MHz
     */
    2,

    /*
     * WDTOSC Ƶ�ʷ�Ƶϵ�������� 2 - 64 ֮���ż��
     * ����ʱ��Դѡ���Ź�����ʱ����Ҫ���� WDTOSC Ƶ�ʷ�Ƶϵ����Ƶ��ѡ��
     * ����ΪĬ��ֵ 0.6MHz��64 ��Ƶ��ʱ��Ƶ�� 9.375KHz
     */
    64,

    /*
     * WDTOSC Ƶ��ѡ��
     * wdtosc_freq = 600000UL Hz
     */
    AMHW_LPC82X_CLK_WDTOSC_RATE_0_6MHZ,

    /* ƽ̨��ʼ������ */
    __lpc82x_clk_plfm_init,

    /* ��ƽ̨���ʼ������ */
    NULL
};

/** \brief CLK �豸ʵ�� */
am_local am_lpc82x_clk_dev_t __g_lpc82x_clk_dev;

/**
 * \brief CLK ʵ����ʼ��
 */
int am_lpc82x_clk_inst_init (void)
{
    return am_lpc82x_clk_init(&__g_lpc82x_clk_dev, &__g_lpc82x_clk_devinfo);
}

/**
 * @}
 */

/* end of file */
