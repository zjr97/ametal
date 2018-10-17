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
 * \brief STD所有例程函数入口声明
 * \sa    demo_std_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  sdy, first implementation
 * \endinternal
 */

#ifndef __DEMO_STD_ENTRIES_H
#define __DEMO_STD_ENTRIES_H

#include "am_cap.h"
#include "am_crc.h"
#include "am_i2c.h"
#include "am_i2c_slv.h"
#include "am_pwm.h"
#include "am_wdt.h"
#include "am_spi.h"
#include "am_spi_slv.h"
#include "am_adc.h"
#include "am_uart.h"
#include "am_temp.h"
#include "am_timer.h"
#include "am_rtc.h"
#include "am_hc595.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ADC例程，利用查询方式获取ADC转换结果，通过标准接口实现
 *
 * \param[in] handle ADC 标准服务句柄
 * \param[in] chan   ADC 通道号
 *
 * \return 无
 */
void demo_std_adc_entry (am_adc_handle_t handle, int chan);

/**
 * \brief ADC 利用板子的热敏电阻(NTC)，推算出温度例程，通过标准接口实现
 *
 * \param[in] handle    ADC 标准服务句柄
 * \param[in] chan      ADC 通道号（该通道对应的引脚需连接至 NTC 端）
 * \param[in] res_fixed 固定分压电阻值（单位：欧姆），与具体硬件电路相关
 *
 * \return 无
 */
void demo_std_adc_ntc_entry (am_adc_handle_t handle,
                             int             chan,
                             uint32_t        res_fixed);

/**
 * \brief 蜂鸣器例程，通过标准接口实现
 *
 * \param 无
 *
 * \return 无
 */
void demo_std_buzzer_entry (void);

/**
 * \brief 定时器实现捕获功能，通过标准接口实现
 *
 * \param[in] cap_handle 输入捕获标准服务句柄
 * \param[in] pwm_handle PWM 标准服务句柄
 * \param[in] cap_chan   定时器捕获通道（一般默认使用捕获通道 0）
 * \param[in] pwm_chan   定时器输出通道（一般默认使用 PWM 通道 0）
 *
 * \return 无
 */
void demo_std_timer_cap_entry (am_cap_handle_t cap_handle, int cap_chan);

/**
 * \brief CRC 例程，通过标准接口实现
 *
 * \param[in] crc_handle CRC 标准服务句柄
 *
 * \return 无
 */
void demo_std_crc_entry (am_crc_handle_t crc_handle);

/**
 * \brief GPIO 例程，通过标准接口实现
 *
 * \param[in] input_pin  GPIO 管脚标号 (# PIO*_0)
 * \param[in] output_pin GPIO 管脚标号 (# PIO*_0)
 *
 * \return 无
 */
void demo_std_gpio_entry (int input_pin, int output_pin);

/**
 * \brief GPIO 引脚中断例程，通过标准接口实现
 *
 * \param[in] pin GPIO 管脚标号 (# PIO*_0)
 *
 * \return 无
 */
void demo_std_gpio_trigger_entry (int pin);

/**
 * \brief I2C 主机读取温度传感器 LM75 例程，通过标准接口实现
 *
 * \param[in] handle 温度标准服务句柄
 *
 * \return 无
 */
void demo_std_i2c_lm75_entry (am_temp_handle_t handle);

/**
 * \brief I2C 主机访问 EEPROM 设备例程，通过异步标准接口实现
 *
 * \param[in] handle      I2C 标准服务句柄
 * \param[in] eeprom_addr EEPROM 地址
 * \param[in] test_len    测试字节数
 *
 * \return 无
 */
void demo_std_i2c_master_async_entry (am_i2c_handle_t handle,
                                      uint32_t        eeprom_addr,
                                      uint32_t        test_len);

/**
 * \brief I2C 主机访问 EEPROM 设备例程，通过同步标准接口实现
 *
 * \param[in] handle      I2C 标准服务句柄
 * \param[in] eeprom_addr EEPROM 地址
 * \param[in] test_len    测试字节数
 *
 * \return 无
 */
void demo_std_i2c_master_sync_entry (am_i2c_handle_t handle,
                                     uint32_t        eeprom_addr,
                                     uint32_t        test_len);

/**
 * \brief I2C 从机模拟 TMP100 例程，通过标准接口实现
 *
 * \param[in] handle I2C 标准服务句柄
 *
 * \return 无
 */
void demo_std_i2c_slave_subaddr_entry (am_i2c_slv_handle_t handle);

/**
 * \brief I2C 从机例程，通过标准接口实现
 *
 * \param[in] handle   I2C 标准服务句柄
 * \param[in] dev_addr 从机地址
 *
 * \return 无
 */
void demo_std_i2c_slave_entry (am_i2c_slv_handle_t handle, uint16_t dev_addr);
 
/**
 * \brief 按键例程（4个按键）
 * \param[in] led_id LED 编号
 * \return 无
 */
void demo_std_4key_entry (void);

/**
 * \brief 按键例程
 * \param[in] led_id LED 编号
 * \return 无
 */
void demo_std_key_entry (void);

/**
 * \brief 按键例程，使用数码管显示当前按下的按键（按键事件在按键回调中立即处理）
 * \param[in] id  数码管编号
 * \return 无
 */
void demo_std_key_digitron_entry (int32_t id);

/**
 * \brief 按键例程，使用数码管显示当前按下的按键（按键事件缓存到环形缓冲区中）
 * \param[in] id  数码管编号
 * \return 无
 */
