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
 * \brief ����ͨ�ö�ʱ��ʵ�ֵ���ʱ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-12  tee, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_int.h"
#include "am_timer.h"
#include "am_bsp_delay_timer.h"

/*******************************************************************************
  Local macro define
*******************************************************************************/

/* ����400usʱ��ʹ��while(i--)����ʽ������ʱ */
#define __DELAY_DEC_TIME_US         500

/*******************************************************************************
  Local struct type define
*******************************************************************************/

/**
 * \brief ��ʱ��ʱ�������Ϣ����
 */
static struct __delay_timer {
    am_timer_handle_t handle;           /**< \brief ��ʱ��ʱ���������        */
    uint8_t           chan;             /**< \brief ��ʱ��ʱ��ͨ��            */
    uint32_t          freq;             /**< \brief ��ʱ��ʱ��Ƶ��            */
    uint32_t          max_ticks;        /**< \brief ��ʱ��ʱ��������ֵ      */
    uint32_t          cali_ticks;       /**< \brief ��ʱ��ʱ�������õĴ���    */
    uint32_t          count_get_ticks;  /**< \brief count get �����ĵ� tick   */
    uint32_t          dec_factor;       /**< \brief ��ʱ����                  */
    uint32_t          dec_cali_factor1; /**< \brief �ݼ�����ʱ����ֵ1         */
    uint32_t          dec_cali_factor2; /**< \brief �ݼ�����ʱ����ֵ2         */
    uint32_t          dec_cali_us;      /**< \brief �ݼ�����ʱ����ֵ          */
} __g_delay_timer = {NULL, 0, 0, 0, 0, 0, 0, 0};

/*******************************************************************************
  Local Functions
*******************************************************************************/

/* ��ȡ��ʱ����ǰ����ֵ */
static uint32_t __timer_count_get (void)
{
    uint32_t ticks;

    am_timer_count_get(__g_delay_timer.handle,
                       __g_delay_timer.chan,
                       &ticks);

    return ticks;
}

/******************************************************************************/

/* ����һ�γ���������ĵ� ticks */
static uint32_t __time_ticks_cal (uint32_t start_ticks, uint32_t end_ticks)
{
    uint32_t ticks;

    if (end_ticks >= start_ticks) {
        ticks = end_ticks - start_ticks;
    } else {
        ticks = end_ticks + (__g_delay_timer.max_ticks - start_ticks);
    }

    if (ticks >= __g_delay_timer.count_get_ticks) {
        ticks -= __g_delay_timer.count_get_ticks;
    } else {
        ticks = 0;                                     /* ��Ӧ�ó����������  */
    }

    return ticks;
}

/******************************************************************************/

/* ����am_timer_count_get() �����ĵ�ʱ�� */
static void __delay_count_get_ticks_cal (void)
{
    uint32_t           start_ticks;
    uint32_t           cur_ticks;

    __g_delay_timer.count_get_ticks = 0;

    start_ticks = __timer_count_get();
    cur_ticks   = __timer_count_get();

    __g_delay_timer.count_get_ticks = __time_ticks_cal(start_ticks, cur_ticks);
}

/******************************************************************************/
/* ������� Ticks ��ʱ�Ĺ���ƫ�� */
static void __delay_cali_ticks_cal (void)
{
    uint32_t           start_ticks;
    uint32_t           cur_ticks;

    __g_delay_timer.cali_ticks = 0xFFFFFFFF;            /* set to max         */

    /* 
     * ����������ʱ���, 
     * ����ARMCC��ʹ��΢��ʱ��64λ���ļ���ǳ���ʱ��������������� 
     */
    start_ticks = __timer_count_get();                  /* ������¼��ʼλ�ô� */
    am_udelay(__DELAY_DEC_TIME_US + 1);
    cur_ticks   = __timer_count_get();                  /* ������¼����λ�ô� */

    /* �Ѿ����˶���ticks, ��Ϊ��ʱ�������ֵ */
    __g_delay_timer.cali_ticks = __time_ticks_cal(start_ticks, cur_ticks);
}

/******************************************************************************/

/* while(i--), ��Ϊ us ������ʱ�ĺ��ĺ����������Ż������ɱ��������� */
static void __delay_by_factor (uint32_t dec_factor) __attribute__ ((noinline));
 
static void __delay_by_factor (uint32_t dec_factor)
{
    volatile uint32_t factor = dec_factor;

    /*
     * ���� ISB ָ������ˮ�ߣ������֧Ԥ�����ʱ���Ӱ�죬���������ʱ����
     */
    while(factor--) {
        __asm volatile ("isb");
    }
}

