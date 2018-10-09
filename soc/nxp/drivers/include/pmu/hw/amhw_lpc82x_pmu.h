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
 * \brief LPC82X PMU Ӳ�������ӿ�����
 * 
 * 1. ����ģʽ���ƣ�
 * 2. �͹����������ƣ�
 * 3. ���ͨ�ñ��ݼĴ���������ȵ���ģʽ�±������ݣ�
 * 4. ���¶ȷ�Χ(-40��~ 105��)��Vdd��ѹֵ��Χ(1.8V~3.35V)��������������
 * ע�⣺
 *     ��ȵ���ģʽ������������ܹ���(�����ֲ�˵��)��
 *         - �¶�С�ڵ���25�ȣ�Vdd��ѹֵ����3.4V
 *         - �¶ȴ���25�ȣ�Vdd��ѹֵ����3.35V
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-01  sky, modified.
 * - 1.00 15-07-13  zxl, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC82X_PMU_H
#define __AMHW_LPC82X_PMU_H

#include "ametal.h"
#include "am_lpc82x.h"
#include "hw/amhw_lpc82x_syscon.h"

#ifdef __cplusplus
extern "C" {
#endif

 /** 
 * \addtogroup amhw_lpc82x_if_pmu
 * \copydoc amhw_lpc82x_pmu.h
 * @{
 */

/**
  * \brief LPC82x PMU ��Դ����Ĵ�����ṹ��
 */
typedef struct amhw_lpc82x_pmu {
    __IO uint32_t pcon;      /**< \brief ƫ��: 0x00 ��Դ���ƼĴ���(R/W) */
    __IO uint32_t gpreg[4];  /**< \brief ƫ��: 0x04 ͨ�üĴ���0��3(R/W) */
    __IO uint32_t dpdctrl;   /**< \brief ƫ��: 0x14 ��ȵ�����ƼĴ���0(R/W) */
} amhw_lpc82x_pmu_t;


/**
 * \brief �͹���ģʽ
 */
typedef enum amhw_lpc82x_pmu_pm_src {
    AMHW_LPC82X_PMU_PCON_MODE_NORMAL = 0,   /**< \brief ����ģʽ��˯��ģʽ */
    AMHW_LPC82X_PMU_PCON_MODE_DEEPSLP,      /**< \brief ���˯��ģʽ */
    AMHW_LPC82X_PMU_PCON_MODE_PD,           /**< \brief ����ģʽ */
    AMHW_LPC82X_PMU_PCON_MODE_DEEPPD,       /**< \brief ��ȵ���ģʽ */
} amhw_lpc82x_pmu_pm_src_t;


/**
 * \brief ͨ�üĴ���
 */
typedef enum amhw_lpc82x_pmu_gp_reg_src {
    GP_REG_0 = 0,                /**< \brief ͨ�üĴ���0 */
    GP_REG_1,                    /**< \brief ͨ�üĴ���1 */
    GP_REG_2,                    /**< \brief ͨ�üĴ���2 */
    GP_REG_3,                    /**< \brief ͨ�üĴ���3 */
} amhw_lpc82x_pmu_gp_reg_src_t;

/**
 * \brief PMU PCON PM ѡ���Դģʽ
 *
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \param[in] value    : ���ò���ֵΪ amhw_lpc82x_pmu_pm_src_t
 *                       #AMHW_LPC82X_PMU_PCON_MODE_NORMAL   : ������˯��ģʽ
 *                       #AMHW_LPC82X_PMU_PCON_MODE_DEEPSLP  : ���˯��ģʽ
 *                       #AMHW_LPC82X_PMU_PCON_MODE_PD       : ����ģʽ
 *                       #AMHW_LPC82X_PMU_PCON_MODE_DEEPPD   : ��ȵ���ģʽ
 *                                               ��ARM Cortex-M0+ �ں˵��磩
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_pm_cfg (amhw_lpc82x_pmu_t        *p_hw_pmu,
                             amhw_lpc82x_pmu_pm_src_t  value)
{
    AM_BIT_CLR_MASK(p_hw_pmu->pcon, 0x03);
    AM_BIT_SET_MASK(p_hw_pmu->pcon, value);
}

/**
 * \brief PMU PCON NODPD ��ֹ����������ȵ���ģʽ
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 *
 * \note ��λֻ��ͨ���ϵ縴λ�ſ����㣬��˽�1д���λ������������
 *       ʹ���޷�������ȵ���ģʽ��
 */
am_static_inline
void amhw_lpc82x_pmu_nodpd_enable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    AM_BIT_SET(p_hw_pmu->pcon, 3);
}

/**
 * \brief PMU PCON SLEEPFLAG ��ȡ˯��ģʽ��־״̬
 *
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 *
 * \retval 0 : �������ڹ���ģʽ
 * \retval 1 : �����ѽ���˯��/���˯�߻���ȵ���ģʽ
 */
am_static_inline
uint8_t amhw_lpc82x_pmu_sleepflag_get (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    return (((p_hw_pmu->pcon & AM_BIT(8)) != 0) ? 1 : 0);
}

