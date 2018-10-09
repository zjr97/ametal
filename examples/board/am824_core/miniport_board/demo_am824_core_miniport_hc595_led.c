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
 * \brief MiniPort-595 + MiniPort-LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �Ƚ� MiniPort-595 ��չ��ֱ���� AM824-Core �� MiniPort �����ӣ�
 *   2. �� MiniPort-LED ��չ���� MiniPort-595 �ӿ������ӡ�
 *
 * - ʵ������
 *   1. ��ˮ������
 *
 * \par Դ����
 * \snippet demo_am824_core_miniport_hc595_led.c src_am824_core_miniport_hc595_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_core_miniport_hc595_led
 * \copydoc demo_am824_core_miniport_hc595_led.c
 */

/** [src_am824_core_miniport_hc595_led] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_miniport_hc595_led_entry (void)
{
    AM_DBG_INFO("demo am116_core miniport hc595 led!\r\n");

    demo_std_hc595_led_entry(am_miniport_595_inst_init());
}
/** [src_am824_core_miniport_hc595_led] */

/* end of file */
