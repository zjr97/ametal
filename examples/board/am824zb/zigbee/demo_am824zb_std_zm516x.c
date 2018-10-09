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
 * \brief ZM516X ģ����ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ���Ա� Demo ��Ҫʹ������ AM824ZB �壬�������Ҫ���ز�ͬ�ĳ���
 *      ����һ�� AM824ZB ��򿪺� USE_BORD0���رպ� USE_BORD1�����벢���س���
 *      ����һ�� AM824ZB ��򿪺� USE_BORD1���رպ� USE_BORD0�����벢���س���
 *
 * - ʵ������
 *   1. ������ʼ�������óɹ��� LED0 �����������ʼ��ʧ�ܣ�LED0 ��˸��
 *   2. ������� 1S ��Է�����һ�����ݣ����պ����յ��Է����͹��������ݺ󣬵��Դ���
 *      �����յ��������������������Ϊ "received data from 0x****: I'm 0x**"��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_8 ���ƣ�
 *    2. ʹ�ð���������Ҫ�� J14 �� KEY �� PIO0_1 �̽���һ��
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    4. ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE ����Ϊ 1
 *       ���ú��Ѿ�Ĭ������Ϊ 1�� �û������ٴ����ã�
 *    5. ZigBee ģ�������ӹ�ϵ���£�
 * <pre>
 *           PIO0_26  <-->  ZigBee_TX
 *           PIO0_27  <-->  ZigBee_RX
 *           PIO0_28  <-->  ZigBee_RST
 * </pre>
 *        �����Ҫʹ�� ZigBee����Щ IO �ڲ�������������;��
 *
 * \par Դ����
 * \snippet demo_am824zb_std_zm516x.c src_am824zb_std_zm516x
 *
 * \internal
 * \par Modification History
 * - 1.01 18-01-16  pea, simplify demo, enable display head
 * - 1.00 17-05-26  mex, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824zb_std_zm516x
 * \copydoc demo_am824zb_std_zm516x.c
 */

/** [src_am824zb_std_zm516x] */
#include "ametal.h"
#include "am_zm516x.h"
#include "am_vdebug.h"
#include "demo_components_entries.h"
#include "am_lpc82x_inst_init.h"

/**
 * \brief �������
 */
void demo_am824zb_std_zm516x_entry (void)
{
    am_zm516x_handle_t zm516x_handle  = am_zm516x_inst_init();

    demo_zm516x_entry(zm516x_handle);
}
/** [src_am824zb_std_zm516x] */

/* end of file */
