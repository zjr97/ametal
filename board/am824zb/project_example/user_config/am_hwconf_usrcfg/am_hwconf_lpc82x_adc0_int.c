/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC82X ADC �û������ļ���
 * \sa am_hwconf_lpc82x_adc0_int.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-14  hgo, add calibrate func.
 * - 1.00 15-07-15  bob, first implementation.
 * \endinternal
 */

#include "am_lpc82x_adc_int.h"
#include "ametal.h"
#include "am_lpc82x.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_adc.h"
/**
 * \addtogroup am_if_src_hwconf_lpc82x_adc0_int
 * \copydoc am_hwconf_lpc82x_adc0_int.c
 * @{
 */

/** \brief ADC0 ƽ̨��ʼ������ */
static void __lpc82x_adc0_plfm_init (void)
{
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_ADC0);
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_ADC0);

    /* ����ͨ������������Ϊ����ģʽINACTIVE */
    am_gpio_pin_cfg(PIO0_7,  PIO0_7_ADC_0   | PIO0_7_INACTIVE);
/*    am_gpio_pin_cfg(PIO0_6,  PIO0_6_ADC_1   | PIO0_6_INACTIVE);  */

    am_gpio_pin_cfg(PIO0_14, PIO0_14_ADC_2  | PIO0_14_INACTIVE);
/*    am_gpio_pin_cfg(PIO0_23, PIO0_23_ADC_3  | PIO0_23_INACTIVE); */
/*    am_gpio_pin_cfg(PIO0_22, PIO0_22_ADC_4  | PIO0_22_INACTIVE); */
/*    am_gpio_pin_cfg(PIO0_21, PIO0_21_ADC_5  | PIO0_21_INACTIVE); */
/*    am_gpio_pin_cfg(PIO0_20, PIO0_20_ADC_6  | PIO0_20_INACTIVE); */
/*    am_gpio_pin_cfg(PIO0_19, PIO0_19_ADC_7  | PIO0_19_INACTIVE); */
/*    am_gpio_pin_cfg(PIO0_18, PIO0_18_ADC_8  | PIO0_18_INACTIVE); */
/*    am_gpio_pin_cfg(PIO0_17, PIO0_17_ADC_9  | PIO0_17_INACTIVE); */
/*    am_gpio_pin_cfg(PIO0_13, PIO0_13_ADC_10 | PIO0_13_INACTIVE); */
/*    am_gpio_pin_cfg(PIO0_4,  PIO0_4_ADC_11  | PIO0_4_INACTIVE);  */

    /* ADC�Զ����� */
    amhw_lpc82x_adc_calibrate(LPC82X_ADC0,
                              amhw_lpc82x_clk_system_clkrate_get());
}

/** \brief ADC0 ƽ̨���ʼ�� */
static void __lpc82x_adc0_plfm_deinit (void)
{
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_ADC0);
    amhw_lpc82x_syscon_powerdown(AMHW_LPC82X_SYSCON_PD_ADC0);
}

/** \brief ADC0 �豸��Ϣ */
static const am_lpc82x_adc_int_devinfo_t __g_adc0_devinfo = {
    LPC82X_ADC0_BASE,              /**< \brief ADC�Ĵ�����Ļ���ַ */
    CLK_ADC0,                      /**< \brief ADC0ʱ��ID */
    2500,                          /**< \brief ADC�ο���ѹ����λ��mV */
    INUM_ADC0_SEQA,                /**< \brief ADC0����A�ж� */
    INUM_ADC0_OVR,                 /**< \brief ADC0 overrun �ж� */
    __lpc82x_adc0_plfm_init,       /**< \brief ƽ̨��ʼ������ */
    __lpc82x_adc0_plfm_deinit,     /**< \brief ƽ̨���ʼ������  */
};

/** \brief ADC0�豸ʵ�� */
static am_lpc82x_adc_int_dev_t __g_adc0_dev;

/** \brief ADC0 ʵ����ʼ�������ADC��׼������ */
am_adc_handle_t am_lpc82x_adc0_int_inst_init (void)
{
    return am_lpc82x_adc_int_init(&__g_adc0_dev, &__g_adc0_devinfo);
}

/** \brief ADC0 ʵ�����ʼ�� */
void am_lpc82x_adc0_int_inst_deinit (am_adc_handle_t handle)
{
    am_lpc82x_adc_int_deinit(handle);
}

/**
 * @}
 */

/* end of file */
