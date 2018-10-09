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
 * \brief SPI �ӻ������������̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �ӿں�����Դ��Ӧ�� SPI �ӿ�����������
 *
 * - ʵ������
 *   1. ���յ����ݣ�ͨ�����ڴ�ӡ������
 *
 * \note
 *    1. ����Դ��ѡ�� demo_am824_std_spi_master_dma.c �ĳ���
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. ���� PIO0_12 ���ͻᵼ�µ�Ƭ����λʱ���� ISP ģʽ������ PIO0_12 Ӧ
 *       ��Ƭ����λ�������ӡ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_spi_slave_dma.c src_lpc824_hw_spi_slave_dma
 *
 * \internal
 * \par History
 * - 1.01 15-11-27  sky, modified
 * - 1.00 15-07-16  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_spi_slave_dma
 * \copydoc demo_lpc824_hw_spi_slave_dma.c
 */

/** [src_lpc824_hw_spi_slave_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc_spi.h"
#include "hw/amhw_lpc82x_clk.h"

/** \brief ��������ӳ�� */
am_local __attribute__((aligned(16)))  am_lpc82x_dma_xfer_desc_t __g_desc[2];

am_local uint16_t __g_buf_dsta[16];                /**< \brief A ������������ */
am_local uint16_t __g_buf_dstb[16];                /**< \brief B ������������ */

am_local volatile uint8_t __g_a_transfer_done;     /**< \brief A ������ɱ�־ */
am_local volatile uint8_t __g_b_transfer_done;     /**< \brief B ������ɱ�־ */

/**
 * \brief DMA �жϷ�����
 *
 * \param[in] p_arg �жϷ�������ڲ���
 * \param[in] p_flg DMA �жϱ�־������ A �����жϣ�B �����жϣ������жϵȣ�
 *
 * \return ��
 */
am_local void __dma_isr (void *p_arg, int stat)
{
    if (stat & AM_LPC82X_DMA_STAT_INTA) {
        __g_a_transfer_done = 1;
    }

    if (stat & AM_LPC82X_DMA_STAT_INTB) {
        __g_b_transfer_done = 1;
    }

    if (stat & AM_LPC82X_DMA_STAT_INTERR) {

        /* �˴�û�д��� */
    }
}

/**
 * \brief DMA ƹ��ģʽ������Ժ���
 */
am_local void __dma_ping_pong_test (amhw_lpc_spi_t *p_hw_spi, uint8_t chan)
{
    uint32_t                    flags1 = 0;
    uint32_t                    flags2 = 0;
    am_lpc82x_dma_controller_t *p_ctr  = NULL;

    p_ctr = am_lpc82x_dma_controller_get(chan,
                                         DMA_CHAN_OPT_PRIO_0 |
                                         DMA_CHAN_OPT_PERIPH_REQ_EN);

    if (p_ctr == NULL) {
        AM_DBG_INFO("Geting a Controller Faild !\r\n");
        AM_FOREVER {};
    }

    /* DMA �������� 1 */
    flags1 = AM_LPC82X_DMA_XFER_VALID         | /* ��ǰͨ����������Ч */
             AM_LPC82X_DMA_XFER_RELOAD        | /* �����������ͨ�������� */
             AM_LPC82X_DMA_XFER_SWTRIG        | /* ������� */
             AM_LPC82X_DMA_XFER_WIDTH_16BIT   | /* �������ݿ�ȣ�16 bit */
             AM_LPC82X_DMA_XFER_SRCINC_NOINC  | /* Դ�����ݵ�ַ������ */
             AM_LPC82X_DMA_XFER_DSTINC_1X     | /* Ŀ�����ݵ�ַ�� 1 ����ȵ��� */
             AM_LPC82X_DMA_XFER_SETINTA;        /* ʹ���ж� A */

    /* DMA �������� 2 */
    flags2 = AM_LPC82X_DMA_XFER_VALID         | /* ��ǰͨ����������Ч */
             AM_LPC82X_DMA_XFER_RELOAD        | /* �����������ͨ�������� */
             AM_LPC82X_DMA_XFER_SWTRIG        | /* ������� */
             AM_LPC82X_DMA_XFER_WIDTH_16BIT   | /* �������ݿ�ȣ�16 bit */
             AM_LPC82X_DMA_XFER_SRCINC_NOINC  | /* Դ�����ݵ�ַ������ */
             AM_LPC82X_DMA_XFER_DSTINC_1X     | /* Ŀ�����ݵ�ַ�� 1 ����ȵ��� */
             AM_LPC82X_DMA_XFER_SETINTB;        /* ʹ���ж� B */

    /* ����ͨ�������� A */
    am_lpc82x_dma_xfer_desc_build(
       &__g_desc[0],                          /* A ������������ */
        (uint32_t)&(p_hw_spi->rxdat),         /* Դ�����ݵ�ַ */
        (uint32_t)__g_buf_dsta,               /* A �Ļ�������ַ */
        32,                                   /* �����ֽ��� */
        flags1);                              /* �������� 1 */

    /* ����ͨ�������� B */
    am_lpc82x_dma_xfer_desc_build(
       &__g_desc[1],                          /* B ������������ */
        (uint32_t)&(p_hw_spi->rxdat),         /* Դ�����ݵ�ַ */
        (uint32_t)__g_buf_dstb,               /* B �Ļ�������ַ */
        32,                                   /* �����ֽ��� */
        flags2);                              /* �������� 2 */

    am_lpc82x_dma_xfer_desc_link(&__g_desc[1], &__g_desc[0]); /* �������������� */
    am_lpc82x_dma_xfer_desc_link(&__g_desc[0], &__g_desc[1]); /* �������������� */

    /* DMA �������� */
    am_lpc82x_dma_xfer_desc_startup(p_ctr,
                                   &__g_desc[0],
                                    __dma_isr,
                                    (void*)0);
}

