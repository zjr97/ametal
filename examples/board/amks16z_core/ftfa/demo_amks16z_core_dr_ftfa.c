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
 * \brief FTFA����,ͨ��������Ľӿ�ʵ��
 *
 * - �������裺
 *      - ���ڽӵ��Դ���
 *
 * - ʵ������
 *      - �����������ڴ�ӡ ��erase error!��
 *      - д��������ڴ�ӡ "program error!"
 *      - д��ɹ������ڴ�ӡ 55������ (1024/4) ��32bitʮ����������
 *
 * \par Դ����
 * \snippet demo_amks16z_core_dr_ftfa.c src_amks16z_core_dr_ftfa
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_dr_ftfa
 * \copydoc demo_amks16z_core_dr_ftfa.c
 */

/** [src_amks16z_core_dr_ftfa] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_fsl_ftfa.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

void demo_amks16z_core_dr_ftfa_entry (void)
{
    AM_DBG_INFO("demo amks16z_core dr ftfa!\r\n");

    demo_fsl_dr_ftfa_entry(KL26_FTFA);
}

/** [src_amks16z_core_dr_ftfa] */

/* end of file */
