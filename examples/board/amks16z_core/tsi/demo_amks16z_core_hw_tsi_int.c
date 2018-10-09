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
 * \brief   TSI�����жϼ�⣬Ӳ����ʵ��
 *
 *  ʵ������
 *  1.���ֲ��Ӵ�PIOA_1����ʱ�������⵽�Ļ���ֵ
 *  2.������PIOA_1���ź󣬵��ݼ����ڷ�ֵ����1000ʱ�������жϣ�LED1״̬��ת
 *
 *  ע�⣺
 *  1.���и�����ʱPIOA_1�������óɴ������š�
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_tsi_int.c src_amks16z_core_hw_tsi_int
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-26  xjc, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_tsi_int
 * \copydoc demo_amks16z_core_hw_tsi_int.c
 */
 
/** [src_amks16z_core_hw_tsi_int] */
#include "ametal.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_fsl_tsi.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief ���������
 */
void demo_amks16z_core_hw_tsi_int_entry(void)
{  
    AM_DBG_INFO("demo amks16z_core hw tsi int!\r\n");

    /* ʹ��tsi�������ʱ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TSI);

    /* ����PIOA_1����ΪTSI0_CH2 */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_TSI0_CH2);

    demo_fsl_hw_tsi_int_entry(KL26_TSI, INUM_TSI0);

}

/** [src_amks16z_core_hw_tsi_int] */
 
/* end of file */

