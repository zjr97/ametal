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
 * \brief IAP ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��� UID, PID, Boot ����汾�ź�ǩ����
 *   2. ���� RAM �� FLASH��������ҳ���ݣ�
 *   3. ����������죬˵�� IAP ָ����ִ�в�������
 *
 *       ��������ָ�������ſɽ��� IAP �� ISP ָ����������⣬�ɽ���ҳ������������С
 *       Ϊ 1KB��ҳ��СΪ 64 �ֽڣ�һ���������� 16 ҳ������ 0 ��ҳ 0 λ�� 0x0000 0000
 *       ��ַ��16KB flash ���������� 0-15��32KB flash �������� 0-31.
 *
 *       �������       |    ������С[kB]      |    ҳ���      |         ��ַ��Χ
 *    ------------- | ---------------- | ----------- | -------------------------
 *           0      |        1         |    0 -  15  | 0x0000 0000 - 0x0000 03ff
 *           1      |        1         |   16 -  31  | 0x0000 0400 - 0x0000 07ff
 *           2      |        1         |   32 -  47  | 0x0000 0800 - 0x0000 0bff
 *           3      |        1         |   48 -  63  | 0x0000 0c00 - 0x0000 0fff
 *           4      |        1         |   64 -  79  | 0x0000 1000 - 0x0000 13ff
 *           5      |        1         |   80 -  95  | 0x0000 1400 - 0x0000 17ff
 *           6      |        1         |   96 - 111  | 0x0000 1800 - 0x0000 1bff
 *           7      |        1         |  112 - 127  | 0x0000 1c00 - 0x0000 1fff
 *           8      |        1         |  128 - 143  | 0x0000 2000 - 0x0000 23ff
 *           9      |        1         |  144 - 159  | 0x0000 2400 - 0x0000 27ff
 *          10      |        1         |  160 - 175  | 0x0000 2800 - 0x0000 2bff
 *          11      |        1         |  176 - 191  | 0x0000 2c00 - 0x0000 2fff
 *          12      |        1         |  192 - 207  | 0x0000 3000 - 0x0000 33ff
 *          13      |        1         |  208 - 223  | 0x0000 3400 - 0x0000 37ff
 *          14      |        1         |  224 - 239  | 0x0000 3800 - 0x0000 3bff
 *          15      |        1         |  240 - 255  | 0x0000 3c00 - 0x0000 3fff
 *          16      |        1         |  256 - 271  | 0x0000 4000 - 0x0000 43ff
 *          17      |        1         |  272 - 287  | 0x0000 4400 - 0x0000 47ff
 *          18      |        1         |  288 - 303  | 0x0000 4800 - 0x0000 4bff
 *          19      |        1         |  304 - 319  | 0x0000 4c00 - 0x0000 4fff
 *          20      |        1         |  320 - 335  | 0x0000 5000 - 0x0000 53ff
 *          21      |        1         |  336 - 351  | 0x0000 5400 - 0x0000 57ff
 *          22      |        1         |  352 - 367  | 0x0000 5800 - 0x0000 5bff
 *          23      |        1         |  368 - 383  | 0x0000 5c00 - 0x0000 5fff
 *          24      |        1         |  384 - 399  | 0x0000 6000 - 0x0000 63ff
 *          25      |        1         |  400 - 415  | 0x0000 6400 - 0x0000 67ff
 *          26      |        1         |  416 - 431  | 0x0000 6800 - 0x0000 6bff
 *          27      |        1         |  432 - 447  | 0x0000 6c00 - 0x0000 6fff
 *          28      |        1         |  448 - 463  | 0x0000 7000 - 0x0000 73ff
 *          29      |        1         |  464 - 479  | 0x0000 7400 - 0x0000 77ff
 *          30      |        1         |  480 - 495  | 0x0000 7800 - 0x0000 7bff
 *          31      |        1         |  496 - 511  | 0x0000 7c00 - 0x0000 7fff
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ��������Ҫ�̽� J7 ����ñ�����ܱ� PIO0_24 ���ơ����ұ����� am_prj_config.h
 *       �ڽ� AM_CFG_BUZZER_ENABLE ����Ϊ 1�����ú��Ѿ�Ĭ������Ϊ 1�� �û������ٴ�
 *       ���ã�
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_iap.c src_lpc824_hw_iap
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-12  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_iap
 * \copydoc demo_lpc824_hw_iap.c
 */

/** [src_lpc824_hw_iap] */
#include "ametal.h"
#include "am_int.h"
#include "am_buzzer.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_iap.h"

/**
 * \brief ���һҳ����
 *
 * \param[in] sector_num     ������ţ�ȡֵ��Χ��0 ~ 31 (32KB flash)
 * \param[in] page_in_sector ҳ��ţ�ȡֵ��Χ��0 ~ 15
 *
 * \return ��
 */
