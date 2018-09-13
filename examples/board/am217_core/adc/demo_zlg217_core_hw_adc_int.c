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
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_4 (ADC ͨ�� 4) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ʹ�� ADC ģ�鹦�ܣ����뱣֤ ADC ģ���ϵ磻
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zlg217_hw_adc_int.c src_zlg217_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-28  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_hw_adc_int
 * \copydoc demo_zlg217_hw_adc_int.c
 */

/** [src_zlg217_hw_adc_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg217.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "demo_zlg_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_hw_adc_int_entry (void)
{
    AM_DBG_INFO("demo am217_core hw adc int!\r\n");

    /* ����Ӳ��������ǰ�Ļ������� ���������ţ�ʹ��ʱ�ӵ� */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AIN);
    am_clk_enable(CLK_ADC1);

    demo_zlg_hw_adc_int_entry(ZLG217_ADC1,
                              INUM_ADC1_2,
                              AMHW_ZLG_ADC_CHANNEL4,
                              3300);
}
/** [src_zlg217_hw_adc_int] */

/* end of file */
