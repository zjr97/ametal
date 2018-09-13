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
 * \brief RX8025SA�����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-07  vir, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_rx8025sa.h"
#include "am_gpio.h"
/*****************************************************************************
 * �궨��
 ****************************************************************************/
 
 /** \brief RX8025SA�豸��ַ  (��λ)*/
#define __RX8025SA_ADDR               0x32

#define __RX8025SA_12H_FORMAT  0   /** \brief 12Сʱ�� */
#define __RX8025SA_24H_FORMAT  1   /** \brief 24Сʱ�� */
/**
 * \name RX8025SA �Ĵ�����ַ + ����ģʽ �� Ĭ��Ϊ0��
 *
 * \note ����λΪ���Ĵ�����ַ
 *       ����λΪ������ģʽ        0h ��׼��readģʽ
 *                      4h ����˳��readģʽ �����Ƽ���
 */
 
#define __RX8025SA_REG_SECONDS          0x00    /**< \brief ��Ĵ�����ַ + ��׼ģʽ */
#define __RX8025SA_REG_MINUTES          0x10    /**< \brief �ּĴ�����ַ + ��׼ģʽ */
#define __RX8025SA_REG_HOURS            0x20    /**< \brief ʱ�Ĵ�����ַ + ��׼ģʽ */
#define __RX8025SA_REG_WEEKDAYS         0x30    /**< \brief ���ڼĴ�����ַ + ��׼ģʽ */
#define __RX8025SA_REG_DAYS             0x40    /**< \brief �ռĴ�����ַ + ��׼ģʽ */
#define __RX8025SA_REG_MONTHS           0x50    /**< \brief �¼Ĵ�����ַ + ��׼ģʽ */
#define __RX8025SA_REG_YEAERS           0x60    /**< \brief ��Ĵ�����ַ + ��׼ģʽ */

#define __RX8025SA_REG_DIGITAL_OFFSET   0x70    /**< \brief ʱ��ƫ�ƼĴ�����ַ + ��׼ģʽ */

#define __RX8025SA_REG_MINUTES_ALARM_W  0x80    /**< \brief ����W���ӼĴ�����ַ + ��׼ģʽ */
#define __RX8025SA_REG_HOURS_ALARM_W    0x90    /**< \brief ����WСʱ�Ĵ�����ַ  + ��׼ģʽ*/
#define __RX8025SA_REG_WEEKDAYS_ALARM_W 0xa0    /**< \brief ����W���ڼĴ�����ַ + ��׼ģʽ*/

#define __RX8025SA_REG_MINUTES_ALARM_D  0xb0    /**< \brief ����D���ӼĴ�����ַ + ��׼ģʽ */
#define __RX8025SA_REG_HOURS_ALARM_D    0xc0    /**< \brief ����DСʱ�Ĵ�����ַ  + ��׼ģʽ*/
 /* 0x0d is reserved */
#define __RX8025SA_REG_CONTROL1         0xe0    /**< \brief ����״̬�Ĵ���1��ַ + ��׼ģʽ */
#define __RX8025SA_REG_CONTROL2         0xf0    /**< \brief ����״̬�Ĵ���2��ַ + ��׼ģʽ */

/**
 * \name RX8025SA �Ĵ���λ������
 * \anchor grp_rx8025sa_bitfield_descriptions
 * @{
 */


#define __RX8025SA_C1_ALARM_W_EN   0x80   /**< \brief ʹ��ALARM_W���� */
#define __RX8025SA_C1_ALARM_D_EN   0x40   /**< \brief ʹ��ALARM_D���� */

#define __RX8025SA_C2_DAFG_ALARM_D        (uint8_t)(1<<0)    /**< \brief DAFGλ*/
#define __RX8025SA_C2_WAFG_ALARM_W        (uint8_t)(1<<1)    /**< \brief WAFGλ*/
#define __RX8025SA_C2_CTFG_INT            (uint8_t)(1<<2)    /**< \brief CTFGλ*/

#define __RX8025SA_C1_24H_FORMAT   0x20  /**< \brief 24Сʱ�� */

#define __RX8025SA_C2_VDSL_1_3_SET   0x80  /**< \brief �͵�ѹ��⹦�ܵı�׼��ѹֵ�趨Ϊ1.3v*/



/**
 * \name RX8025SA I2C��ǰ״̬
 * \anchor grp_rx8025sa_i2c_operation
 * @{
 */

#define __RX8025SA_I2C_RD_STATUS        0x00    /**< \brief ��ȡ״̬ */
#define __RX8025SA_I2C_WR_STATUS        0x01    /**< \brief ���״̬ */
#define __RX8025SA_I2C_DATA_PROCESSING  0x02    /**< \brief ���ݴ���׶� */

/* RTC driver function implementation */
static int __rx8025sa_time_set (void *p_drv, am_tm_t *p_tm);
static int __rx8025sa_time_get (void *p_drv, am_tm_t *p_tm);

/**
 * \brief RTC driver functions definition
 */
static struct am_rtc_drv_funcs __g_rtc_drv_funcs = {
    __rx8025sa_time_set,
    __rx8025sa_time_get,
};

/* �������� */
static void __rx8025sa_intb_isr (void *p_arg);

/* ALARM_CLK driver function implementation */
static int __rx8025sa_alarm_clk_time_set (void *p_drv, am_alarm_clk_tm_t *p_tm);
static int __rx8025sa_alarm_clk_callback_set (void          *p_drv,
                                              am_pfnvoid_t   pfn_alarm_callback,
                                              void          *p_arg);
