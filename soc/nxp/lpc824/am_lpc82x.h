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
 * \brief LPC82X оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-07  cyl, first implementation.
 * \endinternal
 */
 
#ifndef __AM_LPC82X_H
#define __AM_LPC82X_H

#ifdef __cplusplus
extern "C" {    
#endif
    

/** \brief оƬ���Ŷ��� */ 
#include "lpc82x_pin.h"    
    
/** \brief оƬ�жϱ�Ŷ��� */    
#include "lpc82x_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "lpc82x_regbase.h"

/** \brief оƬ����ӳ�� */
#include "lpc82x_periph_map.h"

/** \brief ʱ��ID���� */
#include "lpc82x_clk.h"

/** \brief DMAͨ������������ */
#include "lpc82x_dma_chan.h"


/**
 * \name Cortex-M0+ �ں˴���������������
 * @{
 */
#ifndef AM_CORTEX_M0

#define AM_CORTEX_M0             1

#endif

#if defined AM_CORTEX_M0

#define __MPU_PRESENT            0  /**< \brief M0+����MPU              */
#define __NVIC_PRIO_BITS         2  /**< \brief M0+��Ϊ2                */
#define __Vendor_SysTickConfig   0  /**< \brief ����Ϊ1 ��������SysTick  */

#include "core_cm0plus.h"

#endif

/** @} */
    
#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC82X_H */

/* end of file */
