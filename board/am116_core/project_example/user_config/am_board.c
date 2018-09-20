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
 * \brief am116_core ���İ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */


#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"
#include "am_event_input_key.h"
#include "am_event_category_input.h"
#include "am_zlg116.h"
#include "am_zlg116_inst_init.h"

#include "am_bsp_system_heap.h"
#include "am_bsp_delay_timer.h"
#include "am_bsp_isr_defer_pendsv.h"

#ifdef __CC_ARM
#ifdef __MICROLIB
#include "am_bsp_microlib.h"
#else
#include "am_bsp_armlib.h"
#endif /* __MICROLIB */
#elif defined(__GNUC__)
#include "am_bsp_newlib.h"
#endif

/*******************************************************************************
  �弶��ʼ��
*******************************************************************************/

void am_board_init (void)
{
    am_uart_handle_t  dbg_handle = NULL;

    am_bsp_system_heap_init();

#ifdef AM_VDEBUG
#if (AM_CFG_DEBUG_ENABLE == 1)
    dbg_handle = am_debug_uart_inst_init(); 
#endif /* (AM_CFG_DEBUG_ENABLE == 1) */
#endif /* AM_VDEBUG */

#if (AM_CFG_STDLIB_ENABLE == 1)
    #ifdef __CC_ARM
        #ifdef __MICROLIB

            /* ��ʼ��Micro LIB */
            am_bsp_microlib_init(dbg_handle);
        #else

            /* ��ʼ��ARM LIB */
            am_bsp_armlib_init(dbg_handle);
        #endif /* __MICROLIB */

    #elif defined(__GNUC__)

        /* ��ʼ�� NEW LIB �� */
        am_bsp_newlib_init(dbg_handle);
    #endif
#endif /* (AM_CFG_STDLIB_ENABLE == 1) */

#if ((AM_CFG_SOFTIMER_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1))
    am_system_tick_softimer_inst_init();
#elif (AM_CFG_SYSTEM_TICK_ENABLE == 1)
    am_system_tick_inst_init();
#endif /* ((AM_CFG_SOFTIMER_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1)) */

    /* ��ʱ��������ʹ�� ����ϵͳ�δ�Ķ�ʱ�� (�������ʱ������ SYSTICK) */
#if (AM_CFG_DELAY_ENABLE == 1)
    am_bsp_delay_timer_init(am_zlg116_systick_inst_init(), 0);
#endif /* (AM_CFG_DELAY_ENABLE == 1) */

#if (AM_CFG_LED_ENABLE == 1)
    am_led_gpio_inst_init();
#endif /* (AM_CFG_LED_ENABLE == 1) */

#if (AM_CFG_BUZZER_ENABLE == 1)
    am_buzzer_pwm_inst_init();
#endif /* (AM_CFG_BUZZER_ENABLE == 1) */

#if (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_event_input_key_init();           /**< \brief ���������¼���ʼ�� */
    am_event_category_input_init();      /**< \brief ��ʼ�������¼������� */
#endif /* (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1) */

#if (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_key_gpio_inst_init();
#endif /* (AM_CFG_KEY_GPIO_ENABLE == 1) */

#if (AM_CFG_ISR_DEFER_ENABLE == 1)
    am_bsp_isr_defer_pendsv_init();
#endif /* (AM_CFG_ISR_DEFER_ENABLE == 1) */

    /* �������ݴ���� */
}

/* end of file */
