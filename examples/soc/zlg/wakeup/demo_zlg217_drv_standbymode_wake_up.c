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
 * \brief ����ģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * - �������裺
 *   1. �ϵ�ǰ�� WAKE_UP(PIOA_0) ���ӵ��͵�ƽ��
 *   2. �ȴ� MCU �������ģʽ��
 *   3. �� PIOA_0 ���ӵ��ߵ�ƽ��ʹ PIOA_0 �ϲ��������ػ��� MCU��
 *
 * - ʵ������
 *   1. �ɹ��������ģʽʱ���������"enter standby!"���� J-Link ���ԶϿ���
 *      ���򴮿����"WAKE_UP(PIOA_0) must be low!"��
 *   2. PIOA_0 ���������غ�MCU ��λ���С�
 *
 * \note
 *    ֻ���� WAKE_UP(PIOA_0) Ϊ�͵�ƽ��ʱ����ܽ������ģʽ
 *
 * \par Դ����
 * \snippet demo_zlg217_drv_standbymode_wake_up.c src_zlg217_drv_standbymode_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_drv_standbymode_wake_up
 * \copydoc demo_zlg217_drv_standbymode_wake_up.c
 */
 
/** [src_zlg217_drv_standbymode_wake_up] */
#include "ametal.h"
#include "am_board.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "zlg217_pin.h"
#include "am_zlg217_pwr.h"
#include "am_zlg217_inst_init.h"

/**
 * \brief ��˸ LED0
 */
am_local void __led_flash (void)
{
    while (1) {
        am_led_on(LED0);
        am_mdelay(500);
        am_led_off(LED0);
        am_mdelay(500);
    }
}

/**
 * \brief �������
 */
void demo_zlg217_drv_standbymode_wake_up_entry (void)
{
    uint32_t i = 0;

    AM_DBG_INFO("low power test!\r\n");

    am_zlg217_pwr_inst_init();

    /* �������� */
    am_zlg217_wake_up_cfg(AM_ZLG217_PWR_MODE_STANBY, NULL, NULL);

    for (i = 0; i < 5; i++) {
        am_mdelay(1000);
    }

    /* �������ģʽ */
    if (am_zlg217_pwr_mode_into(AM_ZLG217_PWR_MODE_STANBY) != AM_OK) {

        /* ֻ���� WAKE_UP(PIOA_0) Ϊ�͵�ƽ��ʱ����ܽ������ģʽ */
        AM_DBG_INFO("WAKE_UP(PIOA_0) must be low!\r\n");
        __led_flash();
    }

    /* ��Ӧ��ִ�е������Ϊ����ģʽ����֮��оƬ��ֱ�Ӹ�λ */
    AM_DBG_INFO("error!\r\n");

    __led_flash();
}

/** [src_zlg217_drv_standbymode_wake_up] */

/* end of file */
