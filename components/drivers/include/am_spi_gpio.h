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
 * \brief GPIO�� ģ��SPI ����ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 18-04-10  vir, first implementation.
 * \endinternal
 */

#ifndef __AM_SPI_GPIO_H
#define __AM_SPI_GPIO_H

#include "am_common.h"
#include "am_spi.h"
#include "am_list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_am_if_spi_gpio
 * \copydoc am_spi_gpio.h
 * @{
 */
/**
 * \brief SPI_GPIO �豸��Ϣ�����ṹ��
 */
typedef struct am_spi_gpio_devinfo {
    int      sck_pin;        /**< \brief SCk���� */
    int      mosi_pin;       /**< \brief MOSI���� (����ģʽ��������Ϊ������) */
    int      miso_pin;       /**< \brief MISO���� */

    /**
     *  \brief �����ٶ�ָ��, ֵԽ�������ٶ�Խ��, ͨ������߼���������ȷ��ʵ�ʵ������ٶ�
     *         ��׼�ӿ�������SPI�ٶ� ��Ч
     */
    uint32_t speed_exp;
} am_spi_gpio_devinfo_t;

/**
 * \brief SPI_GPIO �豸�ṹ��
 */
typedef struct am_spi_gpio_dev {
    /** \brief ��׼SPI���� */
    am_spi_serv_t                           spi_serv;

    /** \brief SPI��������Ϣ���� */
    struct am_list_head                     msg_list;

    /** \brief ָ��SPI����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_spi_transfer_t                      *p_cur_trans;

    /** \brief ��ǰ���ڴ������Ϣ */
    am_spi_message_t                       *p_cur_msg;

    /** \brief ��ǰ�����SPI�豸 */
    am_spi_device_t                        *p_cur_spi_dev;

    /** \brief æ��ʶ */
    volatile am_bool_t                      busy;

    /** \brief SPI״̬ */
    volatile uint8_t                        state;

    /** \brief SCK ״̬ */
    volatile uint8_t                        sck_state;

    /** \brief SPI_GPIO �豸��Ϣ */
    const am_spi_gpio_devinfo_t            *p_devinfo;
} am_spi_gpio_dev_t;

/**
 * \brief SPI_GPIO ��ʼ��
 *
 * \param[in] p_dev     : ָ��SPI_GPIO �豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SPI_GPIO �豸��Ϣ�ṹ���ָ��
 *
 * \return SPI��׼����������
 */
am_spi_handle_t am_spi_gpio_init (am_spi_gpio_dev_t           *p_dev,
                                  const am_spi_gpio_devinfo_t *p_devinfo);

/**
 * \brief ���SPI_GPIO��ʼ��
 *
 * \param[in] handle : ����豸������SPI��׼����������
 *
 * \return ��
 */
void am_spi_gpio_deinit (am_spi_handle_t handle);


/** @} grp_am_if_spi_gpio */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SPI_GPIO_H */
