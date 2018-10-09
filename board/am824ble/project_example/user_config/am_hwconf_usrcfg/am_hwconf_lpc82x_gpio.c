/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
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
 * - 1.01 15-12-08  mem,modified
 * - 1.00 15-07-08  zxl, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc82x_gpio.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_gpio
 * \copydoc am_hwconf_lpc82x_gpio.c
 * @{
 */

/**
 * \brief GPIO ƽ̨��ʼ��
 */
am_local void __lpc82x_gpio_plfm_init (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_GPIO);

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_GPIO);
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_IOCON);
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SWM);
}

/**
 * \brief GPIO ƽ̨���ʼ��
 */
am_local void __lpc82x_gpio_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_GPIO);

    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_GPIO);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_IOCON);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SWM);
}

/**
 * \brief ʹ�õ��ж�ͨ������
 *
 * Ĭ��ʹ�����е��ж�ͨ�����û����Ը���ʵ��ʹ��ͨ���������Ĵ�ֵ�������ڴ��ռ��
 *
 * \note �����ֵΪ 0�����޷�ʹ�� GPIO �жϹ��ܣ����ǿ���ʹ������ GPIO ����
 */
#define __GPIO_PINT_USE_COUNT    AMHW_LPC82X_PINT_CHAN_NUM

/** \brief ���Ŵ�����Ϣ�ڴ� */
am_local
struct am_lpc82x_gpio_trigger_info __g_gpio_triginfos[__GPIO_PINT_USE_COUNT];

/** \brief ���Ŵ�����Ϣӳ�� */
am_local uint8_t                   __g_gpio_infomap[__GPIO_PINT_USE_COUNT];

/** \brief GPIO �豸��Ϣ */
am_local am_const am_lpc82x_gpio_devinfo_t __g_lpc82x_gpio_devinfo = {

    LPC82X_SWM_BASE,             /* SWM �Ĵ������ַ */
    LPC82X_GPIO_BASE,            /* GPIO �Ĵ������ַ */
    LPC82X_IOCON_BASE,           /* IOCON �Ĵ������ַ */
    LPC82X_PINT_BASE,            /* PINT �Ĵ������ַ */
    {
        INUM_PIN_INT0,           /* PINT0 �жϺ� */
        INUM_PIN_INT1,           /* PINT1 �жϺ� */
        INUM_PIN_INT2,           /* PINT2 �жϺ� */
        INUM_PIN_INT3,           /* PINT3 �жϺ� */
        INUM_PIN_INT4,           /* PINT4 �жϺ� */
        INUM_PIN_INT5,           /* PINT5 �жϺ� */
        INUM_PIN_INT6,           /* PINT6 �жϺ� */
        INUM_PIN_INT7,           /* PINT7 �жϺ� */
    },
    __GPIO_PINT_USE_COUNT,       /* GPIO ֧�ֵ������жϺ����� */
    &__g_gpio_infomap[0],        /* ���Ŵ�����Ϣӳ�� */
    &__g_gpio_triginfos[0],      /* ���Ŵ�����Ϣ�ڴ� */
    __lpc82x_gpio_plfm_init,     /* ƽ̨��ʼ������ */
    __lpc82x_gpio_plfm_deinit    /* ƽ̨���ʼ������ */
};

/** \brief GPIO �豸ʵ�� */
am_local am_lpc82x_gpio_dev_t __g_lpc82x_gpio_dev;

/**
 * \brief GPIO ʵ����ʼ��
 */
int am_lpc82x_gpio_inst_init (void)
{
    return am_lpc82x_gpio_init(&__g_lpc82x_gpio_dev, &__g_lpc82x_gpio_devinfo);
}

/**
 * \brief GPIO ʵ�����ʼ��
 */
void am_lpc82x_gpio_inst_deinit (void)
{
    am_lpc82x_gpio_deinit();
}

/**
 * @}
 */

/* end of file */
