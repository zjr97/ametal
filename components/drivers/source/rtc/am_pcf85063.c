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
 * \brief PCF85063�����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.10 17-08-16  vir, add standard alarm_clk
 * - 1.00 16-08-05  sky, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_pcf85063.h"
#include "am_gpio.h"

/*****************************************************************************
 * �궨��
 ****************************************************************************/

/** \brief PCF85063�豸��ַ */
#define __PCF85063_ADDR               0x51

/**
 * \name PCF85063 �Ĵ�����ַ
 * \anchor grp_pcf85063_reg_addr
 * @{
 */


#define __PCF85063_REG_CTRL_STATUS1   0x00  /**< \brief ����״̬�Ĵ���1 */
#define __PCF85063_REG_CTRL_STATUS2   0x01  /**< \brief ����״̬�Ĵ���2 */

#define __PCF85063_REG_OFFSET         0x02  /**< \brief �����Ĵ��� */
#define __PCF85063_REG_RAM_BYTE       0x03  /**< \brief RAM�ֽڼĴ��� */

#define __PCF85063_REG_VL_SECONDS     0x04  /**< \brief ʱ��-��Ĵ���(SECONDS:0~59) */
#define __PCF85063_REG_MINUTES        0x05  /**< \brief ʱ��-�ּĴ���(MINUTES:0~59) */
#define __PCF85063_REG_HOURS          0x06  /**< \brief ʱ��-ʱ�Ĵ���(HOURS:0~23) */
#define __PCF85063_REG_DAYS           0x07  /**< \brief ����-��Ĵ���(DAYS:1~31) */
#define __PCF85063_REG_WEEKDAYS       0x08  /**< \brief ����-�ܼ��Ĵ���(WEEKDAYS:0~6) */
#define __PCF85063_REG_CENTURY_MONTHS 0x09  /**< \brief ����-�¼Ĵ���(MONTHS:1~12) */
#define __PCF85063_REG_YEAERS         0x0A  /**< \brief ����-��Ĵ���(YEARS:0~99) */

#define __PCF85063_REG_SECOND_ALARM   0x0B  /**< \brief �����ӼĴ��� */
#define __PCF85063_REG_MINUTE_ALARM   0x0C  /**< \brief �������ӼĴ��� */
#define __PCF85063_REG_HOUR_ALARM     0x0D  /**< \brief Сʱ���ӼĴ��� */
#define __PCF85063_REG_DAY_ALARM      0x0E  /**< \brief �����ӼĴ��� */
#define __PCF85063_REG_WEEKDAY_ALARM  0x0F  /**< \brief �ܼ����ӼĴ��� */

#define __PCF85063_REG_TIMER_VALUE    0x10  /**< \brief ��ʱ���Ĵ��� */
#define __PCF85063_REG_TIMER_MODE     0x11  /**< \brief ��ʱ��ģʽ�Ĵ��� */

/**
 * @}
 */

/**
 * \name PCF85063 �Ĵ���λ������
 * \anchor grp_pcf85063_bitfield_descriptions
 * @{
 */

#define __PCF85063_BF_STOP        0x20     /**< \brief RTCֹͣ */
#define __PCF85063_BF_12_24       0x02     /**< \brief 12/24Сʱ��(0:24 1:12) */

#define __PCF85063_BF_AIE         0x80     /**< \brief �����ж�ʹ��-AIE */
#define __PCF85063_BF_AF          0x40     /**< \brief �����жϱ�־ */
#define __PCF85063_BF_MI          0x20     /**< \brief �����ж����� */
#define __PCF85063_BF_HMI         0x10     /**< \brief ������ж����� */
#define __PCF85063_BF_TF          0x08     /**< \brief ��ʱ���жϱ�־ */
#define __PCF85063_BF_COF         0x07     /**< \brief ʱ��������� */

#define __PCF85063_BF_ALARM_DIS   0x80     /**< \brief ���ӽ��� */

#define __PCF85063_BF_TIMER_TCF   0x18     /**< \brief ��ʱ��ʱ��Դλ������-TCF[1:0] */
#define __PCF85063_BF_TE          0x04     /**< \brief ��ʱ��ʹ��-TIE */
#define __PCF85063_BF_TIE         0x02     /**< \brief ��ʱ���ж�����-TIE */
#define __PCF85063_BF_TI_TP       0x01     /**< \brief ��ʱ���ж�TTL(0) or PULSE(1) */

/**
 * @}
 */

/**
 * \name PCF85063 I2C��ǰ״̬
 * \anchor grp_pcf85063_i2c_operation
 * @{
 */

#define __PCF85063_I2C_RD_C2_STATUS        0x00    /**< \brief ��ȡ���ƼĴ���״̬ */
#define __PCF85063_I2C_WR_C2_STATUS        0x01    /**< \brief ������ƼĴ�����Ӧ��״̬λ */
#define __PCF85063_I2C_RD_WEEKDAYS         0x02    /**< \brief ��ȡ�ܼ��Ĵ�����ֵ */
#define __PCF85063_I2C_WR_WEEKDAYS         0x03    /**< \brief д���ܼ��Ĵ�����ֵ*/
#define __PCF85063_I2C_DATA_PROCESSING     0x04    /**< \brief ���ݴ���׶� */

/**
 * @}
 */

/**
 * \name PCF85063 �����λ��
 * \note ��Ҫʹ�������λʱ��ֱ�ӽ��ø�λ��д��CS1�Ĵ���
 * @{
 */

#define __PCF85063_SOFTWARE_RESET_CODE  0x58    /**< \brief �����λ�� */

/**
 * @}
 */
/**
 * \name PCF85063 ����ģʽ
 * @{
 */

#define __PCF85063_ALARM_MODE_STANDARD     0x01    /**< \brief �û����õ��Ǳ�׼�����ӽӿ� */
#define __PCF85063_ALARM_MODE_NONSTANDARD  0x02    /**< \brief �û����õ��ǷǱ�׼�����ӽӿ� */
/**
 * @}
 */

/*****************************************************************************
 * ��̬����
 ****************************************************************************/

/* RTC driver function implementation */
static int __pcf85063_time_set (void *p_drv, am_tm_t *p_tm);
static int __pcf85063_time_get (void *p_drv, am_tm_t *p_tm);

/**
 * \brief RTC driver functions definition
 */
static struct am_rtc_drv_funcs __g_rtc_drv_funcs = {
    __pcf85063_time_set,
    __pcf85063_time_get
};

/* �������� */
static void __pcf85063_eint_isr (void *p_arg);

/* ALARM_CLK driver function implementation */
static int __pcf85063_alarm_clk_time_set (void *p_drv, am_alarm_clk_tm_t *p_tm);
static int __pcf85063_alarm_clk_callback_set (void         *p_drv,
                                              am_pfnvoid_t  pfn_alarm_callback,
                                              void         *p_arg);
