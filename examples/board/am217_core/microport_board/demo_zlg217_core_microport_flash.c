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
 * \brief MicroPort FLASH ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������:
 *   1. �� MicroPort FLASH ������ӵ� AM217BLE �� MicroPort �ӿڡ�
 *
 * - ʵ������:
 *   1. ����д���ݵ� FLASH��
 *   2. ������ FLASH ��ȡ���ݣ���ͨ�����ڴ�ӡ����
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_microport_flash.c src_microport_flash
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_flash
 * \copydoc demo_microport_flash.c
 */

/** [src_microport_flash] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_mx25xx.h"
#include "am_is25xx.h"
#include "am_zlg217_inst_init.h"

#define __TEST_LENTH      16    /**< \brief ��д�ֽ��� */

/**
 * \brief MicroPort FLASH ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zlg217_core_microport_flash_entry (void)
{
    AM_DBG_INFO("demo am217_core microport flash!\r\n");

	demo_mx25xx_entry(am_microport_flash_inst_init(), __TEST_LENTH);

	 //demo_is25xx_entry(am_microport_flash_inst_init(), __TEST_LENTH);
}
/** [src_microport_flash] */

/* end of file */
