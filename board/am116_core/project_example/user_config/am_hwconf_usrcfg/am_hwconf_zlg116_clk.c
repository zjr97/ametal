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
 * \brief ZLG116 ʱ���û������ļ�
 * \sa am_hwconf_zlg116_clk.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-13  sdy, first implementation.
 * \endinternal
 */
 
#include "am_zlg116_clk.h"
#include "hw/amhw_zlg116_rcc.h"
/**
 * \addtogroup am_if_src_hwconf_zlg116_clk
 * \copydoc am_hwconf_zlg116_clk.c
 * @{
 */
/** \brief CLK ƽ̨��ʼ�� */
static void __zlg116_clk_plfm_init (void)
{
}
/**
 * \brief CLK�豸��Ϣ
 */
static const am_zlg116_clk_devinfo_t __g_clk_devinfo =
{
    /**
     * \brief HSEOSC�ⲿ����Ƶ��
     *
     *  ���pllin_srcѡ�� AMHW_ZLG116_PLLCLK_HSE �� PLLIN = hse_osc��
     *  PLLIN = 12000000
     */
    12000000,
    /** \brief
     *    PLL ʱ��Դѡ��
     *    -# AMHW_ZLG116_PLLCLK_HSI_DIV4 : HSI ����  4 ��Ƶ��ΪPLL����ʱ��
     *    -# AMHW_ZLG116_PLLCLK_HSE      : HSE ��ΪPLL����ʱ��
     */
	AMHW_ZLG116_PLLCLK_HSE,
    /**
     * \brief PLL ��Ƶϵ������ѡ1-64
     *        PLLOUT = PLLIN * pll_mul / pll_div
     *        PLLOUT  = 12000000 * 4 / 1 = 48Mhz
     */
    4,
    /**
     * \brief PLL ��Ƶϵ������ѡ1-8
     *        PLLOUT = PLLIN * pll_mul / pll_div
     *        PLLOUT  = 12000000 * 4 / 1 = 48Mhz
     */
    1,
    /** \brief USB��Ƶϵ����USBCLK = PLLOUT / (usb_div + 1),�������ó�48Mhz */
    0,
    /**
     * \brief AHB��Ƶϵ����AHBCLK = PLLOUT / DIV,AHB���Ƶ��Ϊ48Mhz
     *
     *    ahb_div |  DIV
     *   ---------------------
     *        0-7 |   1
     *        8   |   2
     *        9   |   4
     *        10  |   8
     *        11  |   16
     *        12  |   64
     *        13  |  128
     *        14  |  256
     *        15  |  512
     */
    0,
    /**
     * \brief APB1��Ƶϵ����APB1CLK = AHBCLK / (2 ^ apb1_div)
     *        APB1���Ƶ��Ϊ24Mhz
     */
    1,
    /**
     * \brief APB2��Ƶϵ����APB2CLK = AHBCLK / (2 ^ apb2_div)
     *        APB2���Ƶ��Ϊ48Mhz
     */
    0,
    /* ƽ̨��ʼ������������ʱ�����ŵȲ��� */
    __zlg116_clk_plfm_init,
    /* CLK��ƽ̨ȥ��ʼ������ */
    NULL
};
/** \brief ʱ���豸ʵ�� */
static am_zlg116_clk_dev_t __g_clk_dev;
/**
 * \brief CLK ʵ����ʼ������ʼ��ϵͳʱ��
 * \retval AM_OK : ʱ�ӳɹ���ʼ��
 */
int am_zlg116_clk_inst_init (void)
{
    return am_zlg116_clk_init(&__g_clk_dev, &__g_clk_devinfo);
}
/**
 * @}
 */
/* end of file */
