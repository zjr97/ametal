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
 * \brief RX8025T �����ļ�
 * \sa am_hwconf_rx8025t.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "lpc82x_pin.h"
#include "am_rx8025t.h"
#include "am_time.h"
#include "am_alarm_clk.h"

/**
 * \addtogroup am_if_src_hwconf_rx8025t
 * \copydoc am_hwconf_rx8025t.c
 * @{
 */

/*******************************************************************************
    RX8025T ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

static am_rx8025t_dev_t    __g_rx8025t_dev; /* ����һ��rx8025tʵ�� */

static const am_rx8025t_devinfo_t  __g_rx8025t_devinfo = {  /* RX8025Tʵ����Ϣ */
    PIO0_1,                                                 /* INT��Ӧ��IO���ź� */
    PIO0_10,                                                /* CLK_EN��Ӧ��IO���ź� */
};

am_rx8025t_handle_t am_rx8025t_inst_init (void)
{
    am_i2c_handle_t i2c_handle = am_lpc82x_i2c1_inst_init(); /* ��ȡI2C1ʵ����� */
    static am_rx8025t_handle_t rx8025t_handle = NULL;

    if (rx8025t_handle == NULL) {
        rx8025t_handle = am_rx8025t_init(&__g_rx8025t_dev,
                                         &__g_rx8025t_devinfo,
                                          i2c_handle);
    }

    return rx8025t_handle;
}

/*******************************************************************************
    RX8025T ʵ����ʼ�� ��ʹ��ͨ�õ�RTC���ܣ�
*******************************************************************************/

static am_rtc_serv_t      __g_rx8025t_rtc; /* ����һ�� RTC ʵ�� */

am_rtc_handle_t am_rx8025t_rtc_inst_init(void)
{
    am_rx8025t_handle_t rx8025t_handle = am_rx8025t_inst_init();

    return am_rx8025t_rtc_init(rx8025t_handle, &__g_rx8025t_rtc);
}

/*******************************************************************************
    RX8025T ʵ����ʼ�� ��ʹ��ͨ�õ����ӹ��ܣ�
*******************************************************************************/

static am_alarm_clk_serv_t  __g_rx8025t_alarm_clk; /* ����һ������ʵ�� */

am_alarm_clk_handle_t  am_rx8025t_alarm_clk_inst_init(void)
{
    am_rx8025t_handle_t  rx8025t_handle = am_rx8025t_inst_init();
    return am_rx8025t_alarm_clk_init (rx8025t_handle, &__g_rx8025t_alarm_clk);
}

/*******************************************************************************
    RX8025T ʵ����ʼ�� ����RX8025T����ϵͳʱ�䣩
*******************************************************************************/

#define __UPDATE_SYSCLK_NS   1000000 /**< \brief ÿ1ms(1000000ns)����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S       10      /**< \brief ÿ10s����RTC����һ��ϵͳʱ��ֵ */

int am_rx8025t_time_inst_init(void)
{
    am_rtc_handle_t rtc_handle = am_rx8025t_rtc_inst_init();

    return am_time_init(rtc_handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
