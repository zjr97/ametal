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
 * \brief PLL ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��ӡ PLL ����Ƶ�ʡ�ʵ�����Ƶ�ʺ� CLKOUT �������Ƶ�ʣ�
 *   2. CLKOUT ����(PIO0_27 ����)��� __CLKOUT_DIV ��Ƶ�����ʱ��Ƶ�ʣ�
 *   3. LED0 �� 0.5s ��ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_hw_pll.c src_am824_hw_pll
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-20  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_pll
 * \copydoc demo_am824_hw_pll.c
 */

/** [src_am824_hw_pll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_nxp_entries.h"


/**
 * \brief �������
 */
void demo_am824_core_hw_pll_entry (void)
{
    am_kprintf("demo am824 hw pll! \r\n");
  
    demo_lpc824_hw_pll_entry();
}
/** [src_am824_hw_pll] */

/* end of file */
