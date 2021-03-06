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
 * \brief IS25XX 例程
 *
 * - 实验现象：
 *   1. 串口打印出测试结果。
 *
 * \par 源代码
 * \snippet demo_is25xx.c src_is25xx
 *
 * \internal
 * \par Modification history
 * - 1.00  18-09-03  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_is25xx
 * \copydoc demo_is25xx.c
 */

/** [src_is25xx] */
#include "ametal.h"
#include "am_delay.h"
#include "am_is25xx.h"
#include "am_vdebug.h"

#define __IS25_BUF_SIZE 512 /**< \brief 缓冲区大小 */

/**
 * \brief 例程入口
 */
void demo_is25xx_entry (am_is25xx_handle_t is25xx_handle, int32_t test_lenth)
{
    int     ret;
    uint16_t i;
    uint8_t wr_buf[__IS25_BUF_SIZE] = {0}; /* 写数据缓存定义 */
    uint8_t rd_buf[__IS25_BUF_SIZE] = {0}; /* 读数据缓存定义 */

    if (__IS25_BUF_SIZE < test_lenth) {
        test_lenth = __IS25_BUF_SIZE;
    }

    /* 填充发送缓冲区 */
    for (i = 0;i < test_lenth; i++) {
        wr_buf[i] = i;
        rd_buf[i] = 0;
    }

    /* 擦除扇区 */
    ret = am_is25xx_erase(is25xx_handle, 0x001000, test_lenth);
    if (ret != AM_OK) {
        AM_DBG_INFO("am_is25xx_erase error(id: %d).\r\n", ret);
        return;
    }
    
    /* 写数据 */
    ret = am_is25xx_write(is25xx_handle, 0x001000, &wr_buf[0], test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_is25xx_write error(id: %d).\r\n", ret);
        return;
    }
    am_mdelay(5);
    
    /* 读数据 */
    ret = am_is25xx_read(is25xx_handle, 0x001000, &rd_buf[0], test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_is25xx_read error(id: %d).\r\n", ret);
        return;
    }

    /* 校验写入和读取的数据是否一致 */
    for (i = 0; i < test_lenth; i++) {
        AM_DBG_INFO("Read FLASH the %2dth data is %2x\r\n", i ,wr_buf[i]);

        /* 校验失败 */
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
/** [src_is25xx] */

/* end of file */
