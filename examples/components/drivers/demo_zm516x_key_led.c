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
 * \brief ZM516X ģ�� KEY LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ���Ա� Demo ��Ҫʹ������ AM824ZB �壬�������Ҫ���ز�ͬ�ĳ���
 *      ����һ�� AM824ZB ��򿪺� USE_BORD0���رպ� USE_BORD1�����벢���س���
 *      ����һ�� AM824ZB ��򿪺� USE_BORD1���رպ� USE_BORD0�����벢���س���
 *
 * - ʵ������
 *   1. ZM516X ģ���ʼ�������óɹ��� LED0 �����������ʼ��ʧ�ܣ�LED0 ��˸��
 *   2. ���� KEY/RST ������Է����� key_code��������ͳɹ�����ͨ�����ڴ�ӡ
 *      "send key code xx success"�������ʧ�ܣ���ͨ�����ڴ�ӡ
 *      "send key code xx failed"���Է����յ�֮�󣬷�ת LED1����ͨ������
 *      ��ӡ "received key code: xx"��
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
 * \snippet demo_zm516x_key_led.c src_zm516x_key_led
 *
 * \internal
 * \par Modification History
 * - 1.01 18-01-16  pea, use the send API with the ACK
 * - 1.00 17-09-20  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc82x_std_zm516x_key_led
 * \copydoc demo_lpc82x_std_zm516x_key_led.c
 */

/** [src_zm516x_key_led] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_rngbuf.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_input.h"
#include "am_board.h"
#include <string.h>

//#define USE_BORD0                /**< \brief ʹ�øú�ʱ�����������ڵ��� 0 */
#define USE_BORD1              /**< \brief ʹ�øú�ʱ�����������ڵ��� 1 */

#define __MAX_KEY_BUF_SIZE   4   /**< \brief ������������ܱ�����ٴΰ������� */

/** \brief �������λ������ṹ */
am_local struct am_rngbuf __g_key_rngbuf;

/** \brief �������λ����������ɴ�� __MAX_KEY_BUF_SIZE ����ֵ */
am_local char             __g_key_buf[sizeof(int) * __MAX_KEY_BUF_SIZE + 1];

/** \brief ���ջ��λ������ṹ */
am_local struct am_rngbuf __g_recv_rngbuf;

/** \brief ���ջ��λ����������ɴ�� __MAX_KEY_BUF_SIZE ����ֵ */
am_local char             __g_recv_buf0[sizeof(int) * __MAX_KEY_BUF_SIZE + 1];
am_local char             __g_recv_buf1[sizeof(int) * __MAX_KEY_BUF_SIZE];

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
 * \brief �����ص���������
 *
 * \param[in] p_usr_data �û����ݣ�ע��ʱ�趨���û�����
 * \param[in] key_code   ��������
 * \param[in] key_state  ����״̬��AM_INPUT_KEY_STATE_PRESSED
 *
 * \return ��
 */
am_local void __input_key_proc (void *p_arg, int key_code, int key_state)
{
    if (key_code == KEY_KP0) {
        if (key_state == AM_INPUT_KEY_STATE_PRESSED) {

            /* �жϰ����������Ƿ��� */
            if (am_rngbuf_freebytes(&__g_key_rngbuf) >= sizeof(key_code)) {
                am_rngbuf_put(&__g_key_rngbuf,
                               (const char *)&key_code,
                               sizeof(key_code));
            }
        }
    }
}

/**
 * \brief ������ʼ��
 */
am_local void __key_init (void)
{
    am_local am_input_key_handler_t key_handler;

    am_input_key_handler_register(&key_handler, __input_key_proc, NULL);
}

/**
 * \brief �������
 */
