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
 * \brief  LSM6DSL������ٶȴ�����Ӧ�ýӿ�ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 2018-09-12  wk, first implementation.
 * \endinternal
 */

#include "am_lsm6dsl.h"


/** \brief i2c��ַ */
#define    LSM6DSL_ADDR                         0x6B

/** \brief �豸�Ĵ�����ַ */
#define    LSM6DSL_FUNC_CFG_ACCESS              0x01   /**< \brief Ƕ��ʽ�������üĴ��� */

#define    LSM6DSL_SENSOR_SYNC_TIME_FRAME       0x04   /**< \brief ������ͬ�����üĴ��� */
#define    LSM6DSL_SENSOR_SYNC_RES_RATIO        0x05

#define    LSM6DSL_FIFO_CTRL1                   0x06   /**< \brief FIFO���üĴ��� */
#define    LSM6DSL_FIFO_CTRL2                   0x07
#define    LSM6DSL_FIFO_CTRL3                   0x08
#define    LSM6DSL_FIFO_CTRL4                   0x09
#define    LSM6DSL_FIFO_CTRL5                   0x0A

#define    LSM6DSL_DRDY_PULSE_CFG_G             0x0B
#define    LSM6DSL_RESERVED                     0x0C
#define    LSM6DSL_INT1_CTRL                    0x0D   /**< \brief INT1���ſ��� */
#define    LSM6DSL_INT2_CTRL                    0x0E   /**< \brief INT2���ſ��� */

#define    LSM6DSL_WHO_AM_I                     0x0F   /**< \brief ID */

#define    LSM6DSL_CTRL1_XL                     0x10   /**< \brief ���ٶȼƺ������ǿ��ƼĴ��� */
#define    LSM6DSL_CTRL2_G                      0x11
#define    LSM6DSL_CTRL3_C                      0x12
#define    LSM6DSL_CTRL4_C                      0x13
#define    LSM6DSL_CTRL5_C                      0x14
#define    LSM6DSL_CTRL6_C                      0x15
#define    LSM6DSL_CTRL7_G                      0x16
#define    LSM6DSL_CTRL8_XL                     0x17
#define    LSM6DSL_CTRL9_XL                     0x18
#define    LSM6DSL_CTRL10_C                     0x19

#define    LSM6DSL_MASTER_CONFIG                0x1A   /**< \brief I2C�����üĴ��� */

#define    LSM6DSL_WAKE_UP_SRC                  0x1B   /**< \brief �жϼĴ��� */
#define    LSM6DSL_TAP_SRC                      0x1C
#define    LSM6DSL_D6D_SRC                      0x1D

#define    LSM6DSL_STATUS_REG                   0x1E   /**< \brief ״̬���ݼĴ����û��ӿ� */

#define    LSM6DSL_OUT_TEMP_L                   0x20   /**< \brief �¶�������ݼĴ��� */
#define    LSM6DSL_OUT_TEMP_H                   0x21

#define    LSM6DSL_OUTX_L_G                     0x22   /**< \brief ����������Ĵ����û��ӿ� */
#define    LSM6DSL_OUTX_H_G                     0x23
#define    LSM6DSL_OUTY_L_G                     0x24
#define    LSM6DSL_OUTY_H_G                     0x25
#define    LSM6DSL_OUTZ_L_G                     0x26	
#define    LSM6DSL_OUTZ_H_G                     0x27

#define    LSM6DSL_OUTX_L_XL                    0x28   /**< \brief ���ٶȼ�����Ĵ��� */
#define    LSM6DSL_OUTX_H_XL                    0x29
#define    LSM6DSL_OUTY_L_XL                    0x2A
#define    LSM6DSL_OUTY_H_XL                    0x2B
#define    LSM6DSL_OUTZ_L_XL                    0x2C
#define    LSM6DSL_OUTZ_H_XL                    0x2D

#define    LSM6DSL_ENSORHUB1_REG                0x2E   /**< \brief ����������������Ĵ��� */
#define    LSM6DSL_ENSORHUB2_REG                0x2F
#define    LSM6DSL_ENSORHUB3_REG                0x30
#define    LSM6DSL_ENSORHUB4_REG                0x31
#define    LSM6DSL_ENSORHUB5_REG                0x32
#define    LSM6DSL_ENSORHUB6_REG                0x33
#define    LSM6DSL_ENSORHUB7_REG                0x34
#define    LSM6DSL_ENSORHUB8_REG                0x35
#define    LSM6DSL_ENSORHUB9_REG                0x36
#define    LSM6DSL_ENSORHUB10_REG               0x37
#define    LSM6DSL_ENSORHUB11_REG               0x38
#define    LSM6DSL_ENSORHUB12_REG               0x39

