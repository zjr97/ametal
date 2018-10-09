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
 * \brief ����ģ���Զ����������̣�ͨ����׼�ӿ�ʵ��
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
 * \snippet demo_zlg9021_baudrate.c src_zlg9021_baudrate
 *
 * \internal
 * \par Modification history
 * - 1.00 17-12-08  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg9021_baudrate
 * \copydoc demo_zlg9021_baudrate.c
 */

/** [src_zlg9021_baudrate] */
#include "ametal.h"
#include "am_zlg9021.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_led.h"
#include "am_lpc82x_inst_init.h"

/**
 * \brief ����˸ LED0
 */
static void flash_led (void)
{
    while (1) {
        am_led_on(0);
        am_mdelay(100);
        am_led_off(0);
        am_mdelay(100);
    }
}

/**
 * \brief �������
 */
void demo_zlg9021_baudrate_entry (am_zlg9021_handle_t zlg9021_handle)
{
    int32_t   i                      = 0;
    uint32_t  zlg9021_baudrate       = 0;
    uint32_t  zlg9021_baudrate_tab[] = {4800, 9600, 19200, 38400, 57600, 115200};

    /* �ȴ�ģ���ʼ�����(ģ���ʼ�����֮��ᷢ�� "TTM:ZLG9021P0-1-TC") */
    am_mdelay(500);

    /* ��������ģ�� */
    for (i = 0; i < AM_NELEMENTS(zlg9021_baudrate_tab); i++) {

        /* ������ ZLG9021 ͨ�ŵĴ��ڵĲ����� */
        am_uart_ioctl(zlg9021_handle->uart_handle,
                      AM_UART_BAUD_SET,
                      (void *)zlg9021_baudrate_tab[i]);

        /* ���Ի�ȡ ZLG9021 �Ĳ����� */
        am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_BAUD_GET,
                         (void *)&zlg9021_baudrate);

        if (zlg9021_baudrate_tab[i] == zlg9021_baudrate) {
            AM_DBG_INFO("ZLG9021 BAUDRATE: %d\r\n", zlg9021_baudrate);
            break;
        }
    }

    if (i == AM_NELEMENTS(zlg9021_baudrate_tab)) {
        AM_DBG_INFO("AM_ZLG9021_BAUD_GET failed\r\n");
        flash_led();
    }

    while (1) {
        am_led_on(0);
        am_mdelay(500);
        am_led_off(0);
        am_mdelay(500);
    }
}

/** [src_zlg9021_baudrate] */

/* end of file */
