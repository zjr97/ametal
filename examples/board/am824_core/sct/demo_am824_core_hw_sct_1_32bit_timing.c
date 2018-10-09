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
 * \brief SCT 32 λ��ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ����˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *    3. ������ʹ���� SCT �¼� 0�����ڲ����������жϣ�ʹ��ƥ��ͨ�� 0���¼�����������
 *       ���㡣
 *
 * \par Դ����
 * \snippet demo_am824_hw_sct_1_32bit_timing.c src_am824_hw_sct_1_32bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-08  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_sct_1_32bit_timing
 * \copydoc demo_am824_hw_sct_1_32bit_timing.c
 */

/** [src_am824_hw_sct_1_32bit_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_sct_1_32bit_timing_entry (void)
{
    uint32_t frq = 0;
  
    AM_DBG_INFO("demo am824_core hw sct 1_32bit timing\r\n");
    /* ƽ̨��ʼ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SCT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);

    AM_DBG_INFO("The demo for SCT timing:\r\n");
    AM_DBG_INFO("The led toggle in 10Hz \r\n");

    frq = amhw_lpc82x_clk_system_clkrate_get();
  
    demo_lpc_hw_sct_1_32bit_timing_entry(LPC82X_SCT0, INUM_SCT0, frq);
}
/** [src_am824_hw_sct_1_32bit_timing] */

/* end of file */
