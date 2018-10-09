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
 * \brief DMA Ӳ���������̣�ͨ��������ӿ�ʵ��
 *
 * - �������裺
 *   1. �� PIO0_17 �� PIO0_18 �̽ӣ�
 *   2. �۲촮�������Ϣ����������� "Press any key to finish level test!" ��
 *      ͨ���������������ַ��Լ������ԣ�
 *   3. �۲촮�������Ϣ����������� "Enter the trigger count to make burst!" ��
 *      ͨ���������ַ����ķ�ʽ����������Ĵ�����ÿ�δ������� 8 �ֽڵ����ݣ�
 *   4. �۲촮�������Ϣ����������� "Press any key to finish edge test!" ��ͨ��
 *      �������������ַ��Լ������ԣ�
 *   5. �۲촮�������Ϣ����������� "Enter any key make a burst!" ��ͨ��������
 *      �������ַ��Լ������ԡ��ظ��˹��� 6 �Ρ�
 *
 * - ʵ������
 *   1. DMA ͨ�� 0 ��������Ϊ�ж������ƽ������û��Ӳ�����������£����ݲ������ͣ�
 *   2. DMA ͨ�� 0 ��������Ϊ�ж�������ش�����ÿ��Ӳ�����������СΪ���õ�ͻ�����ȣ�
 *   3. DMA ͨ�� 0 ��������Ϊ�ж�������ش�����Ŀ���ַ���ƣ�ÿ��Ӳ��������
 *      ֻ������ͻ����С�ĵ�ַ��Χ�ڴ������ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_drv_dma_hwtrigger_burst.c src_lpc824_drv_dma_hwtrigger_burst
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem,modified
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_drv_dma_hwtrigger_burst
 * \copydoc demo_lpc824_drv_dma_hwtrigger_burst.c
 */

/** [src_lpc824_drv_dma_hwtrigger_burst] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc_usart.h"
#include "lpc82x_periph_map.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_syscon.h"

#define __GET_CHAR(ch) \
            amhw_lpc_usart_poll_receive(LPC82X_USART0, (&ch), 1);

#define __TEST_COUNT   48               /**< \brief �������ݴ�С */

am_local uint8_t __g_buf_src[__TEST_COUNT] = {0}; /**< \brief Դ�����ݻ����� */
am_local uint8_t __g_buf_dst[__TEST_COUNT] = {0}; /**< \brief ͨ�� 0 Ŀ�����ݻ����� */

/**
 * \brief ��������ӡ����
 */
am_local void __buffer_printf (uint8_t *p_buf, uint16_t count)
{
    uint16_t i;

    AM_DBG_INFO("-------------------");
    for (i = 0; i < __TEST_COUNT; i++) {
        if ((i % 10) == 0) {
            AM_DBG_INFO("\r\n");
        }
        AM_DBG_INFO("%d ", p_buf[i]);
    }
    AM_DBG_INFO("\r\n -------------------\r\n");
}

/**
 * \brief Ӳ��������ƽͻ��ģʽ����
 */
am_local void __dma_hwtrigger_bust_level_test (uint8_t  chan, int pin)
{
    int                         i     = 0;
    uint8_t                     ch    = 0;
    am_lpc82x_dma_controller_t *p_ctr = NULL;
    am_lpc82x_dma_transfer_t    transfer;

    AM_DBG_INFO("DMA PINT0 level triger burst test!\r\n");

    for (i = 0; i < __TEST_COUNT; i++) {
        __g_buf_src[i] = i;
    }
    AM_DBG_INFO("Src buffer data:\r\n");
    __buffer_printf(__g_buf_src, __TEST_COUNT);

    for (i = 0; i < __TEST_COUNT; i++) {
        __g_buf_dst[i] = 0;
    }
    AM_DBG_INFO("Dst buffer init data:\r\n");
    __buffer_printf(__g_buf_dst, __TEST_COUNT);

    /* ���� PINT �͵�ƽ����(��Ҫ���� NVIC �ж�) */
    amhw_lpc82x_pint_trigger_set(LPC82X_PINT,
                                 AMHW_LPC82X_PINT_CHAN_0,
                                 AMHW_LPC82X_PINT_TRIGGER_LOW);

    p_ctr = am_lpc82x_dma_controller_get(
                chan,                             /* DMA ͨ�� 0 */
                DMA_CHAN_OPT_PRIO_0             | /* ���ȼ� 0 */
                DMA_CHAN_OPT_HWTRIG_MODE_HIGH   | /* �źŸߵ�ƽ���� */
                DMA_CHAN_OPT_HWTRIG_SRC_PININT0 | /* �ж����� 0 ���� */
                DMA_CHAN_OPT_HWTRIG_BURST_EN);    /* ʹ��ͻ��ģʽ */

    if (p_ctr == NULL) {
        AM_DBG_INFO("Geting a Controller Faild!\r\n");
        AM_FOREVER {};
    }

    am_lpc82x_dma_transfer_build(
       &transfer,                          /* ����ṹ�� */
        (uint32_t)__g_buf_src,             /* Դ��ַ */
        (uint32_t)__g_buf_dst,             /* Ŀ���ַ */
        __TEST_COUNT,                      /* �����ֽ��� */
        AM_LPC82X_DMA_TRANS_WIDTH_8BIT  |  /* ������ */
        AM_LPC82X_DMA_TRANS_SRCINC_1X   |  /* Դ��ַ�� 1 */
        AM_LPC82X_DMA_TRANS_DSTINC_1X);    /* Ŀ���ַ�� 1 */

    am_lpc82x_dma_transfer(p_ctr, &transfer, NULL, (void*)0);

    /* �ӳ�һ��ʱ�� */
    am_mdelay(100);

    /* ��ӡ���������� */
    AM_DBG_INFO("Dest buffer data: (transfered but not triggered)\r\n");
    __buffer_printf(__g_buf_dst, __TEST_COUNT);

    /* ���� DMA ���� */
    AM_DBG_INFO("Make a trigger...");
    am_gpio_set(pin, AM_GPIO_LEVEL_LOW);
    am_mdelay(10);
    am_gpio_set(pin, AM_GPIO_LEVEL_HIGH);

    /* ��ӡ���������� */
    AM_DBG_INFO("Dest buffer data: (transfered and triggered)\r\n");
    __buffer_printf(__g_buf_dst, __TEST_COUNT);

    /* �ͷ� DMA */
    AM_DBG_INFO("Release DMA resource!\r\n");
    am_lpc82x_dma_controller_release(p_ctr);

    AM_DBG_INFO("Press any key to finish level test!\r\n");
    __GET_CHAR(ch);
}

