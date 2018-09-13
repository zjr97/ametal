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
 * \brief ���������������HC595������λ��GPIO����
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_SCAN_HC595_GPIO_H
#define __AM_DIGITRON_SCAN_HC595_GPIO_H

#include "ametal.h"
#include "am_digitron_scan.h"
#include "am_digitron_seg_hc595.h"
#include "am_digitron_com_gpio.h"
#include "am_hc595.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_digitron_scan_hc595_gpio
 * \copydoc am_digitron_scan_hc595_gpio.h
 * @{
 */

/**
 * \brief ��̬ɨ�����������Ϣ������HC595������λ��GPIO������
 */
typedef struct am_digitron_scan_hc595_gpio_info {

    am_digitron_scan_devinfo_t scan_info;  /**< \brief ����ܶ�̬ɨ�������Ϣ */
    am_digitron_base_info_t    base_info;  /**< \brief ����ܻ�����Ϣ  */
    const int                 *p_com_pins; /**< \brief λѡ GPIO���� ��Ϣ */

} am_digitron_scan_hc595_gpio_info_t;

/**
 * \brief ��̬ɨ����������豸������HC595������λ��GPIO������
 */
typedef struct am_digitron_scan_hc595_gpio_dev {
    am_digitron_scan_dev_t           scan_dev;
    am_digitron_scan_ops_separate_t  scan_ops;
    am_digitron_seg_hc595_dev_t      seg_dev;
    am_digitron_com_gpio_dev_t       com_dev;
} am_digitron_scan_hc595_gpio_dev_t;

/**
 * \brief ��̬ɨ��������ܳ�ʼ��
 *
 * \param[in] p_dev  : �豸ʵ��
 * \param[in] p_info : �豸ʵ����Ϣ
 * \param[in] handle : ��׼��HC595������ 
 *
 * \retval AM_OK      : ��ʼ���ɹ�
 * \retval -AM_EINVAL ����ʼ��ʧ�ܣ��������ڴ���
 */
int am_digitron_scan_hc595_gpio_init (
    am_digitron_scan_hc595_gpio_dev_t        *p_dev,
    const am_digitron_scan_hc595_gpio_info_t *p_info,
    am_hc595_handle_t                         handle);

/**
 * \brief ���������ɨ��ص���������������һ����
 *
 *     ��һ���µ������λ��ʼɨ��ʱ������øûص�����
 *
 * \param[in] p_dev  : �豸ʵ��
 * \param[in] pfn_cb : �ص�����
 * \param[in] p_arg  : �ص������û�����
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL ������ʧ�ܣ��������ڴ���
 */
int am_digitron_scan_hc595_gpio_cb_set (am_digitron_scan_hc595_gpio_dev_t *p_dev,
                                        am_digitron_scan_cb_t              pfn_cb,
                                        void                              *p_arg);

/**
 * \brief ��̬ɨ��������ܽ��ʼ��
 *
 * \param[in] p_dev   : �豸ʵ��
 *
 * \retval AM_OK      : ���ʼ���ɹ�
 * \retval -AM_EINVAL �����ʼ��ʧ�ܣ��������ڴ���
 */
int am_digitron_scan_hc595_gpio_deinit (am_digitron_scan_hc595_gpio_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_SCAN_HC595_GPIO_H */

/* end of file */
