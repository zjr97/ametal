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
 * \brief ͨ������ܻ�����Ϣ & ����
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_BASE_H
#define __AM_DIGITRON_BASE_H

#include "ametal.h"
#include "am_digitron_disp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name am_if_digitron_base
 * @{
 */

/**
 * \name �����ɨ�跽ʽ
 *
 *     ���ھ������Ӧ�ó��ϣ�������һ������ܣ���ÿ��ɨ��һ������ܡ�
 * ��������Ϊ1��ɨ�跽ʽΪ��ɨ�衣ɨ�跽ʽ����Ӳ�������ġ�
 *
 * @{
 */

/** \brief ����ɨ�裬ÿ��ɨ��һ�������  */
#define AM_DIGITRON_SCAN_MODE_ROW      0

/** \brief ����ɨ�裬ÿ��ɨ��һ�������  */
#define AM_DIGITRON_SCAN_MODE_COL      1

/** @} */

/**
 * \brief ����ܻ�����Ϣ
 */
typedef struct am_digitron_base_info {
    uint8_t        num_segment;       /**< \brief ����ܶ��� */
    uint8_t        num_rows;          /**< \brief ����ܾ�������� */
    uint8_t        num_cols;          /**< \brief ����ܾ�������� */
    uint8_t        scan_mode;         /**< \brief ɨ�跽ʽ������ɨ�����ɨ�� */
    am_bool_t      seg_active_low;    /**< \brief ����ܶζ˵ļ���      */
    am_bool_t      com_active_low;    /**< \brief ����ܹ����˵ļ��� */
} am_digitron_base_info_t;

/**
 * \brief ��ȡ����ܵĶ���
 * \param[in] p_info : ����ܻ�����Ϣ
 * \return ����ܵĶ���
 */
am_static_inline
uint8_t am_digitron_num_segment_get (const am_digitron_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->num_segment;
    }
    return 0;
}

/**
 * \brief ��ȡ����ܵ�����
 * \param[in] p_info : ����ܻ�����Ϣ
 * \return ����ܵ�����
 */
am_static_inline
uint8_t am_digitron_num_row_get (const am_digitron_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->num_rows;
    }
    return 0;
}

/**
 * \brief ��ȡ����ܵ�����
 * \param[in] p_info : ����ܻ�����Ϣ
 * \return ����ܵ�����
 */
am_static_inline
uint8_t am_digitron_num_col_get (const am_digitron_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->num_cols;
    }
    return 0;
}

/**
 * \brief ��ȡ����ܵ�ɨ�跽ʽ
 * \param[in] p_info : ����ܻ�����Ϣ
 * \return ����ܵ�ɨ�跽ʽ������ɨ�����ɨ�裩
 */
am_static_inline
uint8_t am_digitron_scan_mode_get (const am_digitron_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->scan_mode;
    }
    return 0;
}

/**
 * \brief ����ܶ��Ƿ�͵�ƽ����
 * \param[in] p_info : ����ܻ�����Ϣ
 * \return ����ܵĶ���
 */
am_static_inline
am_bool_t am_digitron_seg_active_low_get (const am_digitron_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->seg_active_low;
    }
    return AM_FALSE;
}

/**
 * \brief �����λ�Ƿ�͵�ƽ����
 * \param[in] p_info : ����ܻ�����Ϣ
 * \return ����ܵĶ���
 */
am_static_inline
am_bool_t am_digitron_com_active_low_get (const am_digitron_base_info_t *p_info)
{
    if (p_info != NULL) {
        return p_info->com_active_low;
    }
    return AM_FALSE;
}

/**
 * \brief ����ܶ��뷢���������뵥�����ͣ�
 */
typedef struct am_digitron_base_sender_seg {

    /** \brief ���뷢�ͣ�һ�ο��ܷ��Ͷ������ܵ�λ�� */
    int  (*pfn_seg_send) (void    *p_cookie, 
                          void    *p_seg, 
                          uint8_t  num_segment, 
                          uint8_t  num_digitron);

    /** \brief ���뷢�ͺ������Զ������ */
    void  *p_cookie;

} am_digitron_base_sender_seg_t;

/**
 * \brief �����λ�뷢������λ����������
 */
