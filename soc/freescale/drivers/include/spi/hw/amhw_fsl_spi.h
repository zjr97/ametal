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
 * \brief SPI Ӳ�������ӿ�
 * 
 * 1. ֧�������ʹӻ����䣻
 * 2. ֧�ֵ�������ģʽ��
 * 3. ֧��64-bit FIFOģʽ����(��SPI1)
 * 4. ֧��DMA����(���ͺͽ���)��
 * 5. �����ʿ����ã�
 * 6. ʱ����λ�ͼ��Կ����ã�
 * 7. ֧��8bits����16bits����,������LSB����MSB���䣻
 * 8. ��������ƥ��������ݣ�ƥ��ɹ�ʱ�����жϣ�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-26  sdy, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_SPI_H
#define __AMHW_FSL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
#include "am_bitops.h"
/**
 * \addtogroup amhw_fsl_if_spi
 * \copydoc amhw_fsl_spi.h
 * @{
 */
 
/**
 * \brief SPI�Ĵ�����ṹ��
 */
typedef struct amhw_fsl_spi {
    __IO uint8_t  s;             /**< \brief SPI ״̬�Ĵ���       */
    __IO uint8_t  br;            /**< \brief SPI ���������üĴ��� */
    __IO uint8_t  c2;            /**< \brief SPI ���ƼĴ���2      */
    __IO uint8_t  c1;            /**< \brief SPI ���ƼĴ���1      */
    __IO uint8_t  ml;            /**< \brief SPI ���ֽ�ƥ��Ĵ��� */
    __IO uint8_t  mh;            /**< \brief SPI ���ֽ�ƥ��Ĵ��� */
    __IO uint8_t  dl;            /**< \brief SPI ���ֽ����ݼĴ��� */
    __IO uint8_t  dh;            /**< \brief SPI ���ֽ����ݼĴ��� */
    __I  uint8_t  reserved[2];   /**< \brief SPI �����Ĵ���       */
    __IO uint8_t  ci;            /**< \brief SPI �ж�����Ĵ���   */
    __IO uint8_t  c3;            /**< \brief SPI ���ƼĴ���3      */
} amhw_fsl_spi_t;


/**
 * \name SPI ״̬��־
 * @{
 */

#define AMHW_FSL_SPI_STAT_R_FULL        AM_BIT(7)  /**< \brief �������       */
#define AMHW_FSL_SPI_STAT_MATCH         AM_BIT(6)  /**< \brief ���ݷ���ƥ��   */
#define AMHW_FSL_SPI_STAT_T_EMPTY       AM_BIT(5)  /**< \brief �������       */
#define AMHW_FSL_SPI_STAT_MODF          AM_BIT(4)  /**< \brief ������         */
#define AMHW_FSL_SPI_STAT_R_NEAR_FULL   AM_BIT(3)  /**< \brief ����FIFO�ӽ��� */
#define AMHW_FSL_SPI_STAT_T_NEAR_EMPTY  AM_BIT(2)  /**< \brief ����FIFO�ӽ��� */
#define AMHW_FSL_SPI_STAT_T_FIFO_FULL   AM_BIT(1)  /**< \brief ����FIFO��     */
#define AMHW_FSL_SPI_STAT_R_FIFO_EMPTY  AM_BIT(0)  /**< \brief ����FIFO��     */

/** @} */

/**
 * \name SPI FIFO�����־
 * @{
 */

#define AMHW_FSL_SPI_ERROR_T_FIFO   AM_BIT(7)     /**< \brief ����FIFO����    */
#define AMHW_FSL_SPI_ERROR_R_FIFO   AM_BIT(6)     /**< \brief ����FIFO����    */
#define AMHW_FSL_SPI_OV_T_FIFO      AM_BIT(5)     /**< \brief ����FIFO���    */
#define AMHW_FSL_SPI_OV_R_FIFO      AM_BIT(4)     /**< \brief ����FIFO���    */

