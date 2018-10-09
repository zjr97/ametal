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
 * \brief ʵ����ʼ����������
 *
 * ���������豸��I2C��SPI��ADC...����ʵ����ʼ���������ڱ�ͷ�ļ���������ʹ��ʵ��
 * ��ʼ���������������ɻ��һ������ľ����Ȼ��ʹ����صĽӿں�����������в�����
 *
 * \sa am_kl26_inst_init.h
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  nwt, first implementation.
 * \endinternal
 */
 
#ifndef __AM_KL26_INST_INIT_H
#define __AM_KL26_INST_INIT_H
 
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
#include "am_hwconf_led_gpio.h"
#include "am_hwconf_key_gpio.h"
#include "am_hwconf_buzzer_pwm.h"
#include "am_hwconf_debug_uart.h"
#include "am_hwconf_system_tick_softimer.h"
#include "am_hwconf_lm75.h"
#include "am_hwconf_microport.h"
#include "am_hwconf_miniport_zlg72128.h"
#include "am_hwconf_miniport_595.h"
#include "am_hwconf_miniport_view.h"
#include "am_hwconf_miniport_led.h"
#include "am_hwconf_miniport_key.h"
#include "am_hwconf_miniport_view_key.h"
#include "am_gpio.h"
#include "am_rtc.h"
#include "am_dac.h"

/**
 * \addtogroup am_kl26_if_inst_init
 * \copydoc am_kl26_inst_init.h
 * @{
 */

/**
 * \brief  �ж�ʵ����ʼ������ʼ���ж�����
 * \retval AM_OKΪʵ�����ɹ�������ʧ��
 */
int am_kl26_nvic_inst_init (void);

/**
 * \brief  �ж�ʵ�����ʼ��
 * \retval ��
 */
void am_kl26_nvic_inst_deinit (void);

/**
 * \brief  tpm0 Timer ʵ����ʼ�� ��ȡTimer��׼������
 * \retval Timer��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_timer_handle_t am_kl26_tpm0_timing_inst_init (void);

/**
 * \brief  tpm0 Timer ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm0_timing_inst_init() ������õ�Timer���
 * \retval ��
 */
void am_kl26_tpm0_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief  tpm1 Timer ʵ����ʼ�� ��ȡTimer��׼������
 * \retval Timer��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_timer_handle_t am_kl26_tpm1_timing_inst_init (void);

/**
 * \brief  tpm1 Timer ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm0_timing_inst_init() ������õ�Timer���
 * \retval ��
 */
void am_kl26_tpm1_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief  tpm2 Timer ʵ����ʼ�� ��ȡTimer��׼������
 * \retval Timer��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_timer_handle_t am_kl26_tpm2_timing_inst_init (void);


/**
 * \brief  tpm2 Timer ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm0_timing_inst_init() ������õ�Timer���
 * \retval ��
 */
void am_kl26_tpm2_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief  tpm0 pwm ʵ����ʼ�� ��ȡTimer��׼������
 * \retval pwm��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_kl26_tpm0_pwm_inst_init (void);

/**
 * \brief  tpm0 pwm ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm0_pwm_inst_init() ������õ�pwm���
 * \retval ��
 */
void am_kl26_tpm0_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief  tpm1 pwm ʵ����ʼ�� ��ȡTimer��׼������
 * \retval pwm��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_kl26_tpm1_pwm_inst_init (void);

/**
 * \brief  tpm1 pwm ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm1_pwm_inst_init() ������õ�pwm���
 * \retval ��
 */
void am_kl26_tpm1_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief  tpm2 pwm ʵ����ʼ�� ��ȡTimer��׼������
 * \retval pwm��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_kl26_tpm2_pwm_inst_init (void);

/**
 * \brief  tpm2 pwm ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm2_pwm_inst_init() ������õ�pwm���
 * \retval ��
 */
void am_kl26_tpm2_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief  tpm0 cap ʵ����ʼ�� ��ȡTimer��׼������
 * \retval cap��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_cap_handle_t am_kl26_tpm0_cap_inst_init (void);

/**
 * \brief  tpm0 cap ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm0_cap_inst_init() ������õ�cap���
 * \retval ��
 */
void am_kl26_tpm0_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief  tpm1 cap ʵ����ʼ�� ��ȡTimer��׼������
 * \retval cap��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_cap_handle_t am_kl26_tpm1_cap_inst_init (void);

