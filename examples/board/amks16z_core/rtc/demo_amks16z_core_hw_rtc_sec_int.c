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
 * \brief
 *
 * - �������裺
 *      - PTC1�������32.786kHz��ʱ������
 *      - ʹ�õ��Դ��ڴ�ӡ
 *
 * - ʵ������
 *      - ���ڴ�ӡ�����õ�ʱ��
 *      - �Ժ�ÿ���ӡһ��ʱ��
 *      - LED0��״̬ÿ���ӷ�תһ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_rtc_sec_int.c src_amks16z_core_hw_rtc_sec_int
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_hw_rtc_sec_int
 * \copydoc demo_amks16z_core_hw_rtc_sec_int.c
 */

/** [src_amks16z_core_hw_rtc_sec_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_int.h"
#include <time.h>
#include "am_kl26_inst_init.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_fsl_rtc.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

#include "../../../../soc/freescale/kl26/am_kl26.h"
/**
 * \brief AMetal Ӧ�ó������
 */
void demo_amks16z_core_hw_rtc_sec_int_entry (void)
{
	  
    /* RTC ʱ��Դѡ��Ϊ�ⲿRTCʱ��Դ */
    amhw_kl26_sim_ercclk32k_src_set(KL26_SIM_OSC32KSEL_CLKIN);

    /* RTC ģ��ʱ��ʹ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_RTC);

    /* PORTC ʱ������ʹ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PORTC);

    /* PTC1 ����λ RTC_CLK_INPUT */
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_1, 1);

    demo_fsl_hw_rtc_sec_int_entry(KL26_RTC);
}

/** [src_amks16z_core_hw_rtc_sec_int] */

/* end of file */
