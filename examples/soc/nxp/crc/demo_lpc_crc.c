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
 * \snippet demo_lpc_hw_crc.c src_lpc_hw_crc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-7-13  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_crc
 * \copydoc demo_lpc_hw_crc.c
 */

/** [src_lpc_hw_crc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc_crc.h"
#include "demo_nxp_entries.h"

/**
 * \brief CRC-CCITT ����
 *
 * \param[in] p_data ָ�� CRC �������ݻ�������ָ��
 * \param[in] nbytes �������ݵĳ���
 *
 * \return CRC-CCITT ����Ľ��
 */
am_local uint16_t __crc_ccitt (amhw_lpc_crc_t     *p_hw_crc, 
                               am_const uint8_t   *p_data, 
                               uint32_t            nbytes)
{

    /* û�б�־��Ҫ��λ����־ֵΪ 0 */
    amhw_lpc_crc_mode_set(p_hw_crc, AMHW_LPC_CRC_POLY_CCITT, 0);

    amhw_lpc_crc_seed_set(p_hw_crc, 0xFFFF);

    amhw_lpc_crc_data8_write(p_hw_crc, p_data, nbytes);

    return amhw_lpc_crc_sum_get(p_hw_crc);
}

/**
 * \brief CRC-16 ����
 *
 * \param[in] p_data ָ�� CRC �������ݻ�������ָ��
 * \param[in] nbytes �������ݵĳ���
 *
 * \return CRC-16 ����Ľ��
 */
am_local uint16_t __crc_16 (amhw_lpc_crc_t     *p_hw_crc, 
                            am_const uint8_t   *p_data, 
                            uint32_t            nbytes)
{
    amhw_lpc_crc_mode_set(p_hw_crc,
                          AMHW_LPC_CRC_POLY_CRC16,
                          AMHW_LPC_CRC_MODE_WRDATA_BIT_RVS |
                          AMHW_LPC_CRC_MODE_SUM_BIT_RVS);

    amhw_lpc_crc_seed_set(p_hw_crc, 0x0000);

    amhw_lpc_crc_data8_write(p_hw_crc, p_data, nbytes);

    return amhw_lpc_crc_sum_get(p_hw_crc);
}

/**
 * \brief CRC-32 ����
 *
 * \param[in] p_data ָ�� CRC �������ݻ�������ָ��
 * \param[in] nbytes �������ݵĳ���
 *
 * \return CRC-32 ����Ľ��
 */
am_local uint32_t __crc_32 (amhw_lpc_crc_t     *p_hw_crc, 
                            am_const uint8_t   *p_data, 
                            uint32_t            nbytes)
{
    amhw_lpc_crc_mode_set(p_hw_crc,
                          AMHW_LPC_CRC_POLY_CRC32,
                          AMHW_LPC_CRC_MODE_WRDATA_BIT_RVS |
                          AMHW_LPC_CRC_MODE_SUM_BIT_RVS    |
                          AMHW_LPC_CRC_MODE_SUM_CMPL);

    amhw_lpc_crc_seed_set(p_hw_crc, 0xFFFFFFFF);

    amhw_lpc_crc_data8_write(p_hw_crc, p_data, nbytes);

    return amhw_lpc_crc_sum_get(p_hw_crc);
}


void demo_lpc_hw_crc_entry(amhw_lpc_crc_t     *p_hw_crc,
                           am_const char      *p_data, 
                           uint32_t            nbytes)
{
    uint16_t result_crc16     = 0;
    uint16_t result_crc_ccitt = 0;
    uint32_t result_crc32     = 0;
  
    /* ������ӦΪ��0xbb3d */
    result_crc16 = __crc_16(p_hw_crc, (am_const uint8_t *)p_data, nbytes);
    AM_DBG_INFO("CRC-16 result is     : 0x%x \r\n", result_crc16);

    /* ������ӦΪ��0x29b1 */
    result_crc_ccitt = __crc_ccitt(p_hw_crc, (am_const uint8_t *)p_data,
                                   nbytes);
    AM_DBG_INFO("CRC-CCITT result is  : 0x%x \r\n", result_crc_ccitt);

    /* ������ӦΪ��0xcbf43926 */
    result_crc32 = __crc_32(p_hw_crc, (am_const uint8_t *)p_data, nbytes);
    AM_DBG_INFO("CRC-32 result is     : 0x%x \r\n", result_crc32);
}
/** [src_lpc_hw_crc] */

/* end of file */
