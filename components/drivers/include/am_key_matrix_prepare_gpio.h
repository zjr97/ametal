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
 * \brief ������̻���׼����GPIO��
 *
 * �԰���ɨ��Ϊ����ÿ�ο��Զ�ȡһ�а����ļ�ֵ���ڶ�ȡ֮ǰ����Ҫ�����еĹ�����
 * ����Ϊ�͵�ƽ����ߵ�ƽ�����Ա�����������İ��¡�һ�а����������󣬱���
 * �ָ���ƽ���Ա�����һ�а�����
 *
 * \internal
 * \par modification history:
 * - 15-09-15 tee, first implementation.
 * \endinternal
 */

#ifndef __AM_KEY_MATRIX_PREPARE_GPIO_H
#define __AM_KEY_MATRIX_PREPARE_GPIO_H

#include "ametal.h"
#include "am_types.h"
#include "am_key_matrix.h"
#include "am_key_matrix_base.h"

/**
 * \addtogroup am_if_key_matrix_prepare_gpio
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** \brief ��������豸  */
typedef struct am_key_matrix_prepare_gpio {
    am_key_matrix_prepare_t          isa;
    const am_key_matrix_base_info_t *p_info;
    int                              last_idx;
    const int                       *p_pins;
    int                              pin_num;
} am_key_matrix_prepare_gpio_t;

/**
 * \brief ��ֵ��ȡ�豸��ʼ����GPIO��
 *
 * \param[in] p_dev       : �����豸ʵ��
 * \param[in] p_base_info : ������̻�����Ϣ
 * \param[in] p_pins      : GPIO�����б�
 *                          - ��������ɨ�裬��������Ӧ�����������
 *                          - ��������ɨ�裬��������Ӧ�����������
 * \return ͨ�õľ�������豸
 */
am_key_matrix_prepare_t * am_key_matrix_prepare_gpio_init (
    am_key_matrix_prepare_gpio_t    *p_dev,
    const am_key_matrix_base_info_t *p_info,
    const int                       *p_pins);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AM_KEY_MATRIX_VAL_READ_GPIO_H */

/* end of file */
