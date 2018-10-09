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
 * \brief  BME��װʽ�洢ָ��ʵ������
 *
 * - ������
 *   1.PIOA_1 ��������PC���ڵ�TXD;
 *   2.PIOA_2 ��������PC���ڵ�RXD;
 *   3.������λ�����ڲ�����Ϊ115200��8λ���ݳ��� 1λֹͣλ ����żУ��;
 *
 * -ʵ�����󣺴������δ�ӡ�������ַ���������C����ʵ����BMEָ��ִ��Ч���ϵĲ��
 *         ���Կ���BMEָ��ʵ�ֵ�ִ��Ч�ʸ���Ч������������led��

 *         systick end value: 0xff9d63
 *
 *         systick current value read overhead: 0x7
 *
 *         extracted data with las1 normal C is 1
 *
 *         systick start value: 0xff9d5c
 *
 *         systick end value: 0xff9d30
 *
 *         actual execution cycle for las1 operation with normal C code: 0x25
 *
 *         extracted data with las1 BME macro is 1
 *
 *         systick start value: 0xff9d6a
 *
 *         systick end value: 0xff9d58
 *
 *         actual execution cycle for las1 operation with BME macros: 0xb
 *
 *         extracted data with ubfx normal C is 17
 *
 *         systick start value: 0xff9d56
 *
 *         systick end value: 0xff9d2d
 *
 *         actual execution cycle for ubfx operation with normal C: 0x22
 *
 *         extracted data with ubfx BME macro is 17
 *
 *         systick start value: 0xff9d6a
 *
 *         systick end value: 0xff9d59
 *
 *         actual execution cycle for ubfx operation with BME macro: 0xa
 *
 * \note BME�� ����д1��������AMHW_KL26_BME_LAS1_*����ʹ����������w1c����λ�ļĴ����У��������״̬�Ĵ���.
 *
 * \par Դ����
 * \snippet demo_kl26_hw_bme_deco_loads.c src_kl26_hw_bme_deco_loads
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-18  nwt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_kl26_if_hw_bme_deco_loads
 * \copydoc demo_kl26_hw_bme_deco_loads.c
 */
 
/** [src_kl26_hw_bme_deco_loads] */

#include "hw/amhw_fsl_bme.h"
#include "ametal.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "hw/amhw_kl26_gpio.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "hw/amhw_arm_systick.h"
#include "am_board.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define  GPIO_PODR_SHIFT    4      /** <\brief GPIO��������Ĵ���ƫ�ƶ���  */

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
 * \brief ������BME LAS1ָ������GPIOʱ�ĵδ�ʱ�Ӽ���ֵ
 */
static void __gpio_las1_op_with_bme_macros(void)
{
    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    /* ʵ��ִ�в��������ʱ������ */
    uint32_t execution_cycle;

    uint32_t rdata;

    cnt_start_value = AMHW_ARM_SYSTICK->val;

    rdata =  AMHW_KL26_BME_LAS1_W(&KL26_GPIO->gpio[2].pdor, 4);

    cnt_end_value   = AMHW_ARM_SYSTICK->val;

    execution_cycle = cnt_start_value - cnt_end_value - __overhead;

#ifdef AM_VDEBUG
    am_kprintf("extracted data with las1 BME macro is %d\n\r", rdata);
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("actual execution cycle for las1 operation with BME macros: 0x%x\n\r", execution_cycle);
#endif
}

/**
 * \brief ������C����ʵ�� LAS1ָ����ʵ������GPIOʱ�ĵδ�ʱ�Ӽ���ֵ
 */
static void __gpio_las1_op_with_normalc(uint32_t volatile *p_addr, uint8_t bitpos)
{
    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    /* ʵ��ִ�в��������ʱ������ */
    uint32_t execution_cycle;

    uint32_t mask;

    uint8_t load_bit;


    cnt_start_value = AMHW_ARM_SYSTICK->val;

    /* C����ʵ�ֶ�����1����  */
    mask= 1UL << bitpos;
    load_bit = (*p_addr & mask)>>bitpos;
    *p_addr |= mask;;

    cnt_end_value   = AMHW_ARM_SYSTICK->val;

    execution_cycle = cnt_start_value - cnt_end_value - __overhead;

#ifdef AM_VDEBUG
    am_kprintf("extracted data with las1 normal C is %d\n\r", load_bit);
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("actual execution cycle for las1 operation with normal C code: 0x%x\n\r", execution_cycle);
#endif

}

