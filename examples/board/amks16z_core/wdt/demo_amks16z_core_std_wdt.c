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
 * \brief WDT ι���͸�λ���ӣ�ͨ��������ʵ��
 *
 * - ʵ������
 *   1. ���Ź����ó�ʱʱ��Ϊ256ms����ʱ50ms��ι������������ִ�У�
 *      ���ڴ�ӡι����Ϣ��
 *   2. ����ִ�е���ʱ1sʱ��ϵͳ��λ���������¿�ʼִ�С�
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_wdt.c src_amks16z_core_std_wdt
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-30  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_std_wdt
 * \copydoc demo_amks16z_core_std_wdt.c
 */

/** [src_amks16z_core_std_wdt] */
#include "ametal.h"
#include "am_uart.h"
#include "am_wdt.h"
#include "am_delay.h"
#include "am_kl26_inst_init.h"
#include "demo_amks16z_core_all_entries.h"
#include "demo_std_entries.h"

#define   TIME_OUT_MS     256       /**< \brief ��ʱʱ�� */
#define   FEED_TIME_MS    300       /**< \brief ι��ʱ�� */

/**
 * \brief ���Ź���ں�������׼�ӿڲ�ʵ��
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 * \return ��
 */
void demo_amks16z_core_std_wdt_entry (void)
{
    am_wdt_handle_t  handle = NULL;     /**< \brief ���Ź���׼������ */

    /* ��ʼ��WDT����ȡWDT���ֵ */
    handle = am_kl26_wdt_inst_init();

    demo_std_wdt_entry(handle, TIME_OUT_MS, FEED_TIME_MS);
}

/** [src_amks16z_core_std_wdt] */

/* end of file */