#define    LSM6DSL_FIFO_STATUS1                 0x3A   /**< \brief FIFO״̬�Ĵ��� */
#define    LSM6DSL_FIFO_STATUS2                 0x3B
#define    LSM6DSL_FIFO_STATUS3                 0x3C
#define    LSM6DSL_FIFO_STATUS4                 0x3D

#define    LSM6DSL_FIFO_DATA_OUT_L              0x3E   /**< \brief FIFO��������Ĵ��� */
#define    LSM6DSL_FIFO_DATA_OUT_H              0x3F

#define    LSM6DSL_TIMESTAMP0_REG               0x40   /**< \brief ʱ�������Ĵ��� */
#define    LSM6DSL_TIMESTAMP1_REG               0x41
#define    LSM6DSL_TIMESTAMP2_REG               0x42

#define    LSM6DSL_STEP_TIMESTAMP_L             0x49   /**< \brief ����������ʱ����Ĵ��� */
#define    LSM6DSL_STEP_TIMESTAMP_H             0x4A

#define    LSM6DSL_STEP_COUNTER_L               0x4B   /**< \brief ��������������Ĵ��� */
#define    LSM6DSL_STEP_COUNTER_H               0x4C

#define    LSM6DSL_SENSORHUB13_REG              0x4D   /**< \brief ����������������Ĵ��� */
#define    LSM6DSL_SENSORHUB14_REG              0x4E
#define    LSM6DSL_SENSORHUB15_REG              0x4F
#define    LSM6DSL_SENSORHUB16_REG              0x50
#define    LSM6DSL_SENSORHUB17_REG              0x51
#define    LSM6DSL_SENSORHUB18_REG              0x52

#define    LSM6DSL_FUNC_SRC1                    0x53   /**< \brief �жϼĴ��� */
#define    LSM6DSL_FUNC_SRC2                    0x54

#define    LSM6DSL_WRIST_TILT_IA                0x55   /**< \brief �жϼĴ��� */

#define    LSM6DSL_TAP_CFG                      0x58   /**< \brief �жϼĴ��� */
#define    LSM6DSL_TAP_THS_6D                   0x59
#define    LSM6DSL_INT_DUR2                     0x5A
#define    LSM6DSL_WAKE_UP_THS                  0x5B
#define    LSM6DSL_WAKE_UP_DUR                  0x5C
#define    LSM6DSL_FREE_FALL                    0x5D
#define    LSM6DSL_MD1_CFG                      0x5E
#define    LSM6DSL_MD2_CFG                      0x5F

#define    LSM6DSL_MASTER_CMD_CODE              0x60
#define    LSM6DSL_SENS_SYNC_SPI_ERROR_CODE     0x61

#define    LSM6DSL_OUT_MAG_RAW_X_L              0x66   /**< \brief ��������Ĵ��� */
#define    LSM6DSL_OUT_MAG_RAW_X_H              0x67
#define    LSM6DSL_OUT_MAG_RAW_Y_L              0x68
#define    LSM6DSL_OUT_MAG_RAW_Y_H              0x69
#define    LSM6DSL_OUT_MAG_RAW_Z_L              0x6A
#define    LSM6DSL_OUT_MAG_RAW_Z_H              0x6B

#define    LSM6DSL_X_OFS_USR                    0x73   /**< \brief ���ٶȼ��û�ƫ��У�� */
#define    LSM6DSL_Y_OFS_USR                    0x74
#define    LSM6DSL_Z_OFS_USR                    0x75

/**
 * \brief ��ȡLSM6DSL������ٶȼĴ���
 * \return AM_OK:�ɹ�    OTHER��ʧ��
 */
