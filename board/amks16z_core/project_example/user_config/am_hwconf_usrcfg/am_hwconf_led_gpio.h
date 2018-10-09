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
 * \brief LED �����ļ���GPIOֱ��������
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_HWCONF_LED_GPIO_H
#define __AM_HWCONF_LED_GPIO_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief LED ʵ����ʼ����GPIOֱ��������
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ�����C�ļ��и��������Ƿ�Ϸ�
 */
int am_led_gpio_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