/**
 * \brief SPI �ӻ�����
 *
 * \param[in] p_hw_spi ָ�� SPI �Ĵ������ָ��
 * \param[in] len      ����֡���ȣ���Χ 1 ~ 16.
 *
 * \return ��
 */
am_local void __spi_slv_start (amhw_lpc_spi_t *p_hw_spi, uint8_t len)
{
    amhw_lpc_spi_data_flen_set(p_hw_spi, len);
}

/**
 * \brief SPI �ӻ���ʼ������
 *
 * \param[in] p_hw_spi ָ�� SPI �Ĵ������ָ��
 *
 * \retval AM_OK      �������
 * \retval -AM_EINVAL ������Ч
 */
am_local int __spi_slv_init (amhw_lpc_spi_t *p_hw_spi)
{
    amhw_lpc_spi_enable(p_hw_spi);         /* ������ɣ�ʹ�� SPI(Ĭ��Ϊ�ӻ�) */

    return AM_OK;
}


void demo_lpc824_hw_spi_slave_dma_entry(amhw_lpc_spi_t *p_hw_spi, uint8_t chan)
{
    uint8_t i = 0;

    /* SPI �ӻ���ʼ������ */
    __spi_slv_init(p_hw_spi);

    /* SPI �ֳ������� */
    __spi_slv_start(p_hw_spi, 16);

    AM_DBG_INFO("Transform Start \r\n");

    __dma_ping_pong_test(p_hw_spi, chan);

    AM_FOREVER {

        /* A ������ɱ�־λ��λ��ͨ�����ڽ����յ����ݴ�ӡ���� */
        if (__g_a_transfer_done) {
            __g_a_transfer_done = 0;
            for (i = 0; i < 16; i++){
                AM_DBG_INFO("A_buf %2dst is :0x%04x\r\n", i, __g_buf_dsta[i]);
            }
        }

        /* B ������ɱ�־λ��λ��ͨ�����ڽ����յ����ݴ�ӡ���� */
        if (__g_b_transfer_done) {
            __g_b_transfer_done = 0;
            for (i = 0; i < 16; i++){
                AM_DBG_INFO("B_buf %2dst is :0x%04x\r\n", i, __g_buf_dstb[i]);
            }
        }
    }
}
/** [src_lpc824_hw_spi_slave_dma] */

/* end of file */
