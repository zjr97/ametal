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
 * \brief GPIO������������ӿڣ���ֵ��ȡͨ��GPIO��ɣ�
 *
 * \internal
 * \par modification history:
 * - 15-09-15 tee, first implementation.
 * \endinternal
 */

#ifndef __AM_KEY_MATRIX_GPIO_H
#define __AM_KEY_MATRIX_GPIO_H

#include "ametal.h"
#include "am_types.h"
#include "am_key_matrix.h"
#include "am_key_matrix_softimer.h"
#include "am_key_matrix_read_gpio.h"
#include "am_key_matrix_prepare_gpio.h"

/**
 * \addtogroup am_if_key_matrix_gpio
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief GPIO�����;��������Ϣ
 */
typedef struct am_key_matrix_gpio_info {
    am_key_matrix_base_info_t base_info;   /**< \brief ������̻�����Ϣ  */
    const int                *p_pins_row;  /**< \brief ��������          */
    const int                *p_pins_col;  /**< \brief ��������          */
} am_key_matrix_gpio_info_t;

/** \brief ��������豸  */
typedef struct am_key_matrix_gpio {
    am_key_matrix_t                  isa;
    am_key_matrix_prepare_gpio_t     prepare;
    am_key_matrix_read_gpio_t        read;
    const am_key_matrix_gpio_info_t *p_info;
} am_key_matrix_gpio_t;

/**
 * \brief ������ʼ��
 *
 * \param[in] p_dev   : �����豸ʵ��
 * \param[in] p_info  : �����豸ʵ����Ϣ
 *
 * \return ͨ�õľ�������豸
 */
am_key_matrix_t * am_key_matrix_gpio_init (
    am_key_matrix_gpio_t            *p_dev,
    const am_key_matrix_gpio_info_t *p_info);
 
/**
 * \brief GPIO�����;��������Ϣ���������ʱ���Զ�ɨ�裩
 */
typedef struct am_key_matrix_gpio_softimer_info {
    am_key_matrix_gpio_info_t key_matrix_gpio_info;
    int                       scan_interval_ms;
} am_key_matrix_gpio_softimer_info_t;

/** \brief ��������豸  */
typedef struct am_key_matrix_gpio_softimer {
    am_key_matrix_softimer_t         isa;
    am_key_matrix_gpio_t             key;
} am_key_matrix_gpio_softimer_t;

/**
 * \brief ������ʼ�����������ʱ���Զ�ɨ�裩
 *
 * \param[in] p_dev  : �����豸ʵ��
 * \param[in] p_info : �����豸ʵ����Ϣ
 *
 * \return AM_OK, ��ʼ���ɹ�������ֵ����ʼ��ʧ��
 */
int am_key_matrix_gpio_softimer_init (
    am_key_matrix_gpio_softimer_t            *p_dev,
    const am_key_matrix_gpio_softimer_info_t *p_info);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AM_KEY_MATRIX_GPIO_H */

/* end of file */
