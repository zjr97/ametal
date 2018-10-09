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
 * \brief ģ��Ƚ������̣���ѯģʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_1 ����ģ������ 2��
 *   2. PIO0_14 ����ģ������ 3��
 *
 * - ʵ������
 *   1. ���� 2 �������� 3 ʱ�����ڻ�����ȽϽ�� "result: PIO0_1_ACMP_I2 > PIO0_14_ACMP_I3"��
 *   2. ���� 2 С������ 3 ʱ�����ڻ�����ȽϽ�� "result: PIO0_1_ACMP_I2 < PIO0_14_ACMP_I3"��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_acmp_poll.c src_lpc824_hw_acmp_poll
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-05  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_acmp_poll
 * \copydoc demo_lpc824_hw_acmp_poll.c
 */

/** [src_lpc824_hw_acmp_poll] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "hw/amhw_lpc82x_acmp.h"

void demo_lpc824_hw_acmp_poll_entry(amhw_lpc82x_acmp_t *p_hw_acmp,
                                    int                 pin)
{
    amhw_lpc82x_acmp_config(p_hw_acmp,
                            AMHW_LPC82X_ACMP_CTRL_VP_CMP2 | /* ���� 2 Ϊͬ������� */
                            AMHW_LPC82X_ACMP_CTRL_VM_CMP3); /* ���� 3 Ϊ��������� */

    amhw_lpc82x_acmp_ladder_disable(p_hw_acmp);
    AM_FOREVER {

        if (am_gpio_get(pin)) {
            AM_DBG_INFO("result: PIO0_1_ACMP_I2 > PIO0_14_ACMP_I3\r\n");
        } else {
            AM_DBG_INFO("result: PIO0_1_ACMP_I2 < PIO0_14_ACMP_I3\r\n");
        }
        am_mdelay(200);
    }
}

/** [src_lpc824_hw_acmp_poll] */

/* end of file */

