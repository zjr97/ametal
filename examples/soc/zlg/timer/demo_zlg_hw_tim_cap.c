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
 * \brief ��ʱ���������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �ڶ�ʱ���������������� PWM��
 *
 * - ʵ������
 *   1. ���Դ��ڴ�ӡ���񵽵� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \par Դ����
 * \snippet demo_zlg_hw_tim_cap.c src_zlg_hw_tim_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-04-22  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_hw_tim_cap
 * \copydoc demo_zlg_hw_tim_cap.c
 */

/** [src_zlg_hw_tim_cap] */
#include "ametal.h"
#include "am_cap.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg_tim.h"

static volatile am_bool_t g_flag       = AM_FALSE; /**< \brief �����־ */
static volatile uint32_t  g_time_ns    = 0;        /**< \brief �������ֵ */
static uint32_t           __g_clk_rate = 0;        /**< \brief ʱ��Ƶ�� */

static void __zlg_tim_hw_cap_irq_handler (void *p_arg)
{
    amhw_zlg_tim_t   *p_hw_tim  = (amhw_zlg_tim_t *)p_arg;
    uint8_t           chans_num = 4;

    uint8_t           i         = 1;
    uint32_t          value     = 0;

    uint32_t          count_err = 0;
    uint64_t          time_ns   = 0;
    uint16_t          reg_pre   = 0,  pre = 1;

    static uint32_t   count16   = 0;

    static am_bool_t  first     = AM_TRUE;


    for (i = 1; i <= chans_num; i++) {
        if ((amhw_zlg_tim_status_flg_get(p_hw_tim, 1UL << i)) != 0) {

            /* �õ���Ӧͨ����ֵ */
            value = amhw_zlg_tim_ccr_cap_val_get(p_hw_tim, i - 1);
					  if(0 == i - 1) {
                if (g_flag == AM_FALSE) {

                    if (first == AM_TRUE) {

                        count16 = value;

                        first  = AM_FALSE;

                    } else {

                        /* ��ʱ��TIM����32λ������ʱ, �������ʱ���ݴ��� */
                        if(count16 < value) {

														reg_pre = (uint16_t)amhw_zlg_tim_prescale_get(p_hw_tim);

														pre = reg_pre + 1;

														count_err = value - count16;

														/* �����ζ�ȡֵ�Ĳ�ת����ʱ�� */
														time_ns = (uint64_t)1000000000 *
																			(uint64_t)count_err *
																			pre /
																			(uint64_t)__g_clk_rate;

														g_time_ns = time_ns;
												}

                        first = AM_TRUE;

                        /* �ñ�־Ϊ�棬����������� */
                        g_flag = AM_TRUE;
                    }
                }
					  }
            /* ���ͨ��i��־ */
            amhw_zlg_tim_status_flg_clr(p_hw_tim, (1UL << i));
        }
    }
}

/**
 * \brief ���ö�ʱ��Ϊ���벶��
 */
static void tim_cap_chan_config (amhw_zlg_tim_t     *p_hw_tim,
                                 amhw_zlg_tim_type_t type,
                                 uint32_t            chan,
                                 uint32_t            cap_edge)
{

    /* �������벻��Ƶ, 1 �α��ؾʹ��� 1 �β��� */
    amhw_zlg_tim_icpsc_set(p_hw_tim, 0, chan);

    /* ѡ�������ͨ��ӳ�䲻���� */
    amhw_zlg_tim_ccs_set(p_hw_tim, 1, chan);

    /* ���������˲����ķ�ƵֵΪ 0(Ĭ�ϲ�ʹ���˲�) */
    amhw_zlg_tim_icf_set(p_hw_tim, AMHW_ZLG_TIM_ICF_FSAMPLING0, chan);

    /*  ѡ�������ش��� */
    if ((cap_edge & AM_CAP_TRIGGER_RISE) == AM_CAP_TRIGGER_RISE) {
        amhw_zlg_tim_ccp_captrigger_set(p_hw_tim,
                                           type,
                                           AM_CAP_TRIGGER_RISE,
                                           chan);
    }

    /*  ѡ���½��ش��� */
    if ((cap_edge & AM_CAP_TRIGGER_FALL) == AM_CAP_TRIGGER_FALL) {
        amhw_zlg_tim_ccp_captrigger_set(p_hw_tim,
                                           type,
                                           AM_CAP_TRIGGER_FALL,
                                           chan);
    }
}

