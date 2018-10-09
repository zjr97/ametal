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
 * \brief KL26 CLK �û������ļ���
 * \sa am_kl26_hwconfig_clk.c
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-30  mkr, first implementation.
 * \endinternal
 */

#include "am_kl26_clk.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "am_bitops.h"
#include "hw/amhw_kl26_mcg.h"
#include "../../../../../soc/freescale/kl26/kl26_periph_map.h"
#include "../../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_clk
 * \copydoc am_kl26_hwconfig_clk.c
 * @{
 */

/**
 * \brief ʱ�ӹ���ģʽ,
 *
 *   �ɶ���ΪAM_KL26_CLK_MODE_FEI��AM_KL26_CLK_MODE_PEE
 *
 *  - FEI mode: ʹ���ڲ����� IRC(32.768KHz)��FLL�ο�ʱ�� ����FLL��Ƶ��(47.972352MHz)����ʱ�ӣ�
 *              Core clock = 47.972352MHz��
 *              Bus clock  = 23.986171MHz
 *
 *  - PEE mode: ʹ���ⲿʱ��XTAL��PLL�ο�ʱ�� ����PLL��Ƶ��(96MHz)����ʱ�ӣ�
 *              Core clock = 48MHz��
 *              Bus clock  = 24Hz
 *
 * \note �ı�ʱ��ģʽʱ����ı������豸��Ϣ��core_clk_div��Ա, ��ΪAM_KL26_CLK_MODE_FEI����ֵΪ1����ΪAM_KL26_CLK_MODE_PEE����ֵΪ2
 *
 */
#define __CLK_MODE    AM_KL26_CLK_MODE_FEI

/**
 * \brief CLK ƽ̨��ʼ��
 */
static void __kl26_clk_plfm_init (void)
{
    /** \brief  �����ⲿ����OSC���Ź��� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PORTA);

    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOA_18, PIOA_18_EXTAL0);
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOA_19, PIOA_19_XTAL0);
}

/**
 * \brief CLK ƽ̨ȥ��ʼ��
 */
static void __kl26_clk_plfm_deinit (void)
{
    /* ʱ����ȥ��ʼ������*/
    return;
}

/**
 * \brief CLK �豸��Ϣ
 */
static const am_kl26_clk_devinfo_t __g_clk_devinfo = {

    /* ʱ�ӹ���ģʽ */
    __CLK_MODE,

    /* AM_KL26_CLK_MODE_PEEģʽ���ⲿ����Ƶ�ʣ�����8-32MHz, 4�������� */
    (8 * 1000 * 1000),

    /* �ں�ʱ��core_clk��Ƶϵ��(1-16),
     * CORE_CLK = MCGOUTCLK / core_clk_div
     * Core clock upto 48MHz
     **************************************************
     * mode    core_clk_div   Core clock    Bus clock *
     * FEI        1          47.972352MHz 23.986171MHz*
     * PEE        2             48MHz        24MHz    *
     **************************************************
     */
    1,

    /* CLKƽ̨��ʼ�� */
	__kl26_clk_plfm_init,

	/*  CLK ƽ̨ȥ��ʼ�� */
	__kl26_clk_plfm_deinit,

};

/** \brief CLK�豸ʵ��   */
static am_kl26_clk_dev_t __g_clk_dev;

/**
 * \brief  CLK ʵ����ʼ������ʼ��ϵͳʱ��
 *
 * \retval AM_OK : ʱ�ӳɹ���ʼ��
 */
int am_kl26_clk_inst_init (void)
{
    return am_kl26_clk_init(&__g_clk_dev, &__g_clk_devinfo);
}

/**
 * @}
 */

/* end of file */
