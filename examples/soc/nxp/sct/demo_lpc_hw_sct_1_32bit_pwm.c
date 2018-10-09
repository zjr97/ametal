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
 * \brief SCT 32 λ PWM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_23(SCT_OUT0) ��� 4kHz �� PWM��ռ�ձ�Ϊ 50%��
 *   2. PIO0_27(SCT_OUT4) ��� 4kHz �� PWM��ռ�ձ�Ϊ 25%��
 *   3. LED0 �� 0.2s ��ʱ������˸��
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
 * \snippet demo_lpc_hw_sct_1_32bit_pwm.c src_lpc_hw_sct_1_32bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-19  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_sct_1_32bit_pwm
 * \copydoc demo_lpc_hw_sct_1_32bit_pwm.c
 */

/** [src_lpc_hw_sct_1_32bit_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc_sct.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/**
 * \brief ������ʹ�������� SCT �¼�
 *
 * 1. �¼� 0�����ڲ��� 2 · PWM �Ĺ�ͬ���ڣ�ʹ��ƥ��ͨ�� 0�������Կ���
 *           __PWM0_OUT_NUM��__PWM0_OUT_NUM ��λ���¼��������������㣻
 * 2. �¼� 1�����ڿ��Ƶ� 1 · PWM ��ռ�ձȣ�ʹ��ƥ��ͨ�� __PWM0_MAT_NUM�������Կ���
 *           __PWM0_OUT_NUM ���㣻
 * 3. �¼� 2�����ڿ��Ƶ� 2 · PWM ��ռ�ձȣ�ʹ��ƥ��ͨ�� __PWM1_MAT_NUM�������Կ���
 *           __PWM1_OUT_NUM ���㣻
 * �����¼��� SCT ״̬ 0 ����Ч���¼������� SCT ״̬�������ı䣻
 */
#define __PWM0_MAT_NUM   AMHW_LPC_SCT_MAT(1)   /**< \brief PWM0��ʹ��ƥ�� 1 */
#define __PWM0_OUT_NUM   (0)                   /**< \brief PWM0, SCT_OUT0 */

#define __PWM1_MAT_NUM   AMHW_LPC_SCT_MAT(2)   /**< \brief PWM1��ʹ��ƥ�� 2 */
#define __PWM1_OUT_NUM   (4)                   /**< \brief PWM1, SCT_OUT4 */

/**
 * \brief ��ʼ�� SCT Ϊ 32bit ��ʱ����ʹ�� MATCH0 ����� PWM
 *
 * \param[in] p_hw_sct ָ��SCT�Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_pwm_init (amhw_lpc_sct_t *p_hw_sct)
{

    /* ��ʼ��ƥ�� 0 Ϊ�Զ��޶�����ȷ�� PWM ������ */
    amhw_lpc_sct_config(p_hw_sct,

                        /* ʹ�� 32-bit ��ʱ�� */
                        AMHW_LPC_SCT_CONFIG_32BIT_COUNTER  |

                        /* SCT ʱ��ʹ��ϵͳʱ�� */
                        AMHW_LPC_SCT_CONFIG_CLKMODE_SYSCLK |

                        /* ƥ�� 0 Ϊ�Զ��޶� */
                        AMHW_LPC_SCT_CONFIG_AUTOLIMIT_L );

    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_lpc_sct_regmode_config(p_hw_sct,
                                AMHW_LPC_SCT_MODE_UNIFY,
                                AMHW_LPC_SCT_MAT(0),
                                AMHW_LPC_SCT_MATCAP_MATCH);

    /* ����ƥ��Ĵ�����ƥ��ֵ */
    amhw_lpc_sct_mat_val_set(p_hw_sct,
                             AMHW_LPC_SCT_MODE_UNIFY,
                             AMHW_LPC_SCT_MAT(0), 0);

    /* �����¼� 0 Ϊ PWM0 */
    amhw_lpc_sct_event_ctrl(p_hw_sct,

                            /* �¼� 0 */
                            AMHW_LPC_SCT_EVT(0),

                            /* �¼�������ƥ�� 0 */
                            AMHW_LPC_SCT_EV_CTRL_MATCHSEL(0)    |

                            /* ֻ��ʹ��ָ����ƥ��Ĵ��� */
                            AMHW_LPC_SCT_EV_CTRL_COMBMODE_MATCH |

                            /* STATEV ֵ���� STATE */
                            AMHW_LPC_SCT_EV_CTRL_STATELD_ADD    |

                            /* �� 0��STATE û�иı� */
                            AMHW_LPC_SCT_EV_CTRL_STATEV(0));

    /* ʹ��״̬ 0 ���¼� 0 ���� */
    amhw_lpc_sct_event_state_enable(p_hw_sct,
                                    AMHW_LPC_SCT_EVT(0),
                                    AMHW_LPC_SCT_STATE(0));

    /* �� CLRCTR λ�����������Ϊ 0 */
    amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_CLRCTR_L);

    /* �õ�ǰ״ֵ̬Ϊ 0 */
    amhw_lpc_sct_state_set(p_hw_sct,
                           AMHW_LPC_SCT_MODE_UNIFY,
                           AMHW_LPC_SCT_STATE(0));

    /* Ԥ��ƵΪ 0��ʹ��ϵͳʱ�� */
    amhw_lpc_sct_prescale_set(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY, 0);
}

