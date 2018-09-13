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
 * \brief  DS1302 Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-8-11  fra, first implementation.
 * \endinternal
 */

#ifndef __AM_DS1302_H
#define __AM_DS1302_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_ds1302
 * @copydoc am_ds1302.h
 * @{
 */
 
#include "ametal.h"
#include "am_time.h"
#include "am_rtc.h"
#include "am_spi.h"
 
/**
 * \brief DS1302spiģʽ�豸��Ϣ�ṹ��
 *
 * ������SPIģʽ�����MOSI��MISO�ӵ�һ���оƬ
 * ��Ҫ�����ײ�֧��SPI�����ƴ���,�������ײ㲻֧��
 * �����ƴ��䣬��ᱨ����ô��ѡ��gpioģʽ����
 */
typedef struct am_ds1302_spi_devinfo {

    /**< \brief Ƭѡ����  */
    uint16_t          ce_pin;

} am_ds1302_spi_devinfo_t;

/**
 * \brief DS1302gpioģʽ�豸��Ϣ�ṹ��
 */
typedef struct am_ds1302_gpio_devinfo {

    uint16_t          sclk_pin;              /**< \brief SCLK���Ŷ�Ӧ��IO�ܽź� */
    uint16_t          ce_pin;                /**< \brief ce���Ŷ�Ӧ��IO�ܽź� */
    uint16_t          io_pin;                /**< \brief IO���Ŷ�Ӧ��IO�ܽź� */

} am_ds1302_gpio_devinfo_t;

/**
 * \brief DS1302�豸�ṹ��
 */
typedef struct am_ds1302_dev {

    void              *pfn;          /**< \brief DS1302�������� */
    void              *p_drv;        /**< \brief ���������ĵ�һ����ڲ��� */

} am_ds1302_dev_t;

/** \brief DS1302�����������  */
typedef am_ds1302_dev_t  *am_ds1302_handle_t;

/**
 * \brief DS1302spiģʽ���豸�ṹ��
 */
typedef struct am_ds1302_spi_dev {

    /** \brief spi�����豸 */
    am_spi_device_t                     spi_dev;

    /** \brief DS1302spiģʽ�豸��Ϣ */
    const am_ds1302_spi_devinfo_t      *p_spi_devinfo;

    /** \brief DS1302��׼���� */
    am_ds1302_dev_t                     common;

} am_ds1302_spi_dev_t;

/**
 * \brief DS1302gpioģʽ���豸�ṹ��
 */
typedef struct am_ds1302_gpio_dev {

    /** \brief DS1302gpioģʽ�豸��Ϣ */
    const am_ds1302_gpio_devinfo_t      *p_gpio_devinfo;

    /** \brief DS1302��׼���� */
    am_ds1302_dev_t                      common;

} am_ds1302_gpio_dev_t;

/**
 * \brief DS1302 �豸��ʼ����spi������ʽ
 *
 * \param[in] p_dev          : ָ��DS1302�豸�ṹ���ָ��
 * \param[in] p_devinfo      : ָ��DS1302�豸��Ϣ�ṹ���ָ��
 * \param[in] spi_handle     : spi�������
 *
 * \return DS1302����������,���Ϊ NULL��������ʼ��ʧ��
 */
am_ds1302_handle_t am_ds1302_spi_init (am_ds1302_spi_dev_t            *p_dev,
                                       const am_ds1302_spi_devinfo_t  *p_devinfo,
                                       am_spi_handle_t                 spi_handle);

/**
 * \brief DS1302 �豸��ʼ����gpio������ʽ
 *
 * \param[in] p_dev          : ָ��DS1302�豸�ṹ���ָ��
 * \param[in] p_devinfo      : ָ��DS1302�豸��Ϣ�ṹ���ָ��
 *
 * \return DS1302����������,���Ϊ NULL��������ʼ��ʧ��
 */
am_ds1302_handle_t am_ds1302_gpio_init (am_ds1302_gpio_dev_t            *p_dev,
                                        const am_ds1302_gpio_devinfo_t  *p_devinfo);

/**
 * \brief DS1302 �豸���ʼ��
 *
 * \param[in] handle : ds1302�������
 *
 * \return ��
 */
void am_ds1302_deinit (am_ds1302_handle_t handle);

/**
 * \brief ��ȡRTC��׼������
 *
 * \param[in] handle     : DS1302�������
 * \param[in] p_rtc      : ָ��RTC��׼����
 *
 * return RTC��׼����������
 */
am_rtc_handle_t am_ds1302_rtc_init (am_ds1302_handle_t    handle,
                                    am_rtc_serv_t        *p_rtc);

/**
 * \brief DS1302ʱ���������ú���
 *
 * \param[in] handle : DS1302����������
 * \param[in] p_tm   : ָ��ʱ��ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_ds1302_time_set (am_ds1302_handle_t handle, am_tm_t *p_tm);

/**
 * \brief DS1302ʱ�����ڻ�ȡ����
 *
 * \param[in]  handle : ds1302����������
 * \param[out] p_tm   : ָ��ʱ��ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_ds1302_time_get (am_ds1302_handle_t handle, am_tm_t *p_tm);

/**
 * \brief DS1302��ֹ����
 *
 * \param[in]  handle : ds1302����������
 *
 * \retval AM_OK      : �����ɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_ds1302_stop (am_ds1302_handle_t handle);

/**
 * \brief DS1302дRAM����
 *
 * \param[in]  handle  : ds1302����������
 * \param[in]  p_data  : ָ��д��RAM�����ݻ�������ָ��,���ݵĴ�С������31�ֽ�
 * \param[in]  data_len: �������ݵĳ���
 * \param[in]  position: д��RAM�е���ʼλ��(0~30)
 *
 * \retval AM_OK       : �����ɹ�
 * \retval -AM_EINVAL  : ��������
 */
int am_ds1302_ram_write (am_ds1302_handle_t handle,
                         uint8_t           *p_data,
                         uint8_t            data_len,
                         uint8_t            position);

/**
 * \brief DS1302��RAM����
 *
 * \param[in]  handle  : ds1302����������
 * \param[out] p_data  : ������RAM�е�����
 * \param[in]  data_len: �������ݵĳ���
 * \param[in]  position: ��RAM����ʼλ��(0~30)
 *
 * \retval AM_OK       : �����ɹ�
 * \retval -AM_EINVAL  : ��������
 */
int am_ds1302_ram_read (am_ds1302_handle_t handle,
                        uint8_t           *p_data,
                        uint8_t            data_len,
                        uint8_t            position);


/**
 * \name��������Ŀ�������ֵ
 * @{
 */
#define   AM_DS1302_TRICKLE_1D_2K      0xa5  /**< \brief һ�������ܣ�����2K */
#define   AM_DS1302_TRICKLE_1D_4K      0xa6  /**< \brief һ�������ܣ�����4K */
#define   AM_DS1302_TRICKLE_1D_8K      0xa7  /**< \brief һ�������ܣ�����8K */
#define   AM_DS1302_TRICKLE_2D_2K      0xa9  /**< \brief ���������ܣ�����2K */
#define   AM_DS1302_TRICKLE_2D_4K      0xaa  /**< \brief ���������ܣ�����4K */
#define   AM_DS1302_TRICKLE_2D_8K      0xab  /**< \brief ���������ܣ�����8K */
/** @}*/

/**
 * \brief DS1302������
 *
 * \param[in]  handle  : ds1302����������
 * \param[in]  set_val : ��������Ŀ�������ֵ����ϣ���ѡ���µĺ�
 *                       -#AM_DS1302_TRICKLE_1D_2K
 *                       -#AM_DS1302_TRICKLE_1D_4K
 *                       -#AM_DS1302_TRICKLE_1D_8K
 *                       -#AM_DS1302_TRICKLE_2D_2K
 *                       -#AM_DS1302_TRICKLE_2D_4K
 *                       -#AM_DS1302_TRICKLE_2D_8K
 *
 *                       -xD��ʾ��������Ŀ��yK��ʾ������ֵ
 *                       -�������ļ����������:
 *                       IMAX = (VCC - ������ѹ��)/R, ��3.3Vϵͳ��ѹ����VCC�ϣ�
 *                       ѡ����һ�������ܣ�����ѡ��2K
 *                       ��ôIMAX = (3.3- 0.7) / 2k = 1.3mA����������
 *                       ���ܳ�����ѡ��������������������
 *                       �û��ɸ�����ѡ��صĳ������Ĵ�С��ѡ����Ӧ�ĺ�
 *
 * \retval AM_OK      : �����ɹ�
 * \retval -AM_EINVAL : ����ʧ��
 */
int am_ds1302_trickle_enable(am_ds1302_handle_t handle, uint8_t set_val);

/**
 * \brief DS1302���ܳ�纯��
 *
 * \param[in]  handle : ds1302����������
 *
 * \retval AM_OK      : �����ɹ�
 * \retval -AM_EINVAL : ����ʧ��
 */
int am_ds1302_trickle_disable(am_ds1302_handle_t handle);

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AM_DS1302_H */

/* end of file */
