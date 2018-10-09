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
 * \brief I2S ���ͣ�DMA��ʽ�����̣�ͨ��HW��ӿ�ʵ��
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
 * \snippet demo_kl26_hw_i2s_dma.c src_kl26_hw_i2s_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-29 mkr , first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_hw_i2s_dma
 * \copydoc demo_kl26_hw_i2s_dma.c
 */

/** [src_kl26_hw_i2s_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_kl26_clk.h"
#include "am_kl26_inst_init.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_fsl_i2s.h"
#include "am_kl26_dma.h"
#include "am_int.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/** \brief ʹ��I2S0 */
#define I2S_DEV    KL26_I2S0

static volatile uint8_t __g_signal = 0;


/** \brief DAC_DMA������ɻص����� */
static void __am_fsl_i2s_dma_isr (void *p_arg , uint8_t flag);

/**
 * \brief I2S �豸��ʼ��
 */
static void __i2s_init (amhw_fsl_i2s_t *p_hw_i2s)
{
    /** \brief I2Sʱ������ */
    static amhw_fsl_i2s_clock_cfg_t i2s0_clk;

    /* ʹ��I2S ʱ���ſ� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_I2S);

    /* ����I2Sʱ�� */
    i2s0_clk.bclk          = 256000UL ;
    i2s0_clk.bclk_src      = AMHW_FSL_I2S_BCLK_SRC_MCLK;
    i2s0_clk.bclk_src_freq = 4096000UL;
    i2s0_clk.mclk          = 4096000UL;
    i2s0_clk.mclk_src      = AMHW_FSL_I2S_MCLK_SRC_SYSCLK;
    i2s0_clk.mclk_src_freq = am_kl26_clk_core_clkrate_get();

    /* ���ͼĴ�����ʼ�� */
    amhw_fsl_i2s_tx_init(p_hw_i2s);
    amhw_fsl_i2s_tx_clock_setup(p_hw_i2s, &i2s0_clk);
    amhw_fsl_i2s_tx_sync_mode_set(p_hw_i2s, AMHW_FSL_I2S_SYNC_DISABLED);
    amhw_fsl_i2s_tx_mode_set(p_hw_i2s, AMHW_FSL_I2S_MODE_MASTER);
    amhw_fsl_i2s_tx_protocol_set(p_hw_i2s, AMHW_FSL_I2S_PROTOCOL_TYPE);
    amhw_fsl_i2s_tx_channel_mode_set(p_hw_i2s, AMHW_FSL_I2S_CHANNEL_MODE_STEREO);
    amhw_fsl_i2s_tx_channel_enable(p_hw_i2s);
    amhw_fsl_i2s_tx_word_width_cfg(p_hw_i2s, AMHW_FSL_I2S_PROTOCOL_TYPE, 32);

    amhw_fsl_i2s_tx_int_disable(p_hw_i2s, AMHW_FSL_I2S_INT_REQ_FIFO_WARN);
    amhw_fsl_i2s_tx_int_disable(p_hw_i2s, AMHW_FSL_I2S_INT_REQ_FIFO_ERROR);

    amhw_fsl_i2s_tx_dma_request_enable(p_hw_i2s);

    amhw_fsl_i2s_tx_enable(p_hw_i2s);

#if 0
    /* ���ռĴ�����ʼ�� */
    amhw_fsl_i2s_rx_init(p_hw_i2s);
    amhw_fsl_i2s_rx_clock_setup(p_hw_i2s, &i2s0_clk);
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

/** \brief DMA ��ʼ������ */
static void _fsl_i2s_dma_init (uint8_t            dma_chan,
                               uint32_t          *p_dest,
                               uint32_t          *p_src,
                               uint32_t           lenth)
{
    uint32_t flags;
    amhw_kl26_dma_xfer_desc_t dma_desc;

    /* DMA�������� */
    flags = KL26_DMA_DCR_PER_REQUEST_ENABLE      |  /* ��������Դʹ��    */
            KL26_DMA_DCR_SINGLE_TRANSFERS        |  /* ���δ���          */
            KL26_DMA_DCR_AUTO_ALIGN_DISABLE      |  /* �Զ��������      */
            KL26_DMA_DCR_SOURCE_SIZE_32_BIT      |  /* Դ��ַ4�ֽڶ�ȡ   */
            KL26_DMA_DCR_SOURCE_SIZE_32_BIT      |  /* Ŀ�ĵ�ַ4�ֽ�д�� */
            KL26_DMA_DCR_REQUEST_AFFECTED        |  /* ������Ӱ��        */
            KL26_DMA_DCR_NO_LINKING              |  /* ��ͨ������        */
            KL26_DMA_DCR_INTERRUTP_ENABLE        |  /* DMA�ж�ʹ��       */
            KL26_DMA_DCR_START_DISABLE    ;         /* DMA��ʼ�������   */

    /* ����DMA�жϷ����� */
    am_kl26_dma_isr_connect(dma_chan, __am_fsl_i2s_dma_isr, I2S_DEV);

    am_kl26_dma_chan_cfg(dma_chan,
                         KL26_DMA_TRIGGER_DISABLE | /**< \brief DMA����ģʽ */
                         DMA_REQUEST_MUX0_I2S0TX);       /**< \brief I2S����Դ      */

    /* ����ͨ�������� */
    am_kl26_dma_xfer_desc_build(&dma_desc,              /* ͨ��������   */
                                (uint32_t)(p_src),      /* Դ�����ݻ��� */
                                (uint32_t)(p_dest),     /* Ŀ�����ݻ��� */
                                (uint32_t)(lenth << 2), /* �����ֽ���   */
                                flags);                 /* ��������     */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_kl26_dma_chan_start(&dma_desc,
                               KL26_DMA_MER_TO_PER, /*  �ڴ浽����  */
                               dma_chan) == AM_ERROR) {
        am_kprintf("DMA init error!\n");
    }

}

