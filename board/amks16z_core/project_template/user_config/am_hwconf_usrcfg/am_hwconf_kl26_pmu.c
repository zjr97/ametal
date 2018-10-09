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
 * \brief KL16 PMU �û������ļ�
 * \sa am_kl26_hwconfig_pmu.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-10-30  liqing, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "kl26_periph_map.h"
#include "hw/amhw_arm_nvic.h"
#include "am_kl26_pmu.h"
#include "kl26_inum.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_pmu
 * \copydoc am_kl26_hwconfig_pmu.c
 * @{
 */

/** \brief PMU ƽ̨��ʼ�� */
void __kl26_plfm_pmu_init (void)
{

}

/** \brief ���PMU ƽ̨��ʼ�� */
void __kl26_plfm_pmu_deinit (void)
{
	amhw_arm_nvic_disable(INUM_LLWU);
}
/**
 * \brief PMU �豸��Ϣ
 */
const  struct am_kl26_pmu_devinfo  __g_pmu_devinfo = {
    KL26_SMC,                                /**< \brief SMC�Ĵ���ָ��       */
    KL26_PMC,                                /**< \brief PMC�Ĵ���ָ��       */
    KL26_RCM,                                /**< \brief RCM�Ĵ���ָ��       */
    KL26_LLWU,                               /**< \brief LLWU�Ĵ���ָ��      */
    AM_KL26_PMU_ARG_VLLS0_POR_DISABLE |      /**< \brief VLLS0���ܵ�Դ���   */
    AM_KL26_PMU_ARG_VLLSx_ISOACK_CLEAR,      /**< \brief �Զ��������ACK��־ */
    __kl26_plfm_pmu_init,                    /**< \brief PMUƽ̨��ʼ�� */
    __kl26_plfm_pmu_deinit                   /**< \brief PMUƽ̨ȥ��ʼ�� */
};

/** \brief PMU �豸ʵ�� */
am_kl26_pmu_dev_t __g_pmu_dev;

/**
 * \brief  PMU ʵ����ʼ������ʼ��ϵͳʱ��
 * \retval AM_OK : �ɹ���ʼ��
 */
int am_kl26_pmu_inst_init (void)
{
    return am_kl26_pmu_init(&__g_pmu_dev, &__g_pmu_devinfo);
}

/** \brief PMUʵ�����ʼ�� */
void am_kl26_pmu_inst_deinit (void)
{
    am_kl26_pmu_deinit(&__g_pmu_dev);
}

/**
 * @}
 */

/* end of file */