/**
 * \brief  tpm1 cap ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm1_cap_inst_init() ������õ�cap���
 * \retval ��
 */
void am_kl26_tpm1_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief  tpm2 cap ʵ����ʼ�� ��ȡTimer��׼������
 * \retval cap��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_cap_handle_t am_kl26_tpm2_cap_inst_init (void);

/**
 * \brief  tpm2 cap ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_tpm2_cap_inst_init() ������õ�cap���
 * \retval ��
 */
void am_kl26_tpm2_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief  pit Timer ʵ����ʼ�� ��ȡTimer��׼������
 * \retval cap��׼������  ��ΪNULL��������ʼ��ʧ��
 */
am_timer_handle_t am_kl26_pit_timing_inst_init (void);

/**
 * \brief  pit Timer ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_pit_timing_inst_init() ������õ�Timer���
 * \retval ��
 */
void am_kl26_pit_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief  CLK ʵ����ʼ������ʼ��ϵͳʱ��
 * \retval AM_OK : ʱ�ӳɹ���ʼ��
 */
int am_kl26_clk_inst_init (void);

/**
 * \brief  PMU ʵ����ʼ������ʼ��ϵͳʱ��
 * \retval AM_OK : �ɹ���ʼ��
 */
int am_kl26_pmu_inst_init (void);

/** \brief PMUʵ�����ʼ�� */
void am_kl26_pmu_inst_deinit (void);

/**
 * \brief  GPIO ʵ����ʼ��
 * \retval AM_OK    : ��ʼ���ɹ�
 */
int am_kl26_gpio_inst_init (void);

/**
 * \brief GPIO ʵ�����ʼ��
 * \return ��
 */
void am_kl26_gpio_inst_deinit (void);

/**
 * \brief  USART0 ʵ����ʼ�������UART��׼������
 * \return UART��׼����������ΪNULL��������ʼ��ʧ��
 */
am_uart_handle_t am_kl26_uart0_inst_init (void);

/**
 * \brief USART0 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_uart0_inst_init() ������õ�UART���
 * \return ��
 */
void am_kl26_uart0_inst_deinit (am_uart_handle_t handle);

/**
 * \brief  USART1 ʵ����ʼ�������UART��׼������
 * \return UART��׼����������ΪNULL��������ʼ��ʧ��
 */
am_uart_handle_t am_kl26_uart1_inst_init (void);

/**
 * \brief     USART1 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_uart1_inst_init() ������õ�UART���
 * \return ��
 */
void am_kl26_uart1_inst_deinit (am_uart_handle_t handle);

/**
 * \brief  USART2 ʵ����ʼ�������UART��׼������
 * \return UART��׼����������ΪNULL��������ʼ��ʧ��
 */
am_uart_handle_t am_kl26_uart2_inst_init (void);

/**
 * \brief USART2 ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_uart2_inst_init() ������õ�UART���
 * \return ��
 */
void am_kl26_uart2_inst_deinit (am_uart_handle_t handle);

/**
 * \brief  RTC ʵ����ʼ�������RTC��׼������
 * \return RTC ��׼����������ΪNULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_kl26_rtc_inst_init (void);

/**
 * \brief RTC ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_rtc_inst_init() ������õ�RTC���
 * \return ��
 */
void am_kl26_rtc_inst_deinit (am_rtc_handle_t handle);


/**
 * \brief  LPTMR Timer ʵ����ʼ�������Timer��׼������
 * \return Timer ��׼����������ΪNULL��������ʼ��ʧ��
 */
am_timer_handle_t am_kl26_lptmr_timing_inst_init (void);

/**
 * \brief LPTMR Timer ʵ�����ʼ��
 * \param[in] handle : ͨ�� am_kl26_lptmr_timing_inst_init() ������õ�Timer���
 * \return ��
 */
void am_kl26_lptmr_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief ADC0 ʵ����ʼ�������ADC��׼������
 *
 * \return ��
 */
am_adc_handle_t am_kl26_adc0_inst_init (void);

/**
 * \brief ADC0 ʵ�����ʼ��
 * \param[in] handle : ADC0���ֵ
 *
 * \return ��
 */
void am_kl26_adc0_inst_deinit (am_adc_handle_t handle);

/**
 * \brief DMA ʵ����ʼ��
 * \return ��
 */
void am_kl26_dma_inst_init (void);

/**
 * \brief DMA ʵ�����ʼ��
 * \return ��
 */
