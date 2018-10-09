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
 * \brief MiniPort-KEY ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �� MiniPort-KEY ����ֱ���� AM116-Core �� MiniPort�ӿ������ӡ�
 *
 * - ʵ������
 *   1. ���°���ʱ�����Դ��ڴ�ӡ��ǰ������Ϣ��
 *
 * \note
 *    1. ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE ����Ϊ 1��
 *       ���ú��Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *    2. LED0/LED1 ��Ҫ�̽� J9/J10 ����ñ�����ֱܷ� PIO0_20/PIO0_21 ���ƣ�
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_core_miniport_key.c src_am824_core_miniport_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_key
 * \copydoc demo_miniport_key.c
 */

/** [src_am824_core_miniport_key] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_miniport_key_entry (void)
{
    AM_DBG_INFO("demo am824_core miniport key!\r\n");

    am_miniport_key_inst_init();

    demo_std_4key_entry();
}
/** [src_am824_core_miniport_key] */

/* end of file */
