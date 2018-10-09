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
 * \brief UART�жϷ�ʽ�½��շ����������̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. PIOC_3 ��������PC���ڵ�TXD;
 *   2. PIOC_4 ��������PC���ڵ�RXD��
 *   3. ������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *    
 * - ʵ������
 *   1. �������"HW example---UART test in interrupt mode:"��
 *   2. ����������յ����ַ���
 *
 * \note ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()��
 *
 * \par Դ����
 * \snippet demo_fsl_hw_uart_int.c src_fsl_hw_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-19  nwt, make some changes.
 * - 1.00 15-10-20  xym, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_fsl_if_hw_uart_int
 * \copydoc demo_fsl_hw_uart_int.c
 */ 

/** [src_fsl_hw_uart_int] */
#include "ametal.h"
#include "hw/amhw_fsl_uart.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE     (115200)              /** <\brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static const uint8_t __g_hw_polling_str[]={"HW example---UART test in interrupt mode:\r\n"};

static const uint8_t   *__gp_tx_buf   = NULL; /**< \brief ���ͻ�����.        */
static volatile uint8_t __g_tx_index  = 0;    /**< \brief ��ǰ������������.   */
static volatile uint8_t __g_tx_nbytes = 0;    /**< \brief ��Ҫ���͵����ֽ���. */
static am_bool_t       __g_uart0_flog = 0;    /**< \brief ����0��־.       */
/** 
 * \brief ���ڷ������ݣ��ж�ģʽ�£��ú�������������
 *
 * \param[in] p_hw_uart : ָ������ƵĴ����豸�ṹ��
 * \param[in] p_buf     : ָ�������ݵĻ�����
 * \param[in] len       : ���͵��ֽ���
 * 
 * \retval    1         : ���;���
 * \retval    0         : ����ģ��æµ���޷�����
 * 
 * \note ���ͻ����������ȫ�ֵģ���֤���������ݷ������ǰ��������û�б��ͷŵ� 
 */
static uint8_t __uart_int_send(amhw_fsl_uart_t *p_hw_uart, const uint8_t *p_buf, uint32_t len)
{
    if (__g_tx_index >= __g_tx_nbytes)  {   /* �ϴη����Ѿ��������     */
        __gp_tx_buf   = p_buf;            /* ���¶��巢�ͻ�������     */
        __g_tx_index  = 0;                /* �ӻ�������ʼ�ֽڿ�ʼ���� */
        __g_tx_nbytes = len;              /* ����g_tx_nbytes���ֽ�    */

        amhw_fsl_uart_int_enable(p_hw_uart, AMHW_FSL_UART_INT_C2_TIE);

        return 1;
    } 

    return 0;
}

/** 
 * \brief �����жϷ�����
 * \param[in] p_arg : ָ������ƵĴ����豸�ṹ�� ����am_int_connect()ע��
 */
static void __uart_hw_irq_handler (void *p_arg)
{
    amhw_fsl_uart_t *p_hw_uart = (amhw_fsl_uart_t *)p_arg;

    uint32_t uart_int_stat;

    uint8_t data;
    
    if (__g_uart0_flog) {
        uart_int_stat = amhw_fsl_uart_ver0_intstat_get(p_hw_uart);
    } else {
        uart_int_stat = amhw_fsl_uart_ver1_intstat_get(p_hw_uart);
    }

    if (uart_int_stat & AMHW_FSL_UART_INTSTAT_S1_RDRF) {
        /* ��ȡ�½������ݣ������ͳ�ȥ */
        data = amhw_fsl_uart_rxdata_read(p_hw_uart);
        amhw_fsl_uart_txdata_write(p_hw_uart, data);

    } else if (uart_int_stat & AMHW_FSL_UART_INTSTAT_S1_TDRE) {
        /* �����ж� */
        if(__g_tx_index < __g_tx_nbytes) {
            /* ���������д��������� */
            amhw_fsl_uart_txdata_write(p_hw_uart, __gp_tx_buf[__g_tx_index++]);

        } else {
            /* ������û�з������ݣ��رշ����ж� */
            amhw_fsl_uart_int_disable(p_hw_uart, AMHW_FSL_UART_INT_C2_TIE);
        } 
    } 
}

/**
 * \brief UART hw �ж��շ���ʼ��
 */
static void __uart_int_init (amhw_fsl_uart_t *p_hw_uart,
                             uint32_t         uart_clk,
                             int              inum)
{

    amhw_fsl_uart_stop_bit_set (p_hw_uart, AMHW_FSL_UART_BDH_SBNS_STOP_1);
    amhw_fsl_uart_data_mode_set(p_hw_uart, AMHW_FSL_UART_C1_M_8BIT);
    amhw_fsl_uart_parity_set(p_hw_uart,    AMHW_FSL_UART_C1_PARITY_NO);

    /* ���ô��ڲ����� */
    if (__g_uart0_flog) {
            amhw_fsl_uart_ver0_baudrate_set(p_hw_uart,
                                            uart_clk,
                                            UART_BAUDRATE);
    } else {
        amhw_fsl_uart_ver1_baudrate_set(p_hw_uart,
                                        uart_clk,
                                        UART_BAUDRATE);
    }

    /* �ر����д����ж� */
    amhw_fsl_uart_int_disable(p_hw_uart, AMHW_FSL_UART_INT_ALL);

    /* �����ж������ţ������ж� */
    am_int_connect(inum, __uart_hw_irq_handler, (void *)p_hw_uart);
    am_int_enable(inum);

    /* ʹ�ܴ���.    */
    amhw_fsl_uart_enable(p_hw_uart);
    
    /* ʹ��RDRF����׼�ж� */
    amhw_fsl_uart_int_enable(p_hw_uart, AMHW_FSL_UART_INT_C2_IRIE);
}

/**
 * \brief �������
 */
void demo_fsl_hw_uart_int_entry (amhw_fsl_uart_t *p_hw_uart,
                                 int              inum,
                                 uint32_t         uart_clk,
                                 am_bool_t        uart0_flog)
{
    __g_uart0_flog = uart0_flog;

    /* UART�жϳ�ʼ�� */
    __uart_int_init(p_hw_uart, uart_clk, inum);
    
    __uart_int_send(p_hw_uart, __g_hw_polling_str, sizeof(__g_hw_polling_str));
    
    while (1) {

    }
}
/** [src_fsl_hw_uart_int] */

/* end of file */
