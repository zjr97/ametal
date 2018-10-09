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
 * \brief PCF85063 �����ļ�
 * \sa am_hwconf_pcf85063.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "lpc82x_pin.h"
#include "am_pcf85063.h"
#include "am_time.h"
#include "am_alarm_clk.h"

/**
 * \addtogroup am_if_src_hwconf_pcf85063
 * \copydoc am_hwconf_pcf85063.c
 * @{
 */

/*******************************************************************************
    PCF85063 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

static am_pcf85063_dev_t    __g_pcf85063_dev; /* ����һ��pcf85063ʵ�� */

static const am_pcf85063_devinfo_t __g_pcf85063_devinfo = { /* ����ʵ����Ϣ */
    PIO0_1,                                                 /* INT��Ӧ��IO���ź� */
    -1,                                                     /* CLK_ENδʹ�� */
};

am_pcf85063_handle_t am_pcf85063_inst_init (void)
{
    am_i2c_handle_t             i2c_handle      = am_lpc82x_i2c1_inst_init();
    static am_pcf85063_handle_t pcf85063_handle = NULL;

    if (pcf85063_handle == NULL) {
        pcf85063_handle = am_pcf85063_init(&__g_pcf85063_dev,
                                           &__g_pcf85063_devinfo,
                                            i2c_handle);
    }

    return pcf85063_handle;
}

/*******************************************************************************
    PCF85063 ʵ����ʼ�� ��ʹ��ͨ�õ�RTC���ܣ�
*******************************************************************************/

static am_rtc_serv_t      __g_pcf85063_rtc;                 /* ����һ�� RTC ʵ�� */

am_rtc_handle_t am_pcf85063_rtc_inst_init(void)
{
    am_pcf85063_handle_t pcf85063_handle = am_pcf85063_inst_init();

    return am_pcf85063_rtc_init(pcf85063_handle, &__g_pcf85063_rtc);
}

/*******************************************************************************
    PCF85063 ʵ����ʼ�� ��ʹ��ͨ�õ����ӹ��ܣ�
*******************************************************************************/

static am_alarm_clk_serv_t  __g_pcf85063_alarm_clk;         /* ����һ������ʵ�� */

am_alarm_clk_handle_t  am_pcf85063_alarm_clk_inst_init(void)
{
    am_pcf85063_handle_t  pcf85063_handle = am_pcf85063_inst_init();
    return am_pcf85063_alarm_clk_init (pcf85063_handle, &__g_pcf85063_alarm_clk);
}

/*******************************************************************************
    PCF85063 ʵ����ʼ�� ����PCF85063����ϵͳʱ�䣩
*******************************************************************************/

#define __UPDATE_SYSCLK_NS   1000000 /**< \brief ÿ1ms(1000000ns)����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S       10      /**< \brief ÿ10s����RTC����һ��ϵͳʱ��ֵ */

int am_pcf85063_time_inst_init(void)
{
    am_rtc_handle_t rtc_handle = am_pcf85063_rtc_inst_init();

    return am_time_init(rtc_handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
