/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ZM516X ģ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ��ȡ���ı���ģ���������Ϣ��
 *   2. ZM516X ģ��� 11 ͨ���� 26 ͨ����������ģ�顣�������������ģ�飬��ȡ��ģ��
 *      ���ź�ǿ�Ⱥ�������Ϣ����ͨ�����ڴ�ӡ��
 *   3. ZM516X ģ���ʼ����������ɺ� LED0 ���������ʧ�ܣ�LED0 ��˸��
 *   4. ������ģ���ͨ���ָ�Ϊ����ǰ��ͨ���š�
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_8 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. ZigBee ģ�������ӹ�ϵ���£�
 * <pre>
 *           PIO0_26  <-->  ZigBee_TX
 *           PIO0_27  <-->  ZigBee_RX
 *           PIO0_28  <-->  ZigBee_RST
 * </pre>
 *        �����Ҫʹ�� ZigBee����Щ IO �ڲ�������������;��
 *
 * \par Դ����
 * \snippet demo_am824zb_std_zm516x_search.c src_am824zb_std_zm516x_search
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-15  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_am824zb_std_zm516x_search
 * \copydoc demo_am824zb_std_zm516x_search.c
 */

/** [src_am824zb_std_zm516x_search] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_vdebug.h"
#include "demo_components_entries.h"
#include "am_lpc82x_inst_init.h"

/**
 * \brief �������
 */
void demo_am824zb_std_zm516x_search_entry (void)
{
    am_zm516x_handle_t zm516x_handle  = am_zm516x_inst_init();

    demo_zm516x_search_entry(zm516x_handle);
}
/** [src_am824zb_std_zm516x_search] */

/* end of file */
