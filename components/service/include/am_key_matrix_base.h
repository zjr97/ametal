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
 * \brief ͨ�þ�����̻�����Ϣ
 *
 * \internal
 * \par modification history:
 * - 15-09-15 tee, first implementation.
 * \endinternal
 */

#ifndef __AM_KEY_MATRIX_BASE_H
#define __AM_KEY_MATRIX_BASE_H

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup am_if_key_matrix_base
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name ʹ�õ�ɨ�跽ʽ
 *
 * ����ɨ�跽ʽ��Ӳ�����
 *
 * @{
 */

/** \brief ����ɨ�裬ÿ��ɨ��һ�а���  */
#define AM_KEY_MATRIX_SCAN_MODE_ROW      0

/** \brief ����ɨ�裬ÿ��ɨ��һ�а���  */
#define AM_KEY_MATRIX_SCAN_MODE_COL      1

/** @} */

/**
 * \brief ������̻�����Ϣ
 */
typedef struct am_key_matrix_base_info {
    int          row;         /**< \brief ����Ŀ */
    int          col;         /**< \brief ����Ŀ */
    const int   *p_codes;     /**< \brief ����������Ӧ�ı��룬���е�˳�����ζ�Ӧ  */
    am_bool_t    active_low;  /**< \brief �������º��Ƿ�Ϊ�͵�ƽ */
    uint8_t      scan_mode;   /**< \brief ɨ�跽ʽ ������ɨ�����ɨ�裩*/
} am_key_matrix_base_info_t;

/**
 * \brief ��ȡ������Ŀ
 * \param[in] p_info : ������̻�����Ϣ
 * \return ������Ŀ
 */
am_static_inline
int  am_key_matrix_num_key_get (const am_key_matrix_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->row * p_info->col;
    }
    return 0;
}

/**
 * \brief ��ȡ����
 * \param[in] p_info : ������̻�����Ϣ
 * \return ����
 */
am_static_inline
int  am_key_matrix_num_row_get (const am_key_matrix_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->row;
    }
    return 0;
}

/**
 * \brief ��ȡ����
 * \param[in] p_info : ������̻�����Ϣ
 * \return ����
 */
am_static_inline
int  am_key_matrix_num_col_get (const am_key_matrix_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->col;
    }
    return 0;
}

/**
 * \brief ��ȡ���Ϊ idx ������Ӧ�ı���
 * \param[in] p_info : ������̻�����Ϣ
 * \return ��������
 */
am_static_inline
int  am_key_matrix_code_get (const am_key_matrix_base_info_t *p_info, int idx)
{
    if ((p_info != NULL) && (idx < am_key_matrix_num_key_get(p_info))) {
        return p_info->p_codes[idx];
    }
    return 0;
}

/**
 * \brief �������º��Ƿ�Ϊ�͵�ƽ
 * \param[in] p_info : ������̻�����Ϣ
 * \return �������º��Ƿ�Ϊ�͵�ƽ
 */
am_static_inline
am_bool_t  am_key_matrix_active_low_get (const am_key_matrix_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->active_low;
    }
    return AM_FALSE;
}

/**
 * \brief ��ȡ���̵�ɨ�跽ʽ
 * \param[in] p_info : ������̻�����Ϣ
 * \return �������º��Ƿ�Ϊ�͵�ƽ
 */
am_static_inline
uint8_t  am_key_matrix_scan_mode_get (const am_key_matrix_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->scan_mode;
    }
    return AM_FALSE;
}

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AM_KEY_MATRIX_BASE_H */

/* end of file */
