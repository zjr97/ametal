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
 * \brief GPIO���� �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_HWCONF_KEY_GPIO_H
#define __AM_HWCONF_KEY_GPIO_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

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
