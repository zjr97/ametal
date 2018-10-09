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
 * \brief ���Ű�ȫ����flash����
 *
 * - ʵ������
 *   1. ���ڴ�ӡ����ʾ��Ϣ Please input Verify BackdoorAccess Key!
 *   2. �� Verify BackdoorAccess Key ��ƥ��ʱ��������� Verify BackdoorAccess Key Fail!
 *   3. ��Կƥ����Զ���flash�����ݣ�SWD���Կڿ��ţ�LED��˸
 *
 * - ��������
 *   1. �������eclipse�±�����am_kl26_gcc_vector�еĺ�AM_KL26_FLASH_SEC_BACKDOOR�򿪣�
 *      �������keil�±�����am_kl26_armcc_startup.s��FSEC��ֵ��Ϊ0x82����Լ�ڵ�225�У���
 *   2. �����������ʾ��Ϣʱ�����ַ���ģʽ�·���43218765��
 *
 * \note: ���Ű�ȫ��Կ��ͨ��flash config���öε� gFlashConfig ��һ������ǰ8���ֽڵ����ݾ�������
 *        �û������������demo����������оƬ
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_backdoor_sec.c src_amks16z_core_hw_backdoor_sec
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_backdoor_sec
 * \copydoc demo_amks16z_core_hw_backdoor_sec.c
 */

/** [src_amks16z_core_hw_backdoor_sec] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "demo_fsl_entrys.h"
#include "am_kl26_inst_init.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief �������
 */
void demo_amks16z_core_hw_backdoor_sec_entry (void)
{

    am_uart_handle_t uart_handle;

    AM_DBG_INFO("demo amks16z_core hw backdoor sec!\r\n");

    uart_handle = am_kl26_uart0_inst_init();

    demo_fsl_hw_backdoor_sec_entry(KL26_FTFA, uart_handle);
}


/** [src_amks16z_core_hw_backdoor_sec] */

/* end of file */