static int __lsm6dsl_read_reg(am_lsm6dsl_handle_t handle, 
                              uint8_t             reg_addr,
                              int16_t             *p_accel)
{
    uint8_t accel_temp[2];
    int ret = AM_OK;
    
    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = &(handle->i2c_dev);
    
    ret =  am_i2c_read(p_i2c_dev, reg_addr, accel_temp, 2);
    
    /* ����ȡ�Ƿ�ʧ�� */
    if (ret != AM_OK) {
        return ret;
    }
    /* ���ݴ��� */
    if (accel_temp[0] & 0x01) {
        *p_accel = (((uint16_t)(accel_temp[1] << 8)
		           | (uint16_t)accel_temp[0])*360/65535);			
    }
    
    return ret;
}
 

int am_lsm6dsl_read_temp(am_lsm6dsl_handle_t handle, int16_t* p_temp)
{
	int ret = AM_OK;
    /* ��ȡ�¶� */    
        ret = __lsm6dsl_read_reg(handle, LSM6DSL_OUT_TEMP_L, p_temp);
    /* ����ȡ�Ƿ�ʧ�� */
    if (ret != AM_OK) {
        return ret;
    }
	/* �����¶� */
    *p_temp = (int8_t)(24 + *p_temp * 1.0 / 2);
		
    return  ret;
}


/**
 * \brief ��ȡlsm6dsl������ٶ�
 * \return AM_OK:�ɹ�    OTHER��ʧ��
 */
int am_lsm6dsl_read_accel(am_lsm6dsl_handle_t handle, int16_t* p_accel)
{
    int ret = AM_OK;
    /* ��ȡX������� */
    ret = __lsm6dsl_read_reg(handle, LSM6DSL_OUTX_L_XL, &p_accel[0]);
    /* ����ȡ�Ƿ�ʧ�� */
    if (ret != AM_OK) {
        return ret;
    }  

    /* ��ȡY����ٶ� */    
    ret = __lsm6dsl_read_reg(handle, LSM6DSL_OUTY_L_XL, &p_accel[1]);
    /* ����ȡ�Ƿ�ʧ�� */
    if (ret != AM_OK) {
        return ret;
    }
		
    /* ��ȡZ����ٶ� */    
    ret = __lsm6dsl_read_reg(handle, LSM6DSL_OUTZ_L_XL, &p_accel[2]);
    /* ����ȡ�Ƿ�ʧ�� */
    if (ret != AM_OK) {
        return ret;
    }
		
    return  ret;  
}

/**
 * \brief LSM6DSL����Ŵ�������ʼ��
 */
am_lsm6dsl_handle_t am_lsm6dsl_init(am_lsm6dsl_dev_t     *p_dev, 
                              const am_lsm6dsl_devinfo_t *p_devinfo,
                                    am_i2c_handle_t      i2c_handle)
{
    uint8_t lsm6dsl_id =    0; 
  
    /* ��֤������Ч�� */
    if (NULL == p_dev ||  NULL == p_devinfo || NULL == i2c_handle) {
        return NULL;
    }
		
    p_dev->i2c_dev.handle = i2c_handle; 
		
    /* ��ʼ���ú�LSM6DSL�豸��Ϣ */
    am_i2c_mkdev(&(p_dev->i2c_dev),i2c_handle,
                 LSM6DSL_ADDR,AM_I2C_ADDR_7BIT 
		         | AM_I2C_SUBADDR_1BYTE);

    /* ��ȡLSM6DSL ID */
    am_i2c_read(&(p_dev->i2c_dev),LSM6DSL_WHO_AM_I, &lsm6dsl_id, 1);
    AM_DBG_INFO("lsm6dsl_ID = 0x%x\r\n", lsm6dsl_id);
		
		
    /* ����״̬�Ĵ��� */
    am_i2c_write(&(p_dev->i2c_dev), LSM6DSL_CTRL1_XL, &(p_devinfo->ctrl1_xl), 1);
		
		
    /* ����״̬�Ĵ��� */
    am_i2c_write(&(p_dev->i2c_dev), LSM6DSL_STATUS_REG, &(p_devinfo->status_reg), 1);
		
		
    /* ����FIFO������� */
    am_i2c_write(&(p_dev->i2c_dev), LSM6DSL_FIFO_CTRL5, &(p_devinfo->fifo_odr), 1);
		
    return p_dev;
}

/**
 * \brief LSM6DSL �豸���ʼ��
 */
void am_lsm6dsl_deinit (am_lsm6dsl_handle_t handle)
{
	
}

/* end of file */
