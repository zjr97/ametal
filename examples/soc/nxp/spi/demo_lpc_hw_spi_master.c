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
 * \brief SPI ���������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI ������ SPI �ӻ������������ӡ�
 *
 * - ʵ������
 *   1. ������ÿ 500 ����ͨ�� SPI����ӻ����� "nihao" �ַ�����
 *   2. �ӻ����յ��ַ�����ͨ�����ڽ��ַ�����ӡ�������� LED0 ��˸��
 *
 * \note
 *    1. ��������Ҫ�� demo_lpc_hw_spi_slave.c һͬ���ԣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc_hw_spi_master.c src_lpc_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.01 15-11-26  sky, modified
 * - 1.00 15-07-15  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_spi_master
 * \copydoc demo_lpc_hw_spi_master.c
 */

/** [src_lpc_hw_spi_master] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc_spi.h"

#define __SPI_SPEED        100000  /**< \brief SPI ���ʺ궨�� */
#define __SPI_PRE_DELAY    0       /**< \brief SSEL ��λ����ʼ֡����ʱ */
#define __SPI_POST_DELAY   0       /**< \brief ֡ĩβ�� SSEL �����λ����ʱ */
#define __SPI_FRAME_DELAY  0       /**< \brief SPI ��������֡����ʱ */
#define __SPI_TRANS_DELAY  0       /**< \brief ���δ��� SSEL �����λ����ʱ */

/**
 * \brief SPI0 Ӳ����ʼ��
 *
 * \param[in] p_hw_spi ָ�� SPI �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __spi_master_hard_init (amhw_lpc_spi_t *p_hw_spi,
                                      uint32_t        clk)
{

    /* ���� SPI ��Ƶֵ */
    amhw_lpc_spi_div_set(
        p_hw_spi,
        ((clk / __SPI_SPEED)));

    /* ���� SPI ������ʱ */
    amhw_lpc_spi_pre_delay(p_hw_spi, __SPI_PRE_DELAY);
    amhw_lpc_spi_post_delay(p_hw_spi, __SPI_POST_DELAY);
    amhw_lpc_spi_frame_delay(p_hw_spi, __SPI_FRAME_DELAY);
    amhw_lpc_spi_trans_delay(p_hw_spi, __SPI_TRANS_DELAY);

    /* ���� SPI ������� */
    amhw_lpc_spi_cfg_set(p_hw_spi,
                         AMHW_LPC_SPI_CFG_MASTER | AMHW_LPC_SPI_CFG_CHANGE);
    amhw_lpc_spi_enable(p_hw_spi);

    /* ���� SPI һ�����ݳ���Ϊ 8 λ */
    amhw_lpc_spi_data_flen_set(p_hw_spi, 8);
}

/**
 * \brief SPI0 �����ֽ�
 *
 * \param[in] p_hw_spi ָ�� SPI �Ĵ������ָ��
 * \param[in] dat      Ҫ���͵��ֽ�����
 *
 * \return ��
 */
am_local void __spi_sent_byte (amhw_lpc_spi_t *p_hw_spi, uint16_t dat)
{

    /* �ȴ����Ϳ��мĴ�����λ */
    while (!(amhw_lpc_spi_stat_get(p_hw_spi) & AMHW_LPC_SPI_STAT_IDLE));

    /* �������� */
    amhw_lpc_spi_txdatctl(p_hw_spi,
                          dat,
                          AMHW_LPC_SPI_TXDATCTL_EOT |
                          AMHW_LPC_SPI_TXDATCTL_RX_IGNORE,
                          8);
}

/**
 * \brief SPI0 �����ַ���
 *
 * \param[in] p_hw_spi ָ�� SPI �Ĵ������ָ��
 * \param[in] p_str    Ҫ�����ַ�����ַ
 *
 * \return ��
 */
am_local void __spi_sent_str(amhw_lpc_spi_t *p_hw_spi, am_const uint8_t *p_str)
{
    while (*p_str != 0) {
        __spi_sent_byte(p_hw_spi, *p_str++);
    }
}

void demo_lpc_hw_spi_master_entry(amhw_lpc_spi_t *p_hw_spi,
                                     uint32_t        clk)
{
    /* SPI0 Ӳ����ʼ�� */
    __spi_master_hard_init(p_hw_spi, clk);

    AM_FOREVER {

        /* SPI �����ַ��� */
        __spi_sent_str(p_hw_spi, (am_const uint8_t *)"nihao");

        am_mdelay(500);

    }
}
/** [src_lpc_hw_spi_master] */

/* end of file */
