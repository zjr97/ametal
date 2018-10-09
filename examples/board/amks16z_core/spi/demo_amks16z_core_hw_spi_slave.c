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
 * \brief SPI�ӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI�ӻ��ӿں������ӿڶ�Ӧ��������;
 *   2. ���������ص�demo�壬�����ϵ���߸�λ��
 *
 * - ʵ������:
 *   1. �ӻ������������ݣ���ͨ�����ڽ����յ������ݴ�ӡ������
 *   2. �ӻ��������ݵ���������ͨ�����ڽ����͵����ݴ�ӡ������
 *
 * - ע�⣺
 *   1. ��Ҫʹ�������豸�䵱������
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_spi_slave.c src_amks16z_core_hw_spi_slave
 *
 * \internal
 * \par History
 * - 1.00 16-09-27  sdy, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_spi_slave
 * \copydoc demo_amks16z_core_hw_spi_slave.c
 */
 
/** [src_amks16z_core_hw_spi_slave] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_kl26_inst_init.h"
#include "hw/amhw_fsl_spi.h"
#include "hw/amhw_kl26_sim.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"


/**
 * \brief �������
 */
void demo_amks16z_core_hw_spi_slave_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw spi slave!\r\n");

    /* ����ʹ��Ƭѡ,�͵�ƽ��Ч */
    am_gpio_pin_cfg(PIOC_4, PIOC_4_SPI0_PCS0);
    am_gpio_pin_cfg(PIOC_5, PIOC_5_SPI0_SCK );
    am_gpio_pin_cfg(PIOC_6, PIOC_6_SPI0_MOSI);
    am_gpio_pin_cfg(PIOC_7, PIOC_7_SPI0_MISO);

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_SPI0);

    demo_fsl_hw_spi_slave_entry(KL26_SPI0);
}

/** [src_amks16z_core_hw_spi_slave] */

/* end of file */

