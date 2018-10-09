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
 * \brief DMA Ӳ���������̣�ͨ��������ӿ�ʵ��
 *
 * - �������裺
 *   1. �� PIO0_17 �� PIO0_18 �̽ӣ�
 *   2. �۲촮�������Ϣ����������� "Press any key to finish level test!" ��
 *      ͨ���������������ַ��Լ������ԣ�
 *   3. �۲촮�������Ϣ����������� "Enter the trigger count to make burst!" ��
 *      ͨ���������ַ����ķ�ʽ����������Ĵ�����ÿ�δ������� 8 �ֽڵ����ݣ�
 *   4. �۲촮�������Ϣ����������� "Press any key to finish edge test!" ��ͨ��
 *      �������������ַ��Լ������ԣ�
 *   5. �۲촮�������Ϣ����������� "Enter any key make a burst!" ��ͨ��������
 *      �������ַ��Լ������ԡ��ظ��˹��� 6 �Ρ�
 *
 * - ʵ������
 *   1. DMA ͨ�� 0 ��������Ϊ�ж������ƽ������û��Ӳ�����������£����ݲ������ͣ�
 *   2. DMA ͨ�� 0 ��������Ϊ�ж�������ش�����ÿ��Ӳ�����������СΪ���õ�ͻ�����ȣ�
 *   3. DMA ͨ�� 0 ��������Ϊ�ж�������ش�����Ŀ���ַ���ƣ�ÿ��Ӳ��������
 *      ֻ������ͻ����С�ĵ�ַ��Χ�ڴ������ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_drv_dma_hwtrigger_burst.c src_am824_drv_dma_hwtrigger_burst
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem,modified
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_drv_dma_hwtrigger_burst
 * \copydoc demo_am824_drv_dma_hwtrigger_burst.c
 */

/** [src_am824_drv_dma_hwtrigger_burst] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "demo_nxp_entries.h"

#define __GET_CHAR(ch) \
            amhw_lpc_usart_poll_receive(AMHW_LPC82X_USART0, (&ch), 1);

#define __GPIO_PIN     PIO0_17          /**< \brief �����ж��źŵ����� */
#define __INT_PIN      PIO0_18          /**< \brief ��Ϊ�ж� 0 ��������� */


/**
 * \brief ��ʼ���жϲ����ͼ������
 */
am_local void __pin_init()
{

    /* ���ڲ����ж��ź� */
    am_gpio_pin_cfg(__GPIO_PIN, AM_GPIO_PULLUP | AM_GPIO_OUTPUT_INIT_HIGH);

    /* �ж���������Ϊ���� */
    am_gpio_pin_cfg(__INT_PIN, AM_GPIO_PULLUP | AM_GPIO_INPUT);

    /* �ж� 0 ����ѡ�� */
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_0, __INT_PIN);
}

/**
 * \brief �������
 */
void demo_am824_core_drv_dma_hwtrigger_burst_entry (void)
{

    /* ������������ */
    __pin_init();
  
    demo_lpc824_drv_dma_hwtrigger_burst_entry(DMA_CHAN_0, __GPIO_PIN);
}
/** [src_am824_drv_dma_hwtrigger_burst] */

/* end of file */
