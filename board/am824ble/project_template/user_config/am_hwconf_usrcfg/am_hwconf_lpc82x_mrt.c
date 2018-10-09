/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC82X MRT �û������ļ�
 * \sa am_hwconf_lpc82x_mrt.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-08  mem,modified
 * - 1.00 15-07-15  win, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc_mrt.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_mrt
 * \copydoc am_hwconf_lpc82x_mrt.c
 * @{
 */

/**
 * \brief MRT ƽ̨��ʼ��
 */
am_local void __lpc82x_mrt_plfm_init (void)
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_MRT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_MRT);
}

/**
 * \brief MRT ƽ̨���ʼ��
 */
am_local void __lpc82x_mrt_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_MRT);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_MRT);
}

/** \brief MRT �豸��Ϣ */
am_local am_const am_lpc_mrt_devinfo_t __g_lpc82x_mrt_devinfo = {
    LPC82X_MRT_BASE,             /* MRT �Ĵ������ַ */
    INUM_MRT,                    /* MRT �жϺ� */
    CLK_MRT,                     /* MRT ʱ�Ӻ� */
    4,                           /* ʹ�õ�ͨ���� */
    __lpc82x_mrt_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc82x_mrt_plfm_deinit,    /* ƽ̨���ʼ������ */
};

/** \brief MRT �豸ʵ�� */
am_local am_lpc_mrt_dev_t __g_lpc82x_mrt_dev;

/**
 * \brief MRT ʵ����ʼ��
 */
am_timer_handle_t am_lpc82x_mrt_inst_init (void)
{
    return am_lpc_mrt_init(&__g_lpc82x_mrt_dev, &__g_lpc82x_mrt_devinfo);
}

/**
 * \brief MRT ʵ�����ʼ��
 */
void am_lpc82x_mrt_inst_deinit (am_timer_handle_t handle)
{
    am_lpc_mrt_deinit((am_lpc_mrt_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
