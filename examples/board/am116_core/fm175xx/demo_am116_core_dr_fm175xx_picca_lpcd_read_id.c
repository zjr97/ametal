/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief fm175xx�������ͺ�ID��ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ���ڴ�ӡ����Ƭ���ͺźͿ��ż���Ƭ��Ϣ
 *
 * \par Դ����
 * \snippet demo_am116_dr_fm175xx_picca_read_id.c src_am116_dr_fm175xx_picca_read_id
 *
 * \internal
 * \par Modification history
 * - 1.00 18-08-07  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_am116_core_dr_fm175xx_picca_read_id
 * \copydoc demo_am116_core_dr_fm175xx_picca_read_id.c
 */

/** [src_am116_dr_fm175xx_picca_read_id] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_hwconf_fm175xx.h"
#include "demo_components_entries.h"

/**
 * \brief A��LPCDģʽ ���������ͺͿ�������
 */
void demo_am116_core_dr_fm175xx_picca_lpcd_read_id (void)
{
    am_fm175xx_handle_t handle = am_fm175xx_inst_init();

    demo_fm175xx_picca_lpcd_mode(handle);
}

/** [demo_am116_core_dr_fm175xx_picca_read_id] */

/* end of file */



