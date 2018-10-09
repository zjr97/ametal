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
 * \brief MiniPort-595 �û������ļ�
 * \sa am_hwconf_miniport_595.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_hc595_spi.h"
#include "am_hc595_gpio.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_595
 * \copydoc am_hwconf_miniport_595.c
 * @{
 */

/** \brief �Ƿ�ʹ�� GPIO ģ�� SPI 0: ʹ��Ӳ�� SPI  1: ʹ�� GPIO ģ�� SPI */
#define    __USE_GPIO_SPI    0

#if (__USE_GPIO_SPI == 1)

/** \brief MiniPort-595 GPIO �豸��Ϣ */
am_local am_const am_hc595_gpio_info_t __g_miniport_595_gpio_devinfo = {
    PIO0_10,    /* �������� (SPI_MOSI) */
    PIO0_11,    /* ��λʱ������ (SPI_CLK) */
    PIO0_14,    /* ������������ (SPI_CS) */
    -1,         /* OE �̶�Ϊ�͵�ƽ��δʹ�� */
    AM_TRUE     /* ��λ�ȷ��� */
};

/** \brief MiniPort-595 GPIO �豸ʵ�� */
am_local am_hc595_gpio_dev_t __g_miniport_595_gpio_dev;
#else

/** \brief MiniPort-595 SPI �豸��Ϣ */
am_local  am_hc595_spi_info_t __g_miniport_595_spi_devinfo = {
    PIO0_14,    /* ������������ */
    -1,         /* δʹ�� OE ���� */
    300000,     /* ʱ��Ƶ�� 300KHz */
    AM_TRUE     /* ���ݵ�λ�ȷ��� */
};

/** \brief MiniPort-595 SPI �豸ʵ�� */
am_local am_hc595_spi_dev_t __g_miniport_595_spi_dev;
#endif /* (__USE_GPIO_SPI != 1) */

/**
 * \brief MiniPort-595 ʵ����ʼ��
 */
am_hc595_handle_t am_miniport_595_inst_init (void)
{
#if (__USE_GPIO_SPI == 1)
    return am_hc595_gpio_init(&__g_miniport_595_gpio_dev,
                              &__g_miniport_595_gpio_devinfo);
#else
    return am_hc595_spi_init(&__g_miniport_595_spi_dev,
                             &__g_miniport_595_spi_devinfo,
                              am_lpc82x_spi1_dma_inst_init());
#endif
}

/**
 * @}
 */

/* end of file */
