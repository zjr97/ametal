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
 * \brief am824 �������̺����������
 * \sa demo_am824_core_all_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  lnk, first implementation
 * \endinternal
 */

#ifndef __DEMO_AM824_CORE_ALL_ENTRIES_H
#define __DEMO_AM824_CORE_ALL_ENTRIES_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ģ��Ƚ������̣��ж�ģʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_acmp_int_entry (void);

/**
 * \brief ģ��Ƚ������̣���ѹ���ݣ���ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_acmp_lad_entry (void);

/**
 * \brief ģ��Ƚ������̣���ѯģʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_acmp_poll_entry (void);

/**
 * \brief ADC ���̣�ת���������ͨ�� DMA ���䣬ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_adc_dma_entry (void);

/**
 * \brief ADC ��ֵ�Ƚ����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_adc_thcmp_entry (void);

/**
 * \brief ADC DMA ���̣��жϷ�ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_adc_dma_int_entry (void);

/**
 * \brief ADC DMA ���̣���ѯ��ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_adc_dma_poll_entry (void);

/**
 * \brief ADC ���̣��жϷ�ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_adc_int_entry (void);

/**
 * \brief ADC ���ð����������� (NTC) �����¶Ȳ������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_adc_ntc_entry (void);

/**
 * \brief ADC ���̣���ѯ��ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_adc_poll_entry (void);

/**
 * \brief ���������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_buzzer_entry (void);

/**
 * \brief CRC ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_crc_entry (void);

/**
 * \brief CRC���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_crc_entry (void);

/**
 * \brief DMA Ӳ���������̣�ͨ��������ӿ�ʵ��
 */
void demo_am824_core_drv_dma_hwtrigger_burst_entry (void);

/**
 * \brief �ڴ浽�ڴ�� DMA �������̣�ͨ��������ӿ�ʵ��
 */
void demo_am824_core_drv_dma_m2m_entry (void);

/**
 * \brief DMA ƹ�Ҵ������̣�ͨ��������ӿ�ʵ��
 */
void demo_am824_core_drv_dma_ping_pong_entry (void);

/**
 * \brief ������������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_flash_ctrl_entry (void);

/**
 * \brief GPIO �����ж����̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_hw_gpio_int_entry (void);

/**
 * \brief GPIO ģʽƥ��������ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_gpio_pmatch_entry (void);

/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_gpio_entry (void);

/**
 * \brief GPIO �����ж����̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_gpio_int_entry (void);

/**
 * \brief GPIO �������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_gpio_key_entry (void);

/**
 * \brief GPIO ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_gpio_entry (void);

/**
 * \brief I2C ��д EEPROM ���̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_i2c_master_dma_entry (void);

/**
 * \brief I2C ��д EEPROM ���̣���ѯ��ʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_i2c_master_poll_entry (void);

/**
 * \brief I2C �ӻ����̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_i2c_slave_dma_entry (void);

/**
 * \brief I2C �ӻ����̣��жϷ�ʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_i2c_slave_int_entry (void);

/**
 * \brief I2C �ӻ����̣���ѯ��ʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_i2c_slave_poll_entry (void);

/**
 * \brief I2C ������ LM75 ��������ȡ�¶�ֵ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_i2c_lm75_entry (void);

/**
 * \brief I2C ������д EEPROM ���̣�ͨ���첽��׼�ӿ�ʵ��
 */
void demo_am824_core_std_i2c_master_async_entry (void);

/**
 * \brief I2C ������д EEPROM ���̣�ͨ��ͬ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_i2c_master_sync_entry (void);

/**
 * \brief IAP ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_iap_entry (void);

/**
 * \brief �����������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_key_input_event_entry (void);

/**
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_led_entry (void);

/**
 * \brief ��Ƶ�ʶ�ʱ����MRT�����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_mrt_entry (void);

/**
 * \brief ��Ƶ�ʶ�ʱ����MRT�����̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_mrt_timer_entry (void);

/**
 * \brief PLL ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_pll_entry (void);

/**
 * \brief PMU ��ȵ���ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_pmu_deeppowerdown_entry (void);

/**
 * \brief PMU ���˯��ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_pmu_deepsleep_entry (void);

/**
 * \brief PMU ����ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_pmu_powerdown_entry (void);

/**
 * \brief PMU ˯��ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_pmu_sleep_entry (void);

/**
 * \brief SCT 32 λ PWM ���̣�ͨ��������ӿ�ʵ��
 */
void demo_am824_core_drv_sct_timing_pwm_entry (void);