static int __rx8025sa_alarm_clk_on (void *p_drv);
static int __rx8025sa_alarm_clk_off (void *p_drv);

/**
 * \brief ALARM_CLK driver functions definition
 */
static struct am_alarm_clk_drv_funcs __g_alarm_clk_drv_funcs = {
    __rx8025sa_alarm_clk_time_set,
    __rx8025sa_alarm_clk_callback_set,
    __rx8025sa_alarm_clk_on,
    __rx8025sa_alarm_clk_off,
};
/**
 * \brief �����ƽ��ÿ���¶�Ӧ������
 */
static const uint8_t __mdays[2][12] = {
    /* ƽ�� */
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    /* ���� */
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/**
 * \brief �ж�����Ƿ�Ϊ����
 *
 * \param[in] year : ���
 *
 * \retval 1 : ����
 * \retval 0 : ƽ��
 */
static uint8_t __rx8025sa_leap_year_check (uint16_t year)
{
    return (((!(year % 4) && (year % 100)) || !(year % 400)) ? 1 : 0);
}

/**
 * \brief ��������һ���еĵڼ���
 *
 * \param[in] year  : ���
 * \param[in] month : �·�
 * \param[in] day   : ��
 *
 * \retval 1 : ����
 * \retval 0 : ƽ��
 */
static uint8_t __rx8025sa_day_of_year (uint16_t year, uint8_t month, uint8_t day)
{
    uint8_t i;

    if (__rx8025sa_leap_year_check(year)) {
        for (i = 0; i < month; i++) {
            day += __mdays[1][i];
        }
    } else {
        for (i = 0; i < month; i++) {
            day += __mdays[0][i];
        }
    }

    return (day);
}
/**
 * \brief ����ʱ����Ϣ����Ч��
 *
 * \param[in] p_tm : ָ��ʱ��ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
int __rx8025sa_time_validator (am_tm_t *p_tm)
{
    if (p_tm->tm_year > 199 || p_tm->tm_year < 0 ||
        p_tm->tm_mon > 11   || p_tm->tm_mon < 0 ||
        p_tm->tm_mday >
        __mdays[__rx8025sa_leap_year_check(1900 + p_tm->tm_year)][p_tm->tm_mon] ||
        p_tm->tm_mday < 0 ||
        p_tm->tm_wday > 6 || p_tm->tm_wday < 0 ||
        p_tm->tm_hour > 23 || p_tm->tm_hour < 0 ||
        p_tm->tm_min > 59 || p_tm->tm_min < 0 ||
        p_tm->tm_sec > 59 || p_tm->tm_sec < 0 ) {
        return -AM_EINVAL;
    } else {
        return AM_OK;
    }
}
/**
 * \brief RTC��׼��������-ʱ��������������
 *
 * \param[in] p_drv : ָ���豸�ṹ���ָ��
 * \param[in] p_tm  : ָ��ʱ��ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
static int __rx8025sa_time_set (void *p_drv, am_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    uint8_t temp;

    /* ���ݻ����� */
    uint8_t buf[7] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ��֤ʱ����Ϣ����Ч�� */
    if ((AM_OK != __rx8025sa_time_validator(p_tm)) ||
        (p_tm->tm_hour > 23) || (p_tm->tm_hour < 0)) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_rx8025sa_dev_t *)p_drv)->i2c_dev);

    /* ��ʱ��������Ϣ����buf�� */
    buf[__RX8025SA_REG_SECONDS >> 4 ] = AM_HEX_TO_BCD(p_tm->tm_sec);
    buf[__RX8025SA_REG_MINUTES >> 4 ] = AM_HEX_TO_BCD(p_tm->tm_min);

    if (((am_rx8025sa_dev_t *)p_drv)->time_format == __RX8025SA_24H_FORMAT){
        buf[__RX8025SA_REG_HOURS >> 4] = AM_HEX_TO_BCD(p_tm->tm_hour);         /* 24Сʱ�Ƶ�Сʱ */
    } else {
        temp = AM_HEX_TO_BCD((p_tm->tm_hour % 12));
        if (temp == 0) {
            temp = 12;
        }
        buf[__RX8025SA_REG_HOURS >> 4] = temp | ((p_tm->tm_hour / 12) << 5);   /* 12Сʱ�Ƶ�Сʱ */
    }

    buf[__RX8025SA_REG_WEEKDAYS >> 4] = AM_HEX_TO_BCD(p_tm-> tm_wday);
    buf[__RX8025SA_REG_DAYS >> 4]     = AM_HEX_TO_BCD(p_tm->tm_mday);
    buf[__RX8025SA_REG_MONTHS >> 4]   = AM_HEX_TO_BCD(p_tm->tm_mon + 1);
    buf[__RX8025SA_REG_YEAERS >> 4]   = AM_HEX_TO_BCD(p_tm->tm_year);

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_SECONDS,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }

    return AM_OK;

}

