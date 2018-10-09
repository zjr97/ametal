/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SPI drivers for standard interface 
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-15  jon, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC_SPI_INT_H
#define __AM_LPC_SPI_INT_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"    
#include "am_spi.h"
#include "hw/amhw_lpc_spi.h"
#include "am_int.h"

/**
 * \addtogroup am_lpc_if_spi_int
 * \copydoc am_lpc_spi_int.h
 * @{
 */
 
/**
 * \brief SPI �豸��Ϣ�ṹ��
 */
typedef struct am_lpc_spi_int_devinfo {
    uint32_t           spi_regbase;       /**< \brief SPI�Ĵ�����Ļ���ַ */
    uint16_t           inum;              /**< \brief SPI �жϱ��    */
    uint32_t           clk_id;            /**< \brief SPI clk id */

    /** \brief SPIƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief SPIƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_lpc_spi_int_devinfo_t;

/**
 * \brief SPI �豸
 */
typedef struct am_lpc_spi_int_dev {

    am_spi_serv_t              spi_serve;       /**< \brief SPI��׼������.   */
    const am_lpc_spi_int_devinfo_t *p_devinfo;  /**< \brief SPI�豸��Ϣ��ָ��. */

    struct am_list_head        msg_list;        /**< \brief SPI��������Ϣ���� . */

    /** \brief ָ��SPI��Ϣ�ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ����Ϣ */
    am_spi_message_t          *p_cur_msg;

    /** \brief ָ��SPI����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_spi_transfer_t         *p_cur_trans;

    am_spi_device_t           *p_cur_spi_dev;   /**< \brief ��ǰ�����SPI�豸. */
    am_spi_device_t           *p_tgl_dev;       /**< \brief ��ǰ������SPI�豸. */

    uint32_t                   nbytes_to_recv;  /**< \brief �����յ��ֽ���.    */
    uint32_t                   data_ptr;        /**< \brief ���ݴ������.      */

    am_bool_t                  busy;            /**< \brief SPIæ��ʶ.        */
    uint32_t                   state;           /**< \brief SPI������״̬��״̬. */

} am_lpc_spi_int_dev_t;

/**
 * \brief SPI ��ʼ��
 *
 * \param[in] p_dev     : ָ��SPI�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SPI�豸��Ϣ�ṹ���ָ��
 *
 * \return SPI��׼����������
 */
am_spi_handle_t am_lpc_spi_int_init (am_lpc_spi_int_dev_t           *p_dev,
                                          const am_lpc_spi_int_devinfo_t *p_devinfo);

/**
 * \brief ���SPI��ʼ��
 * \param[in] handle : SPI��׼����������
 * \return ��
 */
void am_lpc_spi_int_deinit (am_spi_handle_t handle);




/** 
 * @} am_lpc_if_spi_int
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC_SPI_INT_H */

/*end of file */
