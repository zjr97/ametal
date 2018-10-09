/*******************************************************************************
* AMetal
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
 * \brief GPIOƽ̨�����㸨�����ߺ�
 *
 * - ���ļ���������lpc8xx_pin.h \sa lpc82x_pin.h �䶨����GPIOƽ̨���ŵĸ������ܡ�
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-26  mem, modified.
 * - 1.02 15-07-28  zxl, modified.
 * - 1.00 15-07-08  zxl, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC82X_GPIO_UTIL_H
#define __AM_LPC82X_GPIO_UTIL_H

#include "ametal.h"
#include "am_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * \addtogroup am_lpc82x_if_gpio_util
 * \copydoc am_lpc82x_gpio_util.h
 * @{
 */
 
/* 
 * bit[31:12] ƽ̨����
 *
 * - bit[13:12] �м�ģʽ���� 
 * - bit[15:14] ���ų������� 
 * - bit[17:16] ���뷴ת���� 
 * - bit[23:18] �������ã�SWM��      
 * - bit[25:24] I2Cģʽ����          
 * - bit[28:26] �˲�����            
 * - bit[31:29] �˲�����Ƶ
 */

/**
 * \name �����м�ģʽ���ù��ߺ�
 *
 * @{
 */
 
/** \brief �м�ģʽ��ƫ�� */
#define AM_LPC82X_GPIO_REP_BITS_START   12
      
/** \brief �м�ģʽ�볤�� */             
#define AM_LPC82X_GPIO_REP_BITS_LEN     2
      
/** \brief �����м�ģʽ���� */             
#define AM_LPC82X_GPIO_REP_CODE(a)      AM_SBF(((a) +1), \
                                               AM_LPC82X_GPIO_REP_BITS_START)

/** \brief �м�ģʽλ������ */             
#define AM_LPC82X_GPIO_REP_MASK         AM_SBF(0x03, \
                                               AM_LPC82X_GPIO_REP_BITS_START)
      
/** \brief ��ȡ�м�ģʽ�� */                
#define AM_LPC82X_GPIO_REP_GET(data) \
                           (AM_BITS_GET((data), \
                                        AM_LPC82X_GPIO_REP_BITS_START, \
                                        AM_LPC82X_GPIO_REP_BITS_LEN) \
                            - 1)

/** @} */

/**
 * \name ���ų������ù��ߺ�
 *
 * @{
 */
 
/** \brief ������ƫ�� */
#define AM_LPC82X_GPIO_HYS_BITS_START   14
  
/** \brief �����볤�� */               
#define AM_LPC82X_GPIO_HYS_BITS_LEN     2
  
/** \brief ���ó��ͱ��� */              
#define AM_LPC82X_GPIO_HYS_CODE(a)      AM_SBF(((a) + 1), \
                                               AM_LPC82X_GPIO_HYS_BITS_START)

/** \brief ����λ������ */              
#define AM_LPC82X_GPIO_HYS_MASK         AM_SBF(0x03, \
                                               AM_LPC82X_GPIO_HYS_BITS_START)
  
/** \brief ��ȡ������ */               
#define AM_LPC82X_GPIO_HYS_GET(data) \
                           (AM_BITS_GET((data), \
                                        AM_LPC82X_GPIO_HYS_BITS_START, \
                                        AM_LPC82X_GPIO_HYS_BITS_LEN) \
                            - 1)

/** @} */

/**
 * \name �������뷴ת���ù��ߺ�
 *
 * @{
 */
 
/** \brief ���뷴ת��ƫ�� */
#define AM_LPC82X_GPIO_INV_BITS_START   16

/** \brief ���뷴ת�볤�� */
#define AM_LPC82X_GPIO_INV_BITS_LEN     2

/** \brief �������뷴ת���� */
#define AM_LPC82X_GPIO_INV_CODE(a)      AM_SBF(((a) + 1), \
                                               AM_LPC82X_GPIO_INV_BITS_START)