/**
 * \brief RTC��׼��������-ʱ���ȡ��������
 *
 * \param[in] p_drv : ָ���豸�ṹ���ָ��
 * \param[in] p_tm  : ָ��ʱ��ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
static int __rx8025sa_time_get (void *p_drv, am_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    uint8_t  temp;

    /* ���ݻ����� */
    uint8_t buf[7] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_rx8025sa_dev_t *)p_drv)->i2c_dev);

    /* ͨ��I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_SECONDS,
                      buf,
                      sizeof(buf));

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }

    /** ��buf�л�ȡʱ��������Ϣ */
    p_tm->tm_sec  = AM_BCD_TO_HEX(buf[__RX8025SA_REG_SECONDS >> 4] & 0x7F);
    p_tm->tm_min  = AM_BCD_TO_HEX(buf[__RX8025SA_REG_MINUTES >> 4] & 0x7F);

    if (((am_rx8025sa_dev_t *)p_drv)->time_format == __RX8025SA_24H_FORMAT){
        p_tm->tm_hour = AM_BCD_TO_HEX(buf[__RX8025SA_REG_HOURS >> 4] & 0x3F);        /* 24Сʱ�Ƶ�Сʱ */
    } else {
        temp = AM_BCD_TO_HEX(buf[__RX8025SA_REG_HOURS >> 4]& 0x1F);
        if (temp == 12) {
            temp =0;
        }
        p_tm->tm_hour = temp + ((buf[__RX8025SA_REG_HOURS >> 4] >> 5) & 0x01) * 12;  /* 12Сʱ�Ƶ�Сʱ */
    }

    p_tm->tm_wday = AM_BCD_TO_HEX(buf[__RX8025SA_REG_WEEKDAYS >> 4] & 0x07);
    p_tm->tm_mday = AM_BCD_TO_HEX(buf[__RX8025SA_REG_DAYS >> 4] & 0x3F );
    p_tm->tm_mon  = AM_BCD_TO_HEX(buf[__RX8025SA_REG_MONTHS >> 4] & 0x1F) - 1;
    p_tm->tm_year = AM_BCD_TO_HEX(buf[__RX8025SA_REG_YEAERS >> 4]);
    p_tm->tm_yday = __rx8025sa_day_of_year(p_tm->tm_year, p_tm->tm_mon, p_tm->tm_mday);
    return AM_OK;

}

/**
 * \brief ALARM_CLK ��׼��������-����ʱ�����ú���
 *
 * \param[in] p_drv : ָ���豸�ṹ���ָ��
 * \param[in] p_tm  : ָ������ʱ��ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
static int __rx8025sa_alarm_clk_time_set (void *p_drv, am_alarm_clk_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[3] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ��֤ʱ����Ϣ����Ч�� */
    if ((p_tm->min  > 59) || (p_tm->min  < 0) ||
        (p_tm->hour > 23) || (p_tm->hour < 0)) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_rx8025sa_dev_t *)p_drv)->i2c_dev);

    /* ��ʱ��������Ϣ����buf�� */
    buf[0] = AM_HEX_TO_BCD(p_tm->min);
    buf[1] = AM_HEX_TO_BCD(p_tm->hour);
    /* ������������ת��BCD�� */
    buf[2] = p_tm->wdays;

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_MINUTES_ALARM_W,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }

    return AM_OK;
}

/**
 * \brief ALARM_CLK ��׼��������-���ӻص����������ú���
 *
 * \param[in] p_drv         : ָ���豸�ṹ���ָ��
 * \param[in] pfn_callback  : ָ��ص�������ָ��
 * \param[in] p_arg         : ָ��ص�����������ָ��
 *
 * \retval AM_OK  : ���óɹ�
 * \retval ����             : �鿴������
 */
static int __rx8025sa_alarm_clk_callback_set (void         *p_drv,
                                              am_pfnvoid_t  pfn_alarm_callback,
                                              void          *p_arg)
{
	/* �������÷���ֵ */
    int ret = AM_OK;

    /* RX8025SA �豸ָ�� */
    am_rx8025sa_handle_t  rx8025sa_handle = NULL;

    /* �豸��Ϣָ�� */
   const am_rx8025sa_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    rx8025sa_handle =  (am_rx8025sa_handle_t)p_drv;
    p_devinfo      = rx8025sa_handle->p_devinfo;

    /* ���������жϻص����� */
    ret = am_gpio_trigger_connect(p_devinfo->intb_pin,
                                  __rx8025sa_intb_isr,
                                  rx8025sa_handle);
    if (AM_OK != ret) {
        return ret;
    }

    /* ����Ϊ�½��ش��� */
    am_gpio_trigger_cfg(p_devinfo->intb_pin, AM_GPIO_TRIGGER_FALL);
    am_gpio_trigger_on(p_devinfo->intb_pin);

    /* �����жϻص����� */
    rx8025sa_handle->triginfo[2].pfn_callback = pfn_alarm_callback;
    rx8025sa_handle->triginfo[2].p_arg        = p_arg;

    /* ������еĻص�������Ϊ�� */
    if (rx8025sa_handle->triginfo[2].pfn_callback == NULL) {

        /* ɾ�������жϻص����� */
        ret = am_gpio_trigger_disconnect(p_devinfo->intb_pin,
                                         __rx8025sa_intb_isr,
                                         rx8025sa_handle);

        if (AM_OK != ret) {
            return ret;
        }

        /* �ر����Ŵ��� */
        am_gpio_trigger_off(p_devinfo->intb_pin);
    }

    return AM_OK;
}

/**
 * \brief ALARM_CLK ��׼��������-�������Ӻ���
 *
 * \param[in] p_drv : ָ���豸�ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
static int __rx8025sa_alarm_clk_on (void *p_drv)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]  = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    /* ��p_drv�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_rx8025sa_dev_t *)p_drv)->i2c_dev);

    /* ��ȡ���ƼĴ���1 */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ʹ�� */
    buf[0] |= __RX8025SA_C1_ALARM_W_EN;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}

