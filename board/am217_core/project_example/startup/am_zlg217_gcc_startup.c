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
    uint32_t *pSrc;
    uint32_t *pDest;

    /*
    * Call the SystemInit code from CMSIS interface if available.
    * SystemInit is a week function which can be override
    * by an external function.
    */
    SystemInit();

    /*
    * Set the "Vector Table Offset Register". From the ARM
    * documentation, we got the following information:
    *
    * Use the Vector Table Offset Register to determine:
    *  - if the vector table is in RAM or code memory
    *  - the vector table offset.
    */
    *((uint32_t*)0xE000ED08) = (uint32_t)&_stext;

    /*
    * Copy the initialized data of the ".data" segment
    * from the flash to the are in the ram.
    */
    pSrc  = &_etext;
    pDest = &_sdata;
    while(pDest < &_edata) {
        *pDest++ = *pSrc++;
    }

    /*
    * Clear the ".bss" segment.
    */
    pDest = &_sbss;
    while(pDest < &_ebss) {
        *pDest++ = 0;
    }

    /*
    * And now the main function can be called.
    * Scotty, energie...
    */
    main();

    /*
    * In case there are problems with the
    * "warp drive", stop here.
    */
    while(1) {};
}

/* end of file */
