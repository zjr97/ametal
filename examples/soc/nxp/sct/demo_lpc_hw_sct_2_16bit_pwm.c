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
 * \brief SCT ��Ϊ 2 �� 16 λ��ʱ����� PWM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_23(SCT_OUT0) ��� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *   2. PIO0_27(SCT_OUT2) ��� 1KHz �� PWM��ռ�ձ�Ϊ 25%��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. SCT ʹ�� 32 λ��������ֻ�ܲ���һ������� PWM������ PWM ���ʹ��ͬһƵ�ʣ�
 *       �����������ƥ��ֵΪ 0xFFFFFFFF��
 *    3. SCT ʹ�� 16 λ�����������Բ��� 2 ������� PWM��ÿһ�� PWM �����ʹ��ͬһ
 *       Ƶ�ʣ������������ƥ��ֵΪ 0xFFFF��
 *    4. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_lpc_hw_sct_2_16bit_pwm.c src_lpc_hw_sct_2_16bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-19  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_sct_2_16bit_pwm
 * \copydoc demo_lpc_hw_sct_2_16bit_pwm.c
 */

/** [src_lpc_hw_sct_2_16bit_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc_sct.h"
#include "demo_nxp_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define   __SCT_HANDLE_H        1              /**< \brief ���ڲ������� */
#define   __SCT_HANDLE_L        0              /**< \brief ���ڲ������� */

/**
 * \brief ������ʹ���� 4 �� SCT �¼�
 *
 * 1. �¼� 0�����ڲ��� L · PWM �����ڣ�ʹ��ƥ��ͨ�� 0 �ĵ� 16 λ��������
 *           __PWM_L_0_OUT_NUM ��λ���¼�����������������㣻
 * 2. �¼� 7�����ڲ��� H · PWM �����ڣ�ʹ��ƥ��ͨ�� 0 �ĸ� 16 λ��������
 *           __PWM_H_0_OUT_NUM ��λ���¼�����������������㣻
 * 2. �¼� 1�����ڿ��� L · PWM ��ռ�ձȣ�ʹ��ƥ��ͨ�� __PWM_L_0_MAT_NUM �ĵ��飬
 *           �����Կ��� __PWM_L_0_OUT_NUM ���㣻
 * 3. �¼� 2�����ڿ��� H · PWM ��ռ�ձȣ�ʹ��ƥ��ͨ�� __PWM_H_0_MAT_NUM �ĸ��飬
 *           �����Կ��� __PWM_H_0_OUT_NUM ���㣻
 * �����¼��� SCT ״̬ 0 ����Ч���¼������� SCT ״̬�������ı䣻
 */

/**
 * \name ������� PWM
 * @{
 */

/** \brief ���� PWM0 ʹ��ƥ�� 1 ��λ */
#define __PWM_L_0_MAT_NUM    AMHW_LPC_SCT_MAT(1)

/** \brief ���� PWM0 ʹ���¼� 1 */
#define __PWM_L_0_EVT_NUM    AMHW_LPC_SCT_EVT(1)

/** \brief ���� PWM0��SCT_OUT1 */
#define __PWM_L_0_OUT_NUM    AMHW_LPC_SCT_OUT(1)
/**
 * @}
 */

/**
 * \name ������� PWM
 * @{
 */

/** \brief ���� PWM0 ʹ��ƥ�� 1 ��λ */
#define __PWM_H_0_MAT_NUM    AMHW_LPC_SCT_MAT(1)

/** \brief ���� PWM0 ʹ���¼� 2 */
#define __PWM_H_0_EVT_NUM    AMHW_LPC_SCT_EVT(2)

/** \brief ���� PWM0, SCT_OUT2 */
#define __PWM_H_0_OUT_NUM    AMHW_LPC_SCT_OUT(2)
/**
 * @}
 */

/**
 * \brief ���� 16 λ��ʱ��ָ������ֵ����ѵ�Ԥ��Ƶֵ��ƥ��Ĵ���ֵ
 *
 * \param[in]  count   ����ֵ
 * \param[out] p_match ָ��ʱ��ƥ��ֵ��ָ��
 *
 * \return ������� 8bits Ԥ��Ƶֵ
 */
