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
 * \brief MiniPort zlg72128�������ο�
 *
 * - ��������
 *   1. �Ƚ�MiniPort zlg72128����ֱ���� �װ�(AMKS16Z-Core)���ΪJ4�� MiniPort �����ӣ�
 *   2. �� am_prj_config.h ���潫 AM_CFG_KEY_GPIO_ENABLE �� AM_CFG_KEY_ENABLE
 *      ����Ϊ1��
 *
 * - ʵ������
 *   1. ����һ����������λ�������ʾ������ŵĶ����ƣ�
 *   2. ż�����ʱ���������˸���������ʱ������ܲ���˸��
 *
 * \par Դ����
 * \snippet demo_miniport_zlg72128.c src_miniport_zlg72128
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-03  nwt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_zlg72128
 * \copydoc demo_miniport_zlg72128.c
 */

/** [src_miniport_zlg72128] */
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "demo_std_entries.h"
#include "am_hwconf_miniport_view.h"
#include "am_kl26_inst_init.h"

/* ������� */
void demo_amks16z_core_miniport_zlg72128_entry (void)
{
    AM_DBG_INFO("demo am116_core miniport zlg72128!\r\n");

    am_miniport_zlg72128_inst_init();

    demo_std_key_digitron_rngbuf_entry(0);
}

/** [src_miniport_zlg72128] */

/* end of file */
