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
 * \brief SCT ��Ϊ 2 �� 16 λ��ʱ����ʱ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ����˸;
 *   2. ����������(PIO0_24)״̬�� 8KHz ��Ƶ�ʷ�ת���������Ϊ 4KHz��
 *      ÿ������ 50 ���룬����Ƶ��Ϊ 10Hz��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ��������Ҫ�̽� J7 ����ñ�����ܱ� PIO0_24 ���ƣ�
 *    3. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����Ĭ�ϳ�ʼ����������
 *
 * \par Դ����
 * \snippet demo_lpc_hw_sct_2_16bit_timing.c src_lpc_hw_sct_2_16bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.02 15-12-14  hgo, change PIO0_15 to PIO0_24 .
 * - 1.01 15-11-19  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_sct_2_16bit_timing
 * \copydoc demo_lpc_hw_sct_2_16bit_timing.c
 */

/** [src_lpc_hw_sct_2_16bit_timing] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_gpio.h"
#include "hw/amhw_lpc_sct.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define   __SCT_HANDLE_H        1            /**< \brief ���ڲ������鶨ʱ�� */
#define   __SCT_HANDLE_L        0            /**< \brief ���ڲ������鶨ʱ�� */

volatile am_bool_t  __g_beep_on =  AM_FALSE; /**< \brief ������������־λ */

static int __buzzer_pin = 24;
/**
 * \brief ������ʹ���� 2 �� SCT �¼�
 *
 * 1. �¼� 0�������������жϣ�ʹ��ƥ��ͨ�� 0 �ĵ� 16 λ���¼������������������㣻
 * 2. �¼� 1�������������жϣ�ʹ��ƥ��ͨ�� 0 �ĸ� 16 λ���¼������������������㣻
 *
 * �����¼��� SCT ״̬ 0 ����Ч���¼������� SCT ״̬�������ı䣻
 */

/**
 * \brief ���� 16 λ��ʱ��ָ������ֵ��ʱ�� ����ѵ�Ԥ��Ƶֵ��ƥ��Ĵ���ֵ
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
   *p_match       = 65536;

    /**
     * ����ֵ��СΪ 65536��
     * Ԥ��ƵΪ 1��ƥ��ֵ���ڼ���ֵ
     */
    if (count <= 65536) {
        prescale = 1;
       *p_match = count;

        return prescale;
    }

    /* ���ƥ��ֵ��ֱ���ҵ���õ� */
    for (match = 65536; match > 0; match--) {

        result_quot = count / match;
        result_rem  = count % match;

        /*
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

                /* ���ָ����ʵ�Ԥ��Ƶ��ƥ��ֵ */
                min_remainder = result_rem;
                prescale      = result_quot;
               *p_match      = match;
            }
        }
    }

    return prescale;
}

/**
 * \brief SCT0 �жϷ�����
 *
 * \param[in] p_arg �û��Զ���������� am_int_connect() ��������
 *
 * \return ��
 */
am_local void __sct0_irq_handler (void *p_arg)
{

    amhw_lpc_sct_t *p_hw_sct = (amhw_lpc_sct_t *)p_arg;
    /* �¼� 0 �ж� */
    if (amhw_lpc_sct_event_flag_chk(p_hw_sct,
                                    AMHW_LPC_SCT_EVT(0)) == AM_TRUE) {

        am_led_toggle(LED0);

        /* ���־ */
        amhw_lpc_sct_event_flag_clr(p_hw_sct, AMHW_LPC_SCT_EVT(0));

        /* �������������� */
        __g_beep_on = AM_TRUE;
    }

    /* �¼� 1 �ж� */
    if (amhw_lpc_sct_event_flag_chk(p_hw_sct,
                                    AMHW_LPC_SCT_EVT(1)) == AM_TRUE) {

        /* ���������� */
        am_gpio_toggle(__buzzer_pin);

        amhw_lpc_sct_event_flag_clr(p_hw_sct,
                                    AMHW_LPC_SCT_EVT(1));
    }
}

/**
 * \brief ʹ�ܶ�ʱ��
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] handle   ���鶨ʱ����#__SCT_HANDLE_H�����鶨ʱ����#__SCT_HANDLE_L
 *
 * \return ��
 */
am_local void __sct_2_16bit_timer_enable (amhw_lpc_sct_t *p_hw_sct,
                                          uint8_t         handle)
{
    if (handle == __SCT_HANDLE_H) {

        /* ����ֹλ��SCT �����������ʼ���� */
        amhw_lpc_sct_ctrl_clr(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_H |
                                        AMHW_LPC_SCT_CTRL_HALT_H);

    } else {

        /* ����ֹλ��SCT �����������ʼ���� */
        amhw_lpc_sct_ctrl_clr(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_L |
                                        AMHW_LPC_SCT_CTRL_HALT_L);
    }
}

