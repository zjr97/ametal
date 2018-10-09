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
 * \snippet demo_lpc824_drv_dma_ping_pong.c src_lpc824_drv_dma_ping_pong
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem,modified
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_drv_dma_ping_pong
 * \copydoc demo_lpc824_drv_dma_ping_pong.c
 */

/** [src_lpc824_drv_dma_ping_pong] */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_dma.h"
#include "lpc82x_dma_chan.h"

/** \brief ������������ʹ��ƹ�Ҵ���ʱ��������������16�ֽڶ��� */
am_local __attribute__((aligned(16)))  am_lpc82x_dma_xfer_desc_t __g_desc[2];

am_local volatile am_bool_t __g_trans_a_done;  /**< \brief ������ɱ�־ */
am_local volatile am_bool_t __g_trans_b_done;  /**< \brief ������ɱ�־ */
am_local volatile am_bool_t __g_trans_err;     /**< \brief ��������־ */

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg �û��Զ������
 * \param[in] stat  DMA �������״̬��־���ò����Ŀ���ȡֵ��
 *                      AM_LPC82X_DMA_STAT_INTA   A �жϷ���
 *                      AM_LPC82X_DMA_STAT_INTB   B �жϷ���
 *                      AM_LPC82X_DMA_STAT_INTERR ������
 *
 * \return ��
 */
am_local void __dma_ping_pong_isr (void *p_arg, int stat)
{
    __g_trans_err = AM_FALSE;

    if (stat & AM_LPC82X_DMA_STAT_INTERR) {
        __g_trans_err = AM_TRUE;
    }

    if (stat & AM_LPC82X_DMA_STAT_INTA) {
        __g_trans_a_done = AM_TRUE;
    }
    if (stat & AM_LPC82X_DMA_STAT_INTB) {
        __g_trans_b_done = AM_TRUE;
    }
}

/**
 * \brief DMA ���䣬ƹ��ģʽ
 */
void demo_lpc824_drv_dma_ping_pong_entry (uint8_t  chan, 
                                          uint8_t *p_src, 
                                          int      len)
{
    int          i      = 0;
    uint32_t     flags1 = 0;
    uint32_t     flags2 = 0;
    
    /* ����ping-pong���ݻ������ռ� */
    uint8_t *p_dsta = calloc(len, sizeof(uint8_t));
    uint8_t *p_dstb = calloc(len, sizeof(uint8_t));
    
    am_lpc82x_dma_controller_t *p_ctr  = NULL;

    p_ctr = am_lpc82x_dma_controller_get(chan, DMA_CHAN_OPT_PRIO_1);

    if (p_ctr == NULL) {
        AM_DBG_INFO("Geting a Controller Faild !\r\n");
        AM_FOREVER {};
    }

    /* DMA �������� */
    flags1 = AM_LPC82X_DMA_XFER_VALID           | /* ��ǰͨ����������Ч */
             AM_LPC82X_DMA_XFER_RELOAD          | /* �����������ͨ�������� */
             AM_LPC82X_DMA_XFER_SWTRIG          | /* ������� */
             AM_LPC82X_DMA_XFER_WIDTH_8BIT      | /* �������ݿ�ȣ�8 bit */
             AM_LPC82X_DMA_XFER_SRCINC_1X       | /* Դ��ַ�� 1 �����ݿ�ȵ��� */
             AM_LPC82X_DMA_XFER_DSTINC_1X       | /* Ŀ���ַ�� 1 �����ݿ�ȵ��� */
             AM_LPC82X_DMA_XFER_SETINTA;          /* ʹ���ж� A */

    /* DMA �������� */
    flags2 = AM_LPC82X_DMA_XFER_VALID           | /* ��ǰͨ����������Ч */
             AM_LPC82X_DMA_XFER_RELOAD          | /* �����������ͨ�������� */
             AM_LPC82X_DMA_XFER_CLRTRIG         | /* ���������־ */
             AM_LPC82X_DMA_XFER_WIDTH_8BIT      | /* �������ݿ�ȣ�8 bit */
             AM_LPC82X_DMA_XFER_SRCINC_1X       | /* Դ��ַ�� 1 �����ݿ�ȵ��� */
             AM_LPC82X_DMA_XFER_DSTINC_1X       | /* Ŀ���ַ�� 1 �����ݿ�ȵ��� */
             AM_LPC82X_DMA_XFER_SETINTB;          /* ʹ���ж� B */

    /* ����ͨ�������� A */
    am_lpc82x_dma_xfer_desc_build(
       &__g_desc[0],            /* A ������������ */
        (uint32_t)p_src,        /* Դ�����ݻ����� */
        (uint32_t)p_dsta,       /* A ��Ŀ��˻�������ַ */
        len,                    /* �����ֽ��� */
        flags1);                /* �������� */

    /* ����ͨ��������B */
    am_lpc82x_dma_xfer_desc_build(
       &__g_desc[1],            /* B ������������ */
        (uint32_t)p_src,        /* Դ�����ݻ����� */
        (uint32_t)p_dstb,       /* B ��Ŀ��˻�������ַ */
        len,                    /* �����ֽ��� */
        flags2);                /* �������� */

    /* �������������� */
    am_lpc82x_dma_xfer_desc_link(&__g_desc[1], &__g_desc[0]);
    am_lpc82x_dma_xfer_desc_link(&__g_desc[0], &__g_desc[1]);

    /* ���� DMA ���䣬���Ͽ�ʼ���� */
    am_lpc82x_dma_xfer_desc_startup(p_ctr,
                                   &__g_desc[0],
                                    __dma_ping_pong_isr,
                                    (void*)0);

    am_mdelay(1);

    /* �ȴ�������� */
    while ((__g_trans_a_done == AM_FALSE) || (__g_trans_b_done == AM_FALSE));

    /* ��ֹ���������ݴ��� */
    am_lpc82x_dma_controller_abort(p_ctr);

    /* ����ʹ�øÿ�����ʱ��Ӧ�ͷſ����� */
    am_lpc82x_dma_controller_release(p_ctr);

    /* ��ʵ�������� */
    for (i = 0; i < len; i++) {
        if (p_src[i] != p_dsta[i]) {
            __g_trans_err = AM_TRUE;
                      
            am_kprintf("%d", i);  
                    
            break;
        }
    }
    for (i = 0; i < len; i++) {
        if (p_src[i] != p_dstb[i]) {
            __g_trans_err = AM_TRUE;
            break;
        }
    }

    if (__g_trans_err == AM_TRUE) {

         /* �ͷſռ� */
        free(p_dsta);
        free(p_dstb);
        
        AM_FOREVER {
            am_led_on(LED0);
            am_mdelay(200);
            am_led_off(LED0);
            am_mdelay(200);
        }
    } else {
        am_led_on(LED0);
    }
        
        /* �ͷſռ� */
    free(p_dsta);
    free(p_dstb);
        
    while(1) {
        ;
    }
}

/** [src_lpc824_drv_dma_ping_pong] */

/* end of file */
