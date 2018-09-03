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
 * \brief GPIO�� ģ��I2C ����ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 18-04-09  vir, first implementation.
 * \endinternal
 */

#ifndef __AM_I2C_GPIO_H
#define __AM_I2C_GPIO_H

#include "am_common.h"
#include "am_i2c.h"
#include "am_list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_am_if_i2c_gpio
 * \copydoc am_i2c_gpio.h
 * @{
 */
/**
 * \brief I2C_GPIO �豸��Ϣ�����ṹ��
 */
typedef struct am_i2c_gpio_devinfo {
    int      scl_pin;        /**< \brief SCL���� */
    int      sda_pin;        /**< \brief SDA���� */

    /** \brief �����ٶ�ָ��, ֵԽ�������ٶ�Խ��, ͨ������߼���������ȷ��ʵ�ʵ������ٶ�  */
    uint32_t speed_exp;
} am_i2c_gpio_devinfo_t;

/**
 * \brief I2C_GPIO �豸�ṹ��
 */
typedef struct am_i2c_gpio_dev {
    /** \brief ��׼I2C���� */
    am_i2c_serv_t                           i2c_serv;

    /** \brief I2C��������Ϣ���� */
    struct am_list_head                     msg_list;

    /** \brief ָ��I2C����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_i2c_transfer_t                      *p_cur_trans;

    /** \brief ��ǰ���ڴ������Ϣ */
    am_i2c_message_t                       *p_cur_msg;

    /** \brief æ��ʶ */
    volatile am_bool_t                      busy;

    /** \brief I2C״̬ */
    volatile uint8_t                        state;

    /** \brief �������ݽ���/���ͼ��� */
    volatile uint32_t                       data_ptr;

    /** \brief I2C_GPIO �豸��Ϣ */
    const am_i2c_gpio_devinfo_t             *p_devinfo;
} am_i2c_gpio_dev_t;

/**
 * \brief I2C_GPIO ��ʼ��
 *
 * \param[in] p_dev     : ָ��I2C_GPIO �豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��I2C_GPIO �豸��Ϣ�ṹ���ָ��
 *
 * \return I2C��׼����������
 */
am_i2c_handle_t am_i2c_gpio_init (am_i2c_gpio_dev_t           *p_dev,
                                  const am_i2c_gpio_devinfo_t *p_devinfo);

/**
 * \brief ���I2C_GPIO��ʼ��
 *
 * \param[in] handle : ����豸������I2C��׼����������
 *
 * \return ��
 */
void am_i2c_gpio_deinit (am_i2c_handle_t handle);


/** @} grp_am_if_i2c_gpio */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2C_GPIO_H */
