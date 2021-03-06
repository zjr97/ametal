/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief BME280压力温湿度传感器应用接口头文件
 * \sa am_bme280.h
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-11  yrz, first implementation.
 * \endinternal
 */

#ifndef __AM_BME280_H
#define __AM_BME280_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_i2c.h"
 
/**
 * \addtogroup am_if_bme280
 * \copydoc am_bme280.h
 * @{
 */    
    
/**
 * \brief BME280传感器配置
 */
typedef enum am_bme280_config {

    /**
     * \brief 可配置的湿度过采样样本数     
     */
    HUMIDITY_OVERESAMPLE_X1  = AM_SBF(1,0),  /**< \brief 湿度过采样样本数为1  */
    HUMIDITY_OVERESAMPLE_X2  = AM_SBF(2,0),  /**< \brief 湿度过采样样本数为2  */ 
    HUMIDITY_OVERESAMPLE_X4  = AM_SBF(3,0),  /**< \brief 湿度过采样样本数为4  */
    HUMIDITY_OVERESAMPLE_X8  = AM_SBF(4,0),  /**< \brief 湿度过采样样本数为8  */
    HUMIDITY_OVERESAMPLE_X16 = AM_SBF(5,0),  /**< \brief 湿度过采样样本数为16 */
    
    /**
     * \brief 可配置的压力过采样样本数     
     */
    PRESSURE_OVERESAMPLE_X1  = AM_SBF(1,2),  /**< \brief 压力过采样样本数为1  */
    PRESSURE_OVERESAMPLE_X2  = AM_SBF(2,2),  /**< \brief 压力过采样样本数为2  */ 
    PRESSURE_OVERESAMPLE_X4  = AM_SBF(3,2),  /**< \brief 压力过采样样本数为4  */
    PRESSURE_OVERESAMPLE_X8  = AM_SBF(4,2),  /**< \brief 压力过采样样本数为8  */
    PRESSURE_OVERESAMPLE_X16 = AM_SBF(5,2),  /**< \brief 压力过采样样本数为16 */
    
    /**
     * \brief 可配置的温度过采样样本数     
     */
    TEMP_OVERESAMPLE_X1  = AM_SBF(1,5),      /**< \brief 温度过采样样本数为1  */
    TEMP_OVERESAMPLE_X2  = AM_SBF(2,5),      /**< \brief 温度过采样样本数为2  */ 
    TEMP_OVERESAMPLE_X4  = AM_SBF(3,5),      /**< \brief 温度过采样样本数为4  */
    TEMP_OVERESAMPLE_X8  = AM_SBF(4,5),      /**< \brief 温度过采样样本数为8  */
    TEMP_OVERESAMPLE_X16 = AM_SBF(5,5),      /**< \brief 温度过采样样本数为16 */    
    
    /**
     * \brief 可配置的电源模式     
     */
    SLEEP_MODE   = AM_SBF(0,0),              /**< \brief 睡眠模式             */
    FORCED_MODE  = AM_SBF(1,0),              /**< \brief 强制模式             */
    NORMAL_MODE  = AM_SBF(3,0),              /**< \brief 正常模式             */

    /**
     * \brief 可配置的待机时间    
     */
    STANDBY_TIME_HALF_MS = AM_SBF(0,5),      /**< \brief 待机时间0.5ms        */
    STANDBY_TIME_63MS    = AM_SBF(1,5),      /**< \brief 待机时间62.5ms       */
    STANDBY_TIME_125MS   = AM_SBF(2,5),      /**< \brief 待机时间125ms        */
    STANDBY_TIME_250MS   = AM_SBF(3,5),      /**< \brief 待机时间250ms        */
    STANDBY_TIME_500MS   = AM_SBF(4,5),      /**< \brief 待机时间500ms        */
    STANDBY_TIME_1000MS  = AM_SBF(5,5),      /**< \brief 待机时间1000ms       */
    STANDBY_TIME_2000MS  = AM_SBF(6,5),      /**< \brief 待机时间2000ms       */
    STANDBY_TIME_4000MS  = AM_SBF(7,5),      /**< \brief 待机时间4000ms       */

} am_bme280_config_t;
    
   
/**
 * \brief BME280校准参数
 */ 
