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
 * \brief ���������ļ�������ϵͳ���弶��Ӳ������
 * \sa am_prj_config.h
 * \internal
 * \par Modification history
 * - 1.00 16-09-23  nwt, first implementation.
 * \endinternal
 */
 
#ifndef __AM_PRJ_CONFIG_H
#define __AM_PRJ_CONFIG_H

#include "ametal.h"

/**
 * \addtogroup am_if_prj_config
 * \copydoc am_prj_config.h
 * @{
 */

/**
 * \brief һЩȫ��ʹ�õĵ�ʵ���豸��Ĭ����ϵͳ����ʱ��ʼ�����Ա�ȫ��ʹ��
 * 
 *  �� GPIO��DMA ��INT �ȡ����ȷ��Ӧ�ó���ʹ����Щ��Դ�����Խ���Ӧ�ĺ�ֵ�޸�Ϊ0��
 *  ���������������������ܣ�����Ӧ��ֵ�޸�Ϊ0����ЩĬ�ϳ�ʼ���ĵ�ʵ���豸��
 *
 * @{
 */
 
/** \brief Ϊ1������ʱ�����ʱ�ӳ�ʼ��  */
#define AM_CFG_CLK_ENABLE                1
 
/** \brief Ϊ1����ʼ�� GPIO ����ع���  */
#define AM_CFG_GPIO_ENABLE               1

/** \brief Ϊ1����ʼ�� INT ��ع���     */
#define AM_CFG_INT_ENABLE                1

/** \brief Ϊ1����ʼ�� DMA ��ع���     */
#define AM_CFG_DMA_ENABLE                1

/** \brief Ϊ1����ʼ�� PMU��ع���     */
#define AM_CFG_PMU_ENABLE                1

/** \brief Ϊ1��ʹ��WDT���Ź���ع���     */
#define AM_CFG_SIM_COP                   0

/** @} */


/**
 * \name ʹ��һЩϵͳ����
 * @{
 */

/* ʹ�� NVRAM ���� */
#define AM_CFG_NVRAM_ENABLE              1

/* ʹ��  MTD ����  */
#define AM_CFG_MTD_ENABLE                1

/** \brief �Ƿ�ʹ�ð���ϵͳ */
#define AM_CFG_KEY_ENABLE                1

/** \brief �Ƿ�ʹ�� isr defer ��� */
#define AM_CFG_ISR_DEFER_ENABLE          1

/** @} */



/**
 * \name �弶��ʼ������
 *
 * Ĭ�Ͽ���ʹ�ð��ϵ�һЩ��Դ���� LED���������ȣ������ʹ�ã�Ӧ��ֹ��Ӧ�ĺ�
 *
 * @{
 */
 
/** 
 * \brief ���Ϊ1�����ʼ����ʱ����
 *
 * ��ʼ�������ʹ��am_mdelay() �� am_udelay()��ʱ����
 *
 * ע�⣬Ĭ�ϵ���ʱ������ am_delay.c�ļ�ʵ�֣������ر����󣬿������и���Ϊ����ʵ�ַ�ʽ
 *
 */
#define AM_CFG_DELAY_ENABLE          1

/** 
 * \brief ���Ϊ1�����ʼ��led����ع��ܣ�����Ĭ��������LED
 */
#define AM_CFG_LED_ENABLE            1

/**
 * \brief ���Ϊ1�����ʼ�����ذ���
 * KEY_KP0 ��Ĭ�ϰ�����ţ� ��PIOE_24 ����Ҫ�̽�����ñ J14��PTE24��KEY�����������������ܣ�
 */
#define AM_CFG_KEY_GPIO_ENABLE       1

/** 
 * \brief ���Ϊ1�����ʼ��PWM��������������
 *
 * Ĭ��ʹ��TPM0_CH2 ��PIOC_3�����PWM ����Ҫ�̽�����ñ J7��
 */
#define AM_CFG_BUZZER_ENABLE         1

/**
 * \brief ���Ϊ1�����ʼ�������ʱ��
 * 
 * �����ʱ��Ĭ��ʹ�� TPM2��ʱ��
 * �����ʱ����ʹ����� am_softimer.h
 */
#define AM_CFG_SOFTIMER_ENABLE       1

/** \brief �����ʱ��ʹ�õ�TPM2ͨ��    */
#define AM_CFG_SOFTIMER_CHAN         0

/** 
 * \brief ���Ϊ1�����ʼ�����ڵ�����������Դ���Ĭ��ΪUART0
 *
 * UART0��TXD����Ĭ��Ϊ PIOA_2, ֻ��Ҫ��PIOA_2���ӵ�����ģ����������ţ�
 * ���ɿ��� AM_DBG_INFO() ��ӡ�ĵ�����Ϣ
 */
#define AM_CFG_DEBUG_ENABLE          1

/** @} */

/**
 * \brief �Ƿ�ʹ�ñ�׼�⣨ʹ�ñ�׼�⣩
 *
 * ��ʹ���˱�׼�⣬��ϵͳ���Զ��������׼�⣬�û�����ʹ�� printf() ��
 * malloc() ��free()�ȱ�׼�⺯����
 * ֵ��ע����ǣ�ʹ�ñ�׼��ʱ�����ķ�ϵͳ����� FLASH �� RAM ��Դ���û�
 * Ӧ����ʹ��
 */
#define AM_CFG_STDLIB_ENABLE         1

/**
 * \brief ���Ϊ1�����ʼ��ϵͳ�δ�
 */
#define AM_CFG_SYSTEM_TICK_ENABLE    1

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_PRJ_CONFIG_H */

/* end of file */
