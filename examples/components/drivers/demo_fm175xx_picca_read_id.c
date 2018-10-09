/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief fm175xx�������ͺ�ID��ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ���ڴ�ӡ����Ƭ���ͺźͿ��ż���Ƭ��Ϣ
 *
 * \par Դ����
 * \snippet demo_fm175xx_picca_read_id.c src_fm175xx_picca_read_id
 *
 * \internal
 * \par Modification history
 * - 1.00 18-08-07  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fm175xx_picca_read_id
 * \copydoc demo_fm175xx_picca_read_id.c
 */

/** [src_fm175xx_picca_read_id] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_vdebug.h"

/**
 * \brief A�࿨�������ͺͿ�������
 */
void demo_fm175xx_picca_read_id (am_fm175xx_handle_t handle)
{
    uint8_t              tag_type[2]  = { 0 };      /* ATQA */
    uint8_t              uid[10]      = { 0 };      /* UID */
    uint8_t              uid_real_len =   0;         /* ���յ���UID�ĳ��� */
    uint8_t              sak[3]       = { 0 };      /* SAK */

    while (1) {
        int i ;
        if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                                  (handle,
                                                    AM_FM175XX_PICCA_REQ_IDLE,
                                                    tag_type,
                                                    uid,
                                                   &uid_real_len,
                                                    sak)) {
            am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

            /* ��ӡUID */
            am_kprintf("UID  :");
            for (i = 0; i < uid_real_len; i++) {
                am_kprintf("%02x ", uid[i]);
            }
            am_kprintf("\n");

            /* ��ӡSAK */
            am_kprintf("SAK  :");
            for (i = 4; i <= uid_real_len; i+=3) {
                am_kprintf("%02x ", sak[(i - 4) / 3]);
            }
            am_kprintf("\n\n");
        }
    }
}

/** [demo_fm175xx_picca_read_id] */

/* end of file */