/** \brief DAC_DMA������ɻص����� */
static void __am_fsl_i2s_dma_isr (void *p_arg , uint8_t flag)
{
    amhw_fsl_i2s_t *p_hw_i2s = (amhw_fsl_i2s_t *)p_arg;

    if (flag == AM_KL26_DMA_INT_NORMAL) {

        /* FIFO���������λ */
        if ((amhw_fsl_i2s_tcsr_get(p_hw_i2s) & AMHW_FSL_I2S_TCSR_FEF_MASK)) {
            amhw_fsl_i2s_tx_state_flag_clr(p_hw_i2s,AMHW_FSL_I2S_STATE_FLAG_FIFO_ERROR);
            amhw_fsl_i2s_tx_reset_set(p_hw_i2s,AMHW_FSL_I2S_RESET_TYPE_FIFO);
        }
        /* FIFO�� */
        if ((amhw_fsl_i2s_tcsr_get(p_hw_i2s) & AMHW_FSL_I2S_TCSR_FWF_MASK)) {
            __g_signal = 1;
            amhw_fsl_i2s_tx_dma_request_disable(p_hw_i2s);
        }
    }
}

/**
 * \brief i2s dma��ʽ���ݷ��ͣ�����HW��ӿں���ʵ��
 * \return ��
 */
void demo_kl26_hw_i2s_dma_entry (void)
{

    /** \brief I2S���ݷ��ͻ�����  */
    uint32_t send_buf[10] = {1,2,3,4,5,6,7,8,9,10};

    am_kl26_dma_inst_init();       /* DMAʵ����ʼ��            */
    _fsl_i2s_dma_init(DMA_CHAN_0,  /* DMA�����ʼ�� */
                      (uint32_t *)&(I2S_DEV->tdr),
                      send_buf,
                      10);
    __i2s_init(I2S_DEV);
    am_kprintf("The I2S dma Demo \r\n");

    while(1) {
        if (1 == __g_signal) {
            __g_signal = 0;
        _fsl_i2s_dma_init(DMA_CHAN_0, /* DMA�����ʼ�� */
                          (uint32_t *)&(I2S_DEV->tdr),
                          send_buf,
                          10);
            amhw_fsl_i2s_tx_dma_request_enable(I2S_DEV);
        }
    }
}
/** [src_kl26_hw_i2s_dma] */

/* end of file */
