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
 * \brief ��ʱ��ʵ�ֱ�׼��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Դ��������ʱ���������Ϣ
 *   2. ��ʱ���ڵ���(Ĭ��Ϊ 2Hz)�����Դ��ڻ���� The timing frq is 2Hz;
 *   3. LED0 ��ת
 *
 * \par Դ����
 * \snippet demo_std_timer_timing.c src_std_timer_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_timer_timing
 * \copydoc demo_std_timer_timing.c
 */

/** [src_std_timer_timing] */
#include "ametal.h"
#include "am_timer.h"
#include "am_delay.h"
#include "am_common.h"
#include "am_vdebug.h"
#include "am_led.h"

#define LED0   0

/**
 * \brief ��ʱ���ص�����
 */
static void __tim_timing_callback (void *p_arg)
{
    am_led_toggle(LED0);
    AM_DBG_INFO("The timing frq is 2Hz\r\n");
}

/**
 * \brief �������
 */
void demo_std_timer_timing_entry (am_timer_handle_t handle,
                                  int               timing_chan)
{

    const am_timer_info_t *p_info  = am_timer_info_get(handle);

    uint32_t clkin;

    am_timer_clkin_freq_get(handle, &clkin);

    AM_DBG_INFO("The timer size is : %d-bit \r\n", p_info->counter_width);
    AM_DBG_INFO("The timer clk_frequency: %d Hz\r\n", clkin);

    /* ���ûص����� */
    am_timer_callback_set(handle, timing_chan, __tim_timing_callback, NULL);

    /* ���ö�ʱʱ��Ϊ 1s ����1000000us�� */
    am_timer_enable_us(handle, timing_chan, 1000000);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_timer_timing] */

/* end of file */