void demo_zm516x_key_led_entry (am_zm516x_handle_t zm516x_handle)
{

#ifdef USE_BORD0
    uint8_t              src_addr[2] = {0x20, 0x01};
    uint8_t              dst_addr[2] = {0x20, 0x02};
#endif

#ifdef  USE_BORD1
    uint8_t              src_addr[2] = {0x20, 0x02};
    uint8_t              dst_addr[2] = {0x20, 0x01};
#endif

    int                  ret = 0;
    int                  key_code;

    am_zm516x_addr_t     zb_addr;
    am_zm516x_cfg_info_t zm516x_cfg_info;

    AM_DBG_INFO("src_addr: 0x%02x%02x dst_addr: 0x%02x%02x\n",
                src_addr[0],
                src_addr[1],
                dst_addr[0],
                dst_addr[1]);

    /* ��ʼ������ */
    __key_init();

    /* ��ʼ�����λ����� */
    am_rngbuf_init(&__g_key_rngbuf, __g_key_buf, sizeof(__g_key_buf));
    am_rngbuf_init(&__g_recv_rngbuf, __g_recv_buf0, sizeof(__g_recv_buf0));

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

    /* ���� ZigBee ģ��ͨ���ţ���ʱ���D1�� */
    if (am_zm516x_channel_set(zm516x_handle, 25) != AM_OK) {
        AM_DBG_INFO("am_zm516x_channel_set failed\r\n");
        flash_led();
    }

    /* ���� ZigBee ģ��Ŀ���ַ����ʱ���D2�� */
    zb_addr.p_addr    = dst_addr;
    zb_addr.addr_size = sizeof(dst_addr);
    if (am_zm516x_dest_addr_set(zm516x_handle, &zb_addr) != AM_OK) {
        AM_DBG_INFO("am_zm516x_dest_addr_set failed\r\n");
        flash_led();
    }

    /* ���� ZigBee ģ����յ����ݰ���ͷ�Ƿ���ʾԴ��ַ����ʱ���D3�� */
    if (am_zm516x_display_head_set(zm516x_handle, AM_FALSE) != AM_OK) {
    	AM_DBG_INFO("am_zm516x_display_head_set failed\r\n");
        flash_led();
    }

    /* ���� ZigBee ģ���ͨѶģʽ����ʱ���D9�� */
    if (am_zm516x_mode_set(zm516x_handle, AM_ZM516X_COMM_UNICAST) != AM_OK) {
        AM_DBG_INFO("am_zm516x_mode_set failed\r\n");
        flash_led();
    }

    /* ��ȡ ZigBee ģ���������Ϣ���������D1�� */
    if (am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_info_get failed\r\n");
        flash_led();
    }

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
                zm516x_cfg_info.dev_name,
                zm516x_cfg_info.dev_pwd,
                zm516x_cfg_info.dev_mode,
                zm516x_cfg_info.chan,
                zm516x_cfg_info.panid[0],
                zm516x_cfg_info.panid[1],
                zm516x_cfg_info.my_addr[0],
                zm516x_cfg_info.my_addr[1],
                zm516x_cfg_info.dst_addr[0],
                zm516x_cfg_info.dst_addr[1],
                zm516x_cfg_info.power_level,
                zm516x_cfg_info.retry_num,
                zm516x_cfg_info.tran_timeout,
                zm516x_cfg_info.send_mode);

    /*  ������ɣ����� LED0 */
    am_led_on(LED0);

    AM_FOREVER {

        /* �жϰ������������Ƿ��а������� */
        if (am_rngbuf_nbytes(&__g_key_rngbuf) >= sizeof(int)) {

            /* �Ӱ����������л�ȡ��ֵ */
            am_rngbuf_get(&__g_key_rngbuf,
                           (char *)&key_code,
                           sizeof(key_code));

            /* ���ͼ�ֵ */
            if (am_zm516x_send_with_ack(zm516x_handle,
                                       &key_code,
                                        sizeof(key_code)) != sizeof(key_code)) {
                AM_DBG_INFO("send key code %d failed\r\n", key_code);

            } else {
                AM_DBG_INFO("send key code %d success\r\n", key_code);
            }
        }

        /*  am_zm516x_receive�����Ķ���ʱΪ10ms */
        ret = am_zm516x_receive(zm516x_handle,
                                __g_recv_buf1,
                                sizeof(__g_recv_buf1));
        if (ret > 0) {

            /* �жϽ��ջ������Ƿ��� */
            if (am_rngbuf_freebytes(&__g_key_rngbuf) >= sizeof(key_code)) {
                am_rngbuf_put(&__g_recv_rngbuf,
                               __g_recv_buf1,
                               ret);
            }

            /* �жϽ��ջ��������Ƿ��а������� */
            if (am_rngbuf_nbytes(&__g_recv_rngbuf) >= sizeof(int)) {

                /* �ӽ��ջ������л�ȡ��ֵ */
                am_rngbuf_get(&__g_recv_rngbuf,
                               (char *)&key_code,
                               sizeof(key_code));

                am_led_toggle(LED1);
                AM_DBG_INFO("received key code: %d\r\n", key_code);
            }
        }
    }
}
/** [src_zm516x_key_led] */

/* end of file */
