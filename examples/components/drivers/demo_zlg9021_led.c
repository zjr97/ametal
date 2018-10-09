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
 * \brief ����ģ�� LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �ֻ���װ�������������������������ģ�飻
 *   2. ���������������ͨ���ַ�����ʽ��ģ��ֱ��� "on"��"off"��"tog"��
 *
 * - ʵ������
 *   1. ZLG9021 ģ���ʼ�������óɹ��� LED0 �� 500 ms �ļ������˸�������ʼ��ʧ�ܣ�
 *      LED0 �� 100 ms �ļ������˸��
 *   2. �������ӳɹ���LED0 Ϩ��
 *   3. ���յ� "on"��"off"��"tog" �ַ���ʱ���ֱ������Ϩ�𡢷�ת LED0�������ֻ��˷�
 *      �� "ok!"��
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
 *    5. �������� APP ������ http://www.zlg.cn/wireless/down/down/id/199.html ҳ��
 *       �����ص��ֻ�͸�� APP ����Դ���н�ѹ�õ���
 *    6. ����ģ��Ĭ�ϲ�����Ϊ 9600���û������� am_hwconf_zlg9021.h �����á�����û�
 *       ����ȷ�����п��������������ʣ����Գ���ʹ�� demo_zlg9021_baudrate
 *       �����Զ���������ģ�鲨���ʡ�
 *
 * \par Դ����
 * \snippet demo_zlg9021_led.c src_zlg9021_led
 *
 * \internal
 * \par Modification history
 * - 1.00 17-12-08  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg9021_led
 * \copydoc demo_zlg9021_led.c
 */

/** [src_zlg9021_led] */
#include "ametal.h"
#include "am_zlg9021.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_led.h"
#include "string.h"

/** \brief �������ӱ�־ */
#define __ZLG9021_STATE_BLE_CONNECTED     1

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
void demo_zlg9021_led_entry (am_zlg9021_handle_t zlg9021_handle)
{
    uint8_t             buf[4]                 = {0};
    char                zlg9021_name[15]       = {0};
    char                zlg9021_mac_addr[13]   = {0};
    char                zlg9021_pwd[13]        = {0};
    int32_t             zlg9021_tx_power       = 0;
    uint32_t            zlg9021_ble_adv_period = 0;
    uint32_t            zlg9021_version        = 0;
    am_bool_t           zlg9021_enc            = 0;

    /* �ȴ�ģ���ʼ�����(ģ���ʼ�����֮��ᷢ�� "TTM:ZLG9021P0-1-TC") */
    am_mdelay(500);

    /* ���ý��ճ�ʱʱ��(��λ��ms) */
    if (am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_TIMEOUT,
                         (void *)100) != AM_OK) {
        AM_DBG_INFO("AM_ZLG9021_TIMEOUT failed\r\n");
        flash_led();
    }

    /* ��ȡģ���� */
    if (am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_NAME_GET,
                         (void *)zlg9021_name) != AM_OK) {
         AM_DBG_INFO("AM_ZLG9021_NAME_GET failed\r\n");
         flash_led();
     }

    /* ��ȡ MAC ��ַ */
    if (am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_MAC_GET,
                         (void *)zlg9021_mac_addr) != AM_OK) {
         AM_DBG_INFO("AM_ZLG9021_MAC_GET failed\r\n");
         flash_led();
     }

    /* ��ȡ BLE �Ĺ㲥����(��λ: ms) */
    if (am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_BLE_ADV_PERIOD_GET,
                         (void *)&zlg9021_ble_adv_period) != AM_OK) {
         AM_DBG_INFO("AM_ZLG9021_MAC_GET failed\r\n");
         flash_led();
     }

    /* ��ȡ���͹���(dBm) */
    if (am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_TX_POWER_GET,
                         (void *)&zlg9021_tx_power) != AM_OK) {
         AM_DBG_INFO("AM_ZLG9021_TX_POWER_GET failed\r\n");
         flash_led();
     }

    /* ��ȡ�̼��汾�� */
    if (am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_VERSION_GET,
                         (void *)&zlg9021_version) != AM_OK) {
         AM_DBG_INFO("AM_ZLG9021_VERSION_GET failed\r\n");
         flash_led();
     }

    /* ��ȡģ�������� */
    if (am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_PWD_GET,
                         (void *)&zlg9021_pwd) != AM_OK) {
         AM_DBG_INFO("AM_ZLG9021_PWD_GET failed\r\n");
         flash_led();
     }

    /* ��ȡģ��ļ���״̬ */
    if (am_zlg9021_ioctl(zlg9021_handle,
                         AM_ZLG9021_ENC_GET,
                         (void *)&zlg9021_enc) != AM_OK) {
         AM_DBG_INFO("AM_ZLG9021_ENC_GET failed\r\n");
         flash_led();
     }

    AM_DBG_INFO("\r\nzlg9021_name: %s\r\n"
                "zlg9021_mac_addr: %s\r\n"
                "zlg9021_pwd: %s\r\n"
                "zlg9021_tx_power: %d\r\n"
                "zlg9021_ble_adv_period: %d\r\n"
                "zlg9021_version: %d\r\n"
                "zlg9021_enc: %d\r\n",
                zlg9021_name,
                zlg9021_mac_addr,
                zlg9021_pwd,
                zlg9021_tx_power,
                zlg9021_ble_adv_period,
                zlg9021_version,
                zlg9021_enc);

    while (1) {

        if (zlg9021_handle->connect_state == __ZLG9021_STATE_BLE_CONNECTED) {

            memset(buf, '\0', 4);
            if ( am_zlg9021_recv(zlg9021_handle, buf, 3) > 0) {
                AM_DBG_INFO("zlg9021_recv:%s\r\n", buf);
            }

            if (strcmp((char *)buf, "on") == 0) {
                am_led_on(0);
                am_zlg9021_send(zlg9021_handle, (uint8_t *)"ok!", 3);
            }

            if (strcmp((char *)buf, "off") == 0) {
                am_led_off(0);
                am_zlg9021_send(zlg9021_handle, (uint8_t *)"ok!", 3);
            }

            if (strcmp((char *)buf, "tog") == 0) {
                am_led_toggle(0);
                am_zlg9021_send(zlg9021_handle, (uint8_t *)"ok!", 3);
            }
        } else {
            am_led_on(0);
            am_mdelay(500);
            am_led_off(0);
            am_mdelay(500);
        }
    }
}

/** [src_zlg9021_led] */

/* end of file */
