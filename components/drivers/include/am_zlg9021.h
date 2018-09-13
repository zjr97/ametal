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
 * \brief ZLG9021�ӿں���
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-06  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_ZLG9021_H
#define __AM_ZLG9021_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"
#include "am_i2c.h"
#include "am_softimer.h"
#include "am_uart_rngbuf.h"

/**
 * @addtogroup am_if_zlg9021
 * @copydoc am_zlg9021.h
 * @{
 */

/**
 * \name ZLG9021��������
 * 
 *     ������������ am_zlg9021_ioctl() ������ cmd ��������p_arg������ʵ����������
 * ����Ĳ�ͬ����ͬ��
 *
 * @{
 */

/**
 * \brief ����BLE���Ӽ������λms
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ��ʾ���õ�BLE����ʱ������
 * ��Чֵ�У�20��50��100��200��300��400��500��1000��1500��2000
 */
#define  AM_ZLG9021_BLE_CONNECT_INTERVAL_SET     1

/**
 * \brief ��ȡBLE���Ӽ������λms
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡBLE����ʱ������
 */
#define  AM_ZLG9021_BLE_CONNECT_INTERVAL_GET     2

/**
 * \brief ģ��������
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ����ʾ��ģ�������ַ������ַ���
 * ������Ҫ��15���ַ����ڡ�
 */
#define  AM_ZLG9021_RENAME                       3

/**
 * \brief ģ�����������Զ���ģ����������MAC��ַ��
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ����ʾ��ģ�������ַ������ַ���
 * ������Ҫ��15���ַ����ڡ����º�ģ��ᱻ����Ϊ NAME(xxxxxx)��������Ϊģ��� MAC
 * ��ַ�� 3 ���ֽڵ� Hex �룬 ���� iOS ϵͳʶ��ģ��
 */
#define  AM_ZLG9021_RENAME_MAC_STR              4


/**
 * \brief ��ȡģ����
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ��ת��ģ�����Ļ����������飩��
 * ��������С����Ϊ15�ֽڡ�
 */
#define  AM_ZLG9021_NAME_GET                     5

/**
 * \brief ���ò�����
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ��ʾ���õĲ����ʣ�
 * ��Чֵ�У�4800��9600��19200��38400��57600��115200
 */
#define  AM_ZLG9021_BAUD_SET                     6


/**
 * \brief ��ȡ������
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ������
 */
#define  AM_ZLG9021_BAUD_GET                     7



/**
 * \brief ��ȡMAC��ַ
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ��13�ַ��Ļ�����
 */
#define  AM_ZLG9021_MAC_GET                       8



/**
 * \brief ��λZLG9021
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define  AM_ZLG9021_RESET                         9


/**
 * \brief ����BLE�Ĺ㲥���ڣ���λ:ms��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ��ʾ�㲥����
 * ��Чֵ�У�200��500��1000��1500��2000��2500��3000��4000��5000
 */
#define  AM_ZLG9021_BLE_ADV_PERIOD_SET            10


/**
 * \brief ��ȡBLE�Ĺ㲥���ڣ���λ:ms��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����Ի�ȡ�㲥����
 */
#define  AM_ZLG9021_BLE_ADV_PERIOD_GET            11


/**
 * \brief ���÷��͹��ʣ�dBm��
 *
 * ��ʱ�� p_arg ����������Ϊ  int ���ͣ���ֵ��ʾ���书��
 * ��Чֵ�У�-20��-18��-16��-14��-12��-10��-8��-6��-4��-2��0��2��4
 */
#define  AM_ZLG9021_TX_POWER_SET                  12


/**
 * \brief ��ȡ���͹��ʣ�dBm��
 *
 * ��ʱ�� p_arg ����������Ϊ  int ָ�����ͣ����Ի�ȡ�㲥����
 */
#define  AM_ZLG9021_TX_POWER_GET                  13


/**
 * \brief ����BCTS����͵�ƽ����������֮�����ʱ����λ:ms��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ��ʾ��ʱʱ��
 * ��Чֵ�У�0��10��20��30
 */
#define  AM_ZLG9021_BCTS_DELAY_SET                14


/**
 * \brief ��ȡBCTS����͵�ƽ����������֮�����ʱ����λ:ms��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ��ʱʱ��
 */
#define  AM_ZLG9021_BCTS_DELAY_GET                15


/**
 * \brief �͹���ģʽ
 *
 * ��ʱ�� p_arg ����Ϊ am_bool_t��ֵΪAM_TRUEʱ����͹���ģʽ��ֵΪAM_FALSEʱ�˳��͹���ģʽ��
 *
 * ��p_arg��ֵΪ AM_TRUE���ú���ʹZLG9021����͹���ģʽ����ʱ����EN������Ч����ʼ��ʱ
 * ʵ����Ϣ�ṩ����������EN���ţ�ģ�鲻������������ͣ���EN������Ч����ʹ���������
 * ����ʹZLG9021����͹���ģʽ��
 *
 * ��p_arg��ֵΪFLASE����ʾ�˳��͹���ģʽ��ģ��ָ�����������
 */
