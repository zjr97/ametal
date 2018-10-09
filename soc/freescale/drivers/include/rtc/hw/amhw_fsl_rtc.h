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
 * \brief RTC Ӳ�������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */


#ifndef __AMHW_FSL_RTC_H
#define __AMHW_FSL_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_fsl_if_rtc
 * \copydoc amhw_fsl_rtc.h
 * @{
 */

/**
 *  \name RTC λ������صĺ궨��
 *  @{
 */

/******************************************************************************
  RTC У׼�Ĵ����������
******************************************************************************/

/** \brief У׼��Ъ��������ǰֵ��ʼλƫ���� */
#define AMHW_FSL_RTC_CIC_SHIFT  (24UL)

/** \brief ��ǰ��У׼ֵ��ʼλƫ���� */
#define AMHW_FSL_RTC_TCV_SHIFT  (16UL)

/** \brief У׼��Ъ������ʼλƫ���� */
#define AMHW_FSL_RTC_CIR_SHIFT  (8UL)

/** \brief У׼����ʼλƫ���� */
#define AMHW_FSL_RTC_TCR_SHIFT  (0UL)


/*******************************************************************************
  RTC ���ƼĴ���������غ�
*******************************************************************************/

/** \brief 2pF ��������λ */
#define AMHW_FSL_RTC_SC2P       (1 << 13UL)

/** \brief 4pF ��������λ */
#define AMHW_FSL_RTC_SC4P       (1 << 12UL)

/** \brief 8pF ��������λ */
#define AMHW_FSL_RTC_SC8P       (1 << 11UL)

/** \brief 16pF ��������λ */
#define AMHW_FSL_RTC_SC16P      (1 << 10UL)

/** \brief 32kHz ʱ������������豸ʹ��λ */
#define AMHW_FSL_RTC_CLKO       (1 <<  9UL)

/** \brief 32.768 kHzʱ��ʹ��λ */
#define AMHW_FSL_RTC_OSCE       (1 <<  8UL)

/** \brief ��������ѡ��λ */
#define AMHW_FSL_RTC_WPS        (1 <<  4UL)

/** \brief ����ǿ�Ƹ���ʹ��λ */
#define AMHW_FSL_RTC_UM         (1 <<  3UL)

/** \brief ����Ȩģʽ�¿�дʹ��λ */
#define AMHW_FSL_RTC_SUP        (1 <<  2UL)

/** \brief ��������ʹ��λ */
#define AMHW_FSL_RTC_WPE        (1 <<  1UL)

/** \brief RTC ģ�������λ */
#define AMHW_FSL_RTC_SWR        (1 <<  0UL)


/*******************************************************************************
  RTC ״̬�Ĵ���������غ�
*******************************************************************************/

/** \brief RTC ��ʹ�ܱ�־λ */
#define AMHW_FSL_RTC_TCE        (1 <<  4UL)

/** \brief ���ӷ�����־λ */
#define AMHW_FSL_RTC_TAF        (1 <<  2UL)

/** \brief RTC ʱ�Ӽ����������־λ */
#define AMHW_FSL_RTC_TOF        (1 <<  1UL)

/** \brief RTC ʱ��ģ����Ч��־λ */
#define AMHW_FSL_RTC_TIF        (1 <<  0UL)



/******************************************************************************
  RTC �����Ĵ���������غ�
******************************************************************************/

/** \brief RTC����ʹ��λ */
#define AMHW_FSL_RTC_LRL        (1 <<  6UL)

/** \brief RTC����״̬λ */
#define AMHW_FSL_RTC_SRL        (1 <<  5UL)

/** \brief RTC���ƼĴ�������ʹ��λ */
#define AMHW_FSL_RTC_CRL        (1 <<  4UL)

/** \brief RTCУ׼����ʹ��λ */
#define AMHW_FSL_RTC_TCL        (1 <<  3UL)


/*******************************************************************************
   RTC �ж�ʹ�ܼĴ���������غ�
*******************************************************************************/

/** \brief �������ſ���λ */
#define AMHW_FSL_RTC_WPON       (1 << 7UL)

/** \brief ÿ���ж�ʹ��λ */
#define AMHW_FSL_RTC_TSIE       (1 << 4UL)

/** \brief �����ж�ʹ�� */
#define AMHW_FSL_RTC_TAIE       (1 << 2UL)

/** \brief ����ж�ʹ�� */
#define AMHW_FSL_RTC_TOIE       (1 << 1UL)

/** \brief ʱ��ģ����Ч�ж�ʹ��λ */
#define AMHW_FSL_RTC_TIIE       (1 << 0UL)


/**
 *  @}
 */

/**
 *  \brief RTC �Ĵ����ṹ�嶨��
 */
typedef struct amhw_fsl_rtc {
    __IO uint32_t tsr;    /**< \brief RTC ��Ĵ��� */
    __IO uint32_t tpr;    /**< \brief RTC Ԥ��Ƶ�Ĵ��� */
    __IO uint32_t tar;    /**< \brief RTC ���ӼĴ��� */
    __IO uint32_t tcr;    /**< \brief RTC У׼�Ĵ��� */
    __IO uint32_t cr;     /**< \brief RTC ���ƼĴ��� */
    __IO uint32_t sr;     /**< \brief RTC ״̬�Ĵ��� */
    __IO uint32_t lr;     /**< \brief RTC �����Ĵ��� */
    __IO uint32_t ier;    /**< \brief RTC �ж�ʹ�ܼĴ��� */
} amhw_fsl_rtc_t;


/*******************************************************************************
    ������������
*******************************************************************************/

/**
 *  \brief д������Ĵ���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \param second Ҫд��������ֵ
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_second_set (amhw_fsl_rtc_t *p_hw_rtc, uint32_t second)
{
    p_hw_rtc->tsr = second;
}

/**
 *  \brief ��������Ĵ���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ������Ĵ�����ֵ
 */
am_static_inline
uint32_t amhw_fsl_rtc_second_get (amhw_fsl_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->tsr;
}

/**
 *  \brief дԤ��Ƶ�Ĵ���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \param[in] prescaler Ҫд���Ԥ��Ƶ����ֵ
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_prescaler_set (amhw_fsl_rtc_t *p_hw_rtc, uint16_t prescaler)
{
    p_hw_rtc->tpr = prescaler & 0xffff;
}

/**
 *  \brief ��Ԥ��Ƶ�Ĵ���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return Ԥ��Ƶ�Ĵ���
 */
am_static_inline
uint16_t amhw_fsl_rtc_prescaler_get (amhw_fsl_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->tpr & 0xffff);
}