static int __pcf85063_alarm_clk_on (void *p_drv);
static int __pcf85063_alarm_clk_off (void *p_drv);

/**
 * \brief ALARM_CLK driver functions definition
 */
static struct am_alarm_clk_drv_funcs __g_alarm_clk_drv_funcs = {
    __pcf85063_alarm_clk_time_set,
    __pcf85063_alarm_clk_callback_set,
    __pcf85063_alarm_clk_on,
    __pcf85063_alarm_clk_off,
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
 * \brief ƫ�Ʋ����Ļ�׼
 */
static const float __offset_lsb_ppm[2] = {
    4.34,       /* ����ģʽ�µ�ppm��׼ */
    4.069       /* ����ģʽ�µ�ppm��׼ */
};

/*****************************************************************************
 * �ڲ�����ʵ��
 ****************************************************************************/

/**
 * \brief �ж�����Ƿ�Ϊ����
 *
 * \param[in] year : ���
 *
 * \retval 1 : ����
 * \retval 0 : ƽ��
 */
static uint8_t __pcf85063_leap_year_check (uint16_t year)
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
static uint8_t __pcf85063_day_of_year (uint16_t year, uint8_t month, uint8_t day)
{
    uint8_t i;

    if (__pcf85063_leap_year_check(year)) {
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
int __pcf85063_time_validator (am_tm_t *p_tm)
{
    if (p_tm->tm_year > 199 || p_tm->tm_year < 0 ||
        p_tm->tm_mon > 11   || p_tm->tm_mon < 0 ||
        p_tm->tm_mday >
        __mdays[__pcf85063_leap_year_check(1900 + p_tm->tm_year)][p_tm->tm_mon] ||
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
 * \brief PCF85063�豸��ʼ��
 * \param[in] p_dev : ָ��PCF85063�豸�ṹ��
 * \return AM_OK��ʾ��ʼ���ɹ�, ����ʧ��
 */
static int __pcf85063_init (am_pcf85063_dev_t *p_dev)
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
                       __PCF85063_REG_CTRL_STATUS2,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
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
static int __pcf85063_time_set (void *p_drv, am_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[7] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ��֤ʱ����Ϣ����Ч�� */
    if ((AM_OK != __pcf85063_time_validator(p_tm)) ||
        (p_tm->tm_hour > 23) || (p_tm->tm_hour < 0)) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_pcf85063_dev_t *)p_drv)->i2c_dev);

    /* ��ʱ��������Ϣ����buf�� */
    buf[__PCF85063_REG_VL_SECONDS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_sec);
    buf[__PCF85063_REG_MINUTES - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_min);
    buf[__PCF85063_REG_HOURS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_hour);
    buf[__PCF85063_REG_DAYS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_mday);
    buf[__PCF85063_REG_WEEKDAYS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_wday);
    buf[__PCF85063_REG_CENTURY_MONTHS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_mon + 1);
    buf[__PCF85063_REG_YEAERS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_year);

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_VL_SECONDS,
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
static int __pcf85063_time_get (void *p_drv, am_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[7] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_pcf85063_dev_t *)p_drv)->i2c_dev);

