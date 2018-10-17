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
 * \brief fm175xx��B�࿨��ID��ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��B�࿨����������֤���������߸�Ӧ����
 *
 * - ʵ������
 *   1. ����Ƭ�������߸�Ӧ���󴮿ڴ�ӡ����Ƭ��ID��
 *
 * - ע�⣺
 *   1. ����Ƭ�������߸�Ӧ���󴮿�ֻ�ܴ�ӡһ��ID����Ҫ�ٴδ�ӡID��Ҫ����Ƭ�Ƴ���Ӧ��������;
 *   2. fm17510��֧��B�࿨�Ķ�д��
 *
 * \par Դ����
 * \snippet demo_am116_dr_fm175xx_piccb_read_id.c src_am116_dr_fm175xx_piccb_read_id
 *
 * \internal
 * \par Modification history
 * - 1.00 18-02-05  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_fm175xx_piccb_read_id
 * \copydoc demo_am116_dr_fm175xx_piccb_read_id.c
 */

/** [src_am116_dr_fm175xx_piccb_read_id] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_hwconf_fm175xx.h"
#include "demo_components_entries.h"

/**
 * \brief B�࿨����������
 */
void demo_am116_core_dr_fm175xx_piccb_read_id (void)
{
    am_fm175xx_handle_t handle = am_fm175xx_inst_init();

    demo_fm175xx_piccb_read_id(handle);
}

/** [src_am116_dr_fm175xx_piccb_read_id] */

/* end of file */
