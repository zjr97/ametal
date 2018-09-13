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
 * \brief DS1302�����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.01 18-03-13  vir, get time by BURST MODE.
 * - 1.00 17-08-11  fra, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_spi.h"
#include "am_ds1302.h"


/*****************************************************************************
 * �궨��
 ****************************************************************************/

/*
 * \brief �Ĵ�����ַ
 */
#define __DS1302_REG_SECOND_WD               0X80
#define __DS1302_REG_SECOND_RD               0X81
#define __DS1302_REG_MIN_WD                  0X82
#define __DS1302_REG_MIN_RD                  0X83
#define __DS1302_REG_HR_WD                   0X84
#define __DS1302_REG_HR_RD                   0X85
#define __DS1302_REG_DATE_WD                 0X86
#define __DS1302_REG_DATE_RD                 0X87
#define __DS1302_REG_MONTH_WD                0X88
#define __DS1302_REG_MONTH_RD                0X89
#define __DS1302_REG_DAY_WD                  0X8A
#define __DS1302_REG_DAY_RD                  0X8B
#define __DS1302_REG_YEAR_WD                 0X8C
#define __DS1302_REG_YEAR_RD                 0X8D
#define __DS1302_REG_CONTROL_WD              0X8E
#define __DS1302_REG_CONTROL_RD              0X8F
#define __DS1302_REG_TRICKLE_WR              0X90
#define __DS1302_REG_TRICKLE_RD              0X91

#define __DS1302_REG_RAM_WD                  0XC0
#define __DS1302_REG_RAM_RD                  0XC1

#define __DS1302_REG_CLOCK_BURST_WD          0XBE
#define __DS1302_REG_CLOCK_BURST_RD          0XBF

/**
 * \brief �����궨��
 */
#define __DS1302_YEAR_OFFS    100

/*****************************************************************************
 * DS1302�����������Ͷ���
 ****************************************************************************/

/**
 * \brief DS1302��������
 */
struct __am_ds1302_drv_funcs {

    int  (*pfn_ds1302_write)(void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes);

    int  (*pfn_ds1302_read) (void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes);
};


/*****************************************************************************
 * ��̬����
 ****************************************************************************/

/* RTC driver function implementation */
static int __ds1302_time_set (void *p_drv, am_tm_t *p_tm);
static int __ds1302_time_get (void *p_drv, am_tm_t *p_tm);

/* DS1302 SPI������������*/
static int __ds1302_spi_write(void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes);
static int __ds1302_spi_read (void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes);

/* DS1302 GPIO������������*/
static int __ds1302_gpio_write(void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes);
static int __ds1302_gpio_read(void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes);

/**
 * \brief RTC driver functions definition
 */
static struct am_rtc_drv_funcs __g_rtc_drv_funcs = {
    __ds1302_time_set,
    __ds1302_time_get
};

/**
 * \brief DS1302 SPI��ʽ������������
 */
static struct __am_ds1302_drv_funcs __g_ds1302_spi_drv_funcs = {
    __ds1302_spi_write,
    __ds1302_spi_read
};

/**
 * \brief DS1302 gpio��ʽ������������
 */
static struct __am_ds1302_drv_funcs __g_ds1302_gpio_drv_funcs = {
    __ds1302_gpio_write,
    __ds1302_gpio_read
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
static uint8_t __ds1302_leap_year_check (uint16_t year)
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
static uint8_t __ds1302_day_of_year (uint16_t year, uint8_t month, uint8_t day)
{
    uint8_t i;

    if (__ds1302_leap_year_check(year)) {
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
static int __ds1302_time_validator (am_tm_t *p_tm)
{
    if (p_tm->tm_year > 199 || p_tm->tm_year < 0 ||
        p_tm->tm_mon > 11   || p_tm->tm_mon < 0 ||
        p_tm->tm_mday >
        __mdays[__ds1302_leap_year_check(1900 + p_tm->tm_year)][p_tm->tm_mon] ||
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
 * \brief DS1302�豸дһ���ֽ�
 *
 * \param[in] p_dev : ָ��DS1302�豸�ṹ��
 * \param[in] data  : д���һ�ֽ�����
 *
 * \return AM_OK��ʾ��ʼ���ɹ�, ����ʧ��
 */
static int __ds1302_write_byte (am_ds1302_gpio_dev_t *p_dev, uint8_t data)
{
    uint8_t i = 0;

    /* �����ж� */
    if (NULL == p_dev){
        return AM_ERROR;
    }

    /* ����ʱ�� */
    am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 0);
    am_udelay(2);
    for (i = 0; i < 8; i++) {
        am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 0);
        if ((data & 0x01) == 1) {
            am_gpio_set(p_dev->p_gpio_devinfo->io_pin, 1);
        } else {
            am_gpio_set(p_dev->p_gpio_devinfo->io_pin, 0);
        }
        am_udelay(2);
        am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 1);
        am_udelay(2);
        data >>= 1;
    }

    return AM_OK;
}


/**
 * \brief DS1302�豸��һ���ֽ�
 *
 * \param[in] p_dev   :  ָ��DS1302�豸�ṹ��
 *
 * \return    ret_val :  ���ض�����ֵ
 */
static uint8_t __ds1302_read_byte (am_ds1302_gpio_dev_t *p_dev)
{
    uint8_t  i = 0;
    uint8_t ret_val = 0;
    uint8_t get_val = 0;

    am_udelay(2);
    for (i = 0; i < 8; i++) {
        am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 0);
        ret_val >>= 1;
        get_val = am_gpio_get(p_dev->p_gpio_devinfo->io_pin);
        if (get_val == 1){
            ret_val |= 0x80;
        }
        am_udelay(2);
        am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 1);
        am_udelay(2);
    }

    return ret_val;
}

/**
 * \brief DS1302�豸д����, GPIOģʽ
 *
 * \param[in] p_dev : ָ��DS1302�豸�ṹ��
 * \param[in] data  : д���һ�ֽ�����
 * \param[in] addr  : д��ĵ�ַ
 *
 * \return AM_OK��ʾ��ʼ���ɹ�, ����ʧ��
 */
static int __ds1302_gpio_write(void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes)
{
    int i = 0;
    am_ds1302_gpio_dev_t * p_dev = (am_ds1302_gpio_dev_t *)p_drv;

    /* �����ж� */
    if (NULL == p_dev){
        return AM_ERROR;
    }
    /* ��ֹ���� */
    am_gpio_set(p_dev->p_gpio_devinfo->ce_pin, 0);

    /* ����ʱ�� */
    am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 0);

    /* ����ce����ʼ��������*/
    am_gpio_set(p_dev->p_gpio_devinfo->ce_pin, 1);

    am_udelay(2);

    /* ��IO����Ϊ��� */
    am_gpio_pin_cfg(p_dev->p_gpio_devinfo->io_pin, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_LOW);

    __ds1302_write_byte(p_dev, addr);

    for ( i = 0; i < nbytes; i++ ) {
        __ds1302_write_byte(p_dev, *p_buf++);
    }

    /* ����ʱ�� */
    am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 0);

    /* ��ֹ���� */
    am_gpio_set(p_dev->p_gpio_devinfo->ce_pin, 0);

    return AM_OK;
}

/**
 * \brief DS1302�豸д����,SPIģʽ
 *
 * \param[in] p_dev : ָ��DS1302�豸�ṹ��
 * \param[in] data  : д���һ�ֽ�����
 * \param[in] addr  : д��ĵ�ַ
 *
 * \return AM_OK��ʾ��ʼ���ɹ�, ����ʧ��
 */
static int __ds1302_spi_write(void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes)
{

    am_ds1302_spi_dev_t * p_dev = (am_ds1302_spi_dev_t *)p_drv;

    uint8_t com = addr;

    /* д���ַ������ */
    return am_spi_write_then_write(&p_dev->spi_dev, &com,1, p_buf, nbytes);
}


/**
 * \brief DS1302�豸��������GPIOģʽ
 *
 * \param[in] p_dev : ָ��DS1302�豸�ṹ��
 * \param[in] addr  : �����ݵĵ�ַ
 *
 * \return AM_OK��ʾ��ʼ���ɹ�, ����ʧ��
 */
static int __ds1302_gpio_read(void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes)
{
    int i = 0;
    am_ds1302_gpio_dev_t * p_dev = (am_ds1302_gpio_dev_t *)p_drv;

    /* ��ֹ���� */
    am_gpio_set(p_dev->p_gpio_devinfo->ce_pin, 0);

    /* ����ʱ�� */
    am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 0);

    /* ����ce����ʼ��������*/
    am_gpio_set(p_dev->p_gpio_devinfo->ce_pin, 1);

    /* ��IO����Ϊ��� */
    am_gpio_pin_cfg(p_dev->p_gpio_devinfo->io_pin, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_LOW);

    /* д���ַ */
    __ds1302_write_byte(p_dev, addr);

    /* ��IO����Ϊ���� */
    am_gpio_pin_cfg(p_dev->p_gpio_devinfo->io_pin, AM_GPIO_PULLUP | AM_GPIO_INPUT);

    /* �������� */
    for ( i = 0; i < nbytes; i++) {
        *p_buf++= __ds1302_read_byte(p_dev);
    }

    /* ����ʱ�� */
    am_gpio_set(p_dev->p_gpio_devinfo->sclk_pin, 0);

    /* ��ֹ���� */
    am_gpio_set(p_dev->p_gpio_devinfo->ce_pin, 0);

    return AM_OK;
}

/**
 * \brief DS1302�豸��������SPIģʽ
 *
 * \param[in] p_dev  : ָ��DS1302�豸�ṹ��
 * \param[in] addr   : �����ݵĵ�ַ
 *
 * \return   ret_val : ������ֵ
 */
static int __ds1302_spi_read(void *p_drv, uint8_t addr, uint8_t *p_buf, size_t nbytes)
{

    am_ds1302_spi_dev_t * p_dev = (am_ds1302_spi_dev_t *)p_drv;

    uint8_t com = addr;

    /* �ȷ���ַ�ڷ����� */
    return am_spi_write_then_read(&(p_dev->spi_dev), &com, 1, p_buf, nbytes);
}

/**
 * \brief DS1302�豸��ʼ��
 *
 * \param[in] p_dev : ָ��DS1302�豸�ṹ��
 *
 * \return AM_OK��ʾ��ʼ���ɹ�, ����ʧ��
 */
