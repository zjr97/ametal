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
 * \brief MicroPort FLASH ���̣�ͨ�� MTD �ӿ�ʵ�֡�
 *
 * ���� MX25L1606 �ǵ��͵� FLASH �洢�ڼ䣬��˿���ʹ�� MTD �ӿڶ�д��
 * ʹ֮����������޹أ�ʵ�ֿ�ƽ̨���á�
 *
 * - ��������:
 *   1. �� MicroPort FLASH ������ӵ� AMKS16RFID �� MicroPort �ӿڡ�
 *
 * - ʵ������:
 *   1. ����д���ݵ� FLASH��
 *   2. ������ FLASH ��ȡ���ݣ���ͨ�����ڴ�ӡ����
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_1 �������� PC ���ڵ� TXD��
 *    PIOA_2 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_microport_flash_mtd.c src_microport_flash_mtd
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_flash_mtd
 * \copydoc demo_microport_flash_mtd.c
 */

/** [src_microport_flash_mtd] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_hwconf_microport.h"
#include "demo_components_entries.h"
#include "am_kl26_inst_init.h"

/**
 * \brief MicroPort FLASH ���̣�ͨ�� MTD �ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_flash_mtd_entry (void)
{
    AM_DBG_INFO("demo amks16z_core microport flash mtd!\r\n");

    demo_mtd_entry(am_microport_flash_mtd_inst_init(), 8);
}

/** [src_microport_flash_mtd] */

/* end of file */
