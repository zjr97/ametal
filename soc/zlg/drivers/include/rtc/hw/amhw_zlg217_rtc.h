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
 * \brief RTC interfaces for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.01 18-06-15  pea, fix bug
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG217_RTC_H
#define __AMHW_ZLG217_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_common.h"

/**
 * \addtogroup amhw_zlg217_if_rtc
 * \copydoc amhw_zlg217_rtc.h
 * @{
 */

/**
 * \brief RTC �Ĵ����ṹ�嶨��
 */
typedef struct amhw_zlg217_rtc {
    __IO uint16_t crh;         /**< \brief RTC ���ƼĴ�����λ */
    __I  uint16_t reserve0;    /**< \brief ����λ */
    __IO uint16_t crl;         /**< \brief RTC ���ƼĴ�����λ */
    __I  uint16_t reserve1;    /**< \brief ����λ */
    __IO uint16_t prlh;        /**< \brief RTC Ԥ��Ƶװ�ؼĴ�����λ */
    __I  uint16_t reserve2;    /**< \brief ����λ */
    __IO uint16_t prll;        /**< \brief RTC Ԥ��Ƶװ�ؼĴ�����λ */
    __I  uint16_t reserve3;    /**< \brief ����λ */
    __IO uint16_t divh;        /**< \brief RTC Ԥ��Ƶ����Ƶ���ӼĴ�����λ */
    __I  uint16_t reserve4;    /**< \brief ����λ */
    __IO uint16_t divl;        /**< \brief RTC Ԥ��Ƶ����Ƶ���ӼĴ�����λ */
    __I  uint16_t reserve5;    /**< \brief ����λ */
    __IO uint16_t cnth;        /**< \brief RTC �������Ĵ�����λ */
    __I  uint16_t reserve6;    /**< \brief ����λ */
    __IO uint16_t cntl;        /**< \brief RTC �������Ĵ�����λ */
    __I  uint16_t reserve7;    /**< \brief ����λ */
    __IO uint16_t alrh;        /**< \brief RTC ���ӼĴ�����λ */
    __I  uint16_t reserve8;    /**< \brief ����λ */
    __IO uint16_t alrl;        /**< \brief RTC ���ӼĴ�����λ */
    __I  uint16_t reserve9;    /**< \brief ����λ */
} amhw_zlg217_rtc_t;

/**
 * \brief RTC ���ƼĴ�����λ�ж�����ö��
 */
typedef enum {
    AMHW_ZLG217_RTC_SECIE = 0,
    AMHW_ZLG217_RTC_ALRIE = 1,
    AMHW_ZLG217_RTC_OWIE  = 2,
} amhw_zlg217_rtc_crh_int_permit;

/**
 * \brief RTC ���ƼĴ�����λ״̬��־ö��
 */
typedef enum {
    AMHW_ZLG217_RTC_SECF  = 0,
    AMHW_ZLG217_RTC_ALRF  = 1,
    AMHW_ZLG217_RTC_OWF   = 2,
    AMHW_ZLG217_RTC_RSF   = 3,
    AMHW_ZLG217_RTC_RTOFF = 5,
} amhw_zlg217_rtc_crl_status;

/**
 * \brief �ж�������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] permit   RTC ���ƼĴ�����λ�ж�����ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_crh_allow_int (amhw_zlg217_rtc_t              *p_hw_rtc,
                                    amhw_zlg217_rtc_crh_int_permit  permit)
{
    p_hw_rtc->crh |= (1 << permit);
}

/**
 * \brief �жϽ�ֹ����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] permit   RTC ���ƼĴ�����λ�ж�����ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_crh_forbid_int (amhw_zlg217_rtc_t              *p_hw_rtc,
                                     amhw_zlg217_rtc_crh_int_permit  permit)
{
    p_hw_rtc->crh &= ~(1 << permit);
}

/**
 * \brief �����ƼĴ�����λ״̬λ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] status    RTC ���ƼĴ�����λ״̬��־ö��
 *
 * \retval AM_TRUE  ��־λ��λ
 * \retval AM_FALSE ��־λδ��λ
 */