/**
 * \brief ALARM_CLK ��׼��������-�ر����Ӻ���
 *
 * \param[in] p_drv : ָ���豸�ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
static int __rx8025sa_alarm_clk_off (void *p_drv)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]  = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    /* ��p_drv�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_rx8025sa_dev_t *)p_drv)->i2c_dev);

    /* ��ȡ���ƼĴ��� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �ر������ж� */
    buf[0] &= ~__RX8025SA_C1_ALARM_W_EN;

    /* �������ж���Ϣд�����״̬�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}

/**
 * \brief �����жϱ�־��ִ���û��жϻص�����
 *
 * \param[in] p_dev     : ָ��RX8025SA�豸��ָ��
 * \param[in] intr_flag : �жϱ�־
 *
 * \return ��
 */
static void __rx8025sa_callback_exec (void    *p_drv,
                                      uint8_t  intr_flag)
{
    am_rx8025sa_dev_t *p_dev        = NULL;
    am_pfnvoid_t       pfn_callback = NULL;
    void              *p_arg        = NULL;

    /* ���������Ч�� */
    if (0 == intr_flag || NULL == p_drv) {
        return;
    }

    p_dev = (am_rx8025sa_dev_t *)p_drv;

    /* ����������жϣ���ִ�ж�Ӧ�û��жϻص����� */
    if (intr_flag & __RX8025SA_C2_CTFG_INT) {
        pfn_callback = p_dev->triginfo[0].pfn_callback;
        p_arg        = p_dev->triginfo[0].p_arg;
        if (NULL != pfn_callback) {
            pfn_callback(p_arg);
        }
    }

    /* �����ALARM_D�жϣ���ִ�ж�Ӧ�û��жϻص����� */
    if (intr_flag & __RX8025SA_C2_DAFG_ALARM_D) {
        pfn_callback = p_dev->triginfo[1].pfn_callback;
        p_arg        = p_dev->triginfo[1].p_arg;
        if (NULL != pfn_callback) {
            pfn_callback(p_arg);
        }
    }

    /* �����ALARM_W�жϣ���ִ�ж�Ӧ�û��жϻص����� */
    if (intr_flag & __RX8025SA_C2_WAFG_ALARM_W) {
        pfn_callback = p_dev->triginfo[2].pfn_callback;
        p_arg        = p_dev->triginfo[2].p_arg;
        if (NULL != pfn_callback) {
            pfn_callback(p_arg);
        }
    }
}
/**
 * \brief rx8025sa�豸��ʼ��
 * \param[in] p_dev : ָ��rx8025sa�豸�ṹ��
 * \return AM_OK��ʾ��ʼ���ɹ�, ����ʧ��
 */
static int __rx8025sa_init (am_rx8025sa_dev_t *p_dev)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(p_dev->i2c_dev);

    /* ����״̬�Ĵ���2ʱ���������,����жϱ�־ */
    buf[0] = 0;

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
    		           __RX8025SA_REG_CONTROL1,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ���ж��ж�ȡ���ݺ�Ĵ�����,�ж��ж�����
 *
 * \param[in,out] buf         : ���ݻ�����
 * \param[in]     p_intr_flag : �жϱ�־  �μ� \ref grp_rx8025sa_intr_flag
 *
 * \return ��
 *
 * \note ������buf ��Ӧ CONTROL2�Ĵ���
 */
static void __rx8025sa_read_write_data_processing (void    *p_arg,
                                                   uint8_t *p_intr_flag)
{
    am_rx8025sa_dev_t *p_dev = NULL;

    if (NULL == p_arg) {
        return;
    }

    p_dev = (am_rx8025sa_dev_t *)p_arg;

    *p_intr_flag = 0;

    /* �ж��Ƿ�ΪDAFG��־��λ */
    if (p_dev->buf[0] & __RX8025SA_C2_DAFG_ALARM_D) {

        /* ��¼ALARM_D�жϱ�־ */
        *p_intr_flag |= __RX8025SA_C2_DAFG_ALARM_D;

        /* ���DAFG��־ */
        p_dev->buf[0] &= ~__RX8025SA_C2_DAFG_ALARM_D;
    }

    /* �ж��Ƿ�ΪCTFG��־��λ */
    if (p_dev->buf[0] & __RX8025SA_C2_CTFG_INT) {
          /* ��¼�����жϱ�־,�����*/
        *p_intr_flag |= __RX8025SA_C2_CTFG_INT;

          /* ���CTFG��־ */
        p_dev->buf[0] &= ~__RX8025SA_C2_CTFG_INT;
        }

    /* �ж��Ƿ�ΪWAFG��־��λ */
    if (p_dev->buf[0] & __RX8025SA_C2_WAFG_ALARM_W) {
        /* ��¼�����жϱ�־,����� */
        *p_intr_flag |= __RX8025SA_C2_WAFG_ALARM_W;

          /* ���WAFG��־ */
        p_dev->buf[0] &= ~__RX8025SA_C2_WAFG_ALARM_W;
        }
}
/**
 * \brief I2C��д�����е�״̬��
 * \param[in] p_arg : ����
 * \return ��
 * \note ״̬�任˳��   [1]����ʼ --> [2]дsubaddr,��ȡ״̬ --> [3]��������
 *                   --> [5]дsubaddr --> [6]д������ --> [7]�������
 */
