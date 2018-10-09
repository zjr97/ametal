/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AM824BLE ����ģ���Զ����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��Ƭ���ֱ���ͨ�� 4800��9600��19200��38400��57600 �� 115200 �Ĳ���������
 *      ZLG7021��
 *   2. ������ӳɹ���ͨ�����ڴ�ӡ��ǰ�Ĳ����ʲ��� 500 ms �ļ������˸ LED0������
 *      LED0 �� 100 ms �ļ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_8 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��
 *       AM_CFG_KEY_ENABLE �� AM_CFG_SOFTIMER_ENABLE ����Ϊ 1������Щ��
 *       �Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *    4. ZLG9021 ģ�������ӹ�ϵ���£�
 * <pre>
 *           PIO0_26  <-->  ZLG9021_RX
 *           PIO0_27  <-->  ZLG9021_TX
 *           PIO0_16  <-->  ZLG9021_EN
 *           PIO0_25  <-->  ZLG9021_BRTS
 *           PIO0_28  <-->  ZLG9021_RESET
 * </pre>
 *       �����Ҫʹ�� ZLG9021����Щ IO �ڲ�������������;��
 *
 * \par Դ����
 * \snippet demo_am824ble_std_zlg9021_baudrate.c src_am824ble_std_zlg9021_baudrate
 *
 * \internal
 * \par Modification history
 * - 1.00 17-12-08  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824ble_std_zlg9021_baudrate
 * \copydoc demo_am824ble_std_zlg9021_baudrate.c
 */

/** [src_am824ble_std_zlg9021_baudrate] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_led.h"
#include "am_lpc82x_inst_init.h"
#include "demo_components_entries.h"

/**
 * \brief �������
 */
void demo_am824ble_std_zlg9021_baudrate_entry (void)
{
    am_zlg9021_handle_t zlg9021_handle = am_zlg9021_inst_init();

    demo_zlg9021_baudrate_entry(zlg9021_handle);
}

/** [src_am824ble_std_zlg9021_baudrate] */

/* end of file */
