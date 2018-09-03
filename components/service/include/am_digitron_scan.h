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
 * \brief ͨ�ö�̬ɨ���������
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_SCAN_H
#define __AM_DIGITRON_SCAN_H

#include "ametal.h"
#include "am_digitron_disp.h"
#include "am_softimer.h"
#include "am_digitron_dev.h"
#include "am_digitron_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name am_if_digitron_scan
 * @{
 */

/**
 * \brief ��̬ɨ�����������Ϣ
 */
typedef struct am_digitron_scan_devinfo {

    /** \brief ��׼������豸��Ϣ������ID�� */
    am_digitron_devinfo_t devinfo; 

    /** \brief ��������ܵ�ɨ��Ƶ�ʣ�һ�� 50Hz */
    uint8_t               scan_freq;
 
    /** \brief һ����˸�����ڣ�������ʱ�䣬�� 500ms */
    uint16_t              blink_on_time;
    
    /** \brief һ����˸�����ڣ�Ϩ���ʱ�䣬�� 500ms */
    uint16_t              blink_off_time; 

    /**
     * \brief ������Դ棬��������������ܶ������
     *
     * ����ܶ��� 1 ~ 8�� ����������Ϊ uint8_t����С��������ܸ���һ��
     * ����ܶ��� 8 ~ 16������������Ϊ uint16_t����С��������ܸ���һ��
     */
    void                  *p_disp_buf;

    /**
     * \brief �����ɨ���Դ棬���ڴ�ŵ���ɨ��ľ�������������ܶ������
     *
     * ����ܶ��� 1 ~ 8�� ����������Ϊ uint8_t����С�뵥�������ɨ��ĸ���һ��
     * ����ܶ��� 8 ~ 16������������Ϊ uint16_t����С�뵥�������ɨ��ĸ���һ��
     *
     * �簴��ɨ�裬�����С�� num_rows ��ͬ��
     * �簴��ɨ�裬�����С�� num_cols ��ͬ��
     *
     * ���ھ��󲿷�Ӧ�õ�·��һ��ֻ��ɨ��һ������ܣ������СΪ1
     */
    void                  *p_scan_buf;

} am_digitron_scan_devinfo_t;


/**
 * \brief ���������������λѡ�ֿ����У���Ӧ���ɾ��������ṩ
 *
 * �����λ��ֿ����ͣ��Զ�������Ӱ���⣬����Ӱ�����ڣ�ִ�пռ�ص�������
 *
 */
typedef struct am_digitron_scan_ops_separate {
   am_digitron_base_sender_seg_t      *p_send_seg; /**< \brief ���뷢���� */
   am_digitron_base_selector_com_t    *p_sel_com;  /**< \brief λѡ�� */
} am_digitron_scan_ops_separate_t;

/**
 * \brief ���������������λѡͬʱ���У���Ӧ���ɾ��������ṩ
 *
 *     �����λ��ͬʱ���ͣ���Ҫ���д�����Ӱ���⣬�µ�����ܼ���󣬶�ѡ��λѡ��
 * ������Ч״̬
 */
typedef struct am_digitron_scan_ops_unite {
    am_digitron_base_sender_data_t   *p_send_data; /**< \brief ���뷢���� */
} am_digitron_scan_ops_unite_t;

/**
 * \brief ���лص����������������Ÿ��ã�
 *
 * �������λ��ʼɨ��ʱ������øûص�������������������밴�����õ�����Ӧ�ó��ϡ�
 * �ڻص�����ִ���ڼ䣬�����λѡ������Ч״̬����ѡ������Ч״̬
 *
 * \param[in] p_cookie : ���������Զ������
 * \param[in] scan_idx : ��ǰ������λѡ
 *
 * \return ��
 */
typedef void (*am_digitron_scan_cb_t) (void *p_cookie, int scan_idx);

/**
 * \brief ͨ�ö�̬ɨ��������豸
 */
typedef struct am_digitron_scan_dev {

    am_digitron_dev_t isa;             /**< \brief �Ǳ�׼��������豸      */
    am_softimer_t     timer;           /**< \brief ʹ�������ʱ��          */

    uint8_t           scan_idx;        /**< \brief ��ǰɨ������            */
    uint8_t           scan_interval;   /**< \brief ɨ��ʱ����            */
    uint8_t           num_scan;        /**< \brief ����ɨ��ĸ�����һ��Ϊ1 */
    uint8_t           num_digitron;    /**< \brief ����ܸ���              */
    uint32_t          blink_flags;     /**< \brief ��˸���(bit map)       */
    uint16_t          blink_cnt;       /**< \brief ��˸����                */

    uint16_t  (*pfn_decode)(uint16_t code);

    const void                       *pfn_buf_access; 
    am_bool_t                         is_separate;
    void                             *p_ops;
    am_digitron_scan_cb_t             pfn_black_cb;
    void                             *p_arg;
    const am_digitron_scan_devinfo_t *p_info;
    const am_digitron_base_info_t    *p_baseinfo;
} am_digitron_scan_dev_t;

/**
 * \brief ��̬ɨ��������ܳ�ʼ��
 *
 * \param[in] p_dev       : ��̬ɨ����������豸ʵ��
 * \param[in] p_info      : ��̬ɨ����������豸ʵ����Ϣ
 * \param[in] is_separate : �����λ���Ƿ�Ϊ�������ͣ� ������ p_ops ��ʵ������
 *                         - AM_TRUE�� ����Ϊ��am_digitron_scan_ops_unite_t *
 *                         - AM_FALSE������Ϊ��am_digitron_scan_ops_separate_t *
 *
 * \retval AM_OK      : ��ʼ���ɹ�
 * \retval -AM_EINVAL ����ʼ��ʧ�ܣ��������ڴ���
 */
int am_digitron_scan_init (am_digitron_scan_dev_t           *p_dev,
                           const am_digitron_scan_devinfo_t *p_info,
                           const am_digitron_base_info_t    *p_baseinfo,
                           am_bool_t                         is_separate,
                           void                             *p_ops);

/**
 * \brief ���������ɨ��ص���������������һ����
 *
 *     ��һ���µ������λ��ʼɨ��ʱ������øûص�����
 * 
 * \param[in] p_dev  : ��̬ɨ����������豸ʵ��
 * \param[in] pfn_cb : �ص�����
 * \param[in] p_arg  : �ص������û�����
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL ������ʧ�ܣ��������ڴ���
 */
int am_digitron_scan_cb_set (am_digitron_scan_dev_t *p_dev,
                             am_digitron_scan_cb_t   pfn_cb,
                             void                   *p_arg);

/**
 * \brief ��̬ɨ��������ܽ��ʼ��
 *
 * \param[in] p_dev   : ��̬ɨ����������豸ʵ��
 *
 * \retval AM_OK      : ���ʼ���ɹ�
 * \retval -AM_EINVAL �����ʼ��ʧ�ܣ��������ڴ���
 */
int am_digitron_scan_deinit (am_digitron_scan_dev_t *p_dev);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_SCAN_H */

/* end of file */
