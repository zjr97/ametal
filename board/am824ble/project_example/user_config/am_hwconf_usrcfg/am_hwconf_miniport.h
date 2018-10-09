/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief MiniPort �û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-01-24  pea, first implementation
 * \endinternal
 */

#ifndef __AM_HWCONF_MINIPORT_H
#define __AM_HWCONF_MINIPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_hc595.h"

/*******************************************************************************
  MiniPort-595 ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MiniPort-595 ʵ����ʼ��
 *
 * param ��
 *
 * \return HC595 ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_hc595_handle_t am_miniport_595_inst_init (void);

/*******************************************************************************
  MiniPort-KEY ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MiniPort-KEY ʵ����ʼ��������ʹ�ã�
 *
 * param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_miniport_key.c �ļ��е������Ƿ���ȷ
 */
int am_miniport_key_inst_init (void);

/*******************************************************************************
  MiniPort-KEY ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MiniPort-LED ʵ����ʼ��������ʹ�ã�
 *
 * param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_miniport_led.c �ļ��е������Ƿ���ȷ
 */
int am_miniport_led_inst_init (void);

/**
 * \brief MiniPort-595 + MiniPort-LED ʵ����ʼ��
 *
 * param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_miniport_led.c �ļ��е������Ƿ���ȷ
 */
int am_miniport_led_595_inst_init (void);

/*******************************************************************************
  MiniPort-View KEY ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MiniPort-KEY + MiniPort-View ʵ����ʼ��
 *
 * param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_miniport_view_key.c �ļ��е�����
 *               �Ƿ���ȷ
 */
int am_miniport_view_key_inst_init (void);

/**
 * \brief MiniPort-595 + MiniPort-KEY + MiniPort-View ʵ����ʼ��
 *
 * param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_miniport_view_key.c �ļ��е�����
 *               �Ƿ���ȷ
 */
int am_miniport_view_key_595_inst_init (void);

/*******************************************************************************
  MiniPort-View ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MiniPort-View ʵ����ʼ��������ʹ�ã�
 *
 * param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_miniport_view.c �ļ��е������Ƿ���ȷ
 */
int am_miniport_view_inst_init (void);

/**
 * \brief MiniPort-595 + MiniPort-View ʵ����ʼ��
 *
 * param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_miniport_view.c �ļ��е������Ƿ���ȷ
 */
int am_miniport_view_595_inst_init (void);

/*******************************************************************************
  MiniPort-ZLG72128 ʵ����ʼ��
*******************************************************************************/

/**
 * \brief MiniPort-ZLG72128 ʵ����ʼ��
 *
 * param ��
 *
 * \retval AW_OK ��ʼ���ɹ�
 * \retval  < 0  ��ʼ��ʧ�ܣ����� am_hwconf_miniport_zlg72128.c �ļ��е�����
 *               �Ƿ���ȷ
 */
int am_miniport_zlg72128_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_HWCONF_MINIPORT_H */

/* end of file */
