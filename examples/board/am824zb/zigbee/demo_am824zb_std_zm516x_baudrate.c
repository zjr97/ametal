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
 * \brief ZM516X ģ���Զ����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��Ƭ���ֱ���ͨ�� 2400��4800��9600��19200��38400��57600 �� 115200 �Ĳ���
 *      ������ ZM516X ģ�飻
 *   2. ������ӳɹ���ͨ�����ڴ�ӡ��ǰ�Ĳ����ʲ��� LED0 ���������� LED0 ��˸��
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
 * \snippet demo_am824zb_std_zm516x_baudrate.c src_am824zb_std_zm516x_baudrate
 *
 * \internal
 * \par Modification history
 * - 1.00 18-04-12  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824zb_std_zm516x_baudrate
 * \copydoc demo_am824zb_std_zm516x_baudrate.c
 */

/** [src_am824zb_std_zm516x_baudrate] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_vdebug.h"
#include "demo_components_entries.h"
#include "am_lpc82x_inst_init.h"

/**
 * \brief �������
 */
void demo_am824zb_std_zm516x_baudrate_entry (void)
{
    am_zm516x_handle_t   zm516x_handle = am_zm516x_inst_init();

    demo_zm516x_baudrate_entry(zm516x_handle);
}

/** [src_am824zb_std_zm516x_baudrate] */

/* end of file */
