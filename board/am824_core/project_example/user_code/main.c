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
 * \brief LPC82X ģ�幤��
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-07  nwt, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_led.h"
#include "demo_am824_core_entries.h"
/**
 * \brief AMetal Ӧ�ó������
 */
void am_main (void) 
{
    AM_DBG_INFO("Start up successful!\r\n");
    /*
     * ����Ϊ����demo����ں�������Ҫ�����ĸ� demo�� ��ȡ����Ӧ���������е�ע��
     *
     * Ĭ�����е���LED��˸ demo��
     *
     * ע�⣺ͬһʱ��ֻ������һ�� demo����ֻ��ʹĳһ�д���ȡ��ע��״̬��
     */

   demo_am824_core_std_led_entry();
   //demo_am824_core_std_wwdt_entry();
   //demo_am824_core_hw_wwdt_entry();
   //demo_am824_core_hw_acmp_int_entry();
   //demo_am824_core_hw_acmp_lad_entry();
   //demo_am824_core_hw_acmp_poll_entry();
   //demo_am824_core_hw_adc_dma_entry();
   //demo_am824_core_hw_adc_thcmp_entry();
   //demo_am824_core_std_adc_dma_int_entry();
   //demo_am824_core_std_adc_dma_poll_entry();
   //demo_am824_core_std_adc_int_entry();
   //demo_am824_core_std_adc_ntc_entry();
   //demo_am824_core_std_adc_poll_entry();
   //demo_am824_core_std_buzzer_entry();
   //demo_am824_core_hw_crc_entry();
   //demo_am824_core_std_crc_entry();
   //demo_am824_core_drv_dma_hwtrigger_burst_entry();
   //demo_am824_core_drv_dma_m2m_entry();
   //demo_am824_core_drv_dma_ping_pong_entry();
   //demo_am824_core_hw_flash_ctrl_entry();
   //demo_am824_core_hw_gpio_entry();
   //demo_am824_core_hw_gpio_int_entry();
   //demo_am824_core_hw_gpio_pmatch_entry();
   //demo_am824_core_std_gpio_entry();
   //demo_am824_core_std_gpio_int_entry();
   //demo_am824_core_std_gpio_key_entry();
   //demo_am824_core_hw_i2c_master_dma_entry();
   //demo_am824_core_hw_i2c_master_poll_entry();
   //demo_am824_core_hw_i2c_slave_dma_entry();
   //demo_am824_core_hw_i2c_slave_int_entry();
   //demo_am824_core_hw_i2c_slave_poll_entry();
   //demo_am824_core_std_i2c_lm75_entry();
   //demo_am824_core_std_i2c_master_sync_entry();
   //demo_am824_core_std_i2c_master_async_entry();
   //demo_am824_core_hw_iap_entry();
   //demo_am824_core_std_key_input_event_entry();
   //demo_am824_microport_eeprom_entry();
   //demo_am824_microport_eeprom_nvram_entry();
   //demo_am824_microport_rs485_entry();
   //demo_am824_core_miniport_hc595_led_entry();
   //demo_am824_core_miniport_key_entry();
   //demo_am824_core_miniport_key_digitron_entry();
   //demo_am824_core_miniport_led_entry();
   //demo_am824_core_miniport_zlg72128_entry();
   //demo_am824_core_hw_mrt_entry();
   //demo_am824_core_std_mrt_timer_entry();
   //demo_am824_core_hw_pll_entry();
   //demo_am824_core_hw_pmu_deeppowerdown_entry();
   //demo_am824_core_hw_pmu_deepsleep_entry();
   //demo_am824_core_hw_pmu_powerdown_entry();
   //demo_am824_core_hw_pmu_sleep_entry();
   //demo_am824_core_drv_sct_timing_pwm_entry();
   //demo_am824_core_hw_sct_1_32bit_pwm_entry();
   //demo_am824_core_hw_sct_1_32bit_timing_entry();
   //demo_am824_core_hw_sct_2_16bit_pwm_entry();
   //demo_am824_core_hw_sct_2_16bit_timing_entry();
   //demo_am824_core_hw_sct_cap_entry();
   //demo_am824_core_hw_sct_multi_states_entry();
   //demo_am824_core_std_sct_cap_entry();
   //demo_am824_core_std_sct_pwm_entry();
   //demo_am824_core_std_sct_timer_entry();
   //demo_am824_core_hw_spi_master_entry();
   //demo_am824_core_hw_spi_slave_entry();
   //demo_am824_core_hw_spi_slave_dma_entry();
   //demo_am824_core_std_spi_master_dma_entry();
   //demo_am824_core_std_spi_master_int_entry();
   //demo_am824_core_hw_bod_entry();
   //demo_am824_core_hw_clkout_entry();
   //demo_am824_core_std_delay_entry();
   //demo_am824_core_std_systick_timer_entry();
   //demo_am824_core_hw_usart_autobaud_entry();
   //demo_am824_core_hw_usart_poll_entry();
   //demo_am824_core_hw_usart_rx_dma_entry();
   //demo_am824_core_hw_usart_tx_dma_entry();
   //demo_am824_core_std_usart_flowctrl_entry();
   //demo_am824_core_std_usart_poll_entry();
   //demo_am824_core_std_usart_rngbuf_entry();
   //demo_am824_core_hw_wkt_deeppowerdown_wakeup_entry();
   //demo_am824_core_hw_wkt_timer_entry();
   //demo_am824_core_std_wkt_timer_entry();
    while(1) {
        ;
    }
}

/* end of file */