#define  AM_ZLG9021_POWERDOWN                     16

/**
 * \brief ��ȡ�̼��汾��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ�汾��
 * ��ȡ��ֵΪ�������磺100����Ӧ1.00�汾����101����Ӧ1.01�汾��
 */
#define  AM_ZLG9021_VERSION_GET                   17

/**
 * \brief ��ȡ��ǰ������״̬
 *
 * ��ʱ�� p_arg ����������Ϊ  am_bool_t ָ�����ͣ����ڻ�ȡ����״̬��
 * ��ֵΪ AM_TRUE�����������ӣ���ֵΪ AM_FALSE������δ����
 */
#define  AM_ZLG9021_CONSTATE_GET                  18

/**
 * \brief �Ͽ���ǰ����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define  AM_ZLG9021_DISCONNECT                    19

/**
 * \brief ����ģ��������
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ����ʾ�������ַ������ַ���
 * ������Ҫ��15���ַ����ڡ����º�ģ��ᱻ����Ϊ NAME(xxxxxx)��������Ϊģ��� MAC
 * ��ַ�� 3 ���ֽڵ� Hex �룬 ���� iOS ϵͳʶ��ģ��
 */
#define  AM_ZLG9021_PWD_SET                       20

/**
 * \brief ��ȡģ��������
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ��ת������루�ַ������Ļ�������
 * ��������С����Ϊ15�ֽڡ�
 */
#define  AM_ZLG9021_PWD_GET                       21

/**
 * \brief �����Ƿ������ܴ���
 *
 * ��ʱ�� p_arg ����������Ϊ  am_bool_t ���ͣ� ֵΪAM_TRUEʱ����������ܹ��ܣ�ֵΪAM_FALSE
 * ʱ�رմ�����ܹ��ܡ�
 */
#define  AM_ZLG9021_ENC_SET                       22

/**
 * \brief ��ȡģ��ļ���״̬
 *
 * ��ʱ�� p_arg ����������Ϊ  am_bool_t ָ�����ͣ�  ���ڻ�ȡ��ǰ�����Ƿ���ܡ�
 */
#define  AM_ZLG9021_ENC_GET                       23

/**
 * \brief �ָ���������
 *
 * p_arg����ΪNULL
 *
 * �����������ϵͳ������ 30s ��ִ�У�������ȷ�ָ��������ã����򣬿��ָܻ���������
 * ʧ�ܡ�ʹ�ø�����ʱ����Ҫȷ��ʵ����Ϣ�е� RESTORE ������Ч����Ϊ-1��
 */
#define  AM_ZLG9021_RESTORE                       30

/** @} */

/**
 * \name ZLG9021֧��һЩ���ڿ�������
 * @{
 */

/**
 * \brief ��ȡ���ջ��������ѽ��յ����ݸ���
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ���ջ��������ѽ��յ����ݸ���
 */
#define AM_ZLG9021_NREAD                         24

/**
 * \brief ��ȡ���ͻ���������д������ݸ���
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ���ͻ���������д������ݸ���
 */
#define AM_ZLG9021_NWRITE                        25

/**
 * \brief ��շ��ͻ������ͽ��ջ�����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define AM_ZLG9021_FLUSH                         26

/**
 * \brief ��շ��ͻ�����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define AM_ZLG9021_WFLUSH                        27

/**
 * \brief ��ս��ջ�����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define AM_ZLG9021_RFLUSH                       28

/**
 * \brief ���ý��ճ�ʱʱ�䣨��λ��ms��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ����
 */
#define AM_ZLG9021_TIMEOUT                      29

/** @} */
 
/**
 * \brief ZLG9021ʵ����Ϣ�ṹ�嶨��
 */
typedef struct am_zlg9021_devinfo {

    /** \brief EN���ţ���EN���Ź̶��ӵ͵�ƽ��������MCU���ƣ���ʱ����ֵ����Ϊ -1 */
    int          pin_en;

    /** \brief BRTS���ţ���������ÿ�η���������ZLG9021ǰ�����ͣ�����������  */
    int          pin_brts;

    /** \brief ��λ����  */
    int          pin_rst;

    /** \brief RESTORE���ţ����ڻָ���������   */
    int          pin_restore;

    /** \brief ģ�鵱ǰʹ�õĲ�����        */
    uint32_t     baudrate;

    /** \brief ���ڴ��ڽ��յĻ������������С��32����     */
    uint8_t     *p_uart_rxbuf;

    /** \brief ���ڴ��ڷ��͵Ļ������������С��32����     */
    uint8_t     *p_uart_txbuf;

    /** \brief ���ڴ��ڽ��յĻ�������С */
    uint16_t     rxbuf_size;

    /** \brief ���ڴ��ڷ��͵Ļ�������С */
    uint16_t     txbuf_size;

} am_zlg9021_devinfo_t;

