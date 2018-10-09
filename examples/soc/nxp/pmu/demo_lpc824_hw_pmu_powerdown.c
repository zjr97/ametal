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
 * \brief PMU ����ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ�鲽�裺
 *   1. �öŰ��߽� PIO0_23 �� GND ���ӣ��ѵ�ƽ���͡�
 *
 * - ʵ������
 *   1. ���г���һ��� LED0 ��˸һ�κ�������ģʽ��
 *   2. �� PIO0_23 �� GND �����ӶϿ�ʱ��CPU �����ѣ�LED0 ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ʹ�øó���󣬻ᵼ���´γ�����д��ʱ���ⲻ��оƬ������оƬ�������
 *       ģʽ�� SWD ����ģʽ�رգ����´�����ʱ�� P0_12 ���ͻ򰴶���λ��֮��һ����
 *       �����������ص��ԡ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_pmu_powerdown.c src_lpc824_hw_pmu_powerdown
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-21  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_pmu_powerdown
 * \copydoc demo_lpc824_hw_pmu_powerdown.c
 */

/** [src_lpc824_hw_pmu_powerdown] */
#include "ametal.h"
#include "am_int.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_pint.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/**
 * \name ϵͳ���ƼĴ����궨��
 * @{
 */

/** \brief ���������ص��߳�ģʽʱ������˯�� */
#define __AMHW_LPC82X_SCR_ISRBACK_NTO_SLP     AM_SBF(0, 1)

/** \brief ���������ص��߳�ģʽʱ����˯�� */
#define __AMHW_LPC82X_SCR_ISRBACK_TO_SLP      AM_SBF(1, 1)

/** \brief ��˯��ģʽ��Ϊ�͹���ģʽ */
#define __AMHW_LPC82X_SCR_LOWPWR_MODE_SLP     AM_SBF(0, 2)

/** \brief �����˯��ģʽ��Ϊ�͹���ģʽ */
#define __AMHW_LPC82X_SCR_LOWPWR_MODE_DPSLP   AM_SBF(1, 2)

/** \brief ֻ��ʹ�ܵ��ж��ܹ����Ѵ����� */
#define __AMHW_LPC82X_SCR_WKUP_BY_ENAISR      AM_SBF(0, 4)

/** \brief �����ж��ܹ����Ѵ����� */
#define __AMHW_LPC82X_SCR_WKUP_BY_ALLISR      AM_SBF(1, 4)

/**
 * @}
 */

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/
am_local volatile uint8_t __g_powerdown_wkt_flag = 0; /** \brief �жϱ�־���� */

/*******************************************************************************
  ���غ�������
*******************************************************************************/

/**
 * \brief ϵͳ���ƼĴ����趨
 *
 * \param[in] flags ϵͳ���ƼĴ����� (#__AMHW_LPC82X_SCR_ISRBACK_NTO_SLP)
 *
 * \return ��
 */
am_local void __lpc82x_scb_scr_set (uint32_t flags)
{
    SCB->SCR = flags;
}

/**
 * \brief �����жϷ�����
 */
am_local void __powerdown_pint_isr (void *p_arg)
{

    /* ����жϱ�־ */
    amhw_lpc82x_pint_edge_dec_clr(LPC82X_PINT, AMHW_LPC82X_PINT_CHAN_0);

    /* �ı��жϱ�־���� */
    __g_powerdown_wkt_flag = 1;
}

/**
 * \brief PMU ����ģʽ��ʼ��
 */
void demo_lpc824_hw_pmu_powerdown_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                         int                 pin)
{

    /* LED0 ��˸һ�� */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);
  
    /* �򿪿��Ź�������Դ */
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_WDT_OSC);

    /* PIO0_23 �ж�ʹ���ж�ͨ�� 0 */
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_0, pin);

    /* ����Ϊ˫���ش��� */
    amhw_lpc82x_pint_trigger_set(LPC82X_PINT,
                                 AMHW_LPC82X_PINT_CHAN_0,
                                 AMHW_LPC82X_PINT_TRIGGER_BOTH_EDGES);

    /* PIN0 ��Ϊ����Դ */
    amhw_lpc82x_syscon_wakeup_enable(AMHW_LPC82X_SYSCON_STARTER_PINT0);

    /* �����жϷ����� */
    am_int_connect(INUM_PIN_INT0, __powerdown_pint_isr, (void *)0);

    /* ʹ�������ж� */
    am_int_enable(INUM_PIN_INT0);

    /* ���û��ѼĴ��� */
    amhw_lpc82x_syscon_deepwakeup_cfg(amhw_lpc82x_syscon_powerstat_get());

    /* BOD �ϵ磬���Ź�������Դ�ϵ� */
    amhw_lpc82x_syscon_deepsleep_enable(AMHW_LPC82X_SYSCON_PD_BOD |
                                        AMHW_LPC82X_SYSCON_PD_WDT_OSC);

    /* ARM Cortex-M0+ �ں˵ĵ͹���ģʽ������Ϊ���˯��ģʽ */
    __lpc82x_scb_scr_set(__AMHW_LPC82X_SCR_ISRBACK_NTO_SLP   | /* �жϷ���ʱ������˯��ģʽ */
                         __AMHW_LPC82X_SCR_LOWPWR_MODE_DPSLP | /* ���˯��ģʽ��Ϊ�͹���ģʽ */
                         __AMHW_LPC82X_SCR_WKUP_BY_ENAISR);    /* ֻ��ʹ�ܵ��жϲ��ܻ��� */

    /* ARM WFI ���������ģʽ */
    amhw_lpc82x_pmu_pm_cfg(p_hw_pmu, AMHW_LPC82X_PMU_PCON_MODE_PD);

    /* �������ģʽ */
    __WFI();

    AM_FOREVER {

        /* �ӵ���ģʽ���Ѻ�LED0 ������˸ */
        am_led_toggle(LED0);
        am_mdelay(500);
    }
}
/** [src_lpc824_hw_pmu_powerdown] */

/* end of file */
