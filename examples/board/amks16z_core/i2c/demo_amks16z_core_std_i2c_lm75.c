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
 * \brief I2C������LM75��������ȡ�¶�ֵ��ʾ����
 *
 * - ��������:
 *       1. ��J11��J13������ñ���ӣ�
 *       2. ���������������ӡ�
 *
 * - ʵ������:
 *       ��LM75���������¶�ֵ�򴮿ڴ�ӡ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_i2c_lm75.c src_amks16z_core_std_i2c_lm75
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-21 ari, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_std_i2c_lm75
 * \copydoc demo_amks16z_core_std_i2c_lm75.c
 */
 
/** [src_amks16z_core_std_i2c_lm75] */
/*******************************************************************************
  includes
*******************************************************************************/
#include "ametal.h"
#include "am_vdebug.h"
#include "am_i2c.h"
#include "am_kl26_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief ���Ժ������
 */
void demo_amks16z_core_std_i2c_lm75_entry (void)
{
    am_temp_handle_t handle;

    AM_DBG_INFO("demo amks16z_core std i2c lm75!\r\n");

    handle = am_temp_lm75_inst_init();

    demo_std_i2c_lm75_entry(handle);

}



/** [src_amks16z_core_std_i2c_lm75] */

/* end of file */
