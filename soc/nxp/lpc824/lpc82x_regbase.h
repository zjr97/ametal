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
 * \brief LPC82X оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-07  cyl, first implementation.
 * \endinternal
 */
 
#ifndef __LPC82X_REGBASE_H
#define __LPC82X_REGBASE_H

#ifdef __cplusplus
extern "C" {    
#endif
    
/** 
 * \addtogroup lpc82x_if_regbase
 * \copydoc lpc82x_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */
 
/** \brief NVIC����ַ          */
#define LPC82X_NVIC_BASE           (0xE000E100UL)  

/** \brief SYSTICK����ַ       */
#define LPC82X_SYSTICK_BASE        (0xE000E010UL)  

/** \brief WWDT����ַ          */
#define LPC82X_WWDT_BASE           (0x40000000UL)  

/** \brief MRT ����ַ          */
#define LPC82X_MRT_BASE            (0x40004000UL)  

/** \brief WKT ����ַ          */
#define LPC82X_WKT_BASE            (0x40008000UL)  

/** \brief SWM ����ַ          */
#define LPC82X_SWM_BASE            (0x4000C000UL)  

/** \brief ADC ����ַ          */
#define LPC82X_ADC0_BASE           (0x4001C000UL)  

/** \brief PMU ����ַ          */
#define LPC82X_PMU_BASE            (0x40020000UL)  

/** \brief CMP ����ַ          */
#define LPC82X_ACMP_BASE           (0x40024000UL)  

/** \brief ���븴�û���ַ      */
#define LPC82X_INMUX_BASE          (0x40028000UL)  


/** \brief FMC ����ַ         */
#define LPC82X_FMC_BASE            (0x40040000UL)

/** \brief IOCON����ַ        */
#define LPC82X_IOCON_BASE          (0x40044000UL)   

/** \brief SYSCON����ַ       */
#define LPC82X_SYSCON_BASE         (0x40048000UL)   

/** \brief I2C0����ַ         */
#define LPC82X_I2C0_BASE           (0x40050000UL)   

/** \brief I2C1����ַ         */
#define LPC82X_I2C1_BASE           (0x40054000UL)   

/** \brief I2C2����ַ         */
#define LPC82X_I2C2_BASE           (0x40070000UL)   
                                        
/** \brief I2C3����ַ         */        
#define LPC82X_I2C3_BASE           (0x40074000UL)   

/** \brief SPI0����ַ         */
#define LPC82X_SPI0_BASE           (0x40058000UL)   

/** \brief SPI1����ַ         */ 
#define LPC82X_SPI1_BASE           (0x4005C000UL)   

/** \brief USART0����ַ       */ 
#define LPC82X_USART0_BASE         (0x40064000UL)   

/** \brief USART1����ַ       */ 
#define LPC82X_USART1_BASE         (0x40068000UL)   

/** \brief USART2����ַ       */ 
#define LPC82X_USART2_BASE         (0x4006C000UL)   

/** \brief CRC ����ַ         */
#define LPC82X_CRC_BASE            (0x50000000UL)  

/** \brief DMA ����ַ         */ 
#define LPC82X_DMA_BASE            (0x50008000UL)   

/** \brief GPIOͨ������ַ     */
#define LPC82X_GPIO_BASE           (0xA0000000UL)   

/** \brief PIN_INT����ַ      */
#define LPC82X_PINT_BASE           (0xA0004000UL)   

/** \brief SCT0�Ļ���ַ       */
#define LPC82X_SCT0_BASE           (0x50004000UL)   

/** \brief IAP API��ַ        */
#define LPC82X_IAP_ENTRY_LOCATION  (0x1FFF1FF1UL)   

/** @} */    

/**
 * @} lpc82x_if_regbase
 */
    
#ifdef __cplusplus
}
#endif

#endif /* __LPC82X_REGBASE_H */

/* end of file */
