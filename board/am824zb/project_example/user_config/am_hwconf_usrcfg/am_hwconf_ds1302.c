/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief DS1302 �����ļ�
 * \sa am_hwconf_ds1302.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "lpc82x_pin.h"
#include "am_ds1302.h"
#include "am_time.h"

/**
 * \addtogroup am_if_src_hwconf_ds1302
 * \copydoc am_hwconf_ds1302.c
 * @{
 */

/*******************************************************************************
    DS1302 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

/* ����һ��ds1302ʵ�� */
static am_ds1302_gpio_dev_t            __g_ds1302_gpio_dev;

/* DS1302ʵ����Ϣ */
static const am_ds1302_gpio_devinfo_t  __g_ds1302_gpio_devinfo = {
    PIO0_15,                                       /* SCLK��Ӧ��IO���ź� */
    PIO0_14,                                       /* CE��Ӧ��IO���ź� */
    PIO0_13,                                       /* IO��Ӧ��IO���ź� */
};

am_ds1302_handle_t am_ds1302_inst_init (void)
{
    static am_ds1302_handle_t ds1302_handle = NULL;

    if (ds1302_handle == NULL) {
        ds1302_handle = am_ds1302_gpio_init(&__g_ds1302_gpio_dev,
                                            &__g_ds1302_gpio_devinfo);
    }

    return ds1302_handle;
}

/*******************************************************************************
    DS1302 ʵ����ʼ�� ��ʹ��ͨ�õ�RTC���ܣ�
*******************************************************************************/

static am_rtc_serv_t      __g_ds1302_rtc;                 /* ����һ�� RTC ʵ�� */

am_rtc_handle_t am_ds1302_rtc_inst_init(void)
{
    am_ds1302_handle_t ds1302_handle = am_ds1302_inst_init();

    return am_ds1302_rtc_init(ds1302_handle, &__g_ds1302_rtc);
}

/*******************************************************************************
    DS1302 ʵ����ʼ�� ����DS1302����ϵͳʱ�䣩
*******************************************************************************/

#define __UPDATE_SYSCLK_NS   1000000 /**< \brief ÿ1ms(1000000ns)����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S       10      /**< \brief ÿ10s����RTC����һ��ϵͳʱ��ֵ */

int am_ds1302_time_inst_init(void)
{
    am_rtc_handle_t rtc_handle = am_ds1302_rtc_inst_init();

    return am_time_init(rtc_handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
