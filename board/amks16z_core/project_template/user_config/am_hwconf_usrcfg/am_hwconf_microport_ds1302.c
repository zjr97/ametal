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
 * \brief MicroPort DS1302 �����ļ�
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
#include "am_kl26_inst_init.h"
#include "kl26_pin.h"

/**
 * \addtogroup am_if_src_hwconf_microport_ds1302
 * \copydoc am_hwconf_microport_ds1302.c
 * @{
 */

/** \brief �豸��Ϣ */
am_local am_const am_ds1302_gpio_devinfo_t __g_microport_ds1302_gpio_devinfo = {
    PIOD_1,      /**< \brief SCLK ��Ӧ�� IO ���ź� */
    PIOD_0,      /**< \brief CE ��Ӧ�� IO ���ź� */
    PIOD_3,      /**< \brief IO ��Ӧ�� IO ���ź� */
};

/*******************************************************************************
  MicroPort DS1302 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

/** \brief �豸���� */
am_local am_ds1302_gpio_dev_t __g_microport_ds1302_gpio_dev;

/** \brief ʵ����ʼ�� */
am_ds1302_handle_t am_microport_ds1302_inst_init (void)
{
    am_local am_ds1302_handle_t microport_ds1302_handle = NULL;

    if (microport_ds1302_handle == NULL) {
        microport_ds1302_handle = am_ds1302_gpio_init(
                                            &__g_microport_ds1302_gpio_dev,
                                            &__g_microport_ds1302_gpio_devinfo);
    }

    return microport_ds1302_handle;
}

/*******************************************************************************
  MicroPort DS1302 ʵ����ʼ�� ��ʹ��ͨ�õ� RTC ���ܣ�
*******************************************************************************/

/** \brief �豸���� */
am_local am_rtc_serv_t __g_microport_ds1302_rtc;

/** \brief ʵ����ʼ�� */
am_rtc_handle_t am_microport_ds1302_rtc_inst_init (void)
{
    am_ds1302_handle_t microport_ds1302_handle = am_microport_ds1302_inst_init();

    return am_ds1302_rtc_init(microport_ds1302_handle,
                             &__g_microport_ds1302_rtc);
}

/*******************************************************************************
  MicroPort DS1302 ʵ����ʼ�� ���� DS1302 ����ϵͳʱ�䣩
*******************************************************************************/

/** \brief ÿ 1ms(1000000ns) ����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_SYSCLK_NS   1000000

/** \brief ÿ 10s ���� RTC ����һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S       10

/** \brief ʵ����ʼ�� */
int am_microport_ds1302_time_inst_init (void)
{
    am_rtc_handle_t rtc_handle = am_microport_ds1302_rtc_inst_init();

    return am_time_init(rtc_handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
