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
 * \brief FTFA����,ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *      - ʹ�õ��Դ��ڴ�ӡ��Ϣ
 *      - д��ʧ��ʱ����ӡ ��write error!��
 *      - д�����ʱ����ӡ ��data not wrote correct!��
 *      - �ɹ�д��ʱ����ӡд�������(32bit)�� ��flash test finished��
 * - ʵ������
 *
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_ftfa.c src_amks16z_core_hw_ftfa
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_ftfa
 * \copydoc demo_amks16z_core_hw_ftfa.c
 */


/** [src_amks16z_core_hw_ftfa] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_int.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

void demo_amks16z_core_hw_ftfa_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw ftfa!\r\n");

    deme_fsl_hw_ftfa_entry(KL26_FTFA);
}

/** [src_amks16z_core_hw_ftfa] */

/* end of file */
