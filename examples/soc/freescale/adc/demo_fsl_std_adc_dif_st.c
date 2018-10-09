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
 * \brief ADC���̣��������ת����DMA������ת�������ͨ����׼�ӿ�ʵ��
 *
 * \note ʹ�ô�demo��Ҫ����ʹ��am_kl26_hwconfig_adc0.c�ļ��е�AM_FSL_ADC_DIF_EN��
 *
 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. J12����ñ�̽ӣ���ʱ�ο���ѹΪ2.5v����
 *   4. PIOE_20(ADC_DP0)��PIOE_21(ADC_DM0)����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_fsl_std_adc_dif_st.c src_fsl_std_adc_dif_st
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-19  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_std_adc_dif_st
 * \copydoc demo_fsl_std_adc_dif_st.c
 */

/** [src_fsl_std_adc_dif_st] */
#include "ametal.h"
#include "am_adc.h"
#include "am_vdebug.h"
#include "am_board.h"

/**
 * \brief ADC������룬DMA���䣬�������
 * \return ��
 */
void demo_fsl_std_adc_dif_st_entry (am_adc_handle_t adc0_handle)
{
    int32_t  adc_bits     = 0;          /**< \brief ADCλ�� */
    int32_t  adc_vref     = 0;          /**< \brief ADC�ο���ѹ*/
    uint16_t adv_val0[10] = {0};        /**< \brief ADC����ԭʼֵ */
    int32_t  adc_sum      = 0;
    int16_t  adc_mv;                /**< \brief ������ѹ */
    int      chan = 0;              /**< \brief ͨ��0 */
    int      i;

    adc_bits = am_adc_bits_get(adc0_handle, chan); /* ��ȡADCת������ */
    adc_vref = am_adc_vref_get(adc0_handle, chan); /* ��ȡADC�ο���ѹ����λ��mV */

    am_kprintf("The KL26 Adc Dif Software Trigger Demo\r\n");

    while (1) {

        /* ��ȡADCת�������������ɲŷ��� */
        am_adc_read(adc0_handle, chan, adv_val0, 10);

        adc_sum = 0;
        for (i = 0; i < 10; i++) {

            if (adv_val0[i] & 0x8000) {
                /* ����Ϊ�����Ĳ��룬����ת�� */
                adv_val0[i] = ((~adv_val0[i]) + 1) & 0xFFFF;
            }

            adc_sum += adv_val0[i];
        }
        /**
         * ���ģʽ�£�λ���ı䣬��ߵ�����λ����ɷ���λ�����Ǿ���λ���ı��ˣ�
         * ����ADCģ������̲�Ӧ�øı�ģ�����Ӧ�����������ֵ�����ϡ�2
         */
        adc_sum /= 5;
        adc_mv = adc_sum * adc_vref / ((1 << adc_bits) - 1);

        /* �������������ѹֵ */
        am_kprintf("Vol: %d mv\r\n", adc_mv);

        am_mdelay(500);
    }
}

/** [src_fsl_std_adc_dif_st] */

/* end of file */
