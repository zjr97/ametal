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
 * \brief FGPIO Ӳ�������������������
 *
 * - ������
 *   1.��J14��key��PIOC_0�̽���һ��;
 *   2.��J9��LED0��PIOC_4�̽���һ��;
 *   3.��J10��LED1��PIOC_8�̽���һ��;
 *
 * -ʵ�����󣺳������ص�demo��󣬰���һ�ΰ���LED0�����һ�η�ת����������demo���ϵ�LED0������
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_fgpio.c src_amks16z_core_hw_fgpio
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-18  nwt, make some changes.
 * - 1.00 15-10-16  wxj, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_fgpio
 * \copydoc demo_amks16z_core_hw_fgpio.c
 */
 
/** [src_amks16z_core_hw_fgpio] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_fgpio_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw fgpio!\r\n");

    demo_kl26_hw_fgpio_entry();
}

/** [src_amks16z_core_hw_fgpio] */
 
/* end of file */
