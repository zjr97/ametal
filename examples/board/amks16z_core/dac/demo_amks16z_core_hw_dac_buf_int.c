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
 *   1. ����PIOE_30ΪDACģ�����
 *   2. ��ʾ�����ɼ���ģת���������PE30���ź����
 *   3. ʾ������ʾPIOE_30��ģ��������ڴ��Ϊ7������Ҳ���
 *
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_dac_buf_int.c src_amks16z_core_hw_dac_buf_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_dac_buf_int
 * \copydoc demo_amks16z_core_hw_dac_buf_int.c
 */

 /** [src_amks16z_core_hw_dac_buf_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_int.h"
#include "hw/amhw_kl26_sim.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief DAC ʹ�û������ж�������Ҳ��źţ�HW��ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_dac_buf_int_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw dac buf int!\r\n");

    /* ����PIOE_30ΪDAC0_OUT����                 */
    am_gpio_pin_cfg (PIOE_30, PIOE_30_DAC0_OUT);

    /* ����DACʱ��                               */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_DAC0);

    demo_fsl_hw_dac_buf_int_entry(KL26_DAC0, INUM_DAC0);
}

/** [src_amks16z_core_hw_dac_buf_int] */

/* end of file */
