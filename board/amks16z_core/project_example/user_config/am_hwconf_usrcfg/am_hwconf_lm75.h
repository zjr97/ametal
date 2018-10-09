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
 * \brief LM75 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_HWCONF_LM75_H
#define __AM_HWCONF_LM75_H

#include "ametal.h"
#include "am_temp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief LM75ʵ����ʼ��
 * \return �¶ȱ�׼����������ΪNULL��������ʼ��ʧ��
 */
am_temp_handle_t am_temp_lm75_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif
