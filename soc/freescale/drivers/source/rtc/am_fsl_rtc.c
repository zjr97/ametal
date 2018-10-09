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
 * \brief RTC ģ���������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_fsl_rtc.h"

#ifdef USE_TIME_LIB
#include <time.h>
#include <string.h>
#endif /* USE_TIME_LIB */

/** ƽ��ÿ�µ���ʼ���� */
static const uint32_t __non_leap_year[] =
{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

/** ����ÿ�µ���ʼ���� */
static const uint32_t __leap_year[] =
{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};


/** \brief ʱ���ȡ���� */
static int __fsl_rtc_time_get (void *p_drv, am_tm_t *p_tm);

/** \brief ʱ�����ú��� */
static int __fsl_rtc_time_set (void *p_drv, am_tm_t *p_tm);

/** \brief RTC �������� */
static const struct am_rtc_drv_funcs __g_rtc_drv_funcs = {
    __fsl_rtc_time_set,
    __fsl_rtc_time_get,
};

/**
 *  \brief ��ת��Ϊtmʱ������
 *
 *  \param p_time ָ��tmʱ�����ݵ�ָ��
 *  \param  seconds ������
 *  \return ��
 */
#ifdef USE_TIME_LIB
static void __sec2tm (am_tm_t *p_time, uint32_t sec)
{
    time_t     second = sec;
    struct tm *p_tm   = NULL;

    p_tm = localtime(&second);

    if ((NULL != p_time) && (NULL != p_tm)) {
        memcpy(p_time, p_tm, sizeof(am_tm_t));
    }
}
#else

/* һ����ÿ���µ������������� */
const char __days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static int __week_get (int year, int month, int day)
{
    day++;
    month++;
    year += 1900;

    /* �����һ�»���½��л��� */
    if ((month == 1) || (month == 2)) {
        month += 12;
        year--;
    }

    /* �õ������ڼ������� */
    return (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 -
            year / 100 + year / 400) % 7;
}

static void __sec2tm (am_tm_t *p_time, uint32_t sec)
{
    uint32_t four_year_pass;
    int32_t  hour_num;

    if (NULL == p_time) {
        return;
    }

    p_time->tm_isdst = 0;

    /* ȡ��ʱ�� */
    p_time->tm_sec = (int)(sec % 60);
    sec /= 60;

    /* ȡ����ʱ�� */
    p_time->tm_min = (int)(sec % 60);
    sec /= 60;

    /* ȡ��ȥ���ٸ����꣬ÿ������ 1461*24 Сʱ */
    four_year_pass = ((uint32_t)sec / (1461L * 24L));

    /* ������� */
    p_time->tm_year = (four_year_pass << 2) + 70;

    /* ������ʣ�µ�Сʱ�� */
    sec %= 1461L * 24L;

    /* У������Ӱ�����ݣ�����һ����ʣ�µ�Сʱ�� */
    for (;;) {

        /* һ���Сʱ�� */
        hour_num = 365 * 24;

        /* �ж����� */
        if ((p_time->tm_year & 3) == 0) {

            /* �����꣬һ�����24Сʱ����һ�� */
            hour_num += 24;
        }
        if (sec < hour_num) {
            break;
        }
        p_time->tm_year++;
        sec -= hour_num;
    }

    /* Сʱ�� */
    p_time->tm_hour = (int)(sec % 24);

    /* һ����ʣ�µ����� */
    sec /= 24;

    /* �ٶ�Ϊ���� */
    sec++;

    p_time->tm_yday = sec - 1;

    /* У��������������·ݣ����� */
    if ((p_time->tm_year & 3) == 0) {
        if (sec > 60) {
            sec--;
            p_time->tm_yday = sec;
        } else {
            if (sec == 60) {
                p_time->tm_mon = 1;
                p_time->tm_mday = 29;

                /* �������� */
                p_time->tm_wday = __week_get(p_time->tm_year, p_time->tm_mon, p_time->tm_mday);
                return;
            }
        }
    }

    /* �������� */
    for (p_time->tm_mon = 0; __days[p_time->tm_mon] < sec; p_time->tm_mon++) {
        sec -= __days[p_time->tm_mon];
    }

    p_time->tm_mday = (int)(sec);

    /* �������� */
    p_time->tm_wday = __week_get(p_time->tm_year, p_time->tm_mon, p_time->tm_mday);
}
#endif /* USE_TIME_LIB */

/**
 *  \brief tmʱ������ת��Ϊ��
 *
 *  \param p_time ָ��tmʱ�����ݵ�ָ��
 *
 *  \return ������
 *
 *  \note ʱ���Ǵ�1900�꿪ʼ��
 */
#ifdef USE_TIME_LIB
static uint32_t __tm2sec (am_tm_t *p_time)
{
    time_t time = 0;

    if (NULL != p_time) {
        time = mktime((struct tm*)p_time);
    }

    return (uint32_t)((time != -1) ? time : 0);
}
#else
static uint32_t __tm2sec (am_tm_t *p_time)
{
    unsigned int mon  = p_time->tm_mon + 1;
    unsigned int year = p_time->tm_year + 1900;

    if (NULL == p_time) {
        return 0;
    }

    /* 1..12 -> 11,12,1..10 */
    if (0 >= (int) (mon -= 2)) {
        mon += 12;                  /* Puts Feb last since it has leap day */
        year -= 1;
    }

    return ((((uint32_t)
            (year / 4 - year / 100 + year / 400 + 367 * mon / 12 + p_time->tm_mday) +
            year * 365 - 719499) *
            24 + p_time->tm_hour) * /* now have hours */
            60 + p_time->tm_min) *  /* now have minutes */
            60 + p_time->tm_sec;    /* finally seconds */
}
#endif /* USE_TIME_LIB */

/**
 *  \brief Brief
 *
 *  \param[in] p_drv ָ��RTC�豸��ָ��
 *  \param[in,out] p_tm ָ��ʱ����Ϣ�ṹ���ָ��
 *
 *  \return AM_OK
 */
static int __fsl_rtc_time_get (void *p_drv, am_tm_t *p_tm)
{
    uint32_t sec;
    am_fsl_rtc_dev_t *p_dev   = (am_fsl_rtc_dev_t *)p_drv;
    sec                       = amhw_fsl_rtc_second_get(p_dev->p_devinfo->p_hw_rtc);
    __sec2tm(p_tm, sec);
    return AM_OK;
}

static int __fsl_rtc_time_set (void *p_drv, am_tm_t *p_tm)
{
    uint32_t sec;

    am_fsl_rtc_dev_t *p_dev   = (am_fsl_rtc_dev_t *)p_drv;
    amhw_fsl_rtc_t *p_hw_rtc  = p_dev->p_devinfo->p_hw_rtc;
    sec                       = __tm2sec(p_tm);

    /** �رռ����� */
    amhw_fsl_rtc_time_counter_status_clr(p_hw_rtc);

    /** ����Ԥ��Ƶ������ */
    amhw_fsl_rtc_prescaler_set(p_hw_rtc, 0x00);

    /** ����������� */
    amhw_fsl_rtc_second_set(p_hw_rtc, sec);

    /** ���������� */
    amhw_fsl_rtc_time_counter_status_set(p_hw_rtc);

    return AM_OK;
}


/**
 * \brief ��ʼ��RTC
 *
 * \param[in] p_dev     : ָ��RTC�豸
 * \param[in] p_devinfo : ָ��RTC�豸��Ϣ
 *
 * \return RTC��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_rtc_handle_t am_fsl_rtc_init (am_fsl_rtc_dev_t           *p_dev,
                                 const am_fsl_rtc_devinfo_t *p_devinfo)
{
    amhw_fsl_rtc_t *p_hw_rtc;

    if (NULL == p_dev || NULL == p_devinfo ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_hw_rtc                = p_devinfo->p_hw_rtc;
    p_dev->p_devinfo        = p_devinfo;
    p_dev->rtc_serv.p_funcs = (struct am_rtc_drv_funcs *)&__g_rtc_drv_funcs;
    p_dev->rtc_serv.p_drv   = p_dev;

    /**
     *  �豸��ʼ��
     */

    /* ����������δʹ�ܡ��������Чʱ�ų�ʼ�� */
    if ((0 == amhw_fsl_rtc_time_counter_status_get(p_hw_rtc)) ||
        (0 != amhw_fsl_rtc_count_over_status_get(p_hw_rtc))   ||
        (0 != amhw_fsl_rtc_is_time_invalid(p_hw_rtc))) {

        /* �ر�������� */
        amhw_fsl_rtc_time_counter_status_clr(p_hw_rtc);

        /* �����������Ч������������Ƶ��������������� */
        if (amhw_fsl_rtc_is_time_invalid(p_hw_rtc) ||
            amhw_fsl_rtc_count_over_status_get(p_hw_rtc)) {

            amhw_fsl_rtc_prescaler_set(p_hw_rtc, 0x00);
            amhw_fsl_rtc_second_set(p_hw_rtc, 0x00);
        }

        /* У׼�Ĵ�����0 */
        amhw_fsl_rtc_alarm_set(p_hw_rtc, 0x00);
        amhw_fsl_rtc_compensate_interval_set(p_hw_rtc, 0x00);
        amhw_fsl_rtc_compensate_value_set(p_hw_rtc, 0x00);
        amhw_fsl_rtc_current_compensate_counter_set(p_hw_rtc, 0x00);
        amhw_fsl_rtc_current_compensate_value_set(p_hw_rtc, 0x00);

        /** ʹ��������� */
        amhw_fsl_rtc_time_counter_status_set(p_hw_rtc);
    }

    return &(p_dev->rtc_serv);
}

