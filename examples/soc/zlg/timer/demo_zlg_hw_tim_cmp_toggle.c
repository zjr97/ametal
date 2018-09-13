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
 * \brief ��ʱ��ͨ���Ƚ�ƥ�����ŷ�ת���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ�������� 10Hz ��Ƶ�ʽ��з�ת��
 *   2. LED0 ��ת��
 *
 * \par Դ����
 * \snippet demo_zlg_hw_tim_cmp_toggle.c src_zlg_hw_tim_cmp_toggle
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zlg_hw_tim_cmp_toggle
 * \copydoc demo_zlg_hw_tim_cmp_toggle.c
 */

/** [src_zlg_hw_tim_cmp_toggle] */
#include "ametal.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg_tim.h"
#include "am_led.h"

#define LED0          0

/**
 * \brief CMP �жϷ�����
 */
static void __zlg_tim_cmp_irq_handler (void *p_arg)
{
    uint8_t         i        = 1;
    amhw_zlg_tim_t *p_hw_tim = (amhw_zlg_tim_t *)p_arg;

    for (i = 1; i <= 4 ; i++) {
        if ((amhw_zlg_tim_status_flg_get(p_hw_tim, 1UL << i) & AMHW_ZLG_TIM_CC1IF) != 0) {

            am_led_toggle(LED0);

            /* ���ͨ��i��־ */
            amhw_zlg_tim_status_flg_clr(p_hw_tim, (1UL << i));
        }
    }
}

/**
 * \brief ���ö�ʱ������Ƚ�ģʽ��ƥ����ƽ������ת
 */
static void tim_cmp_toggle_chan_config (amhw_zlg_tim_t *p_hw_tim,
                                        uint32_t        chan,
                                        uint32_t        cnt)
{
    uint32_t match, temp;
    uint16_t pre_real = 1, pre_reg = 0;


    {
        temp = cnt;

        /* 16λ���������ֵ65536, ��Ƶ�����ֵ65536 */
        if (temp  > 4294967295UL) {
            return ;
        }

        /* ������С��65536ʱ������Ƶ(ֵΪ1,1����Ϊ1��Ƶ) */
        temp = cnt  / 65536 + 1;

        /* 16λ��ʱ����Ҫ����ȡ�ú��ʵķ�Ƶֵ */
        for (pre_real = 1; pre_real < temp; ) {
            pre_reg++;           /* ����д��Ĵ����ķ�Ƶֵ0,1,2,... */
            pre_real++;          /* ��Ƶ�� */
        }
    }

    /* �����Զ�����ֵ */
    match = cnt / pre_real ;

    /* ���÷�Ƶֵ */
    amhw_zlg_tim_prescale_set(p_hw_tim, pre_reg);

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zlg_tim_arr_set(p_hw_tim, match - 1);

    /* ���ñȽ����ͨ����ƥ��ֵ */
    amhw_zlg_tim_ccr_ouput_reload_val_set(p_hw_tim,  match / 2 - 1, chan);

    /* ��������0 */
    amhw_zlg_tim_count_set(p_hw_tim, 0);

    /* ѡ���ͨ��Ϊ��� */
    amhw_zlg_tim_ccs_set(p_hw_tim, 0, chan);

    /* ѡ���ͨ����ģʽΪCMP_TOGGLE */
    amhw_zlg_tim_ocm_set(p_hw_tim, AMHW_ZLG_TIM_TOGGLE, chan);

    /* ��ֹԤװ�� */
    amhw_zlg_tim_ccs_ocpe_disable(p_hw_tim, chan);

    /* ���ñȽ����ͨ��ccp�ߵ�ƽ������Ч */
    amhw_zlg_tim_ccp_output_set(p_hw_tim, 0, chan);
}

void tim_cmp_toggle_enable (amhw_zlg_tim_t      *p_hw_tim,
                            amhw_zlg_tim_type_t  type,
                            uint32_t             chan,
                            uint8_t              int_num)
{

    /* ʹ��ͨ���Ƚ���� */
    amhw_zlg_tim_cce_output_enable(p_hw_tim, chan);

    /* �߼���ʱ��ʹ������� MOE */
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
    am_int_connect(int_num, __zlg_tim_cmp_irq_handler, (void *)p_hw_tim);

    /* ʹ���ж� */
    amhw_zlg_tim_int_enable(p_hw_tim, (1ul << (chan + 1)));

    am_int_enable(int_num);

    /*��ʹ�ܶ�ʱ��TIM������� */
    amhw_zlg_tim_enable(p_hw_tim);
}

/**
 * \brief ��ʱ�� TIM ����Ƚ�ͨ����ת��ʼ������
 */
void tim_cmp_toggle_init (amhw_zlg_tim_t *p_hw_tim, amhw_zlg_tim_type_t type)
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
void demo_zlg_hw_tim_cmp_toggle_entry (amhw_zlg_tim_t      *p_hw_tim,
                                       amhw_zlg_tim_type_t  type,
                                       uint32_t             chan,
                                       uint32_t             clk_rate,
                                       uint8_t              inum)
{

    /* ��ʼ����ʱ��Ϊ����Ƚ�ͨ����ת���� */
    tim_cmp_toggle_init(p_hw_tim, type);
    tim_cmp_toggle_chan_config(p_hw_tim, chan, clk_rate / 10);
    tim_cmp_toggle_enable(p_hw_tim, type, chan, inum);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg_hw_tim_cmp_toggle] */

/* end of file */
