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
 * \brief ZM516X ģ����ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ���Ա� Demo ��Ҫʹ������ AM824ZB �壬�������Ҫ���ز�ͬ�ĳ���
 *      ����һ�� AM824ZB ��򿪺� USE_BORD0���رպ� USE_BORD1�����벢���س���
 *      ����һ�� AM824ZB ��򿪺� USE_BORD1���رպ� USE_BORD0�����벢���س���
 *
 * - ʵ������
 *   1. ������ʼ�������óɹ��� LED0 �����������ʼ��ʧ�ܣ�LED0 ��˸��
 *   2. ������� 1S ��Է�����һ�����ݣ����պ����յ��Է����͹��������ݺ󣬵��Դ���
 *      �����յ��������������������Ϊ "received data from 0x****: I'm 0x**"��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_8 ���ƣ�
 *    2. ʹ�ð���������Ҫ�� J14 �� KEY �� PIO0_1 �̽���һ��
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    4. ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE ����Ϊ 1
 *       ���ú��Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *    5. ZigBee ģ�������ӹ�ϵ���£�
 * <pre>
 *           PIO0_26  <-->  ZigBee_TX
 *           PIO0_27  <-->  ZigBee_RX
 *           PIO0_28  <-->  ZigBee_RST
 * </pre>
 *        �����Ҫʹ�� ZigBee����Щ IO �ڲ�������������;��
 *
 * \par Դ����
 * \snippet demo_zm516x.c src_zm516x
 *
 * \internal
 * \par Modification History
 * - 1.01 18-01-16  pea, simplify demo, enable display head
 * - 1.00 17-05-26  mex, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_zm516x
 * \copydoc demo_std_zm516x.c
 */

/** [src_zm516x] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include <string.h>
#include "am_lpc82x_inst_init.h"


#define USE_BORD0            /**< \brief ʹ�øú�ʱ�����������ڵ��� 0 */
//#define USE_BORD1          /**< \brief ʹ�øú�ʱ�����������ڵ��� 1 */

/**
 * \brief ��˸ LED0
 */
static void flash_led (void)
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
void demo_zm516x_entry (am_zm516x_handle_t zm516x_handle)
{
    char                 send_buf[11] = "I'm 0x00\r\n";
    am_zm516x_addr_t     zb_addr;
    int                  ret = 0;

#ifdef USE_BORD0
    uint8_t              src_addr[2] = {0x20, 0x01};
    uint8_t              dst_addr[2] = {0x20, 0x02};
#endif

#ifdef  USE_BORD1
    uint8_t              src_addr[2] = {0x20, 0x02};
    uint8_t              dst_addr[2] = {0x20, 0x01};
#endif

    uint8_t              buf[20] = {0};
    uint32_t             snd_tick = 0;
    am_zm516x_cfg_info_t zm516x_cfg_info;

    AM_DBG_INFO("src_addr: 0x%02x%02x dst_addr: 0x%02x%02x\n",
                src_addr[0],
                src_addr[1],
                dst_addr[0],
                dst_addr[1]);

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

    zm516x_cfg_info.my_addr[0] = src_addr[0];
    zm516x_cfg_info.my_addr[1] = src_addr[1];
    zm516x_cfg_info.dst_addr[0] = dst_addr[0];
    zm516x_cfg_info.dst_addr[1] = dst_addr[1];
    zm516x_cfg_info.panid[0] = 0x10;
    zm516x_cfg_info.panid[1] = 0x01;

    /* �޸� ZigBee ģ���������Ϣ���������D6�������óɹ��踴λ */
    if (am_zm516x_cfg_info_set(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_info_set failed\r\n");
        flash_led();
    }

    /* ʹ ZigBee ģ�鸴λ���������D9�� */
    am_zm516x_reset(zm516x_handle);
    am_mdelay(10);

    /* ����Ŀ���ַ */
    zb_addr.p_addr    = src_addr;
    zb_addr.addr_size = 2;

    /* ���� ZigBee ģ����յ����ݰ���ͷ�Ƿ���ʾԴ��ַ���������DC�� */
    if (am_zm516x_cfg_display_head_set(zm516x_handle,
                                      &zb_addr,
                                       AM_TRUE) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_display_head_set failed\r\n");
        flash_led();
    }

    /* ���óɹ�����λ ZM516X ģ�飨�������D9�� */
    am_zm516x_reset(zm516x_handle);
    am_mdelay(10);

    /* ���� ZM516X ģ����յ����ݰ���ͷ�Ƿ���ʾԴ��ַ����ʱ���D3�� */
    if (am_zm516x_display_head_set(zm516x_handle, AM_TRUE) != AM_OK) {
        AM_DBG_INFO("am_zm516x_display_head_set failed\r\n");
        flash_led();
    }

    /**
     * ���� ZigBee ģ�����˯��ģʽ����ʱ���D8������Ҫ�������ԣ�ZM516X ˯�ߺ�
     * ֻ�ܸ�λģ����ģ��� WAKE ��������������ģ��
     */
//    am_zm516x_enter_sleep(zm516x_handle);

    /* ���в���ͨ�������� LED0 */
    am_led_on(LED0);

    AM_FOREVER {

        if (snd_tick++ > 100) {
            snd_tick = 0;
            send_buf[7] = (src_addr[1] & 0x0F) + '0';
            am_zm516x_send(zm516x_handle, send_buf, strlen(send_buf));
        }

        /* am_zm516x_receive �����Ķ���ʱΪ 10ms */
        ret = am_zm516x_receive(zm516x_handle, buf, sizeof(buf));

        if (ret > 0) {
            AM_DBG_INFO("received data from 0x%02x%02x: %s\r\n",
                        buf[0],
                        buf[1],
                        buf + 2);
            memset(buf, 0x00, sizeof(buf));
        }
    }
}
/** [src_zm516x] */

/* end of file */
