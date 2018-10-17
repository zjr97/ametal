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
 * \brief ���Եļ�ʵ��
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ���
 * \code
 * #include "am_assert.h"
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-23  orz, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_assert.h"

void am_assert_msg (const char *msg)
{
    volatile int exit = 0;

    (void)am_kprintf(msg);

    while (0 == exit) {
    }
}

/* end of file */