am_local uint32_t __prescale_and_match_calculate (uint32_t  count,
                                                  uint32_t *p_match)
{
    uint32_t match, min_remainder, prescale;
    uint32_t result_quot, result_rem;

    min_remainder = count;
    prescale      = 1;
    *p_match      = 65536;

    /**
     * ����ֵ��СΪ 65536��
     * Ԥ��ƵΪ 1��ƥ��ֵ���ڼ���ֵ
     */
    if (count <= 65536) {
        prescale      = 1;
        *p_match      = count;
        return prescale;
    }

    /* ���ƥ��ֵ��ֱ���ҵ���õ� */
    for (match = 65536; match > 0; match--) {

        result_quot = count / match;
        result_rem  = count % match;

        /**
         * ����Ԥ��Ƶ���Ϊ 8bits��result_quot �����ֵΪ 256��������� 256������ֵ
         * ���޷��ﵽ
         */
        if (result_quot <= 256) {
            if (result_rem == 0) {

                /* ��������ʵ�Ԥ��Ƶ��ƥ��ֵ */
                prescale = result_quot;
                *p_match = match;
                break;

            } else if (result_rem < min_remainder) {

                /* ��������ʵ�Ԥ��Ƶ��ƥ��ֵ */
                min_remainder = result_rem;
                prescale      = result_quot;
                *p_match      = match;
            }
        }
    }

    return prescale;
}

/**
 * \brief ��ʼ�� SCT ���� PWM
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] handle   ���飺#__SCT_HANDLE_H�����飺#__SCT_HANDLE_L
 *
 * \return ��
 *
 * \note ����ʹ���¼� 12��ƥ�� 0 �ĸ� 16 λ bits ��������
 *       ����ʹ���¼� 0��ƥ�� 0 �ĵ� 16 λ bits ��������
 */
am_local void __sct_2_16bit_pwm_init (amhw_lpc_sct_t *p_hw_sct, uint8_t handle)
{
    uint32_t            event_num = 0;
    uint32_t            event_ctl = 0;
    amhw_lpc_sct_mode_t sct_mode  = AMHW_LPC_SCT_MODE_UNIFY;

    if (handle == __SCT_HANDLE_H) {

        sct_mode  = AMHW_LPC_SCT_MODE_SEPARATE_H;
        event_num = AMHW_LPC_SCT_EVT(7);        /* ����ʹ���¼� 7 */

        /* �¼�����ƥ��� 16 λ */
        event_ctl = AMHW_LPC_SCT_EV_CTRL_HEVENT_H;

    } else {
        sct_mode  = AMHW_LPC_SCT_MODE_SEPARATE_L;
        event_num = AMHW_LPC_SCT_EVT(0);         /* ����ʹ���¼� 0 */

        /* �¼�����ƥ��� 16 λ */
        event_ctl = AMHW_LPC_SCT_EV_CTRL_HEVENT_L;
    }

    /* ����ƥ��/����Ĵ���Ϊƥ��Ĵ��� */
    amhw_lpc_sct_regmode_config(p_hw_sct,
                                sct_mode,
                                AMHW_LPC_SCT_MAT(0),
                                AMHW_LPC_SCT_MATCAP_MATCH);

    amhw_lpc_sct_mat_val_set(p_hw_sct, sct_mode, AMHW_LPC_SCT_MAT(0), 0);


    /* �����¼� 0 */
    amhw_lpc_sct_event_ctrl(p_hw_sct,
                            event_num,

                            /* ѡ���״̬��ƥ��Ĵ��� */
                            event_ctl                           |

                            /* �¼�����ƥ�� 0 */
                            AMHW_LPC_SCT_EV_CTRL_MATCHSEL(0)    |

                            /* ֻ��ʹ��ָ��ƥ�� */
                            AMHW_LPC_SCT_EV_CTRL_COMBMODE_MATCH |

                            /*  STATEV ֵ���� STATE */
                            AMHW_LPC_SCT_EV_CTRL_STATELD_ADD    |

                            /* �� 0��STATE û�иı� */
                            AMHW_LPC_SCT_EV_CTRL_STATEV(0));

    /* ʹ��״̬ 0 �����¼� */
    amhw_lpc_sct_event_state_enable(p_hw_sct,
                                    event_num,
                                    AMHW_LPC_SCT_STATE(0));

    /* ���õ�ǰ״ֵ̬Ϊ 0 */
    amhw_lpc_sct_state_set(p_hw_sct, sct_mode, AMHW_LPC_SCT_STATE(0));

    if (handle == __SCT_HANDLE_H) {

    /* �� CLRCTR λ������������Ϊ 0 */
        amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_CLRCTR_H);
    } else {
        amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_CLRCTR_L);
    }
}

