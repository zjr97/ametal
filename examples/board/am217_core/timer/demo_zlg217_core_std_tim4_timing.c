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
 * \brief TIM4 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ�ʷ�ת��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. 16 λ��ʱ����ʱ����ֵ��Ϊ 65536 �ı�������ʱ����һЩƫ�
 *    3. ���� TIM4 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *       am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SOFTIMER_ENABLE
 *       �� AM_CFG_SYSTEM_TICK_ENABLE ����Ϊ 0��
 *
 *
 * \par Դ����
 * \snippet demo_zlg217_std_tim4_timing.c src_zlg217_std_tim4_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-25  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_tim4_timing
 * \copydoc demo_zlg217_std_tim4_timing.c
 */

/** [src_zlg217_std_tim4_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg217_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_tim4_timing_entry (void)
{

    AM_DBG_INFO("demo am217_core std tim16 timing!\r\n");

    demo_std_timer_timing_entry(am_zlg217_tim4_timing_inst_init(), 0);

}
/** [src_zlg217_std_tim4_timing] */

/* end of file */