static void __rx8025sa_i2c_read_write_fsm (void *p_arg)
{
    /* I2C�豸 */
    am_i2c_device_t *p_dev_i2c = NULL;

    /* rx8025sa�豸 */
    am_rx8025sa_dev_t *p_dev_rx8025sa = NULL;

    /* �жϲ�������Ч�� */
    if (NULL == p_arg) {
        return;
    }

    /* ��ȡi2c_status */
    p_dev_rx8025sa = (am_rx8025sa_dev_t *)p_arg;

    /*��ȡi2c_device */
    p_dev_i2c = &(p_dev_rx8025sa->i2c_dev);

    switch (p_dev_rx8025sa->status) {

    /* ��ȡ״̬ */
    case __RX8025SA_I2C_RD_STATUS:

        /* ������һ״̬ */
        p_dev_rx8025sa->status = __RX8025SA_I2C_WR_STATUS;

        am_i2c_mktrans(&p_dev_rx8025sa->trans[0],
                       p_dev_i2c->dev_addr,
                       (p_dev_i2c->dev_flags | AM_I2C_M_WR),
                       (uint8_t *)&p_dev_rx8025sa->sub_addr,
                       1);

        am_i2c_mktrans(&p_dev_rx8025sa->trans[1],
                       p_dev_i2c->dev_addr,
                       (p_dev_i2c->dev_flags | AM_I2C_M_RD),
                       (uint8_t *)p_dev_rx8025sa->buf,
                       p_dev_rx8025sa->nbytes);

        am_i2c_mkmsg(&p_dev_rx8025sa->msg,
                     p_dev_rx8025sa->trans,
                     2,
                     (am_pfnvoid_t)__rx8025sa_i2c_read_write_fsm,
                     p_arg);

        am_i2c_msg_start(p_dev_i2c->handle, &p_dev_rx8025sa->msg);
        break;

    /* ���״̬ */
    case __RX8025SA_I2C_WR_STATUS:

        /* ������һ״̬ */
        p_dev_rx8025sa->status = __RX8025SA_I2C_DATA_PROCESSING;

        /* �������ݣ���ȡ�ж�״̬ */
        __rx8025sa_read_write_data_processing(p_arg, &p_dev_rx8025sa->intr_flag);

        am_i2c_mktrans(&p_dev_rx8025sa->trans[0],
                       p_dev_i2c->dev_addr,
                       (p_dev_i2c->dev_flags | AM_I2C_M_WR),
                       (uint8_t *)&p_dev_rx8025sa->sub_addr,
                       1);

        am_i2c_mktrans(&p_dev_rx8025sa->trans[1],
                       p_dev_i2c->dev_addr,
                       (p_dev_i2c->dev_flags | AM_I2C_M_NOSTART | AM_I2C_M_WR),
                       (uint8_t *)p_dev_rx8025sa->buf,
                       p_dev_rx8025sa->nbytes);

        am_i2c_mkmsg(&p_dev_rx8025sa->msg,
                     p_dev_rx8025sa->trans,
                     2,
                     (am_pfnvoid_t)__rx8025sa_i2c_read_write_fsm,
                     p_arg);

        am_i2c_msg_start(p_dev_i2c->handle, &p_dev_rx8025sa->msg);
        break;

    /* ���ݴ��� */
    case __RX8025SA_I2C_DATA_PROCESSING:

        /* ������һ״̬ */
        p_dev_rx8025sa->status = __RX8025SA_I2C_RD_STATUS;

        /* ִ���û��ж��жϻص����� */
        __rx8025sa_callback_exec(p_arg, p_dev_rx8025sa->intr_flag);

        /* ����GPIO�ж� */
        if ( (p_dev_rx8025sa->intr_flag & __RX8025SA_C2_DAFG_ALARM_D ) ||
             (p_dev_rx8025sa->intr_flag & __RX8025SA_C2_CTFG_INT )){
             am_gpio_trigger_on(p_dev_rx8025sa->p_devinfo->inta_pin);
        }
        if ( p_dev_rx8025sa->intr_flag & __RX8025SA_C2_WAFG_ALARM_W) {
             am_gpio_trigger_on(p_dev_rx8025sa->p_devinfo->intb_pin);
        }

        break;

    default:
        break;
    }
}

/**
 * \brief RX8025SA ����INTA�жϻص�����
 * \param[in] p_arg : �жϻص���������
 * \return ��
 */
static void __rx8025sa_inta_isr (void *p_arg)
{
    am_rx8025sa_dev_t        *p_dev        = (am_rx8025sa_dev_t *)p_arg;

    if (NULL == p_arg) {
        return;
    }

    /* �ر�GPIO�ж� */
    am_gpio_trigger_off(p_dev->p_devinfo->inta_pin);

    if (p_dev->status == __RX8025SA_I2C_RD_STATUS) {

        /* ������д״̬�� */
        __rx8025sa_i2c_read_write_fsm(p_arg);
    }
}

/**
 * \brief RX8025SA ����INTB�жϻص�����
 * \param[in] p_arg : �жϻص���������
 * \return ��
 */
