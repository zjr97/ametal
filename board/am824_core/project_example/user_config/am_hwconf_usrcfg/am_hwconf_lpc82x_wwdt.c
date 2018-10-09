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
 * \brief LPC82X WWDT �û������ļ�
 * \sa am_hwconf_lpc82x_wwdt.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-07  sss, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc_wwdt.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_wwdt
 * \copydoc am_hwconf_lpc82x_wwdt.c
 * @{
 */

/**
 * \brief WWDT ƽ̨��ʼ��
 */
am_local void __lpc82x_wwdt_plfm_init (void)
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_WWDT);

    /* ���� WDT ʱ�ӣ�0.6MHz��64 ��Ƶ��ʱ��Ƶ�� 9.375KHz */
    amhw_lpc82x_clk_wdtoscc_cfg(AMHW_LPC82X_CLK_WDTOSC_RATE_0_6MHZ, 64);

    /* ʹ�� WDTOSC */
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_WDT_OSC);
}

/**
 * \brief WWDT ƽ̨���ʼ��
 */
am_local void __lpc82x_wwdt_plfm_deinit (void)
{
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_WWDT);
}

/** \brief WWDT �豸��Ϣ */
am_local am_const am_lpc_wwdt_devinfo_t __g_lpc82x_wwdt_devinfo = {
    LPC82X_WWDT_BASE,          /* WWDT �Ĵ�����ַ */
    CLK_WWDT,                  /* WWDT ʱ�Ӻ� */
    __lpc82x_wwdt_plfm_init,   /* ƽ̨��ʼ������ */
    __lpc82x_wwdt_plfm_deinit, /* ƽ̨���ʼ������ */
};

/** \brief WWDT �豸ʵ�� */
am_local am_lpc_wwdt_dev_t __g_lpc82x_wwdt_dev;

/**
 * \brief WWDT ʵ����ʼ��
 */
am_wdt_handle_t am_lpc82x_wwdt_inst_init (void)
{
    return am_lpc_wwdt_init(&__g_lpc82x_wwdt_dev, &__g_lpc82x_wwdt_devinfo);
}

/**
 * \brief WWDT ʵ�����ʼ��
 */
void am_lpc82x_wwdt_inst_deinit (am_wdt_handle_t handle)
{
    am_lpc_wwdt_deinit((am_lpc_wwdt_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
