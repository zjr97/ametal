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
 * \brief ��ʱ�� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ��������� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \par Դ����
 * \snippet demo_zlg116_hw_tim_pwm.c src_zlg116_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zlg116_hw_tim_pwm
 * \copydoc demo_zlg116_hw_tim_pwm.c
 */

/** [src_zlg116_hw_tim_pwm] */
#include "ametal.h"
#include "am_clk.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"
//#include "am_zlg116.h"
#include "hw/amhw_zlg_tim.h"
#include "am_led.h"

#define LED0          0
/**
  * \brief PWM �жϷ�����
  */
static void __zlg_tim_hw_pwm_irq_handler (void *p_arg)
{
    amhw_zlg_tim_t *p_hw_tim = (amhw_zlg_tim_t *)p_arg;
    uint8_t         i        = 1;

    for (i = 1; i <= 4 ; i++) {
        if ((amhw_zlg_tim_status_flg_get(p_hw_tim, 1UL << i)) != 0) {

					  am_led_toggle(LED0);

            /* ���ͨ�� i ��־ */
            amhw_zlg_tim_status_flg_clr(p_hw_tim, (1UL << i));
        }
    }
}

/**
 * \brief ���ö�ʱ��Ϊ PWM ���(PWM ģʽ 2)
 */
void tim_pwm_chan_config (amhw_zlg_tim_t *p_hw_tim,
                          uint32_t        chan,
                          uint32_t        duty_ns,
                          uint32_t        period_ns,
                          uint32_t        clk_rate)
{
    uint32_t period_c, duty_c, temp;
    uint16_t pre_real = 1, pre_reg = 0;

    /* �������Ϸ� */
    if ((period_ns == 0) || (duty_ns > 4294967295UL) ||
        (period_ns > 4294967295UL) || (duty_ns > period_ns)) {
        return ;
    }

    /* ��������õ����Ǽ���ֵCNT, ��ʽns * 10e-9= cnt * (1/clkfrq) */
    period_c = (uint64_t)(period_ns) * (clk_rate) / (uint64_t)1000000000;
    duty_c   = (uint64_t)(duty_ns)   * (clk_rate) / (uint64_t)1000000000;

    {
         /* ������С��65536ʱ������Ƶ(ֵΪ1,1����Ϊ1��Ƶ) */
         temp = period_c / 65536 + 1;

         /* 16λ��ʱ����Ҫ����ȡ�ú��ʵķ�Ƶֵ */
         for (pre_real = 1; pre_real < temp; ) {
              pre_reg++;           /* ����д��Ĵ����ķ�Ƶֵ0,1,2,... */
              pre_real++;          /* ��Ƶ�� */
         }
     }

    /* ���÷�Ƶֵ */
    amhw_zlg_tim_prescale_set(p_hw_tim, pre_reg);

    /* ���¼���PWM�����ڼ�����Ƶ�� */
    period_c = period_c / pre_real;
    duty_c = duty_c / pre_real;

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zlg_tim_arr_set(p_hw_tim, period_c - 1);

    /* ���ñȽ����ͨ����ƥ��ֵ */
    amhw_zlg_tim_ccr_ouput_reload_val_set(p_hw_tim,  duty_c - 1, chan);

    /* ��������0 */
    amhw_zlg_tim_count_set(p_hw_tim, 0);

    /*��ʹ�ܶ�ARRԤװ�� */
    amhw_zlg_tim_arpe_enable(p_hw_tim);

    /* ѡ���ͨ��Ϊ��� */
    amhw_zlg_tim_ccs_set(p_hw_tim, 0, chan);

    /* ѡ���ͨ����ģʽΪPWMģʽ2 */
    amhw_zlg_tim_ocm_set(p_hw_tim, AMHW_ZLG_TIM_PWM_MODE2, chan);

    /* PWM���ͨ��Ԥװ��ʹ�� */
    amhw_zlg_tim_ccs_ocpe_enable(p_hw_tim, chan);

    /* ���ñȽ����ͨ��ccp�ߵ�ƽ������Ч */
    amhw_zlg_tim_ccp_output_set(p_hw_tim, 0, chan);
}

void tim_pwm_enable (amhw_zlg_tim_t      *p_hw_tim,
                     amhw_zlg_tim_type_t  type,
                     uint32_t             chan,
                     int32_t              int_num)
{

    /* ʹ��ͨ��PWM��� */
    amhw_zlg_tim_cce_output_enable(p_hw_tim, chan);

    /* �߼���ʱ��ʹ�������MOE */
    if ((AMHW_ZLG_TIM_TYPE0 == type) ||
        (AMHW_ZLG_TIM_TYPE2 == type) ||
        (AMHW_ZLG_TIM_TYPE3 == type)) {

        amhw_zlg_tim_bdtr_enable(p_hw_tim, AMHW_ZLG_TIM_MOE);
    }

    /* ���������¼������³�ʼ��Prescaler������ ��Repetition������ */
    amhw_zlg_tim_egr_set(p_hw_tim, AMHW_ZLG_TIM_UG);

    if (amhw_zlg_tim_status_flg_get(p_hw_tim, AMHW_ZLG_TIM_UG) != 0) {
        /* ���¶�ʱ��ʱ����������¼�,�����־λ */
        amhw_zlg_tim_status_flg_clr(p_hw_tim, AMHW_ZLG_TIM_UG);
    }

    /* �����жϻص����� */
    am_int_connect(int_num, __zlg_tim_hw_pwm_irq_handler, (void *)p_hw_tim);

    /* ʹ���ж� */
    amhw_zlg_tim_int_enable(p_hw_tim, (1ul << (chan + 1)));

    am_int_enable(int_num);

    /*��ʹ�ܶ�ʱ��TIM������� */
    amhw_zlg_tim_enable(p_hw_tim);
}

/**
 * \brief ��ʱ��TIM PWM�����ʼ������
 *
 * \param[in] p_hw_tim : ָ��ʱ���Ĵ������ָ��
 * \param[in] clk_id   : ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \return ��
 */
void tim_pwm_init (amhw_zlg_tim_t     *p_hw_tim, amhw_zlg_tim_type_t type)
{
    if ((AMHW_ZLG_TIM_TYPE0 == type) || (AMHW_ZLG_TIM_TYPE1 == type)) {

        /* ���ض���ģʽ */
        amhw_zlg_tim_cms_set(p_hw_tim, 0);

        /* ���ϼ��� */
        amhw_zlg_tim_dir_set(p_hw_tim, 0);
    }

    /* ����ʱ�ӷָ�:TDTS = Tck_tin */
    amhw_zlg_tim_ckd_set(p_hw_tim, 0);

    /* ��������¼� */
    amhw_zlg_tim_udis_enable(p_hw_tim);
}

/**
 * \brief �������
 */
void demo_zlg_hw_tim_pwm_entry (amhw_zlg_tim_t     *p_hw_tim,
                                amhw_zlg_tim_type_t type,
                                uint32_t            chan,
                                uint32_t            clk_rate,
                                int32_t             inum)
{

    /* ��ʼ����ʱ��TIMΪPWM���� */
    tim_pwm_init(p_hw_tim, type);

    /* ���ö�ʱ��TIM PWM���ͨ�� */
    tim_pwm_chan_config(p_hw_tim,
                        chan,
                        250000 / 2,
                        250000,
                        clk_rate);

    tim_pwm_enable(p_hw_tim, type, chan, inum);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg116_hw_tim_pwm] */

/* end of file */
