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
 * \brief KL26 TPM0 ��ʱ�����û������ļ�
 * \sa am_kl26_hwconfig_tpm0_timing.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-14  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_kl26.h"
#include "hw/amhw_kl26_sim.h"
#include "am_fsl_tpm_timing.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_tpm0_timing
 * \copydoc am_kl26_hwconfig_tpm0_timing.c
 * @{
 */

/** \brief TPM0 ƽ̨��ʼ�� */
void __kl26_plfm_tpm0_timing_init (void)
{
    amhw_kl26_sim_tpm_src_set(KL26_SIM_TPMSRC_PLLFLLCLK);
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TPM0);
}

/** \brief ��� TPM0 ƽ̨��ʼ�� */
void __kl26_plfm_tpm0_timing_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_TPM0);
}

/** \brief TPM0 �豸��Ϣ */
const am_fsl_tpm_timing_devinfo_t  __g_tpm0_timing_devinfo = {
    KL26_TPM0,                  /**< \brief ָ��TPM�Ĵ������ָ�� */
    INUM_TPM0,                       /**< \brief TPM0�жϱ�� */
    CLK_TPM0,                        /**< \brief ʱ�Ӻ� */
    __kl26_plfm_tpm0_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __kl26_plfm_tpm0_timing_deinit   /**< \brief ƽ̨���ʼ������ */
};

/** \brief TPM0 �豸����  */
am_fsl_tpm_timing_dev_t  __g_tpm0_timing_dev;

/** \brief tpm2 Timer ʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_kl26_tpm0_timing_inst_init (void)
{
    return am_fsl_tpm_timing_init(&__g_tpm0_timing_dev,
                                  &__g_tpm0_timing_devinfo);
}

/** \brief tpm2 Timer ʵ�����ʼ�� */
void am_kl26_tpm0_timing_inst_deinit (am_timer_handle_t handle)
{
    am_fsl_tpm_timing_deinit(handle);
}

/**
 * @}
 */

/* end of file */
