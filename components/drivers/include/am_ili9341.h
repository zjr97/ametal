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
 * \brief ili9341�����ӿ��ļ�
 *
 * \ note   ILI9341Һ���� ��СΪ  320 *240
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-18  vir, first implementation.
 * \endinternal
 */

#ifndef __AM_ILI9341_H
#define __AM_ILI9341_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_ili9341
 * @copydoc am_ili9341.h
 * @{
 */
 
#include "ametal.h"

/**
 * \brief ili9341 ��������
 *
 * \note д���д8λ��16λ������������������
 */
struct am_ili9341_drv_funcs {

    /** \brief �������� */
    int (*pfn_ili9341_cmd_write)(void *p_drv, uint8_t cmd);

    /** \brief ����8λ���� */
    int (*pfn_ili9341_data_u8_write)(void *p_drv, uint8_t data);

    /** \brief ����16λ���� */
    int (*pfn_ili9341_data_u16_write)(void *p_drv, uint16_t data);

    /** \brief��ȡ8λ���� */
    int (*pfn_ili9341_data_u8_read)(void *p_drv, uint8_t *p_data);

    /** \brief��ȡ16λ���� */
    int (*pfn_ili9341_data_u16_read)(void *p_drv, uint16_t *p_data);

};

/**
 * \brief ili9341 ��׼����
 */
typedef struct am_ili9341_serv {

    struct am_ili9341_drv_funcs *p_funcs;

    void                        *p_drv;
} am_ili9341_serv_t;

/**
 * \brief ILI9341 �豸��Ϣ�ṹ��
 *
 * \note
 */
typedef struct am_ili9341_devinfo {

    /** \brief ILI9341�ĸ�λ���� �����ӵ���GPIO���ű�� */
    int rst_pin;

    /** \brief ILI9341�ı������� �����ӵ���GPIO���ű�� */
    int bl_pin;

    /** ������Ļ�ķ��򣬺�����  0:���� �� 1������ */
    uint8_t lcd_dir;

}am_ili9341_devinfo_t;

/**
 * \brief ILI9341�豸�ṹ��
 */
typedef struct am_ili9341_dev {

    /** ���û�����ɫ  ,ֵ�ο�grp_color*/
    uint16_t point_color;

    /* ������Ļ�ı�����ɫ , ֵ�ο�grp_color*/
    uint16_t back_color;


    uint16_t width;    /* ���� (in pixels) */
    uint16_t heigh;    /* ���� (in pixels) */

    /**< \brief �ӿ�����   */
    am_ili9341_serv_t      *p_serv;

    const am_ili9341_devinfo_t *p_devinfo;  /* ָ���豸��Ϣ������ָ�� */

} am_ili9341_dev_t;

typedef am_ili9341_dev_t *am_ili9341_handle_t;

/**
 * \brief ILI9341 �豸��ʼ��
 *
 * \param[in] p_dev      :ָ��ILI9341�豸�ṹ���ָ��
 * \param[in] p_devinfo  :ָ��ILI9341�豸��Ϣ�ṹ���ָ��
 * \param[in] p_serv     :ָ��ILI9341����ṹ���ָ��
 *
 * \return ILI9341����������,���Ϊ NULL��������ʼ��ʧ��
 */
am_ili9341_handle_t am_ili9341_init(am_ili9341_dev_t                   *p_dev,
                                    const am_ili9341_devinfo_t         *p_devinfo,
                                    am_ili9341_serv_t                  *p_serv);

/**
 * \brief ILI9341 �豸���ʼ��
 * \param[in] handle : ILI9341�������
 * \return ��
 */
void am_ili9341_deinit (am_ili9341_handle_t handle);

/**
 * \brief ili9341�����λ
 *
 * \param[in] p_dev      :ָ��ILI9341�豸�ṹ���ָ��
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_ili9341_reset(am_ili9341_handle_t handle);

/**
 * \name ��ɫ
 * \anchor grp_color
 * @{
 */
#define AM_ILI9341_COLOR_BLACK       0X0000    /* ��ɫ */
#define AM_ILI9341_COLOR_WHITE       0XFFFF    /* ��ɫ */
#define AM_ILI9341_COLOR_BLUE        0X001F    /* ��ɫ */
#define AM_ILI9341_COLOR_DARKGREEN   0X03E0    /* ���� */
#define AM_ILI9341_COLOR_GREEN       0x07E0    /* ��ɫ */
#define AM_ILI9341_COLOR_RED         0xF800    /* ��ɫ */
#define AM_ILI9341_COLOR_CYAN        0x7FFF    /* ���� */
#define AM_ILI9341_COLOR_YELLOW      0xFFE0    /* ��ɫ */
#define AM_ILI9341_COLOR_GRAY        0X8430    /* ��ɫ */
#define AM_ILI9341_COLOR_BROWN       0XBC40    /* ��ɫ */
#define AM_ILI9341_COLOR_MAGENTA     0xF81F    /* Ʒ�� */
#define AM_ILI9341_COLOR_DARKBLUE    0X01CF    /* ����ɫ */
#define AM_ILI9341_COLOR_LIGHTBLUE   0X7D7C    /* ǳ��ɫ */
#define AM_ILI9341_COLOR_GRAYBLUE    0X5458    /* ����ɫ */
/**
 * @}
 */

/**
 * \brief ���û��ʵ���ɫ
 * \param[in] handle    :ָ��ILI9341�ľ��
 * \param[in] color     :Ҫ������ɫ ���ο�  \ref grp_color
 *
 * \retval AM_OK     : �����ɹ�
 */
int am_ili9341_point_color_set(am_ili9341_handle_t handle, uint16_t color);


/**
 * \brief ���ñ�����ɫ
 * \param[in] handle    :ָ��ILI9341�ľ��
 * \param[in] color     :Ҫ������ɫ ���ο�  \ref grp_color
 *
 * \retval AM_OK     : �����ɹ�
 */
int am_ili9341_back_color_set(am_ili9341_handle_t handle, uint16_t color);


/**
 * \brief ����
 *
 * \param[in] handle ָ��ILI9341�豸�ṹ���ָ��
 *
 * \retval AM_OK     : �����ɹ�
 *         AM_EINVAL : ��Ч����
 * \note ��������ɫΪ�û����õı�����ɫ
 */
int am_ili9341_clear (am_ili9341_handle_t handle);


/**
 * \brief ��ֱ��
 *
 * \param[in] handle    :ָ��ILI9341�豸�ṹ���ָ��
 *
 * \retval AM_OK     : �����ɹ�
 *         AM_EINVAL : ��Ч����
 *
 * \note (x1,y1) ��ʼ����
 *       (x2,y2) �յ�����
 */
int am_ili9341_draw_line(am_ili9341_handle_t handle,
        uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * \brief ������
 * \param[in] handle    :ָ��ILI9341�豸�ṹ���ָ��
 *
 * \retval AM_OK     : �����ɹ�
 *         AM_EINVAL : ��Ч����
 *
 * \note (x1,y1) ��  (x2,y2)Ϊ���ε������Խ�����
 */
int am_ili9341_draw_rectangle(am_ili9341_handle_t handle,
        uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * \brief ��Բ
 * \param[in] handle    :ָ��ILI9341�豸�ṹ���ָ��
 *
 * \retval AM_OK     : �����ɹ�
 *         AM_EINVAL : ��Ч����
 *
 * \note (x0,y0)ΪԲ�ĵ�����  ,r Ϊ�뾶
 */
int am_ili9341_draw_circle(am_ili9341_handle_t handle,
        uint16_t x0, uint16_t y0, uint8_t r);

/**
 * \brief ��ʾһ���ַ�
 *
 * \param[in] handle    :ָ��ILI9341�豸�ṹ���ָ��
 * \param[in] x        : x����
 * \param[in] y        : y����
 * \param[in] num      : Ҫ��ʾ���ַ�
 * \param[in] size     : �ַ���С   ֵ��ȡΪ 12��16��24
 * \param[in] mode     : ���ӷ�ʽ mode =1
 *                       �ǵ��ӷ�ʽ mode =0
 *
 * \retval AM_OK     : �����ɹ�
 *         AM_EINVAL : ��Ч����
 */
int am_ili9341_show_char(am_ili9341_handle_t handle,
        uint16_t x, uint16_t y, uint8_t num, uint8_t size,uint8_t mode);


/**
 * \brief ��ʾ���֣�
 *
 * \param[in] handle    :ָ��ILI9341�豸�ṹ���ָ��
 * \param[in] x        : x����
 * \param[in] y        : y����
 * \param[in] num      : Ҫ��ʾ������
 * \param[in] len      : ���ֵ�λ��
 * \param[in] size     : ���������С   ֵ��ȡΪ 12��16��24
 *
 * \retval AM_OK     : �����ɹ�
 *         AM_EINVAL : ��Ч����
 */
int am_ili9341_show_num(am_ili9341_handle_t handle,
       uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size);

/**
 * \brief ��ʾ�ַ���
 * \param[in] handle    :ָ��ILI9341�豸�ṹ���ָ��
 * \param[in] x        : x����
 * \param[in] y        : y����
 * \param[in] size     : ���������С   ֵ��ȡΪ 12��16��24
 * \param[in] width    : ��ʾ����Ŀ�
 * \param[in] height   : ��ʾ����ĸ�
 * \param[in] p_str    : ָ��Ҫ��ʾ���ַ���ָ��*
 *
 * \retval AM_OK     : �����ɹ�
 *         AM_EINVAL : ��Ч����
 */
int am_ili9341_show_string (am_ili9341_handle_t handle,
                            uint16_t x,        uint16_t y,
                            uint8_t size,      uint16_t width,
                            uint16_t height,   char *p_str);



/**
 * \brief ��һ�������ɫ
 *
 * \param[in] handle    :ָ��ILI9341�ľ��
 * \param[in] color     :Ҫ������ɫ ���ο�  \ref grp_color
 *
 * \note ��x��y��Ҫ���������
 */
void am_ili9341_draw_point (am_ili9341_handle_t handle,
                            uint16_t            x,
                            uint16_t            y,
                            uint16_t            color);

/**
 * \brief ili9341 LCD������ɫ���
 *
 * \param[in] handle    :ָ��ILI9341�豸�ṹ���ָ��
 * \param[in] color    :Ҫ������ɫ ���ο�  \ref grp_color
 *
 * \note (x1,y1)��(x2,y2)ΪҪ�������� Ϊ�Խ�����
 *       ֻ����䳤��������
 *
 */
void am_ili9341_color_fill(am_ili9341_handle_t handle,
                           uint16_t x1, uint16_t y1,
                           uint16_t x2, uint16_t y2,
                           uint16_t color);

/**
 * \brief ��һƬ��������ض�����ɫ
 *
 * \param[in] handle    :ָ��ILI9341�ľ��
 * \param[in] x0, x1   : X��������
 * \param[in] y0, y1   : Y��������
 * \param[in] buf      : ������ɫֵ
 * \param[in] data_len : ������ɫ��ʽ�ĳ��� (��λ���ֽڣ�
 * \param[in] reverse  : ��ת��־������X1(Y1)��ֵ��X0(Y0)��С
 *
 */
void am_ili9341_area_draw_color(am_ili9341_handle_t handle,
                                  uint16_t x0, uint16_t y0,
                                  uint16_t x1, uint16_t y1,
                                  uint8_t *buf,uint8_t data_len,
                                  uint8_t reverse );

/**
 * \brief ������Ļ
 */
void am_ili9341_on(am_ili9341_handle_t handle);

/**
 * \brief �ر���Ļ
 */
void am_ili9341_off(am_ili9341_handle_t handle);

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _AM_ILI9341_H */

/* end of file */