/**
 *  \brief �������ӼĴ�����ֵ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \param alarm_second Ҫ���õ����ӼĴ���ֵ
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_alarm_set (amhw_fsl_rtc_t *p_hw_rtc, uint32_t alarm_second)
{
    p_hw_rtc->tar = alarm_second;
}

/**
 *  \brief ��ȡ���ӼĴ�����ֵ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ���ӼĴ�����ֵ
 */
am_static_inline
uint32_t amhw_fsl_rtc_alarm_get (amhw_fsl_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->tar;
}

/**
 *  \brief ����ÿ�ε�У׼��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \param value ÿ��У׼����
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_compensate_value_set (amhw_fsl_rtc_t *p_hw_rtc,
                                        uint32_t        value)
{
    p_hw_rtc->tcr |= ((value << AMHW_FSL_RTC_TCR_SHIFT) &
                      (0XFF << AMHW_FSL_RTC_TCR_SHIFT));
}

/**
 *  \brief ����У׼��Ъ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \param interval У׼��Ъ��ÿ���������һ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_compensate_interval_set (amhw_fsl_rtc_t *p_hw_rtc,
                                           uint32_t        interval)
{
    p_hw_rtc->tcr |= ((interval << AMHW_FSL_RTC_CIR_SHIFT) &
                      (0XFF << AMHW_FSL_RTC_CIR_SHIFT));
}

/**
 *  \brief ��ȡ��ǰ��У׼��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��ǰУ׼��
 */
am_static_inline
uint8_t amhw_fsl_rtc_current_compensate_value_get (amhw_fsl_rtc_t *p_hw_rtc)
{
    return (uint8_t)((p_hw_rtc->tcr & (0xff << AMHW_FSL_RTC_TCV_SHIFT))
                      >> AMHW_FSL_RTC_TCV_SHIFT);
}

