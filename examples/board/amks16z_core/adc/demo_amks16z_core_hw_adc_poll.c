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
 * \brief ADC���̣����ò�ѯ��ʽ��ȡ���������ADCת�������ͨ��HW��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. J12����ñ�̽ӣ��ο���ѹ�Ĵ�С��оƬVREF�ܽ����ӵĵ�ƽ�йأ��˴��Ĳο���ѹΪ2.5V����
 *   4. PIOE_20(ADCͨ��0����ͨ������) ����ģ�����롣
 *
 * - ʵ������
 *   1. ADCģ����444.44kHz������(����ʱ��Ϊ24MHz)������16λ����;
 *   2. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_adc_poll.c src_amks16z_core_hw_adc_poll
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-14  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_adc_poll
 * \copydoc demo_amks16z_core_hw_adc_poll.c
 */

/** [src_amks16z_core_hw_adc_poll] */
#include "demo_fsl_entrys.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_board.h"
#include "hw/amhw_kl26_sim.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief ADC��ѯ��ȡ����ֵ��ʹ��HW��ӿں���
 * \return ��
 */
void demo_amks16z_core_hw_adc_poll_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw adc poll!\r\n");

    /* ����ADC ͨ��0ģ���������� */
    am_gpio_pin_cfg(PIOE_20, PIOE_20_ADC0_SE0);

    /* ʹ��ADCʱ��                  */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_ADC0);

    demo_fsl_hw_adc_poll_entry(KL26_ADC0,
                               AMHW_FSL_ADC_CHAN_0,
                               CLK_BUS,
                               2500);
}
/** [src_amks16z_core_hw_adc_poll] */

/* end of file */
