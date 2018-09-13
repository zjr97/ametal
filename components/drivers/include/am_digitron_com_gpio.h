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
 * \brief λѡ��������GPIO��
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_COM_GPIO_H
#define __AM_DIGITRON_COM_GPIO_H

#include "ametal.h"
#include "am_digitron_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name am_if_digitron_com_gpio
 * @{
 */

/**
 * \brief GPIOλѡ���豸
 */
typedef struct am_digitron_com_gpio {
    am_digitron_base_selector_com_t    selector;
    const am_digitron_base_info_t     *p_info;
    int                                last_com;
    const int                         *p_pins;
    int                                pin_num;
} am_digitron_com_gpio_dev_t;

/**
 * \brief GPIOλѡ����ʼ��
 *
 * \param[in] p_dev  : GPIOλѡ���豸ʵ��
 * \param[in] p_info : ����ܻ�����Ϣ
 * \param[in] p_pins : ���ű�������Ŀ��ɨ�跽ʽ������ܸ������
 *                     - ��ɨ��ʱ����������������ȣ�
 *                     - ��ɨ��ʱ����������������ȡ�
 *
 * \return ��׼��λѡ�����ɹ������ɨ����ʹ�ã�
 */
am_digitron_base_selector_com_t *am_digitron_com_gpio_init (
        am_digitron_com_gpio_dev_t        *p_dev,
        const am_digitron_base_info_t     *p_info,
        const int                         *p_pins);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_COM_GPIO_H */

/* end of file */
