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
 * \brief sim���̣�ͨ��HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡͨ��Ψһ��ʶ��UID��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_sim_uid.c src_amks16z_core_hw_sim_uid
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_sim_uid
 * \copydoc demo_amks16z_core_hw_sim_uid.c
 */

/** [src_amks16z_core_hw_sim_uid] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_fsl_entrys.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_sim_uid_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw sim uid!\r\n");

    demo_kl26_hw_sim_uid_entry();
}


/** [src_amks16z_core_hw_sim_uid] */

/* end of file */
