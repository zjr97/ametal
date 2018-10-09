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
 * \brief DAC��ģת�����̣�ͨ��HW�ӿ�ʵ�֣�DMA��������
 *
 * - ʵ������
 *   1. �ɼ���ģת���������PE30�ĵ�ѹֵ
 *
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_dac_dma_st.c src_amks16z_core_hw_dac_dma_st
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-27  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_dac_dma_st
 * \copydoc demo_amks16z_core_hw_dac_dma_st.c
 */

 /** [src_amks16z_core_hw_dac_dma_st] */
#include "ametal.h"
#include "am_dac.h"
#include "am_fsl_dac.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_kl26_inst_init.h"
#include "am_kl26_dma.h"
#include "am_int.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief DAC�����ѹ��DMA�������ݣ�HW��ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_dac_dma_st_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw dac dma st!\r\n");

    demo_kl26_hw_dac_dma_st_entry();
}


 /** [src_amks16z_core_hw_dac_dma_st] */

/* end of file */

