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
 * \brief TIM2 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ�ʷ�ת��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. 16 λ��ʱ����ʱ����ֵ��Ϊ 65536 �ı�������ʱ����һЩƫ�
 *
 * \par Դ����
 * \snippet demo_zlg217_std_tim2_timing.c src_zlg217_std_tim2_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-25  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_tim2_timing
 * \copydoc demo_zlg217_std_tim2_timing.c
 */

/** [src_zlg217_std_tim2_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zlg217_inst_init.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_tim2_timing_entry (void)
{
    AM_DBG_INFO("demo am217_core std tim2 timing!\r\n");

    demo_std_timer_timing_entry(am_zlg217_tim2_timing_inst_init(), 0);
}
/** [src_zlg217_std_tim2_timing] */

/* end of file */
