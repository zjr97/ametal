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
 * \brief SC16IS7XX �����ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� am_sc16is7xx.h
 *
 * \par ʹ��ʾ��
 * \code
 * #include "am_sc16is7xx.h"
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 18-05-22  pea, first implementation
 * \endinternal
 */

#ifndef __AM_SC16IS7XX_H
#define __AM_SC16IS7XX_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_sc16is7xx
 * \copydoc am_sc16is7xx.h
 * @{
 */

#include "ametal.h"
#include "am_i2c.h"
#include "am_uart.h"
#include "am_wait.h"
#include "am_types.h"

#define  SC16IS7XX_CHAN_MAX    2     /**< \brief ��󴮿�ͨ���� */
#define  SC16IS7XX_FIFO_SIZE   64    /**< \brief FIFO ��С */

/** \brief SC16IS7XX �ص���Ϣ */
typedef struct am_sc16is7xx_cbinfo {
    void *p_arg[2];
} am_sc16is7xx_cbinfo_t;

/** \brief SC16IS7XX �豸��Ϣ */
typedef struct am_sc16is7xx_devinfo {

    /** \brief ����ͨ������ */
    uint8_t  chan_num;

    /** \brief I2C 7 λ�ӻ���ַ */
    uint8_t  i2c_addr;

    /** \brief ��λ���� */
    int      rst_pin;

    /** \brief �ж����ţ�����Ϊ -1 ʱ����ֻ֧����ѯģʽ */
    int      irq_pin;

    /** \brief ϵͳʱ��Ƶ�ʣ���λΪ HZ */
    uint32_t clk_freq;

    /** \brief ���ڲ����� */
    uint32_t serial_rate[SC16IS7XX_CHAN_MAX];

    /** \brief ��������λ��ֵΪ 5~8 */
    uint8_t  serial_data[SC16IS7XX_CHAN_MAX];

    /** \brief ����У��λ��0:��У�� 1:��У�� 2:żУ�� */
    uint8_t  serial_parity[SC16IS7XX_CHAN_MAX];

    /** \brief ����ֹͣλ��ֵΪ 1~2 */
    uint8_t  serial_stop[SC16IS7XX_CHAN_MAX];

    /** \brief RS485 ������ƺ���, AM_TRUE:����ģʽ�� AM_FALSE:����ģʽ */
    void   (*pfn_rs485_dir)(uint8_t chan, am_bool_t is_txmode);

    /** \brief ƽ̨��ʼ������ */
    void   (*pfn_plfm_init)(void);

    /** \brief ƽ̨ȥ��ʼ������ */
    void   (*pfn_plfm_deinit)(void);

} am_sc16is7xx_devinfo_t;

/** \brief SC16IS7XX �豸 */
typedef struct am_sc16is7xx_dev {

    /** \brief ��׼ UART ���� */
    am_uart_serv_t          uart_serv[SC16IS7XX_CHAN_MAX];

    /** \brief ָ���û�ע��� txchar_get ���� */
    am_uart_txchar_get_t    pfn_txchar_get[SC16IS7XX_CHAN_MAX];

    /** \brief ָ���û�ע��� rxchar_put ���� */
    am_uart_rxchar_put_t    pfn_rxchar_put[SC16IS7XX_CHAN_MAX];

    /** \brief ָ���û�ע��Ĵ���ص����� */
    am_uart_err_t           pfn_err[SC16IS7XX_CHAN_MAX];

    /** \brief txchar_get �������� */
    void                   *p_txget_arg[SC16IS7XX_CHAN_MAX];

    /** \brief rxchar_put �������� */
    void                   *p_rxput_arg[SC16IS7XX_CHAN_MAX];

    /** \brief ����ص������û����� */
    void                   *p_err_arg[SC16IS7XX_CHAN_MAX];

    /** \brief ���ڲ����� */
    uint32_t                serial_rate[SC16IS7XX_CHAN_MAX];

    /** \brief ����ѡ�� */
    uint32_t                serial_opts[SC16IS7XX_CHAN_MAX];

    /** \brief ����ģʽ */
    uint32_t                serial_mode[SC16IS7XX_CHAN_MAX];

    /** \brief ���������ģʽ */
    uint32_t                serial_mode_avail;

    /** \brief �Ƿ�ʹ���� RS485 ģʽ */
    am_bool_t               is_rs485_en[SC16IS7XX_CHAN_MAX];

    /** \brief IIR �Ĵ��������� */
    uint8_t                 iir_reg[SC16IS7XX_CHAN_MAX];

    /** \brief IER �Ĵ��������� */
    uint8_t                 ier_reg[SC16IS7XX_CHAN_MAX];

    /** \brief LCR �Ĵ��������� */
    uint8_t                 lcr_reg[SC16IS7XX_CHAN_MAX];

    /** \brief LSR �Ĵ��������� */
    uint8_t                 lsr_reg[SC16IS7XX_CHAN_MAX];

    /** \brief RXLVL �Ĵ��������� */
    uint8_t                 rxlvl_reg[SC16IS7XX_CHAN_MAX];

    /** \brief TXLVL �Ĵ��������� */
    uint8_t                 txlvl_reg[SC16IS7XX_CHAN_MAX];

    /** \brief ���ջ����� */
    uint8_t                 rx_buf[SC16IS7XX_CHAN_MAX][SC16IS7XX_FIFO_SIZE];

    /** \brief ���ͻ����� */
    uint8_t                 tx_buf[SC16IS7XX_CHAN_MAX][SC16IS7XX_FIFO_SIZE];

    /** \brief I2C ��׼���������� */
    am_i2c_handle_t         i2c_handle;

    /** \brief I2C ���豸 */
    am_i2c_device_t         i2c_dev[SC16IS7XX_CHAN_MAX];

    /** \brief I2C ��Ϣ */
    am_i2c_message_t        i2c_msg[SC16IS7XX_CHAN_MAX];

    /** \brief I2C ���� */
    am_i2c_transfer_t       i2c_trans[SC16IS7XX_CHAN_MAX][2];

    /** \brief ��ǰ������ӵ�ַ */
    uint8_t                 subaddr[SC16IS7XX_CHAN_MAX];

    /** \brief I2C ������� */
    uint32_t                i2c_err_cnt[SC16IS7XX_CHAN_MAX];

    /** \brief ��ǰ I2C �Ƿ�æ */
    volatile am_bool_t      is_i2c_busy[SC16IS7XX_CHAN_MAX];

    /** \brief ��ǰ״̬��״̬ */
    volatile uint8_t        state[SC16IS7XX_CHAN_MAX];

    /** \brief ���ַ���ȡ��־λ */
    volatile am_err_t       char_none_flag[SC16IS7XX_CHAN_MAX];

    /** \brief �����жϷ��ͱ�־λ */
    volatile am_err_t       int_en_flag[SC16IS7XX_CHAN_MAX];

    /** \brief �ж��Ƿ�ʹ�� */
    volatile am_bool_t      is_irq_en[SC16IS7XX_CHAN_MAX];

    /** \brief ״̬������ */
    uint32_t                sm_cnt[SC16IS7XX_CHAN_MAX];

    /** \brief SC16IS7XX ������Ϣ */
    am_sc16is7xx_cbinfo_t   uartinfo[SC16IS7XX_CHAN_MAX];

    /** \brief SC16IS7XX I2C ��Ϣ */
    am_sc16is7xx_cbinfo_t   i2cinfo[SC16IS7XX_CHAN_MAX];

    /** \brief �豸��Ϣ */
    am_sc16is7xx_devinfo_t *p_devinfo;

} am_sc16is7xx_dev_t;

/** \brief SC16IS7XX ��׼�������������Ͷ��� */
typedef struct am_sc16is7xx_dev *am_sc16is7xx_handle_t;

/**
 * \brief ��ȡָ��ͨ���� UART ��׼����������
 *
 * \param[in] handle SC16IS7XX ��׼������
 * \param[in] chan   ͨ����
 *
 * \return UART ��׼��������������Ϊ NULL��������ȡʧ��
 */
am_uart_handle_t am_sc16is7xx_uart_handle_get (am_sc16is7xx_handle_t handle,
                                               uint8_t               chan);

/**
 * \brief ��ʼ�� SC16IS7XX ����
 *
 * \param[in] p_dev      SC16IS7XX �豸�ṹ��
 * \param[in] p_info     SC16IS7XX ʵ����Ϣ
 * \param[in] i2c_handle ���� SC16IS7XX �� I2C ���
 *
 * \return SC16IS7XX ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_sc16is7xx_handle_t am_sc16is7xx_init (am_sc16is7xx_dev_t           *p_dev,
                                         const am_sc16is7xx_devinfo_t *p_devinfo,
                                         am_i2c_handle_t               i2c_handle);

/**
 * \brief ���ʼ�� SC16IS7XX ����
 *
 * \param[in] handle ͨ�� am_sc16is7xx_init ������ȡ�� SC16IS7XX ���
 *
 * \retval  AM_OK     ���ʼ���ɹ�
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_sc16is7xx_deinit (am_sc16is7xx_handle_t handle);

/**
 * @} am_if_sc16is7xx
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SC16IS7XX_H */

/* end of file */
