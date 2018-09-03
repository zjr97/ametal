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
 * \brief ZLG217 �жϺŶ���
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __ZLG217_INUM_H
#define __ZLG217_INUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \addtogroup zlg217_if_inum
 * \copydoc zlg217_inum.h
 * @{
 */

/**
 * \name ZLG217 CPU �жϺ�
 * @{
 */

#define INUM_WWDG                 0    /**< \brief ���ڶ�ʱ���ж� */
#define INUM_PVD                  1    /**< \brief ��Դ��ѹ����ж� */
#define INUM_TAMPER               2    /**< \brief �������ж� */
#define INUM_RTC                  3    /**< \brief ʵʱʱ�ӣ�RTC��ȫ���ж� */
#define INUM_FLASH                4    /**< \brief ����ȫ���ж� */
#define INUM_RCC                  5    /**< \brief ��λ��ʱ�ӿ��ƣ�RCC���ж� */

#define INUM_EXTI0                6    /**< \brief EXTI��0�ж� */
#define INUM_EXTI1                7    /**< \brief EXTI��1�ж� */
#define INUM_EXTI2                8    /**< \brief EXTI��2�ж� */
#define INUM_EXTI3                9    /**< \brief EXTI��3�ж� */
#define INUM_EXTI4                10   /**< \brief EXTI��4�ж� */

#define INUM_DMA1_1               11   /**< \brief DMA1ͨ��1ȫ���ж� */
#define INUM_DMA1_2               12   /**< \brief DMA1ͨ��2ȫ���ж� */
#define INUM_DMA1_3               13   /**< \brief DMA1ͨ��3ȫ���ж� */
#define INUM_DMA1_4               14   /**< \brief DMA1ͨ��4ȫ���ж� */
#define INUM_DMA1_5               15   /**< \brief DMA1ͨ��5ȫ���ж� */
#define INUM_DMA1_6               16   /**< \brief DMA1ͨ��6ȫ���ж� */
#define INUM_DMA1_7               17   /**< \brief DMA1ͨ��7ȫ���ж� */

#define INUM_ADC1_2               18   /**< \brief ADC1��ADC2��ȫ���ж� */
#define INUM_USB                  19   /**< \brief USB�ж� */

#define INUM_CAN_RX1              21   /**< \brief CAN����1�ж� */

#define INUM_EXTI9_5              23   /**< \brief EXTI��[9��5]�ж� */
#define INUM_TIM1_BRK             24   /**< \brief TIM1�Ͽ��ж� */
#define INUM_TIM1_UP              25   /**< \brief TIM1�����ж� */
#define INUM_TIM1_TRG_COM         26   /**< \brief TIM1������ͨ���ж� */
#define INUM_TIM1_CC              27   /**< \brief TIM1����Ƚ��ж� */
#define INUM_TIM2                 28   /**< \brief TIM2ȫ���ж� */
#define INUM_TIM3                 29   /**< \brief TIM3ȫ���ж� */
#define INUM_TIM4                 30   /**< \brief TIM14ȫ���ж� */

#define INUM_I2C1_EV              31   /**< \brief I2C1�¼��ж� */

#define INUM_I2C2_EV              33   /**< \brief I2C1�¼��ж� */

#define INUM_SPI1                 35   /**< \brief SPI1ȫ���ж� */
#define INUM_SPI2                 36   /**< \brief SPI2ȫ���ж� */

#define INUM_UART1                37   /**< \brief UART1ȫ���ж� */
#define INUM_UART2                38   /**< \brief UART2ȫ���ж� */
#define INUM_UART3                39   /**< \brief UART3ȫ���ж� */

#define INUM_EXTI15_10            40   /**< \brief EXTI��[15��10]�ж� */
#define INUM_RTC_Alarm            41   /**< \brief ����EXTI17��RTC�����ж� */
#define INUM_USB_WK               42   /**< \brief ����EXTI18�Ĵ�USB���������ж� */

#define INUM_AES                  45   /**< \brief AESȫ���ж� */

/** @} */

/**
 * \brief ���ж���Ϊ��(INUM_USB - INUM_WWDT + 1),
 *
 */
#define INUM_INTERNAL_COUNT     (INUM_AES - INUM_WWDG + 1)

/**
 * \brief ����жϺ�Ϊ�� INUM_USB
 */
#define INUM_INTERNAL_MAX        INUM_AES

/** \brief ��С�жϺ�: INUM_WWDT */
#define INUM_INTERNAL_MIN        INUM_WWDG

/**
 * \cond
 * �жϺŶ��壬Ϊ core_cm3.h�ļ�����
 */
typedef enum {

    /* ----------------------  Cortex-M3���쳣��  ------------------- */

    /** \brief 2  ���������ж�, ���ܱ�ֹͣ����ռ */
    NonMaskableInt_IRQn      = -14,

    /** \brief 3  Ӳ�������ж� */
    HardFault_IRQn           = -13,

    /** \brief 11  ϵͳ�������ͨ��SVCָ�� */
    SVCall_IRQn              =  -5,

    /** \brief 14  ϵͳ�Ĺ������� */
    PendSV_IRQn              =  -2,

    /** \brief 15  ϵͳ�δ�ʱ�� */
    SysTick_IRQn             =  -1,

    /******  ZLG217 Specific Interrupt Numbers *******************************************************/
    WWDG_IRQn                = 0,         /**< \brief ���ڶ�ʱ���ж� */
    PVD_IRQn                  =1,         /**< \brief ��Դ��ѹ����ж� */
    TAMPER_IRQn               =2,         /**< \brief �������ж� */
    RTC_IRQn                  =3,         /**< \brief ʵʱʱ�ӣ�RTC��ȫ���ж� */
    FLASH_IRQn                =4,         /**< \brief ����ȫ���ж� */
    RCC_IRQn                  =5,         /**< \brief ��λ��ʱ�ӿ��ƣ�RCC���ж� */
    EXTI0_IRQn                =6,         /**< \brief EXTI��0�ж� */
    EXTI1_IRQn                =7,         /**< \brief EXTI��1�ж� */
    EXTI2_IRQn                =8,         /**< \brief EXTI��2�ж� */
    EXTI3_IRQn                =9,         /**< \brief EXTI��3�ж� */
    EXTI4_IRQn                =10,        /**< \brief EXTI��4�ж� */
    DMA1_1_IRQn               =11,        /**< \brief DMA1ͨ��1ȫ���ж� */
    DMA1_2_IRQn               =12,        /**< \brief DMA1ͨ��2ȫ���ж� */
    DMA1_3_IRQn               =13,        /**< \brief DMA1ͨ��3ȫ���ж� */
    DMA1_4_IRQn               =14,        /**< \brief DMA1ͨ��4ȫ���ж� */
    DMA1_5_IRQn               =15,        /**< \brief DMA1ͨ��5ȫ���ж� */
    DMA1_6_IRQn               =16,        /**< \brief DMA1ͨ��6ȫ���ж� */
    DMA1_7_IRQn               =17,        /**< \brief DMA1ͨ��7ȫ���ж� */
    ADC1_2_IRQn               =18,        /**< \brief ADC1��ADC2��ȫ���ж� */
    USB_IRQn                  =19,        /**< \brief USB�ж� */
    Reserved0                 =20,        /**< \brief RESERVED */
    CAN_RX1_IRQn              =21,        /**< \brief CAN����1�ж� */
    Reserved1                 =22,        /**< \brief RESERVED */
    EXTI9_5_IRQn              =23,        /**< \brief EXTI��[9��5]�ж� */
    TIM1_BRK_IRQn             =24,        /**< \brief TIM1�Ͽ��ж� */
    TIM1_UP_IRQn              =25,        /**< \brief TIM1�����ж� */
    TIM1_TRG_COM_IRQn         =26,        /**< \brief TIM1������ͨ���ж� */
    TIM1_CC_IRQn              =27,        /**< \brief TIM1����Ƚ��ж� */
    TIM2_IRQn                 =28,        /**< \brief TIM2ȫ���ж� */
    TIM3_IRQn                 =29,        /**< \brief TIM3ȫ���ж� */
    TIM4_IRQn                 =30,        /**< \brief TIM14ȫ���ж� */
    I2C1_EV_IRQn              =31,        /**< \brief I2C1�¼��ж� */
    Reserved2                 =32,        /**< \brief RESERVED */
    I2C2_EV_IRQn              =33,        /**< \brief I2C1�¼��ж� */
    Reserved3                 =34,        /**< \brief RESERVED */
    SPI1_IRQn                 =35,        /**< \brief SPI1ȫ���ж� */
    SPI2_IRQn                 =36,        /**< \brief SPI2ȫ���ж� */
    UART1_IRQn                =37,        /**< \brief UART1ȫ���ж� */
    UART2_IRQn                =38,        /**< \brief UART2ȫ���ж� */
    UART3_IRQn                =39,        /**< \brief UART3ȫ���ж� */
    EXTI15_10_IRQn            =40,        /**< \brief EXTI��[15��10]�ж� */
    RTCAlarm_IRQn             =41,        /**< \brief ����EXTI17��RTC�����ж� */
    USB_WK_IRQn               =42,        /**< \brief ����EXTI18�Ĵ�USB���������ж� */
    Reserved4                 =43,        /**< \brief RESERVED */
    Reserved5                 =44,        /**< \brief RESERVED */
    AES_IRQn                  =45,        /**< \brief AESȫ���ж� */
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

#endif /* __ZLG217_INUM_H */

/* end of file */
