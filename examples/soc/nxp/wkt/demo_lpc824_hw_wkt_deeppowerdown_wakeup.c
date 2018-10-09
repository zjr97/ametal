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
 * \brief WKT ��ȵ��绽�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���г���һ��� LED0 ��˸һ�κ������ȵ���ģʽ��
 *   2. �ȴ� 5s ��WKT ��ʱʱ�䵽��CPU �����ѣ����ͨ�üĴ�������У����ȷ��LED0
 *      ��˸һ�Σ����ͨ�üĴ�������У�����LED0 ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ������ȵ���ģʽ��ֻ�� WAKEUP ���ź� WKT ��ʱ���ܻ���оƬ������Ĭ��״̬��
 *       WAKEUP ���Ż���ʹ�ܣ�����һ��ȷ�� WAKEUP �ⲿ��������Դ����֤��Ч�ĸߵ�ƽ
 *       ״̬��������������Ѳ��������۲첻�� WKT ���� CPU���������̽� WAKEUP ����
 *       (PIO0_4)���ѹ��ܽ�ֹ�ˣ����Բ���Ҫ�� PIO0_4 ������
 *    3. ʹ�øó���󣬻ᵼ���´γ�����д��ʱ���ⲻ��оƬ������оƬ������ȵ���
 *       ģʽ�� SWD ����ģʽ�رգ����´�����ʱ�� P0_12 ���ͻ򰴶���λ��֮��һ����
 *       �����������ص��ԡ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_wkt_deeppowerdown_wakeup.c src_lpc824_hw_wkt_deeppowerdown_wakeup
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-14  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_wkt_deeppowerdown_wakeup
 * \copydoc demo_lpc824_hw_wkt_deeppowerdown_wakeup.c
 */

/** [src_lpc824_hw_wkt_deeppowerdown_wakeup] */
#include "ametal.h"
#include "am_int.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc_wkt.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** \brief ѡ�� IRC ʱ�� Ƶ��Ϊ 750kHz */
#define __IRC_CLOCK_FREQ          750

/** \brief ѡ��͹���ʱ�� Ƶ��Ϊ 10kHz */
#define __LOW_POWER_CLOCK_FREQ    10

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

/** \brief �жϱ�־���� */
am_local volatile uint8_t __g_deeppowerdown_wkt_flag = 0;

/*******************************************************************************
  ���غ�������
*******************************************************************************/

/**
 * \brief ���õ�ǰ��ʱ���ļ���ֵ
 *
 * \param[in] delay_inms ���ö�ʱʱ�� delay_inms����ʱʱ��(��λ��ms)
 *
 * \return ��
 */
am_local void __wkt_delayms_set (amhw_lpc_wkt_t  *p_hw_wkt, uint32_t delay_inms)
{

    /* ��ʱ (delay_inms) ms */
    if(amhw_lpc_wkt_clksel_get(p_hw_wkt)) {
        amhw_lpc_wkt_count_set(p_hw_wkt,
                               __LOW_POWER_CLOCK_FREQ * delay_inms);
    } else {
        amhw_lpc_wkt_count_set(p_hw_wkt, __IRC_CLOCK_FREQ * delay_inms);
    }
}

/**
 * \brief ϵͳ���ƼĴ����趨
 *
 * \param[in] flags ϵͳ���ƼĴ����� (#__AMHW_LPC82X_SCR_ISRBACK_NTO_SLP)
 *
 * \return ��
 */
am_local void __scb_scr_set (uint32_t flags)
{
    SCB->SCR = flags;
}

/**
 * \brief WKT �жϷ�����
 */
am_local void __deeppowerdown_wkt_isr (void *p_arg)
{
    amhw_lpc_wkt_t  *p_hw_wkt = (amhw_lpc_wkt_t *)p_arg;

    if (amhw_lpc_wkt_alarmflag_get(p_hw_wkt)) {
        amhw_lpc_wkt_alarmflag_clear(p_hw_wkt); /* ����жϱ�־ */
        __g_deeppowerdown_wkt_flag = 1;                /* �ı��жϱ�־���� */
    }
}

/**
 * \brief ��ȵ���ģʽ��ʼ��
 */
am_local void __wkt_deeppowerdown_wakeup (amhw_lpc82x_pmu_t *p_hw_pmu,
                                          amhw_lpc_wkt_t    *p_hw_wkt,
                                          int                inum,
                                          uint32_t           delay_inms)
{

    /* �Ѿ�����ȵ����л��� */
    if (amhw_lpc82x_pmu_dpdflag_get(p_hw_pmu) != 0x0) {

        /* �����ȵ���ģʽ��־λ */
        amhw_lpc82x_pmu_dpdflag_clear(p_hw_pmu);

        if ((amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_0) != 0x12345678) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_1) != 0x87654321) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_2) != 0x56781234) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_3) != 0x43218765)) {

            /* ����ȵ��绽�Ѻ�ͨ�üĴ������ݼ��ʧ�ܣ�LED0 ������˸ */
            AM_FOREVER {

                /* LED0 �� 0.5s �ļ��һֱ��˸ */
                am_led_toggle(LED0);
                am_mdelay(500);
            }
        }
    } else {

        /* δ������ȵ���ģʽ������ͨ�üĴ������ݣ����ڲ��� */
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_0, 0x12345678);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_1, 0x87654321);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_2, 0x56781234);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_3, 0x43218765);

        /* �������� PIO0_4 �ϵĻ��ѹ��� */
        amhw_lpc82x_pmu_wakepad_disable(p_hw_pmu);

        /* ARM Cortex-M0+ �ں˵ĵ͹���ģʽ������Ϊ���˯��ģʽ */
        __scb_scr_set(__AMHW_LPC82X_SCR_LOWPWR_MODE_DPSLP);

        /* ʹ�ܵ͹������� */
        amhw_lpc82x_pmu_lposcen_enable(p_hw_pmu);

        /* ��ȵ���ģʽ��ʹ�ܵ͹������� */
        amhw_lpc82x_pmu_lposcdpden_enable(p_hw_pmu);

        /* ARM WFI ��������ȵ���ģʽ */
        amhw_lpc82x_pmu_pm_cfg(p_hw_pmu,
                               AMHW_LPC82X_PMU_PCON_MODE_DEEPPD);

        /* ��ʱ (delayInMs) delay_inmss */
        __wkt_delayms_set(p_hw_wkt, delay_inms);
       
        /* �� WKT �ж� */
        am_int_enable(inum);
       
        /* �����жϷ����� */
        am_int_connect(inum, __deeppowerdown_wkt_isr, (void *)p_hw_wkt);

        /* ������ȵ���ģʽ */
        __WFI();
    }
}

/*******************************************************************************
  �ⲿ��������
*******************************************************************************/

void demo_lpc824_hw_wkt_deeppowerdown_wakeup_entry(amhw_lpc82x_pmu_t *p_hw_pmu,
                                                   amhw_lpc_wkt_t    *p_hw_wkt,
                                                   int                inum,
                                                   uint32_t           delay_inms)
{

    /* ��ʱһ�룬�����´����س��� */
    am_mdelay(1000);

    /* LED0 ��˸һ�� */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);

    /* ���� DeepPowerDown ģʽ */
    __wkt_deeppowerdown_wakeup(p_hw_pmu, p_hw_wkt, inum, delay_inms);

    /* ����ȵ���ģʽ���Ѻ�ͨ�üĴ������ݼ����ȷ��LED0 ��˸һ�� */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);

    AM_FOREVER {
        ; /* VOID */
    }
}

/** [src_lpc824_hw_wkt_deeppowerdown_wakeup] */

/* end of file */