/**
 * \brief ���ܶ�ʱ��
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] handle   ���鶨ʱ����#__SCT_HANDLE_H�����鶨ʱ����#__SCT_HANDLE_L
 *
 * \return ��
 */
am_local void __sct_2_16bit_timer_disable (amhw_lpc_sct_t *p_hw_sct,
                                           uint8_t         handle)
{
    if (handle == __SCT_HANDLE_H) {

        /* ����ֹλ��SCT �����������ֹ���� */
        amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_H |
                                        AMHW_LPC_SCT_CTRL_HALT_H);

    } else {

        /* ����ֹλ��SCT �����������ֹ���� */
        amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_STOP_L |
                                        AMHW_LPC_SCT_CTRL_HALT_L);
    }
}

/**
 * \brief ��ʼ����ʱ��
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 * \param[in] handle   ���鶨ʱ����#__SCT_HANDLE_H�����鶨ʱ����#__SCT_HANDLE_L
 * \param[in] freq     ��ʱ���ж�Ƶ��
 *
 * \return ��
 *
 * \note ���鶨ʱ��ʹ���¼� 0�����鶨ʱ��ʹ���¼� 1
 */
am_local void __sct_2_16bit_timer_init (amhw_lpc_sct_t *p_hw_sct,
                                        uint8_t         handle,
                                        uint32_t        freq,
                                        uint32_t        frq)
{
    uint32_t counters;
    uint32_t prescale, match;

    amhw_lpc_sct_mode_t  sct_mode;
    uint32_t             event_num;
    uint32_t             event_ctl;


    if (handle == __SCT_HANDLE_H) {

        sct_mode  = AMHW_LPC_SCT_MODE_SEPARATE_H;
        event_num = AMHW_LPC_SCT_EVT(1);           /* ���鶨ʱ��ʹ���¼� 1 */

        /* �¼�������ƥ���16bits */
        event_ctl = AMHW_LPC_SCT_EV_CTRL_HEVENT_H;

    } else {
        sct_mode  = AMHW_LPC_SCT_MODE_SEPARATE_L;
        event_num = AMHW_LPC_SCT_EVT(0);           /* ���鶨ʱ��ʹ���¼� 0 */

        /* �¼�������ƥ��� 16bits */
        event_ctl = AMHW_LPC_SCT_EV_CTRL_HEVENT_L;
    }

    /* ����ƥ��/����Ĵ��� 0 Ϊ 16bits ƥ��Ĵ��� */
    amhw_lpc_sct_regmode_config(p_hw_sct,
                                sct_mode,
                                AMHW_LPC_SCT_MAT(0),
                                AMHW_LPC_SCT_MATCAP_MATCH);

    /**
     * ���� 16 λ��ʱ��Ԥ��Ƶ��ƥ��ֵ�����磬Ҫ���� 10Hz ���жϣ�ϵͳʱ��Ƶ��Ϊ
     * 100MHz����ʱ������ֵΪ��100 000 000 / 10 = 10 000 000��
     * ������Ϊ 16bits�����ֵΪ 65536����ʹ��Ԥ��Ƶ��10 000 000 = 200 * 50000��
     * ƥ��ֵΪ��50000��
     * Ԥ��ƵֵΪ��200
     */
    counters = frq / freq;

    prescale = __prescale_and_match_calculate(counters, &match);

    prescale -= 1;
    match    -= 1;

    /* ��Ҫ�ı�Ԥ��Ƶ��Ӧ����ֹ SCT */
    if (prescale != amhw_lpc_sct_prescale_get(p_hw_sct, sct_mode)) {

        if (amhw_lpc_sct_halt_check(p_hw_sct, sct_mode) == AM_TRUE ) {
            amhw_lpc_sct_prescale_set(p_hw_sct, sct_mode, prescale);
        } else {
            __sct_2_16bit_timer_disable(p_hw_sct, handle);
            amhw_lpc_sct_prescale_set(p_hw_sct, sct_mode, prescale);
            __sct_2_16bit_timer_enable(p_hw_sct, handle);
        }
    }

    /* ֻ�д��� HALT ״̬��ʱ����������ƥ��Ĵ���ʱ */
    if (amhw_lpc_sct_halt_check(p_hw_sct, sct_mode) == AM_TRUE ) {
        amhw_lpc_sct_mat_val_set(p_hw_sct,
                                 sct_mode,
                                 AMHW_LPC_SCT_MAT(0),
                                 match);
    }

    /* ��������ƥ��ֵ */
    amhw_lpc_sct_mat_reload_val_set(p_hw_sct,
                                    sct_mode,
                                    AMHW_LPC_SCT_MAT(0),
                                    match);

    /* ���鶨ʱ��ʹ���¼� 1�������¼� 1 */
    amhw_lpc_sct_event_ctrl(p_hw_sct,
                            event_num,
                            event_ctl                           |

                            /* �¼�������ƥ�� 0 */
                            AMHW_LPC_SCT_EV_CTRL_MATCHSEL(0)    |

                            /* ֻ��ʹ��ָ��ƥ�� */
                            AMHW_LPC_SCT_EV_CTRL_COMBMODE_MATCH |

                            /* STATEV ֵ���� STATE */
                            AMHW_LPC_SCT_EV_CTRL_STATELD_ADD    |

                            /* �� 0��STATE û�иı� */
                            AMHW_LPC_SCT_EV_CTRL_STATEV(0));

    /* ���õ�ǰ״ֵ̬Ϊ 0 */
    amhw_lpc_sct_state_set(p_hw_sct, sct_mode, AMHW_LPC_SCT_STATE(0));

    /* ʹ��״̬ 0 �в����¼� */
    amhw_lpc_sct_event_state_enable(p_hw_sct,
                                    event_num,
                                    AMHW_LPC_SCT_STATE(0));

    /* ʹ���¼����������޶� */
    amhw_lpc_sct_event_limit_enable(p_hw_sct, sct_mode, event_num);

    /* ʹ���¼������ж� */
    amhw_lpc_sct_event_int_enable(p_hw_sct, event_num);

    if (handle == __SCT_HANDLE_H) {

        /* ���� CLRCTR λ������������Ϊ 0 */
        amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_CLRCTR_H);
    } else {
        amhw_lpc_sct_ctrl_set(p_hw_sct, AMHW_LPC_SCT_CTRL_CLRCTR_L);
    }
}

