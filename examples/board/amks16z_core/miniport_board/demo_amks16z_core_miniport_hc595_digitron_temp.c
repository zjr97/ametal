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
 * \brief MiniPort-View + MiniPort-595 �¶���ʾ��ʹ�õװ�LM75BD��ȡ�¶ȣ�����
 *
 * - ��������
 *   1. Ҫʹ�õװ�(AMKS16Z-Core)�ϵ� LM75 �¶ȴ���������Ҫ�̽� J11��J13��
 *   2. �Ƚ� MiniPort-595 ����ֱ���� AMKS16Z-Core ���ΪJ4�� MiniPort �����ӣ�
 *   3. �� MiniPort-View ������ MiniPort-595 �ӿ������ӡ�
 *
 * - ʵ������
 *   1. ���Կ����������ʾ��ǰ�¶ȣ���J14��ðѡ��̽� KEY �� RES�����µװ��ϵ�
 *      KEY/RES�������ʵ���ᷢ�ȣ������¶ȴ������ɼ������¶����ߡ�
 *
 * - ����˵��
 *   1. �������ʹ��I2C��ȡLM75���¶ȣ�����ʹ�ò鿴I2C�µ��������
 *
 * \par Դ����
 * \snippet demo_miniport_hc595_digitron_temp.c src_miniport_hc595_digitron_temp
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_hc595_digitron_temp
 * \copydoc demo_miniport_hc595_digitron_temp.c
 */

/** [src_miniport_hc595_digitron_temp] */
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "demo_std_entries.h"
#include "am_hwconf_miniport_view.h"
#include "am_kl26_inst_init.h"

/* ������� */
void demo_amks16z_core_miniport_hc595_digitron_temp_entry (void)
{
    AM_DBG_INFO("demo amks16z_core miniport hc595 digitron temp!\r\n");

    am_miniport_view_595_inst_init();

    demo_std_digitron_temp_entry(0, am_temp_lm75_inst_init());
}

/** [src_miniport_hc595_digitron_temp] */

/* end of file */
