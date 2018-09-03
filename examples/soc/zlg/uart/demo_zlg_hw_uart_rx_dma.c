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
 * \brief UART DMA �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ͨ����λ������һ������ MCU ���� 5 ���ַ���
 *
 * - ʵ������
 *   1. ָ�����ڴ�ӡ�����յ������ݣ�
 *   2. Ȼ��ָ�����ڴ�ӡ�� "DMA transfer done!"��
 *
 * \par Դ����
 * \snippet demo_zlg_hw_uart_rx_dma.c src_zlg_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 17-03-10  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_hw_uart_rx_dma
 * \copydoc demo_zlg_hw_uart_rx_dma.c
 */

/** [src_zlg_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_int.h"
//#include "am_zlg116.h"
#include "am_zlg_dma.h"
#include "hw/amhw_zlg_uart.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_BAUDRATE      (115200)             /**< \brief ������ */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zlg_dma_xfer_desc_t g_desc;                  /**< \brief DMA ���������� */
static volatile am_bool_t       g_trans_done = AM_FALSE; /**< \brief ������ɱ�־ */
static uint8_t                  g_buf_dst[5] = {0};      /**< \brief Ŀ������ݻ����� */
static int32_t                  g_dma_chan = 0;          /**< \brief DMA ͨ���� */
static amhw_zlg_uart_t         *gp_hw_uart = NULL;       /**< \brief UART ���� */

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_zlg_dma_isr_connect() ��������
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AM_ZLG116_DMA_INT_ERROR) �� (#AM_ZLG116_DMA_INT_NORMAL)
 *
 * \return ��
 */
static void uart_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_ZLG_DMA_INT_NORMAL) {
        if (flag_chan == g_dma_chan) {

            /* ����UART���� */
            amhw_zlg_uart_rx_enable(gp_hw_uart, AM_FALSE);

            /* ����UART����ʱʹ��DMA���� */
            amhw_zlg_uart_dma_mode_enable(gp_hw_uart, AM_FALSE);

            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }
}

/**
 * \brief UART����DMA��������
 */
static int uart_rx_dma_tran_cfg (amhw_zlg_uart_t *p_hw_uart,
                                 int32_t          dma_chan,
                                 uint32_t         dma_tran_len)
{
    uint32_t i;
    uint32_t flags;

    for (i = 0; i < sizeof(g_buf_dst); i++) {
        g_buf_dst[i] = 0;
    }

    /* DMA�������� */
    flags = AMHW_ZLG_DMA_CHAN_PRIORITY_HIGH         |  /* ��������Դ���� */
            AMHW_ZLG_DMA_CHAN_MEM_SIZE_8BIT         |  /* Դ��ַ1�ֽ� */
            AMHW_ZLG_DMA_CHAN_PER_SIZE_8BIT         |  /* Ŀ�ĵ�ַ1�ֽ�д�� */
            AMHW_ZLG_DMA_CHAN_MEM_ADD_INC_ENABLE    |  /* ������Ӱ�� */
            AMHW_ZLG_DMA_CHAN_PER_ADD_INC_DISABLE   |  /* ��ͨ������ */
            AMHW_ZLG_DMA_CHAN_CIRCULAR_MODE_DISABLE ,  /* DMA�ж�ʹ�� */

    /* ����DMA�жϷ����� */
    am_zlg_dma_isr_connect(dma_chan, uart_dma_isr, (void *)dma_chan);


    /* ����ͨ�������� */
    am_zlg_dma_xfer_desc_build(&g_desc,                      /* ͨ�������� */
                                   (uint32_t)(&(p_hw_uart->rdr)), /* Դ�����ݻ��� */
                                   (uint32_t)(g_buf_dst),       /* Ŀ�����ݻ��� */
                                   (uint32_t)dma_tran_len,      /* �����ֽ��� */
                                   flags);                      /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_zlg_dma_xfer_desc_chan_cfg(&g_desc,
                                          AMHW_ZLG_DMA_PER_TO_MER, /* ���赽 �ڴ� */
                                          (uint8_t)dma_chan) == AM_ERROR) {
        return AM_ERROR;
    } else {
        /* �������� */
    }

    return AM_OK;
}

/**
 * \brief UART ��ʼ��
 */
static void uart_hw_init (amhw_zlg_uart_t *p_hw_uart, uint32_t clk_rate)
{
    amhw_zlg_uart_baudrate_set(p_hw_uart, clk_rate, UART_BAUDRATE);

    amhw_zlg_uart_stop_bit_sel(p_hw_uart, AMHW_ZLG_UART_STOP_1BIT);
    amhw_zlg_uart_data_length(p_hw_uart, AMHW_ZLG_UART_DATA_8BIT);
    amhw_zlg_uart_parity_bit_sel(p_hw_uart,  AMHW_ZLG_UART_PARITY_NO);

    /* ʹ�ܴ��� */
    amhw_zlg_uart_tx_enable(p_hw_uart, AM_TRUE);
    amhw_zlg_uart_rx_enable(p_hw_uart, AM_TRUE);
    amhw_zlg_uart_enable(p_hw_uart);
}

/**
 * \brief UART���մ���ʱDMA��ʼ��
 */
static void uart_hw_dma_init (amhw_zlg_uart_t *p_hw_uart)
{
    /* ���ڷ���DMA����ʹ�� */
    amhw_zlg_uart_dma_mode_enable(p_hw_uart, AM_TRUE);

    /* ʹ�ܴ��� */
    amhw_zlg_uart_enable(p_hw_uart);
}

/**
 * \brief �������
 */
void demo_zlg_hw_uart_rx_dma_entry (amhw_zlg_uart_t *p_hw_uart,
                                    uint32_t         clk_rate,
                                    int32_t          dma_chan)
{
    gp_hw_uart = p_hw_uart;
    g_dma_chan = dma_chan;

    /* UART��ʼ�� */
    uart_hw_init(p_hw_uart, clk_rate);

    /* UART����DMA����ĳ�ʼ�� */
    uart_hw_dma_init(p_hw_uart);

    amhw_zlg_uart_poll_send(p_hw_uart,
                            (uint8_t *)"UART DMA RX start:\r\n",
                            (uint32_t)sizeof("UART DMA RX start:\r\n") - 1);
    /* ��ʼDMA���� */
    uart_rx_dma_tran_cfg(p_hw_uart, dma_chan, sizeof(g_buf_dst));
    am_zlg_dma_chan_start(dma_chan);

    /* �ȴ�������� */
    while (g_trans_done == AM_FALSE);

    g_trans_done = AM_FALSE;

    amhw_zlg_uart_poll_send(p_hw_uart, g_buf_dst, sizeof(g_buf_dst));
    amhw_zlg_uart_poll_send(p_hw_uart,
                            (uint8_t *)"\r\nDMA transfer done!\r\n",
                            sizeof("\r\nDMA transfer done!\r\n") - 1);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg_hw_uart_rx_dma] */

/* end of file */
