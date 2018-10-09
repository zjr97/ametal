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
 * \brief PCF85063 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_PCF85063_H
#define __AM_HWCONF_PCF85063_H

#include "ametal.h"
#include "am_pcf85063.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief PCF85063 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
 * \return PCF85063оƬ�������ΪNULL��������ʼ��ʧ��
 * \note ��ʹ��оƬ���⹦��ʱ��ʹ�øú�����ȡоƬ�ľ��
 */
am_pcf85063_handle_t am_pcf85063_inst_init (void);

/**
 * \brief PCF85063 ʵ����ʼ�� ��ʹ��ͨ�õ�RTC���ܣ�
 * \return RTC��׼����������ΪNULL��������ʼ��ʧ��
 * \note ��ʹ��ͨ�õ�RTC����ʱ��ʹ�øú�����ȡRTC��׼������
 */
am_rtc_handle_t am_pcf85063_rtc_inst_init(void);

/**
 * \brief PCF85063 ʵ����ʼ�� ��ʹ��ͨ�õ����ӹ��ܣ�
 * \return ���ӱ�׼����������ΪNULL��������ʼ��ʧ��
 * \note ��ʹ��ͨ�õ����ӹ���ʱ��ʹ�øú�����ȡ���ӱ�׼������
 */
am_alarm_clk_handle_t  am_pcf85063_alarm_clk_inst_init(void);

/**
 * \brief PCF85063 ʵ����ʼ�� ����PCF85063����ϵͳʱ�䣩
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ�����C�ļ��и��������Ƿ�Ϸ�
 */
int am_pcf85063_time_inst_init(void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
