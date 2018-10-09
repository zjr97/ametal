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
 * \brief SMC Ӳ�������ӿ�
 * 
 * 1. ϵͳģʽ���ƣ�
 * 2. ϵͳģʽ��ȡ��
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-14  mkr, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_SMC_H
#define __AMHW_FSL_SMC_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
#include "am_bitops.h"
/**
 * \addtogroup amhw_fsl_if_smc
 * \copydoc amhw_fsl_smc.h
 * @{
 */
 
/**
 * \brief SMC�Ĵ�����ṹ��
 */
typedef struct amhw_fsl_smc {
    __IO uint8_t  pmprot;           /**< \brief SMC ģʽ�����Ĵ��� */
    __IO uint8_t  pmctrl;           /**< \brief SMC ģʽ���ƼĴ��� */
    __IO uint8_t  stopctrl;         /**< \brief SMC ֹͣ���ƼĴ��� */
    __I  uint8_t  pmstat;           /**< \brief SMC ģʽ״̬�Ĵ��� */
} amhw_fsl_smc_t;

/**
 * \name ϵͳ�������ģʽ
 * @{
 */

#define AMHW_FSL_SMC_PROTECT_AVLP_ALLOW  AM_BIT(5) /**< \brief �������VLPxģʽ  */
#define AMHW_FSL_SMC_PROTECT_ALLS_ALLOW  AM_BIT(3) /**< \brief �������LLSģʽ   */
#define AMHW_FSL_SMC_PROTECT_AVLLS_ALLOW AM_BIT(1) /**< \brief �������VLLSxģʽ */

/** @} */

/**
 * \name ����ģʽ
 * @{
 */

#define AMHW_FSL_SMC_RUNMODE_RUN    AM_SBF(0x00, 5) /**< \brief ��������ģʽ    */
#define AMHW_FSL_SMC_RUNMODE_VLPR   AM_SBF(0x02, 5) /**< \brief �͹�������ģʽ  */

/** @} */

/**
 * \name ֹͣģʽ
 * @{
 */

/** \brief ����ֹͣģʽ */
#define AMHW_FSL_SMC_STOPMODE_STOP      (AM_SBF(0, 8) | AM_SBF(0, 6))

/** \brief ֹͣģʽ1 */
#define AMHW_FSL_SMC_STOPMODE_STOP1     (AM_SBF(0, 8) | AM_SBF(1, 6))

/** \brief ֹͣģʽ2 */
#define AMHW_FSL_SMC_STOPMODE_STOP2     (AM_SBF(0, 8) | AM_SBF(2, 6))

/** \brief �͹���ֹͣģʽ */
#define AMHW_FSL_SMC_STOPMODE_VLPS      (AM_SBF(2, 8) | 0)

/** \brief ��©��ֹͣģʽ */
#define AMHW_FSL_SMC_STOPMODE_LLS       (AM_SBF(3, 8) | 0)

/** \brief ����©��ֹͣģʽ3 */
#define AMHW_FSL_SMC_STOPMODE_VLLS3     (AM_SBF(4, 8) | AM_SBF(3, 0))

/** \brief ����©��ֹͣģʽ1 */
#define AMHW_FSL_SMC_STOPMODE_VLLS1     (AM_SBF(4, 8) | AM_SBF(1, 0))

/** \brief ����©��ֹͣģʽ0 */
#define AMHW_FSL_SMC_STOPMODE_VLLS0     (AM_SBF(4, 8) | AM_SBF(0, 0))

/** @} */

/**
 * \name оƬģʽ
 * @{
 */

#define AMHW_FSL_SMC_MODE_RUN    AM_BIT(0)   /**< \brief ����ģʽ        */
#define AMHW_FSL_SMC_MODE_STOP   AM_BIT(1)   /**< \brief ֹͣģʽ        */
#define AMHW_FSL_SMC_MODE_VLPR   AM_BIT(2)   /**< \brief �͹�������ģʽ  */
#define AMHW_FSL_SMC_MODE_VLPW   AM_BIT(3)   /**< \brief �͹��ĵȴ�ģʽ  */
#define AMHW_FSL_SMC_MODE_VLPS   AM_BIT(4)   /**< \brief �͹���ֹͣģʽ  */
#define AMHW_FSL_SMC_MODE_LLS    AM_BIT(5)   /**< \brief ��©��ģʽģʽ  */
#define AMHW_FSL_SMC_MODE_VLLS   AM_BIT(6)   /**< \brief ����©��ģʽ    */

