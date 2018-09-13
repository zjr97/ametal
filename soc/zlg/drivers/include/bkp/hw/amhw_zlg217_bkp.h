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
 * \brief ���ݼĴ����ӿ�
 *
 * \internal
 * \par History
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG217_BKP_H
#define __AMHW_ZLG217_BKP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_common.h"

/**
 * \addtogroup amhw_zlg217_if_bkp
 * \copydoc amhw_zlg217_bkp.h
 * @{
 */

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif
/**
 * @}
 */

/** \brief BKP_RTCCR register bit mask */
#define  AMHW_ZLG217_BKP_RTCCR_CAL_SET  (0x007F) /**< Calibration value */
#define  AMHW_ZLG217_BKP_RTCCR_CCO_SET  (0x0080) /**< Calibration Clock Output */
#define  AMHW_ZLG217_BKP_RTCCR_ASOE_SET (0x0100) /**< Alarm or Second Output Enable */
#define  AMHW_ZLG217_BKP_RTCCR_ASOS_SET (0x0200) /**< Alarm or Second Output Selection */

/** \brief BKP_CR register bit mask */
#define  AMHW_ZLG217_BKP_CR_TPE_SET     (0x01)   /**< TAMPER pin enable */
#define  AMHW_ZLG217_BKP_CR_TPAL_SET    (0x02)   /**< TAMPER pin active level */

/** \brief CSR register bit mask */
#define  AMHW_ZLG217_BKP_CSR_CTE_SET    (0x0001) /**< Clear Tamper event */
#define  AMHW_ZLG217_BKP_CSR_CTI_SET    (0x0002) /**< Clear Tamper Interrupt */
#define  AMHW_ZLG217_BKP_CSR_TPIE_SET   (0x0004) /**< TAMPER Pin interrupt enable */
#define  AMHW_ZLG217_BKP_CSR_TEF_SET    (0x0100) /**< Tamper Event Flag */
#define  AMHW_ZLG217_BKP_CSR_TIF_SET    (0x0200) /**< Tamper Interrupt Flag */

/**
  * \brief ���ݼĴ�����ṹ��
  */
typedef struct amhw_zlg217_bkp {
    __I  uint32_t reserve0;  /**< \brief ���� */
    __IO uint32_t dr[10];    /**< \brief �����������ݼĴ��� */
    __IO uint16_t rtc_cr;    /**< \brief RTC ���ƼĴ��� */
    __I  uint16_t reserve1;  /**< \brief ���� */
    __IO uint16_t cr;        /**< \brief BKP ���ƼĴ��� */
    __I  uint16_t reserve2;  /**< \brief ���� */
    __IO uint16_t csr;       /**< \brief ʱ�Ӽ��״̬�Ĵ��� */
} amhw_zlg217_bkp_t;

/**
 * \brief Clears Tamper Pin Event pending flag.
 *
 * \param[in] p_hw_bkp Pointer to amhw_zlg217_bkp_t Structure
 * \param[in] flag     see AMHW_BKP_CSR_CTE_SET or AMHW_BKP_CSR_CTI_SET
 *
 * \return None
 */
am_static_inline
void amhw_zlg217_bkp_clear_flag (amhw_zlg217_bkp_t *p_hw_bkp, uint16_t flag)
{

    /* Set CTE bit to clear Tamper Pin Event flag */
    p_hw_bkp->csr |= flag;
}

/**
 * \brief д�����������ݼĴ���
 *
 * \param[in] index    �����������ݼĴ���������ֵΪ 0 ~ 9
 * \param[in] value    д�뱸���������ݼĴ�����ֵ��ֵΪ 0 ~ 65536
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_bkp_dr_write (amhw_zlg217_bkp_t *p_hw_bkp,
                               uint8_t            index,
                               uint16_t           value)
{
    p_hw_bkp->dr[index] = value & 0x0000FFFF;
}

/**
 * \brief �������������ݼĴ���
 *
 * \param[in] index    �����������ݼĴ���������ֵΪ 0 ~ 9
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ���ض�Ӧ���ݼĴ�����ֵ
 */
