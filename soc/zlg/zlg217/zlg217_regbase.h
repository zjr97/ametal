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
 * \brief ZLG217 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __ZLG217_REGBASE_H
#define __ZLG217_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zlg217_if_regbase
 * \copydoc zlg217_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

/** \brief GPIO����ַ */
#define ZLG217_GPIO_BASE              (0x40010800UL)

/** \brief GPIOA����ַ */
#define ZLG217_GPIOA_BASE             (0x40010800UL)

/** \brief GPIOB����ַ */
#define ZLG217_GPIOB_BASE             (0x40010C00UL)

/** \brief GPIOC����ַ */
#define ZLG217_GPIOC_BASE             (0x40011000UL)

/** \brief GPIOD����ַ */
#define ZLG217_GPIOD_BASE             (0x40011400UL)

/** \brief GPIOE����ַ */
#define ZLG217_GPIOE_BASE             (0x40011800UL)

/** \brief AFIOA����ַ */
#define ZLG217_AFIO_BASE              (0x40010000UL)

/** \brief �߼����ƶ�ʱ��1����ַ */
#define ZLG217_TIM1_BASE              (0x40012C00UL)

/** \brief ͨ�ö�ʱ��2����ַ */
#define ZLG217_TIM2_BASE              (0x40000000UL)

/** \brief ͨ�ö�ʱ��3����ַ */
#define ZLG217_TIM3_BASE              (0x40000400UL)

/** \brief ͨ�ö�ʱ��4����ַ */
#define ZLG217_TIM4_BASE              (0x40000800UL)

/** \brief RTC����ַ */
#define ZLG217_RTC_BASE               (0x40002800UL)

/** \brief ��Դ����PWR����ַ */
#define ZLG217_PWR_BASE               (0x40007000UL)

/** \brief ���ݿ���BKP����ַ */
#define ZLG217_BKP_BASE               (0x40006C00UL)

/** \brief UART1 ����ַ */
#define ZLG217_UART1_BASE             (0x40013800UL)

/** \brief UART2 ����ַ */
#define ZLG217_UART2_BASE             (0x40004400UL)

/** \brief UART3 ����ַ */
#define ZLG217_UART3_BASE             (0x40004800UL)

/** \brief ADC1 ����ַ */
#define ZLG217_ADC1_BASE              (0x40012400UL)

/** \brief ADC2 ����ַ */
#define ZLG217_ADC2_BASE              (0x40012800UL)

/** \brief DAC ����ַ */
#define ZLG217_DAC_BASE               (0x40007400UL)

/** \brief DMA ����ַ */
#define ZLG217_DMA_BASE               (0x40020000UL)

/** \brief RCC����������ַ */
#define ZLG217_RCC_BASE               (0x40021000UL)

/** \brief SPI1����������ַ */
#define ZLG217_SPI1_BASE              (0x40013000UL)

/** \brief SPI2����������ַ */
#define ZLG217_SPI2_BASE              (0x40003800UL)

/** \brief I2C1����ַ */
#define ZLG217_I2C1_BASE              (0x40005400UL)

/** \brief I2C2����ַ */
#define ZLG217_I2C2_BASE              (0x40005800UL)

/** \brief IWDG����������ַ */
#define ZLG217_IWDG_BASE              (0x40003000UL)

/** \brief WWDG����������ַ */
#define ZLG217_WWDG_BASE              (0x40002C00UL)

/** \brief CAN����������ַ */
#define ZLG217_CAN_BASE               (0x40006400UL)

/** \brief USB����������ַ */
#define ZLG217_USB_BASE               (0x40005C00UL)

/** \brief �ⲿ�ж�(�¼�)������EXTI����ַ */
#define ZLG217_EXTI_BASE              (0x40010400UL)

/** \brief FLASH����ַ */
#define ZLG217_FLASH_BASE             (0x40022000UL)

/** \brief SRAM����ַ */
#define ZLG217_SRAM_BASE              (0x20000000UL)

/** \brief FLASH����ַ */
#define ZLG217_FLASH_UID_BASE         (0x1FFFF7E8UL)

/** \brief CRC����ַ */
#define ZLG217_CRC_BASE               (0x40023000UL)

/** \brief SYSTICK����ַ */
#define ZLG217_SYSTICK                (0xE000E010UL)

/** @} */

/**
 * @} zlg217_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZLG217_REGBASE_H */

/* end of file */
