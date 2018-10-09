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
 * \brief ADC���̣����ò�ѯ��ʽ��ȡ���������ADCת�������ͨ��HW��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. J12����ñ�̽ӣ��ο���ѹ�Ĵ�С��оƬVREF�ܽ����ӵĵ�ƽ�йأ��˴��Ĳο���ѹΪ2.5V����
 *   4. PIOE_20(ADCͨ��0����ͨ������) ����ģ�����롣
 *
 * - ʵ������
 *   1. ADCģ����444.44kHz������(����ʱ��Ϊ24MHz)������16λ����;
 *   2. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_fsl_hw_adc_poll.c src_fsl_hw_adc_poll
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-14  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_hw_adc_poll
 * \copydoc demo_fsl_hw_adc_poll.c
 */

/** [src_fsl_hw_adc_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "hw/amhw_fsl_adc.h"
#include "am_board.h"

/**
 * \brief  ADC ���ú���
 * \param[in] ��
 * \return    ��
 */
static void adc_config (amhw_fsl_adc_t     *p_hw_adc)
{
    /* ����ADCģ������ʻ�ʱ�� */
    amhw_fsl_adc_clkdiv_set(p_hw_adc, AMHW_FSL_ADC_CLK_DIV_2);
    amhw_fsl_adc_clksrc_set(p_hw_adc, AMHW_FSL_ADC_CLK_SRC_BUS);

    /* ���÷ֱ��� */
    amhw_fsl_adc_mode_set(p_hw_adc, AMHW_FSL_ADC_BITS_16);

    /* ʹ��������� , Ĭ��ʹ������A*/
    amhw_fsl_adc_hwtrg_disable(p_hw_adc);

    /* ʹ����������ģʽ */
    amhw_fsl_adc_continue_enable(p_hw_adc);

    /* ʹ�ܸ���ת��ģʽ */
    amhw_fsl_adc_hsc_enable(p_hw_adc);

    /* ��ʹ�ܵ͹��� */
    amhw_fsl_adc_lowpower_disable(p_hw_adc);

    /* �ر�Ӳ��ƽ���ͱȽϹ��� */
    amhw_fsl_adc_cmp_disable(p_hw_adc);
    amhw_fsl_adc_avg_disable(p_hw_adc);

    /**
     * ���óɵ���ģʽ�� ͨ��Ϊ0�������жϣ�
     * �������ADCת��ģʽʱ��д��ADCת��ͨ��ֵ��
     * ������ADCת�����˴��Ȳ�����ת��
     */
    amhw_fsl_adc_sc1_cfg(p_hw_adc,
                          AMHW_FSL_ADC_SEQ_A,
                          AMHW_FSL_ADC_SC1_CHAN_SEL_CFG(AMHW_FSL_ADC_CHAN_CLOSE));
}

/**
 * \brief  ADC �������ת������
 * \param[in] ��
 * \return    ��
 */
static void adc_start (amhw_fsl_adc_t     *p_hw_adc,
                       amhw_fsl_adc_chan_t chan)
{
    amhw_fsl_adc_chan_set(p_hw_adc, AMHW_FSL_ADC_SEQ_A, chan);
}

/**
 * \brief ADC��ѯ��ȡ����ֵ��ʹ��HW��ӿں���
 * \return ��
 */
void demo_fsl_hw_adc_poll_entry (amhw_fsl_adc_t     *p_hw_adc,
                                 amhw_fsl_adc_chan_t chan,
                                 uint32_t            clk_bus,
                                 uint32_t            vref_mv)
{
    uint32_t adc_mv;                /**< \brief ������ѹ */
    uint32_t adc_dat;               /**< \brief ����ֵ */
    uint32_t cnt = 0;               /**< \brief ��ȡ���� */

    /* ADCУ׼ */
    amhw_fsl_adc_calibrate(p_hw_adc, clk_bus);

    /* ADC���ó�ʼ�� */
    adc_config(p_hw_adc);

    am_kprintf("The ADC HW Poll Demo\r\n");

    /* ����ת��ʹ�� */
    amhw_fsl_adc_continue_enable(p_hw_adc);

    /* ѡ��ͨ��0 */
    adc_start(p_hw_adc, chan);

    while(1) {

        while (!amhw_fsl_adc_complete_is(p_hw_adc, AMHW_FSL_ADC_SEQ_A));    /* �ȴ�ADCת����� */
        am_led_toggle(LED1);
        adc_dat = amhw_fsl_adc_dat_get(p_hw_adc, AMHW_FSL_ADC_SEQ_A);
        cnt++;
        if (cnt >= 2000UL) { /* ��ʱ�����ƴ��ڴ�ӡ����  */
            cnt = 0;
            adc_mv = adc_dat * vref_mv / ((1UL << 16) - 1);
            /* �������������ѹֵ */
            am_kprintf("Vol: %d mv\r\n", adc_mv);
        }
    }
}
/** [src_fsl_hw_adc_poll] */

/* end of file */
