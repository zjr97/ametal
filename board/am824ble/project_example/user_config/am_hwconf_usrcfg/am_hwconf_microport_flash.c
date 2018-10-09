/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief MicroPort-FLASH(MX25xx) �û������ļ�
 * \sa am_hwconf_microport_flash.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_mtd.h"
#include "am_ftl.h"
#include "am_mx25xx.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_microport_flash
 * \copydoc am_hwconf_microport_flash.c
 * @{
 */

/** \brief MicroPort-FLASH �豸��Ϣ */
am_local am_const am_mx25xx_devinfo_t __g_microport_flash_devinfo = {
    AM_SPI_MODE_0,         /* ʹ��ģʽ 0 */
    PIO0_1,                /* Ƭѡ���� */
    30000000,              /* �������� */
    AM_MX25XX_MX25L1606    /* �����ͺ� */
};

/*******************************************************************************
  MicroPort-FLASH(MX25xx) ʵ����ʼ��
*******************************************************************************/

/** \brief MicroPort-FLASH �豸ʵ�� */
am_local am_mx25xx_dev_t __g_microport_flash_dev;

/**
 * \brief MicroPort-FLASH ʵ����ʼ��
 */
am_mx25xx_handle_t am_microport_flash_inst_init (void)
{
    am_spi_handle_t spi_handle = am_lpc82x_spi0_dma_inst_init();

    return am_mx25xx_init(&__g_microport_flash_dev,
                          &__g_microport_flash_devinfo,
                           spi_handle);
}

/*******************************************************************************
  MTD ʵ����ʼ��
*******************************************************************************/

/** \brief MicroPort-FLASH (MTD) �豸ʵ�� */
am_local am_mtd_serv_t __g_microport_flash_mtd_serv;

/**
 * \brief MicroPort-FLASH ʵ����ʼ����ʹ�� MTD ��׼�ӿڣ�
 */
am_mtd_handle_t am_microport_flash_mtd_inst_init (void)
{
    am_mx25xx_handle_t handle = am_microport_flash_inst_init();

    return am_mx25xx_mtd_init(handle,
                             &__g_microport_flash_mtd_serv,
                              0);
}

/*******************************************************************************
  FTL ʵ����ʼ��
*******************************************************************************/

#define __FTL_LOGIC_BLOCK_SZIE    256          /**< \brief �߼����С */
#define __FTL_LOG_BLOCK_NUM       2            /**< \brief ��־�������2~10�� */

#define __CHIP_SZIE          (2 * 1024 * 1024) /**< \brief ������ */
#define __ERASE_UNIT_SZIE    4096              /**< \brief ��С������Ԫ��С */

/** \brief MicroPort-FLASH (FTL) �豸ʵ�� */
am_local am_ftl_serv_t __g_microport_flash_ftl_serv;

/**
 * \brief MicroPort-FLASH RAM ����������
 */
am_local uint8_t __g_ftl_buf[AM_FTL_RAM_SIZE_GET(__CHIP_SZIE,
                                                 __ERASE_UNIT_SZIE,
                                                 __FTL_LOGIC_BLOCK_SZIE,
                                                 __FTL_LOG_BLOCK_NUM)];

/** \brief MicroPort-FLASH FTL ��Ϣ */
am_local am_const am_ftl_info_t __g_ftl_info = {
    __g_ftl_buf,               /* RAM ������ */
    sizeof(__g_ftl_buf),       /* RAM ��������С */
    __FTL_LOGIC_BLOCK_SZIE,    /* �߼���Ĵ�С */
    __FTL_LOG_BLOCK_NUM,       /* ��־����� */
    0                          /* ����������飨������Ԫ������ */
};

/**
 * \brief MicroPort-FLASH ʵ����ʼ����ʹ�� FTL ��׼�ӿڣ�
 */
am_ftl_handle_t am_microport_flash_ftl_inst_init (void)
{
    return am_ftl_init(&__g_microport_flash_ftl_serv,
                       &__g_ftl_info,
                       am_microport_flash_mtd_inst_init());
}

/**
 * @}
 */

/* end of file */
