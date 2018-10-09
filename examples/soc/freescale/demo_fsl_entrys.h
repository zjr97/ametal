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
 * \brief fslϵ�������������������̺����������
 * \sa    demo_fsl_entrys.h
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  lnk, first implementation.
 * \endinternal
 */

#include "hw/amhw_fsl_adc.h"
#include "hw/amhw_fsl_bme.h"
#include "hw/amhw_fsl_cmp.h"
#include "hw/amhw_fsl_dac.h"
#include "hw/amhw_kl26_dma.h"
#include "hw/amhw_fsl_ftfa.h"
#include "hw/amhw_fsl_i2c.h"
#include "hw/amhw_fsl_i2s.h"
#include "hw/amhw_fsl_llwu.h"
#include "hw/amhw_fsl_lptmr.h"
#include "hw/amhw_kl26_mcm.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "hw/amhw_fsl_pit.h"
#include "hw/amhw_fsl_pmc.h"
#include "hw/amhw_fsl_rcm.h"
#include "hw/amhw_fsl_rtc.h"
#include "hw/amhw_fsl_smc.h"
#include "hw/amhw_fsl_spi.h"
#include "hw/amhw_fsl_tpm.h"
#include "hw/amhw_fsl_tsi.h"
#include "hw/amhw_fsl_uart.h"

#include "am_dac.h"
#include "am_adc.h"
#include "am_i2c.h"
#include "am_spi.h"
#include "am_pwm.h"

/**
 * \brief ADC Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num   : �жϺ�
 * \param[in] chan      : ���Ŷ�Ӧ�� ADC ͨ����
 * \param[in] clk_bus   : ����ʱ��
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_fsl_hw_adc_int_entry (amhw_fsl_adc_t     *p_hw_adc,
                                int                 int_num,
                                amhw_fsl_adc_chan_t chan,
                                uint32_t            clk_bus,
                                uint32_t            vref_mv);

/**
 * \brief ADC��ѯ��ȡ����ֵ��ʹ��HW��ӿں���
 *
 * \param[in] p_hw_adc  : ָ�� ADC ����Ĵ������ָ��
 * \param[in] int_num   : �жϺ�
 * \param[in] chan      : ���Ŷ�Ӧ�� ADC ͨ����
 * \param[in] clk_bus   : ����ʱ��
 * \param[in] vref_mv   : ADC�ο���ѹ�����Խ�ADC�������ת��Ϊ��ѹֵ��ʾ
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_fsl_hw_adc_poll_entry (amhw_fsl_adc_t     *p_hw_adc,
                                 amhw_fsl_adc_chan_t chan,
                                 uint32_t            clk_bus,
                                 uint32_t            vref_mv);

/**
 * \brief adc���������DMA��������һ�β�������ADC������
 *
 * \param[in] adc0_handle  : ADC���
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_fsl_std_adc_descs_st_entry(am_adc_handle_t adc0_handle);

/**
 * \brief ADC������룬DMA���䣬�������
 *
 * \param[in] adc0_handle  : ADC���
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� ADC ģ����Ӧ��ʱ�ӣ�
 * ���� ADC ͨ����Ӧ�����ţ���Щ���ö������оƬ��ء�
 *
 * \return ��
 */
void demo_fsl_std_adc_dif_st_entry (am_adc_handle_t adc0_handle);

/**
 * \brief  BME HW���װʽ����ָ������
 * \return ��
 */
void demo_kl26_hw_bme_deco_loads_entry (void);

/**
 * \brief  BME HW���װʽ�洢ָ��(gpio)����
 * \return ��
 */
void demo_kl26_hw_bme_deco_stores_gpio_entry (void);

/**
 * \brief  BME HW���װʽ�洢ָ������
 * \return ��
 */
void demo_kl26_hw_bme_deco_stores_entry (void);

/**
 * \brief CMP�Ƚ���HW���ж�����
 *
 * \param[in] p_hw_cmp  : ָ�� cmp �Ĵ������ָ��
 * \param[in] inum      : �жϺ�
 *
 * \return ��
 */
void demo_fsl_hw_cmp_int_entry (amhw_fsl_cmp_t *p_hw_cmp,
                                int             inum);

/**
 * \brief DAC ʹ�û������ж�������Ҳ��źţ�HW��ʵ��
 *
 * \param[in] p_hw_dac  : ָ�� DAC �Ĵ������ָ��
 * \param[in] inum      : �жϺ�
 *
 * \return ��
 */
