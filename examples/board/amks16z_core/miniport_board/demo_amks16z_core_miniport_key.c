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
 * \brief MiniPort-KEY ʾ�����򣬽����ο�
 *
 * - ��������
 *   1. �� MiniPort-KEY ����ֱ���� AM116-Core �� MiniPort�ӿ������ӡ�
 *
 * - ʵ������
 *   1. ���°���ʱ�����Դ��ڴ�ӡ��ǰ������Ϣ��
 *
 * \note
 *    ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��
 *    AM_CFG_KEY_ENABLE �� AM_CFG_SOFTIMER_ENABLE ����Ϊ 1������Щ��
 *    �Ѿ�Ĭ������Ϊ 1�� �û������ٴ����á�
 *
 * \par Դ����
 * \snippet demo_miniport_key.c src_miniport_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_key
 * \copydoc demo_miniport_key.c
 */

/** [src_miniport_key] */
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "demo_std_entries.h"
#include "am_hwconf_miniport_view.h"
#include "am_kl26_inst_init.h"

/**
 * \brief Application Main entry point
 */
void demo_amks16z_core_miniport_key_entry (void)
{
    AM_DBG_INFO("demo amks16z_core miniport key!\r\n");

    am_miniport_key_inst_init();

    demo_std_4key_entry();
}


/** [src_miniport_key] */

/* end of file */
