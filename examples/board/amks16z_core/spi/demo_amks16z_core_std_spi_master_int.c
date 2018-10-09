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
 * \brief ��SPIΪ������ʾ��SPI��Transfer��ʹ�÷�����ͨ����׼�ӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI MOSI��MISO�̽�(PIOD2 == PIOD_3),����ӻ��豸����
 *   2. ���°�������һ������
 *
 * - ʵ������:
 * \note
 *   1. ����ͨ�� MOSI �������ݣ����������ݴ� MOSI ���أ�
 *   2. ���Դ��ڴ�ӡ���Խ����
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_spi_master_int.c src_amks16z_core_std_spi_master_int
 *
 * \internal
 * \par History
 * - 1.00 16-09-30  sdy, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_std_spi_master_int
 * \copydoc demo_amks16z_core_std_spi_master_int.c
 */
 
/** [src_amks16z_core_std_spi_master_int] */
#include "ametal.h"
#include "am_prj_config.h"
#include "am_spi.h"
#include "am_wait.h"
#include "am_gpio.h"
#include "am_kl26_inst_init.h"
#include "am_buzzer.h"
#include "am_board.h"
#include "demo_std_entries.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief �������
 */
void demo_amks16z_core_std_spi_master_int_entry (void)
{
    int             cs_pin;
    am_spi_handle_t spi_handle = am_kl26_spi0_int_inst_init();

    cs_pin     = PIOD_0;
    demo_std_spi_master_entry(spi_handle, cs_pin);
}

/** [src_amks16z_core_std_spi_master_int] */

/* end of file */
