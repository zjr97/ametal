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
 * \brief TPMʵ�ֲ����ܣ�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. ������ò����ܵõ���PWM�źŵ����ں�Ƶ�ʡ�
 *
 * - ע�⣺
 *   1. TPM1ͨ��PIOE_23�������PWM��
 *   2. TPM0��������ͨ��0ʹ��PIOD_0���ţ�
 *   3. ����PIOE_23���ź�PIOD_0���ţ�ʹ�ò������PWMƵ�ʡ�
 *
 * \par Դ����
 * \snippet demo_fsl_hw_tpm_cap.c src_fsl_hw_tpm_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_fsl_if_hw_tpm_cap
 * \copydoc demo_fsl_hw_tpm_cap.c
 */
 
/** [src_fsl_hw_tpm_cap] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_pwm.h"
#include "am_vdebug.h"
#include "hw/amhw_fsl_tpm.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/** \brief �����ز��� */
#define TPM_CAP_TRIGGER_RISE  1

/** \brief �½��ز��� */
#define TPM_CAP_TRIGGER_FALL  2

/** \brief TPMͨ���� */
#define TPM_CAP_CH_NUM        AMHW_FSL_TPM_CH(0)

static volatile am_bool_t  __g_flag    = AM_FALSE;  /**< \brief �����־���Ƿ񲶻��µ��¼�   */
static volatile uint64_t   __g_time_ns = 0;         /**< \brief �������ֵ */
uint32_t                   __g_tpm_clock;           /**< \brief tpm���õ�ʱ��Դ��С */

void tpm_cap_isr (void *p_arg)
{
    static uint32_t count1;
    static am_bool_t first = AM_TRUE;

    amhw_fsl_tpm_t   *p_hw_tpm = (amhw_fsl_tpm_t *)p_arg;
    uint32_t          cap_val;
    
    if (amhw_fsl_tpm_stat_flag_get(p_hw_tpm) & AMHW_FSL_TPM_STAT_FLAG(TPM_CAP_CH_NUM)) {
        cap_val = amhw_fsl_tpm_ch_value_get(p_hw_tpm, TPM_CAP_CH_NUM);
        if (__g_flag == AM_FALSE) {
            if (first == AM_TRUE) {
                count1 = cap_val;
                first = AM_FALSE;
            } else {
                if(cap_val > count1) {
                    /* �����ζ�ȡֵ�Ĳ�ת����ʱ��  */
                    __g_time_ns = (uint64_t)1000000000 * (uint64_t)(cap_val - count1) / __g_tpm_clock;
                }
                first = AM_TRUE;
                /* �ñ�־Ϊ�棬����������� */
                __g_flag = AM_TRUE;
            } 
        }

        /* ���ͨ����־ */
        amhw_fsl_tpm_stat_flag_clear(p_hw_tpm, AMHW_FSL_TPM_STAT_FLAG(TPM_CAP_CH_NUM));
    }
}

/**
 * \brief �����ʼ��
 * \param[in] p_tpm : ָ��TPM�Ĵ������ָ��
 * \return ��
 * \note Ĭ������TPM0��ͨ��0���ţ���ѡ������ͨ�������ڴ��޸�
 */
void tpm_cap_init (amhw_fsl_tpm_t *p_hw_tpm)
{
    /* �ر�ʱ�ӣ�ֹͣ���� */
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_NONE);

    /* ��������� */
    amhw_fsl_tpm_count_clear(p_hw_tpm);

    /* Ԥ��Ƶ���� */
    amhw_fsl_tpm_prescale_set(p_hw_tpm, AMHW_FSL_TPM_DIVIDED_BY_1);

//    /* ��ȡtpmʱ��ԴƵ�ʣ����ں������ */
//    __g_tpm_clock = am_kl26_clk_periph_rate_get(p_hw_tpm);

}

/**
 * \brief ��ʼ��һ·PWM�����
 *
 * \param[in] p_tpm    : ָ��TPM�Ĵ������ָ�롣
 * \param[in] cap_num  : �����š�
 * \param[in] cap_edge : �������ѡ�� (#TPM_CAP_TRIGGER_RISE) �� (#TPM_CAP_TRIGGER_FALL)
 *
 * \return  ��
 */
void tpm_cap_chan_config (amhw_fsl_tpm_t *p_hw_tpm, uint8_t cap_num, uint8_t cap_edge)
{
    if (cap_edge == TPM_CAP_TRIGGER_RISE) {
        amhw_fsl_tpm_ch_mode(p_hw_tpm, cap_num, AMHW_FSL_TPM_COUNTING_UP,
                              AMHW_FSL_TPM_CHSC_MS(0) | AMHW_FSL_TPM_CHSC_EL_SEL(1));
    } else {
        amhw_fsl_tpm_ch_mode(p_hw_tpm, cap_num, AMHW_FSL_TPM_COUNTING_UP,
                              AMHW_FSL_TPM_CHSC_MS(0) | AMHW_FSL_TPM_CHSC_EL_SEL(2));
    }
}

void tpm_cap_chan_enable (amhw_fsl_tpm_t *p_hw_tpm, uint32_t cap_num)
{
    /* ʹ��ͨ���ж� */
    amhw_fsl_tpm_ch_sc_set(p_hw_tpm, cap_num, AMHW_FSL_TPM_CHSC_IE);

    /* ��ʱ�ӣ��������� */
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_MODULE);
}

/**
 * \brief �������
 */
void demo_fsl_hw_tpm_cap_entry (am_pwm_handle_t  tpm2_pwm_handle,
                                amhw_fsl_tpm_t  *p_hw_tpm,
                                int              inum,
                                uint32_t         tpm_clock)
{
    uint32_t        freq;               /**< \brief ���񵽵�Ƶ�� */
    uint32_t        time_ns;

    AM_DBG_INFO("The TPM demo for CAP service\r\n");

    __g_tpm_clock = tpm_clock;

    /* TPM2ͨ��1ʹ��PIOE_23���� amhw_timer_cap_config.c ������ */
    am_pwm_config(tpm2_pwm_handle, 1, 500000 / 2, 500000); /* TƵ��Ϊ2KHz */
    am_pwm_enable(tpm2_pwm_handle, 1);
    
    am_int_connect(inum, tpm_cap_isr, (void *)p_hw_tpm);
    am_int_enable(inum);

    tpm_cap_init(p_hw_tpm);
    tpm_cap_chan_config(p_hw_tpm, TPM_CAP_CH_NUM, TPM_CAP_TRIGGER_RISE);
    tpm_cap_chan_enable(p_hw_tpm, TPM_CAP_CH_NUM);

    while (1) {
        uint32_t key = am_int_cpu_lock();
        if (__g_flag == AM_TRUE) {
            time_ns = __g_time_ns;
            __g_flag = AM_FALSE;
            am_int_cpu_unlock(key);
            freq = (uint32_t)1000000000 / time_ns;           /* ת����Ƶ�� */
            AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n", time_ns, freq);
        } else {
            am_int_cpu_unlock(key);
        }
        am_mdelay(200);
        am_led_toggle(LED0);
    }
}
 
/** [src_fsl_hw_tpm_cap] */

/* end of file */
