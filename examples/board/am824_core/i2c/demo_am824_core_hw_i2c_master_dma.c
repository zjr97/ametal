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
 * \brief I2C ��д EEPROM ���̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_10 �������� EEPROM �� SCL ���ţ�
 *   2. PIO0_11 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. �� EEPROM �豸д�� __TEST_LENTH �ֽ����ݣ�
 *   2. ��ȡ EEPROM �е�����ͨ�����ڴ�ӡ������
 *   3. ��д�����ݺͶ�ȡ������һ�£�У��ͨ����LED0 �� 200ms �����˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. DMA ��ʼ�������Ѿ��� am_prj_config.c �ļ��ڲ���ɡ�
 *
 * \par Դ����
 * \snippet demo_am824_hw_i2c_master_dma.c src_am824_hw_i2c_master_dma
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-04  cyl, modified the using of dma interface
 * - 1.00 15-07-16  win, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_am824_hw_i2c_master_dma
 * \copydoc demo_am824_hw_i2c_master_dma.c
 */

/** [src_am824_hw_i2c_master_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define __I2C_MASTER  LPC82X_I2C0      /**< \brief I2C ����������ͨ���Ŷ��� */
#define __I2C_CLKDIV  15               /**< \brief I2C ������ʱ�ӷ�Ƶ�������� */

#define __EEPROM_ADDR 0x50             /**< \brief EEPROM ������ַ */
#define __SUB_ADDR    0x00             /**< \brief �ӻ��ӵ�ַ */



/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/


/**
 * \brief �������
 */
void demo_am824_core_hw_i2c_master_dma_entry (void)
{
    AM_DBG_INFO("demo am824 master dma!\r\n");

    am_gpio_pin_cfg(PIO0_10, PIO0_10_I2C0_SCL);
    am_gpio_pin_cfg(PIO0_11, PIO0_11_I2C0_SDA);

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_I2C0);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_I2C0);

    demo_lpc824_hw_i2c_master_dma_entry(__I2C_MASTER, 
                                        __I2C_CLKDIV, 
                                        __EEPROM_ADDR, 
                                        __SUB_ADDR);
    
}
/** [src_am824_hw_i2c_master_dma] */

/* end of file */
