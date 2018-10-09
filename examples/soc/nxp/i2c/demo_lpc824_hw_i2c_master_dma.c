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
 * \brief I2C ��д EEPROM ���̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_10 �������� EEPROM �� SCL ���ţ�
 *   2. PIO0_11 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. �� EEPROM �豸д�� __TEST_LENTH �ֽ����ݣ�
 *   2. ��ȡ EEPROM �е�����ͨ�����ڴ�ӡ������
 *   3. ��д�����ݺͶ�ȡ������һ�£�У��ͨ����LED0 �� 200ms �����˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *    3. DMA ��ʼ�������Ѿ��� am_prj_config.c �ļ��ڲ���ɡ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_i2c_master_dma.c src_lpc824_hw_i2c_master_dma
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-04  cyl, modified the using of dma interface
 * - 1.00 15-07-16  win, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_lpc824_hw_i2c_master_dma
 * \copydoc demo_lpc824_hw_i2c_master_dma.c
 */

/** [src_lpc824_hw_i2c_master_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc_i2c.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define __I2C_MASTER  LPC82X_I2C0      /**< \brief I2C ����������ͨ���Ŷ��� */
#define __I2C_CLKDIV  15               /**< \brief I2C ������ʱ�ӷ�Ƶ�������� */

#define __AM_I2C_RD   1                /**< \brief I2C ������ */
#define __AM_I2C_WR   0                /**< \brief I2C д���� */

#define __TX_DAM_ARG  0                /**< \brief I2C DMA ������ɻص��������� */
#define __RX_DAM_ARG  1                /**< \brief I2C DMA ������ɻص��������� */

#define __TEST_LENTH  8                /**< \brief ���Զ�д���ֽ���(���ܴ���ҳ��С) */


/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

am_local uint8_t __g_buf_srca[__TEST_LENTH];    /**< \brief A Դ�����ݻ����� */
am_local uint8_t __g_buf_dstb[__TEST_LENTH];    /**< \brief B Ŀ������ݻ����� */

am_local volatile am_bool_t __g_trans_done_tx;  /**< \brief ������ɱ�־ */
am_local volatile am_bool_t __g_trans_done_rx;  /**< \brief ������ɱ�־ */

  
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
am_local void __i2c_dma_isr (void *p_arg, volatile int stat)
{
    if ((stat & AM_LPC82X_DMA_STAT_INTA) && ((int)p_arg == __TX_DAM_ARG)) {
        while ((__I2C_MASTER->stat & AMHW_LPC_I2C_MASTER_STATE_MASK) !=
                AMHW_LPC_I2C_STAT_MSTTX);

        __g_trans_done_tx = AM_TRUE;
        amhw_lpc_i2c_mst_dma_disable(LPC82X_I2C0);
        amhw_lpc_i2c_mst_stop(LPC82X_I2C0);
    }

    if ((stat & AM_LPC82X_DMA_STAT_INTA) && ((int)p_arg == __RX_DAM_ARG)) {
        while ((__I2C_MASTER->stat & AMHW_LPC_I2C_MASTER_STATE_MASK) !=
                AMHW_LPC_I2C_STAT_MSTRX);

        __g_trans_done_rx = AM_TRUE;
        amhw_lpc_i2c_mst_dma_disable(LPC82X_I2C0);
        amhw_lpc_i2c_mst_stop(LPC82X_I2C0);
    }

    if (stat & AM_LPC82X_DMA_STAT_INTERR) {

        /* �û��Զ���ִ�д��� */
    }
}

/**
 * \brief I2C ������ʼ������
 *
 * \param[in] p_hw_i2c ָ�� I2C �Ĵ������ָ��
 * \param[in] clkdiv   I2C ����ʱ�ӷ�Ƶ����
 *
 * \retval  AM_OK     �������
 * \retval -AM_EINVAL ������Ч
 */
am_local int __i2c_mst_init (amhw_lpc_i2c_t *p_hw_i2c,
                             uint32_t        clkdiv)
{
    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }

    /* �ر� I2C �����������ò��� */
    amhw_lpc_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);

    /* ����ʱ�ӷ�Ƶ���� */
    amhw_lpc_i2c_clkdiv_set(p_hw_i2c, clkdiv);

    amhw_lpc_i2c_msttime_set(p_hw_i2c, 9, 9);

    /* ����������ɣ����� I2C ������ */
    amhw_lpc_i2c_mode_enable(p_hw_i2c, AM_I2C_MASTER_MODE);

    return AM_OK;
}

/**
 * \brief ���� I2C, ���ʹӻ���ַ�ʹӻ��ӵ�ַ
 *
 * \param[in] p_hw_i2c ָ��I2C�Ĵ������ָ��
 * \param[in] dev_addr �ӻ���ַ
 * \param[in] sub_addr �ӵ�ַ
 * \param[in] flags    ֵλ __AM_I2C_RD �� __AM_I2C_WR
 *
 * \return ��
 */
