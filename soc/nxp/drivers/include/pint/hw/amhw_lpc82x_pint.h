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
 * \brief LPC82X PIN INT(�����ж�) Ӳ�������ӿ�
 *
 * 1. ���֧��8�������жϣ� 
 * 2. ÿ���жϿɴ�����0-28������ѡ��
 *    ������Ϊ�����ء��½��ء�˫���ء��ߵ�ƽ���͵�ƽ������
 * 3. �ж�ͨ��������Ϊģʽƥ���������룬�Զ��������в������㣬
 *    ���������ڴ����жϻ����ںˡ�
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-24  mem, modified.
 * - 1.01 15-09-18  zxl, modified.
 * - 1.00 15-07-06  zxl, first implementation.
 * \endinternal
 */
#ifndef __AMHW_LPC82X_PINT_H
#define __AMHW_LPC82X_PINT_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * \addtogroup amhw_lpc82x_if_pint
 * \copydoc amhw_lpc82x_pint.h
 * @{
 */

/**
 * @brief LPC82x �����жϼĴ�����ṹ��
 */
typedef struct amhw_lpc82x_pint{
    __IO uint32_t isel;     /**< \brief �����ж�ģʽ�Ĵ�           */
    __IO uint32_t ienr;     /**< \brief ��ƽ���������ж�ʹ�ܼĴ��� */
    __O  uint32_t sienr;    /**< \brief ��ƽ���������ж����üĴ��� */
    __O  uint32_t cienr;    /**< \brief ��ƽ���������ж�����Ĵ��� */
    __IO uint32_t ienf;     /**< \brief ��ƽ���½����ж�ʹ�ܼĴ��� */
    __O  uint32_t sienf;    /**< \brief ��ƽ���½����ж����üĴ��� */
    __O  uint32_t cienf;    /**< \brief ��ƽ���½����ж�����Ĵ��� */
    __IO uint32_t rise;     /**< \brief �����ж������ؼĴ���       */
    __IO uint32_t fall;     /**< \brief �����ж��½��ؼĴ���       */
    __IO uint32_t ist;      /**< \brief �����ж�״̬�Ĵ���         */
    __IO uint32_t pmctrl;   /**< \brief ģʽƥ���жϿ��ƼĴ���     */
    __IO uint32_t pmsrc;    /**< \brief ģʽƥ���ж�λƬԴ�Ĵ���   */
    __IO uint32_t pmcfg;    /**< \brief ģʽƥ���ж�λƬ���üĴ��� */
} amhw_lpc82x_pint_t;

/** \brief �ж�ͨ������ */
#define AMHW_LPC82X_PINT_CHAN_NUM     8

/**
 * \name �ж�ͨ�����
 * \anchor grp_amhw_lpc82x_pint_chan
 * @{
 */

#define AMHW_LPC82X_PINT_CHAN_0    0  /**< \brief �ж�ͨ�� 0       */
#define AMHW_LPC82X_PINT_CHAN_1    1  /**< \brief �ж�ͨ�� 1       */
#define AMHW_LPC82X_PINT_CHAN_2    2  /**< \brief �ж�ͨ�� 2       */
#define AMHW_LPC82X_PINT_CHAN_3    3  /**< \brief �ж�ͨ�� 3       */
#define AMHW_LPC82X_PINT_CHAN_4    4  /**< \brief �ж�ͨ�� 4       */
#define AMHW_LPC82X_PINT_CHAN_5    5  /**< \brief �ж�ͨ�� 5       */
#define AMHW_LPC82X_PINT_CHAN_6    6  /**< \brief �ж�ͨ�� 6       */
#define AMHW_LPC82X_PINT_CHAN_7    7  /**< \brief �ж�ͨ�� 7       */

/** @} */

/**
 * \brief ����ģʽ����
 */
typedef enum amhw_lpc82x_pint_trigger { 
    AMHW_LPC82X_PINT_TRIGGER_HIGH = 0,   /**< \brief �ߵ�ƽ����ģʽ */
    AMHW_LPC82X_PINT_TRIGGER_LOW,        /**< \brief �͵�ƽ����ģʽ */
    AMHW_LPC82X_PINT_TRIGGER_RISE,       /**< \brief �����ش���ģʽ */
    AMHW_LPC82X_PINT_TRIGGER_FALL,       /**< \brief �½��ش���ģʽ */
    AMHW_LPC82X_PINT_TRIGGER_BOTH_EDGES, /**< \brief ˫���ش���ģʽ */
    AMHW_LPC82X_PINT_TRIGGER_OFF         /**< \brief �رմ���ģʽ   */
} amhw_lpc82x_pint_trigger_t;

/**
 * \brief �ж�λƬ���
 */
typedef enum amhw_lpc82x_pint_bitslice {
    AMHW_LPC82X_PINT_BITSLICE_0 = 0,          /**< \brief λƬ 0         */
    AMHW_LPC82X_PINT_BITSLICE_1,              /**< \brief λƬ 1         */
    AMHW_LPC82X_PINT_BITSLICE_2,              /**< \brief λƬ 2         */
    AMHW_LPC82X_PINT_BITSLICE_3,              /**< \brief λƬ 3         */
    AMHW_LPC82X_PINT_BITSLICE_4,              /**< \brief λƬ 4         */
    AMHW_LPC82X_PINT_BITSLICE_5,              /**< \brief λƬ 5         */
    AMHW_LPC82X_PINT_BITSLICE_6,              /**< \brief λƬ 6         */
    AMHW_LPC82X_PINT_BITSLICE_7               /**< \brief λƬ 7         */
} amhw_lpc82x_pint_bitslice_t;

/**
 * \brief �ж�λƬ����ƥ�����
 */
typedef enum amhw_lpc82x_pint_slice_arg {
    AMHW_LPC82X_PINT_SLICE_ARG_ALWAYS_VALID = 0, /**< \brief һֱ��Ч           */ 
    AMHW_LPC82X_PINT_SLICE_ARG_STICKY_RISE,      /**< \brief ����������         */ 
    AMHW_LPC82X_PINT_SLICE_ARG_STICKY_FALL,      /**< \brief �����½���         */ 
    AMHW_LPC82X_PINT_SLICE_ARG_STICKY_RISE_FALL, /**< \brief ���������ػ��½��� */ 
    AMHW_LPC82X_PINT_SLICE_ARG_HIGH_LEVEL,       /**< \brief �ߵ�ƽ��Ч         */ 
    AMHW_LPC82X_PINT_SLICE_ARG_LOW_LEVEL,        /**< \brief �͵�ƽ��Ч         */ 
    AMHW_LPC82X_PINT_SLICE_ARG_ALWAYS_INVALID,   /**< \brief һֱ��Ч           */ 
    AMHW_LPC82X_PINT_SLICE_ARG_RISE_FALL         /**< \brief �����ػ��½����¼� */ 
} amhw_lpc82x_pint_slice_arg_t;

/**
 * \brief �����жϴ���ģʽ
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 * \param[in] mode      : ����ģʽ
 *
 * \return ��
 *
 * \note ���ؼ��״ֻ̬����������\n
 *       ����Ϊ�жϱ��ش���ģʽǰ��Ӧ���� #amhw_lpc82x_pint_rise_dec_clr() ���� 
 *       ���֮ǰ�ı��ؼ��״̬��
 */
void amhw_lpc82x_pint_trigger_set (amhw_lpc82x_pint_t         *p_hw_pint, 
                                   uint8_t                     chan,
                                   amhw_lpc82x_pint_trigger_t  mode);

/**
 * \brief ��ȡͨ���ĵ�ǰ����ģʽ
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 *
 * \return ͨ������ģʽ
 */
amhw_lpc82x_pint_trigger_t 
amhw_lpc82x_pint_trigger_get (amhw_lpc82x_pint_t *p_hw_pint, 
                              uint8_t             chan);

/**
 * \brief ��ȡ�����ؼ���״̬�����д���״̬
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 *
 * \retval AM_TRUE  ����⵽������
 * \retval AM_FALSE ��û�м�⵽�����ػ��������ر����
 */
am_static_inline 
am_bool_t amhw_lpc82x_pint_rise_dec_get (amhw_lpc82x_pint_t *p_hw_pint,
                                         uint8_t             chan)
{
    return (p_hw_pint->rise & AM_BIT(chan)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief �����Ӧͨ���������ؼ��
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_pint_rise_dec_clr (amhw_lpc82x_pint_t *p_hw_pint, 
                                    uint8_t             chan)
{
    p_hw_pint->rise = AM_BIT(chan);
}

/**
 * \brief ��ȡ�½��ؼ���״̬�����д���״̬
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 *
 * \retval AM_TRUE  ����⵽�½���
 * \retval AM_FALSE ��û�м�⵽�½��ػ����½��ر����
 */
am_static_inline 
am_bool_t amhw_lpc82x_pint_fall_dec_get (amhw_lpc82x_pint_t *p_hw_pint,
                                         uint8_t             chan)
{
    return ((p_hw_pint->fall & AM_BIT(chan)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �����Ӧͨ�����½��ؼ��
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_pint_fall_dec_clr (amhw_lpc82x_pint_t *p_hw_pint, 
                                    uint8_t             chan)
{
    p_hw_pint->fall = AM_BIT(chan);
}

/**
 * \brief ��ȡͨ���ж�״̬
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 *
 * \retval AM_TRUE  ��ͨ���ж��ж���������
 * \retval AM_FALSE ��û���ж�����
 */
am_static_inline 
am_bool_t amhw_lpc82x_pint_int_stat_get (amhw_lpc82x_pint_t *p_hw_pint,
                                         uint8_t             chan)
{
    return (p_hw_pint->ist & AM_BIT(chan)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ���ش����жϷ���ʱ�����ô˺���������ؼ��
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 *
 * \return ��
 *
 * \note �жϷ���ʱ�����ģʽΪ���ش�������Ҫ���øú�������жϱ�־
 */
am_static_inline 
void amhw_lpc82x_pint_edge_dec_clr (amhw_lpc82x_pint_t *p_hw_pint, 
                                    uint8_t             chan)
{
    p_hw_pint->ist = AM_BIT(chan);
}


/**
 * \brief ��ƽ�����жϷ���ʱ�����ô˺�����ת���ŵ��жϴ�����ƽ
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �ж�ͨ�����
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_pint_level_int_tog (amhw_lpc82x_pint_t *p_hw_pint, 
                                     uint8_t             chan)
{
    p_hw_pint->ist = AM_BIT(chan);
}


/**
 * \brief �����ж�ģʽΪģʽƥ������
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 *
 * \return ��
 *
 * \note ���ú������жϲ���ʹ��
 */
am_static_inline 
void amhw_lpc82x_pint_pmatch_mode_set (amhw_lpc82x_pint_t *p_hw_pint)
{
    AM_BIT_SET(p_hw_pint->pmctrl, 0);
}

/**
 * \brief �����ж�ģʽΪ�����ж�ģʽ
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_pint_pin_int_mode_set (amhw_lpc82x_pint_t *p_hw_pint)
{
    AM_BIT_CLR(p_hw_pint->pmctrl, 0);
}

/**
 * \brief ʹ��ģʽƥ������"�����¼�"���
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_pint_pmatch_rxev_enable (amhw_lpc82x_pint_t *p_hw_pint)
{
    AM_BIT_SET(p_hw_pint->pmctrl, 1);
}

/**
 * \brief ����ģʽƥ������"�����¼�"���
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_pint_pmatch_rxev_disable (amhw_lpc82x_pint_t *p_hw_pint)
{
    AM_BIT_CLR(p_hw_pint->pmctrl, 1);
}

/**
 * \brief ��ȡλƬ���״̬
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] slice     : λƬ���
 *
 * \retval AM_TRUE  : λƬ�����Ч
 * \retval AM_FALSE : λƬ�����Ч
 */
am_static_inline 
am_bool_t amhw_lpc82x_pint_pmatch_get (amhw_lpc82x_pint_t          *p_hw_pint,
                                       amhw_lpc82x_pint_bitslice_t  slice)
{
    return (p_hw_pint->pmctrl & AM_BIT(slice + 24)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ����λƬ����
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] slice     : λƬ���
 * \param[in] chan      : �ж�ͨ��
 * \param[in] arg       : λƬ����
 * \param[in] is_end    : �����ֵΪAM_TURE����ǰλƬ��Ϊ���չ���
 *
 * \return ��
 */
void amhw_lpc82x_pint_pmatch_slice_cfg(amhw_lpc82x_pint_t           *p_hw_pint, 
                                       amhw_lpc82x_pint_bitslice_t   slice,
                                       uint8_t                       chan,
                                       amhw_lpc82x_pint_slice_arg_t  arg,
                     am_bool_t                     is_end);
/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC82X_PINT_H */

/* end of file */
