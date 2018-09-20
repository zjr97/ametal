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
 * \brief MicroPort SC16IS740 �����ļ�
 * \sa am_hwconf_microport_sc16is740.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_time.h"
#include "am_alarm_clk.h"
#include "am_sc16is740.h"
#include "am_zlg116_inst_init.h"
#include "zlg116_pin.h"

/**
 * \addtogroup am_if_src_hwconf_microport_sc16is740
 * \copydoc am_hwconf_microport_sc16is740.c
 * @{
 */

/** \brief �豸��Ϣ */
am_local am_const am_sc16is740_devinfo_t __g_microport_sc16is740_devinfo = {
    -1,    /**< \brief INT δʹ�� */
    -1,    /**< \brief CLK_EN δʹ�� */
};

/*******************************************************************************
  MicroPort SC16IS740 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

/** \brief �豸���� */
am_local am_sc16is740_dev_t __g_microport_sc16is740_dev;

/** \brief ʵ����ʼ�� */
am_sc16is740_handle_t am_microport_sc16is740_inst_init (void)
{

    /* ��ȡ I2C ʵ����� */
    am_i2c_handle_t i2c_handle = am_zlg116_i2c1_inst_init();

    return am_sc16is740_init(&__g_microport_sc16is740_dev,
                           &__g_microport_sc16is740_devinfo,
                            i2c_handle);
}

/*******************************************************************************
  MicroPort SC16IS740 ʵ����ʼ�� ��ʹ��ͨ�õ� RTC ���ܣ�
*******************************************************************************/

/** \brief �豸���� */
am_local am_rtc_serv_t __g_microport_sc16is740_rtc;

/** \brief ʵ����ʼ�� */
am_rtc_handle_t am_microport_sc16is740_rtc_inst_init (void)
{
    am_sc16is740_handle_t microport_sc16is740_handle = am_microport_sc16is740_inst_init();

    return am_sc16is740_rtc_init(microport_sc16is740_handle,
                              &__g_microport_sc16is740_rtc);
}

#if 0
/*******************************************************************************
  MicroPort SC16IS740 ʵ����ʼ�� ��ʹ��ͨ�õ����ӹ��ܣ�
*******************************************************************************/

/** \brief �豸���� */
am_local am_alarm_clk_serv_t __g_microport_sc16is740_alarm_clk;

/** \brief ʵ����ʼ�� */
am_alarm_clk_handle_t  am_microport_sc16is740_alarm_clk_inst_init (void)
{
    am_sc16is740_handle_t  microport_sc16is740_handle = am_microport_sc16is740_inst_init();
    return am_sc16is740_alarm_clk_init(microport_sc16is740_handle,
                                    &__g_microport_sc16is740_alarm_clk);
}
#endif

/*******************************************************************************
  MicroPort SC16IS740 ʵ����ʼ�� ����SC16IS740����ϵͳʱ�䣩
*******************************************************************************/

/** \brief ÿ 1ms(1000000ns) ����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_SYSCLK_NS   1000000

/** \brief ÿ 10s ���� RTC ����һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S       10

/** \brief ʵ����ʼ�� */
int am_microport_sc16is740_time_inst_init (void)
{
    am_rtc_handle_t rtc_handle = am_microport_sc16is740_rtc_inst_init();

    return am_time_init(rtc_handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
