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
 * \brief  RX8025SA Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-07  vir, first implementation.
 * \endinternal
 */

#ifndef __AM_RX8025SA_H
#define __AM_RX8025SA_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_rx8025sa
 * @copydoc am_rx8025sa.h
 * @{
 */
 
#include "ametal.h"
#include "am_time.h"
#include "am_rtc.h"
#include "am_alarm_clk.h"
#include "am_i2c.h"

/**
 * \brief RX8025SA �豸��Ϣ�ṹ��
 *
 * \note ��Ҫ���������ź�
 */
typedef struct am_rx8025sa_devinfo {

    /** \brief INTA�������ӵ���GPIO���ű�� */
    uint8_t inta_pin;

    /** \brief INTA�������ӵ���GPIO���ű�� */
    uint8_t intb_pin;
    /**
     * \brief RX8025SA��FOE(CLK_EN)���������ӵ���GPIO���ű��
     *  ���ڿ���FOUT�Ƿ����Ƶ��,����Ҫʱ����ֵΪ -1
     */
    int clk_en_pin;

} am_rx8025sa_devinfo_t;

/**
 * \brief RX8025SA �豸�ṹ��
 */
typedef struct am_rx8025sa_dev {

    am_bool_t         conn_stat_inta;  /**< \brief ��ǰINTA�ж�����״̬ */
    uint8_t           time_format;            /** \brief Сʱ�� */

    /* ���±�����Ҫ�������ж��ж�доƬ�ļĴ��� */
    uint8_t           status;     /**< \brief ��ǰ״̬ */
    uint8_t           intr_flag;  /**< \brief �жϱ�־ */
    uint8_t           sub_addr;   /**< \brief I2C�����ӵ�ַ */
    uint8_t           buf[1];     /**< \brief I2C���ݻ����� */
    uint8_t           nbytes;     /**< \brief �������ݳ��� */
    am_i2c_transfer_t trans[2];   /**< \brief RX8025SA״̬��transfer */
    am_i2c_message_t  msg;        /**< \brief RX8025SA״̬��msg */

    am_i2c_device_t  i2c_dev;     /**< \brief RX8025SA I2C�豸 */

    /* INT���ŵĴ�����Ϣ */
    struct am_rx8025sa_trigger_info {

        /** \brief �����ص����� */
        am_pfnvoid_t  pfn_callback;

        /** \brief �ص������Ĳ��� */
        void *p_arg;

    } triginfo[3];

    const am_rx8025sa_devinfo_t * p_devinfo;  /* ָ���豸��Ϣ������ָ�� */

} am_rx8025sa_dev_t;

/** \brief RX8025SA����������� */
typedef am_rx8025sa_dev_t *am_rx8025sa_handle_t;

/**
 * \brief RX8025SA �豸��ʼ��
 *
 * \param[in] p_dev      : ָ��RX8025SA�豸�ṹ���ָ��
 * \param[in] p_devinfo  : ָ��RX8025SA�豸��Ϣ��ָ��
 * \param[in] i2c_handle : I2C��׼����������
 *
 * \return RX8025SA����������,���Ϊ NULL��������ʼ��ʧ��
 *
 * \note ������Ҫ��Ƶ��������ܣ��豸��Ϣ�ṹ���е�clk_en_pin ��ֵΪ -1 ����
 */
am_rx8025sa_handle_t am_rx8025sa_init (am_rx8025sa_dev_t           *p_dev,
                                       const am_rx8025sa_devinfo_t *p_devinfo,
                                       am_i2c_handle_t              i2c_handle);

/**
 * \brief RX8025SA �豸���ʼ��
 * \param[in] handle : RX8025SA�������
 * \return ��
 */
void am_rx8025sa_deinit (am_rx8025sa_handle_t handle);

/**
 * \brief ��ȡRTC��׼������
 *
 * \param[in] handle     : RX8025SA�������
 * \param[in] p_rtc      : ָ��RTC��׼����
 *
 * return RTC��׼����������
 */
am_rtc_handle_t am_rx8025sa_rtc_init (am_rx8025sa_handle_t  handle,
                                      am_rtc_serv_t        *p_rtc);

/**
 * \brief ��ȡRX8025SA ALARM_CLK��׼����
 *
 * \param[in] handle       : RX8025SA�������
 * \param[in] p_alarm_clk  : ָ��ALARM_CLK��׼����
 *
 * return ALARM_CLK��׼����������
 */
am_alarm_clk_handle_t am_rx8025sa_alarm_clk_init (am_rx8025sa_handle_t   handle,
                                                  am_alarm_clk_serv_t   *p_alarm_clk);

/**
 * \name rx8025�����������ӵ�����ֵ
 * \anchor grp_rx8025sa_alarm_week
 *  eg�� ���Ҫ���������������������� ������   ��alarm_week��ֵΪ ��
 *        AM_RX8025SA_ALARM_SUNDAY | AM_RX8025SA_ALARM_WEDNESDAY
 */
#define AM_RX8025SA_ALARM_SUNDAY    0X01
#define AM_RX8025SA_ALARM_MONDAY    0X02
#define AM_RX8025SA_ALARM_TUESDAY   0X04
#define AM_RX8025SA_ALARM_WEDNESDAY 0X08
#define AM_RX8025SA_ALARM_THURSDAY  0X10
#define AM_RX8025SA_ALARM_FRIDAY    0X20
#define AM_RX8025SA_ALARM_SATURDAY  0X40

/**
 * \brief ������Ϣ�ṹ��
 */
typedef struct am_rx8025sa_alarm_info {
    int min;     /**< \brief minutes after the hour       - [0, 59]  */
    int hour;    /**< \brief hours after midnight         - [1, 12] / [0, 23]   */
    int alarm_week;    /**< \brief ֵ�ο�grp_rx8025sa_alarm_week  alarm_d���ӿ��Ժ���*/
}am_rx8025sa_alarm_info_t;

/**
 * \brief ʹ��RX8025SA�� ALARM_D����
 *
 * \param[in] handle       : RX8025SA����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_alarm_d_enable (am_rx8025sa_handle_t handle);
/**
 * \brief ����RX8025SA �� ALARM_D ����
 *
 * \param[in] handle : RX8025SA����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_alarm_d_disable (am_rx8025sa_handle_t handle);


/**
 * \brief ʹ��RX8025SA�� ALARM_W����
 *
 * \param[in] handle       : RX8025SA����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_alarm_w_enable (am_rx8025sa_handle_t handle);
/**
 * \brief ����RX8025SA �� ALARM_W ����
 *
 * \param[in] handle : RX8025SA����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_alarm_w_disable (am_rx8025sa_handle_t handle);

/**
 * \name RX8025SA  �����жϵ�һЩģʽ
 * \anchor grp_int_mode
 * note��  ÿ��00��
 *       ÿʱ00��00��
 *       ÿ��1��00ʱ00��00��                        ����INTA ����
 */

#define AM_RX8025SA_INTA_OFF                 0X00  /**< \brief INTA���ų��ָߵ�ƽ����� */
#define AM_RX8025SA_INTA_LOW                 0X01  /**< \brief INTA��������͵�ƽ */
#define AM_RX8025SA_PULSE_2HZ_MODE           0X02  /**< \brief 2HZ������ģʽ */
#define AM_RX8025SA_PULSE_1HZ_MODE           0X03  /**< \brief 1HZ������ģʽ */
#define AM_RX8025SA_LEVEL_PER_SECOND_MODE    0X04  /**< \brief ÿ������INTA���ŵĵ�ƽģʽ */
#define AM_RX8025SA_LEVEL_PER_MINUTE_MODE    0X05  /**< \brief ÿ������INTA���ŵĵ�ƽģʽ */
#define AM_RX8025SA_LEVEL_PER_HOUR_MODE      0X06  /**< \brief ÿʱ����INTA���ŵĵ�ƽģʽ */
#define AM_RX8025SA_LEVEL_PER_MONTH_MODE     0X07  /**< \brief ÿ������INTA���ŵĵ�ƽģʽ */


/**
 * \brief RX8025SA �����жϺ�������
 *
 * \param[in] handle   : rx8025sa����������
 * \param[in] int_mode :�����ж�ģʽ��ο�grp_int_mode
 *
 * \param[in] pfn_periodic_int_callback   :�����жϵĻص�����
 * \param[in] p_periodic_int_arg          :�����жϵĻص������Ĳ���
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_periodic_int_set (am_rx8025sa_handle_t  handle,
                                   uint8_t              int_mode,
                                  am_pfnvoid_t          pfn_periodic_int_callback,
                                  void                 *p_periodic_int_arg);


/**
 * \brief RX8025SA ����D�ص�����������ʱ������
 *
 * \param[in] handle       : rx8025sa����������
 * \param[in] p_alarm_info : ����ʱ����Ϣ
 *
 * \param[in] pfn_alarm_callback   :�����жϵĻص�����
 * \param[in] p_alarm_arg          :�����жϵĻص������Ĳ���
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_alarm_d_set(am_rx8025sa_handle_t      handle,
                            am_rx8025sa_alarm_info_t *p_alarm_info,
                            am_pfnvoid_t              pfn_alarm_callback,
                            void                     *p_alarm_arg);
/**
 * \brief RX8025SA ����W�ص�����������ʱ������
 *
 * \param[in] handle       : rx8025sa����������
 * \param[in] p_alarm_info : ����ʱ����Ϣ
 *
 * \param[in] pfn_alarm_callback   :�����жϵĻص�����
 * \param[in] p_alarm_arg          :�����жϵĻص������Ĳ���
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_alarm_w_set(am_rx8025sa_handle_t      handle,
                            am_rx8025sa_alarm_info_t *p_alarm_info,
                            am_pfnvoid_t              pfn_alarm_callback,
                            void                     *p_alarm_arg);

/*
 * \brief ��Դ��ѹ�𵴼��
 * \brief\param[in] handle       : rx8025sa����������
 *
 * \note     ����ֵ˵����
 *   return 0  ��Դ��ѹ�����ͣ�����ֹͣ
 *          1  ��Դ��ѹ���ͣ�����ֹͣ
 *          2  ����
 *          3  ��Ȼ��Դ���ͣ������Լ���
 *          4,5 ��Դ�½���0v
 *          6,7 ��Դ˲ͣ�Ŀ����Դ�
 *
 */
int am_rx8025sa_power_check(am_rx8025sa_handle_t  handle);

/**
 * \name ���͵�ѹ����ֵ�趨
 * \anchor grp_rx8025sa_check_voltage
 */
#define RX8025SA_CHECK_VOLTAGE_1_3V  0   /** \brief ��Դ ���ͼ�⹦�ܵı�׼��ѹֵ�趨Ϊ1.3v */
#define RX8025SA_CHECK_VOLTAGE_2_1V  1   /** \brief ��Դ ���ͼ�⹦�ܵı�׼��ѹֵ�趨Ϊ2.1v */

/**
 * \brief �͵�ѹ��⹦�ܵı�׼��ѹֵ�趨
 *
 * \param[in] handle        : RX8025SA����������
 * \param[in] check_v_value : �͵�ѹ��ֵ ���ο� grp_rx8025sa_check_voltage
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_check_voltage_set (am_rx8025sa_handle_t handle, uint8_t check_v_value);

/*
 * \brief ��ʱƵ�ʽ��е�������
 * \param[in] handle   : RX8025SA����������
 * \param[in] clk      : Ҫ��������Ƶ�ʴ�С  �������ķ�Χ ��-189.1*10^-6 <= (clk-32768)/32768 <= +189.1*10^-6
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note clk �ĵ�λΪHZ����FOUT�����Ƶ��û��Ӱ�졣
 */
int am_rx8025sa_clk_adjust ( am_rx8025sa_handle_t handle, float clk );

/*
 * \brief  ���� clk����� ��FOUT�����32.768KHZƵ��
 * \param[in] handle     : RX8025SA����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note ��Ҫʹ��оƬ�����Ƶ�ʾͱ��������豸��Ϣ��clk_en_pin��
 */
int am_rx8025sa_clkout_set(am_rx8025sa_handle_t handle);

/*
 * \brief  �ر� clk�����
 * \param[in] handle     : RX8025SA����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025sa_clkout_close(am_rx8025sa_handle_t handle);
                              
/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _AM_RX8025SA_H */

/* end of file */

