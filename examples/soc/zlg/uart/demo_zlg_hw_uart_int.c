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
 * \brief UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� "HW example---UART test in interrupt mode:"��
 *   2. ָ������������յ����ַ���
 *
 * \par Դ����
 * \snippet demo_zlg_hw_uart_int.c src_zlg_hw_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-01-20  ari, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zlg_hw_uart_int
 * \copydoc demo_zlg_hw_uart_int.c
 */

/** [src_zlg_hw_uart_int] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_zlg_uart.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE      (115200)           /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static const uint8_t hw_polling_str[] =
                              {"HW example---UART test in interrupt mode:\r\n"};

static const uint8_t   *gp_tx_buf   = NULL; /**< \brief ���ͻ����� */
static volatile uint8_t g_tx_index  = 0;    /**< \brief ��ǰ������������ */
static volatile uint8_t g_tx_nbytes = 0;    /**< \brief ��Ҫ���͵����ֽ��� */

/**
 * \brief ���ڷ������ݣ��ж�ģʽ�£��ú�������������
 *
 * \param[in] p_hw_uartָ������ƵĴ����豸�ṹ��
 * \param[in] p_buf    ָ�������ݵĻ�����
 * \param[in] len      ���͵��ֽ���
 *
 * \retval 1 ���;���
 * \retval 0 ����ģ��æµ���޷�����
 *
 * \note ���ͻ����������ȫ�ֵģ���֤���������ݷ������ǰ��������û�б��ͷŵ�
 */
static uint8_t uart_int_send (amhw_zlg_uart_t *p_hw_uart,
                              const uint8_t   *p_buf,
                              uint32_t         len)
{
    if (g_tx_index >= g_tx_nbytes)  {   /* �ϴη����Ѿ�������� */
        gp_tx_buf   = p_buf;            /* ���¶��巢�ͻ������� */
        g_tx_index  = 0;                /* �ӻ�������ʼ�ֽڿ�ʼ���� */
        g_tx_nbytes = len;              /* ����g_tx_nbytes���ֽ� */

        /* ������дһ��һ���ֽڵ����ݲ��Բ��������ж� */
        while(amhw_zlg_uart_status_flag_check(p_hw_uart,
                                AMHW_ZLG_UART_TX_COMPLETE_FALG) == AM_FALSE);

        amhw_zlg_uart_data_write(p_hw_uart, p_buf[g_tx_index++]);

        amhw_zlg_uart_int_enable(p_hw_uart,
                                    AMHW_ZLG_UART_INT_TX_EMPTY_ENABLE);

        return 1;
    }

    return 0;
}

/**
 * \brief �����жϷ�����
 *
 * \param[in] p_arg ָ������ƵĴ����豸�ṹ�� ���� am_int_connect() ע��
 */
static void uart_hw_irq_handler (void *p_arg)
{
    amhw_zlg_uart_t *p_hw_uart = (amhw_zlg_uart_t *)p_arg;
    uint8_t          data;

    if (amhw_zlg_uart_int_flag_check(p_hw_uart,
                                     AMHW_ZLG_UART_INT_RX_VAL_FLAG) == AM_TRUE) {
        amhw_zlg_uart_int_flag_clr(p_hw_uart, AMHW_ZLG_UART_INT_RX_VAL_FLAG);

        /* ��ȡ�½������ݣ������ͳ�ȥ */
        data = amhw_zlg_uart_data_read(p_hw_uart);
        amhw_zlg_uart_data_write(p_hw_uart, data);

    } else if (amhw_zlg_uart_int_flag_check(p_hw_uart,
                               AMHW_ZLG_UART_INT_TX_EMPTY_FLAG) == AM_TRUE) {
        amhw_zlg_uart_int_flag_clr(p_hw_uart,
                                   AMHW_ZLG_UART_INT_TX_EMPTY_FLAG);

        /* �����ж� */
        if(g_tx_index < g_tx_nbytes) {

            /* ���������д��������� */
            amhw_zlg_uart_data_write(p_hw_uart, gp_tx_buf[g_tx_index++]);

        } else {

            /* ������û�з������ݣ��رշ����ж� */
            amhw_zlg_uart_int_disable(p_hw_uart,
                                      AMHW_ZLG_UART_INT_TX_EMPTY_ENABLE);
        }
    }
}

/**
 * \brief UART hw �ж��շ���ʼ��
 */
void uart_int_init (amhw_zlg_uart_t *p_hw_uart, 
                           uint32_t         clk_rate,
                           unsigned long    uart_base,
                           unsigned char    inum_uart)
{
    uint8_t inum = 0;

    amhw_zlg_uart_stop_bit_sel(p_hw_uart, AMHW_ZLG_UART_STOP_1BIT);
    amhw_zlg_uart_data_length(p_hw_uart, AMHW_ZLG_UART_DATA_8BIT);
    amhw_zlg_uart_parity_bit_sel(p_hw_uart,  AMHW_ZLG_UART_PARITY_NO);

    /* ���ô��ڲ����� */
    amhw_zlg_uart_baudrate_set(p_hw_uart, clk_rate, UART_BAUDRATE);

    /* �ر����д����ж� */
    amhw_zlg_uart_int_disable(p_hw_uart, AMHW_ZLG_UART_INT_ALL_ENABLE_MASK);

    /* �������ͬ���ڶ�Ӧ���ж������� */
    if ((uint32_t)p_hw_uart - uart_base) {
        inum = inum_uart + 1;
    } else {
        inum = inum_uart;
    }

    /* ʹ�ܴ��� */
    amhw_zlg_uart_rx_enable(p_hw_uart,AM_TRUE);
    amhw_zlg_uart_tx_enable(p_hw_uart,AM_TRUE);
    amhw_zlg_uart_enable(p_hw_uart);

    /* ʹ��RDRF����׼�ж� */
    amhw_zlg_uart_int_enable(p_hw_uart, AMHW_ZLG_UART_INT_RX_VAL_ENABLE);

    /* �����ж������ţ������ж� */
    am_int_connect(inum, uart_hw_irq_handler, (void *)p_hw_uart);
    am_int_enable(inum);
}

/**
 * \brief �������
 */
void demo_zlg_hw_uart_int_entry (amhw_zlg_uart_t *p_hw_uart, 
                                 uint32_t         clk_rate,
                                 unsigned long    uart_base,
                                 unsigned char    inum_uart)
{

    uart_int_init(p_hw_uart, clk_rate , uart_base, inum_uart);

    uart_int_send(p_hw_uart, hw_polling_str, sizeof(hw_polling_str));

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg_hw_uart_int] */

/* end of file */