void demo_fsl_hw_dac_buf_int_entry (amhw_fsl_dac_t *p_hw_dac,
                                    int             inum);

/**
 * \brief DAC�����ѹ��DMA�������ݣ�HW��ӿ�ʵ��
 * \return ��
 */
void demo_kl26_hw_dac_dma_st_entry (void);

/**
 * \brief DAC�����ѹֵ������HW��ʵ��
 *
 * \param[in] p_hw_dac  : ָ�� DAC �Ĵ������ָ��
 * \param[in] voltage_mv: ʹDAC����ĵ�ѹֵ(��λ:mv)
 *
 * \return ��
 */
void demo_fsl_hw_dac_entry (amhw_fsl_dac_t *p_hw_dac,
                            uint16_t        mv_out);

/**
 * \brief DAC�����ѹ����׼�ӿڲ�ʵ��
 *
 * \param[in] p_hw_dac  : ָ�� DAC �Ĵ������ָ��
 * \param[in] voltage_mv: ʹDAC����ĵ�ѹֵ(��λ:mv)
 *
 * \return ��
 */
void demo_fsl_std_dac_entry (am_dac_handle_t dac0_handle,
                             uint32_t        mv_out);

/**
 * \brief DMA�ڴ浽�ڴ�
 * \return ��
 */
void demo_kl26_dr_dma_m2m_entry (void);

/**
 * \brief FTFA����,ͨ��������Ľӿ�ʵ��
 *
 * \param[in] p_hw_ftfa  : ָ�� FTFA �Ĵ������ָ��
 *
 * \return ��
 */
void demo_fsl_dr_ftfa_entry (amhw_fsl_ftfa_t *p_hw_ftfa);

/**
 * \brief FTFA����,ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] p_hw_ftfa  : ָ�� FTFA �Ĵ������ָ��
 *
 * \return ��
 */
void deme_fsl_hw_ftfa_entry (amhw_fsl_ftfa_t *p_hw_ftfa);

/**
 * \brief  FGPIOӲ��HW������
 * \return ��
 */
void demo_kl26_hw_fgpio_entry (void);

/**
 * \brief  GPIOӲ��HW���ж�����
 * \return ��
 */
void demo_kl26_hw_gpio_int_entry (void);

/**
 * \brief  GPIOӲ��HW������
 * \return ��
 */
void demo_kl26_hw_gpio_entry (void);

/**
 * \brief i2c��дAM75ʾ����ͨ��hw��ӿ�ʵ��
 *
 * \param[in] p_hw_i2c  : ָ�� I2C �Ĵ������ָ��
 * \param[in] i2c_clk   : I2Cʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_i2c_master_poll_entry (amhw_fsl_i2c_t *p_hw_i2c,
                                        uint32_t        i2c_clk);

/**
 * \brief i2s dma��ʽ���ݷ��ͣ�����HW��ӿں���ʵ��
 * \return ��
 */
void demo_kl26_hw_i2s_dma_entry (void);

/**
 * \brief i2s�ж����ݷ��ͣ�����HW��ӿں���ʵ��
 *
 * \param[in] p_hw_i2s    : ָ�� I2S �Ĵ������ָ��
 * \param[in] inum_i2s    : �жϺ�
 * \param[in] p_i2s0_clk  : I2S����ʱ��
 *
 * \return ��
 */
void demo_fsl_hw_i2s_int_entry (amhw_fsl_i2s_t           *p_hw_i2s,
                                int                       inum_i2s,
                                amhw_fsl_i2s_clock_cfg_t *p_i2s0_clk);

/**
 * \brief i2s���ݷ��ͣ�����HW��ӿں���ʵ��
 *
 * \param[in] p_hw_i2s    : ָ�� I2S �Ĵ������ָ��
 * \param[in] p_i2s0_clk  : I2S����ʱ��
 *
 * \return ��
 */
void demo_fsl_hw_i2s_polling_entry (amhw_fsl_i2s_t           *p_hw_i2s,
                                    amhw_fsl_i2s_clock_cfg_t *p_i2s0_clk);

