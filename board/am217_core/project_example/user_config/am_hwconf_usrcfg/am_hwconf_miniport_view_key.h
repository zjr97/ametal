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
 * \brief MiniPort-View �� MiniPort-Key���ʹ�ã��Ը���λѡ����
 *
 * �����Ե���ʹ�ã�Ҳ���Ժ� MiniPort-595 ����ʹ�ã��Խ�ʡ�������š�
 *
 * ��ǰ֧�ֵ��÷��У�
 * 1. MiniPort-Key + MiniPort-View                : am_miniport_view_key_inst_init();
 * 2. MiniPort-595 + MiniPort-View + MiniPort-Key : am_miniport_view_key_595_inst_init();
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-25  tee, first implementation
 * \endinternal
 */

#ifndef __AM_HWCONF_MINIPORT_VIEW_KEY_H
#define __AM_HWCONF_MINIPORT_VIEW_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \brief MiniPort-View �� MiniPort-Key ����ʹ��ʵ����ʼ��
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ����C�ļ��и��������Ƿ�Ϸ�
 */
int am_miniport_view_key_inst_init (void);

/**
 * \brief MiniPort-View��MiniPort-595 �� MiniPort-Key ����ʹ��ʵ����ʼ��
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ����C�ļ��и��������Ƿ�Ϸ�
 */
int am_miniport_view_key_595_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
