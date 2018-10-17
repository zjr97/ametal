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
 * \brief GPIO Ӳ�������ӿ�
 *
 * 1. GPIO �����ܹ�ͨ���������Ϊ���������
 * 2. ����GPIO ����Ĭ��Ϊ���룬�ڸ�λʱ�жϽ��ܣ�
 * 3. ���żĴ����������ŵ������û���ͬʱ���á�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-07  nwt, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG_GPIO_H
#define __AMHW_ZLG_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_zlg_if_gpio
 * \copydoc amhw_zlg_gpio.h
 * @{
 */

/**
 * \name GPIO �˿ڱ��
 * @{
 */

#define AMHW_ZLG_GPIO_PORT_A    0        /**< \brief �˿� A */
#define AMHW_ZLG_GPIO_PORT_B    16       /**< \brief �˿� B */
#define AMHW_ZLG_GPIO_PORT_C    32       /**< \brief �˿� C */
#define AMHW_ZLG_GPIO_PORT_D    48       /**< \brief �˿� D */

/** @} */

/**
 * \name AF selection
 * @{
 */
 
/**
 * \brief AF 0 selection
 * SPI1, MC0, TIM17_BKIN, SWDIO,SWCLK, UART1
 */
#define AMHW_ZLG_GPIO_AF_0       ((uint8_t)0x00)

/**
 * \brief AF 1 selection
 * UART1, TIM3_CH1, TIM3_CH2, TIM3_CH3,TIM3_CH4, I2C1
 */
#define AMHW_ZLG_GPIO_AF_1       ((uint8_t)0x01)

/**
 * \brief AF 2 selection
 * TIM2_CH1_ETR, TIM2_CH2, TIM2_CH3, TIM2_CH3, TIM2_CH4, TIM1_BKIN,
 * TIM1_CH1N, TIM1_CH1, TIM1_CH2,TIM1_CH3, TIM1_CH4, TIM1_ETR,
 * TIM1_CH2N, TIM1_CH3N, TIM2_CH2,TIM1 6_BKIN, TIM16_CH1N, TIM17_CH1N,
 * TIM16_CH1, TIM17_CH1
 */
#define AMHW_ZLG_GPIO_AF_2       ((uint8_t)0x02)

/** \brief AF 3 selection */
#define AMHW_ZLG_GPIO_AF_3       ((uint8_t)0x03)

/** \brief AF 4 selection, TIM14_CH1, I2C1  */
#define AMHW_ZLG_GPIO_AF_4       ((uint8_t)0x04)

/** \brief AF 5 selection */
#define AMHW_ZLG_GPIO_AF_5       ((uint8_t)0x05)

/** \brief AF 6 selection */
#define AMHW_ZLG_GPIO_AF_6       ((uint8_t)0x06)

/** \brief AF 7 selection */
#define AMHW_ZLG_GPIO_AF_7       ((uint8_t)0x07)

/** \brief AF default selection, ����û�и���(Ĭ��GPIO)  */
#define AMHW_ZLG_GPIO_AF_DEFAULT ((uint8_t)0x0f)

/** @} */
 
/**
 * \brief �ܽŸ��÷�Χ���
 */
#define AMHW_ZLG_GPIO_IS_AF(af) (((af) == AMHW_ZLG_GPIO_AF_0) || \
                                 ((af) == AMHW_ZLG_GPIO_AF_1) || \
                                 ((af) == AMHW_ZLG_GPIO_AF_2) || \
                                 ((af) == AMHW_ZLG_GPIO_AF_3) || \
                                 ((af) == AMHW_ZLG_GPIO_AF_4) || \
                                 ((af) == AMHW_ZLG_GPIO_AF_5) || \
                                 ((af) == AMHW_ZLG_GPIO_AF_6) || \
                                 ((af) == AMHW_ZLG_GPIO_AF_7))

/**
 * \name GPIO ���ŵ�ƽ
 * @{
 */
#define AMHW_ZLG_GPIO_LEVEL_LOW     0        /**< \brief �͵�ƽ */
#define AMHW_ZLG_GPIO_LEVEL_HIGH    1        /**< \brief �ߵ�ƽ */
/** @} */

