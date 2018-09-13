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
 * \brief ZigBee ģ�� ZM516X �����ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� am_zm516x.h
 *
 * \par ʹ��ʾ��
 * \code
 * #include "am_zm516x.h"
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.01 18-01-16  pea, update API to v1.03 manual
 * - 1.00 15-09-06  afm, first implementation
 * \endinternal
 */

#ifndef __AM_ZM516X_H
#define __AM_ZM516X_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_zm516x
 * \copydoc am_zm516x.h
 * @{
 */

#include "am_types.h"
#include "am_wait.h"
#include "am_uart_rngbuf.h"

/** \brief ZM516X ģ��ʵ����Ϣ */
typedef struct am_zm516x_dev_info {
    int      rst_pin;       /**< \brief ��λ���� */
    int      ack_pin;       /**< \brief ACK ���� */
    uint16_t ack_timeout;   /**< \brief ACK ��ʱʱ�� */
    uint8_t *p_txbuf;       /**< \brief ���ͻ����� */
    uint32_t txbuf_size;    /**< \brief ���ͻ�������С���ֽ����� */
    uint8_t *p_rxbuf;       /**< \brief ���ջ����� */
    uint32_t rxbuf_size;    /**< \brief ���ջ�������С���ֽ����� */
} am_zm516x_dev_info_t;

/** \brief ZM516X ģ�������� */
typedef struct am_zm516x_dev {
    am_uart_rngbuf_handle_t uart_handle;     /**< \brief UART ���(���λ�����) */
    am_uart_rngbuf_dev_t    uart_rngbuf_dev; /**< \brief UART �豸(���λ�����) */
    am_wait_t               ack_wait;        /**< \brief ACK �ȴ��ź� */
    am_zm516x_dev_info_t   *p_devinfo;       /**< \brief �豸ʵ����Ϣ */
} am_zm516x_dev_t;

/** \brief ZM516X ģ���׼�������������Ͷ��� */
typedef struct am_zm516x_dev *am_zm516x_handle_t;

/** \brief ZM516X ģ���������Ϣ */
typedef struct am_zm516x_cfg_info {
    char    dev_name[16];     /**< \brief �豸���� */
    char    dev_pwd[16];      /**< \brief �豸���� */
    uint8_t dev_mode;         /**< \brief �豸���ͣ�0: �ն��豸 1: ·���豸 */
    uint8_t chan;             /**< \brief ͨ���� */
    uint8_t panid[2];         /**< \brief ���� ID (PanID) */
    uint8_t my_addr[2];       /**< \brief ���������ַ */
    uint8_t my_mac[8];        /**< \brief ���������ַ(MAC) */
    uint8_t dst_addr[2];      /**< \brief Ŀ�������ַ */
    uint8_t dst_mac[8];       /**< \brief Ŀ�������ַ(����) */
    uint8_t reserve;          /**< \brief ���� */

    /**
     * \brief ���书�ʣ�ֵΪ 0~3���ֱ��Ӧ���书�ʣ�
     *        -32dBm��-20.5dBm��-9dBm��+2.5dBm
     */
    uint8_t power_level;
    uint8_t retry_num;        /**< \brief �����������Դ��� */
    uint8_t tran_timeout;     /**< \brief ������������ʱ����(10ms) */

    /**
     * \brief ���ڲ����ʣ�ֵΪ 1~7���ֱ��Ӧ�����ʣ�
     *        2400��4800��9600��19200��38400��57600��115200
     */
    uint8_t serial_rate;
    uint8_t serial_data;      /**< \brief ��������λ��ֵΪ 5~8 */
    uint8_t serial_stop;      /**< \brief ����ֹͣλ��ֵΪ 1~2 */
    uint8_t serial_parity;    /**< \brief ����У��λ 0: ��У�� 1: ��У�� 2: żУ�� */
    uint8_t send_mode;        /**< \brief ����ģʽ 0: ����  1: �㲥 */
} am_zm516x_cfg_info_t;

/** \brief ZM516X ģ��Ļ�����Ϣ(ͨ���������� D4 ���) */
typedef struct am_zm516x_base_info {
    uint8_t dev_mode[2];      /**< \brief �豸���� */
    uint8_t chan;             /**< \brief ͨ���� */
    uint8_t data_rate;        /**< \brief RFͨѶ����  */
    uint8_t panid[2];         /**< \brief ���� ID (PanID) */
    uint8_t addr[2];          /**< \brief �����ַ */
    uint8_t state;            /**< \brief ����״̬ */
} am_zm516x_base_info_t;

/** \brief ZM516X Զ��ģ���������Ϣ(ͨ����ȡԶ��������Ϣ���� D5 ���) */
typedef struct am_zm516x_remote_info {
    am_zm516x_cfg_info_t cfg_info;       /**< \brief ������Ϣ */
    uint8_t              state;          /**< \brief ����״̬ */
    uint8_t              dev_mode[2];    /**< \brief �豸���� */
    uint8_t              version[2];     /**< \brief �̼��汾 */
} am_zm516x_remote_info_t;

/**
 * \name ZM516X ģ��� AD ͨ����
 * @{
 */
#define AM_ZM516X_AD_CHANNEL0         0
#define AM_ZM516X_AD_CHANNEL1         1
#define AM_ZM516X_AD_CHANNEL2         2
#define AM_ZM516X_AD_CHANNEL3         3
/** @} */

/** \brief ZM516X ģ���ͨѶģʽ */
typedef enum am_zm516x_comm_mode {
    AM_ZM516X_COMM_UNICAST = 0,    /**< \brief ���� */
    AM_ZM516X_COMM_BROADCAST,      /**< \brief �㲥 */
} am_zm516x_comm_mode_t;

/** \brief ZM516X ģ��� MAC ��ַ */
typedef struct am_zm516x_mac_addr {
    uint8_t mac[8];                /**< \brief MAC ��ַ */
}am_zm516x_mac_addr_t;

/** \brief ZM516X �ӻ�ģ����Ϣ(ͨ����ѯ����ģ��洢�Ĵӻ���Ϣ���� E7 ���) */
typedef struct am_zm516x_slave_info {
    uint8_t mac[8];                /**< \brief MAC ��ַ */
    uint8_t addr[2];               /**< \brief �����ַ */
}am_zm516x_slave_info_t;

/**
 * \brief ZM516X ģ��ĵ�ַ
 *
 * ��ַ��Ϊ 2 �ֽڵ������ַ�� 8 �ֽڵ� MAC ��ַ��ʹ�� addr_size
 * ��ַ���������ֵ�ַ����
 */
typedef struct am_zm516x_addr {
    uint8_t *p_addr;               /**< \brief ��ַ */
    uint8_t  addr_size;            /**< \brief ��ַ���ȣ��ֽ����� */
}am_zm516x_addr_t;

/**
 * \brief ZM516X ģ��� PWM ��Ϣ
 */
typedef struct am_zm516x_pwm {

    /**
     * \brief PWM Ƶ�ʣ��ĸ��ֽ����Ϊһ�� 32 λ������С��ģʽ����λΪ Hz��ͨ��
     *        1��2��4 ��Ƶ�ʷ�Χ���趨�� 62Hz~800000Hz��ͨ�� 3 ��Ƶ�ʷ�Χ���趨
     *        �� 62Hz~60000Hz���� PWM �źŵ�Ƶ��Ϊ 0 ʱ����ʾ����� PWM �ź�
     */
    uint8_t freq[4];

    /**
     * \brief PWM ռ�ձȣ�ռ�ձȵ�ֵ���趨�� 1~99����ʾռ�ձȵİٷֱ�
     */
    uint8_t duty_cycle;
}am_zm516x_pwm_t;

/**
 * \brief �� ZM516X ģ�鷢�� nbytes ���ֽ�����
 *
 * ����ӿ��� ZM516X ģ�鷢�� nbytes ���ֽ����ݡ����豸���ڲ����岻�����������´���
 * ʣ������ݲ��ᱻд�룬����ֵΪ�Ѿ����͵����ݸ���
 *
 * \param[in] handle ZM516X ģ��������
 * \param[in] p_buf  Ҫд��ģ������ݻ�����ָ��
 * \param[in] nbytes Ҫд����ֽڸ���
 *
 * \return �ɹ����͵����ݸ�����С�� 0 Ϊʧ�ܣ�ʧ��ԭ��ɲ鿴 errno
 *
 * \attention �÷��ͺ���Ϊ�첽����������ZM516X �����������Ǹ��ݴ����ַ�֡���ʱ��
 *            ���ж���������Ľ���������ڵ����� am_zm516x_send ���ͺ�����Ҫ��
 *            ���ŵ��� ZM516X �����������Ҫ��ʱ�ȴ����ͻ���������ȫ���͵�ʱ��
 *            ���� ZM516X ��֡���ʱ��󣬲��ܵ��� ZM516X ������������� ZM516X
 *            ����������ᵱ�������ݷ��� ZM516X �����ϣ���ʱ�ȴ�ʱ�佨���ǣ�
 *            T(s) = (1 / ������) * 10 * �ֽ��� + 0.05
 */
am_err_t am_zm516x_send (am_zm516x_handle_t handle,
                         const void        *p_buf,
                         size_t             nbytes);

/**
 * \brief �� ZigBee ģ�鷢�� nbytes ���ֽ����ݣ����ȴ� ACK
 *
 * ����ӿ��� ZM516X ģ�鷢�� nbytes ���ֽ����ݡ����豸���ڲ����岻�����������´���
 * ʣ������ݲ��ᱻд�룬����ֵΪ�Ѿ����͵����ݸ���
 *
 * \param[in] handle ZM516X ģ��������
 * \param[in] p_buf  Ҫд��ģ������ݻ�����ָ��
 * \param[in] nbytes Ҫд����ֽڸ���
 *
 * \retval  > 0          �ɹ����͵����ݸ���
 * \retval -AM_ENOTSUP   û������ ACK ����
 * \retval -AM_ETIMEDOUT ������Ӧ��
 *
 * \attention 1. �÷��ͺ���Ϊͬ�������������������ݺ󽫵ȴ� ACK�����յ� ACK ����
 *               ��ʱʱ�Ż᷵�أ�
 *            2. ����ģʽΪ�㲥ģʽʱ������� ACK��
 */
am_err_t am_zm516x_send_with_ack (am_zm516x_handle_t handle,
                                  const void        *p_buf,
                                  size_t             nbytes);

/**
 * \brief �� ZM516X ģ����� maxbytes ���ֽ�����
 *
 * - ����ӿڴ� ZM516X ģ�������� maxbytes ���ֽ�����
 * - ���豸�ɽ������ݸ���Ϊ 0������������
 *
 * \param[in]  handle   ZM516X ģ��������
 * \param[out] p_buf    ��Ŷ�ȡ���ݵĻ�����ָ��
 * \param[in]  maxbytes ���Ҫ��ȡ���ֽڸ���
 *
 * \return �ɹ����յ����ݸ�����С�� 0 Ϊʧ�ܣ�ʧ��ԭ��ɲ鿴 errno
 */
am_err_t am_zm516x_receive (am_zm516x_handle_t handle,
                            void              *p_buf,
                            size_t             maxbytes);

/**
 * \brief ��ȡ ZM516X ģ���������Ϣ���������D1��
 *
 * \param[in]  handle ZM516X ģ��������
 * \param[out] p_info ��ȡ ZM516X ģ���������Ϣ
 *
 * \retval  AM_OK    ��ȡ�ɹ�
 * \retval -AM_EPERM ��ȡʧ��
 */
am_err_t am_zm516x_cfg_info_get (am_zm516x_handle_t    handle,
                                 am_zm516x_cfg_info_t *p_info);

/**
 * \brief ���� ZigBee ģ��ͨ���ţ��������D2��
 *
 * ģ��ɹ����� 16 ������ͨ���ϣ�����ģ����ز�Ƶ�ʲ�ͬ����ͬͨ����ģ��˴˼���
 * ��ͨ����ͨ�����������Ͽ���ʵ�������ϻ������ε�Ч��
 *
 * \param[in] handle ZM516X ģ��������
 * \param[in] chan   ͨ���� 11~26
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EPERM  ����ʧ��
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zm516x_cfg_channel_set (am_zm516x_handle_t handle, uint8_t chan);

/**
 * \brief ��������ģ�飨�������D4��
 *
 * ģ����յ�������󣬻��������ڵ���ͬͨ��������ģ�鷢���㲥�����������б���
 * ˾�̼��� ZigBee ģ�鶼��Ӧ��˹㲥��Ӧ�����ݻὫ�Լ�����ػ�����Ϣ���ص�����
 * ����Ŀ��ڵ㡣��������ǰ��Ҫ����ͨ���Ų�����������Ӧͨ����ģ��
 *
 * \param[in]  handle      ZM516X ģ��������
 * \param[in]  buf_size    p_base_info ָ��Ļ�������С����λΪ
 *                         sizeof(am_zm516x_base_info_t)
 * \param[out] p_base_info �洢���յ��Ĵӻ���Ϣ�Ļ�����
 * \param[out] p_get_size  ʵ����������ģ������
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EPERM  ��ȡʧ��
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zm516x_discover (am_zm516x_handle_t     handle,
                             uint8_t                buf_size,
                             am_zm516x_base_info_t *p_base_info,
                             uint8_t               *p_get_size);

/**
 * \brief ��ȡԶ��������Ϣ���������D5��
 *
 * \param[in]  handle        ZM516X ģ��������
 * \param[in]  p_zb_addr     Ŀ���ַ
 * \param[out] p_remote_info �������� ZM516X ģ���������Ϣ
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EPERM  ��ȡʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 *
 * \attention ��������λ��5��8������λ�������Ϊ 5��6��7 λ���򲻿��Ի�ȡ������Ϣ
 */
am_err_t am_zm516x_remote_info_get (am_zm516x_handle_t       handle,
                                    am_zm516x_addr_t        *p_zb_addr,
                                    am_zm516x_remote_info_t *p_remote_info);

/**
 * \brief �޸� ZM516X ģ���������Ϣ���������D6�������óɹ��踴λ
 *
 * \param[in] handle ZM516X ģ��������
 * \param[in] p_info ZM516X ģ���������Ϣ
 *
 * \retval  AM_OK    �޸ĳɹ�
 * \retval -AM_EPERM �޸�ʧ��
 *
 * \attention AMetal ƽ̨���� ZM516X ģ��Ĵ��ڲ���ֻ֧�ֲ��������ã�����λ�̶�Ϊ
 *            8 λ��У��Ϊ��У�飬ֹͣλΪ 1 λ���ڸ���ģ�������λ��У��λ��ֹͣ
 *            λʱ��Ҫע�⣬�����С�ĸ����ˣ���Ҫ��ģ��ָ�����Ĭ�ϲ��ܲ���
 */
am_err_t am_zm516x_cfg_info_set (am_zm516x_handle_t    handle,
                                 am_zm516x_cfg_info_t *p_info);

/**
 * \brief ʹ ZM516X ģ�鸴λ���������D9��
 *
 * ��λ֡��Ӧ��
 *
 * \param[in] handle ZM516X ģ��������
 *
 * \return ��
 */
void am_zm516x_reset (am_zm516x_handle_t handle);

/**
 * \brief �ָ� ZM516X ģ��������ã��������DA�������óɹ��踴λ
 *
 * \param[in] handle ZM516X ģ��������
 *
 * \retval  AM_OK    ���óɹ�
 * \retval -AM_EPERM ����ʧ��
 */
am_err_t am_zm516x_default_set (am_zm516x_handle_t handle);

/**
 * \brief ���� ZigBee ģ����յ����ݰ���ͷ�Ƿ���ʾԴ��ַ���������DC����
 *        ���óɹ��踴λ
 *
 * \param[in] handle    ZM516X ģ��������
 * \param[in] p_zb_addr Ŀ���ַ
 * \param[in] flag      ��ͷ�Ƿ���ʾԴ��ַ AM_TRUE: ��ʾ��AM_FALSE: ����ʾ
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EPERM  ����ʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_display_head_set (am_zm516x_handle_t handle,
                                         am_zm516x_addr_t  *p_zb_addr,
                                         am_bool_t          flag);

/**
 * \brief ����ָ����ַ ZigBee ģ��� GPIO ������������������E1��
 *
 * \param[in] handle    ZM516X ģ��������
 * \param[in] p_zb_addr Ŀ���ַ
 * \param[in] dir       �ܽŷ��򣬸��ֽڸ���λ 1 Ϊ�����0 Ϊ���룻
 *                      bit0 ��Ӧ GPIO1��bit3 ��Ӧ GPIO4
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EPERM  ����ʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_gpio_dir_set (am_zm516x_handle_t handle,
                                     am_zm516x_addr_t  *p_zb_addr,
                                     uint8_t            dir);

/**
 * \brief ��ȡָ����ַ ZigBee ģ��� GPIO ������������������E1��
 *
 * \param[in]  handle    ZM516X ģ��������
 * \param[in]  p_zb_addr Ŀ���ַ
 * \param[out] p_dir     ��ȡ���Ĺܽŷ��򣬸��ֽڸ���λ 1 Ϊ�����0 Ϊ���룻
 *                       bit0 ��Ӧ GPIO1��bit3 ��Ӧ GPIO4
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EPERM  ��ȡʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_gpio_dir_get (am_zm516x_handle_t handle,
                                     am_zm516x_addr_t  *p_zb_addr,
                                     uint8_t           *p_dir);

/**
 * \brief IO/AD �ɼ����ã��������E2�������óɹ��踴λ
 *
 * AW516x ϵ�� ZigBee ģ���� 4 ·�� IO �� 4 ·�� AD��IO/AD �ɼ�����������趨ģ��
 * IO �����ϴ� IO �� AD ״̬���������õ�����ʱ�䶨ʱ�ϴ� IO �� AD ״̬
 *
 * \param[in] handle     ZM516X ģ��������
 * \param[in] p_zb_addr  Ŀ���ַ
 * \param[in] dir        IO �������أ�bit0~bit3 ��Ӧ IO1~IO4������ЩλΪ 1 ʱ��
 *                       ��ʾ�����ش�����Ϊ 0 ʱ����ʾ�½��ش���
 * \param[in] period     �ϴ����ڣ���λΪ 10ms���������õ�ֵΪ 65535��
 *                       �����õ��������Ϊ 655350ms
 * \param[in] is_dormant �Ƿ����ߣ�ָʾģ���Ƿ�������״̬�����ֽ�Ϊ 1 ��ʾģ�鴦
 *                       ������״̬��IO �������õ�״̬�����仯ʱ����ģ�飬����Ŀ��
 *                       �ڵ��ַ���� IO/AD �ɼ�֡��������ڴ��� 0��ģ����˿��� IO
 *                       �����⣬����������ڶ�ʱ��ʱ���ѣ�Ȼ����Ŀ��ڵ��ַ����
 *                       IO/AD �ɼ�֡���������� IO/AD �ɼ�֡��ģ���������״̬��
 *                       ���ֽ�Ϊ 0 ��ʾģ�鲻����
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EPERM  ����ʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_io_adc_upload_set (am_zm516x_handle_t handle,
                                          am_zm516x_addr_t  *p_zb_addr,
                                          uint8_t            dir,
                                          uint16_t           period,
                                          am_bool_t          is_dormant);

/**
 * \brief IO/AD �ɼ����û�ȡ���������E2��
 * \param[in] handle        ZM516X ģ��������
 * \param[in] p_zb_addr     Ŀ���ַ
 * \param[out] p_dir        ��ȡ���� IO �����������ã��������Ҫ��ȡ������ NULL ��
 *                          �ɡ�bit0~bit3 ��Ӧ IO1~IO4������ЩλΪ 1 ʱ����ʾ������
 *                          ������Ϊ 0 ʱ����ʾ�½��ش���
 * \param[out] p_period     ��ȡ�����ϴ��������ã���λΪ 10ms���������Ҫ��ȡ����
 *                          �� NULL ����
 * \param[out] p_is_dormant ��ȡ�����Ƿ��������ã��������Ҫ��ȡ������ NULL ���ɡ�
 *                          ָʾģ���Ƿ�������״̬�����ֽ�Ϊ 1 ��ʾģ�鴦������״
 *                          ̬��IO �������õ�״̬�����仯ʱ����ģ�飬����Ŀ��ڵ��
 *                          ַ���� IO/AD �ɼ�֡��������ڴ��� 0��ģ����˿��� IO����
 *                          �⣬����������ڶ�ʱ��ʱ���ѣ�Ȼ����Ŀ��ڵ��ַ����
 *                          IO/AD �ɼ�֡���������� IO/AD �ɼ�֡��ģ���������״
 *                          ̬�����ֽ�Ϊ 0 ��ʾģ�鲻����
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EPERM  ��ȡʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_io_adc_upload_get (am_zm516x_handle_t handle,
                                          am_zm516x_addr_t  *p_zb_addr,
                                          uint8_t           *p_dir,
                                          uint16_t          *p_period,
                                          uint8_t           *p_is_dormant);

/**
 * \brief ����ָ����ַ ZigBee ģ��� GPIO ���ֵ���������E3��
 *
 * �ڵ��ø�����ǰ��Ҫ�ȵ��� I/O ���������������Ӧ�� IO ����Ϊ���
 *
 * \param[in] handle    ZM516X ģ��������
 * \param[in] p_zb_addr Ҫ���õ� ZM516X ģ���Ŀ���ַ
 * \param[in] value     GPIO ���ֵ��IO �ֽڵ� bit0~bit3 ��Ӧ IO1~IO4������ӦλΪ
 *                      1����ʾ I/O ����ߵ�ƽ������ӦλΪ 0����ʾ I/O ����͵�ƽ
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EPERM  ����ʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_gpio_set (am_zm516x_handle_t handle,
                                 am_zm516x_addr_t  *p_zb_addr,
                                 uint8_t            value);


/**
 * \brief ��ȡָ����ַ ZigBee ģ��� GPIO ����ֵ���������E3��
 *
 * �ڵ��ø�����ǰ��Ҫ�ȵ��� I/O ���������������Ӧ�� IO ����Ϊ����
 *
 * \param[in]  handle    ZM516X ģ��������
 * \param[in]  p_zb_addr Ҫ���õ� ZM516X ģ���Ŀ���ַ
 * \param[out] p_value   ��ȡ���� GPIO ����ֵ��IO �ֽڵ� bit0~bit3 ��Ӧ IO1~IO4��
 *                       ����ӦλΪ 1����ʾ I/O ����ߵ�ƽ������ӦλΪ 0����ʾ I/O
 *                       ����͵�ƽ
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EPERM  ��ȡʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_gpio_get (am_zm516x_handle_t handle,
                                 am_zm516x_addr_t  *p_zb_addr,
                                 uint8_t           *p_value);

/**
 * \brief ����ָ����ַ ZigBee ģ��� PWM ���ֵ���������E4��
 *
 * \param[in] handle    ZM516X ģ��������
 * \param[in] p_zb_addr Ҫ���õ� ZM516X ģ���Ŀ���ַ
 * \param[in] p_pwm     PWM ����ָ�룬ָ��ָ����ڴ����Ϊ sizeof(am_zm516x_pwm_t)
 *                      �� 4 ����С���������ܴ洢�� 4 �� PWM ͨ���Ĳ���
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EPERM  ����ʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_pwm_set (am_zm516x_handle_t handle,
                                am_zm516x_addr_t  *p_zb_addr,
                                am_zm516x_pwm_t   *p_pwm);


/**
 * \brief ��ȡָ����ַ ZigBee ģ��� PWM ���ֵ���ã��������E4��
 *
 * \param[in]  handle    ZM516X ģ��������
 * \param[in]  p_zb_addr Ҫ���õ� ZM516X ģ���Ŀ���ַ
 * \param[out] p_pwm     PWM ����ָ�룬ָ��ָ����ڴ����Ϊ sizeof(am_zm516x_pwm_t)
 *                       �� 4 ����С���������ܴ洢�� 4 �� PWM ͨ���Ĳ���
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EPERM  ��ȡʧ��
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EFAULT ��ַ����
 */
am_err_t am_zm516x_cfg_pwm_get (am_zm516x_handle_t handle,
                                am_zm516x_addr_t  *p_zb_addr,
                                am_zm516x_pwm_t   *p_pwm);

/**
 * \brief �������������ܣ��������E5�������óɹ��踴λ
 *
 * ����������Ϊһ����ӵ������������˽ṹ�����������ӻ��źŲ��ɴ�ʱ���ɼ����м̽ڵ�
 * �����źŴ��ݡ�ģ����������ģʽ�£�����ģ����Զ�ѡ����Χû�б�ʹ�õ� PANID ��ͨ
 * �����γ�һ�����������磬�����Զ�����һ��Ψһ�ı��������ַ���ӻ�ģ�飬�ӻ�ģ��ʹ
 * ��ʱ��ʹ�������������ܺ�Ͳ���Ҫ�����κε����ò������ӻ�ģ���ڼ����������ܸ���
 * ������ͨѶ��һ������ģ�������� 200 ���ӻ�ģ�顣��ϸ������ο��ĵ�
 * AW516x_ZigBee.pdf
 *
 * \param[in] handle ZM516X ģ��������
 * \param[in] state  ������ʹ�ܣ�0: ʧ�� 1: ʹ��
 * \param[in] type   �ڵ����ͣ�0: �����ڵ� 1: �ӻ��ڵ�
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EPERM  ����ʧ��
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zm516x_cfg_network_set (am_zm516x_handle_t handle,
                                    am_bool_t          state,
                                    uint8_t            type);

/**
 * \brief ��������ӻ��������磨�������E6��
 *
 * ����������翪���Ĵ���ʱ��Ϊ������������������������������������ʼ���ܴӻ���
 * �������󣬵����������ʱ����������ٽ��ܴӻ����������󣬴���ʱ�������������
 * �������Ĺ���״̬
 *
 * \param[in] handle ZM516X ģ��������
 * \param[in] time   ����������翪���Ĵ���ʱ�䣬��λΪ��
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EPERM  ����ʧ��
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zm516x_cfg_join_enable (am_zm516x_handle_t handle,
                                    uint16_t           time);

/**
 * \brief ��ѯ����ģ��洢�Ĵӻ���Ϣ���������E7��
 *
 * \param[in]  handle       ZM516X ģ��������
 * \param[in]  buf_size     p_slave_info ָ��Ļ�������С����λΪ
 *                          sizeof(am_zm516x_slave_info_t)
 * \param[out] p_slave_info �洢���յ��Ĵӻ���Ϣ�Ļ�����
 * \param[out] p_get_size   ʵ�ʻ�ȡ���Ĵӻ���Ϣ����
 *
 * \retval  AM_OK     ��ѯ�ɹ�
 * \retval -AM_EPERM  ��ѯʧ��
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zm516x_cfg_slave_get (am_zm516x_handle_t      handle,
                                  uint8_t                 buf_size,
                                  am_zm516x_slave_info_t *p_slave_info,
                                  uint8_t                *p_get_size);

/**
 * \brief ��ѯ���ӻ�״̬���������E8��
 *
 * \param[in]  handle           ZM516X ģ��������
 * \param[out] p_state          ��ȡ����״̬��0: �����ڵ� 1: �ӻ��ڵ㣬�粻��Ҫ��
 *                              ȡ�ò��������� NULL ����
 * \param[out] p_response_state ��ȡ������Ӧ״̬����ģ������Ϊ����ʱ��
 *                                  0: ��������
 *                                  1: �������ڼ������
 *                                  2: ��������ӻ���������
 *                              ��ģ������Ϊ�ӻ�ʱ��
 *                                  0: �ӻ����ڼ�����
 *                                  1: �ӻ��Ѽ�������
 *                                  2: �ӻ����˳�����
 *                              �粻��Ҫ��ȡ�ò��������� NULL ����
 *
 * \retval  AM_OK     ��ѯ�ɹ�
 * \retval -AM_EPERM  ��ѯʧ��
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zm516x_cfg_state_get (am_zm516x_handle_t handle,
                                  uint8_t           *p_state,
                                  uint8_t           *p_response_state);

/**
 * \brief ���� ZM516X ģ��ͨ���ţ���ʱ���D1��
 *
 * \param[in] handle ZM516X ģ��������
 * \param[in] chan   ͨ����
 *
 * \retval  AM_OK    ���óɹ�
 * \retval -AM_EPERM ����ʧ��
 */
am_err_t am_zm516x_channel_set (am_zm516x_handle_t handle, uint8_t chan);

/**
 * \brief ���� ZM516X ģ��Ŀ���ַ����ʱ���D2��
 *
 * \param[in] handle    ZM516X ģ��������
 * \param[in] p_zb_addr Ŀ���ַ
 *
 * \retval  AM_OK    ���óɹ�
 * \retval -AM_EPERM ����ʧ��
 */
am_err_t am_zm516x_dest_addr_set (am_zm516x_handle_t handle,
                                  am_zm516x_addr_t  *p_zb_addr);

/**
 * \brief ���� ZM516X ģ����յ����ݰ���ͷ�Ƿ���ʾԴ��ַ����ʱ���D3��
 *
 * \param[in] handle ZM516X ģ��������
 * \param[in] flag   ��ͷ�Ƿ���ʾԴ��ַ AM_TRUE: ��ʾ��AM_FALSE: ����ʾ
 *
 * \retval  AM_OK    ���óɹ�
 * \retval -AM_EPERM ����ʧ��
 */
am_err_t am_zm516x_display_head_set (am_zm516x_handle_t handle, am_bool_t flag);

/**
 * \brief ����ָ����ַ ZM516X ģ��� GPIO �������������ʱ���D4��
 *
 * \param[in] handle    ZM516X ģ��������
 * \param[in] p_zb_addr Ҫ���õ� ZM516X ģ���Ŀ���ַ
 * \param[in] dir       �ܽŷ��򣬸��ֽڸ���λ 1 Ϊ�����0 Ϊ���룻
 *                      bit0 ��Ӧ GPIO0��bit7 ��Ӧ GPIO7
 *
 * \retval  AM_OK    ���óɹ�
 * \retval -AM_EPERM ����ʧ��
 */
am_err_t am_zm516x_gpio_dir (am_zm516x_handle_t handle,
                             am_zm516x_addr_t  *p_zb_addr,
                             uint8_t            dir);

/**
 * \brief ��ȡָ����ַ ZM516X ģ��� GPIO ����ֵ����ʱ���D5��
 *
 * \param[in]  handle    ZM516X ģ��������
 * \param[in]  p_zb_addr Ҫ��ȡ�� ZM516X ģ���Ŀ���ַ
 * \param[out] p_value   ��ȡ���Ĺܽ�����ֵ�����ֽڸ���λ 1 Ϊ�ߵ�ƽ��0 Ϊ�͵�ƽ��
 *                       bit0 ��Ӧ GPIO0��bit7 ��Ӧ GPIO7
 *
 * \retval  AM_OK    ��ȡ�ɹ�
 * \retval -AM_EPERM ��ȡʧ��
 */
am_err_t am_zm516x_gpio_get (am_zm516x_handle_t handle,
                             am_zm516x_addr_t  *p_zb_addr,
                             uint8_t           *p_value);

/**
 * \brief ����ָ����ַ ZM516X ģ��� GPIO ���ֵ����ʱ���D6��
 *
 * \param[in] handle    ZM516X ģ��������
 * \param[in] p_zb_addr Ҫ���õ� ZM516X ģ���Ŀ���ַ
 * \param[in] value     �ܽ����ֵ�����ֽڸ���λ 1 Ϊ�ߵ�ƽ��0 Ϊ�͵�ƽ��
 *                      bit0 ��Ӧ GPIO0��bit7 ��Ӧ GPIO7
 *
 * \retval  AM_OK    ���óɹ�
 * \retval -AM_EPERM ����ʧ��
 */
am_err_t am_zm516x_gpio_set (am_zm516x_handle_t handle,
                             am_zm516x_addr_t  *p_zb_addr,
                             uint8_t            value);

/**
 * \brief ��ȡָ����ַ ZM516X ģ��� AD ת��ֵ����ʱ���D7��
 *
 * ��ȡ���� AD ֵΪ AD ��ת��ֵ����Ҫ�ο� ZM516X ģ���û��ֲ�
 * ���� ZM516X ģ�� AD ��λ�����ο���ѹת��Ϊ��ѹֵ
 *
 * \param[in]  handle    ZM516X ģ��������
 * \param[in]  p_zb_addr Ҫ��ȡ�� ZM516X ģ���Ŀ���ַ
 * \param[in]  chan      AD ��ͨ����
 * \param[out] p_value   AD ��ת��ֵ
 *
 * \retval  AM_OK    ��ȡ�ɹ�
 * \retval -AM_EPERM ��ȡʧ��
 */
am_err_t am_zm516x_ad_get (am_zm516x_handle_t handle,
                           am_zm516x_addr_t  *p_zb_addr,
                           uint8_t            chan,
                           uint16_t          *p_value);

/**
 * \brief ���� ZM516X ģ�����˯��ģʽ����ʱ���D8��
 *
 * \param[in] handle ZM516X ģ��������
 *
 * \return ��
 */
void am_zm516x_enter_sleep (am_zm516x_handle_t handle);

/**
 * \brief ����ZM516Xģ���ͨѶģʽ����ʱ���D9��
 *
 * \param[in] handle ZM516Xģ��������
 * \param[in] mode   ģ���ͨѶģʽ
 *
 * \retval  AM_OK    ���óɹ�
 * \retval -AM_EPERM ����ʧ��
 */
am_err_t am_zm516x_mode_set (am_zm516x_handle_t    handle,
                             am_zm516x_comm_mode_t mode);

/**
 * \brief ��ȡָ����ַ ZM516X ģ����ź�ǿ�ȣ���ʱ���DA��
 *
 * \param[in]  handle    ZM516X ģ��������
 * \param[in]  p_zb_addr Ҫ��ȡ�ı��� ZM516X ģ����Ŀ���ַ֮����ź�ǿ��
 * \param[out] p_signal  �ź�ǿ��
 *
 * \retval  AM_OK    ��ȡ�ɹ�
 * \retval -AM_EPERM ��ȡʧ��
 */
am_err_t am_zm516x_sigal_get (am_zm516x_handle_t handle,
                              am_zm516x_addr_t  *p_zb_addr,
                              uint8_t           *p_signal);

/**
 * \brief ��ʼ�� ZM516X ģ������
 *
 * \param[in] p_dev       ZM516X ģ���豸�ṹ��
 * \param[in] p_info      ZM516X ģ��ʵ����Ϣ
 * \param[in] uart_handle ���� ZM516X ģ��Ĵ��ھ��
 *
 * \return ZM516X ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_zm516x_handle_t am_zm516x_init (am_zm516x_dev_t            *p_dev,
                                   const am_zm516x_dev_info_t *p_info,
                                   am_uart_handle_t            uart_handle);

/**
 * \brief ���ʼ�� ZM516X ģ������
 *
 * \param[in] handle ͨ��am_zm516x_init������ȡ��ZM516X���
 *
 * \retval  AM_OK     ���ʼ���ɹ�
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zm516x_deinit (am_zm516x_handle_t handle);

/** @} am_if_zm516x */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZM516X_H */

/* end of file */