/**
 * \brief LPTMRʵ�ֶ�ʱ�����̣�ͨ��HW��ӿ�ʵ��
 *
 * \param[in] p_hw_lptmr    : ָ�� lptmr �Ĵ������ָ��
 * \param[in] inum        : �жϺ�
 * \param[in] lptmr_clock : lptmrʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_lptmr_timing_entry (amhw_fsl_lptmr_t *p_hw_lptmr,
                                     int               inum,
                                     uint32_t          lptmr_clock);

/**
 * \brief PIT ��ʱ��ʵ��(32λ)��ʱ���ܵ����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] p_hw_pit    : ָ�� pit �Ĵ������ָ��
 * \param[in] inum        : �жϺ�
 * \param[in] pit_clk     : pitʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_pit_1_32bit_timing_entry (amhw_fsl_pit_t *p_hw_pit,
                                           int             inum,
                                           uint32_t        pit_clk);

/**
 * \brief PMUʾ����HW��ʵ��
 *
 * \note ���Կ��Ź�����ʱ�뽫am_prj_config.h�ļ��еĺ�AM_CFG_SIM_COP��Ϊ1
 *
 * \return ��
 */
void demo_kl26_std_pmu_lowpower_entry (void);

/**
 * \brief RTCʾ���� HW��ʵ��
 *
 * \param[in] p_hw_rtc    : ָ�� rtc �Ĵ������ָ��
 *
 * \return ��
 */
void demo_fsl_hw_rtc_sec_int_entry (amhw_fsl_rtc_t *p_hw_rtc);

/**
 * \brief ���氲ȫ��Կ�������
 *
 * \param[in] p_hw_ftfa    : ָ�� ftfa �Ĵ������ָ��
 * \param[in] uart_handle  : uart ���ھ��
 *
 * \return ��
 */
void demo_fsl_hw_backdoor_sec_entry (amhw_fsl_ftfa_t *p_hw_ftfa,
                                     am_uart_handle_t uart_handle);

/**
 * \brief UID�������
 */
void demo_kl26_hw_sim_uid_entry (void);

/**
 * \brief SPI������ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] p_hw_spi    : ָ�� spi �Ĵ������ָ��
 * \param[in] pin_cs      : spiƬѡ����
 * \param[in] spi_freq    : spi ����ʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_spi_master_entry (amhw_fsl_spi_t *p_hw_spi,
                                   int             pin_cs,
                                   uint32_t        spi_freq);
/**
 * \brief SPI�ӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] p_hw_spi0    : ָ��ӻ� spi0 �Ĵ������ָ��
 * \param[in] p_hw_spi1    : ָ������ spi1 �Ĵ������ָ��
 * \param[in] slave_inum   : �ӻ��жϺ�
 * \param[in] spi_freq     : spi ��������ʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_spi_slave_irq_entry (amhw_fsl_spi_t *p_hw_spi0,
                                      amhw_fsl_spi_t *p_hw_spi1,
                                      int             slave_inum,
                                      uint32_t        spi_freq);

/**
 * \brief SPI�ӻ�ƥ���ж���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] p_hw_spi0    : ָ��ӻ� spi0 �Ĵ������ָ��
 * \param[in] p_hw_spi1    : ָ������ spi1 �Ĵ������ָ��
 * \param[in] slave_inum   : �ӻ��жϺ�
 * \param[in] spi_freq     : spi ��������ʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_spi_slave_match_entry (amhw_fsl_spi_t *p_hw_spi0,
                                        amhw_fsl_spi_t *p_hw_spi1,
                                        int             slave_inum,
                                        uint32_t        spi_freq);

/**
 * \brief SPI�ӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] p_hw_spi    : ָ��ӻ� spi �Ĵ������ָ��
 *
 * \return ��
 */
void demo_fsl_hw_spi_slave_entry (amhw_fsl_spi_t *p_hw_spi);

/**
 * \brief TPMʵ�ֲ����ܣ�ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] tpm2_pwm_handle    : pwm��׼���
 * \param[in] p_hw_tpm           : ָ��tpm �Ĵ������ָ��
 * \param[in] inum               : �жϺ�
 * \param[in] tpm_clock          : tpm ʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_tpm_cap_entry (am_pwm_handle_t  tpm2_pwm_handle,
                                amhw_fsl_tpm_t  *p_hw_tpm,
                                int              inum,
                                uint32_t         tpm_clock);

/**
 * \brief TPMʵ��PWM���ܣ�ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] p_hw_tpm           : ָ��tpm �Ĵ������ָ��
 * \param[in] clkfreq            : tpm ʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_tpm_pwm_entry (amhw_fsl_tpm_t *p_hw_tpm,
                                uint32_t        clkfreq);

/**
 * \brief TPMʵ�ֱ�׼��ʱ�����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * \param[in] p_hw_tpm       : ָ��tpm �Ĵ������ָ��
 * \param[in] freq           : tpm��ʱ���ж�Ƶ��
 * \param[in] inum           : �жϺ�
 * \param[in] tpm_clock      : tpm ʱ��Ƶ��
 *
 * \return ��
 */