/** @} */

/**
 * \name SPI ��ͨ�ж�
 * @{
 */

#define AMHW_FSL_SPI_IRQ_MATCH       AM_BIT(7)  /**< \brief ����ƥ���ж�      */
#define AMHW_FSL_SPI_IRQ_R_MODDEF    AM_BIT(6)  /**< \brief ���ջ�������ж�  */
#define AMHW_FSL_SPI_IRQ_T           AM_BIT(5)  /**< \brief ��������ж�      */

/**
 * \name SPI FIFO�ж�
 * @{
 */

#define AMHW_FSL_SPI_FIFO_IRQ_T_NERAEMPTY AM_BIT(2) /**< \brief ����FIFO�����ж� */
#define AMHW_FSL_SPI_FIFO_IRQ_R_NERAFULL  AM_BIT(1) /**< \brief ����FIFO�����ж� */

/** @} */

/**
 * \name SPI ����ģʽ
 * @{
 */

#define AMHW_FSL_SPI_WMODE_MASTER    (1 << 4)  /**< \brief ����ģʽ         */
#define AMHW_FSL_SPI_WMODE_SLAVE     (0 << 4)  /**< \brief �ӻ�ģʽ         */
#define AMHW_FSL_SPI_WMODE_M_SINGLE  ( 0x11 )  /**< \brief ������������ģʽ */
#define AMHW_FSL_SPI_WMODE_S_SINGLE  ( 0x01 )  /**< \brief �������ߴӻ�ģʽ */

/** @} */

/**
 * \name SPI ����
 * @{
 */

/** \brief �������ݿ��Ϊ8λ */
#define AMHW_FSL_SPI_CFG_8BIT_WIDTH     (AM_BIT(31) | AM_SBF(0,0))

/** \brief �������ݿ��Ϊ16λ */
#define AMHW_FSL_SPI_CFG_16BIT_WIDTH    (AM_BIT(31) | AM_SBF(1,0))

/** \brief ����DMA���� */
#define AMHW_FSL_SPI_CFG_TDMA_DIS       (AM_BIT(30) | AM_SBF(0,1))

/** \brief ʹ��DMA���� */
#define AMHW_FSL_SPI_CFG_TDMA_EN        (AM_BIT(30) | AM_SBF(1,1))

/** \brief ����DMA���� */
#define AMHW_FSL_SPI_CFG_RDMA_DIS       (AM_BIT(29) | AM_SBF(0,2))

/** \brief ʹ��DMA���� */
#define AMHW_FSL_SPI_CFG_RDMA_EN        (AM_BIT(29) | AM_SBF(1,2))

/** \brief ֹͣģʽSPI�������� */
#define AMHW_FSL_SPI_CFG_WIAT_EN        (AM_BIT(28) | AM_SBF(0,3))

/** \brief ֹͣģʽSPI������ */
#define AMHW_FSL_SPI_CFG_WIAT_DIS       (AM_BIT(28) | AM_SBF(1,3))

/** \brief ��λ���ȷ��� */
#define AMHW_FSL_SPI_CFG_MSB            (AM_BIT(27) | AM_SBF(0,4))

/** \brief ��λ���ȷ��� */
#define AMHW_FSL_SPI_CFG_LSB            (AM_BIT(27) | AM_SBF(1,4))

/** @} */

/**
 * \name SPI Ƭѡ���Ź���
 * @{
 */

/** \brief SPIʹ��CS������ΪƬѡ��� */
#define AMHW_FSL_SPI_CS_SPI_OUT   ((1 << 4) | (1 << 1))

/** \brief SPIʹ��CS������Ϊ���룬�������� */
#define AMHW_FSL_SPI_CS_SPI_MODF  ((1 << 4) | (0 << 1))

/** \brief SPI��ʹ��CS���ţ�CS����ΪGPIOģʽ */
#define AMHW_FSL_SPI_CS_GPIO      ((0 << 4) | (0 << 1))

