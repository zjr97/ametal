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
 * \brief I2S ���ͣ���ѯ��ʽ�����̣�ͨ��HW��ӿ�ʵ��
 *
 * - �������裺
 *   1. ����I2S ������Ž���TX_D0��TX_FS��TX_BCLK���߼������ǡ�
 *   2. ���Գ���
 *
 * - ʵ������
 *   1. �������߼��������Ͽ���TX_D0��TX_FS��TX_BCLK�����ݣ�
 *   2. ����TX_D0Ϊ�������ݵĲ��룬TX_FS��֡ʱ�ӣ�TX_BCLK��λʱ�ӡ�
 *
 * \par Դ����
 * \snippet demo_fsl_hw_i2s_polling.c src_fsl_hw_i2s_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-28 mkr , first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_fsl_if_hw_i2s_polling
 * \copydoc demo_fsl_hw_i2s_polling.c
 */

/** [src_fsl_hw_i2s_polling] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "hw/amhw_fsl_i2s.h"
#include "demo_fsl_entrys.h"

/**
 * \brief I2S �豸��ʼ��
 */
static void __i2s_init (amhw_fsl_i2s_t           *p_hw_i2s,
                        amhw_fsl_i2s_clock_cfg_t *p_i2s0_clk)
{
    /* ����I2Sʱ�� */
    p_i2s0_clk->bclk          = 256000UL ;
    p_i2s0_clk->bclk_src      = AMHW_FSL_I2S_BCLK_SRC_MCLK;
    p_i2s0_clk->bclk_src_freq = 4096000UL;
    p_i2s0_clk->mclk          = 4096000UL;
    p_i2s0_clk->mclk_src      = AMHW_FSL_I2S_MCLK_SRC_SYSCLK;

    /* ���ͼĴ�����ʼ�� */
    amhw_fsl_i2s_tx_init(p_hw_i2s);
    amhw_fsl_i2s_tx_clock_setup(p_hw_i2s, p_i2s0_clk);
    amhw_fsl_i2s_tx_sync_mode_set(p_hw_i2s, AMHW_FSL_I2S_SYNC_DISABLED);
    amhw_fsl_i2s_tx_mode_set(p_hw_i2s, AMHW_FSL_I2S_MODE_MASTER);
    amhw_fsl_i2s_tx_protocol_set(p_hw_i2s, AMHW_FSL_I2S_PROTOCOL_TYPE);
    amhw_fsl_i2s_tx_channel_mode_set(p_hw_i2s, AMHW_FSL_I2S_CHANNEL_MODE_STEREO);
    amhw_fsl_i2s_tx_channel_enable(p_hw_i2s);
    amhw_fsl_i2s_tx_word_width_cfg(p_hw_i2s, AMHW_FSL_I2S_PROTOCOL_TYPE, 32);

    amhw_fsl_i2s_tx_int_disable(p_hw_i2s, AMHW_FSL_I2S_INT_REQ_FIFO_WARN);
    amhw_fsl_i2s_tx_int_disable(p_hw_i2s, AMHW_FSL_I2S_INT_REQ_FIFO_ERROR);

    amhw_fsl_i2s_tx_enable(p_hw_i2s);

#if 0
    /* ���ռĴ�����ʼ�� */
    amhw_fsl_i2s_rx_init(p_hw_i2s);
    amhw_fsl_i2s_rx_clock_setup(p_hw_i2s, p_i2s0_clk);
    amhw_fsl_i2s_tx_int_disable(p_hw_i2s, AMHW_FSL_I2S_INT_REQ_ALL);
    amhw_fsl_i2s_rx_sync_mode_set(p_hw_i2s, AMHW_FSL_I2S_SYNC_SELF);
    amhw_fsl_i2s_rx_mode_set(p_hw_i2s, AMHW_FSL_I2S_MODE_MASTER);
    amhw_fsl_i2s_rx_protocol_set(p_hw_i2s, AMHW_FSL_I2S_PROTOCOL_TYPE);
    amhw_fsl_i2s_rx_channel_mode_set(p_hw_i2s, AMHW_FSL_I2S_CHANNEL_MODE_MONO);
    amhw_fsl_i2s_rx_channel_enable(p_hw_i2s);
    amhw_fsl_i2s_rx_word_width_cfg(p_hw_i2s, AMHW_FSL_I2S_PROTOCOL_TYPE, 32);
    amhw_fsl_i2s_rx_state_flag_clr(p_hw_i2s, AMHW_FSL_I2S_STATE_FLAG_ALL);
    amhw_fsl_i2s_rx_enable(p_hw_i2s);
#endif
}

/**
 * \brief i2s���ݷ��ͣ�����HW��ӿں���ʵ��
 * \return ��
 */
void demo_fsl_hw_i2s_polling_entry (amhw_fsl_i2s_t           *p_hw_i2s,
                                    amhw_fsl_i2s_clock_cfg_t *p_i2s0_clk)
{
    /** \brief I2S���ݷ��ͻ�����  */
    static uint32_t send_buf[6] = {0,1,2,3,4,5};

    __i2s_init(p_hw_i2s, p_i2s0_clk);

    am_kprintf("The I2S polling Demo \r\n");

    while(1) {

        /* ѭ�����ͻ����������� */
        amhw_fsl_i2s_senddata_polling(p_hw_i2s, send_buf, 6);
    }
}
/** [src_fsl_hw_i2s_polling] */

/* end of file */
