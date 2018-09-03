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
 * \brief ��ʱ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED0 ��˸Ƶ�� 10Hz��
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ơ�
 *
 * \par Դ����
 * \snippet demo_zlg217_std_delay.c src_zlg217_std_delay
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_delay
 * \copydoc demo_zlg217_std_delay.c
 */

/** [src_zlg217_std_delay] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_delay_entry (void)
{
    AM_DBG_INFO("The demo for delay, "
                "The delay is implement through SYSTICK\r\n");

    demo_std_delay_entry(LED0);
}
/** [src_zlg217_std_delay] */

/* end of file */