/* ʹ�������ṹ�������������Ŀ�ʼ */
#if defined(__CC_ARM)
    #pragma push
    #pragma anon_unions
#elif defined(__ICCARM__)
    #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
    #pragma warning 586
#else
    #warning Not supported compiler t
#endif

/**
 * \brief gpio�����жϴ�����ʽ����
 */
typedef enum amhw_zlg_gpio_trig_mode {
    AMHW_ZLG_PINT_TRIGGER_HIGH       = 0x0,   /**< \brief �ߵ�ƽ���� */
    AMHW_ZLG_PINT_TRIGGER_LOW        = 0x1,   /**< \brief �͵�ƽ���� */
    AMHW_ZLG_PINT_TRIGGER_RISE       = 0x2,   /**< \brief �����ش��� */
    AMHW_ZLG_PINT_TRIGGER_FALL       = 0x3,   /**< \brief �½��ش��� */
    AMHW_ZLG_PINT_TRIGGER_BOTH_EDGES = 0x4    /**< \brief ˫���ش��� */
} amhw_zlg_pin_trig_mode_t;

/**
 * \brief GPIO����������·��Ӧ�ٶ�
 * \note ѡ���ö������GPIO����������·��Ӧ�ٶ�ʱ��GPIO����Ҳȷ��Ϊ�������
 */
typedef enum amhw_zlg_gpio_speed_mode {
    AMHW_ZLG_GPIO_SPEED_10MHz = 3UL,
    AMHW_ZLG_GPIO_SPEED_20MHz = 2UL,
    AMHW_ZLG_GPIO_SPEED_50MHz = 1UL
}amhw_zlg_gpio_speed_mode_t;

/**
 * \brief GPIO����ģʽ
 *
 * \note ������Ϊ���������ʱ�����в�ͬ��ģʽ
 */
typedef enum amhw_zlg_gpio_mode {
    
    /** \brief ��GPIO���ŵķ���Ϊ���뷽�����ž������¼���ģʽ */
    AMHW_ZLG_GPIO_MODE_AIN = 0x00,         /**< \brief ģ������ģʽ     */
    AMHW_ZLG_GPIO_MODE_IN_FLOATING = 0x01, /**< \brief ��������ģʽ     */
    AMHW_ZLG_GPIO_MODE_IPD = 0x02,         /**< \brief ��������ģʽ     */
    AMHW_ZLG_GPIO_MODE_IPU = 0x02,         /**< \brief ��������ģʽ     */

    /** \brief ��GPIO���ŵķ���Ϊ����������ž������¼���ģʽ */
    AMHW_ZLG_GPIO_MODE_OUT_PP = 0x00,      /**< \brief ͨ���������ģʽ */
    AMHW_ZLG_GPIO_MODE_OUT_OD = 0x01,      /**< \brief ͨ�ÿ�©���ģʽ */
    AMHW_ZLG_GPIO_MODE_AF_PP  = 0x02,      /**< \brief �����������ģʽ */
    AMHW_ZLG_GPIO_MODE_AF_OD  = 0x03       /**< \brief ���ÿ�©���ģʽ */

} amhw_zlg_gpio_mode_t;

/**
 * \brief GPIO �Ĵ�����ṹ��
 */
typedef struct amhw_zlg_gpio {
    __IO uint32_t cr[2];       /**< \brief �˿�����(�ߵ�)�Ĵ��� */
    __I  uint32_t idr;         /**< \brief �˿��������ݼĴ��� */
    __IO uint32_t odr;         /**< \brief �˿�����Ĵ��� */
    __O  uint32_t bsrr;        /**< \brief �˿�����/����Ĵ��� */
    __O  uint32_t brr;         /**< \brief �˿�λ����Ĵ��� */
    __IO uint32_t lckr;        /**< \brief �˿����������Ĵ��� */
    __I  uint32_t reserve;     /**< \brief ���� */
    __IO uint32_t afr[2];      /**< \brief �˿ڸ��ù���(�ߵ�)�Ĵ��� */
} amhw_zlg_gpio_t;

