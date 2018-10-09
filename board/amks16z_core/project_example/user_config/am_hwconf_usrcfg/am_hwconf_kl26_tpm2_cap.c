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
 * \brief KL26 ���ڲ����ܵ��û������ļ�
 * \sa am_kl26_hwconfig_tpm2_cap.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_fsl_tpm_cap.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_sim.h"
#include "../../../../../soc/freescale/kl26/am_kl26.h"


/**
 * \addtogroup am_kl26_if_hwconfig_src_tpm2_cap
 * \copydoc am_kl26_hwconfig_tpm2_cap.c
 * @{
 */
 
/** \brief TPM2���ڲ����ܵ�ƽ̨��ʼ�� */
void __kl26_plfm_tpm2_cap_init (void)
{
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TPM2);
    amhw_kl26_sim_tpm_src_set(KL26_SIM_TPMSRC_PLLFLLCLK);
}

/** \brief  ���TPM2ƽ̨��ʼ�� */
void __kl26_plfm_tpm2_cap_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_TPM2);
}

/** \brief TPM2���ڲ����ܵ�����������Ϣ�б� */
am_fsl_tpm_cap_ioinfo_t __g_tpm2_cap_ioinfo_list[] = {
    {PIOE_22, PIOE_22_TPM2_CH0, PIOE_22_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��0 */
    {PIOE_23, PIOE_23_TPM2_CH1, PIOE_23_GPIO | AM_GPIO_INPUT},  /**< \brief ͨ��1 */
};

/** \brief TPM2���ڲ����ܵ��豸��Ϣ */
const am_fsl_tpm_cap_devinfo_t  __g_tpm2_cap_devinfo = {
    KL26_TPM2,                      /**< \brief ָ��TPM2�Ĵ������ָ�� */
    INUM_TPM2,                      /**< \brief TPM2�жϱ�� */
    2,                              /**< \brief 2������ͨ��  */
    CLK_TPM2,                       /**< \brief ʱ�Ӻ� */
    &__g_tpm2_cap_ioinfo_list[0],
    __kl26_plfm_tpm2_cap_init,      /**< \brief ƽ̨��ʼ������ */
    __kl26_plfm_tpm2_cap_deinit     /**< \brief ƽ̨���ʼ������ */

};

/** \brief TPM2���ڲ����ܵ��豸���� */
am_fsl_tpm_cap_dev_t  __g_tpm2_cap_dev;

/** \brief tpm2 cap ʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_kl26_tpm2_cap_inst_init (void)
{
    return am_fsl_tpm_cap_init(&__g_tpm2_cap_dev,
                               &__g_tpm2_cap_devinfo);
}

/** \brief tpm2 cap ʵ�����ʼ�� */
void am_kl26_tpm2_cap_inst_deinit (am_cap_handle_t handle)
{
    am_fsl_tpm_cap_deinit(handle);
}

/**
 * @}
 */

/* end of file */
