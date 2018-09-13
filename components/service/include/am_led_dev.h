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
 * \brief ��׼��LED�豸����
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_LED_DEV_H
#define __AM_LED_DEV_H

#include "ametal.h"
#include "am_led.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name am_if_led_dev
 * @{
 */

/**
 * \brief LED��������
 */
typedef struct am_led_drv_funcs {

    /* ����LED��״̬ */
    int (*pfn_led_set)   (void *p_cookie, int id, am_bool_t on);

    /* ��תLED��״̬ */
    int (*pfn_led_toggle)(void *p_cookie, int id);

} am_led_drv_funcs_t;

/**
 * \brief ͨ��LED������Ϣ
 */
typedef struct am_led_servinfo {
    int         start_id;        /**< \brief ���豸�ṩ��LED�������ʼ��� */
    int         end_id;          /**< \brief ���豸�ṩ��LED����Ľ������ */
} am_led_servinfo_t;

/**
 * \brief ͨ��LED�豸
 */
typedef struct am_led_dev {
    const am_led_drv_funcs_t     *p_funcs;   /**< \brief ��������            */
    void                         *p_cookie;  /**< \brief ������������  */
    const am_led_servinfo_t      *p_info;    /**< \brief LED������Ϣ     */
    struct am_led_dev            *p_next;    /**< \brief ��һ��LED�豸 */
} am_led_dev_t;

/** 
 * \brief LED�豸������ʼ��
 * \retval AM_OK : LED�豸������ʼ�����ʼ���ɹ�
 */
int am_led_dev_lib_init (void);

/**
 * \brief ���һ��LED�豸
 *
 * \param[in] p_dev    : LED�豸ʵ��
 * \param[in] p_info   ��LED�豸������Ϣ
 * \param[in] p_funcs  : LED�豸����������
 * \param[in] p_cookie : ���������Ĳ���
 *
 * \retval AM_OK      : ��ӳɹ�
 * \retval -AM_EINVAL �����ʧ�ܣ��������ڴ���
 * \retval -AM_EPERM  : ���ʧ�ܣ����豸��Ӧ��LED����Ѿ�����
 */
int am_led_dev_add (am_led_dev_t             *p_dev,
                    const am_led_servinfo_t  *p_info,
                    const am_led_drv_funcs_t *p_funcs,
                    void                     *p_cookie);
/**
 * \brief ɾ��һ��LED�豸
 *
 * \param[in] p_dev     : LED�豸ʵ��
 *
 * \retval AM_OK      : ɾ���ɹ�
 * \retval -AM_EINVAL ��ɾ��ʧ�ܣ��������ڴ���
 * \retval -AM_ENODEV : ɾ��ʧ�ܣ��޴˲���
 */
int am_led_dev_del (am_led_dev_t *p_dev);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LED_DEV_H */

/* end of file */