/**
 * \brief ��ʼ�� SCT Ϊ 2 �� PWM ���
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_pwm_init (amhw_lpc_sct_t *p_hw_sct)
{
    amhw_lpc_sct_config(p_hw_sct,

                        /* ��ʱ����Ϊ 2 �� 16 λ��ʱ�� */
                        AMHW_LPC_SCT_CONFIG_16BIT_COUNTER  |

                        /* ����ƥ�� 0 �Զ����� */
                        AMHW_LPC_SCT_CONFIG_AUTOLIMIT_L    |

                        /* ����ƥ�� 0 �Զ����� */
                        AMHW_LPC_SCT_CONFIG_AUTOLIMIT_H    |

                        /* SCT ʱ��ʹ��ϵͳʱ�� */
                        AMHW_LPC_SCT_CONFIG_CLKMODE_SYSCLK);

    __sct_2_16bit_pwm_init(p_hw_sct, __SCT_HANDLE_L);
    __sct_2_16bit_pwm_init(p_hw_sct, __SCT_HANDLE_H);
}

/**
 * \brief ʹ�� SCT ��� PWM
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] handle   ���飺#__SCT_HANDLE_H�����飺#__SCT_HANDLE_L
 *
 * \return  ��
 */
am_local void __sct_2_16bit_pwm_enable (amhw_lpc_sct_t *p_hw_sct,
                                        uint8_t         handle)
{
    if (handle == __SCT_HANDLE_H) {

        amhw_lpc_sct_ctrl_halt_to_stop(p_hw_sct,
                                       AMHW_LPC_SCT_MODE_SEPARATE_H);

        /* ���ֹͣλ��SCT �����������ʼ���� */
        amhw_lpc_sct_ctrl_clr(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_H);

        if (amhw_lpc_sct_halt_check(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_SEPARATE_L) == AM_TRUE) {

            /* ���鲻����ֹ�������Ϊֹͣ��������鲻����� PWM */
            amhw_lpc_sct_ctrl_halt_to_stop(p_hw_sct,
                                           AMHW_LPC_SCT_MODE_SEPARATE_L);
        }

    } else {

        /* ���ֹͣλ��SCT �����������ʼ���� */
        amhw_lpc_sct_ctrl_clr(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_L |
                                        AMHW_LPC_SCT_CTRL_HALT_L);
    }
}

/**
 * \brief ��ֹ SCT ��� PWM
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] handle   ���飺#__SCT_HANDLE_H�����飺#__SCT_HANDLE_L
 *
 * \return ��
 */
am_local void __sct_2_16bit_pwm_disable (amhw_lpc_sct_t *p_hw_sct,
                                         uint8_t         handle)
{
    if (handle == __SCT_HANDLE_H) {

        /* ����ֹλ��SCT �����������ֹ���� */
        amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_H |
                                        AMHW_LPC_SCT_CTRL_HALT_H);

    } else {

        /* ������������ */
        if (amhw_lpc_sct_halt_check(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_SEPARATE_H) == AM_FALSE &&
            amhw_lpc_sct_stop_check(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_SEPARATE_H) == AM_FALSE){

            /* ���鲻����ֹ�������Ϊֹͣ��������鲻����� PWM */
            amhw_lpc_sct_ctrl_halt_to_stop(p_hw_sct,
                                           AMHW_LPC_SCT_MODE_SEPARATE_L);

        } else {

            /* ����ֹλ��SCT �����������ֹ���� */
            amhw_lpc_sct_ctrl_set(p_hw_sct,
                                  AMHW_LPC_SCT_CTRL_STOP_L |
                                  AMHW_LPC_SCT_CTRL_HALT_L);
        }
    }
}

