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
 * \brief CMP Ӳ�������ӿ�
 *
 * 1. ���� 2.7 V �� 5.5 V ��������Դ��ѹ��Χ�ϲ�����
 * 2. Ƭ�� 6 λ�ֱ��� DAC���ɴ� VDD ���ڲ���϶��ѡ���׼��ѹ��
 * 3. �����ó��ͣ�
 * 4. ���ڱȽ�������������ء��½��ء����������ػ������½���ʱѡ���жϣ�
 * 5. ��ѡ��ת�Ƚ��������
 * 6. ����ֹͣģʽ�²�����
 * 7. ֧�ִ���DMA���䡣
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-14  mkr, first implementation.
 * \endinternal
 */
#ifndef  __AMHW_FSL_CMP_H
#define  __AMHW_FSL_CMP_H

#ifdef __cplusplus
extern "C" {
#endif
#include "am_types.h"

/**
 * \addtogroup amhw_fsl_if_cmp
 * \copydoc amhw_fsl_cmp.h
 * @{
 */

/**
 * \brief CMP �Ĵ�����ṹ��
 */
typedef struct amhw_fsl_cmp {
    __IO    uint8_t     ctrl0;          /**< \brief CMP �Ƚ������ƼĴ���0     */
    __IO    uint8_t     ctrl1;          /**< \brief CMP �Ƚ������ƼĴ���1     */
    __IO    uint8_t     fpr;            /**< \brief CMP �˲����ڼĴ���               */
    __IO    uint8_t     scr;            /**< \brief CMP ״̬����ƼĴ���     */
    __IO    uint8_t     daccr;          /**< \brief CMP DAC���ƼĴ���     */
    __IO    uint8_t     muxcr;          /**< \brief CMP MUX���ƼĴ���     */
} amhw_fsl_cmp_t;

/**
 * \name CMP ���ƼĴ���0λ����
 * \anchor grp_amhw_fsl_cmp_ctrl0
 * @{
 */
#define AMHW_FSL_CMP_CTRL0_FILTER_CNT_MASK    (7UL << 4)    /**< \brief �˲����������� */
#define AMHW_FSL_CMP_CTRL0_HYSTCTR_MASK       (3UL << 0)    /**< \brief ���Ϳ������� */

#define AMHW_FSL_CMP_CTRL0_FILTER_CNT_CFG(x) \
    (((x)<< 4) & AMHW_FSL_CMP_CTRL0_FILTER_CNT_MASK) /**< \brief �˲����������� */
#define AMHW_FSL_CMP_CTRL0_HYSTCTR_CFG(x) \
    (((x)<< 0) & AMHW_FSL_CMP_CTRL0_HYSTCTR_MASK) /**< \brief ���Ϳ������� */
/** @} */

/**
 * \name CMP ���ƼĴ���1λ����
 * \anchor grp_amhw_cmp_ctrl1
 * @{
 */
#define AMHW_FSL_CMP_CTRL1_EN_MASK    (1UL << 0)    /**< \brief ģ��ʹ������ */
#define AMHW_FSL_CMP_CTRL1_OPE_MASK   (1UL << 1)    /**< \brief �������ʹ������ */
#define AMHW_FSL_CMP_CTRL1_COS_MASK   (1UL << 2)    /**< \brief ���ѡ������ */
#define AMHW_FSL_CMP_CTRL1_INV_MASK   (1UL << 3)    /**< \brief �ȽϷ�ת���� */
#define AMHW_FSL_CMP_CTRL1_PMODE_MASK (1UL << 4)    /**< \brief ����ģʽ���� */
#define AMHW_CMP_FSL_CTRL1_TRIGM_MASK (1UL << 5)    /**< \brief ����ʹ��ʹ������ */
#define AMHW_FSL_CMP_CTRL1_WE_MASK    (1UL << 6)    /**< \brief ����ʹ������ */
#define AMHW_FSL_CMP_CTRL1_SE_MASK    (1UL << 7)    /**< \brief ����ʹ������ */
/** @} */

/**
 * \name CMP �˲�����λ����
 * \anchor grp_amhw_cmp_fpr
 * @{
 */
#define AMHW_FSL_CMP_FPR_MASK    0xFF    /**< \brief �˲��������� */
#define AMHW_FSL_CMP_FPR_CFG(x) ((x) & AMHW_FSL_CMP_FPR_MASK) /**< \brief �˲��������� */
/** @} */

/**
 * \name CMP ״̬���ƼĴ���λ����
 * \anchor grp_amhw_cmp_scr
 * @{
 */
#define AMHW_FSL_CMP_SCR_COUT_MASK    (1UL << 0)    /**< \brief ģ��������� */
#define AMHW_FSL_CMP_SCR_CFF_MASK     (1UL << 1)    /**< \brief �½��ر�־���� */
#define AMHW_FSL_CMP_SCR_CFR_MASK     (1UL << 2)    /**< \brief �����ر�־���� */
#define AMHW_FSL_CMP_SCR_IEF_MASK     (1UL << 3)    /**< \brief ʹ��CFF�ж����� */
#define AMHW_FSL_CMP_SCR_IER_MASK     (1UL << 4)    /**< \brief ʹ��CFR�ж����� */
#define AMHW_FSL_CMP_SCR_DMAEN_MASK   (1UL << 6)    /**< \brief ����DMA�������� */
/** @} */

/**
 * \name CMP DAC���ƼĴ���λ����
 * \anchor grp_amhw_cmp_daccr
 * @{
 */
#define AMHW_FSL_CMP_DACCR_VOSEL_MASK    0x0F   /**< \brief ��ѹѡ������ */
#define AMHW_FSL_CMP_DACCR_VRSEL_MASK    0x40   /**< \brief �����ѹѡ��Դ���� */
#define AMHW_FSL_CMP_DACCR_DACEN_MASK    0x80   /**< \brief DACģ��ʹ������ */

#define AMHW_FSL_CMP_DACCR_VOSEL_CFG(x) \
    ((x) & AMHW_FSL_CMP_DACCR_VOSEL_MASK) /**< \brief DAC�����ѹ���� */
/** @} */

/**
 * \name CMP ��ѡ���ƼĴ���λ����
 * \anchor grp_amhw_fsl_cmp_muxcr
 * @{
 */
#define AMHW_FSL_CMP_MUXCR_MSEL_MASK    (7UL << 0)    /**< \brief ��������ѡ������ */
#define AMHW_FSL_CMP_MUXCR_PSEL_MASK    (7UL << 3)    /**< \brief ͬ������ѡ������ */
#define AMHW_FSL_CMP_MUXCR_PSTM_MASK    (1UL << 7)    /**< \brief ��·�������� */

#define AMHW_FSL_CMP_MUXCR_MSEL_CFG(x) \
    ((x) & AMHW_FSL_CMP_MUXCR_MSEL_MASK) /**< \brief ��������ѡ������ */
#define AMHW_FSL_CMP_MUXCR_PSEL_CFG(x) \
    (((x) << 3) & AMHW_FSL_CMP_MUXCR_PSEL_MASK) /**< \brief ��������ѡ������ */
/** @} */


/**
 * \brief ���ó��͵�ƽ���ò���
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] level    : ���͵�ƽ
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_hyst_set (amhw_fsl_cmp_t *p_hw_cmp, uint8_t level)
{
    p_hw_cmp->ctrl0 &= ~AMHW_FSL_CMP_CTRL0_HYSTCTR_MASK;
    p_hw_cmp->ctrl0 |= AMHW_FSL_CMP_CTRL0_HYSTCTR_CFG(level);
}

/**
 * \brief ��ȡ���͵�ƽ���ò���
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return    ���͵�ƽ
 */
am_static_inline
uint8_t amhw_fsl_cmp_hyst_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (uint8_t)(p_hw_cmp->ctrl0 & AMHW_FSL_CMP_CTRL0_HYSTCTR_MASK);
}
/**
 * \brief �����˲���������
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] cnt      : �˲���������
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_filter_val_set (amhw_fsl_cmp_t *p_hw_cmp, uint8_t cnt)
{
    p_hw_cmp->ctrl0 &= ~AMHW_FSL_CMP_CTRL0_FILTER_CNT_MASK;
    p_hw_cmp->ctrl0 |= AMHW_FSL_CMP_CTRL0_FILTER_CNT_CFG(cnt);
}

/**
 * \brief ��ȡ�˲���������
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return  �˲���������
 */