/**
 * \brief SCT ʵ�ֶ�ʱ����
 *
 * \param[in] p_hw_sct ָ�� SCT �Ĵ������ָ��
 *
 * \return ��
 */
am_local void __sct_2_16bit_init (amhw_lpc_sct_t *p_hw_sct, 
                                  uint32_t        frq)
{
    amhw_lpc_sct_config(p_hw_sct,

                        /* ��ʱ��ʵ�� 2 �� 16bits ��ʱ�� */
                        AMHW_LPC_SCT_CONFIG_16BIT_COUNTER  |

                        /* SCT ʱ��ʹ��ϵͳʱ�� */
                        AMHW_LPC_SCT_CONFIG_CLKMODE_SYSCLK);

    /* ʹ�ܵ��鶨ʱ���жϣ��ж�Ƶ��Ϊ 10Hz */
    __sct_2_16bit_timer_init(p_hw_sct, __SCT_HANDLE_L, 10, frq);

    /* ʹ�ܸ��鶨ʱ���жϣ��ж�Ƶ��Ϊ 8KHz */
    __sct_2_16bit_timer_init(p_hw_sct, __SCT_HANDLE_H, 8000, frq);
}

void demo_lpc_hw_sct_2_16bit_timing_entry (amhw_lpc_sct_t *p_hw_sct, 
                                           int             inum, 
                                           uint32_t        frq,
                                           int             buzzer_pin)
{
   /* ���������� */
    __buzzer_pin = buzzer_pin;
  
    /* ʹ�� SCT ʵ�ֶ�ʱ���� */
    __sct_2_16bit_init(p_hw_sct, frq);

    am_int_connect(inum, __sct0_irq_handler, (void *)p_hw_sct);

    /* ʹ�� SCT0 �ж� */
    am_int_enable(inum);

    /* ʹ�ܵ��鶨ʱ�� */
    __sct_2_16bit_timer_enable(p_hw_sct, __SCT_HANDLE_L);

    AM_FOREVER {

        if (__g_beep_on == AM_TRUE) {

            /* ʹ�ܸ��鶨ʱ�������з�������� */
            __sct_2_16bit_timer_enable(p_hw_sct, __SCT_HANDLE_H);

            am_mdelay(50);

            /* ���ܸ��鶨ʱ����ֹͣ��������� */
            __sct_2_16bit_timer_disable(p_hw_sct, __SCT_HANDLE_H);

            __g_beep_on =  AM_FALSE;
        }
    }
}
/** [src_lpc_hw_sct_2_16bit_timing] */

/* end of file */
