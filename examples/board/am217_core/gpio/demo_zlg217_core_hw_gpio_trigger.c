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
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� J14 �� KEY �� PIOC_7 �̽���һ��
 *
 * - ʵ������
 *    ÿ�ΰ���ʱ���ڴ�ӡ "the gpio interrupt happen!"��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zlg217_hw_gpio_trigger.c src_zlg217_hw_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-24  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_hw_gpio_trigger
 * \copydoc demo_zlg217_hw_gpio_trigger.c
 */

/** [src_zlg217_hw_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zlg217.h"
#include "amhw_zlg217_gpio.h"
#include "amhw_zlg217_exti.h"
#include "amhw_zlg217_afio.h"
#include "demo_zlg_entries.h"

/**
 * \brief �������
 */
void demo_zlg217_core_hw_gpio_trigger_entry (void)
{

    AM_DBG_INFO("demo am217_core hw gpio trigger!\r\n");

    /* ���� GPIOC �˿�ʱ�� */
    am_clk_enable(CLK_IOPC);

    am_clk_enable(CLK_AFIO);

    demo_zlg_hw_gpio_trigger_entry((amhw_zlg_gpio_t *)ZLG217_GPIO,
                                   (amhw_zlg_syscfg_t *)ZLG217_AFIO,
                                   (amhw_zlg_exti_t *)ZLG217_EXTI,
                                   PIOC_7,
                                   AMHW_ZLG_SYSCFG_EXTI_PORTSOURCE_GPIOC,
                                   AMHW_ZLG_SYSCFG_EXTI_PINSOURCE_7,
                                   (amhw_zlg_exti_line_num_t)AMHW_ZLG217_LINE_NUM7);
}
/** [src_zlg217_hw_gpio_trigger] */

/* end of file */
