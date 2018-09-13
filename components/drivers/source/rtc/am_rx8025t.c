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
 * \brief RX8025T�����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.01 18-01-08  sdq, make some changes.
 * - 1.00 17-08-07  vir, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_rx8025t.h"
#include "am_gpio.h"
/*****************************************************************************
 * �궨��
 ****************************************************************************/
 
 /** \brief RX8025T�豸��ַ  (��λ)*/
#define __RX8025T_ADDR               0x32

#define __RX8025T_YEAR_OFFS          100
/**
 * \name RX8025T�Ĵ�����ַ
 */
 
#define __RX8025T_REG_SECONDS          0x00    /**< \brief ��Ĵ�����ַ  */
#define __RX8025T_REG_MINUTES          0x01    /**< \brief �ּĴ�����ַ  */
#define __RX8025T_REG_HOURS            0x02    /**< \brief ʱ�Ĵ�����ַ   */
#define __RX8025T_REG_WEEKDAYS         0x03    /**< \brief ���ڼĴ�����ַ */
#define __RX8025T_REG_DAYS             0x04    /**< \brief �ռĴ�����ַ  */
#define __RX8025T_REG_MONTHS           0x05    /**< \brief �¼Ĵ�����ַ  */
#define __RX8025T_REG_YEAERS           0x06    /**< \brief ��Ĵ�����ַ   */

#define __RX8025T_REG_RAM              0x07    /**< \brief RAM�Ĵ�����ַ   */

#define __RX8025T_REG_MINUTES_ALARM    0x08    /**< \brief ���ӷּĴ�����ַ   */
#define __RX8025T_REG_HOURS_ALARM      0x09    /**< \brief ����ʱ�Ĵ�����ַ   */
#define __RX8025T_REG_WEEK_DAY_ALARM   0x0a    /**< \brief �������ڻ���Ĵ�����ַ   */

#define __RX8025T_REG_TIMER_COUNTER0   0x0b    /**< \brief ��ʱ���ƼĴ���1��ַ   */
#define __RX8025T_REG_TIMER_COUNTER1   0x0c    /**< \brief ��ʱ���ƼĴ���2��ַ   */

#define __RX8025T_REG_EXTENSION        0X0d    /**< \brief ��չ�Ĵ�����ַ   */
#define __RX8025T_REG_FLAG             0x0e    /**< \brief ��־�Ĵ�����ַ   */
#define __RX8025T_REG_CONTROL          0x0f    /**< \brief ���ƼĴ�����ַ   */

/**
 * \name RX8025T �Ĵ���λ������
 * \anchor grp_rx8025t_bitfield_descriptions
 * @{
 */

#define __RX8025T_TE_TIMER_ENABLE      0x10    /**< \brief ʹ�ܶ�ʱ�� */
#define __RX8025T_USEL_MIN_UPDATE      0x20    /**< \brief ���µ�ÿ���Ӵ����ж� */
#define __RX8025T_WADA_ALARM_DAY       0x40    /**< \brief ���ӹ���ѡ����ΪĿ�� */

#define __RX8025T_FLAG_AF   0x08    /**< \brief �����жϱ�־��λ */
#define __RX8025T_FLAG_TF   0x10    /**< \brief ��ʱ���жϱ�־��λ */
#define __RX8025T_FLAG_UF   0x20    /**< \brief ʱ������жϱ�־��λ */

#define __RX8025T_ALARM_INT_ENABLE   0x08  /**< \brief �����ж�ʹ�� */
/**
 * \name RX8025T I2C��ǰ״̬
 * \anchor grp_rx8025t_i2c_operation
 * @{
 */

#define __RX8025T_I2C_RD_STATUS        0x00    /**< \brief ��ȡ״̬ */
#define __RX8025T_I2C_WR_STATUS        0x01    /**< \brief ���״̬ */
#define __RX8025T_I2C_DATA_PROCESSING  0x02    /**< \brief ���ݴ���׶� */

/* RTC driver function implementation */
static int __rx8025t_time_set (void *p_drv, am_tm_t *p_tm);
static int __rx8025t_time_get (void *p_drv, am_tm_t *p_tm);

/**
 * \brief RTC driver functions definition
 */
static struct am_rtc_drv_funcs __g_rtc_drv_funcs = {
    __rx8025t_time_set,
    __rx8025t_time_get,
};

/* �������� */
static void __rx8025t_eint_isr (void *p_arg);

/* ALARM_CLK driver function implementation */
static int __rx8025t_alarm_clk_time_set (void *p_drv, am_alarm_clk_tm_t *p_tm);
static int __rx8025t_alarm_clk_callback_set (void         *p_drv,
                                             am_pfnvoid_t  pfn_alarm_callback,
                                             void         *p_arg);
static int __rx8025t_alarm_clk_on (void *p_drv);
static int __rx8025t_alarm_clk_off (void *p_drv);

/**
 * \brief ALARM_CLK driver functions definition
 */
