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
 * \brief  PCF85063 Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.10 17-08-16  vir, optimize structure
 * - 1.00 16-08-05  sky, first implementation.
 * \endinternal
 */

#ifndef __AM_PCF85063_H
#define __AM_PCF85063_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_pcf85063
 * \copydoc am_pcf85063.h
 * @{
 */
 
#include "ametal.h"
#include "am_time.h"
#include "am_rtc.h"
#include "am_alarm_clk.h"
#include "am_i2c.h"

/**
 * \brief PCF85063 �豸��Ϣ�ṹ��
 *
 * \note ��Ҫ���������ź�
 */
typedef struct am_pcf85063_devinfo {

    /** 
     * \brief PCF85063���ж�INT���������ӵ���GPIO���ű�ţ�
     *        ����Ҫʱ����ֵΪ -1 
     */
    int int_pin;

    /**
     * \brief PCF85063��CLKOE(CLK_EN)���������ӵ���GPIO���ű��
     *  ���ڿ���CLKOUT�Ƿ����Ƶ�ʣ�����Ҫʱ����ֵΪ -1
     */
    int clk_en_pin;

} am_pcf85063_devinfo_t;

/**
 * \brief PCF85063 �豸�ṹ��
 */
typedef struct am_pcf85063_dev {

    am_bool_t         conn_stat;      /**< \brief ��ǰINT�ж�����״̬ */
    
    /** \brief ���ڴ�ű�׼���ӽӿ�����ʱ��wdays��ֵ */
    uint8_t           alarm_clk_wdays;
    
     /** \brief ���������û����õ��Ǳ�׼���ӽӿڻ��ǷǱ�׼�� */
    uint8_t           alarm_mode;

    uint8_t           status;        /**< \brief ��ǰ״̬ */
    uint8_t           intr_flag;     /**< \brief �жϱ�־ */
    uint8_t           sub_addr[2];   /**< \brief I2C�����ӵ�ַ */
    uint8_t           buf[1];        /**< \brief I2C���ݻ����� */
    uint8_t           nbytes;        /**< \brief �������ݳ��� */
    am_i2c_transfer_t trans[2];      /**< \brief PCF85063״̬��transfer */
    am_i2c_message_t  msg;           /**< \brief PCF85063״̬��msg */

    am_i2c_device_t  i2c_dev;        /**< \brief PCF85063 I2C�豸 */

    /** \brief INT���ŵĴ�����Ϣ���� */
    struct am_pcf85063_trigger_info {

        /** \brief �����ص����� */
        am_pfnvoid_t  pfn_callback;

        /** \brief �ص������Ĳ��� */
        void *p_arg;

    } triginfo[2];                  /**< \brief INT���ŵĴ�����Ϣ */

    /** \brief ָ���豸��Ϣ������ָ�� */
    const am_pcf85063_devinfo_t * p_devinfo;

} am_pcf85063_dev_t;


/** \brief PCF85063����������� */
typedef am_pcf85063_dev_t *am_pcf85063_handle_t;

/**
 * \brief PCF85063 �豸��ʼ��
 *
 * \param[in] p_dev      : ָ��PCF85063�豸�ṹ���ָ��
 * \param[in] p_devinfo  : ָ��PCF85063�豸��Ϣ��ָ��
 * \param[in] i2c_handle : I2C��׼����������
 *
 * \return PCF85063����������,���Ϊ NULL��������ʼ��ʧ��
 *
 * \note ������Ҫ��Ƶ��������ܣ��豸��Ϣ�ṹ���е�clk_en_pin ��ֵΪ -1 ���ɣ�
 */
am_pcf85063_handle_t am_pcf85063_init (am_pcf85063_dev_t           *p_dev,
                                       const am_pcf85063_devinfo_t *p_devinfo,
                                       am_i2c_handle_t              i2c_handle);

/**
 * \brief PCF85063 �豸���ʼ��
 * \param[in] handle : PCF85063�������
 * \return ��
 */
void am_pcf85063_deinit (am_pcf85063_handle_t handle);


/**
 * \brief ��ȡRTC��׼������
 *
 * \param[in] handle     : PCF85063�������
 * \param[in] p_rtc      : ָ��RTC��׼����
 *
 * return RTC��׼����������
 */
am_rtc_handle_t am_pcf85063_rtc_init (am_pcf85063_handle_t  handle,
                                      am_rtc_serv_t        *p_rtc);
/**
 * \brief ��ȡPCF85063 ALARM_CLK��׼����
 *
 * \param[in] handle       : PCF85063�������
 * \param[in] p_alarm_clk  : ָ��ALARM_CLK��׼����
 *
 * return ALARM_CLK��׼����������
 */
am_alarm_clk_handle_t am_pcf85063_alarm_clk_init (am_pcf85063_handle_t   handle,
                                                  am_alarm_clk_serv_t    *p_alarm_clk);

/**
 * \brief �����λPCF85063
 *
 * \param[in] handle : PCF85063����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_software_reset (am_pcf85063_handle_t handle);

/**
 * \brief ��ֹPCF85063
 *
 * \param[in] handle : PCF85063����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_stop (am_pcf85063_handle_t handle);

/**
 * \brief ����PCF85063(��λʱPCF85063���������ýӿ���Ҫ����� am_pcf85063_stop())
 *
 * \param[in] handle : PCF85063����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_start (am_pcf85063_handle_t handle);

/**
 * \brief д PCF85063 RAM_Byte �Ĵ���
 *
 * \param[in] handle   : PCF85063����������
 * \param[in] data     : ��д�� PCF85063 RAM_Byte �Ĵ�����ֵ
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_ram_write (am_pcf85063_handle_t handle, uint8_t data);

/**
 * \brief �� PCF85063 RAM_Byte �Ĵ���
 *
 * \param[in] handle      : PCF85063����������
 * \param[out] p_data     : ��ȡPCF85063 RAM_Byte �Ĵ����Ļ�����
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note ֻ�ܶ���һ���ֽ�������
 */
int am_pcf85063_ram_read (am_pcf85063_handle_t handle, uint8_t *p_data);

/**
 * \brief PCF85063ʱ���������ú���
 *
 * \param[in] handle : PCF85063����������
 * \param[in] p_tm   : ָ��ʱ��ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_pcf85063_time_set (am_pcf85063_handle_t handle, am_tm_t *p_tm);

/**
 * \brief PCF85063ʱ�����ڻ�ȡ����
 *
 * \param[in]  handle : PCF85063����������
 * \param[out] p_tm   : ָ��ʱ��ṹ���ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_pcf85063_time_get (am_pcf85063_handle_t handle, am_tm_t *p_tm);

/**
 * \name PCF85063 ƫ�Ʋ�������
 * \anchor grp_pcf85063_offset
 * @{
 */

/** \brief ����ģʽ��ÿ��Сʱ����һ�Σ� */
#define AM_PCF85063_OFFSET_MODE_NORMAL      0

/** \brief ����ģʽ��ÿ�ķ��Ӳ���һ�Σ� */
#define AM_PCF85063_OFFSET_MODE_COURSE      1

/**
 * @}
 */

/**
 * \brief PCF85063ʱ��Դ��������
 *
 * \param[in] handle : PCF85063����������
 * \param[in] mode   : ����ģʽ #AM_PCF85063_OFFSET_MODE_NORMAL �� grp_pcf85063_offset
 * \param[in] ppm    : ʱ��Դ��ppm(�羧�������ֲ������ע��ppm)
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_pcf85063_offset_set (am_pcf85063_handle_t handle, uint8_t mode, float ppm);

/**
 * \name PCF85063 ����ʹ�ܺ�
 * \anchor grp_pcf85063_alarm_enable
 * @{
 */

#define AM_PCF85063_ALARM_SECOND_ENABLE  0x01   /**< \brief ��������ʹ�� */
#define AM_PCF85063_ALARM_MINUTE_ENABLE  0x02   /**< \brief ��������ʹ�� */
#define AM_PCF85063_ALARM_HOUR_ENABLE    0x04   /**< \brief Сʱ����ʹ�� */
#define AM_PCF85063_ALARM_DAY_ENABLE     0x08   /**< \brief ������ʹ�� */
#define AM_PCF85063_ALARM_WEEKDAY_ENABLE 0x10   /**< \brief �ܼ�����ʹ�� */

/**
 * @}
 */

/**
 * \brief ������Ϣ�ṹ��
 *
 * \note enabled������ʹ�ܺ깹�� �μ� \ref grp_pcf85063_alarm_enable
 *       ����ȡ���ǵĻ�ֵ����������ʹ��ʱ�����ӣ���
 *       enable = AM_PCF85063_ALARM_MINUTE_ENABLE | AM_PCF85063_ALARM_HOUR_ENABLE��
 *       ����ζ�ŵ�ǰʱ��ͬʱ�Ǻ��������õ�ʱ����Ϣʱ�����ӱ�ǲŻ���λ����enable�������б�־
 *       ��Ӧ��ʱ�䶼�뵱ǰʱ���Ǻ�ʱ�����ӲŻ���Ӧ��
 */
typedef struct am_pcf85063_alarm_info {
    uint8_t     enable;     /**< \brief ����ʹ�� */
    int         sec;        /**< \brief seconds after the minute     - [0, 59]  */
    int         min;        /**< \brief minutes after the hour       - [0, 59]  */
    int         hour;       /**< \brief hours after midnight         - [0, 23]  */
    int         mday;       /**< \brief day of the month             - [1, 31]  */
    int         wday;       /**< \brief days since Sunday            - [0, 6]   */
} am_pcf85063_alarm_info_t;

/**
 * \brief ʹ��PCF85063����
 *
 * \param[in] handle       : PCF85063����������
 * \param[in] p_alarm_info : ������Ϣ����
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_alarm_enable (am_pcf85063_handle_t      handle,
                              am_pcf85063_alarm_info_t *p_alarm_info);

/**
 * \brief ����PCF85063����
 *
 * \param[in] handle : PCF85063����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_alarm_disable (am_pcf85063_handle_t handle);

/**
 * \name PCF85063 CLKOUT���Ƶ�ʱ���
 * \anchor grp_pcf85063_clkout_freq
 * @{
 */

#define AM_PCF85063_CLKOUT_FREQ_32768HZ    0x00 /**< \brief ���Ƶ��32768Hz */
#define AM_PCF85063_CLKOUT_FREQ_16384HZ    0x01 /**< \brief ���Ƶ��16384Hz */
#define AM_PCF85063_CLKOUT_FREQ_8192HZ     0x02 /**< \brief ���Ƶ��8192Hz */
#define AM_PCF85063_CLKOUT_FREQ_4096HZ     0x03 /**< \brief ���Ƶ��4096Hz */
#define AM_PCF85063_CLKOUT_FREQ_2048HZ     0x04 /**< \brief ���Ƶ��2048Hz */
#define AM_PCF85063_CLKOUT_FREQ_1024HZ     0x05 /**< \brief ���Ƶ��1024Hz */
#define AM_PCF85063_CLKOUT_FREQ_1HZ        0x06 /**< \brief ���Ƶ��1Hz */
#define AM_PCA85063A_CLKOUT_FREQ_DISABLE   0x07 /**< \brief �������Ƶ�� */

/**
 * @}
 */

/**
 * \brief ����PCF85063ʱ�����
 *
 * \param[in] handle : PCF85063����������
 * \param[in] freq   : ʱ�����Ƶ�ʱ��� �μ� \ref grp_pcf85063_clkout_freq
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_clkout_set (am_pcf85063_handle_t handle, uint8_t freq);

/**
 * \brief  �ر� clk�����
 * \param[in] handle     : PCF85063����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_clkout_close(am_pcf85063_handle_t handle);

/**
 * \name PCF85063 ��ʱ��ʱ��Դ�궨��
 * \anchor grp_pcf85063_timer_src
 * @{
 */

#define AM_PCF85063_TIEMR_SRC_FREQ_4096HZ      (0x00)    /**< \brief 4096Hz */
#define AM_PCF85063_TIEMR_SRC_FREQ_64HZ        (0x08)    /**< \brief 64Hz */
#define AM_PCF85063_TIEMR_SRC_FREQ_1HZ         (0x10)    /**< \brief 1Hz */
#define AM_PCF85063_TIEMR_SRC_FREQ_1_DIV_60HZ  (0x18)    /**< \brief 1/60Hz */

/**
 * @}
 */

/**
 * \brief ʹ��PCF85063��ʱ��
 *
 * \param[in] handle          : PCF85063����������
 * \param[in] clk_freq        : ʱ��Ƶ��ѡ�� �μ� \ref grp_pcf85063_timer_src
 * \param[in] max_timer_count : ������ֵ
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note ���ȼ���������:
 *       4096Hz [244us    ~ 62.256ms]
 *       64Hz   [15.625ms ~ 3.984s]
 *       1Hz    [1s       ~ 255s]
 *       1/60Hz [1min     ~ 255min]
 */
int am_pcf85063_timer_enable (am_pcf85063_handle_t handle,
                              uint8_t              clk_freq,
                              uint8_t              max_timer_count);

/**
 * \brief ����PCF85063��ʱ��
 *
 * \param[in] handle : PCF85063����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_timer_disable (am_pcf85063_handle_t handle);

/**
 * \brief ��ȡ��ʱ����ǰ�ļ���ֵ
 *
 * \param[in]  handle  : PCF85063����������
 * \param[out] p_count : ���ڻ�ȡ��ʱ����ǰ����ֵ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_pcf85063_timer_count_get (am_pcf85063_handle_t  handle,
                                 uint8_t              *p_count);

/**
 * \name PCF85063 ����/��ʱ���ж�������Ϣ
 * \anchor grp_pcf85063_int_type_info
 * @{
 */

#define AM_PCF85063_INT_TIMER       0x1   /**< \brief ��ʱ���ж�TI */
#define AM_PCF85063_INT_HMINUTE     0x2   /**< \brief ������ж�HMI */
#define AM_PCF85063_INT_MINUTE      0x4   /**< \brief һ�����ж�MI */

/**
 * @}
 */

/**
 * \brief ʹ��PCF85063����/��ʱ���ж�
 *
 * \param[in] handle : PCF85063����������
 * \param[in] flags  : �жϱ�־������ֻ��һ��������Ҳ����ͨ��ȡ�����ʽ������������
 *                     �� AM_PCF85063_INT_TIMER | AM_PCF85063_INT_HMINUTE��
 *                     �жϱ�־�μ� \ref grp_pcf85063_int_type_info
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note ������жϡ������ж��Լ���ʱ���жϹ���TF��ǣ�û�������ж�Դ��Ҫע��ͬʱʹ�õ����
 */
int am_pcf85063_minute_timer_int_enable (am_pcf85063_handle_t handle,
                                         uint8_t              flags);

/**
 * \brief ����PCF85063����/��ʱ���ж�
 *
 * \param[in] handle : PCF85063����������
 * \param[in] flags  : �жϱ�־������ֻ��һ��������Ҳ����ͨ��ȡ�����ʽ������������
 *                     �� AM_PCF85063_INT_TIMER | AM_PCF85063_INT_HMINUTE��
 *                     �жϱ�־�μ� \ref grp_pcf85063_int_type_info
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note ������жϡ������ж��Լ���ʱ���жϹ���TF��ǣ�û�������ж�Դ��Ҫע��ͬʱʹ�õ����
 */
int am_pcf85063_minute_timer_int_disable (am_pcf85063_handle_t handle,
                                          uint8_t              flags);

/**
 * \brief PCF85063 ����/��ʱ���ص���������
 *
 * \param[in] handle                    : PCF85063����������
 * \param[in] pfn_minute_timer_callback : ����/��ʱ���жϻص�����
 * \param[in] p_minute_timer_arg        : ����/��ʱ���жϻص���������
 *
 * \return AM_OK-�ɹ�,����ʧ��
 *
 * \note ��ʱ���жϡ�������ж��Լ�һ�����ж϶�����TF��ǣ�û�������ж�Դ��
 *       ��˽������жϵĻص������ϲ�Ϊһ����
 */
int am_pcf85063_minute_timer_cb_set (am_pcf85063_handle_t  handle,
                                     am_pfnvoid_t          pfn_minute_timer_callback,
                                     void                 *p_minute_timer_arg);

/**
 * \brief PCF85063 ���ӻص���������
 *
 * \param[in] handle                    : PCF85063����������
 * \param[in] pfn_alarm_callback        : �����жϻص�����
 * \param[in] p_alarm_arg               : �����жϻص���������
 *
 * \return AM_OK-�ɹ�,����ʧ��
 */
int am_pcf85063_alarm_cb_set (am_pcf85063_handle_t  handle,
                              am_pfnvoid_t          pfn_alarm_callback,
                              void                 *p_alarm_arg);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_PCF85063_H */

/* end of file */