/** @} */

/**
 * \name SPI ����ģʽ
 * @{
 */ 

/** \brief SCKĬ��Ϊ�ͣ������½��ظı䣬�����ر��� */
#define AMHW_FSL_SPI_MODE_0     ((0 << 3) |(0 << 2))
 
/** \brief SCKĬ��Ϊ�ͣ����������ظı䣬�½��ر��� */
#define AMHW_FSL_SPI_MODE_1     ((0 << 3) |(1 << 2))

/** \brief SCKĬ��Ϊ�ߣ����������ظı䣬�½��ر��� */
#define AMHW_FSL_SPI_MODE_2     ((1 << 3) |(0 << 2))
     
/** \brief SCKĬ��Ϊ�ߣ������½��ظı䣬��������   */
#define AMHW_FSL_SPI_MODE_3     ((1 << 3) |(1 << 2))

/** @} */

/**
 * \name SPI FIFO�ж����ѡ��
 * @{
 */

/** \brief �������FIFO�ӽ����ж� */
#define AMHW_FSL_SPI_FIFO_IRQ_CLR_TNE   (1 << 3)

/** \brief �������FIFO�ӽ����ж� */
#define AMHW_FSL_SPI_FIFO_IRQ_CLR_RNF   (1 << 2)

/** \brief �����������ж�(����FIFO��) */
#define AMHW_FSL_SPI_FIFO_IRQ_CLR_TE    (1 << 1)

/** \brief ����������(����FIFO��) */
#define AMHW_FSL_SPI_FIFO_IRQ_CLR_RF    (1 << 0)

/** @} */

/**
 * \name FIFO�ӽ��̶�ѡ��
 * @{
 */

/** \brief ���ͻ�����С��16bit,���ջ���������48bit */
#define AMHW_FSL_SPI_FIFO_T_16BITS_R_48BITS ( (0 << 5) | (0 << 4))

/** \brief ���ͻ�����С��16bit,���ջ���������32bit */
#define AMHW_FSL_SPI_FIFO_T_16BITS_R_32BITS ( (0 << 5) | (1 << 4) )

/** \brief ���ͻ�����С��32bit,���ջ���������48bit */
#define AMHW_FSL_SPI_FIFO_T_32BITS_R_48BITS ( (1 << 5) | (0 << 4) )

/** \brief ���ͻ�����С��32bit,���ջ���������32bit */
#define AMHW_FSL_SPI_FIFO_T_32BITS_R_32BITS ( (1 << 5) | (1 << 4) )

/** @} */

/**
 * \brief ʹ��SPIģ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return ��
 */
am_static_inline 
void amhw_fsl_spi_enable (amhw_fsl_spi_t *p_hw_spi)
{
    p_hw_spi->c1 |= (1 << 6);
}

/**
 * \brief ����SPIģ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ��
 */
am_static_inline
void amhw_fsl_spi_disable (amhw_fsl_spi_t *p_hw_spi)
{
    p_hw_spi->c1 &= (~(1 << 6));
}

/**
 * \brief ��ȡ״̬��־
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ״̬��־(#AMHW_FSL_SPI_STAT_R_FULL)
 */
am_static_inline
uint8_t amhw_fsl_spi_stat_get (amhw_fsl_spi_t *p_hw_spi)
{
    return p_hw_spi->s;
}

/**
 * \brief ���÷�Ƶϵ��
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] pdiv     : Ԥ��Ƶϵ��(0-8)
 * \param[in] div      : ����ϵ��(0-9)
 *
 * \return  ��
 *
 * \note �ܷ�Ƶϵ��Div=(pdiv+1)*2^(div+1),SPI�����ʣ�Baud=����ʱ��/�ܷ�Ƶϵ��
 */
