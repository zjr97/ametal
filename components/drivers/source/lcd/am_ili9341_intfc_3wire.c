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
 * \brief ili9341 ���߽ӿ���������ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-27  vir, first implementation.
 * \endinternal
 */

#include "am_ili9341_intfc_3wire.h"
#include "am_gpio.h"

/**
 * \brief �ڱ�׼��SPI�ӿ��в���Ƭѡ�źţ������Լ��ڵ���ʱ����Ƭѡ����
 */
static void __ili9341_no_use_cs(am_spi_device_t *p_dev, int pin)
{

}

/**
 * \brief ����8λ����
 */
static  int __ili9341_3wire_cmd_write(void *p_drv, uint8_t cmd)
{
    int ret = AM_OK;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    am_ili9341_intfc_3wire_dev_t *p_dev = (am_ili9341_intfc_3wire_dev_t *)p_drv;
    const am_ili9341_intfc_3wire_devinfo_t *p_devinfo = p_dev->p_devinfo;

    /* ����Ƭѡ  cs*/
    am_gpio_set( p_devinfo->cs_pin,AM_GPIO_LEVEL_LOW);

    /* ����mosi���� ��ʾ���� ���� */
    am_gpio_pin_cfg(p_devinfo->mosi_pin,AM_GPIO_OUTPUT_INIT_LOW );

    /* ����һ��ʱ���� */
    am_gpio_pin_cfg(p_devinfo->sck_pin,AM_GPIO_OUTPUT_INIT_LOW | AM_GPIO_PUSH_PULL);
    am_gpio_set(p_devinfo->sck_pin, AM_GPIO_LEVEL_HIGH);
    am_gpio_set(p_devinfo->sck_pin, AM_GPIO_LEVEL_LOW);

    /* ������ͳ�ȥ */
    am_gpio_pin_cfg(p_devinfo->sck_pin, p_devinfo->sck_func );
    am_gpio_pin_cfg(p_devinfo->mosi_pin, p_devinfo->mosi_func );
    ret = am_spi_write_then_read (&(p_dev->spi_dev),
                                  &cmd,
                                  1,
                                  NULL,
                                  0);

    /* ����Ƭѡ  cs*/
    am_gpio_set(p_devinfo->cs_pin, AM_GPIO_LEVEL_HIGH);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;

}

/**
 * \brief ����8λ����
 */
static int __ili9341_3wire_data_u8_write(void *p_drv,uint8_t data)
{
    int ret = AM_OK;

    if (NULL == p_drv) {
        return -AM_EINVAL;
    }

    am_ili9341_intfc_3wire_dev_t *p_dev = (am_ili9341_intfc_3wire_dev_t *)p_drv;
    const am_ili9341_intfc_3wire_devinfo_t *p_devinfo = p_dev->p_devinfo;

    /* ����Ƭѡ  cs*/
    am_gpio_set( p_devinfo->cs_pin,AM_GPIO_LEVEL_LOW);

    /* ���� mosi���� ��ʾ���� ���� */
    am_gpio_pin_cfg(p_devinfo->mosi_pin,AM_GPIO_OUTPUT_INIT_HIGH );

    /* ����һ��ʱ���� */
    am_gpio_pin_cfg(p_devinfo->sck_pin,AM_GPIO_OUTPUT_INIT_LOW | AM_GPIO_PUSH_PULL);
    am_gpio_set(p_devinfo->sck_pin, AM_GPIO_LEVEL_HIGH);
    am_gpio_set(p_devinfo->sck_pin, AM_GPIO_LEVEL_LOW);

    /* �����ݷ��ͳ�ȥ */
    am_gpio_pin_cfg(p_devinfo->sck_pin, p_devinfo->sck_func  );
    am_gpio_pin_cfg(p_devinfo->mosi_pin, p_devinfo->mosi_func);
    ret = am_spi_write_then_read (&(p_dev->spi_dev),
                                  &data,
                                  1,
                                  NULL,
                                  0);

    /* ����Ƭѡ  cs*/
    am_gpio_set(p_devinfo->cs_pin, AM_GPIO_LEVEL_HIGH);

    if (AM_OK != ret) {
        return ret;
    }
    return AM_OK;
}

/**
 * \brief ����16λ����
 */
static int __ili9341_3wire_data_u16_write(void *p_drv,uint16_t data)
{
    uint8_t data1 = (uint8_t)(data >> 8);
    uint8_t data2 = (uint8_t) data;

    __ili9341_3wire_data_u8_write(p_drv, data1);
    __ili9341_3wire_data_u8_write(p_drv, data2);
    return AM_OK;
}

static struct am_ili9341_drv_funcs __g_ili9341_funcs = {
        __ili9341_3wire_cmd_write,
        __ili9341_3wire_data_u8_write,
        __ili9341_3wire_data_u16_write,
        NULL,
        NULL,
};


am_ili9341_serv_t * am_ili9341_intfc_3wire_init(am_ili9341_intfc_3wire_dev_t *p_dev,
                             const am_ili9341_intfc_3wire_devinfo_t *p_devinfo,
                             am_spi_handle_t                         spi_handle)
{
    int ret = AM_OK;

    p_dev->serv.p_funcs = &__g_ili9341_funcs;
    p_dev->serv.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    /* ����spi�豸 */
    am_spi_mkdev(&p_dev->spi_dev,
                  spi_handle,
                  8,                    /* �ִ�СΪ8-bit */
                  AM_SPI_MODE_0,
                  p_devinfo->max_speed_hz,
                  p_dev->p_devinfo->cs_pin,
                  __ili9341_no_use_cs);
    /* �����豸 */
    ret = am_spi_setup( &(p_dev->spi_dev));
    if ( ret != AM_OK ) {
        return NULL;
    }

    return &p_dev->serv;
}

/* end of file */
