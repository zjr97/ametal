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
 * \brief fm175xx��B�࿨��ID��ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��B�࿨����������֤���������߸�Ӧ����
 *
 * - ʵ������
 *   1. ����Ƭ�������߸�Ӧ���󴮿ڴ�ӡ����Ƭ��ID��
 *
 * - ע�⣺
 *   1. ����Ƭ�������߸�Ӧ���󴮿�ֻ�ܴ�ӡһ��ID����Ҫ�ٴδ�ӡID��Ҫ����Ƭ�Ƴ���Ӧ��������;
 *   2. fm17510��֧��B�࿨�Ķ�д��
 *
 * \par Դ����
 * \snippet demo_fm175xx_piccb_read_id.c src_fm175xx_piccb_read_id
 *
 * \internal
 * \par Modification history
 * - 1.00 18-02-05  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fm175xx_piccb_read_id
 * \copydoc demo_fm175xx_piccb_read_id.c
 */

/** [src_fm175xx_piccb_read_id] */
#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_vdebug.h"
#include "am_delay.h"
 
/**
 * \brief B�࿨����������
 */
void demo_fm175xx_piccb_read_id (am_fm175xx_handle_t handle)
{ 
    uint8_t uid[8]     = { 0 };       /* UID */
    uint8_t i;

    while (1) {
        if (!am_fm175xx_piccb_active(handle,
                                     AM_FM175XX_PICCB_REQ_IDLE,
                                     uid)) {
            am_kprintf("UID : ");
            for (i = 0; i < 8; i++) {
                am_kprintf("%02x ", uid[i]);
            }
            am_kprintf("\r\n");
        }
        am_mdelay(500);
    }
}

/** [src_fm175xx_piccb_read_id] */

/* end of file */
