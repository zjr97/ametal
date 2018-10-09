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
 * \brief ��SPI�ж�ģʽ�²���SPI_FLASH��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI�ӿں�SPI_FLASH��Ӧ�Ľӿ�����������
 *   2. ���Ӵ��ڣ�������Ϊ115200��8������λ��1ֹͣλ����У�飻
 *   3. ���������ص�demo�壬�����ϵ���߸�λ��
 *
 * - ʵ������:
 *   1. ��SPI_FLASH�ж�ȡ�������ݣ�ͨ�����ڴ�ӡ������
 *   2. д�����ݺͶ�ȡ��������ͬ��SPI_FLASH��д���Գɹ���LED0��200ms�����˸��
 *
 * \note
 *   1. �ɼ������������£�ֱ��ʹ�� am_spi_write_then_read() �� 
 *      am_spi_write_then_write() �������ɡ�
 *
 * \par Դ����
 * \snippet demo_amks16z_core_std_spi_flash_dma.c src_amks16z_core_std_spi_flash_dma
 *
 * \internal
 * \par History
 * - 1.01 15-11-27  sky, modified.
 * - 1.00 15-07-16  aii, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_std_spi_flash_dma
 * \copydoc demo_amks16z_core_std_spi_flash_dma.c
 */
 
/** [src_amks16z_core_std_spi_flash_dma] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_spi.h"
#include "am_kl26_inst_init.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "demo_std_entries.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \brief STD��SPI��дFlash���Ժ������
 *
 * \param[in] spi_handle : SPI��׼����������
 * \param[in] cs_pin     : �û��Զ���Ƭѡ��
 *
 * \return ��
 */
void demo_amks16z_core_std_spi_flash_dma_entry (void)
{
    int             cs_pin;
    am_spi_handle_t spi_handle;

    cs_pin     = PIOD_0;
    spi_handle = am_kl26_spi0_dma_inst_init();

    demo_std_spi_flash_entry(spi_handle, cs_pin, 0, 24);
}

/** [src_amks16z_core_std_spi_flash_dma] */

/* end of file */
