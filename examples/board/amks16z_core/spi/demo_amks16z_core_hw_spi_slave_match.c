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
 * \brief SPI�ӻ�ƥ���ж���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI�ӻ��ӿں������ӿڶ�Ӧ��������(PIOC_4 == PIOD_4, PIOC_5 == PIOD_5,
 *      PIOC_6 == PIOD_6, PIOC_7 == PIOD_7)����
 *
 * - ʵ������:
 *   1. SPI0�ӻ�����SPI1�������ݣ�������ݱ�ƥ�䣬���ʹӻ��������������
 *   2. SPI1���������յ����������Ƿ���ȷ�������ȷ����LED������LED��˸������
 *
 * \par Դ����
 * \snippet demo_kl26_hw_spi_slave_match.c src_kl26_hw_spi_slave_match
 *
 * \internal
 * \par History
 * - 1.00 15-10-30  liqing, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_kl26_if_hw_spi_slave_match
 * \copydoc demo_kl26_hw_spi_slave_match.c
 */
 
/** [src_kl26_hw_spi_slave_match] */
#include "ametal.h"
#include "am_int.h"
#include "am_kl26_inst_init.h"
#include "hw/amhw_fsl_spi.h"
#include "hw/amhw_kl26_sim.h"
#include "am_kl26_clk.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/kl26_inum.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief SPI0�ӻ����ų�ʼ��
 */
static void __spi0_pin_init (void)
{
    /* ����ʹ��Ƭѡ,�͵�ƽ��Ч */
    am_gpio_pin_cfg(PIOC_4, PIOC_4_SPI0_PCS0);
    am_gpio_pin_cfg(PIOC_5, PIOC_5_SPI0_SCK );
    am_gpio_pin_cfg(PIOC_6, PIOC_6_SPI0_MOSI);
    am_gpio_pin_cfg(PIOC_7, PIOC_7_SPI0_MISO);
}

/**
 * \brief SPI1���������ų�ʼ��
 */
static void __spi1_pin_init (void)
{
    am_gpio_pin_cfg(PIOD_4, PIOD_4_SPI1_PCS0);
    am_gpio_pin_cfg(PIOD_5, PIOD_5_SPI1_SCK  | AM_GPIO_PULLUP );
    am_gpio_pin_cfg(PIOD_6, PIOD_6_SPI1_MOSI | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOD_7, PIOD_7_SPI1_MISO | AM_GPIO_PULLUP);
}

/**
 * \brief �������
 */
void demo_amks16z_core_hw_spi_slave_match_entry (void)
{
    uint32_t spi_freq;
    __spi0_pin_init();
    __spi1_pin_init();

    /* ����SPIʱ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_SPI0);
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_SPI1);

    spi_freq = am_kl26_clk_periph_rate_get(KL26_SPI1);

    demo_fsl_hw_spi_slave_match_entry(KL26_SPI0,
                                      KL26_SPI1,
                                      INUM_SPI0,
                                      spi_freq);
}

/** [src_kl26_hw_spi_slave_match] */

/* end of file */