/**
 * \brief ��ʼ�����һ· PWM
 *
 * \param[in] p_hw_sct  ָ�� SCT �Ĵ������ָ��
 * \param[in] handle    ���飺#__SCT_HANDLE_H�����飺#__SCT_HANDLE_L
 * \param[in] match_num ƥ����
 * \param[in] event_num �¼����
 * \param[in] out_num   ���ͨ����Ϊ 0~5 ֮��
 *
 * \note ƥ�� 0 ����ȷ�����ڣ�match_num ����ʹ�� AMHW_LPC_SCT_MAT(0)
 *
 */
am_local void __sct_pwm_out_init (amhw_lpc_sct_t *p_hw_sct,
                                  uint8_t         handle,
                                  uint32_t        match_num,
                                  uint32_t        event_num,
                                  uint8_t         out_num)
{
    uint32_t            hevent_mode;
    amhw_lpc_sct_mode_t sct_mode;

    /* ƥ�� 0 ʹ���Զ����� */
    if (match_num == AMHW_LPC_SCT_MAT(0)) {
        return;
    }

    /* �¼� 0���¼� 7 ����������� */
    if (event_num == AMHW_LPC_SCT_EVT(0) ||
        event_num == AMHW_LPC_SCT_EVT(7)) {
        return;
    }

    if (handle == __SCT_HANDLE_H) {
        sct_mode    = AMHW_LPC_SCT_MODE_SEPARATE_H;
        hevent_mode = AMHW_LPC_SCT_EV_CTRL_HEVENT_H;
    } else {
        sct_mode    = AMHW_LPC_SCT_MODE_SEPARATE_L;
        hevent_mode = AMHW_LPC_SCT_EV_CTRL_HEVENT_L;
    }

    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_lpc_sct_regmode_config(p_hw_sct,
                                sct_mode,
                                match_num,
                                AMHW_LPC_SCT_MATCAP_MATCH);

    /* �����¼� */
    amhw_lpc_sct_event_ctrl(p_hw_sct,
                            event_num,
                            hevent_mode |
                            AMHW_LPC_SCT_EV_CTRL_MATCHSEL(match_num) |
                            AMHW_LPC_SCT_EV_CTRL_COMBMODE_MATCH |
                            AMHW_LPC_SCT_EV_CTRL_STATELD_ADD |
                            AMHW_LPC_SCT_EV_CTRL_STATEV(0));

    /* ʹ��״̬ 0 �в����¼� */
    amhw_lpc_sct_event_state_enable(p_hw_sct,
                                    event_num,
                                    AMHW_LPC_SCT_STATE(0));

    if (sct_mode == AMHW_LPC_SCT_MODE_SEPARATE_H) {

        /* �����¼� 7 Ϊ PWM ��� */
        amhw_lpc_sct_out_set_enable(p_hw_sct,
                                    out_num,
                                    AMHW_LPC_SCT_EVT(7));
    } else {

        /* �����¼� 0 Ϊ PWM ��� */
        amhw_lpc_sct_out_set_enable(p_hw_sct,
                                    out_num,
                                    AMHW_LPC_SCT_EVT(0));
    }

    /* �¼���� PWM ��� */
    amhw_lpc_sct_out_clr_enable(p_hw_sct, out_num, event_num);

    /**
     * ����Чʱ��������ڽ��������ͻ���ڸ�������£�ռ�ձ�Ϊ 100%��
     * �ʴ�ʱҪ��λ���
     */
    amhw_lpc_sct_conflict_res_config(p_hw_sct,
                                     out_num,
                                     AMHW_LPC_SCT_RES_SET_OUTPUT);

    /* ��λ�����㲻�����ڷ��� */
    amhw_lpc_sct_output_dir_ctrl(p_hw_sct,
                                 out_num,
                                 AMHW_LPC_SCT_OUTPUTDIRCTRL_INDEPENDENT);
}

