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
 * \brief ADC���̣��������ת����DMA����ת�������ʹ�ö��������������ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. J12����ñ�̽ӣ���ʱ�ο���ѹΪ2.5v����
 *   4. PIOE_20(ADCͨ��0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_fsl_std_adc_descs_st.c src_fsl_std_adc_descs_st
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-18  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_std_adc_descs_st
 * \copydoc demo_fsl_std_adc_descs_st.c
 */

/** [src_fsl_std_adc_descs_st] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_adc.h"
#include "am_board.h"
#include "hw/amhw_fsl_adc.h"
#include "am_int.h"

volatile static uint8_t __g_flag_complete  = 0;   /**< \brief ADCת����ɱ�־ */
volatile static uint8_t __g_flag_complete0 = 0;   /**< \brief ���ݻ�����0��ɱ�־ */
volatile static uint8_t __g_flag_complete1 = 0;   /**< \brief ���ݻ�����1��ɱ�־ */

/** \brief ������������������ص����� */
static void __fsl_adc_callback (void *p_arg, int state)
{
    if (state != AM_OK) {
        return;
    }

    if ((int)p_arg == 0) {
        __g_flag_complete0 = 1;
    }

    if ((int)p_arg == 1) {
        __g_flag_complete1 = 1;
    }
}

/** \brief ADCת����ɻص����� */
void __fsl_adc_seq_complete (void *p_arg, int state)
{
    __g_flag_complete = 1;
}

/**
 * \brief adc���������DMA��������һ�β�������ADC������
 * \return ��
 */
void demo_fsl_std_adc_descs_st_entry (am_adc_handle_t adc0_handle)
{
    uint32_t adc_bits = 0;          /**< \brief ADCλ�� */
    uint32_t adc_vref = 0;          /**< \brief ADC�ο���ѹ*/
    uint32_t adc_mv;                /**< \brief ������ѹ */
    int      chan = 0;              /**< \brief ͨ��0 */
    int      i;
    am_adc_buf_desc_t   desc[2];                /**< \brief ʹ���������������� */
    uint16_t            adc_val0[10];           /**< \brief ���ݻ�����1     */
    uint16_t            adc_val1[10];           /**< \brief ���ݻ�����2     */
    uint32_t key;
    uint32_t adc_sum;

    adc_bits = am_adc_bits_get(adc0_handle, chan); /* ��ȡADCת������ */
    adc_vref = am_adc_vref_get(adc0_handle, chan); /* ��ȡADC�ο���ѹ����λ��mV */

    /* ���û����������� */
    am_adc_mkbufdesc(&desc[0], adc_val0, 10, __fsl_adc_callback, (void *)0);
    am_adc_mkbufdesc(&desc[1], adc_val1, 10, __fsl_adc_callback, (void *)1);

    /* ����ADCת�� */
    am_adc_start(adc0_handle,
                 chan,
                 desc,
                 2,
                 0,
                 AM_ADC_DATA_ALIGN_RIGHT,
                 __fsl_adc_seq_complete,
                 NULL);

    am_kprintf("The KL26 Adc Std descs Software Trigger Demo\r\n");

    while (1) {

        if (1 == __g_flag_complete0) {
            key = am_int_cpu_lock();
            __g_flag_complete0 = 0;
            am_int_cpu_unlock(key);
            am_kprintf("Finished the 1th desc\r\n");
        }

        if (1 == __g_flag_complete1) {
            key = am_int_cpu_lock();
            __g_flag_complete1 = 0;
            am_int_cpu_unlock(key);
            am_kprintf("Finished the 2th desc\r\n");
        }

        if (1 == __g_flag_complete) {
            key = am_int_cpu_lock();
            __g_flag_complete = 0;
            am_int_cpu_unlock(key);

            adc_sum = 0;
            for (i = 0; i < 10; i++) {
                adc_sum += adc_val0[i];
            }

            adc_sum /= 10;
            adc_mv = adc_sum * adc_vref / ((1UL << adc_bits) - 1);

            /* �������������ѹֵ */
            am_kprintf("Vol0: %d mv\r\n", adc_mv);

            adc_mv  = 0;
            adc_sum = 0;
            for (i = 0; i < 10; i++) {
                adc_sum += adc_val1[i];
            }

            adc_sum /= 10;
            adc_mv = adc_sum * adc_vref / ((1UL << adc_bits) - 1);

            /* �������������ѹֵ */
            am_kprintf("Vol1: %d mv\r\n", adc_mv);

            for (i = 0; i < 10; i++) {
                adc_val0[i] = 0;
                adc_val1[i] = 0;
            }
        }
    }
}

/** [src_fsl_std_adc_descs_st] */

/* end of file */
