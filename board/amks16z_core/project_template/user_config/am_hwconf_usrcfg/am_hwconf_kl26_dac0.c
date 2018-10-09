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
 * \brief KL26 DAC �û������ļ���
 * \sa am_kl26_hwconfig_dac.c
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-26  mkr, first implementation.
 * \endinternal
 */

#include "am_kl26.h"
#include "hw/amhw_kl26_sim.h"
#include "am_fsl_dac.h"
#include "am_gpio.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_dac
 * \copydoc am_kl26_hwconfig_dac.c
 * @{
 */

/**
 * \brief DAC ƽ̨��ʼ����
 */
void __kl26_plfm_dac0_init (void)
{
    /* ����PIOE_30ΪDAC0_OUT����                 */
     am_gpio_pin_cfg (PIOE_30,PIOE_30_DAC0_OUT);

     /* ����DACʱ��                  */
     amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_DAC0);
}

/**
 * \brief DAC ƽ̨ȥ��ʼ����
 */
void __kl26_plfm_dac0_deinit (void)
{
   /* �ر�DACʱ��                  */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_DAC0);
}

/** \brief DAC �豸��Ϣ */
static const am_fsl_dac_devinfo_t _g_dac0_devinfo =
{
    KL26_DAC0,                /**< \brief ָ��DAC0�Ĵ������ָ�� */
    INUM_DAC0,                     /**< \brief DAC0�жϺ�             */
    12,                            /**< \brief DACת������            */
    3270,                          /**< \brief DAC�ο���ѹ����λ��mV  */
    AMHW_FSL_DAC_VREF_2,          /**< \brief DAC��ѹԴ              */
    __kl26_plfm_dac0_init,
    __kl26_plfm_dac0_deinit,
};

/** \brief DAC0�豸ʵ�� */
static am_fsl_dac_dev_t _g_dac0_dev;

/** \brief DAC0 ʵ����ʼ�������DAC��׼������ */
am_dac_handle_t am_kl26_dac0_inst_init (void)
{
    return am_fsl_dac_init(&_g_dac0_dev, &_g_dac0_devinfo);
}

/** \brief DAC0 ʵ�����ʼ�� */
void am_kl26_dac0_inst_deinit (am_dac_handle_t handle)
{
    am_fsl_dac_deinit(handle);
}


/**
 * @}
 */

/* end of file */
