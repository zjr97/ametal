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
 * \snippet demo_fsl_hw_backdoor_sec.c src_fsl_hw_backdoor_sec
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_hw_backdoor_sec
 * \copydoc demo_fsl_hw_backdoor_sec.c
 */

/** [src_fsl_hw_backdoor_sec] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "hw/amhw_fsl_ftfa.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/** \brief ���Ű�ȫ��Կ */
uint8_t backdoor_accesskey[8];

/**
 * \brief �������
 */
void demo_fsl_hw_backdoor_sec_entry (amhw_fsl_ftfa_t *p_hw_ftfa,
                                     am_uart_handle_t uart_handle)
{
    uint8_t key = 0;
    int32_t ret = 0;
    int i = 0;

    AM_DBG_INFO("Please input BackdoorAccess Key!\r\n");
    
    /* �����ַ� */
    am_uart_poll_receive(uart_handle, backdoor_accesskey, sizeof(backdoor_accesskey));

    AM_DBG_INFO("BackdoorAccess Key is:\r\n ");

    for (i = 0; i < 8; i++) {
        AM_DBG_INFO("0x%x  ", backdoor_accesskey[i]);
    }

    AM_DBG_INFO("\r\n");

    /* ʹ��FLASHæ��ʱ�ȴ� */
   // amhw_kl26_mcm_flash_stalling_enable(KL26_MCM);

    key = am_int_cpu_lock();
    /** ��flash����ִ�к���������RAM */
    amhw_fsl_ftfa_func_copy();
    am_int_cpu_unlock (key);


    key = am_int_cpu_lock();
    /* ��flash����ִ�к���������RAM */
    ret = amhw_fsl_ftfa_backdoor_access_key_verify(p_hw_ftfa, backdoor_accesskey);
    am_int_cpu_unlock (key);

    if (ret != 0) {
        AM_DBG_INFO(" Verify BackdoorAccess Key Fail!\r\n");
        while(1);
    }


    while (1) {

        am_led_toggle(LED0);
        am_mdelay(200);
    }
}


/** [src_fsl_hw_backdoor_sec] */

/* end of file */
