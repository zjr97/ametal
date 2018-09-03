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
 * \brief MiniPort-View �� MiniPort-Key ��  MiniPort-595 ����ʹ��
 *
 * �������ʺ����������
 * 1. ����ܶ���ʹ��GPIO����
 * 2. �����λ��ʹ��HC595����
 * 3. ������̲�����ɨ�跽ʽ�������������λѡ�߸���
 * 4. ������̵ļ�ֵ��ȡʹ��GPIO��ȡ����GPIO������ܶ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-12  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_MINIPORT_VIEW_KEY_595_H
#define __AM_DIGITRON_MINIPORT_VIEW_KEY_595_H

#include "ametal.h"
#include "am_digitron_scan_hc595_gpio.h"
#include "am_key_matrix_read_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_miniport_view_key_595
 * @{
 */

/**
 * \brief MiniPort-View + MiniPort-Key + MiniPort-595 ����ʹ�������Ϣ
 */
typedef struct am_miniport_view_key_595_info {
    am_digitron_scan_hc595_gpio_info_t scan_info;  /**< \brief ����ܶ�̬ɨ�������Ϣ */
    am_key_matrix_base_info_t          key_info;   /**< \brief ����������Ϣ */
    const int                         *p_pins_row; /**< \brief �������ţ����߸��ã�  */
} am_miniport_view_key_595_info_t;

/**
 * \brief MiniPort View + MiniPort Key + MiniPort-595 ����ʹ���豸
 */
typedef struct am_miniport_view_key_595_dev {
    am_digitron_scan_hc595_gpio_dev_t      scan_hc595_gpio_dev;
    am_key_matrix_t                        key_dev;
    am_key_matrix_read_gpio_t              read;
    const am_miniport_view_key_595_info_t *p_info;
} am_miniport_view_key_595_dev_t;

/**
 * \brief ��̬ɨ��������ܳ�ʼ��
 *
 * \param[in] p_dev  : ��̬ɨ����������豸ʵ��
 * \param[in] p_info : ��̬ɨ����������豸ʵ����Ϣ
 * \param[in] handle : HC595������
 *
 * \retval AM_OK      : ��ʼ���ɹ�
 * \retval -AM_EINVAL ����ʼ��ʧ�ܣ��������ڴ���
 */
int am_miniport_view_key_595_init (am_miniport_view_key_595_dev_t        *p_dev,
                                   const am_miniport_view_key_595_info_t *p_info,
                                   am_hc595_handle_t                      handle);

/**
 * \brief ��̬ɨ��������ܽ��ʼ��
 *
 * \param[in] p_dev : ��̬ɨ����������豸ʵ��
 *
 * \retval AM_OK      : ���ʼ���ɹ�
 * \retval -AM_EINVAL �����ʼ��ʧ�ܣ��������ڴ���
 */
int am_miniport_view_key_595_deinit (am_miniport_view_key_595_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_MINIPORT_VIEW_KEY_595_H */

/* end of file */