/**
 * \brief PMU PCON SLEEPFLAG д 1 SLEEPFLAGλ����
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_sleepflag_clear (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    p_hw_pmu->pcon = ((p_hw_pmu->pcon) & 0xF) | AM_BIT(8);
}

/**
 * \brief PMU PCON DPDFLAG ��ȡ��ȵ����־״̬
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \retval 0 : ���������ȵ���ģ
 * \retval 1 : �����ѽ�����ȵ���ģʽ
 */
am_static_inline
uint8_t amhw_lpc82x_pmu_dpdflag_get (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    return (((p_hw_pmu->pcon & AM_BIT(11)) != 0) ? 1 : 0);
}

/**
 * \brief PMU PCON DPDFLAG д 1 DPDFLAGλ����
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_dpdflag_clear (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    p_hw_pmu->pcon = ((p_hw_pmu->pcon) & 0xF) | AM_BIT(11);
}

/**
 * \brief PMU GPDATA ������ȵ���ģʽ�±�������
 *
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \param[in] chan     : ͨ�üĴ��� 0~3 (#GP_REG_0)
 * \param[in] value    : ������Ҫ����������
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_pmu_gpdata_save (amhw_lpc82x_pmu_t            *p_hw_pmu,
                                  amhw_lpc82x_pmu_gp_reg_src_t  chan,
                                  uint32_t                      value)
{
    p_hw_pmu->gpreg[chan] = value;
}

/**
 * \brief PMU GPDATA ��ȡ��ȵ���ģʽ�±�������
 *
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \param[in] chan     : ͨ�üĴ��� 0~3 (#GP_REG_0)
 *
 * \return ���ض�Ӧ�Ĵ�����������ֵ
 */
am_static_inline 
uint32_t amhw_lpc82x_pmu_gpdata_get (amhw_lpc82x_pmu_t            *p_hw_pmu,
                                     amhw_lpc82x_pmu_gp_reg_src_t  chan)
{
    return (p_hw_pmu->gpreg[chan]);
}

/**
 * \brief PMU DPDCTRL WAKEUPHYS WAKEUP���ų���ʹ��
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_wakeuphys_enable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    AM_BIT_SET(p_hw_pmu->dpdctrl, 0);
}

/**
 * \brief PMU DPDCTRL WAKEUPHYS WAKEUP���ų��ͽ���
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_wakeuphys_disable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    AM_BIT_CLR(p_hw_pmu->dpdctrl, 0);
}

/**
 * \brief PMU DPDCTRL WAKEPAD_DISABLE WAKEUP����ʹ��(ʹ��PIO0_4���ѹ���)
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_wakepad_enable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
     AM_BIT_CLR(p_hw_pmu->dpdctrl, 1);
}

/**
 * \brief PMU DPDCTRL WAKEPAD_DISABLE WAKEUP���Ž���(����PIO0_4���ѹ���)
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_wakepad_disable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
     AM_BIT_SET(p_hw_pmu->dpdctrl, 1);
}

/**
 * \brief PMU DPDCTRL LPOSCEN ʹ�ܵ͹�������
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_lposcen_enable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
     AM_BIT_SET(p_hw_pmu->dpdctrl, 2);
}

/**
 * \brief PMU DPDCTRL LPOSCEN ���ܵ͹�������
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_lposcen_disable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
     AM_BIT_CLR(p_hw_pmu->dpdctrl, 2);
}

/**
 * \brief PMU DPDCTRL LPOSCDPDEN ��ȵ���ģʽ��ʹ�ܵ͹�������
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_lposcdpden_enable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
     AM_BIT_SET(p_hw_pmu->dpdctrl, 3);
}

/**
 * \brief PMU DPDCTRL LPOSCDPDEN ��ȵ���ģʽ�½��ܵ͹�������
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_lposcdpden_disable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
     AM_BIT_CLR(p_hw_pmu->dpdctrl, 3);
}

/**
 * \brief PMU DPDCTRL WAKEUPCLKHYS WAKEUP���ų���ʹ��
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_wakeupclkhys_enable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    AM_BIT_SET(p_hw_pmu->dpdctrl, 4);
}

/**
 * \brief PMU DPDCTRL WAKEUPCLKHYS WAKEUP���ų��ͽ���
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_wakeupclkhys_disable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    AM_BIT_CLR(p_hw_pmu->dpdctrl, 4);
}

/**
 * \brief PMU DPDCTRL WAKECLKPAD_DISABLE WAKEUP����ʹ��(ʹ��PIO0_28�ⲿʱ�ӹ���)
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_wakeclkpad_enable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    AM_BIT_SET(p_hw_pmu->dpdctrl, 5);
}

/**
 * \brief PMU DPDCTRL WAKECLKPAD_DISABLE WAKEUP���Ž���(����PIO0_28�ⲿʱ�ӹ���)
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_pmu_wakeclkpad_disable (amhw_lpc82x_pmu_t *p_hw_pmu)
{
    AM_BIT_CLR(p_hw_pmu->dpdctrl, 5);
}


/**
 * @} amhw_lpc82x_if_pmu
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC82X_PMU_H */

/* end of file */