am_static_inline
uint8_t amhw_fsl_cmp_filter_val_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (uint8_t)((p_hw_cmp->ctrl0 & AMHW_FSL_CMP_CTRL0_FILTER_CNT_MASK) >> 4);
}


/**
 * \brief ʹ�ܿ��ƼĴ���1ĳλ
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] mask     : �˲���������, ֵΪAMHW_FSL_CMP_CTRL1_*һ�������Ļ�ֵ
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_ctrl1_set (amhw_fsl_cmp_t *p_hw_cmp, uint8_t mask)
{
    p_hw_cmp->ctrl1 |= mask;
}
/**
 * \brief ������ƼĴ���1ĳλ
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] mask     : �˲���������, ֵΪAMHW_FSL_CMP_CTRL1_*һ�������Ļ�ֵ
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_ctrl1_clr (amhw_fsl_cmp_t *p_hw_cmp, uint8_t mask)
{
    p_hw_cmp->ctrl1 &= ~mask;
}

/**
 * \brief ���ÿ��ƼĴ���1
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] cfg     : �˲���������, ֵΪAMHW_FSL_CMP_CTRL1_*һ�������Ļ�ֵ
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_ctrl1_cfg (amhw_fsl_cmp_t *p_hw_cmp, uint8_t cfg)
{
    p_hw_cmp->ctrl1 = cfg;
}

/**
 * \brief  ʹ�ܲ���
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_sample_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 |= AMHW_FSL_CMP_CTRL1_SE_MASK;
}

/**
 * \brief ���ܲ���
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_sample_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 &= ~AMHW_FSL_CMP_CTRL1_SE_MASK;
}

/**
 * \brief  ʹ�ܴ��ڲ���
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_window_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 |= AMHW_FSL_CMP_CTRL1_WE_MASK;
}

/**
 * \brief ���ܴ��ڲ���
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_window_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 &= ~AMHW_FSL_CMP_CTRL1_WE_MASK;
}

/**
 * \brief  ʹ�ܴ���ģʽ
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_trigm_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 |= AMHW_CMP_FSL_CTRL1_TRIGM_MASK;
}

/**
 * \brief ���ܴ���ģʽ
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_trigm_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 &= ~AMHW_CMP_FSL_CTRL1_TRIGM_MASK;
}

/**
 * \brief  ����ģʽ
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_pmode_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 |= AMHW_FSL_CMP_CTRL1_PMODE_MASK;
}

/**
 * \brief ����ģʽ
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_pmode_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 &= ~AMHW_FSL_CMP_CTRL1_PMODE_MASK;
}

/**
 * \brief  ʹ�ܷ�ת
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_inv_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 |= AMHW_FSL_CMP_CTRL1_INV_MASK;
}

/**
 * \brief ����ת
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_inv_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 &= ~AMHW_FSL_CMP_CTRL1_INV_MASK;
}

/**
 * \brief  ѡ�����COUTA
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_cos_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 |= AMHW_FSL_CMP_CTRL1_COS_MASK;
}

/**
 * \brief ѡ�����COUT
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_cos_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 &= ~AMHW_FSL_CMP_CTRL1_COS_MASK;
}
/**
 * \brief  ʹ�ܱȽ��������
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_ope_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 |= AMHW_FSL_CMP_CTRL1_OPE_MASK;
}

/**
 * \brief ���ܱȽ��������
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_ope_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 &= ~AMHW_FSL_CMP_CTRL1_OPE_MASK;
}

/**
 * \brief  ʹ�ܱȽ�ģ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 |= AMHW_FSL_CMP_CTRL1_EN_MASK;
}

/**
 * \brief ���ܱȽ�ģ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->ctrl1 &= ~AMHW_FSL_CMP_CTRL1_EN_MASK;
}

/**
 * \brief �����˲���������
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] period   : �˲���������
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_fpr_set (amhw_fsl_cmp_t *p_hw_cmp, uint8_t period)
{
    p_hw_cmp->fpr = period;
}

/**
 * \brief ��ȡ�˲���������
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return    �˲���������
 */