/**
 * \brief ������BME UBFXָ��������GPIO�ܽ���������Ĵ�����ĳЩλ�ε����ݵδ�ʱ�Ӽ���ֵ
 */
static void __gpio_ubfx_op_with_bme_macros(void)
{
    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    /* ʵ��ִ�в��������ʱ������ */
    uint32_t execution_cycle;

    uint32_t rdata;

    cnt_start_value = AMHW_ARM_SYSTICK->val;

    rdata = AMHW_KL26_BME_UBFX_W(&KL26_GPIO_ALIASED->gpio[2].pdor,
                                 GPIO_PODR_SHIFT, /* �ӵڼ���λ��ʼ����. */
                                 5);              /* ����λ�ĳ���.  */

    cnt_end_value = AMHW_ARM_SYSTICK->val;

    execution_cycle = cnt_start_value - cnt_end_value - __overhead;

#ifdef AM_VDEBUG
    am_kprintf("extracted data with ubfx BME macro is %d\n\r", rdata);
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("actual execution cycle for ubfx operation with BME macro: 0x%x\n\r", execution_cycle);
#endif

}


/**
 * \brief ������C����ʵ��BME UBFXָ��������GPIO�ܽ���������Ĵ�����ĳЩλ�ε����ݵδ�ʱ�Ӽ���ֵ
 */
static void __gpio_ubfx_op_with_normalc(volatile uint32_t  *p_addr,
                                        uint32_t *p_rdata,
                                        uint8_t bitpos,
                                        uint8_t fieldwidth)
{
    uint32_t cnt_start_value;
    uint32_t cnt_end_value;

    /* actual execution cycle */
    uint32_t execution_cycle;

    uint32_t reg_val;
    uint32_t mask;

    cnt_start_value = AMHW_ARM_SYSTICK->val;

    reg_val = *p_addr;

    /* generate bit mask */
    mask  = ((1UL << (fieldwidth)) - 1) << bitpos;

    /* read data returned to core */
    *p_rdata = (reg_val &  mask) >> bitpos;

    cnt_end_value = AMHW_ARM_SYSTICK->val;

    execution_cycle = cnt_start_value - cnt_end_value - __overhead;

#ifdef AM_VDEBUG
    am_kprintf("extracted data with ubfx normal C is %d\n\r", *p_rdata);
    am_kprintf("systick start value: 0x%x\n\r", cnt_start_value);
    am_kprintf("systick end value: 0x%x\n\r", cnt_end_value);
    am_kprintf("actual execution cycle for ubfx operation with normal C: 0x%x\n\r", execution_cycle);
#endif
}

/**
 * \brief �������
 */
void demo_kl26_hw_bme_deco_loads_entry (void)
{

    uint32_t rdata = 0;

    /* �������κ��м����ʱ�δ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���  */
    __cal_systick_read_overhead();                  /* ������ͨ���� */
    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���  */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ����ʹ��C����ʵ�ֶ�����1��������ʱ�ĵδ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���   */

    /* C���Զ�����1���� */
    __gpio_las1_op_with_normalc(&KL26_GPIO->gpio[2].pdor, 4);

    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���   */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ����ʹ��BME LAS1ָ������ʱ�ĵδ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���   */
    __gpio_las1_op_with_bme_macros();               /* BMEָ��LAS1���� */
    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���   */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ����ʹ��C����ʵ��UBFX��������ʱ�ĵδ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���   */

    /* C����ʵ��UBFX���� */
    __gpio_ubfx_op_with_normalc(&KL26_GPIO->gpio[2].pdor,
                                &rdata,
                                GPIO_PODR_SHIFT,
                                5);

    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���   */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ����ʹ��BME UBFXָ������ʱ�ĵδ�ʱ�Ӽ���ֵ */
    amhw_arm_systick_enable(AMHW_ARM_SYSTICK);      /* ʹ�����¼���   */
    __gpio_ubfx_op_with_bme_macros();               /* BMEָ��UBFX���� */
    amhw_arm_systick_disable(AMHW_ARM_SYSTICK);     /* �������¼���   */
    amhw_arm_systick_val_set(AMHW_ARM_SYSTICK, 0);  /* �������ֵ   */

    /* ʹ��BME LAC1ָ���������ָ��λ����LED */
    rdata =  AMHW_KL26_BME_LAC1_W(&KL26_GPIO->gpio[2].pdor, 8);
    rdata =  AMHW_KL26_BME_LAC1_W(&KL26_GPIO->gpio[2].pdor, 4);

    while (1) {
        ;
    }
}

/** [src_kl26_hw_bme_deco_loads] */
 
/* end of file */
