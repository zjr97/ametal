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
 * \brief MicroPort FLASH(MX25xx) �����ļ�
 * \sa am_hwconf_microport_flash.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_mtd.h"
#include "am_mx25xx.h"
#include "am_zlg217_inst_init.h"
#include "zlg217_pin.h"

/**
 * \addtogroup am_if_src_hwconf_microport_flash
 * \copydoc am_hwconf_microport_flash.c
 * @{
 */

/** \brief �豸��Ϣ */
am_local am_const am_mx25xx_devinfo_t __g_microport_flash_devinfo = {
    AM_SPI_MODE_0,          /**< \brief ʹ��ģʽ 0 */
    PIOA_4,                 /**< \brief Ƭѡ���� */
    30000000,               /**< \brief �������� */
    AM_MX25XX_MX25L1606     /**< \brief �����ͺ� */
};

/*******************************************************************************
  MicroPort FLASH(MX25xx) ʵ����ʼ��
*******************************************************************************/

/** \brief �豸���� */
am_local am_mx25xx_dev_t __g_microport_flash_dev;

/** \brief ʵ����ʼ�� */
am_mx25xx_handle_t am_microport_flash_inst_init (void)
{

    /* ��ȡ SPI0 ʵ����� */
    am_spi_handle_t spi_handle = am_zlg217_spi1_dma_inst_init();

    return am_mx25xx_init(&__g_microport_flash_dev,
                          &__g_microport_flash_devinfo,
                           spi_handle);
}

/*******************************************************************************
  MTD ʵ����ʼ��
*******************************************************************************/

/** \brief �豸���� */
am_local am_mtd_serv_t __g_microport_flash_mtd;

/** \brief ʵ����ʼ�� */
am_mtd_handle_t am_microport_flash_mtd_inst_init (void)
{
    am_mx25xx_handle_t microport_flash_handle = am_microport_flash_inst_init();

    return am_mx25xx_mtd_init(microport_flash_handle,
                             &__g_microport_flash_mtd,
                              0);
}

/*******************************************************************************
  FTL ʵ����ʼ��
*******************************************************************************/

#include "am_ftl.h"

#define  MX25XX_FTL_LOGIC_BLOCK_SZIE  256 /**< \brief �߼����С���Զ��壩  */
#define  MX25XX_FTL_LOG_BLOCK_NUM     2   /**< \brief ��־�������2 ~ 10,�Զ��壩*/

/*
 * ���� AM_MX25XX_MX25L1606 ��Ӧ�������Ϣ
 */
#define  MX25XX_CHIP_SZIE        (2 * 1024 * 1024) /**< \brief ������ */
#define  MX25XX_ERASE_UNIT_SZIE   4096             /**< \brief ��С������Ԫ��С */

/** \brief �豸���� */
am_local am_ftl_serv_t __g_ftl;

/** \brief RAM ���������� */
am_local uint8_t __g_ftl_buf[AM_FTL_RAM_SIZE_GET(MX25XX_CHIP_SZIE,
                                                 MX25XX_ERASE_UNIT_SZIE,
                                                 MX25XX_FTL_LOGIC_BLOCK_SZIE,
                                                 MX25XX_FTL_LOG_BLOCK_NUM)];

/** \brief FTL ��Ϣ */
am_local am_const am_ftl_info_t __g_ftl_info = {
    __g_ftl_buf,                 /**< \brief RAM ������ */
    sizeof(__g_ftl_buf),         /**< \brief RAM ��������С */
    MX25XX_FTL_LOGIC_BLOCK_SZIE, /**< \brief �߼���Ĵ�С */
    MX25XX_FTL_LOG_BLOCK_NUM,    /**< \brief ��־����� */
    0                            /**< \brief ����������飨������Ԫ������ */
};

/** \brief ʵ����ʼ�� */
am_ftl_handle_t am_microport_flash_ftl_inst_init (void)
{
    return am_ftl_init(&__g_ftl,
                       &__g_ftl_info,
                       am_microport_flash_mtd_inst_init());
}

/**
 * @}
 */

/* end of file */
