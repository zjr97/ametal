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
 * \brief  CS1237 Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-9-15  lqy, first implementation.
 * \endinternal
 */

#ifndef __AM_CS1237_H
#define __AM_CS1237_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_cs1237
 * @copydoc am_cs1237.h
 * @{
 */

#include "ametal.h"
#include "am_adc.h"
/**
 * \brief CS1237 �豸��Ϣ�ṹ��
 */
typedef struct am_cs1237_adc_devinfo{

    /** \brief IOģ��SPI SCLK����ѡ�� */
    uint8_t      clk;

    /**
     * \brief cs1237_out����ѡ��
     *
     * \note ���Ӳ��û�ж�DRDY/DOUT���ŷ��룬������Ӧ�ú�in_pin��ͬ
     * */
    uint8_t      out_pin;

    /**
     * \brief cs1237_in����ѡ��
     *
     * \note ���Ӳ��û�ж�DRDY/DOUT���ŷ��룬������Ӧ�ú�out_pin��ͬ
     * */
    uint8_t      in_pin;

    /** \brief REF��׼Դ״̬����,0ʹ���ڲ���׼Դ��1ʹ���ⲿ��׼Դ */
    uint8_t      refo_off;

    /**
     * \brief ADC�ο���ѹ����λ��mV
     *
     * \note �òο���ѹ�ɾ���ĵ�·����
     *
     */
    uint32_t     vref;

    /** \brief CLKʱ��ߵ�ƽ��ʱʱ�� ��΢���*/
    uint8_t      high_clk_delay;

    /** \brief CLKʱ��͵�ƽ��ʱʱ�� ��΢���*/
    uint8_t      low_clk_delay;

    /** \brief ����͹���ģʽclk�ߵ�ƽ����ʱ�� ��΢�������ֵ100us*/
    uint8_t      powerdown_delay;

}am_cs1237_adc_devinfo_t;

/** \brief �����ص����� */
typedef void (*am_cs1237_code_read_cb_t) (void *p_arg,uint32_t code);

/**
 * \brief CS1237 �豸�ṹ��
 */
typedef struct am_cs1237_adc_dev{

    /** \brief �Ŵ��� */
    uint8_t                        pga;
    /** \brief ������� */
    uint8_t                        out_speed;
    /** \brief ͨ�� */
    uint8_t                        ch;
    /** \brief �Ƿ����ж�ģʽ */
    am_bool_t                      is_int;

    /** \brief INT���ŵĴ�����Ϣ���� */
    struct am_cs1237_trigger_info {

        /** \brief �����ص����� */
        am_cs1237_code_read_cb_t   pfn_callback;
        /** \brief �ص������Ĳ��� */
        void                      *p_arg;

    } triginfo;/**< \brief INT���ŵĴ�����Ϣ */

    /** \brief �豸��Ϣ */
    const am_cs1237_adc_devinfo_t *p_devinfo;

    /** \brief ADC��׼���� */
    am_adc_serv_t                  adc_serve;

    /** \brief ����û�����ת����Ļص����� */
    am_adc_seq_cb_t                pfn_callback;

    /** \brief �û������ص������Ļص��������� */
    void                          *p_arg;

    /** \brief ��ǰת�������������������׵�ַ */
    am_adc_buf_desc_t             *p_desc;

    /** \brief ��ǰת������������������ */
    uint32_t                       desc_num;

    /** \brief ת���Ĵ��� */
    uint32_t                       count;

    /** \brief ת����־ */
    uint32_t                       flags;

    /** \brief �Ե�ǰ�����������Ѿ������Ĵ��� */
    uint32_t                       conv_cnt;

    /** \brief ����ִ�е�ǰ���������������� */
    uint32_t                       desc_index;

    /** \brief ����������ת����ɵĴ��� */
    uint32_t                       seq_cnt;

}am_cs1237_adc_dev_t;

typedef am_cs1237_adc_dev_t * am_cs1237_adc_handle_t; /**< \brief ������� */

/**
 * \name CS1237ͨ��ѡ��
 * @{
 */

#define AM_CS1237_CHANNEL_A         0      /**< \brief ͨ�� A,Ĭ�� */
#define AM_CS1237_CHANNEL_RESERVE   1      /**< \brief оƬ����ʹ��λ */
#define AM_CS1237_CHANNEL_TEMP      2      /**< \brief �¶� */
#define AM_CS1237_CHANNEL_SHORT     3      /**< \brief �ڶ� */

/** @} */

/**
 * \name CS1237 PGAѡ��
 * @{
 */

#define AM_CS1237_PGA_1             0       /**< \brief �Ŵ��� 1*/
#define AM_CS1237_PGA_2             1       /**< \brief �Ŵ��� 2*/
#define AM_CS1237_PGA_64            2       /**< \brief �Ŵ��� 64*/
#define AM_CS1237_PGA_128           3       /**< \brief �Ŵ��� 128��Ĭ��*/

/** @} */

/**
 * \name CS1237 �������ѡ��
 * @{
 */

#define AM_CS1237_SPEED_10HZ        0       /**< \brief ADC�������10HZ��Ĭ��  */
#define AM_CS1237_SPEED_40HZ        1       /**< \brief ADC�������40HZ     */
#define AM_CS1237_SPEED_640HZ       2       /**< \brief ADC�������640HZ    */
#define AM_CS1237_SPEED_1280HZ      3       /**< \brief ADC�������1280HZ   */

/** @} */

/**
 * \brief CS1237 �豸��ʼ��
 *
 * \param[in] p_dev      :ָ��CS1237�豸�ṹ���ָ��
 * \param[in] p_devinfo  :ָ��CS1237�豸��Ϣ�ṹ���ָ��
 *
 * \return CS1237����������,���Ϊ NULL��������ʼ��ʧ��
 */
am_cs1237_adc_handle_t am_cs1237_init(am_cs1237_adc_dev_t            *p_dev,
                                  const am_cs1237_adc_devinfo_t  *p_devinfo);

/**
 * \brief CS1237 �豸���ʼ��
 *
 * \param[in] handle : CS1237�������
 *
 * \return ��
 */
void am_cs1237_deinit (am_cs1237_adc_handle_t handle);

/**
 * \brief CS1237 ���üĴ�����
 *
 * \param[in] p_dev : CS1237�������
 *
 * \return adc���üĴ���ֵ
 */
uint8_t am_cs1237_config_reg_read(am_cs1237_adc_dev_t  *p_dev);

/**
 * \brief CS1237 ���üĴ���pgaд
 *
 * \param[in] p_dev : CS1237�������
 * \param[in] pga   : pga��غ�
 *
 * \retval  AM_OK     : ���óɹ�
 *          AM_ERROR  : ����ʧ�ܣ�ADCδ׼����
 */
int am_cs1237_pga_set(am_cs1237_adc_dev_t  *p_dev, uint32_t pga);

/**
 * \brief CS1237 ���üĴ���chд
 *
 * \param[in] p_dev : CS1237�������
 * \param[in] ch    : ch��غ�
 *
 * \retval  AM_OK     : ���óɹ�
 *          AM_ERROR  : ����ʧ�ܣ�ADCδ׼����
 */
int am_cs1237_ch_set(am_cs1237_adc_dev_t  *p_dev, uint32_t ch);

/**
 * \brief CS1237 ���üĴ���speedд
 *
 * \param[in] p_dev : CS1237�������
 * \param[in] speed : speed��غ�
 *
 * \retval  AM_OK     : ���óɹ�
 *          AM_ERROR  : ����ʧ�ܣ�ADCδ׼����
 */
int am_cs1237_out_speed_set(am_cs1237_adc_dev_t  *p_dev, uint32_t speed);

/**
 * \brief CS1237 pga�Ŵ�����
 *
 * \param[in] p_dev : CS1237�������
 *
 * \return pga�Ŵ���
 */
uint32_t am_cs1237_pga_get(am_cs1237_adc_dev_t  *p_dev);

/**
 * \brief CS1237 ͨ���Ŷ�
 *
 * \param[in] p_dev : CS1237�������
 *
 * \return chͨ����
 */
uint8_t am_cs1237_ch_get(am_cs1237_adc_dev_t  *p_dev);

/**
 * \brief CS1237 adc������ʶ�
 *
 * \param[in] p_dev : CS1237�������
 *
 * \return adc�������
 */
uint32_t am_cs1237_out_speed_get(am_cs1237_adc_dev_t  *p_dev);

/**
 * \brief CS1237 �����
 *
 * \param[in] p_dev   : CS1237�������
 *
 * \retval  AM_OK     : �����ɹ�
 */
int am_cs1237_read_int_enable(am_cs1237_adc_dev_t  *p_dev);

/**
 * \brief CS1237 ��ֹ��
 *
 * \param[in] p_dev   : CS1237�������
 *
 * \retval  AM_OK     : �����ɹ�
 */
int am_cs1237_read_int_disable(am_cs1237_adc_dev_t  *p_dev);

/**
 * \brief CS1237 ��ѭ��adc�ɼ�ֵ
 *
 * \param[in]  p_dev   : CS1237�������
 * \param[out] val     : ��������
 *
 * \retval  AM_OK �ɼ��ɹ�
 */
int am_cs1237_read_polling(am_cs1237_adc_dev_t *p_dev, uint32_t *val);

/**
 * \brief CS1237 ����͹���ģʽ
 *
 * \param[in] p_dev   : CS1237�������
 *
 * \retval  ��
 */
void am_cs1237_power_down_enter(am_cs1237_adc_dev_t  *p_dev);

/**
 * \brief CS1237 �˳��͹���ģʽ
 *
 * \param[in] p_dev   : CS1237�������
 *
 * \retval  ��
 */
void am_cs1237_power_down_out(am_cs1237_adc_dev_t  *p_dev);

/**
 * \brief CS1237 �����жϻص�����
 *
 * \param[in] p_dev   : CS1237�������
 * \param[in] p_fun   : CS1237�жϻص�����
 * \param[in] p_arg   : CS1237�жϻص���������
 *
 * \retval  ��
 */
void am_cs1237_int_connect(am_cs1237_adc_dev_t      *p_dev ,
                           am_cs1237_code_read_cb_t  p_fun,
                           void                     *p_arg);

/**
 * \brief CS1237 ɾ���жϻص�����
 *
 * \param[in] p_dev   : CS1237�������
 * \param[in] p_fun   : CS1237�жϻص�����
 * \param[in] p_arg   : CS1237�жϻص���������
 *
 * \retval  ��
 */
void am_cs1237_int_disconnect(am_cs1237_adc_dev_t      *p_dev ,
                              am_cs1237_code_read_cb_t  p_fun,
                              void                     *p_arg);

/**
 * \brief CS1237 ��ñ�׼adc���
 * \param[in] p_dev : CS1237�������
 *
 * \retval ��׼adc�������
 */
am_adc_handle_t am_cs1237_standard_adc_handle_get(am_cs1237_adc_dev_t *p_dev);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SPI_H */

/*end of file */


