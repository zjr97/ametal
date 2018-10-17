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
 * \brief fm175xxʹ�ò�ͬ�ķ�����ȡ��Ƭ��Ϣ��ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. �����Ƭ֧��haltָ���ÿ�����½����������߸�Ӧ���󣬴���ֻ�ܴ�ӡ�����ο�Ƭ��Ϣ��
 *   2. �����Ƭ��֧��haltָ��򽫿��������߸�Ӧ���󣬴������������ϵĴ�ӡ����Ƭ��Ϣ��
 *
 * \par Դ����
 * \snippet demo_am116_dr_fm175xx_picca_halt.c src_am116_dr_fm175xx_picca_halt
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_fm175xx_picca_halt
 * \copydoc demo_am116_dr_fm175xx_picca_halt.c
 */

/** [src_am116_dr_fm175xx_picca_halt] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_hwconf_fm175xx.h"
#include "demo_components_entries.h"

/**
 * \brief A�࿨�����߿�����
 */
void demo_am116_core_dr_fm175xx_picca_halt (void)
{
    am_fm175xx_handle_t handle = am_fm175xx_inst_init();

    demo_fm175xx_picca_halt(handle);
}

/** [src_am116_dr_fm175xx_picca_halt] */

/* end of file */
