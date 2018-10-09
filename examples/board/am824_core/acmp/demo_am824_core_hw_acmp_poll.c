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
 * \snippet demo_am824_hw_acmp_poll.c src_am824_hw_acmp_poll
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-05  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_acmp_poll
 * \copydoc demo_am824_hw_acmp_poll.c
 */

/** [src_am824_hw_acmp_poll] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "hw/amhw_lpc82x_acmp.h"
#include "demo_nxp_entries.h"

/**
 * \brief ACMP ƽ̨��ʼ������
 */
am_local void __plfm_acmp_init()
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_ACMP);
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_ACMP);

    /* ʹ�ܹܽ�  PIO0_1 Ϊ�Ƚ������� 2 ���ܣ��Ƚ������� 2 �ܽŹ̶�Ϊ PIO0_1�� */
    am_gpio_pin_cfg (PIO0_1, PIO0_1_ACMP_I2);

    /* ʹ�ܹܽ�  PIO0_14 Ϊ�Ƚ������� 3 ���ܣ��Ƚ������� 3 �ܽŹ̶�Ϊ PIO0_14�� */
    am_gpio_pin_cfg (PIO0_14, PIO0_14_ACMP_I3);

    /* ʹ�ܹܽ� PIO0_18 Ϊ�Ƚ���������� */
    am_gpio_pin_cfg (PIO0_18, PIO_FUNC_ACMP_O);
}


/**
 * \brief �������
 */
void demo_am824_core_hw_acmp_poll_entry (void)
{

    am_kprintf("demo am824_core hw acmp poll!\r\n");

    /* ƽ̨��ʼ�� */
    __plfm_acmp_init();

    demo_lpc824_hw_acmp_poll_entry(LPC82X_ACMP, PIO0_18);
}
/** [src_am824_hw_acmp_poll] */

/* end of file */
