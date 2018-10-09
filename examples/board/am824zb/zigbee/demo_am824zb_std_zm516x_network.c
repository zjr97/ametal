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
 * - �������裺
 *   1. ���Ա� Demo ������Ҫʹ������ AM824ZB �壬����ֻ���� 1 �����ӻ������ж����
 *      �����ʹӻ���Ҫ���ز�ͬ�ĳ���
 *      ��Ϊ�����Ŀ�����򿪺� MASTER_BORD_USE���رպ� SLAVE_BORD_USE�����벢���أ�
 *      ��Ϊ�ӻ��Ŀ�����򿪺� SLAVE_BORD_USE���رպ� MASTER_BORD_USE�����벢���أ�
 *   2. ���ӻ��� JOIN ����ñ�̽� 3 �����£�ʹ�ӻ�������������׶Σ�
 *   3. ���������� KEY/RES ������ʹ�������� __JOIN_TIME �������ģʽ��
 *   4. �ȴ������˳�����ģʽ�󣬰��´ӻ��� KEY/RES ������
 *
 * - ʵ������
 *   1. ��� ZM516X ģ���ʼ��������ʧ�ܣ�LED0 ��˸��
 *   2. ���ڴ�ӡ��ȡ���ı���ģ��������Ϣ��
 *   3. ���ڴ�ӡ��ʾ��Ϣ��
 *   4. ������ӡ�ӻ��б���ӻ���Ϣ��
 *   5. ������ӻ����� "I'am Master\r\n";
 *   5. �ӻ����������� "I'am Slave x\r\n"������ x Ϊ�ӻ������ַ;
 *   3. �����ʹӻ��ֱ�ͨ�����Դ��ڴ�ӡ���յ������ݡ�
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
 * \snippet demo_am824zb_std_zm516x_network.c src_am824zb_std_zm516x_network
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-15  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824zb_std_zm516x_network
 * \copydoc demo_am824zb_std_zm516x_network.c
 */

/** [src_am824zb_std_zm516x_network] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_vdebug.h"
#include "demo_components_entries.h"
#include "am_lpc82x_inst_init.h"

/**
 * \brief �������
 */
void demo_am824zb_std_zm516x_network_entry (void)
{

    am_zm516x_handle_t zm516x_handle  = am_zm516x_inst_init();

    demo_zm516x_network_entry(zm516x_handle);
}
/** [src_am824zb_std_zm516x_network] */

/* end of file */