/**
 * \brief ��ʼ��һ· PWM
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] mat_num  ƥ����
 * \param[in] out_num  ���ͨ�� 0~5
 *
 * \note ƥ�� 0 ����ȷ�� PWM ���ڣ��� mat_num ����Ϊ AMHW_LPC_SCT_MAT(0)��
 */
am_local void __sct_pwm_out_init (amhw_lpc_sct_t *p_hw_sct,
                                  uint32_t        mat_num,
                                  uint8_t         out_num)
{
    uint8_t evt_num = (uint8_t)mat_num;

    if (mat_num == AMHW_LPC_SCT_MAT(0)) {
        return;
    }

    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_lpc_sct_regmode_config(p_hw_sct,

                                /* SCT ģʽΪ UNIFY(1 32-bit ������) */
                                AMHW_LPC_SCT_MODE_UNIFY,

                                /* ƥ��ͨ�� */
                                mat_num,

                                /* ����ƥ��Ĵ��� */
                                AMHW_LPC_SCT_MATCAP_MATCH);

    /* ʹ���¼���ͬ��ƥ��� */
    amhw_lpc_sct_event_ctrl(p_hw_sct,
                            evt_num,
                            AMHW_LPC_SCT_EV_CTRL_MATCHSEL(mat_num) |

                            /* ֻ��ʹ��ָ����ƥ��Ĵ��� */
                            AMHW_LPC_SCT_EV_CTRL_COMBMODE_MATCH    |

                            /*  STATEV ֵ���� STATE */
                            AMHW_LPC_SCT_EV_CTRL_STATELD_ADD       |

                            /* �� 0��STATE û�иı� */
                            AMHW_LPC_SCT_EV_CTRL_STATEV(0));

    /* ʹ��״̬ 0 ���¼� 0 ���� */
    amhw_lpc_sct_event_state_enable(p_hw_sct, evt_num, AMHW_LPC_SCT_STATE(0));

    /* �¼� 0 ��� PWM */
    amhw_lpc_sct_out_set_enable(p_hw_sct, out_num, AMHW_LPC_SCT_EVT(0));

    /* �� PWM ��� */
    amhw_lpc_sct_out_clr_enable(p_hw_sct, out_num, evt_num);

    /**
     * ����Чʱ��������ڽ��������ͻ���ڸ�������£�ռ�ձ�Ϊ 100%��
     * �ʴ�ʱҪ��λ�����
     */
    amhw_lpc_sct_conflict_res_config(p_hw_sct, out_num,
                                     AMHW_LPC_SCT_RES_SET_OUTPUT);

    /* ��λ�����㲻�����ڷ��� */
    amhw_lpc_sct_output_dir_ctrl(p_hw_sct, out_num,
                                 AMHW_LPC_SCT_OUTPUTDIRCTRL_INDEPENDENT);
}

/**
 * \brief ���� PWM ռ�ձ�ʱ��
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] num      ƥ���
 * \param[in] duty_ns  ��Чʱ�䣬��λΪ ns
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹ SCT ��
 *       PWM(__sct_pwm_disable())�����øú�������ʹ�� (__sct_pwm_enable())
 *       ��� SCT û����ֹ����ֵ����д������ƥ��ֵ��������һ������Ч
 */