am_local void __print_page_data (uint32_t sector_num, uint8_t page_in_sector)
{
    uint8_t *p_data   = NULL;
    uint32_t page_num = 0;
    uint32_t i        = 0;

    if (sector_num > 31 || page_in_sector > 15) {
        return;
    }

    page_num = sector_num * 16 + page_in_sector;

    AM_DBG_INFO("The page %d in sector %d data is : \r\n",
               page_in_sector, sector_num);

    p_data = (uint8_t *)(64 * page_num); /* ҳ����ʼ��ַ */

    /* һҳ�Ĵ�СΪ 64 �ֽ� */
    for (i = 0; i < 64; i++) {
        AM_DBG_INFO("%3d  ",*p_data++);
        if (((i+1) % 8) == 0) {
            AM_DBG_INFO("\r\n");
        }
    }
    AM_DBG_INFO("\r\n");
}

/**
 * \brief �������
 */
void demo_lpc824_hw_iap_entry (void)
{
    uint32_t               i            = 0;
    uint8_t                boot_ver[2]  = {0};
    uint16_t               boot_ver_tmp = 0;
    uint32_t               uid[4]       = {0};
    uint32_t               pid          = 0;
    uint32_t               key          = 0;
    amhw_lpc82x_iap_stat_t stat;

    /* �� RAM �е����ݿ����� FLASH ʱ��RAM ��ַ�������ֶ��� */
#if defined(__CC_ARM)
    __align(4) unsigned char data[256];
#elif defined(__GNUC__)
    __attribute__((aligned(4))) unsigned char data[256];
#endif

    /* FLASH ��������ʱ����ֹ���жϴ�ϣ���Ҫ���ж� */
    key = am_int_cpu_lock();

    /* ��ȡ UID */
    stat = amhw_lpc82x_iap_unique_id_read(uid);

    if (stat != AMHW_LPC82X_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("Read UID failed : %d \r\n",stat);
        am_buzzer_beep(500);
    } else {
        AM_DBG_INFO("uid = 0x%04x%04x%04x%04x\r\n",
                    uid[3],
                    uid[2],
                    uid[1],
                    uid[0]);
    }

    /* ��ȡ PID */
    pid = amhw_lpc82x_iap_part_id_read();
    AM_DBG_INFO("PID = 0x%x\r\n", pid);

    /* ��ȡ boot ����汾�� */
    boot_ver_tmp = amhw_lpc82x_iap_boot_ver_read();

    boot_ver[1] = boot_ver_tmp >> 8;
    boot_ver[0] = boot_ver_tmp;

    AM_DBG_INFO("Boot Code version: %d.%d \r\n", boot_ver[1], boot_ver[0]);

    /*
     * �����ݴ� RAM ������ FLASH��
     * ������ţ�31����ַ��Χ��0x0000 7C00 - 0x0000 7FFF��
     */
    for (i = 0; i < 256; i++) {
        data[i] = i;
    }

    /* ׼������ 31 */
    amhw_lpc82x_iap_prepare(31, 31);

    /* �������� 31 */
    amhw_lpc82x_iap_erase_sector(31, 31);

    /* ��������Ƿ�հ� */
    stat = amhw_lpc82x_iap_blank_check(31, 31);

    if (stat != AMHW_LPC82X_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("The Sector 31 is not blank\r\n");
        am_buzzer_beep(500);

    } else {
        AM_DBG_INFO("The Sector 31 is blank! \r\n");
    }

    amhw_lpc82x_iap_prepare(31, 31);

    /*
     * �����ݴ� RAM ������ FLASH��
     * ���� 31 ����ʼ��ַ�� 0x0000 7C00��
     */
    stat = amhw_lpc82x_iap_copy(0x00007C00, (uint32_t)&data[0], 256);

    if (stat != AMHW_LPC82X_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("Copy to FLASH failed \r\n");
        am_buzzer_beep(500);
    } else {
        AM_DBG_INFO("Copy to FLASH success \r\n");
    }

    stat = amhw_lpc82x_iap_compare(0x00007C00, (uint32_t)&data[0], 256);

    if (stat != AMHW_LPC82X_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("The data compare failed,%d \r\n", stat);
        am_buzzer_beep(500);
    } else {
        AM_DBG_INFO("The data compare success,the data in flash as follow :\r\n");
        __print_page_data(31, 0);
        __print_page_data(31, 1);
        __print_page_data(31, 2);
        __print_page_data(31, 3);
    }

    amhw_lpc82x_iap_prepare(31, 31);

    /* ����ҳ 496 - 499
     * ���� 31 ����ʼҳ�� 496(31 * 16)
     * ���� 31 ǰ4ҳ�����ݶ�����Ϊ��0xFF
     */
    amhw_lpc82x_iap_erase_page(496, 496 + 3);

    if (stat != AMHW_LPC82X_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("The page erase failed,%d \r\n",stat);
        am_buzzer_beep(500);

    } else {
        AM_DBG_INFO("The page erase success,the data in flash as follow :\r\n");

        /* ��������ӦΪ 255 */
        __print_page_data(31, 0);
        __print_page_data(31, 1);
        __print_page_data(31, 2);
        __print_page_data(31, 3);
    }

    /* ����ʹ���ж� */
    am_int_cpu_unlock(key);

    AM_FOREVER {
        am_led_on(LED0);
        am_mdelay(500);
        am_led_off(LED0);
        am_mdelay(500);
    }
}
/** [src_lpc824_hw_iap] */

/* end of file */
