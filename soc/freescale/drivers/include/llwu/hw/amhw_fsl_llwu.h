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
 * \brief LLWU Ӳ�������ӿ�
 * 
 * - ����LLS��VLLSxģʽLLWU����Դ������Դ��Ϊ���ţ��ڲ�ģ�飬�˲�ͨ��
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-14  ari, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_LLWU_H
#define __AMHW_FSL_LLWU_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
#include "am_bitops.h"
/**
 * \addtogroup amhw_fsl_if_llwu
 * \copydoc amhw_fsl_llwu.h
 * @{
 */
 
/**
 * \brief LLWU �Ĵ�����ṹ��
 */
typedef struct amhw_fsl_llwu {
    __IO uint8_t  pe[4];          /**< \brief LLWU ��������ʹ�ܼĴ���  */
    __IO uint8_t  me;             /**< \brief LLWU ����ģ��ʹ�ܼĴ���  */
    __IO uint8_t  f[3];           /**< \brief LLWU ���ѱ�־�Ĵ���      */
    __IO uint8_t  filt[2];        /**< \brief LLWU ���������˲��Ĵ���  */
} amhw_fsl_llwu_t;

/**
 * \brief LLWU ��������(_X��ʾ��оƬ��֧��)
 */
typedef enum amhw_fsl_llwu_pin {
    AMHW_FSL_LLWU_PIN_0_X  = 0,     /**< \brief LLWU ��������P0    */
    AMHW_FSL_LLWU_PIN_1_X,          /**< \brief LLWU ��������P1    */
    AMHW_FSL_LLWU_PIN_2_X,          /**< \brief LLWU ��������P2    */
    AMHW_FSL_LLWU_PIN_3_X,          /**< \brief LLWU ��������P3    */
    AMHW_FSL_LLWU_PIN_4_X,          /**< \brief LLWU ��������P4    */
    AMHW_FSL_LLWU_PIN_5_PTB0,       /**< \brief LLWU ��������P5    */
    AMHW_FSL_LLWU_PIN_6_PTC1,       /**< \brief LLWU ��������P6    */
    AMHW_FSL_LLWU_PIN_7_PTC3,       /**< \brief LLWU ��������P7    */
    AMHW_FSL_LLWU_PIN_8_PTC4,       /**< \brief LLWU ��������P8    */
    AMHW_FSL_LLWU_PIN_9_PTC5,       /**< \brief LLWU ��������P9    */
    AMHW_FSL_LLWU_PIN_10_PTC6,      /**< \brief LLWU ��������P10   */
    AMHW_FSL_LLWU_PIN_11_X,         /**< \brief LLWU ��������P11   */
    AMHW_FSL_LLWU_PIN_12_X,         /**< \brief LLWU ��������P12   */
    AMHW_FSL_LLWU_PIN_13_X,         /**< \brief LLWU ��������P13   */
    AMHW_FSL_LLWU_PIN_14_PTD4,      /**< \brief LLWU ��������P14   */
    AMHW_FSL_LLWU_PIN_15_PTD6,      /**< \brief LLWU ��������P15   */
} amhw_fsl_llwu_pin_t;

/**
 * \brief LLWU �������Ų���
 */
typedef enum amhw_fsl_llwu_pin_arg{
    AMHW_FSL_LLWU_PIN_ARG_DISABLE  = 0,  /**< \brief ��ʹ�û������� */
    AMHW_FSL_LLWU_PIN_ARG_RISING,        /**< \brief �����ػ���     */
    AMHW_FSL_LLWU_PIN_ARG_FALLING,       /**< \brief �½��ػ���     */
    AMHW_FSL_LLWU_PIN_ARG_ANY            /**< \brief ���ű仯����   */
} amhw_fsl_llwu_pin_arg_t;

/**
 * \brief LLWU ����ģ��(_X��ʾ��оƬ��֧��)
 */
typedef enum amhw_fsl_llwu_module {
    AMHW_FSL_LLWU_MODULE_0_LPTMR0  = 0,     /**< \brief LLWU ����ģ��M0   */
    AMHW_FSL_LLWU_MODULE_1_CMP0,            /**< \brief LLWU ����ģ��M1   */
    AMHW_FSL_LLWU_MODULE_2_X,               /**< \brief LLWU ����ģ��M2   */
    AMHW_FSL_LLWU_MODULE_3_X,               /**< \brief LLWU ����ģ��M3   */
    AMHW_FSL_LLWU_MODULE_4_TSI0,            /**< \brief LLWU ����ģ��M4   */
    AMHW_FSL_LLWU_MODULE_5_RTCA,            /**< \brief LLWU ����ģ��M5   */
    AMHW_FSL_LLWU_MODULE_6_X,               /**< \brief LLWU ����ģ��M6   */
    AMHW_FSL_LLWU_MODULE_7_RTCS ,           /**< \brief LLWU ����ģ��M7   */
} amhw_fsl_llwu_module_t;

