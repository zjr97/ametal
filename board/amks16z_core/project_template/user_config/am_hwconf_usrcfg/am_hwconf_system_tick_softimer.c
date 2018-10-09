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
 * \brief ϵͳ�δ������ʱ�������ļ�
 * \sa am_hwconf_system_tick_softimer.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_timer.h"
#include "am_softimer.h"
#include "am_system.h"
#include "am_arm_nvic.h"
#include "am_kl26.h"
#include "am_kl26_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_system_tick_softimer
 * \copydoc am_hwconf_system_tick_softimer.c
 * @{
 */

/**
 * \brief ����ϵͳ�δ��Ƶ�ʣ�Ĭ�� 1KHz
 *
 * ϵͳ�δ��ʹ����� am_system.h
 */
#define __SYSTEM_TICK_RATE      1000

/** \brief ʹ�õĶ�ʱ�����жϺ� */
#define __TIMER_INUM            INUM_PIT

/** \brief ʹ�ö�ʱ��ͨ�� 0 */
#define __TIMER_CHAN            0

/** \brief ��ʱ���ص����������ڲ���ϵͳ�δ� */
am_local void __system_tick_callback (void *p_arg)
{
    am_system_module_tick();       /* ����ϵͳ�δ� */
}

/** \brief ��ʱ���ص����������ڲ���ϵͳ�δ����������ʱ���ȵ� */
am_local void __system_tick_softimer_callback (void *p_arg)
{
    am_system_module_tick();       /* ����ϵͳ�δ� */
    am_softimer_module_tick();     /* ���������ʱ�� */
}

/** \brief ϵͳ�δ�ʵ����ʼ��(��ʹ�������ʱ��) */
am_timer_handle_t am_system_tick_inst_init (void)
{
    am_timer_handle_t  pit_handle;

    pit_handle = am_kl26_pit_timing_inst_init();

    if (NULL != pit_handle) {

        uint32_t clk_freq;

        am_timer_count_freq_get(pit_handle, 0, &clk_freq);

        /* ����ʱ�����ж����ȼ�����Ϊ��� */
        am_arm_nvic_priority_set(__TIMER_INUM, 0x03, 0x03);

        am_timer_callback_set(pit_handle,
                              __TIMER_CHAN,
                              __system_tick_callback,
                              NULL);

        am_system_module_init(__SYSTEM_TICK_RATE);

        am_timer_enable(pit_handle,
                        __TIMER_CHAN,
                        clk_freq / __SYSTEM_TICK_RATE);
    }

    return pit_handle;
}

/** \brief ϵͳ�δ�ʵ����ʼ��(ʹ�������ʱ��) */
am_timer_handle_t am_system_tick_softimer_inst_init (void)
{
	am_timer_handle_t pit_handle = NULL;

	pit_handle = am_kl26_pit_timing_inst_init();

	if (NULL != pit_handle) {

		/* ��ʼ�������ʱ�� */
		am_softimer_module_init(__SYSTEM_TICK_RATE);

		/* ����ʱ�����ж����ȼ�����Ϊ��� */
		am_arm_nvic_priority_set(SysTick_IRQn, 0x03, 0x03);

		am_timer_callback_set(pit_handle,
							  0,
							  __system_tick_softimer_callback,
							  NULL);

		am_system_module_init(__SYSTEM_TICK_RATE);

        am_timer_enable_us(pit_handle,
                           0,
                           1000000 / __SYSTEM_TICK_RATE);
	}

    return pit_handle;
}

/**
 * @}
 */

/* end of file */