/**
 * \brief DAM ����Ӳ��ͻ��ģʽ����
 */
am_local void __dma_hwtrigger_bust_edge_test (uint8_t  chan, int pin)
{
    int                         i     = 0;
    uint8_t                     ch    = 0;
    am_lpc82x_dma_controller_t *p_ctr = NULL;
    am_lpc82x_dma_transfer_t    transfer;

    AM_DBG_INFO("DMA PINT0 edge triger burst test!\r\n");

    for (i = 0; i < __TEST_COUNT; i++) {
        __g_buf_src[i] = i;
    }
    AM_DBG_INFO("Src buffer data:\r\n");
    __buffer_printf(__g_buf_src, __TEST_COUNT);

    for (i = 0; i < __TEST_COUNT; i++) {
        __g_buf_dst[i] = 0;
    }
    AM_DBG_INFO("Dst buffer init data:\r\n");
    __buffer_printf(__g_buf_dst, __TEST_COUNT);

    /* ���� PINT �½��ش��� */
   amhw_lpc82x_pint_trigger_set(LPC82X_PINT,
                                AMHW_LPC82X_PINT_CHAN_0,
                                AMHW_LPC82X_PINT_TRIGGER_LOW);

    p_ctr = am_lpc82x_dma_controller_get(
                chan,
                DMA_CHAN_OPT_PRIO_0              | /* ���ȼ� 0 */
                DMA_CHAN_OPT_HWTRIG_MODE_FALL    | /* Ӳ���½��ش��� */
                DMA_CHAN_OPT_HWTRIG_BURST_8      | /* ͻ�������СΪ 8 */
                DMA_CHAN_OPT_HWTRIG_SRC_PININT0  | /* �ж����� 0 ���� */
                DMA_CHAN_OPT_HWTRIG_BURST_EN);     /* ʹ��ͻ��ģʽ */

    if (p_ctr == NULL) {
        AM_DBG_INFO("Geting a controller faild!\r\n");
        AM_FOREVER {};
    }
    am_lpc82x_dma_transfer_build(
       &transfer,                          /* ����ṹ�� */
        (uint32_t)__g_buf_src,             /* Դ��ַ */
        (uint32_t)__g_buf_dst,             /* Ŀ���ַ */
        __TEST_COUNT,                      /* �����ֽ��� */
        AM_LPC82X_DMA_TRANS_WIDTH_8BIT  |  /* ������ */
        AM_LPC82X_DMA_TRANS_SRCINC_1X   |  /* Դ��ַ�� 1 */
        AM_LPC82X_DMA_TRANS_DSTINC_1X);    /* Ŀ���ַ�� 1 */

    am_lpc82x_dma_transfer(p_ctr, &transfer, NULL, (void*)0);

    am_mdelay(10);

    /* ��ӡ���������� */
    AM_DBG_INFO("Dest buffer data: (transfered but not triggered)\r\n");
    __buffer_printf(__g_buf_dst, __TEST_COUNT);

    /* �������� count �α��ش��� DAM ���� */
    do {
        AM_DBG_INFO("Enter the trigger count to make burst!\r\n");
        __GET_CHAR(ch);
    } while (ch < 49 && ch > 57);

    while ((ch--) > 48) {

        /* ���� DMA ���� */
        am_mdelay(10);
        am_gpio_set(pin, AM_GPIO_LEVEL_LOW);
        am_mdelay(10);
        am_gpio_set(pin, AM_GPIO_LEVEL_HIGH);
    }

    am_mdelay(100);

    /* ��ӡ���������� */
    AM_DBG_INFO("Dest buffer data:(transfered and triggered)\r\n");
    __buffer_printf(__g_buf_dst, __TEST_COUNT);

    /* ���ݻ�û���꣬���ǿ�����ֹ���� */
    AM_DBG_INFO("Abort the Transfer!\r\n");
    am_lpc82x_dma_controller_abort(p_ctr);

    /* �ͷ� DMA */
    AM_DBG_INFO("Release DMA resource!\r\n");
    am_lpc82x_dma_controller_release(p_ctr);

    AM_DBG_INFO("Press any key to finish edge test!\r\n");
    __GET_CHAR(ch);
}

