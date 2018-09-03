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
 * \brief GPIO hardware operation interface
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-21  zcb, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG217_GPIO_H
#define __AMHW_ZLG217_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"

/**
 * \addtogroup amhw_zlg217_if_gpio
 * \copydoc amhw_zlg217_gpio.h
 * @{
 */

#define AMHW_ZLG217_GPIO_PORT_MAX 5  /**< \brief GPIO ����GPIO�˿����� */

/**
 * \brief GPIO �˿ڼĴ����ṹ��
 */
typedef struct gpio_reg {
    __IO  uint32_t crl;               /**< \brief �˿����õͼĴ��� */
    __IO  uint32_t crh;               /**< \brief �˿����ø߼Ĵ��� */
    __I   uint32_t idr;               /**< \brief �˿��������ݼĴ��� */
    __IO  uint32_t odr;               /**< \brief �˿�������ݼĴ��� */
    __O   uint32_t bsrr;              /**< \brief �˿�����/����Ĵ��� */
    __O   uint32_t brr;               /**< \brief �˿�λ����Ĵ��� */
    __IO  uint32_t lckr;              /**< \brief �˿����������Ĵ��� */
          uint32_t reserve[249];      /**< \brief ���� */
} amhw_zlg217_gpio_reg_t;

/**
 * \brief GPIO �Ĵ�����ṹ��
 */
typedef struct amhw_zlg217_gpio {
    amhw_zlg217_gpio_reg_t    gpio[AMHW_ZLG217_GPIO_PORT_MAX];    /**< \brief GPIO �˿� */
} amhw_zlg217_gpio_t;

/**
 * \brief GPIO�������ٶ�
 * \note ѡ���ö������GPIO����������·��Ӧ�ٶ�ʱ��GPIO����Ҳȷ��Ϊ�������
 */
typedef enum amhw_zlg217_gpio_speed_mode {
    AMHW_ZLG217_GPIO_SPEED_10MHz = 1UL,
    AMHW_ZLG217_GPIO_SPEED_2MHz = 2UL,
    AMHW_ZLG217_GPIO_SPEED_50MHz = 3UL
}amhw_zlg217_gpio_speed_mode_t;

/**
 * \brief GPIO����ģʽ
 *
 * \note ������Ϊ���������ʱ�����в�ͬ��ģʽ
 */
typedef enum amhw_zlg217_gpiomode
{
    /** \brief ��GPIO���ŵķ���Ϊ���뷽�����ž������¼���ģʽ */
    AMHW_ZLG217_GPIO_MODE_AIN = 0x00,         /**< \brief ģ��ģʽ */
    AMHW_ZLG217_GPIO_MODE_IN_FLOATING = 0x01, /**< \brief ����ģʽ(��ģʽ���޶�������) */
    AMHW_ZLG217_GPIO_MODE_IPD = 0x02,         /**< \brief ����ģʽ(��ģʽ���޶�������) */
    AMHW_ZLG217_GPIO_MODE_IPU = 0x02,         /**< \brief ����ģʽ (��ģʽ���޶�������) */

    /** \brief ��GPIO���ŵķ���Ϊ����������ž������¼���ģʽ */
    AMHW_ZLG217_GPIO_MODE_OUT_PP = 0x00,      /**< \brief ͨ������ģʽ (��ģʽ���޶������) */
    AMHW_ZLG217_GPIO_MODE_OUT_OD = 0x01,      /**< \brief ͨ�ÿ�©ģʽ (��ģʽ���޶������) */
    AMHW_ZLG217_GPIO_MODE_AF_PP = 0x02,       /**< \brief ��������ģʽ(��ģʽ���޶������) */
    AMHW_ZLG217_GPIO_MODE_AF_OD = 0x03        /**< \brief ���ÿ�©ģʽ(��ģʽ���޶������) */

}amhw_zlg217_gpiomode_t;

/**
 * \brief ����GPIO���ŷ���Ϊ���������������·��Ӧ�ٶ�
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] speed_mode : ����Ϊ����ʱ����������·��Ӧ�ٶ�ģʽ��
 *                         ֵΪ amhw_zlg217_gpio_speed_mode_t ���ö������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_gpio_pin_dir_output (amhw_zlg217_gpio_t            *p_hw_gpio,
                                      amhw_zlg217_gpio_speed_mode_t  speed_mode,
                                      int                            pin)
{
    if (pin & 0x8) {
        p_hw_gpio->gpio[pin >> 4].crh &= ~(0x3 << ((pin & 0x7) << 2));
        p_hw_gpio->gpio[pin >> 4].crh |= (speed_mode & 0x3) << ((pin & 0x7) << 2);
    } else {
        p_hw_gpio->gpio[pin >> 4].crl &= ~(0x3 << ((pin & 0x7) << 2));
        p_hw_gpio->gpio[pin >> 4].crl |= (speed_mode & 0x3) << ((pin & 0x7) << 2);
    }
}

/**
 * \brief ����GPIO���ŷ���Ϊ����
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_gpio_pin_dir_input (amhw_zlg217_gpio_t *p_hw_gpio, int pin)
{
    if (pin & 0x8) {
        p_hw_gpio->gpio[pin >> 4].crh &= ~((0x3) << ((pin & 0x7) << 2));
    } else {
        p_hw_gpio->gpio[pin >> 4].crl &= ~((0x3) << ((pin & 0x7) << 2));
    }
}

/**
 * \brief ��ȡGPIO���������������
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return 0 �� ����
 *          1 �� ���
 */
