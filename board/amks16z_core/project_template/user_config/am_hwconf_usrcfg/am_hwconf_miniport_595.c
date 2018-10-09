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
 * \brief Miniport-595 �����ļ�
 * \sa am_hwconf_miniport_595.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_kl26_inst_init.h"
#include "am_hc595_gpio.h"
#include "am_hc595_spi.h"
#include "kl26_pin.h"
#include "am_kl26.h"
#include "am_kl26_spi_int.h"
#include "hw/amhw_kl26_sim.h"
//#include "am_gpio.h"
//#include "amhw_fsl_spi.h"


/**
 * \addtogroup am_if_src_hwconf_miniport_595
 * \copydoc am_hwconf_miniport_595.c
 * @{
 */

/*******************************************************************************
   Public functions
*******************************************************************************/
static  am_hc595_spi_info_t __hc595_spi_info = {
    PIOD_4,                                        /* ������������ */
    -1,                                            /* δʹ��oe���� */
    300000,                                        /* ʱ��300KHZ */
    AM_TRUE                                        /* ���ݵ�λ�ȷ��� */
};

/** \brief 595 SPI1 ��ʼ�� */
static void __miniport_595_spi1_init (void)
{
    am_gpio_pin_cfg(PIOD_5,  PIOD_5_SPI1_SCK   | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOB_17, PIOB_17_SPI1_MOSI | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOB_16, PIOB_16_SPI1_MISO | AM_GPIO_PULLUP);

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_SPI1);
}

/** \brief ���595 SPI1 ��ʼ�� */
static void __miniport_595_spi1_deinit (void)
{
    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(PIOD_5,  AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_17, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_16, AM_GPIO_INPUT);

    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_SPI1);
}

/**
 * \brief SPI1 �豸��Ϣ
 */
const  struct am_kl26_spi_int_devinfo  __g_miniport_595_devinfo = {
    KL26_SPI1_BASE,                  /**< \brief SPI1�Ĵ���ָ��   */
    INUM_SPI1,                       /**< \brief SPI1�жϺ�       */
    AM_KL26_SPI_INT_CFG_WIAT_EN,     /**< \brief SPI ���ñ�ʶ    */
    __miniport_595_spi1_init,        /**< \brief SPI1ƽ̨��ʼ������ */
    __miniport_595_spi1_deinit       /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_kl26_spi_int_dev_t __g_miniport_595_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_miniport_595_spi1_inst_init (void)
{
    return am_kl26_spi_int_init(&__g_miniport_595_dev, &__g_miniport_595_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_miniport_595_spi1_inst_deinit (am_spi_handle_t handle)
{
    am_kl26_spi_int_deinit(handle);
}

/* MiniPort-595 ʵ����ʼ�� */
am_hc595_handle_t am_miniport_595_inst_init (void)
{
    static am_hc595_spi_dev_t    miniport_595;

    return  am_hc595_spi_init(&miniport_595,
                              &__hc595_spi_info,
                              am_miniport_595_spi1_inst_init());
}

/**
 * @}
 */

/* end of file */
