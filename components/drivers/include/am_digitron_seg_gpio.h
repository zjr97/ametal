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
 * \brief ����������GPIO��
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_SEG_GPIO_H
#define __AM_DIGITRON_SEG_GPIO_H

#include "ametal.h"
#include "am_digitron_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name am_if_digitron_seg_gpio
 * @{
 */

/**
 * \brief GPIO�����豸
 */
typedef struct am_digitron_seg_gpio {
    am_digitron_base_sender_seg_t      sender;
    const am_digitron_base_info_t     *p_info;
    const int                         *p_pins;
    int                                pin_num;
} am_digitron_seg_gpio_dev_t;


/**
 * \brief GPIO���뷢������ʼ��
 *
 * \param[in] p_dev  : GPIO���뷢�����豸ʵ��
 * \param[in] p_info : ����ܻ�����Ϣ
 * \param[in] p_pins : ���ű�0�����Ŷ�Ӧ��Ч��������λ���� ��a' �Σ� �Դ�����
 *                     ������ĿӦ���뵥��ɨ�������ܸ����Ķ����ܺ����
 *
 * \return ��׼�Ķ��뷢�������ɹ������ɨ����ʹ�ã�
 */
am_digitron_base_sender_seg_t *am_digitron_seg_gpio_init (
        am_digitron_seg_gpio_dev_t     *p_dev,
        const am_digitron_base_info_t  *p_info,
        const int                      *p_pins);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_SEG_GPIO_H */

/* end of file */
