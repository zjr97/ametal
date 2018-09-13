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
 * \brief �ڱ�׼������̵Ļ����ϣ���������ʱ����ʵ���Զ�ɨ��
 *
 * \internal
 * \par modification history:
 * - 15-09-15 tee, first implementation.
 * \endinternal
 */

#ifndef __AM_KEY_MATRIX_SOFTIMER_H
#define __AM_KEY_MATRIX_SOFTIMER_H

#include "ametal.h"
#include "am_types.h"
#include "am_key_matrix_base.h"
#include "am_key_matrix.h"
#include "am_softimer.h"

/**
 * \addtogroup am_if_key_matrix_softimer
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** \brief ��������豸  */
typedef struct am_key_matrix_softimer {
    am_key_matrix_t  *p_real;
    am_softimer_t     timer;
    int               scan_idx;
} am_key_matrix_softimer_t;

/**
 * \brief ��ʼ�������������ʱ����ʵ���Զ�ɨ��
 *
 * \param[in] p_dev            : �����豸ʵ��
 * \param[in] p_timer          : �����ʱ��ʵ��
 * \param[in] scan_interval_ms : ɨ�����о�����̵�ʱ������ ��λ ms
 *
 * \return  AM_OK����ʼ���ɹ�; ����ֵ����ʼ��ʧ�ܣ�ʧ��ԭ����鿴�����
 * \note ɨ����У��У�ǰ����ȷ�����ݾ�����ȷ��ȡ����Ч����
 */
int am_key_matrix_softimer_init (am_key_matrix_softimer_t *p_dev,
                                 am_key_matrix_t          *p_key,
                                 int                       scan_interval_ms);

/**
 * \brief ���ʼ����ֹͣ�����ʱ������ֹ�Զ�ɨ��
 *
 * \param[in] p_dev  : �����豸ʵ��
 *
 * \return  AM_OK�����ʼ���ɹ�; ����ֵ�����ʼ��ʧ�ܣ�ʧ��ԭ����鿴�����
 *
 * \note ��ֹ�������ٴ�ʹ�������ʱ��ʵ���Զ�ɨ�裬����Ҫ���µ��� \sa
 * am_key_matrix_softimer_init()����
 */
int am_key_matrix_softimer_deinit (am_key_matrix_softimer_t *p_dev);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AM_KEY_MATRIX_SOFTIMER_H */

/* end of file */