static int __ds1302_init (am_ds1302_dev_t *p_dev)
{
    uint8_t data = 0;
    struct __am_ds1302_drv_funcs *p_funcs = (struct __am_ds1302_drv_funcs *)(p_dev->pfn);

    /* �����ж� */
    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    data = 0x00;

    /* ��ֹд���� */
    p_funcs->pfn_ds1302_write(p_dev->p_drv, __DS1302_REG_CONTROL_WD, &data,1);

    /* ����ʱ�� */
    p_funcs->pfn_ds1302_write(p_dev->p_drv, __DS1302_REG_SECOND_WD, &data, 1);

    /* ѡ��24Сʱ�� */
    p_funcs->pfn_ds1302_write(p_dev->p_drv, __DS1302_REG_HR_WD, &data, 1);

    /* ����д���� */
    data = 0x80;
    p_funcs->pfn_ds1302_write(p_dev->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

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
static int __ds1302_time_set (void *p_drv, am_tm_t *p_tm)
{
    uint8_t data   = 0;
    uint8_t buf[8] = {0};
    int     ret    = AM_OK;
    am_ds1302_dev_t              *p_dev      = (am_ds1302_dev_t *)p_drv;
    struct __am_ds1302_drv_funcs *p_funcs    = (struct __am_ds1302_drv_funcs *)(p_dev->pfn);

    /* �жϲ�������Ч�� */
    if (NULL == p_dev || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* ��֤ʱ����Ϣ����Ч�� */
    if ((AM_OK != __ds1302_time_validator(p_tm)) ||
        (p_tm->tm_hour > 23) || (p_tm->tm_hour < 0)) {
        return -AM_EINVAL;
    }

    /* �ж�DS1302�Ƿ�ֹͣ */
    p_funcs->pfn_ds1302_read(p_dev->p_drv, __DS1302_REG_SECOND_RD, &data, 1);
    data = AM_BCD_TO_HEX(data);
    if ( data & (1 << 7) ) {
        return -AM_EINVAL;
    }

    /* ��ֹд���� */
    data = 0;
    p_funcs->pfn_ds1302_write(p_dev->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    buf[0] = AM_HEX_TO_BCD(p_tm->tm_sec);
    buf[1] = AM_HEX_TO_BCD(p_tm->tm_min);
    buf[2] = AM_HEX_TO_BCD(p_tm->tm_hour);
    buf[3] = AM_HEX_TO_BCD(p_tm->tm_mday);
    buf[4] = AM_HEX_TO_BCD(p_tm->tm_mon + 1);
    buf[5] = AM_HEX_TO_BCD(p_tm->tm_wday + 1);
    buf[6] = AM_HEX_TO_BCD((p_tm->tm_year - __DS1302_YEAR_OFFS) % 100);
    buf[7] = 0;

    /* ����ͻ��ģʽ,����д8���ֽ� */
    ret = p_funcs->pfn_ds1302_write(p_dev->p_drv, __DS1302_REG_CLOCK_BURST_WD, buf, sizeof(buf));

    /* ����д���� */
    data = 0x80;
    p_funcs->pfn_ds1302_write(p_dev->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    return ret;
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
static int __ds1302_time_get (void *p_drv, am_tm_t *p_tm)
{
    uint8_t data   = 0;
    uint8_t buf[8] ={0};
    int     ret    = AM_OK;
    am_ds1302_dev_t              *p_dev         = (am_ds1302_dev_t *)p_drv;
    struct __am_ds1302_drv_funcs *p_funcs       = (struct __am_ds1302_drv_funcs *)(p_dev->pfn);

    /* �жϲ�������Ч�� */
    if (NULL == p_drv || NULL == p_tm) {
        return -AM_EINVAL;
    }

    /* �ж�DS1302�Ƿ�ֹͣ */
    p_funcs->pfn_ds1302_read(p_dev->p_drv, __DS1302_REG_SECOND_RD, &data, 1);
    data = AM_BCD_TO_HEX(data);
    if ( data & (1 << 7) ) {
        return -AM_EINVAL;
    }

    /* ����ͻ��ģʽ,������8���ֽ� */
    ret = p_funcs->pfn_ds1302_read(p_dev->p_drv, __DS1302_REG_CLOCK_BURST_RD, buf, sizeof(buf));

    p_tm->tm_sec  = AM_BCD_TO_HEX(buf[0] & ~0X80);
    p_tm->tm_min  = AM_BCD_TO_HEX(buf[1] & ~0X80);
    p_tm->tm_hour = AM_BCD_TO_HEX(buf[2] & ~0XC0);
    p_tm->tm_mday = AM_BCD_TO_HEX(buf[3] & ~0XC0);
    p_tm->tm_mon  = AM_BCD_TO_HEX(buf[4] & 0X1F) - 1;
    p_tm->tm_wday = AM_BCD_TO_HEX(buf[5] & 0X07) - 1;
    p_tm->tm_year = AM_BCD_TO_HEX(buf[6]) + __DS1302_YEAR_OFFS;
    p_tm->tm_yday = AM_BCD_TO_HEX(__ds1302_day_of_year(p_tm->tm_year, p_tm->tm_mon, p_tm->tm_mday));


    return ret;
}


/*****************************************************************************
 * �ⲿ����ʵ��
 ****************************************************************************/

/**
 * \brief DS1302 �豸��ʼ��,SPI����
 */
am_ds1302_handle_t am_ds1302_spi_init (am_ds1302_spi_dev_t                   *p_dev,
                                       const am_ds1302_spi_devinfo_t         *p_spi_devinfo,
                                       am_spi_handle_t                        spi_handle)
{

    am_ds1302_handle_t ret_handle = NULL;

    /* ��֤������Ч�� */
    if ((p_dev == NULL) || (spi_handle == NULL)) {
        return NULL;
    }

     /* ��ʼ���豸��Ϣ */
     p_dev->p_spi_devinfo = p_spi_devinfo;

     /* ����������ֵ */
     p_dev->common.pfn = &__g_ds1302_spi_drv_funcs;

     /* ��һ����ڲ�����ֵ*/
     p_dev->common.p_drv = p_dev;

     /* ��ʼ��CS���� */
     am_gpio_pin_cfg(p_spi_devinfo->ce_pin, AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PUSH_PULL);

     am_spi_mkdev(&(p_dev->spi_dev),
                  spi_handle,
                  0,
                  AM_SPI_MODE_0 | AM_SPI_CS_HIGH | AM_SPI_LSB_FIRST |AM_SPI_3WIRE,
                  3000000,
                  p_spi_devinfo->ce_pin,
                  NULL);

     if (am_spi_setup(&(p_dev->spi_dev)) != AM_OK) {
         return NULL;
     }

     /* ��ʼ��1302�豸 */
     __ds1302_init(&(p_dev->common));

     ret_handle = &(p_dev->common);

     return ret_handle;

}


/**
 * \brief DS1302 �豸��ʼ����GPIO����
 */
am_ds1302_handle_t am_ds1302_gpio_init (am_ds1302_gpio_dev_t                   *p_dev,
                                        const am_ds1302_gpio_devinfo_t         *p_gpio_devinfo)
{
    am_ds1302_handle_t ret_handle = NULL;

    /* ��֤������Ч�� */
     if (NULL == p_dev) {
         return NULL;
     }

     /* ��ʼ���豸��Ϣ */
     p_dev->p_gpio_devinfo = p_gpio_devinfo;

     /* ����������ֵ */
     p_dev->common.pfn = &__g_ds1302_gpio_drv_funcs;

     /* ��һ����ڲ�����ֵ*/
     p_dev->common.p_drv = p_dev;

     am_gpio_pin_cfg(p_dev->p_gpio_devinfo->ce_pin, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_LOW);
     am_gpio_pin_cfg(p_dev->p_gpio_devinfo->sclk_pin, AM_GPIO_PUSH_PULL | AM_GPIO_OUTPUT_INIT_LOW);


     /* ��ʼ��1302�豸 */
     __ds1302_init(&(p_dev->common));

     ret_handle = &(p_dev->common);

     return ret_handle;
}



/**
 * \brief DS1302 �豸���ʼ��
 */
void am_ds1302_deinit (am_ds1302_handle_t handle)
{

}


/**
 * \brief ��ȡDS1302 RTC��׼����
 */
am_rtc_handle_t am_ds1302_rtc_init (am_ds1302_handle_t  handle,
                                    am_rtc_serv_t      *p_rtc)
{
    p_rtc->p_drv   = handle;
    p_rtc->p_funcs = &__g_rtc_drv_funcs;
    return p_rtc;
}



/**
 * \brief ��ֹDS1302
 */
int am_ds1302_stop (am_ds1302_handle_t handle)
{
    uint8_t data = 0;
    struct __am_ds1302_drv_funcs *p_funcs    = (struct __am_ds1302_drv_funcs *)(handle->pfn);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��ֹд���� */
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    /* ������Ĵ������е�ֵ*/

    p_funcs->pfn_ds1302_read(handle->p_drv, __DS1302_REG_SECOND_RD, &data, 1);

    /* ��д����Ĵ���*/
    data |= 0X80;
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_SECOND_WD, &data, 1);

    /* ����д���� */
    data = 0X80;
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    return AM_OK;
}

/**
 * \brief д DS1302 RAM �Ĵ���
 */
int am_ds1302_ram_write (am_ds1302_handle_t handle,
                         uint8_t           *p_data,
                         uint8_t            data_len,
                         uint8_t            position)
{
    uint8_t i       = 0;
    uint8_t regaddr = 0;
    uint8_t data    = 0;
    struct __am_ds1302_drv_funcs *p_funcs = (struct __am_ds1302_drv_funcs *)(handle->pfn);

    /* ��֤��������Ч�� */
    if (NULL == handle || NULL == p_data) {
        return -AM_EINVAL;
    }

    /* д�����ݵĴ�С��λ�ò��Ϸ�*/
    if ((data_len + position) > 31) {
        return -AM_EINVAL;
    }

    /* ������ʼ��ַ */
    regaddr = __DS1302_REG_RAM_WD + position * 2;

    /* ��ֹд���� */
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    for (i = 0; i < data_len; i++) {
        p_funcs->pfn_ds1302_write(handle->p_drv, regaddr, p_data++,1);
        regaddr += 2;
    }

    /* ����д���� */
    data = 0X80;
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);


    return AM_OK;
}

/**
 * \brief �� DS1302 RAM �Ĵ���
 */
int am_ds1302_ram_read (am_ds1302_handle_t handle,
                        uint8_t           *p_data,
                        uint8_t            data_len,
                        uint8_t            position)
{
    uint8_t i       = 0;
    uint8_t regaddr = 0;
    uint8_t data    = 0;
    struct __am_ds1302_drv_funcs *p_funcs = (struct __am_ds1302_drv_funcs *)(handle->pfn);

    /* ��֤��������Ч�� */
    if (NULL == handle || NULL == p_data) {
        return -AM_EINVAL;
    }

    /* д�����ݵĴ�С��λ�ò��Ϸ�*/
    if ((data_len + position) > 31) {
        return -AM_EINVAL;
    }

    /* ������ʼ��ַ */
    regaddr = __DS1302_REG_RAM_RD + position * 2;

    /* ��ֹд���� */
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    for (i = 0; i < data_len; i++) {
        p_funcs->pfn_ds1302_read(handle->p_drv, regaddr, p_data++, 1);
        regaddr += 2;
    }

    /* ����д���� */
    data = 0X80;
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    return AM_OK;
}

/**
 * \brief ʹ�ܳ��
 */
int am_ds1302_trickle_enable(am_ds1302_handle_t handle, uint8_t set_val)
{
    uint8_t data = 0;
    struct __am_ds1302_drv_funcs *p_funcs = (struct __am_ds1302_drv_funcs *)(handle->pfn);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��ֹд���� */
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_TRICKLE_WR, &set_val,1);

    /* ����д���� */
    data = 0X80;
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data,1);


    return AM_OK;
}

/**
 * \brief ���ܳ��
 */
int am_ds1302_trickle_disable(am_ds1302_handle_t handle)
{
    uint8_t data = 0;
    struct __am_ds1302_drv_funcs *p_funcs = (struct __am_ds1302_drv_funcs *)(handle->pfn);

    /* ��֤��������Ч�� */
    if (NULL == handle) {
        return -AM_EINVAL;
    }

    /* ��ֹд���� */
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data, 1);

    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_TRICKLE_WR, &data, 1);

    /* ����д���� */
    data = 0X80;
    p_funcs->pfn_ds1302_write(handle->p_drv, __DS1302_REG_CONTROL_WD, &data,1);

    return AM_OK;
}

/**
 * \brief ����ʱ��
 */
int am_ds1302_time_set (am_ds1302_handle_t handle, am_tm_t *p_tm)
{
    return __ds1302_time_set(handle,p_tm);
}


/**
 * \brief ��ȡʱ��
 */

int am_ds1302_time_get (am_ds1302_handle_t handle, am_tm_t *p_tm)
{
    return __ds1302_time_get(handle,p_tm);
}


/* end of file */