/**
 * \brief SCT 32 λ PWM ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_sct_1_32bit_pwm_entry (void);

/**
 * \brief SCT 32 λ��ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_sct_1_32bit_timing_entry (void);

/**
 * \brief SCT ��Ϊ 2 �� 16 λ��ʱ����� PWM ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_sct_2_16bit_pwm_entry (void);

/**
 * \brief SCT ��Ϊ 2 �� 16 λ��ʱ����ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_sct_2_16bit_timing_entry (void);

/**
 * \brief SCT 32 λ�������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_sct_cap_entry (void);

/**
 * \brief SCT ������״̬���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_sct_multi_states_entry (void);

/**
 * \brief SCT �������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_sct_cap_entry (void);

/**
 * \brief SCT PWM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_sct_pwm_entry (void);

/**
 * \brief SCT ��ʱ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_sct_timer_entry (void);

/**
 * \brief SPI ���������������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_spi_master_entry (void);

/**
 * \brief SPI �ӻ������������̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_spi_slave_dma_entry (void);

/**
 * \brief SPI �ӻ������������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_spi_slave_entry (void);

/**
 * \brief SPI ��д FLASH(MX25L3206E) ���̣�DMA ��ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_spi_flash_dma_entry (void);

/**
 * \brief SPI ��д FLASH(MX25L3206E) ���̣��жϷ�ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_spi_flash_int_entry (void);

/**
 * \brief SPI �ػ����̣�DMA ��ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_spi_master_dma_entry (void);

/**
 * \brief SPI �ػ����̣��жϷ�ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_spi_master_int_entry (void);

/**
 * \brief ���������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_bod_entry (void);

/**
 * \brief ʱ��Ƶ��������̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_clkout_entry (void);

/**
 * \brief Systick ��ʱ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_delay_entry (void);

/**
 * \brief Systick ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_systick_timer_entry (void);

/**
 * \brief USART �Զ�ƥ�䲨�������̣�ͨ��Ӳ����ӿ�ʵ��
 */
void demo_am824_core_hw_usart_autobaud_entry (void);

/**
 * \brief USART ���̣���ѯ��ʽ����ͨ��Ӳ����ӿ�ʵ��
 */
void demo_am824_core_hw_usart_poll_entry (void);

/**
 * \brief USART �����������̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_usart_rx_dma_entry (void);

/**
 * \brief USART �����������̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_usart_tx_dma_entry (void);

/**
 * \brief USART ���������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_usart_flowctrl_entry (void);

/**
 * \brief USART ���̣���ѯ��ʽ����ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_usart_poll_entry (void);

/**
 * \brief USART ���λ��������̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_usart_rngbuf_entry (void);

/**
 * \brief WKT ��ȵ��绽�����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_wkt_deeppowerdown_wakeup_entry (void);

/**
 * \brief WKT ��ʱ�����̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_wkt_timer_entry (void);

/**
 * \brief WKT ��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_wkt_timer_entry (void);

/**
 * \brief WWDT ���̣�ͨ�� HW ��ӿ�ʵ��
 */
void demo_am824_core_hw_wwdt_entry (void);

/**
 * \brief WWDT ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_std_wwdt_entry (void);

/**
 * \brief MicroPort-DS1302 ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_microport_ds1302_entry (void);

/**
 * \brief MicroPort-EEPROM ���̣�ͨ�� NVRAM ��׼�ӿ�ʵ��
 */
void demo_am824_core_microport_eeprom_nvram_entry (void);

/**
 * \brief MicroPort-EEPROM ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_microport_eeprom_entry (void);

/**
 * \brief MicroPort-FLASH ���̣�ͨ�� FTL ��׼�ӿ�ʵ��
 */
void demo_am824_core_microport_flash_ftl_entry (void);

/**
 * \brief MicroPort-FLASH ���̣�ͨ�� MTD ��׼�ӿ�ʵ��
 */
void demo_am824_core_microport_flash_mtd_entry (void);

/**
 * \brief MicroPort-FLASH ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_microport_flash_entry (void);

/**
 * \brief MicroPort-RS485 ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_microport_rs485_entry (void);

/**
 * \brief MicroPort-RTC(PCF85063) ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_microport_rtc_entry (void);

/**
 * \brief MicroPort-RX8025T ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_microport_rx8025t_entry (void);

/**
 * \brief MicroPort USB(XR21V141x) ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_microport_usb_entry (void);

/**
 * \brief MiniPort-View ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_digitron_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-View + MiniPort-KEY ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_hc595_digitron_key_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-View + ���� LM75 ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_hc595_digitron_temp_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-View ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_hc595_digitron_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-LED ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_hc595_led_entry (void);

/**
 * \brief MiniPort-KEY + MiniPort-View ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_key_digitron_entry (void);

/**
 * \brief MiniPort-KEY ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_key_entry (void);

/**
 * \brief MiniPort-LED ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_led_entry (void);

/**
 * \brief MiniPort-ZLG72128 ���̣�ͨ����׼�ӿ�ʵ��
 */
void demo_am824_core_miniport_zlg72128_entry (void);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_AM824_CORE_ALL_ENTRIES_H */

/* end of file */
