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
 * \brief ZLG GPIO �������ò�������
 *
 * \note: �������Ź��ܵ�ʱ��һ��Ҫͬʱ�������ŵ�ģʽ����������ģʽ������ģʽ��
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-21  zcb, first implementation
 * \endinternal
 */

#ifndef __ZLG217_PIN_H
#define __ZLG217_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_zlg217_gpio_util.h"

 /**
 * \addtogroup zlg217_if_pin
 * \copydoc zlg217_pin.h
 * @{
 */

/**
 * \name ZLG217 GPIO ���ű��
 * \anchor grp_gpio_pin_number
 * @{
 */

#define PIOA            0         /**< \brief �˿�A������ʼ�� */
#define PIOA_0          0         /**< \brief PIOA_0 ���ź� */
#define PIOA_1          1         /**< \brief PIOA_1 ���ź� */
#define PIOA_2          2         /**< \brief PIOA_2 ���ź� */
#define PIOA_3          3         /**< \brief PIOA_3 ���ź� */
#define PIOA_4          4         /**< \brief PIOA_4 ���ź� */
#define PIOA_5          5         /**< \brief PIOA_5 ���ź� */
#define PIOA_6          6         /**< \brief PIOA_6 ���ź� */
#define PIOA_7          7         /**< \brief PIOA_7 ���ź� */
#define PIOA_8          8         /**< \brief PIOA_8 ���ź� */
#define PIOA_9          9         /**< \brief PIOA_9 ���ź� */
#define PIOA_10         10        /**< \brief PIOA_10 ���ź� */
#define PIOA_11         11        /**< \brief PIOA_11 ���ź� */
#define PIOA_12         12        /**< \brief PIOA_13 ���ź� */
#define PIOA_13         13        /**< \brief PIOA_13 ���ź� */
#define PIOA_14         14        /**< \brief PIOA_14 ���ź� */
#define PIOA_15         15        /**< \brief PIOA_15 ���ź� */

#define PIOB            16        /**< \brief �˿�B������ʼ�� */
#define PIOB_0          16        /**< \brief PIOB_8 ���ź� */
#define PIOB_1          17        /**< \brief PIOB_1 ���ź� */
#define PIOB_2          18        /**< \brief PIOB_2 ���ź� */
#define PIOB_3          19        /**< \brief PIOB_3 ���ź� */
#define PIOB_4          20        /**< \brief PIOB_4 ���ź� */
#define PIOB_5          21        /**< \brief PIOB_5 ���ź� */
#define PIOB_6          22        /**< \brief PIOB_3 ���ź� */
#define PIOB_7          23        /**< \brief PIOB_4 ���ź� */
#define PIOB_8          24        /**< \brief PIOB_5 ���ź� */
#define PIOB_9          25        /**< \brief PIOB_5 ���ź� */
#define PIOB_10         26        /**< \brief PIOB_10���ź� */
#define PIOB_11         27        /**< \brief PIOB_11���ź� */
#define PIOB_12         28        /**< \brief PIOB_12���ź� */
#define PIOB_13         29        /**< \brief PIOB_13���ź� */
#define PIOB_14         30        /**< \brief PIOB_14���ź� */
#define PIOB_15         31        /**< \brief PIOB_15���ź� */

#define PIOC            32        /**< \brief �˿�C������ʼ�� */
#define PIOC_0          32        /**< \brief PIOC_13���ź� */
#define PIOC_1          33        /**< \brief PIOC_13���ź� */
#define PIOC_2          34        /**< \brief PIOC_13���ź� */
#define PIOC_3          35        /**< \brief PIOC_13���ź� */
#define PIOC_4          36        /**< \brief PIOC_13���ź� */
#define PIOC_5          37        /**< \brief PIOC_13���ź� */
#define PIOC_6          38        /**< \brief PIOC_13���ź� */
#define PIOC_7          39        /**< \brief PIOC_13���ź� */
#define PIOC_8          40        /**< \brief PIOC_13���ź� */
#define PIOC_9          41        /**< \brief PIOC_13���ź� */
#define PIOC_10         42        /**< \brief PIOC_13���ź� */
#define PIOC_11         43        /**< \brief PIOC_13���ź� */
#define PIOC_12         44        /**< \brief PIOC_13���ź� */
#define PIOC_13         45        /**< \brief PIOC_13���ź� */
#define PIOC_14         46        /**< \brief PIOC_14���ź� */
#define PIOC_15         47        /**< \brief PIOC_15���ź� */

#define PIOD            48        /**< \brief �˿�D������ʼ�� */
#define PIOD_0          48        /**< \brief PIOD_0���ź� */
#define PIOD_1          49        /**< \brief PIOD_1���ź� */
#define PIOD_2          50        /**< \brief PIOD_2���ź� */
#define PIOD_3          51        /**< \brief PIOD_3���ź� */

/**
 * \brief ������ĿΪ39
 */
#define PIN_NUM         52

/**
 * \brief ֧��ͬʱ������������ж�����16
 */
#define PIN_INT_MAX     16

/** @} */

/**
 * \name ZLG217 ���Ŷ���,����������SWCK��SWIO֮�⣬�������Ÿ�λʱ��Ĭ��ΪGPIO����(��������)
 * @{
 */

/******************************************************************************/

/**
 * \name PIOA_0���Ÿ��ù���
 * @{
 */
#define PIOA_0_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_0_ADC1_IN0              PIOA_0_NO_REMAP   /**< \brief ADC1_IN0 */
#define PIOA_0_WKUP                  PIOA_0_NO_REMAP   /**< \brief WAKE_UP */
#define PIOA_0_UART2_CTS             PIOA_0_NO_REMAP   /**< \brief UART2_CTS */
#define PIOA_0_GPIO                  PIOA_0_NO_REMAP   /**< \brief GPIO */