am_local void __sct_pwm_duty_config (amhw_lpc_sct_t *p_hw_sct,
                                     uint32_t        num,
                                     uint32_t        duty_ns,
                                     uint32_t        frq)
{

    /* ��ʱ��ת��Ϊռ����Чʱ�� */
    uint32_t duty_c = (uint64_t)(duty_ns) *
                      frq /
                      (uint64_t)1000000000;

    /* ռ����Чʱ������Ϊ 1 */
    if (duty_c == 0) {
        duty_c = 1;
    }

    /* ֻ�д��� HALT ״̬��ʱ����������ƥ��Ĵ���ʱ */
    if (amhw_lpc_sct_halt_check(p_hw_sct,
                                AMHW_LPC_SCT_MODE_UNIFY) == AM_TRUE ) {

        amhw_lpc_sct_mat_val_set(p_hw_sct,
                                 AMHW_LPC_SCT_MODE_UNIFY,
                                 num,
                                 duty_c - 1);
    }

    /* ��������ƥ��ֵ */
    amhw_lpc_sct_mat_reload_val_set(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_UNIFY,
                                    num,
                                    duty_c - 1);

}

/**
 * \brief ʹ�� SCT �� PWM ���
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_pwm_enable (amhw_lpc_sct_t *p_hw_sct)
{

    /* �����ֹλ��SCT ��ʼ���� */
    amhw_lpc_sct_ctrl_clr(p_hw_sct,
                          AMHW_LPC_SCT_CTRL_STOP_L | AMHW_LPC_SCT_CTRL_HALT_L);
}

/**
 * \brief ���� SCT �� PWM ���
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_pwm_disable (amhw_lpc_sct_t *p_hw_sct)
{

    /* ����ֹλ��SCT ��ֹ���� */
    amhw_lpc_sct_ctrl_set(p_hw_sct,
                          AMHW_LPC_SCT_CTRL_STOP_L | AMHW_LPC_SCT_CTRL_HALT_L);
}

/**
 * \brief ���� PWM ����
 *
 * \param[in] p_hw_sct  ָ�� SCT �Ĵ������ָ��
 * \param[in] period_ns ���ڣ���λΪ ns
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹ SCT ��
 *       PWM(__sct_pwm_disable())�����øú�������ʹ�� (__sct_pwm_enable())
 */
am_local void __sct_pwm_period_config (amhw_lpc_sct_t *p_hw_sct,
                                       uint32_t        period_ns,
                                       uint32_t        frq)
{

    /* ��ʱ��ת��Ϊ���� */
    uint32_t period_c = (uint64_t)(period_ns) *
                        frq /
                        (uint64_t)1000000000;

    /* ��������Ϊ 1 */
    if (period_c == 0) {
        period_c = 1;
    }

    /* ֻ�д��� HALT ״̬��ʱ����������ƥ��Ĵ���ʱ */
    if (amhw_lpc_sct_halt_check(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY) == AM_TRUE ) {

        amhw_lpc_sct_mat_val_set(p_hw_sct,
                                 AMHW_LPC_SCT_MODE_UNIFY,
                                 AMHW_LPC_SCT_MAT(0),
                                 period_c - 1);
    }

    /* ��������ƥ��ֵ */
    amhw_lpc_sct_mat_reload_val_set(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_UNIFY,
                                    AMHW_LPC_SCT_MAT(0),
                                    period_c - 1);
}

void demo_lpc_hw_sct_1_32bit_pwm_entry (amhw_lpc_sct_t *p_hw_sct, uint32_t frq)
{
    /* �ȹر� PWM ��� */
    __sct_pwm_disable(p_hw_sct);

    /* ��ʼ�� SCT ����� PWM */
    __sct_pwm_init(p_hw_sct);

    /* PWM0 ��ʼ�� */
    __sct_pwm_out_init(p_hw_sct, __PWM0_MAT_NUM, __PWM0_OUT_NUM);

    /* PWM1 ��ʼ�� */
    __sct_pwm_out_init(p_hw_sct, __PWM1_MAT_NUM, __PWM1_OUT_NUM);

    /* ��������Ϊ 250000ns(4KHz) */
    __sct_pwm_period_config(p_hw_sct, 250000, frq);

    /* ���� PWM0 ռ�ձ� */
    __sct_pwm_duty_config(p_hw_sct, __PWM0_MAT_NUM, 125000, frq);

    /* ���� PWM1 ռ�ձ� */
    __sct_pwm_duty_config(p_hw_sct, __PWM1_MAT_NUM, 62500, frq);

    /* ʹ�� SCT0����� PWM */
    __sct_pwm_enable(p_hw_sct);

    AM_FOREVER {
        am_led_toggle(LED0);
        am_mdelay(200);
    }
}
/** [src_lpc_hw_sct_1_32bit_pwm] */

/* end of file */
