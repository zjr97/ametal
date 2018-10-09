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
 * \snippet demo_amks16z_core_hw_i2s_dma.c src_amks16z_core_hw_i2s_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-29 mkr , first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_i2s_dma
 * \copydoc demo_amks16z_core_hw_i2s_dma.c
 */

/** [src_amks16z_core_hw_i2s_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_kl26_inst_init.h"
#include "am_int.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief i2s dma��ʽ���ݷ��ͣ�����HW��ӿں���ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_i2s_dma_entry (void)
{
    AM_DBG_INFO("demo amks16z_core hw i2s dma!\r\n");

    /* ����I2S �������� */
    am_gpio_pin_cfg(PIOC_1, PIOC_1_I2S0_TXD0);     /* TX_D0   */
    am_gpio_pin_cfg(PIOC_2, PIOC_2_I2S0_TX_FS);    /* TX_FS   */
    am_gpio_pin_cfg(PIOC_3, PIOC_3_I2S0_TX_BCLK);  /* TX_BCLK */
    am_gpio_pin_cfg(PIOC_4, PIOC_4_I2S0_MCLK);     /* MCLK    */
    am_gpio_pin_cfg(PIOC_5, PIOC_5_I2S0_RXD0);     /* RX_D0   */
    am_gpio_pin_cfg(PIOC_6, PIOC_6_I2S0_RX_BCLK);  /* RX_BCLK */
    am_gpio_pin_cfg(PIOC_7, PIOC_7_I2S0_RX_FS);    /* RX_FS   */

    demo_kl26_hw_i2s_dma_entry();
}
/** [src_amks16z_core_hw_i2s_dma] */

/* end of file */