/** @} */

/**
 * \brief ����ϵͳ��������ģʽ
 *
 * \param[in] p_hw_smc : ָ��SMC�Ĵ������ָ��
 * \param[in] flags    : ģʽ����궨�壬AMHW_SMC_PROTECT_*_ALLOW��ֵ����
 *                      ��#AMHW_FSL_SMC_PROTECT_AVLP_ALLOW��
 *
 * \return ��
 *
 * \note ��λ��ֻ���Բ���һ��
 */
am_static_inline
void amhw_fsl_smc_mode_allow_cfg (amhw_fsl_smc_t *p_hw_smc, uint8_t flags)
{
    p_hw_smc->pmprot = flags;
}

/**
 * \brief ����ģʽѡ��
 *
 * \param[in] p_hw_smc : ָ��SMC�Ĵ������ָ��
 * \param[in] flags    : ����ģʽ�궨�壬AMHW_FSL_SMC_RUNMODE_*��ֵ
 *                      ��#AMHW_FSL_SMC_RUNMODE_RUN��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_smc_run_mdoe_sel (amhw_fsl_smc_t *p_hw_smc, uint8_t flags)
{
    p_hw_smc->pmctrl = flags | (p_hw_smc->pmctrl & (~(0x03 << 5)));
}

/**
 * \brief ֹͣģʽѡ��
 *
 * \param[in] p_hw_smc : ָ��SMC�Ĵ������ָ��
 * \param[in] flags    : ֹͣģʽ�궨�壬AMHW_FSL_SMC_STOPMODE_*��ֵ
 *                      ��#AMHW_FSL_SMC_STOPMODE_STOP��
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_smc_stop_mdoe_sel (amhw_fsl_smc_t *p_hw_smc, uint16_t flags)
{
    uint8_t pmctrl   = p_hw_smc->pmctrl & (~0x07);
    uint8_t stopctrl = p_hw_smc->stopctrl & (~0xC7); /* stopλ��VLLSλ */

    pmctrl   |= flags >> 8;
    stopctrl |= flags;

    p_hw_smc->stopctrl = stopctrl;
    p_hw_smc->pmctrl   = pmctrl;
}

/**
 * \brief �жϽ���ֹͣģʽ�Ƿ��ж�
 * \param[in] p_hw_smc : ָ��SMC�Ĵ������ָ��
 * \retval AM_TRUE : ���жϣ�AM_FALSE : δ���ж�
 */
am_static_inline
am_bool_t amhw_fsl_smc_stop_mdoe_isabort (amhw_fsl_smc_t *p_hw_smc)
{
    return (p_hw_smc->pmctrl & 0x08) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ʹ��VLLS0ģʽ��Դ����·
 * \param[in] p_hw_smc : ָ��SMC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_smc_vlls0_por_enable (amhw_fsl_smc_t *p_hw_smc)
{
    p_hw_smc->stopctrl &= (~0x20);
}

/**
 * \brief ����VLLS0ģʽ��Դ����·
 * \param[in] p_hw_smc : ָ��SMC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_smc_vlls0_por_disable (amhw_fsl_smc_t *p_hw_smc)
{
    p_hw_smc->stopctrl |= 0x20;
}

/**
 * \brief ��ȡ��ǰϵͳģʽ
 * \param[in] p_hw_smc : ָ��SMC�Ĵ������ָ��
 * \return оƬģʽ
 */
am_static_inline
uint8_t amhw_fsl_smc_mode_get (amhw_fsl_smc_t *p_hw_smc)
{
    return p_hw_smc->pmstat;
}

/** 
 * @} amhw_if_fsl_smc
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_SMC_H */

/*end of file */