static struct am_alarm_clk_drv_funcs __g_alarm_clk_drv_funcs = {
    __rx8025t_alarm_clk_time_set,
    __rx8025t_alarm_clk_callback_set,
    __rx8025t_alarm_clk_on,
    __rx8025t_alarm_clk_off,
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
static uint8_t __rx8025t_leap_year_check (uint16_t year)
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
static uint8_t __rx8025t_day_of_year (uint16_t year, uint8_t month, uint8_t day)
{
    uint8_t i;

    if (__rx8025t_leap_year_check(year)) {
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
int __rx8025t_time_validator (am_tm_t *p_tm)
{
    if (p_tm->tm_year > 199 || p_tm->tm_year < 0 ||
        p_tm->tm_mon > 11   || p_tm->tm_mon < 0 ||
        p_tm->tm_mday >
        __mdays[__rx8025t_leap_year_check(1900 + p_tm->tm_year)][p_tm->tm_mon] ||
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
static int __rx8025t_time_set (void *p_drv, am_tm_t *p_tm)
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
    if ((AM_OK != __rx8025t_time_validator(p_tm)) ||
        (p_tm->tm_hour > 23) || (p_tm->tm_hour < 0)) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_rx8025t_dev_t *)p_drv)->i2c_dev);

    /* ��ʱ��������Ϣ����buf�� */
    buf[__RX8025T_REG_SECONDS ] = AM_HEX_TO_BCD(p_tm->tm_sec);
    buf[__RX8025T_REG_MINUTES ] = AM_HEX_TO_BCD(p_tm->tm_min);
    buf[__RX8025T_REG_HOURS]    = AM_HEX_TO_BCD(p_tm->tm_hour);         /* 24Сʱ�Ƶ�Сʱ */

    buf[__RX8025T_REG_WEEKDAYS] = 1 << p_tm->tm_wday;
    buf[__RX8025T_REG_DAYS]     = AM_HEX_TO_BCD(p_tm->tm_mday);
    buf[__RX8025T_REG_MONTHS]   = AM_HEX_TO_BCD(p_tm->tm_mon + 1);
    buf[__RX8025T_REG_YEAERS]   = AM_HEX_TO_BCD((p_tm->tm_year - __RX8025T_YEAR_OFFS) % 100);

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_SECONDS,
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
static int __rx8025t_time_get (void *p_drv, am_tm_t *p_tm)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    uint8_t  temp = 0;

    /* ���ݻ����� */
    uint8_t buf[7] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(((am_rx8025t_dev_t *)p_drv)->i2c_dev);

    /* ͨ��I2C��ȡ���� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_SECONDS,
                      buf,
                      sizeof(buf));

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }

    /** ��buf�л�ȡʱ��������Ϣ */
    p_tm->tm_sec  = AM_BCD_TO_HEX(buf[__RX8025T_REG_SECONDS] & 0x7F);
    p_tm->tm_min  = AM_BCD_TO_HEX(buf[__RX8025T_REG_MINUTES] & 0x7F);
    p_tm->tm_hour = AM_BCD_TO_HEX(buf[__RX8025T_REG_HOURS] & 0x3F);

    while((buf[__RX8025T_REG_WEEKDAYS] >>= 1)) {
        temp++;
    }
    p_tm->tm_wday = temp;
    p_tm->tm_mday = AM_BCD_TO_HEX(buf[__RX8025T_REG_DAYS] & 0x3F );
    p_tm->tm_mon  = AM_BCD_TO_HEX(buf[__RX8025T_REG_MONTHS] & 0x1F) - 1;
    p_tm->tm_year = AM_BCD_TO_HEX(buf[__RX8025T_REG_YEAERS]) + __RX8025T_YEAR_OFFS;
    p_tm->tm_yday = __rx8025t_day_of_year(p_tm->tm_year, p_tm->tm_mon, p_tm->tm_mday);
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
static int __rx8025t_alarm_clk_time_set (void *p_drv, am_alarm_clk_tm_t *p_tm)
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
    p_i2c_dev = &(((am_rx8025t_dev_t *)p_drv)->i2c_dev);

    /* ��ʱ��������Ϣ����buf�� */
    buf[__RX8025T_REG_MINUTES_ALARM - __RX8025T_REG_MINUTES_ALARM] =
    		                              AM_HEX_TO_BCD(p_tm->min);
    buf[__RX8025T_REG_HOURS_ALARM - __RX8025T_REG_MINUTES_ALARM] =
    		                              AM_HEX_TO_BCD(p_tm->hour);
    /* ������������ת��BCD�� */
    buf[__RX8025T_REG_WEEK_DAY_ALARM - __RX8025T_REG_MINUTES_ALARM] = p_tm->wdays;

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
    	               __RX8025T_REG_MINUTES_ALARM,
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
static int __rx8025t_alarm_clk_callback_set (void         *p_drv,
                                             am_pfnvoid_t  pfn_alarm_callback,
                                             void         *p_arg)
{
	/* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t wada_buf[1] = {0};

    /* RX8025T �豸ָ�� */
    am_rx8025t_handle_t  rx8025t_handle = NULL;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �豸��Ϣָ�� */
    const am_rx8025t_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    rx8025t_handle = (am_rx8025t_handle_t)p_drv;
    p_devinfo      = rx8025t_handle->p_devinfo;
    p_i2c_dev      = &(rx8025t_handle->i2c_dev);

    if (-1 == p_devinfo->int_pin) {
        return -AM_ENOTSUP;
    }

    /* conn_stat���ڼ�¼��ǰ�ж�����״̬,�����ظ�����GPIO���Ӻ��� */
    if (!(rx8025t_handle->conn_stat)) {

        /* ���������жϻص����� */
        ret = am_gpio_trigger_connect(p_devinfo->int_pin,
        		                      __rx8025t_eint_isr,
									  rx8025t_handle);
        if (AM_OK != ret) {
            return ret;
        }

        /* ����Ϊ�½��ش��� */
        am_gpio_trigger_cfg(p_devinfo->int_pin, AM_GPIO_TRIGGER_FALL);
        am_gpio_trigger_on(p_devinfo->int_pin);

        /* ����conn_stat_inta״̬ΪTRUE */
        rx8025t_handle->conn_stat = AM_TRUE;

    }

    /* �����жϻص����� */
    rx8025t_handle->triginfo[2].pfn_callback = pfn_alarm_callback;
    rx8025t_handle->triginfo[2].p_arg        = p_arg;

    /* ������еĻص�������Ϊ�� */
    if ((rx8025t_handle->triginfo[0].pfn_callback == NULL) &&
    	(rx8025t_handle->triginfo[1].pfn_callback == NULL) &&
        (rx8025t_handle->triginfo[2].pfn_callback == NULL)) {

        /* ���conn_statΪTRUE�����GPIO������Ӻ��� */
        if (rx8025t_handle->conn_stat) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->int_pin,
                                             __rx8025t_eint_isr,
                                             rx8025t_handle);

            if (AM_OK != ret) {
                return ret;
            }

            /* �ر����Ŵ��� */
            am_gpio_trigger_off(p_devinfo->int_pin);

            /* ����conn_stat״̬ΪFALSE */
            rx8025t_handle->conn_stat = AM_FALSE;
        }
    }

