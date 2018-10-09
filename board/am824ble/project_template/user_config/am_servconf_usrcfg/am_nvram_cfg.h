/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief NVRAM ��׼����洢�ζ���
 *
 * ��ʹ��NVRAM��׼�ӿڽ��з���ʧ���ݵĴ洢���ȡʱ���� \sa am_nvram_set() ��
 * \sa am_nvram_get()���ӿڵ���ϸ������� \sa am_nvram.h��
 *
 * �洢�ε�����name�͵�Ԫ��unit���ڸ��ļ��ж��壬�����û�����ϵͳ�����еķ���ʧ
 * �洢�Ρ�
 *
 * \internal
 * \par modification history
 * - 1.00 15-01-19  tee, first implementation
 * \endinternal
 */

#ifndef __AM_NVRAM_CFG_H
#define __AM_NVRAM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief  NVRAM��׼�����ʼ��
 *
 * \note ʹ��NVRAMǰ��������øú�������ͨ����am_prj_config.h�ļ��е�
 *       #AM_CFG_NVRAM_ENABLE ��ֵ�޸�Ϊ 1 ʵ�֣�ʹϵͳ����ʱ�Զ����øú���
 */
void am_nvram_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_NVRAM_CFG_H */

/* end of file */
