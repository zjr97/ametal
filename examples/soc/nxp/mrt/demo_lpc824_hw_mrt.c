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
 * \brief ��Ƶ�ʶ�ʱ����MRT�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ����˸��
 *   2. PIO0_17 ���ŵ������ƽ״̬�� 8KHz ��Ƶ�ʱ任������ 4KHz �Ĳ��Ρ�
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� MRT Ĭ����Ϊϵͳ1�δ�ʹ�ã�ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_SOFTIMER_ENABLE�� AM_CFG_SYSTEM_TICK_ENABLE �Լ�
 *       AM_CFG_KEY_GPIO_ENABLE ����Ϊ 0����ʹ�������ʱ����ϵͳ��ડ����ض���������
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_mrt.c src_lpc824_hw_mrt
 *
 * \internal
 * \par History
 *
 * - 1.01 15-12-02  mem ,modified
 * - 1.00 15-07-15  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_mrt
 * \copydoc demo_lpc824_hw_mrt.c
 */

/** [src_lpc824_hw_mrt] */
#include "ametal.h"
#include "am_led.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_clk.h"
#include "hw/amhw_lpc_mrt.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \brief MRT �жϷ�����
  */
am_local void __mrt_irq_handler (void *p_arg)
{
    amhw_lpc_mrt_t *p_hw_mrt = (amhw_lpc_mrt_t *)p_arg;
    /* ͨ�� 0 �жϴ��� */
    if (amhw_lpc_mrt_chan_pending_chk(p_hw_mrt, AMHW_LPC_MRT_CH(0))
                                                                  == AM_TRUE) {
        am_gpio_toggle(PIO0_17);

        /* ���жϹ����־ */
        amhw_lpc_mrt_int_pending_clr(p_hw_mrt, AMHW_LPC_MRT_CH(0));
    }

    /* ͨ�� 1 �жϴ��� */
    if (amhw_lpc_mrt_chan_pending_chk(p_hw_mrt, AMHW_LPC_MRT_CH(1))
                                                                  == AM_TRUE) {
        am_led_toggle(LED0);

        /* �����Ҫ�ٴβ����жϣ�one-shot ģʽӦ���ٴμ����ж�ֵ */
        amhw_lpc_mrt_intval_set(p_hw_mrt,
                                AMHW_LPC_MRT_CH(1),
                                amhw_lpc82x_clk_system_clkrate_get() / 10,
                                AM_TRUE);

        /* ���жϹ����־ */
        amhw_lpc_mrt_int_pending_clr(p_hw_mrt, AMHW_LPC_MRT_CH(1));
    }
}

/**
 * \brief �������
 */
void demo_lpc824_hw_mrt_entry (amhw_lpc_mrt_t *p_hw_mrt, int inum)
{
    uint32_t ticks = 0;

    /* ��������ͨ�����ж� */
    amhw_lpc_mrt_int_disable(p_hw_mrt, AMHW_LPC_MRT_CH(0));
    amhw_lpc_mrt_int_disable(p_hw_mrt, AMHW_LPC_MRT_CH(1));
    amhw_lpc_mrt_int_disable(p_hw_mrt, AMHW_LPC_MRT_CH(2));
    amhw_lpc_mrt_int_disable(p_hw_mrt, AMHW_LPC_MRT_CH(3));

    am_int_connect(inum, __mrt_irq_handler, (void *)p_hw_mrt);
    am_int_enable(inum);

    /**
     * ͨ�� 0 Ϊ AMHW_LPC_MRT_MODE_REPEAT ģʽ���ж�Ƶ��Ϊ 8KHz��
     * ����ж�ֵΪ 0x7FFFFFFF��
     * �� 24MHz�����ʱ��Ϊ 0x7FFFFFFF / 24 us = 89478485 us����СƵ��Ϊ��2 Hz��
     */
    amhw_lpc_mrt_mode_set(p_hw_mrt,
                          AMHW_LPC_MRT_CH(0),
                          AMHW_LPC_MRT_MODE_REPEAT);
    amhw_lpc_mrt_intval_set(p_hw_mrt,
                            AMHW_LPC_MRT_CH(0),
                            amhw_lpc82x_clk_system_clkrate_get() / 8000,
                            AM_TRUE);
    amhw_lpc_mrt_int_enable(p_hw_mrt, AMHW_LPC_MRT_CH(0));

    /* ͨ�� 1 Ϊ AMHW_LPC_MRT_MODE_ONESHOT ģʽ���ж�Ƶ�� 10Hz */
    amhw_lpc_mrt_mode_set(p_hw_mrt,
                          AMHW_LPC_MRT_CH(1),
                          AMHW_LPC_MRT_MODE_ONESHOT);
    amhw_lpc_mrt_intval_set(p_hw_mrt,
                           AMHW_LPC_MRT_CH(1),
                           amhw_lpc82x_clk_system_clkrate_get() / 10,
                           AM_TRUE);
    amhw_lpc_mrt_int_enable(p_hw_mrt, AMHW_LPC_MRT_CH(1));

    /* ͨ�� 2 Ϊ AMHW_LPC_MRT_MODE_ONESHOT ģʽ����ʱ 100us */
    amhw_lpc_mrt_mode_set(p_hw_mrt,
                          AMHW_LPC_MRT_CH(2),
                          AMHW_LPC_MRT_MODE_ONESHOT);

    ticks = 100 * (amhw_lpc82x_clk_system_clkrate_get() / 1000000);

    amhw_lpc_mrt_intval_set(p_hw_mrt,
                            AMHW_LPC_MRT_CH(2),
                            ticks,
                            AM_TRUE);

    /* �ȴ� */
    while((amhw_lpc_mrt_chan_pending_chk(p_hw_mrt, AMHW_LPC_MRT_CH(2))
                                                                == AM_FALSE));

    /* ��ͨ�� 2 �жϱ�־ */
    amhw_lpc_mrt_int_pending_clr(p_hw_mrt, AMHW_LPC_MRT_CH(2));

    /*
     * ͨ�� 3 Ϊ AMHW_LPC_MRT_MODE_ONESHOT_STALL ģʽ��ʱ 100ns��
     * one-stall ģʽ�����ڷǳ����ݵ���ʱ��������д����ֹͣʱ����Ƶ�ʶ�ʱ������
     * ��ʱ����ʱ��ɺ��ٽ���д����������Ҫ�жϻ��ѯ״̬��־��
     */
    amhw_lpc_mrt_mode_set(p_hw_mrt,
                          AMHW_LPC_MRT_CH(3),
                          AMHW_LPC_MRT_MODE_ONESHOT_STALL);

    /* ��ʱ 100 ��ϵͳʱ�ӣ�����ʱ��ɣ�д������ʼ���� */
    amhw_lpc_mrt_intval_set(p_hw_mrt,
                            AMHW_LPC_MRT_CH(3),
                            100,
                            AM_TRUE);

    AM_FOREVER {
        AM_DBG_INFO("idle channel :%d \r\n",
                    amhw_lpc_mrt_idle_channel_get(p_hw_mrt));
        am_mdelay(1000);
    }
}
/** [src_lpc824_hw_mrt] */

/* end of file */
