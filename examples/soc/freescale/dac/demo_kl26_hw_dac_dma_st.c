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
 * \brief DAC��ģת�����̣�ͨ��HW�ӿ�ʵ�֣�DMA��������
 *
 * - ʵ������
 *   1. �ɼ���ģת���������PE30�ĵ�ѹֵ
 *
 *
 * \par Դ����
 * \snippet demo_kl26_hw_dac_dma_st.c src_kl26_hw_dac_dma_st
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-27  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_hw_dac_dma_st
 * \copydoc demo_kl26_hw_dac_dma_st.c
 */

 /** [src_kl26_hw_dac_dma_st] */
#include "ametal.h"
#include "am_dac.h"
#include "am_fsl_dac.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_kl26_inst_init.h"
#include "am_kl26_dma.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_fsl_dac.h"
#include "am_int.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

#define   __BUFLEN  360

static volatile uint8_t  __g_signal = 0;

static const uint16_t __g_sin_wave[__BUFLEN] = { /* ���Ҳ����� */
    0x0800, 0x0823, 0x0847, 0x086B, 0x088E, 0x08B2, 0x08D6, 0x08F9,
    0x091C, 0x0940, 0x0963, 0x0986, 0x09A9, 0x09CC, 0x09EF, 0x0A11,
    0x0A34, 0x0A56, 0x0A78, 0x0A9A, 0x0ABC, 0x0ADD, 0x0AFF, 0x0B20,
    0x0B40, 0x0B61, 0x0B81, 0x0BA1, 0x0BC1, 0x0BE0, 0x0BFF, 0x0C1E,
    0x0C3D, 0x0C5B, 0x0C78, 0x0C96, 0x0CB3, 0x0CD0, 0x0CEC, 0x0D08,
    0x0D24, 0x0D3F, 0x0D5A, 0x0D74, 0x0D8E, 0x0DA7, 0x0DC0, 0x0DD9,
    0x0DF1, 0x0E09, 0x0E20, 0x0E37, 0x0E4D, 0x0E63, 0x0E78, 0x0E8D,
    0x0EA1, 0x0EB5, 0x0EC8, 0x0EDB, 0x0EED, 0x0EFE, 0x0F0F, 0x0F20,
    0x0F30, 0x0F3F, 0x0F4E, 0x0F5C, 0x0F6A, 0x0F77, 0x0F84, 0x0F8F,
    0x0F9B, 0x0FA6, 0x0FB0, 0x0FB9, 0x0FC2, 0x0FCB, 0x0FD2, 0x0FD9,
    0x0FE0, 0x0FE6, 0x0FEB, 0x0FF0, 0x0FF4, 0x0FF7, 0x0FFA, 0x0FFC,
    0x0FFE, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFE, 0x0FFC, 0x0FFA, 0x0FF7,
    0x0FF4, 0x0FF0, 0x0FEB, 0x0FE6, 0x0FE0, 0x0FD9, 0x0FD2, 0x0FCB,
    0x0FC2, 0x0FB9, 0x0FB0, 0x0FA6, 0x0F9B, 0x0F8F, 0x0F84, 0x0F77,
    0x0F6A, 0x0F5C, 0x0F4E, 0x0F3F, 0x0F30, 0x0F20, 0x0F0F, 0x0EFE,
    0x0EED, 0x0EDB, 0x0EC8, 0x0EB5, 0x0EA1, 0x0E8D, 0x0E78, 0x0E63,
    0x0E4D, 0x0E37, 0x0E20, 0x0E09, 0x0DF1, 0x0DD9, 0x0DC0, 0x0DA7,
    0x0D8E, 0x0D74, 0x0D5A, 0x0D3F, 0x0D24, 0x0D08, 0x0CEC, 0x0CD0,
    0x0CB3, 0x0C96, 0x0C78, 0x0C5B, 0x0C3D, 0x0C1E, 0x0BFF, 0x0BE0,
    0x0BC1, 0x0BA1, 0x0B81, 0x0B61, 0x0B40, 0x0B20, 0x0AFF, 0x0ADD,
    0x0ABC, 0x0A9A, 0x0A78, 0x0A56, 0x0A34, 0x0A11, 0x09EF, 0x09CC,
    0x09A9, 0x0986, 0x0963, 0x0940, 0x091C, 0x08F9, 0x08D6, 0x08B2,
    0x088E, 0x086B, 0x0847, 0x0823, 0x0800, 0x07DC, 0x07B8, 0x0794,
    0x0771, 0x074D, 0x0729, 0x0706, 0x06E3, 0x06BF, 0x069C, 0x0679,
    0x0656, 0x0633, 0x0610, 0x05EE, 0x05CB, 0x05A9, 0x0587, 0x0565,
    0x0543, 0x0522, 0x0500, 0x04DF, 0x04BF, 0x049E, 0x047E, 0x045E,
    0x043E, 0x041F, 0x0400, 0x03E1, 0x03C2, 0x03A4, 0x0387, 0x0369,
    0x034C, 0x032F, 0x0313, 0x02F7, 0x02DB, 0x02C0, 0x02A5, 0x028B,
    0x0271, 0x0258, 0x023F, 0x0226, 0x020E, 0x01F6, 0x01DF, 0x01C8,
    0x01B2, 0x019C, 0x0187, 0x0172, 0x015E, 0x014A, 0x0137, 0x0124,
    0x0112, 0x0101, 0x00F0, 0x00DF, 0x00CF, 0x00C0, 0x00B1, 0x00A3,
    0x0095, 0x0088, 0x007B, 0x0070, 0x0064, 0x0059, 0x004F, 0x0046,
    0x003D, 0x0034, 0x002D, 0x0026, 0x001F, 0x0019, 0x0014, 0x000F,
    0x000B, 0x0008, 0x0005, 0x0003, 0x0001, 0x0000, 0x0000, 0x0000,
    0x0001, 0x0003, 0x0005, 0x0008, 0x000B, 0x000F, 0x0014, 0x0019,
    0x001F, 0x0026, 0x002D, 0x0034, 0x003D, 0x0046, 0x004F, 0x0059,
    0x0064, 0x0070, 0x007B, 0x0088, 0x0095, 0x00A3, 0x00B1, 0x00C0,
    0x00CF, 0x00DF, 0x00F0, 0x0101, 0x0112, 0x0124, 0x0137, 0x014A,
    0x015E, 0x0172, 0x0187, 0x019C, 0x01B2, 0x01C8, 0x01DF, 0x01F6,
    0x020E, 0x0226, 0x023F, 0x0258, 0x0271, 0x028B, 0x02A5, 0x02C0,
    0x02DB, 0x02F7, 0x0313, 0x032F, 0x034C, 0x0369, 0x0387, 0x03A4,
    0x03C2, 0x03E1, 0x0400, 0x041F, 0x043E, 0x045E, 0x047E, 0x049E,
    0x04BF, 0x04DF, 0x0500, 0x0522, 0x0543, 0x0565, 0x0587, 0x05A9,
    0x05CB, 0x05EE, 0x0610, 0x0633, 0x0656, 0x0679, 0x069C, 0x06BF,
    0x06E3, 0x0706, 0x0729, 0x074D, 0x0771, 0x0794, 0x07B8, 0x07DC,
};

