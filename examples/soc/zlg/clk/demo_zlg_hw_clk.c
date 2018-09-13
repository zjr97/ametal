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
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡָ��������Ƶ�ʡ�
 * 
 * \par Դ����
 * \snippet demo_zlg_hw_clk.c src_zlg_hw_clk
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-7-13  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_hw_clk
 * \copydoc demo_zlg_hw_clk.c
 */

/** [src_zlg_hw_clk] */
#include "ametal.h"
#include "am_clk.h"
#include "am_vdebug.h"

/**
 * \brief �������
 */
void demo_zlg_hw_clk_entry (am_clk_id_t *p_clk_id_buf, uint8_t buf_lenth)
{
    int32_t  i;
    uint32_t clk = 0;

    for (i = 0; i < buf_lenth; i++) {
        clk = am_clk_rate_get(p_clk_id_buf[i]);
        AM_DBG_INFO("CLK ID %d = %d\r\n", p_clk_id_buf[i], clk);
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg_hw_clk] */

/* end of file */
