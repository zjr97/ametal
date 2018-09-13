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
 * \brief ZLG217 I2C �ӻ��û������ļ�
 * \sa am_hwconf_zlg217_i2c.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-07  vir, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg217.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg_i2c_slv.h"
#include "am_zlg217_clk.h"
#include "amhw_zlg_i2c.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_i2c_slv
 * \copydoc am_hwconf_zlg217_i2c_slv.c
 * @{
 */

/** \brief I2C1 ƽ̨��ʼ������ */
static void __zlg_i2c1_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_6, PIOB_6_I2C1_SCL_REMAP0 | PIOB_6_AF_OD);
    am_gpio_pin_cfg(PIOB_7, PIOB_7_I2C1_SDA_REMAP0 | PIOB_7_AF_OD);

    am_clk_enable(CLK_I2C1);
    am_zlg217_clk_reset(CLK_I2C1);
}

/** \brief ���I2C1 ƽ̨��ʼ������ */
static void __zlg_i2c1_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C1);
}

/**
 * \name I2C1 ��������������
 * @{
 */

/** @} */

/**
 * \brief I2C1 �ӻ��豸��Ϣ
 */
static const am_zlg_i2c_slv_devinfo_t __g_i2c1_devinfo = {

    ZLG217_I2C1_BASE,                 /**< \brief I2C1 �Ĵ������ַ */
    INUM_I2C1_EV,                     /**< \brief I2C1 �жϱ�� */

    __zlg_i2c1_plfm_init,             /**< \brief ƽ̨��ʼ�� */
    __zlg_i2c1_plfm_deinit            /**< \brief ƽ̨ȥ��ʼ�� */
};

/**< \brief I2C1 �豸ʵ�� */
static am_zlg_i2c_slv_dev_t __g_i2c1_dev;

/** \brief I2C1 ʵ����ʼ�������I2C��׼������ */
am_i2c_slv_handle_t  am_zlg217_i2c1_slv_inst_init (void)
{
    return am_zlg_i2c_slv_init(&__g_i2c1_dev, &__g_i2c1_devinfo);
}

/** \brief I2C1 ʵ�����ʼ�� */
void am_zlg217_i2c1_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_zlg_i2c_slv_deinit(handle);
}

/** \brief I2C2 ƽ̨��ʼ������ */
static void __zlg_i2c2_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_I2C2_SCL | PIOB_10_AF_OD | PIOB_10_SPEED_2MHz );
    am_gpio_pin_cfg(PIOB_11, PIOB_11_I2C2_SDA | PIOB_11_AF_OD | PIOB_11_SPEED_2MHz);

    am_clk_enable(CLK_I2C2);
    am_zlg217_clk_reset(CLK_I2C2);
}

/** \brief ���I2C1 ƽ̨��ʼ������ */
static void __zlg_i2c2_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C2);
}

/**
 * \name I2C2 ��������������
 * @{
 */

/** @} */

/**
 * \brief I2C2 �ӻ��豸��Ϣ
 */
static const am_zlg_i2c_slv_devinfo_t __g_i2c2_devinfo = {

    ZLG217_I2C2_BASE,                 /**< \brief I2C2�Ĵ������ַ */
    INUM_I2C2_EV,                     /**< \brief I2C2 �жϱ�� */

    __zlg_i2c2_plfm_init,             /**< \brief ƽ̨��ʼ�� */
    __zlg_i2c2_plfm_deinit            /**< \brief ƽ̨ȥ��ʼ�� */
};

/**< \brief I2C2 �豸ʵ�� */
static am_zlg_i2c_slv_dev_t __g_i2c2_dev;

/** \brief I2C2 ʵ����ʼ�������I2C��׼������ */
am_i2c_slv_handle_t  am_zlg217_i2c2_slv_inst_init (void)
{
    return am_zlg_i2c_slv_init(&__g_i2c2_dev, &__g_i2c2_devinfo);
}

/** \brief I2C2 ʵ�����ʼ�� */
void am_zlg217_i2c2_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_zlg_i2c_slv_deinit(handle);
}

/** @} */

/* end of file */
