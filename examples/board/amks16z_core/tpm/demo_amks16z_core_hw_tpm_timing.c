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
 * \brief TPMʵ�ֱ�׼��ʱ�����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 *
 *\note TPM��4��ʱ��Դ����ѡ��Ĭ������ʱ��Դ��СΪ20M,���жϵ���СƵ��Ϊ:
 *              fre = 20000000/(128*65535) = 2.38Hz  ��16λ��ʱ�������128��Ƶ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_tpm_timing.c src_amks16z_core_hw_tpm_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_tpm_timing
 * \copydoc demo_amks16z_core_hw_tpm_timing.c
 */
 
/** [src_amks16z_core_hw_tpm_timing] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_kl26_clk.h"
#include "hw/amhw_fsl_tpm.h"
#include "hw/amhw_kl26_sim.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_tpm_timing_entry (void)
{
    uint32_t tpm_clk;

    /* ƽ̨��ʼ�� */
    amhw_kl26_sim_tpm_src_set(KL26_SIM_TPMSRC_PLLFLLCLK);
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TPM0);

    tpm_clk = am_kl26_clk_periph_rate_get(KL26_TPM0);

    demo_fsl_hw_tpm_timing_entry(KL26_TPM0, 10, INUM_TPM0, tpm_clk);
}

/** [src_amks16z_core_hw_tpm_timing] */

/* end of file */
