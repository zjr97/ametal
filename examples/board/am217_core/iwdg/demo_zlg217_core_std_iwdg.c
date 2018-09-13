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
 * \brief IWDG ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �޸ĺ궨�� __IWDG_FEED_TIME_MS ��ֵ������ 1500ms(���� 5ms ���)��оƬ��λ��
 *   2. �޸ĺ궨�� __IWDG_FEED_TIME_MS ��ֵ��С�� 1500ms(���� 5ms ���)�������������С�
 *
 * \par Դ����
 * \snippet demo_zlg217_std_iwdg.c src_zlg217_std_iwdg
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-26  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_iwdg
 * \copydoc demo_zlg217_std_iwdg.c
 */

/** [src_zlg217_std_iwdg] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_wdt.h"
#include "am_zlg217_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief ���Ź���ʱʱ��
 *
 * \note ��Ϊ���Ź��ڲ�ʱ��WDTOSC����������__IWDG_TIMEOUT_MS��Ӧ��ʵ��ʱ��
 *       ������
 */
#define __IWDG_TIMEOUT_MS       1500

/**
 * \brief ���Ź�ι��ʱ�䣬��ι��ʱ�䳬��IWDG_TIMEOUT_MS��ֵ������5ms���ϣ�,
 *        ��������Ź��¼���
 */
#define __IWDG_FEED_TIME_MS     2000

/**
 * \brief �������
 */
void demo_zlg217_core_std_iwdg_entry (void)
{
    AM_DBG_INFO("demo am217_core std iwdg!\r\n");

    demo_std_wdt_entry(am_zlg217_iwdg_inst_init(),
                        __IWDG_TIMEOUT_MS, 
                        __IWDG_FEED_TIME_MS);
}
/** [src_zlg217_std_iwdg] */

/* end of file */