    /* ͨ��I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_VL_SECONDS,
                      buf,
                      sizeof(buf));

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }

    /** ��buf�л�ȡʱ��������Ϣ */
    p_tm->tm_sec  =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_VL_SECONDS - __PCF85063_REG_VL_SECONDS] & 0x7F);
    p_tm->tm_min  =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_MINUTES - __PCF85063_REG_VL_SECONDS] & 0x7F);
    p_tm->tm_hour =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_HOURS - __PCF85063_REG_VL_SECONDS] & 0x3F);
    p_tm->tm_mday =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_DAYS - __PCF85063_REG_VL_SECONDS] & 0x3F);
    p_tm->tm_wday =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_WEEKDAYS - __PCF85063_REG_VL_SECONDS] & 0x07);
    p_tm->tm_mon  =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_CENTURY_MONTHS - __PCF85063_REG_VL_SECONDS] & 0x1F) - 1;
    p_tm->tm_year =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_YEAERS - __PCF85063_REG_VL_SECONDS]);
    p_tm->tm_yday = __pcf85063_day_of_year(p_tm->tm_year, p_tm->tm_mon, p_tm->tm_mday);
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
static int __pcf85063_alarm_clk_time_set (void *p_drv, am_alarm_clk_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    uint8_t temp;      /* ��ʱ�������ʱ��wday��ֵ */
    uint8_t count;     /* ������Ž����δ����������ڼ����������� */
    uint8_t flag = 1;

    /* ���ݻ����� */
    uint8_t buf[4] = {0};
    am_tm_t current_tm;
    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ��֤ʱ����Ϣ����Ч�� */
    if ((p_tm->min  > 59) || (p_tm->min  < 0) ||
        (p_tm->hour > 23) || (p_tm->hour < 0) ||
        (( p_tm->wdays & 0x7F) == 0 )) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_pcf85063_dev_t *)p_drv)->i2c_dev);

    /* �����ӵ�wdays���ݴ������ */
    ((am_pcf85063_dev_t *)p_drv)->alarm_clk_wdays = p_tm->wdays;

    /* ����û����õ��ǷǱ�׼�����ӽӿ� */
    ((am_pcf85063_dev_t *)p_drv)->alarm_mode = __PCF85063_ALARM_MODE_STANDARD;

    /* ��ȡ��ǰʱ�� */
    __pcf85063_time_get(p_drv, &current_tm);

    /* ��ʱ��������Ϣ����buf��  �����λΪ0��ʾʹ�ܸüĴ��� */
    buf[0] = AM_HEX_TO_BCD(p_tm->min);
    buf[1] = AM_HEX_TO_BCD(p_tm->hour);
    buf[2] = 0X80;                           /* �ر������� */

    /*
     * \brief �жϽ����ʱ���Ƿ񳬹����ӵ�ʱ��
     * \note flag =1 ��������ʱ�䣬����������Ч��ֱ�Ӵ����쿪ʼ�ж�
     *       flag =0 ��û�й�����ʱ�䣬����������Ч���ӽ��쿪ʼ�ж�
     */
    flag = 1;
    if ( p_tm->hour > current_tm.tm_hour ) {
       flag = 0;    /* �����������Ч */
    } else if ( p_tm->hour == current_tm.tm_hour ) {
                if (  p_tm->min > current_tm.tm_min ) {
                     flag = 0;   /* �����������Ч */
                }
    }
    temp = p_tm->wdays;                   /* ��������ֵ��ŵ���ʱ����������  */
    count = current_tm.tm_wday + flag;    /* ������������������ֵ������� */
    temp = temp >> count;                 /* ������ʱ��wday����ʹ�����λ����������������ڼ� */

    while (! (temp & 0x1) ) {
        temp = temp >> 1;                /* �������������û���������ӣ��Ǽ����鿴�������� */
        count++;
        if( 7 == count) {                /* �жϵ���������û���������ӵ�����ֵ���ִ������쿪ʼ�ж� */
            count = 0;
            temp  = p_tm->wdays;
        }
    }

    buf[3] = count;  /* ���Ҫ���ӵ��������� */



    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_MINUTE_ALARM,
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
static int __pcf85063_alarm_clk_callback_set (void         *p_drv,
                                              am_pfnvoid_t  pfn_alarm_callback,
                                              void         *p_arg)
{
	/* �������÷���ֵ */
    int ret = AM_OK;

    /* PCF85063 �豸ָ�� */
    am_pcf85063_handle_t  pcf85063_handle = NULL;

    /* �豸��Ϣָ�� */
    const am_pcf85063_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    pcf85063_handle = (am_pcf85063_handle_t)p_drv;
    p_devinfo       = pcf85063_handle->p_devinfo;

    if (-1 == p_devinfo->int_pin) {
        return -AM_ENOTSUP;
    }

    /* conn_stat���ڼ�¼��ǰ�ж�����״̬,�����ظ�����GPIO���Ӻ��� */
    if (!(pcf85063_handle->conn_stat)) {

        /* ���������жϻص����� */
        ret = am_gpio_trigger_connect(p_devinfo->int_pin,
        		                      __pcf85063_eint_isr,
									  pcf85063_handle);
        if (AM_OK != ret) {
            return ret;
        }

        /* ����Ϊ�½��ش��� */
        am_gpio_trigger_cfg(p_devinfo->int_pin, AM_GPIO_TRIGGER_FALL);
        am_gpio_trigger_on(p_devinfo->int_pin);

        /* ����conn_stat_inta״̬ΪTRUE */
        pcf85063_handle->conn_stat = AM_TRUE;
    }

    /* �����жϻص����� */
    pcf85063_handle->triginfo[1].pfn_callback = pfn_alarm_callback;
    pcf85063_handle->triginfo[1].p_arg        = p_arg;

    /* ������еĻص�������Ϊ�� */
    if ((pcf85063_handle->triginfo[0].pfn_callback == NULL) &&
    	(pcf85063_handle->triginfo[1].pfn_callback == NULL)) {

        /* ���conn_statΪTRUE�����GPIO������Ӻ��� */
        if (pcf85063_handle->conn_stat) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->int_pin,
                                             __pcf85063_eint_isr,
                                             pcf85063_handle);

            if (AM_OK != ret) {
                return ret;
            }

            /* �ر����Ŵ��� */
            am_gpio_trigger_off(p_devinfo->int_pin);

            /* ����conn_stat״̬ΪFALSE */
            pcf85063_handle->conn_stat = AM_FALSE;
        }
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
static int __pcf85063_alarm_clk_on (void *p_drv)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1]     = {0};
    uint8_t buf_cs2[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    /* ��p_drv�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_pcf85063_dev_t *)p_drv)->i2c_dev);

    buf[0] = __PCF85063_BF_ALARM_DIS;
     /* �ر������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_SECOND_ALARM,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �ر������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_DAY_ALARM,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ��ȡ����״̬�Ĵ���2(�������������ж�) */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS2,
                      buf_cs2,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ʹ�� */
    buf_cs2[0] |= __PCF85063_BF_AIE;

    /* ���AF��־ */
    buf_cs2[0] &= ~__PCF85063_BF_AF;

    /* �������ж���Ϣд�����״̬�Ĵ���2 */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS2,
                       buf_cs2,
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
static int __pcf85063_alarm_clk_off (void *p_drv)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[5]     = {0};
    uint8_t buf_cs2[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    /* ��p_drv�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_pcf85063_dev_t *)p_drv)->i2c_dev);

    /* �ر��롢�֡�Сʱ���졢�������� */
    buf[0] = __PCF85063_BF_ALARM_DIS;
    buf[1] = __PCF85063_BF_ALARM_DIS;
    buf[2] = __PCF85063_BF_ALARM_DIS;
    buf[3] = __PCF85063_BF_ALARM_DIS;
    buf[4] = __PCF85063_BF_ALARM_DIS;

    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_DAY_ALARM,
                       buf,
                       sizeof (buf));

    if (AM_OK != ret) {
        return ret;
    }

    /* ��ȡ����״̬�Ĵ���2(�������������ж�) */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS2,
                      buf_cs2,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ʧ�� */
    buf_cs2[0] &= ~__PCF85063_BF_AIE;

    /* ���AF��־ */
    buf_cs2[0] &= ~__PCF85063_BF_AF;

    /* �������ж���Ϣд�����״̬�Ĵ���2 */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS2,
                       buf_cs2,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}

/**
 * \brief �����жϱ�־��ִ���û��жϻص�����
 *
 * \param[in] p_dev     : ָ��PCF85063�豸��ָ��
 * \param[in] intr_flag : �жϱ�־
 *
 * \return ��
 */
static void __pcf85063_callback_exec (void    *p_drv,
                                      uint8_t  intr_flag)
{
    am_pcf85063_dev_t *p_dev        = NULL;
    am_pfnvoid_t       pfn_callback = NULL;
    void              *p_arg        = NULL;

    /* ���������Ч�� */
    if (0 == intr_flag || NULL == p_drv) {
        return;
    }

    p_dev = (am_pcf85063_dev_t *)p_drv;

    /* �����TIMER�жϣ���ִ�ж�Ӧ�û��жϻص����� */
    if (intr_flag & __PCF85063_BF_TF) {
        pfn_callback = p_dev->triginfo[0].pfn_callback;
        p_arg        = p_dev->triginfo[0].p_arg;
        if (NULL != pfn_callback) {
            pfn_callback(p_arg);
        }
    }

    /* �����ALARM�жϣ���ִ�ж�Ӧ�û��жϻص����� */
    if (intr_flag & __PCF85063_BF_AF) {
        pfn_callback = p_dev->triginfo[1].pfn_callback;
        p_arg        = p_dev->triginfo[1].p_arg;
        if (NULL != pfn_callback) {
            pfn_callback(p_arg);
        }
    }
}

/**
 * \brief ���ж��ж�ȡ���ݺ�Ĵ�����,�ж��ж�����
 *
 * \param[in,out] buf         : ���ݻ�����
 * \param[in]     p_intr_flag : �жϱ�־  �μ� \ref grp_pcf85063_intr_flag
 *
 * \return ��
 *
 * \note ������buf ��Ӧ CTRL_STATUS2�Ĵ��� //shauew buf�Ĵ����Ƿ��Ӧ
 */
