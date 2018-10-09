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
 * \brief LPC82X GPIO �û������ļ�
 * \sa am_hwconf_lpc82x_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-08  mem,modified.
 * - 1.00 15-07-8  zxl, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc82x_gpio.h"
#include "lpc82x_regbase.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"
/**
 * \addtogroup am_if_src_hwconf_lpc82x_gpio
 * \copydoc am_hwconf_lpc82x_gpio.c
 * @{
 */

 /** \brief GPIOƽ̨��ʼ�� */
static void __lpc82x_gpio_plfm_init (void)
{
    /* ��λGPIO������� */
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_GPIO);

    /* ʹ��GPIO�������ʱ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_GPIO);
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_IOCON);
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SWM);
}

/** \brief GPIOƽ̨���ʼ�� */
static void __lpc82x_gpio_plfm_deinit (void)
{
    /* ��λGPIO������� */
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_GPIO);

    /* ����GPIO�������ʱ�� */
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_GPIO);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_IOCON);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SWM);
}

/**
 * \brief ʹ�õ��ж�ͨ������
 *
 *        Ĭ��ʹ�����е��ж�ͨ�����û����Ը���ʵ��ʹ��ͨ������
 *        ���Ĵ�ֵ�������ڴ��ռ��
 *
 * \note �����ֵΪ0�����޷�ʹ��GPIO�жϹ��ܣ����ǿ���ʹ������GPIO����
 */
#define __GPIO_PINT_USE_COUNT   AMHW_LPC82X_PINT_CHAN_NUM

/** \brief ���Ŵ�����Ϣ�ڴ� */
static
struct am_lpc82x_gpio_trigger_info __g_gpio_triginfos[__GPIO_PINT_USE_COUNT];

/** \brief ���Ŵ�����Ϣӳ�� */
static uint8_t                     __g_gpio_infomap[__GPIO_PINT_USE_COUNT];

/** \brief GPIO�豸��Ϣ */
static const am_lpc82x_gpio_devinfo_t __g_gpio_devinfo = {

    LPC82X_SWM_BASE,           /**< \brief SWM�Ĵ������ַ          */
    LPC82X_GPIO_BASE,          /**< \brief GPIO�Ĵ������ַ         */
    LPC82X_IOCON_BASE,         /**< \brief IOCON�Ĵ������ַ        */
    LPC82X_PINT_BASE,          /**< \brief PINT�Ĵ������ַ         */
    {
        INUM_PIN_INT0,         /**< \brief PINT0�жϺ�              */
        INUM_PIN_INT1,         /**< \brief PINT1�жϺ�              */
        INUM_PIN_INT2,         /**< \brief PINT2�жϺ�              */
        INUM_PIN_INT3,         /**< \brief PINT3�жϺ�              */
        INUM_PIN_INT4,         /**< \brief PINT4�жϺ�              */
        INUM_PIN_INT5,         /**< \brief PINT5�жϺ�              */
        INUM_PIN_INT6,         /**< \brief PINT6�жϺ�              */
        INUM_PIN_INT7,         /**< \brief PINT7�жϺ�              */
    },
    __GPIO_PINT_USE_COUNT,     /**< \brief GPIO֧�ֵ������жϺ����� */
    &__g_gpio_infomap[0],      /**< \brief ���Ŵ�����Ϣӳ��         */
    &__g_gpio_triginfos[0],    /**< \brief ���Ŵ�����Ϣ�ڴ�         */

    __lpc82x_gpio_plfm_init,   /**< \brief ƽ̨��ʼ������           */
    __lpc82x_gpio_plfm_deinit  /**< \brief ƽ̨���ʼ������         */
};

/** \brief GPIO�豸ʵ�� */
static am_lpc82x_gpio_dev_t __g_gpio_dev;

/** \brief GPIO ʵ����ʼ�� */
int am_lpc82x_gpio_inst_init (void)
{
    return am_lpc82x_gpio_init(&__g_gpio_dev, &__g_gpio_devinfo);
}

/** \brief GPIO ʵ�����ʼ�� */
void am_lpc82x_gpio_inst_deinit (void)
{
    am_lpc82x_gpio_deinit();
}


/**
 * @}
 */

/* end of file */