/**
 * \brief ���� PWM ����
 *
 * \param[in] p_hw_sct  ָ�� SCT �Ĵ������ָ��
 * \param[in] handle    ���飺#__SCT_HANDLE_H�����飺#__SCT_HANDLE_L
 * \param[in] period_ns ���ڣ���λΪ ns
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹ SCT �� PWM��
 *       ���øú�������ʹ��
 */
am_local void __sct_pwm_period_config(amhw_lpc_sct_t *p_hw_sct,
                                      uint8_t         handle,
                                      uint32_t        period_ns,
                                      uint32_t        frq)
{

    /* ת��ʱ��Ϊ���� */
    uint32_t            period_c = (uint64_t)(period_ns) * 
                                    frq /
                                   (uint64_t)1000000000;
    uint32_t            prescale = 0;
    uint32_t            match    = 0;
    amhw_lpc_sct_mode_t sct_mode;

    if (handle == __SCT_HANDLE_H) {
        sct_mode = AMHW_LPC_SCT_MODE_SEPARATE_H;
    } else {
        sct_mode = AMHW_LPC_SCT_MODE_SEPARATE_L;
    }

    /* ��������Ϊ 1 */
    if (period_c == 0) {
        period_c = 1;
    }

    /**
     * ������������Ϊ��65536 * 256(Ԥ��Ƶ), ���ʱ��Ϊ��
     * 65536 / (g_system_clkfreq / 256) = 65536 * 256 / g_system_clkfreq.
     *
     * �� 100MHz ʱ�����ʱ��Ϊ��256 * 65536 / 100 us =  167772 us
     * �� 12MHz ʱ�����ʱ��Ϊ��256 * 65536 /  12 us  =  1398101 us
     * �� 24MHz ʱ�����ʱ��Ϊ��256 * 65536 /  24 us  =  699051 us
     */
    if (period_c >= 256 * 65536) {
        period_c = 256 * 65536;     /* �������Ϊ 256 * 65536 */
    }

    /* ����Ԥ��Ƶ��ƥ��ֵ */
    prescale = __prescale_and_match_calculate(period_c, &match);

    prescale -= 1;

    if (prescale != amhw_lpc_sct_prescale_get(p_hw_sct, sct_mode)) {

        if (amhw_lpc_sct_halt_check(p_hw_sct, sct_mode) == AM_TRUE ) {
            amhw_lpc_sct_prescale_set(p_hw_sct, sct_mode, prescale);

        } else {
            __sct_2_16bit_pwm_disable(p_hw_sct, handle);
            amhw_lpc_sct_prescale_set(p_hw_sct, sct_mode, prescale);
            __sct_2_16bit_pwm_enable(p_hw_sct, handle);
        }
    }

    /* ֻ�д��� HALT ״̬��ʱ����������ƥ��Ĵ���ʱ */
    if (amhw_lpc_sct_halt_check(p_hw_sct, sct_mode) == AM_TRUE ) {
        amhw_lpc_sct_mat_val_set(p_hw_sct,
                                 sct_mode,
                                 AMHW_LPC_SCT_MAT(0),
                                 match - 1);
    }

    /* ��������ƥ��ֵ */
    amhw_lpc_sct_mat_reload_val_set(p_hw_sct,
                                    sct_mode,
                                    AMHW_LPC_SCT_MAT(0),
                                    match - 1);
}

/**
 * \brief ���� PWM ��Чʱ�䣨ռ�ձȣ�
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] handle   ���飺#__SCT_HANDLE_H�����飺#__SCT_HANDLE_L
 * \param[in] mat_num  ƥ����
 * \param[in] duty_ns  ��Чʱ�䣬��λΪ ns
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹ SCT �� PWM(sct_pwm_disable())��
 *       ���øú�������ʹ��(sct_pwm_enable())����� SCT û����ֹ����ֵ����д��
 *       ����ƥ��ֵ��������һ������Ч
 */
