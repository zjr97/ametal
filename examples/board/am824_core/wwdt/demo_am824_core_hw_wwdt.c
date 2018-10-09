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
 * \brief WWDT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��Ļ��ӡ���Ź�ʱ��Ƶ�ʣ�
 *   2. ǰ 5 �α����жϷ���ʱ����ִ��ι������,���ڴ�ӡ��ǰι��������
 *   3. �� 6 �α����жϷ���ʱ����ִ��ι���������ᷢ�����Ź���λ��
 *   4. ��λ��LED0 �� 500ms�����ڴ�ӡ "Watchdog reset occurred!"��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. WDT ʱ�ӣ�0.6MHz��64 ��Ƶ��ʱ��Ƶ�� 9.375KHz��WDT �������̶� 4 ��Ƶʱ�ӣ�
 *       �� WDT ʱ��Ƶ�ʴ��� 400K ʱ��WDT ���ڹ��ܲ�������ʹ�á�
 *
 * \par Դ����
 * \snippet demo_am824_hw_wwdt.c src_am824_hw_wwdt
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-14  hgo, del amhw_lpc_wwdt_option_clr()
 * - 1.00 15-07-22  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_wwdt
 * \copydoc demo_am824_hw_wwdt.c
 */

/** [src_am824_hw_wwdt] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "hw/amhw_lpc_wwdt.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_wwdt_entry (void)
{
    uint32_t wdt_freq;
  
    am_kprintf("demo am824_core hw wwdt!\r\n");

    /* ʹ�� WWDT ʱ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_WWDT);

    /* ���� WDT ʱ�ӣ�0.6MHz��64 ��Ƶ��ʱ��Ƶ�� 9.375KHz */
    amhw_lpc82x_clk_wdtoscc_cfg(AMHW_LPC82X_CLK_WDTOSC_RATE_0_6MHZ, 64);

    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_WDT_OSC);

    AM_DBG_INFO("\r\nThe wdt osc freq is %d .\r\n",
                amhw_lpc82x_clk_wdt_rate_get());

    /* ���Ź���ʱ��Ƶ��Ϊ����ʱ��Ƶ�� 4 ��Ƶ */
    wdt_freq = amhw_lpc82x_clk_wdt_rate_get() / 4;

    /* �ر� LED0 */
    am_led_off(LED0);

    demo_lpc_hw_wwdt_entry(LPC82X_WWDT, INUM_WDT, wdt_freq);
}
/** [src_am824_hw_wwdt] */

/* end of file */
