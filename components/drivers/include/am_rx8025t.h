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
 * \brief  RX8025T Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-07  vir, first implementation.
 * \endinternal
 */

#ifndef __AM_RX8025T_H
#define __AM_RX8025T_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_rx8025t
 * @copydoc am_rx8025t.h
 * @{
 */

#include "ametal.h"
#include "am_time.h"
#include "am_rtc.h"
#include "am_alarm_clk.h"
#include "am_i2c.h"
#include "am_softimer.h"

/**
 * \brief RX8025T �豸��Ϣ�ṹ��
 *
 * \note ��Ҫ���������ź�
 */
typedef struct am_rx8025t_devinfo {

    /**
     * \brief RX8025T���ж�INT���������ӵ���GPIO���ű�ţ�
     *        ����Ҫʱ����ֵΪ -1
     */
    int int_pin;

    /**
     * \brief RX8025T��FOE(CLK_EN)���������ӵ���GPIO���ű��
     *  ���ڿ���FOUT�Ƿ����Ƶ��,����Ҫʱ����ֵΪ -1
     */
    int clk_en_pin;

} am_rx8025t_devinfo_t;

/**
 * \brief RX8025T �豸�ṹ��
 */
typedef struct am_rx8025t_dev {

    am_bool_t         conn_stat;  /**< \brief ��ǰINT�ж�����״̬ */

    /* ���±�����Ҫ�������ж��ж�доƬ�ļĴ��� */
    uint8_t           status;     /**< \brief ��ǰ״̬ */
    uint8_t           intr_flag;  /**< \brief �жϱ�־ */
    uint8_t           sub_addr;   /**< \brief I2C�����ӵ�ַ */
    uint8_t           buf[1];     /**< \brief I2C���ݻ����� */
    uint8_t           nbytes;     /**< \brief �������ݳ��� */
    am_i2c_transfer_t trans[2];   /**< \brief RX8025T״̬��transfer */
    am_i2c_message_t  msg;        /**< \brief RX8025T״̬��msg */

    am_i2c_device_t  i2c_dev;     /**< \brief RX8025T I2C�豸 */

    am_softimer_t timer;          /**< \brief �����ж���ʱ����������ʱ�� */

    /**< \brief ���������Ķ�ȡ�ж�״̬�Ĵ��������ж����ٺ��������ȡ�����ж�״̬����ֵΪ0ʱ��ʾ
     * ��һ�ζ�ȡ�ж�״̬�����ڼ�⵽�жϷ�������ֵΪ1ʱ��ʾ��һ�ζ�ȡ�ж�״̬����Ϊ�����ڵ�һ�ζ�ȡ״̬
     * ֮�����״̬֮ǰ���������һ���жϣ���ֵΪ2ʱ��ʾ��һ�ζ�ȡ�ж�״̬����Ϊ�����ڵڶ��ζ�ȡ״̬
     * ֮�����״̬֮ǰ���������һ���жϡ���һ�κ͵ڶ��ζ�ȡ�жϵ�ʱ�����϶̣�Լ0.5ms����ȷ������
     * �ϵ�ʵʱ�ԣ��ڶ��κ͵����ζ�ȡ�ļ��ʱ��ϳ���Լ2ms��ȷ���������жϲ������� */
    uint8_t read_int_time_status;

    /** \brief INT���ŵĴ�����Ϣ���� */
    struct am_rx8025t_trigger_info {

        /** \brief �����ص����� */
        am_pfnvoid_t  pfn_callback;

        /** \brief �ص������Ĳ��� */
        void *p_arg;

    } triginfo[3];                         /**< \brief INT���ŵĴ�����Ϣ���� */

    const am_rx8025t_devinfo_t *p_devinfo; /**< \brief ָ���豸��Ϣ������ָ�� */

} am_rx8025t_dev_t;

/** \brief RX8025T����������� */
typedef am_rx8025t_dev_t *am_rx8025t_handle_t;

/**
 * \brief RX8025T �豸��ʼ��
 *
 * \param[in] p_dev      : ָ��RX8025T�豸�ṹ���ָ��
 * \param[in] p_devinfo  : ָ��RX8025T�豸��Ϣ��ָ��
 * \param[in] i2c_handle : I2C��׼����������
 *
 * \return RX8025T����������,���Ϊ NULL��������ʼ��ʧ��
 *
 * \note ������Ҫ��Ƶ��������ܣ��豸��Ϣ�ṹ���е�clk_en_pin ��ֵΪ -1 ����
 */
am_rx8025t_handle_t am_rx8025t_init (am_rx8025t_dev_t           *p_dev,
                                     const am_rx8025t_devinfo_t *p_devinfo,
                                     am_i2c_handle_t             i2c_handle);

/**
 * \brief RX8025T �豸���ʼ��
 * \param[in] handle : RX8025T�������
 * \return ��
 */
void am_rx8025t_deinit (am_rx8025t_handle_t handle);

/**
 * \brief ��ȡRTC��׼������
 *
 * \param[in] handle     : RX8025T�������
 * \param[in] p_rtc      : ָ��RTC��׼����
 *
 * return RTC��׼����������
 */
am_rtc_handle_t am_rx8025t_rtc_init (am_rx8025t_handle_t  handle,
                                     am_rtc_serv_t       *p_rtc);

/**
 * \brief ��ȡRX8025T ����ALARM_CLK��׼����
 *
 * \param[in] handle           : RX8025T�������
 * \param[in] p_alarm_clk      : ָ��ALARM_CLK��׼����
 *
 * return ALARM_CLK��׼����������
 */
am_alarm_clk_handle_t am_rx8025t_alarm_clk_init (am_rx8025t_handle_t   handle,
                                                 am_alarm_clk_serv_t  *p_alarm_clk);

/**
 * \brief ��ȡRX8025T ALARM_CLK��׼����
 *
 * \param[in] handle           : RX8025T�������
 * \param[in] p_alarm_clk      : ָ��ALARM_CLK��׼����
 *
 * return ALARM_CLK��׼����������
 */
am_alarm_clk_handle_t am_rx8025t_alarm_clk_init (am_rx8025t_handle_t   handle,
                                                 am_alarm_clk_serv_t  *p_alarm_clk);

/**
 * \brief �����λRX8025T
 *
 * \param[in] handle           : RX8025T�������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_software_reset (am_rx8025t_handle_t handle);

/**
 * \name �жϱ�־
 * \anchor grp_int_select
 * @{
 */
 
#define AM_RX8025T_BF_UIE   0X20  /**< \brief ʱ������ж�λ */
#define AM_RX8025T_BF_TIE   0X10  /**< \brief ��ʱ���ж�λ */
#define AM_RX8025T_BF_AIE   0X08  /**< \brief �����ж�λ */

 /** @} */

/**
 * \brief ��  �����жϡ���ʱ�жϡ������ж� ʹ��
 * \param[in] handle     : RX8025T����������
 * \param[in] int_select : ѡ��ʹ���жϵķ�ʽ  �ο� \ref grp_int_select
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * eg��Ҫʹ�ܶ�ʱ���������ж�      AM_RX8025T_BF_TIE | AM_RX8025T_BF_AIE
 *
 */
int am_rx8025t_int_enable (am_rx8025t_handle_t handle, uint8_t int_select);

/**
 * \brief ��  �����жϡ���ʱ�жϡ������ж� ʧ��
 * \param[in] handle     : RX8025T����������
 * \param[in] int_select : ѡ��ʧ���жϵķ�ʽ  �ο�grp_int_select
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * eg��Ҫʧ�ܶ�ʱ���������ж�      AM_RX8025T_BF_TIE | AM_RX8025T_BF_AIE
 *
 */
int am_rx8025t_int_disable (am_rx8025t_handle_t handle, uint8_t int_select);


/**
 * \name ��ʱ��ʱ��Ƶ�ʵ�ѡ��
 * \anchor grp_timer_clk
 * @{
 */

#define AM_RX8025T_TIMER_CLK_4096HZ     0X00   /**< \brief ��ʱ����ʱ��Ƶ��Ϊ4096HZ */
#define AM_RX8025T_TIMER_CLK_64HZ       0X01   /**< \brief ��ʱ����ʱ��Ƶ��Ϊ64HZ   */
#define AM_RX8025T_TIMER_CLK_PER_SEC    0X02   /**< \brief ��ʱ����ʱ��Ƶ��Ϊÿ��һ��   */
#define AM_RX8025T_TIMER_CLK_PER_MIN    0X03   /**< \brief ��ʱ����ʱ��Ƶ��Ϊÿ����һ��   */

 /** @} */

/**
 * \brief ʹ�ܶ�ʱ��
 *
 * \param[in] handle : RX8025T����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_timer_enable(am_rx8025t_handle_t  handle);

/**
 * \brief ʧ�ܶ�ʱ��
 *
 * \param[in] handle : RX8025T����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_timer_disable(am_rx8025t_handle_t  handle);

/**
 * \brief ���ö�ʱ��һЩ��������������ʱ����ʹ�ܶ�ʱ���ж�
 *
 * \param[in] handle     : RX8025T����������
 * \param[in] count      �� ����ֵ ����Χ0~4095 ���ݼ�����
 * \param[in] timer_clk  : ��ʱ����ʱ��Ƶ�� ��ȡֵ�ο� \ref grp_timer_clk
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note ����count��timer_clk�Ϳ���������жϵ�����ʱ��
 */
int am_rx8025t_timer_set (am_rx8025t_handle_t  handle, uint16_t count, uint8_t timer_clk);

/**
 * \brief ���ö�ʱ���Ļص�����
 *
 * \param[in] handle             : RX8025T����������
 * \param[in] pfn_timer_callback : ��ʱ���жϻص�����
 * \param[in] p_timer_arg        : ��ʱ���жϻص���������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_timer_cb_set( am_rx8025t_handle_t  handle,
                             am_pfnvoid_t         pfn_timer_callback,
                             void                *p_timer_arg);


/**
 * \name �����ж�Դѡ��
 * \anchor grp_update_int_select
 * @{
 */

#define AM_RX8025T_USEL_PER_SEC  0X00  /**< \brief ����Ϊ���µ�ÿ���Ӵ����ж� */
#define AM_RX8025T_USEL_PER_MIN  0X01  /**< \brief ����Ϊ���µ�ÿ���Ӵ����ж� */

 /** @} */

/**
 * \brief ʱ����´����жϹ������ã���ʹ�ܸ����ж�
 * \param[in] handle     : RX8025T����������
 * \param[in] mode       : �����жϵķ�ʽ ��ֵ��ο� \ref grp_update_int_select
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_time_update_set( am_rx8025t_handle_t  handle, uint8_t mode);

/**
 * \brief ���ø����жϵĻص�����
 *
 * \param[in] handle                  : RX8025T����������
 * \param[in] pfn_update_int_callback : ʱ������жϻص�����
 * \param[in] p_update_int_arg        : ʱ������жϻص���������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_update_int_cb_set(am_rx8025t_handle_t  handle,
                                 am_pfnvoid_t         pfn_update_int_callback,
                                 void                *p_update_int_arg);

/**
 * \name ���ӵ�ģʽѡ��
 * \anchor grp_alarm_mode
 * @{
 */

#define AM_RX8025T_ALARM_WEEK  0X01   /**< \brief �������ӹ�������ΪĿ�� */
#define AM_RX8025T_ALARM_DAY   0X02   /**< \brief �������ӹ�����ΪĿ�� */

/** @} */

/**
 * \name ���ӵ���������
 * \anchor grp_week
 * @{
 */
#define AM_RX8025T_ALARM_SUNDAY    0X01      /**< \brief ������ */
#define AM_RX8025T_ALARM_MONDAY    0X02      /**< \brief ����һ */
#define AM_RX8025T_ALARM_TUESDAY   0X04      /**< \brief ���ڶ� */
#define AM_RX8025T_ALARM_WEDNESDAY 0X08      /**< \brief ������ */
#define AM_RX8025T_ALARM_THURSDAY  0X10      /**< \brief ������ */
#define AM_RX8025T_ALARM_FRIDAY    0X20      /**< \brief ������ */
#define AM_RX8025T_ALARM_SATURDAY  0X40      /**< \brief ������ */

#define AM_RX8025T_ALARM_EVERYDAY  0X80      /**< \brief ÿһ�� */

/** @} */

 
#define AM_RX8025T_ALARM_IGNORED_MIN   0X80  /**< \brief ���Է� */
#define AM_RX8025T_ALARM_IGNORED_HOUR  0X80  /**< \brief ����Сʱ */

/**
 * \brief ������Ϣ�ṹ��
 * eg : ����ÿ�����ڵ�����һ��������18��15������
 *   am_rx8025t_alarm_info_t alarm_info={AM_RX8025T_ALARM_WEEK,
 *                                       15,
 *                                       18,
 *                                       AM_RX8025T_ALARM_MONDAY | AM_RX8025T_ALARM_SATURDAY}
 *
 */
typedef struct am_rx8025t_alarm_info {
    
    /** \brief ����ģʽ���ο� \ref grp_alarm_mode */
    uint8_t alarm_mode;
    
    /** 
     * \brief ���� 0 ~ 59������ƥ����ӣ�������Ϊ��#AM_RX8025T_ALARM_IGNORED_MIN
     */
    uint8_t min;
    
    /** 
     * \brief Сʱ 0 ~ 23������ƥ��Сʱ��������Ϊ��#AM_RX8025T_ALARM_IGNORED_HOUR
     */
    uint8_t hour;
    
     /** 
      * \brief ���ڻ�����
      * ��ģʽΪ #AM_RX8025T_ALARM_WEEK, ���ֵָ�����ڣ���ο� \ref grp_week
      * ��ģʽΪ #AM_RX8025T_ALARM_DAY,  ���ֵָ���죺��ʾÿ���µĵڼ���
      */
    uint8_t week_day;
    
}am_rx8025t_alarm_info_t;

/**
 * \brief RX8025T ���ӻص�����������ʱ������
 *
 * \param[in] handle              : RX8025T����������
 * \param[in] p_alarm_info        : ���ӵ���Ϣ
 * \param[in] pfn_alarm_callback  : �����жϻص�����
 * \param[in] p_alarm_arg         : �����жϻص���������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 */
int am_rx8025t_alarm_set(am_rx8025t_handle_t      handle,
                         am_rx8025t_alarm_info_t *p_alarm_info,
                         am_pfnvoid_t             pfn_alarm_callback,
                         void                    *p_alarm_arg);

/**
 * \name �����������
 * \anchor grp_offset_mode
 * @{
 */
#define AM_RX8025T_OFFSET_INTERVAL_0_5_SEC   0X00  /**< \brief �������Ϊ0.5s */
#define AM_RX8025T_OFFSET_INTERVAL_2_0_SEC   0X01  /**< \brief �������Ϊ2s */
#define AM_RX8025T_OFFSET_INTERVAL_10_SEC    0X02  /**< \brief �������Ϊ10s */
#define AM_RX8025T_OFFSET_INTERVAL_30_SEC    0X03  /**< \brief �������Ϊ30s */
/** @} */

/**
 * \brief �¶Ȳ���
 *
 * \param[in] handle      : RX8025T����������
 * \param[in] offset_mode : ������ʱ���� ��ֵ��ο� \ref grp_offset_mode
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_temperature_offset(am_rx8025t_handle_t handle,uint8_t offset_mode);

/**
 * \name Ƶ�������Сѡ��
 * \anchor grp_frequency
 * @{
 */
#define AM_RX8025T_FOUT_32768HZ  0X00   /**< \brief 32768 HZ output */
#define AM_RX8025T_FOUT_1024HZ   0X01   /**< \brief 1024 HZ output */
#define AM_RX8025T_FOUT_1HZ      0X02   /**< \brief 1 HZ output */
/** @} */

/**
 * \brief  clkout ���ʱ��Ƶ�ʵ�����,������Ƶ�����
 *
 * \param[in] handle     : RX8025T����������
 * \param[in] frequency  : clkout(FOUT)���Ƶ�ʵĴ�С��
 *                         �����ִ�С����ѡ�� ��ֵ��ο� \ref grp_frequency
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note ��Ҫʹ��оƬ�����Ƶ�ʾͱ��������豸��Ϣ��clk_en_pin��
 */
int am_rx8025t_clkout_set(am_rx8025t_handle_t handle, uint8_t frequency);

/**
 * \brief  �ر� clk�����
 * \param[in] handle     : RX8025T����������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_clkout_close(am_rx8025t_handle_t handle);

/**
 * \brief  ��һ�ֽڵ�����д�뵽RX8025T��RAM��
 * \param[in] handle     : RX8025T����������
 * \param[in] data       : Ҫд�������
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 */
int am_rx8025t_ram_write (am_rx8025t_handle_t handle, uint8_t data);

/**
 * \brief  clkout ����RX8025T RAMһ���ֽڵ�����
 * \param[in] handle     : RX8025T����������
 * \param[in] p_data     : ����������Ҫ��ŵĵ�ַ
 *
 * \retval AM_OK : �����ɹ�
 * \retval ����  : ��������,����鿴���ش������
 *
 * \note ֻ����һ���ֽڵ�����
 */
int am_rx8025t_ram_read (am_rx8025t_handle_t handle, uint8_t *p_data);

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_RX8025T_H */

/* end of file */
