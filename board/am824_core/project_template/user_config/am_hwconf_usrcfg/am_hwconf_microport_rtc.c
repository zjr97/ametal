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
 * \brief MicroPort-RTC(PCF85063) �û������ļ�
 * \sa am_hwconf_microport_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_time.h"
#include "am_pcf85063.h"
#include "am_alarm_clk.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_microport_rtc
 * \copydoc am_hwconf_microport_rtc.c
 * @{
 */

/** \brief MicroPort-RTC �豸��Ϣ */
am_local am_const am_pcf85063_devinfo_t __g_microport_rtc_devinfo = {
    PIO0_1,    /* INT ���� */
    -1,        /* CLK_EN ���� */
};

/*******************************************************************************
  MicroPort PCF85063 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

/** \brief MicroPort-RTC �豸ʵ�� */
am_local am_pcf85063_dev_t __g_microport_rtc_dev;

/**
 * \brief MicroPort-RTC ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
 */
am_pcf85063_handle_t am_microport_rtc_inst_init (void)
{
    am_i2c_handle_t i2c_handle = am_lpc82x_i2c1_inst_init();

    return am_pcf85063_init(&__g_microport_rtc_dev,
                            &__g_microport_rtc_devinfo,
                             i2c_handle);
}

/*******************************************************************************
  MicroPort PCF85063 ʵ����ʼ�� ��ʹ��ͨ�õ� RTC ���ܣ�
*******************************************************************************/

/** \brief MicroPort-RTC (RTC ��׼����) �豸ʵ�� */
am_local am_rtc_serv_t __g_microport_rtc_rtc_serv;

/**
 * \brief MicroPort-RTC ʵ����ʼ����ʹ��ͨ�õ� RTC ���ܣ�
 */
am_rtc_handle_t am_microport_rtc_rtc_inst_init (void)
{
    am_pcf85063_handle_t handle = am_microport_rtc_inst_init();

    return am_pcf85063_rtc_init(handle,
                               &__g_microport_rtc_rtc_serv);
}

/*******************************************************************************
  MicroPort PCF85063 ʵ����ʼ�� ��ʹ��ͨ�õ����ӹ��ܣ�
*******************************************************************************/

/** \brief MicroPort-RTC (ALARM_CLK ��׼����) �豸ʵ�� */
am_local am_alarm_clk_serv_t __g_microport_rtc_alarm_clk_serv;

/**
 * \brief MicroPort-RTC ʵ����ʼ����ʹ��ͨ�õ����ӹ��ܣ�
 */
am_alarm_clk_handle_t am_microport_rtc_alarm_clk_inst_init (void)
{
    am_pcf85063_handle_t handle = am_microport_rtc_inst_init();

    return am_pcf85063_alarm_clk_init(handle,
                                     &__g_microport_rtc_alarm_clk_serv);
}

/*******************************************************************************
  MicroPort PCF85063 ʵ����ʼ�� ���� PCF85063 ����ϵͳʱ�䣩
*******************************************************************************/

/** \brief ÿ 1ms(1000000ns) ����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_SYSCLK_NS   1000000

/** \brief ÿ 10s ���� RTC ����һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S       10

/**
 * \brief MicroPort-RTC ʵ����ʼ������ PCF85063 ����ϵͳʱ�䣩
 */
int am_microport_rtc_time_inst_init (void)
{
    am_rtc_handle_t handle = am_microport_rtc_rtc_inst_init();

    return am_time_init(handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
