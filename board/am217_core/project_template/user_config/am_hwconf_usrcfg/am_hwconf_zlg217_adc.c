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
 * \brief ZLG217 ADC �û������ļ�
 * \sa am_hwconf_zlg217_adc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "zlg217_periph_map.h"
#include "am_zlg217.h"
#include "zlg217_inum.h"
#include "am_gpio.h"
#include "am_zlg_adc.h"
#include "amhw_zlg_adc.h"
#include "amhw_zlg217_rcc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_adc
 * \copydoc am_hwconf_zlg217_adc.c
 * @{
 */

/** \brief ADCƽ̨��ʼ�� */
static void __zlg_plfm_adc1_init (void)
{
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AIN);
    am_clk_enable(CLK_ADC1);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __zlg_plfm_adc1_deinit (void)
{
    am_gpio_pin_cfg(PIOA_4, PIOA_4_INPUT_FLOAT);
    am_clk_disable (CLK_ADC1);
}

/** \brief �豸��Ϣ */
static const am_zlg_adc_devinfo_t __g_adc1_devinfo = {

    ZLG217_ADC1_BASE,                 /**< \brief ADC */
    INUM_ADC1_2,                      /**< \brief ADC���жϱ�� */
    CLK_ADC1,                         /**< \brief ADCʱ�Ӻ� */

    3300,                             /**< \brief �ο���ѹ */
    AMHW_ZLG_ADC_DATA_VALID_12BIT, /**< \brief ת������ */

    __zlg_plfm_adc1_init,             /**< \brief ADC1��ƽ̨��ʼ�� */
    __zlg_plfm_adc1_deinit,           /**< \brief ADC1��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
static am_zlg_adc_dev_t  __g_adc1_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_zlg217_adc1_inst_init (void)
{
    return am_zlg_adc_init(&__g_adc1_dev, &__g_adc1_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_zlg217_adc1_inst_deinit (am_adc_handle_t handle)
{
    am_zlg_adc_deinit(handle);
}

/** \brief ADC2ƽ̨��ʼ�� */
static void __zlg_plfm_adc2_init (void)
{
    am_gpio_pin_cfg(PIOB_0, PIOB_0_AIN);
    am_clk_enable(CLK_ADC2);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __zlg_plfm_adc2_deinit (void)
{
    am_gpio_pin_cfg(PIOB_0, PIOB_0_INPUT_FLOAT);
    am_clk_disable (CLK_ADC2);
}

/** \brief ADC�豸��Ϣ */
static const am_zlg_adc_devinfo_t __g_adc2_devinfo = {

    ZLG217_ADC2_BASE,                 /**< \brief ADC */
    INUM_ADC1_2,                      /**< \brief ADC���жϱ�� */
    CLK_ADC2,                         /**< \brief ADCʱ�Ӻ� */

    3300,                             /**< \brief �ο���ѹ */
    AMHW_ZLG_ADC_DATA_VALID_12BIT, /**< \brief ת������ */

    __zlg_plfm_adc2_init,             /**< \brief ADC2��ƽ̨��ʼ�� */
    __zlg_plfm_adc2_deinit,           /**< \brief ADC2��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
static am_zlg_adc_dev_t  __g_adc2_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_zlg217_adc2_inst_init (void)
{
    return am_zlg_adc_init(&__g_adc2_dev, &__g_adc2_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_zlg217_adc2_inst_deinit (am_adc_handle_t handle)
{
    am_zlg_adc_deinit(handle);
}

/**
 * @}
 */

/* end of file */
