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
 * \brief ���������̣�ͨ����׼�ӿ�ʵ��
 *
 *
 * - �������裺
 *   1. �̽�J7����ñ��PIOC_3���Ʒ�����;
 *   2. ��Ҫ��am_prj_config.hͷ�ļ���ʹ�ܺ�AM_CFG_BUZZER_ENABLE��
 *
 * - ʵ������
 *   1. ��������0.5s��ʱ�������С�
 *
 * \warning ������ռ����TPM0_PWM2��PIOC_3���ţ�������˸÷��������Ͳ��ܽ�TPM0����
 *          Ϊ������PWM���ܡ�����Ҫ��Ӧ�ó�����ʹ�÷�PWM���ܣ��Ͳ��ܵ��÷�������API��
 *          ��Ҫ��am_prj_config.hͷ�ļ�����ܺ�AM_CFG_BUZZER_ENABLE��
 *       
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_buzzer.c src_amks16z_core_std_buzzer
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-30  sdy, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_amks16z_core_if_std_buzzer
 * \copydoc demo_amks16z_core_std_buzzer.c
 */
 
/** [src_amks16z_core_std_buzzer] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_board.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_buzzer_entry (void)
{  
    AM_DBG_INFO("demo amks16z_core std buzzer!\r\n");

    demo_std_buzzer_entry();
}

/** [src_amks16z_core_std_buzzer] */

/* end of file */
