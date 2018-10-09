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
 * \brief SCT 32 λ PWM ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_23(SCT_OUT0) ��� 500Hz �� PWM��ռ�ձ�Ϊ 25%��
 *   2. LED0 ״̬��תƵ��Ϊ 500Hz��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. �������£��¼� 0 ÿ 2000000ns ����� IO ͨ�� 0 �øߣ��������жϣ��������ڣ�
 *       �¼� 1 ÿ 500000ns��ռ���� 25%������� IO ͨ�� 0 ���㣬����ռ�ձȣ�
 *    3. �������£�ÿ�����¼� 0 ʱ���¼� 1 Ҳ��ͬʱ��������ʱ�����¼���������� IO
 *       ͨ�� 0���Ҳ�����ƽ��ͻ����ʱ��Ҫ�ƶ������ͻ�İ취������ָ�����������ϴ�
 *       ��ƽ���䣻
 *    4. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_lpc_drv_sct_timing_pwm.c src_lpc_drv_sct_timing_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  hgo, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_drv_sct_timing_pwm
 * \copydoc demo_lpc_drv_sct_timing_pwm.c
 */

/** [src_lpc_drv_sct_timing_pwm] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc_sct.h"


/**
 * \brief SCT �¼��ж�
 *
 * \param[in] p_arg ʹ�� (#AM_LPC_SCT_EVT_OUT_INT) �жϻص���ָ���Ļص�����
 *
 * return ��
 */
am_local void __sct_evt_irq (void *p_arg)
{
    am_led_toggle(LED0);    /* ��ת LED0 ״̬ */
}

void demo_lpc_drv_sct_timing_pwm_entry (am_lpc_sct_handle_t sct_handle)
{
    uint32_t            period_mat_val    = 0;    /* ����ƥ��ֵ   */
    uint32_t            duty_mat_val      = 0;    /* ռ�ձ�ƥ��ֵ */
    am_lpc_sct_evt_t    lpc_sct_evt;           /* SCT �¼�     */
    /* �¼���ʼ�� */
    am_lpc_sct_evt_init(&lpc_sct_evt);

    /* ��ȡ 500Hz ʱ������ֵ, 500Hz ����ֵΪ 2000000ns */
    period_mat_val = am_lpc_sct_time_to_match(sct_handle, 2000000);

    /* ����һ���¼����ڲ��� 500Hz ���жϣ����ṩ PWM ���� */
    am_lpc_sct_evt_build(&lpc_sct_evt,

                          /* ʹ��ƥ��ͨ�� 0���趨ƥ��ֵ��ֻ���ƥ������ */
                          AM_LPC_SCT_EVT_COND_MAT(0, period_mat_val) |
                          AM_LPC_SCT_EVT_COND_OPR_MATCH,

                          /* ���¼���״̬ 0 �¿ɷ��� */
                          AM_LPC_SCT_EVT_STAT_EN(0),

                          /* ���¼�������SCT ״̬���� */
                          AM_LPC_SCT_EVT_OUT_STAT_ADD(0),

                          /* ���¼�����ʱ��SCT ���������� */
                          AM_LPC_SCT_EVT_OUT_CNT_LIMIT,

                          /* ���¼���ʹ�� DMA ���� */
                          AM_LPC_SCT_EVT_FUNCS_NOT_USE,

                          /* ���¼�������� IO ͨ�� 0 ��λ */
                          AM_LPC_SCT_EVT_OUT_IO_SET(0),

                          /* ���¼������жϣ����������Ļص������Ͳ��� */
                          AM_LPC_SCT_EVT_OUT_INT(__sct_evt_irq, NULL));

    /* �����¼����Ϊ 0�� ����ӵ� SCT */
    am_lpc_sct_evt_add(sct_handle, 0, &lpc_sct_evt);

    /* ��ȡռ 500Hz ʱ�� 25% ����ֵ��ƥ��ֵ����ʱ��Ϊ(2000000 * 25% = 500000)ns */
    duty_mat_val = am_lpc_sct_time_to_match(sct_handle, 500000);

    /* ����һ���¼����ڲ��� 500Hz ���жϣ��Լ��ṩ PWM ���� */
    am_lpc_sct_evt_build(&lpc_sct_evt,

                          /* ʹ��ƥ��ͨ�� 1���趨ƥ��ֵ��ֻ���ƥ������ */
                          AM_LPC_SCT_EVT_COND_MAT(1, duty_mat_val) |
                          AM_LPC_SCT_EVT_COND_OPR_MATCH,

                          /* ���¼���״̬ 0 �¿ɷ��� */
                          AM_LPC_SCT_EVT_STAT_EN(0),

                          /* ���¼�������SCT ״̬���� */
                          AM_LPC_SCT_EVT_OUT_STAT_ADD(0),

                          /* ���¼������Ƽ����� */
                          AM_LPC_SCT_EVT_FUNCS_NOT_USE,

                          /* ���¼���ʹ�� DMA ���� */
                          AM_LPC_SCT_EVT_FUNCS_NOT_USE,

                          /* ���¼�������� IO ͨ�� 0 ���� */
                          AM_LPC_SCT_EVT_OUT_IO_CLR(0),

                          /* ���¼��������ж� */
                          AM_LPC_SCT_EVT_FUNCS_NOT_USE);

    /* �����¼����Ϊ 1�� ����ӵ� SCT */
    am_lpc_sct_evt_add(sct_handle, 1, &lpc_sct_evt);

    /**
     * ��Ϊ�¼� 0 ���¼� 1 ��������� IO ͨ�� 0 �ĵ�ƽ��ͻ��������ָ����ͻ�������
     * �ó�ͻ����ʱ������һ�� PWM ���ڣ�IO ��Ҫ��������
     */
    am_lpc_sct_conflict_res_config(sct_handle,
                                   0,
                                   AM_LPC_SCT_RES_OUT_SET);

    /* ���� SCT */
    am_lpc_sct_start(sct_handle);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_lpc_drv_sct_timing_pwm] */

/* end of file */
