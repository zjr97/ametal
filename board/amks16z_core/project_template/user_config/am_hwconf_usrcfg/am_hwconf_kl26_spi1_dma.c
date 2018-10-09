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
 * \brief KL16 SPI �û������ļ�
 * \sa am_kl26_hwconfig_spi1_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-10-23  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_kl26.h"
#include "am_kl26_spi_dma.h"
#include "am_gpio.h"
#include "hw/amhw_fsl_spi.h"
#include "hw/amhw_kl26_sim.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_spi1_dma
 * \copydoc am_kl26_hwconfig_spi1_dma.c
 * @{
 */

/** \brief SPI1 ƽ̨��ʼ�� */
static void __kl26_plfm_spi1_dma_init (void)
{
    am_gpio_pin_cfg(PIOD_5, PIOD_5_SPI1_SCK  | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOD_6, PIOD_6_SPI1_MISO | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOD_7, PIOD_7_SPI1_MOSI | AM_GPIO_PULLUP);

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
static void __kl26_plfm_spi1_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOD_5, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOD_6, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOD_7, AM_GPIO_INPUT);

    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_SPI1);
}
/**
 * \brief SPI1 �豸��Ϣ
 */
static const struct am_kl26_spi_dma_devinfo  __g_spi1_devinfo = {
    KL26_SPI1_BASE,                /**< \brief SPI1�Ĵ���ָ��   */
    AM_KL26_SPI_DMA_CFG_WIAT_EN,       /**< \brief SPI ���ñ�ʶ   */

    DMA_CHAN_1,
    DMA_CHAN_0,
    DMA_REQUEST_MUX0_SPI1TX,
    DMA_REQUEST_MUX0_SPI1RX,
    __kl26_plfm_spi1_dma_init,         /**< \brief SPI1ƽ̨��ʼ������ */
    __kl26_plfm_spi1_dma_deinit        /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_kl26_spi_dma_dev_t __g_spi1_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_kl26_spi1_dma_inst_init (void)
{
    return am_kl26_spi_dma_init(&__g_spi1_dev, &__g_spi1_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_kl26_spi1_dma_inst_deinit (am_spi_handle_t handle)
{
    am_kl26_spi_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */
