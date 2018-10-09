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
 * \brief SCT ��Ϊ 2 �� 16 λ��ʱ����ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ����˸;
 *   2. ����������(PIO0_24)״̬�� 8KHz ��Ƶ�ʷ�ת���������Ϊ 4KHz��
 *      ÿ������ 50 ���룬����Ƶ��Ϊ 10Hz��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ��������Ҫ�̽� J7 ����ñ�����ܱ� PIO0_24 ���ƣ�
 *    3. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����Ĭ�ϳ�ʼ����������
 *
 * \par Դ����
 * \snippet demo_am824_hw_sct_2_16bit_timing.c src_am824_hw_sct_2_16bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.02 15-12-14  hgo, change PIO0_15 to PIO0_24 .
 * - 1.01 15-11-19  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_sct_2_16bit_timing
 * \copydoc demo_am824_hw_sct_2_16bit_timing.c
 */

/** [src_am824_hw_sct_2_16bit_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"


/**
 * \brief �������
 */
void demo_am824_core_hw_sct_2_16bit_timing_entry (void)
{
    AM_DBG_INFO("demo am824_core hw sct 2-16bit timing\r\n");
  
    uint32_t frq = 0;
    /* ƽ̨��ʼ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SCT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);

    AM_DBG_INFO("The LED0 blinking in 10Hz\r\n");
    AM_DBG_INFO("The PIO0_24 toggle in 8KHz, The output waveform is 4KHz\r\n");

    /* ��ʼ�������� ������ߣ����������� */
    am_gpio_pin_cfg(PIO0_24, AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PULLUP);

    frq = amhw_lpc82x_clk_system_clkrate_get();
    demo_lpc_hw_sct_2_16bit_timing_entry(LPC82X_SCT0, 
                                         INUM_SCT0, 
                                         frq,
                                         PIO0_24);
}
/** [src_am824_hw_sct_2_16bit_timing] */

/* end of file */
