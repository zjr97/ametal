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
 * \brief LPC82X IOCON (IO����) Ӳ�������ӿ�
 * 
 *  1. ����ģʽ���������������������м�ģʽ����
 *  2. ʹ�ܺͽ������ų��ͣ�
 *  3. ʹ�ܺͽ����������뷴ת��
 *  4. ʹ�ܺͽ��ܿ�©ģʽ��
 *  5. ���������˲����ڣ�
 *  6. �����˲�����Ƶ��
 *  7. ����I2C���������ٶ�ģʽ( PIO0_10 �� PIO0_11)��
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-24  mem, modified.
 * - 1.01 15-09-18  zxl, modified.
 * - 1.00 15-07-03  zxl, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC82X_IOCON_H
#define __AMHW_LPC82X_IOCON_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc82x_if_iocon
 * \copydoc amhw_lpc82x_iocon.h
 * @{
 */


/**
 * \brief LPC82x IOCON �Ĵ�����ṹ��
 */
typedef struct amhw_lpc82x_iocon {
    __IO uint32_t  pio[31];       /**< \brief ���Ź��ܺ͵������Կ��ƼĴ��� */
} amhw_lpc82x_iocon_t;


/**
 * \brief LPC82x (PIO0_0~PIO0_28) �������üĴ���ƫ�Ʊ�
 *
 *  offset = amhw_lpc82x_iocon_offset_pin[PIO_15] : PIO_15���żĴ���ƫ�� \n
 *  pio[offset]                                   : ����PIO_15�ļĴ���
 */
extern const uint8_t amhw_lpc82x_iocon_offset_pin[];

/**
 * \brief PINT ����ģʽ
 */
typedef enum amhw_lpc82x_iocon_mode {
    AMHW_LPC82X_IOCON_MODE_INACTIVE = 0,  /**< \brief ����ģʽ(������������) */
    AMHW_LPC82X_IOCON_MODE_PULLDOWN,      /**< \brief ����ģʽ               */
    AMHW_LPC82X_IOCON_MODE_PULLUP,        /**< \brief ����ģʽ               */
    AMHW_LPC82X_IOCON_MODE_REPEATER       /**< \brief �м�ģʽ               */
} amhw_lpc82x_iocon_mode_t;

/**
 *  \brief PINT �����˲�����
 */
typedef enum amhw_lpc82x_iocon_filt_cycle {
    AMHW_LPC82X_IOCON_FILT_CYCLE_0 = 0,   /**< \brief ��ʹ���˲�����         */
    AMHW_LPC82X_IOCON_FILT_CYCLE_1,       /**< \brief ����С��һ�������ź�   */
    AMHW_LPC82X_IOCON_FILT_CYCLE_2,       /**< \brief ����С�����������ź�   */
    AMHW_LPC82X_IOCON_FILT_CYCLE_3        /**< \brief ����С�����������ź�   */
} amhw_lpc82x_iocon_filt_cycle_t;

/**
 * \brief PINT �����˲�����ʱ�ӷ�Ƶ
 */
typedef enum amhw_lpc82x_iocon_filt_clkdiv {
    AMHW_LPC82X_IOCON_FILT_CLKDIV_0 = 0,  /**< \brief �˲�������ʱ�ӷ�Ƶ0    */
    AMHW_LPC82X_IOCON_FILT_CLKDIV_1,      /**< \brief �˲�������ʱ�ӷ�Ƶ1    */
    AMHW_LPC82X_IOCON_FILT_CLKDIV_2,      /**< \brief �˲�������ʱ�ӷ�Ƶ2    */
    AMHW_LPC82X_IOCON_FILT_CLKDIV_3,      /**< \brief �˲�������ʱ�ӷ�Ƶ3    */
    AMHW_LPC82X_IOCON_FILT_CLKDIV_4,      /**< \brief �˲�������ʱ�ӷ�Ƶ4    */
    AMHW_LPC82X_IOCON_FILT_CLKDIV_5,      /**< \brief �˲�������ʱ�ӷ�Ƶ5    */
    AMHW_LPC82X_IOCON_FILT_CLKDIV_6       /**< \brief �˲�������ʱ�ӷ�Ƶ6    */
} amhw_lpc82x_iocon_filt_clkdiv_t;


/**
 * \brief PINT ����I2Cģʽ��������PIO0_10��PIO0_11��
 */
typedef enum amhw_lpc82x_iocon_i2c_mode {
    AMHW_LPC82X_IOCON_I2C_MODE_STD  = 0,  /**< \brief I2C��׼ģʽ/����ģʽ   */
    AMHW_LPC82X_IOCON_I2C_MODE_IO,        /**< \brief ��ͨIOģʽ             */
    AMHW_LPC82X_IOCON_I2C_MODE_PLUS       /**< \brief ������ģʽ             */
} amhw_lpc82x_iocon_i2c_mode_t;


/**
 * \brief ��������ģʽ
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] mode       : ����ģʽ
 *
 * \return ��
 *
 * \note ��PIO0_10��PIO0_11��Ч���ڲ���©
 */
am_static_inline
void amhw_lpc82x_iocon_mode_set (amhw_lpc82x_iocon_t      *p_hw_iocon,
                                 int                       pin,
                                 amhw_lpc82x_iocon_mode_t  mode)
{
    uint32_t reg = p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]];

    AM_BIT_CLR_MASK(reg, AM_SBF(0x3, 3));
    AM_BIT_SET_MASK(reg, AM_SBF(mode, 3));

    p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]] = reg;
}