/******************************************************************************/
static uint32_t  __delay_by_factor_ticks_cal (uint32_t dec_factor)
{
    uint32_t  start_ticks;
    uint32_t  cur_ticks;

    start_ticks = __timer_count_get();
    __delay_by_factor(dec_factor);
    cur_ticks   = __timer_count_get();
    
    return __time_ticks_cal(start_ticks, cur_ticks);
}

/******************************************************************************/
/* ����ݼ�����ʱ���� */
static void __delay_by_fator_cal (void)
{
    uint32_t           ticks, ticks1, ticks2;
    uint32_t           delay_us;
    uint32_t           dec_factor = 100;

    while (1) {

        ticks1 = __delay_by_factor_ticks_cal(dec_factor);

        /* ticks ����100 us ��Ӧ��ticks �ż��㣬ʹ������� < 0.01us */
        if (ticks1 > __g_delay_timer.freq / 10000) {

            ticks2 = __delay_by_factor_ticks_cal(dec_factor * 2);

            /* ����dec_factor���ķѵ�ticks��Ϊ��ʱdec_factor����Ӧ�� ticks */
            ticks = ticks2 - ticks1;

            /*
             * ticks ��Ӧ��us��: us = ticks / (__g_delay_timer.freq / 1000000)
             *               ����us = 1000000 * ticks / __g_delay_timer.freq
             *
             * 1us ��Ӧ����ʱ���� ��dec_factor / us
             *
             * 256us ����������λ���㣩��Ӧ����ʱ���ӣ� 256 * dec_factor / us
             *
             * ����256 * dec_factor / (1000000 * ticks / __g_delay_timer.freq)
             *
             * ����256 * dec_factor * __g_delay_timer.freq / (1000000 * ticks)
             *
             * ���������
             *
             * ����4 * dec_factor * __g_delay_timer.freq / (15625 * ticks)
             *     4 * dec_factor * (__g_delay_timer.freq / 15625) / ticks
             */
            __g_delay_timer.dec_factor = 4 * dec_factor * \
                                         (__g_delay_timer.freq / 15625) / ticks;

            break;
        }
        dec_factor *= 2;
    }

    /*
      * ���� dec_cali_us
      */
     __g_delay_timer.dec_cali_us = 0xFFFFFFFF;           /* set to max */

    ticks1 = __timer_count_get();
    am_udelay(1);
    ticks2 = __timer_count_get();

    ticks1 = __time_ticks_cal(ticks1, ticks2);

    /* ticks1 ��Ӧ��us, �������� */
    __g_delay_timer.dec_cali_us = \
            (ticks1 * 1000 + (__g_delay_timer.freq / 2000)) / \
                                                (__g_delay_timer.freq / 1000);
    /*
      * ���� delay ����������ʱ1
      */
     __g_delay_timer.dec_cali_factor1 = 0xFFFFFFFF;          /* set to max */

    delay_us = __g_delay_timer.dec_cali_us + 1;

    ticks1 = __timer_count_get();
    am_udelay(delay_us);
    ticks2 = __timer_count_get();

    ticks1 = __time_ticks_cal(ticks1, ticks2);

    /*
     * �� ticks1 ת��Ϊ��Ӧ�� ��ʱ����
     *
     * ��ʱ ticks ��Ӧ����ʱ����Ϊ�� dec_factor
     *
     * ticks ��Ӧ����ʱ���Ӽ�Ϊ�� ticks1 * dec_factor / ticks
     *
     * Ҳ��ѡ�� ticks ת��Ϊ us��
     * (ticks * 1000 + (__g_delay_timer.freq / 2000))
     *                                        / (__g_delay_timer.freq / 1000);
     */
    __g_delay_timer.dec_cali_factor1 = (ticks1 * dec_factor + ticks / 2) / ticks;

    /*
     * ���� delay ����������ʱ2
     */
    __g_delay_timer.dec_cali_factor2 = 0xFFFFFFFF;          /* set to max */

    /* ����ʱ��ʱ������ dec_cali_factor1 */
    delay_us = (__g_delay_timer.dec_cali_factor1 + 1) * 256 /   \
                                     __g_delay_timer.dec_factor + 1;

    ticks1 = __timer_count_get();
    am_udelay(delay_us);
    ticks2 = __timer_count_get();

    ticks1 = __time_ticks_cal(ticks1, ticks2);

    /* �� ticks1 ת��Ϊ��Ӧ�� ��ʱ���� */
    __g_delay_timer.dec_cali_factor2 = (ticks1 * dec_factor + ticks / 2) / ticks;
}

/******************************************************************************/

