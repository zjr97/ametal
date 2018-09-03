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
 
#include "am_key_matrix_prepare_gpio.h"
#include "am_gpio.h"

/*******************************************************************************
  Local macro defines
*******************************************************************************/
#define __PREPARE_GPIO_IDX_INVALID  (-1)

/*******************************************************************************
   Local Functions
*******************************************************************************/
static int __key_prepare (void *p_arg, int idx)
{
    am_key_matrix_prepare_gpio_t *p_dev = (am_key_matrix_prepare_gpio_t *)p_arg;

    int active_level;

    if ((p_dev == NULL) || (idx >= p_dev->pin_num)) {
        return -AM_EINVAL;
    }

    active_level = !am_key_matrix_active_low_get(p_dev->p_info);

    if (p_dev->last_idx != __PREPARE_GPIO_IDX_INVALID) {
        am_gpio_set(p_dev->p_pins[idx], !active_level);
    }

    am_gpio_set(p_dev->p_pins[idx], active_level);

    p_dev->last_idx = idx;

    return AM_OK;
}

/******************************************************************************/
static int __key_finish (void *p_arg, int idx)
{
    am_key_matrix_prepare_gpio_t *p_dev = (am_key_matrix_prepare_gpio_t *)p_arg;

    int active_level;

    if ((p_dev == NULL) || (idx >= p_dev->pin_num)) {
        return -AM_EINVAL;
    }

    active_level = !am_key_matrix_active_low_get(p_dev->p_info);

    if (p_dev->last_idx != __PREPARE_GPIO_IDX_INVALID) {
        am_gpio_set(p_dev->p_pins[idx], !active_level);
    }

    p_dev->last_idx = __PREPARE_GPIO_IDX_INVALID;

    return AM_OK;
}

/*******************************************************************************
   Public Functions
*******************************************************************************/
am_key_matrix_prepare_t * am_key_matrix_prepare_gpio_init (
    am_key_matrix_prepare_gpio_t    *p_dev,
    const am_key_matrix_base_info_t *p_info,
    const int                       *p_pins)
{
    int i;
    int cfg_flags;

    if ((p_dev == NULL) || (p_info == NULL) || (p_pins == NULL)) {
        return NULL;
    }

    if (am_key_matrix_scan_mode_get(p_info) == AM_KEY_MATRIX_SCAN_MODE_ROW) {
        p_dev->pin_num = am_key_matrix_num_row_get(p_info);
    } else {
        p_dev->pin_num = am_key_matrix_num_col_get(p_info);
    }

    p_dev->p_info     = p_info;
    p_dev->p_pins     = p_pins;
    p_dev->last_idx   = __PREPARE_GPIO_IDX_INVALID;

    cfg_flags = (am_key_matrix_active_low_get(p_info)) ?
                 AM_GPIO_OUTPUT_INIT_HIGH :
                 AM_GPIO_OUTPUT_INIT_LOW;

    /* ��������������Ϊ���״̬ */
    for (i = 0; i < p_dev->pin_num; i++) {
        am_gpio_pin_cfg(p_pins[i], cfg_flags);
    }

    p_dev->isa.pfn_prepare = __key_prepare;
    p_dev->isa.pfn_finish  = __key_finish;
    p_dev->isa.p_cookie    = p_dev;

    return &(p_dev->isa);
}

/* end of file */
