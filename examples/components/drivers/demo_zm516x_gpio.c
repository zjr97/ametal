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
 * \brief ZM516X ģ�� GPIO ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ZM516X ģ���ʼ�������óɹ��� LED0 �����������ʼ��ʧ�ܣ�LED0 ��˸��
 *   2. ���ڴ�ӡ��ȡ����ģ��������Ϣ��
 *   3. ��ȡ IO1(JOIN) ���ŵĵ�ƽ������ͬ�ĵ�ƽ����� IO2(DETECH) ���š�
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
 * \snippet demo_zm516x_gpio.c src_zm516x_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-15  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_zm516x_gpio
 * \copydoc demo_zm516x_gpio.c
 */

/** [src_zm516x_gpio] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include <string.h>

#define    __TEST_CFG_COMMAND    (1)    /**< \brief �Ƿ���������������� */
#define    __TEST_CMD_COMMAND    (1)    /**< \brief �Ƿ������ʱ�������� */

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

#if (__TEST_CFG_COMMAND == 1)

/**
 * \brief ��ӡ PWM ��Ϣ
 */
am_local void __pwm_info_print (am_zm516x_pwm_t *p_pwm_info, uint8_t num)
{
    uint8_t  i    = 0;
    uint32_t temp = 0;

    AM_DBG_INFO("\r\n__pwm_info_print\r\n");
    for (i = 0; i < num; i++) {
        memcpy(&temp, &((p_pwm_info + i)->freq), sizeof(uint32_t));

        AM_DBG_INFO("freq:%d\r\n"
                    "duty_cycle:%d\r\n",
                    temp,
                    (p_pwm_info + i)->duty_cycle);
    }
    AM_DBG_INFO("\r\n");
}
#endif /* (__TEST_CFG_COMMAND == 1) */

/**
 * \brief �������
 */
