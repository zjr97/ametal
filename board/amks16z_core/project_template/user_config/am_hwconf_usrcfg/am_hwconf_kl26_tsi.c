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
 * \brief KL26 TSI �û������ļ���
 * \sa am_kl26_hwconfig_tsi.c
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-26  nwt, make some changes.
 * - 1.00 15-10-22  wxj, first implementation.
 * \endinternal
 */

#include "am_kl26.h"
#include "am_fsl_tsi.h"
#include "hw/amhw_fsl_tsi.h"
#include "kl26_periph_map.h"
#include "hw/amhw_kl26_sim.h"
#include "am_gpio.h"


/**
 * \addtogroup am_kl26_if_hwconfig_src_tsi
 * \copydoc am_kl26_hwconfig_tsi.c
 * @{
 */

/** \brief tsiƽ̨��ʼ�� */
static void __plfm_tsi_init (void)
{
    /* ʹ��tsi�������ʱ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TSI);

    /* ����PIOA_1����ΪTSI0_CH2 */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_TSI0_CH2);
}

/** \brief tsiƽ̨ȥ��ʼ�� */
static void __plfm_tsi_deinit (void)
{
    /* ����tsi�������ʱ�� */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_TSI);
}

/** \brief tsi�豸��Ϣ     */
static const am_fsl_tsi_devinfo_t __g_tsi_devinfo = {
    KL26_TSI,       /**< \brief ָ��tsi�˿ڼĴ������ָ�� */
    AM_FALSE,               /**< \brief �����õ͹����жϻ���MCU���� */
	INUM_TSI0,
    __plfm_tsi_init,     /**< \brief TSIƽ̨��ʼ��.  */
    __plfm_tsi_deinit    /**< \brief TSIƽ̨ȥ��ʼ��.  */
};

/** \brief tsi�豸ʵ��   */
static am_fsl_tsi_dev_t __g_tsi_dev;

/**
 * \brief TSIʵ����ʼ��
 */
int am_kl26_tsi_inst_init (void)
{
    return am_fsl_tsi_init(&__g_tsi_dev, &__g_tsi_devinfo);
}

/**
 * \brief TSIʵ�����ʼ��
 */
void am_kl26_tsi_inst_deinit (void)
{
    am_fsl_tsi_deinit(&__g_tsi_dev);
}


/**
 * @}
 */

/* end of file */
