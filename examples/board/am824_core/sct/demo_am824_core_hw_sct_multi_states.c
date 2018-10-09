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
 * \brief SCT ������״̬���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_16(SCT_OUT5)����������Ρ�
 *
 * \code
 *  |---         ״̬0        ---|--- ״̬1 ---|--- ״̬0      ......
 *             _____     _____     ___         __            ___
 *            |     |   |     |   |   |       |  |          |     ......
 *  __________|     |___|     |___|   |_______|  |__________|
 *
 *  0         10    15  18    23  26  3      10  12         10     (ms)
 *                              (״̬1, 0)     (״̬0, 0)
 *          �¼� 0  1   2      3   4   5      6  7
 * \endcode
 *
 * \note
 *    1. ���� PIO0_16(SCT_OUT5) ���ŵ��߼������ǣ����ῴ���ò��Σ�ǰ 10ms Ϊ�͵�ƽ��
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_am824_hw_sct_multi_states.c src_am824_hw_sct_multi_states
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-08  hgo, modified
 * - 1.00 14-12-09  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_sct_multi_states
 * \copydoc demo_am824_hw_sct_multi_states.c
 */

/** [src_am824_hw_sct_multi_states] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_sct_multi_states_entry (void)
{
    uint32_t frq = 0;

    am_kprintf("demo am824_core hw sct multi!\r\n");
    /* ƽ̨��ʼ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SCT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);

    /* ѡ�� SCT_OUT5 ��Ӧ���� PIO0_16 */
    am_gpio_pin_cfg(PIO0_16, PIO_FUNC_SCT_OUT5);

    frq = amhw_lpc82x_clk_system_clkrate_get();
  
    demo_lpc_hw_sct_multi_states_entry(LPC82X_SCT0, frq);
}
/** [src_am824_hw_sct_multi_states] */

/* end of file */
