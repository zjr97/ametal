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
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. DMA ����ɹ�����ӡ "transfer success"��
 *   2. DMA ���������ӡ "transfer failure"��
 *
 * \par Դ����
 * \snippet demo_zlg_drv_dma_m2m.c src_zlg_drv_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-11  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_drv_dma_m2m
 * \copydoc demo_zlg_drv_dma_m2m.c
 */

/** [src_zlg_drv_dma_m2m] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
//#include "am_zlg116.h"
#include "am_zlg_dma.h"
#include "hw/amhw_zlg_dma.h"

static uint8_t g_buf_src[50];           /**< \brief Դ�����ݻ����� */
static uint8_t g_buf_dst[50];           /**< \brief Ŀ������ݻ����� */

static volatile am_bool_t g_trans_done; /**< \brief ������ɱ�־ */

static amhw_zlg_dma_xfer_desc_t g_desc; /**< \brief ������ */

/**
 * \brief DMA �жϷ������
 */
static void dma_isr (void *p_arg , uint32_t flag)
{
    if (flag == AM_ZLG_DMA_INT_NORMAL) {
        g_trans_done = AM_TRUE;
    }
}

/**
 * \brief DMA M2M ģʽ���Գ���
 *
 * \retval  AM_OK    ����ɹ�
 * \retval  AM_ERROR ����ʧ��
 */
static int dma_m2m_test (uint8_t dma_chan)
{
    uint32_t flags;
    uint32_t i;

    for (i = 0; i < 50; i++) {
        g_buf_src[i] = i;
        g_buf_dst[i] = 0;
    }

    /* ���� DMA �жϷ����� */
    am_zlg_dma_isr_connect(dma_chan, dma_isr, (void *)0);

    /* DMA �������� */
    flags = AMHW_ZLG_DMA_CHAN_PRIORITY_HIGH         |  /* �ж����ȼ� �� */
            AMHW_ZLG_DMA_CHAN_MEM_SIZE_8BIT         |  /* �ڴ����ݿ�� 1 �ֽ� */
            AMHW_ZLG_DMA_CHAN_PER_SIZE_8BIT         |  /* �������ݿ�� 1 �ֽ� */
            AMHW_ZLG_DMA_CHAN_MEM_ADD_INC_ENABLE    |  /* �ڴ��ַ���� */
            AMHW_ZLG_DMA_CHAN_PER_ADD_INC_ENABLE    |  /* �����ַ���� */
            AMHW_ZLG_DMA_CHAN_CIRCULAR_MODE_DISABLE ;  /* �ر�ѭ��ģʽ */


    /* ����ͨ�������� */
    am_zlg_dma_xfer_desc_build(&g_desc,                /* ͨ�������� */
                                (uint32_t)(g_buf_src), /* Դ�����ݻ����� */
                                (uint32_t)(g_buf_dst), /* Ŀ������ݻ����� */
                                50,                    /* �����ֽ��� */
                                flags);                /* �������� */

    /* ���� DMA ���䣬���Ͽ�ʼ���� */
    if (am_zlg_dma_xfer_desc_chan_cfg(&g_desc,
                                       AMHW_ZLG_DMA_MER_TO_MER, /* �ڴ浽�ڴ� */
                                       dma_chan) == AM_ERROR) {
        return AM_ERROR;
    } else {
        am_zlg_dma_chan_start(dma_chan);
    }

    while(g_trans_done == AM_FALSE); /* �ȴ�������� */

    for (i = 0; i < 50; i++) {
        if (g_buf_src[i] != g_buf_dst[i]) {
            return AM_ERROR;
        }
    }
    return AM_OK;
}

/**
 * \brief �������
 */
void demo_zlg_drv_dma_m2m_entry (uint32_t dma_chan)
{
    if (dma_m2m_test(dma_chan) == AM_OK){
        am_kprintf("transfer success\n");
    } else {
        am_kprintf("transfer failure\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg_drv_dma_m2m] */

/* end of file */
