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
 * \brief ADC ���̣���ѯ��ʽ����ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽� J12 ����ñ��ʹ�òο���ѹΪ 2.5V��
 *   2. PIO0_7(ADC ͨ�� 0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_std_adc_poll.c src_am824_std_adc_poll
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-09-10  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_adc_poll
 * \copydoc demo_am824_std_adc_poll.c
 */

/** [src_am824_std_adc_poll] */
#include "ametal.h"
#include "am_adc.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"

#include "demo_nxp_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** \brief ʹ�õ� ADC ͨ�� */
#define __ADC_CHAN         0

/**
 * \brief �������
 */
void demo_am824_core_std_adc_poll_entry (void)
{

    AM_DBG_INFO("demo am824_core std adc poll!\r\n");

    demo_lpc_std_adc_poll_entry(am_lpc82x_adc0_int_inst_init(),
                                 __ADC_CHAN, 
                                100000);
  
}
/** [src_am824_std_adc_poll] */

/* end of file */