/**
 * \brief ZLG9021�豸�ṹ�嶨��
 */
typedef struct am_zlg9021_dev {

    /** \brief �����Ƿ��ڷ���֮��  */
    volatile am_bool_t          in_send;

    /** \brief brts �Ƿ���Ҫ����Ϊ�ߵ�ƽ */
    volatile am_bool_t          is_brts;

    /** \brief BLE is connected? */
    volatile int                connect_state;

    /** \brief ������״̬  */
    volatile int                cmd_proc_state;

    /** \brief ��ȡ "TIM:CONNECT"��״̬  */
    volatile int                stat_rep_type;

    /** \brief ��ȡ "TIM:DISCONNECT"��״̬  */
    volatile int                stat_rep_cnt;

    /** \brief UARTʵ�����                    */
    am_uart_handle_t            uart_handle;

    /** \brief �������ݻ��λ�����      */
    struct am_rngbuf            rx_rngbuf;

    /** \brief �������ݻ��λ�����      */
    struct am_rngbuf            tx_rngbuf;

    /** \brief ���ڱ����豸��Ϣָ�� */
    const am_zlg9021_devinfo_t *p_devinfo;

    /** \brief ���ڽ�������Ӧ��ĵȴ��ṹ��       */
    am_wait_t                   ack_wait;

    /** \brief ���ڽ������ݵĵȴ��ṹ��   */
    am_wait_t                   rx_wait;

    /** \brief ���ճ�ʱʱ��                */
    volatile uint32_t           timeout_ms;

    /** \brief �����Ӧ���ջ�����  */
    uint8_t                    *p_cmd_rxbuf;

    /** \brief �����Ӧ���ջ������ĳ���  */
    volatile int                cmd_rxbuf_len;

    /** \brief �����Ӧ�Ѿ����յĳ���  */
    volatile int                cmd_rx_len;

    /** \brief The Timer for timeout */
    am_softimer_t               timer;

    /** \brief The Timer for BRTS */
    am_softimer_t               timer_brts;

} am_zlg9021_dev_t;


/** \brief ����ZLG9021�������  */
typedef struct am_zlg9021_dev *am_zlg9021_handle_t;
                                      
/**
 * \brief ZLG9021��ʼ������
 *
 * ʹ��ZLG9021ǰ��Ӧ�����ȵ��øó�ʼ���������Ի�ȡ����ZLG9021��handle��
 *
 * \param[in] p_dev      : ָ��ZLG9021�豸��ָ��
 * \param[in] p_devinfo  : ָ��ZLG9021�豸��Ϣ��ָ��
 * \param[in] uart_handle : UART��׼������������ʹ�ø�UART�����ZLG9021ͨ�ţ�
 *
 * \return ����ZLG9021��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 *
 * \note �豸ָ��p_devָ����豸ֻ��Ҫ���壬����Ҫ�ڵ��ñ�����ǰ��ʼ����
 */
am_zlg9021_handle_t am_zlg9021_init (am_zlg9021_dev_t           *p_dev,
                                     const am_zlg9021_devinfo_t *p_devinfo,
                                     am_uart_handle_t            uart_handle);


/**
 * \brief ZLG9021���ƺ���
 *
 * \param[in] handle    : ZLG9021ʵ�����
 * \param[in] cmd       : ����ָ����磺#AM_ZLG9021_BAUD_SET
 * \param[in,out] p_arg : �����Ӧ�Ĳ��������磺 115200
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_EIO     : ִ�д���
 * \retval -AM_ENOTSUP : ָ�֧��
 *
 * \note ����
 */
int am_zlg9021_ioctl(am_zlg9021_handle_t  handle,
                     int                  cmd,
                     void                *p_arg);


/**
 * \brief ����͸������
 *
 * \param[in] handle : ZLG9021ʵ�����
 * \param[in] p_buf  : �����͵�����
 * \param[in] len    : ���ݳ���
 *
 * \return �Ǹ�����ʵ�ʷ��͵��ֽ���������������ʧ��
 */
int am_zlg9021_send (am_zlg9021_handle_t  handle,
                     const uint8_t       *p_buf,
                     int                  len);


/**
 * \brief ����͸������
 *
 * \param[in] handle : ZLG9021ʵ�����
 * \param[in] p_buf  : �����͵�����
 * \param[in] len    : ���ݳ���
 *
 * \return �Ǹ�����ʵ�ʽ��յ��ֽ���������������ʧ��
 */
int am_zlg9021_recv (am_zlg9021_handle_t  handle,
                     uint8_t             *p_buf,
                     int                  len);
 
/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG9021_H */

/* end of file */