/** \brief DAC_DMA������ɻص����� */
static void __am_kl26_dac_dma_isr (void *p_arg , uint8_t flag)
{
    if (flag == AM_KL26_DMA_INT_NORMAL) {
        __g_signal = 1;
    }
}

/** \brief DMA ��ʼ������ */
static void _kl26_dac_dma_init (uint8_t   dma_chan, uint8_t *p_dest,
                          const uint16_t *p_src,    uint32_t  lenth)
{
    uint32_t flags;
    amhw_kl26_dma_xfer_desc_t dma_desc;

    /* DMA�������� */
    flags = KL26_DMA_DCR_PER_REQUEST_ENABLE      |  /* ��������Դʹ��    */
            KL26_DMA_DCR_SINGLE_TRANSFERS        |  /* ���δ���          */
            KL26_DMA_DCR_AUTO_ALIGN_DISABLE      |  /* �Զ��������      */
            KL26_DMA_DCR_SOURCE_SIZE_16_BIT      |  /* Դ��ַ2�ֽڶ�ȡ   */
            KL26_DMA_DCR_SOURCE_SIZE_16_BIT      |  /* Ŀ�ĵ�ַ2�ֽ�д�� */
            KL26_DMA_DCR_REQUEST_AFFECTED        |  /* ������Ӱ��        */
            KL26_DMA_DCR_NO_LINKING              |  /* ��ͨ������        */
            KL26_DMA_DCR_INTERRUTP_ENABLE        |  /* DMA�ж�ʹ��       */
            KL26_DMA_DCR_START_DISABLE    ;         /* DMA��ʼ�������   */

    /* ����DMA�жϷ����� */
    am_kl26_dma_isr_connect(dma_chan, __am_kl26_dac_dma_isr, NULL);

    am_kl26_dma_chan_cfg(dma_chan,
                         KL26_DMA_TRIGGER_DISABLE | /**< \brief DMA����ģʽ */
                         DMA_REQUEST_MUX0_DAC0);         /**< \brief DAC����Դ      */

    /* ����ͨ�������� */
    am_kl26_dma_xfer_desc_build(&dma_desc,              /* ͨ��������   */
                                (uint32_t)(p_src),      /* Դ�����ݻ��� */
                                (uint32_t)(p_dest),     /* Ŀ�����ݻ��� */
                                (uint32_t)(lenth << 1), /* �����ֽ���   */
                                flags);                 /* ��������     */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_kl26_dma_chan_start(&dma_desc,
                               KL26_DMA_MER_TO_PER, /*  �ڴ浽����  */
                               dma_chan) == AM_ERROR) {
        am_kprintf("DMA init error!\n");
    }

}