/**
 *  \brief ���RTC��ʼ��
 *
 *  \param p_dev ָ��RTC�豸��ָ��
 *
 *  \return ��
 */
void am_fsl_rtc_deinit (am_rtc_handle_t handle)
{

    am_fsl_rtc_dev_t *p_dev = (am_fsl_rtc_dev_t *)handle;

    if (p_dev == NULL || p_dev->p_devinfo == NULL ) {
        return ;
    }

    amhw_fsl_rtc_time_counter_status_clr(p_dev->p_devinfo->p_hw_rtc);

    p_dev->p_devinfo        = NULL;
    p_dev->rtc_serv.p_funcs = NULL;
    p_dev->rtc_serv.p_drv   = NULL;
    p_dev                   = NULL;

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/**
 *  \brief ����RTC��У׼����
 *
 *  \param p_dev ָ��RTC�豸��ָ��
 *
 *  \param frq RTCʱ�ӵ�ʵ��Ƶ�ʣ���Hz��
 *
 *  \return ʵ��У׼���Ƶ��
 */
int am_fsl_rtc_compensation_set (am_fsl_rtc_dev_t *p_dev, float frq)
{
    int i, j;             /** ѭ������         */
    int m, n;             /** ���������ݴ�     */
    float err_aim;        /** Ŀ��ƫ��         */
    float err, err_pre;   /** ������ľ���ƫ�� */
    amhw_fsl_rtc_t *p_hw_rtc;
    p_hw_rtc = p_dev->p_devinfo->p_hw_rtc;

    if (NULL == p_dev) {
        return -AM_EINVAL;
    }

    err_aim = 32768.0f - frq;
    err_pre = err = err_aim > 0 ? err_aim : -err_aim;

    /** ������������ */
    if (frq < (32768 - 127)) {
        m = -127;
        n = 1;
        amhw_fsl_rtc_current_interval_and_value_set(p_hw_rtc, n - 1, m);
        return (32768.0f * frq) / (32768.0f - m * 1.0);
    }

    /** ������������ */
    else if (frq > (32768 + 128)) {
        m = 128;
        n = 1;
        amhw_fsl_rtc_current_interval_and_value_set(p_hw_rtc, n - 1, m);
        return (32768.0f * frq) / (32768.0f - m * 1.0);
    }

    /** ǡ�������� */
    else if (0 == (frq - (int)frq)) {
        m = 32768 - frq;
        n = 1;
    }

    /** С������ */
    else {
        m = (int)err_aim;
        n = 1;

        for (j = 1; j < 256; j ++) {

            /** �ӿ� */
            if (err_aim > 0) {
                for (i = (int)err_aim * j;
                     (i < 128) && (i < (int)(err_aim + 1)*j);
                     i++) {
                    err = err_aim > i * 1.0 / j ?
                          err_aim - i * 1.0 / j :
                          i * 1.0 / j - err_aim;

                    if (err < err_pre) {
                        err_pre = err;
                        m = i;
                        n = j;

                        /** �õ���ƫ���������ѭ�� */
                        if (0 == err_pre) {
                            goto out;
                        }
                    }
                }

                /** i������������ѭ�� */
                if (i > 127) {
                    break;
                }
            }

            /** ���� */
            else {
                for (i = (int)err_aim * j;
                     (i > -127) && (i > (int)(err_aim - 1)*j);
                     i--) {
                    err = err_aim > i * 1.0 / j ?
                          err_aim - i * 1.0 / j :
                          i * 1.0 / j - err_aim;

                    if (err < err_pre) {
                        err_pre = err;
                        m = i;
                        n = j;

                        /** �õ���ƫ���������ѭ�� */
                        if (0 == err_pre) {
                            goto out;
                        }
                    }
                }

                /** i������������ѭ�� */
                if (i < -128) {
                    break;
                }
            }
        }
    }

out:
    amhw_fsl_rtc_current_interval_and_value_set(p_hw_rtc, n - 1, m);
    return (int)(frq + err_pre);
}

/**
 *  \brief ����RTC����ʱ��
 *
 *  \param p_dev ָ��RTC�豸��ָ��
 *  \param p_tm ��Ҫ���õ�ʱ��
 *
 *  \return ��
 */
void am_fsl_rtc_alarm_set (am_fsl_rtc_dev_t *p_dev, am_tm_t *p_tm)
{
    uint32_t sec;

    sec = __tm2sec(p_tm);
    amhw_fsl_rtc_second_set(p_dev->p_devinfo->p_hw_rtc, sec);
}

/**
 *  \breif �������ڼ���һ���еĵڼ���
 *
 *  \param day
 *  \param month
 *  \param year
 *
 *  \return һ���еĵڼ��� (1��1�ռ�Ϊ��0��)
 */
int am_fsl_rtc_date2yday (uint8_t day, uint8_t month, uint32_t year)
{
    if (((0 == year % 4) && (0 != year % 100)) || (year % 400 == 0)) {
        return __leap_year[month-1] + day - 1;
    }
    else {
        return __non_leap_year[month - 1] + day - 1;
    }
}

/** end of the file */