void demo_zm516x_gpio_entry (am_zm516x_handle_t zm516x_handle)
{
    am_zm516x_cfg_info_t zm516x_cfg_info;
    am_zm516x_addr_t     zb_addr;

#if (__TEST_CFG_COMMAND == 1)
    am_zm516x_pwm_t      pwm[4];
    uint8_t              i              = 0;
    uint8_t              dir            = 0;
    uint16_t             period         = 0;
    am_bool_t            is_dormant     = 0;
    uint32_t             temp           = 0;
#endif /* (__TEST_CFG_COMMAND == 1) */

#if (__TEST_CMD_COMMAND == 1)
    uint8_t              gpio_dir       = 0;
    uint8_t              gpio_value     = 0;
    uint16_t             adc_value      = 0;
#endif /* (__TEST_CMD_COMMAND == 1) */

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

    /* ����Ŀ���ַ */
    zb_addr.p_addr    = zm516x_cfg_info.my_addr;
    zb_addr.addr_size = 2;

#if (__TEST_CFG_COMMAND == 1)
    gpio_dir = 0x05;

    /* ����ָ����ַ ZigBee ģ��� GPIO ������������������E1�� */
    if (am_zm516x_cfg_gpio_dir_set(zm516x_handle,
                                  &zb_addr,
                                   gpio_dir) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_gpio_dir_set failed\r\n");
        flash_led();
    }

    /* ��ȡָ����ַ ZigBee ģ��� GPIO ������������������E1�� */
    if (am_zm516x_cfg_gpio_dir_get(zm516x_handle,
                                  &zb_addr,
                                  &gpio_dir) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_gpio_dir_get failed\r\n");
        flash_led();
    }

    dir = 0x0a;
    period = 100;
    is_dormant = AM_FALSE;

    /* IO/AD �ɼ����ã��������E2�������óɹ��踴λ */
    if (am_zm516x_cfg_io_adc_upload_set(zm516x_handle,
                                       &zb_addr,
                                        dir,
                                        period,
                                        is_dormant) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_io_adc_upload_set failed\r\n");
        flash_led();
    }

    /* ���óɹ�����λ ZM516X ģ�飨�������D9�� */
    am_zm516x_reset(zm516x_handle);
    am_mdelay(10);

    /* IO/AD �ɼ����û�ȡ���������E2�� */
    if (am_zm516x_cfg_io_adc_upload_get(zm516x_handle,
                                       &zb_addr,
                                       &dir,
                                       &period,
                                       &is_dormant) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_io_adc_upload_set failed\r\n");
        flash_led();
    }
    AM_DBG_INFO("io_adc_upload: dir = 0x%02x, period = %d, is_dormant = %s\r\n",
                dir,
                period,
                (is_dormant != AM_FALSE) ? "AM_TRUE" : "AM_FALSE");

    gpio_value = 0x05;

    /* ����ָ����ַ ZigBee ģ��� GPIO ���ֵ���������E3�� */
    if (am_zm516x_cfg_gpio_set(zm516x_handle,
                              &zb_addr,
                               gpio_value) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_gpio_set failed\r\n");
        flash_led();
    }

    /* ��ȡָ����ַ ZigBee ģ��� GPIO ����ֵ���������E3�� */
    if (am_zm516x_cfg_gpio_get(zm516x_handle,
                              &zb_addr,
                              &gpio_value) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_gpio_get failed\r\n");
        flash_led();
    }
    AM_DBG_INFO("gpio_value: 0x%02x\r\n", gpio_value);

    temp = 1000;
    for (i = 0; i < 4; i++) {
        memcpy(&pwm[i].freq, &temp, 4);
        pwm[i].duty_cycle = 50;
    }

    /* ����ָ����ַ ZigBee ģ��� PWM ���ֵ���������E4�� */
    if (am_zm516x_cfg_pwm_set(zm516x_handle,
                             &zb_addr,
                             &pwm[0]) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_pwm_set failed\r\n");
        flash_led();
    }

    /* ��ȡָ����ַ ZigBee ģ��� PWM ���ֵ���ã��������E4�� */
    if (am_zm516x_cfg_pwm_get(zm516x_handle,
                             &zb_addr,
                             &pwm[0]) != AM_OK) {
        AM_DBG_INFO("am_zm516x_cfg_pwm_get failed\r\n");
        flash_led();
    }
    __pwm_info_print(pwm, 4);
#endif /* (__TEST_CFG_COMMAND == 1) */

    AM_DBG_INFO("\r\n");

#if (__TEST_CMD_COMMAND == 1)
    gpio_dir = 0x08;

    /* ����ָ����ַ ZM516X ģ��� GPIO �������������ʱ���D4�� */
    if (am_zm516x_gpio_dir(zm516x_handle,
                          &zb_addr,
                           gpio_dir) != AM_OK) {
        AM_DBG_INFO("am_zm516x_gpio_dir failed\r\n");
        flash_led();
    }

    /* ��ȡָ����ַ ZM516X ģ��� AD ת��ֵ����ʱ���D7�� */
    if (am_zm516x_ad_get(zm516x_handle,
                        &zb_addr,
                         0,
                        &adc_value) != AM_OK) {
        AM_DBG_INFO("am_zm516x_ad_get failed\r\n");
        flash_led();
    }
    AM_DBG_INFO("adc_value: %d voltage: %dmV\r\n",
                adc_value,
                adc_value * 2470 / 1024);
#endif /* (__TEST_CMD_COMMAND == 1) */

    /* ������ɣ����� LED0 */
    am_led_on(LED0);

    AM_FOREVER {

#if (__TEST_CMD_COMMAND == 1)

        /* ��ȡָ����ַ ZM516X ģ��� GPIO ����ֵ����ʱ���D5�� */
        if (am_zm516x_gpio_get(zm516x_handle,
                              &zb_addr,
                              &gpio_value) != AM_OK) {
            AM_DBG_INFO("am_zm516x_gpio_get failed\r\n");
            flash_led();
        }
        AM_DBG_INFO("gpio_value: 0x%02x\r\n", gpio_value);

        /* ����ָ����ַ ZM516X ģ��� GPIO ���ֵ����ʱ���D6�� */
        if (am_zm516x_gpio_set(zm516x_handle,
                              &zb_addr,
                               (gpio_value & 0x04) << 1) != AM_OK) {
            AM_DBG_INFO("am_zm516x_gpio_set failed\r\n");
            flash_led();
        }
#endif /* (__TEST_CMD_COMMAND == 1) */

        am_mdelay(100);
    }
}
/** [src_zm516x_gpio] */

/* end of file */
