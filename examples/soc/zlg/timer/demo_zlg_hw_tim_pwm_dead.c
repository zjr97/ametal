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
 * \brief ��ʱ��������ʱ��Ļ��� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��Ӧ����������� PWM��Ƶ��Ϊ 100KHz��ռ�ձ�Ϊ 40%������ʱ��Ϊ 100ns��
 *
 * \par Դ����
 * \snippet demo_zlg_hw_tim_pwm_dead.c src_zlg_hw_tim_pwm_dead
 *
 * \internal
 * \par Modification history
 * - 1.00 18-06-06  pea, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zlg_hw_tim_pwm_dead
 * \copydoc demo_zlg_hw_tim_pwm_dead.c
 */

/** [src_zlg_hw_tim_pwm_dead] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_bitops.h"
//#include "am_zlg116.h"
#include "hw/amhw_zlg_tim.h"

/**
 * \brief PWM ���Ƶ�ʶ��壬��λΪ Hz
 *        �����Ƶ�ʲ����ɶ�ʱ��ʱ��������Ƶ�õ���ʵ��Ƶ�ʻ������
 */
#define  __PWM_FREQ  100000

/**
 * \brief PWM ռ�ձȶ��壬��λΪ %
 *        100% / (arr �Ĵ���ֵ + 1)Ϊռ�ձȵ����ľ��ȣ�
 */
#define  __PWM_DUTY  40

/**
 * \brief PWM ռ�ձȳ������壬__PWM_DUTY / __PWM_UNIT �ĵ�λΪ %
 *        ������Ҫ����ֵ�ľ���Ϊ 1%���� __PWM_UNIT ����Ϊ 100��
 *        �����Ҫ����ֵ�ľ���Ϊ 0.1%���� __PWM_UNIT ����Ϊ 1000���Դ�����
 */
#define  __PWM_UNIT  100

/**
 * \brief ����ʱ�䶨�壬��λΪƤ�룬������ TIMx_CR1 �е� CKD �йأ�
 *        ���綨ʱ��ʱ��Ϊ 48MHz��CKD ����Ϊ 0��������ʱ�侫��Ϊ 1 / 48MHz = 20.83ns
 *        �������ʱ����󣬻ᵼ�� PWM �������
 *        ͬʱ����������ʱ��Ĳ��룬�ᵼ��ռ�ձ���
 *        ռ�ձ���� = (����ʱ�� / PWM ����) * 100%
 *        ���磬PWM Ƶ��Ϊ 100KHz������Ϊ 10us������ʱ������Ϊ 100ns ʱ��ռ�ձ����Ϊ 1%
 *        �����ʱռ�ձ�����Ϊ 40%���� TIM_CHx �������ռ�ձ�Ϊ 40% - 1% = 39%
 *        TIM_CHxN �������ռ�ձ�Ϊ 40% + 1% = 41%
 */
#define  __DEAD_TIME  100000

/**
 * \brief ���ö�ʱ�� TIM Ϊ PWM ���(PWM ģʽ 2)
 *
 * \param[in] p_hw_tim ָ��ʱ���Ĵ������ָ��
 * \param[in] chan     PWM �����ͨ����TIM1��TIM2��TIM3 �� 4 ��ͨ����
 *                     �� TIM14��TIM16��TIM17 ֻ��һ��
 * \param[in] freq     PWM Ƶ�ʣ���λΪ Hz��ʵ�ʿ��ܻ������
 * \param[in] duty     ռ�ձȣ���λΪ %��ʵ�ʿ��ܻ������
 * \param[in] clk_rate ��ʱ��ʱ��Ƶ��
 *
 * \return ��
 *
 * \note �� ARR �Ĵ����������� PWM ͨ��ʹ����ͬ�����ڲ���
 */
