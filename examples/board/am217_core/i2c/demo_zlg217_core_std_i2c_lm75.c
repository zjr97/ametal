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
 * \brief I2C ������ LM75 ��������ȡ�¶�ֵ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������:
 *   1. �� J14 �� KEY �� RES �̽���һ��ʹ�ð��� RES ����ͨ���ʵ��裻
 *   2. �̽�����ñ J11 �� J13��ʹ I2C1 �� LM75 ���ӡ�
 *
 * - ʵ������:
 *   1. ��������¶�ֵ��
 *   2. ���� RES ��������һ�������������¶�ֵ���ߡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zlg217_std_i2c_lm75.c src_zlg217_std_i2c_lm75
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-10 win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_i2c_lm75
 * \copydoc demo_zlg217_std_i2c_lm75.c
 */

/** [src_zlg217_std_i2c_lm75] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_temp.h"
#include "am_hwconf_lm75.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_std_i2c_lm75_entry (void)
{
    am_kprintf("demo am217_core std i2c lm75!\r\n");

    demo_std_i2c_lm75_entry(am_temp_lm75_inst_init());

}
/** [src_zlg217_std_i2c_lm75] */

/* end of file */
