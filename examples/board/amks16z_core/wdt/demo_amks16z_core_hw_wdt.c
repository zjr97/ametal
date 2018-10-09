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
 * \brief WDT ι���͸�λ���ӣ�ͨ��Ӳ����ʵ��
 *
 * - ʵ������
 *   1. ���Ź����ó�ʱʱ��Ϊ256ms����ʱ50ms��ι������������ִ�У�
 *      ���ڴ�ӡι����Ϣ��
 *   2. ����ִ�е���ʱ1sʱ��ι����ʱ��ϵͳ��λ���������¿�ʼִ�С�
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_wdt.c src_amks16z_core_hw_wdt
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-30  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_wdt
 * \copydoc demo_amks16z_core_hw_wdt.c
 */

/** [src_kl26_hw_wdt] */
#include "ametal.h"
#include "am_delay.h"
#include "am_uart.h"
#include "am_vdebug.h"
#include "am_kl26_inst_init.h"
#include "demo_fsl_entrys.h"

/**
 * \brief WDT��ں�����HW��ʵ��
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 * \return ��
 */
void demo_amks16z_core_hw_wdt_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw wdt!\r\n");

    demo_kl26_hw_wdt_entry();
}

/** [src_amks16z_core_hw_wdt] */

/* end of file */
