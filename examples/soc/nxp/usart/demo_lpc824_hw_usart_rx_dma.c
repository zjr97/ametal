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
 * \brief USART �����������̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. ����λ�����յ� "DMA rx transfer start:" ʱ��ͨ����λ��һ������ MCU ����
 *      16 ���ַ���
 *
 * - ʵ������
 *   1  ���ڴ�ӡ "DMA rx transfer start:"��
 *   1. ���ڴ�ӡ�����յ������ݣ�
 *   2. ���ڴ�ӡ "DMA transfer done!"��
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_usart_rx_dma.c src_lpc824_hw_usart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-15  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_usart_rx_dma
 * \copydoc demo_lpc824_hw_usart_rx_dma.c
 */

/** [src_lpc824_hw_usart_rx_dma] */
#include "ametal.h"
#include "am_board.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc_usart.h"
#include "hw/amhw_lpc82x_clk.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/**
 * \brief ��������Ƶ�����ã���������Ƶ�ʱ���С��ϵͳʱ��Ƶ����ӦΪ�����ʵ���������
 *
 * Ϊ�����ò�����Ϊ 115200�������ô��ڻ�������Ƶ��Ϊ��
 * 11059200Hz(11059200 = 115200 * 96)��
 * ���ڻ�������Ƶ������Ϊ 11.059200MHz�����������������ʵ����� (9600,4800,115200)
 *
 * \note  USART0\1\2 ����һ����������Ƶ��,��Ҫ���׸Ķ�
 */
#define  __LPC82X_UASART_BASE_RATE  11059200

/** \brief DMA ���ڽ��մ�С */
#define __USART_RX_BYTES            16

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/
am_local uint8_t __g_buf_dst[256];             /**< \brief Ŀ������ݻ����� */
am_local am_lpc82x_dma_controller_t *__gp_ctr = NULL; /**< \brief DMAͨ�������� */

/**
 * \brief DMA ������ɻص�����
 *
 * \param[in] p_arg �û��Զ������
 * \param[in] stat  DMA �������״̬��־���ò����Ŀ���ȡֵ��
 *                      AM_LPC82X_DMA_STAT_INTA
 *                      AM_LPC82X_DMA_STAT_INTB
 *                      AM_LPC82X_DMA_STAT_INTERR
 *
 * \return ��
 */
am_local void __rx_dma_callback (void *p_arg, int stat)
{
    amhw_lpc_usart_t *p_hw_usart = (amhw_lpc_usart_t *)p_arg;
    if (stat & AM_LPC82X_DMA_STAT_INTA) {

        /* DMA ������� */
        am_lpc82x_dma_controller_release(__gp_ctr);

        amhw_lpc_usart_poll_send(p_hw_usart, __g_buf_dst, __USART_RX_BYTES);

        amhw_lpc_usart_poll_send(p_hw_usart,
                                 (am_const uint8_t *)"\r\nDMA transfer done!\r\n",
                                 sizeof("DMA transfer done!\r\n") - 1);
    }

    if (stat & AM_LPC82X_DMA_STAT_INTERR) {

        /* �������ִ�д��� */
    }
}

/**
 * \brief USART ͨ�� DMA ��������
 */
am_local void __usart_dma_receive (amhw_lpc_usart_t *p_hw_usart,
                                   am_const uint8_t *p_rxbuf, 
                                   uint32_t          nbytes,
                                   int               chan)
{
    am_lpc82x_dma_transfer_t transfer;

    /* ���� DMA ������ */
    __gp_ctr = am_lpc82x_dma_controller_get(chan,
                                            DMA_CHAN_OPT_PRIO_3 |
                                            DMA_CHAN_OPT_PERIPH_REQ_EN);
    /* ���� DMA ���������� */
    am_lpc82x_dma_transfer_build(&transfer,
                                  (uint32_t)&(p_hw_usart->rxdat),
                                  (uint32_t)p_rxbuf,
                                  nbytes,
                                  AM_LPC82X_DMA_TRANS_WIDTH_8BIT |
                                  AM_LPC82X_DMA_TRANS_SRCINC_NOINC |
                                  AM_LPC82X_DMA_TRANS_DSTINC_1X);

    /* ��ʼ DMA ���� */
    am_lpc82x_dma_transfer(__gp_ctr,
                          &transfer,
                           __rx_dma_callback,
                           (void*)p_hw_usart);
}

/**
 * \brief USART ��ʼ��
 */
void demo_lpc824_hw_usart_rx_dma_entry (amhw_lpc_usart_t *p_hw_usart,
                                        uint32_t          uclk,
                                        uint32_t          baudrate,
                                        int               chan)
{

    /* USART0 8 λ���ݳ��� 1 λֹͣλ ����żУ�� */
    amhw_lpc_usart_config(p_hw_usart,
                          AMHW_LPC_USART_CFG_8BIT |
                          AMHW_LPC_USART_CFG_STOP_1 |
                          AMHW_LPC_USART_CFG_PARITY_NO);

   /* ������ 115200 */
    amhw_lpc_usart_baudrate_set(p_hw_usart,
                                uclk,
                                baudrate);

    /* ʹ�ܴ��� */
    amhw_lpc_usart_enable(p_hw_usart);
    amhw_lpc_usart_poll_send(p_hw_usart,
                             (am_const uint8_t *)"DMA rx transfer start:\r\n",
                             sizeof("DMA rx transfer start:\r\n") - 1);

    /* �ȴ����ڷ��Ϳ��� */
    while ((amhw_lpc_usart_stat_get(p_hw_usart) &
            AMHW_LPC_USART_STAT_TXIDLE) == 0);

    /* ��ʼ DMA ���䣬�������� */
    __usart_dma_receive(p_hw_usart, __g_buf_dst, __USART_RX_BYTES, chan);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_lpc824_hw_usart_rx_dma] */

/* end of file */