/** \brief ���뷴תλ������ */            
#define AM_LPC82X_GPIO_INV_MASK         AM_SBF(0x03, \
                                               AM_LPC82X_GPIO_INV_BITS_START)

/** \brief ��ȡ���뷴ת�� */
#define AM_LPC82X_GPIO_INV_GET(data) \
                           (AM_BITS_GET((data), \
                                        AM_LPC82X_GPIO_INV_BITS_START, \
                                        AM_LPC82X_GPIO_INV_BITS_LEN) \
                            - 1)

/** @} */

/**
 * \name ���Ź������ù��ߺ�
 *
 * @{
 */
 
/** \brief ������ƫ�� */
#define AM_LPC82X_GPIO_FUNC_BITS_START  18
  
/** \brief �����볤�� */               
#define AM_LPC82X_GPIO_FUNC_BITS_LEN    6
  
/** \brief ���ù��ܱ��� */              
#define AM_LPC82X_GPIO_FUNC_CODE(a)     AM_SBF(((a) + 1), \
                                               AM_LPC82X_GPIO_FUNC_BITS_START)

/** \brief ����λ������ */              
#define AM_LPC82X_GPIO_FUNC_MASK        AM_SBF(0x3F, \
                                               AM_LPC82X_GPIO_FUNC_BITS_START)
               
/** \brief ��ȡ������ */               
#define AM_LPC82X_GPIO_FUNC_GET(data) \
                           (AM_BITS_GET((data), \
                                        AM_LPC82X_GPIO_FUNC_BITS_START, \
                                        AM_LPC82X_GPIO_FUNC_BITS_LEN) \
                            - 1)

/** @} */

/**
 * \name ����I2Cģʽ���ù��ߺ�
 *
 * @{
 */

/** \brief I2Cģʽ��ƫ�� */
#define AM_LPC82X_GPIO_I2C_BITS_START   24

/** \brief I2Cģʽ�볤�� */
#define AM_LPC82X_GPIO_I2C_BITS_LEN     2

/** \brief ����I2Cģʽ����� */
#define AM_LPC82X_GPIO_I2C_CODE(a)      AM_SBF(((a) + 1), \
                                               AM_LPC82X_GPIO_I2C_BITS_START)

/** \brief I2Cģʽ������ */             
#define AM_LPC82X_GPIO_I2C_MASK         AM_SBF(0x03, \
                                               AM_LPC82X_GPIO_I2C_BITS_START)

/** \brief I2Cģʽ�����û�ȡ */
#define AM_LPC82X_GPIO_I2C_GET(data) \
                           (AM_BITS_GET((data), \
                                        AM_LPC82X_GPIO_I2C_BITS_START, \
                                        AM_LPC82X_GPIO_I2C_BITS_LEN) \
                            - 1)
           
/** @} */

/**
 * \name �����˲��������ù��ߺ�
 *
 * @{
 */

/** \brief �˲�������ƫ�� */
#define AM_LPC82X_GPIO_FIL_CYC_BITS_START  26
                                           
/** \brief �˲������볤�� */               
#define AM_LPC82X_GPIO_FIL_CYC_BITS_LEN    3
                                           
/** \brief �����˲����ڱ��� */             
#define AM_LPC82X_GPIO_FIL_CYC_CODE(a)     AM_SBF(((a) + 1), \
                                                  AM_LPC82X_GPIO_FIL_CYC_BITS_START)
                                           
/** \brief �˲��������� */                 
#define AM_LPC82X_GPIO_FIL_CYC_MASK        AM_SBF(0x07, \
                                                  AM_LPC82X_GPIO_FIL_CYC_BITS_START)
                                           
