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
 * \brief AM824-Core ���İ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_board.h"
#include "am_event_input_key.h"
#include "am_event_category_input.h"
#include "am_prj_config.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

#include "am_bsp_system_heap.h"
#include "am_bsp_isr_defer_pendsv.h"
#include "am_bsp_delay_timer.h"


#ifdef __CC_ARM
#ifdef __MICROLIB
#include "am_bsp_microlib.h"
#else
#include "am_bsp_armlib.h"
#endif /* __MICROLIB */
#elif defined(__GNUC__)
#include "am_bsp_newlib.h"
#endif

/** \brief SRAM ��Ϣ,ʹ�� ARMCC ʱ��Ҫ�ṩ SRAM������ַ */
#ifdef __CC_ARM
#define SRAM_SIZE   8
#define SRAM_START  0x10000000
#define SRAM_END    (SRAM_START + SRAM_SIZE * 1024)
#endif /* __CC_ARM */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/**
 * \brief ������ʹ�õĶ�ʱ���� handle
 *
 * ��ʹ�÷�����ʱ��Ĭ�Ͻ�ʹ�� SCT �� OUT1 ��� PWM ���Σ�����Ѿ��� SCT ��ʼ��Ϊ
 * PWM ���ܣ����� SCT ���������· PWM����˿���ʹ�ø� handle���Ա�ʹ������ 5 · PWM
 */
am_pwm_handle_t g_buzzer_pwm_handle;

/**
 * \brief ϵͳ�δ�ʹ�õĶ�ʱ���� handle
 *
 * ��ʹ��ϵͳ�δ�ʱ��Ĭ��ʹ�� MRT ��ͨ�� 0 ��Ϊ������ʱ��Ԫ������Ѿ��� MRT ��ʼ��Ϊ
 * ��ʱ�����ܣ����� MRT ����֧�� 4 ·��ʱ����˿���ʹ�ø� handle���Ա�ʹ������ 3 ·
 * ��ʱͨ��
 */
am_timer_handle_t g_system_tick_timer_handle;

/*******************************************************************************
  ��������
*******************************************************************************/

/**
 * \brief �弶��ʼ��
 */
void am_board_init (void)
{
    am_uart_handle_t dbg_handle = NULL;
    am_timer_handle_t handle;
	
#ifdef  __GNUC__
    extern char __heap_start__;            /* Defined by the linker */
    extern char __heap_end__;              /* Defined by the linker */

    static char *heap_start = &__heap_start__;
    static char *heap_end   = &__heap_end__;

#elif defined(__CC_ARM)

    extern int Image$$RW_IRAM1$$ZI$$Limit; /* Defined by the linker */
	
    int *heap_start = (int *)&Image$$RW_IRAM1$$ZI$$Limit;
    int *heap_end   = (int *)SRAM_END;
#endif

    /* ϵͳ��ջ��ʼ�� */
    am_bsp_system_heap_init((void *)heap_start, (void *)heap_end);

#if (AM_CFG_DELAY_ENABLE == 1)

    handle = am_arm_systick_inst_init();
    am_bsp_delay_timer_init(handle , 0);
#endif /* (AM_CFG_DELAY_ENABLE == 1) */

#if (AM_CFG_LED_ENABLE == 1)
    am_led_gpio_inst_init();
#endif /* (AM_CFG_LED_ENABLE == 1) */

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
    g_system_tick_timer_handle = am_system_tick_softimer_inst_init();
#elif (AM_CFG_SYSTEM_TICK_ENABLE == 1)
    g_system_tick_timer_handle = am_system_tick_inst_init();
#endif /* ((AM_CFG_SOFTIMER_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1)) */

#if (AM_CFG_BUZZER_ENABLE == 1)
    g_buzzer_pwm_handle = am_buzzer_pwm_inst_init();
#endif /* (AM_CFG_BUZZER_ENABLE == 1) */

#if (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_event_input_key_init();           /* ���������¼���ʼ�� */
    am_event_category_input_init();      /* ��ʼ�������¼������� */
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
