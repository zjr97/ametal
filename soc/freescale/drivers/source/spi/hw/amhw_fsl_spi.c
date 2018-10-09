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
 * \brief  SPIӲ����ʵ���ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-26  sdy, first implementation.
 * \endinternal
 */

#include "hw/amhw_fsl_spi.h"

/**
 * \brief ʹ��SPI��ͨ�ж�
 */
void amhw_fsl_spi_int_enable (amhw_fsl_spi_t *p_hw_spi, uint8_t irq_flags)
{
    if ( irq_flags & AMHW_FSL_SPI_IRQ_MATCH) {       /* ����ƥ���ж�       */
        p_hw_spi->c2 |= 0x80;
    }
    if ( irq_flags & AMHW_FSL_SPI_IRQ_R_MODDEF) {    /* ���ջ�������ж�   */
        p_hw_spi->c1 |= 0x80;
    }
    if ( irq_flags & AMHW_FSL_SPI_IRQ_T) {           /* ��������ж�       */
        p_hw_spi->c1 |= 0x20;
    }
}

/**
 * \brief ����SPI��ͨ�ж�
 */
void amhw_fsl_spi_int_disable (amhw_fsl_spi_t *p_hw_spi, uint8_t irq_flags)
{
    if ( irq_flags & AMHW_FSL_SPI_IRQ_MATCH) {       /* ����ƥ���ж�       */
        p_hw_spi->c2 &= (~0x80);
    }
    if ( irq_flags & AMHW_FSL_SPI_IRQ_R_MODDEF) {    /* ���ջ�������ж�   */
        p_hw_spi->c1 &= (~0x80);
    }
    if ( irq_flags & AMHW_FSL_SPI_IRQ_T) {           /* ��������ж�       */
        p_hw_spi->c1 &= (~0x20);
    }
}

/**
 * \brief ����SPI����ģʽ
 */
void amhw_fsl_spi_workmode_cfg (amhw_fsl_spi_t *p_hw_spi, uint8_t mode_flag)
{
    uint8_t tmp  = mode_flag & 0x10;

    p_hw_spi->c1 = (tmp | ( p_hw_spi->c1 & (~0x10)));   /* ���ӻ�ѡ��     */

    tmp          =  mode_flag & 0x01;
    p_hw_spi->c2 = (tmp | ( p_hw_spi->c2 & (~0x01)));   /* ��˫������ѡ�� */
}

/**
 * \brief ����SPI��������
 */
void amhw_fsl_spi_feature_cfg (amhw_fsl_spi_t *p_hw_spi, uint32_t flags)
{
    if (flags & AM_BIT(31)) { /* �������ݿ�ȣ�8bit/16bit�� */
        p_hw_spi->c2 = (((flags & 0x01) << 6) | (p_hw_spi->c2 & (~AM_BIT(6))));
    }
    if (flags & AM_BIT(30)) {   /* �Ƿ�ʹ�ܷ���DMA          */
        p_hw_spi->c2 = (((flags & 0x02) << 4) | (p_hw_spi->c2 & (~AM_BIT(5))));
    }
    if (flags & AM_BIT(29)) {   /* �Ƿ�ʹ�ܽ���DMA          */
        p_hw_spi->c2 = (((flags & 0x04) << 0) | (p_hw_spi->c2 & (~AM_BIT(2))));
    }
    if (flags & AM_BIT(28)) {   /* �Ƿ���waitģʽ�¹���     */
        p_hw_spi->c2 = (((flags & 0x08) >> 2) | (p_hw_spi->c2 & (~AM_BIT(1))));
    }
    if (flags & AM_BIT(27)) {   /* ��λ�ȷ��ͻ��ǵ�λ�ȷ��� */
        p_hw_spi->c1 = (((flags & 0x10) >> 4) | (p_hw_spi->c1 & (~AM_BIT(0))));
    }
}

/**
 * \brief ����SPIƬѡ����CS����
 */
void amhw_fsl_spi_cs_cfg (amhw_fsl_spi_t *p_hw_spi, uint8_t cs_flag)
{
    uint8_t tmp  = cs_flag & 0x10;

    p_hw_spi->c2 = (tmp | (p_hw_spi->c2 & (~0x10))); /*  �����Ƿ�ΪGPIO     */

    tmp = cs_flag & 0x02;
    p_hw_spi->c1 = (tmp | (p_hw_spi->c1 & (~0x02))); /*  ����Ϊ���뻹����� */
}

/* end of file */