static void __pcf85063_read_write_data_processing (void    *p_arg,
                                                   uint8_t *p_intr_flag)
{
    am_pcf85063_dev_t *p_dev = NULL;

    if (NULL == p_arg) {
        return;
    }

    p_dev = (am_pcf85063_dev_t *)p_arg;

    *p_intr_flag = 0;

    /* �ж��Ƿ�ΪTF��־��λ */
    if (p_dev->buf[0] & __PCF85063_BF_TF) {

        /* ��¼TIMER�жϱ�־ */
        *p_intr_flag |= __PCF85063_BF_TF;

        /* ���TF��־ */
        p_dev->buf[0] &= ~__PCF85063_BF_TF;
    }

    /* �ж��Ƿ�ΪAF��־��λ */
    if (p_dev->buf[0] & __PCF85063_BF_AF) {
        if (p_dev->buf[0] & __PCF85063_BF_AIE) {
            /* ��¼�����жϱ�־,�����AF */
            *p_intr_flag |= __PCF85063_BF_AF;
            p_dev->buf[0] &= ~__PCF85063_BF_AF;
        }
    }
}


static void __pcf85063_get_next_wday_processing (void *p_arg)
{
    am_pcf85063_dev_t *p_dev = NULL;
    
    uint8_t            temp;      /* ��ʱ�������ʱ��wday��ֵ  */
    uint8_t            count;     /* ������Ž����δ����������ڼ����������� */
    
    if (NULL == p_arg) {
        return;
    }

    p_dev = (am_pcf85063_dev_t *)p_arg;
    if ( p_dev->alarm_mode == __PCF85063_ALARM_MODE_NONSTANDARD) {
        return;
    }
 
    temp = p_dev->alarm_clk_wdays;   /* ��������ֵ��ŵ���ʱ����������  */
    count = p_dev->buf[0] + 1;    /* �����������ֵ������� */
    temp = temp >> count;                    /* ������ʱ��wday����ʹ�����λ������������ڼ� */

    while (! (temp & 0x1) ) {
        temp = temp >> 1;                /* ������û���������ӣ��Ǽ����鿴���� */
        count++;
        if( 7 == count) {                /* �жϵ���������û���������ӵ�����ֵ���ִ������쿪ʼ�ж� */
            count = 0;
            temp  =  p_dev->alarm_clk_wdays;
        }
    }
    p_dev->buf[0] = count;
}
/**
 * \brief I2C��д�����е�״̬��
 * \param[in] p_arg : ����
 * \return ��
 * \note ״̬�任˳��   [1]����ʼ --> [2]��ȡsubaddr[0]��ֵ --> [3]�������ݣ���д��subaddr[0]
 *     --> [4] ��ȡsubaddr[1]��ֵ--> [5]�������ݣ���д��subaddr[1]--> [6]��������--> [7]�������
 */
static void __pcf85063_i2c_read_write_fsm (void *p_arg)
{
    /* I2C�豸 */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* PCF85063�豸  */
    am_pcf85063_dev_t *p_pcf85063_dev = NULL;

    /* �жϲ�������Ч�� */
    if (NULL == p_arg) {
        return;
    }

    p_pcf85063_dev = (am_pcf85063_dev_t *)p_arg;

    /*��ȡi2c_device */
    p_i2c_dev = &(p_pcf85063_dev->i2c_dev);

    switch (p_pcf85063_dev->status) {

    /* ��ȡ���ƼĴ���2��ֵ */
    case __PCF85063_I2C_RD_C2_STATUS:

        /* ������һ״̬ */
        p_pcf85063_dev->status = __PCF85063_I2C_WR_C2_STATUS;

        am_i2c_mktrans(&p_pcf85063_dev->trans[0],
                       p_i2c_dev->dev_addr,
                      (p_i2c_dev->dev_flags | AM_I2C_M_WR),
                      (uint8_t *)&p_pcf85063_dev->sub_addr[0],
                       1);

        am_i2c_mktrans(&p_pcf85063_dev->trans[1],
                       p_i2c_dev->dev_addr,
                      (p_i2c_dev->dev_flags | AM_I2C_M_RD),
                      (uint8_t *)p_pcf85063_dev->buf,
                      p_pcf85063_dev->nbytes);

        am_i2c_mkmsg(&p_pcf85063_dev->msg,
                     p_pcf85063_dev->trans,
                     2,
                     (am_pfnvoid_t)__pcf85063_i2c_read_write_fsm,
                     p_arg);

        am_i2c_msg_start(p_i2c_dev->handle, &p_pcf85063_dev->msg);
        break;

    /* ������ƼĴ���2��Ӧ��״̬ */
    case __PCF85063_I2C_WR_C2_STATUS:

        /* ������һ״̬ */
        p_pcf85063_dev->status = __PCF85063_I2C_RD_WEEKDAYS;

        /* �������ݣ���ȡ�ж�״̬ */
        __pcf85063_read_write_data_processing(p_arg, &p_pcf85063_dev->intr_flag);

        am_i2c_mktrans(&p_pcf85063_dev->trans[0],
                       p_i2c_dev->dev_addr,
                      (p_i2c_dev->dev_flags | AM_I2C_M_WR),
                      (uint8_t *)&p_pcf85063_dev->sub_addr[0],
                       1);

        am_i2c_mktrans(&p_pcf85063_dev->trans[1],
                        p_i2c_dev->dev_addr,
                       (p_i2c_dev->dev_flags | AM_I2C_M_NOSTART | AM_I2C_M_WR),
                       (uint8_t *)p_pcf85063_dev->buf,
                       p_pcf85063_dev->nbytes);

        am_i2c_mkmsg(&p_pcf85063_dev->msg,
                     p_pcf85063_dev->trans,
                     2,
                     (am_pfnvoid_t)__pcf85063_i2c_read_write_fsm,
                     p_arg);

        am_i2c_msg_start(p_i2c_dev->handle, &p_pcf85063_dev->msg);
        break;

     /* ��ȡ���ڼĴ�����ֵ  */
    case __PCF85063_I2C_RD_WEEKDAYS:

        /* ������һ״̬ */
        p_pcf85063_dev->status = __PCF85063_I2C_WR_WEEKDAYS;

        am_i2c_mktrans(&p_pcf85063_dev->trans[0],
                       p_i2c_dev->dev_addr,
                      (p_i2c_dev->dev_flags | AM_I2C_M_WR),
                      (uint8_t *)&p_pcf85063_dev->sub_addr[1],
                       1);

        am_i2c_mktrans(&p_pcf85063_dev->trans[1],
                       p_i2c_dev->dev_addr,
                      (p_i2c_dev->dev_flags | AM_I2C_M_RD),
                      (uint8_t *)p_pcf85063_dev->buf,
                      p_pcf85063_dev->nbytes);

        am_i2c_mkmsg(&p_pcf85063_dev->msg,
                     p_pcf85063_dev->trans,
                     2,
                     (am_pfnvoid_t)__pcf85063_i2c_read_write_fsm,
                     p_arg);

        am_i2c_msg_start(p_i2c_dev->handle, &p_pcf85063_dev->msg);
        break;

    /* �������ڼĴ���  */
    case __PCF85063_I2C_WR_WEEKDAYS:

        /* ������һ״̬ */
        p_pcf85063_dev->status = __PCF85063_I2C_DATA_PROCESSING;

        /* ��ȡ��һ��Ҫ���ӵ����ڼ�*/
        __pcf85063_get_next_wday_processing(p_arg);

        am_i2c_mktrans(&p_pcf85063_dev->trans[0],
                       p_i2c_dev->dev_addr,
                      (p_i2c_dev->dev_flags | AM_I2C_M_WR),
                      (uint8_t *)&p_pcf85063_dev->sub_addr[1],
                       1);

        am_i2c_mktrans(&p_pcf85063_dev->trans[1],
                        p_i2c_dev->dev_addr,
                       (p_i2c_dev->dev_flags | AM_I2C_M_NOSTART | AM_I2C_M_WR),
                       (uint8_t *)p_pcf85063_dev->buf,
                       p_pcf85063_dev->nbytes);

        am_i2c_mkmsg(&p_pcf85063_dev->msg,
                     p_pcf85063_dev->trans,
                     2,
                     (am_pfnvoid_t)__pcf85063_i2c_read_write_fsm,
                     p_arg);

        am_i2c_msg_start(p_i2c_dev->handle, &p_pcf85063_dev->msg);
        break;

        /* ���ݴ��� */
    case __PCF85063_I2C_DATA_PROCESSING:

        /* ������һ״̬ */
        p_pcf85063_dev->status = __PCF85063_I2C_RD_C2_STATUS;

        /* ִ���û��ж��жϻص����� */
        __pcf85063_callback_exec(p_arg, p_pcf85063_dev->intr_flag);

        /* ����GPIO�ж� */
        am_gpio_trigger_on(p_pcf85063_dev->p_devinfo->int_pin);
        break;

    default:
        break;
    }
}

