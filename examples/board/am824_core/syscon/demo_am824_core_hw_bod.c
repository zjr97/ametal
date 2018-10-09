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
 * \brief ���������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ�鲽�裺
 *   1. �ı乩���ѹ��ʹ֮���� 2.85V��
 *
 * - ʵ������
 *   1. ���ⲿ��������ĸ�λ��������� "Reset by External Reset Pin"��
 *   2. ������������ĸ�λ��������� "Reset by BOD"��
 *   3. ���������£�LED0 �������������ѹ���Ͻ��ͣ����� 2.85V ʱ��LED0 ����
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ơ�
 *
 * \par Դ����
 * \snippet demo_am824_hw_bod.c src_am824_hw_bod
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-17  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_bod
 * \copydoc demo_am824_hw_bod.c
 */

/** [src_am824_hw_bod] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_bod_entry (void)
{
    am_kprintf("demo am824_core hw bod!\r\n");
    demo_lpc824_hw_bod_entry();
}
/** [src_am824_hw_bod] */

/* end of file */
