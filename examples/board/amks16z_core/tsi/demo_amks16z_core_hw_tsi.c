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
 * \brief   TSI������⣬Ӳ����ʵ��
 *
 *  ʵ������
 *  1.���ֲ��Ӵ�PIOA_1����ʱ�������⵽�Ļ���ֵ
 *  2.������PIOA_1���ź󣬼�⵽��ֵ��󣬲��������
 *
 *  ע�⣺
 *  1.���и�����ʱPIOA_1�������óɴ������š�
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_tsi.c src_amks16z_core_hw_tsi
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  nwt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_tsi
 * \copydoc demo_amks16z_core_hw_tsi.c
 */
 
/** [src_amks16z_core_hw_tsi] */
#include "ametal.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_fsl_tsi.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"
    
/**
 * \brief ���������
 */
void demo_amks16z_core_hw_tsi_entry (void)
{  
    AM_DBG_INFO("demo amks16z_core hw tsi!\r\n");

    /* ʹ��tsi�������ʱ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TSI);

    /* ����PIOA_1����ΪTSI0_CH2 */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_TSI0_CH2);

    demo_fsl_hw_tsi_entry(KL26_TSI);
}

/** [src_amks16z_core_hw_tsi] */
 
/* end of file */

