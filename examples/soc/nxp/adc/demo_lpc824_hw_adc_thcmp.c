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
 * \brief ADC ��ֵ�Ƚ����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ������չʾ�� 2 ����ֵ�Ƚϣ�
 *   1. ��ֵ�Ƚ� 0: ��Χ�Ƚϣ�
 *   2. ��ֵ�Ƚ� 1: ��Խ�Ƚϡ�
 *
 * - �������裺
 *   1. PIO0_7(ADC ͨ�� 0) ����ģ������ 1��
 *   2. PIO0_6(ADC ͨ�� 1) ����ģ������ 2��
 *   3. �̽� J12 ����ñ��ʹ�òο���ѹΪ 2.5V��
 *   4. ������ͨ����ģ�������ѹ�ֱ�� 0 ���� 2500mV��
 *
 * - ʵ������
 *   1. ģ������ 1 �ĵ�ѹ���� 1100mV ����� 2000mV ʱ�����ڻ������ѹֵ���ȽϽ����
 *   2. ģ������ 2 �ĵ�ѹ�仯���� 1100mV ʱ�����ڻ������ѹֵ���ȽϽ����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_adc_thcmp.c src_lpc824_hw_adc_thcmp
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_adc_thcmp
 * \copydoc demo_lpc824_hw_adc_thcmp.c
 */

/** [src_lpc824_hw_adc_thcmp] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_adc.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** \brief �ͱȽ���ֵ(mV) */
#define __THRE_LOW            ((1100 * 4095) / vref_mv)

/** \brief �߱Ƚ���ֵ(mV) */
#define __THRE_HIGH           ((2000 * 4095) / vref_mv)

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

am_local volatile am_bool_t __g_tc0_flag; /** \brief ��ֵ�Ƚ� 0 �жϱ�־ */
am_local volatile am_bool_t __g_tc1_flag; /** \brief ��ֵ�Ƚ� 1 �жϱ�־ */

am_local volatile uint32_t __g_val_chan0; /** \brief ADC ͨ�� 0 ���ݻ����� */
am_local volatile uint32_t __g_val_chan1; /** \brief ADC ͨ�� 1 ���ݻ����� */

/**
 * \brief ADC �жϷ�����
 */
am_local void __adc_isr (void *p_arg)
{
    uint32_t            int_flags =  0;
    amhw_lpc82x_adc_t  *p_hw_adc  = (amhw_lpc82x_adc_t *)p_arg;
  
    int_flags = amhw_lpc82x_adc_flags_get(p_hw_adc);

    /* �Ƿ�Ϊ��ֵ�Ƚ��ж� */
    if (int_flags & AMHW_LPC82X_ADC_FLAGS_THCMP_INT_MASK) {

        /* �ж��Ƿ�Ϊ ADC ͨ�� 0 ��ֵ�Ƚ��ж� */
        if (int_flags &
            AMHW_LPC82X_ADC_FLAGS_THCMP_MASK(AMHW_LPC82X_ADC_CHAN_0)) {
            __g_tc0_flag  = AM_TRUE;
            __g_val_chan0 = amhw_lpc82x_adc_chan_data_get(
                                p_hw_adc, AMHW_LPC82X_ADC_CHAN_0);
            amhw_lpc82x_adc_flags_clr(
                p_hw_adc,
                AMHW_LPC82X_ADC_FLAGS_THCMP_MASK(AMHW_LPC82X_ADC_CHAN_0));
        }

        /* �ж��Ƿ�Ϊ ADC ͨ�� 1 ��ֵ�Ƚ��ж� */
        if (int_flags &
            AMHW_LPC82X_ADC_FLAGS_THCMP_MASK(AMHW_LPC82X_ADC_CHAN_1)) {
            __g_tc1_flag  = AM_TRUE;
            __g_val_chan1 = amhw_lpc82x_adc_chan_data_get(
                                p_hw_adc, AMHW_LPC82X_ADC_CHAN_1);
            amhw_lpc82x_adc_flags_clr(
                p_hw_adc,
                AMHW_LPC82X_ADC_FLAGS_THCMP_MASK(AMHW_LPC82X_ADC_CHAN_1));
        }

        amhw_lpc82x_adc_flags_clr(p_hw_adc,
                                  AMHW_LPC82X_ADC_FLAGS_THCMP_INT_MASK);
    }
}

/**
 * \brief ADC ����
 */
