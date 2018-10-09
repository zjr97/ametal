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
 * \brief fm175xx使用不同的方法读取卡片信息，通过驱动接口实现
 *
 * - 操作步骤：
 *   1. 正确连接并配置好串口。
 *   2. 正确连接好天线。
 *   3. 将A类卡置于天线感应区。
 *
 * - 实验现象：
 *   1. 如果卡片支持halt指令，则每次重新将卡放置天线感应区后，串口只能打印出两次卡片信息。
 *   2. 如果卡片不支持halt指令，则将卡放置天线感应区后，串口能连续不断的打印出卡片信息。
 *
 * \par 源代码
 * \snippet demo_fm175xx_picca_halt.c src_fm175xx_picca_halt
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fm175xx_picca_halt
 * \copydoc demo_fm175xx_picca_halt.c
 */

/** [src_fm175xx_picca_halt] */
#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_vdebug.h"
#include "am_delay.h"

/**
 * \brief A类卡读休眠卡例程
 */
void demo_fm175xx_picca_halt (am_fm175xx_handle_t handle)
{
    uint8_t tag_type[2] = { 0 };      /* ATQA */
    uint8_t uid[10]     = { 0 };      /* UID */
    uint8_t uid_real_len = 0;         /* 接收到的UID的长度 */
    uint8_t sak[3]      = { 0 };      /* SAK */
    uint8_t i;

    while (1) {

        /* 寻所有未休眠（halt）的卡 */
        am_kprintf("read idle...\n");
        if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                         (handle,
                                          AM_FM175XX_PICCA_REQ_IDLE,
                                          tag_type,
                                          uid,
                                          &uid_real_len,
                                          sak)) {
            am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

            am_kprintf("UID  :");
            for (i = 0; i < uid_real_len; i++) {
                am_kprintf("%02x ", uid[i]);
            }
            am_kprintf("\n");
            am_kprintf("SAK  :%02x\n\n", sak[0]);

            am_fm175xx_picca_halt(handle);  /* 让卡片休眠 */
            am_kprintf("halt\n");
            am_kprintf("read halt...\n");
            /* 读所有的卡（能读到休眠的卡） */
            if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                             (handle,
                                              AM_FM175XX_PICCA_REQ_ALL,
                                              tag_type,
                                              uid,
                                              &uid_real_len,
                                              sak)) {

                am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

                am_kprintf("UID  :");
                for (i = 0; i < uid_real_len; i++) {
                    am_kprintf("%02x ", uid[i]);
                }
                am_kprintf("\n");
                am_kprintf("SAK  :%02x\n\n", sak[0]);
            }
        }
        am_mdelay(500);
    }
}

/** [src_fm175xx_picca_halt] */

/* end of file */
