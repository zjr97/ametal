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
 * \brief MiniPort-LED ʾ�����򣬽����ο�
 *
 * - ��������
 *   1. �� MiniPort-LED ����ֱ���� �װ�(AMKS16Z-Core)���ΪJ4�� MiniPort�ӿ������ӡ�
 *
 * - ʵ������
 *   1. ��ˮ������
 *
 * - ע�⣺
 *   1. Ҫʹ�ø����̣���Ҫ��am_prj_config.h���潫AM_CFG_LED_ENABLE����Ϊ0��
 *
 * \par Դ����
 * \snippet demo_miniport_led.c src_miniport_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_led
 * \copydoc demo_miniport_led.c
 */

/** [src_miniport_led] */
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "demo_std_entries.h"
#include "am_hwconf_miniport_view.h"
#include "am_kl26_inst_init.h"

/*
 * �������
 */
void demo_amks16z_core_miniport_led_entry (void)
{
    AM_DBG_INFO("demo amks16z_core miniport led!\r\n");

    am_miniport_led_inst_init();

    demo_std_led_water_light_entry(2, 9);
}

/** [src_miniport_led] */

/* end of file */
