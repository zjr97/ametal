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
 * \brief ZLG ���߽ӿ� ILI9341 ����
 *
 * \note ��������ͨ���Ĵ���ֱ�Ӳ���Ӳ��SPI(ƬѡҲ����Ӳ��Ƭѡ)���ٶȿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-27  vir, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG_ILI9341_INTFC_3WIRE_H
#define __AM_ZLG_ILI9341_INTFC_3WIRE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_ili9341.h"
#include "amhw_zlg_spi.h"

/**
 * @addtogroup am_zlg_if_ili9341_3wire_spi
 * @copydoc am_zlg_ili9341_3wire_spi.h
 * @{
 */

/**
 * \brief ili9341���߽ӿ���Ϣ
 */
typedef struct am_zlg_ili9341_intfc_3wire_devinfo {

    /** \brief ILI9341��SPI��Ƭѡ���� CS�����ӵ���GPIO���ű�� */
    int                cs_pin;

    /** \brief ILI9341��SPI��sck �����ӵ���GPIO���ű�� */
    int                sck_pin;

    /** \brief lcd_sck �����Ź��� */
    uint32_t           sck_func;

    /** \brief ILI9341��SPI��MOSI�����ӵ���GPIO���ű�� */
    int                mosi_pin;

    /** \brief lcd_mosi �����Ź��� */
    uint32_t           mosi_func;

    /**  \brief ILI9341��SPI��MISO�����ӵ���GPIO���ű�� */
    int                miso_pin;

    /** \brief lcd_mosi �����Ź��� */
    uint32_t           miso_func;

    /** \brief lcd_mosi �����Ź��� */
    uint32_t           cs_func;

    /** \brief SPI�Ĵ�����Ļ���ַ */
    amhw_zlg_spi_t    *spi_reg_base;

    /** \brief ʱ��ID */
    uint32_t           clk_spi;

    /** \brief SPI �ٶȣ���� 24Mhz */
    uint32_t           speed_hz;

}am_zlg_ili9341_intfc_3wire_devinfo_t;

/**
 * \brief ili9341���߽ӿ��豸
 */
typedef struct am_zlg_ili9341_intfc_3wire_dev {

    /** \brief ���߽ӿ��������� */
    am_ili9341_serv_t                 serv;

    /** \brief ���߽ӿڵĽӿ���Ϣ */
    const am_zlg_ili9341_intfc_3wire_devinfo_t *p_devinfo;

}am_zlg_ili9341_intfc_3wire_dev_t;

/**
 * \brief ili9341 ���߽ӿڳ�ʼ������
 *
 * \param[in] p_dev     ָ��ILI9341���߽ӿ��豸�ṹ���ָ��
 * \param[in] p_devinfo ָ��ILI9341���߽ӿ���Ϣ��ָ��
 *
 * \return ���߽ӿڷ���ָ��
 */
am_ili9341_serv_t *am_zlg_ili9341_intfc_3wire_init(
                         am_zlg_ili9341_intfc_3wire_dev_t           *p_dev,
                         const am_zlg_ili9341_intfc_3wire_devinfo_t *p_devinfo);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _AM_ZLG_ILI9341_INTFC_3WIRE_H */

/* end of file */
