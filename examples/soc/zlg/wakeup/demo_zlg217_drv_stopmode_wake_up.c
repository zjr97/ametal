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
 * \brief ֹͣģʽ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. MCU ����ֹͣģʽʱ�� J-Link ���ԶϿ���
 *   2. ���� KEY/RES ������ MCU��������� wake_up������������С�
 *
 * \par Դ����
 * \snippet demo_zlg217_drv_stopmode_wake_up.c src_zlg217_drv_stopmode_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_drv_stopmode_wake_up
 * \copydoc demo_zlg217_drv_stopmode_wake_up.c
 */

/** [src_zlg217_drv_stopmode_wake_up] */
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
 * \brief �����жϷ�����
 */
static void gpio_isr (void *p_arg)
{
    ;
}

/**
 * \brief �������
 */
void demo_zlg217_drv_stopmode_wake_up_entry (void)
{
    uint32_t i = 0;

    AM_DBG_INFO("low power test!\r\n");

    am_zlg217_pwr_inst_init();

    /* �������� */
    am_zlg217_wake_up_cfg(AM_ZLG217_PWR_MODE_STOP, gpio_isr, (void *)0);

    for (i = 0; i < 5; i++) {
        am_mdelay(1000);
    }

    /* ����ͣ��ģʽ */
    am_zlg217_pwr_mode_into(AM_ZLG217_PWR_MODE_STOP);

    AM_DBG_INFO("wake_up!\r\n");

    while (1) {

        /* ָʾ��ָʾʱ���Ƿ�ָ����� */
        am_led_on(LED0);
        am_mdelay(500);
        am_led_off(LED0);
        am_mdelay(500);

    }
}
/** [src_zlg217_drv_stopmode_wake_up] */

/* end of file */
