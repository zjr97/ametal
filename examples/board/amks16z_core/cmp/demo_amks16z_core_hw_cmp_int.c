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
 * \brief ģ��Ƚ����Ƚϵ�ѹ���̣�ͨ��HW��Ľӿ��жϷ�ʽʵ��

 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. PIOC_6��ӿɵ��ĵ�ѹ���루���û�������������
 * - ʵ������
 *   �������ѹ����1.65v����ʱ��LED��ת�������ڹ����⣩�����ڴ�ӡ��Ϣ����CMP INT����
 *
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_cmp_int.c src_amks16z_core_hw_cmp_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-22  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_cmp_int
 * \copydoc demo_amks16z_core_hw_cmp_int.c
 */

/** [src_amks16z_core_hw_cmp_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_kl26_sim.h"
#include "am_gpio.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief CMP�Ƚ���HW���ж�����
 * \return ��
 */
void demo_amks16z_core_hw_cmp_int_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw cmp int!\r\n");

    /* ʹ��CMPʱ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_CMP);

    /* PIOC_6ΪCMP0_IN0   */
    am_gpio_pin_cfg (PIOC_6, PIOC_6_CMP0_IN0);

    /* PIOE_0����ΪCMP0_OUT */
    am_gpio_pin_cfg (PIOE_0, PIOE_0_CMP0_OUT);

    demo_fsl_hw_cmp_int_entry(KL26_CMP0,
                              INUM_CMP0);
}

/** [src_amks16z_core_hw_cmp_int] */

/* end of file */
