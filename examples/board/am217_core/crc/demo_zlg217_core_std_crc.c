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
 * \brief CRC ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������ �� The crc-16 init failed
 *
 *                          The crc-ccitt init failed
 *
 *                          CRC-32 result is          : 0x9ae0daaf
 *
 * \note
 *    1. ֻ֧�� 4 �ֽڶ��������(CRC-32)�������ֽ��� % 4 == 0��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zlg217_std_crc.c src_zlg217_std_crc
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_crc
 * \copydoc demo_zlg217_std_crc.c
 */

/** [src_zlg217_std_crc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg_crc.h"
#include "am_zlg217_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_crc_entry (void)
{
    AM_DBG_INFO("demo am217_core std crc!\r\n");    

    am_crc_handle_t crc_handle;

    crc_handle = am_zlg217_crc_inst_init();

    demo_std_crc_entry(crc_handle);
}
/** [src_zlg217_std_crc] */

/* end of file */
