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
 * \brief ZM516X ģ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ���Ա� Demo ������Ҫʹ������ AM824ZB �壬����ֻ���� 1 �����ӻ������ж����
 *      �����ʹӻ���Ҫ���ز�ͬ�ĳ���
 *      ��Ϊ�����Ŀ�����򿪺� MASTER_BORD_USE���رպ� SLAVE_BORD_USE�����벢���أ�
 *      ��Ϊ�ӻ��Ŀ�����򿪺� SLAVE_BORD_USE���رպ� MASTER_BORD_USE�����벢���أ�
 *   2. ���ӻ��� JOIN ����ñ�̽� 3 �����£�ʹ�ӻ�������������׶Σ�
 *   3. ���������� KEY/RES ������ʹ�������� __JOIN_TIME �������ģʽ��
 *   4. �ȴ������˳�����ģʽ�󣬰��´ӻ��� KEY/RES ������
 *
 * - ʵ������
 *   1. ��� ZM516X ģ���ʼ��������ʧ�ܣ�LED0 ��˸��
 *   2. ���ڴ�ӡ��ȡ���ı���ģ��������Ϣ��
 *   3. ���ڴ�ӡ��ʾ��Ϣ��
 *   4. ������ӡ�ӻ��б���ӻ���Ϣ��
 *   5. ������ӻ����� "I'am Master\r\n";
 *   5. �ӻ����������� "I'am Slave x\r\n"������ x Ϊ�ӻ������ַ;
 *   3. �����ʹӻ��ֱ�ͨ�����Դ��ڴ�ӡ���յ������ݡ�
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
 * \snippet demo_zm516x_network.c src_zm516x_network
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-15  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zm516x_network
 * \copydoc demo_zm516x_network.c
 */

/** [src_zm516x_network] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"
#include <stdio.h>

#define MASTER_BORD_USE    /**< \brief ʹ�øú�ʱ���������������� */
//#define SLAVE_BORD_USE     /**< \brief ʹ�øú�ʱ�����������ڴӻ� */

#ifdef MASTER_BORD_USE
#define __TYPE       0     /**< \brief ����ʱΪ���� */
#else
#define __TYPE       1     /**< \brief ����ʱΪ�ӻ� */
#endif

#define __JOIN_TIME  3     /**< \brief ��������ӻ����������ʱ��(��λΪ��) */

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
 * \brief ��ӡ ZM516X ģ���������Ϣ
 */
am_local void __cfg_info_print (am_zm516x_cfg_info_t *p_zm516x_cfg_info)
{
    AM_DBG_INFO("\r\n__cfg_info_print\r\n");
    AM_DBG_INFO("dev_name:%s\r\n"
                "dev_pwd:%s\r\n"
                "dev_mode:%d\r\n"
                "chan:%d\r\n"
                "panid:0x%02x%02x\r\n"
                "my_addr:0x%02x%02x\r\n"
                "dst_addr:0x%02x%02x\r\n"
                "power_level:%d\r\n"
                "retry_num:%d\r\n"
                "tran_timeout:%d\r\n"
                "send_mode:%d\r\n",
                p_zm516x_cfg_info->dev_name,
                p_zm516x_cfg_info->dev_pwd,
                p_zm516x_cfg_info->dev_mode,
                p_zm516x_cfg_info->chan,
                p_zm516x_cfg_info->panid[0],
                p_zm516x_cfg_info->panid[1],
                p_zm516x_cfg_info->my_addr[0],
                p_zm516x_cfg_info->my_addr[1],
                p_zm516x_cfg_info->dst_addr[0],
                p_zm516x_cfg_info->dst_addr[1],
                p_zm516x_cfg_info->power_level,
                p_zm516x_cfg_info->retry_num,
                p_zm516x_cfg_info->tran_timeout,
                p_zm516x_cfg_info->send_mode);
    AM_DBG_INFO("\r\n");
}

#ifdef MASTER_BORD_USE

/**
 * \brief ��ӡ ZM516X �ӻ�ģ����Ϣ(ͨ����ѯ����ģ��洢�Ĵӻ���Ϣ���� E7 ���)
 */
am_local void __slave_info_print (am_zm516x_slave_info_t *p_zm516x_slave_info)
{
    AM_DBG_INFO("\r\n__slave_info_print\r\n");
    AM_DBG_INFO("mac: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n"
                "addr:0x%02x%02x\r\n",
                p_zm516x_slave_info->mac[0],
                p_zm516x_slave_info->mac[1],
                p_zm516x_slave_info->mac[2],
                p_zm516x_slave_info->mac[3],
                p_zm516x_slave_info->mac[4],
                p_zm516x_slave_info->mac[5],
                p_zm516x_slave_info->mac[6],
                p_zm516x_slave_info->mac[7],
                p_zm516x_slave_info->addr[0],
                p_zm516x_slave_info->addr[1]);
}
#endif /* MASTER_BORD_USE */

/**
 * \brief �������
 */