    /* ��ȡ�Ĵ��� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_EXTENSION,
                      wada_buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

   /* ��׼������ӹ���ֻ��ѡ��������Ϊ����ʱ��Ĺ��� */
   wada_buf[0] &= ~__RX8025T_WADA_ALARM_DAY;

    /* ����Ϣд��̬�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_EXTENSION,
                       wada_buf,
                       1);

    if (AM_OK != ret) {
        return ret;
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
static int __rx8025t_alarm_clk_on (void *p_drv)
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
    p_i2c_dev = &(((am_rx8025t_dev_t *)p_drv)->i2c_dev);

    /* ��ȡ���ƼĴ���1 */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_CONTROL,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ʹ�� */
    buf[0] |= __RX8025T_ALARM_INT_ENABLE;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_CONTROL,
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
static int __rx8025t_alarm_clk_off (void *p_drv)
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
    p_i2c_dev = &(((am_rx8025t_dev_t *)p_drv)->i2c_dev);

    /* ��ȡ���ƼĴ��� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_CONTROL,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �ر������ж� */
    buf[0] &= ~__RX8025T_ALARM_INT_ENABLE;

    /* �������ж���Ϣд�����״̬�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_CONTROL,
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
 * \param[in] p_dev     : ָ��RX8025T�豸��ָ��
 * \param[in] intr_flag : �жϱ�־
 *
 * \return ��
 */
static void __rx8025t_callback_exec (void    *p_drv,
                                      uint8_t  intr_flag)
{
    am_rx8025t_dev_t *p_dev        = NULL;
    am_pfnvoid_t       pfn_callback = NULL;
    void              *p_arg        = NULL;

    /* ���������Ч�� */
    if (0 == intr_flag || NULL == p_drv) {
        return;
    }

    p_dev = (am_rx8025t_dev_t *)p_drv;

    /* ����������жϣ���ִ�ж�Ӧ�û��жϻص����� */
    if (intr_flag & __RX8025T_FLAG_UF) {
        pfn_callback = p_dev->triginfo[0].pfn_callback;
        p_arg        = p_dev->triginfo[0].p_arg;
        if (NULL != pfn_callback) {
            pfn_callback(p_arg);
        }
    }

    /* �����ALARM_D�жϣ���ִ�ж�Ӧ�û��жϻص����� */
    if (intr_flag & __RX8025T_FLAG_TF) {
        pfn_callback = p_dev->triginfo[1].pfn_callback;
        p_arg        = p_dev->triginfo[1].p_arg;
        if (NULL != pfn_callback) {
            pfn_callback(p_arg);
        }
    }

    /* �����ALARM_W�жϣ���ִ�ж�Ӧ�û��жϻص����� */
    if (intr_flag & __RX8025T_FLAG_AF) {
        pfn_callback = p_dev->triginfo[2].pfn_callback;
        p_arg        = p_dev->triginfo[2].p_arg;
        if (NULL != pfn_callback) {
            pfn_callback(p_arg);
        }
    }
}

/**
 * \brief ���ж��ж�ȡ���ݺ�Ĵ�����,�ж��ж�����
 *
 * \param[in,out] buf         : ���ݻ�����
 * \param[in]     p_intr_flag : �жϱ�־  �μ� \ref grp_rx8025t_intr_flag
 *
 * \return ��
 *
 * \note ������buf ��Ӧ CONTROL2�Ĵ���
 */
static void __rx8025t_read_write_data_processing (void    *p_arg,
                                                  uint8_t *p_intr_flag)
{
    am_rx8025t_dev_t *p_dev = NULL;

    if (NULL == p_arg) {
        return;
    }

    p_dev = (am_rx8025t_dev_t *)p_arg;

    *p_intr_flag = 0;

    /* �ж��Ƿ�ΪUF��־��λ */
    if (p_dev->buf[0] & __RX8025T_FLAG_UF) {

        /* ��¼ʱ������жϱ�־ */
        *p_intr_flag |= __RX8025T_FLAG_UF;

        /* ���UF��־ */
        p_dev->buf[0] &= ~__RX8025T_FLAG_UF;
    } else {
        p_dev->buf[0] |= __RX8025T_FLAG_UF;
    }

    /* �ж��Ƿ�ΪTF��־��λ */
    if (p_dev->buf[0] & __RX8025T_FLAG_TF) {
         /* ��¼��ʱ���жϱ�־,�����*/
        *p_intr_flag |= __RX8025T_FLAG_TF;

         /* ���TF��־ */
        p_dev->buf[0] &= ~__RX8025T_FLAG_TF;
    } else {
        p_dev->buf[0] |= __RX8025T_FLAG_TF;
    }

    /* �ж��Ƿ�ΪAF��־��λ */
    if (p_dev->buf[0] & __RX8025T_FLAG_AF) {
        /* ��¼�����жϱ�־,����� */
        *p_intr_flag |= __RX8025T_FLAG_AF;

          /* ���AF��־ */
        p_dev->buf[0] &= ~__RX8025T_FLAG_AF;
    } else {
        p_dev->buf[0] |= __RX8025T_FLAG_AF;
    }

}
/**
 * \brief I2C��д�����е�״̬��
 * \param[in] p_arg : ����
 * \return ��
 * \note ״̬�任˳��   [1]����ʼ --> [2]дsubaddr,��ȡ״̬ --> [3]��������
 *                   --> [5]дsubaddr --> [6]д������ --> [7]�������
 *
 *       ���ʱ������жϺͶ�ʱ���ж���ͬһ�뵽�����������Է��ֶ�ʱ���жϻ��ʱ������ж��ȵ�����ȡ�ж�
 *       ״ֻ̬�ܶ�ȡ����ʱ���жϣ��ȵ�����жϱ�ʶ��ʱ�򣨶�ȡ�ж�Լ0.5ms֮�󣩣�ʱ������ж�Ҳ����
 *       �ˣ������ʱ����������ж���ôʱ������жϽ��ò�����Ӧ�����ֻ�����ʱ���жϣ���ô���β�����ʱ
 *       ������жϻᱻ�Ƴٵ���һ���κ�һ���ж�����ʱһ�������Ƴٵ�ʱ��ȡ������һ���жϵ�����ʱ�䡣Ϊ
 *       �˽��������⣬���õķ����ǵ�һ�ζ�ȡ�ж�֮��ֻ�����������жϣ�֮���ٶ�ȡһ���жϱ�ʶ���ٽ�
 *       �д������ַ����ܱ�֤�жϷ������ܼ�ʱ���������������ĳ��ԭ�򣨳����ִ���ٶȼӿ��SPI�ж�
 *       �����ĸ��죩����״̬����ʱ�������̣��Ϳ��ܵ��µڶ��ζ�ȡ״̬��ʱ����Ȼû�ж�ȡ��ʱ�������
 *       �ϣ����ڵڶ�����״̬��ʱ��ʱ������жϵ����ˡ�Ϊ�˱����������⣬�ټ���һ�������ʱ����������ʱ
 *       ���������ж�2ms֮������ζ�ȡ�ж�״̬�����д���
 */
static void __rx8025t_i2c_read_write_fsm (void *p_arg)
{
    am_i2c_device_t  *p_dev_i2c     = NULL; /* I2C�豸 */
    am_rx8025t_dev_t *p_dev_rx8025t = NULL; /* rx8025t�豸 */

    /* �жϲ�������Ч�� */
    if (NULL == p_arg) {
        return;
    }

    p_dev_rx8025t = (am_rx8025t_dev_t *)p_arg;

    /*��ȡi2c_device */
    p_dev_i2c = &(p_dev_rx8025t->i2c_dev);

    switch (p_dev_rx8025t->status) {

    /* ��ȡ״̬ */
    case __RX8025T_I2C_RD_STATUS:

        p_dev_rx8025t->read_int_time_status++;

        /* ������һ״̬ */
        p_dev_rx8025t->status = __RX8025T_I2C_WR_STATUS;

        am_i2c_mktrans(&p_dev_rx8025t->trans[0],
                       p_dev_i2c->dev_addr,
                       (p_dev_i2c->dev_flags | AM_I2C_M_WR),
                       (uint8_t *)&p_dev_rx8025t->sub_addr,
                       1);

        am_i2c_mktrans(&p_dev_rx8025t->trans[1],
                       p_dev_i2c->dev_addr,
                       (p_dev_i2c->dev_flags | AM_I2C_M_RD),
                       (uint8_t *)p_dev_rx8025t->buf,
                       p_dev_rx8025t->nbytes);

        am_i2c_mkmsg(&p_dev_rx8025t->msg,
                     p_dev_rx8025t->trans,
                     2,
                     (am_pfnvoid_t)__rx8025t_i2c_read_write_fsm,
                     p_arg);

        am_i2c_msg_start(p_dev_i2c->handle, &p_dev_rx8025t->msg);
        break;

    /* ���״̬ */
    case __RX8025T_I2C_WR_STATUS:

        /* ������һ״̬ */
        p_dev_rx8025t->status = __RX8025T_I2C_DATA_PROCESSING;

        /* �������ݣ���ȡ�ж�״̬ */
        __rx8025t_read_write_data_processing(p_arg, &p_dev_rx8025t->intr_flag);

        am_i2c_mktrans(&p_dev_rx8025t->trans[0],
                       p_dev_i2c->dev_addr,
                       (p_dev_i2c->dev_flags | AM_I2C_M_WR),
                       (uint8_t *)&p_dev_rx8025t->sub_addr,
                       1);

        am_i2c_mktrans(&p_dev_rx8025t->trans[1],
                       p_dev_i2c->dev_addr,
                       (p_dev_i2c->dev_flags | AM_I2C_M_NOSTART | AM_I2C_M_WR),
                       (uint8_t *)p_dev_rx8025t->buf,
                       p_dev_rx8025t->nbytes);

        am_i2c_mkmsg(&p_dev_rx8025t->msg,
                     p_dev_rx8025t->trans,
                     2,
                     (am_pfnvoid_t)__rx8025t_i2c_read_write_fsm,
                     p_arg);

        am_i2c_msg_start(p_dev_i2c->handle, &p_dev_rx8025t->msg);
        break;

    /* ���ݴ��� */
    case __RX8025T_I2C_DATA_PROCESSING:

        /* ������һ״̬ */
        p_dev_rx8025t->status = __RX8025T_I2C_RD_STATUS;

        /* ִ���û��ж��жϻص����� */
        __rx8025t_callback_exec(p_arg, p_dev_rx8025t->intr_flag);

        if (p_dev_rx8025t->read_int_time_status == 1) {
            am_i2c_msg_start(p_dev_i2c->handle, &p_dev_rx8025t->msg);
        } else if (p_dev_rx8025t->read_int_time_status == 2){
            /* ���������ʱ�� */
            am_softimer_start(&p_dev_rx8025t->timer, 2);
        } else if (p_dev_rx8025t->read_int_time_status == 3){
            p_dev_rx8025t->read_int_time_status = 0;
            /* ����GPIO�ж� */
            am_gpio_trigger_on(p_dev_rx8025t->p_devinfo->int_pin);
        }
        break;

    default:
        break;
    }
}

/**
 * \brief RX8025T�ж�״̬��ȡ��ʱ����ص�����
 */
static void __softimer_cb (void *p_arg)
{
    am_rx8025t_dev_t *p_dev = (am_rx8025t_dev_t *)p_arg;

    am_softimer_stop(&p_dev->timer);
    __rx8025t_i2c_read_write_fsm(p_arg);
}


/**
 * \brief RX8025T ����INTA�жϻص�����
 * \param[in] p_arg : �жϻص���������
 * \return ��
 */
static void __rx8025t_eint_isr (void *p_arg)
{
    am_rx8025t_dev_t *p_dev = (am_rx8025t_dev_t *)p_arg;

    if (NULL == p_arg) {
        return;
    }

    /* �ر�GPIO�ж� */
    am_gpio_trigger_off(p_dev->p_devinfo->int_pin);

    if (p_dev->status == __RX8025T_I2C_RD_STATUS) {
        /* ������д״̬�� */
         __rx8025t_i2c_read_write_fsm(p_arg);
    }
}

/*****************************************************************************
 * �ⲿ����ʵ��
 ****************************************************************************/

/*
 *������д��RAM��
 */
int am_rx8025t_ram_write (am_rx8025t_handle_t handle, uint8_t data)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf = data;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
    		           __RX8025T_REG_RAM,
                       &buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/*
 * ��RAM�����ݶ�����
 */
int am_rx8025t_ram_read (am_rx8025t_handle_t handle, uint8_t *pbuf)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ���豸�ṹ���л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ����I2C�������� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_RAM,
                      pbuf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief �����λRX8025T
 */
int am_rx8025t_software_reset (am_rx8025t_handle_t handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[1] = {0x01};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = &(handle->i2c_dev);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_CONTROL,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief RX8025T �豸��ʼ��
 */
am_rx8025t_handle_t am_rx8025t_init (am_rx8025t_dev_t           *p_dev,
                                     const am_rx8025t_devinfo_t *p_devinfo,
                                     am_i2c_handle_t             i2c_handle)
{
    /* �������÷���ֵ */
    int ret = AM_OK;
    int i;

    /* ��֤������Ч�� */
    if (NULL == p_dev || NULL == i2c_handle || NULL == p_devinfo) {
        return NULL;
    }

    /* ����i2c�豸 */
    am_i2c_mkdev(&(p_dev->i2c_dev),
                 i2c_handle,
                 __RX8025T_ADDR,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    /* ��ʼ���豸��Ϣ */
    p_dev->conn_stat = AM_FALSE;
    p_dev->p_devinfo = p_devinfo;

    for (i = 0; i < 3; i++) {
        p_dev->triginfo[i].pfn_callback = NULL;
        p_dev->triginfo[i].p_arg        = NULL;
    }
    p_dev->status   = __RX8025T_I2C_RD_STATUS;      /* ��ʼ״̬ */
    p_dev->sub_addr = __RX8025T_REG_FLAG;       /* �������ļĴ�����ַ */
    p_dev->nbytes   = 1;                             /* ��Ҫ��ȡ�����ݸ��� */

    /* ��ʼ��RX8025T�豸 */
    ret = am_rx8025t_software_reset(p_dev);

    /* ��ʼ�������ʱ�� */
    am_softimer_init(&p_dev->timer, __softimer_cb, (void *)p_dev);

    p_dev->read_int_time_status = 0;

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
 * \brief RX8025T �豸���ʼ��
 */
void am_rx8025t_deinit (am_rx8025t_handle_t handle)
{

}

/**
 * \brief ��ȡRX8025T RTC��׼����
 */
am_rtc_handle_t am_rx8025t_rtc_init (am_rx8025t_handle_t  handle,
                                     am_rtc_serv_t       *p_rtc)
{
    p_rtc->p_drv   = handle;
    p_rtc->p_funcs = &__g_rtc_drv_funcs;
    return p_rtc;
}

/**
 * \brief ��ȡRX8025T ALARM_CLK��׼����
 */
am_alarm_clk_handle_t am_rx8025t_alarm_clk_init (am_rx8025t_handle_t   handle,
		                                         am_alarm_clk_serv_t  *p_alarm_clk)
{
	p_alarm_clk->p_drv   = handle;
	p_alarm_clk->p_funcs = &__g_alarm_clk_drv_funcs;
    return p_alarm_clk;
}

/**
 * \brief ��  �����жϡ���ʱ�жϡ������ж� ʹ��
 */
int am_rx8025t_int_enable (am_rx8025t_handle_t handle, uint8_t int_select)
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
                      __RX8025T_REG_CONTROL,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �ж�ʹ�� */
    buf[0] |= int_select;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
    		           __RX8025T_REG_CONTROL,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}

/**
 * \brief ��  �����жϡ���ʱ�жϡ������ж� ʧ��
 */
int am_rx8025t_int_disable (am_rx8025t_handle_t handle, uint8_t int_select)
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
                      __RX8025T_REG_CONTROL,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �ж�ʧ�� */
    buf[0] &= ~int_select;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_CONTROL,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}
/*
 *  ʹ�ܶ�ʱ��
 */
int am_rx8025t_timer_enable(am_rx8025t_handle_t  handle)
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
                      __RX8025T_REG_EXTENSION,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ʹ�� */
    buf[0] |= __RX8025T_TE_TIMER_ENABLE;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_EXTENSION,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}

/*
 *  ʧ�ܶ�ʱ��
 */
int am_rx8025t_timer_disable(am_rx8025t_handle_t  handle)
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
                      __RX8025T_REG_EXTENSION,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ʹ�� */
    buf[0] &= ~__RX8025T_TE_TIMER_ENABLE;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_EXTENSION,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}

