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
 * \brief ����������HC595��
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_SEG_HC595_H
#define __AM_DIGITRON_SEG_HC595_H

#include "ametal.h"
#include "am_digitron_base.h"
#include "am_hc595.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name am_if_digitron_seg_hc595
 * @{
 */

/**
 * \brief HC595�����豸
 */
typedef struct am_digitron_seg_hc595 {
    am_digitron_base_sender_seg_t      sender;
    am_hc595_handle_t                  handle;
} am_digitron_seg_hc595_dev_t;

/**
 * \brief HC595���뷢������ʼ��
 *
 * \param[in] p_dev  : HC595���뷢�����豸ʵ��
 * \param[in] p_info : ����ܻ�����Ϣ
 * \param[in] flags  : HC595���ݷ��ͱ�־����Q0 �� 'a'�����ӣ��� ���� LSB Ӧ���ȷ���
 * \param[in] handle : ��׼��HC595������
 *
 * \return ��׼�Ķ��뷢�������ɹ������ɨ����ʹ�ã�
 */
am_digitron_base_sender_seg_t *am_digitron_seg_hc595_init (
        am_digitron_seg_hc595_dev_t     *p_dev,
        const am_digitron_base_info_t   *p_info,
        am_hc595_handle_t                handle);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_SEG_HC595_H */

/* end of file */
