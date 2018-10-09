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
 * \brief ADC ���̣��жϷ�ʽ����ͨ����׼�ӿ�ʵ��
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
 * \snippet demo_lpc_std_adc_int.c src_lpc_std_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_std_adc_int
 * \copydoc demo_lpc_std_adc_int.c
 */

/** [src_lpc_std_adc_int] */
#include "ametal.h"
#include "am_adc.h"
#include "am_vdebug.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** \brief ADC BUF1 �ɼ���ɻص�������־ */
#define __ADC_BUF0_FLAG    0

/** \brief ADC BUF2 �ɼ���ɻص�������־ */
#define __ADC_BUF1_FLAG    1

/** \brief һ������ʹ�� 2 �������������� */
#define __ADC_DESC_NUN     2

/** \brief ADC BUF �� 100 �����ݳ��ȣ�32λ�� */
#define __ADC_BUF_LEN      100

/** \brief ������������ת�� */
#define __ADC_TRANS_COUNT  0

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief ��ǰ��� AD �������������ţ���ЧֵС��__ADC_DESC_NUN */
am_local volatile uint8_t    __g_buf_flag = 255;

/** \brief ADC ������������ */
am_local am_adc_buf_desc_t   __g_desc[__ADC_DESC_NUN];

/** \brief ADC ���ݻ����� */
am_local uint16_t            __g_adc_val[__ADC_DESC_NUN][__ADC_BUF_LEN];

/**
 * \brief ADC ת���ص�����
 */
am_local void __adc_convert_cb (void *p_arg, int state)
{
    if (__g_buf_flag > __ADC_DESC_NUN && state == AM_OK) {
        __g_buf_flag = (uint32_t)p_arg;
    } else {

       /* �����ٶ�������ٶȲ�ƥ�䣨Ӧ���Ͳ����ʣ� */
        AM_DBG_INFO("the speed too high\r\n");
    }
}


void demo_lpc_std_adc_int_entry(am_adc_handle_t adc_handle,
                                int             chan,
                                uint32_t        rate)
{
    uint32_t        i          = 0;
    uint32_t        adc_aver   = 0;      /* ����ƽ��ֵ */
  
    /* ���������� */
    am_adc_mkbufdesc(&__g_desc[0],
                     &__g_adc_val[0][0],
                      __ADC_BUF_LEN,
                      __adc_convert_cb,
                      (void *)__ADC_BUF0_FLAG);

    am_adc_mkbufdesc(&__g_desc[1],
                     &__g_adc_val[1][0],
                      __ADC_BUF_LEN,
                      __adc_convert_cb,
                     (void *)__ADC_BUF1_FLAG);

    /**
     * ���� 10KHz �����ʣ�֧�ֵĲ��������û����ݴ����������йأ�
     * ��ʹ���жϹ���ģʽ������ʹ�ù��ߵĲ�����
     * ʵ�����趨�Ĳ����ʸ��û����������Ͳɼ��ź��й�
     */
    am_adc_rate_set(adc_handle, chan, rate);

    /* ���� ADC ת�� */
    am_adc_start(adc_handle,
                 chan,
                &__g_desc[0],
                 __ADC_DESC_NUN,
                 __ADC_TRANS_COUNT,
                 AM_ADC_DATA_ALIGN_RIGHT,
                 NULL,
                 NULL);

    AM_FOREVER {

        if (__g_buf_flag == __ADC_BUF0_FLAG) {

            /* ADC ���ݴ��� */
            adc_aver = 0;
            for (i = 0; i < __ADC_BUF_LEN; i++) {

                /* ��Ϊ�������Ҷ��� */
                adc_aver += __g_adc_val[__g_buf_flag][i];
            }

            /* ������ AD �������� buf ����ƽ��ֵ �������� buf �������� */
            adc_aver /= __ADC_BUF_LEN;
            adc_aver = adc_aver * 2500 / ((1 << 12) -1);

            __g_buf_flag = 255;        /* ���������ݱ�־��� */

            AM_DBG_INFO("the verf0 is : %d mV \r\n", adc_aver);

        } else if (__g_buf_flag == __ADC_BUF1_FLAG) {

                /* ADC ���ݴ��� */
                adc_aver = 0;
                for (i = 0; i < __ADC_BUF_LEN; i++) {

                    /* ��Ϊ�������Ҷ��� */
                    adc_aver += __g_adc_val[__g_buf_flag][i];
                }

                /* ������ AD �������� buf ����ƽ��ֵ �������� buf �������� */
                adc_aver /= __ADC_BUF_LEN;
                adc_aver = adc_aver * 2500 / ((1 << 12) -1);

                __g_buf_flag = 255;        /* ���������ݱ�־��� */

                AM_DBG_INFO("the verf1 is : %d mV \r\n", adc_aver);
        }
    }
}


/** [src_lpc_std_adc_dma_poll] */

/* end of file */

