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
 * - ʵ������
 *   1. ���ڴ�ӡ��ȡ���ı���ģ���������Ϣ��
 *   2. ZM516X ģ��� 11 ͨ���� 26 ͨ����������ģ�顣�������������ģ�飬��ȡ��ģ��
 *      ���ź�ǿ�Ⱥ�������Ϣ����ͨ�����ڴ�ӡ��
 *   3. ZM516X ģ���ʼ����������ɺ� LED0 ���������ʧ�ܣ�LED0 ��˸��
 *   4. ������ģ���ͨ���ָ�Ϊ����ǰ��ͨ���š�
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
 * \snippet demo_zm516x_search.c src_zm516x_search
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-15  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zm516x_search
 * \copydoc demozm516x_search.c
 */

/** [src_zm516x_search] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"

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

/**
 * \brief ��ӡ ZM516X ģ��Ļ�����Ϣ(ͨ���������� D4 ���)
 */
am_local
void __base_info_print (am_zm516x_base_info_t *p_zm516x_base_info, uint8_t num)
{
    uint8_t i = 0;

    AM_DBG_INFO("\r\n__base_info_print\r\n");

    for (i = 0; i < num; i++) {
        AM_DBG_INFO("dev_mode:%d\r\n"
                    "chan:%d\r\n"
                    "data_rate:%d\r\n"
                    "panid:0x%02x%02x\r\n"
                    "addr:0x%02x%02x\r\n"
                    "state:0x%02x\r\n",
                  ((p_zm516x_base_info + i)->dev_mode[0] << 8) ||
                   (p_zm516x_base_info + i)->dev_mode[1],
                   (p_zm516x_base_info + i)->chan,
                   (p_zm516x_base_info + i)->data_rate,
                   (p_zm516x_base_info + i)->panid[0],
                   (p_zm516x_base_info + i)->panid[1],
                   (p_zm516x_base_info + i)->addr[0],
                   (p_zm516x_base_info + i)->addr[1],
                   (p_zm516x_base_info + i)->state);
        AM_DBG_INFO("\r\n");
    }
}

/**
 * \brief ��ӡ ZM516X Զ��ģ���������Ϣ(ͨ����ȡԶ��������Ϣ D5 ���)
 */
am_local
void __remote_info_print (am_zm516x_remote_info_t *p_zm516x_remote_info)
{
    AM_DBG_INFO("\r\n__remote_info_print\r\n");
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
                p_zm516x_remote_info->cfg_info.dev_name,
                p_zm516x_remote_info->cfg_info.dev_pwd,
                p_zm516x_remote_info->cfg_info.dev_mode,
                p_zm516x_remote_info->cfg_info.chan,
                p_zm516x_remote_info->cfg_info.panid[0],
                p_zm516x_remote_info->cfg_info.panid[1],
                p_zm516x_remote_info->cfg_info.my_addr[0],
                p_zm516x_remote_info->cfg_info.my_addr[1],
                p_zm516x_remote_info->cfg_info.dst_addr[0],
                p_zm516x_remote_info->cfg_info.dst_addr[1],
                p_zm516x_remote_info->cfg_info.power_level,
                p_zm516x_remote_info->cfg_info.retry_num,
                p_zm516x_remote_info->cfg_info.tran_timeout,
                p_zm516x_remote_info->cfg_info.send_mode);

    AM_DBG_INFO("state:0x%02x\r\n"
                "dev_mode:%d\r\n"
                "version:0x%02x%02x\r\n",
                p_zm516x_remote_info->state,
                (p_zm516x_remote_info->dev_mode[0] << 8) ||
                p_zm516x_remote_info->dev_mode[1],
                p_zm516x_remote_info->version[0],
                p_zm516x_remote_info->version[1]);
    AM_DBG_INFO("\r\n");
}

/**
 * \brief �������
 */
void demo_zm516x_search_entry (am_zm516x_handle_t zm516x_handle)
{
    uint8_t                 i              = 0;
    uint8_t                 j              = 0;
    uint8_t                 get_size       = 0;
    uint8_t                 signal         = 0;
    am_zm516x_base_info_t   base_info[5];
    am_zm516x_cfg_info_t    zm516x_cfg_info;
    am_zm516x_remote_info_t remote_info;
    am_zm516x_addr_t        zb_addr;

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

    /* ���ñ��ص�ַ�����ص�ַ������������������ģ���ַ��ͬ */
    uint8_t              src_addr[2] = {0x20, 0x02};

    zm516x_cfg_info.my_addr[0] = src_addr[0];
    zm516x_cfg_info.my_addr[1] = src_addr[1];

    /* �޸� ZigBee ģ���������Ϣ���������D6�������óɹ��踴λ */
    if (am_zm516x_cfg_info_set(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_info_set failed\r\n");
        flash_led();
    }
    /* ���óɹ�����λ ZM516X ģ�飨�������D9�� */
    am_zm516x_reset(zm516x_handle);
    am_mdelay(10);
    __cfg_info_print(&zm516x_cfg_info);

    /* ����Ŀ���ַ */
    zb_addr.p_addr    = zm516x_cfg_info.my_addr;
    zb_addr.addr_size = 2;

    /* ��������ͨ�� */
    for (i = 11; i <= 26; i++) {

        /* ���� ZM516X ģ��ͨ���ţ���ʱ���D1�� */
        if (am_zm516x_channel_set(zm516x_handle, i) != AM_OK) {
            AM_DBG_INFO("am_zm516x_channel_set failed\r\n");
            flash_led();
        }

        /* ��������ģ�飨�������D4�� */
        if (am_zm516x_discover(zm516x_handle,
                               5,
                               base_info,
                              &get_size) != AM_OK) {
            AM_DBG_INFO("channel %d has not found the device\r\n", i);
        } else {
            AM_DBG_INFO("\r\nchannel %d has found %d device\r\n", i, get_size);

            for (j = 0; j < get_size; j++) {
                AM_DBG_INFO("-------------the %d-------------\r\n", j);
                __base_info_print(&base_info[j], 1);

                /* ����Ŀ���ַ */
                zb_addr.p_addr    = base_info[j].addr;
                zb_addr.addr_size = 2;

                /* ��ȡָ����ַ ZM516X ģ����ź�ǿ�ȣ���ʱ���DA�� */
                if (am_zm516x_sigal_get(zm516x_handle,
                                       &zb_addr,
                                       &signal) != AM_OK) {
                    AM_DBG_INFO("failed to get 0x%02x%02x signal\r\n");
                } else {
                    AM_DBG_INFO("signal: %ddBm\r\n", signal / 3 - 95);
                }

                /* ��ȡԶ��������Ϣ���������D5�� */
                if (am_zm516x_remote_info_get(zm516x_handle,
                                             &zb_addr,
                                             &remote_info) != AM_OK) {
                    AM_DBG_INFO("failed to get 0x%02x%02x remote info\r\n",
                                base_info[j].addr[0],
                                base_info[j].addr[1]);
                } else {
                    __remote_info_print(&remote_info);
                }
            }
        }
    }

    AM_DBG_INFO("\r\nsearch complete, recovery the channal to %d\r\n",
                zm516x_cfg_info.chan);

    /* ���� ZigBee ģ��ͨ���ţ��������D2�� */
    if (am_zm516x_cfg_channel_set(zm516x_handle,
                                  zm516x_cfg_info.chan) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_channel_set failed\r\n");
        flash_led();
    }

    /* ������ɣ����� LED0 */
    am_led_on(LED0);

    AM_FOREVER {
        am_mdelay(100);
    }
}
/** [src_zm516x_search] */

/* end of file */
