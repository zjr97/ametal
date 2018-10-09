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
 * \brief ��I2C��ѯģʽ�´�LM75��������ȡ�¶�ֵ��ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *       1. ��J11��J13������ñ���ӣ�
 *       2. ���������������ӡ�
 *
 * - ʵ������:
 *       ��LM75���������¶�ֵ�򴮿ڴ�ӡ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_i2c_master_poll.c src_amks16z_core_hw_i2c_master_poll
 * 
 * \internal
 * \par History
 * - 1.00 16-09-22  ari, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_i2c_master_poll
 * \copydoc demo_amks16z_core_hw_i2c_master_poll.c
 */
 
/** [src_amks16z_core_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_kl26_clk.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_sim.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/kl26_periph_map.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief ���Ժ������
 */
void demo_amks16z_core_hw_i2c_master_poll_entry (void)
{

    uint32_t i2c_clk;

    AM_DBG_INFO("demo amks16z_core hw i2c master poll!\r\n");

    /**
     * PIOC_10 ~ I2C1_SCL, PIOC_11 ~ I2C1_SDA;
     */
    am_gpio_pin_cfg(PIOC_10, PIOC_10_I2C1_SCL);
    am_gpio_pin_cfg(PIOC_11, PIOC_11_I2C1_SDA);

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_I2C1);

    i2c_clk = am_kl26_clk_periph_rate_get(KL26_I2C1);

    demo_fsl_hw_i2c_master_poll_entry(KL26_I2C1, i2c_clk);
}

/** [src_amks16z_core_hw_i2c_master_poll] */

/* end of file */
