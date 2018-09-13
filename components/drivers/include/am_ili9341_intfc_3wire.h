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
 * \brief  ���߽ӿ� ILI9341 ���� (���õ��Ǳ�׼���SPI������ ���ٶ���)
 *
 * \ note  ���ߣ� MOSI �� CS�� SCK
 *             MOSI һ�δ��� 9λ�ģ����ȷ��͵�һλ�� ����/�����  ѡ�� λ ��Ȼ�������ݻ������λ�ȴ���
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-27  vir, first implementation.
 * \endinternal
 */


#ifndef __AM_ILI9341_INTFC_3WIRE_H
#define __AM_ILI9341_INTFC_3WIRE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_spi.h"
#include "am_ili9341.h"

/**
 * @addtogroup am_if_ili9341_intfc_3wire
 * @copydoc am_ili9341_intfc_3wire.h
 * @{
 */


/**
 * \brief ili9341���߽ӿ���Ϣ
 */
typedef struct am_ili9341_intfc_3wire_devinfo {

    /** \brief ILI9341��SPI��Ƭѡ���� CS�����ӵ���GPIO���ű�� */
    int cs_pin;

    /** \brief ILI9341��SPI��clk �����ӵ���GPIO���ű�� */
    int sck_pin;

    /* lcd_sck �����Ź��� */
    uint32_t sck_func;

    /** \brief ILI9341��SPI��MOSI�����ӵ���GPIO���ű�� */
    int mosi_pin;

    /* lcd_mosi �����Ź��� */
    uint32_t mosi_func;

    /** \brief ILI9341��SPI��MISO�����ӵ���GPIO���ű�� */
    int miso_pin;

    /* lcd_miso �����Ź��� */
    uint32_t miso_func;

    /**
     *  \brief SPI �ٶ�
     *  \note ���ǲ��ñ�׼SPI�ӿڣ��ɴﵽ50MHZ��
     */
    uint32_t max_speed_hz;

}am_ili9341_intfc_3wire_devinfo_t;


/**
 * \brief ili9341���߽ӿ��豸
 */
typedef struct am_ili9341_intfc_3wire_dev {

    /**< \brief ���߽ӿ��������� */
    am_ili9341_serv_t                 serv;

    /**< \brief SPI�豸  */
    am_spi_device_t                   spi_dev;

    /**< \brief ���߽ӿڵĽӿ���Ϣ */
    const am_ili9341_intfc_3wire_devinfo_t *p_devinfo;

}am_ili9341_intfc_3wire_dev_t;


/**
 * \brief ili9341 ���߽ӿڳ�ʼ������
 * \param[in] p_dev          :ָ��ILI9341���߽ӿ��豸�ṹ���ָ��
 * \param[in] p_devinfo      :ָ��ILI9341���߽ӿ���Ϣ��ָ��
 * \param[in] spi_handle     : SPI ���
 *
 * \return  ���߽ӿڷ���ָ��
 */
am_ili9341_serv_t * am_ili9341_intfc_3wire_init(am_ili9341_intfc_3wire_dev_t *p_dev,
                             const am_ili9341_intfc_3wire_devinfo_t *p_devinfo,
                             am_spi_handle_t                         spi_handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _AM_ILI9341_INTFC_3WIRE_H */

/* end of file */

