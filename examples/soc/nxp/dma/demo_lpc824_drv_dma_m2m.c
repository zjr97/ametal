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
 * \snippet demo_lpc824_drv_dma_m2m.c src_lpc824_drv_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem,modified
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_drv_dma_m2m
 * \copydoc demo_lpc824_drv_dma_m2m.c
 */

/** [src_lpc824_drv_dma_m2m] */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"
#include "am_lpc82x_dma.h"

/**
 * \name �ڴ濽��״̬��־,�������� m2m_result_t �е� result ��Ա
 * \anchor grp_dam_m2m_result
 * @{
 */
#define __TRANS_OK      0
#define __TRANS_INIT    1
#define __TRANS_ERROR  -1
/**
 * @}
 */

/** \brief �ڴ濽����� */
typedef struct m2m_result {
    am_lpc82x_dma_controller_t *p_ctr;  /**< \brief ͨ�������� */
    volatile int                result; /**< \brief ������ */
} m2m_result_t;

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg �û��Զ������
 * \param[in] stat  DMA �������״̬��־���ò����Ŀ���ȡֵ��
 *                      AM_LPC82X_DMA_STAT_INTA    A �жϷ���
 *                      AM_LPC82X_DMA_STAT_INTB    B �жϷ���
 *                      AM_LPC82X_DMA_STAT_INTERR  ������
 *
 * \return ��
 */
am_local void __dma_m2m_isr (void *p_arg, int stat)
{
    m2m_result_t *p_reslut = (m2m_result_t*)p_arg;

    /* DAM ������� */
    if (stat & AM_LPC82X_DMA_STAT_INTERR) {
        p_reslut->result = __TRANS_ERROR;
    } else if (stat == AM_LPC82X_DMA_STAT_INTA) {
        p_reslut->result = __TRANS_OK;
    }

    /* �ͷſ����� */
    am_lpc82x_dma_controller_release(p_reslut->p_ctr);
}

/**
 * \brief DMA �ڴ濽��
 */
am_local int __dma_memory_copy (uint32_t      dst,
                                uint32_t      src,
                                uint16_t      nbytes,
                                m2m_result_t *p_result)
{
    uint8_t                     dma_chan = 0;
    am_lpc82x_dma_controller_t *p_ctr    = NULL;
    am_lpc82x_dma_transfer_t    transfer;

    /* ��ȡͨ�������� */
    do {
        p_ctr = am_lpc82x_dma_controller_get(dma_chan++, DMA_CHAN_OPT_PRIO_1);
    } while (p_ctr == NULL && dma_chan <= 17);

    if (p_ctr == NULL) {
        return AM_ERROR;
    }

    /* ���촫��ṹ�� */
    am_lpc82x_dma_transfer_build(
       &transfer,                           /* ����ṹ */
        src,                                /* Դ��ַ */
        dst,                                /* Ŀ���ַ */
        nbytes,                             /* �����С */
        AM_LPC82X_DMA_TRANS_WIDTH_8BIT  |   /* ������ */
        AM_LPC82X_DMA_TRANS_SRCINC_1X   |   /* Դ��ַ���� */
        AM_LPC82X_DMA_TRANS_DSTINC_1X);     /* Ŀ���ַ���� */

    /* �������� */
    p_result->p_ctr  = p_ctr;
    p_result->result = __TRANS_INIT;

    am_lpc82x_dma_transfer(p_ctr, &transfer, __dma_m2m_isr, (void*)p_result);

    return AM_OK;
}

void demo_lpc824_drv_dma_m2m_entry(uint8_t *p_src, int len)
{
    int i = 0;
    m2m_result_t trans_result;
  
    /* ����ռ� */
    uint8_t *p_dst = calloc(len, sizeof(uint8_t));

    
    
    /* �ڴ濽�� */
    __dma_memory_copy((uint32_t)p_dst,
                      (uint32_t)p_src,
                      len,
                     &trans_result);

    /* �ȴ�������� */
    while (trans_result.result == __TRANS_INIT) {};

    /* ����У�� */
    for (i = 0; i < len; i++) {

        /* ����ʧ�� */
        if (p_src[i] != p_dst[i]) {
            AM_FOREVER {
                am_led_on(LED0);
                am_mdelay(200);
                am_led_off(LED0);
                am_mdelay(200);
            }
        }
    }

    am_led_on(LED0);
    
    /* �ͷ��ڴ�ռ� */
    free(p_dst);
    AM_FOREVER {
        ; /* VOID */
    }
}

/** [src_lpc824_drv_dma_m2m] */

/* end of file */