static void __rx8025sa_intb_isr (void *p_arg)
{
    am_rx8025sa_dev_t        *p_dev        = (am_rx8025sa_dev_t *)p_arg;

    if (NULL == p_arg) {
        return;
    }

    /* �ر�GPIO�ж� */
    am_gpio_trigger_off(p_dev->p_devinfo->intb_pin);

    if (p_dev->status == __RX8025SA_I2C_RD_STATUS) {

        /* ������д״̬�� */
        __rx8025sa_i2c_read_write_fsm(p_arg);
    }
}

/**
 * \brief RX8025SA ʱ���ʽ����
 */
static int __rx8025sa_time_format_set (am_rx8025sa_handle_t handle, uint8_t format)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]  = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    handle->time_format = format;
    /* ��ȡ���ƼĴ���1 */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    if ( format == __RX8025SA_24H_FORMAT ){
        buf[0] |= __RX8025SA_C1_24H_FORMAT;
    } else {
        buf[0] &= ~ __RX8025SA_C1_24H_FORMAT;
    }

    /* д�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;

}

/*****************************************************************************
 * �ⲿ����ʵ��
 ****************************************************************************/

/**
 * \brief RX8025SA �豸��ʼ��
 */
am_rx8025sa_handle_t am_rx8025sa_init (am_rx8025sa_dev_t           *p_dev,
                                       const am_rx8025sa_devinfo_t *p_devinfo,
                                       am_i2c_handle_t              i2c_handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;
    int i;

    /* ��֤������Ч�� */
    if (NULL == p_dev || NULL == i2c_handle) {
        return NULL;
    }

    /* ����i2c�豸 */
    am_i2c_mkdev(&(p_dev->i2c_dev),
                 i2c_handle,
                 __RX8025SA_ADDR,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    /* ��ʼ���豸��Ϣ */
    p_dev->conn_stat_inta = AM_FALSE;
    p_dev->p_devinfo      = p_devinfo;

    p_dev->time_format    = __RX8025SA_24H_FORMAT;        /* Ĭ��24Сʱ�Ƽ�ʱ */

    for (i = 0; i < 3; i++) {
        p_dev->triginfo[i].pfn_callback = NULL;
        p_dev->triginfo[i].p_arg        = NULL;
    }
    p_dev->status   = __RX8025SA_I2C_RD_STATUS;      /* ��ʼ״̬ */
    p_dev->sub_addr =__RX8025SA_REG_CONTROL2;        /* �������ļĴ�����ַ */
    p_dev->nbytes   = 1;                             /* ��Ҫ��ȡ�����ݸ��� */

    /* ��ʼ��RX8025SA�豸 */
    ret = __rx8025sa_init(p_dev);
    if (AM_OK != ret) {
        return NULL;
    }

    /* ��ʼ��ʱ���ʽ */
    ret = __rx8025sa_time_format_set( p_dev, p_dev->time_format);

    if (AM_OK != ret) {
        return NULL;
    }

    /* ��ʼ��clk_en_pin ��GPIO�� */
    if (p_dev->p_devinfo->clk_en_pin != -1) {
         am_gpio_pin_cfg(p_dev->p_devinfo->clk_en_pin, AM_GPIO_OUTPUT_INIT_LOW | AM_GPIO_PUSH_PULL);  /* ����Ϊ������� */
    }

    return p_dev;
}


/**
 * \brief RX8025SA �豸���ʼ��
 */
void am_rx8025sa_deinit (am_rx8025sa_handle_t handle)
{

}

/**
 * \brief ��ȡRX8025SA RTC��׼����
 */
am_rtc_handle_t am_rx8025sa_rtc_init (am_rx8025sa_handle_t  handle,
                                      am_rtc_serv_t        *p_rtc)
{
    p_rtc->p_drv   = handle;
    p_rtc->p_funcs = &__g_rtc_drv_funcs;
    return p_rtc;
}

/**
 * \brief ��ȡRX8025SA ALARM_CLK��׼����
 */
am_alarm_clk_handle_t am_rx8025sa_alarm_clk_init (am_rx8025sa_handle_t   handle,
		                                         am_alarm_clk_serv_t    *p_alarm_clk)
{
	p_alarm_clk->p_drv   = handle;
	p_alarm_clk->p_funcs = &__g_alarm_clk_drv_funcs;
    return p_alarm_clk;
}

/**
 * \brief ʹ��rx8025�� alarm_d ����
 */
int am_rx8025sa_alarm_d_enable (am_rx8025sa_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ���ƼĴ���1 */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ʹ�� */
    buf[0] |= __RX8025SA_C1_ALARM_D_EN;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}
/**
 * \brief ʹ��rx8025�� alarm_w ����
 */
int am_rx8025sa_alarm_w_enable (am_rx8025sa_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ���ƼĴ���1 */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����жϽ��� */
    buf[0] |= __RX8025SA_C1_ALARM_W_EN;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}



/**
 * \brief ���� RX8025SA �� ALARM_D ����
 */
int am_rx8025sa_alarm_d_disable (am_rx8025sa_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[2]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ���ƼĴ���1,2(�������������ж�) */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      2);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����жϽ��� */
    buf[0] &= ~__RX8025SA_C1_ALARM_D_EN;

    /* ���AF��־ */
    buf[1] &= ~__RX8025SA_C2_DAFG_ALARM_D;

    /* �������ж���Ϣд�����״̬�Ĵ���1,2 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       2);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ���� RX8025SA �� ALARM_W ����
 */
int am_rx8025sa_alarm_w_disable (am_rx8025sa_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[2]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ���ƼĴ���1,2(�������������ж�) */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      2);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����жϽ��� */
    buf[0] &= ~__RX8025SA_C1_ALARM_W_EN;

    /* ���AF��־ */
    buf[1] &= ~__RX8025SA_C2_WAFG_ALARM_W;

    /* �������ж���Ϣд�����״̬�Ĵ���1,2 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       2);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}



/**
 * \brief RX8025SA �����жϺ�������
 */
int am_rx8025sa_periodic_int_set (am_rx8025sa_handle_t  handle,
                                   uint8_t              int_mode,
                                  am_pfnvoid_t          pfn_periodic_int_callback,
                                  void                 *p_periodic_int_arg)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �豸��Ϣָ�� */
    const am_rx8025sa_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_devinfo = handle->p_devinfo;
    p_i2c_dev = &(handle->i2c_dev);

    /* conn_stat_inta���ڼ�¼��ǰ�ж�����״̬,�����ظ�����GPIO���Ӻ��� */
    if (!(handle->conn_stat_inta)) {

        /* ���������жϻص����� */
        ret = am_gpio_trigger_connect(p_devinfo->inta_pin,
                                      __rx8025sa_inta_isr,
                                      handle);
        if (AM_OK != ret) {
            return ret;
        }

        /* ����Ϊ�½��ش��� */
        am_gpio_trigger_cfg(p_devinfo->inta_pin, AM_GPIO_TRIGGER_FALL);
        am_gpio_trigger_on(p_devinfo->inta_pin);

        /* ����conn_stat״̬ΪTRUE */
        handle->conn_stat_inta = AM_TRUE;

    }

    /* �����жϻص����� */
    handle->triginfo[0].pfn_callback = pfn_periodic_int_callback;
    handle->triginfo[0].p_arg        = p_periodic_int_arg;

    /* ������еĻص�������Ϊ�� */
    if ((handle->triginfo[0].pfn_callback == NULL) &&
        (handle->triginfo[1].pfn_callback == NULL)) {

        /* ���conn_stat_intaΪTRUE�����GPIO������Ӻ��� */
        if (handle->conn_stat_inta) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->inta_pin,
                                             __rx8025sa_inta_isr,
                                             handle);

            if (AM_OK != ret) {
                return ret;
            }

            /* �ر����Ŵ��� */
            am_gpio_trigger_off(p_devinfo->inta_pin);

            /* ����conn_stat״̬ΪFALSE */
            handle->conn_stat_inta = AM_FALSE;
        }
    }

    /* ��ȡ���ƼĴ���1 */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }
    buf[0] |= int_mode;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}

