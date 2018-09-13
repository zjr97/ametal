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
 * - �������裺
 *   1. �� MicroPort EEPROM ������ӵ� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ����д���ݵ� EEPROM��
 *   2. ������ EEPROM ��ȡ���ݣ���ͨ�����ڴ�ӡ����
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \par Դ����
 * \snippet demo_ep24cxx.c src_ep24cxx
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_ep24cxx
 * \copydoc demo_ep24cxx.c
 */

/** [src_ep24cxx] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_ep24cxx.h"

#define __BUF_SIZE  16    /**< \brief ��������С */

/**
 * \brief �������
 */
void demo_ep24cxx_entry (am_ep24cxx_handle_t ep24cxx_handle, int32_t test_lenth)
{
    uint8_t i;
    uint8_t wr_buf[__BUF_SIZE] = {0}; /* д���ݻ��涨�� */
    uint8_t rd_buf[__BUF_SIZE] = {0}; /* �����ݻ��涨�� */
    int     ret;

    if (__BUF_SIZE < test_lenth) {
        test_lenth = __BUF_SIZE;
    }

    /* ��䷢�ͻ����� */
    for (i = 0;i < test_lenth; i++) {
        wr_buf[i] = (i + 6);
    }

    /* д���� */
    ret = am_ep24cxx_write(ep24cxx_handle,
                           0x00,
                          &wr_buf[0],
                           test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_ep24cxx_write error(id: %d).\r\n", ret);
        return;
    }
    am_mdelay(5);

    /* ������ */
    ret = am_ep24cxx_read(ep24cxx_handle,
                          0x00,
                         &rd_buf[0],
                          test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_ep24cxx_read error(id: %d).\r\n", ret);
        return;
    }

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0; i < test_lenth; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is 0x%02x\r\n", i ,rd_buf[i]);

        /* У��ʧ�� */
        if(wr_buf[i] != rd_buf[i]) {
            AM_DBG_INFO("verify failed at index %d.\r\n", i);
            break;
        }
    }

    if (test_lenth == i) {
        AM_DBG_INFO("verify success!\r\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_ep24cxx] */

/* end of file */
