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
 * \brief MicroPort-DS1302 �û������ļ�
 * \sa am_hwconf_microport_ds1302.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_time.h"
#include "am_ds1302.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_microport_ds1302
 * \copydoc am_hwconf_microport_ds1302.c
 * @{
 */

/** \brief MicroPort-DS1302 �豸��Ϣ */
am_local am_const am_ds1302_gpio_devinfo_t __g_microport_ds1302_gpio_devinfo = {
    PIO0_15,    /* SCLK ���� */
    PIO0_14,    /* CE ���� */
    PIO0_13,    /* IO ���� */
};

/*******************************************************************************
  MicroPort-DS1302 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

/** \brief MicroPort-DS1302 (GPIO ģʽ) �豸ʵ�� */
am_local am_ds1302_gpio_dev_t __g_microport_ds1302_gpio_dev;

/**
 * \brief MicroPort-DS1302 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
 */
am_ds1302_handle_t am_microport_ds1302_inst_init (void)
{
    return am_ds1302_gpio_init(&__g_microport_ds1302_gpio_dev,
                               &__g_microport_ds1302_gpio_devinfo);
}

/*******************************************************************************
  MicroPort-DS1302 ʵ����ʼ�� ��ʹ��ͨ�õ� RTC ���ܣ�
*******************************************************************************/

/** \brief MicroPort-DS1302 (RTC ��׼����) �豸ʵ�� */
am_local am_rtc_serv_t __g_microport_ds1302_rtc;

/** \brief MicroPort-DS1302 ʵ����ʼ����ʹ��ͨ�õ� RTC ���ܣ� */
am_rtc_handle_t am_microport_ds1302_rtc_inst_init (void)
{
    am_ds1302_handle_t handle = am_microport_ds1302_inst_init();

    if (NULL != handle) {
        return am_ds1302_rtc_init(handle,
                                 &__g_microport_ds1302_rtc);
    } else {
        return NULL;
    }
}

/*******************************************************************************
  MicroPort-DS1302 ʵ����ʼ�� ���� DS1302 ����ϵͳʱ�䣩
*******************************************************************************/

/** \brief ÿ 1ms(1000000ns) ����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_SYSCLK_NS    1000000

/** \brief ÿ 10s ���� RTC ����һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S        10

/**
 * \brief MicroPort-DS1302 ʵ����ʼ������ DS1302 ����ϵͳʱ�䣩
 */
int am_microport_ds1302_time_inst_init (void)
{
    am_rtc_handle_t handle = am_microport_ds1302_rtc_inst_init();

    return am_time_init(handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
