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
 * \brief KL26 I2C1 �û������ļ�
 * \sa am_kl26_hwconfig_i2c1.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-10-27  LXY , first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "hw/amhw_kl26_sim.h"
#include "kl26_periph_map.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "am_fsl_i2c.h"
#include "am_gpio.h"
#include "kl26_pin.h"
#include "kl26_clk.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_i2c1
 * \copydoc am_kl26_hwconfig_i2c1.c
 * @{
 */

/**
 * \name I2C1 ��������������
 * @{
 */

#define BUS_SPEED_I2C1     (100000)     /**< \brief I2C1 �������ʲ������� */

/** @} */

/** \brief I2C1 ƽ̨��ʼ������ */
void amhw_kl26_plfm_i2c1_init (void)
{
    am_gpio_pin_cfg (PIOC_11, PIOC_11_I2C1_SDA);
    am_gpio_pin_cfg (PIOC_10, PIOC_10_I2C1_SCL);

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_I2C1);
}

/** \brief ���I2C1 ƽ̨��ʼ������ */
void amhw_kl26_plfm_i2c1_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_I2C1);
}


/**
 * \brief I2C1 �豸��Ϣ
 */
const  struct am_fsl_i2c_devinfo  __g_i2c1_devinfo = {
    KL26_I2C1,                        /**< \brief ָ��I2C1�Ĵ������ָ�� */
    BUS_SPEED_I2C1,
    INUM_I2C1,                             /**< \brief I2C1 �жϱ�� */
	CLK_I2C1,                              /**< \brief I2C1  ʱ�Ӻ� */
    10,                                    /**< \brief I2C1 ��ʱʱ������ */
    amhw_kl26_plfm_i2c1_init,              /** \brief I2C1 ƽ̨��ʼ������ */
    amhw_kl26_plfm_i2c1_deinit             /** \brief ���I2C1 ƽ̨��ʼ������ */
};

am_fsl_i2c_dev_t __g_i2c1_dev;            /**< \brief I2C1 �豸ʵ�� */

/** \brief i2c1ʵ����ʼ�������i2c��׼������ */
am_i2c_handle_t am_kl26_i2c1_inst_init (void)
{
    return am_fsl_i2c_init(&__g_i2c1_dev, &__g_i2c1_devinfo);
}

/** \brief i2c1ʵ�����ʼ�� */
void am_kl26_i2c1_inst_deinit (am_i2c_handle_t handle)
{
    am_fsl_i2c_deinit(handle);
}
/** @} */

/* end of file */
