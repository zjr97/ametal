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
 * \brief I2C ������д EEPROM ���̣�ͨ���첽��׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_16 �������� EEPROM �� SCL ���ţ�
 *   2. PIO0_18 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. ����д��ַ�����ݵ��ӻ���
 *   2. �������մӻ����ݣ���ͨ�����ڴ�ӡ����
 *   3. ����д������ݺͽ��յ��Ĵӻ��ӻ�����һ�£�
 *   4. LED0 �� 200ms ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_std_i2c_master_async.c src_am824_std_i2c_master_async
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-02  cyl, using the newest async interface to implement
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_i2c_master_async
 * \copydoc demo_am824_std_i2c_master_async.c
 */

/** [src_am824_std_i2c_master_async] */
#include "ametal.h"
#include "am_i2c.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define __EEPROM_ADDR    0x50   /**< \brief EEPROM �豸�ĵ�ַ */
#define __TEST_LEN       8      /**< \brief ���Զ�д���ֽ���(���ܴ���ҳ��С) */

/**
 * \brief �������
 */
void demo_am824_core_std_i2c_master_async_entry (void)
{

    AM_DBG_INFO("demo am824_core std i2c master async!\r\n");

    demo_std_i2c_master_async_entry(am_lpc82x_i2c1_inst_init(),
                                    __EEPROM_ADDR,
                                    __TEST_LEN);
    
}
/** [src_am824_std_i2c_master_async] */

/* end of file */