am_static_inline
uint16_t amhw_zlg217_bkp_dr_read (amhw_zlg217_bkp_t *p_hw_bkp, uint8_t index)
{
    return p_hw_bkp->dr[index] & 0x0000FFFF;
}

/**
 * \brief RTC ʱ��У׼����
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 * \param[in] index    У׼ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_bkp_rtccr_cal_set (amhw_zlg217_bkp_t *p_hw_bkp, uint8_t cal)
{
    p_hw_bkp->rtc_cr = ((p_hw_bkp->rtc_cr & (~AMHW_ZLG217_BKP_RTCCR_CAL_SET)) |
                        (cal & AMHW_ZLG217_BKP_RTCCR_CAL_SET));
}

/**
 * \brief RTC ʱ��У׼��ȡ
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ���ض�Ӧ���ݼĴ�����ֵ
 */
am_static_inline
uint8_t amhw_zlg217_bkp_rtccr_cal_get (amhw_zlg217_bkp_t *p_hw_bkp)
{
    return (uint8_t)(p_hw_bkp->rtc_cr & AMHW_ZLG217_BKP_RTCCR_CAL_SET);
}

/**
 * \brief RTC ʱ��У׼���ʹ��
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_bkp_rtccr_cco_enable (amhw_zlg217_bkp_t *p_hw_bkp)
{
    p_hw_bkp->rtc_cr |= AMHW_ZLG217_BKP_RTCCR_CCO_SET;
}

/**
 * \brief RTC ʱ��У׼���ʧ��
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_bkp_rtccr_cco_disable (amhw_zlg217_bkp_t *p_hw_bkp)
{
    p_hw_bkp->rtc_cr &= ~AMHW_ZLG217_BKP_RTCCR_CCO_SET;
}

/**
 * \brief RTC ʱ��У׼�����ȡ
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ���ض�Ӧ���ݼĴ�����ֵ
 */
am_static_inline
am_bool_t amhw_zlg217_bkp_rtccr_cco_get (amhw_zlg217_bkp_t *p_hw_bkp)
{
    return (p_hw_bkp->rtc_cr & AMHW_ZLG217_BKP_RTCCR_CCO_SET) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief RTC ����������ӻ�������ʹ��
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_bkp_rtccr_asoe_enable (amhw_zlg217_bkp_t *p_hw_bkp)
{
    p_hw_bkp->rtc_cr |= AMHW_ZLG217_BKP_RTCCR_ASOE_SET;
}

/**
 * \brief RTC ����������ӻ�������ʧ��
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_bkp_rtccr_asoe_disable (amhw_zlg217_bkp_t *p_hw_bkp)
{
    p_hw_bkp->rtc_cr &= ~AMHW_ZLG217_BKP_RTCCR_ASOE_SET;
}

/**
 * \brief RTC ����������ӻ��������ȡ
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ���ض�Ӧ���ݼĴ�����ֵ
 */
am_static_inline
am_bool_t amhw_zlg217_bkp_rtccr_asoe_get (amhw_zlg217_bkp_t *p_hw_bkp)
{
    return (p_hw_bkp->rtc_cr & AMHW_ZLG217_BKP_RTCCR_ASOE_SET) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief RTC ���������
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_bkp_rtccr_asos_second (amhw_zlg217_bkp_t *p_hw_bkp)
{
    p_hw_bkp->rtc_cr |= AMHW_ZLG217_BKP_RTCCR_ASOS_SET;
}

/**
 * \brief RTC �����������
 *
 * \param[in] p_hw_bkp ָ��ϵͳ���üĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_bkp_rtccr_asos_alarm (amhw_zlg217_bkp_t *p_hw_bkp)
{
    p_hw_bkp->rtc_cr &= ~AMHW_ZLG217_BKP_RTCCR_ASOS_SET;
}

/**
 * \brief ʹ������������ν���
 * @{
 */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

  /* ��������������ʹ�� */
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif
/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG_BKP_H */

/* end of file */
