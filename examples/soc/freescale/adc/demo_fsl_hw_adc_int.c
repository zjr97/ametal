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
 * \brief ADC���̣������жϷ�ʽ��ȡ���������ADCת�������ͨ��HW��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_1��������PC���ڵ�TXD��
 *   2. PIOA_2��������PC���ڵ�RXD��
 *   3. J12����ñ�̽ӣ���ʱ�ο���ѹΪ2.5v����
 *   4. PIOE_29(ADCͨ��0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ADCģ����444.44kHz������(����ʱ��Ϊ24MHz)������16λ����;
 *   2. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_fsl_hw_adc_int.c src_fsl_hw_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-18  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_hw_adc_int
 * \copydoc demo_fsl_hw_adc_int.c
 */

/** [src_fsl_hw_adc_int] */
#include "hw/amhw_fsl_adc.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_board.h"

static volatile uint32_t __g_adc_dat;             /**< \brief ����ֵ */
static volatile uint32_t __g_adc_finish_flag;     /**< \brief ADC������ɱ�ʶ */

extern int am_int_disconnect (int inum, am_pfnvoid_t pfn_isr, void *p_arg);
extern int am_int_connect (int inum, am_pfnvoid_t pfn_isr, void *p_arg);
extern int am_int_enable (int inum);
extern int am_int_disable (int inum);


/**
 * \brief  ADC �жϷ�����
 */
static void adc_isr (void *p_arg)
{
    amhw_fsl_adc_t *p_hw_adc = (amhw_fsl_adc_t *)p_arg;

    __g_adc_dat = amhw_fsl_adc_dat_get(p_hw_adc, AMHW_FSL_ADC_SEQ_A);
    __g_adc_finish_flag = 1;
}

/**
 * \brief  ADC ���ú���
 * \param[in] ��
 * \return    ��
 */
static void adc_config (amhw_fsl_adc_t     *p_hw_adc,
                        int                 int_num)
{
    /* ����ADCģ������ʻ�ʱ�� */
    amhw_fsl_adc_clkdiv_set(p_hw_adc, AMHW_FSL_ADC_CLK_DIV_2);
    amhw_fsl_adc_clksrc_set(p_hw_adc, AMHW_FSL_ADC_CLK_SRC_BUS);

    /* ���÷ֱ��� */
    amhw_fsl_adc_mode_set(p_hw_adc, AMHW_FSL_ADC_BITS_16);

    /* ʹ��������� , Ĭ��ʹ������A */
    amhw_fsl_adc_hwtrg_disable(p_hw_adc);

    /* ʹ����������ģʽ */
    amhw_fsl_adc_continue_enable(p_hw_adc);

    /* ʹ�ܸ���ת��ģʽ */
    amhw_fsl_adc_hsc_enable(p_hw_adc);

    /* ��ʹ�ܵ͹��� */
    amhw_fsl_adc_lowpower_disable(p_hw_adc);

    /* �رձȽϹ��� */
    amhw_fsl_adc_cmp_disable(p_hw_adc);

    /* ʹ��Ӳ��ƽ�� */
    amhw_fsl_adc_avg_enable(p_hw_adc);
    amhw_fsl_adc_avgs_set(p_hw_adc, AMHW_FSL_ADC_AVGS_32);

    /* �����жϷ���������ʹ�� */
    am_int_disconnect(int_num, adc_isr, p_hw_adc);
    am_int_connect(int_num, adc_isr, p_hw_adc);
    am_int_enable(int_num);

    /* ���óɵ���ģʽ�� ͨ��Ϊ0�����жϣ�ͬʱ�����������ȹر�ͨ�� */
    amhw_fsl_adc_sc1_cfg(p_hw_adc,
                         AMHW_FSL_ADC_SEQ_A,
                         AMHW_FSL_ADC_SC1_CHAN_SEL_CFG(AMHW_FSL_ADC_CHAN_CLOSE) |
                         AMHW_FSL_ADC_SC1_INT_EN_CFG);
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
 * \brief �жϷ�ʽ��ȡ���������ADCת�������ͨ��HW��ӿ�ʵ��
 * \return ��
 */
void demo_fsl_hw_adc_int_entry (amhw_fsl_adc_t     *p_hw_adc,
                                int                 int_num,
                                amhw_fsl_adc_chan_t chan,
                                uint32_t            clk_bus,
                                uint32_t            vref_mv)
{
    uint32_t adc_mv = 0;                /**< \brief ������ѹ */

    /* ADCУ׼ */
    amhw_fsl_adc_calibrate(p_hw_adc, clk_bus);

    /* ADC���ó�ʼ�� */
    adc_config(p_hw_adc, int_num);

    am_kprintf("The ADC HW Int Demo\r\n");

    /* ѡ��ͨ��B */
    amhw_fsl_adc_seq_set(p_hw_adc, AMHW_FSL_ADC_MUXSEL_B);

    /* ѡ��ͨ��4 */
    adc_start(p_hw_adc, chan);

    while(1) {
        am_int_disable(int_num);
        if (__g_adc_finish_flag) {
            __g_adc_finish_flag = 0;

            adc_mv = __g_adc_dat * 2500 / ((1UL << 16) - 1);
            am_int_enable(int_num);

            am_kprintf("Vol: %d mv\r\n", adc_mv);
            am_mdelay(100);        /* �����PL2102�����Ļ�����Ҫ��ʱһ��ʱ�䣬��Ȼ���Ժ��������� */
        } else {
            am_int_enable(int_num);
        }
    }
}
/** [src_fsl_hw_adc_int] */

/* end of file */
