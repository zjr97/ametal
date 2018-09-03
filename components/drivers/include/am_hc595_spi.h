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
 * \brief HC595��׼�豸ʵ�֣�SPI������
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-23  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_HC595_SPI_H
#define __AM_HC595_SPI_H

#include "am_common.h"
#include "am_hc595.h"
#include "am_spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_am_if_hc595_spi
 * \copydoc am_hc595_spi.h
 * @{
 */

/**
 * \brief SPI����HC595���豸��Ϣ
 *
 * δʹ�õ����ţ���OE���̶�Ϊ�͵�ƽʱ�����Խ� oe���ŵ�ֵ����Ϊ -1
 */
typedef struct am_hc595_spi_info {

    int         pin_lock;     /**< \brief ������������                        */
    int         pin_oe;       /**< \brief ���ʹ�����ţ�δʹ��ʱ������Ϊ -1�� */
    uint32_t    clk_speed;    /**< \brief SPI�����ʱ��Ƶ��                   */

    /**
     * \brief HC595���ݷ����Ƿ����λ�ȷ��ͣ�Ĭ�ϸ�λ�ȷ��ͣ�
     *
     *  ��ֵΪ AM_TRUE �� ���λ�ȷ��ͣ� ���λ���ͳ��� Q7λ��
     *  ��ֵΪ AM_FALSE �� ���λ�ȷ��ͣ� ���λ���ͳ��� Q7λ��
     *
     *  ���磺
     *  - ��Q0 ������� 'a'�����ӣ��� ���� LSB Ӧ���ȷ���
     *  - ��Q7 �� 'a'�����ӣ��� ���� MSB Ӧ���ȷ���
     */
    am_bool_t  lsb_first;

} am_hc595_spi_info_t;

/**
 * \brief SPI����HC595���豸
 */
typedef struct am_hc595_spi_dev {
    am_hc595_dev_t             isa;        /**< \brief ��׼��HC595���� */
    am_spi_device_t            spi_dev;    /**< \brief SPI �豸        */
    const am_hc595_spi_info_t *p_info;
} am_hc595_spi_dev_t;

/**
 * \brief SPI����HC595���豸��ʼ��
 *
 * \param[in] p_dev     : GPIO������ HC595�豸
 * \param[in] handle    : SPI��׼������
 * \param[in] pin_lock  : �������Ž���ΪƬѡ����
 * \param[in] clk_speed : ʱ����Ƶ�ʣ��� 3000000Hz
 * \param[in] lsb_first : �Ƿ��λ�ȷ���
 *
 * \return hc595����������ΪNULL��������ʼ��ʧ��
 */
am_hc595_handle_t am_hc595_spi_init (am_hc595_spi_dev_t        *p_dev,
                                     const am_hc595_spi_info_t *p_info,
                                     am_spi_handle_t            handle);

/**
 * \brief SPI����HC595���豸���ʼ��
 * \param[in] p_dev  : GPIO������ HC595�豸
 * \return AM_OK�����ʼ���ɹ�������ֵ�����ʼ��ʧ��
 */
int am_hc595_spi_deinit (am_hc595_spi_dev_t *p_dev);

/** @} grp_am_if_hc595_spi */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC595_SPI_H */
