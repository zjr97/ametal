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
 * \brief KL26���������ļ�
 * \sa am_prj_config.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-13 nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_prj_config.h"
#include "am_kl26_inst_init.h"
#include "am_softimer.h"
#include "hw/amhw_kl26_sim.h"
#include "am_board.h"
#include "am_nvram_cfg.h"

/** \brief am_main�ⲿ���� */
extern int am_main (void);

/** \brief main������� */
int main (void)
{
#if 0
    am_timer_handle_t tmp2_tmrhdl;
    am_timer_info_t   tmp2_tmrinfo;
#endif

    /* �ر�COP���Ź� */
#if (AM_CFG_SIM_COP == 0)
    amhw_kl26_sim_cop_cfg(KL26_SIM_COP_MODE_NORMAL,
                          KL26_SIM_COP_CLK_INTERNAL,
                          KL26_SIM_COP_DISABLED);
#endif

    /* ϵͳʱ�ӳ�ʼ�� */
#if (AM_CFG_CLK_ENABLE == 1)
    am_kl26_clk_inst_init();
#endif

    /* �жϳ�ʼ�� */
#if (AM_CFG_INT_ENABLE == 1)
    am_kl26_nvic_inst_init();
#endif

    /* GPIO��ʼ�� */
#if (AM_CFG_GPIO_ENABLE == 1)
    am_kl26_gpio_inst_init();
#endif

#if (AM_CFG_DMA_ENABLE == 1)
    am_kl26_dma_inst_init();
#endif

#if (AM_CFG_NVRAM_ENABLE == 1)
    am_nvram_inst_init();
#endif /* (AM_CFG_NVRAM_ENABLE == 1) */

    /* �弶��ʼ�� */
    am_board_init();
#if 0
    /* ADC Ӳ������ʱ��Ҫ������ʱ����Ĭ������TMP2��ΪADCӲ������Դ */
    tmp2_tmrhdl = am_kl26_tpm2_timing_inst_init();
    am_timer_info_get(tmp2_tmrhdl, &tmp2_tmrinfo);

    /* 20HzӲ���������� */
    am_timer_enable(tmp2_tmrhdl, 0, tmp2_tmrinfo.clk_frequency / 50);
#endif

    return am_main();
}

/**
 * @}
 */

/* end of file */