void am_kl26_dma_inst_deinit (void);

/**
 * \brief I2C0 ʵ����ʼ��
 * \return I2C���ֵ
 */
am_i2c_handle_t am_kl26_i2c0_inst_init (void);

/**
 * \brief I2C0 ʵ�����ʼ��
 * \return ��
 */
void am_kl26_i2c0_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C1 ʵ����ʼ��
 * \return I2C���ֵ
 */
am_i2c_handle_t am_kl26_i2c1_inst_init (void);


/**
 * \brief I2C1 ʵ�����ʼ��
 * \return ��
 */
void am_kl26_i2c1_inst_deinit (am_i2c_handle_t handle);


/**
 * \brief SPI0 ʵ����ʼ�������SPI��׼������(INT��ʽ)
 * \return SPI0���ֵ����ΪNULL��������ʼ��ʧ��
 */
am_spi_handle_t am_kl26_spi0_int_inst_init (void);

/**
 * \brief SPI0 ʵ�����ʼ��(INT��ʽ)
 * \param[in] handle : ͨ�� am_kl26_spi0_int_inst_init() ������õ�SPI0���
 * \return ��
 */
void am_kl26_spi0_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 ʵ����ʼ�������SPI��׼������(INT��ʽ)
 * \return SPI1���ֵ����ΪNULL��������ʼ��ʧ��
 */
am_spi_handle_t am_kl26_spi1_int_inst_init (void);

/**
 * \brief SPI1 ʵ�����ʼ��(INT��ʽ)
 * \param[in] handle : ͨ�� am_kl26_spi1_int_inst_init() ������õ�SPI0���
 * \return ��
 */
void am_kl26_spi1_int_inst_deinit (am_spi_handle_t handle);


/**
 * \brief SPI0 ʵ����ʼ�������SPI��׼������(DMA��ʽ)
 * \return SPI0���ֵ����ΪNULL��������ʼ��ʧ��
 */
am_spi_handle_t am_kl26_spi0_dma_inst_init (void);

/**
 * \brief SPI0 ʵ�����ʼ��(DMA��ʽ)
 * \param[in] handle : ͨ�� am_kl26_spi0_dma_inst_init() ������õ�SPI0���
 * \return ��
 */
void am_kl26_spi0_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 ʵ����ʼ�������SPI��׼������(DMA��ʽ)
 * \return SPI1���ֵ����ΪNULL��������ʼ��ʧ��
 */
am_spi_handle_t am_kl26_spi1_dma_inst_init (void);

/**
 * \brief SPI1 ʵ�����ʼ��(DMA��ʽ)
 * \param[in] handle : ͨ�� am_kl26_spi1_dma_inst_init() ������õ�SPI0���
 * \return ��
 */
void am_kl26_spi1_dma_inst_deinit (am_spi_handle_t handle);
/**
 * \brief TSIʵ����ʼ��
 *
 * \param[in] ��
 *
 * \retval AM_OK: ��ʼ�������ɹ�
 */
int am_kl26_tsi_inst_init (void);

/**
 * \brief TSIʵ�����ʼ��
 *
 * \return ��
 */
void am_kl26_tsi_inst_deinit (void);

/**
 * \brief DAC0 ʵ����ʼ��
 * \return ���DAC��׼������
 */
am_dac_handle_t am_kl26_dac0_inst_init (void);

/**
 * \brief DAC0 ʵ�����ʼ��
 * \param[in] handle : DAC0���ֵ
 *
 * \return ��
 */
void am_kl26_dac0_inst_deinit (am_dac_handle_t handle);

/**
 * \brief  WDT ʵ����ʼ�������WDT��׼������
 *
 * \return WDT���ֵ
 */
am_wdt_handle_t am_kl26_wdt_inst_init (void);

/**
 * \brief WDT ʵ�����ʼ��
 *
 * \param[in] handle : WDT���Ź����ֵ
 */
void am_kl26_wdt_inst_deinit (am_wdt_handle_t handle);

/**
 * \brief GPIO LED instance init
 * \param[in] none
 * \return AM_OK: ��ʼ���ɹ�
 */
int am_led_gpio_inst_init (void);

/** \brief SYSTICK ʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_kl26_systick_inst_init (void);

/** \brief SYSTICK ʵ�����ʼ�� */
void am_kl26_systick_inst_deinit (am_timer_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_KL26_INST_INIT_H */

/* end of file */
