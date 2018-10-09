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
 * \brief DAC��ģת�����̣�ͨ��STD�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PE30���1523mv��ѹ��
 *
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_dac.c src_amks16z_core_std_dac
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-27  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_std_dac
 * \copydoc demo_amks16z_core_std_dac.c
 */

 /** [src_amks16z_core_std_dac] */
#include "ametal.h"
#include "am_dac.h"
#include "am_fsl_dac.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_kl26_inst_init.h"
#include "demo_fsl_entrys.h"

/**
 * \brief DAC�����ѹ����׼�ӿڲ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_dac_entry (void)
{
    uint32_t        mv_out      = 1523; /* ��Ҫ����ĵ�ѹֵ  ��λ��mv   */
    am_dac_handle_t dac0_handle = NULL; /* ADC��׼���������� */

    /* DACʵ����ʼ��������ȡDAC���ֵ */
    dac0_handle = am_kl26_dac0_inst_init();

    demo_fsl_std_dac_entry(dac0_handle, mv_out);
}


 /** [src_amks16z_core_std_dac] */

/* end of file */