/**
 *  \brief ���õ�ǰ��У׼��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *  \param value У׼����ÿ��У׼���ٵ�ʱ�Ӹ���
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_current_compensate_value_set (amhw_fsl_rtc_t *p_hw_rtc,
                                                uint8_t         value)
{
    p_hw_rtc->tcr |= (((p_hw_rtc->tcr                   &
                     (~(0xff << AMHW_FSL_RTC_TCV_SHIFT))))) |
                     (value << AMHW_FSL_RTC_TCV_SHIFT);
}

/**
 *  \brief ���õ�ǰ������Ъ��������ֵ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *  \param count ���õĵ�ǰ������ֵ
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_current_compensate_counter_set (amhw_fsl_rtc_t *p_hw_rtc,
                                                  uint8_t         count)
{
    p_hw_rtc->tcr |= ((p_hw_rtc->tcr                     &
                     (~(0xfful << AMHW_FSL_RTC_CIC_SHIFT)))) |
                     (count << AMHW_FSL_RTC_CIC_SHIFT);
}

/**
 *  \brief ���õ�����Ъ�͵�����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *  \param interval ������Ъ
 *  \param value ����ֵ
 *
 *  \return ��
 *
 */
am_static_inline
void amhw_fsl_rtc_current_interval_and_value_set (amhw_fsl_rtc_t *p_hw_rtc,
                                                  uint8_t         interval,
                                                  uint8_t         value)
{
    p_hw_rtc->tcr = (interval << 8) | value;
}

/**
 *  \brief ʹ�� 2pF����������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_2pf_load_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_SC2P;
}

/**
 *  \brief ���� 2pF����������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_2pf_load_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr &= (~ AMHW_FSL_RTC_SC2P);
}

/**
 *  \brief ʹ�� 4pF����������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_4pf_load_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_SC4P;
}

/**
 *  \brief ���� 4pF����������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_4pf_load_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr &= (~ AMHW_FSL_RTC_SC4P);
}

/**
 *  \brief ʹ�� 8pF����������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_8pf_load_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_SC8P;
}

/**
 *  \brief ���� 8pF����������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_8pf_load_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr &= (~ AMHW_FSL_RTC_SC8P);
}

/**
 *  \brief ʹ�� 16pF����������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_16pf_load_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_SC16P;
}

/**
 *  \brief ���� 16pF����������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_16pf_load_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr &= (~ AMHW_FSL_RTC_SC16P);
}

/**
 *  \brief 32kHzʱ������������豸ʹ��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_clk_output_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_CLKO;
}

/**
 *  \brief 32kHzʱ������������豸����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_clk_output_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr &= (~AMHW_FSL_RTC_CLKO);
}

/**
 *  \brief RTC 32.768kHz ����ʹ��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_osc_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_OSCE;
}

/**
 *  \brief RTC 32.768kHz ��������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_osc_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_OSCE;
}

/**
 *  \brief ������������״̬��д״̬�Ĵ���(SR)
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_update_mode_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_UM;
}

/**
 *  \brief ���ò�������������״̬��д״̬�Ĵ���(SR)
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_update_mode_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr &= (~AMHW_FSL_RTC_UM);
}

/**
 *  \brief ʹ�ܻ�������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_wakeup_pin_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_WPE;
}

/**
 *  \brief ʹ�ܻ�������
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_wakeup_pin_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr &= (~AMHW_FSL_RTC_WPE);
}

/**
 *  \brief �����λRTCģ��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_soft_reset (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_SWR;
}

/**
 *  \brief ��������λλ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_soft_rstbit_clear (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->cr |= AMHW_FSL_RTC_SWR;
}

/**
 *  \brief ʱ�������״̬ʹ��λ��ȡ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \retval 0 û��ʹ��
 *  \retval AMHW_FSL_RTC_TCE �Ѿ�ʹ��
 */
am_static_inline
uint32_t amhw_fsl_rtc_time_counter_status_get (amhw_fsl_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->sr & AMHW_FSL_RTC_TCE);
}

