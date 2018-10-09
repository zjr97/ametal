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
 * \brief WKT ��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 1s �����˸��
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ơ�
 *
 * \par Դ����
 * \snippet demo_lpc_std_wkt_timer.c src_lpc_std_wkt_timer
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-02  sky, modified
 * - 1.00 15-09-22  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_std_wkt_timer
 * \copydoc demo_lpc_std_wkt_timer.c
 */

/** [src_lpc_std_wkt_timer] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"

am_local am_timer_handle_t __g_wkt_handle; /**< \brief ��ʱ����׼�������������ͱ��� */

/**
 * \brief WKT �ص�����
 */
am_local void __wkt_callback (void *p_arg)
{
    uint32_t  ckin = (uint32_t)p_arg;
    /* LED0 ��ת */
    am_led_toggle(LED0);

    /**
     * ʹ�ܶ�ʱ�� 1Hz �жϣ�ע�⣬���ֵΪ��0xFFFFFFFF
     * ��Ϊ WKT ��ʱ��û���Զ����أ�������Ҫ�ٴο���
     */
    am_timer_enable(__g_wkt_handle, 0, ckin);
}

void demo_lpc_std_wkt_timer_entry (am_timer_handle_t timer_handle,
                                   uint8_t           chan,
                                   uint32_t          clkin)
{
    uint32_t               wkt_timer_count;

    /* ���� handle */
    __g_wkt_handle = timer_handle;
  
    /* ʹ��ͨ�� 0(ֻ��ͨ�� 0) */
    am_timer_callback_set(timer_handle,
                          0,
                          __wkt_callback, 
                          (void *)clkin);

    /* ʹ�ܶ�ʱ�� 1Hz �жϣ�ע�⣬���ֵΪ��0xFFFFFFFF */
    am_timer_enable(timer_handle, 0, clkin);

    AM_FOREVER {
        am_timer_count_get(timer_handle, 0, &wkt_timer_count);
        am_mdelay(200);
    }
}

/** [src_lpc_std_wkt_timer] */

/* end of file */