typedef struct bme280_calib_param {
	uint16_t  dig_t1;
	int16_t   dig_t2;
	int16_t   dig_t3;
	uint16_t  dig_p1;
	int16_t   dig_p2;
	int16_t   dig_p3;
	int16_t   dig_p4;
	int16_t   dig_p5;
	int16_t   dig_p6;
	int16_t   dig_p7;
	int16_t   dig_p8;
	int16_t   dig_p9;
	int32_t   t_fine;
    uint8_t   dig_h1;
    int16_t   dig_h2;
    uint8_t   dig_h3;
    int16_t   dig_h4;
    int16_t   dig_h5;
    uint8_t   dig_h6;    
} am_bme280_calib_param_t;
    
/**
 * \brief BME280 实例信息结构体定义
 */
typedef struct am_bme280_devinfo {
    uint8_t hum_oversampe;                /**< \brief 湿度过采样样本数        */    
    uint8_t press_oversampe;              /**< \brief 压力过采样样本数        */
    uint8_t temp_oversampe;               /**< \brief 温度过采样样本数        */
    uint8_t power_mode;                   /**< \brief 电源模式                */
    uint8_t standby_time;                 /**< \brief 配置待机时间            */
} am_bme280_devinfo_t;
  
/**
 * \brief BME280 设备结构体
 */
typedef struct am_bme280_dev {
    
    /**< \brief BMP280 I2C设备 */
    am_i2c_device_t i2c_dev; 
    
    /** \brief 用于保存校准参数 */
    am_bme280_calib_param_t calib_param; 
    
    /** \brief 用于保存设备信息指针 */
    const am_bme280_devinfo_t  *p_devinfo;    
    
} am_bme280_dev_t;

/** \brief BME280操作句柄定义 */
typedef am_bme280_dev_t *am_bme280_handle_t;
  
/**
 * \brief BME280传感器读取温度
 *
 * \param[in]  handle : BME280服务操作句柄
 * \param[out] temp   : 指向温度的指针
 *
 * \retval AM_OK : 读取成功
 * \retval OTHER : 读取失败
 */
int am_bme280_read_temp (am_bme280_handle_t handle, int8_t *temp);

/**
 * \brief BME280传感器读取气压
 *
 * \param[in]  handle : BME280服务操作句柄
 * \param[out] press  : 指向气压的指针
 *
 * \retval AM_OK : 读取成功
 * \retval OTHER : 读取失败
 */
int am_bme280_read_press (am_bme280_handle_t handle, uint32_t *press);

/**
 * \brief BME280传感器读取湿度
 *
 * \param[in]  handle   : BME280服务操作句柄
 * \param[out] humidity : 指向湿度的指针
 *
 * \retval AM_OK : 读取成功
 * \retval OTHER : 读取失败
 */
int am_bme280_read_hum (am_bme280_handle_t handle, uint8_t *humidity);

/**
 * \brief BME280传感器初始化
 *
 * \param[in] p_dev      : 指向BME280设备结构体的指针
 * \param[in] p_devinfo  : 指向BME280设备信息结构体的指针 
 * \param[in] i2c_handle : I2C标准服务操作句柄
 *
 * \return BME280服务操作句柄,如果为 NULL，表明初始化失败
 */
am_bme280_handle_t am_bme280_init (am_bme280_dev_t *p_dev, 
                                   const am_bme280_devinfo_t *p_devinfo, 
                                   am_i2c_handle_t i2c_handle);

/**
 * @}
 */
                                   
#ifdef __cplusplus
}
#endif

#endif

/* end of file */