am_local void __adc_config (amhw_lpc82x_adc_t  *p_hw_adc, 
                            uint32_t            vref_mv)
{
    uint32_t adc_flags = 0;
    uint32_t seq_flags = 0;

    adc_flags = AMHW_LPC82X_ADC_CTRL_CLK_DIV(0);   /* ʱ�ӷ�ƵΪ0��1 ��Ƶ�� */

    /* ADC ���� */
    amhw_lpc82x_adc_config(p_hw_adc, adc_flags);

    seq_flags = AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_POL_POS |  /* ʹ�������ش�����ʽ */
                AMHW_LPC82X_ADC_SEQ_CTRL_MODE_EOS     |  /* ����ת��ģʽ */
                AMHW_LPC82X_ADC_SEQ_CTRL_ENABLE_CH(1) |  /* ʹ�� ADC ͨ�� 1 */
                AMHW_LPC82X_ADC_SEQ_CTRL_ENABLE_CH(0);   /* ʹ�� ADC ͨ�� 0 */

    /* ADC ���� A ���� */
    amhw_lpc82x_adc_seq_config(p_hw_adc,
                               AMHW_LPC82X_ADC_SEQ_A, seq_flags);

    /* ʹ���ж� */
    amhw_lpc82x_adc_int_enable(
        p_hw_adc,
        AMHW_LPC82X_ADC_INTEN_CMP_OUTSIDETH(AMHW_LPC82X_ADC_CHAN_0) |
        AMHW_LPC82X_ADC_INTEN_CMP_CROSSTH(AMHW_LPC82X_ADC_CHAN_1));

    /* Ϊͨ��ѡ����ֵ�Ƚ� */
    amhw_lpc82x_adc_thr0_sel(p_hw_adc, AMHW_LPC82X_ADC_CHAN_0);
    amhw_lpc82x_adc_thr1_sel(p_hw_adc, AMHW_LPC82X_ADC_CHAN_1);

    /* ���ñȽ���ֵ */
    amhw_lpc82x_adc_thr_low_set(p_hw_adc,
                                AMHW_LPC82X_ADC_COMP_THRE_0,
                                __THRE_LOW);
    amhw_lpc82x_adc_thr_high_set(p_hw_adc,
                                 AMHW_LPC82X_ADC_COMP_THRE_0,
                                 __THRE_HIGH);

    amhw_lpc82x_adc_thr_low_set(p_hw_adc,
                                AMHW_LPC82X_ADC_COMP_THRE_1,
                                __THRE_LOW);

    /* ʹ������ A */
    amhw_lpc82x_adc_seq_enable(p_hw_adc, AMHW_LPC82X_ADC_SEQ_A);
}

void demo_lpc824_hw_adc_thcmp_entry(amhw_lpc82x_adc_t  *p_hw_adc, 
                                    int                 inum,
                                    uint32_t            vref_mv)
{
    /* ���� ADC �жϷ���������ʹ���ж� */
    am_int_connect(inum, __adc_isr, (void *)p_hw_adc);
    am_int_enable(inum);

    /* ADC ���� */
    __adc_config(p_hw_adc, vref_mv);

    AM_FOREVER {
        amhw_lpc82x_adc_seq_start(p_hw_adc, AMHW_LPC82X_ADC_SEQ_A);

        if (__g_tc0_flag == AM_TRUE) {
            __g_tc0_flag = AM_FALSE;

            AM_DBG_INFO("The ADC channel 0 voltage: %4d mV \r\n",
                        AMHW_LPC82X_ADC_DR_RESULT(__g_val_chan0) * vref_mv / 4095);

            /* �ж�ͨ�� 0 ��ֵ�ȽϽ�� */
            if (AMHW_LPC82X_ADC_DR_THCMPRANGE(__g_val_chan0) == 0x00) {
                AM_DBG_INFO("The ADC channel 0 voltage is in range.\r\n");

            } else if (AMHW_LPC82X_ADC_DR_THCMPRANGE(__g_val_chan0) == 0x01) {
                AM_DBG_INFO("The ADC channel 0 voltage is blow range.\r\n");

            } else if (AMHW_LPC82X_ADC_DR_THCMPRANGE(__g_val_chan0) == 0x02) {
                AM_DBG_INFO("The ADC channel 0 voltage is above range.\r\n");
            }
        }

        if (__g_tc1_flag == AM_TRUE) {
            __g_tc1_flag = AM_FALSE;

            AM_DBG_INFO("The ADC channel 1 voltage: %4d mV \r\n",
                        AMHW_LPC82X_ADC_DR_RESULT(__g_val_chan1) * vref_mv / 4095);

            /* �ж�ͨ�� 1 ��ֵ�ȽϽ�� */
            if (AMHW_LPC82X_ADC_DR_THCMPCROSS(__g_val_chan1) == 0x00) {
                AM_DBG_INFO("The ADC channel 1 voltage "
                            "no threshold Crossing detected.\r\n");

            } else if (AMHW_LPC82X_ADC_DR_THCMPCROSS(__g_val_chan1) == 0x02) {
                AM_DBG_INFO("The ADC channel 1 voltage "
                            "downward Threshold Crossing Detected.\r\n");

            } else if (AMHW_LPC82X_ADC_DR_THCMPCROSS(__g_val_chan1) == 0x03) {
                AM_DBG_INFO("The ADC channel 1 voltage "
                            "upward Threshold Crossing Detected.\r\n");
            }
        }
        am_mdelay(200);
    }
}
/** [src_lpc824_hw_adc_thcmp] */

/* end of file */
