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
 * 1. �����ϣ�GPIOģ�鹦���������ʿɴ�24M��
 *    FGPIOģ�鹦���������ʿɴ�48M
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-15  nwt, make some changes about function name.
 * - 1.00 15-10-16  wxj, first implementation.
 * \endinternal
 */

#ifndef __KL26_GPIO_H
#define __KL26_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"
#include "../../../../kl26/kl26_periph_map.h"
#include "../../../../kl26/kl26_inum.h"

/**
 * \addtogroup amhw_kl26_if_gpio
 * \copydoc amhw_kl26_gpio.h
 * @{
 */

/**
 * \brief GPIO �˿ڼĴ����ṹ��
 */
typedef struct gpio_reg {
    __IO uint32_t pdor;         /**< \brief �˿���������Ĵ��� */
    __O  uint32_t psor;         /**< \brief �˿���������Ĵ��� */
    __O  uint32_t pcor;         /**< \brief �˿���������Ĵ��� */
    __O  uint32_t ptor;         /**< \brief �˿ڷ�ת����Ĵ��� */
    __I  uint32_t pdir;         /**< \brief �˿���������Ĵ��� */
    __IO uint32_t pddr;         /**< \brief �˿����ݷ���Ĵ��� */
    __IO uint32_t reserve[10];  /**< \brief ���� */
} gpio_reg_t;

/**
 * \brief GPIO �Ĵ�����ṹ��
 */
typedef struct amhw_kl26_gpio {
    gpio_reg_t    gpio[5];      /**< \brief GPIO �˿� */
} amhw_kl26_gpio_t;

/**
 * \brief GPIO �Ĵ�����ṹ��
 */
typedef struct amhw_kl26_fgpio {
    gpio_reg_t    fgpio[5];     /**< \brief FGPIO �˿� */
} amhw_kl26_fgpio_t;

/**
 * \brief ����GPIO���ų�ʼ��ƽΪ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_gpio_pin_init_out_low (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 5].pdor &= ~(1ul << (pin & 0x1F));
}

/**
 * \brief ����GPIO���ų�ʼ��ƽΪ��
 *
 * \param[in] p_hw_gpio :ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_gpio_pin_init_out_high (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 5].pdor |= (1ul << (pin & 0x1F));
}

/**
 * \brief ��GPIO���ų�ʼ��ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : �͵�ƽ
 * \retval 1 : �ߵ�ƽ
 */
am_static_inline
int amhw_kl26_gpio_pin_init_get (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    return (((p_hw_gpio->gpio[pin >> 5].pdor &
            (1ul << (pin & 0x1F))) !=0) ? 1 : 0);
}

/**
 * \brief ����GPIO���ŵ�ƽΪ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \note  ��PSOR�Ĵ���д1��дPDOR�Ĵ�����ʹ�ܽ������ƽΪ��
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_gpio_pin_out_high (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 5].psor |= (1ul << (pin & 0x1F));
}

/**
 * \brief ����GPIO���ŵ�ƽΪ��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \note   ��PCOR�Ĵ���д1����PDOR�Ĵ�����ʹ�ܽ������ƽΪ��
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_gpio_pin_out_low (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 5].pcor |= (1ul << (pin & 0x1F));
}

/**
 * \brief ��תGPIO���ŵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \note   ��PTOR�Ĵ���д1����תPDOR�Ĵ�����ֵ��ʹ�ܽ������ƽ��ת
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_gpio_pin_out_toggle (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 5].ptor |= (1ul << (pin & 0x1F));
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
int amhw_kl26_gpio_pin_input_get (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    return ((((p_hw_gpio->gpio[pin >> 5].pdir) &
            (1ul << (pin & 0x1F))) !=0) ? 1 : 0);
}

/**
 * \brief ����GPIO����Ϊ���뷽��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_gpio_pin_dir_input (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 5].pddr &= ~(1ul << (pin & 0x1F));
}

/**
 * \brief ����GPIO����Ϊ�������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_gpio_pin_dir_output (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->gpio[pin >> 5].pddr |= (1ul << (pin & 0x1F));
}

/**
 * \brief ��GPIO��������\�������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : ����
 * \retval 1 : ���
 */
