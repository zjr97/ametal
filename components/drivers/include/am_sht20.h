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
 * \brief  SHT20 ��ʪ�ȴ�����Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 2017-7-13  sky, first implementation.
 * \endinternal
 */

#ifndef __AM_SHT20_H
#define __AM_SHT20_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_i2c.h"

/**
 * \addtogroup am_if_sht20
 * \copydoc am_sht20.h
 * @{
 */

/**
 * \brief SHT20 �豸�ṹ��
 */
typedef struct am_sht20_dev {
    am_i2c_device_t i2c_dev;       /**< \brief SHT20 I2C�豸 */
} am_sht20_dev_t;

/** \brief PCF85063����������� */
typedef am_sht20_dev_t *am_sht20_handle_t;

/**
 * \brief SHT20��������ȡ�¶�
 *
 * \param[in]  handle        : SHT20����������
 * \param[out] p_temperature : ָ���¶ȵ�ָ��
 *
 * \retval AM_OK : ��ȡ�ɹ�
 * \retval OTHER : ��ȡʧ��
 */
int am_sht20_temperature_read (am_sht20_handle_t handle, float *p_temperature);

/**
 * \brief SHT20��������ȡʪ��
 *
 * \param[in]  handle     : SHT20����������
 * \param[out] p_humidity : ָ�����ʪ�ȵ�ָ��
 *
 * \retval AM_OK : ��ȡ�ɹ�
 * \retval OTHER : ��ȡʧ��
 */
int am_sht20_humidity_read (am_sht20_handle_t handle, float *p_humidity);

/**
 * \brief SHT20�����������λ
 * \param[in]  handle : SHT20����������
 * \retval AM_OK : �����λ�ɹ�
 * \retval OTHER : �����λʧ��
 */
int am_sht20_soft_reset (am_sht20_handle_t handle);

/**
 * \brief SHT20��������ʼ��
 *
 * \param[in] p_dev      : ָ��SHT20�豸�ṹ���ָ��
 * \param[in] i2c_handle : I2C��׼����������
 *
 * \return SHT20����������,���Ϊ NULL��������ʼ��ʧ��
 */
am_sht20_handle_t am_sht20_init (am_sht20_dev_t *p_dev, am_i2c_handle_t i2c_handle);

/**
 * \brief SHT20 �豸���ʼ��
 * \param[in]  handle : SHT20����������
 * \return ��
 */
void am_sht20_deinit (am_sht20_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_PCF85063_H */

/* end of file */
