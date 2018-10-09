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
 * \brief SCT �������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_25 ���Ų�������������ȡ PWM ���ڣ�
 *   2. ���ڴ�ӡ���񵽵����ں�Ƶ�ʡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_am824_std_sct_cap.c src_am824_std_sct_cap
 *
 * \internal
 * \par Modification history
 * - 1.02 15-12-07  hgo, modified
 * - 1.01 15-09-24  zxl, modified
 * - 1.00 15-07-15  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_sct_cap
 * \copydoc demo_am824_std_sct_cap.c
 */

/** [src_am824_std_sct_cap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_std_sct_cap_entry (void)
{

    AM_DBG_INFO("The SCT demo for standard CAP service\r\n");

    demo_std_timer_cap_entry(am_lpc82x_sct0_cap_inst_init(), 0);

}
/** [src_am824_std_sct_cap] */

/* end of file */
