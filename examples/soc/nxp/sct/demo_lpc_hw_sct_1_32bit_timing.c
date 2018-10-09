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
 * \brief SCT 32 λ��ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ����˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *    3. ������ʹ���� SCT �¼� 0�����ڲ����������жϣ�ʹ��ƥ��ͨ�� 0���¼�����������
 *       ���㡣
 *
 * \par Դ����
 * \snippet demo_lpc_hw_sct_1_32bit_timing.c src_lpc_hw_sct_1_32bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-08  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_sct_1_32bit_timing
 * \copydoc demo_lpc_hw_sct_1_32bit_timing.c
 */

/** [src_lpc_hw_sct_1_32bit_timing] */
#include "ametal.h"
#include "am_int.h"
#include "am_board.h"
#include "hw/amhw_lpc_sct.h"

/**
 * \brief SCT0 �жϷ�����
 *
 * \param[in] p_arg �û��Զ���������� am_int_connect() ��������
 *
 * \return  ��
 */
am_local void __sct0_irq_handler (void *p_arg)
{
    amhw_lpc_sct_t *p_hw_sct = (amhw_lpc_sct_t *)p_arg;
    /* �¼� 0 �����ж� */
    if (amhw_lpc_sct_event_flag_chk(p_hw_sct,
                                    AMHW_LPC_SCT_EVT(0)) == AM_TRUE ) {
        am_led_toggle(LED0);

        /* �����־ */
        amhw_lpc_sct_event_flag_clr(p_hw_sct, AMHW_LPC_SCT_EVT(0));
    }
}

/**
 * \brief ��ʼ�� SCT Ϊ��ʱ������
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] freq     �ж�Ƶ�ʡ�
 *
 * \return ��
 */
am_local void __sct_timer_init (amhw_lpc_sct_t *p_hw_sct, 
                                uint32_t        freq, 
                                int             inum,
                                uint32_t        frq)
{
    amhw_lpc_sct_config(p_hw_sct,
                        AMHW_LPC_SCT_CONFIG_32BIT_COUNTER  | /* ʹ�� 32 λ��ʱ�� */
                        AMHW_LPC_SCT_CONFIG_CLKMODE_SYSCLK); /* ʹ��ϵͳʱ�� */

    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_lpc_sct_regmode_config(p_hw_sct,

                                /* SCT ģʽΪ UNIFY(1 32-bit ������) */
                                AMHW_LPC_SCT_MODE_UNIFY,

                                /* ƥ��/���� 0 */
                                0,

                                /* ����ƥ��Ĵ��� */
                                AMHW_LPC_SCT_MATCAP_MATCH);

    /* ����ƥ�� 0 ������ƥ��ֵ */
    amhw_lpc_sct_mat_val_set(p_hw_sct,
                             AMHW_LPC_SCT_MODE_UNIFY,
                             AMHW_LPC_SCT_MAT(0),
                             frq / freq - 1);

    amhw_lpc_sct_mat_reload_val_set(
                               p_hw_sct,
                               AMHW_LPC_SCT_MODE_UNIFY,
                               AMHW_LPC_SCT_MAT(0),
                               frq / freq - 1);

    /* �����¼� 0 ���ƼĴ��� */
    amhw_lpc_sct_event_ctrl(p_hw_sct,

                            /* �¼� 0 */
                            AMHW_LPC_SCT_EVT(0),

                            /* �¼�������ƥ�� 0 */
                            AMHW_LPC_SCT_EV_CTRL_MATCHSEL(0)    |

                            /* ֻ��ʹ��ָ����ƥ��Ĵ��� */
                            AMHW_LPC_SCT_EV_CTRL_COMBMODE_MATCH |

                            /*  STATEV ֵ���� STATE */
                            AMHW_LPC_SCT_EV_CTRL_STATELD_ADD    |

                            /* �� 0��STATE û�иı� */
                            AMHW_LPC_SCT_EV_CTRL_STATEV(0));

    /* ���õ�ǰ״ֵ̬Ϊ 0 */
    amhw_lpc_sct_state_set(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY, 0);

    /* ʹ��״̬ 0 ���¼� 0 ���� */
    amhw_lpc_sct_event_state_enable(p_hw_sct,
                                    AMHW_LPC_SCT_EVT(0),
                                    AMHW_LPC_SCT_STATE(0));

    /* ʹ���¼� 0 ���޶������� */
    amhw_lpc_sct_event_limit_enable(p_hw_sct,
                                    AMHW_LPC_SCT_MODE_UNIFY,
                                    AMHW_LPC_SCT_EVT(0));

    /* ʹ���¼� 0 �����ж� */
    amhw_lpc_sct_event_int_enable(p_hw_sct, AMHW_LPC_SCT_EVT(0));

    /* ���� SCT0 ���жϷ����� */
    am_int_connect(inum, __sct0_irq_handler, (void *)p_hw_sct);

    /* ʹ�� SCT0 �ж� */
    am_int_enable(inum);

    /* �� CLRCTR λ���������Ϊ 0 */
    amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_CLRCTR_L);

    /* Ԥ��ƵΪ 0��ʹ��ϵͳʱ�� */
    amhw_lpc_sct_prescale_set(p_hw_sct, AMHW_LPC_SCT_MODE_UNIFY, 0);
}

/**
 * \brief ʹ�� SCT Ϊ��ʱ��(��ʼ����)
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_timer_enable (amhw_lpc_sct_t *p_hw_sct)
{

    /* ����ֹλ��SCT ��ʼ���� */
    amhw_lpc_sct_ctrl_clr(p_hw_sct,
                          AMHW_LPC_SCT_CTRL_STOP_L | AMHW_LPC_SCT_CTRL_HALT_L);
}

void demo_lpc_hw_sct_1_32bit_timing_entry (amhw_lpc_sct_t *p_hw_sct, 
                                              int            inum, 
                                              uint32_t       frq)
{
    /* ʹ�� SCT ʵ�ֶ�ʱ���ܣ��ж�Ƶ��Ϊ 10Hz */
    __sct_timer_init(p_hw_sct, 10, inum, frq);

    /* ʹ�� SCT Ϊ��ʱ�� */
    __sct_timer_enable(p_hw_sct);

    AM_FOREVER {
        ; /* VOID */
    }
}

/** [src_lpc_hw_sct_1_32bit_timing] */

/* end of file */
