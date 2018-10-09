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
 * \brief ���������ļ�������ϵͳ���弶��Ӳ������
 * \sa am_prj_config.h
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  tee, first implementation
 * \endinternal
 */

#ifndef __AM_PRJ_CONFIG_H
#define __AM_PRJ_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \addtogroup am_if_prj_config
 * \copydoc am_prj_config.h
 * @{
 */

/**
 * \brief һЩȫ��ʹ�õĵ�ʵ���豸��Ĭ����ϵͳ����ʱ��ʼ�����Ա�ȫ��ʹ��
 *
 * �� GPIO��DMA��INT �ȡ����ȷ��Ӧ�ó���ʹ����Щ��Դ�����Խ���Ӧ�ĺ�ֵ�޸�Ϊ 0
 * ���������������������ܣ�����Ӧ��ֵ�޸�Ϊ 0����ЩĬ�ϳ�ʼ���ĵ�ʵ���豸
 *
 * @{
 */

/** \brief Ϊ 1������ʱ�����ʱ�ӳ�ʼ�� */
#define AM_CFG_CLK_ENABLE                1

/** \brief Ϊ 1������ʱ����� GPIO ��ʼ�� */
#define AM_CFG_GPIO_ENABLE               1

/** \brief Ϊ 1������ʱ����� INT ��ʼ�� */
#define AM_CFG_INT_ENABLE                1

/** \brief Ϊ 1������ʱ����� DMA ��ʼ�� */
#define AM_CFG_DMA_ENABLE                1

/** 
 * @}
 */

/**
 * \name ʹ��һЩϵͳ����
 * @{
 */

/** \brief �Ƿ�ʹ�� NVRAM ���� */
#define AM_CFG_NVRAM_ENABLE              1

/** \brief �Ƿ�ʹ�ܰ���ϵͳ */
#define AM_CFG_KEY_ENABLE                1

/** \brief �Ƿ�ʹ�� isr defer ��� */
#define AM_CFG_ISR_DEFER_ENABLE          1

/** 
 * @}
 */

/**
 * \name �弶��ʼ������
 *
 * Ĭ�Ͽ���ʹ�ð��ϵ�һЩ��Դ���� LED���������ȣ������ʹ�ã�Ӧ��ֹ��Ӧ�ĺ�
 * @{
 */

/**
 * \brief ���Ϊ 1�����ʼ����ʱ����
 *
 * ��ʼ�������ʹ�� am_mdelay() �� am_udelay() ��ʱ����
 *
 * \note Ĭ�ϵ���ʱ������ am_delay.c �ļ�ʵ�֣������ر����󣬿������и���Ϊ����
 *       ʵ�ַ�ʽ
 */
#define AM_CFG_DELAY_ENABLE              1

/**
 * \brief ���Ϊ 1�����ʼ�� LED ����ع��ܣ�����Ĭ�������� LED
 *
 * ID: 0 --- PIO0_8 ����Ҫ�̽�����ñ J9��
 * ID: 1 --- PIO0_9 ����Ҫ�̽�����ñ J10��
 */
#define AM_CFG_LED_ENABLE                1

/**
 * \brief ���Ϊ 1�����ʼ�����ذ���
 *
 * Ĭ�ϼ�ֵΪ KEY_KP0��ʹ��ʱ��Ҫ�̽�����ñ J14 �� KEY �� PIO0_1������������������
 */
#define AM_CFG_KEY_GPIO_ENABLE           1

/**
 * \brief ���Ϊ 1�����ʼ������������ع���
 *
 * Ĭ��ʹ�� SCT_OUT1 (PIO0_2) ��� PWM ����Ҫ�̽�����ñ J7��
 */
#define AM_CFG_BUZZER_ENABLE             1

/**
 * \brief ���Ϊ 1�����ʼ��ϵͳ�δ�
 */
#define AM_CFG_SYSTEM_TICK_ENABLE        1

/**
 * \brief ���Ϊ 1�����ʼ�������ʱ��
 *
 * �����ʱ��Ĭ��ʹ�� MRT ��ʱ��
 * �����ʱ����ʹ����� am_softimer.h
 */
#define AM_CFG_SOFTIMER_ENABLE           1

/**
 * \brief ���Ϊ 1�����ʼ�����ڵ�����������Դ���Ĭ��Ϊ USART0
 *
 * USART0 �� TXD ����Ĭ��Ϊ PIO0_4 ֻ��Ҫ�� PIO0_4 ���ӵ�����ģ����������ţ�
 * ���ɿ��� AM_DBG_INFO() ��ӡ�ĵ�����Ϣ
 */
#define AM_CFG_DEBUG_ENABLE              1

/**
 * \brief ���Ϊ 1����ϵͳ���Զ������׼��
 *
 * ��ϵͳ�����׼����û��ſ�ʹ�� printf()��malloc()��free() �ȱ�׼�⺯��
 *
 * \note ʹ�ñ�׼��ʱ�����ķ�ϵͳ����� FLASH �� RAM ��Դ���û�Ӧ����ʹ��
 */
#define AM_CFG_STDLIB_ENABLE             1

/** 
 * @} 
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_PRJ_CONFIG_H */

/* end of file */