static void __delay (uint64_t ticks)
{
    uint32_t   max_ticks            = __g_delay_timer.max_ticks;
    uint32_t   half_count_get_ticks = __g_delay_timer.count_get_ticks / 2;

    uint32_t   start_ticks;     /* ��¼ֵ */
    uint32_t   cur_ticks;       /* ��ǰֵ */
    uint32_t   cnt_ticks;       /* ����ֵ */

    /* ��¼��ǰticksֵ */
    start_ticks = __timer_count_get();

    /* ���ˣ�������Ϊ�Ѿ������� cali_ticks, ����Ƿ��Ѿ���ʱ���� */
    if (ticks <= __g_delay_timer.cali_ticks) {
        return;
    } else {
        ticks -= __g_delay_timer.cali_ticks;
    }

    while (1) {

        /* ��ȡ��ǰticksֵ */
        cur_ticks = __timer_count_get();

        /* �Ѿ����˶���ticks */
        if (cur_ticks >= start_ticks) {
            cnt_ticks = cur_ticks - start_ticks;
        } else {
            cnt_ticks = cur_ticks + (max_ticks - start_ticks);
        }

        /*
         * ����Ƿ��Ѿ���ʱ����,
         * �ر�أ�ʣ��ʱ�䲻�� count ��ȡ��ʱ��һ�룬Ҳ��������С���
         */
        if (cnt_ticks >= ticks) {
            break;
        } else {
            ticks -= cnt_ticks;
            if (ticks <= half_count_get_ticks) {
                break;
            }
        }
        start_ticks = cur_ticks;
    }
}

/*******************************************************************************
  Public Functions
*******************************************************************************/

/**
 * \brief ��ʱ������ʼ��
 */
void am_bsp_delay_timer_init (am_timer_handle_t handle, uint8_t chan)
{
    const am_timer_info_t *p_info = NULL;

    int key;

    /* ������Ч���ж� */
    if (NULL == handle) {
        return;
    }

    /* ��ȡ��ǰ��ʱ����Ϣ */
    p_info = am_timer_info_get(handle);

    /* ��ʱ�������ж� */
    if ((!(AM_TIMER_INTERMEDIATE_COUNT & p_info->features)) || /* ��֧�ֶ�ȡ��ǰ����ֵ */
        (AM_TIMER_CANNOT_DISABLE & p_info->features) ||        /* ���ܱ����� */
        (AM_TIMER_STOP_WHILE_READ & p_info->features) ||       /* ��ȡʱ��ֹͣ */
        (!(AM_TIMER_AUTO_RELOAD & p_info->features))) {        /* ��֧���Զ����� */
        return;
    }

    /* ��ʱ��ͨ���������ж� */
    if (chan >= p_info->chan_num) {
        return;
    }

    /* ��ȫ��__g_delay_timer��ֵ */
    __g_delay_timer.handle    = handle;
    __g_delay_timer.chan      = chan;

    am_timer_count_freq_get(handle, chan, &__g_delay_timer.freq);
    am_timer_rollover_get(handle, chan, &__g_delay_timer.max_ticks);

    /* ��������Ӧ��ʹ����ʱ��ʱ��������������ֵΪ���ֵ */
    if (__g_delay_timer.max_ticks == 0) {
        __g_delay_timer.max_ticks = (1 << p_info->counter_width) - 1;
    }
    am_timer_enable(handle, chan, __g_delay_timer.max_ticks);

    /* ����һЩ��Ҫʱ��ʱ���ر��ж� */
    key = am_int_cpu_lock();
    __delay_count_get_ticks_cal();             /* ����count_get()��Ҫ��ticks  */
    am_int_cpu_unlock(key);

    key = am_int_cpu_lock();
    __delay_cali_ticks_cal();                  /* �������ticks��ʱ�������ֵ */
    am_int_cpu_unlock(key);

    key = am_int_cpu_lock();
    __delay_by_fator_cal();                    /* ����ݼ�����ʱ����          */
    am_int_cpu_unlock(key);
}

/******************************************************************************/
void am_mdelay (uint32_t nms)
{
    __delay((uint64_t)nms * __g_delay_timer.freq / 1000);
}

/******************************************************************************/
void am_udelay (uint32_t nus)
{
    if (nus < __DELAY_DEC_TIME_US) {

        uint32_t factor;

        if (nus <= __g_delay_timer.dec_cali_us) {
            return;
        }

        factor = (__g_delay_timer.dec_factor * nus) >> 8;

        if (factor <= __g_delay_timer.dec_cali_factor1) {

            factor -= __g_delay_timer.dec_cali_factor1;

        } else if (factor <= __g_delay_timer.dec_cali_factor2){

            factor -= __g_delay_timer.dec_cali_factor2;

            __delay_by_factor(0);

        } else {

            factor -= __g_delay_timer.dec_cali_factor2;

            __delay_by_factor(factor);
        }

    } else {
        __delay((uint64_t)nus * __g_delay_timer.freq / 1000000);
    }
}

/* end of file */
