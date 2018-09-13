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
 * - ʵ������
 *   1. ָ�����ڴ�ӡ��ʾ�ַ� "DMA tx transfer start:"��
 *   2. Ȼ��ָ�����ڴ�ӡһ���ڴ涨����ַ����ֱ�Ϊ��
 *      uart tx dma test running
 *      uart tx dma test done
 *
 * \note
 *    1. �� DMA �����ڼ䲻Ҫ�Դ������ݼĴ������в�����
 *
 * \par Դ����
 * \snippet demo_zlg_hw_uart_tx_dma.c src_zlg_hw_uart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-10  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_hw_uart_tx_dma
 * \copydoc demo_zlg_hw_uart_tx_dma.c
 */

/** [src_zlg_hw_uart_tx_dma] */
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

/** \brief DMA ���������� */
static amhw_zlg_dma_xfer_desc_t g_desc;

/** \brief ������ɱ�־ */
static volatile am_bool_t g_trans_done = AM_FALSE;

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst[]  = "uart tx dma test running\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst1[] = "uart tx dma test done\r\n";

/** \brief Ŀ������ݻ����� */
static uint8_t   g_buf_dst2[] = "DMA tx transfer start:\r\n";

static int32_t          g_dma_chan = 0;    /**< \brief DMA ͨ���� */
static amhw_zlg_uart_t *gp_hw_uart = NULL; /**< \brief UART ���� */

/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_zlg_dma_isr_connect() �������ݡ�
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (# AM_ZLG_DMA_INT_NORMAL) �� (# AM_ZLG_DMA_INT_ERROR)
 *
 * \return �ޡ�
 */
static void uart_dma_isr (void *p_arg , uint32_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_ZLG_DMA_INT_NORMAL) {
        if (flag_chan == g_dma_chan) {

            /* ����UART����ʱʹ��DMA���� */
            amhw_zlg_uart_dma_mode_enable(gp_hw_uart, AM_FALSE);
            g_trans_done = AM_TRUE;
        }
    } else {
        /* �û��Զ���ִ�д��� */
    }

}

/**
 * \brief DMA�������á�
 */
static int uart_tx_dma_tran_cfg (amhw_zlg_uart_t *p_hw_uart,
                                 int32_t          dma_chan,
                                 const uint8_t   *p_txbuf,
                                 uint32_t         dma_tran_len)
{
    uint32_t flags;

    /* ����DMA�жϷ����� */
    am_zlg_dma_isr_connect(dma_chan, uart_dma_isr, (void *)dma_chan);

    /* DMA�������� */
    flags = AMHW_ZLG_DMA_CHAN_PRIORITY_HIGH         |  /* ��������Դ���� */
            AMHW_ZLG_DMA_CHAN_MEM_SIZE_8BIT         |  /* Դ��ַ1�ֽ� */
            AMHW_ZLG_DMA_CHAN_PER_SIZE_8BIT         |  /* Ŀ�ĵ�ַ1�ֽ�д�� */
            AMHW_ZLG_DMA_CHAN_MEM_ADD_INC_ENABLE    |  /* ������Ӱ�� */
            AMHW_ZLG_DMA_CHAN_PER_ADD_INC_DISABLE   |  /* ��ͨ������ */
            AMHW_ZLG_DMA_CHAN_CIRCULAR_MODE_DISABLE ,  /* DMA�ж�ʹ�� */

    /* ����ͨ�������� */
    am_zlg_dma_xfer_desc_build(&g_desc,                        /* ͨ�������� */
                                (uint32_t)(p_txbuf),           /* Դ�����ݻ����� */
                                (uint32_t)(&(p_hw_uart->tdr)), /* Ŀ������ݻ����� */
                                dma_tran_len,                  /* �����ֽ��� */
                                flags);                        /* �������� */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_zlg_dma_xfer_desc_chan_cfg(&g_desc,
                                       AMHW_ZLG_DMA_MER_TO_PER,  /* �ڴ浽���� */
                                       dma_chan) == AM_ERROR) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief UART��ʼ��
 */
static void uart_hw_init (amhw_zlg_uart_t *p_hw_uart, uint32_t clk_rate)
{
    amhw_zlg_uart_baudrate_set(p_hw_uart,clk_rate, UART_BAUDRATE);

    amhw_zlg_uart_stop_bit_sel(p_hw_uart, AMHW_ZLG_UART_STOP_1BIT);
    amhw_zlg_uart_data_length(p_hw_uart, AMHW_ZLG_UART_DATA_8BIT);
    amhw_zlg_uart_parity_bit_sel(p_hw_uart,  AMHW_ZLG_UART_PARITY_NO);

    /* ʹ�ܴ��� */
    amhw_zlg_uart_tx_enable(p_hw_uart,AM_TRUE);
    amhw_zlg_uart_enable(p_hw_uart);
}


/**
 * \brief UART����DMA�����ʼ��
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
void demo_zlg_hw_uart_tx_dma_entry (amhw_zlg_uart_t *p_hw_uart,
                                    uint32_t         clk_rate,
                                    int32_t          dma_chan)
{
    uint8_t i = 0;
    uint8_t j = 0;

    gp_hw_uart = p_hw_uart;
    g_dma_chan = dma_chan;

    /* UART��ʼ�� */
    uart_hw_init(p_hw_uart, clk_rate);

    /* UART��DMA����ĳ�ʼ�� */
    uart_hw_dma_init(p_hw_uart);

    uart_tx_dma_tran_cfg(p_hw_uart, dma_chan, g_buf_dst2, sizeof(g_buf_dst2) - 1);

    am_zlg_dma_chan_start(dma_chan);

    while (1) {

        if (g_trans_done == AM_TRUE) {

            j++;
            g_trans_done = AM_FALSE;

            /* ���ڷ���DMA����ʹ�� */
            amhw_zlg_uart_dma_mode_enable(p_hw_uart,AM_TRUE);

            /* ʹ�ܴ��� */
            amhw_zlg_uart_tx_enable(p_hw_uart, AM_TRUE);

            if (j < 3) {
                am_zlg_dma_chan_stop(dma_chan);
                if (0 == i) {
                    uart_tx_dma_tran_cfg(p_hw_uart,
                                         dma_chan,
                                         g_buf_dst,
                                         sizeof(g_buf_dst) - 1);
                } else {
                    uart_tx_dma_tran_cfg(p_hw_uart,
                                         dma_chan,
                                         g_buf_dst1,
                                         sizeof(g_buf_dst1) - 1);
                }
                i++;
                am_zlg_dma_chan_start(dma_chan);
            }

        }
    }
}
/** [src_zlg116_hw_uart_tx_dma] */

/* end of file */
