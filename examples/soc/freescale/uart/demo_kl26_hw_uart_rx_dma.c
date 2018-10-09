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
 * \brief UART0ͨ��DMA��ʽ�������ݣ�ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. PIOC_3 ��������PC���ڵ�TXD;
 *   2. PIOC_4 ��������PC���ڵ�RXD;
 *   3. ������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *   4. ͨ����λ������һ������MCU����5���ַ���
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����յ�������;
 *   2. Ȼ�󴮿ڴ�ӡ����DMA transfer done!����

 *
 * \par Դ����
 * \snippet demo_kl26_hw_uart_rx_dma.c src_kl26_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-21  nwt, make some changes.
 * - 1.00 15-07-10  xym, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_hw_uart_rx_dma
 * \copydoc demo_kl26_hw_uart_rx_dma.c
 */

/** [src_kl26_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_fsl_uart.h"
#include "hw/amhw_kl26_sim.h"
#include "am_kl26_clk.h"
#include "am_kl26_dma.h"
#include "am_kl26_inst_init.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_CH            KL26_UART1  /**< \brief UARTͨ��     */
#define UART_BAUDRATE      (115200)         /**< \brief ������       */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

static volatile am_bool_t  __g_trans_done  = AM_FALSE; /**< \brief ������ɱ�־. */
static uint8_t __g_buf_dst[5] = {0};                /**< \brief Ŀ������ݻ����� */

/*******************************************************************************
  ������ǰ����
*******************************************************************************/
static int uart_rx_dma_tran_cfg (uint32_t dma_tran_len);

/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_kl26_dma_isr_connect() �������ݡ�
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AM_KL26_DMA_INT_ERROR) �� (#AM_KL26_DMA_INT_NORMAL)��

 * \return    �ޡ�
 */
static void uart_dma_isr (void *p_arg , uint8_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_KL26_DMA_INT_NORMAL) {
        if (flag_chan == DMA_CHAN_0) {
            /* ����UART����.*/
            amhw_fsl_uart_c2_rx_disable(UART_CH);

            /* ��uart0����ʱDMA������Ҫ�����ж� */
            if (UART_CH != KL26_UART0) {
               /* ���ܽ����ж�*/
               amhw_fsl_uart_int_disable(UART_CH, AMHW_FSL_UART_INT_C2_IRIE);
            }

            /* ����UART����ʱʹ��DMA����.*/
            if(UART_CH == KL26_UART0){
                 amhw_fsl_uart_ver0_dma_rx_disable(UART_CH);
            }else {
                 amhw_fsl_uart_ver1_dma_rx_disable(UART_CH);
            }

            /* ֹͣDMAͨ��. */
            am_kl26_dma_chan_stop(DMA_CHAN_0);

            __g_trans_done = AM_TRUE;

        }
    } else {
        /* �û��Զ���ִ�д��� */
    }
}

/**
 * \brief ���ݲ�ͬ�Ĵ���������Ӧ��DMA����Դ
 */
static uint8_t uart_dma_src_request_set (void)
{
    if (UART_CH == KL26_UART0) {
        return DMA_REQUEST_MUX0_UART0RX;
    } else if (UART_CH == KL26_UART1) {
        return DMA_REQUEST_MUX0_UART1RX;
    } else {
        return DMA_REQUEST_MUX0_UART2RX;
    }
}

/**
 * \brief UART����DMA��������
 */
