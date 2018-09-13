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
 * \brief �������GPIO��ֵ��ȡ
 *
 * \internal
 * \par modification history:
 * - 15-09-15 tee, first implementation.
 * \endinternal
 */

#ifndef __AM_KEY_MATRIX_READ_GPIO_H
#define __AM_KEY_MATRIX_READ_GPIO_H

#include "ametal.h"
#include "am_types.h"
#include "am_key_matrix.h"
#include "am_key_matrix_base.h"

/**
 * \addtogroup am_if_key_matrix_read_gpio
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** \brief ������̼�ֵ��ȡ�豸  */
typedef struct am_key_matrix_read_gpio {
    am_key_matrix_read_t             isa;
    const am_key_matrix_base_info_t *p_info;
    const int                       *p_pins;
    int                              pin_num;
} am_key_matrix_read_gpio_t;

/**
 * \brief ������̼�ֵ��ȡ�豸��ʼ����GPIO��
 *
 * \param[in] p_dev      : �����豸ʵ��
 * \param[in] p_info     : ������Ϣ
 * \param[in] p_pins     :  GPIO�����б����ڶ�ȡһ��ɨ���µ����а����ļ�ֵ
 *                          - ��������ɨ�裬��������Ӧ�����������
 *                          - ��������ɨ�裬��������Ӧ�����������
 *
 * \return ͨ�õľ�����̼�ֵ��ȡ
 */
am_key_matrix_read_t * am_key_matrix_read_gpio_init (
    am_key_matrix_read_gpio_t       *p_dev,
    const am_key_matrix_base_info_t *p_info,
    const int                       *p_pins);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AM_KEY_MATRIX_READ_GPIO_H */

/* end of file */