/**
 * \brief PCF85063�жϻص�����
 * \param[in] p_arg : �жϻص���������
 * \return ��
 */
static void __pcf85063_eint_isr (void *p_arg)
{
    am_pcf85063_dev_t        *p_dev        = (am_pcf85063_dev_t *)p_arg;

    if (NULL == p_arg) {
        return;
    }

    /* �ر�GPIO�ж� */
    am_gpio_trigger_off(p_dev->p_devinfo->int_pin);

    if (p_dev->status == __PCF85063_I2C_RD_C2_STATUS) {

        /* ������д״̬�� */
        __pcf85063_i2c_read_write_fsm(p_arg);
    }
}

/*****************************************************************************
 * �ⲿ����ʵ��
 ****************************************************************************/

/**
 * \brief PCF85063 �豸��ʼ��
 */
am_pcf85063_handle_t am_pcf85063_init (am_pcf85063_dev_t           *p_dev,
                                       const am_pcf85063_devinfo_t *p_devinfo,
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
                 __PCF85063_ADDR,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    /* ��ʼ���豸��Ϣ */
    p_dev->conn_stat = AM_FALSE;
    p_dev->p_devinfo = p_devinfo;

    for (i = 0; i < 2; i++) {
        p_dev->triginfo[i].pfn_callback = NULL;
        p_dev->triginfo[i].p_arg        = NULL;
    }
    p_dev->status      = __PCF85063_I2C_RD_C2_STATUS;   /* ��ʼ״̬ */
    p_dev->sub_addr[0] = __PCF85063_REG_CTRL_STATUS2;   /* �������Ŀ��ƼĴ�����ַ */
    p_dev->sub_addr[1] = __PCF85063_REG_WEEKDAYS;       /* �����������ڼĴ�����ַ */
    p_dev->nbytes   = 1;                                /* ��Ҫ��ȡ�����ݸ��� */

    /* ��ʼ��PCF85063�豸 */
    ret = __pcf85063_init(p_dev);
    if (AM_OK != ret) {
        return NULL;
    }
    /* ��ʼ��clk_en_pin ��GPIO�� */
    if (p_dev->p_devinfo->clk_en_pin != -1) {
         am_gpio_pin_cfg(p_dev->p_devinfo->clk_en_pin, AM_GPIO_PUSH_PULL);  /* ����Ϊ������� */
         am_gpio_set(p_dev->p_devinfo->clk_en_pin, AM_GPIO_LEVEL_LOW);
    }
    return p_dev;
}



/**
 * \brief PCF85063 �豸���ʼ��
 */
void am_pcf85063_deinit (am_pcf85063_handle_t handle)
{

}

/**
 * \brief ��ȡPCF85063 RTC��׼����
 */
am_rtc_handle_t am_pcf85063_rtc_init (am_pcf85063_handle_t  handle,
                                      am_rtc_serv_t        *p_rtc)
{
    p_rtc->p_drv   = handle;
    p_rtc->p_funcs = &__g_rtc_drv_funcs;
    return p_rtc;
}

/**
 * \brief ��ȡPCF85063 ALARM_CLK��׼����
 */
am_alarm_clk_handle_t am_pcf85063_alarm_clk_init (am_pcf85063_handle_t   handle,
		                                         am_alarm_clk_serv_t    *p_alarm_clk)
{
	p_alarm_clk->p_drv   = handle;
	p_alarm_clk->p_funcs = &__g_alarm_clk_drv_funcs;
    return p_alarm_clk;
}

/**
 * \brief �����λPCF85063
 */
int am_pcf85063_software_reset (am_pcf85063_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1] = {__PCF85063_SOFTWARE_RESET_CODE};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = &(handle->i2c_dev);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ��ֹPCF85063
 */