/**
 * \brief RX8025SA ����D�ص�����������ʱ������
 */
int am_rx8025sa_alarm_d_set(am_rx8025sa_handle_t      handle,
                            am_rx8025sa_alarm_info_t *p_alarm_info,
                            am_pfnvoid_t              pfn_alarm_callback,
                            void                     *p_alarm_arg)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[2] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �豸��Ϣָ�� */
    const am_rx8025sa_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_devinfo = handle->p_devinfo;
    p_i2c_dev = &(handle->i2c_dev);

    /* conn_stat_inta���ڼ�¼��ǰ�ж�����״̬,�����ظ�����GPIO���Ӻ��� */
    if (!(handle->conn_stat_inta)) {

        /* ���������жϻص����� */
        ret = am_gpio_trigger_connect(p_devinfo->inta_pin,
                                      __rx8025sa_inta_isr,
                                       handle);
        if (AM_OK != ret) {
            return ret;
        }

        /* ����Ϊ�½��ش��� */
        am_gpio_trigger_cfg(p_devinfo->inta_pin, AM_GPIO_TRIGGER_FALL);
        am_gpio_trigger_on(p_devinfo->inta_pin);

        /* ����conn_stat_inta״̬ΪTRUE */
        handle->conn_stat_inta = AM_TRUE;

    }
    /* �����жϻص����� */
    handle->triginfo[1].pfn_callback = pfn_alarm_callback;
    handle->triginfo[1].p_arg        = p_alarm_arg;

    /* ������еĻص�������Ϊ�� */
    if ((handle->triginfo[0].pfn_callback == NULL) &&
        (handle->triginfo[1].pfn_callback == NULL)) {

        /* ���conn_statΪTRUE�����GPIO������Ӻ��� */
        if (handle->conn_stat_inta) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->inta_pin,
                                             __rx8025sa_inta_isr,
                                             handle);

            if (AM_OK != ret) {
                return ret;
            }

            /* �ر����Ŵ��� */
            am_gpio_trigger_off(p_devinfo->inta_pin);

            /* ����conn_stat״̬ΪFALSE */
            handle->conn_stat_inta = AM_FALSE;
        }
    }

    /* ��֤������Ϣ����ֵ����Ч�� */
    if (p_alarm_info->hour > 23 || p_alarm_info->hour < 0 ||
        p_alarm_info->min  > 59 || p_alarm_info->min < 0) {
        return -AM_EINVAL;
    }

    buf[0] = AM_HEX_TO_BCD(p_alarm_info->min);
    buf[1] = AM_HEX_TO_BCD(p_alarm_info->hour);
    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_MINUTES_ALARM_D,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }
    /* ʹ��ALARM_D����*/
    am_rx8025sa_alarm_d_enable(handle);

    return AM_OK;
}


/**
 * \brief RX8025SA ����W�ص�����������ʱ������
 */
