/*******************************************************************************
*                                 AMetal
*                       ---------------------------
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
 * \brief LPC82X SPI �û�����ʵ��
 * \sa am_hwconf_lpc82x_spi0_int.c
 *
 * \internal
 * \par Modification history
 * - 1.02 15-11-25  sky, modified.
 * - 1.01 15-10-10  aii, second implementation.
 * - 1.00 15-07-10  aii, first implementation.
 * \endinternal
 */

#include "am_lpc82x.h"
#include "am_lpc82x_spi_dma.h"
#include "am_lpc_spi_int.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_spi0_int
 * \copydoc am_hwconf_lpc82x_spi0_int.c
 * @{
 */

/** \brief SPI0 ƽ̨��ʼ�� */
static void __lpc82x_spi0_plfm_init (void)
{

    /* SPI0 �������� */
    am_gpio_pin_cfg(PIO0_15, PIO_FUNC_SPI0_SCK);
    am_gpio_pin_cfg(PIO0_11, PIO_FUNC_SPI0_MOSI);
    am_gpio_pin_cfg(PIO0_13, PIO_FUNC_SPI0_MISO);
    /* CS_Pin ���û�����STD����ʱ���д��룬�˴��������� */

    /* ʹ�� SPI0 ʱ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SPI0);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI0);
}

/** \brief ���SPI0 ƽ̨��ʼ�� */
static void __lpc82x_spi0_plfm_deinit (void)
{
    /* ���� SPI0 ʱ�� */
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI0);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SPI0);
}

/**
 * \brief SPI0 controller device information
 */
static const  struct am_lpc_spi_int_devinfo  __g_spi0_devinfo = {
    LPC82X_SPI0_BASE,                     /**< \brief SPI0 base address */
    INUM_SPI0,                            /**< \brief SPI0 interrupt number */
    CLK_SPI0,                             /**< \brief SPI0 clk id */
    __lpc82x_spi0_plfm_init,              /**< \brief SPI0 plfm init */
    __lpc82x_spi0_plfm_deinit             /**< \brief SPI0 plfm deinit */
};

/** \brief Define space for SPI0 */
static am_lpc_spi_int_dev_t __g_spi0_dev;

/** \brief SP0I ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_lpc82x_spi0_int_inst_init (void)
{
    return am_lpc_spi_int_init(&__g_spi0_dev, &__g_spi0_devinfo);
}

/** \brief SPI ʵ�����ʼ�� */
void am_lpc82x_spi0_int_inst_deinit (am_spi_handle_t handle)
{
    am_lpc_spi_int_deinit(handle);
}


/**
 * @}
 */

/* end of file */
