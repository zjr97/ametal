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
 * \brief CLK ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������Ƶ�ʣ�
 *   2. PIOA_9 ���ϵͳʱ�ӣ�SYSCLK����
 *
 * \note
 *    1. ����Ĭ�ϵ��Դ��� TXD Ϊ PIOA_9����ʱ��������ų�ͻ�����Ա������еĵ�����Ϣ
 *       ͨ�� PIOA_2 ���������۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_2 �������� PC ��
 *       �ڵ� RXD��
 * 
 * \par Դ����
 * \snippet demo_am116_core_hw_clk.c src_am116_core_hw_clk
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-7-13  sss, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am116_core_hw_clk
 * \copydoc demo_am116_core_hw_clk.c
 */

/** [src_am116_core_hw_clk] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg116.h"
#include "am_zlg116_inst_init.h"
#include "demo_zlg_entries.h"

/** \brief ���õ��Դ�������Ĳ����� */
#define __DEBUG_BAUDRATE        115200

/**
 * \brief ��ʼ������ 2 Ϊ���Դ���
 */
am_local void __uart_init (void)
{
    am_uart_handle_t handle = NULL;

    handle = am_zlg116_uart2_inst_init();

    /* ���Գ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE);
}

/**
 * \brief �������
 */
void demo_am116_core_hw_clk_entry (void)
{
    am_clk_id_t clk_id[] = {CLK_PLLIN,
                            CLK_PLLOUT,
                            CLK_AHB,
                            CLK_APB1,
                            CLK_APB2,
                            CLK_HSEOSC,
                            CLK_LSI,
                            CLK_HSI};

    __uart_init();

    AM_DBG_INFO("demo am116_core hw clk!\r\n");

    am_gpio_pin_cfg(PIOA_9, PIOA_9_MCO | PIOA_9_AF_PP | PIOA_9_SPEED_50MHz);

    amhw_zlg116_rcc_mco_src_set(4);

    demo_zlg_hw_clk_entry(&clk_id[0], AM_NELEMENTS(clk_id));
}
/** [src_am116_core_hw_clk] */

/* end of file */
