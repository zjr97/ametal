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
 * \brief LPTMRʵ�ֶ�ʱ�����̣�ͨ��HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0��10Hz��Ƶ����˸��
 *
 * \note LPTMRʱ��Դ��4��ѡ����amdr_hwconfig_lptmr_timing.c�н������ã�ѡ��ͬ��С
 *       ��ʱ��Դ����ʱ�ķ�Χ�;��ȴ��ڲ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_lptmr_timing.c src_amks16z_core_hw_lptmr_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_lptmr_timing
 * \copydoc demo_amks16z_core_hw_lptmr_timing.c
 */

/** [src_amks16z_core_hw_lptmr_timing] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_kl26_clk.h"
#include "hw/amhw_fsl_lptmr.h"
#include "hw/amhw_kl26_sim.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_lptmr_timing_entry (void)
{
    uint32_t lptmr_clock;

    /* ��ʼ��ʱ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_LPTMR);

    /* ��ȡ����Ƶ�� */
    lptmr_clock = am_kl26_clk_periph_rate_get(KL26_LPTMR);

    demo_fsl_hw_lptmr_timing_entry(KL26_LPTMR, INUM_LPTMR0, lptmr_clock);
}

/** [src_amks16z_core_hw_lptmr_timing] */

/* end of file */
