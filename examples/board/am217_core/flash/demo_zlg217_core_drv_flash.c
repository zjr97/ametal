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
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. �����������ڴ�ӡ"erase error!"��
 *   2. д��������ڴ�ӡ"program error!"��
 *   3. д��ɹ������ڴ�ӡ 55 ������(1024/4)�� 32bit ʮ���������ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zlg217_drv_flash.c src_zlg217_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_drv_flash
 * \copydoc demo_zlg217_drv_flash.c
 */

/** [src_zlg217_drv_flash] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_zlg_flash.h"
#include "am_zlg217.h"
#include "demo_zlg_entries.h"

#define FLASH_SECTOR 55    /**< \brief ���� */

/**
 * \brief �������
 */
void demo_zlg217_core_drv_flash_entry (void)
{
    AM_DBG_INFO("demo am217_core drv flash!\r\n");

    demo_zlg_drv_flash_entry(ZLG217_FLASH, FLASH_SECTOR);
}

/** [src_zlg217_drv_flash] */

/* end of file */
