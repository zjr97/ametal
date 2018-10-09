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
 * \brief BME��װʽ�洢ָ��ʵ������
 *
 * - ������
 *   1.PIOA_1 ��������PC���ڵ�TXD;
 *   2.PIOA_2 ��������PC���ڵ�RXD;
 *   3.������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *
 * -ʵ�����󣺴������δ�ӡ�������ַ���������C����ʵ����BMEָ��ִ��Ч���ϵĲ��
 *         ���Կ���BMEָ��ʵ�ֵ�ִ��Ч�ʸ���Ч
 *
 *         systick start value: 0xff9d6a
 *
 *         systick end value: 0xff9d63
 *
 *         systick current value read overhead: 0x7
 *
 *         systick start value: 0xff9cb3
 *
 *         systick end value: 0xff9c9b
 *
 *         actual execution cycle for xor operation with normal C code: 0x11
 *
 *         systick start value: 0xff9cb0
 *
 *         systick end value: 0xff9c9f
 *
 *         actual execution cycle for xor operation with BME macros: 0xa
 *
 *         systick start value: 0xff9d57
 *
 *         systick end value: 0xff9d22
 *
 *         actual execution cycle for BFI operation with normal C: 0x2e
 *
 *         systick start value: 0xff9d19
 *
 *         systick end value: 0xff9d03
 *
 *         actual execution cycle for BFI operation with BME macro: 0xf
 *
 * \note BME ָ�����GPIOģ��ģ�Ӧ��ʹ��KL26_GPIO_BASE�ı�����ַΪ 0x4000_F000
 *
 *
 * \par Դ����
 * \snippet demo_kl26_hw_bme_deco_stores.c src_kl26_hw_bme_deco_stores
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-18  nwt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_kl26_if_hw_bme_deco_stores
 * \copydoc demo_kl26_hw_bme_deco_stores.c
 */
 
/** [src_kl26_hw_bme_deco_stores] */
#include "ametal.h"
#include "am_delay.h"
#include "am_led.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hw/amhw_kl26_gpio.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "hw/amhw_arm_systick.h"
#include "hw/amhw_fsl_bme.h"
#include "am_board.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define  GPIO_PORT_MUX_SHIFT    8      /** <\brief GPIO�ܽŸ��ú궨��  */

/** \brief GPIOģ�������ַ(����BME��BFI��UBFXָ��ʹ��) */
#define KL26_GPIO_ALIASED  ((amhw_kl26_gpio_t    *)0x4000F000UL)

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static volatile uint32_t __overhead = 0;     /** <\brief ���ڼ���δ�ʱ�Ӽ���  */


/**
 * \brief �������κ��м����ʱ�δ�ʱ�Ӽ���ֵ
 */
static void __cal_systick_read_overhead(void)
{
    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    cnt_start_value = AMHW_ARM_SYSTICK->val;

    cnt_end_value   = AMHW_ARM_SYSTICK->val;

    __overhead = cnt_start_value - cnt_end_value;

#ifdef AM_VDEBUG
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("systick current value read overhead: 0x%x\n\r", __overhead);
#endif
}

/**
 * \brief ������BME XORָ������GPIOʱ�ĵδ�ʱ�Ӽ���ֵ
 */
static void __gpio_xor_op_with_bme_macros(void)
{
    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    /* ʵ��ִ�в��������ʱ������ */
    uint32_t execution_cycle;


    /* ���� PORTC4�Źܽ�ΪGPIO���� */
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_4, 0x1);

    /* ����GPIOC 4�Źܽ�Ϊ������� */
    amhw_kl26_gpio_pin_dir_output(KL26_GPIO, PIOC_4);

    /* ����GPIOC 4�Źܽų�ʼ��ƽ */
    amhw_kl26_gpio_pin_init_out_low(KL26_GPIO, PIOC_4);

    cnt_start_value = AMHW_ARM_SYSTICK->val;

    AMHW_KL26_BME_XOR_W(&KL26_GPIO->gpio[2].pdor, 0x10);

    cnt_end_value   = AMHW_ARM_SYSTICK->val;

    execution_cycle = cnt_start_value - cnt_end_value - __overhead;

#ifdef AM_VDEBUG
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("actual execution cycle for xor operation with BME macros: 0x%x\n\r", execution_cycle);
#endif
}

/**
 * \brief ������C����xor��������GPIOʱ�ĵδ�ʱ�Ӽ���ֵ
 */
