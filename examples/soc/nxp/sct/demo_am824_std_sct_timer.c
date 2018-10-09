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
 * \brief SCT ��ʱ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 ��״̬�� 3s Ϊ�����ڶ�ʱ��ת��ֹͣ��ת����״̬���л���
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_lpc82x_std_sct_timer.c src_lpc82x_std_sct_timer
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-15  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc82x_std_sct_timer
 * \copydoc demo_lpc82x_std_sct_timer.c
 */

/** [src_lpc82x_std_sct_timer] */
#include "ametal.h"
#include "am_timer.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"

/**
 * \brief ��ʱ���ص�����
 */
am_local void __src_timing_callback (void *p_arg)
{
    am_led_toggle(LED0);
}

/**
 * \brief �������
 */
void demo_lpc82x_std_sct_timer_entry (void)
{
//    am_timer_info_t   sct_timing_info;
    am_timer_handle_t sct_timing_handle;

    sct_timing_handle = am_lpc82x_sct0_timing_inst_init();
    am_timer_info_get(sct_timing_handle);

    /* ���ûص����� */
    am_timer_callback_set(sct_timing_handle, 0, __src_timing_callback, NULL);

    AM_FOREVER
    {

//        /* ���ö�ʱ�ж�Ƶ��Ϊ 20Hz */
//        am_timer_enable(sct_timing_handle,
//                        0,
//                        sct_timing_info.clk_frequency / 20);

        am_mdelay(3000);
        am_timer_disable(sct_timing_handle, 0);
        am_mdelay(3000);
    }
}
/** [src_lpc82x_std_sct_timer] */

/* end of file */
