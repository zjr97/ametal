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
 * \brief PMU Ӳ�������ӿ�
 * 
 * 1. ֧�ֵ͵�ѹ�����жϣ�
 * 2. ֧�ֵ͵�ѹ��λ��
 * 3. VLLSx����ȷ�Ͽ��ƣ�
 * 4. �ܴ�϶(����)ʹ�ܿ��ơ�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-14  ari, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_PMC_H
#define __AMHW_FSL_PMC_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
#include "am_bitops.h"
/**
 * \addtogroup amhw_fsl_if_pmc
 * \copydoc amhw_fsl_pmc.h
 * @{
 */

/**
 * \brief PMC�Ĵ�����ṹ��
 */
typedef struct amhw_fsl_puc {
    __IO uint8_t lvdsc1;      /**< \brief PMC �͵�ѹ״̬���ƼĴ���1 */
    __IO uint8_t lvdsc2;      /**< \brief PMC �͵�ѹ״̬���ƼĴ���2 */
    __IO uint8_t regsc;       /**< \brief PMC �������ƼĴ���        */
} amhw_fsl_pmc_t;

/**
 * \name PMC�жϱ�־
 * @{
 */

#define AMHW_FSL_PMC_FLAG_LVDF  AM_BIT(7)   /**< \brief �͵�ѹ����־ */
#define AMHW_FSL_PMC_FLAG_LVWF  AM_BIT(6)   /**< \brief �͵�ѹ������־ */

/** @} */

/**
 * \name PMC�ж�ѡ��
 * @{
 */

#define AMHW_FSL_PMC_IRQ_LVD    AM_BIT(7)   /**< \brief �͵�ѹ����ж� */
#define AMHW_FSL_PMC_IRQ_LVW    AM_BIT(6)   /**< \brief �͵�ѹ�����ж� */

/** @} */

/**
 * \name PMCȷ��ѡ��
 * @{
 */

#define AMHW_FSL_PMC_ACK_LVD    AM_BIT(7)   /**< \brief �͵�ѹ���ȷ�� */
#define AMHW_FSL_PMC_ACK_LVW    AM_BIT(6)   /**< \brief �͵�ѹ����ȷ�� */
#define AMHW_FSL_PMC_ACK_VLLS   AM_BIT(5)   /**< \brief VLLS����ȷ��   */

/** @} */

/** \brief �͵�ѹ�����ֵ */
typedef enum amhw_fsl_pmc_lvd_sel {
    AMHW_FSL_PMC_LVD_VLDL = 0,              /**< \brief ����ֵ��� */
    AMHW_FSL_PMC_LVD_VLDH                   /**< \brief ����ֵ��� */
} amhw_fsl_pmc_lvd_sel_t;

/** \brief �͵�ѹ������ֵ */
typedef enum amhw_fsl_pmc_lvw_sel {
    AMHW_FSL_PMC_LVW_VLW1 = 0,              /**< \brief ������ֵ1 */
    AMHW_FSL_PMC_LVW_VLW2,                  /**< \brief ������ֵ2 */
    AMHW_FSL_PMC_LVW_VLW3,                  /**< \brief ������ֵ3 */
    AMHW_FSL_PMC_LVW_VLW4                   /**< \brief ������ֵ4 */
} amhw_fsl_pmc_lvw_sel_t;


/**
 * \brief ��ȡPMC�жϱ�־
 * \param[in] p_hw_pmc : ָ��PMC�Ĵ������ָ��
 * \return �жϱ�־
 */
am_static_inline
uint8_t amhw_fsl_pmc_int_flags_get (amhw_fsl_pmc_t *p_hw_pmc)
{
    uint8_t flags = (p_hw_pmc->lvdsc1 & 0x80);

    flags |= (p_hw_pmc->lvdsc2 & 0x80) >> 1;

    return flags;
}