/** \brief DAC ��ʼ������ */
static void _kl26_dac_init (void)
{
    /**
     * \brief DAC �������������ýṹ�嶨��
     */
    amhw_fsl_dac_buffer_config_t dac_buf_cfg = {
        AM_TRUE,                         /* ʹ��BUF����                   */
        AMHW_FSL_DAC_TRG_SOFT,           /* �������                           */
        AM_TRUE,                         /* �����ȡ��ָ���ж�ʹ�� */
        AM_FALSE,                        /* �����ȡ��ָ���жϽ��� */
        AM_TRUE,                         /* ʹ��DMA����                    */
        AMHW_FSL_DAC_BUFMODE_NORMAL,     /* ������ģʽΪ����ģʽ      */
        AM_TRUE,                         /* ����������ʹ��                 */
    };

    /* ����PIOE_30ΪDAC0_OUT����                 */
    am_gpio_pin_cfg (PIOE_30, PIOE_30_DAC0_OUT);

    /* ����DACʱ��                               */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_DAC0);

    /* DAC����������ʹ�� */
    amhw_fsl_dac_dat_buf_init(KL26_DAC0, &dac_buf_cfg);

    /* ʹ��DACģ�� */
    amhw_fsl_dac_enable(KL26_DAC0);
}

/** \brief ����DACת�� */
static void _kl26_dac_start (void)
{
    amhw_fsl_dac_soft_trg_enable(KL26_DAC0);
}

/**
 * \brief DAC�����ѹ��DMA�������ݣ�HW��ӿ�ʵ��
 * \return ��
 */
void demo_kl26_hw_dac_dma_st_entry (void)
{
    uint32_t key;

    am_kl26_dma_inst_init();       /* DMAʵ����ʼ��            */
    _kl26_dac_dma_init(DMA_CHAN_0, /* DAC DMA�����ʼ�� */
                       (uint8_t *)&(KL26_DAC0->dat),
                       __g_sin_wave,
                       __BUFLEN);
    _kl26_dac_init();              /* DAC ��ʼ�� */

    _kl26_dac_start();             /* ����DAC */

    am_kprintf("DAC hw dac dma test\n");

    while (1) {
        key = am_int_cpu_lock();
        if (1 == __g_signal) {
            __g_signal = 0;
            am_int_cpu_unlock(key);
            _kl26_dac_dma_init(DMA_CHAN_0,
                               (uint8_t *)&(KL26_DAC0->dat),
                               __g_sin_wave,
                               __BUFLEN);
        } else {
            am_int_cpu_unlock(key);
        }

        _kl26_dac_start();

        am_mdelay(20);
    }
}


 /** [src_kl26_hw_dac_dma_st] */

/* end of file */

