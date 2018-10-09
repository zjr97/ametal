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
 * - ʵ������
 *   1. ���ڴ�ӡ "DMA tx transfer start:"��
 *   2. ������� "aAbBcCdD...",�� 256 ���ֽڣ�
 *   3. DMA ������ɺ󴮿ڴ�ӡ "DMA transfer done!"��
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_usart_tx_dma.c src_lpc824_hw_usart_tx_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-15  bob, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_lpc824_hw_usart_tx_dma
 * \copydoc demo_lpc824_hw_usart_tx_dma.c
 */

/** [src_lpc824_hw_usart_tx_dma] */
#include "ametal.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc_usart.h"
#include "hw/amhw_lpc82x_clk.h"
#include "lpc82x_dma_chan.h"

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/
am_local uint8_t __g_buf_src[256];                    /**< \brief Դ�����ݻ����� */
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
 * \return  ��
 */
am_local void __tx_dma_callback (void *p_arg, int stat)
{
    amhw_lpc_usart_t *p_hw_usart = (amhw_lpc_usart_t *)p_arg;
    if (stat & AM_LPC82X_DMA_STAT_INTA) {

        /* DMA ������� */
        am_lpc82x_dma_controller_release(__gp_ctr);

        amhw_lpc_usart_poll_send(p_hw_usart,
                                 (am_const uint8_t *)"\r\n",
                                 sizeof("\r\n") - 1);

        amhw_lpc_usart_poll_send(p_hw_usart,
                                 (am_const uint8_t *)"DMA transfer done!\r\n",
                                 sizeof("DMA transfer done!\r\n") - 1);
    }

    if (stat & AM_LPC82X_DMA_STAT_INTERR) {

        /* �������ִ�д��� */
    }
}
/**
 * \brief DMA ����
 *
 * \param[in] p_txbuf Ҫ���͵������ַ
 * \param[in] nbytes  ���͵��ֽ���
 *
 * \return ��
 */
am_local void __usart_dma_send (amhw_lpc_usart_t *p_hw_usart,
                                am_const uint8_t *p_txbuf, 
                                uint32_t          nbytes,
                                int               chan)
{
    am_lpc82x_dma_transfer_t    transfer;

    /* ���� DMA ������ */
    __gp_ctr = am_lpc82x_dma_controller_get(chan,
                                            DMA_CHAN_OPT_PRIO_3 |
                                            DMA_CHAN_OPT_PERIPH_REQ_EN);
    /* ���� DMA ���������� */
    am_lpc82x_dma_transfer_build(&transfer,
                                  (uint32_t)p_txbuf,
                                  (uint32_t)&(p_hw_usart->txdat),
                                  nbytes,     /* �����ֽ��� */
                                  AM_LPC82X_DMA_TRANS_WIDTH_8BIT |
                                  AM_LPC82X_DMA_TRANS_SRCINC_1X |
                                  AM_LPC82X_DMA_TRANS_DSTINC_NOINC);
    /* ��ʼ DMA ���� */
    am_lpc82x_dma_transfer(__gp_ctr,
                          &transfer,
                           __tx_dma_callback,
                           (void*)p_hw_usart);
}

/**
 * \brief USART ��ʼ��
 */
void demo_lpc824_hw_usart_tx_dma_entry (amhw_lpc_usart_t *p_hw_usart,
                                        uint32_t          uclk,
                                        uint32_t          baudrate,
                                        int               chan)
{
    uint32_t i = 0;

    /* USART0 8 λ���ݳ��� 1 λֹͣλ ����żУ�� */
    amhw_lpc_usart_config(p_hw_usart,
                          AMHW_LPC_USART_CFG_8BIT |
                          AMHW_LPC_USART_CFG_STOP_1 |
                          AMHW_LPC_USART_CFG_PARITY_NO);

   /* ������ 115200 */
    amhw_lpc_usart_baudrate_set (p_hw_usart,
                                 uclk,
                                 baudrate);

    /* ʹ�ܴ��� */
    amhw_lpc_usart_enable(p_hw_usart);
    amhw_lpc_usart_poll_send(p_hw_usart,
                             (am_const uint8_t *)"DMA tx transfer start:\r\n",
                             sizeof("DMA tx transfer start:\r\n") - 1);

    /* �Է������鸳ֵ */
    for (i = 0; i < 256; i += 2) {
        __g_buf_src[i]     = i / 2 % 26 + 'a';
        __g_buf_src[i + 1] = i / 2 % 26 + 'A';
    }

    /* ����DMA ���� */
    __usart_dma_send(p_hw_usart,__g_buf_src, 256, chan);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_lpc824_hw_usart_tx_dma] */

/* end of file */
