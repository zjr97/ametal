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
 * \brief SCT �������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_25 ���Ų�������������ȡ PWM ���ڣ�
 *   2. ���ڴ�ӡ���񵽵����ں�Ƶ�ʡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_lpc82x_std_sct_cap.c src_lpc82x_std_sct_cap
 *
 * \internal
 * \par Modification history
 * - 1.02 15-12-07  hgo, modified
 * - 1.01 15-09-24  zxl, modified
 * - 1.00 15-07-15  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc82x_std_sct_cap
 * \copydoc demo_lpc82x_std_sct_cap.c
 */

/** [src_lpc82x_std_sct_cap] */
#include "ametal.h"
#include "am_cap.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc_sct_cap.h"
#include "am_lpc82x_inst_init.h"

am_local volatile am_bool_t __g_flag    = AM_FALSE; /**< \brief �����־λ */
am_local volatile uint32_t  __g_time_ns = 0;        /**< \brief ����ֵ */

/**
 * \brief ����ص�����
 */
am_local void __cap_callback (void *p_arg, unsigned int cap_val)
{
    am_local uint32_t  count1     = 0;
    am_local am_bool_t first      = AM_TRUE;
    am_cap_handle_t    cap_handle = (am_cap_handle_t)p_arg;

    if (__g_flag == AM_FALSE) {

        if (first == AM_TRUE) {
            count1 = cap_val;
            first  = AM_FALSE;
        } else {
            am_cap_count_to_time(cap_handle,
                                 0,
                                 count1,
                                 cap_val,
                                 (unsigned int *)&__g_time_ns);
            first = AM_TRUE;

            __g_flag = AM_TRUE;
        }
    }
}

/**
 * \brief �������
 */
void demo_lpc82x_std_sct_cap_entry (void)
{
    uint32_t        freq            = 0;
    am_cap_handle_t sct0_cap_handle = NULL;

    AM_DBG_INFO("The SCT demo for standard CAP service\r\n");

    sct0_cap_handle = am_lpc82x_sct0_cap_inst_init();

    am_cap_config(sct0_cap_handle,
                  0,
                  AM_CAP_TRIGGER_RISE,
                  __cap_callback,
                  sct0_cap_handle);

    am_cap_enable(sct0_cap_handle,0);

    AM_FOREVER {
        if (__g_flag == AM_TRUE) {

            freq = 1000000000 / __g_time_ns;
            AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n",
                        __g_time_ns,
                        freq);
            __g_flag = AM_FALSE;
        }

        am_mdelay(200);
    }
}
/** [src_lpc82x_std_sct_cap] */

/* end of file */
