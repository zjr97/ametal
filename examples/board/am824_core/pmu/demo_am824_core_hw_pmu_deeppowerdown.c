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
 * \brief PMU ��ȵ���ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���г���һ��� LED0 ��˸һ�κ������ȵ���ģʽ��
 *   2. �ȴ� 5s ��WKT ��ʱʱ�䵽��CPU �����ѣ����ͨ�üĴ�������У����ȷ��LED0
 *      ��˸һ�Σ����ͨ�üĴ�������У�����LED0 ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ������ȵ���ģʽ��ֻ�� WAKEUP ���ź� WKT ��ʱ���ܻ���оƬ������Ĭ��״̬��
 *       WAKEUP ���Ż���ʹ�ܣ�����һ��ȷ�� WAKEUP �ⲿ��������Դ����֤��Ч�ĸߵ�ƽ
 *       ״̬��������������Ѳ��������۲첻�� WKT ���� CPU���������̽� WAKEUP ����
 *       (PIO0_4)���ѹ��ܽ�ֹ�ˣ����Բ���Ҫ�� PIO0_4 ������
 *    3. ʹ�øó���󣬻ᵼ���´γ�����д��ʱ���ⲻ��оƬ������оƬ������ȵ���
 *       ģʽ�� SWD ����ģʽ�رգ����´�����ʱ�� P0_12 ���ͻ򰴶���λ��֮��һ����
 *       �����������ص��ԡ�
 *
 * \par Դ����
 * \snippet demo_am824_hw_pmu_deeppowerdown.c src_am824_hw_pmu_deeppowerdown
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-14  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_pmu_deeppowerdown
 * \copydoc demo_am824_hw_pmu_deeppowerdown.c
 */

/** [src_am824_hw_pmu_deeppowerdown] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_nxp_entries.h"

/*******************************************************************************
  �ⲿ��������
*******************************************************************************/

/**
 * \brief �������
 */
void demo_am824_core_hw_pmu_deeppowerdown_entry (void)
{
    am_kprintf("demo am824_core hw pmu deeppowerdown!\r\n");
  
    /* ���� DeepPowerDown ģʽ */
    demo_lpc824_hw_pmu_deeppowerdown_entry(LPC82X_PMU);


}
/** [src_am824_hw_pmu_deeppowerdown] */

/* end of file */
