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
 * - 1.02 17-12-11  pea, amend annotation
 * - 1.01 11-04-29  mifi, call SystemInit, and set the Vector Table Offset
*                   before copy of data and bss segment
 * - 1.00 11-04-09  mifi, first implementationS
 * \endinternal
 */

#define __CRT_C__

#include <stdint.h>

/***************************************************************************
  �ⲿ��������
***************************************************************************/
extern unsigned long _stext;
extern unsigned long _etext;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

/***************************************************************************
  �ⲿ��������
***************************************************************************/
extern int main (void);

/***************************************************************************
  ���غ�������
***************************************************************************/
void SystemInit (void) __attribute__((weak));

/***************************************************************************
  ���غ�������
***************************************************************************/

/**
 * \brief SystemInit() �� CMSIS �ӿ�����Ҫ��һ�����������û�������������ʱ
 *        ��������������ﶨ��һ�� weak ����
 */
void SystemInit (void)
{
    ; /* VOID */
}

/**
 * \brief ��λ�жϴ���������ʼ�� C ���л����������ж�������.data �Ρ�.bss �Σ�
 *        ������ main() ����
 */
void ResetHandler (void)
{
    uint32_t *p_src;
    uint32_t *p_dest;

    SystemInit();

    /* �ж��������ض�λ */
    *((uint32_t*)0xE000ED08) = (uint32_t)&_stext;

    /* �� .text ���ж�ȡ���ݳ�ʼ�� .data �� */
    p_src  = &_etext;
    p_dest = &_sdata;
    while (p_dest < &_edata) {
        *p_dest++ = *p_src++;
    }

    /* ��ʼ�� .bss ��Ϊ 0 */
    p_dest = &_sbss;
    while (p_dest < &_ebss) {
        *p_dest++ = 0;
    }

    (void)main();

    /* ��������²�Ӧ�����е����� */
    while (1) {
        ; /* VOID */
    }
}

/* end of file */
