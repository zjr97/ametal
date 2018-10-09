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
 * \brief MiniPort-View + MiniPort-KEY ʾ�����򣬽����ο�
 *
 * - ��������
 *   1. �Ƚ� MiniPort-KEY ����ֱ����װ�(AMKS16Z-Core)���ΪJ4�� MiniPort �����ӣ�
 *   2. �� MiniPort-View ������ MiniPort-KEY �ӿ������ӣ�
 *   3. �� am_prj_config.h ���潫 AM_CFG_KEY_GPIO_ENABLE �� AM_CFG_KEY_ENABLE
 *      ����Ϊ1��
 *
 * - ʵ������
 *   1. ����һ����������λ�������ʾ������ŵĶ����ƣ�
 *   2. ż�����ʱ���������˸���������ʱ������ܲ���˸��
 *
 * \par Դ����
 * \snippet demo_miniport_key_digitron.c src_miniport_key_digitron
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-03  nwt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_key_digitron
 * \copydoc demo_miniport_key_digitron.c
 */

/** [src_miniport_key_digitron] */
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "demo_std_entries.h"
#include "am_hwconf_miniport_view.h"
#include "am_kl26_inst_init.h"

/**
 * \brief �������
 */
void demo_amks16z_core_miniport_key_digitron_entry (void)
{

    AM_DBG_INFO("demo amks16z_core miniport key digitron!\r\n");

    am_miniport_view_key_inst_init();

    demo_std_key_digitron_entry(0);
}

/** [src_miniport_key_digitron] */

/* end of file */
