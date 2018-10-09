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
 * \brief MicroPort EEPROM ���̣�ͨ�� NVRAM �ӿ�ʵ�֡�
 *
 * ���� FM24C02 �� EEPROM �ǵ��͵ķ���ʧ�Դ洢�������ʹ�� NVRAM����
 * ��ʧ�Դ洢������׼�ӿڶ�д���ݾ�������ľ���������ˡ�
 *
 * - ��������:
 *   1. �� MicroPort EEPROM ������ӵ� AMKS16RFID �� MicroPort �ӿڡ�
 *
 * - ʵ������:
 *   1. ����д���ݵ� EEPROM��
 *   2. ������ EEPROM ��ȡ���ݣ���ͨ�����ڴ�ӡ����
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_1 �������� PC ���ڵ� TXD��
 *    PIOA_2 �������� PC ���ڵ� RXD��
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
#include "am_kl26_inst_init.h"
#include "am_hwconf_microport.h"
#include "demo_std_entries.h"

/**
 * \brief MicroPort EEPROM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_eeprom_nvram_entry (void)
{
    AM_DBG_INFO("demo amks16z_core microport eeprom nvram!\r\n");

    am_microport_eeprom_nvram_inst_init();

    demo_std_nvram_entry("microport_eeprom", 0, 16);
}

/** [src_microport_eeprom_nvram] */

/* end of file */
