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
 * \brief USART ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ������λ�����ڲ�����Ϊ 115200��8 λ���ݳ��� 1 λֹͣλ ����żУ�飻
 *   2. �� PC ����λ����������أ����� XON = 0x11�� XOFF = 0x13��
 *
 * - ʵ������
 *   1. ������� "USART flowctrl test:\r\n"��
 *   2. ����������յ����ַ�����
 *   3. ��������λ��ÿ 100 ����ֻ�ܴ��� 5 ���ַ������ͣ�����Ϊ������������أ�����
 *      PC �˴��ģ(ʹ�ô�������ص���λ��)��������Ҳ���ᶪʧ���ݣ�
 *      PC ���͵����������ڽ��յ���������
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_std_usart_flowctrl.c src_am824_std_usart_flowctrl
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_usart_flowctrl
 * \copydoc demo_am824_std_usart_flowctrl.c
 */

/** [src_am824_std_usart_flowctrl] */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "am_vdebug.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_std_usart_flowctrl_entry (void)
{
   am_kprintf("demo am824 std usart flowctrl!\r\n");
  
   demo_lpc_std_usart_flowctrl_entry(am_lpc82x_usart0_inst_init());

}
/** [src_am824_std_usart_flowctrl] */

/* end of file */
