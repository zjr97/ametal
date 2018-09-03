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
 * \brief ͨ��������豸����
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_DEV_H
#define __AM_DIGITRON_DEV_H

#include "ametal.h"
#include "am_digitron_disp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name am_if_digitron_dev
 * @{
 */

/**
 * \brief ͨ������ܲ����ӿ�
 * \note ��ĳһ��ܲ�֧�֣����������ΪNULL
 */
typedef struct am_digitron_disp_ops {

    /** \brief ���ý��뺯���ӿ� */
    int (*pfn_decode_set) (void *p_cookie, uint16_t (*pfn_decode) (uint16_t ch));

    /** \brief �����������˸ */
    int (*pfn_blink_set)(void *p_cookie, int index, am_bool_t blink);

    /** \brief ��ʾ���� */
    int (*pfn_disp_at)(void *p_cookie, int index, uint16_t seg);

    /** \brief ��ʾ�ַ� */
    int (*pfn_disp_char_at)(void *p_cookie, int index, const char ch);

    /** \brief ��ʾ�ַ��� */
    int (*pfn_disp_str)(void *p_cookie, int index, int len, const char *p_str);

    /** \brief ����*/
    int (*pfn_clr)(void *p_cookie);

    /** \brief ʹ�� */
    int (*pfn_enable)(void *p_cookie);

    /** \brief ���� */
    int (*pfn_disable)(void *p_cookie);

} am_digitron_disp_ops_t;

/**
 * \brief ͨ���������ʾ����Ϣ��һ���������ʾ�����ܰ���һ�����������λ��
 */
typedef struct am_digitron_devinfo {

    uint8_t         id;        /**< \brief �������ʾ����� */

} am_digitron_devinfo_t;

/**
 * \brief ͨ��������豸
 */
typedef struct am_digitron_dev {
    const am_digitron_disp_ops_t *p_ops;     /**< \brief ��������  */
    void                         *p_cookie;  /**< \brief ������������ */
    const am_digitron_devinfo_t  *p_info;    /**< \brief �������ʾ����� */
    struct am_digitron_dev       *p_next;    /**< \brief ��һ���������ʾ�� */
} am_digitron_dev_t;

/** 
 * \brief ������豸������ʼ��
 * \retval AM_OK : ������豸������ʼ�����ʼ���ɹ�
 */
int am_digitron_dev_lib_init (void);

/**
 * \brief ���һ��������豸
 *
 * \param[in] p_dd     : ������豸ʵ��
 * \param[in] p_info   ��������豸��Ϣ������������豸�ı�ŵȣ�
 * \param[in] p_ops    : ������豸����������
 * \param[in] p_cookie : ���������Ĳ���
 *
 * \retval AM_OK      : ��ӳɹ�
 * \retval -AM_EINVAL �����ʧ�ܣ��������ڴ���
 * \retval -AM_EPERM  : ���ʧ�ܣ��ñ�ŵ��豸�Ѿ�����
 */
int am_digitron_dev_add (am_digitron_dev_t            *p_dd,
                         const am_digitron_devinfo_t  *p_info,
                         const am_digitron_disp_ops_t *p_ops,
                         void                         *p_cookie);
/**
 * \brief ɾ��һ��������豸
 *
 * \param[in] p_dd     : ������豸ʵ��
 *
 * \retval AM_OK      : ɾ���ɹ�
 * \retval -AM_EINVAL ��ɾ��ʧ�ܣ��������ڴ���
 * \retval -AM_ENODEV : ɾ��ʧ�ܣ��޴˲���
 */
int am_digitron_dev_del (am_digitron_dev_t *p_dd);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_DEV_H */

/* end of file */
