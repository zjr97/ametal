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
 * \brief ZLG116 GPIO �������ò�������
 *
 * \note: �������Ź��ܵ�ʱ��һ��Ҫͬʱ�������ŵ�ģʽ����������ģʽ������ģʽ��
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __ZLG116_PIN_H
#define __ZLG116_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_zlg116_gpio_util.h"

 /**
 * \addtogroup zlg116_if_pin
 * \copydoc zlg116_pin.h
 * @{
 */

/**
 * \name ZLG116 GPIO ���ű��
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
#define PIN_NUM         39

/**
 * \brief ֧��ͬʱ������������ж�����16
 */
#define PIN_INT_MAX     16

/** @} */

/**
 * \name ZLG116���Ŷ���,����������SWCK��SWIO֮�⣬�������Ÿ�λʱ��Ĭ��ΪGPIO����(��������)
 * @{
 */

/******************************************************************************/

/**
 * \name PIOA_0���Ÿ��ù���
 * @{
 */

#define PIOA_0_UART2_CTS      AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART2_CTS */
#define PIOA_0_TIM2_CH1_ETR   AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH1_ETR */
#define PIOA_0_COMP1_OUT      AM_ZLG116_GPIO_FUNC_CODE(0x07)   /**< \brief COMP1_OUT */
#define PIOA_0_ADC_IN0        AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN0 */
#define PIOA_0_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_0_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_0_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_0_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_0_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_0_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_0_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_0_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_0_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_0������Ӧ����
 * @{
 */

#define PIOA_0_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_0_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_0_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_1���Ÿ��ù���
 * @{
 */

#define PIOA_1_UART2_RTS      AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART2_RTS */
#define PIOA_1_TIM2_CH2       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH2 */
#define PIOA_1_ADC_IN1        AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN1 */
#define PIOA_1_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_1_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_1_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_1_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_1_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_1_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_1_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_1_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_1_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_1������Ӧ����
 * @{
 */

#define PIOA_1_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_1_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_1_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_2���Ÿ��ù���
 * @{
 */

#define PIOA_2_UART2_TX       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART2_TX */
#define PIOA_2_TIM2_CH3       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH3 */
#define PIOA_2_COMP2_OUT      AM_ZLG116_GPIO_FUNC_CODE(0x07)   /**< \brief COMP2_OUT */
#define PIOA_2_ADC_IN2        AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN2 */
#define PIOA_2_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_2_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_2_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_2_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_2_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_2_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_2_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_2_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_2_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_2������Ӧ����
 * @{
 */

#define PIOA_2_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_2_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_2_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_3���Ÿ��ù���
 * @{
 */

#define PIOA_3_UART2_RX       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART2_RX */
#define PIOA_3_TIM2_CH4       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH4 */
#define PIOA_3_ADC_IN3        AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN3 */
#define PIOA_3_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_3_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_3_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_3_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_3_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_3_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_3_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_3_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_3_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_3������Ӧ����
 * @{
 */

#define PIOA_3_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_3_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_3_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_4���Ÿ��ù���
 * @{
 */

#define PIOA_4_SPI1_NSS       AM_ZLG116_GPIO_FUNC_CODE(0x00)    /**< \brief SPI1_NSS */
#define PIOA_4_TIM14_CH1      AM_ZLG116_GPIO_FUNC_CODE(0x04)    /**< \brief TIM14_CH1 */
#define PIOA_4_ADC_IN4        AM_ZLG116_GPIO_FUNC_CODE(0x0F)    /**< \brief ADC_IN4 */
#define PIOA_4_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)    /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_4���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_4_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_4_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_4_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_4_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_4_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_4_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_4_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_4_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_4������Ӧ����
 * @{
 */

#define PIOA_4_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_4_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_4_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_5���Ÿ��ù���
 * @{
 */

#define PIOA_5_SPI1_SCK       AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_SCK */
#define PIOA_5_TIM2_CH1_ETR   AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH1_ETR */
#define PIOA_5_ADC_IN5        AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN5 */
#define PIOA_5_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_5_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_5_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_5_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_5_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_5_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_5_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_5_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_5_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_5������Ӧ����
 * @{
 */

#define PIOA_5_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_5_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_5_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_6���Ÿ��ù���
 * @{
 */

#define PIOA_6_SPI1_MISO      AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_MISO */
#define PIOA_6_TIM3_CH1       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief TIM3_CH3 */
#define PIOA_6_TIM1_BKIN      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_BKIN */
#define PIOA_6_TIM16_CH1      AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief TIM3_CH3 */
#define PIOA_6_COMP1_OUT      AM_ZLG116_GPIO_FUNC_CODE(0x07)   /**< \brief COMP1_OUT */
#define PIOA_6_ADC_IN6        AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN6 */
#define PIOA_6_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_6���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_6_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_6_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_6_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_6_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_6_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_6_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_6_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_6_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_6������Ӧ����
 * @{
 */

#define PIOA_6_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_6_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_6_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_7���Ÿ��ù���
 * @{
 */

#define PIOA_7_SPI1_MOSI      AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_MOSI */
#define PIOA_7_TIM3_CH2       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief TIM3_CH2 */
#define PIOA_7_TIM1_CH1N      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH1N */
#define PIOA_7_TIM14_CH1      AM_ZLG116_GPIO_FUNC_CODE(0x04)   /**< \brief TIM14_CH1 */
#define PIOA_7_TIM17_CH1      AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief TIM17_CH1 */
#define PIOA_7_COMP2_OUT      AM_ZLG116_GPIO_FUNC_CODE(0x07)   /**< \brief COMP2_OUT */
#define PIOA_7_ADC_IN7        AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN7 */
#define PIOA_7_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_7���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_7_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_7_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_7_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_7_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_7_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_7_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_7_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_7_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_7������Ӧ����
 * @{
 */

#define PIOA_7_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_7_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_7_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_8���Ÿ��ù���
 * @{
 */

#define PIOA_8_MCO            AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief MCO */
#define PIOA_8_TIM1_CH1       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH1 */
#define PIOA_8_CRS_SYNC       AM_ZLG116_GPIO_FUNC_CODE(0x04)   /**< \brief CRS_SYNC */
#define PIOA_8_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_8_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_8_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_8_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_8_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_8_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_8_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_8_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_8_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_8������Ӧ����
 * @{
 */

#define PIOA_8_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_8_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_8_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_9���Ÿ��ù���
 * @{
 */

#define PIOA_9_UART1_TX       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART1_TX */
#define PIOA_9_TIM1_CH2       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH2 */
#define PIOA_9_UART1_RX       AM_ZLG116_GPIO_FUNC_CODE(0x03)   /**< \brief UART1_RX */
#define PIOA_9_I2C_SCL        AM_ZLG116_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SCL */
#define PIOA_9_MCO            AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief MCO */
#define PIOA_9_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_9_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_9_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_9_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_9_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_9_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_9_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_9_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_9_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_9������Ӧ����
 * @{
 */

#define PIOA_9_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_9_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_9_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_10���Ÿ��ù���
 * @{
 */

#define PIOA_10_TIM17_BKIN     AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief TIM17_BKIN */
#define PIOA_10_UART1_RX       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART1_RX */
#define PIOA_10_TIM1_CH3       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH3 */
#define PIOA_10_UART1_TX       AM_ZLG116_GPIO_FUNC_CODE(0x03)   /**< \brief UART1_TX */
#define PIOA_10_I2C_SDA        AM_ZLG116_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SDA */
#define PIOA_10_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_10���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_10_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_10_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_10_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_10_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_10_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_10_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_10_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_10_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_10������Ӧ����
 * @{
 */

#define PIOA_10_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_10_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_10_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_11���Ÿ��ù���
 * @{
 */

#define PIOA_11_UART1_CTS      AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART1_CTS */
#define PIOA_11_TIM1_CH4       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH4 */
#define PIOA_11_I2C_SCL        AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief I2C_SCL */
#define PIOA_11_COMP1_OUT      AM_ZLG116_GPIO_FUNC_CODE(0x07)   /**< \brief COMP1_OUT */
#define PIOA_11_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_11���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_11_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_11_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_11_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_11_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_11_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_11_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_11_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_11_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_11������Ӧ����
 * @{
 */

#define PIOA_11_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_11_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_11_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_12���Ÿ��ù���
 * @{
 */

#define PIOA_12_UART1_RTS      AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART1_RTS */
#define PIOA_12_TIM1_ETR       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_ETR */
#define PIOA_12_I2C_SDA        AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief I2C_SDA */
#define PIOA_12_COMP2_OUT      AM_ZLG116_GPIO_FUNC_CODE(0x07)   /**< \brief COMP2_OUT */
#define PIOA_12_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_12���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_12_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_12_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_12_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_12_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_12_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_12_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_12_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_12_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_12������Ӧ����
 * @{
 */

#define PIOA_12_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_12_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_12_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_13���Ÿ��ù���
 * @{
 */

#define PIOA_13_SWDIO          AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SWDIO */
#define PIOA_13_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_13_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_13_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_13_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_13_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_13_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_13_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_13_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_13_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_13������Ӧ����
 * @{
 */

#define PIOA_13_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_13_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_13_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_14���Ÿ��ù���
 * @{
 */

#define PIOA_14_SWDCLK         AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SWDCLK */
#define PIOA_14_UART2_TX       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART2_TX */
#define PIOA_14_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_14_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_14_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_14_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_14_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_14_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_14_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_14_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_14_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_14������Ӧ����
 * @{
 */

#define PIOA_14_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_14_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_14_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_15���Ÿ��ù���
 * @{
 */

#define PIOA_15_SPI1_NSS       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief SPI1_NSS */
#define PIOA_15_UART2_RX       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief UART2_RX */
#define PIOA_15_TIM2_CH1_ETR   AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH1_ETR */
#define PIOA_15_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_15_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_15_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_15_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_15_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_15_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_15_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_15_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_15_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_15������Ӧ����
 * @{
 */

#define PIOA_15_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_15_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_15_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_0���Ÿ��ù���
 * @{
 */

#define PIOB_0_TIM3_CH3        AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief TIM3_CH3 */
#define PIOB_0_TIM1_CH2N       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH2N */
#define PIOB_0_ADC_IN8         AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN8 */
#define PIOB_0_GPIO            AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_0_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_0_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_0_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_0_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_0_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_0_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_0_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_0_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_0������Ӧ����
 * @{
 */

#define PIOB_0_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_0_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_0_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_1���Ÿ��ù���
 * @{
 */

#define PIOB_1_TIM14_CH1      AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief TIM14_CH1 */
#define PIOB_1_TIM3_CH4       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief TIM3_CH4 */
#define PIOB_1_TIM1_CH3N      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH3N */
#define PIOB_1_ADC_IN9        AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN9 */
#define PIOB_1_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_1_AIN           AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_1_INPUT_FLOAT   AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_1_INPUT_PD      AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_1_INPUT_PU      AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_1_OUT_PP        AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_1_OUT_OD        AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_1_AF_PP         AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_1_AF_OD         AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_1������Ӧ����
 * @{
 */

#define PIOB_1_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_1_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_1_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_2���Ÿ��ù���
 * @{
 */

#define PIOB_2_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_2_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_2_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_2_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_2_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_2_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_2_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_2_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_2_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_2������Ӧ����
 * @{
 */

#define PIOB_2_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_2_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_2_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_3���Ÿ��ù���
 * @{
 */

#define PIOB_3_SPI1_SCK       AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_SCK */
#define PIOB_3_TIM2_CH2       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH2 */
#define PIOB_3_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_3_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_3_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_3_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_3_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_3_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_3_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_3_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_3_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_3������Ӧ����
 * @{
 */

#define PIOB_3_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_3_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_3_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_4���Ÿ��ù���
 * @{
 */
#define PIOB_4_SPI1_MISO      AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_MISO */
#define PIOB_4_TIM3_CH1       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief TIM3_CH1 */
#define PIOB_4_TIM17_BKIN     AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief TIM17_BKIN */
#define PIOB_4_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_4���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_4_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_4_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_4_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_4_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_4_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_4_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_4_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_4_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_4������Ӧ����
 * @{
 */

#define PIOB_4_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_4_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_4_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_5���Ÿ��ù���
 * @{
 */
#define PIOB_5_SPI1_MOSI      AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_MOSI */
#define PIOB_5_TIM3_CH2       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief TIM3_CH2 */
#define PIOB_5_TIM16_BKIN     AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM16_BKIN */
#define PIOB_5_GPIO            AM_ZLG116_GPIO_FUNC_CODE(0x0F)  /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_5_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_5_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_5_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_5_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_5_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_5_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_5_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_5_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_5������Ӧ����
 * @{
 */

#define PIOB_5_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_5_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_5_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_6���Ÿ��ù���
 * @{
 */
#define PIOB_6_UART1_TX      AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief UART1_TX */
#define PIOB_6_I2C_SCL       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief I2C_SCL */
#define PIOB_6_TIM16_CH1N    AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM16_CH1N */
#define PIOB_6_GPIO          AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_6���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_6_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_6_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_6_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_6_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_6_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_6_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_6_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_6_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_6������Ӧ����
 * @{
 */

#define PIOB_6_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_6_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_6_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_7���Ÿ��ù���
 * @{
 */
#define PIOB_7_UART1_RX       AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief UART1_RX */
#define PIOB_7_I2C_SDA        AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief I2C_SDA */
#define PIOB_7_TIM17_CH1N     AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM17_CH1N */
#define PIOB_7_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_7�ܽŸ���ʱ���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_7_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_7_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_7_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_7_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_7_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_7_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_7_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_7_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_7������Ӧ����
 * @{
 */

#define PIOB_7_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_7_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_7_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_8���Ÿ��ù���
 * @{
 */

#define PIOB_8_I2C_SCL        AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief I2C_SCL */
#define PIOB_8_TIM16_CH1      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM16_CH1 */
#define PIOB_8_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_8_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_8_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_8_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_8_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_8_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_8_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_8_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_8_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_8������Ӧ����
 * @{
 */

#define PIOB_8_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_8_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_8_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_9���Ÿ��ù���
 * @{
 */

#define PIOB_9_I2C_SDA        AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief I2C_SDA */
#define PIOB_9_TIM17_CH1      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM17_CH1 */
#define PIOB_9_SPI2_NSS       AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOB_9_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_9_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_9_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_9_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_9_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_9_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_9_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_9_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_9_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_9������Ӧ����
 * @{
 */

#define PIOB_9_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_9_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_9_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_10���Ÿ��ù���
 * @{
 */
#define PIOB_10_I2C_SCL       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief I2C_SCL */
#define PIOB_10_TIM2_CH3      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH3 */
#define PIOB_10_SPI2_SCK      AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOB_10_GPIO          AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_10���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_10_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_10_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_10_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_10_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_10_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_10_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_10_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_10_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_10������Ӧ����
 * @{
 */

#define PIOB_10_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_10_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_10_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_11���Ÿ��ù���
 * @{
 */

#define PIOB_11_I2C_SDA        AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief I2C_SDA */
#define PIOB_11_TIM2_CH4       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH4 */
#define PIOB_11_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_11���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_11_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_11_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_11_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_11_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_11_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_11_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_11_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_11_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_11������Ӧ����
 * @{
 */

#define PIOB_11_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_11_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_11_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_12���Ÿ��ù���
 * @{
 */

#define PIOB_12_SPI1_NSS       AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_NSS */
#define PIOB_12_SPI2_SCK       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief SPI2_SCK */
#define PIOB_12_TIM1_BKIN      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_BKIN */
#define PIOB_12_SPI2_MOSI      AM_ZLG116_GPIO_FUNC_CODE(0x03)   /**< \brief SPI2_MOSI */
#define PIOB_12_SPI2_MISO      AM_ZLG116_GPIO_FUNC_CODE(0x04)   /**< \brief SPI2_MISO */
#define PIOB_12_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_12���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_12_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_12_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ�*/
#define PIOB_12_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_12_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_12_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_12_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_12_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_12_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_12������Ӧ����
 *
 * @{
 */

#define PIOB_12_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_12_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_12_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_13���Ÿ��ù���
 * @{
 */

#define PIOB_13_SPI1_SCK       AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_SCK */
#define PIOB_13_SPI2_MISO      AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief SPI2_MISO */
#define PIOB_13_TIM1_CH1N      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH1N */
#define PIOB_13_SPI2_NSS       AM_ZLG116_GPIO_FUNC_CODE(0x03)   /**< \brief SPI2_NSS */
#define PIOB_13_SPI2_MOSI      AM_ZLG116_GPIO_FUNC_CODE(0x04)   /**< \brief SPI2_MOSI */
#define PIOB_13_I2C_SCL        AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief I2C_SCL */
#define PIOB_13_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_13_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_13_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_13_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_13_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_13_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_13_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_13_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_13_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_13������Ӧ����
 * @{
 */

#define PIOB_13_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_13_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_13_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_14���Ÿ��ù���
 * @{
 */

#define PIOB_14_SPI1_MISO      AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_MISO */
#define PIOB_14_SPI2_MOSI      AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief SPI2_MOSI */
#define PIOB_14_TIM1_CH2N      AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH2N */
#define PIOB_14_SPI2_SCK       AM_ZLG116_GPIO_FUNC_CODE(0x03)   /**< \brief SPI2_SCK */
#define PIOB_14_SPI2_NSS       AM_ZLG116_GPIO_FUNC_CODE(0x04)   /**< \brief SPI2_NSS */
#define PIOB_14_I2C_SDA        AM_ZLG116_GPIO_FUNC_CODE(0x05)   /**< \brief I2C_SDA */
#define PIOB_14_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_14_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_14_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_14_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_14_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_14_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_14_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_14_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_14_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_14������Ӧ����
 * @{
 */

#define PIOB_14_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_14_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_14_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_15���Ÿ��ù���
 * @{
 */
#define PIOB_15_SPI1_MOSI      AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_MOSI */
#define PIOB_15_SPI2_NSS       AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief SPI2_NSS */
#define PIOB_15_TIM1_CH3       AM_ZLG116_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH3N */
#define PIOB_15_SPI2_MISO      AM_ZLG116_GPIO_FUNC_CODE(0x03)   /**< \brief SPI2_MISO */
#define PIOB_15_SPI2_SCK       AM_ZLG116_GPIO_FUNC_CODE(0x04)   /**< \brief SPI2_SCK */
#define PIOB_15_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_15_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_15_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_15_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_15_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_15_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_15_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_15_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_15_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_15������Ӧ����
 * @{
 */

#define PIOB_15_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_15_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_15_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_13���Ÿ��ù���
 * @{
 */
#define PIOC_13_GPIO            AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_13_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_13_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_13_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_13_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_13_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_13_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_13_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_13_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_13������Ӧ����
 * @{
 */

#define PIOC_13_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_13_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_13_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_14���Ÿ��ù���
 * @{
 */
#define PIOC_14_GPIO            AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_14_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_14_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_14_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_14_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_14_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_14_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_14_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_14_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_14������Ӧ����
 * @{
 */

#define PIOC_14_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_14_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_14_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_15���Ÿ��ù���
 * @{
 */
#define PIOC_15_GPIO            AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_15_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_15_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_15_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_15_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_15_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_15_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_15_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_15_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_15������Ӧ����
 * @{
 */

#define PIOC_15_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_15_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_15_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_0���Ÿ��ù���
 * @{
 */

#define PIOD_0_CRS_SYNC       AM_ZLG116_GPIO_FUNC_CODE(0x00)   /**< \brief CRS_SYNC */
#define PIOD_0_I2C_SDA        AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief I2C_SDA */
#define PIOD_0_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_0_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_0_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_0_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_0_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_0_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_0_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_0_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_0_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_0������Ӧ����
 * @{
 */

#define PIOD_0_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_0_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_0_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_1���Ÿ��ù���
 * @{
 */

#define PIOD_1_I2C_SCL        AM_ZLG116_GPIO_FUNC_CODE(0x01)   /**< \brief I2C_SCL */
#define PIOD_1_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_1_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_1_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_1_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_1_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_1_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_1_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_1_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_1_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_1������Ӧ����
 * @{
 */

#define PIOD_1_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_1_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_1_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_2���Ÿ��ù���
 * @{
 */

#define PIOD_2_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_2_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_2_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_2_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_2_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_2_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_2_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_2_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_2_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_2������Ӧ����
 * @{
 */

#define PIOD_2_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_2_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_2_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_3_GPIO           AM_ZLG116_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_3_AIN            AM_ZLG116_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_3_INPUT_FLOAT    AM_ZLG116_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_3_INPUT_PD       AM_ZLG116_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_3_INPUT_PU       AM_ZLG116_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_3_OUT_PP         AM_ZLG116_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_3_OUT_OD         AM_ZLG116_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_3_AF_PP          AM_ZLG116_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_3_AF_OD          AM_ZLG116_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_3_SPEED_10MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_3_SPEED_20MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_3_SPEED_50MHz    AM_ZLG116_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * @}
 */

/**
 * @}if_zlg116_pin
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZLG116_PIN_H */

/* end of file */
