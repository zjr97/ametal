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
 * \brief zlg ���߽ӿ���������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-27  vir, first implementation
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_zlg_ili9341_3wire_spi.h"

/**
 * \brief ����8λ����
 */
static  int __zlg_ili9341_3wire_cmd_write (void *p_drv, uint8_t cmd)
{
    amhw_zlg_spi_t *p_spi_reg_base  =
      (( am_zlg_ili9341_intfc_3wire_dev_t *) p_drv)->p_devinfo->spi_reg_base;

    uint32_t temp = 0;

    /* ��ʽ���� */
    cmd = ( cmd >> 4) | ( cmd << 4 );
    cmd = ((cmd >> 2) & 0X33) | ( (cmd << 2) & 0XCC);
    cmd = ((cmd >> 1) & 0X55) | ( (cmd << 1) & 0XAA);

    temp = cmd;
    /* ���������� */
    temp <<=1 ;

    /* д������ */
    p_spi_reg_base->txreg = temp;
    p_spi_reg_base->txreg = temp >> 8;
    while ( 0 == ( p_spi_reg_base->cstat & 0x01) );

    return AM_OK;
}

/**
 * \brief ����8λ����
 */
static int __zlg_ili9341_3wire_data_u8_write (void *p_drv,uint8_t data)
{
    amhw_zlg_spi_t *p_spi_reg_base = (( am_zlg_ili9341_intfc_3wire_dev_t *) \
                       p_drv)->p_devinfo->spi_reg_base;

   uint32_t temp = 0;

   /* ��ʽ���� */
   data = ( data >> 4) | ( data << 4 );
   data = ((data >> 2) & 0X33) | ( (data << 2) & 0XCC);
   data = ((data >> 1) & 0X55) | ( (data << 1) & 0XAA);

   temp = data;
   /* ���������� */
    temp = ( temp << 1 ) | 0X1 ;

    /* д������ */
    p_spi_reg_base->txreg = temp;
    p_spi_reg_base->txreg = temp >> 8;
    while ( 0 == ( p_spi_reg_base->cstat & 0x01) );

    return AM_OK;
}

/**
 * \brief ����16λ����
 */
static int __zlg_ili9341_3wire_data_u16_write(void *p_drv,uint16_t data)
{
    amhw_zlg_spi_t *p_spi_reg_base = (( am_zlg_ili9341_intfc_3wire_dev_t *) \
                       p_drv)->p_devinfo->spi_reg_base;

    uint32_t temp = 0;
    uint8_t data1 = (uint8_t)(data >> 8);
    uint8_t data2 = (uint8_t) data;

    /* ��ʽ���� */
    data1 = ( data1 >> 4) | ( data1 << 4 );
    data1 = ((data1 >> 2) & 0X33) | ( (data1 << 2) & 0XCC);
    data1 = ((data1 >> 1) & 0X55) | ( (data1 << 1) & 0XAA);

    temp = data1;
    /* ���������� */
    temp = ( temp << 1 ) | 0X1 ;

    /* д������ */
    p_spi_reg_base->txreg = temp;
    p_spi_reg_base->txreg = temp >> 8;
    while ( 0 == ( p_spi_reg_base->cstat & 0x01) );

    /* ��ʽ���� */
    data2 = ( data2 >> 4) | ( data2 << 4 );
    data2 = ((data2 >> 2) & 0X33) | ( (data2 << 2) & 0XCC);
    data2 = ((data2 >> 1) & 0X55) | ( (data2 << 1) & 0XAA);

    temp = data2; /* ����Ҫ���temp */
    /* ���������� */
    temp = ( temp << 1 ) | 0X1 ;

    /* д������ */
    p_spi_reg_base->txreg = temp;
    p_spi_reg_base->txreg = temp >> 8;
    while ( 0 == ( p_spi_reg_base->cstat & 0x01) );

    return AM_OK;
}

static struct am_ili9341_drv_funcs __g_ili9341_funcs = {
        __zlg_ili9341_3wire_cmd_write,
        __zlg_ili9341_3wire_data_u8_write,
        __zlg_ili9341_3wire_data_u16_write,
        NULL,
        NULL,
};

/**
 * \brief ��ʼ��
 */

am_ili9341_serv_t *am_zlg_ili9341_intfc_3wire_init (
                          am_zlg_ili9341_intfc_3wire_dev_t           *p_dev,
                          const am_zlg_ili9341_intfc_3wire_devinfo_t *p_devinfo)
{
    p_dev->serv.p_funcs = &__g_ili9341_funcs;
    p_dev->serv.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    uint32_t best_pdiv;

    am_gpio_pin_cfg(p_devinfo->cs_pin,   p_devinfo->cs_func);

    /**
     *  ͨ���Ĵ�������SPI
     */
    /* ����ʱ�� */
    am_clk_enable(p_devinfo->clk_spi);

    /* ��������  ,Ĭ��50M��� */
    am_gpio_pin_cfg(p_devinfo->miso_pin, p_devinfo->miso_func);
    am_gpio_pin_cfg(p_devinfo->mosi_pin, p_devinfo->mosi_func);
    am_gpio_pin_cfg(p_devinfo->sck_pin,  p_devinfo->sck_func);

    amhw_zlg_spi_mode_sel(p_devinfo->spi_reg_base, AMHW_ZLG_SPI_MODE_MASTER);
    /* �����ٶ� */
    best_pdiv = am_clk_rate_get(p_devinfo->clk_spi) / p_devinfo->speed_hz;
    amhw_zlg_spi_baud_rate_set(p_devinfo->spi_reg_base, best_pdiv);

    amhw_zlg_spi_tx_enable(p_devinfo->spi_reg_base, AM_TRUE);
    amhw_zlg_spi_rx_enable(p_devinfo->spi_reg_base, AM_TRUE);
    amhw_zlg_spi_module_enable(p_devinfo->spi_reg_base, AM_TRUE);

    amhw_zlg_spi_first_bit_sel(p_devinfo->spi_reg_base, AMHW_ZLG_SPI_DATA_LSB);
    amhw_zlg_spi_data_len_sel(p_devinfo->spi_reg_base, AMHW_ZLG_SPI_DATA_LEN_8BIT);
    amhw_zlg_spi_valid_data_sel(p_devinfo->spi_reg_base,AMHW_ZLG_SPI_VALID_DATA_8BIT);

    /* ����9λ */
    amhw_zlg_spi_extlen_set(p_devinfo->spi_reg_base, 9);

    /* ����ʱ����λ�ͼ��� ģʽ1 */
    amhw_zlg_spi_clk_mode_set(p_devinfo->spi_reg_base, 1);

    /* ���� Ƭѡ��Ч */
    amhw_zlg_spi_cs_sel(p_devinfo->spi_reg_base, AM_TRUE);
    amhw_zlg_spi_nss_ctrl_sel(p_devinfo->spi_reg_base,AMHW_ZLG_SPI_NSS_CTRL_BT_HD);

    return &p_dev->serv;
}

/* end of file */
