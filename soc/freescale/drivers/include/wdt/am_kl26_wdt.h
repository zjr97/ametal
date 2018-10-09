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
 * \brief  WDT����������WDT��׼�ӿ�
 *
 * 1. ���Ź������üĴ���ֻ��дһ�Σ�������ʹ��KL26оƬʱ��������Ҫʹ
 *    �ÿ��Ź�����ʱ�����������ļ���Ŀ��Ź����غ���Ϊ0��ϵͳ���ڰ弶��
 *    ʼ��ʱ�رտ��Ź�������Ҫʹ�ÿ��Ź�����ʱ�������Ź����غ���1��ϵͳ��
 *    �ڿ��Ź�ʹ�ܺ��������ÿ��Ź���ʹ֮����������
 * 2. ���Ź�ʹ��LPOʱ��ʱ���䳬ʱʱ��ֻ������Ϊ32ms,256ms,1024ms������ʱ���е�һ����
 *    Ĭ��ʹ��LPOʱ�����롣
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-30  mkr, first implementation.
 * \endinternal
 */

#ifndef __AM_KL26_WDT_H
#define __AM_KL26_WDT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_wdt.h"
#include "hw/amhw_kl26_sim.h"

/**
 * \addtogroup am_kl26_if_wdt
 * \copydoc am_kl26_wdt.h
 * @{
 */

/**
 * \brief WDT �豸��Ϣ�ṹ��
 */
typedef struct am_kl26_wdt_devinfo {

	/** \brief ָ��WDT�Ĵ�����Ľṹ��ָ�� */
    amhw_kl26_sim_t *p_hw_wdt;

    /** \brief ƽ̨��ʼ������ */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_kl26_wdt_devinfo_t;

/**
 * \brief WDT �豸�ṹ��
 */
typedef struct am_kl26_wdt_dev {

    am_wdt_serv_t                 wdt_serv;   /**< \brief WDT��׼����         */
    const am_kl26_wdt_devinfo_t  *p_devinfo;  /**< \brief ָ��WDT�豸��Ϣ��ָ�� */

} am_kl26_wdt_dev_t;

/**
 * \brief ��ʼ��WDT
 *
 * \param[in] p_dev     : ָ��WDT�豸
 * \param[in] p_devinfo : ָ��WDT�豸��Ϣ
 *
 * \return WDT��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_wdt_handle_t am_kl26_wdt_init(am_kl26_wdt_dev_t           *p_dev,
                                 const am_kl26_wdt_devinfo_t *p_devinfo);

/**
 * \brief ���WDT��ʼ��
 * \param[in] handle : WDT�豸���ֵ
 * \return  ��
 */
void am_kl26_wdt_deinit(am_wdt_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_KL26_WDT_H */

/* end of file */