int am_pcf85063_stop (am_pcf85063_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = &(handle->i2c_dev);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��ȡCS1 */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS1,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ��STOPλ */
    buf[0] |= __PCF85063_BF_STOP;

    /* дSTOP��CS1 */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ����PCF85063(��λʱPCF85063���������ýӿ���Ҫ����� am_pcf85063_stop())
 */
int am_pcf85063_start (am_pcf85063_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = &(handle->i2c_dev);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��ȡCS1 */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS1,
                      buf,
                      1);

    /* ��STOPλ */
    buf[0] &= ~__PCF85063_BF_STOP;

    /* ���CS1�е�STOP */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS1,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief д PCF85063 RAM_Byte �Ĵ���
 */
int am_pcf85063_ram_write (am_pcf85063_handle_t handle, uint8_t data)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = &(handle->i2c_dev);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_RAM_BYTE,
                       &data,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief �� PCF85063 RAM_Byte �Ĵ���
 */
int am_pcf85063_ram_read (am_pcf85063_handle_t handle, uint8_t *p_data)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = &(handle->i2c_dev);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ����I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_RAM_BYTE,
                      p_data,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief PCF85063ʱ���������ú���
 */
int am_pcf85063_time_set (am_pcf85063_handle_t handle, am_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[7]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == handle || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ��֤ʱ����Ϣ����Ч�� */
    if (AM_OK != __pcf85063_time_validator(p_tm)) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ʱ��������Ϣ����buf�� */
    buf[__PCF85063_REG_VL_SECONDS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_sec);
    buf[__PCF85063_REG_MINUTES - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_min);
    buf[__PCF85063_REG_HOURS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_hour);
    buf[__PCF85063_REG_DAYS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_mday);
    buf[__PCF85063_REG_WEEKDAYS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_wday);
    buf[__PCF85063_REG_CENTURY_MONTHS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_mon + 1);
    buf[__PCF85063_REG_YEAERS - __PCF85063_REG_VL_SECONDS] =
                                             AM_HEX_TO_BCD(p_tm->tm_year);

    /* ����I2C����ʱ���Լ��������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_VL_SECONDS,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return -ret;
    }

    return AM_OK;
}

/**
 * \brief PCF85063ʱ�����ڻ�ȡ����
 */
int am_pcf85063_time_get (am_pcf85063_handle_t handle, am_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[7]     = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == handle || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ͨ��I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_VL_SECONDS,
                      buf,
                      sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    /* ��buf�л�ȡʱ��������Ϣ */
    p_tm->tm_sec  =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_VL_SECONDS - __PCF85063_REG_VL_SECONDS] & 0x7F);
    p_tm->tm_min  =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_MINUTES - __PCF85063_REG_VL_SECONDS] & 0x7F);
    p_tm->tm_hour =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_HOURS - __PCF85063_REG_VL_SECONDS] & 0x3F);
    p_tm->tm_mday =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_DAYS - __PCF85063_REG_VL_SECONDS] & 0x3F);
    p_tm->tm_wday =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_WEEKDAYS - __PCF85063_REG_VL_SECONDS] & 0x07);
    p_tm->tm_mon  =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_CENTURY_MONTHS - __PCF85063_REG_VL_SECONDS] & 0x1F) - 1;
    p_tm->tm_year =
    AM_BCD_TO_HEX(buf[__PCF85063_REG_YEAERS - __PCF85063_REG_VL_SECONDS]);
    p_tm->tm_yday = __pcf85063_day_of_year(p_tm->tm_year, p_tm->tm_mon, p_tm->tm_mday);

    return AM_OK;
}

/**
 * \brief PCF85063ʱ��Դ��������
 */
int am_pcf85063_offset_set (am_pcf85063_handle_t handle, uint8_t mode, float ppm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1] = {0};

    /* ƫ���� */
    float  offset_val = 0.0;
    int8_t result     = 0;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == handle || ((mode != AM_PCF85063_OFFSET_MODE_NORMAL)
                       && (mode != AM_PCF85063_OFFSET_MODE_COURSE))) {
        return -AM_EINVAL;
    }

    if ((mode == AM_PCF85063_OFFSET_MODE_NORMAL)
              && ((ppm > 273.420f) || (ppm < -277.760f))) {
        return -AM_EINVAL;
    }

    if ((mode == AM_PCF85063_OFFSET_MODE_COURSE)
              && ((ppm > 256.347f) || (ppm < -260.416f))) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ƫ�������м��� */
    offset_val = ppm / __offset_lsb_ppm[mode];

    /* ���������� */
    if (offset_val > 0) {

        /* ��ƫ���������������� */
        result = offset_val + 0.5f;

    } else {

        /* ��ƫ���������������� */
        result = offset_val - 0.5f;

        /* ����λΪ��7λ */
        result = (result & 0x3F) | 0x40;
    }

    /* ������������buf */
    buf[0] = mode << 7 | result;

    /* ͨ��I2C��ȡ���� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_OFFSET,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ʹ��PCF85063
 */
int am_pcf85063_alarm_enable (am_pcf85063_handle_t      handle,
                              am_pcf85063_alarm_info_t *p_alarm_info)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[5]     = {0};
    uint8_t buf_cs2[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle || NULL == p_alarm_info) {
        return -AM_EINVAL;
    }

    /* ��֤������Ϣ����ֵ����Ч�� */
    if (p_alarm_info->mday > 31 || p_alarm_info->mday < 0 ||
        p_alarm_info->wday > 6  || p_alarm_info->wday < 0 ||
        p_alarm_info->hour > 23 || p_alarm_info->hour < 0 ||
        p_alarm_info->min  > 59 || p_alarm_info->min < 0 ||
        p_alarm_info->sec  > 59 || p_alarm_info->sec < 0 ) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ����û����õ��ǷǱ�׼�����ӽӿ� */
    handle->alarm_mode = __PCF85063_ALARM_MODE_NONSTANDARD;

    /* ����ALARM_SECOND��Ϣ */
    if (p_alarm_info->enable & AM_PCF85063_ALARM_SECOND_ENABLE) {

        /* ʹ�ܲ���������ֵ */
        buf[__PCF85063_REG_SECOND_ALARM - __PCF85063_REG_SECOND_ALARM] &=
                                                 ~__PCF85063_BF_ALARM_DIS;
        buf[__PCF85063_REG_SECOND_ALARM - __PCF85063_REG_SECOND_ALARM] |=
         (AM_HEX_TO_BCD(p_alarm_info->sec) & 0x7F);

    } else {

        /* �������� */
        buf[__PCF85063_REG_SECOND_ALARM - __PCF85063_REG_SECOND_ALARM] |=
                                                    __PCF85063_BF_ALARM_DIS;
    }

    /* ����ALARM_MINUTE��Ϣ */
    if (p_alarm_info->enable & AM_PCF85063_ALARM_MINUTE_ENABLE) {

        /* ʹ�ܲ���������ֵ */
        buf[__PCF85063_REG_MINUTE_ALARM - __PCF85063_REG_SECOND_ALARM] &=
                                                 ~__PCF85063_BF_ALARM_DIS;
        buf[__PCF85063_REG_MINUTE_ALARM - __PCF85063_REG_SECOND_ALARM] |=
         (AM_HEX_TO_BCD(p_alarm_info->min) & 0x7F);

    } else {

        /* �������� */
        buf[__PCF85063_REG_MINUTE_ALARM - __PCF85063_REG_SECOND_ALARM] |=
                                                    __PCF85063_BF_ALARM_DIS;
    }

    /* ����ALARM_HOUR��Ϣ */
    if (p_alarm_info->enable & AM_PCF85063_ALARM_HOUR_ENABLE) {

        /* ʹ�ܲ���������ֵ */
        buf[__PCF85063_REG_HOUR_ALARM - __PCF85063_REG_SECOND_ALARM] &=
                                                 ~__PCF85063_BF_ALARM_DIS;
        buf[__PCF85063_REG_HOUR_ALARM - __PCF85063_REG_SECOND_ALARM] |=
         (AM_HEX_TO_BCD(p_alarm_info->hour) & 0x3F);

    } else {

        /* �������� */
        buf[__PCF85063_REG_HOUR_ALARM - __PCF85063_REG_SECOND_ALARM] |=
                                                    __PCF85063_BF_ALARM_DIS;
    }

    /* ����ALARM_DAY��Ϣ */
    if (p_alarm_info->enable & AM_PCF85063_ALARM_DAY_ENABLE) {

        /* ʹ�ܲ���������ֵ */
        buf[__PCF85063_REG_DAY_ALARM - __PCF85063_REG_SECOND_ALARM] &=
                                                 ~__PCF85063_BF_ALARM_DIS;
        buf[__PCF85063_REG_DAY_ALARM - __PCF85063_REG_SECOND_ALARM] |=
         (AM_HEX_TO_BCD(p_alarm_info->mday) & 0x3F);

    } else {

        /* �������� */
        buf[__PCF85063_REG_DAY_ALARM - __PCF85063_REG_SECOND_ALARM] |=
                                                    __PCF85063_BF_ALARM_DIS;
    }

    /* ����ALARM_WEEKDAY��Ϣ */
    if (p_alarm_info->enable & AM_PCF85063_ALARM_WEEKDAY_ENABLE) {

        /* ʹ�ܲ���������ֵ */
        buf[__PCF85063_REG_WEEKDAY_ALARM - __PCF85063_REG_SECOND_ALARM] &=
                                                 ~__PCF85063_BF_ALARM_DIS;
        buf[__PCF85063_REG_WEEKDAY_ALARM - __PCF85063_REG_SECOND_ALARM] |=
         (AM_HEX_TO_BCD(p_alarm_info->wday) & 0x07);

    } else {

        /* �������� */
        buf[__PCF85063_REG_WEEKDAY_ALARM - __PCF85063_REG_SECOND_ALARM] |=
                                                    __PCF85063_BF_ALARM_DIS;
    }

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_SECOND_ALARM,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    /* ��ȡ����״̬�Ĵ���2(�������������ж�) */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS2,
                      buf_cs2,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ʹ�� */
    buf_cs2[0] |= __PCF85063_BF_AIE;

    /* ���AF��־ */
    buf_cs2[0] &= ~__PCF85063_BF_AF;

    /* �������ж���Ϣд�����״̬�Ĵ���2 */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS2,
                       buf_cs2,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ����PCF85063����
 */
