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
 * \brief GPIO �����û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */
#ifndef __AM_HWCONF_KEY_GPIO_H
#define __AM_HWCONF_KEY_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \brief GPIO����ʵ����ʼ��
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ�����C�ļ��и��������Ƿ�Ϸ�
 */
int am_key_gpio_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
