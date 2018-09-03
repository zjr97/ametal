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
 * \brief �������������ӿ�
 *
 * \internal
 * \par modification history:
 * - 15-09-15 tee, first implementation.
 * \endinternal
 */

#ifndef __AM_KEY_GPIO_H
#define __AM_KEY_GPIO_H

#include "ametal.h"
#include "am_types.h"
#include "am_softimer.h"

/**
 * \addtogroup am_if_key_gpio
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ������Ϣ
 */
typedef struct am_key_gpio_info {
    const int  *p_pins;                /**< \brief ʹ�õ����ź�               */
    const int  *p_codes;               /**< \brief ����������Ӧ�ı��루�ϱ��� */
    int         pin_num;               /**< \brief ������Ŀ */
    am_bool_t   active_low;            /**< \brief �Ƿ�͵�ƽ�������Ϊ�͵�ƽ�� */
    int         scan_interval_ms;      /**< \brief ����ɨ��ʱ������һ��10ms */
} am_key_gpio_info_t;

/** \brief �����豸  */
typedef struct am_key_gpio {
    am_softimer_t             timer;
    const am_key_gpio_info_t *p_info;
    uint32_t                  key_prev;
    uint32_t                  key_press;
} am_key_gpio_t;

/**
 * \brief ������ʼ��
 *
 * \param[in] p_dev  : �����豸ʵ��
 * \param[in] p_info : ������Ϣ
 *
 * \return  AM_OK����ʼ���ɹ�; ����ֵ����ʼ��ʧ�ܣ�ʧ��ԭ����鿴�����
 */
int am_key_gpio_init (am_key_gpio_t *p_dev, const am_key_gpio_info_t *p_info);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AM_KEY_GPIO_H */

/* end of file */