static void tim_cap_enable (amhw_zlg_tim_t *p_hw_tim,
                            uint32_t        chan,
                            uint8_t         int_num)
{

    /* �ж����Ӳ�ʹ�� */
    am_int_connect(int_num, __zlg_tim_hw_cap_irq_handler, (void *)p_hw_tim);
    am_int_enable(int_num);

    /* �����Զ���װ�Ĵ�����ֵ */
    amhw_zlg_tim_arr_set(p_hw_tim, 0xffffffff);

    /* ��������� */
    amhw_zlg_tim_count_set(p_hw_tim, 0);

    /* ���������¼������³�ʼ��Prescaler������ ��Repetition������ */
    amhw_zlg_tim_egr_set(p_hw_tim, AMHW_ZLG_TIM_UG);

    if (amhw_zlg_tim_status_flg_get(p_hw_tim, AMHW_ZLG_TIM_UG) != 0) {

        /* ���¶�ʱ��ʱ����������¼�,�����־λ */
        amhw_zlg_tim_status_flg_clr(p_hw_tim, AMHW_ZLG_TIM_UG);
    }

    /* �������������ֵ������Ĵ����� */
    amhw_zlg_tim_cce_cap_enable(p_hw_tim, chan);

    /* �������ж� */
    amhw_zlg_tim_int_enable(p_hw_tim, (1UL << (chan + 1)));

    /*��ʹ�ܶ�ʱ��TIM������� */
    amhw_zlg_tim_enable(p_hw_tim);
}

/**
 * \brief ��ʱ�����벶���ʼ������
 */
static void tim_cap_init (amhw_zlg_tim_t *p_hw_tim, amhw_zlg_tim_type_t type)
{
    if ((AMHW_ZLG_TIM_TYPE0 == type) || (AMHW_ZLG_TIM_TYPE1 == type)) {

        /* ���ض���ģʽ */
        amhw_zlg_tim_cms_set(p_hw_tim, 0);

        /* ���ϼ��� */
        amhw_zlg_tim_dir_set(p_hw_tim, 0);
    }

    /* ����ʱ�ӷָ�(����ȷ�������˲���������ʱ��Ƶ��,Ĭ�� Fdts = Fck_in */
    amhw_zlg_tim_ckd_set(p_hw_tim, 0);

    /* ��������� */
    amhw_zlg_tim_count_set(p_hw_tim, 0);

    /* ���÷�Ƶ�� */
    amhw_zlg_tim_prescale_set(p_hw_tim, 0x00);

    /* ��������¼� */
    amhw_zlg_tim_udis_enable(p_hw_tim);
}

/**
 * \brief �������
 */
void demo_zlg_hw_tim_cap_entry (amhw_zlg_tim_t      *p_hw_tim,
                                amhw_zlg_tim_type_t  type,
                                uint32_t             chan,
                                uint32_t             clk_rate,
                                int32_t              inum)
{
    uint32_t freq = 0; /* ���񵽵�Ƶ�� */

    __g_clk_rate = clk_rate;

    /* ��ʼ����ʱ��Ϊ������ */
    tim_cap_init(p_hw_tim, type);

    /* ���ö�ʱ������ͨ�� (��֧��˫���ش�������) */
    tim_cap_chan_config(p_hw_tim,
                        type,
                        chan,
                        AM_CAP_TRIGGER_RISE);

    tim_cap_enable(p_hw_tim, chan, inum);

    while (1) {

        if (g_flag == AM_TRUE) {

            freq = 1000000000 / g_time_ns;
            AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n",
                        g_time_ns,
                        freq);
            g_flag = AM_FALSE;
        }
    }
}
/** [src_zlg_hw_tim_cap] */

/* end of file */
