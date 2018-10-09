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
 * \brief KL26 LPTMR ��ʱ�����û������ļ�
 * \sa am_kl26_hwconfig_lptmr_timing.c
 * 
 * \note LPTMֻ��һ����ʱͨ������׼�ӿڲ����ͨ���������塣
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_kl26.h"
#include "hw/amhw_kl26_sim.h"
#include "am_fsl_lptmr_timing.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_lptmr_timing
 * \copydoc am_kl26_hwconfig_lptmr_timing.c
 * @{
 */

/** \brief LPTMR ƽ̨��ʼ�� */
void __kl26_plfm_lptmr_timing_init (void)
{
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_LPTMR);
    
    /* �ر�LPTMRģ�� */
    amhw_fsl_lptmr_ctl_clear(KL26_LPTMR, AMHW_FSL_LPTMR_CSR_TEN);

    /* ʱ��Դѡ�� */
    amhw_fsl_lptmr_clock_set(KL26_LPTMR, AMHW_FSL_LPTMR_CLOCK_SRC_LPOCLK);
}

/** \brief ��� LPTMR ƽ̨��ʼ�� */
void __kl26_plfm_lptmr_timing_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_LPTMR);
}

/** \brief LPTMR �豸��Ϣ */
const am_fsl_lptmr_timing_devinfo_t  __g_lptmr_timing_devinfo = {
    KL26_LPTMR,                  /**< \brief ָ��LPTMR�Ĵ������ָ�� */
    INUM_LPTMR0,                      /**< \brief LPTMR0�жϱ�� */
    CLK_LPTMR,                        /**< \brief LPTMRʱ�Ӻ� */
    __kl26_plfm_lptmr_timing_init,
    __kl26_plfm_lptmr_timing_deinit
};

/** \brief LPTMR �豸����  */
am_fsl_lptmr_timing_dev_t  __g_lptmr_timing_dev;

/** \brief LPTMR Timer ʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_kl26_lptmr_timing_inst_init (void)
{
    return am_fsl_lptmr_timing_init(&__g_lptmr_timing_dev,
                                    &__g_lptmr_timing_devinfo);
}

/** \brief LPTMR Timer ʵ�����ʼ�� */
void am_kl26_lptmr_timing_inst_deinit (am_timer_handle_t handle)
{
    am_fsl_lptmr_timing_deinit(handle);
}

/**
 * @}
 */

/* end of file */
