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
 * \brief I2C �ӻ����̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_10 �������� I2C ������ SCL ���ţ�
 *   2. PIO0_11 �������� I2C ������ SDA ���š�
 *
 * - ʵ������
 *   1. �����������͹��������ݣ�ͨ�����ڷ��͸���λ����
 *   2. ����ʧ���� LED0 �Ƴ�����
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. DMA ��ʼ�������Ѿ��� am_prj_config.c �ļ��ڲ���ɡ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_i2c_slave_dma.c src_lpc824_hw_i2c_slave_dma
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-04  cyl, modified the using of dma interface
 * - 1.00 15-07-16  win, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_lpc824_hw_i2c_slave_dma
 * \copydoc demo_lpc824_hw_i2c_slave_dma.c
 */

/** [src_lpc824_hw_i2c_slave_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc_i2c.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define __SLAVE_ADDR      0x50              /**< \brief ���������ӻ���ַ���� */

#define __TEST_LENTH      4                 /**< \brief ���Զ�д���ֽ��� */

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief DMA ���������� */
am_local __attribute__((aligned(16)))  am_lpc82x_dma_xfer_desc_t __g_desc[2];

am_local uint8_t __g_buf_dsta[__TEST_LENTH];   /**< \brief A Ŀ������ݻ����� */
am_local uint8_t __g_buf_dstb[__TEST_LENTH];   /**< \brief B Ŀ������ݻ����� */

am_local volatile am_bool_t __g_a_trans_done;  /**< \brief A Ŀ��˴�����ɱ�־ */
am_local volatile am_bool_t __g_b_trans_done;  /**< \brief B Ŀ��˴�����ɱ�־ */

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg �û��Զ��������ͨ�� am_lpc82x_dma_xfer_desc_startup() ��������
 * \param[in] stat  DMA �ж�״̬���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                      AM_LPC82X_DMA_STAT_INTA
 *                      AM_LPC82X_DMA_STAT_INTB
 *                      AM_LPC82X_DMA_STAT_INTERR
 *
 * \return ��
 */
am_local void __i2c_dma_isr (void *p_arg, int stat)
{
    if (stat & AM_LPC82X_DMA_STAT_INTA) {
        __g_a_trans_done = AM_TRUE;
        am_led_off(LED0);
    } else if (stat & AM_LPC82X_DMA_STAT_INTB) {
        __g_b_trans_done = AM_TRUE;
        am_led_off(LED0);
    } else if (stat & AM_LPC82X_DMA_STAT_INTERR) {

        /* �û��Զ���ִ�д��� */
    }
}

/**
 * \brief I2C �ӻ���ʼ�����ú���
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] dev_addr ���������ӻ��ĵ�ַ����
 *
 * \retval AM_OK ��ʼ���������
 */
am_local int __i2c_slave_init (amhw_lpc_i2c_t *p_hw_i2c, uint8_t dev_addr)
{
    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_SLAVE_MODE);
    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_TIMEOUT_MODE);

    amhw_lpc_i2c_clkdiv_set(p_hw_i2c, 7);
    amhw_lpc_i2c_slv_addr_set(p_hw_i2c, AMHW_LPC_I2C_SLVADR_0, dev_addr);
    amhw_lpc_i2c_slvqual_set(p_hw_i2c, 0);

    amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_SLAVE_MODE);

    return AM_OK;
}

/**
 * \brief I2C �ӻ���������
 *
 * \param[in] p_hw_i2c ָ��I2C�Ĵ������ָ��
 *
 * \return ��
 *
 * \note ��������������������ӻ�����
 */
am_local void __i2c_slave_start (amhw_lpc_i2c_t *p_hw_i2c)
{
    uint8_t addr     = 0;
    uint8_t sub_addr = 0;

    while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_SLVPEND));
    while ((p_hw_i2c->stat & AMHW_LPC_I2C_SLAVE_STATE_MASK) !=
           AMHW_LPC_I2C_STAT_SLVADDR);

    /* ƥ�䵽�ӻ���ַ�������ӻ� DMA ���� */
    if (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_SLVIDX_MASK)) {

        /* �����������͹����Ĵӻ���ַ, ��ַ���λ 1 �� 0, �������д���� */
        addr = amhw_lpc_i2c_slvdat_read(p_hw_i2c);
        amhw_lpc_i2c_slv_continue(p_hw_i2c);

        while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_SLVPEND));
        while ((p_hw_i2c->stat & AMHW_LPC_I2C_SLAVE_STATE_MASK) !=
               AMHW_LPC_I2C_STAT_SLVRX);

        /* �����������͹����Ĵӻ��ӵ�ַ */
        sub_addr = amhw_lpc_i2c_slvdat_read(p_hw_i2c);
        amhw_lpc_i2c_slv_continue(p_hw_i2c);

        amhw_lpc_i2c_slv_dma_enable(p_hw_i2c);

        AM_DBG_INFO("Slave Address is %x\r\n", addr);
        AM_DBG_INFO("Slave Sub Address is %x\r\n", sub_addr);
    }
}

