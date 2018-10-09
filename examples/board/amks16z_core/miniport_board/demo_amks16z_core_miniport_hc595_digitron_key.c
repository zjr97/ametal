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
 * \brief MiniPort-View + MiniPort-595 + miniPort-KEY ʾ������(��595)�������ο�
 *
 * - ��������
 *   1. �Ƚ� MiniPort-595 ����ֱ����װ�(AMKS16Z-Core)���ΪJ4�� MiniPort �����ӣ�
 *   2. �� MiniPort-View ������ MiniPort-595 �ӿ������ӣ�
 *   3. �� miniPort-KEY �� MiniPort-View ���ӣ�
 *   4. �� am_prj_config.h ���潫 AM_CFG_KEY_GPIO_ENABLE �� AM_CFG_KEY_ENABLE
 *      ����Ϊ1��
 *
 * - ʵ������
 *   1. ����һ����������λ�������ʾ������ŵĶ����ƣ�
 *   2. ż�����ʱ���������˸���������ʱ������ܲ���˸��
 *
 * \par Դ����
 * \snippet demo_miniport_hc595_digitron_key.c src_miniport_hc595_digitron_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_hc595_digitron_key
 * \copydoc demo_miniport_hc595_digitron_key.c
 */

/** [src_miniport_hc595_digitron_key] */
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "demo_std_entries.h"
#include "am_hwconf_miniport_view.h"
#include "am_kl26_inst_init.h"


/* ������� */
void demo_amks16z_core_miniport_hc595_digitron_key_entry (void)
{
    AM_DBG_INFO("demo amks16z_core miniport hc595 digitron key!\r\n");

    am_miniport_view_key_595_inst_init();

    demo_std_key_digitron_entry(0);
}

/** [src_miniport_hc595_digitron_key] */

/* end of file */