static int uart_rx_dma_tran_cfg (uint32_t dma_tran_len)
{
    uint32_t i;
    uint32_t flags;
    static amhw_kl26_dma_xfer_desc_t desc;   /**< \brief DMA ���������� */

    for (i = 0; i < sizeof(__g_buf_dst); i++) {
        __g_buf_dst[i] = 0;
    }

    /* DMA�������� */
    flags = KL26_DMA_DCR_PER_REQUEST_ENABLE     |  /* ��������Դʹ��    */
            KL26_DMA_DCR_SINGLE_TRANSFERS       |  /* ���δ���          */
            KL26_DMA_DCR_AUTO_ALIGN_DISABLE     |  /* �Զ��������      */
            KL26_DMA_DCR_SOURCE_SIZE_8_BIT      |  /* Դ��ַ1�ֽڶ�ȡ   */
            KL26_DMA_DCR_DESTINATION_SIZE_8_BIT |  /* Ŀ�ĵ�ַ1�ֽ�д�� */
            KL26_DMA_DCR_REQUEST_NO_AFFECTED    |  /* ������Ӱ��        */
            KL26_DMA_DCR_NO_LINKING             |  /* ��ͨ������        */
            KL26_DMA_DCR_INTERRUTP_ENABLE       |  /* DMA�ж�ʹ��       */
            KL26_DMA_DCR_START_DISABLE    ;        /* DMA��ʼ����ʹ��   */

    /* ����DMA�жϷ����� */
    am_kl26_dma_isr_connect(DMA_CHAN_0, uart_dma_isr, (void *)0);

    am_kl26_dma_chan_cfg(DMA_CHAN_0,
                         KL26_DMA_TRIGGER_DISABLE |     /**< \brief DMA����ģʽ */
                         uart_dma_src_request_set());        /**< \brief ����Դ      */

    /* ����ͨ�������� */
    am_kl26_dma_xfer_desc_build(&desc,                           /* ͨ��������   */
                                (uint32_t)(&(UART_CH->data)),      /* Դ�����ݻ��� */
                                (uint32_t)(__g_buf_dst),             /* Ŀ�����ݻ��� */
                                (uint32_t)dma_tran_len,            /* �����ֽ���   */
                                flags);                            /* ��������     */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_kl26_dma_chan_start(&desc,
                               KL26_DMA_PER_TO_MER,   /* ���赽 �ڴ�   */
                               (uint8_t)DMA_CHAN_0) == AM_ERROR) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief UARTʱ��ʹ�ܳ�ʼ��
 * \param[in] p_hw_uart : ָ�򴮿��豸�Ĵ����ṹ��, ��KL26_UART1.
 */
static void uart_clock_init (void *p_hw_uart)
{
    uint32_t base_addr = (uint32_t)(p_hw_uart);

    switch (base_addr) {

    /* ����0ʱ�ӳ�ʼ��.     */
    case KL26_UART0_BASE:
        amhw_kl26_sim_uart0_src_set(KL26_SIM_UART0SRC_PLLFLLCLK);
        /* ����UART0ʱ��. */
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART0);
        break;

    /* ����1ʱ�ӳ�ʼ��.    */
    case KL26_UART1_BASE:
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART1);
        break;

    /* ����2ʱ�ӳ�ʼ��.    */
    case KL26_UART2_BASE:
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART2);
        break;
    }
}

/**
 * \brief UART���ų�ʼ��
 * \param[in] p_hw_uart : ָ�򴮿��豸�Ĵ����ṹ��, ��KL26_UART1.
 */
static void uart_pin_init (void *p_hw_uart)
{
    uint32_t base_addr = (uint32_t)(p_hw_uart);

    switch (base_addr) {

    case KL26_UART0_BASE:
        am_gpio_pin_cfg (PIOE_21,PIOE_21_UART0_RX);
        am_gpio_pin_cfg (PIOE_20,PIOE_20_UART0_TX);
        break;

    case KL26_UART1_BASE:
        /* ���ų�ʼ��      PIOC_3_UART1_RX  PIOC_4_UART1_TX     */
        am_gpio_pin_cfg (PIOC_3,PIOC_3_UART1_RX);
        am_gpio_pin_cfg (PIOC_4,PIOC_4_UART1_TX);
        break;

    case KL26_UART2_BASE:
        /* ���ų�ʼ��      PIOD_4_UART2_RX  PIOD_5_UART2_TX     */
        am_gpio_pin_cfg (PIOD_4,PIOD_4_UART2_RX);
        am_gpio_pin_cfg (PIOD_5,PIOD_5_UART2_TX);
        break;
    }
}

/**
 * \brief UART��ʼ��
 */
