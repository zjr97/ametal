/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SPI������DMA����ģʽ
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-07  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC82X_SPI_DMA_H
#define __AM_LPC82X_SPI_DMA_H

#include "am_types.h"
#include "am_spi.h"
#include "am_int.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc82x_dma.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_lpc82x_if_spi_dma
 * \copydoc am_lpc82x_spi_dma.h
 * @{
 */

/**
 * \brief SPI �豸��Ϣ�ṹ��
 */
typedef struct am_lpc82x_spi_dma_devinfo {
    uint32_t          spi_regbase;       /**< \brief SPI�Ĵ�����Ļ���ַ */
    uint32_t          clk_id;            /**< \brief SPI clk id */
    uint32_t          dma_chan_tx;       /**< \brief DMA����ͨ���� */
    uint32_t          dma_chan_rx;       /**< \brief DMA����ͨ���� */
    uint32_t          dma_chan_prio_tx;  /**< \brief DMA����ͨ�����ȼ� */
    uint32_t          dma_chan_prio_rx;  /**< \brief DMA����ͨ�����ȼ� */

    /** \brief SPIƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief SPIƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_lpc82x_spi_dma_devinfo_t;

/**
 * \brief SPI �豸������16�ֽڶ���
 */
typedef struct am_lpc82x_spi_dma_dev {
    am_spi_serv_t                      spi_serve;   /**< \brief SPI��׼������ */
    const am_lpc82x_spi_dma_devinfo_t *p_devinfo;   /**< \brief SPI�豸��Ϣ��ָ�� */

    struct am_list_head        msg_list;        /**< \brief SPI��������Ϣ���� */

    /** \brief ָ��SPI��Ϣ�ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ����Ϣ */
    am_spi_message_t          *p_cur_msg;

    /** \brief ָ��SPI����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_spi_transfer_t         *p_cur_trans;

    am_spi_device_t           *p_cur_spi_dev;   /**< \brief ��ǰ�����SPI�豸 */
    am_spi_device_t           *p_tgl_dev;       /**< \brief ��ǰ������SPI�豸 */

    am_bool_t                  busy;            /**< \brief SPIæ��ʶ */
    am_bool_t                  eot;             /**< \brief �����ֽ� */
    uint32_t                   state;           /**< \brief SPI������״̬��״̬ */

    uint16_t                   rx_trash;        /**< \brief �������ݵ���ʱ���ձ��� */
    uint32_t                   p_tx_buf_eot;    /**< \brief һ֡�е����һ������ */

    /** \brief SPIѡ��DMA����ģʽ��,ʵ�ʴ�������ݸ��� */
    uint32_t                   dma_trans_num;

    /** \brief SPIѡ��DMA������������ڵ�ַƫ�� */
    uint32_t                   dma_trans_count;

    /** \brief SPIѡ��DMA����ģʽ��־(���ڱ�־���δ����Ƿ����1024������) */
    uint32_t                   dma_trans_flg;

    __attribute__((aligned(16)))
    am_lpc82x_dma_xfer_desc_t   g_desc[3];  /**< \brief DMAͨ�������� */

    am_lpc82x_dma_controller_t *p_ctr_tx;   /**< \brief DMA����ͨ�������� */
    am_lpc82x_dma_controller_t *p_ctr_rx;   /**< \brief DMA����ͨ�������� */

} am_lpc82x_spi_dma_dev_t;

/**
 * \brief SPI ��ʼ��
 *
 * ʹ��ǰ�����ȷ��DMAʵ���Ѿ���ʼ��
 *
 * \param[in] p_dev     : ָ��SPI�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SPI�豸��Ϣ�ṹ���ָ��
 *
 * \return SPI��׼����������
 */
am_spi_handle_t am_lpc82x_spi_dma_init (am_lpc82x_spi_dma_dev_t           *p_dev,
                                        const am_lpc82x_spi_dma_devinfo_t *p_devinfo);

/**
 * \brief ���SPI��ʼ��
 * \param[in] handle : SPI��׼����������
 * \return ��
 */
void am_lpc82x_spi_dma_deinit (am_spi_handle_t handle);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC82X_SPI_DMA_H */

/*end of file */
