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
 * \brief DAC��ģת�����̣�ͨ��HW�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �ɼ���ģת���������PE30�ĵ�ѹֵ
 *   2. ʹ��DACREF_2�ο���ѹ��DACREF_2����VDDA�ܽţ���ѹֵΪ3.3V��
 *   3. �����ѹֵΪ1.823V
 *
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_dac.c src_amks16z_core_hw_dac
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_dac
 * \copydoc demo_amks16z_core_hw_dac.c
 */

 /** [src_amks16z_core_hw_dac] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_kl26_inst_init.h"
#include "hw/amhw_kl26_sim.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief DAC�����ѹֵ������HW��ʵ��
 */
void demo_amks16z_core_hw_dac_entry ()
{
    /* ����PIOE_30ΪDAC0_OUT����                 */
    am_gpio_pin_cfg (PIOE_30,PIOE_30_DAC0_OUT);

    /* ����DACʱ��                               */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_DAC0);

	  /* ���1832mv��ѹ */
    demo_fsl_hw_dac_entry(KL26_DAC0, 1832);
}


 /** [src_amks16z_core_hw_dac] */

/* end of file */


