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
 * \brief �ڴ浽�ڴ�� DMA �������̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��� DMA ����ɹ���LED0 ������
 *   2. ��� DMA ����ʧ�ܣ�LED0 ��˸��
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ơ�
 *
 * \par Դ����
 * \snippet demo_am824_drv_dma_m2m.c src_am824_drv_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem,modified
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_drv_dma_m2m
 * \copydoc demo_am824_drv_dma_m2m.c
 */

/** [src_am824_drv_dma_m2m] */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_nxp_entries.h"

#define __TEST_COUNT  256                    /**< \brief �������ݵĴ�С */

am_local uint8_t __g_buf_src[__TEST_COUNT];  /**< \brief Դ�����ݻ����� */

/**
 * \brief �������
 */
void demo_am824_core_drv_dma_m2m_entry (void)
{
    int i = 0;

    am_kprintf("demo am_824 dma drv m2m!\r\n");

    /* ���췢������ */
    for (i = 0; i < __TEST_COUNT; i++) {
        __g_buf_src[i] = i;
        //__g_buf_dst[i] = 0;
    }
  
    am_led_off(LED0);
    demo_lpc824_drv_dma_m2m_entry(__g_buf_src, __TEST_COUNT);
    
}
/** [src_am824_drv_dma_m2m] */

/* end of file */
