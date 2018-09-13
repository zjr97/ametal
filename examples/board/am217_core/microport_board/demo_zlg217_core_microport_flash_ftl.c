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
 * \brief MicroPort FLASH ���̣�ͨ�� FTL �ӿ�ʵ�֡�
 *
 * ����ʹ�� MX25XX ��׼�ӿں� MTD �ӿ���Ҫ��ÿ��д������ǰ��ȷ����Ӧ�Ĵ�
 * ���ռ��Ѿ����������Ʊػ����̴����ܴ��鷳���ڴ�ͬʱ������ MX25L1606
 * ��ĳһ��ַ�β����������� 10 ��ε����ޣ���Ӧ�ε�ַ�ռ�洢���ݽ�����
 * �ɿ������� AMetal �ṩ FTL ��׼�ӿڸ��û�ʹ�ã����ͱ���Ѷȡ�
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
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ʹ�� FTL �ӿ���Ҫ����һ���� RAM �ռ��Լ�һ���������߼��顣
 *
 * \par Դ����
 * \snippet demo_microport_flash_ftl.c src_microport_flash_ftl
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_flash_ftl
 * \copydoc demo_microport_flash_ftl.c
 */

/** [src_microport_flash_ftl] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg217_inst_init.h"

/**
 * \brief MicroPort FLASH ���̣�ͨ�� FTL �ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zlg217_core_microport_flash_ftl_entry (void)
{
    AM_DBG_INFO("demo am217_core microport flash ftl!\r\n");

    demo_ftl_entry(am_microport_flash_ftl_inst_init(), 8);
}
/** [src_microport_flash_ftl] */

/* end of file */
