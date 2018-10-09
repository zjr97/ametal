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
 * \snippet demo_kl26_std_dac.c src_kl26_std_dac
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-27  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_std_dac
 * \copydoc demo_fsl_std_dac.c
 */

 /** [src_fsl_std_dac] */
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
void demo_fsl_std_dac_entry (am_dac_handle_t dac0_handle,
                             uint32_t        mv_out)
{
    uint32_t        dac_bits    = 0;
    uint32_t        dac_vref    = 0;

    /* DACʵ����ʼ��������ȡDAC���ֵ */
    dac0_handle = am_kl26_dac0_inst_init();

    /* ��ȡDACת������ */
    dac_bits = am_dac_bits_get(dac0_handle);

    /* ��ȡDAC�ο���ѹ����λ��mV */
    dac_vref = am_dac_vref_get(dac0_handle);

    /* ����DACͨ�������ѹֵ */
    am_dac_mv_set(dac0_handle, AMHW_FSL_DAC0_CHAN_0, mv_out);

    /* ʹ��DAC��� */
    am_dac_enable(dac0_handle, AMHW_FSL_DAC0_CHAN_0);

    am_kprintf("DAC Std Demo test\n");

    am_kprintf("dac_bits = %d\n", dac_bits);
    am_kprintf("dac_vref = %d\n", dac_vref);

    while (1) {
        am_kprintf("DAC Output...\n");
        am_mdelay(500);
    }
}


 /** [src_fsl_std_dac] */

/* end of file */

