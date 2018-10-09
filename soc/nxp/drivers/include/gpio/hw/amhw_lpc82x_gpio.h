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
 * \brief GPIO Ӳ�������ӿ�
 * 
 * 1. �ɵ�������ÿ�����ŵķ��������ĵ�ƽ��������λ�����㣬��ת��
 * 2. ��ͬʱ����ÿ���˿��������ŵķ��������ĵ�ƽ��������λ�����㣬��ת��
 * 3. �ɵ�����ȡ���ŵ�ƽ��ͬʱ��ȡ�˿��������ŵ�ƽ��
 * 4. ��ͨ���������úͻ�ȡ�˿����ŵ�ƽ��
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-24  mem, modified.
 * - 1.00 15-07-03  zxl, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC82X_GPIO_H
#define __AMHW_LPC82X_GPIO_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * \addtogroup amhw_lpc82x_if_gpio 
 * \copydoc amhw_lpc82x_gpio.h
 * @{
 */
    
/**
 * \brief GPIO �Ĵ�����ṹ��
 */
typedef struct amhw_lpc82x_gpio {
    __IO uint8_t  b[128][32];       /**< \brief �����ֽڼĴ���       */
    __IO uint32_t w[32][32];        /**< \brief �����ּĴ���         */
    __IO uint32_t dir[32];          /**< \brief ����Ĵ���           */
    __IO uint32_t mask[32];         /**< \brief ����Ĵ�             */
    __IO uint32_t pin[32];          /**< \brief �˿����żĴ���       */
    __IO uint32_t mpin[32];         /**< \brief �˿�����Ĵ���       */
    __IO uint32_t set[32];          /**< \brief ����Ķ�����λ�Ĵ��� */
    __O  uint32_t clr[32];          /**< \brief �˿�����Ĵ���       */
    __O  uint32_t not0[32];         /**< \brief �˿ڷ�ת�Ĵ���       */
    __O  uint32_t dirset[32];       /**< \brief �˿ڷ�����λ�Ĵ���   */
    __O  uint32_t dirclr[32];       /**< \brief �˿ڷ�������Ĵ���   */
    __O  uint32_t dirnot[32];       /**< \brief �˿ڷ���ת�Ĵ���   */
} amhw_lpc82x_gpio_t;

/**
 * \name GPIO ���ŵ�ƽ
 * \anchor grp_amhw_lpc82x_gpio_pin_level
 * @{
 */
 
#define AMHW_LPC82X_GPIO_LEVEL_LOW     0        /**< \brief �͵�ƽ */
#define AMHW_LPC82X_GPIO_LEVEL_HIGH    1        /**< \brief �ߵ�ƽ */

/** @} */

/**
 * \name GPIO ���ŷ���
 * \anchor grp_amhw_lpc82x_gpio_pin_dir
 * @{
 */
 
#define AMHW_LPC82X_GPIO_DIR_INPUT     0        /**< \brief ����Ϊ���� */
#define AMHW_LPC82X_GPIO_DIR_OUTPUT    1        /**< \brief ����Ϊ��� */

/** @} */


/**
 * \brief ����GPIO���ŵ������ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] level     : ��ƽ״̬
 *      \arg AMHW_LPC82X_GPIO_LEVEL_LOW  �� �͵�ƽ
 *      \arg AMHW_LPC82X_GPIO_LEVEL_HIGH �� �ߵ�ƽ
 *
 * \return ��
 *
 * \note �ù��ܽ�����������Ϊ�����GPIO����
 */
am_static_inline 
void amhw_lpc82x_gpio_pin_out_set (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                   int                 pin, 
                                   uint8_t             level)
{
    p_hw_gpio->b[0][pin] = level;
}

/**
 * \brief ����GPIO��������ߵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 *
 * \note �ù��ܽ�����������Ϊ�����GPIO����
 */
am_static_inline 
void amhw_lpc82x_gpio_pin_out_high (amhw_lpc82x_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->set[0] = AM_BIT(pin);
}

/**
 * \brief ����GPIO��������͵�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 *
 * \note �ù��ܽ�����������Ϊ�����GPIO����
 */
am_static_inline 
void amhw_lpc82x_gpio_pin_out_low (amhw_lpc82x_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->clr[0] = AM_BIT(pin);
}

/**
 * \brief ��תGPIO���������ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 *
 * \note �ù��ܽ�����������Ϊ�����GPIO����
 */
am_static_inline 
void amhw_lpc82x_gpio_pin_out_tog (amhw_lpc82x_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->not0[0] = AM_BIT(pin);
}

/**
 * \brief ��ȡָ�����ŵĵ�ƽ״̬
 *
��
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \retval AMHW_LPC82X_GPIO_LEVEL_LOW  : �͵�ƽ
 * \retval AMHW_LPC82X_GPIO_LEVEL_HIGH : �ߵ�ƽ
 *
 * \note ���˸���������Ϊģ��I/Oʱ������Ϊ0�����������¶����Ի�ȡ���ŵĵ�ƽ״̬
 */
am_static_inline 
int amhw_lpc82x_gpio_pin_level_get (amhw_lpc82x_gpio_t *p_hw_gpio, int pin)
{
    return AM_BIT_GET(p_hw_gpio->pin[0], pin);
}

/**
 * \brief ����GPIO���ŷ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] dir       : ���ŷ���
 *      \arg AMHW_LPC82X_GPIO_DIR_INPUT  �� ����Ϊ����
 *      \arg AMHW_LPC82X_GPIO_DIR_OUTPUT �� ����Ϊ���
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_pin_dir_set (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                   int                 pin, 
                                   uint8_t             dir)
{
    uint32_t reg = p_hw_gpio->dir[0];
    
    reg &= ~AM_BIT(pin);
    reg |=  AM_SBF(dir, pin);
    p_hw_gpio->dir[0] = reg;
}


/**
 * \brief ����GPIO���ŷ���Ϊ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_pin_dir_output (amhw_lpc82x_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->dirset[0] = AM_BIT(pin);
}

/**
 * \brief ����GPIO���ŷ���Ϊ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_pin_dir_input (amhw_lpc82x_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->dirclr[0] = AM_BIT(pin);
}

/**
 * \brief ��תGPIO���ŷ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_pin_dir_tog (amhw_lpc82x_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->dirnot[0] = AM_BIT(pin);
}

/**
 * \brief ��ȡ���ŵķ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \retval AMHW_LPC82X_GPIO_DIR_INPUT  : ����Ϊ����
 * \retval AMHW_LPC82X_GPIO_DIR_OUTPUT : ����Ϊ���
 */
am_static_inline
uint8_t amhw_lpc82x_gpio_pin_dir_get (amhw_lpc82x_gpio_t *p_hw_gpio, int pin)
{
    return AM_BIT_GET(p_hw_gpio->dir[0], pin);
}

/**
 * \brief ���ö˿����ŵ�״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] value     : ����״̬������n��Ӧbit_n,��bit_nΪ1,�������ŵ�ƽΪ�ߣ�
 *                        ��֮������Ϊ�͵�ƽ
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_out_set (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                    uint32_t            value)
{
    p_hw_gpio->pin[0] = value;
}

/**
 * \brief ���ö˿�GPIO��������ߵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_mask  : ����n��Ӧbit_n,��bit_nΪ1,�������ŵ�ƽΪ�ߣ�
 *                        ��bit_nΪ0��������������
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_out_high (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                     uint32_t            pin_mask)
{
    p_hw_gpio->set[0] = pin_mask;
}

/**
 * \brief ���ö˿�GPIO��������͵�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_mask  : ����n��Ӧbit_n,��bit_nΪ1,�������ŵ�ƽΪ�ͣ�
 *                        ��bit_nΪ0��������������
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_out_low (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                    uint32_t            pin_mask)
{
    p_hw_gpio->clr[0] = pin_mask;
}

/**
 * \brief ��ת�˿�GPIO���������ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_mask  : ����n��Ӧbit_n,��bit_nΪ1,��ת���ŵ�ƽ��
 *                        ��bit_nΪ0��������������
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_out_tog (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                    uint32_t            pin_mask)
{
    p_hw_gpio->not0[0] = pin_mask;
}

/**
 * \brief ��ȡ�˿�GPIO���ŵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return �˿ڵ�����״̬������n��Ӧbit_n,��bit_nΪ1,������n��ƽΪ�ߣ�
 *         ��֮����nΪ�͵�ƽ
 *
 * \note ���˸���������Ϊģ��I/Oʱ������Ϊ0�����������¶����Ի�ȡ���ŵĵ�ƽ״̬
 */
am_static_inline 
uint32_t amhw_lpc82x_gpio_port_levle_get (amhw_lpc82x_gpio_t *p_hw_gpio)
{
    return p_hw_gpio->pin[0];
}

/**
 * \brief ���ö˿�GPIO���ŵķ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] value     : ���ŷ�������n��Ӧbit_n,��bit_nΪ1,
 *                        ���������ŷ���Ϊ�������֮�����ŷ���Ϊ����
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_dir_set (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                    uint32_t            value)
{
    p_hw_gpio->dir[0] = value;
}

/**
 * \brief ���ö˿�GPIO���ŷ���Ϊ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_mask  : ����n��Ӧbit_n,��bit_nΪ1,���������ŷ���Ϊ�����
 *                        ��bit_nΪ0��������������
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_dir_output (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                       uint32_t            pin_mask)
{
    p_hw_gpio->dirset[0] = pin_mask;
}

/**
 * \brief ���ö˿�GPIO��������͵�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_mask  : ����n��Ӧbit_n,��bit_nΪ1,���������ŷ���Ϊ���룬
 *                        ��bit_nΪ0��������������
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_dir_input (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                      uint32_t            pin_mask)
{
    p_hw_gpio->dirclr[0] = pin_mask;
}

/**
 * \brief ��ת�˿�GPIO���ŷ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_mask  : ����n��Ӧbit_n,��bit_nΪ1,��ת���ŷ���
 *                        ��bit_nΪ0��������������
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_dir_tog (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                    uint32_t            pin_mask)
{
    p_hw_gpio->dirnot[0] = pin_mask;
}

/**
 * \brief ��ȡ�˿�GPIO���ŷ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return �˿ڵ����ŷ�������n��Ӧbit_n,��bit_nΪ1,������n����Ϊ�����
 *         ��֮����n����Ϊ����
 */
am_static_inline 
uint32_t amhw_lpc82x_gpio_port_dir_get (amhw_lpc82x_gpio_t *p_hw_gpio)
{
    return p_hw_gpio->dir[0];
}

/**
 * \brief ���ö˿ڵ�GPIO�������룬���ڿ��ƶ˿ڵĶ���д
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] mask      : �˿�����ֵ������n��Ӧbit_n
 * 
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_mask_set (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                uint32_t            mask)
{
    p_hw_gpio->mask[0] = mask;
}

/**
 * \brief ��ȡ�˿�GPIO��������
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ�� 
 *
 * \return �˿ڵ�GPIO�������룬����n��Ӧbit_n
 */
am_static_inline 
uint32_t amhw_lpc82x_gpio_mask_get (amhw_lpc82x_gpio_t *p_hw_gpio)
{
    return p_hw_gpio->mask[0];
}

/**
 * \brief ������������GPIO�˿ڵ�����״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] value     : ����״̬������n��Ӧbit_n����bit_nΪ1����������
 *                        ��ƽΪ�ߣ���֮������Ϊ�͵�ƽ�������Ӧ��MASKֵΪ1��
 *                        �����Ϊ������Ӱ��
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_gpio_port_masked_out_set (amhw_lpc82x_gpio_t *p_hw_gpio,  
                                           uint32_t            value)
{
    p_hw_gpio->mpin[0] = value;
}

/**
 * \brief ���������ȡ�˿�GPIO����״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 *
 * \return ������GPIO�˿�����״̬
 *
 * \note ���ĳһλ��Ӧ��MASK�Ĵ���ֵΪ0���üĴ���������ȡ�����ŵ�ƽ״̬��
 *       ��Ӧ��MASK�Ĵ���ֵΪ1ʱ������Ϊ0
 */
am_static_inline 
uint32_t amhw_lpc82x_gpio_port_masked_level_get (amhw_lpc82x_gpio_t *p_hw_gpio)
{
    return p_hw_gpio->mpin[0];
}


/**
 * @} amhw_lpc82x_if_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC82X_GPIO_H */

/* end of file */
