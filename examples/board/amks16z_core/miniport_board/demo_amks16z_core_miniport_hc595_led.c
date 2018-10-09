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
 * \brief MiniPort-LED + MiniPort-595 ʾ������(��595)�������ο�
 *
 * - ��������
 *   1. �Ƚ� MiniPort-595 ����ֱ����װ�(AMKS16Z-Core)���ΪJ4�� MiniPort �����ӣ�
 *   2. �� MiniPort-LED ������ MiniPort-595 �ӿ������ӡ�
 *
 * - ʵ������
 *   1. ��ˮ������
 *
 * \par Դ����
 * \snippet demo_miniport_hc595_led.c src_miniport_hc595_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_hc595_led
 * \copydoc demo_miniport_hc595_led.c
 */

/** [src_miniport_hc595_led] */
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "demo_std_entries.h"
#include "am_hwconf_miniport_view.h"
#include "am_kl26_inst_init.h"

/* ������� */
void demo_amks16z_core_miniport_hc595_led_entry (void)
{
    AM_DBG_INFO("demo amks16z_core miniport hc595 led!\r\n");

    demo_std_hc595_led_entry(am_miniport_595_inst_init());
}

/** [src_miniport_hc595_led] */

/* end of file */