int am_rx8025sa_alarm_w_set(am_rx8025sa_handle_t      handle,
                            am_rx8025sa_alarm_info_t *p_alarm_info,
                            am_pfnvoid_t              pfn_alarm_callback,
                            void                     *p_alarm_arg)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[3] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �豸��Ϣָ�� */
    const am_rx8025sa_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_devinfo = handle->p_devinfo;
    p_i2c_dev = &(handle->i2c_dev);

     /* ���������жϻص����� */
    ret = am_gpio_trigger_connect(p_devinfo->intb_pin,
                                  __rx8025sa_intb_isr,
                                  handle);
    if (AM_OK != ret) {
        return ret;
    }

    /* ����Ϊ�½��ش��� */
    am_gpio_trigger_cfg(p_devinfo->intb_pin, AM_GPIO_TRIGGER_LOW);
    am_gpio_trigger_on(p_devinfo->intb_pin);

    /* �����жϻص����� */
    handle->triginfo[2].pfn_callback = pfn_alarm_callback;
    handle->triginfo[2].p_arg        = p_alarm_arg;

    /* ������еĻص�������Ϊ�� */
    if ( handle->triginfo[2].pfn_callback == NULL) {

        /* ɾ�������жϻص����� */
        ret = am_gpio_trigger_disconnect(p_devinfo->intb_pin,
                                         __rx8025sa_intb_isr,
                                         handle);

        if (AM_OK != ret) {
            return ret;
        }

        /* �ر����Ŵ��� */
        am_gpio_trigger_off(p_devinfo->inta_pin);

         /* ����conn_stat״̬ΪFALSE */
        handle->conn_stat_inta = AM_FALSE;
    }

    /* ��֤������Ϣ����ֵ����Ч�� */
    if (p_alarm_info->alarm_week > 127  || p_alarm_info->alarm_week < 0 ||
        p_alarm_info->hour > 23 || p_alarm_info->hour < 0 ||
        p_alarm_info->min  > 59 || p_alarm_info->min < 0) {
        return -AM_EINVAL;
    }

    buf[0] = AM_HEX_TO_BCD(p_alarm_info->min);
    buf[1] = AM_HEX_TO_BCD(p_alarm_info->hour);
    buf[2] = p_alarm_info->alarm_week;
    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
    		           __RX8025SA_REG_MINUTES_ALARM_W,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }
    /* ʹ��ALARM_W����*/
    am_rx8025sa_alarm_w_enable(handle);

    return AM_OK;

}
/*
 * ��Դ��ѹ�𵴼��
 */
int am_rx8025sa_power_check(am_rx8025sa_handle_t  handle)
{
    /* �������÷���ֵ */
	int ret;

    /* ���ݻ����� */
    uint8_t buf;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ͨ��I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
    		          __RX8025SA_REG_CONTROL2,
                      &buf,
                      1);

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }
    buf = (buf>>4) & 0x07;

    return buf;
}

/**
 * �͵�ѹ��⹦�ܵı�׼��ѹֵ�趨
 */
int am_rx8025sa_check_voltage_set (am_rx8025sa_handle_t handle, uint8_t check_v_value)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ���ƼĴ���1 */
    ret = am_i2c_read(p_i2c_dev,
    		          __RX8025SA_REG_CONTROL2,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    if ( check_v_value == RX8025SA_CHECK_VOLTAGE_1_3V ){
        buf[0] |= __RX8025SA_C2_VDSL_1_3_SET;
    } else {
    	buf[0] &= ~ __RX8025SA_C2_VDSL_1_3_SET;
    }

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
    		           __RX8025SA_REG_CONTROL2,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;

}

/*
 * ��ʱƵ�ʽ��е�������
 */
int am_rx8025sa_clk_adjust ( am_rx8025sa_handle_t handle, float clk )
{
    /* �������÷���ֵ */
    int   ret = AM_OK;

    double  clk_off;
    int     temp;

    /* ���ݻ����� */
    uint8_t buf[1]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    clk_off = ( clk - 32768)/32768;
    if ( clk_off >= 0 ) {
        temp = (int)(clk_off / 0.00000305 +0.5);
        temp += 1;
    } else {
        temp = (int)(clk_off / 0.00000305 -0.5);
    	 temp +=128;
    }

    buf[0] = temp;

    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_DIGITAL_OFFSET,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}
/**
 * ����Ƶ�����
 */
int am_rx8025sa_clkout_set(am_rx8025sa_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]  = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ���ƼĴ���1 */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025SA_REG_CONTROL1,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    buf[0] &= 0xEF;  /* �����ƼĴ���1��CLEN2Ϊ���� */

    /* д�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025SA_REG_CONTROL1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    /* �� FOE�����øߣ�ʹ��CLK��� */
    /* �� FOE�����øߣ�ʹ��CLK��� */
    if( handle->p_devinfo->clk_en_pin != -1) {
        ret = am_gpio_set(handle->p_devinfo->clk_en_pin, AM_GPIO_LEVEL_HIGH);
    }

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * �ص�Ƶ�����
 */
int am_rx8025sa_clkout_close(am_rx8025sa_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* �� FOE�����õͣ��ر�CLK��� */
    if( handle->p_devinfo->clk_en_pin != -1) {
        ret = am_gpio_set(handle->p_devinfo->clk_en_pin, AM_GPIO_LEVEL_LOW);
    }

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}
/* end of file */
