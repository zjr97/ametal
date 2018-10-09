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
 * \brief WDT ι���͸�λ���ӣ�ͨ��Ӳ����ʵ��
 *
 * - ʵ������
 *   1. ���Ź����ó�ʱʱ��Ϊ256ms����ʱ50ms��ι������������ִ�У�
 *      ���ڴ�ӡι����Ϣ��
 *   2. ����ִ�е���ʱ1sʱ��ι����ʱ��ϵͳ��λ���������¿�ʼִ�С�
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 * \par Դ����
 * \snippet demo_kl26_hw_wdt.c src_kl26_hw_wdt
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-30  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_hw_wdt
 * \copydoc demo_kl26_hw_wdt.c
 */

/** [src_kl26_hw_wdt] */
#include "ametal.h"
#include "am_delay.h"
#include "am_uart.h"
#include "am_kl26_inst_init.h"
#include "hw/amhw_kl26_sim.h"
#include "demo_fsl_entrys.h"

/**
 * \brief WDT��ں�����HW��ʵ��
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 * \return ��
 */
void demo_kl26_hw_wdt_entry (void)
{
    am_uart_handle_t uhandle;          /**< \brief ���ڱ�׼������     */

    /* UART�豸��ʼ������ȡUART���ֵ  */
    uhandle = am_kl26_uart0_inst_init();

    /* ���ÿ��Ź� */
    amhw_kl26_sim_cop_cfg(KL26_SIM_COP_MODE_NORMAL,    /* ��ͨģʽ */
                          KL26_SIM_COP_CLK_INTERNAL,   /* �ڲ�1KHZ��LPOʱ�� */
                          KL26_SIM_COP_TIMOUT_VALUE2); /* ��ʱʱ����Ϊ256ms */

    am_uart_poll_send(uhandle,
                     (uint8_t *)("�ȴ�ι��...\r\n"),
                      sizeof("�ȴ�ι��...\r\n"));

    am_mdelay(50);

    amhw_kl26_sim_srvcop_set(0x55);     /* ι������д0x55 */
    amhw_kl26_sim_srvcop_set(0XAA);     /* ι������д0xAA */

    am_uart_poll_send(uhandle,
                     (uint8_t *)("50ms��ι���ɹ���\r\n"),
                      sizeof("50ms��ι���ɹ���\r\n"));

    am_uart_poll_send(uhandle,
                     (uint8_t *)("�ȴ�ι��...\r\n"),
                      sizeof("�ȴ�ι��...\r\n"));

    am_mdelay(1000);

    /* ���ι����ʱ��������佫����ִ�� */
    amhw_kl26_sim_srvcop_set(0x55);     /* ι������д0x55 */
    amhw_kl26_sim_srvcop_set(0XAA);     /* ι������д0xAA */

    am_uart_poll_send(uhandle,
                     (uint8_t *)("1s��ι���ɹ���\r\n"),
                      sizeof("1s��ι���ɹ���\r\n"));

    while(1) {
        am_uart_poll_send(uhandle,
                         (uint8_t *)("�ȴ�ι��...\r\n"),
                          sizeof("�ȴ�ι��...\r\n"));

        am_mdelay(1000);
    }
}

/** [src_kl26_hw_wdt] */

/* end of file */
