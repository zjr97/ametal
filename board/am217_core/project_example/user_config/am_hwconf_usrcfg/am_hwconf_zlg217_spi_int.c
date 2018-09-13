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
 * \brief ZLG217 SPI INT �û������ļ�
 * \sa am_hwconf_zlg217_spi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-8-22  fra, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg_spi_int.h"
#include "am_gpio.h"
#include "amhw_zlg_spi.h"
#include "am_clk.h"
#include "am_zlg217.h"
#include "zlg217_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_spi_int
 * \copydoc am_hwconf_zlg217_spi_int.c
 * @{
 */

/** \brief SPI1 ƽ̨��ʼ�� */
static void __zlg_plfm_spi1_int_init (void)
{
    am_gpio_pin_cfg(PIOA_5, PIOA_5_SPI1_SCK_REMAP0  | PIOA_5_AF_PP);
    am_gpio_pin_cfg(PIOA_6, PIOA_6_SPI1_MISO_REMAP0 | PIOA_6_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOA_7, PIOA_7_SPI1_MOSI_REMAP0 | PIOA_7_AF_PP);

    am_clk_enable(CLK_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
static void __zlg_plfm_spi1_int_deinit (void)
{
    am_gpio_pin_cfg(PIOA_5, AM_GPIO_INPUT );
    am_gpio_pin_cfg(PIOA_6, AM_GPIO_INPUT );
    am_gpio_pin_cfg(PIOA_7, AM_GPIO_INPUT );

    am_clk_disable(CLK_SPI1);
}

/** \brief SPI1 �豸��Ϣ */
const  struct am_zlg_spi_int_devinfo  __g_spi1_int_devinfo = {
    ZLG217_SPI1_BASE,                        /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                                /**< \brief ʱ��ID�� */
    INUM_SPI1,                               /**< \brief SPI1�жϺ� */
    PIOA_7_SPI1_MOSI_REMAP0 | PIOA_7_AF_PP,  /**< \brief SPI1���ñ�ʶ */
    PIOA_7,                                  /**< \brief MOSI���ź� */
    __zlg_plfm_spi1_int_init,                /**< \brief SPI1ƽ̨��ʼ������ */
    __zlg_plfm_spi1_int_deinit               /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_zlg_spi_int_dev_t __g_spi1_int_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zlg217_spi1_int_inst_init (void)
{
    return am_zlg_spi_int_init(&__g_spi1_int_dev, &__g_spi1_int_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_zlg217_spi1_int_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_int_deinit(handle);
}

/** \brief SPI2 ƽ̨��ʼ�� */
static void __zlg_plfm_spi2_int_init (void)
{
    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI | PIOB_15_AF_PP);
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK  | PIOB_13_AF_PP);

    am_clk_enable(CLK_SPI2);
}

/** \brief ���SPI2 ƽ̨��ʼ�� */
static void __zlg_plfm_spi2_int_deinit (void)
{
    am_gpio_pin_cfg(PIOB_13, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_14, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_15, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI2);
}
/**
 * \brief SPI2 �豸��Ϣ
 */
const  struct am_zlg_spi_int_devinfo  __g_spi2_int_devinfo = {
    ZLG217_SPI2_BASE,                      /**< \brief SPI2�Ĵ���ָ�� */
    CLK_SPI2,                              /**< \brief ʱ��ID�� */
    INUM_SPI2,                             /**< \brief SPI2�жϺ� */
    PIOB_15_SPI2_MOSI | PIOB_15_AF_PP,     /**< \brief SPI2���ñ�ʶ */
    PIOB_15,                               /**< \brief mosi���ź� */
    __zlg_plfm_spi2_int_init,              /**< \brief SPI2ƽ̨��ʼ������ */
    __zlg_plfm_spi2_int_deinit             /**< \brief SPI2ƽ̨���ʼ������ */
};

/** \brief SPI2 �豸ʵ�� */
static am_zlg_spi_int_dev_t __g_spi2_int_dev;

/** \brief SPI2 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zlg217_spi2_int_inst_init (void)
{
    return am_zlg_spi_int_init(&__g_spi2_int_dev, &__g_spi2_int_devinfo);
}

/** \brief SPI2 ʵ�����ʼ�� */
void am_zlg217_spi2_int_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_int_deinit(handle);
}

/**
 * @}
 */

/* end of file */