void demo_std_key_digitron_rngbuf_entry (int32_t id);

/**
 * \brief LED 例程，通过标准接口实现
 * \param[in] led_id LED 编号
 * \return 无
 */
void demo_std_led_entry (int led_id);

/**
 * \brief LED 流水灯例程
 *
 * \param[in] led_id_start  多个LED的起始编号
 * \param[in] num           用于流水灯例程的 LED 数目
 *
 * \return 无
 */
void demo_std_led_water_light_entry (int led_id_start, int num);

/**
 * \brief 定时器 PWM 输出功能，通过标准接口实现
 *
 * \param[in] pwm_handle   PWM 标准服务句柄
 * \param[in] pwm_chan     通道号
 *
 * \return 无
 */
void demo_std_timer_pwm_entry (am_pwm_handle_t pwm_handle, int pwm_chan);

/**
 * \brief 软件定时器例程，通过标准接口实现
 * \return 无
 */
void demo_std_softimer_entry (void);

/**
 * \brief SPI 读写 FLASH(MX25L3206E) 例程，通过标准接口实现
 *
 * \param[in] spi_handle  SPI 标准服务句柄
 * \param[in] cs_pin      片选引脚号
 * \param[in] test_addr   测试地址
 * \param[in] test_length 测试字节数
 *
 * \return 无
 */
void demo_std_spi_flash_entry (am_spi_handle_t spi_handle,
                               int             cs_pin,
                               uint32_t        test_addr,
                               uint32_t        test_length);

/**
 * \brief SPI 例程，通过标准接口实现
 *
 * \param[in] spi_handle SPI 标准服务句柄
 * \param[in] cs_pin     片选引脚号
 *
 * \return 无
 */
void demo_std_spi_master_entry (am_spi_handle_t spi_handle,
                                int             cs_pin);

/**
 * \brief SPI 从机例程，通过标准接口实现
 *
 * \param[in] spi_handle SPI 标准服务句柄
 * \param[in] cs_pin     片选引脚号
 *
 * \return 无
 */
void demo_std_spi_slave_entry (am_spi_slv_handle_t handle);

/**
 * \brief 延时标准接口例程，通过标准接口实现
 *
 * \param[in] led_id LED 编号
 *
 * \return 无
 */
void demo_std_delay_entry (int led_id);

/**
 * \brief Systick 例程，通过标准接口实现
 *
 * \param[in] handle 定时器标准服务句柄
 * \param[in] led_id LED 编号
 *
 * \return 无
 */
void demo_std_systick_timer_entry (am_timer_handle_t handle, int led_id);

/**
 * \brief 定时器实现标准定时器例程，通过标准接口实现
 *
 * \param[in] handle      定时器标准服务句柄
 * \param[in] timing_chan 定时器通道号
 *
 * \return 无
 */
void demo_std_timer_timing_entry (am_timer_handle_t handle,
                                  int               timing_chan);

/**
 * \brief UART 查询方式下接收发送数据例程，通过标准接口实现
 * \param[in] handle UART 标准服务句柄
 * \return 无
 */
void demo_std_uart_polling_entry (am_uart_handle_t handle);

/**
 * \brief UART 环形缓冲区方式下接收发送数据例程，通过标准接口实现
 * \param[in] uart_handle UART 标准服务句柄
 * \return 无
 */
void demo_std_uart_ringbuf_entry (am_uart_handle_t uart_handle);

/**
 * \brief UART RS485例程
 * \param[in] uart_handle UART 标准服务句柄
 * \return 无
 */
void demo_std_uart_rs485_entry (am_uart_handle_t uart_handle);

/**
 * \brief WDT 演示例程，通过标准接口实现
 *
 * \param[in] handle       WDT 标准服务句柄
 * \param[in] time_out_ms  看门狗超时时间
 * \param[in] feed_time_ms 喂狗时间
 *
 * \return 无
 */
void demo_std_wdt_entry (am_wdt_handle_t handle,
                         uint32_t        time_out_ms,
                         uint32_t        feed_time_ms);
                         
/**
 * \brief 数码管显示60秒计时例程
 * \param[in] id 数码管编号
 * \return 无
 */          
void demo_std_digitron_60s_counting_entry (int32_t id);

/**
 * \brief 数码管实时显示温度例程
 *
 * \param[in] id          数码管编号
 * \param[in] temp_handle 温度传感器标准服务句柄
 *
 * \return 无
 */
void demo_std_digitron_temp_entry (int32_t id, am_temp_handle_t temp_handle);
 
/**
 * \brief HC595 输出例程，为便于观察现象，建议将HC595的8个输出连接到LED灯
 * \param[in] hc595_handle  HC595 标准服务句柄
 * \return 无
 */
void demo_std_hc595_led_entry (am_hc595_handle_t hc595_handle);

/**
 * \brief RTC例程
 * \param[in] rtc_handle  RTC设备标准服务句柄
 * \return 无
 */
void demo_std_rtc_entry (am_rtc_handle_t rtc_handle);

/**
 * \brief NVRAM 测试例程
 *
 * 测试使用的存储段需在 __g_nvram_segs[] 列表中定义（am_nvram_cfg.c 文件中）
 *
 * \param[in] p_nvram_name  存储段名
 * \param[in] nvram_unit    存储段单元号
 * \param[in] test_lenth    测试读写数据的长度
 *
 * \return 无
 */
void demo_std_nvram_entry (char *p_nvram_name, int32_t nvram_unit, int32_t test_lenth);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_STD_ENTRIES_H */

/* end of file */
