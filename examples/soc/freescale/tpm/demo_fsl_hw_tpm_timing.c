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
 * \brief TPMʵ�ֱ�׼��ʱ�����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 *
 *\note TPM��4��ʱ��Դ����ѡ��Ĭ������ʱ��Դ��СΪ20M,���жϵ���СƵ��Ϊ:
 *              fre = 20000000/(128*65535) = 2.38Hz  ��16λ��ʱ�������128��Ƶ��
 *
 * \par Դ����
 * \snippet demo_fsl_hw_tpm_timing.c src_fsl_hw_tpm_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_fsl_if_hw_tpm_timing
 * \copydoc demo_fsl_hw_tpm_timing.c
 */
 
/** [src_fsl_hw_tpm_timing] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "hw/amhw_fsl_tpm.h"
#include "am_board.h"

/** 
 * \brief  ��ʱ��0�ص�����
 * \param[in] p_arg : �û��Զ����������am_timer_callback_set() �������ݡ�
 * \return  ��
 */
void tpm_timing_callback (void *p_arg)
{

    amhw_fsl_tpm_t *p_hw_tpm = (amhw_fsl_tpm_t *)p_arg;
    /*
     * �ж��Ƿ��Ƕ�ʱ������ж�
     */
    if (amhw_fsl_tpm_stat_flag_get(p_hw_tpm) & AMHW_FSL_TPM_STAT_OV_FLAG ) {

        am_led_toggle(LED0);
        /* ��������־ */
        amhw_fsl_tpm_stat_flag_clear(p_hw_tpm, AMHW_FSL_TPM_STAT_OV_FLAG);
    }
}

/**
 * \brief ��ʼ��TPMΪ��ʱ�����ܡ�
 *
 * \param[in] p_tpm    : ָ��TPM�Ĵ������ָ��
 * \param[in] freq     : �ж�Ƶ�ʡ�
 * \param[in] inum     : �жϺš�
 * \param[in] tpm_rate : ��ʱ������Ƶ�ʡ�
 *
 * \retval  AM_OK      : ��ʼ���ɹ�
 * \retval  -AM_EINVAL : ��������
 */
int tpm_timer_init (amhw_fsl_tpm_t *p_hw_tpm,
                    uint32_t        freq,
                    int             inum,
                    uint32_t        tpm_clk)
{
    uint32_t  match, temp;
    uint8_t  pre_real, pre_reg = 0;

    match    = tpm_clk / freq;

    if (match > 0xffff * 128) {             /* 16λ��ʱ����128��Ƶ */
        return -AM_EINVAL;
    }

    temp = match / 0xffffu + 1;
    /* ֻ֧�ַ�Ƶ��С1,2,4,8...128����ô��ڷ�Ƶ������С����2^n */
    for (pre_real = 1; pre_real < temp; ) {
        pre_reg++;                        /* ����д��Ĵ����ķ�Ƶֵ0,1,2,... */
        pre_real = pre_real << 1;           /* ��Ƶ��2^n */
    }
    match = match / pre_real;
    amhw_fsl_tpm_prescale_set(p_hw_tpm, (amhw_fsl_tpm_prescale_t)pre_reg);
    amhw_fsl_tpm_count_clear(p_hw_tpm);
    amhw_fsl_tpm_mod_set(p_hw_tpm, match - 1);

    amhw_fsl_tpm_ctrl_set(p_hw_tpm, AMHW_FSL_TPM_SC_TOI_EN);        /* ���ж� */

    am_int_connect(inum, tpm_timing_callback, p_hw_tpm);
    am_int_enable(inum);

    return AM_OK;
}

/**
 * \brief ʹ��TPM��ʱ��(��ʼ����)
 * \param[in] p_tpm : ָ��TPM�Ĵ������ָ��
 * \return ��
 */
void tpm_timer_enable (amhw_fsl_tpm_t *p_hw_tpm)
{
    /* �ر�ʱ�ӣ�TPM��ʼ���� */
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_MODULE);
}

/**
 * \brief  ��ֹTPM��ʱ��(ֹͣ����)
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \return  ��
 */
void hw_tpm_timer_disable (amhw_fsl_tpm_t *p_hw_tpm)
{
    /* �ر�ʱ�ӣ�TPMֹͣ���� */
    amhw_fsl_tpm_clock_mode(p_hw_tpm, AMHW_FSL_TPM_CLK_SRC_NONE);
}

/**
 * \brief �������
 */
void demo_fsl_hw_tpm_timing_entry (amhw_fsl_tpm_t *p_hw_tpm0,
                                   uint32_t        freq,
                                   int             inum,
                                   uint32_t        tpm_clk)
{
    
    AM_DBG_INFO("The demo for TPM timing:\r\n");
    AM_DBG_INFO("The led toggle in 10Hz \r\n");
  
    /* ʹ��TPM0,�ж�Ƶ��Ϊ10Hz */
    tpm_timer_init(p_hw_tpm0, freq, inum, tpm_clk);
    
    /* ��ʼ���� */
    tpm_timer_enable(p_hw_tpm0);

    while (1) {
    }
}

/** [src_fsl_hw_tpm_timing] */

/* end of file */