/** \brief ��ȡ�˲����� */                 
#define AM_LPC82X_GPIO_FIL_CYC_GET(data)  \
                              (AM_BITS_GET((data), \
                                           AM_LPC82X_GPIO_FIL_CYC_BITS_START, \
                                           AM_LPC82X_GPIO_FIL_CYC_BITS_LEN) \
                               -1)
        
/** @} */

/**
 * \name �����˲���Ƶ���ù��ߺ�
 *
 * @{
 */

/** \brief �˲���Ƶ��ƫ�� */
#define AM_LPC82X_GPIO_FIL_DIV_BITS_START  29
  
/** \brief �˲���Ƶ�볤�� */           
#define AM_LPC82X_GPIO_FIL_DIV_BITS_LEN    3
  
/** \brief �����˲���Ƶ���� */         
#define AM_LPC82X_GPIO_FIL_DIV_CODE(a)     AM_SBF(((a) + 1), \
                                                  AM_LPC82X_GPIO_FIL_DIV_BITS_START)
  
/** \brief �˲���Ƶ���� */                
#define AM_LPC82X_GPIO_FIL_DIV_MASK        AM_SBF(0x07UL,\
                                                  AM_LPC82X_GPIO_FIL_DIV_BITS_START)

/** \brief ��ȡ�˲���Ƶ */
#define AM_LPC82X_GPIO_FIL_DIV_GET(data) \
                              (AM_BITS_GET((data), \
                                           AM_LPC82X_GPIO_FIL_DIV_BITS_START, \
                                           AM_LPC82X_GPIO_FIL_DIV_BITS_LEN) \
                               - 1)

/** @} */

/*************************LPC8xx��������***************************************/

/**
 * \name ����ģʽ
 *
 * @{
 */

/** \brief ����ģʽ(������/����) */
#define AM_LPC82X_GPIO_INACTIVE           AM_GPIO_FLOAT

/** \brief ����ģʽ */               
#define AM_LPC82X_GPIO_PULLDOWN           AM_GPIO_PULLDOWN

/** \brief ����ģʽ */               
#define AM_LPC82X_GPIO_PULLUP             AM_GPIO_PULLUP

/** \brief ��©ģʽ */               
#define AM_LPC82X_GPIO_OPEN_DRAIN         AM_GPIO_OPEN_DRAIN

/** \brief �м�ģʽ */               
#define AM_LPC82X_GPIO_REPEATER           AM_LPC82X_GPIO_REP_CODE(0)

/** @} */

/**
 * \name ���ŷ���
 *
 * @{
 */

/** \brief ����  */
#define AM_LPC82X_GPIO_INPUT              AM_GPIO_INPUT

/** \brief �����  */                  
#define AM_LPC82X_GPIO_OUTPUT_HIGH        AM_GPIO_OUTPUT_INIT_HIGH

/** \brief �����  */                  
#define AM_LPC82X_GPIO_OUTPUT_LOW         AM_GPIO_OUTPUT_INIT_LOW

/** @} */

/**
 * \name ���ų���ʹ�ܺͽ���
 *
 * @{
 */

/** \brief ������ */
#define AM_LPC82X_GPIO_HYS_DISABLE        AM_LPC82X_GPIO_HYS_CODE(0UL)

/** \brief ����  */                  
#define AM_LPC82X_GPIO_HYS_ENABLE         AM_LPC82X_GPIO_HYS_CODE(1UL)

/** @} */

/**
 * \name �������뷴תʹ�ܺͽ���
 *
 * @{
 */

/** \brief ���벻��ת */
#define AM_LPC82X_GPIO_INV_DISABLE        AM_LPC82X_GPIO_INV_CODE(0UL)

/** \brief ���뷢ת  */              
#define AM_LPC82X_GPIO_INV_ENABLE         AM_LPC82X_GPIO_INV_CODE(1UL)

/** @} */

/**
 * \name �����˲�����
 *
 * @{
 */

/** \brief ��ʹ���˲� */
#define AM_LPC82X_GPIO_FIL_DISABLE        AM_LPC82X_GPIO_FIL_CYC_CODE(0UL)

