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
 * \brief I2C ��д EEPROM ���̣���ѯ��ʽ����ͨ�� HW ��ӿ�ʵ��
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
 *
 * \par Դ����
 * \snippet demo_am824_hw_i2c_master_poll.c src_am824_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_i2c_master_poll
 * \copydoc demo_am824_hw_i2c_master_poll.c
 */

/** [src_am824_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

#define __I2C_MASTER    LPC82X_I2C0      /**< \brief I2C ����������ͨ���Ŷ��� */
#define __I2C_SPEED     400000           /**< \brief I2C �������ٶȲ������� */
#define __I2C_CLKDIV    6                /**< \brief I2C ������ʱ�ӷ�Ƶ�������� */
#define __EEPROM_ADDR   0x50             /**< \brief EEPROM �豸��ַ���� */


/**
 * \brief I2C ������������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] speed    �����ٶȲ���
 *
 * \retval AM_OK �������
 */
am_local int __i2c_speed_set (amhw_lpc_i2c_t *p_hw_i2c, uint32_t speed)
{
    uint32_t scl   = 0;
    uint32_t scl_h = 0;
    uint32_t scl_l = 0;

    scl = amhw_lpc82x_clk_periph_freq_get(p_hw_i2c) /
          ((amhw_lpc_i2c_clkdiv_get(p_hw_i2c)+1) * speed);

    scl_h = scl >> 1;
    scl_l = (scl - scl_h);
    if (scl_h < 2) {
        scl_h = 2;

    } else if (scl_h > 9) {
        scl_h = 9;
    }

    if (scl_l < 2) {
        scl_l = 2;

    } else if (scl_l > 9) {
        scl_l = 9;
    }
    amhw_lpc_i2c_msttime_set(p_hw_i2c, scl_h, scl_l);

    return AM_OK;
}



  
/**
 * \brief �������
 */
void demo_am824_core_hw_i2c_master_poll_entry (void)
{
    AM_DBG_INFO("demo am824 I2C master poll !\r\n");

    am_gpio_pin_cfg(PIO0_10, PIO0_10_I2C0_SCL);
    am_gpio_pin_cfg(PIO0_11, PIO0_11_I2C0_SDA);

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_I2C0);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_I2C0);

    /* �������� */
    __i2c_speed_set(__I2C_MASTER, __I2C_SPEED);

    demo_lpc_hw_i2c_master_poll_entey(__I2C_MASTER, __I2C_CLKDIV, __EEPROM_ADDR);
}
/** [src_am824_hw_i2c_master_poll] */

/* end of file */
