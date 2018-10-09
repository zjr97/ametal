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
 * \brief WKT ��ʱ�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 1s �����˸��
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ơ�
 *
 * \par Դ����
 * \snippet demo_lpc_hw_wkt_timer.c src_lpc_hw_wkt_timer
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-02  sky, modified
 * - 1.00 15-07-13  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_wkt_timer
 * \copydoc demo_lpc_hw_wkt_timer.c
 */

/** [src_lpc_hw_wkt_timer] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc_wkt.h"


/* ѡ�� IRC ʱ�� Ƶ��Ϊ 750kHz */
#define __IRC_CLOCK_FREQ          750

/* ѡ��͹���ʱ�� Ƶ��Ϊ 10kHz */
#define __LOW_POWER_CLOCK_FREQ    10

/* ѡ���ⲿʱ�� Ƶ��Ϊ 10kHz */
#define __EXT_CLOCK_FREQ          10

/**
 * \brief ���õ�ǰ��ʱ���ļ���ֵ
 *
 * \param[in] delay_inms ���ö�ʱʱ�� delay_inms����ʱʱ��(��λ��ms)
 *
 * \return ��
 */
void wkt_delayms (amhw_lpc_wkt_t *p_hw_wkt, uint32_t delay_inms)
{

    /* ���� WKT ����������ֵ */
    if(amhw_lpc_wkt_clksel_get(p_hw_wkt) == 1) {
        amhw_lpc_wkt_count_set(p_hw_wkt,
                               __LOW_POWER_CLOCK_FREQ * delay_inms);
    } else if(amhw_lpc_wkt_clksel_get(p_hw_wkt) == 0) {
        amhw_lpc_wkt_count_set(p_hw_wkt, __IRC_CLOCK_FREQ * delay_inms);
    } else {

    /* ���������ʹ���ⲿʱ��,����������Ŀ�����û��趨���ⲿʱ��Ƶ�ʾ��� */
        amhw_lpc_wkt_count_set(p_hw_wkt, __EXT_CLOCK_FREQ * delay_inms);
    }

    /* �ȴ���ʱ */
    while(!(amhw_lpc_wkt_alarmflag_get(p_hw_wkt))) {
        ; /* VOID */
    }

    /* �����ʱ��־ */
    amhw_lpc_wkt_alarmflag_clear(p_hw_wkt);
}

void demo_lpc_hw_wkt_timer(amhw_lpc_wkt_t *p_hw_wkt,
                           uint32_t        wkt_mdelay)
{
    AM_FOREVER {

        /* LED0 �� wkt_mdelays �ļ��һֱ��˸ */
        am_led_toggle(LED0);

        wkt_delayms(p_hw_wkt, wkt_mdelay);
    }
}
/** [src_lpc_hw_wkt_timer] */

/* end of file */
