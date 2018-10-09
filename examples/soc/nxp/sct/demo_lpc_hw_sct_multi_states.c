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
 * \brief SCT ������״̬���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_16(SCT_OUT5)����������Ρ�
 *
 * \code
 *  |---         ״̬0        ---|--- ״̬1 ---|--- ״̬0      ......
 *             _____     _____     ___         __            ___
 *            |     |   |     |   |   |       |  |          |     ......
 *  __________|     |___|     |___|   |_______|  |__________|
 *
 *  0         10    15  18    23  26  3      10  12         10     (ms)
 *                              (״̬1, 0)     (״̬0, 0)
 *          �¼� 0  1   2      3   4   5      6  7
 * \endcode
 *
 * \note
 *    1. ���� PIO0_16(SCT_OUT5) ���ŵ��߼������ǣ����ῴ���ò��Σ�ǰ 10ms Ϊ�͵�ƽ��
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_lpc_hw_sct_multi_states.c src_lpc_hw_sct_multi_states
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-08  hgo, modified
 * - 1.00 14-12-09  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_sct_multi_states
 * \copydoc demo_lpc_hw_sct_multi_states.c
 */

/** [src_lpc_hw_sct_multi_states] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc_sct.h"

#define   __OUT_NUM       AMHW_LPC_SCT_OUT(5)       /**< \brief ʹ�� SCT_OUT5 */

/**
 * \brief ��ʼ��ƥ��Ĵ���
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] num      ƥ��
 * \param[in] ms       ƥ��ʱ�䣬��λΪ ms
 *
 * \return ��
 */
am_local void __sct_match_init (amhw_lpc_sct_t *p_hw_sct,
                                uint32_t        num,
                                uint32_t        ms,
                                uint32_t        frq)
{
    uint32_t ms_ticks = frq / 1000;

    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_lpc_sct_regmode_config(p_hw_sct,
                                AMHW_LPC_SCT_MODE_UNIFY,
                                AMHW_LPC_SCT_MAT(num),
                                AMHW_LPC_SCT_MATCAP_MATCH);

    /* ����ƥ�� 0 ������ƥ��ֵ */
    amhw_lpc_sct_mat_val_set(p_hw_sct,
                             AMHW_LPC_SCT_MODE_UNIFY,
                             num,
                             ms_ticks * ms - 1);

    amhw_lpc_sct_mat_reload_val_set(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_UNIFY,
                                    num,
                                    ms_ticks * ms - 1);
}

/**
 * \brief ��ʼ��һ���¼�
 *
 * \param[in] p_hw_sct  ָ�� SCT �Ĵ������ָ��
 * \param[in] evt_num   �¼�
 * \param[in] match_num ƥ��
 * \param[in] state_num ״̬
 * \param[in] state_ld  0: state_ev ����״̬  1: the state_ev ����Ϊ״̬
 * \param[in] state_ev  ��ֵ�ı�״̬
 *
 * \return ��
 */
am_local void __sct_evt_init (amhw_lpc_sct_t *p_hw_sct,
                              uint32_t        evt_num,
                              uint32_t        match_num,
                              uint32_t        state_num,
                              uint32_t        state_ld,
                              uint32_t        state_ev)
{
    if(state_ld == 0) {
        state_ld = AMHW_LPC_SCT_EV_CTRL_STATELD_ADD;
    } else {
        state_ld = AMHW_LPC_SCT_EV_CTRL_STATELD_LOAD;
    }

    /* �����¼� 0 ���� */
    amhw_lpc_sct_event_ctrl(p_hw_sct,
                            evt_num,

                            /* �¼�����ƥ�� */
                            AMHW_LPC_SCT_EV_CTRL_MATCHSEL(match_num) |

                            /* ʹ��ָ��ƥ�� */
                            AMHW_LPC_SCT_EV_CTRL_COMBMODE_MATCH       |
                            state_ld                                  |
                            AMHW_LPC_SCT_EV_CTRL_STATEV(state_ev));

    /* ʹ���¼����� */
    amhw_lpc_sct_event_state_enable(p_hw_sct, evt_num, state_num);
}

