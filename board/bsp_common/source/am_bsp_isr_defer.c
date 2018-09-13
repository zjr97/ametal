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
 * \internal
 * \par modification history
 * - 1.00 12-10-23  orz, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_isr_defer.h"
#include "am_bsp_isr_defer.h"

/*******************************************************************************
  �ڲ��궨��
*******************************************************************************/

/** \brief �жϿ��ƺ�״̬�Ĵ���,0xE000ED04�����ڴ���PendSV�ж� */
#define __ICSR_ADDRESS  0xE000ED04

/** \brief ϵͳ�쳣���ȼ����üĴ�����ַ 0xE000ED20 */
#define __SHP2_ADDRESS  0xE000ED20

/*******************************************************************************
  �ڲ�����
*******************************************************************************/
static void __isr_defer_trigger (void *p_arg)
{
    /* ����PendSV�ж� */
    *(volatile unsigned int *)__ICSR_ADDRESS |= 0x10000000;
}

/*******************************************************************************
  ���жϴ�����
*******************************************************************************/
void PendSV_Handler (void)
{
    am_isr_defer_job_process();
}

/*******************************************************************************
  �������ȼ���Ŀ
*******************************************************************************/
AM_ISR_DEFER_PRIORITY_NUM_DEF(AM_BSP_ISR_DEFER_PRIORITY_NUM);

/*******************************************************************************
  ��������
*******************************************************************************/
void am_bsp_isr_defer_init (void)
{

    /* �� PendSV �����ȼ�����Ϊ��� */
    *(volatile unsigned int *)__SHP2_ADDRESS  |= (0xC0ul << 16);

    am_isr_defer_init(__isr_defer_trigger, NULL);
}

/* end of file */
