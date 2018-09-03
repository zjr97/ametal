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
 * \brief ZLG72128ͨ�ýӿڣ���������ܽӿںͰ����ӿڣ�����
 *
 * \internal
 * \par Modification History
 * - 1.00 17-05-22  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_ZLG72128_STD_H
#define __AM_ZLG72128_STD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_zlg72128.h"
#include "am_digitron_dev.h"

/**
 * @addtogroup am_if_zlg72128_std
 * @copydoc am_zlg72128_std.h
 * @{
 */

#define AM_ZLG72128_STD_KEY_ROW_0  (1 << 0) /**< \brief ʹ�õ�0��      */
#define AM_ZLG72128_STD_KEY_ROW_1  (1 << 1) /**< \brief ʹ�õ�1��      */
#define AM_ZLG72128_STD_KEY_ROW_2  (1 << 2) /**< \brief ʹ�õ�2��      */
#define AM_ZLG72128_STD_KEY_ROW_3  (1 << 3) /**< \brief ʹ�õ�3�У����ܰ����У�*/
                                                 
#define AM_ZLG72128_STD_KEY_COL_0  (1 << 0) /**< \brief ʹ�õ�0��      */
#define AM_ZLG72128_STD_KEY_COL_1  (1 << 1) /**< \brief ʹ�õ�1��      */
#define AM_ZLG72128_STD_KEY_COL_2  (1 << 2) /**< \brief ʹ�õ�2��      */
#define AM_ZLG72128_STD_KEY_COL_3  (1 << 3) /**< \brief ʹ�õ�3��      */
#define AM_ZLG72128_STD_KEY_COL_4  (1 << 4) /**< \brief ʹ�õ�4��      */
#define AM_ZLG72128_STD_KEY_COL_5  (1 << 5) /**< \brief ʹ�õ�5��      */
#define AM_ZLG72128_STD_KEY_COL_6  (1 << 6) /**< \brief ʹ�õ�6��      */
#define AM_ZLG72128_STD_KEY_COL_7  (1 << 7) /**< \brief ʹ�õ�7��      */

/**
 * \brief ZLG72128����ͨ������ܺͰ������豸��Ϣ
 */
typedef struct am_zlg72128_std_devinfo {
    am_zlg72128_devinfo_t  base_info;         /**< \brief �����豸��Ϣ         */
    am_digitron_devinfo_t  id_info;           /**< \brief �������ʾ��ID         */
    uint16_t               blink_on_time;     /**< \brief һ����˸�����ڣ�������ʱ�䣬�� 500ms */
    uint16_t               blink_off_time;    /**< \brief һ����˸�����ڣ�Ϩ���ʱ�䣬�� 500ms */
    uint8_t                key_use_row_flags; /**< \brief ʵ��ʹ�õ��б�־  */
    uint8_t                key_use_col_flags; /**< \brief ʵ��ʹ�õ��б�־ */
    const int             *p_key_codes;    /**< \brief �������룬 ���СΪ key_rows * key_cols */
    uint8_t                num_digitron;   /**< \brief ʵ��ʹ�õ�����ܸ��� */
} am_zlg72128_std_devinfo_t;

/**
 * \brief ZLG72128����ͨ������ܺͰ������豸
 */
typedef struct am_zlg72128_std_digitron_key_dev {

    /** ʹ�õײ��ZLG72128����    */
    am_zlg72128_dev_t     zlg72128_dev;

    /** \brief ������豸      */
    am_digitron_dev_t     digitron_dev;

    /** \brief ZLG72128���      */
    am_zlg72128_handle_t  handle;

    /** \brief ���ܼ�ֵ�������ܼ�ת��Ϊͨ�ð���ʹ��      */
    uint8_t               f_key;
    
    /** \brief ʵ��ʹ�õİ�������  */
    uint8_t               num_rows;

    /** \brief ʵ��ʹ�ð��������� */
    uint8_t               num_cols;

    /** \brief ��˸���  */
    uint16_t              blink_flags;

    /** \brief �Զ�����뺯��  */
    uint16_t  (*pfn_decode)(uint16_t code);

    /** \brief ���ڱ����豸��Ϣָ�� */
    const am_zlg72128_std_devinfo_t  *p_info;

} am_zlg72128_std_dev_t;

/**
 * \brief ZLG72128��ʼ������
 *
 * ʹ��ZLG72128ǰ��Ӧ�����ȵ��øó�ʼ���������Ի�ȡ����ZLG72128��handle��
 *
 * \param[in] p_dev      : ָ��ZLG72128�豸��ָ��
 * \param[in] p_info     : ָ��ZLG72128�豸��Ϣ��ָ��
 * \param[in] i2c_handle : I2C��׼������������ʹ�ø�I2C�����ZLG72128ͨ�ţ�
 *
 * \return AM_OK����ʼ���ɹ������򣬳�ʼ��ʧ��
 */
int am_zlg72128_std_init (am_zlg72128_std_dev_t           *p_dev,
                          const am_zlg72128_std_devinfo_t *p_info,
                          am_i2c_handle_t                  i2c_handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG72128_STD_H */

/* end of file */
