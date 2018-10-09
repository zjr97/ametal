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
 * \brief LPC82x ʱ��ID����
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-12-01  lnk, first implementation.
 * \endinternal
 */
 
#ifndef __LPC82X_CLK_H
#define __LPC82X_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * \addtogroup lpc82x_if_clockid
 * \copydoc lpc82x_clk.h
 * @{
 */
 
 
/**
 * \name ϵͳ�������ʱ��ID
 * \anchor grp_clk_id
 * @{
 */
 
#define CLK_IRC        1            /**< \brief �ڲ�IRCʱ��          */
#define CLK_XTAL       2            /**< \brief �ⲿ����ʱ��         */
#define CLK_CLKIN      3            /**< \brief ������������ʱ��     */
#define CLK_WDTOSC     4            /**< \brief ���Ź�����         */
#define CLK_PLLIN      5            /**< \brief PLL����ʱ��          */
#define CLK_PLLOUT     6            /**< \brief PLL���ʱ��          */
#define CLK_MAIN       7            /**< \brief ��ʱ��               */
#define CLK_SYSTEM     8            /**< \brief ϵͳʱ��             */

#define CLK_ROM         (1 << 8)     /**< \brief ROM ʱ��             */
#define CLK_SRAM0_1     (2 << 8)     /**< \brief SRAM0 SRAM1 ʱ��     */
#define CLK_FLASHREG    (3 << 8)     /**< \brief FLASH�Ĵ����ӿ�ʱ��  */
#define CLK_FLASH       (4 << 8)     /**< \brief FLASH ʱ��           */
#define CLK_I2C0        (5 << 8)     /**< \brief I2C0ʱ��             */
#define CLK_GPIO        (6 << 8)     /**< \brief GPIO ʱ��            */
#define CLK_SWM         (7 << 8)     /**< \brief SWM ʱ��             */
#define CLK_SCT         (8 << 8)     /**< \brief SCT ʱ��             */
#define CLK_WKT         (9 << 8)     /**< \brief WKT ʱ��             */
#define CLK_MRT         (10 << 8)    /**< \brief MRTʱ��              */
#define CLK_SPI0        (11 << 8)    /**< \brief SPI0 ʱ��            */
#define CLK_SPI1        (12 << 8)    /**< \brief SPI1 ʱ��            */
#define CLK_CRC         (13 << 8)    /**< \brief CRC ʱ��             */
#define CLK_UART0       (14 << 8)    /**< \brief UART0 ʱ��           */
#define CLK_UART1       (15 << 8)    /**< \brief UART1 ʱ��           */
#define CLK_UART2       (16 << 8)    /**< \brief UART2 ʱ��           */
#define CLK_WWDT        (17 << 8)    /**< \brief WWDT ʱ��            */
#define CLK_IOCON       (18 << 8)    /**< \brief IOCON ʱ��           */
#define CLK_ACMP        (19 << 8)    /**< \brief ACMP ʱ��            */
#define CLK_I2C1        (21 << 8)    /**< \brief I2C1 ʱ��            */
#define CLK_I2C2        (22 << 8)    /**< \brief I2C2 ʱ��            */
#define CLK_I2C3        (23 << 8)    /**< \brief I2C3 ʱ��            */
#define CLK_ADC0        (24 << 8)    /**< \brief ADC ʱ��             */
#define CLK_MTB         (26 << 8)    /**< \brief MTB ʱ��             */
#define CLK_DMA         (29 << 8)    /**< \brief DMA ʱ��             */

#define CLK_PERIPH_MIN  CLK_ROM      /**< \brief ����ʱ����СIDֵ     */
#define CLK_PERIPH_MAX  CLK_DMA      /**< \brief ����ʱ�����IDֵ     */
/**
 * @} 
 */ 
 
 
/**
 * @} lpc82x_if_clockid
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC82X_CLK_H */

/* end of file */
