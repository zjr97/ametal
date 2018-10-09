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
 * \brief LPC82x ���� ʵ����ʼ����������
 *
 * ���������豸��I2C��SPI��ADC...����ʵ����ʼ���������ڱ�ͷ�ļ���������ʹ��ʵ��
 * ��ʼ���������������ɻ��һ������ľ����Ȼ��ʹ����صĽӿں�����������в�����
 *
 * \sa am_lpc82x_inst_init.h
 * \internal
 * \par Modification history
 * - 1.00 15-12-11  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC82X_INST_INIT_H
#define __AM_LPC82X_INST_INIT_H

#include "am_lpc_sct.h"
#include "ametal.h"
#include "am_adc.h"
#include "am_crc.h"
#include "am_i2c.h"
#include "am_timer.h"
#include "am_cap.h"
#include "am_pwm.h"
#include "am_wdt.h"
#include "am_spi.h"
#include "am_uart.h"
#include "am_zm516x.h"
#include "am_hwconf_miniport_zlg72128.h"
#include "am_hwconf_miniport_595.h"
#include "am_hwconf_led_gpio.h"
#include "am_hwconf_key_gpio.h"
#include "am_hwconf_miniport_view.h"
#include "am_hwconf_miniport_led.h"
#include "am_hwconf_miniport_key.h"
#include "am_hwconf_miniport_view_key.h"
#include "am_hwconf_lm75.h"

/**
 * \addtogroup am_if_lpc82x_inst_init
 * \copydoc am_lpc82x_inst_init.h
 * @{
 */

/**
 * \brief  CLK ʵ����ʼ������ʼ��ϵͳʱ��
 * \retval AM_OK : ʱ�ӳɹ���ʼ��
 * \note ʱ�ӽ�Ϊ���⣬�޽��ʼ������
 */
int am_lpc82x_clk_inst_init (void);


/**
 * \brief  ADC0 �жϷ���ʵ����ʼ�������ADC��׼������
 * \return ADC��׼����������ΪNULL��������ʼ��ʧ��
 */
am_adc_handle_t am_lpc82x_adc0_int_inst_init (void);

/**
 * \brief ADC0 �ж�ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_adc0_inst_init() ������õ�ADC���
 * \return ��
 */
void am_lpc82x_adc0_int_inst_deinit (am_adc_handle_t handle);


/**
 * \brief  ADC0 dma����ʵ����ʼ�������ADC��׼������
 * \return ADC��׼����������ΪNULL��������ʼ��ʧ��
 */
am_adc_handle_t am_lpc82x_adc0_dma_inst_init (void);

/**
 * \brief ADC0 dmaʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_adc0_inst_init() ������õ�ADC���
 * \return ��
 */
void am_lpc82x_adc0_dma_inst_deinit (am_adc_handle_t handle);


/**
 * \brief  CRC ʵ����ʼ�������CRC��׼������
 * \return CRC��׼����������ΪNULL��������ʼ��ʧ��
 */
am_crc_handle_t am_lpc82x_crc_inst_init (void);

/**
 * \brief CRC ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_crc_inst_init() ������õ�CRC���
 * \return ��
 */
void am_lpc82x_crc_inst_deinit (am_crc_handle_t handle);

/**
 * \brief  DMA ʵ����ʼ��
 * \retval AM_OK    : ��ʼ���ɹ�
 */
int am_lpc82x_dma_inst_init (void);

/**
 * \brief DMA ʵ�����ʼ��
 * \return ��
 */
void am_lpc82x_dma_inst_deinit (void);

/**
 * \brief  GPIO ʵ����ʼ��
 * \retval AM_OK    : ��ʼ���ɹ�
 */
int am_lpc82x_gpio_inst_init (void);

/**
 * \brief GPIO ʵ�����ʼ��
 * \return ��
 */
void am_lpc82x_gpio_inst_deinit (void);


/**
 * \brief  I2C0 ʵ����ʼ�������I2C��׼������
 * \return I2C��׼����������ΪNULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_lpc82x_i2c0_inst_init (void);

/**
 * \brief I2C0 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_i2c0_inst_init() ������õ�I2C���
 * \return ��
 */