/*
 * ���ö�ʱ��
 */
int am_rx8025t_timer_set (am_rx8025t_handle_t  handle, uint16_t count, uint8_t timer_clk)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t timer_buf[2]     = {0};
    uint8_t tsel_buf[1]      = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }
    if (count > 4095) {
        return -AM_EINVAL;
    }

    /* ��handle�л�ȡi2c�豸ָ�� */
    p_i2c_dev = &(handle->i2c_dev);

    /* ����count��ֵ */
    timer_buf[0] = (uint8_t)count;
    timer_buf[1] = (uint8_t)(count >> 8);
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_TIMER_COUNTER0,
                       timer_buf,
                       2);
    if (AM_OK != ret) {
        return ret;
    }

    /* ���ö�ʱ����ʱ�� timer_clk */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_EXTENSION,
                      tsel_buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    tsel_buf[0] &= 0xfc;         /* ������λ���� */
    tsel_buf[0] |= timer_clk;

    /* �������ж���Ϣд�����״̬�Ĵ���1 */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_EXTENSION,
                       tsel_buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ʹ�ܶ�ʱ�� */
    ret = am_rx8025t_timer_enable(handle);
    if (AM_OK != ret) {
        return ret;
    }

    /* ������ʱ���ж� */
    ret = am_rx8025t_int_enable(handle,AM_RX8025T_BF_TIE);
    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}