int am_pcf85063_alarm_disable (am_pcf85063_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[5]     = {0};
    uint8_t buf_cs2[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* �������� */
    buf[__PCF85063_REG_SECOND_ALARM - __PCF85063_REG_SECOND_ALARM]  |=
                                                        __PCF85063_BF_ALARM_DIS;
    buf[__PCF85063_REG_MINUTE_ALARM - __PCF85063_REG_SECOND_ALARM]  |=
                                                        __PCF85063_BF_ALARM_DIS;
    buf[__PCF85063_REG_HOUR_ALARM - __PCF85063_REG_SECOND_ALARM]    |=
                                                        __PCF85063_BF_ALARM_DIS;
    buf[__PCF85063_REG_DAY_ALARM - __PCF85063_REG_SECOND_ALARM]     |=
                                                        __PCF85063_BF_ALARM_DIS;
    buf[__PCF85063_REG_WEEKDAY_ALARM - __PCF85063_REG_SECOND_ALARM] |=
                                                        __PCF85063_BF_ALARM_DIS;

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_SECOND_ALARM,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    /* ��ȡ����״̬�Ĵ���2(�������������ж�) */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS2,
                      buf_cs2,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����жϽ��� */
    buf[0] &= ~__PCF85063_BF_AIE;

    /* ���AF��־ */
    buf_cs2[0] &= ~__PCF85063_BF_AF;

    /* �������ж���Ϣд�����״̬�Ĵ���2 */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS2,
                       buf_cs2,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ����PCF85063ʱ�����
 */
int am_pcf85063_clkout_set (am_pcf85063_handle_t handle, uint8_t freq)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤��������Ч�� */
    if (NULL == handle || freq > AM_PCA85063A_CLKOUT_FREQ_DISABLE) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ��ǰ״̬�Ĵ���2��ֵ */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS2,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    buf[0] &= ~__PCF85063_BF_COF;           /* ���clockout�� */
    buf[0] |= __PCF85063_BF_COF & freq;     /* �����µ�clock */

    /* д��״̬�Ĵ���2 */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS2,
                       buf,
                       1);

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
 * \brief �ر�Ƶ�ʵ����
 */
int am_pcf85063_clkout_close(am_pcf85063_handle_t handle)
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

/**
 * \brief ʹ��PCF85063��ʱ��
 */
int am_pcf85063_timer_enable (am_pcf85063_handle_t handle,
                              uint8_t              clk_freq,
                              uint8_t              max_timer_count)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[2] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ����I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_TIMER_VALUE,
                      buf,
                      sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    /* װ�ؼ���ֵ */
    buf[__PCF85063_REG_TIMER_VALUE - __PCF85063_REG_TIMER_VALUE] = max_timer_count;

    /* ѡ��ʱ��Ƶ���Լ�ʹ�ܶ�ʱ�� */
    buf[__PCF85063_REG_TIMER_MODE - __PCF85063_REG_TIMER_VALUE] &=
                                               ~__PCF85063_BF_TIMER_TCF;
    buf[__PCF85063_REG_TIMER_MODE - __PCF85063_REG_TIMER_VALUE] |=
                                    (clk_freq & __PCF85063_BF_TIMER_TCF) |
                                                __PCF85063_BF_TI_TP |
                                                __PCF85063_BF_TE;

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_TIMER_VALUE,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ����PCF85063��ʱ��
 */
int am_pcf85063_timer_disable (am_pcf85063_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ����I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_TIMER_MODE,
                      buf,
                      sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ʱ��ʹ��λ */
    buf[0] &= ~__PCF85063_BF_TE;

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_TIMER_MODE,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

int am_pcf85063_timer_count_get (am_pcf85063_handle_t  handle,
                                 uint8_t              *p_count)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ����I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_TIMER_VALUE,
                      p_count,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ʹ��PCF85063����/��ʱ���ж�
 */
int am_pcf85063_minute_timer_int_enable (am_pcf85063_handle_t handle,
                                         uint8_t              flags)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� buf�洢�Ĵ���ֵ */
    uint8_t buf[2] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ����״̬�Ĵ���2(��������жϱ�־�Լ��������жϵ�ʹ��) */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS2,
                      &buf[0],
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ��ȡ��ʱ��ģʽ�Ĵ���(�������ƶ�ʱ���ж�) */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_TIMER_MODE,
                      &buf[1],
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ���ݲ�ͬ���ж����������� */

    if (flags & AM_PCF85063_INT_TIMER) {
        /* ��ʱ���ж�ʹ��,TF�������� */
        buf[1] |= __PCF85063_BF_TIE;
    }

    if (flags & AM_PCF85063_INT_HMINUTE) {
        /* ������ж�ʹ�� */
        buf[0] |= __PCF85063_BF_HMI;
    }

    if (flags & AM_PCF85063_INT_MINUTE) {
        /*  һ�����ж�ʹ�� */
        buf[0] |= __PCF85063_BF_MI;
    }

    /* ���TF��־ */
    buf[0] &= ~__PCF85063_BF_TF;

    /* ��TF��־��������ж���Ϣд�����״̬�Ĵ���2 */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS2,
                       &buf[0],
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ����ʱ����Ϣд�붨ʱ��ģʽ�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_TIMER_MODE,
                       &buf[1],
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief ����PCF85063����/��ʱ���ж�
 */
int am_pcf85063_minute_timer_int_disable (am_pcf85063_handle_t handle,
                                          uint8_t              flags)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� buf�洢�Ĵ���ֵ */
    uint8_t buf[2] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* ��֤������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ��ȡ����״̬�Ĵ���2(��������жϱ�־�Լ��������жϵ�ʹ��) */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_CTRL_STATUS2,
                      &buf[0],
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ��ȡ��ʱ��ģʽ�Ĵ���(�������ƶ�ʱ���ж�) */
    ret = am_i2c_read(p_i2c_dev,
                      __PCF85063_REG_TIMER_MODE,
                      &buf[1],
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ���ݲ�ͬ���ж����������� */

    if (flags & AM_PCF85063_INT_TIMER) {
        /* ��ʱ���жϽ��� */
        buf[1] &= ~__PCF85063_BF_TIE;
    }

    if (flags & AM_PCF85063_INT_HMINUTE) {
        /* ������жϽ��� */
        buf[0] &= ~__PCF85063_BF_HMI;
    }

    if (flags & AM_PCF85063_INT_MINUTE) {
        /*  һ�����жϽ��� */
        buf[0] &= ~__PCF85063_BF_MI;
    }

    /* ���TF��־ */
    buf[0] &= ~__PCF85063_BF_TF;

    /* ��TF��־��������ж���Ϣд�����״̬�Ĵ���2 */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_CTRL_STATUS2,
                       &buf[0],
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ����ʱ����Ϣд�붨ʱ��ģʽ�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __PCF85063_REG_TIMER_MODE,
                       &buf[1],
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief PCF85063 ����/��ʱ���ص���������
 */
int am_pcf85063_minute_timer_cb_set (am_pcf85063_handle_t  handle,
                                     am_pfnvoid_t          pfn_minute_timer_callback,
                                     void                 *p_minute_timer_arg)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* �豸��Ϣָ�� */
    const am_pcf85063_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡ�豸��Ϣ */
    p_devinfo = handle->p_devinfo;

    if (-1 == p_devinfo->int_pin) {
        return -AM_ENOTSUP;
    }

    /* conn_stat���ڼ�¼��ǰ�ж�����״̬,�����ظ�����GPIO���Ӻ��� */
    if (!(handle->conn_stat)) {

        /* ���������жϻص����� */
        ret = am_gpio_trigger_connect(p_devinfo->int_pin,
                                      __pcf85063_eint_isr,
                                      handle);
        if (AM_OK != ret) {
            return ret;
        }

        /* ����Ϊ�½��ش��� */
        am_gpio_trigger_cfg(p_devinfo->int_pin, AM_GPIO_TRIGGER_FALL);
        am_gpio_trigger_on(p_devinfo->int_pin);

        /* ����conn_stat״̬ΪTRUE */
        handle->conn_stat = AM_TRUE;

    }

    /* �����жϻص����� */
    handle->triginfo[0].pfn_callback = pfn_minute_timer_callback;
    handle->triginfo[0].p_arg        = p_minute_timer_arg;

    /* ������еĻص�������Ϊ�� */
    if ((handle->triginfo[0].pfn_callback == NULL) &&
        (handle->triginfo[1].pfn_callback == NULL)) {

        /* ���conn_statΪTRUE�����GPIO������Ӻ��� */
        if (handle->conn_stat) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->int_pin,
                                             __pcf85063_eint_isr,
                                             handle);

            if (AM_OK != ret) {
                return ret;
            }

            /* �ر����Ŵ��� */
            am_gpio_trigger_off(p_devinfo->int_pin);

            /* ����conn_stat״̬ΪFALSE */
            handle->conn_stat = AM_FALSE;
        }
    }

    return AM_OK;
}

