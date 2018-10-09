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
 * \brief ģ��Ƚ������̣���ѹ���ݣ���ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_14 ����ģ������ 3��
 *   2. PIO0_6 ��ѹ��Ϊ���ݵ�ѹ��Դ����ʵ��� 3.3V ��ѹ���� VDDCMP = 3.3V��
 *
 * - ʵ������
 *   1. ���� 3 ���� 1703mV ʱ�����ڻ�����ȽϽ�� "result: PIO0_14_ACMP_I3 > PIO0_6_ACMP_LAD(1703mV)"��
 *   1. ���� 3 С�� 1703mV ʱ�����ڻ�����ȽϽ�� "result: PIO0_14_ACMP_I3 < PIO0_6_ACMP_LAD(1703mV)"��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_acmp_lad.c src_lpc824_hw_acmp_lad
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-05  hgo, modified
 * - 1.00 15-07-21  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_acmp_lad
 * \copydoc demo_lpc82x_h4_acmp_lad.c
 */

/** [src_lpc824_hw_acmp_lad] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "hw/amhw_lpc82x_acmp.h"


void demo_lpc824_hw_acmp_lad_entry (amhw_lpc82x_acmp_t *p_hw_acmp, int pin)
{
    
    amhw_lpc82x_acmp_config(p_hw_acmp,

                            /* ѡ������ 2 ͨ��Ϊͬ������� */
                            AMHW_LPC82X_ACMP_CTRL_VP_CMP3 |

                            /* ѡ����ݵ�ѹΪ��������� */
                            AMHW_LPC82X_ACMP_CTRL_VM_LADOUT);

        /* ʹ�ܽ��ݵ�ѹ���� */
    amhw_lpc82x_acmp_ladder_enable(p_hw_acmp);

    /* ѡ��Ƚ�����Դ VDDCMP */
    amhw_lpc82x_acmp_ladref_set(p_hw_acmp,
                                AMHW_LPC82X_ACMP_LADDER_VDDCMP);

    /* ���ݵ�ѹ���� Vol = VDDCMP * value / 31 = 3300mV * 16 / 31 = 1703mV */
    amhw_lpc82x_acmp_ladsel_set(p_hw_acmp, 16);
  
    AM_FOREVER {
        if (am_gpio_get(pin)) {
            AM_DBG_INFO("result: PIO0_14_ACMP_I3 > PIO0_6_ACMP_LAD(1703mV)\r\n");
        } else {
            AM_DBG_INFO("result: PIO0_14_ACMP_I3 < PIO0_6_ACMP_LAD(1703mV)\r\n");
        }

        am_mdelay(200);
    }
}


/** [src_lpc824_hw_acmp_lad] */

/* end of file */

