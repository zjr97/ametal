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
 * \brief KL16 SPI0 DMA �û������ļ�
 * \sa am_kl26_hwconfig_spi0_dma.c
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
 * \addtogroup am_kl26_if_hwconfig_src_spi0_dma
 * \copydoc am_kl26_hwconfig_spi0_dma.c
 * @{
 */

/** \brief SPI0 ƽ̨��ʼ�� */
static void __kl26_plfm_spi0_dma_init (void)
{
    am_gpio_pin_cfg(PIOD_1, PIOD_1_SPI0_SCK  | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOD_3, PIOD_3_SPI0_MISO | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOD_2, PIOD_2_SPI0_MOSI | AM_GPIO_PULLUP);

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_SPI0);
}

/** \brief ���SPI0 ƽ̨��ʼ�� */
static void __kl26_plfm_spi0_dma_deinit (void)
{
    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(PIOD_1, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOD_3, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOD_2, AM_GPIO_INPUT);

    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_SPI0);
}

/**
 * \brief SPI0 �豸��Ϣ
 */
static const struct am_kl26_spi_dma_devinfo  __g_spi0_devinfo = {
    KL26_SPI0_BASE,                   /**< \brief SPI0�Ĵ���ָ��   */
    AM_KL26_SPI_DMA_CFG_WIAT_EN,      /**< \brief SPI ���ñ�ʶ    */

    DMA_CHAN_1,
    DMA_CHAN_0,
    DMA_REQUEST_MUX0_SPI0TX,
    DMA_REQUEST_MUX0_SPI0RX,
    __kl26_plfm_spi0_dma_init,        /**< \brief SPI0ƽ̨��ʼ������ */
    __kl26_plfm_spi0_dma_deinit       /**< \brief SPI0ƽ̨���ʼ������ */
};

/** \brief SPI0 �豸ʵ�� */
static am_kl26_spi_dma_dev_t __g_spi0_dev;

/** \brief SPI0 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_kl26_spi0_dma_inst_init (void)
{
    return am_kl26_spi_dma_init(&__g_spi0_dev, &__g_spi0_devinfo);
}

/** \brief SPI0 ʵ�����ʼ�� */
void am_kl26_spi0_dma_inst_deinit (am_spi_handle_t handle)
{
    am_kl26_spi_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */
