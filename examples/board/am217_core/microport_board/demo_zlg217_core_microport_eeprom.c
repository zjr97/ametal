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
 * \brief MicroPort EEPROM ���̣�ͨ����׼�ӿ�ʵ��
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
 * \snippet demo_microport_eeprom.c src_microport_eeprom
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_eeprom
 * \copydoc demo_microport_eeprom.c
 */

/** [src_microport_eeprom] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_ep24cxx.h"
#include "am_zlg217_inst_init.h"


#define __TEST_LENTH      16    /**< \brief ��д�ֽ��� */

/**
 * \brief MicroPort EEPROM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_zlg217_core_microport_eeprom_entry (void)
{
    am_ep24cxx_handle_t ep24cxx_handle    = am_microport_eeprom_inst_init();

    AM_DBG_INFO("demo am217_core microport eeprom!\r\n");

    demo_ep24cxx_entry(ep24cxx_handle, __TEST_LENTH);
}
/** [src_microport_eeprom] */

/* end of file */
