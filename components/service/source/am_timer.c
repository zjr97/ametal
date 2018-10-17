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
 * \brief Timer implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-04-27  tee, first implementation.
 * \endinternal
 */
#include "am_adc.h"
#include "am_timer.h"

/*******************************************************************************
  Local struct type define
*******************************************************************************/
struct __prescale_and_count_cal_ctx {
    uint64_t   desired_ticks;           /* Ŀ�� ticks                         */
    uint64_t   count_max;               /* ��ʱ����� count ֵ                */
    uint64_t   error;                   /* ��ǰԤ��Ƶ�ͼ���ֵ����Ӧ�����ֵ   */
    uint64_t   count;                   /* ��ǰ������: count ֵ             */
    uint32_t   prescale;                /* ��ǰ������: Ԥ��Ƶֵ             */
    am_bool_t  update;                  /* �Ƿ���¹�Ԥ��Ƶֵ                 */
};

/*******************************************************************************
  Local Functions
*******************************************************************************/

static void __error_check_with_new_prescale (
    struct __prescale_and_count_cal_ctx *p_ctx, uint32_t prescale_new)
{
    uint64_t count = p_ctx->desired_ticks / prescale_new;
    uint64_t error;

    /* ���� count ֵ���� count_max */
    if (count > p_ctx->count_max) {
        count = p_ctx->count_max;
    }

    error = p_ctx->desired_ticks - count * prescale_new;

    if (p_ctx->error > error) {        /* ���ָ�С�������ֵ */
        p_ctx->error    = error;
        p_ctx->count    = count;
        p_ctx->prescale = prescale_new;
        p_ctx->update   = AM_TRUE;
    }
}

/******************************************************************************/
static int __prescale_and_count_cal (const am_timer_info_t *p_info,
                                     uint64_t               ticks,
                                     uint32_t              *p_prescale,
                                     uint64_t              *p_count)
{
    struct __prescale_and_count_cal_ctx  ctx;
    
    uint32_t prescale_max;
    uint32_t prescale_min;
    uint32_t prescale;

    uint64_t count_max;

    count_max = ( (uint64_t)1ull << (p_info->counter_width) ) - 1;

    /* �����Ƶ */
    if (ticks <= count_max) {

         *p_prescale = 1;
         *p_count    = ticks;

         return AM_OK;
    }

    /* ��Ҫ��Ƶ������֧���κη�Ƶֵ */
    if (p_info->prescaler == 0) {
        return -AM_ENOTSUP;
    }

    prescale_min = ticks / count_max;        /* ���� Ticks ����С��Ƶ  */

    ctx.count_max     = count_max;
    ctx.desired_ticks = ticks;
    ctx.error         = ticks;              /* ��ʼ����Ϊ������      */
    ctx.count         = count_max;
    ctx.prescale      = 1;
    ctx.update        = AM_FALSE;

    if (p_info->features & AM_TIMER_SUPPORT_ALL_PRESCALE_1_TO_MAX) {

        prescale_max = p_info->prescaler;

        if (prescale_max < prescale_min) {   /* �޷����� */
            return -AM_ENOTSUP;
        }

        /* �������з�Ƶֵ��Ѱ����ѷ�Ƶֵ�������С��*/
        for (prescale = prescale_min; prescale <= prescale_max; prescale++) {
            __error_check_with_new_prescale(&ctx, prescale);
            if (ctx.error == 0) {
                break;
            }
        }

    } else {

        for (prescale = 1; prescale != 0; prescale <<= 1) {

            /* ֧�ָ÷�Ƶ�� ��������СֵҪ��  */
            if ((prescale & p_info->prescaler) && (prescale >= prescale_min)) {
                __error_check_with_new_prescale(&ctx, prescale);
                if (ctx.error == 0) {
                    break;
                }
            }
        }
    }

    if (ctx.update) {

         *p_prescale = ctx.prescale;
         *p_count    = ctx.count;

        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/*******************************************************************************
  Public Functions
*******************************************************************************/

/* ��ȡ��ʱ���ĵ�ǰ����Ƶ�� */
int am_timer_count_freq_get (am_timer_handle_t handle,
                             uint8_t           chan,
                             uint32_t         *p_freq)
{
    uint32_t prescale = 1;

    if ((handle == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    am_timer_clkin_freq_get (handle, p_freq);

    am_timer_prescale_get (handle, chan, &prescale);

    if (prescale != 0) {
        *p_freq /= prescale;
    }

    return AM_OK;
}

/******************************************************************************/
int am_timer_enable_us (am_timer_handle_t handle, uint8_t chan, uint32_t nus)
{
    uint32_t               clkin;
    uint32_t               prescale;
    uint64_t               ticks;
    uint64_t               count;
    const am_timer_info_t *p_info;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_info = am_timer_info_get(handle);

    am_timer_clkin_freq_get(handle, &clkin);

    /* ����������Ƶ���£�Ӧ�ü�¼��count ֵ */
    ticks = (uint64_t)nus *  clkin / 1000000;

    if (__prescale_and_count_cal(p_info, ticks, &prescale, &count) != AM_OK) {
        return -AM_ENOTSUP;
    }

    am_timer_prescale_set(handle, chan, prescale);

    if (p_info->counter_width <= 32) {
        am_timer_enable(handle, chan, count);
    } else {
        am_timer_enable64(handle, chan, count);
    }

    return AM_OK;
}

/* end of file */
