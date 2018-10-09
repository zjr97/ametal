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
 * \brief DMA�ڴ浽�ڴ����̣���DMA������ʵ��
 *
 * - ʵ������
 *   1. ����ɹ��򴮿ڴ�ӡ"transfer success"�������ӡ"transfer failure"��
 *
 * \par Դ����
 * \snippet demo_kl26_dr_dma_m2m.c src_kl26_dr_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-18 mkr , first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_dma_m2m
 * \copydoc demo_kl26_dr_dma_m2m.c
 */

/** [src_kl26_dr_dma_m2m] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_kl26_dma.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

am_bool_t volatile __g_trans_done;           /**< \brief ������ɱ�־     */

/**
 * \brief ��ƹ�Ҵ���ʱ���������ĵ�ַ��Ҫ��16�ֽڶ��롣
 */
amhw_kl26_dma_xfer_desc_t g_desc;

/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� am_kl26_dma_isr_connect() �������ݡ�
 * \param[in] flag  : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AM_KL26_DMA_INT_ERROR) �� (#AM_KL26_DMA_INT_NORMAL)��

 * \return    �ޡ�
 */
static void dma_isr (void *p_arg , uint8_t flag)
{
    int flag_chan  = (int)p_arg;
    if (flag == AM_KL26_DMA_INT_NORMAL) {

        /* DMA������� */
        switch(flag_chan) {

        case DMA_CHAN_0:
            __g_trans_done = AM_TRUE;
            break;

        case DMA_CHAN_1:
            break;

        case DMA_CHAN_2:
            break;

        case DMA_CHAN_3:
            break;

        default:
            break;
        }
    } else  {
        // �û��Զ���ִ�д���
        switch(flag_chan) {

        case DMA_CHAN_0:
            break;

        case DMA_CHAN_1:
            break;

        case DMA_CHAN_2:
            break;

        case DMA_CHAN_3:
            break;

        default:
            break;
        }
    }
}

/**
 * \brief DMA m2mģʽ���Գ���
 *
 * \retval  AM_OK     : ����ɹ�
 * \retval  AM_ERROR  : ����ʧ��
 */
static int dma_m2m_test (void)
{
    uint32_t flags;
    uint32_t i;
    uint8_t buf_src[50];          /**< \brief Դ�����ݻ�����   */
    uint8_t buf_dst[50];          /**< \brief Ŀ������ݻ����� */

    am_kl26_dma_chan_cfg(DMA_CHAN_0,
                         KL26_DMA_TRIGGER_DISABLE |  /**< \brief DMA����ģʽ  */
                         DMA_REQUEST_MUX0_ALWAYSON0);     /**< \brief ����Դ                */

    for (i = 0; i < 50; i++) {
        buf_src[i] = i;
        buf_dst[i] = 0;
    }

    /* ����DMA�жϷ����� */
    am_kl26_dma_isr_connect(DMA_CHAN_0, dma_isr, (void *)0);

    /* DMA�������� */
    flags = KL26_DMA_DCR_PER_REQUEST_DISABLE    |  /* ��������Դ����   */
            KL26_DMA_DCR_CYCLE_TRANSFERS        |  /* ѭ������         */
            KL26_DMA_DCR_AUTO_ALIGN_DISABLE     |  /* �Զ��������     */
            KL26_DMA_DCR_SOURCE_SIZE_8_BIT      |  /* Դ��ַ1�ֽ�      */
            KL26_DMA_DCR_DESTINATION_SIZE_8_BIT |  /* Ŀ�ĵ�ַ1�ֽ�д��*/
            KL26_DMA_DCR_REQUEST_AFFECTED       |  /* ������Ӱ��       */
            KL26_DMA_DCR_NO_LINKING             |  /* ��ͨ������       */
            KL26_DMA_DCR_INTERRUTP_ENABLE       |  /* DMA�ж�ʹ��      */
            KL26_DMA_DCR_START_ENABLE    ;         /* DMA��ʼ����ʹ��  */

    /* ����ͨ�������� */
    am_kl26_dma_xfer_desc_build(&g_desc,               /* ͨ��������       */
                                (uint32_t)(buf_src),   /* Դ�����ݻ�����   */
                                (uint32_t)(buf_dst),   /* Ŀ������ݻ����� */
                                50,                    /* �����ֽ���       */
                                flags);                /* ��������         */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_kl26_dma_chan_start(&g_desc,
                               KL26_DMA_MER_TO_MER,  /* �ڴ浽�ڴ�   */
                               DMA_CHAN_0) == AM_ERROR) {
        return AM_ERROR;
    }

    while(__g_trans_done == AM_FALSE);                   /* �ȴ��������  */

    for (i = 0; i < 50; i++) {
        if (buf_src[i] != buf_dst[i]) {
            return AM_ERROR;
        }
    }
    return AM_OK;
}

/**
 * \brief DMA�ڴ浽�ڴ�
 * \return ��
 */
void demo_kl26_dr_dma_m2m_entry (void)
{

    if (dma_m2m_test() == AM_OK){
        am_kprintf("transfer success\n");
    } else {
        am_kprintf("transfer failure\n");
    }

    while (1){

    }
}

/** [src_kl26_dr_dma_m2m] */

/* end of file */

