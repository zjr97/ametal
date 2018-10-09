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
 * \brief PITʵ�ֱ�׼��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 *
 * - ע�⣺
 *    ���Ҫ���д����̣���Ҫ��am_prj_config.h��AM_CFG_SOFTIMER_ENABLE��
 *    AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SYSTEM_TICK_ENABLE�������ֵ����Ϊ0��
 *
 *    ʹ�ô�demo��Ҫ��am_kl26_hwconfig_pit_timing.c�û������ļ��е��豸��Ϣ�ṹ��
 *    �е�pit���ñ�־��ΪAM_FSL_PIT_TIMING_1_64BIT
 *
 * \note ����PIT����ʱ��ԴΪ24M,��32λ��ʱ����ɼ�ʱ 
 *           0xFFFFFFFF / 20M = 179�룬����64λ��ʱ����ɶ�����ʱ�䡣
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_pit_2_64bit_timing.c src_amks16z_core_std_pit_2_64bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_std_pit_2_64bit_timing
 * \copydoc demo_amks16z_core_std_pit_2_64bit_timing.c
 */

/** [src_amks16z_core_std_pit_2_64bit_timing] */
#include "am_kl26_inst_init.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_std_entries.h"


/**
 * \brief �������
 */
void demo_amks16z_core_std_pit_2_64bit_timing_entry (void)
{
    am_timer_handle_t  pit_timing_handle;

    AM_DBG_INFO("demo amks16z_core std pit 1 64 bit timing!\r\n");

    /* ��ȡPIT TIMER������� */
    pit_timing_handle = am_kl26_pit_timing_inst_init();

    demo_std_timer_timing_entry(pit_timing_handle, 0);
}

/** [src_amks16z_core_std_pit_2_64bit_timing] */

/* end of file */
