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
 * \brief DMA ƹ�Ҵ������̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��� DMA ����ɹ���LED0 ������
 *   2. ��� DMA ����ʧ�ܣ�LED0 ��˸��
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ơ�
 *
 * \par Դ����
 * \snippet demo_am824_drv_dma_ping_pong.c src_am824_drv_dma_ping_pong
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem,modified
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_drv_dma_ping_pong
 * \copydoc demo_am824_drv_dma_ping_pong.c
 */

/** [src_am824_drv_dma_ping_pong] */
#include "ametal.h"
#include "am_led.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "lpc82x_dma_chan.h"
#include "demo_nxp_entries.h"

#define  BUF_LEN              16         /**< \brief buffer ���ݳ��� */

am_local uint8_t __g_buf_src[BUF_LEN];   /**< \brief Դ�����ݻ����� */


/**
 * \brief �������
 */
void demo_am824_core_drv_dma_ping_pong_entry (void)
{
    int i = 0;
    
    am_kprintf("demo am824 drv dma ping pong!\r\n");

    /* �ر� LED0 */
    am_led_off(LED0);
  
    for (i = 0; i < BUF_LEN; i++) {
        __g_buf_src[i] = i;
    }

    demo_lpc824_drv_dma_ping_pong_entry(DMA_CHAN_0, __g_buf_src, BUF_LEN);
}
/** [src_am824_drv_dma_ping_pong] */

/* end of file */