void am_lpc82x_i2c0_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief  I2C1 ʵ����ʼ�������I2C��׼������
 * \return I2C��׼����������ΪNULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_lpc82x_i2c1_inst_init (void);

/**
 * \brief I2C1 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_i2c1_inst_init() ������õ�I2C���
 * \return ��
 */
void am_lpc82x_i2c1_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief  I2C2 ʵ����ʼ�������I2C��׼������
 * \return I2C��׼����������ΪNULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_lpc82x_i2c2_inst_init (void);

/**
 * \brief I2C2 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_i2c2_inst_init() ������õ�I2C���
 * \return ��
 */
void am_lpc82x_i2c2_inst_deinit (am_i2c_handle_t handle);


/**
 * \brief  I2C3 ʵ����ʼ�������I2C��׼������
 * \return I2C��׼����������ΪNULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_lpc82x_i2c3_inst_init (void);

/**
 * \brief I2C3 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_i2c3_inst_init() ������õ�I2C���
 * \return ��
 */
void am_lpc82x_i2c3_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief  �ж�ʵ����ʼ������ʼ���ж�����
 * \retval AM_OKΪʵ�����ɹ�������ʧ��
 */
int am_lpc82x_nvic_inst_init (void);

/**
 * \brief  �ж�ʵ�����ʼ��
 */
void am_lpc82x_nvic_inst_deinit (void);

/**
 * \brief  ϵͳSystick��ʼ��
 */
am_timer_handle_t am_arm_systick_inst_init (void);

/**
 * \brief  MRT ʵ����ʼ�������MRT��׼������
 * \return Timer��׼����������ΪNULL��������ʼ��ʧ��
 */
am_timer_handle_t am_lpc82x_mrt_inst_init (void);

/**
 * \brief MRT ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_mrt_inst_init() ������õ�Timer���
 * \return ��
 */
void am_lpc82x_mrt_inst_deinit (am_timer_handle_t handle);

/**
 * \brief  SCT0 ʵ����ʼ�������SCT��׼������
 * \return SCT��׼����������ΪNULL��������ʼ��ʧ��
 */
am_lpc_sct_handle_t am_lpc82x_sct0_inst_init (void);

/**
 * \brief SCT0 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_sct0_inst_init() ������õ�SCT���
 * \return ��
 */
void am_lpc82x_sct0_inst_deinit (am_lpc_sct_handle_t handle);

/**
 * \brief  SCT0 CAP ʵ����ʼ�������CAP��׼������
 * \return CAP��׼����������ΪNULL��������ʼ��ʧ��
 */
am_cap_handle_t am_lpc82x_sct0_cap_inst_init (void);

/**
 * \brief SCT0 CAP ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_sct0_cap_inst_init() ������õ�CAP���
 * \return ��
 */
void am_lpc82x_sct0_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief  SCT0 PWM ʵ����ʼ�������PWM��׼������
 * \return PWM��׼����������ΪNULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_lpc82x_sct0_pwm_inst_init (void);

/**
 * \brief SCT0 PWM ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_sct0_pwm_inst_init() ������õ�PWM���
 * \return ��
 */
void am_lpc82x_sct0_pwm_inst_deinit (am_pwm_handle_t handle);


/**
 * \brief  SCT0 Timer ʵ����ʼ�������Timer��׼������
 * \return Timer��׼����������ΪNULL��������ʼ��ʧ��
 */
am_timer_handle_t am_lpc82x_sct0_timing_inst_init (void);

/**
 * \brief SCT0 Timer ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_sct0_timing_inst_init() ������õ�Timer���
 * \return ��
 */
void am_lpc82x_sct0_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief  SPI0 �жϷ�ʽʵ����ʼ�������SPI��׼������
 * \return SPI��׼����������ΪNULL��������ʼ��ʧ��
 */
am_spi_handle_t am_lpc82x_spi0_int_inst_init (void);

/**
 * \brief SPI0 �жϷ�ʽʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_spi0_int_inst_init() ������õ�SPI���
 * \return ��
 */
