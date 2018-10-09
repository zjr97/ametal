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
 * \brief LPC82X SPI (DMA ��ʽ) �û������ļ�
 * \sa am_hwconf_lpc82x_spi1_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.02 15-11-25  sky, modified
 * - 1.01 15-10-10  aii, second implementation
 * - 1.00 15-07-10  aii, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_lpc82x.h"
#include "am_lpc_spi_int.h"
#include "am_lpc82x_spi_dma.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_spi1_dma
 * \copydoc am_hwconf_lpc82x_spi1_dma.c
 * @{
 */

/**
 * \brief SPI1 ƽ̨��ʼ��
 */
am_local void __lpc82x_spi1_dma_plfm_init (void)
{
    am_gpio_pin_cfg(PIO0_11, PIO_FUNC_SPI1_SCK);
    am_gpio_pin_cfg(PIO0_10, PIO_FUNC_SPI1_MOSI);
    am_gpio_pin_cfg(PIO0_9, PIO_FUNC_SPI1_MISO);

    /* CS_Pin ���û����� STD ����ʱ���д��룬�˴��������� */

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SPI1);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI1);
}

/**
 * \brief SPI1 ƽ̨���ʼ��
 */
am_local void __lpc82x_spi1_dma_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI1);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SPI1);

    am_gpio_pin_cfg(PIO0_11, AM_GPIO_PULLUP | AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_10, AM_GPIO_PULLUP | AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_9, AM_GPIO_PULLUP | AM_GPIO_INPUT);
}

/** \brief SPI1 (DMA ��ʽ) �豸��Ϣ */
am_local am_const
struct am_lpc82x_spi_dma_devinfo __g_lpc82x_spi1_dma_devinfo = {
    LPC82X_SPI1_BASE,                /* SPI1 �Ĵ��������ַ */
    CLK_SPI1,                        /* SPI1 ʱ�Ӻ� */
    DMA_CHAN_SPI1_TX_REQ,            /* DMA ����ͨ�� */
    DMA_CHAN_SPI1_RX_REQ,            /* DMA ����ͨ�� */
    AMHW_LPC82X_DMA_CHAN_PRIO_1,     /* �������ȼ� */
    AMHW_LPC82X_DMA_CHAN_PRIO_0,     /* �������ȼ� */
    __lpc82x_spi1_dma_plfm_init,     /* ƽ̨��ʼ������ */
    __lpc82x_spi1_dma_plfm_deinit    /* ƽ̨���ʼ������ */
};

/** \brief SPI1 (DMA ��ʽ) �豸ʵ�� */
am_local am_lpc82x_spi_dma_dev_t __g_lpc82x_spi1_dma_dev;

/**
 * \brief SPI1 (DMA ��ʽ) ʵ����ʼ��
 */
am_spi_handle_t am_lpc82x_spi1_dma_inst_init (void)
{
    return am_lpc82x_spi_dma_init(&__g_lpc82x_spi1_dma_dev,
                                  &__g_lpc82x_spi1_dma_devinfo);
}

/**
 * \brief SPI1 (DMA ��ʽ) ʵ�����ʼ��
 */
void am_lpc82x_spi1_dma_inst_deinit (am_spi_handle_t handle)
{
    am_lpc82x_spi_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */
