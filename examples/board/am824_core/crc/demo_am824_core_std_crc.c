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
 *   1. ���ڴ�ӡ "CRC-16 result is     : 0xbb3d\r\n"��
 *   2. ���ڴ�ӡ "CRC-CCITT result is  : 0x29b1\r\n"��
 *   3. ���ڴ�ӡ "CRC-32 result is     : 0xcbf43926\r\n"��
 *   4. LED �� 0.5s ��ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_std_crc.c src_am824_std_crc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-09  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_crc
 * \copydoc demo_am824_std_crc.c
 */

/** [src_am824_std_crc] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_lpc_crc.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_std_crc_entry (void)
{
    am_crc_handle_t crc_handle = NULL;

    am_kprintf("demo am824_core std crc!\r\n");
    crc_handle = am_lpc82x_crc_inst_init();

    demo_std_crc_entry(crc_handle);
}
/** [src_am824_std_crc] */

/* end of file */
