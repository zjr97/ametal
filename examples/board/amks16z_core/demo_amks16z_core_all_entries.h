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
 * \brief KL26 �������̺����������
 * \sa    demo_all_entrys.h
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  lnk, first implementation.
 * \endinternal
 */

/**
 * \brief TPMʵ�ֱ�׼��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_tpm_timing_entry (void);

/**
 * \brief TPMʵ��PWM��׼�ӿ����̣�ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_tpm_pwm_entry (void);

/**
 * \brief TPMʵ�ֲ����ܣ�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_tpm_cap_entry (void);

/**
 * \brief TPMʵ�ֱ�׼��ʱ�����̣�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_tpm_timing_entry (void);

/**
 * \brief TPMʵ��PWM���ܣ�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_tpm_pwm_entry (void);

/**
 * \brief TPMʵ�ֲ����ܣ�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_tpm_cap_entry (void);

/**
 * \brief RTC���̣�ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_rtc_entry (void);

/**
 * \brief PIT ��ʱ��ʵ��(32λ)��ʱ���ܵ����̣�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_pit_1_32bit_timing_entry (void);

/**
 * \brief PITʵ�ֱ�׼��ʱ��(32λ)���̣�ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_pit_1_32bit_timing_entry (void);

/**
 * \brief PITʵ�ֱ�׼��ʱ��(64λ)���̣�ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_pit_2_64bit_timing_entry (void);

/**
 * \brief LPTMRʵ�ֱ�׼��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_lptmr_timing_entry (void);

/**
 * \brief LPTMRʵ�ֶ�ʱ�����̣�ͨ��HW��ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_lptmr_timing_entry (void);

/**
 * \brief ADC��ѯ��ȡ����ֵ��ʹ��HW��ӿں���
 * \return ��
 */
void demo_amks16z_core_hw_adc_poll_entry (void);

/**
 * \brief �жϷ�ʽ��ȡ���������ADCת�������ͨ��HW��ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_adc_int_entry (void);

/**
 * \brief ADCӲ������ת����DMA����ת�������ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_adc_ht_entry (void);

/**
 * \brief adc���������DMA������
 * \return ��
 */
void demo_amks16z_core_std_adc_st_entry (void);

/**
 * \brief ADCӲ������ת����Ӳ��ƽ��ת�������DMA����ת�����
 * \return ��
 */
void demo_amks16z_core_std_adc_ht_avg_entry (void);

/**
 * \brief ADCӲ�������Ƚϣ�DMA����
 * \return ��
 */
void demo_amks16z_core_std_adc_ht_cmp_entry (void);

/**
 * \brief ADCӲ������ת����Ӳ��ƽ���Ƚ������DMA������
 * \return ��
 */
int demo_amks16z_core_std_adc_ht_avg_cmp_entry (void);

/**
 * \brief ADC������룬DMA���䣬�������
 * \return ��
 */
void demo_amks16z_core_std_adc_dif_st_entry (void);

/**
 * \brief adc���������DMA��������һ�β�������ADC������
 * \return ��
 */
void demo_amks16z_core_std_adc_descs_st_entry(void);

/**
 * \brief DMA�ڴ浽�ڴ�
 * \return ��
 */
void demo_amks16z_core_dr_dma_m2m_entry (void);

/**
 * \brief CMP�Ƚ���HW���ж�����
 * \return ��
 */
void demo_amks16z_core_hw_cmp_int_entry (void);

/**
 * \brief FTFA����,ͨ��������Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_dr_ftfa_entry (void);

/**
 * \brief  GPIOӲ��HW������
 * \return ��
 */
void demo_amks16z_core_hw_gpio_entry (void);

/**
 * \brief  FGPIOӲ��HW������
 * \return ��
 */
void demo_amks16z_core_hw_fgpio_entry (void);

/**
 * \brief  GPIOӲ��HW���ж�����
 * \return ��
 */
void demo_amks16z_core_hw_gpio_int_entry (void);

/**
 * \brief  GPIO��׼����
 * \return ��
 */
void demo_amks16z_core_std_gpio_entry (void);

/**
 * \brief  GPIO��׼�жϴ�������
 * \return ��
 */
void demo_amks16z_core_std_gpio_trigger_entry (void);

/**
 * \brief  ����Ӳ��HW���ѯ�շ�����
 * \return ��
 */
void demo_amks16z_core_hw_uart_polling_entry (void);

/**
 * \brief  ����Ӳ��HW���ж��շ�����
 * \retval ��
 */
void demo_amks16z_core_hw_uart_int_entry (void);

/**
 * \brief  ���ڱ�׼�ӿڲ�ѯ�շ�����
 * \return ��
 */
void demo_amks16z_core_std_uart_polling_entry (void);

/**
 * \brief  ���ڻ��λ���������
 * \return ��
 */
void demo_amks16z_core_std_uart_ringbuf_entry (void);

/**
 * \brief  ���ڽ���ʹ��DMA����
 * \return ��
 */
void demo_amks16z_core_hw_uart_rx_dma_entry (void);

/**
 * \brief  LED����
 * \return ��
 */
void demo_amks16z_core_std_led_entry (void);

/**
 * \brief i2c��дAM75ʾ����ͨ����׼�ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_i2c_lm75_entry (void);
/**
 * \brief i2c��дAM75ʾ����ͨ��hw��ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_i2c_master_poll_entry (void);

/**
 * \brief flash hw������
 * \return ��
 */
void demo_amks16z_core_hw_ftfa_entry (void);

/**
 * \brief flash ����������
 * \return ��
 */
void demo_amks16z_core_dr_ftfa_entry (void);