static void __gpio_xor_op_with_normalc(void)
{
    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    /* ʵ��ִ�в��������ʱ������ */
    uint32_t execution_cycle;


    /* ���� PORTC4�Źܽ�ΪGPIO���� */
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_4, 0x1);

    /* ����GPIOC4�Źܽ�Ϊ������� */
    amhw_kl26_gpio_pin_dir_output(KL26_GPIO, PIOC_4);

    /* ����GPIOC4�Źܽų�ʼ��ƽ */
    amhw_kl26_gpio_pin_init_out_low(KL26_GPIO, PIOC_4);

    cnt_start_value = AMHW_ARM_SYSTICK->val;

    KL26_GPIO->gpio[2].pdor ^= 0x10;

    cnt_end_value   = AMHW_ARM_SYSTICK->val;

    execution_cycle = cnt_start_value - cnt_end_value - __overhead;

#ifdef AM_VDEBUG
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("actual execution cycle for xor operation with normal C code: 0x%x\n\r", execution_cycle);
#endif
}

/**
 * \brief ������BME bfiָ�����ùܽŸ��ù���ΪGPIOʱ�ĵδ�ʱ�Ӽ���ֵ
 */
static void __gpio_bfi_op_with_bme_macros(void)
{
    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    /* ʵ��ִ�в��������ʱ������ */
    uint32_t execution_cycle;

    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_4, 0x0);

    cnt_start_value = AMHW_ARM_SYSTICK->val;

    /* ���ݵ�λ����λƫ�Ƶ�λ�ö��� */
    AMHW_KL26_BME_BFI_W(&KL26_PORT->port[2].port_pcr[4], /* �����ַΪPTC4�ܽſ��ƼĴ��� */
                        1 << GPIO_PORT_MUX_SHIFT,             /* ���� */
                        GPIO_PORT_MUX_SHIFT,                  /* �ӵڼ���λ��ʼ�滻 */
                        3);                                   /* ���滻λ�ĳ��� */

    cnt_end_value = AMHW_ARM_SYSTICK->val;

    execution_cycle = cnt_start_value - cnt_end_value - __overhead;

#ifdef AM_VDEBUG
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("actual execution cycle for BFI operation with BME macro: 0x%x\n\r", execution_cycle);
#endif

}

/**
 * \brief ��������C������ʵ��BFIָ�����ùܽŸ��ù���ΪGPIOʱ�ĵδ�ʱ�Ӽ���ֵ
 */
static void __gpio_bfi_op_with_normalc(volatile uint32_t  *p_addr,
                                       uint32_t wdata,
                                       uint8_t bitpos,
                                       uint8_t fieldwidth)
{
    uint32_t reg_val;
    uint32_t mask;

    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    /* ʵ��ִ�в��������ʱ������ */
    uint32_t execution_cycle;

    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_4, 0x0);

    cnt_start_value = AMHW_ARM_SYSTICK->val;

    /* C����ʵ��BFIָ�����ͬ���� */
    reg_val = *p_addr;
    mask    = ((1 << (fieldwidth)) - 1) << bitpos;
    reg_val = (reg_val & ~mask) | ((wdata) & mask);
    *p_addr = reg_val;

    cnt_end_value = AMHW_ARM_SYSTICK->val;

    execution_cycle = cnt_start_value - cnt_end_value - __overhead;

#ifdef AM_VDEBUG
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("actual execution cycle for BFI operation with normal C: 0x%x\n\r", execution_cycle);
#endif
}


/**
 * \brief �������
 */
void demo_kl26_hw_bme_deco_stores_entry (void)
{
    /* �������κ��м����ʱ�δ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���  */
    __cal_systick_read_overhead();                  /* ������ͨ���� */
    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���  */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ����ʹ��C����ʵ��XOR��������ʱ�ĵδ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���   */
    __gpio_xor_op_with_normalc();                   /* C����XOR���� */
    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���   */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ����ʹ��BME XORָ������ʱ�ĵδ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���   */
    __gpio_xor_op_with_bme_macros();                /* BMEָ��XOR���� */
    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���   */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ����ʹ��C����ʵ��BFI��������ʱ�ĵδ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���   */

    /* C����ʵ��BFI���� */
    __gpio_bfi_op_with_normalc(&KL26_PORT->port[2].port_pcr[4],
                               1 << GPIO_PORT_MUX_SHIFT,
                               GPIO_PORT_MUX_SHIFT,
                               3);
    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���   */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ����ʹ��BME BFIָ������ʱ�ĵδ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���   */
    __gpio_bfi_op_with_bme_macros();                /* BMEָ��BFI���� */
    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���   */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    while (1) {
        ;
    }
}

/** [src_kl26_hw_bme_deco_stores] */
 
/* end of file */
