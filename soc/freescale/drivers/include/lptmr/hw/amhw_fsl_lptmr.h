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
 * \brief �͹��Ķ�ʱ����ʱ����LPTMR�������ӿ�
 *
 * 1. 16λ��ʱ����������бȽϹ��ܵ������������
 *    -��ѡ���жϿ��Դ��κε͹���ģʽ�����첽����
 *    -Ӳ���������
 *    -������֧����������ģʽ���ڱȽ�ʱ��λ
 * 2. Ԥ��Ƶ��/���Ϲ������Ŀ����õ�ʱ��Դ;
 * 3. �������������������Դ��
 *    -������/�½���
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_LPTMR_H
#define __AMHW_FSL_LPTMR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_fsl_if_lptmr
 * \copydoc amhw_fsl_lptmr.h
 * @{
 */


/**
 * \brief LPTMR �Ĵ�����ṹ��
 */
typedef struct amhw_fsl_lptmr {
    __IO uint32_t ctl_stat;         /**< \brief ģ����ƼĴ��� */
    __IO uint32_t prescale;         /**< \brief Ԥ��Ƶ�Ĵ��� */
    __IO uint32_t compare;          /**< \brief �ȽϼĴ��� */
    __IO uint32_t counter;          /**< \brief �����Ĵ��� */
} amhw_fsl_lptmr_t;


/**
 * \name ״̬�Ϳ��ƼĴ���λ����(R/W)
 * @{
 */

#define AMHW_FSL_LPTMR_CSR_MASK    (0xFFU)
#define AMHW_FSL_LPTMR_CSR_TCF     (1UL << 7)         /**< \brief ��ʱ���Ƚϱ�־ */
#define AMHW_FSL_LPTMR_CSR_TIE     (1UL << 6)         /**< \brief ��ʱ���ж�ʹ�� */
#define AMHW_FSL_LPTMR_CSR_TPS(s)  (((s) & 0x3) << 4) /**< \brief ��ʱ������ѡ�� */
#define AMHW_FSL_LPTMR_CSR_TPP     (1UL << 3)         /**< \brief ��ʱ�����ż��� */
#define AMHW_FSL_LPTMR_CSR_TFC     (1UL << 2)         /**< \brief ��ʱ������������ֵ */
#define AMHW_FSL_LPTMR_CSR_TMS     (1UL << 1)         /**< \brief ��ʱ������ѡ�� */
#define AMHW_FSL_LPTMR_CSR_TEN     (1UL << 0)         /**< \brief ��ʱ��ʹ�� */

/** @} */

/**
 * \brief ���ƼĴ����趨
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \param[in] flags      : AMHW_FSL_LPTMR_CSR_* ��ֵ����
 *                         AMHW_FSL_LPTMR_CSR_*��� ��OR��ֵ(#AMHW_FSL_LPTMR_CSR_TEN)
 * \return ��
 */
am_static_inline
void amhw_fsl_lptmr_ctl_set (amhw_fsl_lptmr_t *p_hw_lptmr, uint32_t flags)
{
    p_hw_lptmr->ctl_stat |= flags;
}

/**
 * \brief ���ƼĴ����趨
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \param[in] flags      : AMHW_FSL_LPTMR_CSR_* ��ֵ����
 *                         AMHW_FSL_LPTMR_CSR_*��� ��OR��ֵ(#AMHW_FSL_LPTMR_CSR_TEN)
 * \return ��
 */
am_static_inline
void amhw_fsl_lptmr_ctl_clear (amhw_fsl_lptmr_t *p_hw_lptmr, uint32_t flags)
{
    p_hw_lptmr->ctl_stat &= ~flags;
}

/**
 * \brief ���ƼĴ����趨
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 *
 * \retval AM_TRUE  : �Ƚϱ�־����λ
 * \retval AM_FALSE : �Ƚϱ�־δ��λ
 * \note �ж�ʱ��Ҫ��if(amhw_fsl_lptmr_flag_check()==AM_TRUE)��
 *               Ӧ����if(amhw_fsl_lptmr_flag_check())
 */
am_static_inline
am_bool_t amhw_fsl_lptmr_flag_check (amhw_fsl_lptmr_t *p_hw_lptmr)
{
    return (am_bool_t)(p_hw_lptmr->ctl_stat & AMHW_FSL_LPTMR_CSR_TCF);
}

/**
 * \name Ԥ��Ƶ�Ĵ���λ����(R/W)
 * @{
 */

#define AMHW_FSL_LPTMR_PSR_TCF(s)  (((s) & 0xf) << 3) /**< \brief Ԥ��Ƶֵѡ�� */
#define AMHW_FSL_LPTMR_PSR_PBYP    (1UL << 2)         /**< \brief Ԥ��Ƶ����· */
#define AMHW_FSL_LPTMR_PSR_PCS(s)  (((s) & 0x3) << 0) /**< \brief LPTMRʱ��Դѡ�� */

/** @} */

/**
 * \brief LPTMR Ԥ��Ƶ����ѡ��
 * \note ��λ�򱻱�����������ʱ������ֹʱ�ſ��޸�
 */
typedef enum amhw_fsl_lptmr_ps {
    AMHW_FSL_LPTMR_DIVIDED_BY_2     = 0x0,    /**< \brief Ԥ��Ƶ����Ϊ2 */
    AMHW_FSL_LPTMR_DIVIDED_BY_4     = 0x1,    /**< \brief Ԥ��Ƶ����Ϊ4 */
    AMHW_FSL_LPTMR_DIVIDED_BY_8     = 0x2,    /**< \brief Ԥ��Ƶ����Ϊ8 */
    AMHW_FSL_LPTMR_DIVIDED_BY_16    = 0x3,    /**< \brief Ԥ��Ƶ����Ϊ16 */
    AMHW_FSL_LPTMR_DIVIDED_BY_32    = 0x4,    /**< \brief Ԥ��Ƶ����Ϊ32 */
    AMHW_FSL_LPTMR_DIVIDED_BY_64    = 0x5,    /**< \brief Ԥ��Ƶ����Ϊ64 */
    AMHW_FSL_LPTMR_DIVIDED_BY_128   = 0x6,    /**< \brief Ԥ��Ƶ����Ϊ128 */
    AMHW_FSL_LPTMR_DIVIDED_BY_256   = 0x7,    /**< \brief Ԥ��Ƶ����Ϊ256 */
    AMHW_FSL_LPTMR_DIVIDED_BY_512   = 0x8,    /**< \brief Ԥ��Ƶ����Ϊ512 */
    AMHW_FSL_LPTMR_DIVIDED_BY_1024  = 0x9,    /**< \brief Ԥ��Ƶ����Ϊ1024 */
    AMHW_FSL_LPTMR_DIVIDED_BY_2048  = 0xA,    /**< \brief Ԥ��Ƶ����Ϊ2048 */
    AMHW_FSL_LPTMR_DIVIDED_BY_4096  = 0xB,    /**< \brief Ԥ��Ƶ����Ϊ4096 */
    AMHW_FSL_LPTMR_DIVIDED_BY_8192  = 0xC,    /**< \brief Ԥ��Ƶ����Ϊ8192 */
    AMHW_FSL_LPTMR_DIVIDED_BY_16384 = 0xD,    /**< \brief Ԥ��Ƶ����Ϊ16384 */
    AMHW_FSL_LPTMR_DIVIDED_BY_32768 = 0xE,    /**< \brief Ԥ��Ƶ����Ϊ32768 */
    AMHW_FSL_LPTMR_DIVIDED_BY_65536 = 0xF,    /**< \brief Ԥ��Ƶ����Ϊ65536 */
} amhw_fsl_lptmr_ps_t;

/**
 * \brief LPTMRʱ��Դѡ��
 */
typedef enum amhw_fsl_lptmr_clock_src
{
    AMHW_FSL_LPTMR_CLOCK_SRC_MCGIRCLK = 0x0,    /**< \brief MCG ���ʱ��  */
    AMHW_FSL_LPTMR_CLOCK_SRC_LPOCLK,            /**< \brief LPO ʱ�� */
    AMHW_FSL_LPTMR_CLOCK_SRC_ER32KCLK,          /**< \brief ER32K ʱ�� */
    AMHW_FSL_LPTMR_CLOCK_SRC_OSCERCLK,          /**< \brief OSCERCLK ʱ�� */
} amhw_fsl_lptmr_clock_src_t;

/**
 * \brief ��ȡԤ��Ƶ�Ĵ�������
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \return Ԥ��Ƶ�Ĵ�������
 * \note �üĴ���λ���壺[6:3]��Ƶֵѡ��[2]��·ʹ�ܣ�[1:0]ʱ��Դѡ��
 */
am_static_inline
uint32_t amhw_fsl_lptmr_ps_reg_get (amhw_fsl_lptmr_t *p_hw_lptmr)
{
    return p_hw_lptmr->prescale;
}

/**
 * \brief Ԥ��Ƶ�����趨
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \param[in] val        : ��Ҫд���ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_lptmr_prescaler_set (amhw_fsl_lptmr_t    *p_hw_lptmr,
                                   amhw_fsl_lptmr_ps_t  val)
{
    AM_BITS_SET(p_hw_lptmr->prescale, 3, 4, val);
}

/**
 * \brief Ԥ��Ƶ�������趨
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \param[in] b_flag     : ʹ�ܻ����
 *                          -AM_TRUE ��Ƶ������·����Ƶ����Ч
 *                          -AM_FALSE ʹ�ܷ�Ƶ������Ƶ����Ч
 * \return ��
 */
am_static_inline
void amhw_fsl_lptmr_prescaler_filter_set (amhw_fsl_lptmr_t *p_hw_lptmr,
                                          am_bool_t             b_flag)
{
    if (b_flag) {
        p_hw_lptmr->prescale |= AMHW_FSL_LPTMR_PSR_PBYP;
    } else {
        p_hw_lptmr->prescale &= ~AMHW_FSL_LPTMR_PSR_PBYP;
    }
}

/**
 * \brief ����ʱ���趨
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \param[in] clk        : LPTMRʱ��Դѡ��ö������amhw_fsl_lptmr_clock_src_t��Ա
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_lptmr_clock_set (amhw_fsl_lptmr_t           *p_hw_lptmr,
                               amhw_fsl_lptmr_clock_src_t  clk)
{
    AM_BITS_SET(p_hw_lptmr->prescale, 0, 2, clk);
}


/**
 * \brief ʱ��Դ��ȡ
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \param[in] clk        : LPTMRʱ��Դѡ��ö������amhw_fsl_lptmr_clock_src_t��Ա
 *
 * \return ��
 */
am_static_inline
uint32_t amhw_fsl_lptmr_clock_get (amhw_fsl_lptmr_t           *p_hw_lptmr)
{
    return AM_BITS_GET(p_hw_lptmr->prescale, 0, 2);
}

/**
 * \name �ȽϼĴ���λ����(R/W)
 * @{
 */

#define AMHW_FSL_LPTMR_CMR_MASK     (0xFFFFu)    /**< \brief Ԥ��Ƶֵѡ�� */

/** @} */

/**
 * \brief �Ƚ����趨
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \param[in] val        : ��Ҫд���ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_lptmr_compare_set (amhw_fsl_lptmr_t *p_hw_lptmr,
                                 uint32_t          val)
{
    p_hw_lptmr->compare = val;
}

/**
 * \brief �Ƚ�����ȡ
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \return �Ƚ���ֵ
 */
am_static_inline
uint16_t amhw_fsl_lptmr_compare_get (amhw_fsl_lptmr_t *p_hw_lptmr)
{
    return p_hw_lptmr->compare;
}

/**
 * \name ����ֵ�Ĵ���λ����(R/W)
 * @{
 */

#define AMHW_FSL_LPTMR_CNR_MASK  (0xFFFFu)      /**< \brief Ԥ��Ƶֵѡ�� */

/** @} */

/**
 * \brief ��ʱ����ȡ
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \return ��ʱ��ֵ
 */
am_static_inline
uint16_t amhw_fsl_lptmr_counter_get (amhw_fsl_lptmr_t *p_hw_lptmr)
{
    /* ��ֵ֮ǰ��дһ������ֵ�ſ��Զ� */
    p_hw_lptmr->counter = 0;

    return p_hw_lptmr->counter;
}

/**
 * @} amhw_fsl_if_lptmr
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_LPTMR_H */

/* end of file */

