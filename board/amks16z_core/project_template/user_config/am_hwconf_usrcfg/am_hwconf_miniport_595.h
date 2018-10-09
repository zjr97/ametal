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
 * \brief Miniport-595 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_MINIPORT_595_H
#define __AM_HWCONF_MINIPORT_595_H

#include "ametal.h"
#include "am_hc595.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief MiniPort-595 ʵ����ʼ��
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ����C�ļ��и��������Ƿ�Ϸ�
 */
am_hc595_handle_t am_miniport_595_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
