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
 * \brief GPIO������LED
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_LED_GPIO_H
#define __AM_LED_GPIO_H

#include "ametal.h"
#include "am_led_dev.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_led_gpio
 * \copydoc am_led_gpio.h
 * @{
 */

/**
 * \brief LED��Ϣ��GPIO������
 */
typedef struct am_led_gpio_info {

    /** \brief LED����������Ϣ ��������ʼ��źͽ������     */
    am_led_servinfo_t  serv_info;

    /** \brief ʹ�õ�GPIO���ţ�������ĿӦ��Ϊ ��������� - ��ʼ��� + 1��   */
    const int         *p_pins;

    /** \brief LED�Ƿ��ǵ͵�ƽ����  */
    am_bool_t          active_low;

} am_led_gpio_info_t;

/**
 * \brief LED�豸��GPIO������
 */
typedef struct am_led_gpio_dev {
    am_led_dev_t               isa;
    const am_led_gpio_info_t  *p_info;
} am_led_gpio_dev_t;

/**
 * \brief LED�豸��ʼ����GPIO������
 *
 * \param[in] p_dev  : LED�豸
 * \param[in] p_info : LED�豸��Ϣ
 *
 * \retval AM_OK      : ��ʼ���ɹ�
 * \retval -AM_EINVAL : ��ʼ��ʧ��
 */
int am_led_gpio_init (am_led_gpio_dev_t         *p_dev,
                      const am_led_gpio_info_t  *p_info);

/**
 * \brief LED�豸���ʼ����GPIO������
 *
 * \param[in] p_dev  : LED�豸
 *
 * \retval AM_OK      : ���ʼ���ɹ�
 * \retval -AM_EINVAL : ���ʼ��ʧ��
 */
int am_led_gpio_deinit (am_led_gpio_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LED_GPIO_H */

/* end of file */