am_static_inline
void amhw_fsl_spi_div_cfg (amhw_fsl_spi_t *p_hw_spi,
                            uint8_t          pdiv,
                            uint8_t          div)
{
    p_hw_spi->br = ((pdiv & 0x70) | (div & 0x0F));
}

/**
 * \brief ʹ����ͨ�ж�
 *
 * \param[in] p_hw_spi  : ָ��SPI�Ĵ������ָ��
 * \param[in] irq_flags : �жϱ�ʶ��AMHW_FSL_SPI_IRQ_*��ֵ����
 *                        (#AMHW_FSL_SPI_IRQ_MATCH)
 * \return  ��
 */
void amhw_fsl_spi_int_enable (amhw_fsl_spi_t *p_hw_spi, uint8_t irq_flags);

/**
 * \brief ������ͨ�ж�
 *
 * \param[in] p_hw_spi  : ָ��SPI�Ĵ������ָ��
 * \param[in] irq_flags : �жϱ�ʶ��AMHW_FSL_SPI_IRQ_*��ֵ����
 *                       (#AMHW_FSL_SPI_IRQ_MATCH)
 * \return  ��
 */
void amhw_fsl_spi_int_disable (amhw_fsl_spi_t *p_hw_spi, uint8_t irq_flags);

/**
 * \brief ����SPI����ģʽ(Ĭ��Ϊ�ӻ�ģʽ)
 *
 * \param[in] p_hw_spi  : ָ��SPI�Ĵ������ָ��
 * \param[in] mode_flag : ����ģʽ��AMHW_FSL_SPI_WMODE_*��ֵ
 *                        (#AMHW_FSL_SPI_WMODE_MASTER)
 * \return  ��
 */
void amhw_fsl_spi_workmode_cfg (amhw_fsl_spi_t *p_hw_spi, uint8_t mode_flag);

/**
 * \brief ����SPI����
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] flags    : ���Ա�ʶ��AMHW_FSL_SPI_CFG_*��ֵ����
 *                      (#AMHW_FSL_SPI_CFG_8BIT_WIDTH)
 *
 * \return  ��
 *
 * \note ��ǰ���õ����Ա�������ֻ����flags��������������
 */
void amhw_fsl_spi_feature_cfg (amhw_fsl_spi_t *p_hw_spi, uint32_t flags);

/**
 * \brief ����CSƬѡ����(Ĭ��ΪGPIO����)
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] cs_flag  : ���ܱ�ʶ��AMHW_FSL_SPI_CS_*��ֵ(#AMHW_FSL_SPI_CS_GPIO)
 *
 * \return  ��
 *
 * \note ֻ��������������ģʽ(�ӻ�ģʽ��CSֻ��ΪƬѡ����)
 */
void amhw_fsl_spi_cs_cfg (amhw_fsl_spi_t *p_hw_spi, uint8_t cs_flag);

/**
 * \brief ģʽ����(ʱ����λ�ͼ���)
 *
 * \param[in] p_hw_spi  : ָ��SPI�Ĵ������ָ��
 * \param[in] mode_flag : ���ܱ�ʶ��AMHW_FSL_SPI_MODE*��ֵ(#AMHW_FSL_SPI_MODE_0)
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_spi_mode_cfg (amhw_fsl_spi_t *p_hw_spi, uint8_t mode_flag)
{
    uint8_t tmp  = mode_flag & (0x0C);

    p_hw_spi->c1 = (tmp | (p_hw_spi->c1 & (~0x0C)));
}

/**
 * \brief ��ȡ���յ�������(��16bits)
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ��ȡ��������
 */
am_static_inline
uint16_t amhw_fsl_spi_data16_read (amhw_fsl_spi_t *p_hw_spi)
{
    uint16_t tmp = p_hw_spi->dh;

    tmp <<= 8;
    tmp |= p_hw_spi->dl;

    return tmp;
}

/**
 * \brief ��ȡ���յ�������(��8bits)
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ��ȡ��������
 */
