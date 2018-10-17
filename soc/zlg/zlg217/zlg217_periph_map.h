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
 * \brief ZLG217 ����ӳ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG217_PERIPH_MAP_H
#define __AMHW_ZLG217_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zlg217_regbase.h"

#include "hw/amhw_zlg_adc.h"
#include "hw/amhw_zlg_bkp.h"
#include "hw/amhw_zlg_cmp.h"
#include "hw/amhw_zlg_crc.h"
#include "hw/amhw_zlg_dac.h"
#include "hw/amhw_zlg_flash.h"
#include "hw/amhw_zlg_i2c.h"
#include "hw/amhw_zlg_spi.h"
#include "hw/amhw_zlg_tim.h"
#include "hw/amhw_zlg_uart.h"
#include "hw/amhw_zlg_iwdg.h"
#include "hw/amhw_zlg_wwdg.h"
#include "hw/amhw_zlg_pwr.h"
#include "hw/amhw_zlg_exti.h"
#include "hw/amhw_zlg_syscfg.h"
#include "hw/amhw_zlg_gpio.h"
#include "hw/amhw_zlg_dma.h"


/**
 * \addtogroup amhw_zlg217_if_periph_map
 * \copydoc amhw_zlg217_periph_map.h
 * @{
 */

/**
 * \name ���趨��
 * @{
 */

/** \brief GPIO�˿�A�Ĵ�����ָ�� */
#define ZLG217_GPIOA   ((amhw_zlg217_gpio_reg_t  *)ZLG217_GPIOA_BASE)

/** \brief GPIO�˿�B�Ĵ�����ָ�� */
#define ZLG217_GPIOB   ((amhw_zlg217_gpio_reg_t  *)ZLG217_GPIOB_BASE)

/** \brief GPIO�˿�C�Ĵ�����ָ�� */
#define ZLG217_GPIOC   ((amhw_zlg217_gpio_reg_t  *)ZLG217_GPIOC_BASE)

/** \brief GPIO�˿�D�Ĵ�����ָ�� */
#define ZLG217_GPIOD   ((amhw_zlg217_gpio_reg_t  *)ZLG217_GPIOD_BASE)

/** \brief GPIO�˿�E�Ĵ�����ָ�� */
#define ZLG217_GPIOE   ((amhw_zlg217_gpio_reg_t  *)ZLG217_GPIOE_BASE)

/** \brief GPIO�Ĵ�����ָ�� */
#define ZLG217_GPIO    ((amhw_zlg217_gpio_t      *)ZLG217_GPIO_BASE)

/** \brief AFIO�Ĵ�����ָ�� */
#define ZLG217_AFIO    ((amhw_zlg217_afio_t      *)ZLG217_AFIO_BASE)

/** \brief TIM1�Ĵ�����ָ�� */
#define ZLG217_TIM1    ((amhw_zlg_tim_t          *)ZLG217_TIM1_BASE)

/** \brief ͨ�ö�ʱ��2�Ĵ�����ָ�� */
#define ZLG217_TIM2    ((amhw_zlg_tim_t          *)ZLG217_TIM2_BASE)

/** \brief ͨ�ö�ʱ��3�Ĵ�����ָ�� */
#define ZLG217_TIM3    ((amhw_zlg_tim_t          *)ZLG217_TIM3_BASE)

/** \brief ͨ�ö�ʱ��4�Ĵ�����ָ�� */
#define ZLG217_TIM4    ((amhw_zlg_tim_t          *)ZLG217_TIM4_BASE)

/** \brief RTC�Ĵ�����ָ�� */
#define ZLG217_RTC     ((amhw_zlg217_rtc_t       *)ZLG217_RTC_BASE)

/** \brief ��Դ����PWR�Ĵ�����ָ�� */
#define ZLG217_PWR     ((amhw_zlg_pwr_t          *)ZLG217_PWR_BASE)

/** \brief ���ݿ���BKP�Ĵ�����ָ�� */
#define ZLG217_BKP     ((amhw_zlg217_bkp_t       *)ZLG217_BKP_BASE)

/** \brief UART1 �Ĵ�����ָ�� */
#define ZLG217_UART1   ((amhw_zlg_uart_t         *)ZLG217_UART1_BASE)

/** \brief UART2 �Ĵ�����ָ�� */
#define ZLG217_UART2   ((amhw_zlg_uart_t         *)ZLG217_UART2_BASE)

/** \brief UART3 �Ĵ�����ָ�� */
#define ZLG217_UART3   ((amhw_zlg_uart_t         *)ZLG217_UART3_BASE)

/** \brief ADC1 �Ĵ�����ָ�� */
#define ZLG217_ADC1    ((amhw_zlg_adc_t          *)ZLG217_ADC1_BASE)

/** \brief ADC2 �Ĵ�����ָ�� */
#define ZLG217_ADC2    ((amhw_zlg_adc_t          *)ZLG217_ADC2_BASE)

/** \brief DAC �Ĵ�����ָ�� */
#define ZLG217_DAC     ((amhw_zlg_dac_t          *)ZLG217_DAC_BASE)

/** \brief DMA �Ĵ�����ָ�� */
#define ZLG217_DMA     ((amhw_zlg217_dma_t       *)ZLG217_DMA_BASE)

/** \brief RCC�������Ĵ�����ָ�� */
#define ZLG217_RCC     ((amhw_zlg217_rcc_t       *)ZLG217_RCC_BASE)

/** \brief SPI1�������Ĵ�����ָ�� */
#define ZLG217_SPI1    ((amhw_zlg_spi_t          *)ZLG217_SPI1_BASE)

/** \brief SPI2�������Ĵ�����ָ�� */
#define ZLG217_SPI2    ((amhw_zlg_spi_t          *)ZLG217_SPI2_BASE)

/** \brief I2C1�Ĵ�����ָ�� */
#define ZLG217_I2C1    ((amhw_zlg_i2c_t          *)ZLG217_I2C1_BASE)

/** \brief I2C2�Ĵ�����ָ�� */
#define ZLG217_I2C2    ((amhw_zlg_i2c_t          *)ZLG217_I2C2_BASE)

/** \brief IWDG�������Ĵ�����ָ�� */
#define ZLG217_IWDG    ((amhw_zlg_iwdg_t         *)ZLG217_IWDG_BASE)

/** \brief WWDG�������Ĵ�����ָ�� */
#define ZLG217_WWDG    ((amhw_zlg_wwdg_t         *)ZLG217_WWDG_BASE)

/** \brief CAN�������Ĵ�����ָ�� */
#define ZLG217_CAN     ((amhw_zlg217_can_t       *)ZLG217_CAN_BASE)

/** \brief USB�������Ĵ�����ָ�� */
#define ZLG217_USB     ((amhw_zlg217_usb_t       *)ZLG217_USB_BASE)

/** \brief �ⲿ�ж�(�¼�)������EXTI�Ĵ�����ָ�� */
#define ZLG217_EXTI    ((amhw_zlg217_exti_t      *)ZLG217_EXTI_BASE)

/** \brief FLASH�Ĵ�����ָ�� */
#define ZLG217_FLASH   ((amhw_zlg_flash_t        *)ZLG217_FLASH_BASE)

/** \brief CRC�Ĵ�����ָ�� */
#define ZLG217_CRC     (amhw_zlg_crc_t           *)(ZLG217_CRC_BASE)

/** @} */

/**
 * @} amhw_zlg217_if_periph_map
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG217_REG_BASE_H */

/* end of file */
