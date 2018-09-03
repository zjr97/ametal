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
 * \brief �����¼����ࣺ�������������¼�����
 *
 * ��Ϊһ�������¼����࣬���Թ�����������¼����ͣ��磺
 * 1. ���������¼�
 * 2. �������������¼�
 * 3. ������������¼�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-08-23  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_EVENT_CATEGORY_INPUT_H
#define __AM_EVENT_CATEGORY_INPUT_H

#include "am_common.h"
#include "am_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ϵͳ�����¼������ʼ��
 * \return ��
 */
void am_event_category_input_init (void);

/**
 * \brief �������¼���������ע��һ�־����¼����ͣ��簴���¼����͵ȣ�
 * \param[in] p_evt_type : ע����¼�����
 * \return ��׼�����
 */
int am_event_category_intput_event_register (am_event_type_t *p_evt_type);

/**
 * \brief ע��һ�־����¼����ͣ��簴���¼����͵ȣ�
 * \param[in] p_evt_type : ע����¼�����
 * \return ��׼�����
 */
int am_event_category_intput_event_unregister (am_event_type_t *p_evt_type);

/**
 * \brief �������¼���������ע��һ�־����¼������������ڹ���
 *
 * �κ�һ�������¼����������������ô�ע����¼�������
 *
 * \param[in] p_evt_type : ע����¼�������
 *
 * \return ��׼�����
 */
int am_event_category_intput_handler_register (am_event_handler_t *p_evt_handler);


/**
 * \brief ע��һ�־����¼������������ڹ���
 *
 * �κ�һ�������¼����������������ô�ע����¼�������
 *
 * \param[in] p_evt_type : ע����¼�������
 *
 * \return ��׼�����
 */
int am_event_category_intput_handler_unregister (am_event_handler_t *p_evt_handler);


#ifdef __cplusplus
}
#endif

#endif /* __AM_FTL_H */
