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
 * \brief KL26 ʱ��ID����
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-13  ari first implementation.
 * \endinternal
 */

#ifndef __KL26_CLK_ID_H
#define __KL26_CLK_ID_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup kl26_if_clk
 * \copydoc kl26_clk.h
 * @{
 */


/**
 * \name ϵͳ�������ʱ��ID
 * \anchor grp_clk_id
 * @{
 */

#define CLK_SLOW_IRC    (4 << 8 | 0)  /**< \brief ����IRCʱ�� */
#define CLK_FAST_IRC    (4 << 8 | 1)  /**< \brief ����IRCʱ�� */
#define CLK_XTAL        (4 << 8 | 2)  /**< \brief XTAL */
#define CLK_CLKIN       (4 << 8 | 3)  /**< \brief ����ʱ�� */

#define CLK_CORE        (4 << 8 | 4)  /**< \brief �ں�ʱ�� */
#define CLK_SYSTEM      (4 << 8 | 5)  /**< \brief ϵͳʱ�� */
#define CLK_BUS         (4 << 8 | 6)  /**< \brief ����ʱ�� */
#define CLK_FLASH       (4 << 8 | 7)  /**< \brief Flashʱ�� */
#define CLK_PERIPH      (4 << 8 | 8)  /**< \brief ����ʱ�� */
#define CLK_SYSTICK     (4 << 8 | 9)  /**< \brief ϵͳ�δ�ʱ�� */

#define CLK_OSC32K      (4 << 8 | 10) /**< \brief OSC32Kʱ�� */
#define CLK_OSCERC      (4 << 8 | 11) /**< \brief OSCERCʱ�� */

/** \brief rtc out clocks*/
#define CLK_RTCOUT      (4 << 8 | 12) /**< \brief RTC���ʱ�� */

/** \brief mcg clocks*/
#define CLK_MCGFLL      (4 << 8 | 13) /**< \brief FLLʱ�� */
#define CLK_MCGPLL      (4 << 8 | 14) /**< \brief PLLʱ�� */
#define CLK_MCGEXT      (4 << 8 | 15) /**< \brief EXTʱ�� */
#define CLK_MCGIRC      (4 << 8 | 16) /**< \brief IRCʱ�� */
#define CLK_MCGOUT      (4 << 8 | 17) /**< \brief MCG���ʱ�� */

/** \brief LPO clock */
#define CLK_LPO         (4 << 8 | 18) /**< \brief LPOʱ�� */
#define CLK_WDT         (4 << 8 | 19) /**< \brief WDTʱ�� */

/** \brief periph clk */
#define CLK_I2C0        (0 << 8 | 6)  /**< \brief I2C0ʱ�� */
#define CLK_I2C1        (0 << 8 | 7)  /**< \brief I2C1ʱ�� */
#define CLK_UART0       (0 << 8 | 10) /**< \brief UART0ʱ�� */
#define CLK_UART1       (0 << 8 | 11) /**< \brief UART1ʱ�� */
#define CLK_UART2       (0 << 8 | 12) /**< \brief UART2ʱ�� */
#define CLK_USBOTG      (0 << 8 | 18) /**< \brief USBʱ�� */
#define CLK_CMP         (0 << 8 | 19) /**< \brief CMPʱ�� */
#define CLK_SPI0        (0 << 8 | 22) /**< \brief SPI0ʱ�� */
#define CLK_SPI1        (0 << 8 | 23) /**< \brief SPI1ʱ�� */

/** \brief  SCGC5 */
#define CLK_LPTMR       (1 << 8 | 0)  /**< \brief LPTMRʱ�� */
#define CLK_TSI         (1 << 8 | 5)  /**< \brief TSIʱ�� */
#define CLK_PORTA       (1 << 8 | 9)  /**< \brief PORTAʱ�� */
#define CLK_PORTB       (1 << 8 | 10) /**< \brief PORTBʱ�� */
#define CLK_PORTC       (1 << 8 | 11) /**< \brief PORTCʱ�� */
#define CLK_PORTD       (1 << 8 | 12) /**< \brief PORTDʱ�� */
#define CLK_PORTE       (1 << 8 | 13) /**< \brief PORTEʱ�� */

/** \brief  SCGC6 */
#define CLK_FTF         (2 << 8 | 0)  /**< \brief FTFʱ�� */
#define CLK_DMAMUX      (2 << 8 | 1)  /**< \brief DMAMUXʱ�� */
#define CLK_I2S         (2 << 8 | 15) /**< \brief I2Sʱ�� */
#define CLK_PIT         (2 << 8 | 23) /**< \brief PITʱ�� */
#define CLK_TPM0        (2 << 8 | 24) /**< \brief TPM0ʱ�� */
#define CLK_TPM1        (2 << 8 | 25) /**< \brief TPM1ʱ�� */
#define CLK_TPM2        (2 << 8 | 26) /**< \brief TPM2ʱ�� */
#define CLK_ADC0        (2 << 8 | 27) /**< \brief ADC0ʱ�� */
#define CLK_RTC         (2 << 8 | 29) /**< \brief RTCʱ�� */
#define CLK_DAC0        (2 << 8 | 31) /**< \brief DAC0ʱ�� */

/** \brief  SCGC7 */
#define CLK_DMA         (3 << 8 | 8)  /**< \brief DMAʱ�� */

#define CLK_PERIPH_ID_MIN CLK_I2C0    /**< \brief ����ʱ��ID��Сֵ */
#define CLK_PERIPH_ID_MAX CLK_DMA     /**< \brief ����ʱ��ID���ֵ */

/**
 * @}
 */


/**
 * @} kl26_if_clk
 */

#ifdef __cplusplus
}
#endif

#endif /* __KL26_CLK_H */

/* end of file */