/** \brief �˳�С��һ�������ź� */   
#define AM_LPC82X_GPIO_FIL_1CYCLE         AM_LPC82X_GPIO_FIL_CYC_CODE(1UL)

/** \brief �˳�С�����������ź� */   
#define AM_LPC82X_GPIO_FIL_2CYCLE         AM_LPC82X_GPIO_FIL_CYC_CODE(2UL)

/** \brief �˳�С�����������ź� */   
#define AM_LPC82X_GPIO_FIL_3CYCLE         AM_LPC82X_GPIO_FIL_CYC_CODE(3UL)

/** @} */

/**
 * \name �����˲���Ƶ
 *
 * @{
 */

/** \brief ��Ƶϵ��λ0 */
#define AM_LPC82X_GPIO_FIL_DIV0           AM_LPC82X_GPIO_FIL_DIV_CODE(0UL)

/** \brief ��Ƶϵ��λ1 */            
#define AM_LPC82X_GPIO_FIL_DIV1           AM_LPC82X_GPIO_FIL_DIV_CODE(1UL)

/** \brief ��Ƶϵ��λ2 */            
#define AM_LPC82X_GPIO_FIL_DIV2           AM_LPC82X_GPIO_FIL_DIV_CODE(2UL)

/** \brief ��Ƶϵ��λ3 */            
#define AM_LPC82X_GPIO_FIL_DIV3           AM_LPC82X_GPIO_FIL_DIV_CODE(3UL)

/** \brief ��Ƶϵ��λ4 */            
#define AM_LPC82X_GPIO_FIL_DIV4           AM_LPC82X_GPIO_FIL_DIV_CODE(4UL)

/** \brief ��Ƶϵ��λ5 */            
#define AM_LPC82X_GPIO_FIL_DIV5           AM_LPC82X_GPIO_FIL_DIV_CODE(5UL)

/** \brief ��Ƶϵ��λ6 */            
#define AM_LPC82X_GPIO_FIL_DIV6           AM_LPC82X_GPIO_FIL_DIV_CODE(6UL)

/** @} */

/** 
 * \name ���ſ�ת�ƹ���
 * @{
 */

/** \brief UART0_TXD  ���� */
#define AM_LPC82X_GPIO_FUNC_U0_TXD        AM_LPC82X_GPIO_FUNC_CODE(0UL)

/** \brief UART0_RXD  ���� */        
#define AM_LPC82X_GPIO_FUNC_U0_RXD        AM_LPC82X_GPIO_FUNC_CODE(1UL)

/** \brief UART0_RTS  ���� */        
#define AM_LPC82X_GPIO_FUNC_U0_RTS        AM_LPC82X_GPIO_FUNC_CODE(2UL)

/** \brief UART0_CTS  ���� */        
#define AM_LPC82X_GPIO_FUNC_U0_CTS        AM_LPC82X_GPIO_FUNC_CODE(3UL)

/** \brief UART0_SCLK ���� */        
#define AM_LPC82X_GPIO_FUNC_U0_SCLK       AM_LPC82X_GPIO_FUNC_CODE(4UL)

/** \brief UART1_TXD  ���� */        
#define AM_LPC82X_GPIO_FUNC_U1_TXD        AM_LPC82X_GPIO_FUNC_CODE(5UL)

/** \brief UART1_RXD  ���� */        
#define AM_LPC82X_GPIO_FUNC_U1_RXD        AM_LPC82X_GPIO_FUNC_CODE(6UL)

/** \brief UART1_RTS  ���� */        
#define AM_LPC82X_GPIO_FUNC_U1_RTS        AM_LPC82X_GPIO_FUNC_CODE(7UL)

/** \brief UART1_CTS  ���� */        
#define AM_LPC82X_GPIO_FUNC_U1_CTS        AM_LPC82X_GPIO_FUNC_CODE(8UL)

