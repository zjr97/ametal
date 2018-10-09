/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ZM516X ģ���Զ����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��Ƭ���ֱ���ͨ�� 2400��4800��9600��19200��38400��57600 �� 115200 �Ĳ���
 *      ������ ZM516X ģ�飻
 *   2. ������ӳɹ���ͨ�����ڴ�ӡ��ǰ�Ĳ����ʲ��� LED0 ���������� LED0 ��˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_8 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. ZigBee ģ�������ӹ�ϵ���£�
 * <pre>
 *           PIO0_26  <-->  ZigBee_TX
 *           PIO0_27  <-->  ZigBee_RX
 *           PIO0_28  <-->  ZigBee_RST
 * </pre>
 *        �����Ҫʹ�� ZigBee����Щ IO �ڲ�������������;��
 *
 * \par Դ����
 * \snippet demo_zm516x_baudrate.c src_zm516x_baudrate
 *
 * \internal
 * \par Modification history
 * - 1.00 18-04-12  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_zm516x_baudrate
 * \copydoc demo_zm516x_baudrate.c
 */

/** [src_zm516x_baudrate] */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_zm516x.h"
#include "am_vdebug.h"
#include "am_board.h"

/**
 * \brief ��˸ LED0
 */
am_local void flash_led (void)
{
    while (1) {
        am_led_on(LED0);
        am_mdelay(50);

        am_led_off(LED0);
        am_mdelay(500);
    }
}

/**
 * \brief �������
 */
void demo_zm516x_baudrate_entry (am_zm516x_handle_t zm516x_handle)
{
    am_zm516x_cfg_info_t zm516x_cfg_info;
    int32_t              i                     = 0;
    uint32_t             zm516x_baudrate_tab[] = {2400,
                                                  4800,
                                                  9600,
                                                  19200,
                                                  38400,
                                                  57600,
                                                  115200};

    /* �ȴ�ģ���ʼ����� */
    am_mdelay(10);

    /* ��������ģ�� */
    for (i = 0; i < AM_NELEMENTS(zm516x_baudrate_tab); i++) {

        /* ������ ZM516X ͨ�ŵĴ��ڵĲ����� */
        am_uart_ioctl(zm516x_handle->uart_handle->handle,
                      AM_UART_BAUD_SET,
                      (void *)zm516x_baudrate_tab[i]);

        /* ���Ի�ȡ ZM516X ģ���������Ϣ */
        if (am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info) == AM_OK) {
            AM_DBG_INFO("zm516x baudrate is %d\r\n", zm516x_baudrate_tab[i]);
            break;
        }
    }

    if (i == AM_NELEMENTS(zm516x_baudrate_tab)) {
        AM_DBG_INFO("get baudrate failed\r\n");
        flash_led();
    }

    am_led_on(LED0);

    while (1) {
        am_mdelay(1000);
    }
}

/** [src_zm516x_baudrate] */

/* end of file */
