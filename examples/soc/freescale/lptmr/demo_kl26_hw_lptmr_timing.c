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
 * \brief LPTMRʵ�ֶ�ʱ�����̣�ͨ��HW��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0��10Hz��Ƶ����˸��
 *
 * \note LPTMRʱ��Դ��4��ѡ����amdr_hwconfig_lptmr_timing.c�н������ã�ѡ��ͬ��С
 *       ��ʱ��Դ����ʱ�ķ�Χ�;��ȴ��ڲ��
 *
 * \par Դ����
 * \snippet demo_fsl_hw_lptmr_timing.c src_fsl_hw_lptmr_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_hw_lptmr_timing
 * \copydoc demo_fsl_hw_lptmr_timing.c
 */

/** [src_fsl_hw_lptmr_timing] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "hw/amhw_fsl_lptmr.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/**
 * \brief  ��ʱ��0�ص�����
 * \param[in] p_arg : �û��Զ����������am_timer_callback_set() �������ݡ�
 * \return  ��
 */
void hw_lptmr_timing_callback (void *p_arg)
{
    amhw_fsl_lptmr_t *p_hw_lptmr = (amhw_fsl_lptmr_t *)p_arg;

    if (amhw_fsl_lptmr_flag_check(p_hw_lptmr)) {
        am_led_toggle(LED0);

        /* ��������־��д1���� */
        amhw_fsl_lptmr_ctl_set(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TCF);
    }
}

/**
 * \brief ��ʼ��LPTMR
 *
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \param[in] freq       : �ж�Ƶ�ʡ�
 *
 * \retval  AM_OK      : ��ʼ���ɹ�
 * \retval -AM_EINVAL  : ��������
 */
int lptmr_timer_init(amhw_fsl_lptmr_t *p_hw_lptmr,
                     uint32_t          count,
                     int               inum)
{
    uint32_t pre_reg = 0, pre_real;
    uint32_t temp;

    if (count > (0xFFFFu * 65536)) {
        return -AM_EINVAL;
    }

    /* ����Ҫ��Ƶ�����ܷ�Ƶ�� */
    if (count < 0xFFFF) {
        pre_real = 1;
        amhw_fsl_lptmr_prescaler_filter_set(p_hw_lptmr, AM_TRUE);
    } else {
        temp = count / 0xFFFFu + 1;

        /* �����Ƶֵ 2^n */
        for (pre_real = 2; pre_real < temp;) {
            pre_reg++;
            pre_real = pre_real << 1;
        }

        /* ��Ƶ����Ч */
        amhw_fsl_lptmr_prescaler_filter_set(p_hw_lptmr, AM_FALSE);

        /* ����Ԥ��Ƶֵ */
        amhw_fsl_lptmr_prescaler_set(p_hw_lptmr, (amhw_fsl_lptmr_ps_t)pre_reg);
    }

    count = count / pre_real;

    /* ����װ��ֵ */
    amhw_fsl_lptmr_compare_set(p_hw_lptmr, count - 1);

    amhw_fsl_lptmr_ctl_set(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TIE);        /* ���ж� */
    am_int_connect(inum, hw_lptmr_timing_callback, p_hw_lptmr);
    am_int_enable(inum);

    return AM_OK;
}

/**
 * \brief ʹ��LPTMR��ʱ��(��ʼ����)
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \return ��
 */
void lptmr_timer_enable (amhw_fsl_lptmr_t *p_hw_lptmr)
{
    /* �ر�ʱ�ӣ�LPTMR��ʼ���� */
    amhw_fsl_lptmr_ctl_set(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TEN);
}

/**
 * \brief  ��ֹLPTMR��ʱ��(ֹͣ����)
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \return  ��
 */
void lptmr_timer_disable (amhw_fsl_lptmr_t *p_hw_lptmr)
{
    /* �ر�ʱ�ӣ�TPMֹͣ���� */
    amhw_fsl_lptmr_ctl_clear(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TEN);
}

/**
 * \brief �������
 */
void demo_fsl_hw_lptmr_timing_entry (amhw_fsl_lptmr_t *p_hw_lptmr,
                                     int               inum,
                                     uint32_t          lptmr_clock)
{

    /* �ر�LPTMRģ�� */
    amhw_fsl_lptmr_ctl_clear(p_hw_lptmr, AMHW_FSL_LPTMR_CSR_TEN);

    /* ʱ��Դѡ�� */
    amhw_fsl_lptmr_clock_set(p_hw_lptmr, AMHW_FSL_LPTMR_CLOCK_SRC_MCGIRCLK);

    AM_DBG_INFO("The LPTMR demo for standard timing service\r\n");
    AM_DBG_INFO("The led toggle in 10Hz \r\n");

    /* �ж�Ƶ��10Hz */
    lptmr_timer_init(p_hw_lptmr, lptmr_clock / 10, inum);

    /* ʹ��LPTMR,��ʼ���� */
    lptmr_timer_enable(p_hw_lptmr);

    while (1) {

    }
}

/** [src_fsl_hw_lptmr_timing] */

/* end of file */