/** \brief UART1_SCLK ���� */        
#define AM_LPC82X_GPIO_FUNC_U1_SCLK       AM_LPC82X_GPIO_FUNC_CODE(9UL)

/** \brief UART2_TXD  ���� */        
#define AM_LPC82X_GPIO_FUNC_U2_TXD        AM_LPC82X_GPIO_FUNC_CODE(10UL)

/** \brief UART2_RXD  ���� */        
#define AM_LPC82X_GPIO_FUNC_U2_RXD        AM_LPC82X_GPIO_FUNC_CODE(11UL)

/** \brief UART2_RTS  ���� */        
#define AM_LPC82X_GPIO_FUNC_U2_RTS        AM_LPC82X_GPIO_FUNC_CODE(12UL)

/** \brief UART2_CTS  ���� */        
#define AM_LPC82X_GPIO_FUNC_U2_CTS        AM_LPC82X_GPIO_FUNC_CODE(13UL)

/** \brief UART2_SCLK ���� */        
#define AM_LPC82X_GPIO_FUNC_U2_SCLK       AM_LPC82X_GPIO_FUNC_CODE(14UL)

/** \brief SPI0_SCK   ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI0_SCK      AM_LPC82X_GPIO_FUNC_CODE(15UL)

/** \brief SPI0_MOSI  ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI0_MOSI     AM_LPC82X_GPIO_FUNC_CODE(16UL)

/** \brief SPI0_MISO  ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI0_MISO     AM_LPC82X_GPIO_FUNC_CODE(17UL)

/** \brief SPI0_SSEL0 ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI0_SSEL0    AM_LPC82X_GPIO_FUNC_CODE(18UL)

/** \brief SPI0_SSEL1 ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI0_SSEL1    AM_LPC82X_GPIO_FUNC_CODE(19UL)

/** \brief SPI0_SSEL2 ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI0_SSEL2    AM_LPC82X_GPIO_FUNC_CODE(20UL)

/** \brief SPI0_SSEL3 ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI0_SSEL3    AM_LPC82X_GPIO_FUNC_CODE(21UL)

/** \brief SPI1_SCK   ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI1_SCK      AM_LPC82X_GPIO_FUNC_CODE(22UL)

/** \brief SPI1_MOSI  ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI1_MOSI     AM_LPC82X_GPIO_FUNC_CODE(23UL)

/** \brief SPI1_MISO  ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI1_MISO     AM_LPC82X_GPIO_FUNC_CODE(24UL)

/** \brief SPI1_SSEL0 ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI1_SSEL0    AM_LPC82X_GPIO_FUNC_CODE(25UL)

/** \brief SPI1_SSEL1 ���� */        
#define AM_LPC82X_GPIO_FUNC_SPI1_SSEL1    AM_LPC82X_GPIO_FUNC_CODE(26UL)

/** \brief SCT_PIN_PIN0 ���� */      
#define AM_LPC82X_GPIO_FUNC_SCT_PIN0      AM_LPC82X_GPIO_FUNC_CODE(27UL)

/** \brief SCT_PIN_PIN1 ���� */      
#define AM_LPC82X_GPIO_FUNC_SCT_PIN1      AM_LPC82X_GPIO_FUNC_CODE(28UL)

/** \brief SCT_PIN_PIN2 ���� */      
#define AM_LPC82X_GPIO_FUNC_SCT_PIN2      AM_LPC82X_GPIO_FUNC_CODE(29UL)

/** \brief SCT_PIN_PIN3 ���� */      
#define AM_LPC82X_GPIO_FUNC_SCT_PIN3      AM_LPC82X_GPIO_FUNC_CODE(30UL)

/** \brief SCT_OUT0 ���� */          
#define AM_LPC82X_GPIO_FUNC_SCT_OUT0      AM_LPC82X_GPIO_FUNC_CODE(31UL)

