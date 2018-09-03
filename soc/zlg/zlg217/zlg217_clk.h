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
 * \brief ZLG217 ʱ��ID����
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __ZLG217_CLK_H
#define __ZLG217_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zlg217_if_clockid
 * \copydoc zlg217_clk.h
 * @{
 */

/**
 * \name ϵͳ�������ʱ��ID
 * \anchor grp_clk_id
 * @{
 */

/* APB1����ʱ�� */
#define CLK_TIM2    (0x01ul << 8 | 0ul)   /**< \brief TIM2��ʱ�� ʱ�� */
#define CLK_TIM3    (0x01ul << 8 | 1ul)   /**< \brief TIM3��ʱ�� ʱ�� */
#define CLK_TIM4    (0x01ul << 8 | 2ul)   /**< \brief TIM3��ʱ�� ʱ�� */
#define CLK_WWDG    (0x01ul << 8 | 11ul)  /**< \brief WWDG���ڿ��Ź� ʱ�� */
#define CLK_SPI2    (0x01ul << 8 | 14ul)  /**< \brief SPI2 ʱ�� */
#define CLK_UART2   (0x01ul << 8 | 17ul)  /**< \brief UART2 ʱ�� */
#define CLK_UART3   (0x01ul << 8 | 18ul)  /**< \brief UART3 ʱ�� */
#define CLK_I2C1    (0x01ul << 8 | 21ul)  /**< \brief I2C1 ʱ�� */
#define CLK_I2C2    (0x01ul << 8 | 22ul)  /**< \brief I2C1 ʱ�� */
#define CLK_USB     (0x01ul << 8 | 23ul)  /**< \brief USB ʱ�� */
#define CLK_CAN     (0x01ul << 8 | 25ul)  /**< \brief CAN ʱ�� */
#define CLK_BKP     (0x01ul << 8 | 27ul)  /**< \brief CRS ʱ�� */
#define CLK_PWR     (0x01ul << 8 | 28ul)  /**< \brief ��Դ�ӿ� ʱ�� */
#define CLK_DAC     (0x01ul << 8 | 29ul)  /**< \brief ��Դ�ӿ� ʱ�� */

/* APB2����ʱ�� */
#define CLK_AFIO    (0x02ul << 8 | 0ul)  /**< \brief ϵͳ���üĴ��� ʱ�� */
#define CLK_IOPA    (0x02ul << 8 | 2ul)  /**< \brief ϵͳ���üĴ��� ʱ�� */
#define CLK_IOPB    (0x02ul << 8 | 3ul)  /**< \brief ϵͳ���üĴ��� ʱ�� */
#define CLK_IOPC    (0x02ul << 8 | 4ul)  /**< \brief ϵͳ���üĴ��� ʱ�� */
#define CLK_IOPD    (0x02ul << 8 | 5ul)  /**< \brief ϵͳ���üĴ��� ʱ�� */
#define CLK_IOPE    (0x02ul << 8 | 6ul)  /**< \brief ϵͳ���üĴ��� ʱ�� */
#define CLK_ADC1    (0x02ul << 8 | 9ul)  /**< \brief ADC1�ӿ� ʱ�� */
#define CLK_ADC2    (0x02ul << 8 | 10ul) /**< \brief ADC1�ӿ� ʱ�� */
#define CLK_TIM1    (0x02ul << 8 | 11ul) /**< \brief TIM1��ʱ�� ʱ�� */
#define CLK_SPI1    (0x02ul << 8 | 12ul) /**< \brief SPI1 ʱ�� */
#define CLK_UART1   (0x02ul << 8 | 14ul) /**< \brief UART1 ʱ�� */

/* AHB����ʱ�� */
#define CLK_DMA    (0x03ul << 8 | 0ul)   /**< \brief DMA ʱ�� */
#define CLK_SRAM   (0x03ul << 8 | 2ul)   /**< \brief SRAM ʱ�� */
#define CLK_FLITF  (0x03ul << 8 | 4ul)   /**< \brief FLITF ʱ�� */
#define CLK_CRC    (0x03ul << 8 | 6ul)   /**< \brief AES ʱ�� */
#define CLK_AES    (0x03ul << 8 | 7ul)   /**< \brief AES ʱ�� */

/* ����ʱ�� */
#define CLK_PLLIN  (0x04ul << 8 | 0ul)  /**< \brief PLL���� ʱ�� */
#define CLK_PLLOUT (0x04ul << 8 | 1ul)  /**< \brief PLL��� ʱ�� */
#define CLK_AHB    (0x04ul << 8 | 2ul)  /**< \brief AHB ʱ�� */
#define CLK_APB1   (0x04ul << 8 | 3ul)  /**< \brief APB1 ʱ�� */
#define CLK_APB2   (0x04ul << 8 | 4ul)  /**< \brief APB2 ʱ�� */
#define CLK_HSEOSC (0x04ul << 8 | 5ul)  /**< \brief �ⲿ���� ʱ�� */
#define CLK_LSEOSC (0x04ul << 8 | 6ul)  /**< \brief �ⲿ���� ʱ�� */
#define CLK_LSI    (0x04ul << 8 | 7ul)  /**< \brief LSI ʱ�� */
#define CLK_HSI    (0x04ul << 8 | 8ul)  /**< \brief HSI ʱ�� */

/* ������ʱ�� */
#define CLK_SYS    (0x05ul << 8 | 0ul)  /**< \brief ϵͳ ʱ�� */
#define CLK_RTC    (0x05ul << 8 | 1ul)  /**< \brief ϵͳ ʱ�� */
/**
 * @}
 */

/**
 * @} zlg217_if_clk
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZLG217_CLK_H */

/* end of file */