/**
 * \brief LLWU ����ģ�����
 */
typedef enum amhw_fsl_llwu_module_arg {
    AMHW_FSL_LLWU_MODULE_ARG_DISABLE = 0,     /**< \brief LLWU ����ģ�����   */
    AMHW_FSL_LLWU_MODULE_ARG_ENABLE = 1       /**< \brief LLWU ����ģ��ʹ��   */
} amhw_fsl_llwu_module_arg_t;

/**
 * \brief LLWU �˲�ͨ��
 */
typedef enum amhw_fsl_llwu_filt_chan {
    AMHW_FSL_LLWU_FILT_CHAN1  = 0,     /**< \brief LLWU ���������˲�ͨ��1   */
    AMHW_FSL_LLWU_FILT_CHAN2,          /**< \brief LLWU ���������˲�ͨ��2   */
} amhw_fsl_llwu_filt_chan_t;

/**
 * \brief LLWU �˲�ͨ������
 */
typedef enum amhw_fsl_llwu_filt_chan_arg{
    AMHW_FSL_LLWU_FILT_DETECT_DISABLE  = 0,  /**< \brief ��ʹ���˲�ͨ�� */
    AMHW_FSL_LLWU_FILT_DETECT_POSEDGE,       /**< \brief �����ؼ��     */
    AMHW_FSL_LLWU_FILT_DETECT_NEGEDGE,       /**< \brief �½��ؼ��     */
    AMHW_FSL_LLWU_FILT_DETECT_ANYEDGE        /**< \brief ˫���ؼ��     */
} amhw_fsl_llwu_filt_chan_arg_t;

/**
 * \name LLWU ���ѱ�־(_X��ʾ��оƬ��֧��)
 * @{
 */
typedef enum amhw_fsl_llwu_wuf {
    AMHW_FSL_LLWU_WUF_P0_X      = AM_BIT(0),    /**< \brief LLWU ���ѱ�־P0   */
    AMHW_FSL_LLWU_WUF_P1_X      = AM_BIT(1),    /**< \brief LLWU ���ѱ�־P1   */
    AMHW_FSL_LLWU_WUF_P2_X      = AM_BIT(2),    /**< \brief LLWU ���ѱ�־P2   */
    AMHW_FSL_LLWU_WUF_P3_X      = AM_BIT(3),    /**< \brief LLWU ���ѱ�־P3   */
    AMHW_FSL_LLWU_WUF_P4_X      = AM_BIT(4),    /**< \brief LLWU ���ѱ�־P4   */
    AMHW_FSL_LLWU_WUF_P5_PTB0   = AM_BIT(5),    /**< \brief LLWU ���ѱ�־P5   */
    AMHW_FSL_LLWU_WUF_P6_PTC1   = AM_BIT(6),    /**< \brief LLWU ���ѱ�־P6   */
    AMHW_FSL_LLWU_WUF_P7_PTC3   = AM_BIT(7),    /**< \brief LLWU ���ѱ�־P7   */
    AMHW_FSL_LLWU_WUF_P8_PTC4   = AM_BIT(8),    /**< \brief LLWU ���ѱ�־P8   */
    AMHW_FSL_LLWU_WUF_P9_PTC5   = AM_BIT(9),    /**< \brief LLWU ���ѱ�־P9   */
    AMHW_FSL_LLWU_WUF_P10_PTC6  = AM_BIT(10),   /**< \brief LLWU ���ѱ�־P10  */
    AMHW_FSL_LLWU_WUF_P11_X     = AM_BIT(11),   /**< \brief LLWU ���ѱ�־P11  */
    AMHW_FSL_LLWU_WUF_P12_X     = AM_BIT(12),   /**< \brief LLWU ���ѱ�־P12  */
    AMHW_FSL_LLWU_WUF_P13_X     = AM_BIT(13),   /**< \brief LLWU ���ѱ�־P13  */
    AMHW_FSL_LLWU_WUF_P14_PTD4  = AM_BIT(14),   /**< \brief LLWU ���ѱ�־P14  */
    AMHW_FSL_LLWU_WUF_P15_PTD6  = AM_BIT(15),   /**< \brief LLWU ���ѱ�־P15  */

    /* �ڲ�ģ���־������ֱ����� */
    AMHW_FSL_LLWU_WUF_M0_LPTMR0 = AM_BIT(16),   /**< \brief LLWU ���ѱ�־M0   */
    AMHW_FSL_LLWU_WUF_M1_CMP0   = AM_BIT(17),   /**< \brief LLWU ���ѱ�־M1   */
    AMHW_FSL_LLWU_WUF_M2_X      = AM_BIT(18),   /**< \brief LLWU ���ѱ�־M2   */
    AMHW_FSL_LLWU_WUF_M3_X      = AM_BIT(19),   /**< \brief LLWU ���ѱ�־M3   */
    AMHW_FSL_LLWU_WUF_M4_TSI0   = AM_BIT(20),   /**< \brief LLWU ���ѱ�־M4   */
    AMHW_FSL_LLWU_WUF_M5_RTCA   = AM_BIT(21),   /**< \brief LLWU ���ѱ�־M5   */
    AMHW_FSL_LLWU_WUF_M6_X      = AM_BIT(22),   /**< \brief LLWU ���ѱ�־M6   */
    AMHW_FSL_LLWU_WUF_M7RTC     = AM_BIT(23),   /**< \brief LLWU ���ѱ�־M7   */

    AMHW_FSL_LLWU_WUF_F1        = AM_BIT(24),   /**< \brief LLWU ���ѱ�־F1   */
    AMHW_FSL_LLWU_WUF_F2        = AM_BIT(25)    /**< \brief LLWU ���ѱ�־F2   */
} amhw_fsl_llwu_wuf_t;