am_local void __i2c_mst_start (amhw_lpc_i2c_t *p_hw_i2c,
                               uint32_t        dev_addr,
                               uint32_t        sub_addr,
                               uint32_t        flags)
{
    dev_addr = dev_addr << 1;

    /* �����豸��ַ */
    amhw_lpc_i2c_mstdat_write(p_hw_i2c, dev_addr);
    amhw_lpc_i2c_mst_start(p_hw_i2c);       /* I2C ���������������ź� */

    while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_MSTPEND));
    while ((__I2C_MASTER->stat & AMHW_LPC_I2C_MASTER_STATE_MASK) !=
            AMHW_LPC_I2C_STAT_MSTTX);

    amhw_lpc_i2c_mstdat_write(p_hw_i2c, sub_addr);
    amhw_lpc_i2c_mst_continue(p_hw_i2c);

    if (flags == __AM_I2C_RD) {
        dev_addr = dev_addr | 0x01;

        while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_MSTPEND));
        while ((__I2C_MASTER->stat & AMHW_LPC_I2C_MASTER_STATE_MASK) !=
                AMHW_LPC_I2C_STAT_MSTTX);

        /* �����豸��ַ */
        amhw_lpc_i2c_mstdat_write(p_hw_i2c, dev_addr);
        amhw_lpc_i2c_mst_start(p_hw_i2c);       /* I2C ���������������ź� */
    }

    while (!(p_hw_i2c->stat & AMHW_LPC_I2C_STAT_MSTPEND)) ;

    /* ʹ�� I2C DMA ���� */
    amhw_lpc_i2c_mst_dma_enable(p_hw_i2c);
}

/**
 * \brief DMA I2C ���Ժ���
 */
am_local void __i2c_dma_test (uint8_t addr, uint8_t sub_addr)
{
    int                         i     = 0;
    am_lpc82x_dma_controller_t *p_ctr = NULL;
    am_lpc82x_dma_transfer_t    transfer;

    p_ctr = am_lpc82x_dma_controller_get(DMA_CHAN_I2C0_MST_REQ,
                                         DMA_CHAN_OPT_PRIO_3 |
                                         DMA_CHAN_OPT_PERIPH_REQ_EN);

    for (i = 0; i < __TEST_LENTH; i++) {
        __g_buf_srca[i] = i + 8;
    }

    am_lpc82x_dma_transfer_build(&transfer,
                                  (uint32_t)__g_buf_srca,
                                  (uint32_t)&(LPC82X_I2C0->mstdat),
                                  __TEST_LENTH,
                                  AM_LPC82X_DMA_TRANS_WIDTH_8BIT |
                                  AM_LPC82X_DMA_TRANS_SRCINC_1X |
                                  AM_LPC82X_DMA_TRANS_DSTINC_NOINC);

    am_lpc82x_dma_transfer(p_ctr,
                          &transfer,
                           __i2c_dma_isr,
                           (void*)__TX_DAM_ARG);

    __i2c_mst_start(LPC82X_I2C0, addr, sub_addr, __AM_I2C_WR);

    am_mdelay(10);

    am_lpc82x_dma_transfer_build(&transfer,
                                  (uint32_t)&(LPC82X_I2C0->mstdat),
                                  (uint32_t)__g_buf_dstb,
                                  __TEST_LENTH,
                                  AM_LPC82X_DMA_TRANS_WIDTH_8BIT |
                                  AM_LPC82X_DMA_TRANS_SRCINC_NOINC |
                                  AM_LPC82X_DMA_TRANS_DSTINC_1X);

    am_lpc82x_dma_transfer(p_ctr,
                          &transfer,
                           __i2c_dma_isr,
                           (void*)__RX_DAM_ARG);

    __i2c_mst_start(LPC82X_I2C0, addr, sub_addr, __AM_I2C_RD);

    am_mdelay(10);

    for (i = 0; i < __TEST_LENTH; i++) {
        if (__g_buf_dstb[i] != __g_buf_srca[i]) {
            AM_DBG_INFO("verify failed at index %d\r\n", i);
        } else {
            AM_DBG_INFO("Read EEPROM the %2dth data is 0x%02x\r\n",
                        i,
                        __g_buf_dstb[i]);
        }
    }

    if (__TEST_LENTH == i) {
        AM_DBG_INFO("i2c dma transfer done!\r\n");
    }
}


void demo_lpc824_hw_i2c_master_dma_entry (amhw_lpc_i2c_t *p_hw_i2c,
                                          uint32_t        clkdiv,
                                          uint8_t         addr,
                                          uint8_t         sub_addr)
{
    /* I2C ������ʼ������ */
    __i2c_mst_init(p_hw_i2c, clkdiv);

    __i2c_dma_test(addr, sub_addr);

    AM_FOREVER {
        if (__g_trans_done_tx && __g_trans_done_rx) {
            am_led_toggle(LED0);
            am_mdelay(200);
        }
    }
}



/** [src_lpc824_hw_i2c_master_dma] */

/* end of file */
