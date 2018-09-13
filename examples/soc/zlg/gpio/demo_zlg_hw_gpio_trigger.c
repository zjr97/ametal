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
 *   1. ʹ��Ӧ���ж������ϲ����½��ء�
 *
 * - ʵ������
 *   1. �жϲ���ʱ���Դ������ "the gpio interrupt happen!"��
 *
 * \par Դ����
 * \snippet demo_zlg_hw_gpio_trigger.c src_zlg_hw_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg_hw_gpio_trigger
 * \copydoc demo_zlg_hw_gpio_trigger.c
 */

/** [src_zlg_hw_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hw/amhw_zlg_exti.h"
#include "hw/amhw_zlg_gpio.h"
#include "hw/amhw_zlg_syscfg.h"

/**
 * \brief �����жϷ�����
 */
static void __gpio_isr (void *p_arg)
{
    AM_DBG_INFO("the gpio interrupt happen!\r\n");
}

/**
 * \brief �������
 */
void demo_zlg_hw_gpio_trigger_entry (amhw_zlg_gpio_t         *p_hw_gpio,
                                     amhw_zlg_syscfg_t       *p_hw_syscfg,
                                     amhw_zlg_exti_t         *p_hw_exti,
                                     int32_t                  pin,
                                     uint8_t                  portsource,
                                     uint8_t                  pinsource,
                                     amhw_zlg_exti_line_num_t exti_line_num)
{

    /* ȡ�����Ÿ��ù��� */
    amhw_zlg_gpio_pin_afr_set(p_hw_gpio, AMHW_ZLG_GPIO_AF_DEFAULT, pin);

    /* �������ŷ���Ϊ���뼰�������ŵ�ģʽ */
    amhw_zlg_gpio_pin_set(p_hw_gpio, AMHW_ZLG_GPIO_MODE_IPU << 2 | 0x00, pin);

    /* ʹ�������������� */
    amhw_zlg_gpio_pin_out_high(p_hw_gpio, pin);

    /*
     * �ж��� 0 ֻ����һ���˿ڱ��Ϊ 0 �� GPIO ���ţ�����˵��PIOA_0 ���ӵ����ж��� 0��
     * PIOB_0��PIOC_0��PIOD_0 �Ͳ��������ж��� 0, ����ʱ PIOA_1 �������ӵ��ж��� 1��
     * ��Ӧ��ϵ: PIOA_8 ��Ӧ���ⲿ�жϵ�����ԴΪ AMHW_ZLG_EXTI_PINSOURCE8
     */
    amhw_zlg_syscfg_exti_line_config(p_hw_syscfg, portsource, pinsource);

    /* ����ж������� */
    amhw_zlg_exti_imr_clear(p_hw_exti, exti_line_num);
    amhw_zlg_exti_emr_clear(p_hw_exti, exti_line_num);

    /* ����ж��ߴ�����ʽ���� */
    amhw_zlg_exti_rtsr_clear(p_hw_exti, exti_line_num);
    amhw_zlg_exti_ftsr_clear(p_hw_exti, exti_line_num);

    /* �½��ش��� */
    amhw_zlg_exti_ftsr_set(p_hw_exti, exti_line_num);

    /* �������ж��߱�־λ */
    amhw_zlg_exti_pending_clear(p_hw_exti, exti_line_num);

    /* �����û�ע����жϻص����� */
    am_gpio_trigger_connect(pin, __gpio_isr, NULL);

    /* ���ÿ����ж������� */
    amhw_zlg_exti_imr_set(p_hw_exti,  exti_line_num);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_zlg_hw_gpio_trigger] */

/* end of file */