/**
 * \brief PCF85063 ���ӻص���������
 */
int am_pcf85063_alarm_cb_set (am_pcf85063_handle_t  handle,
                              am_pfnvoid_t          pfn_alarm_callback,
                              void                 *p_alarm_arg)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* �豸��Ϣָ�� */
    const am_pcf85063_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡ�豸��Ϣ */
    p_devinfo = handle->p_devinfo;

    if (-1 == p_devinfo->int_pin) {
        return -AM_ENOTSUP;
    }

    /* conn_stat���ڼ�¼��ǰ�ж�����״̬,�����ظ�����GPIO���Ӻ��� */
    if (!(handle->conn_stat)) {

        /* ���������жϻص����� */
        ret = am_gpio_trigger_connect(p_devinfo->int_pin,
                                      __pcf85063_eint_isr,
                                      handle);
        if (AM_OK != ret) {
            return ret;
        }

        /* ����Ϊ�½��ش��� */
        am_gpio_trigger_cfg(p_devinfo->int_pin, AM_GPIO_TRIGGER_FALL);
        am_gpio_trigger_on(p_devinfo->int_pin);

        /* ����conn_stat״̬ΪTRUE */
        handle->conn_stat = AM_TRUE;

    }

    /* �����жϻص����� */
    handle->triginfo[1].pfn_callback = pfn_alarm_callback;
    handle->triginfo[1].p_arg        = p_alarm_arg;

    /* ������еĻص�������Ϊ�� */
    if ((handle->triginfo[0].pfn_callback == NULL) &&
        (handle->triginfo[1].pfn_callback == NULL)) {

        /* ���conn_statΪTRUE�����GPIO������Ӻ��� */
        if (handle->conn_stat) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->int_pin,
                                             __pcf85063_eint_isr,
                                             handle);

            if (AM_OK != ret) {
                return ret;
            }

            /* �ر����Ŵ��� */
            am_gpio_trigger_off(p_devinfo->int_pin);

            /* ����conn_stat״̬ΪFALSE */
            handle->conn_stat = AM_FALSE;
        }
    }

    return AM_OK;
}

/* end of file */