/**
 * \brief ʹ�� SCT ������Ӳ���
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_init (amhw_lpc_sct_t *p_hw_sct,
                          uint32_t        frq)
{
    amhw_lpc_sct_config(p_hw_sct,

                        /* �� 32 λ��ʱ�� */
                        AMHW_LPC_SCT_CONFIG_32BIT_COUNTER  |

                        /* ϵͳʱ���� SCT ʱ�� */
                        AMHW_LPC_SCT_CONFIG_CLKMODE_SYSCLK);

    __sct_match_init(p_hw_sct, AMHW_LPC_SCT_MAT(0), 10, frq); /* ����ƥ�� 0 ֵΪ 10ms */
    __sct_match_init(p_hw_sct, AMHW_LPC_SCT_MAT(1), 15, frq); /* ����ƥ�� 1 ֵΪ 15ms */
    __sct_match_init(p_hw_sct, AMHW_LPC_SCT_MAT(2), 18, frq); /* ����ƥ�� 2 ֵΪ 18ms */
    __sct_match_init(p_hw_sct, AMHW_LPC_SCT_MAT(3), 23, frq); /* ����ƥ�� 3 ֵΪ 23ms */
    __sct_match_init(p_hw_sct, AMHW_LPC_SCT_MAT(4), 26, frq); /* ����ƥ�� 4 ֵΪ 26ms */
    __sct_match_init(p_hw_sct, AMHW_LPC_SCT_MAT(5), 3 , frq); /* ����ƥ�� 5 ֵΪ 3ms */
    __sct_match_init(p_hw_sct, AMHW_LPC_SCT_MAT(6), 12, frq); /* ����ƥ�� 6 ֵΪ 12ms */

    amhw_lpc_sct_output_state_clr(p_hw_sct, __OUT_NUM);  /* ������ */

    /* ״̬ 0 �¼����� */

    /* �¼� 0������ƥ�� 0�����ı�״ֵ̬����� */
    __sct_evt_init(p_hw_sct,
                   AMHW_LPC_SCT_EVT(0),
                   AMHW_LPC_SCT_MAT(0),
                   AMHW_LPC_SCT_STATE(0),
                   0,
                   0);
    amhw_lpc_sct_out_set_enable(p_hw_sct, __OUT_NUM, AMHW_LPC_SCT_EVT(0));

    /* �¼� 1������ƥ�� 1�����ı�״ֵ̬�������� */
    __sct_evt_init(p_hw_sct,
                   AMHW_LPC_SCT_EVT(1),
                   AMHW_LPC_SCT_MAT(1),
                   AMHW_LPC_SCT_STATE(0),
                   0,
                   0);
    amhw_lpc_sct_out_clr_enable(p_hw_sct, __OUT_NUM, AMHW_LPC_SCT_EVT(1));

    /* �¼� 2������ƥ�� 2�����ı�״ֵ̬����� */
    __sct_evt_init(p_hw_sct,
                   AMHW_LPC_SCT_EVT(2),
                   AMHW_LPC_SCT_MAT(2),
                   AMHW_LPC_SCT_STATE(0),
                   0,
                   0);
    amhw_lpc_sct_out_set_enable(p_hw_sct, __OUT_NUM, AMHW_LPC_SCT_EVT(2));

    /* �¼� 3������ƥ�� 3�����ı�״ֵ̬�������� */
    __sct_evt_init(p_hw_sct,
                   AMHW_LPC_SCT_EVT(3),
                   AMHW_LPC_SCT_MAT(3),
                   AMHW_LPC_SCT_STATE(0),
                   0,
                   0);
    amhw_lpc_sct_out_clr_enable(p_hw_sct, __OUT_NUM, AMHW_LPC_SCT_EVT(3));

    /* �¼� 4������ƥ�� 4���ı�״ֵ̬Ϊ 1�������� */
    __sct_evt_init(p_hw_sct,
                   AMHW_LPC_SCT_EVT(4),
                   AMHW_LPC_SCT_MAT(4),
                   AMHW_LPC_SCT_STATE(0),
                   0,
                   1);
    amhw_lpc_sct_out_set_enable(p_hw_sct, __OUT_NUM, AMHW_LPC_SCT_EVT(4));

    /* ��״̬ 0 �У��¼� 4 ��Ϊ�����¼� */
    amhw_lpc_sct_event_limit_enable(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_UNIFY,
                                    AMHW_LPC_SCT_EVT(4));

    /* ״̬ 1 �¼����� */

    /* �¼� 5������ƥ�� 5(3ms)�����ı�״ֵ̬�������� */
    __sct_evt_init(p_hw_sct,
                   AMHW_LPC_SCT_EVT(5),
                   AMHW_LPC_SCT_MAT(5),
                   AMHW_LPC_SCT_STATE(1),
                   0,
                   0);
    amhw_lpc_sct_out_clr_enable(p_hw_sct, __OUT_NUM, AMHW_LPC_SCT_EVT(5));

    /* �¼� 6������ƥ�� 0(10ms)�����ı�״ֵ̬����� */
    __sct_evt_init(p_hw_sct,
                   AMHW_LPC_SCT_EVT(6),
                   AMHW_LPC_SCT_MAT(0),
                   AMHW_LPC_SCT_STATE(1),
                   0,
                   0);
    amhw_lpc_sct_out_set_enable(p_hw_sct, __OUT_NUM, AMHW_LPC_SCT_EVT(6));

    /* �¼� 7������ƥ�� 6(12ms)���ı�״ֵ̬Ϊ 0�������� */
    __sct_evt_init(p_hw_sct,
                   AMHW_LPC_SCT_EVT(7),
                   AMHW_LPC_SCT_MAT(6),
                   AMHW_LPC_SCT_STATE(1),
                   AMHW_LPC_SCT_EV_CTRL_STATELD_LOAD,
                   0);
    amhw_lpc_sct_out_clr_enable(p_hw_sct, __OUT_NUM, AMHW_LPC_SCT_EVT(7));

    /* ʹ���¼� 7 ���Ƽ�����ֵ */
    amhw_lpc_sct_event_limit_enable(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_UNIFY,
                                    AMHW_LPC_SCT_EVT(7));

    /* ���õ�ǰ״ֵ̬Ϊ 0 */
    amhw_lpc_sct_state_set(p_hw_sct,
                           AMHW_LPC_SCT_MODE_UNIFY,
                           AMHW_LPC_SCT_STATE(0));

    /* �� CLRCTR λ���������Ϊ 0 */
    amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_CLRCTR_L);

    /* Ԥ��ƵΪ 0��ʹ��ϵͳʱ�� */
    amhw_lpc_sct_prescale_set(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY, 0);
}

