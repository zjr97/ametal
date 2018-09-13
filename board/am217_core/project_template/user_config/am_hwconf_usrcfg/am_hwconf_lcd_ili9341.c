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
 * \brief ILI9341 �û������ļ�
 * \sa am_hwconf_lcd_ili9341.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-25  vir, first implementation
 * \endinternal
 */

#include "am_zlg_ili9341_3wire_spi.h"
#include "zlg217_pin.h"
#include "zlg217_regbase.h"
#include "am_zlg217_inst_init.h"
#include "zlg217_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lcd_ili9341
 * \copydoc am_hwconf_lcd_ili9341.c
 * @{
 */

/** \brief ili9341�豸��Ϣ */
static const am_ili9341_devinfo_t __g_ili9341_devinfo = {
    PIOD_2,   /**< \brief ��λ���� */
    PIOC_11,  /**< \brief �������� */
    0,        /**< \brief ���� */
};

/** \brief �豸��Ϣ */
static const am_zlg_ili9341_intfc_3wire_devinfo_t __g_ili9341_intfc_devinfo = {
        PIOB_12,                                 /**< \brief CS */
        PIOB_13,                                 /**< \brief CLK */
        PIOB_13_SPI2_SCK | PIOB_13_AF_PP,        /**< \brief SCK���� */
        PIOB_15,                                 /**< \brief MOSI */
        PIOB_15_SPI2_MOSI | PIOB_15_AF_PP,       /**< \brief MOSI���� */
        PIOB_14,                                 /**< \brief MISO */
        PIOB_14_SPI2_MISO | PIOB_14_INPUT_FLOAT, /**< \brief MISO���� */
        PIOB_12_SPI2_NSS | PIOB_12_AF_PP,        /**< \brief CS���� */
        ZLG217_SPI2,                        /**< \brief SPI2�Ļ���ַ */
        CLK_SPI2,                                /**< \brief SPI��ʱ�Ӻ� */
        24000000,                                /**< \brief ����ٶ�Ϊ24MHz */
};

/** \brief ILI9341 �豸ʵ�� */
static am_ili9341_dev_t __g_ili9341_dev;

/**< \brief ILI9341 ���߽ӿ��豸ʵ�� */
static am_zlg_ili9341_intfc_3wire_dev_t  __g_ili9341_intfc_dev;

/*******************************************************************************
  ��ʹ�� EMWIN ʱ��ʼ������
*******************************************************************************/

am_ili9341_handle_t am_zlg217_ili9341_inst_init (void)
{
    return am_ili9341_init( &__g_ili9341_dev, &__g_ili9341_devinfo,
            am_zlg_ili9341_intfc_3wire_init( \
                           &__g_ili9341_intfc_dev ,&__g_ili9341_intfc_devinfo));
}

void am_zlg217_ili9341_inst_deinit (am_ili9341_handle_t handle)
{
    am_ili9341_deinit( handle );
}

/*******************************************************************************
  ��ֲ EMWIN ����Ҫ�ĺ���
*******************************************************************************/

static am_ili9341_handle_t __g_handle_ili9341;

/** \brief ��ʼ����Ļ */
void am_lcd_init (void)
{
    am_ili9341_serv_t *p_serv = am_zlg_ili9341_intfc_3wire_init(
                                    &__g_ili9341_intfc_dev,
                                    &__g_ili9341_intfc_devinfo);

    __g_handle_ili9341 = am_ili9341_init(&__g_ili9341_dev,
                                         &__g_ili9341_devinfo,
                                          p_serv);
}

/** \brief ��һ�����ɫ */
void am_lcd_draw_point (uint16_t x, uint16_t y, uint16_t color)
{
    am_ili9341_draw_point (__g_handle_ili9341, x, y, color);
}

/** \brief ��һƬ���������ɫ */
void am_lcd_color_fill (uint16_t x1,
                        uint16_t y1,
                        uint16_t x2,
                        uint16_t y2,
                        uint16_t color)
{
    am_ili9341_color_fill(__g_handle_ili9341, x1, y1, x2, y2, color);
}

/** \brief ��һƬ��������ض�����ɫ */
void am_lcd_area_draw_color (uint16_t x0,
                             uint16_t y0,
                             uint16_t x1,
                             uint16_t y1,
                             uint8_t *p_buf,
                             uint8_t  data_len,
                             uint8_t  reverse)
{
    am_ili9341_area_draw_color(__g_handle_ili9341,
                               x0,
                               y0,
                               x1,
                               y1,
                               p_buf,
                               data_len,
                               reverse);
}

/** \brief ������ʾ */
void am_lcd_on (void)
{
    am_ili9341_on(__g_handle_ili9341);
}

/** \brief �ر���ʾ */
void am_lcd_off (void)
{
    am_ili9341_off(__g_handle_ili9341);
}

/**
 * @}
 */

/* end of file */