am_static_inline
uint8_t amhw_fsl_cmp_fpr_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (uint8_t)(p_hw_cmp->fpr);
}

/**
 * \brief ��ȡCOUT״̬
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \retval AM_TRUE  : ״̬Ϊ1
 * \retval AM_FALSE : ״̬Ϊ0
 *
 */
am_static_inline
uint8_t amhw_fsl_cmp_cout_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (p_hw_cmp->scr & AMHW_FSL_CMP_SCR_COUT_MASK) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ��ȡCFF״̬
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \retval AM_TRUE  : ״̬Ϊ1
 * \retval AM_FALSE : ״̬Ϊ0
 */
am_static_inline
uint8_t amhw_fsl_cmp_cff_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (p_hw_cmp->scr & AMHW_FSL_CMP_SCR_CFF_MASK) ? AM_TRUE : AM_FALSE;
}
/**
 * \brief ��ȡCFR״̬
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \retval AM_TRUE  : ״̬Ϊ1
 * \retval AM_FALSE : ״̬Ϊ0
 */
am_static_inline
uint8_t amhw_fsl_cmp_cfr_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (p_hw_cmp->scr & AMHW_FSL_CMP_SCR_CFR_MASK) ? AM_TRUE : AM_FALSE;
}
/**
 * \brief ���CFF��־
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_cff_clr (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->scr |= AMHW_FSL_CMP_SCR_CFF_MASK;
}
/**
 * \brief ���CFR��־
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_cfr_clr (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->scr |= AMHW_FSL_CMP_SCR_CFR_MASK;
}

/**
 * \brief  ʹ��CFF�ж�
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_ief_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->scr |= AMHW_FSL_CMP_SCR_IEF_MASK;
}

/**
 * \brief ����CFF�ж�
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_ief_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->scr &= ~AMHW_FSL_CMP_SCR_IEF_MASK;
}

/**
 * \brief  ʹ��CFR�ж�
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_ier_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->scr |= AMHW_FSL_CMP_SCR_IER_MASK;
}

/**
 * \brief ����CFR�ж�
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_ier_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->scr &= ~AMHW_FSL_CMP_SCR_IER_MASK;
}

/**
 * \brief  ʹ�ܴ���DMA����
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_dma_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->scr |= AMHW_FSL_CMP_SCR_DMAEN_MASK;
}

/**
 * \brief ��ֹ����DMA����
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_dma_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->scr &= ~AMHW_FSL_CMP_SCR_DMAEN_MASK;
}

/**
 * \brief ����DAC�����ѹ
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] vosel    : ��ѹ����
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_dac_vol_set (amhw_fsl_cmp_t *p_hw_cmp, uint8_t vosel)
{
    p_hw_cmp->daccr &= ~AMHW_FSL_CMP_DACCR_VOSEL_MASK;
    p_hw_cmp->daccr |= AMHW_FSL_CMP_DACCR_VOSEL_CFG(vosel);
}

/**
 * \brief ��ȡDAC�����ѹ
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return    ���͵�ƽ
 */
