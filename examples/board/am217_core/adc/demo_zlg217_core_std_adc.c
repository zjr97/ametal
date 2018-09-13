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
 * \brief ADC ���̣�ͨ����׼�ӿ�ʵ��
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
 * \snippet demo_zlg217_std_adc.c src_std_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-29  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_adc
 * \copydoc demo_zlg217_std_adc.c
 */

/** [src_std_adc] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_zlg217_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_adc_entry (void)
{
    AM_DBG_INFO("demo am217_core std adc int!\r\n");

    demo_std_adc_entry(am_zlg217_adc1_inst_init(), 4);

}
/** [src_std_adc] */

/* end of file */
