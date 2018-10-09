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
 * \brief ACMP Ӳ�������ӿ�����
 *
 * 1. ��ѡ�ⲿ����ȿ������Ƚ����������룬Ҳ�������Ƚ����ĸ����룻
 * 2. �ڲ���׼��ѹ��0.9V��϶��׼��ѹ���ȿ������Ƚ����������룬Ҳ�������Ƚ����ĸ����룻
 * 3. 32�����ݵ�ѹ�ȿ������Ƚ����������룬Ҳ�������Ƚ����ĸ����룻
 * 4. ��ѹ����Դ�Ŀ�ѡ��Χ�ڵ�Դ����VDD��VDDCMP����֮�䣻
 * 5. ��ѹ�����ڲ���Ҫʱ�ɵ������磻
 * 6. �жϹ��ܡ�
 *
 * \internal
 * \par Modification history
 * - 1.02 15-12-12  hgo, fix amhw_lpc82x_acmp_ladsel_set() bug.
 * - 1.01 15-12-04  hgo, modify macro definition.
 * - 1.00 15-07-16  bob, first implementation.
 * \endinternal
 */
#ifndef  __AMHW_LPC82X_ACMP_H
#define  __AMHW_LPC82X_ACMP_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc82x_if_acmp
 * \copydoc amhw_lpc82x_acmp.h
 * @{
 */

/**
 * \brief ACMP �Ĵ�����ṹ��
 */
typedef struct amhw_lpc82x_acmp {
    __IO uint32_t ctrl;            /**< \brief ACMP ���ƼĴ���          */
    __IO uint32_t lad;             /**< \brief ACMP ������ƼĴ���      */
} amhw_lpc82x_acmp_t;

/**
 * \name ACMP ���ƼĴ���λ����
 * \anchor grp_amhw_lpc82x_acmp_ctrl
 * @{
 */

/** \brief COMPEDGE���������            */
#define AMHW_LPC82X_ACMP_CTRL_EDGESEL_FALL AM_SBF(0UL, 3)

/** \brief COMPEDGE���������            */
#define AMHW_LPC82X_ACMP_CTRL_EDGESEL_RISE AM_SBF(1UL, 3)

/** \brief COMPEDGE�������½������      */
#define AMHW_LPC82X_ACMP_CTRL_EDGESEL_BOTH AM_SBF(2UL, 3)

/** \brief �Ƚ������������ʱ��ͬ�����  */
#define AMHW_LPC82X_ACMP_CTRL_COMPSA       AM_SBF(1UL, 6)

/** \brief ��ѹ����������  */
#define AMHW_LPC82X_ACMP_CTRL_VP_LADOUT    AM_SBF(0UL, 8)

/** \brief �Ƚ���������1   */
#define AMHW_LPC82X_ACMP_CTRL_VP_CMP1      AM_SBF(1UL, 8)

/** \brief �Ƚ���������2   */
#define AMHW_LPC82X_ACMP_CTRL_VP_CMP2      AM_SBF(2UL, 8)

/** \brief �Ƚ���������3   */
#define AMHW_LPC82X_ACMP_CTRL_VP_CMP3      AM_SBF(3UL, 8)

/** \brief �Ƚ���������4   */
#define AMHW_LPC82X_ACMP_CTRL_VP_CMP4      AM_SBF(4UL, 8)

/** \brief ��׼��ѹ������  */
#define AMHW_LPC82X_ACMP_CTRL_VP_BGAP      AM_SBF(5UL, 8)

/** \brief ADCͨ��0������  */
#define AMHW_LPC82X_ACMP_CTRL_VP_ADC0      AM_SBF(6UL, 8)

/** \brief ��ѹ���ݸ�����  */
#define AMHW_LPC82X_ACMP_CTRL_VM_LADOUT    AM_SBF(0UL, 11)

/** \brief �Ƚ���������1   */
#define AMHW_LPC82X_ACMP_CTRL_VM_CMP1      AM_SBF(1UL, 11)

/** \brief �Ƚ���������2   */
#define AMHW_LPC82X_ACMP_CTRL_VM_CMP2      AM_SBF(2UL, 11)

/** \brief �Ƚ���������3   */
#define AMHW_LPC82X_ACMP_CTRL_VM_CMP3      AM_SBF(3UL, 11)

/** \brief �Ƚ���������4   */
#define AMHW_LPC82X_ACMP_CTRL_VM_CMP4      AM_SBF(4UL, 11)

/** \brief ��׼��ѹ������  */
#define AMHW_LPC82X_ACMP_CTRL_VM_BGAP      AM_SBF(5UL, 11)

/** \brief ADCͨ��0������  */
#define AMHW_LPC82X_ACMP_CTRL_VM_ADC0      AM_SBF(6UL, 11)

/** \brief �ж�����λ      */
#define AMHW_LPC82X_ACMP_CTRL_EDGECLR      AM_SBF(1UL, 20)

/** \brief �Ƚ������״̬  */
#define AMHW_LPC82X_ACMP_CTRL_COMPSTAT     AM_SBF(1UL, 21)

/** \brief ���ؼ��״̬    */
#define AMHW_LPC82X_ACMP_CTRL_COMPEDGE     AM_SBF(0UL, 23)

/** \brief �Ƚ���������    */
#define AMHW_LPC82X_ACMP_CTRL_HYS_NONE     AM_SBF(0UL, 25)

/** \brief �Ƚ�������5mV   */
#define AMHW_LPC82X_ACMP_CTRL_HYS_5MV      AM_SBF(1UL, 25)

/** \brief �Ƚ�������10mV  */
#define AMHW_LPC82X_ACMP_CTRL_HYS_10MV     AM_SBF(2UL, 25)

/** \brief �Ƚ�������20mV  */
#define AMHW_LPC82X_ACMP_CTRL_HYS_20MV     AM_SBF(3UL, 25)

/** @} */

/**
 * \name ACMP ��ѹ���ݼĴ���λ����
 * \anchor grp_amhw_lpc82x_acmp_ladder
 * @{
 */

/** \brief ���ݵ�ѹʹ��         */
#define AMHW_LPC82X_ACMP_LADDER_LADEN      AM_SBF(1UL, 0)

/** \brief ��׼��ѹΪ��ԴVDD    */
#define AMHW_LPC82X_ACMP_LADDER_VDD        AM_SBF(0UL, 6)

/** \brief ��׼��ѹΪVDDCMP���� */
#define AMHW_LPC82X_ACMP_LADDER_VDDCMP     AM_SBF(1UL, 6)

/** \brief ��ѹ����ֵ    */
#define AMHW_LPC82X_ACMP_LADDER_LADSEL(n)  AM_SBF((n) & 0x1F, 1)

/** @} */


/**
 * \brief ACMP���ƼĴ�������
 *
 * \param[in] p_hw_acmp     : ָ��ACMP�Ĵ������ָ��
 * \param[in] flags         : AMHW_LPC82X_ACMP_CTRL_* ��ֵ��
 *                            ���AMHW_LPC82X_ACMP_CTRL_*��Ļ�ֵ
 *                            ��(#AMHW_LPC82X_ACMP_CTRL_VM_CMP1)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_acmp_config(amhw_lpc82x_acmp_t *p_hw_acmp, uint32_t flags)
{
    p_hw_acmp->ctrl = flags;
}

/**
 * \brief ACMP���ƼĴ���λ����
 *
 * \param[in] p_hw_acmp     : ָ��ACMP�Ĵ������ָ��
 * \param[in] flags         : AMHW_LPC82X_ACMP_CTRL_* ��ֵ��
 *                            ���AMHW_LPC82X_ACMP_CTRL_*��Ļ�ֵ
 *                           (#AMHW_LPC82X_ACMP_CTRL_VM_CMP1)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_acmp_ctl_set(amhw_lpc82x_acmp_t *p_hw_acmp, uint32_t flags)
{
    AM_BIT_SET_MASK(p_hw_acmp->ctrl, flags);
}

/**
 * \brief ACMP���ƼĴ���λ���
 *
 * \param[in] p_hw_acmp     : ָ��ACMP�Ĵ������ָ��
 * \param[in] flags         : AMHW_LPC82X_ACMP_CTRL_* ��ֵ��
 *                            ���AMHW_LPC82X_ACMP_CTRL_*��Ļ�ֵ
 *                            (#AMHW_LPC82X_ACMP_CTRL_VM_CMP1)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_acmp_ctl_clr(amhw_lpc82x_acmp_t *p_hw_acmp, uint32_t flags)
{
    AM_BIT_CLR_MASK(p_hw_acmp->ctrl, flags);
}

/**
 * \brief ACMP���ƼĴ������û�ȡ
 *
 * \param[in] p_hw_acmp    : ָ��ACMP�Ĵ������ָ��
 *
 * \return ���ƼĴ�����ֵ
 */
am_static_inline
uint32_t amhw_lpc82x_acmp_ctl_get(amhw_lpc82x_acmp_t *p_hw_acmp)
{
    return p_hw_acmp->ctrl;
}

/**
 * \brief ���ACMP�ж�
 *
 * \param[in] p_hw_acmp    : ָ��ACMP�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_acmp_int_clr(amhw_lpc82x_acmp_t *p_hw_acmp)
{
    AM_BIT_SET_MASK(p_hw_acmp->ctrl, AMHW_LPC82X_ACMP_CTRL_EDGECLR);
    AM_BIT_CLR_MASK(p_hw_acmp->ctrl, AMHW_LPC82X_ACMP_CTRL_EDGECLR);
}

/**
 * \brief ACMP���ݵ�ѹʹ��
 *
 * \param[in] p_hw_acmp    : ָ��ACMP�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_acmp_ladder_enable(amhw_lpc82x_acmp_t *p_hw_acmp)
{
    AM_BIT_SET_MASK(p_hw_acmp->lad, AMHW_LPC82X_ACMP_LADDER_LADEN);
}

/**
 * \brief ACMP���ݵ�ѹ����
 *
 * \param[in] p_hw_acmp    : ָ��ACMP�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_acmp_ladder_disable(amhw_lpc82x_acmp_t *p_hw_acmp)
{
    AM_BIT_CLR_MASK(p_hw_acmp->lad, AMHW_LPC82X_ACMP_LADDER_LADEN);
}

/**
 * \brief ACMPѡ���׼��ѹ���ţ���ԴVDD���Ż�VDDCMP���ţ�
 *
 * \param[in] p_hw_acmp  : ָ��ACMP�Ĵ������ָ��
 * \param[in] io_flag    : ���Ʊ�־  #AMHW_LPC82X_ACMP_LADDER_VDD ��
 *                                   #AMHW_LPC82X_ACMP_LADDER_VDDCMP
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_acmp_ladref_set(amhw_lpc82x_acmp_t *p_hw_acmp, uint32_t io_flag)
{
    uint32_t lad = p_hw_acmp->lad;
    
    AM_BIT_CLR_MASK(lad, AMHW_LPC82X_ACMP_LADDER_VDDCMP);
    AM_BIT_SET_MASK(lad, io_flag);
    
    p_hw_acmp->lad = lad;
}

/**
 * \brief ACMP���õ�ѹ����ֵ
 *
 * \param[in] p_hw_acmp   : ָ��ACMP�Ĵ������ָ��
 * \param[in] value       : ��ѹ����ֵ��0~31����׼��ѹ = �����ѹ * value / 31��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_acmp_ladsel_set(amhw_lpc82x_acmp_t *p_hw_acmp, uint32_t value)
{
    uint32_t lad = p_hw_acmp->lad;

    AM_BIT_CLR_MASK(lad, AM_SBF(0x1F, 1));
    AM_BIT_SET_MASK(lad, AMHW_LPC82X_ACMP_LADDER_LADSEL(value));
    
    p_hw_acmp->lad = lad;
    
}

/**
 *@} 
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMHW_LPC82X_ACMP_H */

/* end of file */

