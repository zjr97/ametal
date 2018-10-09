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
 * - ʵ������
 *   1. ��������¶�ֵ��
 *   2. ���� RES ��������һ�������������¶�ֵ���ߡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    2. ������Ҫ�� J14 ����ñ�� KEY �� RES �̽Ӳ���ʹ�ã�
 *    3. ��Ҫ�̽� J11 �� J13 ����ñ��I2C1 �Ż��� LM75 ���ӡ�
 *
 * \par Դ����
 * \snippet demo_am824_std_i2c_lm75.c src_am824_std_i2c_lm75
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-10 win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_i2c_lm75
 * \copydoc demo_am824_std_i2c_lm75.c
 */

/** [src_am824_std_i2c_lm75] */
#include "ametal.h"
#include "am_temp.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_std_i2c_lm75_entry (void)
{
    am_temp_handle_t handle      = NULL;

    handle = am_temp_lm75_inst_init();
  
    demo_std_i2c_lm75_entry(handle);

}
/** [src_am824_std_i2c_lm75] */

/* end of file */