/** @} */

/**
 * \brief �������Ż��ѹ���
 *
 * \param[in] p_hw_llwu : ָ��LLWU�Ĵ������ָ��
 * \param[in] wu_pin    : ��������
 * \param[in] arg       : ���Ų���
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_llwu_pin_cfg (amhw_fsl_llwu_t        *p_hw_llwu,
                             amhw_fsl_llwu_pin_t     wu_pin,
                             amhw_fsl_llwu_pin_arg_t arg)
{
    uint8_t arraypos = wu_pin / 4;
    uint8_t bitpos   = (wu_pin % 4) * 2;
    p_hw_llwu->pe[arraypos] = (arg << bitpos) |
                              (p_hw_llwu->pe[arraypos] & (~(0x3 << bitpos)));
}

/**
 * \brief �����ڲ�ģ�黽�ѹ���
 *
 * \param[in] p_hw_llwu : ָ��LLWU�Ĵ������ָ��
 * \param[in] module    : ����ģ��
 * \param[in] arg       : ģ�����
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_llwu_module_cfg (amhw_fsl_llwu_t            *p_hw_llwu,
                                amhw_fsl_llwu_module_t      module,
                                amhw_fsl_llwu_module_arg_t  arg)
{
    if (arg == AMHW_FSL_LLWU_MODULE_ARG_ENABLE) {
        p_hw_llwu->me |= (1 << module);
    } else {
        p_hw_llwu->me &= ~(1 << module);
    }
}

/**
 * \brief �����˲�ͨ������
 *
 * \param[in] p_hw_llwu : ָ��LLWU�Ĵ������ָ��
 * \param[in] chan      : �˲�ͨ��
 * \param[in] wu_pin    : ��������
 * \param[in] arg       : ������
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_llwu_filt_cfg (amhw_fsl_llwu_t              *p_hw_llwu,
                              amhw_fsl_llwu_filt_chan_t     chan,
                              amhw_fsl_llwu_pin_t           wu_pin,
                              amhw_fsl_llwu_filt_chan_arg_t arg)
{
    p_hw_llwu->filt[chan] = (arg << 5) | wu_pin;
}

/**
 * \brief ��ȡLLWU���ѱ�־
 * \param[in] p_hw_llwu : ָ��LLWU�Ĵ������ָ��
 * \return ���ѱ�־
 */
am_static_inline
uint32_t amhw_fsl_llwu_wuflags_get (amhw_fsl_llwu_t *p_hw_llwu)
{
    uint32_t flags =  (uint32_t)p_hw_llwu->f[0]                      | /* Px */
                     ((uint32_t)p_hw_llwu->f[1] << 8)                | /* Px */
                     ((uint32_t)p_hw_llwu->f[2] << 16)               | /* Mx */
                     ((uint32_t)(p_hw_llwu->filt[0] & (0x80)) << 17) | /* F1 */
                     ((uint32_t)(p_hw_llwu->filt[1] & (0x80)) << 18);  /* F2 */

    return flags;
}

/**
 * \brief ���LLWU���ѱ�־
 *
 * \param[in] p_hw_llwu : ָ��LLWU�Ĵ������ָ��
 * \param[in] flags     : ���ѱ�־�궨�壬AMHW_FSL_LLWU_WUF_*��ֵ
 *                        ��# AMHW_FSL_LLWU_WUF_P5_PTB0_��
 *
 * \return ��
 *
 * \note �ڲ�ģ���־ͨ����������־���
 */
am_static_inline
void amhw_fsl_llwu_wuflags_clr (amhw_fsl_llwu_t *p_hw_llwu, uint32_t flags)
{
    p_hw_llwu->f[0] = flags;                      /* ���Px */
    p_hw_llwu->f[1] = flags >> 8;

    p_hw_llwu->filt[0] |= ((flags >> 17) & 0x80); /* ���F1 */
    p_hw_llwu->filt[1] |= ((flags >> 18) & 0x80); /* ���F2 */
}

/** 
 * @} amhw_fsl_if_llwu
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_LLWU_H */

/*end of file */