am_static_inline
uint8_t amhw_fsl_cmp_dac_vol_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (uint8_t)(p_hw_cmp->daccr & AMHW_FSL_CMP_DACCR_VOSEL_MASK);
}

/**
 * \brief  ʹ��Vin2��Ϊ����ο���ѹ����
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_dac_vin2_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->daccr |= AMHW_FSL_CMP_DACCR_VRSEL_MASK;
}

/**
 * \brief ʹ��Vin1��Ϊ����ο���ѹ����
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_dac_vin2_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->daccr &= ~AMHW_FSL_CMP_DACCR_VRSEL_MASK;
}

/**
 * \brief  ʹ��6λDACģ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_dac_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->daccr |= AMHW_FSL_CMP_DACCR_DACEN_MASK;
}

/**
 * \brief ����6λDACģ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_dac_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->daccr &= ~AMHW_FSL_CMP_DACCR_DACEN_MASK;
}

/**
 * \brief ���÷�������˽���ͨ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] ch       : ����ͨ��
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_msel_set (amhw_fsl_cmp_t *p_hw_cmp, uint8_t ch)
{
    p_hw_cmp->muxcr &= ~AMHW_FSL_CMP_MUXCR_MSEL_MASK;
    p_hw_cmp->muxcr |= AMHW_FSL_CMP_MUXCR_MSEL_CFG(ch);
}

/**
 * \brief ��ȡ��������˽���ͨ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return    ����ͨ��
 */
am_static_inline
uint8_t amhw_fsl_cmp_msel_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (uint8_t)(p_hw_cmp->muxcr & AMHW_FSL_CMP_MUXCR_MSEL_MASK);
}
/**
 * \brief ����ͬ������˽���ͨ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \param[in] ch       : ����ͨ��
 * \return    ��
 */
am_static_inline
void amhw_fsl_cmp_psel_set (amhw_fsl_cmp_t *p_hw_cmp, uint8_t ch)
{
    p_hw_cmp->muxcr &= ~AMHW_FSL_CMP_MUXCR_PSEL_MASK;
    p_hw_cmp->muxcr |= AMHW_FSL_CMP_MUXCR_PSEL_CFG(ch);
}

/**
 * \brief ��ȡͬ������˽���ͨ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return    ����ͨ��
 */
am_static_inline
uint8_t amhw_fsl_cmp_psel_get (amhw_fsl_cmp_t *p_hw_cmp)
{
    return (uint8_t)(p_hw_cmp->muxcr & AMHW_FSL_CMP_MUXCR_PSEL_MASK);
}

/**
 * \brief  ʹ����·��ѡģ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_pstm_enable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->muxcr |= AMHW_FSL_CMP_MUXCR_PSTM_MASK;
}

/**
 * \brief ������·��ѡģ��
 *
 * \param[in] p_hw_cmp : ָ��CMP�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_cmp_pstm_disable (amhw_fsl_cmp_t *p_hw_cmp)
{
    p_hw_cmp->muxcr &= ~AMHW_FSL_CMP_MUXCR_PSTM_MASK;
}

/**
 *@}
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMHW_FSL_CMP_H */

/* end of file */
