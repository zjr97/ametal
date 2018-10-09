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
 * \brief
 *
 * - �������裺
 *      - PTC1�������32.786kHz��ʱ������
 *      - ʹ�õ��Դ��ڴ�ӡ
 *
 *
 * - ʵ������
 *      - ���ڴ�ӡ�����õ�ʱ��
 *      - �Ժ�ÿ���ӡһ��ʱ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_rtc.c src_amks16z_core_std_rtc
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_std_rtc
 * \copydoc demo_amks16z_core_std_rtc.c
 */

/** [src_amks16z_core_std_rtc] */
#include "am_kl26_inst_init.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_fsl_rtc.h"
#include "am_board.h"
#include "demo_std_entries.h"

/**
 * \brief AMetal Ӧ�ó������
 */
void demo_amks16z_core_std_rtc_entry (void)
{
    /** RTC ������ */
    am_rtc_handle_t rtc_handler = am_kl26_rtc_inst_init();

    demo_std_rtc_entry(rtc_handler);
}

/** [src_amks16z_core_std_rtc] */

/* end of file */
