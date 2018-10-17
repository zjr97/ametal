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
 * \brief fm175xx�������ݣ�ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ������ԿA�Կ�Ƭ�Ŀ�2������֤�������֤��ͨ�����ӡkey A authent failed��
 *   2. �����֤�ɹ������ȡ��0��������Ƭ���кţ�����3��������ԿA����ȡ���Ʋ��ֺ���ԿB������4���Ϳ�2
 *      ����ͬһ��������������ӡ������
 *
 * - ע�⣺
 *   1. ÿ����������4���飬���е�0����2����Ϊ���ݿ飬��3����Ϊ���ƿ顣��֤��ʵ�Ƕ��������Եģ����Ǹ�
 *      am_fm175xx_picca_m1_authent()������������һ������Ϊ���ַ����˸ú���������
 *      ��ʵ����֤����Ŀ����ڵ���������֤�ɹ������Ը��ݿ��ƿ��еĿ���Ȩ�޶Ա��������еĿ���ж�д��
 *   2. ��0�е������ǿ�Ƭ���кţ��ÿ�ֻ����
 *   3. ��3λ���ƿ飬��Ȼ���������A��ԿΪȫF�����Ƕ�ȡ������A��ԿȴΪȫ0����ΪA��Կ���κ�����¶�û��
 *      ����Ȩ�ޡ�
 *   4. ��4����֤�Ŀ�2����ͬһ����������˶������������ǲ���ȷ�ģ����ǶԿ�4���ڵ�����������֤��
 *
 * \par Դ����
 * \snippet demo_am116_dr_fm175xx_picca_read_block.c src_am116_dr_fm175xx_picca_read_block
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-21  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_fm175xx_picca_read_block
 * \copydoc demo_am116_dr_fm175xx_picca_read_block.c
 */

/** [src_am116_dr_fm175xx_picca_read_block] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_hwconf_fm175xx.h"
#include "demo_components_entries.h"

/**
 * \brief A�࿨��������
 */
void demo_am116_core_dr_fm175xx_picca_read_block (void)
{
    am_fm175xx_handle_t handle = am_fm175xx_inst_init();

    demo_fm175xx_picca_read_block(handle);
}


/** [src_am116_dr_fm175xx_picca_read_block] */

/* end of file */
