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
 * \brief WWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. �޸ĺ궨�� __WWDG_FEED_TIME_MS ��ֵ������ __WWDG_TIMEOUT_MS��оƬ��λ��
 *   2. �޸ĺ궨�� __WWDG_FEED_TIME_MS ��ֵ��С�� __WWDG_TIMEOUT_MS�������������С�
 *
 * \par Դ����
 * \snippet demo_zlg116_hw_wwdg.c src_zlg116_hw_wwdg
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-26  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg116_hw_wwdg
 * \copydoc demo_zlg116_hw_wwdg.c
 */

/** [src_zlg116_hw_wwdg] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
//#include "am_zlg116.h"
#include "hw/amhw_zlg_wwdg.h"

static uint8_t __g_count = 0x7f;

/**
 * \brief ���Ź�ʹ��
 *
 * \param[in] timeout_ms : ��ʱʱ��ֵ����λ��ms
 *
 * \return ��
 *
 */
static int __zlg_wwdg_enable (amhw_zlg_wwdg_t *p_hw_wwdg,
                              uint32_t         timeout_ms,
                              uint32_t         clk_rate)
{
    uint32_t wdt_freq = clk_rate / 4096;
    uint32_t ticks;
    uint32_t div = 1;

    ticks = (uint64_t) (timeout_ms) * wdt_freq / 1000;

    div = ticks / 0x40 + 1;

    amhw_zlg_wwdg_winvalue_set (p_hw_wwdg, 0x7f);

    if (div <= 1) {
        amhw_zlg_wwdg_timerbase_set(p_hw_wwdg, 0);
        div = 1;
    } else if (div <= 2) {
        amhw_zlg_wwdg_timerbase_set (p_hw_wwdg, 1);
        div = 2;
    } else if (div <= 4) {
        amhw_zlg_wwdg_timerbase_set (p_hw_wwdg, 2);
        div = 4;
    } else if (div <= 8) {
        amhw_zlg_wwdg_timerbase_set (p_hw_wwdg, 3);
        div = 8;
    } else {
        return AM_ERROR;
    }

    wdt_freq /= div;
    ticks = (uint64_t) (timeout_ms) * wdt_freq / 1000;
    __g_count = (ticks + 0x3f) % 0x7f;

    amhw_zlg_wwdg_counter_set (p_hw_wwdg, __g_count);

    /* �������Ź� */
    amhw_zlg_wwdg_enable(p_hw_wwdg);

    return AM_OK;
}

/**
 * \brief ���Ź�ι��
 *
 * \return ��
 *
 */
static void __zlg_sdt_feed (amhw_zlg_wwdg_t *p_hw_wwdg)
{
    amhw_zlg_wwdg_counter_set(p_hw_wwdg, __g_count);
}

/**
 * \brief �������
 */
void demo_zlg_hw_wwdg_entry (amhw_zlg_wwdg_t *p_hw_wwdg,
                             uint32_t         clk_rate,
                             uint32_t         time_out_ms,
                             uint32_t         feed_time_ms)
{
    __zlg_wwdg_enable(p_hw_wwdg, time_out_ms, clk_rate);

    while (1) {

        /* ι������ */
        __zlg_sdt_feed(p_hw_wwdg);

        /* ��ʱ������ʱ����ι��ʱ��ʱ,��������Ź��¼���MCU��λ */
        am_mdelay(feed_time_ms);
    }
}
/** [src_zlg116_hw_wwdg] */

/* end of file */