void demo_zm516x_network_entry (am_zm516x_handle_t zm516x_handle)
{
    char                   recv_buf[21]   = {0};
    uint8_t                state          = 0;
    uint8_t                response_state = 0;
    am_zm516x_cfg_info_t   zm516x_cfg_info;

#ifdef MASTER_BORD_USE
    uint8_t                i              = 0;
    uint8_t                get_size       = 0;
    am_zm516x_addr_t       zb_addr;
    am_zm516x_slave_info_t slave_info[5];
#else
    char                   send_buf[21]   = {0};
#endif /* MASTER_BORD_USE */

    /* �ָ� ZM516X ģ��������ã��������DA�������óɹ��踴λ */
    if (am_zm516x_default_set(zm516x_handle) != AM_OK) {
        AM_DBG_INFO("am_zm516x_default_set failed\r\n");
        flash_led();
    }

    /* ���óɹ�����λ ZM516X ģ�飨�������D9�� */
    am_zm516x_reset(zm516x_handle);
    am_mdelay(10);

    /* ��ȡ ZigBee ģ���������Ϣ���������D1�� */
    if (am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_info_get failed\r\n");
        flash_led();
    }
    __cfg_info_print(&zm516x_cfg_info);

    /* �������������ܣ��������E5�������óɹ��踴λ */
    if (am_zm516x_cfg_network_set(zm516x_handle,
                                  1,
                                  __TYPE) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_network_set failed\r\n");
        flash_led();
    }
    am_mdelay(500);

    /* ���óɹ�����λ ZM516X ģ�飨�������D9�� */
    am_zm516x_reset(zm516x_handle);
    am_mdelay(10);

#ifdef MASTER_BORD_USE

    AM_DBG_INFO("Pressed KEY/RES To Enable JOIN %d Seconds!\r\n", __JOIN_TIME);
    while(am_gpio_get(PIO0_1) != 0);

    /* ��������ӻ��������磨�������E6�� */
    if (am_zm516x_cfg_join_enable(zm516x_handle,
                                  __JOIN_TIME) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_join_enable failed\r\n");
        flash_led();
    }

    AM_DBG_INFO("please wait %d seconds!\r\n", __JOIN_TIME);
    am_mdelay(__JOIN_TIME * 1000);

    /* ��ѯ����ģ��洢�Ĵӻ���Ϣ���������E7�� */
    if (am_zm516x_cfg_slave_get(zm516x_handle,
                                5,
                               &slave_info[0],
                               &get_size) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_slave_get failed\r\n");
        flash_led();
    } else {
        AM_DBG_INFO("slave number is %d\r\n", get_size);
        for (i = 0; i < get_size; i++) {
            AM_DBG_INFO("-------------the %d-------------\r\n", i);
            __slave_info_print(&slave_info[i]);
        }
    }
#else

    AM_DBG_INFO("Please short JOIN pin less than 3 seconds,"
                "waiting to join the network press the KEY/RES to continue!\r\n");
    while(am_gpio_get(PIO0_1) != 0);
#endif /* MASTER_BORD_USE */

    /* ��ѯ���ӻ�״̬���������E8�� */
    if (am_zm516x_cfg_state_get(zm516x_handle,
                               &state,
                               &response_state) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_state_get failed\r\n");
        flash_led();
    }

    AM_DBG_INFO("state: %d, response_state: %d\r\n", state, response_state);

    /* ��ȡ ZigBee ģ���������Ϣ���������D1�� */
    if (am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_info_get failed\r\n");
        flash_led();
    }
    __cfg_info_print(&zm516x_cfg_info);

    /* ������ɣ����� LED0 */
    am_led_on(LED0);

    AM_FOREVER {

#ifdef MASTER_BORD_USE
        if (am_rngbuf_nbytes(&zm516x_handle->uart_rngbuf_dev.rx_rngbuf)
                                                                    >= 20) {
            if (am_zm516x_receive(zm516x_handle, recv_buf, 20) > 0) {
                AM_DBG_INFO(recv_buf);
            }
        }

        for (i = 0; i < get_size; i++) {

            /* ����Ŀ���ַ */
            zb_addr.p_addr    = slave_info[i].addr;
            zb_addr.addr_size = 2;

            /* ���� ZM516X ģ��Ŀ���ַ����ʱ���D2�� */
            if (am_zm516x_dest_addr_set(zm516x_handle,
                                       &zb_addr) != AM_OK) {
                AM_DBG_INFO("am_zm516x_dest_addr_set failed\r\n");
                continue;
            }

            am_zm516x_send(zm516x_handle, "I'am Master\r\n", 14);
        }
#else
        if (am_rngbuf_nbytes(&zm516x_handle->uart_rngbuf_dev.rx_rngbuf) >= 14) {
            if (am_zm516x_receive(zm516x_handle, recv_buf, 14) > 0) {
                AM_DBG_INFO(recv_buf);
            }
        }

        sprintf(send_buf,
                "I'am Slave 0x%02x%02x\r\n",
                zm516x_cfg_info.my_addr[0],
                zm516x_cfg_info.my_addr[1]);
        am_zm516x_send(zm516x_handle, send_buf, 20);
#endif /* MASTER_BORD_USE */

        am_mdelay(500);
    }
}
/** [src_zm516x_network] */

/* end of file */