/**
 * \brief ʹ�����ų���
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 *
 * \note ��PIO0_10��PIO0_11��Ч
 */
am_static_inline
void amhw_lpc82x_iocon_hys_enable (amhw_lpc82x_iocon_t *p_hw_iocon, int pin)
{
    AM_BIT_SET_MASK(p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]], 
                    AM_BIT(5));
}


/**
 * \brief �������ų���
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 *
 * \note ��PIO0_10��PIO0_11��Ч
 */
am_static_inline
void amhw_lpc82x_iocon_hys_disable (amhw_lpc82x_iocon_t *p_hw_iocon, int pin)
{
    AM_BIT_CLR_MASK(p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]],
                    AM_BIT(5));
}


/**
 * \brief ʹ���������뷴ת
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_iocon_inv_enable (amhw_lpc82x_iocon_t *p_hw_iocon, int pin)
{
    AM_BIT_SET_MASK(p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]], 
                    AM_BIT(6));
}


/**
 * \brief �����������뷴ת
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_iocon_inv_disable (amhw_lpc82x_iocon_t *p_hw_iocon, int pin)
{
    AM_BIT_CLR_MASK(p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]], 
                    AM_BIT(6));
}


/**
 * \brief ʹ�����ſ�©
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 *
 * \note ��PIO0_10��PIO0_11��Ч���ڲ���©
 */
am_static_inline
void amhw_lpc82x_iocon_od_enable (amhw_lpc82x_iocon_t *p_hw_iocon, int pin)
{
     AM_BIT_SET_MASK(p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]], 
                     AM_BIT(10));
}


/**
 * \brief �������ſ�©
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 *
 * \note ��PIO0_10��PIO0_11��Ч���ڲ���©
 */
am_static_inline
void amhw_lpc82x_iocon_od_disable (amhw_lpc82x_iocon_t *p_hw_iocon, int pin)
{
   AM_BIT_CLR_MASK(p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]], 
                   AM_BIT(10));
}


/**
 * \brief �����˲���������
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] cycle      : �����˲�����
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_iocon_filt_cycle_set (amhw_lpc82x_iocon_t          *p_hw_iocon,
                                       int                           pin,
                                      amhw_lpc82x_iocon_filt_cycle_t cycle)
{
    uint32_t reg = p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]];

    AM_BIT_CLR_MASK(reg, AM_SBF(0x3, 11));
    AM_BIT_SET_MASK(reg, AM_SBF(cycle, 11));

    p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]] = reg;
}


/**
 * \brief ���ò����˲�����Ƶ
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] div        : ���Ų����˲�����Ƶ����
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_iocon_filt_clkdiv_set (amhw_lpc82x_iocon_t         *p_hw_iocon,
                                        uint8_t                      pin,
                                     amhw_lpc82x_iocon_filt_clkdiv_t div)
{
    uint32_t reg = p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]];

    AM_BIT_CLR_MASK(reg, AM_SBF(0x7, 13));
    AM_BIT_SET_MASK(reg, AM_SBF(div, 13));

    p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]] = reg;
}


/**
 * \brief ����I2Cģʽ
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ #PIO0_10 �� #PIO0_11
 * \param[in] mode       : I2Cģʽ
 *
 * \return ��
 *
 * \note ֻ��PIO0_10��PIO0_11��Ч
 */
am_static_inline
void amhw_lpc82x_iocon_i2c_mode_set (amhw_lpc82x_iocon_t         *p_hw_iocon,
                                     int                          pin,
                                     amhw_lpc82x_iocon_i2c_mode_t mode)
{
    uint32_t reg = p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]];

    AM_BIT_CLR_MASK(reg, AM_SBF(0x3, 8));
    AM_BIT_SET_MASK(reg, AM_SBF(mode, 8));

    p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]] = reg;

}


/**
 * \brief ����PIO�Ĵ���
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] data       : д�뵽�Ĵ���������
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_iocon_pio_cfg (amhw_lpc82x_iocon_t *p_hw_iocon, 
                                int                  pin, 
                                uint32_t             data)
{
    p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]] = data;
}


/**
 * \brief ��ȡPIO�Ĵ��������� 
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return : ����PIO�Ĵ�����ֵ
 */
am_static_inline
uint32_t amhw_lpc82x_iocon_pio_get (amhw_lpc82x_iocon_t *p_hw_iocon, int pin)
{
    return p_hw_iocon->pio[amhw_lpc82x_iocon_offset_pin[pin]];
}

/**
 * @} amhw_lpc82x_if_iocon
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC82X_IOCON_H */

/* end of file */
