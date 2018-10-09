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
 * \brief KL26 GPIO �û������ļ���
 * \sa am_kl26_hwconfig_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-15  nwt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup am_kl26_if_hwconfig_src_gpio
 * \copydoc am_kl26_hwconfig_gpio.c
 * @{
 */

#include "am_gpio.h"
#include "am_kl26_gpio.h"
#include "hw/amhw_kl26_gpio.h"
#include "hw/amhw_kl26_sim.h"
#include "../../../../../soc/freescale/kl26/kl26_periph_map.h"
#include "../../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief ʹ�õ��ж�ͨ������
 *
 *        Ĭ��ʹ�����е��ж�ͨ�����û����Ը���ʵ��ʹ��ͨ������
 *        ���Ĵ�ֵ�������ڴ��ռ��
 *
 * \note �����ֵΪ0�����޷�ʹ��GPIO�жϹ��ܣ����ǿ���ʹ������GPIO����
 */
#define __GPIO_PINT_USE_COUNT   PIN_INT_MAX


/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct am_kl26_gpio_trigger_info g_gpio_triginfos[__GPIO_PINT_USE_COUNT];

/** \brief ���Ŵ�����Ϣӳ�� */
static uint8_t g_gpio_infomap[__GPIO_PINT_USE_COUNT];

/** \brief GPIOƽ̨��ʼ�� */
static void __kl26_plfm_gpio_init (void)
{
    /* ʹ��GPIO�������ʱ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PORTA);
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PORTB);
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PORTC);
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PORTD);
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PORTE);
}

/** \brief GPIOƽ̨ȥ��ʼ�� */
static void __kl26_plfm_gpio_deinit (void)
{
    /* ����GPIO�������ʱ�� */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_PORTA);
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_PORTB);
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_PORTC);
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_PORTD);
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_PORTE);
}

/** \brief GPIO�豸��Ϣ     */
static const am_kl26_gpio_devinfo_t __g_gpio_devinfo = {
    KL26_PORT,               /**< \brief ָ��GPIO�˿ڼĴ������ָ��.*/
    KL26_GPIO,               /**< \brief ָ��GPIO�Ĵ������ָ��.    */
    {
        INUM_PORTA,          /**< \brief �˿�A�ж�.                */
        INUM_PORTC_PORTD,    /**< \brief �˿�C��˿�D�ж�.          */
    },
    __GPIO_PINT_USE_COUNT,   /**< \brief GPIO֧�ֵ������жϺ�����.  */
    g_gpio_infomap,          /**< \brief ���Ŵ�����Ϣӳ��.          */
    g_gpio_triginfos,        /**< \brief ���Ŵ�����Ϣ�ڴ�.          */

    __kl26_plfm_gpio_init,   /**< \brief GPIOƽ̨��ʼ��.            */
    __kl26_plfm_gpio_deinit  /**< \brief GPIOƽ̨ȥ��ʼ��.          */
};

/** \brief GPIO�豸ʵ��   */
am_kl26_gpio_dev_t __g_gpio_dev;

/** \brief GPIO ʵ����ʼ�� */
int am_kl26_gpio_inst_init (void)
{
    return am_kl26_gpio_init(&__g_gpio_dev, &__g_gpio_devinfo);
}

/** \brief GPIO ʵ�����ʼ�� */
void am_kl26_gpio_inst_deinit (void)
{
    am_kl26_gpio_deinit();
}


/**
 * @}
 */

/* end of file */
