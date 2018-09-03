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
 * \brief IWDG ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. �޸ĺ궨�� __IWDG_FEED_TIME_MS ��ֵ������ 1500ms(���� 5ms ���)��оƬ��λ��
 *   2. �޸ĺ궨�� __IWDG_FEED_TIME_MS ��ֵ��С�� 1500ms(���� 5ms ���)�������������С�
 *
 * \par Դ����
 * \snippet demo_zlg_hw_iwdg.c src_zlg_hw_iwdg
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-26  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_hw_iwdg
 * \copydoc demo_zlg_hw_iwdg.c
 */

/** [src_zlg_hw_iwdg] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg_iwdg.h"

/**
 * \brief ���Ź�ʹ��
 *
 * \param[in] timeout_ms : ��ʱʱ��ֵ����λ��ms
 *
 * \return ��
 *
 */
static void __zlg_iwdg_enable (amhw_zlg_iwdg_t *p_hw_iwdg, uint32_t timeout_ms)
{
    uint32_t wdt_freq = 40000;
    uint32_t ticks;
    uint32_t div = 1;

    ticks = (uint64_t) (timeout_ms) * wdt_freq / 1000;

    div = ticks / 0xFFF + 1;

    amhw_zlg_iwdg_keyvalue_set(p_hw_iwdg, 0x5555);

    while(amhw_zlg_iwdg_status_get(p_hw_iwdg) & 0x1ul);
    if (div <= 4) {
        amhw_zlg_iwdg_div_set (p_hw_iwdg, 0);
        div = 4;
    } else if (div <= 8) {
        amhw_zlg_iwdg_div_set (p_hw_iwdg, 1);
        div = 8;
    } else if (div <= 16) {
        amhw_zlg_iwdg_div_set (p_hw_iwdg, 2);
        div = 16;
    } else if (div <= 32) {
        amhw_zlg_iwdg_div_set (p_hw_iwdg, 3);
        div = 32;
    } else if (div <= 64) {
        amhw_zlg_iwdg_div_set (p_hw_iwdg, 4);
        div = 64;
    } else if (div <= 128) {
        amhw_zlg_iwdg_div_set (p_hw_iwdg, 5);
        div = 128;
    } else {
        amhw_zlg_iwdg_div_set (p_hw_iwdg, 6);
        div = 256;
    }

    wdt_freq /= div;

    ticks = (uint64_t) (timeout_ms) * wdt_freq / 1000;

    amhw_zlg_iwdg_keyvalue_set(p_hw_iwdg, 0x5555);
    while(amhw_zlg_iwdg_status_get(p_hw_iwdg) & 0x2ul);
    amhw_zlg_iwdg_reload_set (p_hw_iwdg, ticks);

    /* �������Ź� */
    amhw_zlg_iwdg_keyvalue_set(p_hw_iwdg, 0xAAAA);
    amhw_zlg_iwdg_keyvalue_set(p_hw_iwdg, 0xCCCC);
}

/**
 * \brief ���Ź�ι��
 *
 * \return ��
 *
 */
static void __zlg_sdt_feed(amhw_zlg_iwdg_t *p_hw_iwdg)
{
    amhw_zlg_iwdg_keyvalue_set(p_hw_iwdg, 0xAAAA);
}

/**
 * \brief �������
 */
void demo_zlg_hw_iwdg_entry (amhw_zlg_iwdg_t *p_hw_iwdg,
                             uint32_t         time_out_ms,
                             uint32_t         feed_time_ms)
{
    __zlg_iwdg_enable(p_hw_iwdg, time_out_ms);

    while (1) {

        /* ι������ */
        __zlg_sdt_feed(p_hw_iwdg);

        /* ��ʱ������ʱ����ι��ʱ��ʱ������5ms���ϣ�,��������Ź��¼���MCU��λ */
        am_mdelay(feed_time_ms);
    }
}
/** [src_zlg_hw_iwdg] */

/* end of file */
