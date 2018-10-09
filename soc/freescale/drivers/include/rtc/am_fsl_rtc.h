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
 * \brief RTC ģ���������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_RTC_H
#define __AM_FSL_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "am_rtc.h"
#include "hw/amhw_fsl_rtc.h"

/**
 * \addtogroup am_fsl_if_rtc
 * \copydoc am_fsl_rtc.h
 * @{
 */

/**
 * \brief RTC �豸��Ϣ�ṹ��
 */
typedef struct am_fsl_rtc_devinfo {
    amhw_fsl_rtc_t  *p_hw_rtc;      /**< \brief ָ��RTC�Ĵ�����Ľṹ��ָ�� */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_rtc_devinfo_t;

/**
 * \brief RTC �豸�ṹ��
 */
typedef struct am_fsl_rtc_dev {
    am_rtc_serv_t               rtc_serv;     /**< \brief RTC��׼����           */
    const am_fsl_rtc_devinfo_t *p_devinfo;    /**< \brief ָ��RTC�豸��Ϣ��ָ�� */
} am_fsl_rtc_dev_t;

/**
 * \brief ��ʼ��RTC
 *
 * \param[in] p_dev     : ָ��RTC�豸
 * \param[in] p_devinfo : ָ��RTC�豸��Ϣ
 *
 * \return RTC��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_rtc_handle_t am_fsl_rtc_init (am_fsl_rtc_dev_t           *p_dev,
                                 const am_fsl_rtc_devinfo_t *p_devinfo);

/**
 *  \brief ���RTC��ʼ��
 *
 * \param[in] handle : am_fsl_rtc_init() ��ʼ��������õ�RTC������
 *
 *  \return ��
 */
void am_fsl_rtc_deinit (am_rtc_handle_t handle);

/**
 *  \brief �������ڼ���һ���еĵڼ���
 *
 *  \param day
 *  \param month
 *  \param year
 *
 *  \return һ���еĵڼ��� (1��1�ռ�Ϊ��0��)
 *
 *  \details �� am_fsl_rtc_date2yday(4, 11, 2015)�������11��4����
 *           2015��ĵ�307��
 */
int am_fsl_rtc_date2yday (uint8_t day, uint8_t month, uint32_t year);


/**
 *  \brief ����RTC��У׼����
 *
 *  \param p_dev ָ��RTC�豸��ָ��
 *
 *  \param frq RTCʱ�ӵ�ʵ��Ƶ�ʣ���Hz��
 *
 *  \return ʵ��У׼���Ƶ��
 */
int am_fsl_rtc_compensation_set (am_fsl_rtc_dev_t *p_dev, float frq);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AM_FSL_RTC_H */