am_local void __sct_pwm_duty_config (amhw_lpc_sct_t *p_hw_sct,
                                     uint8_t         handle,
                                     uint32_t        mat_num,
                                     uint32_t        duty_ns,
                                     uint32_t        frq)
{
    uint32_t            clkfreq  = 0;
    uint32_t            duty_c   = 0;
    amhw_lpc_sct_mode_t sct_mode = AMHW_LPC_SCT_MODE_UNIFY;

    if (handle == __SCT_HANDLE_H) {
        sct_mode = AMHW_LPC_SCT_MODE_SEPARATE_H;

    } else {
        sct_mode = AMHW_LPC_SCT_MODE_SEPARATE_L;
    }

    /* ��ʱ��ת��Ϊ���� */
    clkfreq = frq / (amhw_lpc_sct_prescale_get(p_hw_sct, sct_mode) + 1);

    duty_c = (uint64_t)(duty_ns) * (clkfreq) / (uint64_t)1000000000;

    /* ռ����Чʱ����СΪ 1 */
    if (duty_c == 0) {
        duty_c = 1;
    }

    if (duty_c > 65536) {
        duty_c = 65536;
    }

    if (amhw_lpc_sct_halt_check(p_hw_sct,
                                AMHW_LPC_SCT_MODE_UNIFY) == AM_TRUE ) {

        amhw_lpc_sct_mat_val_set(p_hw_sct, sct_mode, mat_num, duty_c - 1);
    }

    /* ��������ƥ��ֵ */
    amhw_lpc_sct_mat_reload_val_set(p_hw_sct, sct_mode, mat_num, duty_c - 1);
}


void demo_lpc_hw_sct_2_16bit_pwm_entry(amhw_lpc_sct_t *p_hw_sct,
                                       int             frq)
{
/* ��ʼ�� SCT Ϊ 2 �� PWM ��� */
    __sct_pwm_init(p_hw_sct);

    /* SCT_OUT1������ */
    __sct_pwm_out_init(p_hw_sct,
                       __SCT_HANDLE_L,       /* ���� */
                       __PWM_L_0_MAT_NUM,    /* ƥ��� */
                       __PWM_L_0_EVT_NUM,    /* �¼��� */
                       __PWM_L_0_OUT_NUM);   /* ����� */

    /* SCT_OUT2������ */
    __sct_pwm_out_init(p_hw_sct,
                       __SCT_HANDLE_H,
                       __PWM_H_0_MAT_NUM,
                       __PWM_H_0_EVT_NUM,
                       __PWM_H_0_OUT_NUM);

    /**
     * ��������Ϊ 250 000ns(4KHz)��
     * �� 100MHz ʱ���������Ϊ��256 * 65536 / 100 us  =  167772 us
     * �� 24MHz  ʱ���������Ϊ��256 * 65536 /  24 us  =  699051 us
     * ��������ϵͳʱ��Ϊ 24MHz
     */
    __sct_pwm_period_config(p_hw_sct, __SCT_HANDLE_L, 250000, frq);

    /* ��������Ϊ 1000000ns(1KHz) */
    __sct_pwm_period_config(p_hw_sct, __SCT_HANDLE_H, 1000000, frq);

    /* ���� PWM0 ��Чʱ�� */
    __sct_pwm_duty_config(p_hw_sct,
                        __SCT_HANDLE_L,
                        __PWM_L_0_MAT_NUM,
                        250000 / 2,
                        frq);

    /* ���� PWM0 ��Чʱ�� */
    __sct_pwm_duty_config(p_hw_sct,
                          __SCT_HANDLE_H,
                          __PWM_H_0_MAT_NUM,
                          1000000 / 4,
                          frq);

    __sct_2_16bit_pwm_enable(p_hw_sct, __SCT_HANDLE_L); /* ʹ�ܵ��� PWM */
    __sct_2_16bit_pwm_enable(p_hw_sct, __SCT_HANDLE_H); /* ʹ�ܸ��� PWM */

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_lpc_hw_sct_2_16bit_pwm] */

/* end of file */