am_static_inline
uint8_t amhw_fsl_spi_data8_read (amhw_fsl_spi_t *p_hw_spi)
{
    return p_hw_spi->dl;
}

/**
 * \brief ��������(16bits)
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] data     �����͵�����
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_spi_data16_wirte (amhw_fsl_spi_t *p_hw_spi, uint16_t data)
{
    p_hw_spi->dh = (data >> 8);
    p_hw_spi->dl = data;
}

/**
 * \brief ��������(8bits)
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] data     �����͵�����
 *
 * \return  ��ȡ��������
 */
am_static_inline
void amhw_fsl_spi_data8_wirte (amhw_fsl_spi_t *p_hw_spi, uint8_t data)
{
    p_hw_spi->dl = data;
}

/**
 * \brief ��ȡ��ǰ���õ�ƥ������(16bit)
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ��ȡ��������
 */
am_static_inline
uint16_t amhw_fsl_spi_matchdata16_read (amhw_fsl_spi_t *p_hw_spi)
{
    uint16_t tmp = p_hw_spi->mh;

    tmp <<= 8;
    tmp |= p_hw_spi->ml;

    return tmp;
}

/**
 * \brief ����ƥ������(16bit)
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] data     ����Ҫƥ�������
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_spi_matchdata16_wirte (amhw_fsl_spi_t *p_hw_spi, uint16_t data)
{
    p_hw_spi->mh = (data >> 8);
    p_hw_spi->ml = data;
}

/**
 * \brief MOMI����SISO�����ߵķ�������
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] dir      ������
 *      \arg 0   :  ����
 *      \arg ��0 �� ���
 *
 * \return ��
 *
 * \note ����ģʽʹ��MIMO,�ӻ�ģʽʹ��SISO����������ģʽ��Ч
 */
am_static_inline
void amhw_fsl_spi_dataline_dir_cfg (amhw_fsl_spi_t *p_hw_spi, uint8_t dir)
{
    if (dir) {
        p_hw_spi->c2 &= (~0x08);
    } else {
        p_hw_spi->c2 |= 0x08;
    }
}

/******************************************************************************
 * ����ΪFIFO��������,ֻ��SPI1֧����������                                    *
 * ***************************************************************************/

/**
 * \brief FIFOģʽʹ������
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] use_fifo : �Ƿ�ʹ��FIFO
 *      \arg AM_TRUE  : ����FIFOģʽ
 *      \arg AM_FALSE : ��ʹ��FIFOģʽ
 *
 * \return  ��
 *
 * \note ֻ��SPI1����ʹ�ô˺���
 */
am_static_inline
void amhw_fsl_spi_fifo_cfg (amhw_fsl_spi_t *p_hw_spi, am_bool_t use_fifo)
{
    /* ʹ��FIFO */
    if (use_fifo) {
        p_hw_spi->c3 |= 0x01;
    } else {
        p_hw_spi->c3 &= (~0x01);
    }
}

/**
 * \brief ��ȡFIFO�����־
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  �����־
 * \note ��ȡ��־��Ӳ��������˺���ֻ�ܱ�SPI1����
 */
am_static_inline
uint8_t amhw_fsl_spi_error_get (amhw_fsl_spi_t *p_hw_spi)
{
    return (p_hw_spi->ci & 0xF0);
}

/**
 * \brief ����FIFO�ӽ��̶�(Ĭ��T-16bit,R-48bit)
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] flags    : �ӽ��̶ȱ�ʶ(#AMHW_FSL_SPI_FIFO_T_16BITS_R_48BITS)
 *
 * \return  ��
 *
 * \note ֻ��SPI1���Ե��ô˺���
 */
am_static_inline
void amhw_fsl_spi_fifo_near_cfg (amhw_fsl_spi_t *p_hw_spi, uint8_t flags)
{
    uint8_t tmp = flags & 0x30;

    p_hw_spi->c3 = (tmp | (p_hw_spi->c3 & (~0x30)));
}