void am_lpc82x_spi0_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief  SPI1 �жϷ�ʽʵ����ʼ�������SPI��׼������
 * \return SPI��׼����������ΪNULL��������ʼ��ʧ��
 */
am_spi_handle_t am_lpc82x_spi1_int_inst_init (void);

/**
 * \brief SPI1 �жϷ�ʽʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_spi1_int_inst_init() ������õ�SPI���
 * \return ��
 */
void am_lpc82x_spi1_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief  SPI0 DMA��ʽʵ����ʼ�������SPI��׼������
 * \return SPI��׼����������ΪNULL��������ʼ��ʧ��
 */
am_spi_handle_t am_lpc82x_spi0_dma_inst_init (void);

/**
 * \brief SPI0 DMA��ʽʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_spi0_dma_inst_init() ������õ�SPI���
 * \return ��
 */
void am_lpc82x_spi0_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief  SPI1 DMA��ʽʵ����ʼ�������SPI��׼������
 * \return SPI��׼����������ΪNULL��������ʼ��ʧ��
 */
am_spi_handle_t am_lpc82x_spi1_dma_inst_init (void);

/**
 * \brief SPI1 DMA��ʽʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_spi1_dma_inst_init() ������õ�SPI���
 * \return ��
 */
void am_lpc82x_spi1_dma_inst_deinit (am_spi_handle_t handle);


/** \brief SYSTICK ʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_lpc82x_systick_inst_init (void);

/** \brief SYSTICK ʵ�����ʼ�� */
void am_lpc82x_systick_inst_deinit (am_timer_handle_t handle);

/**
 * \brief  USART0 ʵ����ʼ�������UART��׼������
 * \return UART��׼����������ΪNULL��������ʼ��ʧ��
 */
am_uart_handle_t am_lpc82x_usart0_inst_init (void);

/**
 * \brief USART0 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_usart0_inst_init() ������õ�UART���
 * \return ��
 */
void am_lpc82x_usart0_inst_deinit (am_uart_handle_t handle);


/**
 * \brief  USART1 ʵ����ʼ�������UART��׼������
 * \return UART��׼����������ΪNULL��������ʼ��ʧ��
 */
am_uart_handle_t am_lpc82x_usart1_inst_init (void);

/**
 * \brief     USART1 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_usart1_inst_init() ������õ�UART���
 * \return ��
 */
void am_lpc82x_usart1_inst_deinit (am_uart_handle_t handle);

/**
 * \brief  USART2 ʵ����ʼ�������UART��׼������
 * \return UART��׼����������ΪNULL��������ʼ��ʧ��
 */
am_uart_handle_t am_lpc82x_usart2_inst_init (void);

/**
 * \brief USART2 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_usart2_inst_init() ������õ�UART���
 * \return ��
 */
void am_lpc82x_usart2_inst_deinit (am_uart_handle_t handle);

/**
 * \brief  WKT ʵ����ʼ�������Timer��׼������
 * \return Timer��׼����������ΪNULL��������ʼ��ʧ��
 */
am_timer_handle_t am_lpc82x_wkt_inst_init (void);

/**
 * \brief WKT ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_wkt_inst_init() ������õ�Timer���
 * \return ��
 */
void am_lpc82x_wkt_inst_deinit (am_timer_handle_t handle);


/**
 * \brief  WWDT ʵ����ʼ�������WDT��׼������
 * \return WDT��׼����������ΪNULL��������ʼ��ʧ��
 */
am_wdt_handle_t am_lpc82x_wwdt_inst_init (void);

/**
 * \brief WWDT ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_lpc82x_wwdt_inst_init() ������õ�WDT���
 * \return ��
 */
void am_lpc82x_wwdt_inst_deinit (am_wdt_handle_t handle);

/**
 * \brief ZM516Xʵ����ʼ�������ZM516Xģ���׼����������
 *
 * \return ZM516Xģ���׼����������
 */
am_zm516x_handle_t am_zm516x_inst_init (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_LPC82X_INST_INIT_H */

/* end of file */
