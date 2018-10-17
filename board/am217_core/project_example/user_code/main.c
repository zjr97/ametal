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
 * \brief ZLG217 ģ�幤��
 *
 * - ʵ������:
 *   ģ������:LED0��1���Ƶ����˸; demo�������:���demo��ں����ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-07  nwt, first implementation
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "demo_am217_core_entries.h"

int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");
    /*
     * ����Ϊ����demo����ں�������Ҫ�����ĸ�demo����ȡ����Ӧ���������е�ע��
     *
     * Ĭ�����е���LED��˸ demo
     *
     * ע�⣺ͬһʱ��ֻ������һ�� demo����ֻ��ʹĳһ�д���ȡ��ע��״̬
     */

	  demo_zlg217_core_std_led_entry();
//    demo_zlg217_core_std_delay_entry();
//    demo_zlg217_core_std_adc_entry();
//    demo_zlg217_core_hw_adc_int_entry();
//    demo_zlg217_core_std_buzzer_entry();
//    demo_zlg217_core_std_crc_entry();
//    demo_zlg217_core_drv_dma_m2m_entry();
//    demo_zlg217_core_drv_flash_entry();
//    demo_zlg217_core_hw_gpio_entry();
//    demo_zlg217_core_hw_gpio_trigger_entry();
//    demo_zlg217_core_std_gpio_entry();
//    demo_zlg217_core_std_gpio_trigger_entry();
//    demo_zlg217_core_hw_i2c_master_poll_entry();
//    demo_zlg217_core_hw_i2c_slave_poll_entry();
//    demo_zlg217_core_std_i2c_lm75_entry();
//    demo_zlg217_core_std_i2c_master_async_entry();
//    demo_zlg217_core_std_i2c_master_sync_entry();
//    demo_zlg217_core_std_key_input_event_entry();
//    demo_zlg217_core_hw_iwdg_entry();
//    demo_zlg217_core_std_iwdg_entry();
//    demo_zlg217_core_std_led_entry();
//    demo_zlg217_core_microport_ds1302_entry();
//    demo_zlg217_core_microport_eeprom_entry();
//    demo_zlg217_core_microport_eeprom_nvram_entry();
//    demo_zlg217_core_microport_flash_entry();
//    demo_zlg217_core_microport_flash_ftl_entry();
//    demo_zlg217_core_microport_flash_mtd_entry();
//    demo_zlg217_core_microport_rs485_entry();
//    demo_zlg217_core_microport_rtc_entry();
//    demo_zlg217_core_microport_rx8025t_entry();
//    demo_zlg217_core_miniport_digitron_entry();
//    demo_zlg217_core_miniport_hc595_digitron_entry();
//    demo_zlg217_core_miniport_hc595_digitron_key_entry();
//    demo_zlg217_core_miniport_hc595_digitron_temp_entry();
//    demo_zlg217_core_miniport_hc595_led_entry();
//    demo_zlg217_core_miniport_key_entry();
//    demo_zlg217_core_miniport_key_digitron_entry();
//    demo_zlg217_core_miniport_led_entry();
//    demo_zlg217_core_miniport_zlg72128_entry();
//    demo_zlg217_core_std_rtc_entry();
//    demo_zlg217_core_hw_spi_master_entry();
//    demo_zlg217_core_std_spi_master_dma_entry();
//    demo_zlg217_core_std_spi_master_int_entry();
//    demo_zlg217_core_hw_tim_cap_entry();
//    demo_zlg217_core_std_tim1_cap_entry();
//    demo_zlg217_core_std_tim2_cap_entry();
//    demo_zlg217_core_std_tim3_cap_entry();
//    demo_zlg217_core_std_tim4_cap_entry();
//    demo_zlg217_core_hw_tim_cmp_toggle_entry();
//    demo_zlg217_core_hw_tim_pwm_entry();
//    demo_zlg217_core_std_tim1_pwm_entry();
//    demo_zlg217_core_std_tim2_pwm_entry();
//    demo_zlg217_core_std_tim3_pwm_entry();
//    demo_zlg217_core_std_tim4_pwm_entry();
//    demo_zlg217_core_hw_tim_timing_entry();
//    demo_zlg217_core_std_tim1_timing_entry();
//    demo_zlg217_core_std_tim2_timing_entry();
//    demo_zlg217_core_std_tim3_timing_entry();
//    demo_zlg217_core_std_tim4_timing_entry();
//    demo_zlg217_core_hw_uart_int_entry();
//    demo_zlg217_core_hw_uart_polling_entry();
//    demo_zlg217_core_hw_uart_rx_dma_entry();
//    demo_zlg217_core_hw_uart_tx_dma_entry();
//    demo_zlg217_core_std_uart_polling_entry();
//    demo_zlg217_core_std_uart_ringbuf_entry();
//    demo_zlg217_core_hw_wwdg_entry();
//    demo_zlg217_core_std_wwdg_entry();
//    demo_bma253_entry();
//    demo_lsm6dsl_entry();
//    demo_ltr_553als_entry();
//    demo_bh1730fvc_entry();
//    demo_bmp280_entry();
//    demo_lps22hb_entry();
//    demo_bmg160_entry();
//    demo_bme280_entry();
//    demo_mmc5883ma_entry();
//    demo_lis3mdl_entry();
//    demo_shtc1_entry();
//    demo_hts221_entry();
//    demo_sc16is7xx_entry();
    while (1) {
    }
}

/* end of file */
