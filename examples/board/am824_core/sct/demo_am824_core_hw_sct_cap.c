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
 * \brief SCT 32 λ�������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ�öŰ��ߣ����ⲿ�ṩ�� PWM �ź��� PIO0_25 ���ӡ�
 *
 * - ʵ������
 *   1. PIO0_25(SCT_IN_2) ����Ϊ�����ܣ����� PWM ���ں�Ƶ�ʲ�ͨ�����������
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    2. ����ʾ�������߼������ǵ����������ԶԱ��������Ƶ�ʺ����ڣ��Ƿ��벶�����
 *       ��һ�£�
 *    3. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_am824_hw_sct_cap.c src_am824_hw_sct_cap
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-19  hgo, modified
 * - 1.01 15-09-23  zxl, modified
 * - 1.00 15-07-14  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_sct_cap
 * \copydoc demo_am824_hw_sct_cap.c
 */

/** [src_am824_hw_sct_cap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_inmux.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_sct_cap_entry (void)
{
    uint32_t frq = 0;
  
    am_kprintf("demo am824_core hw sct cap!\r\n");
  
    /**
    * һ���� 4 ������ͨ��, ÿ��ͨ����ѡ������빦�ܴﵽ 8 ��,
    * ��������й����� amhw_lpc82x_inmux.h �ļ��й��� SCT �Ķ���
    * ������������ͨ�� 2
    */
    amhw_lpc82x_inmux_sct_trig_set(LPC82X_INMUX,
                                   2,
                                   AMHW_LPC82X_INMUX_SCTTRIG_SCT_PIN2);

    /* ƽ̨��ʼ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SCT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);

    /* �� SCT_PIN_2 ������ PIO0_25 ���� */
    am_gpio_pin_cfg(PIO0_25, PIO_FUNC_SCT_PIN2);
  
    /* ���� SCT �����ź�ԴΪ SCT ����ͨ�� 2 */
    amhw_lpc82x_inmux_sct_trig_set(LPC82X_INMUX,
                                   2,
                                   AMHW_LPC82X_INMUX_SCTTRIG_SCT_PIN2);
                                   
    frq = amhw_lpc82x_clk_system_clkrate_get();
    demo_lpc_hw_sct_cap_entry(LPC82X_SCT0, INUM_SCT0, frq);
}
/** [src_am824_hw_sct_cap] */

/* end of file */
