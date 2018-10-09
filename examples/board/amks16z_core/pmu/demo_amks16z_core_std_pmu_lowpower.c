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
 * \brief amks16z_coreϵͳģʽ������ʾ���̣�ͨ��PMU������ʵ��
 *
 * - ��������:
 *   1. ���ݴ������������ʾ���в�����
 *   2. �����ʣ�115200��
 *
 * - ע��:
 *   1. ����lls, vlls֮ǰ��lptmrҲ�ᶨʱ����MCU��
 *   2. ����vllsģʽ���ѻḴλ
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_pmu_lowpower.c src_amks16z_core_std_pmu_lowpower
 *
 * \internal
 * \par History
 * - 1.00 16-09-24  ari, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_amks16z_core_std_pmu_lowpower
 * \copydoc demo_amks16z_core_std_pmu_lowpower.c
 */

/** [src_amks16z_core_std_pmu_lowpower] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/**
 * \brief ������
 */
void demo_amks16z_core_std_pmu_lowpower_entry (void)
{
    AM_DBG_INFO("demo amks16z_core std pmu lowpower!\r\n");

    demo_kl26_std_pmu_lowpower_entry();
}

/** [src_amks16z_core_std_pmu_lowpower] */

/* end of file */