/**
 * \brief GPIO�����������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] flags     : ���ò���
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_gpio_pin_set (amhw_zlg_gpio_t *p_hw_gpio, int flags, int pin)
{
    /* ȡ�õ�ǰ��������GPIO�˿ڵĻ���ַ */
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    /*
     * pin & 0x0f ��������ȡ������Ӧ�˿����ŵ���������Ϊһ��GPIO�˿�ֻ��16������
     * eg : ��оƬ17������Ϊ����0x11 & 0x0f = 0x01, ������GPIO�˿�B��1������
     *
     * ((pin & 0x0f) >> 3) ����д��Ŀ�����ڵ�һ��GPIO�˿ڵĵ�8������0 ~ 7������
     * ���ƼĴ���Ϊcr[0], ��8������8 ~ 15�� ���Ŀ��ƼĴ���Ϊcr[1]
     * eg����оƬ27�� ����Ϊ����((0x1B & 0x0f) >> 3) = 0x01, ������GPIO�˿�B��
     *     11�����ŵĿ��ƼĴ���Ϊcr[1]
     *
     * 4 * ((pin & 0x0f) & 0x07) ��������ȡ���˸������������ĸ�λ�Σ�
     * 7 ~ 0 ���ŷֱ�����cr[0]��λ [31��28]��[27��24]��[23��20]��[19��16]��
     *                             [15��12]��[11��8]�� [7��4]��  [3��0]
     *
     * 15 ~ 8���ŷֱ�����cr[1]��λ [31��28]��[27��24]��[23��20]��[19��16]��
     *                             [15��12]��[11��8]�� [7��4]��  [3��0]
     */

    /* ����ÿ������ģʽ���λ�� */
    AM_BITS_SET(p_gpio_addr->cr[((pin & 0x0f) >> 3)],
                (4 * ((pin & 0x0f) & 0x07)), 
                4, 
                flags);
}

/**
 * \brief ����GPIO���ŷ���Ϊ���������������·��Ӧ�ٶ�
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] speed_mode : ����Ϊ����ʱ����������·��Ӧ�ٶ�ģʽ��
 *                         ֵΪ amhw_zlg_gpio_speed_mode_t ���ö������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_gpio_pin_dir_output (amhw_zlg_gpio_t           *p_hw_gpio,
                                   amhw_zlg_gpio_speed_mode_t speed_mode,
                                   int                        pin)
{
    /* ȡ�õ�ǰ��������GPIO�˿ڵĻ���ַ */
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    /*
     * pin & 0x0f ��������ȡ������Ӧ�˿����ŵ���������Ϊһ��GPIO�˿�ֻ��16������
     * eg : ��оƬ17������Ϊ����0x11 & 0x0f = 0x01, ������GPIO�˿�B��1������
     *
     * ((pin & 0x0f) >> 3) ����д��Ŀ �����ڵ�һ��GPIO�˿ڵĵ�8������0 ~ 7�����Ŀ��Ƽ�
     * ����Ϊcr[0], ��8������8 ~ 15�� ���Ŀ��ƼĴ���Ϊcr[1]
     * eg����оƬ27�� ����Ϊ����((0x1B & 0x0f) >> 3) = 0x01, ������GPIO�˿�B��11�����ŵ�
     *     ���ƼĴ���Ϊcr[1]
     *
     * 4 * ((pin & 0x0f) & 0x07) ��������ȡ���˸������������ĸ�λ�Σ�
     * 7 ~ 0 ��������cr[0]��λ 29��28 λ 25��24 λ 21��20 λ 17��16 λ 13��12λ 9��8λ 5��4 λ 1��0
     * 15 ~ 8��������cr[1]��λ 29��28 λ 25��24 λ 21��20 λ 17��16 λ 13��12λ 9��8λ 5��4 λ 1��0
     *
     */

    /* �������ŷ���Ϊ������λ��, ���øĽӿڲ���Ӱ������λ�� */
    AM_BITS_SET(p_gpio_addr->cr[((pin & 0x0f) >> 3)], (4 * ((pin & 0x0f) & 0x07)), 2, speed_mode);
}

/**
 * \brief ����GPIO���ŷ���Ϊ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_gpio_pin_dir_input (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    /* �������ŷ���Ϊ������λ��, ���øĽӿڲ���Ӱ������λ�� */
    AM_BITS_SET(p_gpio_addr->cr[((pin & 0x0f) >> 3)], (4 * ((pin & 0x0f) & 0x07)), 2, 0x00);
}