/**
 * \brief ����FIFO�жϱ�־���ģʽ(Ĭ���Զ������־)
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] is_auto  : �Ƿ����FIFO״̬�Զ����
 *      \arg AM_TRUE  : ����FIFO״̬�Զ����
 *      \arg AM_FALSE ��ʹ��amhw_fsl_spi_fifo_flags_clr���״̬��־
 *
 * \return  ��
 *
 * \note ֻ��SPI1���Ե��ô˺���
 */
am_static_inline
void amhw_fsl_spi_fifo_irqs_clrmode_cfg (amhw_fsl_spi_t *p_hw_spi,
                                          am_bool_t           is_auto)
{
    if (is_auto) {
        p_hw_spi->c3 &= (~0x08);
    } else {
        p_hw_spi->c3 |= 0x08;
    }
}

/**
 * \brief ���FIFO�жϱ�־
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] flags    : FIFO��־��AMHW_FSL_SPI_FIFO_IRQ_CLR_*��ֵ
 *                      (#AMHW_FSL_SPI_FIFO_IRQ_CLR_TNE)
 *
 * \return  ��
 *
 * \note ֻ��SPI1���Ե��ô˺���
 */
am_static_inline
void amhw_fsl_spi_fifo_irqs_clr (amhw_fsl_spi_t *p_hw_spi, uint8_t flags)
{
    p_hw_spi->ci |= (flags & 0x0F);
}

/**
 * \brief ʹ��FIFO�ж�
 *
 * \param[in] p_hw_spi       : ָ��SPI�Ĵ������ָ��
 * \param[in] fifo_irq_flags : �жϱ�ʶ��AMHW_FSL_SPI_FIFO_IRQ_*��ֵ����
 *                             (#AMHW_FSL_SPI_FIFO_IRQ_T_NERAEMPTY)
 *
 * \return  ��
 *
 * \note �˺���ֻ�ܱ�SPI1����
 */
am_static_inline
void amhw_fsl_spi_fifo_int_enable (amhw_fsl_spi_t *p_hw_spi,
                                    uint8_t          fifo_irq_flags)
{
    if (fifo_irq_flags & AMHW_FSL_SPI_FIFO_IRQ_T_NERAEMPTY) {
        p_hw_spi->c3 |= AMHW_FSL_SPI_FIFO_IRQ_T_NERAEMPTY;
    }
    if (fifo_irq_flags & AMHW_FSL_SPI_FIFO_IRQ_R_NERAFULL) {
        p_hw_spi->c3 |= AMHW_FSL_SPI_FIFO_IRQ_R_NERAFULL;
    }
}

/**
 * \brief ����FIFO�ж�
 *
 * \param[in] p_hw_spi       : ָ��SPI�Ĵ������ָ��
 * \param[in] fifo_irq_flags : �жϱ�ʶ��AMHW_FSL_SPI_FIFO_IRQ_*��ֵ����
 *                           (#AMHW_FSL_SPI_FIFO_IRQ_T_NERAEMPTY)
 * \return  ��
 *
 * \note �˺���ֻ�ܱ�SPI1����
 */
am_static_inline
void amhw_fsl_spi_fifo_int_disable (amhw_fsl_spi_t *p_hw_spi,
                                     uint8_t          fifo_irq_flags)
{
    if (fifo_irq_flags & AMHW_FSL_SPI_FIFO_IRQ_T_NERAEMPTY) {
        p_hw_spi->c3 &= ~AMHW_FSL_SPI_FIFO_IRQ_T_NERAEMPTY;
    }
    if (fifo_irq_flags & AMHW_FSL_SPI_FIFO_IRQ_R_NERAFULL) {
        p_hw_spi->c3 &= ~AMHW_FSL_SPI_FIFO_IRQ_R_NERAFULL;
    }
}

/** 
 * @} amhw_fsl_if_spi
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_SPI_H */

/*end of file */
