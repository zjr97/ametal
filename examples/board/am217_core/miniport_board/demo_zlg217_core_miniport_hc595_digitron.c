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
 * \brief MiniPort-View + MiniPort-595 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �Ƚ� MiniPort-595 ����ֱ���� AM217BLE �� MiniPort �����ӣ�
 *   2. �� MiniPort-View ������ MiniPort-595 �ӿ������ӡ�
 *
 * - ʵ������
 *   1. ���Կ�����ֵ 0 ~ 59 �����������
 *   2. ����С�� 30 ʱ����λ��˸������ 30 ʱʮλ��˸��
 *
 * \par Դ����
 * \snippet demo_miniport_hc595_digitron.c src_miniport_hc595_digitron
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_hc595_digitron
 * \copydoc demo_miniport_hc595_digitron.c
 */

/** [src_miniport_hc595_digitron] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_arm_nvic.h"
#include "am_zlg217_inst_init.h"
#include "am_digitron_disp.h"

/**
 * \brief �������
 */
void demo_zlg217_core_miniport_hc595_digitron_entry (void)
{
    AM_DBG_INFO("demo am217_core miniport hc595 digitron!\r\n");

    am_miniport_view_595_inst_init();

    demo_std_digitron_60s_counting_entry(0);
}
/** [src_miniport_hc595_digitron] */

/* end of file */