/**
 * \brief ����GPIO���ŵ�ģʽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] gpio_mode : ���ŵ�ģʽ��ֵΪ amhw_zlg_gpiomode_t ���ö������
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_gpio_pin_mode_set (amhw_zlg_gpio_t       *p_hw_gpio,
                                 amhw_zlg_gpio_mode_t   gpio_mode,
                                 int                    pin)
{
    /* ȡ�õ�ǰ��������GPIO�˿ڵĻ���ַ */
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    /*
     * pin & 0x0f ��������ȡ������Ӧ�˿����ŵ���������Ϊһ��GPIO�˿�ֻ��16������
     * eg : ��оƬ17������Ϊ����0x11 & 0x0f = 0x01, ������GPIO�˿�B��1������
     *
     * ((pin & 0x0f) >> 3) ����д��Ŀ �����ڵ�һ��GPIO�˿ڵĵ�8������0 ~ 7�����Ŀ��Ƽ�
     * ����Ϊcr[0], ��8������8 ~ 15�� ���Ŀ��ƼĴ���Ϊcr[1]
     * eg����оƬ27�� ����Ϊ����((0x1B & 0x0f) >> 3) = 0x01, ������GPIO�˿�B��11�����ŵ�
     *     ���ƼĴ���Ϊcr[1]
     *
     * 4 * ((pin & 0x0f) & 0x07) ��������ȡ���˸������������ĸ�λ�Σ�
     * 7 ~ 0 ��������cr[0]��λ 29��28 λ 25��24 λ 21��20 λ 17��16 λ 13��12λ 9��8λ 5��4 λ 1��0
     * 15 ~ 8��������cr[1]��λ 29��28 λ 25��24 λ 21��20 λ 17��16 λ 13��12λ 9��8λ 5��4 λ 1��0
     *
     */

    /* ����ÿ������ģʽ���λ�� */
    AM_BITS_SET(p_gpio_addr->cr[((pin & 0x0f) >> 3)], (4 * ((pin & 0x0f) & 0x07) + 2), 2, gpio_mode);
}

/**
 * \brief ��ȡָ�����ŵķ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \retval  0  : ����
 * \retval  1  : ���
 */
am_static_inline
int amhw_zlg_gpio_pin_dir_get (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    return (((AM_BITS_GET(p_gpio_addr->cr[((pin & 0x0f) >> 3)], \
            (4 * ((pin & 0x0f) & 0x07)), 2)) != 0) ? 1 : 0);
}

/**
 * \brief ����GPIO���ŷ���Ϊ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ����GPIO������ģʽ
 */
am_static_inline
int amhw_zlg_gpio_pin_mode_get (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    /* �������ŷ���Ϊ������λ��, ���øĽӿڲ���Ӱ������λ�� */
    return AM_BITS_GET(p_gpio_addr->cr[((pin & 0x0f) >> 3)], (4 * ((pin & 0x0f) & 0x07) + 2), 2);
}

/**
 * \brief ��ȡ���ŵĵ�ƽ״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 *\note �����ŷ���Ϊ�����������Ϊ��©ģʽʱ�����������ݼĴ����ķ��ʿɵõ� I/O ״̬
 *
 * \retval  0  : �͵�ƽ
 * \retval  1  : �ߵ�ƽ
 */
am_static_inline
int amhw_zlg_gpio_pin_get (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    int gpio_mode = 0;

    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    /* ��Ϊ�������ʱ����ȡ���ŵ�״̬����ͨ����ȡODR�Ĵ�����ֵ��ʵ�� */
    if (amhw_zlg_gpio_pin_dir_get(p_hw_gpio, pin) != 0) {

        gpio_mode = amhw_zlg_gpio_pin_mode_get(p_hw_gpio, pin);

        if (gpio_mode == AMHW_ZLG_GPIO_MODE_OUT_PP ||
            gpio_mode == AMHW_ZLG_GPIO_MODE_OUT_PP ) {
            return (((p_gpio_addr->odr & (1UL << (pin & 0x0f))) != 0) ? 1 : 0);
        } else {
            return (((p_gpio_addr->idr & (1UL << (pin & 0x0f))) != 0) ? 1 : 0);
        }
    } else {
        return (((p_gpio_addr->idr & (1UL << (pin & 0x0f))) != 0) ? 1 : 0);
    }
}

