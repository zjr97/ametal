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
 * \brief UART��ѯ��ʽ�½��շ����������̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. PIOC_3 ��������PC���ڵ�TXD;
 *   2. PIOC_4 ��������PC���ڵ�RXD��
 *   3. ������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *
 * - ʵ������
 *   1. �������"HW example---UART test in polling mode:"��
 *   2. ����������յ����ַ�����
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_uart_polling.c src_amks16z_core_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-19  nwt, make some changes.
 * - 1.00 15-07-07  xym, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_amks16z_core_if_hw_uart_polling
 * \copydoc demo_amks16z_core_hw_uart_polling.c
 */

/** [src_amks16z_core_hw_uart_polling] */
#include "ametal.h"
#include "hw/amhw_fsl_uart.h"
#include "hw/amhw_kl26_sim.h"
#include "am_gpio.h"
#include "am_kl26_clk.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

#include "../../../../soc/freescale/kl26/am_kl26.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"
/**
 * \brief UARTʱ��ʹ�ܳ�ʼ��
 * \param[in] p_hw_uart : ָ�򴮿��豸�Ĵ����ṹ��, ��KL26_UART0.
 */
static void uart_polling_clock_init (void *p_hw_uart)
{
    uint32_t base_addr = (uint32_t)(p_hw_uart);

    switch (base_addr) {
    /* ����0ʱ�ӳ�ʼ�� */
    case KL26_UART0_BASE:
        amhw_kl26_sim_uart0_src_set(KL26_SIM_UART0SRC_PLLFLLCLK);
        /* ����UART0ʱ��                  */
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART0);
        break;

    /* ����1ʱ�ӳ�ʼ�� */
    case KL26_UART1_BASE:
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART1);
        break;

    /* ����2ʱ�ӳ�ʼ�� */
    case KL26_UART2_BASE:
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART2);
        break;
    }
}

/**
 * \brief �������
 */
void demo_amks16z_core_hw_uart_polling_entry (void)
{
    uint32_t uart_clk;

    uart_polling_clock_init(KL26_UART1);

    /* ���ų�ʼ��      PIOC_3_UART1_RX  PIOC_4_UART1_TX     */
    am_gpio_pin_cfg (PIOC_3,PIOC_3_UART1_RX);
    am_gpio_pin_cfg (PIOC_4,PIOC_4_UART1_TX);

    uart_clk = am_kl26_clk_periph_rate_get((void *)(KL26_UART1));

    demo_fsl_hw_uart_polling_entry(KL26_UART1, uart_clk, 0);
}
/** [src_amks16z_core_hw_uart_polling] */

/* end of file */