/**
 * \brief DAC�����ѹֵ������HW��ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_dac_entry (void);

/**
 * \brief DAC ʹ�û������ж�������Ҳ��źţ�HW��ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_dac_buf_int_entry (void);

/**
 * \brief DAC�����ѹ����׼�ӿڲ�ʵ��
 * \return ��
 */
void demo_amks16z_core_std_dac_entry (void);

/**
 * \brief DAC�����ѹ��DMA�������ݣ�HW��ӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_dac_dma_st_entry (void);

/**
 * \brief  TSI�������ж�����
 * \return ��
 */
void demo_amks16z_core_dr_tsi_int_entry (void);

/**
 * \brief  TSI HW���ж�����
 * \return ��
 */
void demo_amks16z_core_hw_tsi_int_entry (void);

/**
 * \brief  TSI HW������
 * \return ��
 */
void demo_amks16z_core_hw_tsi_entry (void);


/**
 * \brief  BME HW���װʽ�洢ָ��(gpio)����
 * \return ��
 */
void demo_amks16z_core_hw_bme_deco_stores_gpio_entry (void);

/**
 * \brief  BME HW���װʽ�洢ָ������
 * \return ��
 */
void demo_amks16z_core_hw_bme_deco_stores_entry (void);

/**
 * \brief  BME HW���װʽ����ָ������
 * \return ��
 */
void demo_amks16z_core_hw_bme_deco_loads_entry (void);


/**
 * \brief i2s���ݷ��ͣ�����HW��ӿں���ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_i2s_polling_entry (void);

/**
 * \brief i2s�ж����ݷ��ͣ�����HW��ӿں���ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_i2s_int_entry (void);

/**
 * \brief i2s dma��ʽ���ݷ��ͣ�����HW��ӿں���ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_i2s_dma_entry (void);

/**
* \brief buzzerʾ����ͨ����׼�ӿ�ʵ��
* \return ��
*/
void demo_amks16z_core_std_buzzer_entry (void);

/**
* \brief SPIʾ����ͨ����׼�ӿ�ʵ��(INT��ʽ)
* \return ��
*/
void demo_amks16z_core_std_spi_master_int_entry (void);

/**
* \brief SPIʾ����ͨ����׼�ӿ�ʵ��(DMA��ʽ)
* \return ��
*/
void demo_amks16z_core_std_spi_master_dma_entry (void);

/**
* \brief SPI����FLASHʾ����ͨ����׼�ӿ�ʵ��(INT��ʽ)
* \return ��
*/
void demo_amks16z_core_std_spi_flash_int_entry (void);

/**
* \brief SPI����FLASHʾ����ͨ����׼�ӿ�ʵ��(DMA��ʽ)
* \return ��
*/
void demo_amks16z_core_std_spi_flash_dma_entry (void);

/**
 * \brief WDT��ں�����HW��ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_wdt_entry (void);

/**
 * \brief ���Ź���ں�������׼�ӿڲ�ʵ��
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 * \return ��
 */
void demo_amks16z_core_std_wdt_entry (void);

/**
 * \brief PMUʾ����HW��ʵ��
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 * \return ��
 */
void demo_amks16z_core_std_pmu_lowpower_entry (void);

/**
 * \brief SPI�ӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_spi_slave_entry (void);

/**
 * \brief SPI�ӻ�ƥ���ж���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_spi_slave_match_entry (void);

/**
 * \brief SPI�ӻ�ͨ��DMA�������������ݣ�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_spi_slave_dma_entry (void);

/**
 * \brief SPI������ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_spi_master_entry (void);

/**
 * \brief SPI�ӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_spi_slave_irq_entry (void);

/**
 * \brief  ���ڷ���ʹ��DMA����
 * \return ��
 */
void demo_amks16z_core_hw_uart_tx_dma_entry (void);

/**
 * \brief UID�������
 */
void demo_amks16z_core_hw_sim_uid_entry (void);

/**
 * \brief ���氲ȫ��Կ�������
 */
void demo_amks16z_core_hw_backdoor_sec_entry (void);

/**
 * \brief AMetal Ӧ�ó������
 */
void demo_amks16z_core_hw_rtc_sec_int_entry (void);

/**
 * \brief MiniPort-View + MiniPort-595 �¶���ʾ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_hc595_digitron_temp_interface_entry (void);

/**
 * \brief MiniPort-LED ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_led_entry (void);

/**
 * \brief MiniPort-VIEW ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_digitron_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-LED ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_hc595_led_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-VIEW ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_hc595_digitron_entry (void);

/**
 * \brief MiniPort-KEY
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_key_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-KEY ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_hc595_digitron_key_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-VIEW + LM75 �¶���ʾ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_hc595_digitron_temp_entry (void);

/**
 * \brief MiniPort-ZLG72128��ʾ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_zlg72128_entry (void);

/**
 * \brief MiniPort-KEY + MiniPort-DIGITORN��ʾ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_miniport_key_digitron_entry (void);

/**
 * \brief MicroPort DS1302 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_ds1302_entry (void);

/**
 * \brief MicroPort EEPROM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_eeprom_entry (void);

/**
 * \brief MicroPort EEPROM ���̣�ͨ�� NVRAM �ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_eeprom_nvram_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_flash_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ�� MTD �ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_flash_mtd_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ�� FTL �ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_flash_ftl_entry (void);

/**
 * \brief MicroPort RS485 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_rs485_entry (void);

/**
 * \brief MicroPort RTC ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_rtc_entry (void);

/**
 * \brief MicroPort RX8025T ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_rx8025t_entry (void);

/**
 * \brief MicroPort USB ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_amks16z_core_microport_usb_entry (void);


/* end of file */
