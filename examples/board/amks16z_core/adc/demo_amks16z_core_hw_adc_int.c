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
 * \brief ADC���̣������жϷ�ʽ��ȡ���������ADCת�������ͨ��HW��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. J12����ñ�̽ӣ���ʱ�ο���ѹΪ2.5v����
 *   4. PIOE_29(ADCͨ��0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ADCģ����444.44kHz������(����ʱ��Ϊ24MHz)������16λ����;
 *   2. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_adc_int.c src_amks16z_core_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-18  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_adc_int
 * \copydoc demo_amks16z_core_hw_adc_int.c
 */

/** [src_amks16z_core_hw_adc_int] */
#include "demo_fsl_entrys.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_board.h"
#include "hw/amhw_kl26_sim.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief �жϷ�ʽ��ȡ���������ADCת�������ͨ��HW��ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_adc_int_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw adc int!\r\n");

    /* ����ADC ѡ��ģ���������� */
    am_gpio_pin_cfg(PIOE_29, PIOE_29_ADC0_SE4B);

    /* ʹ��ADCʱ��                  */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_ADC0);

    demo_fsl_hw_adc_int_entry(KL26_ADC0,
                              INUM_ADC0,
                              AMHW_FSL_ADC_CHAN_4,
                              CLK_BUS,
                              2500);
}
/** [src_amks16z_core_hw_adc_int] */

/* end of file */
