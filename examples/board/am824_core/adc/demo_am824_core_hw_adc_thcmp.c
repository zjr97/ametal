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
 * \brief ADC ��ֵ�Ƚ����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ������չʾ�� 2 ����ֵ�Ƚϣ�
 *   1. ��ֵ�Ƚ� 0: ��Χ�Ƚϣ�
 *   2. ��ֵ�Ƚ� 1: ��Խ�Ƚϡ�
 *
 * - �������裺
 *   1. PIO0_7(ADC ͨ�� 0) ����ģ������ 1��
 *   2. PIO0_6(ADC ͨ�� 1) ����ģ������ 2��
 *   3. �̽� J12 ����ñ��ʹ�òο���ѹΪ 2.5V��
 *   4. ������ͨ����ģ�������ѹ�ֱ�� 0 ���� 2500mV��
 *
 * - ʵ������
 *   1. ģ������ 1 �ĵ�ѹ���� 1100mV ����� 2000mV ʱ�����ڻ������ѹֵ���ȽϽ����
 *   2. ģ������ 2 �ĵ�ѹ�仯���� 1100mV ʱ�����ڻ������ѹֵ���ȽϽ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_hw_adc_thcmp.c src_am824_hw_adc_thcmp
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_adc_thcmp
 * \copydoc demo_am824_hw_adc_thcmp.c
 */

/** [src_am824_hw_adc_thcmp] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_adc_thcmp_entry (void)
{

    am_kprintf("demo am824_core hw adc thcmp!\r\n");

    /* ƽ̨��ʼ�� */
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_ADC0);
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_ADC0);

    /* ����ͨ����ʹ��ͨ�� 0 ��ͨ�� 1����������Ϊ����ģʽ INACTIVE */
    am_gpio_pin_cfg(PIO0_7, PIO0_7_ADC_0 | PIO0_7_INACTIVE);
    am_gpio_pin_cfg(PIO0_6, PIO0_6_ADC_1 | PIO0_6_INACTIVE);


    demo_lpc824_hw_adc_thcmp_entry(LPC82X_ADC0, 
                                   INUM_ADC0_THCMP, 
                                   2500);
}
/** [src_am824_hw_adc_thcmp] */

/* end of file */