/** \brief SCT_OUT1 ���� */          
#define AM_LPC82X_GPIO_FUNC_SCT_OUT1      AM_LPC82X_GPIO_FUNC_CODE(32UL)

/** \brief SCT_OUT2 ���� */          
#define AM_LPC82X_GPIO_FUNC_SCT_OUT2      AM_LPC82X_GPIO_FUNC_CODE(33UL)

/** \brief SCT_OUT3 ���� */          
#define AM_LPC82X_GPIO_FUNC_SCT_OUT3      AM_LPC82X_GPIO_FUNC_CODE(34UL)

/** \brief SCT_OUT4 ���� */          
#define AM_LPC82X_GPIO_FUNC_SCT_OUT4      AM_LPC82X_GPIO_FUNC_CODE(35UL)

/** \brief SCT_OUT5 ���� */          
#define AM_LPC82X_GPIO_FUNC_SCT_OUT5      AM_LPC82X_GPIO_FUNC_CODE(36UL)

/** \brief I2C1_SDA ���� */          
#define AM_LPC82X_GPIO_FUNC_I2C1_SDA      AM_LPC82X_GPIO_FUNC_CODE(37UL)

/** \brief I2C1_SCL ���� */          
#define AM_LPC82X_GPIO_FUNC_I2C1_SCL      AM_LPC82X_GPIO_FUNC_CODE(38UL)

/** \brief I2C2_SDA ���� */          
#define AM_LPC82X_GPIO_FUNC_I2C2_SDA      AM_LPC82X_GPIO_FUNC_CODE(39UL)

/** \brief I2C2_SCL ���� */          
#define AM_LPC82X_GPIO_FUNC_I2C2_SCL      AM_LPC82X_GPIO_FUNC_CODE(40UL)

/** \brief I2C3_SDA ���� */          
#define AM_LPC82X_GPIO_FUNC_I2C3_SDA      AM_LPC82X_GPIO_FUNC_CODE(41UL)

/** \brief I2C3_SCL ���� */          
#define AM_LPC82X_GPIO_FUNC_I2C3_SCL      AM_LPC82X_GPIO_FUNC_CODE(42UL)

/** \brief ADC_PINTRIG0 ���� */      
#define AM_LPC82X_GPIO_FUNC_ADC_PINTRIG0  AM_LPC82X_GPIO_FUNC_CODE(43UL)

/** \brief ADC_PINTRIG1 ���� */      
#define AM_LPC82X_GPIO_FUNC_ADC_PINTRIG1  AM_LPC82X_GPIO_FUNC_CODE(44UL)

/** \brief ACMP ���� */              
#define AM_LPC82X_GPIO_FUNC_ACMP_O        AM_LPC82X_GPIO_FUNC_CODE(45UL)

/** \brief CLKOUT ���� */            

#define AM_LPC82X_GPIO_FUNC_CLKOUT        AM_LPC82X_GPIO_FUNC_CODE(46UL)

/** \brief GPIO_INT_BMAT ���� */     
#define AM_LPC82X_GPIO_FUNC_GPIO_INT_BMAT AM_LPC82X_GPIO_FUNC_CODE(47UL)

/** @} */                            

/**  
 * \name ���� GPIO����             
 * @{
 */  

/** \brief GPIO  ���� */             
#define AM_LPC82X_GPIO_FUNC_GPIO          AM_LPC82X_GPIO_FUNC_CODE(48UL)

/** @} */                            

/**  
 * \name ���� ���⹦��             
 * @{
 */  

/** \brief ���⹦��1 */         
#define AM_LPC82X_GPIO_FUNC_OTHER1        AM_LPC82X_GPIO_FUNC_CODE(49UL)

/** \brief ���⹦��2 */         
#define AM_LPC82X_GPIO_FUNC_OTHER2        AM_LPC82X_GPIO_FUNC_CODE(50UL)

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC82X_GPIO_UTIL_H */

/* end of file */
