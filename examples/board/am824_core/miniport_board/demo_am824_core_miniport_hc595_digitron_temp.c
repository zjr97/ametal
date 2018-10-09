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
 * \brief MiniPort-595 + MiniPort-View + ���� LM75 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �Ƚ� MiniPort-595 ��չ��ֱ���� AM824-Core �� MiniPort �����ӣ�
 *   2. �� MiniPort-View ��չ���� MiniPort-595 �ӿ������ӡ�
 *
 * - ʵ������
 *   1. �������ʾ��ǰ�¶ȣ�
 *   2. ���� RES ��������һ������������ʾ�¶�ֵ���ߡ�
 *
 * \note
 *    1. ��Ҫ�̽� J11 �� J13 ����ñ��I2C1 �Ż��� LM75 ���ӣ�
 *    2. ������Ҫ�� J14 ����ñ�� KEY �� RES �̽Ӳ���ʹ�ã�
 *
 *
 * \par Դ����
 * \snippet demo_am824_core_miniport_hc595_digitron_temp.c src_am824_core_miniport_hc595_digitron_temp
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_core_miniport_hc595_digitron_temp
 * \copydoc demo_am824_core_miniport_hc595_digitron_temp.c
 */

/** [src_am824_core_miniport_hc595_digitron_temp] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_miniport_hc595_digitron_temp_entry (void)
{
    AM_DBG_INFO("demo am824_core miniport hc595 digitron temp!\r\n");

    am_miniport_view_595_inst_init();

    demo_std_digitron_temp_entry(0, am_temp_lm75_inst_init());
}
/** [src_am824_core_miniport_hc595_digitron_temp] */

/* end of file */
