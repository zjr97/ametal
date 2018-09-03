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
 * \brief RTC drivers for standard interface
 *
 * \internal
 * \par Modification history
 * - 1.01 18-06-19  pea, add some APIs
 * - 1.00 17-08-28  lqy, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG217_RTC_H
#define __AM_ZLG217_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_rtc.h"
#include "amhw_zlg217_rtc.h"

/**
 * \addtogroup am_zlg217_if_rtc
 * \copydoc am_zlg217_rtc.h
 * @{
 */

#define  AM_ZLG217_RTC_CALLBACK_SECOND  (1 << 0)  /**< \brief RTC ���жϻص�������� */
#define  AM_ZLG217_RTC_CALLBACK_ALARM   (1 << 1)  /**< \brief RTC �����жϻص�������� */
#define  AM_ZLG217_RTC_CALLBACK_OVER    (1 << 2)  /**< \brief RTC ����жϻص�������� */

/**
 * \brief ZLG217 RTC �豸��Ϣ
 */
typedef struct am_zlg217_rtc_devinfo {
    uint32_t rtc_regbase;            /**< \brief RTC �Ĵ�������ַ */
    uint32_t pwr_regbase;            /**< \brief PWR �Ĵ�������ַ */
    uint32_t bkp_regbase;            /**< \brief BKP �Ĵ�������ַ */
    uint32_t rtc_clk_sour;           /**< \brief RTC ʱ��Դ */
    int      rtc_inum;               /**< \brief RTC �жϺ� */
    void   (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������ */
    void   (*pfn_plfm_deinit)(void); /**< \brief ƽ̨���ʼ������ */
} am_zlg217_rtc_devinfo_t;

/**
 * \brief ZLG217 RTC �豸
 */
typedef struct am_zlg217_rtc_dev {
    am_rtc_serv_t                  rtc_serv;        /**< \brief RTC ��׼���� */
    uint8_t                        int_state;       /**< \brief �ж�ʹ�ܱ�־ */
    am_bool_t                      rtc_continue;    /**< \brief RTC �Ƿ�������� */
    am_pfnvoid_t                   pfn_callback[3]; /**< \brief �ص����� */
    void                          *p_arg[3];        /**< \brief �ص��������� */
    const am_zlg217_rtc_devinfo_t *p_devinfo;       /**< \brief RTC �豸��Ϣ */
}am_zlg217_rtc_dev_t;

/**
 * \brief RTC ״̬��ȡ�����������жϱ�������ǰ���������Ƿ�ϵ�
 *
 * \param[in] handle RTC ��׼����������
 *
 * \retval AM_TRUE  ��������δ�ϵ磬RTC ������������һ�ε�״̬����
 * \retval AM_FALSE ��������ϵ磬RTC �������� 0 ��ʼ����
 */
am_bool_t am_zlg217_rtc_state_get (am_rtc_handle_t handle);

/**
 * \brief RTC ͬ����־��λ���� APB1 ��������ֹ������Ҫ���ô˽ӿ�
 *
 * \param[in] handle RTC ��׼����������
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 *
 * \note ����ϵͳ��λ���Դ��λ��ϵͳ�մӴ���ģʽ���ѡ�
 *       ϵͳ�մ�ͣ��ģʽ����ʱ��Ӧ�õ��ô˽ӿ�
 */
am_err_t am_zlg217_rtc_apb1_reflush (am_rtc_handle_t handle);

/**
 * \brief ��ȡ RTC ������ֵ
 *
 * \param[in]  handle RTC ��׼����������
 * \param[out] p_cnt  ָ��洢��ȡ���� RTC ������ֵ��ָ��
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zlg217_rtc_cnt_get (am_rtc_handle_t handle, uint32_t *p_cnt);

/**
 * \brief ���� RTC ������ֵ
 *
 * \param[in] handle RTC ��׼����������
 * \param[in] cnt    RTC ������ֵ
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zlg217_rtc_cnt_set (am_rtc_handle_t handle, uint32_t cnt);

/**
 * \brief ���� RTC ����ֵ
 *
 * \param[in] handle RTC ��׼����������
 * \param[in] alr    RTC ����ֵ
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zlg217_rtc_alr_set (am_rtc_handle_t handle, uint32_t alr);

/**
 * \brief ���� RTC ����ʱ��
 *
 * \param[in] handle RTC ��׼����������
 * \param[in] p_tm   ��Ҫ���õ�ʱ��
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zlg217_rtc_alarm_set (am_rtc_handle_t handle, am_tm_t *p_tm);

/**
 * \brief ���� RTC �жϻص�
 *
 * \param[in] handle       RTC ��׼����������
 * \param[in] type         �ж����ͣ���ѡ AM_ZLG217_RTC_CALLBACK_SECOND
 *                                       AM_ZLG217_RTC_CALLBACK_ALARM
 *                                       AM_ZLG217_RTC_CALLBACK_OVER
 * \param[in] pfn_callback �ص�����
 * \param[in] p_arg        �ص���������
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zlg217_rtc_callback_set (am_rtc_handle_t handle,
                                     uint8_t         type,
                                     am_pfnvoid_t    pfn_callback,
                                     void           *p_arg);

/**
 * \brief RTC �ж�ʹ��
 *
 * \param[in] handle RTC ��׼����������
 * \param[in] type   �ж����ͣ���ѡ AM_ZLG217_RTC_CALLBACK_SECOND
 *                                 AM_ZLG217_RTC_CALLBACK_ALARM
 *                                 AM_ZLG217_RTC_CALLBACK_OVER
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zlg217_rtc_int_enable (am_rtc_handle_t handle,
                                   uint8_t         type);

/**
 * \brief RTC �ж�ʧ��
 *
 * \param[in] handle RTC ��׼����������
 * \param[in] type   �ж����ͣ���ѡ AM_ZLG217_RTC_CALLBACK_SECOND
 *                                 AM_ZLG217_RTC_CALLBACK_ALARM
 *                                 AM_ZLG217_RTC_CALLBACK_OVER
 *
 * \retval  AM_OK     �ɹ�
 * \retval -AM_EINVAL ��������
 */
am_err_t am_zlg217_rtc_int_disable (am_rtc_handle_t handle,
                                    uint8_t         type);
/**
 * \brief ��ʼ�� RTC
 *
 * \param[in] p_dev     ָ�� RTC �豸��ָ��
 * \param[in] p_devinfo ָ�� RTC �豸��Ϣ��ָ��
 *
 * \return RTC ��׼���������������Ϊ NULL��������ʼ��ʧ��
 */
am_rtc_handle_t am_zlg217_rtc_init (am_zlg217_rtc_dev_t           *p_dev,
                                    const am_zlg217_rtc_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ�� RTC
 *
 * \param[in] handle ʹ�� am_zlg217_rtc_init() ��ȡ���� RTC ��׼����������
 *
 * \return ��
 */
void am_zlg217_rtc_deinit (am_rtc_handle_t handle);

/** @} */

/**
 * @} zlg_if_rtc
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZLG217_RTC_H */

/* end of file */