static void uart_hw_init (void)
{
    /* ʹ�ܴ���ʱ��ģ�� */
    uart_clock_init(UART_CH);

    /* ���ô�������������� */
    uart_pin_init(UART_CH);

    amhw_fsl_uart_stop_bit_set (UART_CH, AMHW_FSL_UART_BDH_SBNS_STOP_1);
    amhw_fsl_uart_data_mode_set(UART_CH, AMHW_FSL_UART_C1_M_8BIT);
    amhw_fsl_uart_parity_set(UART_CH,  AMHW_FSL_UART_C1_PARITY_NO);

    /* ���ô��ڲ����� */
    if(UART_CH == KL26_UART0){
        amhw_fsl_uart_ver0_baudrate_set(UART_CH,
                                        am_kl26_clk_periph_rate_get((void *)(UART_CH)),
                                        UART_BAUDRATE);
    }else {
        amhw_fsl_uart_ver1_baudrate_set(UART_CH,
                                        am_kl26_clk_periph_rate_get((void *)(UART_CH)),
                                        UART_BAUDRATE);
    }
}

/**
 * \brief UART���մ���ʱDMA��ʼ��
 */
static void uart_hw_dma_init (void)
{
    /* ����0����DMA����ʹ��  */
    if(UART_CH == KL26_UART0){
        amhw_fsl_uart_ver0_dma_rx_enable(UART_CH);
    }else {
        amhw_fsl_uart_ver1_dma_rx_enable(UART_CH);
    }

    /* ��uart0����ʱDMA������Ҫʹ���ж� */
    if (UART_CH != KL26_UART0) {
       /* ʹ�ܽ����жϣ��ж��źŴ���DMA���� */
       amhw_fsl_uart_int_enable(UART_CH, AMHW_FSL_UART_INT_C2_IRIE);
    }

    /* ʹ�ܴ��� */
    amhw_fsl_uart_enable(UART_CH);
}

/**
 * \brief �������
 */
void demo_kl26_hw_uart_rx_dma_entry (void)
{
    /* DMA��ʼ��.         */
    am_kl26_dma_inst_init();

    /* UART��ʼ��.         */
    uart_hw_init();

    /* UART����DMA����ĳ�ʼ�� */
    uart_hw_dma_init();

    amhw_fsl_uart_poll_send(UART_CH,(uint8_t *)"UART DMA RX start:\r\n",
                             (uint32_t)sizeof("UART DMA RX start:\r\n") - 1);
    /* ��ʼDMA���� */
    uart_rx_dma_tran_cfg(sizeof(__g_buf_dst));

    while (1) {
        /* �ȴ��������  */
        uint32_t key = am_int_cpu_lock();
        if (__g_trans_done == AM_TRUE) {
            __g_trans_done = AM_FALSE;
            am_int_cpu_unlock(key);
            amhw_fsl_uart_poll_send(UART_CH, __g_buf_dst, sizeof(__g_buf_dst));

            amhw_fsl_uart_poll_send(UART_CH, (uint8_t *)"\r\nDMA transfer done!\r\n",
                                     sizeof("\r\nDMA transfer done!\r\n") - 1);

            uart_rx_dma_tran_cfg(sizeof(__g_buf_dst));

            /* ����0����DMA����ʹ��  */
            if(UART_CH == KL26_UART0){
                amhw_fsl_uart_ver0_dma_rx_enable(UART_CH);
            }else {
                amhw_fsl_uart_ver1_dma_rx_enable(UART_CH);
            }

            /* ��uart0����ʱDMA������Ҫʹ���ж� */
            if (UART_CH != KL26_UART0) {
               /* ʹ�ܽ����жϣ��ж��źŴ���DMA���� */
               amhw_fsl_uart_int_enable(UART_CH, AMHW_FSL_UART_INT_C2_IRIE);
            }

            /* ʹ����UART����.*/
            amhw_fsl_uart_c2_rx_enable(UART_CH);
        } else {
            am_int_cpu_unlock(key);
        }
    }
}

/** [src_kl26_hw_uart_rx_dma] */

/* end of file */
