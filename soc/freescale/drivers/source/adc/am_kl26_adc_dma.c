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
 * \brief ADC_DMA implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  ari, first implementation.
 * \endinternal
 */
#include "am_kl26_dma.h"
#include "am_fsl_adc.h"
#include "am_adc.h"

/******************************************************************************/
static void __am_fsl_adc_dma_isr (void *p_arg , uint8_t flag);

/**
 * \brief DMA��������
 */
int am_fsl_adc_dma_tran_cfg (am_fsl_adc_dev_t *p_dev,
                             am_adc_buf_desc_t *p_desc)
{

    uint32_t flags  = 0;
    uint32_t length = 0;
    amhw_kl26_dma_xfer_desc_t    dma_desc;

    if( p_desc->p_buf == NULL) {
        return -AM_EINVAL;
    }

    /* DMA�������� */
    flags = KL26_DMA_DCR_PER_REQUEST_ENABLE      |  /* ��������Դʹ��    */
            KL26_DMA_DCR_SINGLE_TRANSFERS        |  /* ���δ���          */
            KL26_DMA_DCR_AUTO_ALIGN_DISABLE      |  /* �Զ��������      */
            KL26_DMA_DCR_REQUEST_AFFECTED        |  /* ������Ӱ��        */
            KL26_DMA_DCR_NO_LINKING              |  /* ��ͨ������        */
            KL26_DMA_DCR_INTERRUTP_ENABLE        |  /* DMA�ж�ʹ��       */
            KL26_DMA_DCR_START_DISABLE    ;         /* DMA��ʼ�������   */

    /* ����DMA�жϷ����� */
    am_kl26_dma_isr_connect(p_dev->p_devinfo->dma_chan, __am_fsl_adc_dma_isr, p_dev);

    am_kl26_dma_chan_cfg(p_dev->p_devinfo->dma_chan,
                         KL26_DMA_TRIGGER_DISABLE | /**< \brief DMA����ģʽ */
                         DMA_REQUEST_MUX0_ADC0);         /**< \brief ����Դ      */

    if ( p_dev->p_devinfo->is_diff == AM_TRUE ) {
        /* 16λ��13λ��11λ��9λ��������ŵ�  int16_t ���͵�buf�� */
        flags |= KL26_DMA_DCR_SOURCE_SIZE_16_BIT |
                KL26_DMA_DCR_DESTINATION_SIZE_16_BIT;
        length = (p_desc->length) << 1;

    } else if ( p_dev->p_devinfo->bits == 8 ) {
        /* 8λ�������� ��ŵ�uint8_t���͵�buf�� */
        flags |= KL26_DMA_DCR_SOURCE_SIZE_8_BIT |
                KL26_DMA_DCR_DESTINATION_SIZE_8_BIT;
        length = (p_desc->length) << 0;
    } else {
        /* 16λ��12λ��10λ �������� ��ŵ� uint16_t ���͵�buf�� */
        flags |= KL26_DMA_DCR_SOURCE_SIZE_16_BIT |
                KL26_DMA_DCR_DESTINATION_SIZE_16_BIT;
        length = (p_desc->length) << 1;
    }


    /* ����ͨ�������� */
    am_kl26_dma_xfer_desc_build(&dma_desc,                      /* ͨ��������   */
                                (uint32_t)&(p_dev->p_devinfo->p_hw_adc->dat[p_dev->p_devinfo->seq]), /* Դ�����ݻ��� */
                                (uint32_t)(p_desc->p_buf),         /* Ŀ�����ݻ��� */
                                (uint32_t)(length),                /* �����ֽ���   */
                                flags);                            /* ��������     */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_kl26_dma_chan_start(&dma_desc,
                               KL26_DMA_PER_TO_MER,   /* ���赽 �ڴ�   */
                               (uint8_t)p_dev->p_devinfo->dma_chan) == AM_ERROR) {
        return AM_ERROR;
    }

    return AM_OK;
}



/**
 * \brief ADC DMA�����жϷ�����
 */
static void __am_fsl_adc_dma_isr (void *p_arg , uint8_t flag)
{

    am_fsl_adc_dev_t *p_dev = (am_fsl_adc_dev_t *)p_arg;
    uint32_t cfg = 0;

    if (flag == AM_KL26_DMA_INT_NORMAL) { /* ͨ������ */

        if (NULL != p_dev->p_desc[p_dev->desc_pos].pfn_complete) {
            p_dev->p_desc[p_dev->desc_pos].pfn_complete(p_dev->p_desc[p_dev->desc_pos].p_arg, AM_OK);
        }

        p_dev->desc_pos++;
        if (p_dev->desc_pos == p_dev->desc_num) { /* �Ѿ�������� */
            p_dev->desc_pos = 0;

            if (NULL != p_dev->pfn_callback) {
                p_dev->pfn_callback(p_dev->p_arg, AM_OK);
            }
            p_dev->count_pos++; /* ת�����б�׼ */
            if (p_dev->count != 0 && p_dev->count_pos == p_dev->count) {
                p_dev->count_pos = 0;
                am_adc_stop((am_adc_handle_t)&(p_dev->adc_serv), p_dev->chan);  /* �ر�ģ�� */
                amhw_fsl_adc_dma_disable(p_dev->p_devinfo->p_hw_adc); /* �ر�DMA����*/
                am_kl26_dma_chan_stop(p_dev->p_devinfo->dma_chan);
                return ; /* ���� */
            }
        }

        /* ����������һ������ */
        am_adc_stop((am_adc_handle_t)&(p_dev->adc_serv), p_dev->chan);                /* �ر�ADCģ�� */
        am_kl26_dma_chan_stop(p_dev->p_devinfo->dma_chan);   /* ֹͣͨ������  */
        am_fsl_adc_dma_tran_cfg(p_dev, &(p_dev->p_desc[p_dev->desc_pos]));
        amhw_fsl_adc_dma_enable(p_dev->p_devinfo->p_hw_adc);  /* ʹ��DMA����*/

        /* ��ȡADC����״̬���ƼĴ���1��ֵ */
        cfg = amhw_fsl_adc_sc1_get(p_dev->p_devinfo->p_hw_adc,
                                    p_dev->p_devinfo->seq);

        cfg &= ~AMHW_FSL_ADC_SC1_CHAN_MASK;
        cfg |= AMHW_FSL_ADC_SC1_CHAN_SEL_CFG(p_dev->chan);

        amhw_fsl_adc_sc1_cfg(p_dev->p_devinfo->p_hw_adc,      /* ����ADCͨ������*/
                              p_dev->p_devinfo->seq,
                              cfg);
    } else { /* ͨ�Ŵ��� */

    }

}

