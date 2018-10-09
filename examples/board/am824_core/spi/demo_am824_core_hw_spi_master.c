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
 * \brief SPI ���������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI ������ SPI �ӻ������������ӡ�
 *
 * - ʵ������
 *   1. ������ÿ 500 ����ͨ�� SPI����ӻ����� "nihao" �ַ�����
 *   2. �ӻ����յ��ַ�����ͨ�����ڽ��ַ�����ӡ�������� LED0 ��˸��
 *
 * \note
 *    1. ��������Ҫ�� demo_am824_hw_spi_slave.c һͬ���ԣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_hw_spi_master.c src_am824_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.01 15-11-26  sky, modified
 * - 1.00 15-07-15  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_spi_master
 * \copydoc demo_am824_hw_spi_master.c
 */

/** [src_am824_hw_spi_master] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_spi_master_entry (void)
{
    uint32_t clk = 0;
  
    am_kprintf("demo824 hw spi master!\r\n");
  
    /* SPI0 �������� */
    am_gpio_pin_cfg(PIO0_14, PIO_FUNC_SPI0_SSEL0);
    am_gpio_pin_cfg(PIO0_15, PIO_FUNC_SPI0_SCK);
    am_gpio_pin_cfg(PIO0_12, PIO_FUNC_SPI0_MOSI);
    am_gpio_pin_cfg(PIO0_13, PIO_FUNC_SPI0_MISO);

    /* ʹ�� SPI0 ʱ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SPI0);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI0);
  
    clk = amhw_lpc82x_clk_periph_freq_get(LPC82X_SPI0);
  
    demo_lpc_hw_spi_master_entry(LPC82X_SPI0, clk);
}
/** [src_am824_hw_spi_master] */

/* end of file */