am_local void __tim_pwm_chan_config (amhw_zlg_tim_t *p_hw_tim,
                                     uint32_t        chan,
                                     uint32_t        freq,
                                     uint32_t        duty,
                                     uint32_t        clk_rate)
{
    uint16_t pre_real = 1;
    uint16_t pre_reg  = 0;
    uint32_t period_c;
    uint32_t duty_c;
    uint32_t temp;

    /* ��������õ����Ǽ���ֵ CNT */
    period_c = clk_rate / freq;
    duty_c   = period_c * (__PWM_UNIT - duty) / __PWM_UNIT;

    /* ������С�� 65536 ʱ������Ƶ(ֵΪ 1, 1 ����Ϊ 1 ��Ƶ) */
    temp = period_c / 65536 + 1;

    /* 16 λ��ʱ����Ҫ����ȡ�ú��ʵķ�Ƶֵ */
    for (pre_real = 1; pre_real < temp; ) {
        pre_reg++;           /* ����д��Ĵ����ķ�Ƶֵ 0, 1, 2, ... */
        pre_real++;          /* ��Ƶ�� */
    }

    /* ���÷�Ƶֵ */
    amhw_zlg_tim_prescale_set(p_hw_tim, pre_reg);

    /* ���¼��� PWM �����ڼ�����Ƶ�� */
    period_c = period_c / pre_real;
    duty_c = duty_c / pre_real;

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zlg_tim_arr_set(p_hw_tim, period_c - 1);

    /* ���ñȽ����ͨ����ƥ��ֵ */
    amhw_zlg_tim_ccr_ouput_reload_val_set(p_hw_tim,  duty_c, chan);

    /* �������� 0 */
    amhw_zlg_tim_count_set(p_hw_tim, 0);

    /* ʹ�ܶ� ARR Ԥװ�� */
    amhw_zlg_tim_arpe_enable(p_hw_tim);

    /* ѡ���ͨ��Ϊ��� */
    amhw_zlg_tim_ccs_set(p_hw_tim, 0, chan);

    /* ѡ���ͨ����ģʽΪ PWM ģʽ 2 */
    amhw_zlg_tim_ocm_set(p_hw_tim, AMHW_ZLG_TIM_PWM_MODE2, chan);

    /* PWM ���ͨ��Ԥװ��ʹ�� */
    amhw_zlg_tim_ccs_ocpe_enable(p_hw_tim, chan);

    /* ���ñȽ����ͨ�� CCP �ߵ�ƽ������Ч */
    amhw_zlg_tim_ccp_output_set(p_hw_tim, 0, chan);
}

/**
 * \brief ʹ�� PWM ���
 *
 * \param[in] p_hw_tim ָ��ʱ���Ĵ������ָ��
 * \param[in] chan     PWM �����ͨ����TIM1��TIM2��TIM3 �� 4 ��ͨ����
 *                     �� TIM14��TIM16��TIM17 ֻ��һ��
 *
 * \return ��
 */
am_local void __tim_pwm_enable (amhw_zlg_tim_t *p_hw_tim, uint32_t chan)
{

    /* ʹ��ͨ�� PWM ��� */
    amhw_zlg_tim_cce_output_enable(p_hw_tim, chan);

    /* �߼���ʱ��ʹ������� MOE */
    amhw_zlg_tim_bdtr_enable(p_hw_tim, AMHW_ZLG_TIM_MOE);

    /* ���������¼������³�ʼ�� Prescaler �������� Repetition ������ */
    amhw_zlg_tim_egr_set(p_hw_tim, AMHW_ZLG_TIM_UG);

    if (amhw_zlg_tim_status_flg_get(p_hw_tim, AMHW_ZLG_TIM_UG) != 0) {

        /* ���¶�ʱ��ʱ����������¼��������־λ */
        amhw_zlg_tim_status_flg_clr(p_hw_tim, AMHW_ZLG_TIM_UG);
    }

    /* ʹ�ܶ�ʱ�� TIM ������� */
    amhw_zlg_tim_enable(p_hw_tim);
}

/**
 * \brief ��ʱ�� TIM PWM �����ʼ������
 *
 * \param[in] p_hw_tim ָ��ʱ���Ĵ������ָ��
 * \param[in] clk_id   ʱ�� ID (��ƽ̨����), �μ� \ref grp_clk_id
 *
 * \return ��
 */
am_local void __tim_pwm_init (amhw_zlg_tim_t *p_hw_tim)
{
    /* ���ض���ģʽ */
    amhw_zlg_tim_cms_set(p_hw_tim, 0);

    /* ���ϼ��� */
    amhw_zlg_tim_dir_set(p_hw_tim, 0);

    /* ����ʱ�ӷָ�:TDTS = Tck_tin */
    amhw_zlg_tim_ckd_set(p_hw_tim, 0);

    /* ��������¼� */
    amhw_zlg_tim_udis_enable(p_hw_tim);
}