am_static_inline
int amhw_zlg217_gpio_pin_dir_get (amhw_zlg217_gpio_t *p_hw_gpio, int pin)
{
    if (pin & 0x8) {
        return (p_hw_gpio->gpio[pin >> 4].crh & (0x3 << ((pin & 0x7) << 2))) ? 1 : 0;
    } else {
        return (p_hw_gpio->gpio[pin >> 4].crl & (0x3 << ((pin & 0x7) << 2))) ? 1 : 0;
    }
}

/**
 * \brief ����GPIO���ŵ�ģʽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] gpio_mode : ���ŵ�ģʽ��ֵΪ amhw_zlg217_gpiomode_t ���ö������
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_gpio_pin_mode_set (amhw_zlg217_gpio_t     *p_hw_gpio,
                                    amhw_zlg217_gpiomode_t  gpio_mode,
                                    int                     pin)
{
    if (pin & 0x8) {
        p_hw_gpio->gpio[pin >> 4].crh &= ~(0x3 << (((pin & 0x7) << 2) + 2));
        p_hw_gpio->gpio[pin >> 4].crh |= ((gpio_mode & 0x3) << (((pin & 0x7) << 2) + 2));
    } else {
        p_hw_gpio->gpio[pin >> 4].crl &= ~(0x3 << (((pin & 0x7) << 2) + 2));
        p_hw_gpio->gpio[pin >> 4].crl |= ((gpio_mode & 0x3) << (((pin & 0x7) << 2) + 2));
    }
}

/**
 * \brief ��GPIO���������ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : �͵�ƽ
 * \retval 1 : �ߵ�ƽ
 */
am_static_inline
int amhw_zlg217_gpio_pin_input_get(amhw_zlg217_gpio_t *p_hw_gpio, int pin)
{
    return ((p_hw_gpio->gpio[pin >> 4].idr & (0x1 << (pin & 0xf))) ? 1 : 0);
}

/**
 * \brief ��GPIO���������ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : �͵�ƽ
 * \retval 1 : �ߵ�ƽ
 */
am_static_inline
int amhw_zlg217_gpio_pin_output_get (amhw_zlg217_gpio_t *p_hw_gpio, int pin)
{
    return ((p_hw_gpio->gpio[pin >> 4].odr & (0x1 << (pin & 0xf))) ? 1 : 0);
}

/**
 * \brief ����GPIO���ŵ�ƽΪ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 * \note �ù��������������ŵ�ʱ��Ϊʹ���������貢ʧ����������
 */
am_static_inline
void amhw_zlg217_gpio_pin_out_high (amhw_zlg217_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 4].bsrr |= (0x1 << (pin & 0xf));
}

/**
 * \brief ����GPIO���ŵ�ƽΪ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 * \note �ù��������������ŵ�ʱ��Ϊʧ���������貢ʹ����������
 */
am_static_inline
void amhw_zlg217_gpio_pin_out_low (amhw_zlg217_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 4].bsrr |= ((0x1 << (pin & 0xf)) << 16);
}

/**
 * \brief ��תGPIO���ŵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 *
 * \note �ù��������������ŵ�ʱ��Ϊ��������/��������
 */
am_static_inline
void amhw_zlg217_gpio_pin_out_toggle (amhw_zlg217_gpio_t *p_hw_gpio, int pin)
{
    if (amhw_zlg217_gpio_pin_output_get(p_hw_gpio, pin)) {
        amhw_zlg217_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_zlg217_gpio_pin_out_high(p_hw_gpio, pin);
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
void amhw_zlg217_gpio_pinlock_set(amhw_zlg217_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 4].lckr |= (0x1 << (pin & 0xf));
}

/**
 * \brief GPIO�˿���������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port_num  : �˿ڱ�ţ�ֵΪ PIO* (# PIOA)
 *
 * \note �ú���һ�� ��amhw_zlg217_gpio_pinlock_set���ú�����ŵ���
 *
 * \return AM_OK    : ����
 *         AM_ERROR : ʧ��
 */
am_static_inline
int amhw_zlg217_gpio_lckk_set(amhw_zlg217_gpio_t *p_hw_gpio, int port_num)
{
    uint32_t temp = (1UL << 16);

    /* Set LCKK bit */
    p_hw_gpio->gpio[port_num >> 4].lckr |= temp;
    /* Reset LCKK bit */
    p_hw_gpio->gpio[port_num >> 4].lckr &= ~temp;
    /* Set LCKK bit */
    p_hw_gpio->gpio[port_num >> 4].lckr |= temp;
    /* Read LCKK bit */
    temp = p_hw_gpio->gpio[port_num >> 4].lckr;
    /* Read LCKK bit */
    if (p_hw_gpio->gpio[port_num >> 4].lckr & (0x1 << 16)) {
        return AM_OK;
    } else {
        return AM_ERROR;
    }
}

/**
 * @} amhw_zlg217_if_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG217_GPIO_H */

/* end of file */
