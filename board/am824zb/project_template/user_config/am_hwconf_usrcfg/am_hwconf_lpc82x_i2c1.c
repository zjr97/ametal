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
 * \brief LPC82X I2C1 �û������ļ�
 * \sa am_hwconf_lpc82x_i2c1.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  win, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc_i2c.h"
#include "am_lpc82x.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_i2c1
 * \copydoc am_hwconf_lpc82x_i2c1.c
 * @{
 */

/** \brief I2C1 ƽ̨��ʼ������ */
static void __lpc82x_i2c1_plfm_init (void)
{
    /**
     * PIO0_16 ~ I2C1_SCL, PIO0_18 ~ I2C1_SDA
     */
    am_gpio_pin_cfg(PIO0_16, PIO_FUNC_I2C1_SCL | PIO0_16_OPEN_DRAIN);
    am_gpio_pin_cfg(PIO0_18, PIO_FUNC_I2C1_SDA | PIO0_18_OPEN_DRAIN);

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_I2C1);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_I2C1);

}

/** \brief ���I2C1 ƽ̨��ʼ������ */
static void __lpc82x_i2c1_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_I2C1);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_I2C1);
}

/**
 * \name I2C1 ��������������
 * @{
 */

#define BUS_SPEED_I2C1     (400000)     /**< \brief I2C1 �������ʲ������� */

/** @} */

/**
 * \brief I2C1 �豸��Ϣ
 */
static const am_lpc_i2c_devinfo_t __g_i2c1_devinfo = {

    BUS_SPEED_I2C1,                     /**< \brief I2C1 ����ʱ������ */
    LPC82X_I2C1_BASE,                   /**< \brief I2C1�Ĵ������ַ */
    INUM_I2C1,                          /**< \brief I2C1 �жϱ�� */
    CLK_I2C1,                           /**< \brief I2C0 ʱ��ID */
    0,                                  /**< \brief ��ʱֵ0 */

    __lpc82x_i2c1_plfm_init,            /**< \brief ƽ̨��ʼ�� */
    __lpc82x_i2c1_plfm_deinit           /**< \brief ƽ̨ȥ��ʼ�� */
};

static am_lpc_i2c_dev_t __g_i2c1_dev; /**< \brief I2C1 �豸ʵ�� */


/** \brief I2C1 ʵ����ʼ�������I2C��׼������ */
am_i2c_handle_t am_lpc82x_i2c1_inst_init (void)
{
    return am_lpc_i2c_init(&__g_i2c1_dev, &__g_i2c1_devinfo);
}

/** \brief I2C1 ʵ�����ʼ�� */
void am_lpc82x_i2c1_inst_deinit (am_i2c_handle_t handle)
{
    am_lpc_i2c_deinit(handle);
}

/** @} */

/* end of file */
