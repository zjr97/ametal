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
 * \brief PIT ��ʱ��ʵ��(32λ)��ʱ���ܵ����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 *
 * - ע�⣺
 *    ���Ҫ���д����̣���Ҫ��am_prj_config.h��AM_CFG_SOFTIMER_ENABLE��
 *    AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SYSTEM_TICK_ENABLE�������ֵ����Ϊ0��
 *
 * \par Դ����
 * \snippet demo_fsl_hw_pit_1_32bit_timing.c src_fsl_hw_pit_1_32bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */


/**
 * \addtogroup demo_fsl_if_hw_pit_1_32bit_timing
 * \copydoc demo_fsl_hw_pit_1_32bit_timing.c
 */

/** [src_fsl_hw_pit_1_32bit_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_int.h"
#include "hw/amhw_fsl_pit.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"

/**
 * \brief  PIT0�жϷ�����
 * \param[in]  p_arg : �û��Զ���������� am_int_connect() �������ݡ�
 * \return  ��
 */
void pit0_irq_handler(void *p_arg)
{
    amhw_fsl_pit_t *p_hw_pit = (amhw_fsl_pit_t *)p_arg;
    /* ͨ��0�����ж� */
    if (amhw_fsl_pit_timerout_flag_check(p_hw_pit , AMHW_FSL_PIT_CH(0)) == AM_TRUE ) {

        am_led_toggle(LED0);

        /* �����־ */
        amhw_fsl_pit_timerout_flag_clr(p_hw_pit , AMHW_FSL_PIT_CH(0));
    }
}

/**
 * \brief ��ʼ��PITΪ��ʱ�����ܡ�
 *
 * \param[in] p_pit : ָ��PIT�Ĵ������ָ��
 * \param[in] freq  : �ж�Ƶ�ʡ�
 *
 * \return ��
 */
void pit_timer_init (amhw_fsl_pit_t *p_hw_pit,
                     uint32_t        freq,
                     int             inum,
                     uint32_t        pit_clk)
{
    uint32_t load_val;

    load_val = pit_clk / freq;

    /* ʹ��PITģ�� */
    amhw_fsl_pit_module_enable(p_hw_pit);

    /* ����װ��ֵ */
    amhw_fsl_pit_ldval_set(p_hw_pit, AMHW_FSL_PIT_CH(0), load_val);

    /* ���жϲ�ʹ�ܼ��� */
    amhw_fsl_pit_timer_ctrl_set(p_hw_pit,
                                 AMHW_FSL_PIT_CH(0),
                                 AMHW_FSL_PIT_TCTL_TI_EN | AMHW_FSL_PIT_TCTL_TMR_EN);

    am_int_connect(inum, pit0_irq_handler, p_hw_pit);
    am_int_enable(inum);
}


/**
 * \brief ʹ��PITΪ��ʱ��(��ʼ����)
 * \param[in] p_pit : ָ��PIT�Ĵ������ָ��
 * \return ��
 */
void pit_timer_enable (amhw_fsl_pit_t *p_hw_pit)
{
    /* ��ʼ���� */
    amhw_fsl_pit_timer_ctrl_set(p_hw_pit,
                                 AMHW_FSL_PIT_CH(0),
                                 AMHW_FSL_PIT_TCTL_TMR_EN);
}

/**
 * \brief  ��ֹPITΪ��ʱ��(ֹͣ����)
 * \param[in] p_pit : ָ��PIT�Ĵ������ָ��
 * \return  ��
 */
void pit_timer_disable (amhw_fsl_pit_t *p_hw_pit)
{
    /* ��ֹͣλ��PITֹͣ���� */
    amhw_fsl_pit_timer_ctrl_clear(p_hw_pit,
                                   AMHW_FSL_PIT_CH(0),
                                   AMHW_FSL_PIT_TCTL_TMR_EN);
}

/**
 * \brief �������
 */
void demo_fsl_hw_pit_1_32bit_timing_entry (amhw_fsl_pit_t *p_hw_pit,
                                           int             inum,
                                           uint32_t        pit_clk)
{

    AM_DBG_INFO("The demo for PIT timing:\r\n");
    AM_DBG_INFO("The led toggle in 10Hz \r\n");

    /* ʹ��PITʵ�ֶ�ʱ���ܣ��ж�Ƶ��Ϊ10Hz */
    pit_timer_init(p_hw_pit , 10, inum, pit_clk);

    /* ʹ��PIT���� */
    pit_timer_enable(p_hw_pit);

    while (1) {

    }
}

/** [src_fsl_hw_pit_1_32bit_timing] */

/* end of file */