/**
 * \brief ʹ�� SCT ������Ӳ���
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_enable (amhw_lpc_sct_t *p_hw_sct)
{

    /* ����ֹλ��SCT ��ʼ���� */
    amhw_lpc_sct_ctrl_clr(p_hw_sct,
                          AMHW_LPC_SCT_CTRL_STOP_L | AMHW_LPC_SCT_CTRL_HALT_L);
}

/**
 * \brief ��ֹ SCT ������Ӳ���
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_disable (amhw_lpc_sct_t *p_hw_sct)
{

    /* ����ֹλ��SCT ��ֹ���� */
    amhw_lpc_sct_ctrl_set(p_hw_sct,
                          AMHW_LPC_SCT_CTRL_STOP_L | AMHW_LPC_SCT_CTRL_HALT_L);
} 


void demo_lpc_hw_sct_multi_states_entry(amhw_lpc_sct_t *p_hw_sct,
                                        uint32_t        frq)
{
    /* SCT ���� */
    __sct_disable(p_hw_sct);

    /* SCT ʵ�ֶ�ʱ������ */
    __sct_init(p_hw_sct, frq);

    /* SCT ʹ�� */
    __sct_enable(p_hw_sct);

    AM_FOREVER {
        ;
    }
}
/** [src_lpc_hw_sct_multi_states] */

/* end of file */
