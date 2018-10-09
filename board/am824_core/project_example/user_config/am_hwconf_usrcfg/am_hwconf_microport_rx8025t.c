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
 * \brief MicroPort-RX8025T �û������ļ�
 * \sa am_hwconf_microport_rx8025t.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_time.h"
#include "am_rx8025t.h"
#include "am_alarm_clk.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_microport_rx8025t
 * \copydoc am_hwconf_microport_rx8025t.c
 * @{
 */

/** \brief MicroPort-RX8025T �豸��Ϣ */
am_local am_const am_rx8025t_devinfo_t __g_microport_rx8025t_devinfo = {
    PIO0_1,     /* INT ���� */
    PIO0_11,    /* CLK_EN ���� */
};

/*******************************************************************************
  MicroPort-RX8025T ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

/** \brief MicroPort-RX8025T �豸ʵ�� */
am_local am_rx8025t_dev_t __g_microport_rx8025t_dev;

/**
 * \brief MicroPort-RX8025T ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
 */
am_rx8025t_handle_t am_microport_rx8025t_inst_init (void)
{
    am_i2c_handle_t i2c_handle = am_lpc82x_i2c1_inst_init();

    return am_rx8025t_init(&__g_microport_rx8025t_dev,
                           &__g_microport_rx8025t_devinfo,
                            i2c_handle);
}

/*******************************************************************************
  MicroPort-RX8025T ʵ����ʼ�� ��ʹ��ͨ�õ� RTC ���ܣ�
*******************************************************************************/

/** \brief MicroPort-RX8025T (RTC ��׼����) �豸ʵ�� */
am_local am_rtc_serv_t __g_microport_rx8025t_rtc;

/**
 * \brief MicroPort-RX8025T ʵ����ʼ����ʹ��ͨ�õ� RTC ���ܣ�
 */
am_rtc_handle_t am_microport_rx8025t_rtc_inst_init (void)
{
    am_rx8025t_handle_t handle = am_microport_rx8025t_inst_init();

    return am_rx8025t_rtc_init(handle,
                              &__g_microport_rx8025t_rtc);
}

/*******************************************************************************
  MicroPort-RX8025T ʵ����ʼ�� ��ʹ��ͨ�õ����ӹ��ܣ�
*******************************************************************************/

/** \brief MicroPort-RX8025T (ALARM_CLK ��׼����) �豸ʵ�� */
am_local am_alarm_clk_serv_t __g_microport_rx8025t_alarm_clk;

/**
 * \brief MicroPort-RX8025T ʵ����ʼ����ʹ��ͨ�õ����ӹ��ܣ�
 */
am_alarm_clk_handle_t  am_microport_rx8025t_alarm_clk_inst_init (void)
{
    am_rx8025t_handle_t handle = am_microport_rx8025t_inst_init();

    return am_rx8025t_alarm_clk_init(handle,
                                    &__g_microport_rx8025t_alarm_clk);
}

/*******************************************************************************
  MicroPort-RX8025T ʵ����ʼ�� ���� RX8025T ����ϵͳʱ�䣩
*******************************************************************************/

/** \brief ÿ 1ms(1000000ns) ����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_SYSCLK_NS   1000000

/** \brief ÿ 10s ���� RTC ����һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S       10

/**
 * \brief MicroPort-RX8025T ʵ����ʼ������ RX8025T ����ϵͳʱ�䣩
 */
int am_microport_rx8025t_time_inst_init (void)
{
    am_rtc_handle_t rtc_handle = am_microport_rx8025t_rtc_inst_init();

    return am_time_init(rtc_handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