/**
 * \brief ���� DTG ���ü�������ʱ��
 *
 * \param[in] p_hw_tim ָ��ʱ���Ĵ������ָ��
 * \param[in] dtg      �������������ã�TIMx_BDTR �� DTG �ֶ�
 *
 * \return ����ʱ�䣬��λΪƤ��
 */
am_local int32_t __dead_time_get (amhw_zlg_tim_t *p_hw_tim,
                                  uint8_t         dtg,
                                  uint32_t        clk_rate)
{
    int32_t  dt;
    uint32_t tck_int = 1000000000000 / clk_rate;
    uint8_t  ckd     = AM_BITS_GET(p_hw_tim->cr[0], 8, 2);
    uint32_t tdts    = tck_int * (ckd ? ckd * 2 : 1);
    uint32_t tdtg;

    if (7 == AM_BITS_GET(dtg, 5, 3)) {
        tdtg = 16 * tdts;
        dt = (32 + AM_BITS_GET(dtg, 0, 5)) * tdtg;
    } else if (6 == AM_BITS_GET(dtg, 5, 3)) {
        tdtg = 8 * tdts;
        dt = (32 + AM_BITS_GET(dtg, 0, 5)) * tdtg;
    } else if (2 == AM_BITS_GET(dtg, 6, 2)) {
        tdtg = 2 * tdts;
        dt = (64 + AM_BITS_GET(dtg, 0, 6)) * tdtg;
    } else if (0 == AM_BITS_GET(dtg, 7, 1)) {
        tdtg = tdts;
        dt = AM_BITS_GET(dtg, 0, 7) * tdtg;
    } else {
        dt = AM_ERROR;
    }

    /* �������һ�� tck_int ����Ϊʵ�� dtg ����Ϊ 0 ��ʱ��Ҳ��һ�� tck_int ������ʱ�� */
    return dt + tck_int;
}

/**
 * \brief ������Ҫ������ʱ�������ӽ��� DTG ����
 *
 * \param[in] p_hw_tim  ָ��ʱ���Ĵ������ָ��
 * \param[in] dead_time ��Ҫ���õ�����ʱ�䣬��λΪƤ��
 *
 * \return DTG ����ֵ
 */
am_local int32_t __dtg_calculate (amhw_zlg_tim_t *p_hw_tim,
                                  uint32_t        dead_time,
                                  uint32_t        clk_rate)
{
    int32_t i;
    uint32_t dt;

    for (i = 0; i <= 0xFF; i++) {
        dt = __dead_time_get(p_hw_tim, i, clk_rate);
        if (dt >= dead_time) {
            break;
        }
    }

    return (i > 0xFF) ? 0xFF : i;
}

/**
 * \brief �������
 */
void demo_zlg_hw_tim_pwm_dead_entry (amhw_zlg_tim_t     *p_hw_tim,
                                     amhw_zlg_tim_type_t type,
                                     uint32_t            chan,
                                     uint32_t            clk_rate)
{
    if ((AMHW_ZLG_TIM_TYPE0 != type) &&
        (AMHW_ZLG_TIM_TYPE2 != type) &&
        (AMHW_ZLG_TIM_TYPE3 != type)) {
        AM_DBG_INFO("this timer don't support pwm dead!\r\n");
    }

    /* ��ʼ����ʱ�� TIM Ϊ PWM ���� */
    __tim_pwm_init(p_hw_tim);

    /* ���ö�ʱ�� TIM PWM ���ͨ�� */
    __tim_pwm_chan_config(p_hw_tim, 0, __PWM_FREQ, __PWM_DUTY, clk_rate);

    /* ʹ�ܻ������ */
    amhw_zlg_tim_ccne_enable(p_hw_tim, AMHW_ZLG_TIM_CC1S);

    /* ʹ�ܻ�������ߵ�ƽ��Ч */
    amhw_zlg_tim_ccne_set(p_hw_tim, 0, AMHW_ZLG_TIM_CC1S);

    /* ��������ʱ�� */
    amhw_zlg_tim_utg_set(p_hw_tim, __dtg_calculate(p_hw_tim, __DEAD_TIME, clk_rate));

    /* ������ʱ�� */
    __tim_pwm_enable(p_hw_tim, 0);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg_hw_tim_pwm_dead] */

/* end of file */
