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
 * \brief AM_KL26 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-13  mkr, first implementation.
 * \endinternal
 */

#ifndef __AM_KL26_H
#define __AM_KL26_H

#ifdef __cplusplus
extern "C" {
#endif


/** \brief оƬ���Ŷ��� */
#include "../kl26/kl26_pin.h"

/** \brief оƬ�жϱ�Ŷ��� */
#include "../kl26/kl26_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "../kl26/kl26_regbase.h"

/** \brief оƬ����ӳ�� */
#include "../kl26/kl26_periph_map.h"

/** \brief ʱ��ID���� */
#include "../kl26/kl26_clk.h"

/** \brief DMAͨ������������ */
#include "../kl26/kl26_dmamux_chan.h"

/**
 * \name Cortex-M0+ �˴���������������
 * @{
 */
#ifndef AM_CORTEX_M0
#define AM_CORTEX_M0
#endif

#ifdef AM_CORTEX_M0

#define __MPU_PRESENT           0  /**< \brief M0+����MPU                  */
#define __NVIC_PRIO_BITS        2  /**< \brief M0+��Ϊ2                    */
#define __Vendor_SysTickConfig  0  /**< \brief ����Ϊ1 ��������SysTick     */
#define __VTOR_PRESENT          1  /**< \brief ���Ϊ1���������ж�������   */

#include "core_cm0plus.h"

#endif
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_KL26_H */

/* end of file */
