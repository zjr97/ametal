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
 * \brief ��ģת����DAC�������ӿ�
 * 1. Ƭ�Ͽɱ�����������(��ѹ����� 1/4096Vin �� Vin Vin ������ 1/4096Vin)
 * 2. Vin ���Դ������ο���Դ��ѡ��
 *    DACREF_1��DACREF_2���룬DACREF_1���ӵ�VREFH�ܽţ�DACREF_2����VDDA�ܽ�
 * 3. ������ͣ��ģʽ�ľ�̬����
 * 4. ֧�� 16 λ�����ݻ�����
 * 5. ֧�� DMA
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-26  mkr, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_DAC_H
#define __AMHW_FSL_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup amhw_fsl_if_dac
 * \copydoc amhw_fsl_dac.h
 * @{
 */

/**
 * \brief dac �Ĵ�����ṹ��
 */
typedef struct amhw_fsl_dac {
    struct{
        __IO uint8_t datl;      /**< \brief DAC ���ݣ��ͣ��Ĵ���   */
        __IO uint8_t dath;      /**< \brief DAC ���ݣ��ߣ��Ĵ���   */
    } dat[2];                   /**< \brief DAC ���ݼĴ�������       */
    __IO uint8_t reserved[28];  /**< \brief ����                                       */
    __IO uint8_t sr;            /**< \brief DAC ״̬�Ĵ���               */
    __IO uint8_t c0;            /**< \brief DAC���ƼĴ���0     */
    __IO uint8_t c1;            /**< \brief DAC���ƼĴ��� 1     */
    __IO uint8_t c2;            /**< \brief DAC���ƼĴ��� 2     */
} amhw_fsl_dac_t;


/**
 * \brief DAC ͨ�����
 */
#define AMHW_FSL_DAC0_CHAN_0          0      /**< \brief DAC ͨ�� 0 */

/**
 * \brief DAC ��������С
 */
#define AMHW_FSL_DAC_DATL_COUNT       2      /**< \brief DAC ��������С */


/**
 * \name DAC���ݼĴ�������λ�궨��
 * @{
 */

/**
 * \brief DAC ����ͨ������
 */
typedef enum amhw_fsl_dac_dat_index {
    AMHW_FSL_DAC_DAT_0 = 0,                  /**< \brief  ����ͨ��0 */
    AMHW_FSL_DAC_DAT_1                       /**< \brief  ����ͨ��1 */
} amhw_fsl_dac_dat_index_t;

/** \brief ���ݼĴ������� */
#define AMHW_FSL_DAC_DAT_LOW_MASK  0xFFu
#define AMHW_FSL_DAC_DAT_HIGH_MASK 0x0Fu

/** \brief ���ݼĴ������� */
#define AMHW_FSL_DAC_DAT_LOW(x)  \
        (((uint8_t)(((uint8_t)(x)) << 0)) & AMHW_FSL_DAC_DAT_LOW_MASK)

#define AMHW_FSL_DAC_DAT_HIGH(x) \
        (((uint8_t)(((uint8_t)(x)) << 0)) & AMHW_FSL_DAC_DAT_HIGH_MASK)
/** @} */

/**
 * \name DAC ���ƼĴ���C0 λ�궨��
 * \anchor grp_amhw_fsl_dac_c0
 * @{
 */

/**
 * \brief DAC �ο���ѹѡ������
 */
typedef enum amhw_fsl_dac_vref_sel {
    AMHW_FSL_DAC_VREF_1,                    /**< \brief  DACREF_1 ��Ϊ�ο���ѹ */
    AMHW_FSL_DAC_VREF_2,                    /**< \brief  DACREF_2 ��Ϊ�ο���ѹ */
} amhw_fsl_dac_vref_sel_t;

 /**
 * \brief DAC����Դѡ������
 */
typedef enum amhw_fsl_dac_trg_sel {
    AMHW_FSL_DAC_TRG_HARD,                  /**< \brief  DAC Ӳ������         */
    AMHW_FSL_DAC_TRG_SOFT,                  /**< \brief  DAC �������         */
} amhw_fsl_dac_trg_sel_t;

 /**
 * \brief DAC����ģʽ����
 */
typedef enum amhw_fsl_dac_power_sel {
    AMHW_FSL_DAC_POWER_HIGH,                  /**< \brief  DAC High-Powerģʽ  */
    AMHW_FSL_DAC_POWER_LOW                    /**< \brief  DAC Low-Powerģʽ  */
} amhw_fsl_dac_power_sel_t;

/** \brief DACʹ��                                                        */
#define AMHW_FSL_DAC_C0_EN                  ((uint8_t)(1 << 7))
/** \brief DAC����                                                        */
#define AMHW_FSL_DAC_C0_DISEN               ((uint8_t)(0 << 7))
/** \brief DAC�ο���ѹѡ��                                                */
#define AMHW_FSL_DAC_C0_VREF_SEL(x)         ((uint8_t)(((uint8_t)(x)) << 6))
/** \brief  DAC ����Դѡ��                                                */
#define AMHW_FSL_DAC_C0_TRG_SEL(x)          ((uint8_t)(((uint8_t)(x)) << 5))
/** \brief DAC�������ʹ��                                                */
#define AMHW_FSL_DAC_C0_TRG_SOFT_EN         ((uint8_t)(1 << 4))
/** \brief DAC�����������                                                */
#define AMHW_FSL_DAC_C0_TRG_SOFT_DISEN      ((uint8_t)(0 << 4))
/** \brief ʹ��DAC�͹���ģʽ                                              */
#define AMHW_FSL_DAC_C0_POWER_SEL(x)        ((uint8_t)(((uint8_t)(x)) << 3))

/** \brief DAC �����ȡ��ָ���ж�ʹ��                                     */
#define AMHW_FSL_DAC_C0_BTI_EN              ((uint8_t)(1 << 1))
/** \brief DAC �����ȡ��ָ���жϽ���                                     */
#define AMHW_FSL_DAC_C0_BTI_DISEN           ((uint8_t)(0 << 1))
/** \brief DAC �����ȡ��ָ���ж�ʹ��                                     */
#define AMHW_FSL_DAC_C0_BBI_EN              ((uint8_t)(1 << 0))
/** \brief DAC �����ȡ��ָ���жϽ���                                     */
#define AMHW_FSL_DAC_C0_BBI_DISEN           ((uint8_t)(0 << 0))

/** @} */

/**
 * \name DAC ���ƼĴ���C1 λ�궨��
 * @{
 */

 /**
 * \brief DAC����������ģʽѡ��
 */
typedef enum amhw_fsl_dac_buf_mode {
    AMHW_FSL_DAC_BUFMODE_NORMAL,              /**< \brief  DAC ��ͨģʽ         */
    AMHW_FSL_DAC_BUFMODE_SCAN,                /**< \brief  DAC ����ɨ��ģʽ     */
} amhw_fsl_dac_buf_mode_t;

/** \brief DAC��DMAʹ��                                                     */
#define AMHW_FSL_DAC_C1_DMA_EN              ((uint8_t)(1 << 7))
/** \brief DAC ����ģʽ����                                             */
#define AMHW_FSL_DAC_C1_BUFMODE_SEL(x)      ((uint8_t)(((uint8_t)(x)) << 2))
/** \brief DAC ����ʹ��                                                     */
#define AMHW_FSL_DAC_C1_BUF_EN              ((uint8_t)(1 << 0))

/** @} */

/**
 * \name DAC ״̬�Ĵ���SRλ�궨��
 * @{
 */

/** \brief DAC ��������ָ��λ�ñ�־����                               */
#define AMHW_FSL_DAC_SR_BFRP_TOPF_MASK       ((uint8_t)(1 << 1))
/** \brief DAC ��������ָ��λ�ñ�־����                                */
#define AMHW_FSL_DAC_SR_BFRP_BOTF_MASK       ((uint8_t)(1 << 0))

/** @} */

/**
 * \brief DAC ���������ò����ṹ��
 */
typedef struct amhw_fsl_dac_buffer_config
{
    am_bool_t buffer_enable;               /**< \brief  DAC ������ʹ�ܱ�־                 */
    amhw_fsl_dac_trg_sel_t trig_mode;  /**< \brief  DAC ������־                             */
    am_bool_t start_int_enable;            /**< \brief  DAC �����ȡ��ָ���ж�ʹ�� */
    am_bool_t upper_int_enable;            /**< \brief  DAC �����ȡ��ָ���ж�ʹ�� */
    am_bool_t dma_enable;                  /**< \brief  DAC DMAʹ��λ                        */
    amhw_fsl_dac_buf_mode_t buf_mode;  /**< \brief  DAC BUF����ģʽѡ��λ        */
    am_bool_t upper_limit_enable;          /**< \brief  DAC ����ֵ����ʹ�ܱ�־         */
} amhw_fsl_dac_buffer_config_t;

/**
 * \brief dac �жϱ�־λö�ٶ���
 */
typedef enum amhw_fsl_dac_flag_t
{
    AMHW_FSL_DAC_BUF_FLAG_START = 1U, /**< \brief ����ָ�뿪ʼ�¼���־λ */
    AMHW_FSL_DAC_BUF_FLAG_UPPER = 2U  /**< \brief ����ָ�뵽�����ޱ�־λ */
} amhw_fsl_dac_flag_t;

/**
 * \brief DAC���ƼĴ���0���ú���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] flags    : ���ò��� �μ�\ref grp_amhw_fsl_dac_c0
                         AMHW_FSL_DAC_C0_*��ֵ��AMHW_FSL_DAC_C0_*�����ֵ�Ļ�ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_c0_cfg (amhw_fsl_dac_t *p_hw_dac, uint8_t flags)
{
    p_hw_dac->c0 = flags;
}

/**
 * \brief д���ݵ�DAC �����ݼĴ���
 *
 * \param[in] p_hw_dac  : ָ��DAC�Ĵ������ָ��
 * \param[in] dat_index : AMHW_FSL_DAC_DAT_* ö������
 * \param[in] datl      : datlֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_datl_set (amhw_fsl_dac_t           *p_hw_dac,
                             amhw_fsl_dac_dat_index_t  dat_index,
                             uint8_t                    datl)
{
    p_hw_dac->dat[dat_index].datl = AMHW_FSL_DAC_DAT_LOW(datl);
}

/**
 * \brief д���ݵ�DAC �����ݼĴ���
 *
 * \param[in] p_hw_dac  : ָ��DAC�Ĵ������ָ��
 * \param[in] dat_index : AMHW_FSL_DAC_DAT_* ö������
 * \param[in] dath      : dathֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_dath_set (amhw_fsl_dac_t           *p_hw_dac,
                             amhw_fsl_dac_dat_index_t  dat_index,
                             uint8_t                    dath)
{
    p_hw_dac->dat[dat_index].dath = AMHW_FSL_DAC_DAT_HIGH(dath);
}

/**
 * \brief д���ݵ�DAC ���ݼĴ���
 *
 * \param[in] p_hw_dac  : ָ��DAC�Ĵ������ָ��
 * \param[in] dat_index : AMHW_FSL_DAC_DAT_* ö������
 * \param[in] dat       : datֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_dat_set (amhw_fsl_dac_t           *p_hw_dac,
                            amhw_fsl_dac_dat_index_t  dat_index,
                            uint16_t                   dat)
{
    p_hw_dac->dat[dat_index].datl = AMHW_FSL_DAC_DAT_LOW(dat);
    p_hw_dac->dat[dat_index].dath = AMHW_FSL_DAC_DAT_HIGH(dat >> 8);
}


/**
 * \brief ʹ��DAC���ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_enable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c0 |= AMHW_FSL_DAC_C0_EN;
}

/**
 * \brief ����DAC���ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_disable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c0 &= ~AMHW_FSL_DAC_C0_EN;
}

/**
 * \brief DAC�ο���ѹ���ú���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] vref     : amhw_fsl_dac_vref_sel_tö������
 *                       AMHW_FSL_DAC_VREF_* ��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_refv_sel (amhw_fsl_dac_t          *p_hw_dac,
                             amhw_fsl_dac_vref_sel_t  vref)
{
    p_hw_dac->c0 &= ~(1 << 6);
    p_hw_dac->c0 |= AMHW_FSL_DAC_C0_VREF_SEL(vref);
}

/**
 * \brief DAC����Դ���ú���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] trg      : amhw_fsl_dac_trg_sel_tö������
 *                       AMHW_FSL_DAC_TRG_* ö��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_trg_sel (amhw_fsl_dac_t         *p_hw_dac,
                            amhw_fsl_dac_trg_sel_t  trg)
{
    p_hw_dac->c0 &= ~(1 << 5);
    p_hw_dac->c0 |= AMHW_FSL_DAC_C0_TRG_SEL(trg);
}

/**
 * \brief DAC�������ʹ�ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_soft_trg_enable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c0 |= AMHW_FSL_DAC_C0_TRG_SOFT_EN;
}

/**
 * \brief DAC����������ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_soft_trg_disable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c0 &= ~AMHW_FSL_DAC_C0_TRG_SOFT_EN;
}

/**
 * \brief DAC����ģʽ���ú���
 *
 * \param[in] p_hw_dac   : ָ��DAC�Ĵ������ָ��
 * \param[in] power_mode : amhw_fsl_dac_power_sel_tö������
 *                         AMHW_FSL_POWER_* ��ֵ
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_power_set (amhw_fsl_dac_t           *p_hw_dac,
                              amhw_fsl_dac_power_sel_t  power_mode)
{
    p_hw_dac->c0 &= ~(1 << 3);
    p_hw_dac->c0 |= AMHW_FSL_DAC_C0_POWER_SEL(power_mode);
}

/**
 * \brief �����ȡ��ָ���ж�ʹ�ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_buftop_int_enable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c0 |= AMHW_FSL_DAC_C0_BTI_EN;
}

/**
 * \brief �����ȡ��ָ���жϽ��ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_buftop_int_disable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c0 &= ~AMHW_FSL_DAC_C0_BTI_EN;
}

/**
 * \brief �����ȡ��ָ���ж�ʹ�ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_bufbot_int_enable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c0 |= AMHW_FSL_DAC_C0_BBI_EN;
}

/**
 * \brief �����ȡ��ָ���жϽ��ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_bufbot_int_disable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c0 &= ~AMHW_FSL_DAC_C0_BBI_EN;
}

/**
 * \brief DAC�������ģʽ���ú���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] bf_mode  : amhw_fsl_dac_buf_mode_tö������
 *                       AMHW_FSL_DAC_BUFMODE_* ��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_bufmode_set(amhw_fsl_dac_t          *p_hw_dac,
                               amhw_fsl_dac_buf_mode_t  bf_mode)
{
    p_hw_dac->c1 &= ~(1 << 2);
    p_hw_dac->c1 |= AMHW_FSL_DAC_C1_BUFMODE_SEL(bf_mode);
}

/**
 * \brief ʹ��DAC��DMA����
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_dma_enable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c1 |= AMHW_FSL_DAC_C1_DMA_EN;
}

/**
 * \brief ����DAC��DMA����
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_dma_disable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c1 &= ~AMHW_FSL_DAC_C1_DMA_EN;
}

/**
 * \brief ʹ��DAC�Ļ���������
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_buf_enable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c1 |= AMHW_FSL_DAC_C1_BUF_EN;
}

/**
 * \brief ����DAC�Ļ���������
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_buf_disable (amhw_fsl_dac_t *p_hw_dac )
{
    p_hw_dac->c1 &= ~AMHW_FSL_DAC_C1_BUF_EN;
}

/**
 * \brief ����DAC����������ֵ
 *
 * \param[in] p_hw_dac   : ָ��DAC�Ĵ������ָ��
 * \param[in] buf_up_val : ����������ֵ buf_up_val
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_c2_buf_up (amhw_fsl_dac_t *p_hw_dac, uint8_t buf_up_val)
{
    p_hw_dac->c2 |= ((uint8_t)(buf_up_val & 0x01));
}

/**
 * \brief ����DAC������ָ��
 *
 * \param[in] p_hw_dac   : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_c2_bfrp_set (amhw_fsl_dac_t *p_hw_dac)
{
    p_hw_dac->c2 |= ((uint8_t)(1 << 4));
}

/**
 * \brief ����DAC������ָ��
 *
 * \param[in] p_hw_dac   : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_c2_bfrp_clr (amhw_fsl_dac_t *p_hw_dac)
{
    p_hw_dac->c2 &= ~((uint8_t)(1 << 4));
}

/**
 * \brief ��ȡDAC��������־λ
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] flag     : ��Ҫ�õ����жϱ�־λ amhw_fsl_dac_flag_t ö������
 *                       AMHW_FSL_DAC_BUF_FLAG_* ��ֵ
 * \return    AM_TRUE     : ��־λ��λ
 *            AM_FALSE    : ��־λû����λ
 */
am_static_inline
am_bool_t amhw_fsl_dac_bufint_flag_get (amhw_fsl_dac_t      *p_hw_dac,
                                      amhw_fsl_dac_flag_t  flag)
{
    am_bool_t b_ret = AM_TRUE;

    switch (flag) {

    case AMHW_FSL_DAC_BUF_FLAG_START:
        b_ret = (am_bool_t)((p_hw_dac->sr & AMHW_FSL_DAC_SR_BFRP_BOTF_MASK));
        break;

    case AMHW_FSL_DAC_BUF_FLAG_UPPER:
        b_ret = (am_bool_t)(p_hw_dac->sr & AMHW_FSL_DAC_SR_BFRP_TOPF_MASK);
        break;

    default:
        b_ret = AM_FALSE;
        break;
    }

    return b_ret;
}

/**
 * \brief ���DAC�������жϱ�־λ
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] flag     : ��Ҫ�õ����жϱ�־λ amhw_fsl_dac_flag_t ö������
 *                       AMHW_FSL_DAC_BUF_FLAG_* ��ֵ
 * \return ��
 */
am_static_inline
void amhw_fsl_dac_bufint_flag_clr (amhw_fsl_dac_t      *p_hw_dac,
                                    amhw_fsl_dac_flag_t  flag)
{
    switch (flag) {

    case AMHW_FSL_DAC_BUF_FLAG_START:
        p_hw_dac->sr &= ~AMHW_FSL_DAC_SR_BFRP_BOTF_MASK;
        break;

    case AMHW_FSL_DAC_BUF_FLAG_UPPER:
        p_hw_dac->sr &= ~AMHW_FSL_DAC_SR_BFRP_TOPF_MASK;
        break;

    default:
        p_hw_dac->sr &= ~AMHW_FSL_DAC_SR_BFRP_BOTF_MASK;
        p_hw_dac->sr &= ~AMHW_FSL_DAC_SR_BFRP_TOPF_MASK;
        break;
    }
}

/**
 * \brief ���û�����ֵ
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] start    : ��Ҫ����ֵ����ʼλ��
 * \param[in] offset   : ÿ��ƫ��ֵ
 * \param[in] arr[]    : ��Ž�Ҫд�뻺������ֵ
 *
 * \return    AM_ERROR : ����bufֵ����
 *            AM_OK    : ����bufֵ�ɹ�
 */
am_static_inline
int amhw_fsl_dac_buf_val_set (amhw_fsl_dac_t *p_hw_dac,
                               uint8_t          start,
                               uint8_t          offset,
                               uint16_t         arr[])
{
    uint8_t i;

    if ((!arr) || (start + offset > AMHW_FSL_DAC_DATL_COUNT)){
        return AM_ERROR;
    }

    for (i = 0; i < offset; i++) {
        amhw_fsl_dac_dat_set(p_hw_dac,
                              (amhw_fsl_dac_dat_index_t)(start + i),
                              arr[i]);
    }

    return AM_OK;
}
/**
 * \brief DAC���ݻ�������ʼ��
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] p_buf    : ָ��DAC���������ýṹ��
 *
 * \return ��
 */
void amhw_fsl_dac_dat_buf_init (amhw_fsl_dac_t               *p_hw_dac,
                                 amhw_fsl_dac_buffer_config_t *p_buf);

/**
 * @} amhw_if_fsl_dac
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_DAC_H */

/* end of file */
