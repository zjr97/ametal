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
 * \brief MicroPort RTC(PCF85063) �����ļ�
 * \sa am_hwconf_microport_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_time.h"
#include "am_pcf85063.h"
#include "am_alarm_clk.h"
#include "am_kl26_inst_init.h"

#include "../../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \addtogroup am_if_src_hwconf_microport_rtc
 * \copydoc am_hwconf_microport_rtc.c
 * @{
 */

/** \brief �豸��Ϣ */
am_local am_const am_pcf85063_devinfo_t __g_microport_rtc_devinfo = {
    PIOA_12,   /**< \brief INT ��Ӧ�� IO ���ź� */
    -1,        /**< \brief CLK_EN δʹ�� */
};

/*******************************************************************************
  MicroPort PCF85063 ʵ����ʼ����ʹ��оƬ���⹦�ܣ�
*******************************************************************************/

/** \brief �豸���� */
am_local am_pcf85063_dev_t __g_microport_rtc_dev;

/** \brief ʵ����ʼ�� */
am_pcf85063_handle_t am_microport_rtc_inst_init (void)
{
    am_i2c_handle_t             i2c_handle           = am_kl26_i2c0_inst_init();
    am_local am_pcf85063_handle_t microport_rtc_handle = NULL;

    if (microport_rtc_handle == NULL) {
        microport_rtc_handle = am_pcf85063_init(&__g_microport_rtc_dev,
                                                &__g_microport_rtc_devinfo,
                                                 i2c_handle);
    }

    return microport_rtc_handle;
}

/*******************************************************************************
  MicroPort PCF85063 ʵ����ʼ�� ��ʹ��ͨ�õ� RTC ���ܣ�
*******************************************************************************/

/** \brief �豸���� */
am_local am_rtc_serv_t __g_microport_rtc_rtc;

/** \brief ʵ����ʼ�� */
am_rtc_handle_t am_microport_rtc_rtc_inst_init (void)
{
    am_pcf85063_handle_t microport_rtc_handle = am_microport_rtc_inst_init();

    return am_pcf85063_rtc_init(microport_rtc_handle, &__g_microport_rtc_rtc);
}

/*******************************************************************************
  MicroPort PCF85063 ʵ����ʼ�� ��ʹ��ͨ�õ����ӹ��ܣ�
*******************************************************************************/

/** \brief �豸���� */
am_local am_alarm_clk_serv_t __g_microport_rtc_alarm_clk;

/** \brief ʵ����ʼ�� */
am_alarm_clk_handle_t am_microport_rtc_alarm_clk_inst_init (void)
{
    am_pcf85063_handle_t microport_rtc_handle = am_microport_rtc_inst_init();
    return am_pcf85063_alarm_clk_init(microport_rtc_handle,
                                     &__g_microport_rtc_alarm_clk);
}

/*******************************************************************************
  MicroPort PCF85063 ʵ����ʼ�� ���� PCF85063 ����ϵͳʱ�䣩
*******************************************************************************/

/** \brief ÿ 1ms(1000000ns) ����ϵͳʱ�Ӹ���һ��ϵͳʱ��ֵ */
#define __UPDATE_SYSCLK_NS   1000000

/** \brief ÿ 10s ���� RTC ����һ��ϵͳʱ��ֵ */
#define __UPDATE_RTC_S       10

/** \brief ʵ����ʼ�� */
int am_microport_rtc_time_inst_init (void)
{
    am_rtc_handle_t rtc_handle = am_microport_rtc_rtc_inst_init();

    return am_time_init(rtc_handle,
                        __UPDATE_SYSCLK_NS,
                        __UPDATE_RTC_S);
}

/**
 * @}
 */

/* end of file */
