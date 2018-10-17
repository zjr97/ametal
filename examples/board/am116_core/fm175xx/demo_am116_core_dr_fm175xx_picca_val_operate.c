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
 * \brief fm175xxд�����ݣ�ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ������ԿA�Կ�Ƭָ���Ŀ������֤�������֤��ͨ�����ӡkey A authent failed��
 *   2. �����֤�ɹ�������ָ���Ŀ��еĸ�ʽΪ��ֵ��ĸ�ʽ��ô�����е���ֵ��5�ٴ�ӡ������
 *   3. �����֤�ɹ�������ָ�����еĸ�ʽ������ֵ��ĸ�ʽ����ô�����ӡ��ֵ����ʱ���Խ�130�е���������
 *      ��Ϊ1�������ִ�У�ˢ��ʱ�᲻�ϵĴ�ӡͬһ�����֣�֮���ٽ�130�е����������Ϊ0�������ִ�У���
 *      ˢ�����򴮿ڽ���ӡ����15��ʼ������-5����ֵ��
 *
 * \par Դ����
 * \snippet demo_am116_dr_fm175xx_picca_val_operate.c src_am116_dr_fm175xx_picca_val_operate
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-22  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_fm175xx_picca_val_operate
 * \copydoc demo_am116_dr_fm175xx_picca_val_operate.c
 */

/** [src_am116_dr_fm175xx_picca_val_operate] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_hwconf_fm175xx.h"
#include "demo_components_entries.h"

/**
 * \brief A�࿨ֵ��������
 */
void demo_am116_core_dr_fm175xx_picca_val_operate (void)
{
    am_fm175xx_handle_t handle = am_fm175xx_inst_init();

    demo_fm175xx_picca_val_operate(handle);
}

/** [src_am116_dr_fm175xx_picca_val_operate] */

/* end of file */
