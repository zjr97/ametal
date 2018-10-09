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
 * \brief ADC DMA ���̣���ѯ��ʽ����ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽� J12 ����ñ��ʹ�òο���ѹΪ 2.5V��
 *   2. PIO0_7(ADC ͨ�� 0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc_std_adc_dma_poll.c src_lpc_std_adc_dma_poll
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-09-10  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_std_adc_dma_poll
 * \copydoc demo_lpc_std_adc_dma_poll.c
 */

/** [src_lpc_std_adc_dma_poll] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_adc.h"
#include "am_lpc82x_inst_init.h"
#include "demo_nxp_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** \brief ADC ���ݻ��������� */
#define __ADC_BUF_LEN      100

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief ADC ���ݻ����� */
am_local uint16_t __g_adc_val_buf[__ADC_BUF_LEN];



void demo_lpc_std_adc_dma_poll_entry(am_adc_handle_t adc_handle,
                                     int             chan,
                                     uint32_t        rate)
{
    uint8_t i = 0;
/* ���� 10KHz �����ʣ�֧�ֵĲ��������û����ݴ����������йأ� */
    am_adc_rate_set(adc_handle, chan, rate);

    AM_FOREVER {

        /* ��ȡ ADC ת���ĵ�ѹֵ */
        am_adc_read(adc_handle,
                    chan,
                    __g_adc_val_buf,
                    __ADC_BUF_LEN);

        for (i = 0; i < __ADC_BUF_LEN; i++) {
            AM_DBG_INFO("%dmV    \n", AM_ADC_VAL_TO_MV(adc_handle,
                                                     chan,
                                                     __g_adc_val_buf[i]));
        }

        AM_DBG_INFO("\r\n");
    }
}


/** [src_lpc_std_adc_dma_poll] */

/* end of file */

