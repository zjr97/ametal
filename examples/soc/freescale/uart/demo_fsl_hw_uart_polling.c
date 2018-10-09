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
 * \snippet demo_fsl_hw_uart_polling.c src_fsl_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-19  nwt, make some changes.
 * - 1.00 15-07-07  xym, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_fsl_if_hw_uart_polling
 * \copydoc demo_fsl_hw_uart_polling.c
 */

/** [src_fsl_hw_uart_polling] */
#include "ametal.h"
#include "hw/amhw_fsl_uart.h"
#include "am_gpio.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE     (115200)              /** <\brief ������.  */

/**
 * \brief UART hw ��ѯ�շ���ʼ��
 */
static void uart_polling_init (amhw_fsl_uart_t *p_hw_uart,
                               uint32_t         uart_clk,
                               am_bool_t        uart0_flog)
{
    /* ���ô��ڲ����� */
    if(uart0_flog){
        amhw_fsl_uart_ver0_baudrate_set(p_hw_uart,
                                        uart_clk,
                                        UART_BAUDRATE);
    } else {
        amhw_fsl_uart_ver1_baudrate_set(p_hw_uart,
                                        uart_clk,
                                        UART_BAUDRATE);
    }
    amhw_fsl_uart_stop_bit_set (p_hw_uart, AMHW_FSL_UART_BDH_SBNS_STOP_1);
    amhw_fsl_uart_data_mode_set(p_hw_uart, AMHW_FSL_UART_C1_M_8BIT);
    amhw_fsl_uart_parity_set(p_hw_uart,  AMHW_FSL_UART_C1_PARITY_NO);

    /* ʹ�ܴ��� */
    amhw_fsl_uart_enable(p_hw_uart);
}

/**
 * \brief �������
 */
void demo_fsl_hw_uart_polling_entry (amhw_fsl_uart_t *p_hw_uart,
                                     uint32_t         uart_clk,
                                     am_bool_t        uart0_flog)
{
    const uint8_t uart_hw_str[]={"HW example---UART test in polling mode:\r\n"};
    
    /* ���ݻ�����       */
    uint8_t buf_src[256];

    /* UART��ѯ��ʼ�� */
    uart_polling_init(p_hw_uart, uart_clk, uart0_flog);

    amhw_fsl_uart_poll_send(p_hw_uart, uart_hw_str, sizeof(uart_hw_str));

    while (1) {
        /* �����ַ� */
        amhw_fsl_uart_poll_receive(p_hw_uart, buf_src, 1);
        /* ���͸ոս��յ��ַ� */
        amhw_fsl_uart_poll_send(p_hw_uart, buf_src, 1);
    }
}
/** [src_fsl_hw_uart_polling] */

/* end of file */