void demo_fsl_hw_tpm_timing_entry (amhw_fsl_tpm_t *p_hw_tpm,
                                   uint32_t        freq,
                                   int             inum,
                                   uint32_t        tpm_clk);
/**
 * \brief  TSI�������ж�����
 * \return ��
 */
void demo_fsl_dr_tsi_int_entry (void);

/**
 * \brief  TSI HW���ж�����
 *
 * \param[in] p_hw_tsi       : ָ��tsi �Ĵ������ָ��
 * \param[in] inum           : �жϺ�
 *
 * \return ��
 */
void demo_fsl_hw_tsi_int_entry (amhw_fsl_tsi_t *p_hw_tsi,
                                int             inum);

/**
 * \brief  TSI HW������
 *
 * \param[in] p_hw_tsi       : ָ��tsi �Ĵ������ָ��
 *
 * \return ��
 */
void demo_fsl_hw_tsi_entry (amhw_fsl_tsi_t *p_hw_tsi);

/**
 * \brief  ����Ӳ��HW���ж��շ�����
 *
 * \param[in] p_hw_uart   : ָ�� uart �Ĵ������ָ��
 * \param[in] inum        : �жϺ�
 * \param[in] uart_clk    : uart����ʱ��
 * \param[in] uart0_flog  : ���ʹ��UART0�����ֵΪ1������Ϊ0
 *
 * \retval ��
 */
void demo_fsl_hw_uart_int_entry (amhw_fsl_uart_t *p_hw_uart,
                                 int              inum,
                                 uint32_t         uart_clk,
                                 am_bool_t        uart0_flog);

/**
 * \brief  ����Ӳ��HW���ѯ�շ�����
 *
 * \param[in] p_hw_uart   : ָ�� uart �Ĵ������ָ��
 * \param[in] uart_clk    : uart����ʱ��
 * \param[in] uart0_flog  : ���ʹ��UART0�����ֵΪ1������Ϊ0
 *
 * \return ��
 */
void demo_fsl_hw_uart_polling_entry (amhw_fsl_uart_t *p_hw_uart,
                                     uint32_t         uart_clk,
                                     am_bool_t        uart0_flog);

/**
 * \brief  ���ڽ���ʹ��DMA����
 * \return ��
 */
void demo_kl26_hw_uart_rx_dma_entry (void);

/**
 * \brief  ���ڷ���ʹ��DMA����
 * \return ��
 */
void demo_kl26_hw_uart_tx_dma_entry (void);

/**
 * \brief WDT��ں�����HW��ʵ��
 * \return ��
 */
void demo_kl26_hw_wdt_entry (void);

/**
 * \brief MiniPort-View + MiniPort-595 �¶���ʾ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_hc595_digitron_temp_interface_entry (void);

/**
 * \brief MiniPort-LED ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_led_entry (void);

/**
 * \brief MiniPort-VIEW ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_digitron_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-LED ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_hc595_led_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-VIEW ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_hc595_digitron_entry (void);

/**
 * \brief MiniPort-KEY
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_key_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-KEY ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_hc595_digitron_key_entry (void);

/**
 * \brief MiniPort-595 + MiniPort-VIEW + LM75 �¶���ʾ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_hc595_digitron_temp_entry (void);

/**
 * \brief MiniPort-ZLG72128��ʾ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_zlg72128_entry (void);

/**
 * \brief MiniPort-KEY + MiniPort-DIGITORN��ʾ����
 *
 * \param ��
 *
 * \return ��
 */
void demo_miniport_key_digitron_entry (void);

/**
 * \brief MicroPort DS1302 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_ds1302_entry (void);

/**
 * \brief MicroPort EEPROM ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_eeprom_entry (void);

/**
 * \brief MicroPort EEPROM ���̣�ͨ�� NVRAM �ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_eeprom_nvram_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_flash_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ�� MTD �ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_flash_mtd_entry (void);

/**
 * \brief MicroPort FLASH ���̣�ͨ�� FTL �ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_flash_ftl_entry (void);

/**
 * \brief MicroPort RS485 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_rs485_entry (void);

/**
 * \brief MicroPort RTC ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_rtc_entry (void);

/**
 * \brief MicroPort RX8025T ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_rx8025t_entry (void);

/**
 * \brief MicroPort USB ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_microport_usb_entry (void);

/* end of file */
