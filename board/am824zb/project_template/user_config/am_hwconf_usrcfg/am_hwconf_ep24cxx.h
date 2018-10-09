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
 * \brief FM24C02 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-28  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_EP24CXX_H
#define __AM_HWCONF_EP24CXX_H

#include "am_nvram.h"
#include "am_ep24cxx.h"

/**
 * \brief FM24C02 ʵ����ʼ�����ֽ�ʹ��оƬ��ؽӿڲ���FM24C02��
 * \return FM24C02 оƬ�������ΪNULL��������ʼ��ʧ��
 */
am_ep24cxx_handle_t am_fm24c02_inst_init (void);

/**
 * \brief FM24C02 ʵ����ʼ�� ��������׼��NVRAM������
 *
 * \retval  AW_OK  ��ʼ���ɹ�
 * \retval   < 0   ��ʼ��ʧ�ܣ����C�ļ��и��������Ƿ�Ϸ�
 */
int am_fm24c02_nvram_inst_init (void);

#endif

/* end of file */
