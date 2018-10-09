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
 * \brief LPC82X SCT0 TIMING �û������ļ�
 * \sa am_hwconf_lpc82x_sct0_timing.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-09  hgo, modified
 * - 1.00 15-07-07  oce, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc_sct_timing.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_sct0_timing
 * \copydoc am_hwconf_lpc82x_sct0_timing.c
 * @{
 */

/**
 * \brief SCT0 TIMING ƽ̨��ʼ��
 */
am_local void __lpc82x_sct0_timing_plfm_init (void)
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SCT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);
}

/**
 * \brief SCT0 TIMING ƽ̨���ʼ��
 */
am_local void __lpc82x_sct0_timing_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SCT);
}

/** \brief SCT TIMING �豸��Ϣ */
am_local am_const am_lpc_sct_timing_devinfo_t __g_lpc82x_sct0_timing_devinfo = {
    LPC82X_SCT0_BASE,                    /* SCT0 �Ĵ��������ַ */
    INUM_SCT0,                           /* SCT0 �жϺ� */
    CLK_SCT,                             /* SCT0 ʱ�Ӻ� */
    AM_LPC_SCT_TIMING_2_16BIT,           /* SCT ���� 2 �� 16 λ��ʱ�� */
    __lpc82x_sct0_timing_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc82x_sct0_timing_plfm_deinit,    /* ƽ̨���ʼ������ */
};

/** \brief SCT TIMING �豸ʵ�� */
am_local am_lpc_sct_timing_dev_t __g_lpc82x_sct0_timing_dev;

/**
 * \brief SCT0 TIMING ʵ����ʼ��
 */
am_timer_handle_t am_lpc82x_sct0_timing_inst_init (void)
{
    return am_lpc_sct_timing_init(&__g_lpc82x_sct0_timing_dev,
                                   &__g_lpc82x_sct0_timing_devinfo);
}

/**
 * \brief SCT0 TIMING ʵ�����ʼ��
 */
void am_lpc82x_sct0_timing_inst_deinit (am_timer_handle_t handle)
{
    am_lpc_sct_timing_deinit((am_lpc_sct_timing_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