/**
 * \brief I2C �ӻ� DMA �������ݣ����� ping-pong ����
 */
am_local void __dma_i2c_test (amhw_lpc_i2c_t *p_hw_i2c, uint8_t chan)
{
    uint32_t                    flags1 = 0;
    uint32_t                    flags2 = 0;
    am_lpc82x_dma_controller_t *p_ctr  = NULL;

    p_ctr = am_lpc82x_dma_controller_get(chan,
                                         DMA_CHAN_OPT_PRIO_3 |
                                         DMA_CHAN_OPT_PERIPH_REQ_EN);

    /* DMA �������� */
    flags1 =
        AM_LPC82X_DMA_XFER_VALID           | /* ��ǰ������������Ч */
        AM_LPC82X_DMA_XFER_RELOAD          | /* �����������ͨ�������� */
        AM_LPC82X_DMA_XFER_SWTRIG          | /* ������� */
        AM_LPC82X_DMA_XFER_WIDTH_8BIT      | /* �������ݿ�ȣ�8 bit */
        AM_LPC82X_DMA_XFER_SRCINC_NOINC    | /* Դ�����ݵ�ַ������ */
        AM_LPC82X_DMA_XFER_DSTINC_1X       | /* Ŀ������ݵ�ַ�� 1 �����ݿ�ȵ��� */
        AM_LPC82X_DMA_XFER_SETINTA;          /* ʹ���ж� A */

    /* DMA �������� */
    flags2 =
        AM_LPC82X_DMA_XFER_VALID           | /* ��ǰ������������Ч */
        AM_LPC82X_DMA_XFER_RELOAD          | /* �����������ͨ�������� */
        AM_LPC82X_DMA_XFER_SWTRIG          | /* ������� */
        AM_LPC82X_DMA_XFER_WIDTH_8BIT      | /* �������ݿ�ȣ�8 bit */
        AM_LPC82X_DMA_XFER_SRCINC_NOINC    | /* Դ�����ݵ�ַ������ */
        AM_LPC82X_DMA_XFER_DSTINC_1X       | /* Ŀ������ݵ�ַ�� 1 �����ݿ�ȵ��� */
        AM_LPC82X_DMA_XFER_SETINTB;          /* ʹ���ж� B */

    /* ����ͨ�������� A */
    am_lpc82x_dma_xfer_desc_build(
       &__g_desc[0],                           /* A ������������ */
        (uint32_t)&(LPC82X_I2C0->slvdat), /* Դ�����ݻ����� */
        (uint32_t)__g_buf_dsta,                /* A ��Ŀ��˻�������ַ */
        __TEST_LENTH,                          /* �����ֽ��� */
        flags1);                               /* �������� */

    /* ����ͨ�������� B */
    am_lpc82x_dma_xfer_desc_build(
       &__g_desc[1],                           /* B ������������ */
        (uint32_t)&(LPC82X_I2C0->slvdat), /* Դ�����ݻ����� */
        (uint32_t)__g_buf_dstb,                /* B ��Ŀ��˻�������ַ */
        __TEST_LENTH,                          /* �����ֽ��� */
        flags2);                               /* �������� */

    /* ��������ͨ�������� */
    am_lpc82x_dma_xfer_desc_link(&__g_desc[1], &__g_desc[0]);
    am_lpc82x_dma_xfer_desc_link(&__g_desc[0], &__g_desc[1]);

    /* ���� DMA ���䣬���Ͽ�ʼ���� */
    am_lpc82x_dma_xfer_desc_startup(p_ctr,
                                    &__g_desc[0],
                                    __i2c_dma_isr,
                                    NULL);

    __i2c_slave_start(p_hw_i2c);
}

void demo_lpc824_hw_i2c_slave_dma_entry (amhw_lpc_i2c_t *p_hw_i2c,
                                         uint8_t         chan)
{
    uint8_t i = 0;

    /* I2C ������ʼ������ */
    __i2c_slave_init(p_hw_i2c, __SLAVE_ADDR);

    /* ���� LED0 */
    am_led_on(LED0);

    /* I2C ���Ժ��� */
    __dma_i2c_test(p_hw_i2c, chan);

    AM_FOREVER {
        if (__g_a_trans_done) {
            __g_a_trans_done = AM_FALSE;
            for (i = 0; i < __TEST_LENTH; i++) {
                AM_DBG_INFO("A_buf %2dst is 0x%02x\r\n", i, __g_buf_dsta[i]);
            }
        }

        if (__g_b_trans_done) {
            __g_b_trans_done = AM_FALSE;
            for (i = 0; i < __TEST_LENTH; i++) {
                AM_DBG_INFO("B_buf %2dst is 0x%02x\r\n", i, __g_buf_dstb[i]);
            }
        }
    }
}
/** [src_lpc824_hw_i2c_slave_dma] */

/* end of file */
