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
 * \brief CRC ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ "CRC-16 result is     : 0xbb3d\r\n"��
 *   2. ���ڴ�ӡ "CRC-CCITT result is  : 0x29b1\r\n"��
 *   3. ���ڴ�ӡ "CRC-32 result is     : 0xcbf43926\r\n"��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_hw_crc.c src_am824_hw_crc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-7-13  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_crc
 * \copydoc demo_am824_hw_crc.c
 */

/** [src_am824_hw_crc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"
#include "am_lpc82x_clk.h"
#include "hw/amhw_lpc_crc.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/** \brief CRC �������� */
am_local char __g_data_test[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

/** \brief CRC �������ݵĳ��� */
am_local uint32_t __g_length_test = AM_NELEMENTS(__g_data_test);

/**
 * \brief �������
 */
void demo_am824_core_hw_crc_entry (void)
{

    am_kprintf("demo am824_core hw crc!\r\n");

    /* ʹ�ܲ���λ CRC ʱ�� */
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_CRC);

    demo_lpc_hw_crc_entry(LPC82X_CRC, 
                          __g_data_test, 
                          __g_length_test);
}
/** [src_am824_hw_crc] */

/* end of file */