/**
 *  \brief ��1������״̬ʹ��λ,��ʹ�ܼ�����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_time_counter_status_set (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->sr |= AMHW_FSL_RTC_TCE;
}

/**
 *  \brief ��0������״̬ʹ��λ�������ܼ�����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_time_counter_status_clr (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->sr &= ~AMHW_FSL_RTC_TCE;
}

/**
 *  \brief ����״̬��ȡ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \retval 0 ����û�з�����
 *  \retval AMHW_FSL_RTC_TAF ���ӷ�����
 */
am_static_inline
uint32_t amhw_fsl_rtc_alarm_status_get (amhw_fsl_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->sr & AMHW_FSL_RTC_TAF);
}

/**
 *  \brief ����������״̬��ȡ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \retval 0 û�����
 *  \retval AMHW_FSL_RTC_TOF ���������
 */
am_static_inline
uint32_t amhw_fsl_rtc_count_over_status_get (amhw_fsl_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->sr & AMHW_FSL_RTC_TOF);
}

/**
 *  \brief RTC ģ���Ƿ�Ϊ��Ч״̬��ȡ
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \retval 0 ģ����Ч
 *  \retval AMHW_FSL_RTC_TIF ģ����Ч
 */
am_static_inline
uint32_t amhw_fsl_rtc_is_time_invalid (amhw_fsl_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->sr & AMHW_FSL_RTC_TIF);
}

/**
 *  \brief �������Ĵ���(LR)����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_lock_reg_lock (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->lr &= ~AMHW_FSL_RTC_LRL;
}

/**
 *  \brief �Կ��ƼĴ���(CR)����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_control_reg_lock (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->lr &= ~AMHW_FSL_RTC_CRL;
}

/**
 *  \brief ��״̬�Ĵ���(SR)����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_status_reg_lock (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->lr &= ~AMHW_FSL_RTC_SRL;
}

/**
 *  \brief ��У׼�Ĵ���(TCR)����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_compensate_reg_lock (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->lr &= ~AMHW_FSL_RTC_TCL;
}

/**
 *  \brief ����������Ĵ���(LR)����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_lock_reg_unlock (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->lr |= AMHW_FSL_RTC_LRL;
}

/**
 *  \brief ����Կ��ƼĴ���(CR)����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_control_reg_unlock (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->lr |= AMHW_FSL_RTC_CRL;
}

/**
 *  \brief �����״̬�Ĵ���(SR)����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_status_reg_unlock (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->lr |= AMHW_FSL_RTC_SRL;
}

/**
 *  \brief �����У׼�Ĵ���(TCR)����
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_compensate_reg_unlock (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->lr |= AMHW_FSL_RTC_TCL;
}

/**
 *  \brief ��������ʹ��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_wakeup_pin_on (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier |= AMHW_FSL_RTC_WPON;
}

/**
 *  \brief ���ж�ʹ��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_sec_int_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier |= AMHW_FSL_RTC_TSIE;
}

/**
 *  \brief �����ж�ʹ��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_alarm_int_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier |= AMHW_FSL_RTC_TAIE;
}

/**
 *  \brief ����ж�ʹ��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_overflow_int_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier |= AMHW_FSL_RTC_TOIE;
}

/**
 *  \brief ģ���ж���Чʹ��
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_invalid_int_enable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier |= AMHW_FSL_RTC_TIIE;
}

/**
 *  \brief �������ų���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_wakeup_pin_off (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier &= ~AMHW_FSL_RTC_WPON;
}

/**
 *  \brief ���жϳ���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_sec_int_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier &= ~AMHW_FSL_RTC_TSIE;
}

/**
 *  \brief �����жϳ���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_alarm_int_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier &= ~AMHW_FSL_RTC_TAIE;
}

/**
 *  \brief ����жϳ���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_overflow_int_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier &= ~AMHW_FSL_RTC_TOIE;
}

/**
 *  \brief ģ����Ч�жϳ���
 *
 *  \param p_hw_rtc ָ��RTC�Ĵ������ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_rtc_invalid_int_disable (amhw_fsl_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ier &= ~AMHW_FSL_RTC_TIIE;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AMHW_FSL_RTC_H */