am_static_inline
int amhw_kl26_gpio_pin_dir_get (amhw_kl26_gpio_t *p_hw_gpio, int pin)
{
    return (((p_hw_gpio->gpio[pin >> 5].pddr &
            (1ul << (pin & 0x1F))) != 0) ? 1 : 0);
}


/*******************************************************************************
                    FGPIO��������
********************************************************************************/

/**
 * \brief ����FGPIO���ų�ʼ��ƽΪ��
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_fgpio_pin_init_out_low (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    p_hw_fgpio->fgpio[pin >> 5].pdor &= ~(1ul << (pin & 0x1F));
}

/**
 * \brief ����FGPIO���ų�ʼ��ƽΪ��
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_fgpio_pin_init_out_high (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    p_hw_fgpio->fgpio[pin >> 5].pdor |= (1ul << (pin & 0x1F));
}

/**
 * \brief ��FGPIO���ų�ʼ��ƽ
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : �͵�ƽ
 * \retval 1 : �ߵ�ƽ
 */
am_static_inline
int amhw_kl26_fgpio_pin_init_get (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    return (((p_hw_fgpio->fgpio[pin >> 5].pdor &
            (1ul << (pin & 0x1F))) !=0) ? 1 : 0);
}

/**
 * \brief ����FGPIO���ŵ�ƽΪ��
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \note   ��PSOR�Ĵ���д1��дPDOR�Ĵ�����ʹ�ܽ������ƽΪ��
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_fgpio_pin_out_high (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    p_hw_fgpio->fgpio[pin >> 5].psor |= (1ul << (pin & 0x1F));
}

/**
 * \brief ����FGPIO���ŵ�ƽΪ��
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \note   ��PCOR�Ĵ���д1����PDOR�Ĵ�����ʹ�ܽ������ƽΪ��
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_fgpio_pin_out_low (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    p_hw_fgpio->fgpio[pin >> 5].pcor |= (1ul << (pin & 0x1F));
}

/**
 * \brief ��תFGPIO���ŵ�ƽ
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \note   ��PTOR�Ĵ���д1����תPDOR�Ĵ�����ֵ��ʹ�ܽ������ƽ��ת
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_fgpio_pin_out_toggle (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    p_hw_fgpio->fgpio[pin >> 5].ptor |= (1ul << (pin & 0x1F));
}

/**
 * \brief ��FGPIO���������ƽ
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : �͵�ƽ
 * \retval 1 : �ߵ�ƽ
 */
am_static_inline
int amhw_kl26_fgpio_pin_input_get (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    return (((p_hw_fgpio->fgpio[pin >> 5].pdir &
            (1ul << (pin & 0x1F))) !=0) ? 1 : 0);
}

/**
 * \brief ����FGPIO����Ϊ���뷽��
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_fgpio_pin_dir_input (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    p_hw_fgpio->fgpio[pin >> 5].pddr &= ~(1ul << (pin & 0x1F));
}

/**
 * \brief ����FGPIO����Ϊ�������
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
am_static_inline
void amhw_kl26_fgpio_pin_dir_output (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    p_hw_fgpio->fgpio[pin >> 5].pddr |= (1ul << (pin & 0x1F));
}

/**
 * \brief ��FGPIO��������\�������
 *
 * \param[in] p_hw_fgpio : ָ��FGPIO�Ĵ������ָ��
 * \param[in] pin        : ���ű��,ֵΪ PIO* (#PIOA_0)
 *
 * \retval 0 : ����
 * \retval 1 : ���
 */
am_static_inline
int amhw_kl26_fgpio_pin_dir_get (amhw_kl26_fgpio_t *p_hw_fgpio, int pin)
{
    return (((p_hw_fgpio->fgpio[pin >> 5].pddr &
            (1ul << (pin & 0x1F))) != 0) ? 1 : 0);
}

/**
 * @} amhw_kl26_if_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __KL26_GPIO_H */

/* end of file */

