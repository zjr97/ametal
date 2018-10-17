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
 * \brief LSM6DSL������ٶȴ�����Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 2018-09-12  wk, first implementation.
 * \endinternal
 */

#ifndef __AM_LSM6DSL_H
#define __AM_LSM6DSL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_i2c.h"
    
/**
 * \addtogroup am_if_lsm6dsl
 * \copydoc am_lsm6dsl.h
 * @{
 */
/**
 * \brief LSM6DSL����������
 */

typedef enum am_lsm6dsl_config {
	
	/**
	 * \brief �����õ�״̬�Ĵ���
	 */
	STATUS_REG         =   0x03,           /**< \brief �¶ȡ������ǡ����ٶȼ������ݿ��� */
	CTRL1_XL           =   0x10,
	
	/**
	 * \brief �����õ�FIFO�������
	 */
	FIFO_ODR_12point5  =   0x01,           /**< \brief FIFO�������12.5Hz  */
	FIFO_ODR_26        =   0x02,           /**< \brief FIFO�������26Hz    */
	FIFO_ODR_52        =   0x03,           /**< \brief FIFO�������52Hz    */
	FIFO_ODR_104       =   0x04,           /**< \brief FIFO�������104Hz   */
	FIFO_ODR_208       =   0x05,           /**< \brief FIFO�������208Hz   */
	FIFO_ODR_416       =   0x06,           /**< \brief FIFO�������416Hz   */
	FIFO_ODR_833       =   0x07,           /**< \brief FIFO�������833Hz   */
	FIFO_ODR_1point66k =   0x08,           /**< \brief FIFO�������1.66kHz */
	FIFO_ODR_3point33k =   0x09,           /**< \brief FIFO�������3.33kHz */
	FIFO_ODR_6point66k =   0x0A,           /**< \brief FIFO�������6.66kHz */
	
}am_lsm6dsl_config_t;
	
/**
 * \brief BMG160ʵ����Ϣ�ṹ�嶨��
 */
typedef struct am_lsm6dsl_devinfo {    
	
    uint8_t ctrl1_xl;
    uint8_t status_reg;                     /**< \brief ״̬�Ĵ���         */
	uint8_t fifo_odr;                       /**< \brief FIFO�������       */
	

} am_lsm6dsl_devinfo_t;

/**
 * \brief LSM6DSL �豸�ṹ��
 */
typedef struct am_lsm6dsl_dev {
    am_i2c_device_t i2c_dev;                /**< \brief LSM6DSL I2C�豸    */
} am_lsm6dsl_dev_t;

/** \brief LSM6DSL ����������� */
typedef am_lsm6dsl_dev_t *am_lsm6dsl_handle_t;	
	
/**
 * \brief LSM6DSL��������ȡ
 *
 * \param[in]  handle  : LSM6DSL����������
 * \param[out] p_accel : ָ�������ǵ�ָ��
 *
 * \retval AM_OK : ��ȡ�ɹ�
 * \retval OTHER : ��ȡʧ��
 */
int am_lsm6dsl_read_temp(am_lsm6dsl_handle_t handle, int16_t* p_temp);


/**
 * \brief LSM6DSL��������ȡ
 *
 * \param[in]  handle  : LSM6DSL����������
 * \param[out] p_accel : ָ�������ǵ�ָ��
 *
 * \retval AM_OK : ��ȡ�ɹ�
 * \retval OTHER : ��ȡʧ��
 */
int am_lsm6dsl_read_accel(am_lsm6dsl_handle_t handle, int16_t* p_accel);



/**
 * \brief LSM6DSL��������ʼ��
 *
 * \param[in] p_dev      : ָ��LSM6DSL�豸�ṹ���ָ��
 * \param[in] p_devinfo  : ָ��LSM6DSL�豸��Ϣ�ṹ���ָ��  
 * \param[in] i2c_handle : I2C��׼����������
 *
 * \return LSM6DSL����������,���Ϊ NULL��������ʼ��ʧ��
 */
am_lsm6dsl_handle_t am_lsm6dsl_init (am_lsm6dsl_dev_t           *p_dev,
                                     const am_lsm6dsl_devinfo_t *p_devinfo,  
					                 am_i2c_handle_t            i2c_handle);

/**
 * \brief LSM6DSL �豸���ʼ��
 * \param[in]  handle : LSM6DSL����������
 * \return ��
 */
void am_lsm6dsl_deinit(am_lsm6dsl_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LSM6DSL_H */

/* end of file */