/**
 * \brief ʹ��PMC�ж�
 *
 * \param[in] p_hw_pmc  : ָ��PMC�Ĵ������ָ��
 * \param[in] irq_flags : �ж϶��壬AMHW_FSL_PMC_IRQ_*��ֵ(#AMHW_FSL_PMC_IRQ_LVW)
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_int_enable (amhw_fsl_pmc_t *p_hw_pmc, uint8_t irq_flags)
{
    if (irq_flags & AMHW_FSL_PMC_IRQ_LVD) {
        p_hw_pmc->lvdsc1 |= 0x20;
    }
    if (irq_flags & AMHW_FSL_PMC_IRQ_LVW) {
        p_hw_pmc->lvdsc2 |= 0x20;
    }
}

/**
 * \brief ����PMC�ж�
 *
 * \param[in] p_hw_pmc  : ָ��PMC�Ĵ������ָ��
 * \param[in] irq_flags : �ж϶��壬AMHW_FSL_PMC_IRQ_*��ֵ(#AMHW_FSL_PMC_IRQ_LVW)
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_int_disable (amhw_fsl_pmc_t *p_hw_pmc, uint8_t irq_flags)
{
    if (irq_flags & AMHW_FSL_PMC_IRQ_LVD) {
        p_hw_pmc->lvdsc1 &= (~0x20);
    }
    if (irq_flags & AMHW_FSL_PMC_IRQ_LVW) {
        p_hw_pmc->lvdsc2 &= (~0x20);
    }
}

/**
 * \brief ʹ�ܵ͵�ѹ��λ����
 * \param[in] p_hw_pmc  : ָ��PMC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_lvdrest_enable (amhw_fsl_pmc_t *p_hw_pmc)
{
    p_hw_pmc->lvdsc1 |= 0x10;
}

/**
 * \brief ���ܵ͵�ѹ��λ����
 * \param[in] p_hw_pmc  : ָ��PMC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_lvdrest_disable (amhw_fsl_pmc_t *p_hw_pmc)
{
    p_hw_pmc->lvdsc1 &= (~0x10);
}

/**
 * \brief ACKȷ�ϲ���
 *
 * \param[in] p_hw_pmc  : ָ��PMC�Ĵ������ָ��
 * \param[in] ack_flags : ACKȷ��ѡ���־��AMHW_FSL_PMC_ACK_*��ֵ(#AMHW_FSL_PMC_ACK_LVD)
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_ack_set (amhw_fsl_pmc_t *p_hw_pmc, uint8_t ack_flags)
{
    if (ack_flags & AMHW_FSL_PMC_ACK_LVD) {
        p_hw_pmc->lvdsc1 |= 0x40;
    }
    if (ack_flags & AMHW_FSL_PMC_ACK_LVW) {
        p_hw_pmc->lvdsc2 |= 0x40;
    }
    if (ack_flags & AMHW_FSL_PMC_ACK_VLLS) {
        p_hw_pmc->regsc |= 0x08;
    }
}

/**
 * \brief �͵�ѹ�����ֵѡ��
 *
 * \param[in] p_hw_pmc : ָ��PMC�Ĵ������ָ��
 * \param[in] sel      : ��ֵѡ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_lvd_cfg (amhw_fsl_pmc_t *p_hw_pmc, amhw_fsl_pmc_lvd_sel_t sel)
{
    p_hw_pmc->lvdsc1 = (sel | (p_hw_pmc->lvdsc1 & 0x3));
}

/**
 * \brief �͵�ѹ������ֵѡ��
 *
 * \param[in] p_hw_pmc : ָ��PMC�Ĵ������ָ��
 * \param[in] sel      : ��ֵѡ��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_lvw_cfg (amhw_fsl_pmc_t *p_hw_pmc, amhw_fsl_pmc_lvw_sel_t sel)
{
    p_hw_pmc->lvdsc2 = (sel | (p_hw_pmc->lvdsc1 & 0x3));
}

/**
 * \brief ʹ���ܴ�϶��������VLPXģʽ
 * \param[in] p_hw_pmc : ָ��PMC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_bandgap_enable (amhw_fsl_pmc_t *p_hw_pmc)
{
    p_hw_pmc->regsc |= 0x10;
}

/**
 * \brief �����ܴ�϶��������VLPXģʽ
 * \param[in] p_hw_pmc : ָ��PMC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_bandgap_disable (amhw_fsl_pmc_t *p_hw_pmc)
{
    p_hw_pmc->regsc &= (~0x10);
}

/**
 * \brief ʹ���ܴ�϶������
 * \param[in] p_hw_pmc : ָ��PMC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_bandgap_buf_enable (amhw_fsl_pmc_t *p_hw_pmc)
{
    p_hw_pmc->regsc |= 0x01;
}

/**
 * \brief �����ܴ�϶������
 * \param[in] p_hw_pmc : ָ��PMC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_pmc_bandgap_buf_disable (amhw_fsl_pmc_t *p_hw_pmc)
{
    p_hw_pmc->regsc &= (~0x01);
}

/**
 * \brief ���ص���������״̬
 *
 * \param[in] p_hw_pmc : ָ��PMC�Ĵ������ָ��
 *
 * \retval AM_TRUE  : ����������
 * \retval AM_FALSE : ������û�й��������ڹ���״̬
 */
am_static_inline
am_bool_t amhw_fsl_pmc_regulator_wstat_get (amhw_fsl_pmc_t *p_hw_pmc)
{
    return (p_hw_pmc->regsc & 0x04) ? AM_TRUE : AM_FALSE;
}

/** 
 * @} amhw_fsl_if_pmc
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_PMC_H */

/*end of file */
