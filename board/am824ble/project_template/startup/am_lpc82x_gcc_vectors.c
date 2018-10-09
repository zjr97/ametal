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
 * \brief �ж�������
 *
 * \internal
 * \par modification history
 * - 1.01 17-12-11  pea, amend annotation
 * - 1.00 11-04-09  mifi, first implementation
 * \endinternal
 */

/***************************************************************************
  �ⲿ��������
***************************************************************************/
extern unsigned long _estack;

/***************************************************************************
  �ⲿ��������
***************************************************************************/
extern void am_exc_eint_handler (void);

/***************************************************************************
  ���غ�������
***************************************************************************/
void ResetHandler(void);

void NMI_Handler (void) __attribute__((weak));
void HardFault_Handler (void) __attribute__((weak));
void MemManage_Handler (void) __attribute__((weak));
void BusFault_Handler (void) __attribute__((weak));
void UsageFault_Handler (void) __attribute__((weak));
void SVC_Handler (void) __attribute__((weak));
void DebugMon_Handler (void) __attribute__((weak));
void PendSV_Handler (void) __attribute__((weak));
void SysTick_Handler (void) __attribute__((weak));
void am_exc_eint_handler (void) __attribute__((weak));

/***************************************************************************
  ����ȫ�ֱ�������
***************************************************************************/

/** \brief �ж������� */
__attribute__ ((section(".vectors"), used))
void (* const gVectors[])(void) =
{
    (void (*)(void))((unsigned long)&_estack),
    ResetHandler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, 0, 0, 0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,

    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler,
    am_exc_eint_handler
};

/***************************************************************************
  ���غ�������
***************************************************************************/
void NMI_Handler (void) { while (1); }
void HardFault_Handler (void) { while (1); }
void MemManage_Handler (void) { while (1); }
void BusFault_Handler (void) { while (1); }
void UsageFault_Handler (void) { while (1); }
void SVC_Handler (void) { while (1); }
void DebugMon_Handler (void) { while (1); }
void PendSV_Handler (void) { while (1); }
void SysTick_Handler (void) { while (1); }

void am_exc_eint_handler (void) { while (1); }

/* end of file */
