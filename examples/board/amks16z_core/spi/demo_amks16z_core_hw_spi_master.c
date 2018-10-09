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
 * \brief SPI������ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI��PIOC_6��PIOC_7����������ģ��ӻ��豸���ػ����ԣ�
 *
 * - ʵ������:
 *   1. ����ͨ��MOSI�������ݣ����������ݴ�MOSI���أ�
 *   2. �ȽϷ����Ͷ��ص����ݣ������ͬLED0һֱ����,������200msʱ������˸��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_spi_master.c src_amks16z_core_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 16-09-27  sdy, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_amks16z_core_if_hw_spi_master
 * \copydoc demo_amks16z_core_hw_spi_master.c
 */
 
/** [src_amks16z_core_hw_spi_master] */
#include "ametal.h"
#include "am_kl26_inst_init.h"
#include "hw/amhw_fsl_spi.h"
#include "hw/amhw_kl26_sim.h"
#include "am_kl26_clk.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

#define SPI_CS_PIN          PIOC_4     /**< \brief Ƭѡ����             */

/**
 * \brief �������
 */
void demo_amks16z_core_hw_spi_master_entry (void)
{
    uint32_t spi_freq;

    AM_DBG_INFO("demo amks16z_core hw spi master!\r\n");

    /* ����ʱ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_SPI0);

    /* �������� */
    am_gpio_pin_cfg(SPI_CS_PIN, AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOC_5, PIOC_5_SPI0_SCK  | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOC_6, PIOC_6_SPI0_MISO | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOC_7, PIOC_7_SPI0_MOSI | AM_GPIO_PULLUP);

    spi_freq = am_kl26_clk_periph_rate_get(KL26_SPI0);

    demo_fsl_hw_spi_master_entry(KL26_SPI0, SPI_CS_PIN, spi_freq);
}

/** [src_amks16z_core_hw_spi_master] */

/* end of file */
