/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief DS1302 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_DS1302_H
#define __AM_HWCONF_DS1302_H

#include "ametal.h"
#include "am_ds1302.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief DS1302 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
 * \return DS1302оƬ�������ΪNULL��������ʼ��ʧ��
 * \note ��ʹ��оƬ���⹦��ʱ��ʹ�øú�����ȡоƬ�ľ��
 */
am_ds1302_handle_t am_ds1302_inst_init (void);

/**
 * \brief DS1302 ʵ����ʼ�� ��ʹ��ͨ�õ�RTC���ܣ�
 * \return RTC��׼����������ΪNULL��������ʼ��ʧ��
 * \note ��ʹ��ͨ�õ�RTC����ʱ��ʹ�øú�����ȡRTC��׼������
 */
am_rtc_handle_t am_ds1302_rtc_inst_init(void);

/**
 * \brief DS1302 ʵ����ʼ�� ����DS1302����ϵͳʱ�䣩
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ����C�ļ��и��������Ƿ�Ϸ�
 */
int am_ds1302_time_inst_init(void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
