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
 * \brief MicroPort EEPROM ���̣�ͨ�� NVRAM �ӿ�ʵ��
 *
 * ���� FM24C02 �� EEPROM �ǵ��͵ķ���ʧ�Դ洢�������ʹ�� NVRAM����
 * ��ʧ�Դ洢������׼�ӿڶ�д���ݾ�������ľ���������ˡ�
 *
 * - ��������:
 *   1. �� MicroPort EEPROM ������ӵ� AM217BLE �� MicroPort �ӿڡ�
 *
 * - ʵ������:
 *   1. ����д���ݵ� EEPROM��
 *   2. ������ EEPROM ��ȡ���ݣ���ͨ�����ڴ�ӡ����
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_microport_eeprom_nvram.c src_microport_eeprom_nvram
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_eeprom_nvram
 * \copydoc demo_microport_eeprom_nvram.c
 */

/** [src_microport_eeprom_nvram] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_ep24cxx.h"
#include "am_nvram.h"
#include "am_zlg217_inst_init.h"
#include "demo_std_entries.h"

#define __TEST_LENTH      16                  /**< \brief ��д�ֽ��� */
#define __NVRAM_SEG_NAME  "microport_eeprom"  /**< \brief NVRAM ��������� */
#define __NVRAM_SEG_UNIT  0                   /**< \brief NVRAM ����ε�Ԫ�� */

/**
 * \brief MicroPort EEPROM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zlg217_core_microport_eeprom_nvram_entry (void)
{
    AM_DBG_INFO("demo am217_core microport eeprom nvram!\r\n");

    am_microport_eeprom_nvram_inst_init();

    demo_std_nvram_entry(__NVRAM_SEG_NAME, __NVRAM_SEG_UNIT, __TEST_LENTH);
}
/** [src_microport_eeprom_nvram] */

/* end of file */