#define PIOA_0_TIM2_CH1_ETR_REMAP0   AM_ZLG217_GPIO_REMAP_CODE(0x08, 0)   /**< \brief TIM2_CH1_ETR */
#define PIOA_0_TIM2_CH1_ETR_REMAP2   AM_ZLG217_GPIO_REMAP_CODE(0x08, 2)   /**< \brief TIM2_CH1_ETR */

/** @} */

/**
 * \name PIOA_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_0_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_0_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_0_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_0_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_0_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_0_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_0_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_0_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_0������Ӧ����
 * @{
 */

#define PIOA_0_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_0_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_0_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_1���Ÿ��ù���
 * @{
 */
#define PIOA_1_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_1_ADC1_IN1              PIOA_1_NO_REMAP   /**< \brief ADC1_IN1 */
#define PIOA_1_UART2_RTS             PIOA_1_NO_REMAP   /**< \brief UART2_RTS */
#define PIOA_1_GPIO                  PIOA_1_NO_REMAP   /**< \brief GPIO */

#define PIOA_1_TIM2_CH2_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x08, 0)   /**< \brief TIM2_CH2 */
#define PIOA_1_TIM2_CH2_REMAP2       AM_ZLG217_GPIO_REMAP_CODE(0x08, 2)   /**< \brief TIM2_CH2 */

/** @} */

/**
 * \name PIOA_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_1_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_1_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_1_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_1_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_1_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_1_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_1_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_1_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_1������Ӧ����
 * @{
 */

#define PIOA_1_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_1_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_1_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_2���Ÿ��ù���
 * @{
 */
#define PIOA_2_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_2_UART2_TX              PIOA_2_NO_REMAP   /**< \brief UART2_TX */
#define PIOA_2_ADC1_IN2              PIOA_2_NO_REMAP   /**< \brief ADC1_IN2 */
#define PIOA_2_GPIO                  PIOA_2_NO_REMAP   /**< \brief GPIO */

#define PIOA_2_TIM2_CH3_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x08, 0)   /**< \brief TIM2_CH3 */
#define PIOA_2_TIM2_CH3_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x08, 1)   /**< \brief TIM2_CH3 */
/** @} */

/**
 * \name PIOA_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_2_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_2_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_2_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_2_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_2_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_2_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_2_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_2_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_2������Ӧ����
 * @{
 */

#define PIOA_2_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_2_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_2_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_3���Ÿ��ù���
 * @{
 */
#define PIOA_3_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_3_ADC1_IN3              PIOA_3_NO_REMAP   /**< \brief ADC1_IN3 */
#define PIOA_3_UART2_RX              PIOA_3_NO_REMAP   /**< \brief UART2_RX */
#define PIOA_3_GPIO                  PIOA_3_NO_REMAP   /**< \brief GPIO */

#define PIOA_3_TIM2_CH4_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x08, 0)   /**< \brief TIM2_CH4 */
#define PIOA_3_TIM2_CH4_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x08, 1)   /**< \brief TIM2_CH4 */

/** @} */

/**
 * \name PIOA_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_3_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_3_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_3_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_3_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_3_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_3_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_3_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_3_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_3������Ӧ����
 * @{
 */

#define PIOA_3_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_3_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_3_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_4���Ÿ��ù���
 * @{
 */
#define PIOA_4_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_4_ADC1_IN4              PIOA_4_NO_REMAP    /**< \brief ADC1_IN4 */
#define PIOA_4_DAC1_OUT              PIOA_4_NO_REMAP    /**< \brief DAC1_OUT */
#define PIOA_4_GPIO                  PIOA_4_NO_REMAP    /**< \brief GPIO */
#define PIOA_4_SPI1_NSS              PIOA_4_NO_REMAP    /**< \brief SPI1_NSS */

/** @} */

/**
 * \name PIOA_4���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_4_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_4_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_4_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_4_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_4_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_4_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_4_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_4_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_4������Ӧ����
 * @{
 */

#define PIOA_4_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_4_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_4_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_5���Ÿ��ù���
 * @{
 */
#define PIOA_5_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_5_ADC1_IN5              PIOA_5_NO_REMAP   /**< \brief ADC1_IN5 */
#define PIOA_5_DAC2_OUT              PIOA_5_NO_REMAP   /**< \brief DAC2_OUT */
#define PIOA_5_GPIO                  PIOA_5_NO_REMAP   /**< \brief GPIO */

#define PIOA_5_SPI1_SCK_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x00, 0)   /**< \brief SPI1_SCK */

/** @} */

/**
 * \name PIOA_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_5_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_5_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_5_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_5_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_5_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_5_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_5_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_5_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_5������Ӧ����
 * @{
 */

#define PIOA_5_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_5_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_5_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_6���Ÿ��ù���
 * @{
 */
#define PIOA_6_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_6_ADC1_IN6              PIOA_6_NO_REMAP   /**< \brief ADC1_IN6 */
#define PIOA_6_GPIO                  PIOA_6_NO_REMAP   /**< \brief GPIO */

#define PIOA_6_SPI1_MISO_REMAP0      AM_ZLG217_GPIO_REMAP_CODE(0x00, 0)   /**< \brief SPI1_MISO */
#define PIOA_6_TIM3_CH1_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x0A, 0)   /**< \brief TIM3_CH3 */
#define PIOA_6_TIM1_BAKIN_REMAP1      AM_ZLG217_GPIO_REMAP_CODE(0x06, 1)   /**< \brief TIM1_BAKIN */

/** @} */

/**
 * \name PIOA_6���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_6_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_6_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_6_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_6_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_6_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_6_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_6_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_6_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_6������Ӧ����
 * @{
 */

#define PIOA_6_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_6_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_6_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_7���Ÿ��ù���
 * @{
 */
#define PIOA_7_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_7_ADC1_IN7              PIOA_7_NO_REMAP   /**< \brief ADC1_IN7 */
#define PIOA_7_GPIO                  PIOA_7_NO_REMAP   /**< \brief GPIO */

#define PIOA_7_SPI1_MOSI_REMAP0      AM_ZLG217_GPIO_REMAP_CODE(0x00, 0)   /**< \brief SPI1_MOSI */
#define PIOA_7_TIM3_CH2_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x0A, 0)   /**< \brief TIM3_CH2 */
#define PIOA_7_TIM1_CH1N_REMAP1      AM_ZLG217_GPIO_REMAP_CODE(0x06, 1)   /**< \brief TIM1_CH1N */
/** @} */

/**
 * \name PIOA_7���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_7_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_7_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_7_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_7_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_7_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_7_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_7_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_7_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_7������Ӧ����
 * @{
 */

#define PIOA_7_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_7_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_7_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_8���Ÿ��ù���
 * @{
 */
#define PIOA_8_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_8_MCO                   PIOA_8_NO_REMAP   /**< \brief MCO */
#define PIOA_8_GPIO                  PIOA_8_NO_REMAP   /**< \brief GPIO */

#define PIOA_8_TIM1_CH1_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x06, 0)   /**< \brief TIM1_CH1 */
#define PIOA_8_TIM1_CH1_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x06, 1)   /**< \brief TIM1_CH1 */

/** @} */

/**
 * \name PIOA_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_8_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_8_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_8_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_8_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_8_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_8_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_8_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_8_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_8������Ӧ����
 * @{
 */

#define PIOA_8_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_8_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_8_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_9���Ÿ��ù���
 * @{
 */
#define PIOA_9_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_9_GPIO                  PIOA_9_NO_REMAP   /**< \brief GPIO */

#define PIOA_9_UART1_TX_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x02, 0)   /**< \brief UART1_TX */
#define PIOA_9_TIM1_CH2_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x06, 0)   /**< \brief TIM1_CH2 */
#define PIOA_9_TIM1_CH2_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x06, 1)   /**< \brief TIM1_CH2 */

/** @} */

/**
 * \name PIOA_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_9_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_9_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_9_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_9_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_9_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_9_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_9_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_9_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_9������Ӧ����
 * @{
 */

#define PIOA_9_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_9_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_9_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_10���Ÿ��ù���
 * @{
 */
#define PIOA_10_NO_REMAP             AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_10_GPIO                 PIOA_10_NO_REMAP   /**< \brief GPIO */

#define PIOA_10_UART1_RX_REMAP0      AM_ZLG217_GPIO_REMAP_CODE(0x02, 0)   /**< \brief UART1_RX */
#define PIOA_10_TIM1_CH3_REMAP0      AM_ZLG217_GPIO_REMAP_CODE(0x06, 0)   /**< \brief TIM1_CH3 */
#define PIOA_10_TIM1_CH3_REMAP1      AM_ZLG217_GPIO_REMAP_CODE(0x06, 1)   /**< \brief TIM1_CH3 */
/** @} */

/**
 * \name PIOA_10���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_10_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_10_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_10_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_10_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_10_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_10_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_10_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_10_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_10������Ӧ����
 * @{
 */

#define PIOA_10_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_10_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_10_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_11���Ÿ��ù���
 * @{
 */
#define PIOA_11_NO_REMAP             AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_11_UART1_CTS            PIOA_11_NO_REMAP   /**< \brief UART1_CTS */
#define PIOA_11_USBDM                PIOA_11_NO_REMAP   /**< \brief USBDM */
#define PIOA_11_GPIO                 PIOA_11_NO_REMAP   /**< \brief GPIO */

#define PIOA_11_TIM1_CH4_REMAP0      AM_ZLG217_GPIO_REMAP_CODE(0X06, 0)  /**< \brief TIM1_CH4 */
#define PIOA_11_TIM1_CH4_REMAP1      AM_ZLG217_GPIO_REMAP_CODE(0X06, 1)  /**< \brief TIM1_CH4 */
#define PIOA_11_CAN_RX_REMAP0        AM_ZLG217_GPIO_REMAP_CODE(0X0D, 0)  /**< \brief CAN_RX */
/** @} */

/**
 * \name PIOA_11���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_11_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_11_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_11_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_11_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_11_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_11_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_11_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_11_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_11������Ӧ����
 * @{
 */

#define PIOA_11_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_11_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_11_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_12���Ÿ��ù���
 * @{
 */
#define PIOA_12_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_12_UART1_RTS             PIOA_12_NO_REMAP   /**< \brief UART1_RTS */
#define PIOA_12_USBDP                 PIOA_12_NO_REMAP
#define PIOA_12_GPIO                  PIOA_12_NO_REMAP   /**< \brief GPIO */

#define PIOA_12_CAN_TX_REMAP0         AM_ZLG217_GPIO_REMAP_CODE(0x0D, 0)   /**< \brief CAN_TX */
#define PIOA_12_TIM1_ETR_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x06, 0)   /**< \brief TIM1_ETR */
#define PIOA_12_TIM1_ETR_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x06, 1)   /**< \brief TIM1_ETR */

/** @} */

/**
 * \name PIOA_12���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_12_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_12_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_12_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_12_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_12_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_12_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_12_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_12_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_12������Ӧ����
 * @{
 */

#define PIOA_12_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_12_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_12_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_13���Ÿ��ù���
 * @{
 */
#define PIOA_13_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_13_GPIO                  PIOA_13_NO_REMAP   /**< \brief GPIO */

#define PIOA_13_SWDIO                 AM_ZLG217_GPIO_REMAP_CODE(0x10, 0)   /**< \brief SWDIO */

/** @} */

/**
 * \name PIOA_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_13_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_13_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_13_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_13_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_13_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_13_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_13_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_13_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_13������Ӧ����
 * @{
 */

#define PIOA_13_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_13_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_13_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_14���Ÿ��ù���
 * @{
 */
#define PIOA_14_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_14_GPIO                  PIOA_14_NO_REMAP   /**< \brief GPIO */

#define PIOA_14_SWDCLK                AM_ZLG217_GPIO_REMAP_CODE(0x10, 0)   /**< \brief SWDCLK */

/** @} */

/**
 * \name PIOA_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_14_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_14_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_14_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_14_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_14_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_14_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_14_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_14_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_14������Ӧ����
 * @{
 */

#define PIOA_14_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_14_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_14_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_15���Ÿ��ù���
 * @{
 */
#define PIOA_15_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOA_15_SPI1_NSS              PIOA_15_NO_REMAP   /**< \brief SPI1_NSS */
#define PIOA_15_GPIO                  PIOA_15_NO_REMAP   /**< \brief GPIO */

#define PIOA_15_TIM2_CH1_ETR_REMAP1   AM_ZLG217_GPIO_REMAP_CODE(0x08, 1)   /**< \brief TIM2_CH1_ETR */
#define PIOA_15_TIM2_CH1_ETR_REMAP3   AM_ZLG217_GPIO_REMAP_CODE(0x08, 3)   /**< \brief TIM2_CH1_ETR */
#define PIOA_15_JTDI                  AM_ZLG217_GPIO_REMAP_CODE(0x10, 0)   /**< \brief JTDI */

/** @} */

/**
 * \name PIOA_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_15_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_15_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_15_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_15_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_15_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_15_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_15_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_15_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_15������Ӧ����
 * @{
 */

#define PIOA_15_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_15_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_15_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_0���Ÿ��ù���
 * @{
 */
#define PIOB_0_NO_REMAP               AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_0_ADC2_IN0               PIOB_0_NO_REMAP   /**< \brief ADC2_IN0 */
#define PIOB_0_GPIO                   PIOB_0_NO_REMAP   /**< \brief GPIO */

#define PIOB_0_TIM3_CH3_REMAP0        AM_ZLG217_GPIO_REMAP_CODE(0x0A, 0)   /**< \brief TIM3_CH3 */
#define PIOB_0_TIM3_CH3_REMAP2        AM_ZLG217_GPIO_REMAP_CODE(0x0A, 2)   /**< \brief TIM3_CH3 */
#define PIOB_0_TIM1_CH2N_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0X06, 1)   /**< \brief TIM1_CH2N */
/** @} */

/**
 * \name PIOB_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_0_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_0_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_0_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_0_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_0_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_0_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_0_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_0_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_0������Ӧ����
 * @{
 */

#define PIOB_0_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_0_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_0_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_1���Ÿ��ù���
 * @{
 */
#define PIOB_1_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_1_ADC2_IN1              PIOB_1_NO_REMAP   /**< \brief ADC2_IN1 */
#define PIOB_1_GPIO                  PIOB_1_NO_REMAP   /**< \brief GPIO */

#define PIOB_1_TIM3_CH4_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x0A, 0)   /**< \brief TIM3_CH4 */
#define PIOB_1_TIM3_CH4_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x0A, 1)   /**< \brief TIM3_CH4 */
#define PIOB_1_TIM1_CH3N_REMAP1      AM_ZLG217_GPIO_REMAP_CODE(0x06, 1)   /**< \brief TIM1_CH3N */

/** @} */

/**
 * \name PIOB_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_1_AIN                  AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_1_INPUT_FLOAT          AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_1_INPUT_PD             AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_1_INPUT_PU             AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_1_OUT_PP               AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_1_OUT_OD               AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_1_AF_PP                AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_1_AF_OD                AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_1������Ӧ����
 * @{
 */

#define PIOB_1_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_1_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_1_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_2���Ÿ��ù���
 * @{
 */
#define PIOB_2_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_2_GPIO                  PIOB_2_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_2_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_2_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_2_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_2_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_2_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_2_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_2_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_2_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_2������Ӧ����
 * @{
 */

#define PIOB_2_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_2_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_2_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_3���Ÿ��ù���
 * @{
 */
#define PIOB_3_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_3_GPIO                  PIOB_3_NO_REMAP   /**< \brief GPIO */

#define PIOB_3_TRACESWO              AM_ZLG217_GPIO_REMAP_CODE(0x10, 0)   /**< \brief TRACESWO */
#define PIOB_3_TIM2_CH2_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x08, 1)   /**< \brief TIM2_CH2 */
#define PIOB_3_TIM2_CH2_REMAP3       AM_ZLG217_GPIO_REMAP_CODE(0x08, 3)   /**< \brief TIM2_CH2 */
#define PIOB_3_SPI1_SCK_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x00, 1)   /**< \brief SPI1_SCK */

/** @} */

/**
 * \name PIOB_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_3_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_3_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_3_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_3_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_3_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_3_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_3_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_3_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_3������Ӧ����
 * @{
 */

#define PIOB_3_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_3_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_3_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_4���Ÿ��ù���
 * @{
 */
#define PIOB_4_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_4_GPIO                  PIOB_4_NO_REMAP   /**< \brief GPIO */

#define PIOB_4_TIM3_CH1_REMAP2       AM_ZLG217_GPIO_REMAP_CODE(0x0A, 2)   /**< \brief TIM3_CH1 */
#define PIOB_4_SPI1_MISO_REMAP1      AM_ZLG217_GPIO_REMAP_CODE(0x00, 1)   /**< \brief SPI1_MISO */
#define PIOB_4_JNTRST                AM_ZLG217_GPIO_REMAP_CODE(0x10, 0)   /**< \brief JNTRST */
/** @} */

/**
 * \name PIOB_4���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_4_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_4_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_4_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_4_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_4_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_4_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_4_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_4_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_4������Ӧ����
 * @{
 */

#define PIOB_4_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_4_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_4_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_5���Ÿ��ù���
 * @{
 */

#define PIOB_5_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_5_GPIO                  PIOB_5_NO_REMAP   /**< \brief GPIO */
#define PIOB_5_I2C1_SMBAI            PIOB_5_NO_REMAP   /**< \brief I2C1_SMBAI */

#define PIOB_5_TIM3_CH2_REMAP2       AM_ZLG217_GPIO_REMAP_CODE(0x0A, 2)   /**< \brief TIM3_CH2 */
#define PIOB_5_SPI1_MOSI_REMAP1      AM_ZLG217_GPIO_REMAP_CODE(0x00, 1)   /**< \brief SPI1_MOSI */

/** @} */

/**
 * \name PIOB_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_5_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_5_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_5_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_5_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_5_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_5_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_5_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_5_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_5������Ӧ����
 * @{
 */

#define PIOB_5_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_5_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_5_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_6���Ÿ��ù���
 * @{
 */

#define PIOB_6_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_6_GPIO                  PIOB_6_NO_REMAP   /**< \brief GPIO */
#define PIOB_6_TIM4_CH1              PIOB_6_NO_REMAP   /**< \brief TIM4_CH1 */

#define PIOB_6_I2C1_SCL_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x01, 0)   /**< \brief I2C1_SCL */
#define PIOB_6_UART1_TX_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x02, 1)   /**< \brief UART1_TX */

/** @} */

/**
 * \name PIOB_6���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_6_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_6_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_6_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_6_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_6_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_6_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_6_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_6_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_6������Ӧ����
 * @{
 */

#define PIOB_6_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_6_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_6_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_7���Ÿ��ù���
 * @{
 */

#define PIOB_7_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_7_TIM4_CH2              PIOB_7_NO_REMAP   /**< \brief TIM4_CH2 */
#define PIOB_7_GPIO                  PIOB_7_NO_REMAP   /**< \brief GPIO */

#define PIOB_7_I2C1_SDA_REMAP0       AM_ZLG217_GPIO_REMAP_CODE(0x01, 0)   /**< \brief I2C1_SDA */
#define PIOB_7_UART1_RX_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x02, 1)   /**< \brief UART1_RX */

/** @} */

/**
 * \name PIOB_7�ܽŸ���ʱ���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_7_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_7_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_7_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_7_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_7_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_7_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_7_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_7_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_7������Ӧ����
 * @{
 */

#define PIOB_7_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_7_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_7_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_8���Ÿ��ù���
 * @{
 */

#define PIOB_8_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_8_TIM4_CH3              PIOB_8_NO_REMAP   /**< \brief TIM4_CH3 */
#define PIOB_8_GPIO                  PIOB_8_NO_REMAP   /**< \brief GPIO */

#define PIOB_8_I2C1_SCL_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x01, 1)   /**< \brief I2C1_SCL */
#define PIOB_8_CAN_RX_REMAP2         AM_ZLG217_GPIO_REMAP_CODE(0x0D, 2)   /**< \brief CAN_RX */

/** @} */

/**
 * \name PIOB_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_8_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_8_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_8_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_8_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_8_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_8_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_8_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_8_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_8������Ӧ����
 * @{
 */

#define PIOB_8_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_8_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_8_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_9���Ÿ��ù���
 * @{
 */

#define PIOB_9_NO_REMAP              AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_9_TIM4_CH4              PIOB_9_NO_REMAP   /**< \brief TIM4_CH4 */
#define PIOB_9_GPIO                  PIOB_9_NO_REMAP   /**< \brief GPIO */

#define PIOB_9_I2C1_SDA_REMAP1       AM_ZLG217_GPIO_REMAP_CODE(0x01, 1)   /**< \brief I2C1_SDA */
#define PIOB_9_CAN_TX_REMAP2         AM_ZLG217_GPIO_REMAP_CODE(0x0D, 2)   /**< \brief CAN_TX */

/** @} */

/**
 * \name PIOB_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_9_AIN                   AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_9_INPUT_FLOAT           AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_9_INPUT_PD              AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_9_INPUT_PU              AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_9_OUT_PP                AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_9_OUT_OD                AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_9_AF_PP                 AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_9_AF_OD                 AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_9������Ӧ����
 * @{
 */

#define PIOB_9_SPEED_10MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_9_SPEED_2MHz            AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_9_SPEED_50MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_10���Ÿ��ù���
 * @{
 */

#define PIOB_10_NO_REMAP             AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_10_I2C2_SCL             PIOB_10_NO_REMAP   /**< \brief I2C2_SCL */
#define PIOB_10_GPIO                 PIOB_10_NO_REMAP   /**< \brief GPIO */

#define PIOB_10_UART3_TX_REMAP0      AM_ZLG217_GPIO_REMAP_CODE(0x04, 0)   /**< \brief UART3_TX */
#define PIOB_10_TIM2_CH3_REMAP2      AM_ZLG217_GPIO_REMAP_CODE(0x08, 2)   /**< \brief TIM2_CH3 */
#define PIOB_10_TIM2_CH3_REMAP3      AM_ZLG217_GPIO_REMAP_CODE(0x08, 3)   /**< \brief TIM2_CH3 */

/** @} */

/**
 * \name PIOB_10���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_10_AIN                  AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_10_INPUT_FLOAT          AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_10_INPUT_PD             AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_10_INPUT_PU             AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_10_OUT_PP               AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_10_OUT_OD               AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_10_AF_PP                AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_10_AF_OD                AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_10������Ӧ����
 * @{
 */

#define PIOB_10_SPEED_10MHz          AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_10_SPEED_2MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_10_SPEED_50MHz          AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_11���Ÿ��ù���
 * @{
 */

#define PIOB_11_NO_REMAP             AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_11_I2C2_SDA             PIOB_11_NO_REMAP   /**< \brief I2C2_SDA */
#define PIOB_11_GPIO                 PIOB_11_NO_REMAP   /**< \brief GPIO */

#define PIOB_11_UART3_RX_REMAP0      AM_ZLG217_GPIO_REMAP_CODE(0x04, 0)   /**< \brief UART3_RX */
#define PIOB_11_TIM2_CH4_REMAP2      AM_ZLG217_GPIO_REMAP_CODE(0x08, 2)   /**< \brief TIM2_CH4 */
#define PIOB_11_TIM2_CH4_REMAP3      AM_ZLG217_GPIO_REMAP_CODE(0x08, 3)   /**< \brief TIM2_CH4 */

/** @} */

/**
 * \name PIOB_11���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_11_AIN                  AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_11_INPUT_FLOAT          AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_11_INPUT_PD             AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_11_INPUT_PU             AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_11_OUT_PP               AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_11_OUT_OD               AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_11_AF_PP                AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_11_AF_OD                AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_11������Ӧ����
 * @{
 */

#define PIOB_11_SPEED_10MHz          AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_11_SPEED_2MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_11_SPEED_50MHz          AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_12���Ÿ��ù���
 * @{
 */

#define PIOB_12_NO_REMAP             AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_12_SPI2_NSS             PIOB_12_NO_REMAP   /**< \brief SPI2_NSS */
#define PIOB_12_I2C2_SMBAI           PIOB_12_NO_REMAP   /**< \brief I2C2_SMBAI */
#define PIOB_12_GPIO                 PIOB_12_NO_REMAP   /**< \brief GPIO */

#define PIOB_12_TIM1_BAKIN_REMAP0     AM_ZLG217_GPIO_REMAP_CODE(0x06, 0)   /**< \brief TIM1_BAKIN */

/** @} */

/**
 * \name PIOB_12���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_12_AIN                  AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_12_INPUT_FLOAT          AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_12_INPUT_PD             AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_12_INPUT_PU             AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_12_OUT_PP               AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_12_OUT_OD               AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_12_AF_PP                AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_12_AF_OD                AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_12������Ӧ����
 *
 * @{
 */

#define PIOB_12_SPEED_10MHz          AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_12_SPEED_2MHz           AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_12_SPEED_50MHz          AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_13���Ÿ��ù���
 * @{
 */

#define PIOB_13_NO_REMAP            AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_13_SPI2_SCK            PIOB_13_NO_REMAP   /**< \brief SPI2_SCK */
#define PIOB_13_UART3_CTS           PIOB_13_NO_REMAP   /**< \brief UART3_CTS */
#define PIOB_13_GPIO                PIOB_13_NO_REMAP   /**< \brief GPIO */

#define PIOB_13_TIM1_CH1N_REMAP0    AM_ZLG217_GPIO_REMAP_CODE(0x06, 0)   /**< \brief TIM1_CH1N */

/** @} */

/**
 * \name PIOB_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_13_AIN                 AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_13_INPUT_FLOAT         AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_13_INPUT_PD            AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_13_INPUT_PU            AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_13_OUT_PP              AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_13_OUT_OD              AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_13_AF_PP               AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_13_AF_OD               AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_13������Ӧ����
 * @{
 */

#define PIOB_13_SPEED_10MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_13_SPEED_2MHz          AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_13_SPEED_50MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_14���Ÿ��ù���
 * @{
 */

#define PIOB_14_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_14_SPI2_MISO          PIOB_14_NO_REMAP   /**< \brief SPI2_MISO */
#define PIOB_14_UART3_RTS          PIOB_14_NO_REMAP   /**< \brief UART3_RTS */
#define PIOB_14_GPIO               PIOB_14_NO_REMAP   /**< \brief GPIO */

#define PIOB_14_TIM1_CH2N_REMAP0   AM_ZLG217_GPIO_REMAP_CODE(0x06, 0)   /**< \brief TIM1_CH2N */

/** @} */

/**
 * \name PIOB_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_14_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_14_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_14_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_14_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_14_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_14_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_14_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_14_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_14������Ӧ����
 * @{
 */

#define PIOB_14_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_14_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_14_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_15���Ÿ��ù���
 * @{
 */

#define PIOB_15_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOB_15_SPI2_MOSI          PIOB_15_NO_REMAP   /**< \brief SPI2_MOSI */
#define PIOB_15_GPIO               PIOB_15_NO_REMAP   /**< \brief GPIO */

#define PIOB_15_TIM1_CH3N_REMAP0   AM_ZLG217_GPIO_REMAP_CODE(0x06, 0)   /**< \brief TIM1_CH3N */

/** @} */

/**
 * \name PIOB_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_15_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_15_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_15_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_15_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_15_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_15_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_15_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_15_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_15������Ӧ����
 * @{
 */

#define PIOB_15_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_15_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_15_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_0���Ÿ��ù���
 * @{
 */
#define PIOC_0_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_0_ADC2_IN2           PIOC_0_NO_REMAP   /**< \brief ADC2_IN2 */
#define PIOC_0_GPIO               PIOC_0_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_0_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_0_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_0_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_0_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_0_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_0_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_0_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_0_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_0������Ӧ����
 * @{
 */

#define PIOC_0_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_0_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_0_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_1���Ÿ��ù���
 * @{
 */
#define PIOC_1_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_1_ADC2_IN3           PIOC_1_NO_REMAP   /**< \brief ADC2_IN3 */
#define PIOC_1_GPIO               PIOC_1_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_1_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_1_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_1_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_1_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_1_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_1_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_1_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_1_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_1������Ӧ����
 * @{
 */

#define PIOC_1_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_1_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_1_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_2���Ÿ��ù���
 * @{
 */
#define PIOC_2_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_2_ADC2_IN4           PIOC_2_NO_REMAP   /**< \brief ADC2_IN4 */
#define PIOC_2_GPIO               PIOC_2_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_2_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_2_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_2_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_2_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_2_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_2_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_2_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_2_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_2������Ӧ����
 * @{
 */

#define PIOC_2_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_2_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_2_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_3���Ÿ��ù���
 * @{
 */

#define PIOC_3_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_3_ADC2_IN5           PIOC_3_NO_REMAP   /**< \brief ADC2_IN5 */
#define PIOC_3_GPIO               PIOC_3_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_3_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_3_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_3_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_3_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_3_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_3_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_3_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_3_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_3������Ӧ����
 * @{
 */

#define PIOC_3_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_3_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_3_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_4���Ÿ��ù���
 * @{
 */

#define PIOC_4_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_4_ADC2_IN6           PIOC_4_NO_REMAP   /**< \brief ADC2_IN6 */
#define PIOC_4_GPIO               PIOC_4_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_4���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_4_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_4_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_4_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_4_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_4_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_4_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_4_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_4_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_4������Ӧ����
 * @{
 */

#define PIOC_4_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_4_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_4_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_5���Ÿ��ù���
 * @{
 */

#define PIOC_5_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_5_ADC2_IN7           PIOC_5_NO_REMAP   /**< \brief ADC2_IN7 */
#define PIOC_5_GPIO               PIOC_5_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_5_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_5_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_5_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_5_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_5_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_5_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_5_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_5_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_5������Ӧ����
 * @{
 */

#define PIOC_5_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_5_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_5_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_6���Ÿ��ù���
 * @{
 */

#define PIOC_6_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_6_GPIO               PIOC_6_NO_REMAP   /**< \brief GPIO */

#define PIOC_6_TIM3_CH1_REMAP3    AM_ZLG217_GPIO_REMAP_CODE(0X0A, 3)   /**< \brief TIM3_CH1 */

/** @} */

/**
 * \name PIOC_6���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_6_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_6_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_6_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_6_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_6_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_6_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_6_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_6_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_6������Ӧ����
 * @{
 */

#define PIOC_6_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_6_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_6_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_7���Ÿ��ù���
 * @{
 */

#define PIOC_7_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_7_GPIO               PIOC_7_NO_REMAP   /**< \brief GPIO */

#define PIOC_7_TIM3_CH2_REMAP3    AM_ZLG217_GPIO_REMAP_CODE(0x0A, 3)   /**< \brief TIM3_CH2 */

/** @} */

/**
 * \name PIOC_7���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_7_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_7_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_7_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_7_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_7_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_7_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_7_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_7_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_7������Ӧ����
 * @{
 */

#define PIOC_7_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_7_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_7_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_8���Ÿ��ù���
 * @{
 */

#define PIOC_8_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_8_GPIO               PIOC_8_NO_REMAP   /**< \brief GPIO */

#define PIOC_8_TIM3_CH3_REMAP3    AM_ZLG217_GPIO_REMAP_CODE(0x0A, 3)   /**< \brief TIM3_CH3 */

/** @} */

/**
 * \name PIOC_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_8_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_8_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_8_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_8_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_8_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_8_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_8_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_8_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_8������Ӧ����
 * @{
 */

#define PIOC_8_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_8_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_8_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_9���Ÿ��ù���
 * @{
 */

#define PIOC_9_NO_REMAP           AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_9_GPIO               PIOC_9_NO_REMAP   /**< \brief GPIO */

#define PIOC_9_TIM3_CH4_REMAP3    AM_ZLG217_GPIO_REMAP_CODE(0x0A, 3)   /**< \brief TIM3_CH4 */

/** @} */

/**
 * \name PIOC_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_9_AIN                AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_9_INPUT_FLOAT        AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_9_INPUT_PD           AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_9_INPUT_PU           AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_9_OUT_PP             AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_9_OUT_OD             AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_9_AF_PP              AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_9_AF_OD              AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_9������Ӧ����
 * @{
 */

#define PIOC_9_SPEED_10MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_9_SPEED_2MHz         AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_9_SPEED_50MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_10���Ÿ��ù���
 * @{
 */

#define PIOC_10_NO_REMAP          AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_10_GPIO              PIOC_10_NO_REMAP   /**< \brief GPIO */

#define PIOC_10_UART3_TX_REMAP1   AM_ZLG217_GPIO_REMAP_CODE(0x04, 1)   /**< \brief UART3_TX */

/** @} */

/**
 * \name PIOC_10���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_10_AIN               AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_10_INPUT_FLOAT       AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_10_INPUT_PD          AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_10_INPUT_PU          AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_10_OUT_PP            AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_10_OUT_OD            AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_10_AF_PP             AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_10_AF_OD             AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_10������Ӧ����
 * @{
 */

#define PIOC_10_SPEED_10MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_10_SPEED_2MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_10_SPEED_50MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_11���Ÿ��ù���
 * @{
 */

#define PIOC_11_NO_REMAP          AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_11_GPIO              PIOC_11_NO_REMAP   /**< \brief GPIO */

#define PIOC_11_UART3_RX_REMAP1   AM_ZLG217_GPIO_REMAP_CODE(0x04, 1)   /**< \brief UART3_RX */

/** @} */

/**
 * \name PIOC_11���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_11_AIN               AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_11_INPUT_FLOAT       AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_11_INPUT_PD          AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_11_INPUT_PU          AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_11_OUT_PP            AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_11_OUT_OD            AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_11_AF_PP             AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_11_AF_OD             AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_11������Ӧ����
 * @{
 */

#define PIOC_11_SPEED_10MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_11_SPEED_2MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_11_SPEED_50MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_12���Ÿ��ù���
 * @{
 */

#define PIOC_12_NO_REMAP          AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_12_GPIO              PIOC_12_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_12���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_12_AIN               AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_12_INPUT_FLOAT       AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_12_INPUT_PD          AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_12_INPUT_PU          AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_12_OUT_PP            AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_12_OUT_OD            AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_12_AF_PP             AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_12_AF_OD             AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_12������Ӧ����
 * @{
 */

#define PIOC_12_SPEED_10MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_12_SPEED_2MHz        AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_12_SPEED_50MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_13���Ÿ��ù���
 * @{
 */

#define PIOC_13_NO_REMAP         AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_13_TAMPER_RTC       PIOC_13_NO_REMAP   /**< \brief TAMPER_RTC */
#define PIOC_13_GPIO             PIOC_13_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_13_AIN              AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_13_INPUT_FLOAT      AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_13_INPUT_PD         AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_13_INPUT_PU         AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_13_OUT_PP           AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_13_OUT_OD           AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_13_AF_PP            AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_13_AF_OD            AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_13������Ӧ����
 * @{
 */

#define PIOC_13_SPEED_10MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_13_SPEED_2MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_13_SPEED_50MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_14���Ÿ��ù���
 * @{
 */

#define PIOC_14_NO_REMAP        AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_14_OSC32_IN        PIOC_14_NO_REMAP   /**< \brief OSC32_IN */
#define PIOC_14_GPIO            PIOC_14_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_14_AIN             AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_14_INPUT_FLOAT     AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_14_INPUT_PD        AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_14_INPUT_PU        AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_14_OUT_PP          AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_14_OUT_OD          AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_14_AF_PP           AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_14_AF_OD           AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_14������Ӧ����
 * @{
 */

#define PIOC_14_SPEED_10MHz     AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_14_SPEED_2MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_14_SPEED_50MHz     AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_15���Ÿ��ù���
 * @{
 */

#define PIOC_15_NO_REMAP        AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOC_15_OSC32_OUT       PIOC_15_NO_REMAP   /**< \brief OSC32_OUT */
#define PIOC_15_GPIO            PIOC_15_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_15_AIN             AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_15_INPUT_FLOAT     AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_15_INPUT_PD        AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_15_INPUT_PU        AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_15_OUT_PP          AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_15_OUT_OD          AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_15_AF_PP           AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_15_AF_OD           AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_15������Ӧ����
 * @{
 */

#define PIOC_15_SPEED_10MHz     AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_15_SPEED_2MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_15_SPEED_50MHz     AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_0���Ÿ��ù���
 * @{
 */

#define PIOD_0_NO_REMAP         AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOD_0_OSC_IN           PIOD_0_NO_REMAP   /**< \brief OSC_IN */
#define PIOD_0_GPIO             PIOD_0_NO_REMAP    /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_0_AIN              AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_0_INPUT_FLOAT      AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_0_INPUT_PD         AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_0_INPUT_PU         AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_0_OUT_PP           AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_0_OUT_OD           AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_0_AF_PP            AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_0_AF_OD            AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_0������Ӧ����
 * @{
 */

#define PIOD_0_SPEED_10MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_0_SPEED_2MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_0_SPEED_50MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_1���Ÿ��ù���
 * @{
 */

#define PIOD_1_NO_REMAP         AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOD_1_OSC_OUT          PIOD_1_NO_REMAP   /**< \brief OSC_OUT */
#define PIOD_1_GPIO             PIOD_1_NO_REMAP   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_1_AIN              AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_1_INPUT_FLOAT      AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_1_INPUT_PD         AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_1_INPUT_PU         AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_1_OUT_PP           AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_1_OUT_OD           AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_1_AF_PP            AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_1_AF_OD            AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_1������Ӧ����
 * @{
 */

#define PIOD_1_SPEED_10MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_1_SPEED_2MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_1_SPEED_50MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_2���Ÿ��ù���
 * @{
 */

#define PIOD_2_NO_REMAP         AM_ZLG217_GPIO_REMAP_CODE(0x11, 0)
#define PIOD_2_GPIO             PIOD_2_NO_REMAP   /**< \brief GPIO */
#define PIOD_2_TIM3_ETR         PIOD_2_NO_REMAP   /**< \brief TIM3_ETR */

/** @} */

/**
 * \name PIOD_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_2_AIN              AM_ZLG217_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_2_INPUT_FLOAT      AM_ZLG217_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_2_INPUT_PD         AM_ZLG217_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_2_INPUT_PU         AM_ZLG217_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_2_OUT_PP           AM_ZLG217_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_2_OUT_OD           AM_ZLG217_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_2_AF_PP            AM_ZLG217_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_2_AF_OD            AM_ZLG217_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_2������Ӧ����
 * @{
 */

#define PIOD_2_SPEED_10MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_2_SPEED_2MHz       AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_2_SPEED_50MHz      AM_ZLG217_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * @}
 */

/**
 * @}if_zlg217_pin
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZLG217_PIN_H */

/* end of file */
