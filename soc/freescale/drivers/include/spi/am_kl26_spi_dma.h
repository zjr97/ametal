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
 * \brief SPI����������SPI��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-23  sky, modified.
 * - 1.00 15-07-07  aii, first implementation.
 * \endinternal
 */

#ifndef __AM_KL26_SPI_DMA_H
#define __AM_KL26_SPI_DMA_H

#include "am_types.h"
#include "am_spi.h"
#include "am_int.h"
#include "am_kl26_dma.h"
#include "hw/amhw_kl26_dma.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_kl26_if_spi_dma
 * \copydoc am_kl26_spi_dma.h
 * @{
 */

/** \brief ֹͣģʽSPI�������� */
#define AM_KL26_SPI_DMA_CFG_WIAT_EN        (AM_BIT(28) | AM_SBF(0,3))

/** \brief ֹͣģʽSPI������ */
#define AM_KL26_SPI_DMA_CFG_WIAT_DIS       (AM_BIT(28) | AM_SBF(1,3))

/**
 * \brief SPI �豸��Ϣ�ṹ��
 */
typedef struct am_kl26_spi_dma_devinfo {
    uint32_t          spi_regbase;       /**< \brief SPI�Ĵ�����Ļ���ַ */
    uint32_t          flags;             /**< \brief SPI ���ñ�ʶ  */

    uint32_t          dma_chan_tx;       /**< \brief DMA����ͨ���� */
    uint32_t          dma_chan_rx;       /**< \brief DMA����ͨ���� */
    uint32_t          dma_src_tx;  /**< \brief DMA����Դ */
    uint32_t          dma_src_rx;  /**< \brief DMA����Դ */

    /** \brief SPIƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief SPIƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_kl26_spi_dma_devinfo_t;

/**
 * \brief SPI �豸
 */
typedef struct am_kl26_spi_dma_dev {

    am_spi_serv_t                  spi_serve;   /**< \brief SPI��׼������ */
    const am_kl26_spi_dma_devinfo_t   *p_devinfo;   /**< \brief SPI�豸��Ϣ��ָ�� */

    struct am_list_head        msg_list;        /**< \brief SPI��������Ϣ���� */

    /** \brief ָ��SPI��Ϣ�ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ����Ϣ */
    am_spi_message_t          *p_cur_msg;

    /** \brief ָ��SPI����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_spi_transfer_t         *p_cur_trans;

    am_spi_device_t           *p_cur_spi_dev;   /**< \brief ��ǰ�����SPI�豸 */
    am_spi_device_t           *p_tgl_dev;       /**< \brief ��ǰ������SPI�豸 */

    uint32_t                   nbytes_to_recv;  /**< \brief �����յ��ֽ��� */
    uint32_t                   data_ptr;        /**< \brief ���ݴ������ */

    am_bool_t                     busy;            /**< \brief SPIæ��ʶ */
    uint32_t                   state;           /**< \brief SPI������״̬��״̬ */

    uint16_t                   tx_rx_trash;

    __attribute__((aligned(16)))
    amhw_kl26_dma_xfer_desc_t       g_desc[2];  /**< \brief DMAͨ�������� */

} am_kl26_spi_dma_dev_t;

/**
 * \brief SPI ��ʼ��
 *
 * \param[in] p_dev     : ָ��SPI�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SPI�豸��Ϣ�ṹ���ָ��
 *
 * \return SPI��׼����������
 */
am_spi_handle_t am_kl26_spi_dma_init (am_kl26_spi_dma_dev_t           *p_dev,
                                      const am_kl26_spi_dma_devinfo_t *p_devinfo);

/**
 * \brief ���SPI��ʼ��
 * \param[in] handle : SPI��׼����������
 * \return ��
 */
void am_kl26_spi_dma_deinit (am_spi_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_KL26_SPI_DMA_H */

/*end of file */
