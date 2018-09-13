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
 *
 * \par Դ����
 * \snippet demo_std_crc.c src_std_crc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-09  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_crc
 * \copydoc demo_std_crc.c
 */

/** [src_std_crc] */
#include "ametal.h"
#include "am_crc.h"
#include "am_vdebug.h"

/** \brief CRC �������� */
am_local am_const uint8_t __g_data_test[] =
                              {'1', '2', '3', '4', '5', '6', '7', '8'};

/** \brief CRC �������ݵĳ��� */
am_local uint32_t __g_length_test = AM_NELEMENTS(__g_data_test);

/**
 * \brief �������
 */
void demo_std_crc_entry (am_crc_handle_t crc_handle)
{
    uint32_t         crc_result = 0;
    am_crc_pattern_t crc_pattern;   /* ���� CRC ģ�� */

    /* ���� CRC-16 ģ�� */
    crc_pattern.width     = 16;      /* CRC ���(�磺CRC5 �Ŀ��Ϊ 5) */
    crc_pattern.poly      = 0x8005;  /* CRC ���ɶ���ʽ */
    crc_pattern.initvalue = 0x0000;  /* CRC ��ʼֵ */
    crc_pattern.refin     = AM_TRUE; /* �������������Ҫλ��ת�����ֵΪ TRUE */
    crc_pattern.refout    = AM_TRUE; /* ���������ֵ��Ҫλ��ת�����ֵΪ TRUE */
    crc_pattern.xorout    = 0x0000;  /* ������ֵ */

    /* ��ʼ�� CRC Ϊ CRC-16 ģ�� */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-16 init failed\r\n");
    } else {
        am_crc_cal(crc_handle, __g_data_test, __g_length_test);
        am_crc_final(crc_handle, &crc_result);

        /* ������ӦΪ��0xbb3d */
        AM_DBG_INFO("CRC-16 result is        : 0x%x \r\n", crc_result);
    }

    /* �ı�ģ��Ϊ CRC-CCITT ģ�� */
    crc_pattern.width     = 16;
    crc_pattern.poly      = 0x1021;
    crc_pattern.initvalue = 0xFFFF;
    crc_pattern.refin     = AM_FALSE;
    crc_pattern.refout    = AM_FALSE;
    crc_pattern.xorout    = 0x0000;

    /* ��ʼ�� CRC Ϊ CRC-CCITT ģ�� */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-ccitt init failed\r\n");
    } else {
        am_crc_cal(crc_handle, __g_data_test, __g_length_test);
        am_crc_final(crc_handle, &crc_result);

        /* ������ӦΪ��0x29b1 */
        AM_DBG_INFO("CRC-CCITT result is     : 0x%x \r\n", crc_result);
    }

    /* �ı�ģ��Ϊ CRC-32 ģ�� */
    crc_pattern.width     = 32;
    crc_pattern.poly      = 0x04C11DB7;
    crc_pattern.initvalue = 0xFFFFFFFF;
    crc_pattern.refin     = AM_TRUE;
    crc_pattern.refout    = AM_TRUE;
    crc_pattern.xorout    = 0xFFFFFFFF;

    /* ��ʼ�� CRC Ϊ CRC-32 ģ�� */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-32 init failed\r\n");
    } else {
        am_crc_cal(crc_handle, __g_data_test, __g_length_test);
        am_crc_final(crc_handle, &crc_result);

        /* ������ӦΪ��0xcbf43926 */
        AM_DBG_INFO("CRC-32 result is        : 0x%x \r\n", crc_result);
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_crc] */

/* end of file */
