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
 * \brief ISR DEFER �弶֧��
 *
 * Ϊ�������ж��д�����ڷ��غ�ʱ������Ӱ��ϵͳʵʱ�ԣ��������ж���Ҫ����������Ƴ�
 * �ӳ������д������ am_isr_defer.h
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-23  tee, first implementation
 * \endinternal
 */

#ifndef __AM_BSP_ISR_DEFER_H
#define __AM_BSP_ISR_DEFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_isr_defer.h"

/**
 * \brief �����ж��ӳ�ģ��ʹ�õ����ȼ���ĿΪ32
 *
 * ֻ��Ҫʹ�øú궨��һ�Σ�job����Ч���ȼ���Ϊ��0 ~ 31
 *
 */
#define AM_BSP_ISR_DEFER_PRIORITY_NUM     32

/**
 * \brief ISR DEFER �弶��ʼ�������ж��ӳ�������� PENDSV�� ����
 */
void am_bsp_isr_defer_init (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_BSP_NEWLIB_H */

/* end of file */
