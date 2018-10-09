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
 * \brief I2S ���ͣ��жϷ�ʽ�����̣�ͨ��HW��ӿ�ʵ��
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
 * \snippet demo_amks16z_core_hw_i2s_int.c src_amks16z_core_hw_i2s_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-28 mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16z_core_if_hw_i2s_int
 * \copydoc demo_amks16z_core_hw_i2s_int.c
 */

/** [src_amks16z_core_hw_i2s_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_kl26_clk.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_sim.h"
#include "am_int.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \brief i2s�ж����ݷ��ͣ�����HW��ӿں���ʵ��
 * \return ��
 */
void demo_amks16z_core_hw_i2s_int_entry (void)
{
    /** \brief I2Sʱ������ */
    static amhw_fsl_i2s_clock_cfg_t i2s0_clk;

    /** \brief ����I2S �������� */
    am_gpio_pin_cfg (PIOC_1,  PIOC_1_I2S0_TXD0);     /* TX_D0   */
    am_gpio_pin_cfg (PIOC_2,  PIOC_2_I2S0_TX_FS);    /* TX_FS   */
    am_gpio_pin_cfg (PIOC_3,  PIOC_3_I2S0_TX_BCLK);  /* TX_BCLK */
    am_gpio_pin_cfg (PIOC_4,  PIOC_4_I2S0_MCLK);     /* MCLK    */
    am_gpio_pin_cfg (PIOC_5,  PIOC_5_I2S0_RXD0);     /* RX_D0   */
    am_gpio_pin_cfg (PIOC_6,  PIOC_6_I2S0_RX_BCLK);  /* RX_BCLK */
    am_gpio_pin_cfg (PIOC_7,  PIOC_7_I2S0_RX_FS);    /* RX_FS   */

    /** \brief ʹ��I2S ʱ���ſ� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_I2S);

    i2s0_clk.mclk_src_freq = am_kl26_clk_core_clkrate_get();

    demo_fsl_hw_i2s_int_entry(KL26_I2S0, INUM_I2S, &i2s0_clk);

}
/** [src_amks16z_core_hw_i2s_int] */

/* end of file */
