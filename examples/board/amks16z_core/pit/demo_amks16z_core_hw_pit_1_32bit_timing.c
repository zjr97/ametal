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
 * \brief PIT ��ʱ��ʵ��(32λ)��ʱ���ܵ����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 *
 * - ע�⣺
 *    ���Ҫ���д����̣���Ҫ��am_prj_config.h��AM_CFG_SOFTIMER_ENABLE��
 *    AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SYSTEM_TICK_ENABLE�������ֵ����Ϊ0��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_pit_1_32bit_timing.c src_amks16z_core_hw_pit_1_32bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */


/**
 * \addtogroup demo_amks16z_core_if_hw_pit_1_32bit_timing
 * \copydoc demo_amks16z_core_hw_pit_1_32bit_timing.c
 */

/** [src_amks16z_core_hw_pit_1_32bit_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_int.h"
#include "am_kl26_clk.h"
#include "hw/amhw_fsl_pit.h"
#include "hw/amhw_kl26_sim.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"


/**
 * \brief �������
 */
void demo_amks16z_core_hw_pit_1_32bit_timing_entry (void)
{
    uint32_t pit_clk;

    AM_DBG_INFO("demo amks16z_core hw pit 1 32 bit timing!\r\n");
    /* ƽ̨��ʼ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PIT);

    pit_clk = am_kl26_clk_periph_rate_get(KL26_PIT);

    demo_fsl_hw_pit_1_32bit_timing_entry(KL26_PIT, INUM_PIT, pit_clk);
}

/** [src_amks16z_core_hw_pit_1_32bit_timing] */

/* end of file */
