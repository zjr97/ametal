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
 * \brief HC595������LED
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_LED_HC595_H
#define __AM_LED_HC595_H

#include "ametal.h"
#include "am_led_dev.h"
#include "am_hc595.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_led_hc595
 * \copydoc am_led_hc595.h
 * @{
 */

/**
 * \brief LED��Ϣ��HC595������
 */
typedef struct am_led_hc595_info {

    /** \brief LED����������Ϣ ��������ʼ��źͽ������     */
    am_led_servinfo_t  serv_info;

    /** \brief HC595�ļ�������  */
    int                hc595_num;

    /** \brief ���ݻ��棬��С��HC595�ļ���������ͬ */
    uint8_t           *p_buf;

    /** \brief LED�Ƿ��ǵ͵�ƽ����  */
    am_bool_t          active_low;

} am_led_hc595_info_t;

/**
 * \brief LED�豸��GPIO������
 */
typedef struct am_led_hc595_dev {
    am_led_dev_t                isa;
    am_hc595_handle_t           handle;
    const am_led_hc595_info_t  *p_info;
} am_led_hc595_dev_t;

/**
 * \brief LED�豸��ʼ����HC595������
 *
 * \param[in] p_dev  : LED�豸
 * \param[in] p_info : LED�豸��Ϣ
 * \param[in] handle : HC595���
 *
 * \retval AM_OK      : ��ʼ���ɹ�
 * \retval -AM_EINVAL : ��ʼ��ʧ��
 */
int am_led_hc595_init (am_led_hc595_dev_t         *p_dev,
                       const am_led_hc595_info_t  *p_info,
                       am_hc595_handle_t           handle);

/**
 * \brief LED�豸���ʼ����HC595������
 *
 * \param[in] p_dev  : LED�豸
 *
 * \retval AM_OK      : ���ʼ���ɹ�
 * \retval -AM_EINVAL : ���ʼ��ʧ��
 */
int am_led_hc595_deinit (am_led_hc595_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LED_HC595_H */

/* end of file */
