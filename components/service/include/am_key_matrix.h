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
 * \brief ͨ�þ�����������ӿڣ�������������������ʵ�־���ļ�ֵ��ȡ������
 *
 * \internal
 * \par modification history:
 * - 15-09-15 tee, first implementation.
 * \endinternal
 */

#ifndef __AM_KEY_MATRIX_H
#define __AM_KEY_MATRIX_H

#include "ametal.h"
#include "am_types.h"
#include "am_key_matrix_base.h"
 
/**
 * \addtogroup am_if_key_matrix
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ��ֵ��ȡ����׼��
 */
typedef struct am_key_matrix_prepare {
    
    /** \brief ��ȡ��ֵ׼�����ú����ڼ�ֵ��ȡǰ���� */
    int (*pfn_prepare) (void *p_cookie, int idx);

    /** \brief ��ȡ��ֵ�������ú����ڼ�ֵ��ȡ����� */
    int (*pfn_finish) (void *p_cookie, int idx); 
    
    /** \brief �����Զ������ */
    void *p_cookie;

} am_key_matrix_prepare_t;

/**
 * \brief ��ֵ��ȡ����ȡһ�л�һ�еļ�ֵ��
 */
typedef struct am_key_matrix_read {

    /** \brief ��ֵ��ȡ��������ȡһ�л�һ�еļ�ֵ */
    uint32_t (*pfn_val_read) (void *p_cookie, int idx);

    /** \brief �����Զ������ */
    void      *p_cookie;

} am_key_matrix_read_t;


/** \brief ��������豸  */
typedef struct am_key_matrix {
    const am_key_matrix_base_info_t *p_info;
    uint32_t                         key_samp_last;
    uint32_t                         key_samp_cur;
    uint32_t                         key_final;
    am_key_matrix_prepare_t         *p_prepare;
    am_key_matrix_read_t            *p_read;
} am_key_matrix_t;

/**
 * \brief �����豸��ʼ��
 *
 * \param[in] p_dev      : �����豸ʵ��
 * \param[in] p_info     : ������Ϣ
 * \param[in] p_prepare  : ��ֵ��ȡ��׼������������׼��������������ΪNULL
 * \param[in] p_read     : ��ֵ��ȡ��
 *
 * \return  AM_OK����ʼ���ɹ�; ����ֵ����ʼ��ʧ�ܣ�ʧ��ԭ����鿴�����
 */
int am_key_matrix_init (am_key_matrix_t                 *p_dev,
                        const am_key_matrix_base_info_t *p_info,
                        am_key_matrix_prepare_t         *p_prepare,
                        am_key_matrix_read_t            *p_read);

/**
 * \brief ִ��һ��ɨ�裬ɨ��һ�л�һ�У����Զ�ɨ�裬һ������������ܸ�������ʱ��
 *
 * \param[in] p_dev    : �����豸ʵ��
 * \param[in] scan_idx : ����ɨ����кŻ��к�
 *
 * \return  AM_OK����ʼ���ɹ�; ����ֵ����ʼ��ʧ�ܣ�ʧ��ԭ����鿴�����
 * \note ɨ����У��У�ǰ����ȷ�����ݾ�����ȷ��ȡ����Ч����
 */
int am_key_matrix_scan (am_key_matrix_t *p_dev, int scan_idx);

/**
 * \brief ��ȡ���ɨ������
 * \param[in] p_dev  : �����豸ʵ��
 * \return  ���ɨ������
 */
int am_key_matrix_scan_idx_max_get (am_key_matrix_t *p_dev);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AM_KEY_MATRIX_H */

/* end of file */