typedef struct am_digitron_base_sender_com {

    /** \brief λ�뷢�ͣ�һ�ο���ѡ�ж�������λ����̬ɨ�������ʹ�ã� */
    int (*pfn_com_send) (void *p_cookie, uint32_t com);

    /** \brief λ�뷢�ͺ������Զ������ */
    void *p_cookie;

} am_digitron_base_sender_com_t;

/**
 * \brief �����λѡ������λ����������
 */
typedef struct am_digitron_base_selector_com {

    /** \brief λѡ����ѡ��������λ��Ч����̬ɨ��ʹ�ã�������λ��Ч */
    int (*pfn_com_sel) (void *p_cookie, int idx);
    
    /** \brief λѡ�������Զ������ */
    void *p_cookie;

} am_digitron_base_selector_com_t;

/**
 * \brief �����λ��Ͷ��뷢������λ��Ͷ���ͬʱ���ͣ�
 */
typedef struct am_digitron_base_sender_data {

    /** \brief λ��Ͷ���ͬʱ���� */
    int (*pfn_data_send) (void    *p_cookie,
                          void    *p_seg,
                          uint8_t  num_segment,
                          uint8_t  num_digitron,
                          uint32_t com);

    /** \brief ���ݷ��ͺ������Զ������ */
    void *p_cookie;

} am_digitron_base_sender_data_t;


/**
 * \brief ����ܶ��뷢�ͣ����뵥�����ͣ�
 *
 * \param[in] p_sender     : ���뷢����
 * \param[in] p_seg        : ���뻺����
 * \param[in] num_segment  : ��������ܵĶ���Ŀ
 * \param[in] num_digitron : ��ǰɨ�������ܸ���
 *
 * \return ��׼�����
 */
am_static_inline
int am_digitron_seg_send  (am_digitron_base_sender_seg_t *p_sender,
                           void                          *p_seg,
                           uint8_t                        num_segment,
                           uint8_t                        num_digitron)

{
    if (p_sender && p_sender->pfn_seg_send) {

        return p_sender->pfn_seg_send(p_sender->p_cookie,
                               p_seg,
                               num_segment,
                               num_digitron);
    }
    return -AM_ENOTSUP;
}

/**
 * \brief �����λ�뷢�ͣ�λ�뵥�����ͣ�
 *
 * \param[in] p_sender : λ�뷢����
 * \param[in] com      : λ��
 *
 * \return ��׼�����
 */
am_static_inline
int am_digitron_com_send (am_digitron_base_sender_com_t *p_sender,
                          uint32_t                       com)
{
    if (p_sender && p_sender->pfn_com_send) {
        return p_sender->pfn_com_send(p_sender->p_cookie, com);
    }
    return -AM_ENOTSUP;
}

/**
 * \brief �����λ��ѡ��
 *
 * \param[in] p_sender : λ��ѡ����
 * \param[in] idx      : λѡ����
 *
 * \return ��׼�����
 */
am_static_inline
int am_digitron_com_sel (am_digitron_base_selector_com_t *p_sel, int idx)
{
    if (p_sel && p_sel->pfn_com_sel) {
        return p_sel->pfn_com_sel(p_sel->p_cookie, idx);
    }
    return -AM_ENOTSUP;
}

/**
 * \brief λ��Ͷ���ͬʱ���ͣ������ٲ���λ��Ͷ������ͬʱ���͵�Ӳ����·ʹ�ã�
 *
 * \param[in] p_sender     : ���ݷ�����
 * \param[in] p_seg        : ɨ����뻺����
 * \param[in] num_segment  : ������Ŀ
 * \param[in] num_digitron : ��ǰɨ�������ܸ���
 * \param[in] com          : λ��
 *
 * \return ��׼�����
 */
am_static_inline
int am_digitron_data_send (am_digitron_base_sender_data_t *p_sender,
                           void                           *p_seg,
                           uint8_t                         num_segment,
                           uint8_t                         num_digitron,
                           uint32_t                        com)

{
    if (p_sender && p_sender->pfn_data_send) {

        return p_sender->pfn_data_send(p_sender->p_cookie,
                                       p_seg,
                                       num_segment,
                                       num_digitron,
                                       com);
    }
    return -AM_EINVAL;
}

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_BASE_H */

/* end of file */