/*
 * ��ʱ���ص������趨
 */
int am_rx8025t_timer_cb_set( am_rx8025t_handle_t  handle,
                             am_pfnvoid_t         pfn_timer_callback,
                             void                *p_timer_arg)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* �豸��Ϣָ�� */
    const am_rx8025t_devinfo_t *p_devinfo = NULL;

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
                                      __rx8025t_eint_isr,
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
    handle->triginfo[1].pfn_callback = pfn_timer_callback;
    handle->triginfo[1].p_arg        = p_timer_arg;

    /* ������еĻص�������Ϊ�� */
    if ((handle->triginfo[0].pfn_callback == NULL) &&
        (handle->triginfo[1].pfn_callback == NULL) &&
        (handle->triginfo[2].pfn_callback == NULL)) {

        /* ���conn_statΪTRUE�����GPIO������Ӻ��� */
        if (handle->conn_stat) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->int_pin,
                                             __rx8025t_eint_isr,
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

/*
 * ʱ����´����жϹ�������
 */
int am_rx8025t_time_update_set( am_rx8025t_handle_t  handle, uint8_t mode)
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

    /* ��ȡ�Ĵ��� */
    ret = am_i2c_read(p_i2c_dev,
    		          __RX8025T_REG_EXTENSION,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ѡ�� */
    if ( mode == AM_RX8025T_USEL_PER_MIN) {
        buf[0] |= __RX8025T_USEL_MIN_UPDATE;
    } else {
        buf[0] &= ~__RX8025T_USEL_MIN_UPDATE;
    }


    /* ����Ϣд��̬�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_EXTENSION,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    /* ʹ��ʱ������ж� */
    ret = am_rx8025t_int_enable(handle,AM_RX8025T_BF_UIE);
    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}
/*
 * �����жϻص���������
 */
int am_rx8025t_update_int_cb_set( am_rx8025t_handle_t  handle,
                                  am_pfnvoid_t         pfn_update_int_callback,
                                  void                *p_update_int_arg)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* �豸��Ϣָ�� */
    const am_rx8025t_devinfo_t *p_devinfo = NULL;

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
                                      __rx8025t_eint_isr,
                                      handle);
        if (AM_OK != ret) {
            return ret;
        }

        /* ����Ϊ�½��ش��� */
        am_gpio_trigger_cfg(p_devinfo->int_pin, AM_GPIO_TRIGGER_LOW);
        am_gpio_trigger_on(p_devinfo->int_pin);

        /* ����conn_stat״̬ΪTRUE */
        handle->conn_stat = AM_TRUE;

    }

    /* �����жϻص����� */
    handle->triginfo[0].pfn_callback = pfn_update_int_callback;
    handle->triginfo[0].p_arg        = p_update_int_arg;

    /* ������еĻص�������Ϊ�� */
    if ((handle->triginfo[0].pfn_callback == NULL) &&
        (handle->triginfo[0].pfn_callback == NULL) &&
        (handle->triginfo[1].pfn_callback == NULL)) {

        /* ���conn_statΪTRUE�����GPIO������Ӻ��� */
        if (handle->conn_stat) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->int_pin,
                                             __rx8025t_eint_isr,
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
 * \brief RX8025T ���ӻص�����������ʱ������
 */
int am_rx8025t_alarm_set(am_rx8025t_handle_t      handle,
                         am_rx8025t_alarm_info_t *p_alarm_info,
                         am_pfnvoid_t             pfn_alarm_callback,
                         void                    *p_alarm_arg)
{
    /* �������÷���ֵ */
    int ret = AM_OK;

    /* ���ݻ����� */
    uint8_t buf[3]      = {0};
    uint8_t wada_buf[1] = {0};

    /* I2C�豸ָ�� */
    am_i2c_device_t *p_i2c_dev = NULL;

    /* �豸��Ϣָ�� */
    const am_rx8025t_devinfo_t *p_devinfo = NULL;

    /* �����������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_devinfo = handle->p_devinfo;
    p_i2c_dev = &(handle->i2c_dev);

    if (-1 == p_devinfo->int_pin) {
        return -AM_ENOTSUP;
    }

    /* conn_stat���ڼ�¼��ǰ�ж�����״̬,�����ظ�����GPIO���Ӻ��� */
    if (!(handle->conn_stat)) {

        /* ���������жϻص����� */
        ret = am_gpio_trigger_connect(p_devinfo->int_pin,
                                      __rx8025t_eint_isr,
                                      handle);
        if (AM_OK != ret) {
            return ret;
        }

        /* ����Ϊ�½��ش��� */
        am_gpio_trigger_cfg(p_devinfo->int_pin, AM_GPIO_TRIGGER_FALL);
        am_gpio_trigger_on(p_devinfo->int_pin);

        /* ����conn_stat_inta״̬ΪTRUE */
        handle->conn_stat = AM_TRUE;

    }

    /* �����жϻص����� */
    handle->triginfo[2].pfn_callback = pfn_alarm_callback;
    handle->triginfo[2].p_arg        = p_alarm_arg;

    /* ������еĻص�������Ϊ�� */
    if ((handle->triginfo[0].pfn_callback == NULL) &&
    	(handle->triginfo[1].pfn_callback == NULL) &&
        (handle->triginfo[2].pfn_callback == NULL)) {

        /* ���conn_statΪTRUE�����GPIO������Ӻ��� */
        if (handle->conn_stat) {

            /* ɾ�������жϻص����� */
            ret = am_gpio_trigger_disconnect(p_devinfo->int_pin,
            	                        	 __rx8025t_eint_isr,
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

    /* ��ȡ�Ĵ��� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_EXTENSION,
                      wada_buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    /* �����ж�ѡ�� */
    if ( p_alarm_info->alarm_mode == AM_RX8025T_ALARM_DAY) {
    	wada_buf[0] |= __RX8025T_WADA_ALARM_DAY;
    } else {
    	wada_buf[0] &= ~__RX8025T_WADA_ALARM_DAY;
    }

    /* ����Ϣд��̬�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_EXTENSION,
                       wada_buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    buf[__RX8025T_REG_MINUTES_ALARM  - __RX8025T_REG_MINUTES_ALARM] = AM_HEX_TO_BCD(p_alarm_info->min);
    buf[__RX8025T_REG_HOURS_ALARM    - __RX8025T_REG_MINUTES_ALARM] = AM_HEX_TO_BCD(p_alarm_info->hour);
    if( p_alarm_info->alarm_mode == AM_RX8025T_ALARM_DAY) {
        buf[__RX8025T_REG_WEEK_DAY_ALARM - __RX8025T_REG_MINUTES_ALARM] = AM_HEX_TO_BCD(p_alarm_info->week_day);
    } else {
        buf[__RX8025T_REG_WEEK_DAY_ALARM - __RX8025T_REG_MINUTES_ALARM] = p_alarm_info->week_day;
    }

    /* ����I2C�������� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_MINUTES_ALARM,
                       buf,
                       sizeof(buf));

    if (AM_OK != ret) {
        return -AM_EINVAL;
    }
    /* ʹ��ALARM����*/
    ret = am_rx8025t_int_enable( handle, AM_RX8025T_BF_AIE);
    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 * \brief �¶Ȳ���ʱ����
 */
int am_rx8025t_temperature_offset(am_rx8025t_handle_t handle,uint8_t offset_mode)
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

    /* ��ȡ�Ĵ��� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_EXTENSION,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    buf[0] &= 0x3f;         /* ������λ���� */
    buf[0] |= offset_mode << 6;

    /* ����Ϣд��̬�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_CONTROL,
                       buf,
                       1);

    if (AM_OK != ret) {
        return ret;
    }

    return AM_OK;
}

/**
 *  \brief clkout ���ʱ��Ƶ�ʵ�����
 */
int am_rx8025t_clkout_set(am_rx8025t_handle_t handle, uint8_t frequency)
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

    /* ��ȡ�Ĵ��� */
    ret = am_i2c_read(p_i2c_dev,
                      __RX8025T_REG_EXTENSION,
                      buf,
                      1);

    if (AM_OK != ret) {
        return ret;
    }

    buf[0] &= 0xf3;         /* �� bit3 �� bit2 ��λ���� */
    buf[0] |= frequency << 2;

    /* ����Ϣд��̬�Ĵ��� */
    ret = am_i2c_write(p_i2c_dev,
                       __RX8025T_REG_EXTENSION,
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
int am_rx8025t_clkout_close(am_rx8025t_handle_t handle)
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