/**
 * \brief DAM ����Ӳ��ͻ����ַ���Ʋ���
 */
am_local void __dma_hwtrigger_bust_wrap_test (uint8_t chan, int pin)
{
    int                         i     = 0;
    uint8_t                     ch    = 0;
    am_lpc82x_dma_controller_t *p_ctr = NULL;
    am_lpc82x_dma_transfer_t    transfer;

    AM_DBG_INFO("DMA PINT0 wrap triger burst test!\r\n");

    for (i = 0; i < __TEST_COUNT; i++) {
        __g_buf_src[i] = i;
    }
    AM_DBG_INFO("Src buffer data:\r\n");
    __buffer_printf(__g_buf_src, __TEST_COUNT);

    for (i = 0; i < __TEST_COUNT; i++) {
        __g_buf_dst[i] = 0;
    }
    AM_DBG_INFO("Dst buffer init data:\r\n");
    __buffer_printf(__g_buf_dst, __TEST_COUNT);

    /* ���� PINT �½��ش��� */
    amhw_lpc82x_pint_trigger_set(LPC82X_PINT,
                                 AMHW_LPC82X_PINT_CHAN_0,
                                 AMHW_LPC82X_PINT_TRIGGER_LOW);

    p_ctr = am_lpc82x_dma_controller_get(
                chan,
                DMA_CHAN_OPT_PRIO_0                | /* ���ȼ� 0 */
                DMA_CHAN_OPT_HWTRIG_MODE_FALL      | /* Ӳ���½��ش��� */
                DMA_CHAN_OPT_HWTRIG_BURST_8        | /* ͻ�������СΪ 8 */
                DMA_CHAN_OPT_HWTRIG_BURST_DST_WRAP | /* Ŀ���ַ���� */
                DMA_CHAN_OPT_HWTRIG_SRC_PININT0    | /* �ж����� 0 ���� */
                DMA_CHAN_OPT_HWTRIG_BURST_EN);       /* ʹ��ͻ��ģʽ */

    if (p_ctr == NULL) {
        AM_DBG_INFO("Geting a controller faild!\r\n");
        AM_FOREVER {};
    }
    am_lpc82x_dma_transfer_build(
       &transfer,                          /* ����ṹ�� */
        (uint32_t)__g_buf_src,             /* Դ��ַ */
        (uint32_t)__g_buf_dst,             /* Ŀ���ַ */
        __TEST_COUNT,                      /* �����ֽ��� */
        AM_LPC82X_DMA_TRANS_WIDTH_8BIT  |  /* ������ */
        AM_LPC82X_DMA_TRANS_SRCINC_1X   |  /* Դ��ַ�� 1 */
        AM_LPC82X_DMA_TRANS_DSTINC_1X);    /* Ŀ���ַ�� 1 */

    am_lpc82x_dma_transfer(p_ctr, &transfer, NULL, (void*)0);

    while(__g_buf_dst[__TEST_COUNT-1] < (__TEST_COUNT-1)) {
        AM_DBG_INFO("Enter any key make a burst!\r\n");
        __GET_CHAR(ch);

        /* ���� DMA ���� */
        am_mdelay(10);
        am_gpio_set(pin, AM_GPIO_LEVEL_LOW);
        am_mdelay(10);
        am_gpio_set(pin, AM_GPIO_LEVEL_HIGH);

        AM_DBG_INFO("Dst buffer init data:\r\n");
        __buffer_printf(__g_buf_dst, __TEST_COUNT);
    }

    /* �ͷ� DMA */
    AM_DBG_INFO("Release DMA resource!\r\n");
    am_lpc82x_dma_controller_release(p_ctr);

    AM_DBG_INFO("Press any key to finish wrap test!\r\n");
    __GET_CHAR(ch);
}

void demo_lpc824_drv_dma_hwtrigger_burst_entry (uint8_t  chan,
                                                int      pin)
{
    int i = 0;

    /* �������������� */
    for (i = 0; i < __TEST_COUNT; i++) {
        __g_buf_src[i] = i+1;
    }

    /* Ӳ��������ƽͻ��ģʽ���� */
    __dma_hwtrigger_bust_level_test(chan, pin);

    /* Ӳ����������ͻ��ģʽ���� */
    __dma_hwtrigger_bust_edge_test(chan, pin);

    /* Ӳ������ͻ������ģʽ���� */
    __dma_hwtrigger_bust_wrap_test(chan, pin);

    AM_DBG_INFO("Finish all test!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_lpc824_drv_dma_hwtrigger_burst] */

/* end of file */
