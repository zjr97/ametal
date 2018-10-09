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
 * \brief kl26 ���İ�
 *
 * \internal
 * \par Modification history.
 *
 * - 1.00 16-09-23  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"
#include "am_event_input_key.h"
#include "am_event_category_input.h"
#include "am_bsp_isr_defer_pendsv.h"
#include "am_bsp_system_heap.h"
#include "am_bsp_delay_timer.h"

#include "am_kl26_inst_init.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

#ifdef __CC_ARM
#ifdef __MICROLIB
#include "am_bsp_microlib.h"
#else
#include "am_bsp_armlib.h"
#endif /* __MICROLIB */
#elif defined(__GNUC__)
#include "am_bsp_newlib.h"
#endif


/** \brief SRAM ��Ϣ,ʹ�� ARMCC ʱ��Ҫ�ṩ SRAM ������ַ */
#ifdef __CC_ARM
#define SRAM_SIZE   15
#define SRAM_START  0x1FFFF000
#define SRAM_END    (SRAM_START + SRAM_SIZE * 1024)

#endif /* __CC_ARM */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/**
 * \brief ������ʹ�õĶ�ʱ���� handle
 *
 * ��ʹ�÷�����ʱ��Ĭ�Ͻ�ʹ�� TPM0 �� CH1 ��� PWM ���Σ�����Ѿ��� TPM0 ��ʼ��Ϊ
 * PWM ���ܣ����� TPM0 ���������· PWM����˿���ʹ�ø� handle���Ա�ʹ������ 5 · PWM��
 */
am_pwm_handle_t g_buzzer_pwm_handle;

/**
 * \brief ϵͳ�δ�ʹ�õĶ�ʱ���� handle
 *
 * ��ʹ��ϵͳ�δ�ʱ��Ĭ��ʹ�� PIT ��Ϊ������ʱ��Ԫ������Ѿ��� PIT ��ʼ��Ϊ��ʱ�����ܡ�
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
    extern void am_board_system_heap_init (void);

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

    /*
     * ��ʹ����ʱ������ʹ�ã���ִ�г�ʼ����Ĭ��ʵ��Ϊʹ�� Systick ��ʱ��
     */
#if (AM_CFG_DELAY_ENABLE == 1)
    am_bsp_delay_timer_init(am_kl26_systick_inst_init(), 0);
#endif

    /**
     * \brief ���Ϊ1�����ʼ��led����ع��ܣ�Ĭ��ֻʹ�ð��ϵ�����LED
     *
     * ID: 0 --- PIOA_4
     * ID: 1 --- PIOA_5
     */
#if (AM_CFG_LED_ENABLE == 1)
    am_led_gpio_inst_init();
#endif /* AM_CFG_LED_ENABLE */

#if (AM_CFG_BUZZER_ENABLE == 1)
    g_buzzer_pwm_handle = am_buzzer_pwm_inst_init();
#endif /* (AM_CFG_BUZZER_ENABLE == 1) */


#if (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_event_input_key_init();           /**< \brief ���������¼���ʼ�� */
    am_event_category_input_init();      /**< \brief ��ʼ�������¼������� */
#endif /* (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1) */

#if (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_key_gpio_inst_init();
#endif /* (AM_CFG_KEY_GPIO_ENABLE == 1) */

    /* PMU��س�ʼ�� */
#if (AM_CFG_PMU_ENABLE == 1)
    am_kl26_pmu_inst_init();
#endif

#if (AM_CFG_ISR_DEFER_ENABLE == 1)
    am_bsp_isr_defer_pendsv_init();
#endif /* (AM_CFG_ISR_DEFER_ENABLE == 1) */

    /* �������ݴ���� */
}

/* end of file */
