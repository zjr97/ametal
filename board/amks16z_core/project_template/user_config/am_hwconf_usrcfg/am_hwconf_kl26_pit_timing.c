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
 * \brief KL26 PIT ��ʱ�����û������ļ�
 * \sa am_kl26_hwconfig_pit_timing.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-18  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_kl26.h"
#include "hw/amhw_kl26_sim.h"
#include "am_fsl_pit_timing.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_pit_timing
 * \copydoc am_kl26_hwconfig_pit_timing.c
 * @{
 */

/** \brief PIT ƽ̨��ʼ�� */
void __kl26_plfm_pit_timing_init (void)
{
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PIT);
}

/** \brief ��� PIT ƽ̨��ʼ�� */
void __kl26_plfm_pit_timing_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_PIT);
}

/** \brief PIT �豸��Ϣ */
const am_fsl_pit_timing_devinfo_t  __g_pit_timing_devinfo = {
    KL26_PIT ,                 /**< \brief ָ��PIT�Ĵ������ָ��  */
    AM_FSL_PIT_TIMING_2_32BIT,      /**< \brief ����Ϊ2ͨ����32λ��ʱ�� */
    INUM_PIT,                       /**< \brief PIT�жϱ�� */
    CLK_PIT,                        /**< \brief PITʱ�Ӻ� */
    __kl26_plfm_pit_timing_init,    /**< \brief ƽ̨��ʼ������ */
    __kl26_plfm_pit_timing_deinit   /**< \brief ƽ̨���ʼ������ */
};

/** \brief PIT �豸����  */
am_fsl_pit_timing_dev_t  __g_pit_timing_dev;

/** \brief pit Timer ʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_kl26_pit_timing_inst_init (void)
{
    return am_fsl_pit_timing_init(&__g_pit_timing_dev,
                                  &__g_pit_timing_devinfo);
}

/** \brief pit Timer ʵ�����ʼ�� */
void am_kl26_pit_timing_inst_deinit (am_timer_handle_t handle)
{
    am_fsl_pit_timing_deinit(handle);
}

/**
 * @}
 */

/* end of file */