am_static_inline
am_bool_t amhw_zlg217_rtc_crl_read_statu (amhw_zlg217_rtc_t          *p_hw_rtc,
                                          amhw_zlg217_rtc_crl_status  status)
{
    return (am_bool_t)((p_hw_rtc->crl & (1ul << status)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ���ƼĴ�����λ״̬λ���
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] status   RTC ���ƼĴ�����λ״̬��־ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_clr_status_clear (amhw_zlg217_rtc_t          *p_hw_rtc,
                                       amhw_zlg217_rtc_crl_status  status)
{
    p_hw_rtc->crl &= ~(1 << status);
}

/**
 * \brief ���� RTC ����ģʽ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_crl_cnf_enter (amhw_zlg217_rtc_t *p_hw_rtc)
{
    p_hw_rtc->crl |= (1 << 4);
}

/**
 * \brief �˳� RTC ����ģʽ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_crl_cnf_out (amhw_zlg217_rtc_t *p_hw_rtc)
{
    p_hw_rtc->crl &= ~(1 << 4);
}

/**
 * \brief RTC Ԥ��Ƶװ�ؼĴ�����λд����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] divh     Ԥ��Ƶ��λ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_prlh_div_write (amhw_zlg217_rtc_t *p_hw_rtc, uint16_t divh)
{
    p_hw_rtc->prlh = (divh & 0x000F);
}

/**
 * \brief RTC Ԥ��Ƶװ�ؼĴ�����λд����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] divl     Ԥ��Ƶ��λ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_prll_div_write (amhw_zlg217_rtc_t *p_hw_rtc, uint16_t divl)
{
    p_hw_rtc->prll = divl;
}

/**
 * \brief RTC Ԥ��Ƶװ�ؼĴ�����λ������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 *
 * \return RTC Ԥ��Ƶ�Ĵ�����λ״ֵ̬
 */
am_static_inline
uint16_t amhw_zlg217_rtc_divh_div_read (amhw_zlg217_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->divh;
}

/**
 * \brief RTC Ԥ��Ƶװ�ؼĴ�����λ������
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 *
 * \return RTC Ԥ��Ƶ�Ĵ�����λ״ֵ̬
 */
am_static_inline
uint16_t amhw_zlg217_rtc_divl_div_read (amhw_zlg217_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->divl;
}

/**
 * \brief RTC �������Ĵ�����λ���ú���
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] cnth     ��������λ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_cnth_set (amhw_zlg217_rtc_t *p_hw_rtc, uint16_t cnth)
{
    p_hw_rtc->cnth = cnth;
}

/**
 * \brief RTC �������Ĵ�����λ���ú���
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] cntl     ��������λ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_cntl_set (amhw_zlg217_rtc_t *p_hw_rtc, uint16_t cntl)
{
    p_hw_rtc->cntl = cntl;
}

/**
 * \brief ��ȡ RTC �������Ĵ�����λ����ֵ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 *
 * \return ��������λ��ֵ
 */
am_static_inline
uint16_t amhw_zlg217_rtc_cnth_get (amhw_zlg217_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->cnth;
}

/**
 * \brief ��ȡ RTC �������Ĵ�����λ����ֵ
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 *
 * \return �Ĵ�����λ��ֵ
 */
am_static_inline
uint16_t amhw_zlg217_rtc_cntl_get (amhw_zlg217_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->cntl;
}

/**
 * \brief RTC ���ӼĴ�����λд����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] alarmh   ���ӼĴ�����λ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_alrh_set (amhw_zlg217_rtc_t *p_hw_rtc, uint16_t alarmh)
{
    p_hw_rtc->alrh = alarmh;
}

/**
 * \brief RTC ���ӼĴ�����λд����
 *
 * \param[in] p_hw_rtc ָ�� amhw_zlg217_rtc_t �ṹ��ָ��
 * \param[in] alarml   ���ӼĴ�����λ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rtc_alrl_set (amhw_zlg217_rtc_t *p_hw_rtc, uint16_t alarml)
{
    p_hw_rtc->alrl = alarml;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZLG217_RTC_H */

/* end of file */