/**
 * \brief ����GPIO��������ߵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��.
 *
 * \note �ù��������������ŵ�ʱ��Ϊʹ���������貢ʧ����������
 */
am_static_inline
void amhw_zlg_gpio_pin_out_high (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

     /* ��Ӧ��������ߵ�ƽ */
    p_gpio_addr->bsrr|= (1UL << (pin & 0x0f));
}

/**
 * \brief ����GPIO��������͵�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 * \note �ù��������������ŵ�ʱ��Ϊʧ���������貢ʹ����������
 */
am_static_inline
void amhw_zlg_gpio_pin_out_low (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    p_gpio_addr->brr |= (1UL << (pin & 0x0f));
}

/**
 * \brief ��תGPIO������ŵĵ�ƽ״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 * \note �ù��������������ŵ�ʱ��Ϊ��������/��������
 */
am_static_inline
void amhw_zlg_gpio_pin_toggle (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    if (amhw_zlg_gpio_pin_get(p_hw_gpio,pin)) {
        amhw_zlg_gpio_pin_out_low(p_hw_gpio,pin);
    } else {
        amhw_zlg_gpio_pin_out_high(p_hw_gpio,pin);
    }
}

/**
 * \brief ����GPIO��������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \note �ú������ö������ͬһGPIO�˿ڲ�ͬ���ŵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_gpio_pinlock_set (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);
    p_gpio_addr->lckr |= (1UL << (pin & 0x0f));
}

/**
 * \brief GPIO�˿���������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port_num  : �˿ڱ�ţ�ֵΪ PIO* (# AMHW_GPIO_PORT_A)
 *
 * \note �ú���һ�� ��amhw_zlg_gpio_pinlock_set���ú�����ŵ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_gpio_lckk_set (amhw_zlg_gpio_t *p_hw_gpio, int port_num)
{
    uint32_t temp = (1UL << 16);

    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (port_num >> 4) * 0x400);

    /* Set LCKK bit */
    p_gpio_addr->lckr |= temp;
    /* Reset LCKK bit */
    p_gpio_addr->lckr &= ~temp;
    /* Set LCKK bit */
    p_gpio_addr->lckr |= temp;
    /* Read LCKK bit */
    temp =  p_gpio_addr->lckr;
    /* Read LCKK bit */
    temp =  p_gpio_addr->lckr;
}

/**
 * \brief ���Ÿ��ù�����ӳ������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] gpio_af   : ���Ÿ��ù��ܱ�ţ�ֵΪ AMHW_GPIO_AF_* ��һ��� (# AMHW_GPIO_AF_0)
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_gpio_pin_afr_set (amhw_zlg_gpio_t *p_hw_gpio, int gpio_af, int pin)
{
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    /* �������Ÿ��ù��ܵ����λ��, ���øĽӿڲ���Ӱ������λ�� */
    AM_BITS_SET(p_gpio_addr->afr[((pin & 0x0f) >> 3)], (4 * ((pin & 0x0f) & 0x07)), 4, gpio_af);
}

/**
 * \brief ��ȡ��ǰ���Ÿ��ù�����AF
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ���� AMHW_GPIO_AF_* ��һ���ֵ (# AMHW_GPIO_AF_0)
 */
am_static_inline
uint32_t amhw_zlg_gpio_pin_afr_get (amhw_zlg_gpio_t *p_hw_gpio, int pin)
{
    amhw_zlg_gpio_t *p_gpio_addr = (amhw_zlg_gpio_t *)((int)p_hw_gpio \
                                      + (pin >> 4) * 0x400);

    /* �������ŷ���Ϊ������λ��, ���øĽӿڲ���Ӱ������λ�� */
    return AM_BITS_GET(p_gpio_addr->afr[((pin & 0x0f) >> 3)], (4 * ((pin & 0x0f) & 0x07)), 4);
}

/**
 * @}
 */

/* ʹ�������ṹ�������������Ľ��� */
#if defined(__CC_ARM)
    #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
    #pragma warning restore
#else
    #warning Not supported compiler t
#endif

/**
 * @} amhw_zlg_if_zlg_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG_GPIO_H */

/* end of file */
