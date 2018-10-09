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
 * \brief �����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Դ��ڴ�ӡ�����¼���
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ʹ�ð�����Ҫ�� J14 ����ñ�� KEY �� PIO0_1 �̽ӣ��ұ����� am_prj_config.h
 *       �ڽ� AM_CFG_KEY_GPIO_ENABLE ����Ϊ 1�����ú��Ѿ�Ĭ������Ϊ 1�� �û�������
 *       �����ã�
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_std_key_input_event.c src_am824_std_key_input_event
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-8  hbt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_key_input_event
 * \copydoc demo_am824_std_key_input_event.c
 */

/** [src_am824_std_key_input_event] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_std_key_input_event_entry (void)
{
    AM_DBG_INFO("demo am824 std input event!\r\n");

    demo_std_key_entry();
}
/** [src_am824_std_key_input_event] */

/* end of file */
