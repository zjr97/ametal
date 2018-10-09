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
 * \brief LPC82X �жϺŶ���
 *
 * \internal
 * \par Modification history
 * - 1.00 15-06-21  jon, first implementation.
 * \endinternal
 */


#ifndef __LPC82X_INUM_H
#define __LPC82X_INUM_H

#ifdef __cplusplus
extern "C" {
    
#endif

#include "ametal.h"

/** 
 * \addtogroup lpc82x_if_inum
 * \copydoc lpc82x_inum.h
 * @{
 */

/**
 * \name LPC82x CPU �жϺ�
 * @{
 */
                                                                                            
#define INUM_SPI0                0    /**< \brief SPI0�ж�               */
#define INUM_SPI1                1    /**< \brief SPI1�ж�               */
#define INUM_USART0              3    /**< \brief USART0�ж�             */
#define INUM_USART1              4    /**< \brief USART1�ж�             */
#define INUM_USART2              5    /**< \brief USART2�ж�             */
#define INUM_I2C1                7    /**< \brief I2C1�ж�               */
#define INUM_I2C0                8    /**< \brief I2C0�ж�               */
#define INUM_SCT0                9    /**< \brief SCT�ж�                */
#define INUM_MRT                 10   /**< \brief Multi-rate ��ʱ���ж�  */
#define INUM_ACMP                11   /**< \brief ģ��Ƚ����ж�         */
#define INUM_WDT                 12   /**< \brief ���Ź��ж�             */
#define INUM_BOD                 13   /**< \brief BOD�ж�                */
#define INUM_FLASH               14   /**< \brief FLASH�ж�              */
#define INUM_WKT                 15   /**< \brief WKT�ж�                */
#define INUM_ADC0_SEQA           16   /**< \brief ADC0����A�ж�          */
#define INUM_ADC0_SEQB           17   /**< \brief ADC0����B�ж�          */
#define INUM_ADC0_THCMP          18   /**< \brief ADC0��ֵ�ȽϺʹ����ж� */
#define INUM_ADC0_OVR            19   /**< \brief ADC0 overrun �ж�      */
#define INUM_DMA                 20   /**< \brief DMA�ж�                */
#define INUM_I2C2                21   /**< \brief I2C2�ж�               */
#define INUM_I2C3                22   /**< \brief I2C3�ж�               */
#define INUM_PIN_INT0            24   /**< \brief �����ж�0              */
#define INUM_PIN_INT1            25   /**< \brief �����ж�1              */
#define INUM_PIN_INT2            26   /**< \brief �����ж�2              */
#define INUM_PIN_INT3            27   /**< \brief �����ж�3              */
#define INUM_PIN_INT4            28   /**< \brief �����ж�4              */
#define INUM_PIN_INT5            29   /**< \brief �����ж�5              */
#define INUM_PIN_INT6            30   /**< \brief �����ж�6              */
#define INUM_PIN_INT7            31   /**< \brief �����ж�7              */

/** @} */




/**
 * \brief ���ж���Ϊ��(INUM_PIN_INT7 - INUM_SPI0 + 1),
 * 
 */
#define INUM_INTERNAL_COUNT     (INUM_PIN_INT7 - INUM_SPI0 + 1)

/** 
 * \brief ����жϺ�Ϊ��INUM_PIN_INT7
 */
#define INUM_INTERNAL_MAX        INUM_PIN_INT7


/** \brief ��С�жϺ�: INUM_SPI0 */
#define INUM_INTERNAL_MIN        INUM_SPI0


/**
 * \cond
 * \brief �жϺŶ��壬Ϊcore_cm0plus.h�ļ�����
 */
typedef enum {                                                         
    /** \brief  1  ��λ����                                                */
    Reset_IRQn               = -15,                                    
                                                                       
    /** \brief  2  ���������ж�, ���ܱ�ֹͣ����ռ                          */
    NonMaskableInt_IRQn      = -14,                                    
                                                                       
    /** \brief  3  Ӳ�������ж�                                            */
    HardFault_IRQn           = -13,                                    
                                                                       
    /** \brief 11  ϵͳ�������ͨ��SVCָ��                                 */
    SVCall_IRQn              =  -5,                                    
                                                                       
    /** \brief 14  ϵͳ�Ĺ�������                                          */
    PendSV_IRQn              =  -2,                                    
                                                                       
    /** \brief 15  ϵͳ�δ�ʱ��                                          */
    SysTick_IRQn             =  -1,   
   
    /* ---------------  �����ж� ------------------------------------ */
    SPI0_IRQn                = 0,    /**< \brief SPI0     Interrupt        */
    SPI1_IRQn                = 1,    /**< \brief SPI1     Interrupt        */
    Reserved0_IRQn           = 2,    /**< \brief Reserved Interrupt        */
    UART0_IRQn               = 3,    /**< \brief USART0   Interrupt        */
    UART1_IRQn               = 4,    /**< \brief USART1   Interrupt        */
    UART2_IRQn               = 5,    /**< \brief USART2   Interrupt        */
    Reserved1_IRQn           = 6,    /**< \brief Reserved Interrupt        */
    I2C1_IRQn                = 7,    /**< \brief I2C1     Interrupt        */
    I2C0_IRQn                = 8,    /**< \brief I2C0     Interrupt        */
    SCT_IRQn                 = 9,    /**< \brief SCT      Interrupt        */
    MRT_IRQn                 = 10,   /**< \brief MRT      Interrupt        */
    CMP_IRQn                 = 11,   /**< \brief CMP      Interrupt        */
    WDT_IRQn                 = 12,   /**< \brief WDT      Interrupt        */
    BOD_IRQn                 = 13,   /**< \brief BOD      Interrupt        */
    FLASH_IRQn               = 14,   /**< \brief Flash    Interrupt        */
    WKT_IRQn                 = 15,   /**< \brief WKT      Interrupt        */
    ADC_SEQA_IRQn            = 16,   /**< \brief ADC sequence A completion */
    ADC_SEQB_IRQn            = 17,   /**< \brief ADC sequence B completion */
    ADC_THCMP_IRQn           = 18,   /**< \brief ADC threshold  compare    */
    ADC_OVR_IRQn             = 19,   /**< \brief ADC overrun               */
    DMA_IRQn                 = 20,   /**< \brief DMA      Interrupt        */
    I2C2_IRQn                = 21,   /**< \brief I2C0     Interrupt        */
    I2C3_IRQn                = 22,   /**< \brief I2C3     Interrupt        */
    Reserved2_IRQn           = 23,   /**< \brief Reserved Interrupt        */
    PIN_INT0_IRQn            = 24,   /**< \brief External Interrupt 0      */
    PIN_INT1_IRQn            = 25,   /**< \brief External Interrupt 1      */
    PIN_INT2_IRQn            = 26,   /**< \brief External Interrupt 2      */
    PIN_INT3_IRQn            = 27,   /**< \brief External Interrupt 3      */
    PIN_INT4_IRQn            = 28,   /**< \brief External Interrupt 4      */
    PIN_INT5_IRQn            = 29,   /**< \brief External Interrupt 5      */
    PIN_INT6_IRQn            = 30,   /**< \brief External Interrupt 6      */
    PIN_INT7_IRQn            = 31,   /**< \brief External Interrupt 7      */
} IRQn_Type;

/**
 * \endcond
 */


/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC82X_INUM_H */

/* end of file */
