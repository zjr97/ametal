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
 * \brief WWDT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��Ļ��ӡ���Ź�ʱ��Ƶ�ʣ�
 *   2. ǰ 5 �α����жϷ���ʱ����ִ��ι������,���ڴ�ӡ��ǰι��������
 *   3. �� 6 �α����жϷ���ʱ����ִ��ι���������ᷢ�����Ź���λ��
 *   4. ��λ��LED0 �� 500ms�����ڴ�ӡ "Watchdog reset occurred!"��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. WDT ʱ�ӣ�0.6MHz��64 ��Ƶ��ʱ��Ƶ�� 9.375KHz��WDT �������̶� 4 ��Ƶʱ�ӣ�
 *       �� WDT ʱ��Ƶ�ʴ��� 400K ʱ��WDT ���ڹ��ܲ�������ʹ�á�
 *
 * \par Դ����
 * \snippet demo_lpc_hw_wwdt.c src_lpc_hw_wwdt
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-14  hgo, del amhw_lpc_wwdt_option_clr()
 * - 1.00 15-07-22  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc_hw_wwdt
 * \copydoc demo_lpc_hw_wwdt.c
 */

/** [src_lpc_hw_wwdt] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_arm_nvic.h"
#include "am_board.h"
#include "hw/amhw_lpc_wwdt.h"

/** \brief ���Ź���������ͳ�� */
am_local volatile uint8_t __g_wdt_update_count;

/**
 * \brief ���Ź���ʱ�����жϴ�����
 *
 * \param[in] p_arg ��ڲ���
 *
 * \return ��
 */
am_local void __wdt_irq_handler (void *p_arg)
{

    amhw_lpc_wwdt_t *handle = (amhw_lpc_wwdt_t *)p_arg;
    /* ���Ź���ʱ�����ֱ���״̬ */
    if (amhw_lpc_wwdt_status_get(handle) & AMHW_LPC_WWDT_WDMOD_WDINT) {

        /* ��ӡι��ʱ��ǰ�ĵ�������ֵ */
        AM_DBG_INFO("The current countis %d .\r\n",
                    amhw_lpc_wwdt_currentcount_get(handle));

        amhw_lpc_wwdt_status_clr(handle,
                                 AMHW_LPC_WWDT_WDMOD_WDINT);

        /* �ڳ�ʱǰ 5 �α����жϷ����� ִ��ι������Ȼ�������Ź���λ */
        if (__g_wdt_update_count < 5) {
            amhw_lpc_wwdt_feed(handle);
            __g_wdt_update_count++;
            AM_DBG_INFO("The %d times feed .\r\n", __g_wdt_update_count);
        }
    }
}


void demo_lpc_hw_wwdt_entry (amhw_lpc_wwdt_t *p_hw_wwdt,
                             int              inum,
                             uint32_t         wdt_freq)

{
          /* ��⿴�Ź��Ƿ�λ */
    if (amhw_lpc_wwdt_status_get(p_hw_wwdt) & AMHW_LPC_WWDT_WDMOD_WDTOF) {

        /* �� LED0 */
        am_led_on(LED0);

        /* ��ӡ���Ź���λ��Ϣ */
        AM_DBG_INFO("Watchdog reset occurred! \r\n");

        amhw_lpc_wwdt_status_clr(p_hw_wwdt, AMHW_LPC_WWDT_WDMOD_WDTOF);
    }

    /* WWDT ��ʼ�� */
    amhw_lpc_wwdt_init(p_hw_wwdt);

    /**
     * ���ÿ��Ź�ʱ�������Լ 2s
     * ���ÿ��Ź�����ʱ��Ϊ 512 ticks
     * ���ÿ��Ź����ڶ�ʱ��ʱ��Ϊ 1s
     */
    amhw_lpc_wwdt_timeout_set(p_hw_wwdt, wdt_freq * 2);
    amhw_lpc_wwdt_warning_set(p_hw_wwdt, 512);
    amhw_lpc_wwdt_window_set(p_hw_wwdt, wdt_freq * 1);

    /* ���Ź�ʱ�䷢���󣬸�λ MCU */
    amhw_lpc_wwdt_option_set(p_hw_wwdt, AMHW_LPC_WWDT_WDMOD_WDRESET);

    /* ��������ͳ�ʱ�ж� */
    amhw_lpc_wwdt_status_clr(p_hw_wwdt,
                             AMHW_LPC_WWDT_WDMOD_WDTOF |
                             AMHW_LPC_WWDT_WDMOD_WDINT);

    /* ע�ῴ�Ź��жϺ��� */
    am_int_connect(inum, __wdt_irq_handler, (void *)p_hw_wwdt);

    /* ����Ѿ�����Ŀ��Ź��ж� */
    amhw_arm_nvic_pending_clr(inum);

    /* �򿪿��Ź��ж� */
    am_int_enable(inum);

    /* �������Ź���ʱ�� */
    amhw_lpc_wwdt_start(p_hw_wwdt);

    while (1) {
      ; /* void */
    }
}

/** [src_lpc_hw_wwdt] */

/* end of file */
