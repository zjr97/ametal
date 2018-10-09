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
 * \brief MiniPort-595 + MiniPort-View + MiniPort-KEY ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �Ƚ� MiniPort-595 ��չ��ֱ���� AM824-Core �� MiniPort �����ӣ�
 *   2. �� MiniPort-View ��չ���� MiniPort-595 �ӿ������ӣ�
 *   3. �� MiniPort-KEY �� MiniPort-View ���ӡ�
 *
 * - ʵ������
 *   1. ����һ����������λ�������ʾ������ŵĶ����ƣ�
 *   2. ż�����ʱ���������˸���������ʱ������ܲ���˸��
 *
 * \note
 *    ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE ����Ϊ 1��
 *    ���ú��Ѿ�Ĭ������Ϊ 1�� �û������ٴ����á�
 *
 * \par Դ����
 * \snippet demo_am824_core_miniport_hc595_digitron_key.c src_am824_core_miniport_hc595_digitron_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_core_miniport_hc595_digitron_key
 * \copydoc demo_am824_core_miniport_hc595_digitron_key.c
 */

/** [src_am824_core_miniport_hc595_digitron_key] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_miniport_hc595_digitron_key_entry (void)
{
    AM_DBG_INFO("demo am824_core miniport hc595 digitron key!\r\n");

    am_miniport_view_key_595_inst_init();

    demo_std_key_digitron_entry(0);
}
/** [src_am824_core_miniport_hc595_digitron_key] */

/* end of file */
