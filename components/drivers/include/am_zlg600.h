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
 * \brief ZLG600�ײ���������
 * 
 * \internal
 * \par Modification history
 * - 1.01 16-08-03  sky, modified.
 * - 1.00 15-09-03  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_ZLG600_H
#define __AM_ZLG600_H
 
#include "am_types.h"
#include "am_uart_rngbuf.h"
#include "am_i2c.h"

/**
 * @addtogroup am_if_zlg600
 * @copydoc am_zlg600.h
 * @{
 */
 
/** 
 * \name ZLG600��ͨ��ģʽ������ģʽ
 * @{
 */

#define AM_ZLG600_MODE_AUTO_CHECK         0         /**< \brief �Զ����ģʽ  */
#define AM_ZLG600_MODE_I2C                1         /**< \brief I2Cģʽ       */
#define AM_ZLG600_MODE_UART               2         /**< \brief ����ģʽ      */
#define AM_ZLG600_MODE_MASTER       (1 << 4)        /**< \brief ����ģʽ���������ܣ� */
#define AM_ZLG600_MODE_SLAVE        (0 << 4)        /**< \brief �ӻ�ģʽ��Ĭ�ϣ� */

/** @}*/

/**
 * \name ZLG600�����ӷ�ʽ
 * @{
 */

#define AM_ZLG600_CMNT_UART        0            /**< \brief UART���� */
#define AM_ZLG600_CMNT_I2C         1            /**< \brief I2C���� */

/** @} */

 /** 
 * \name ZLG600��֡��ʽ
 * @{
 */

#define AM_ZLG600_FRAME_FMT_OLD  0             /**< \brief  ��֡��ʽ      */
#define AM_ZLG600_FRAME_FMT_NEW  1             /**< \brief  ��֡��ʽ      */

 /** @} */
 
/**
 * \name ֧�ֵĲ�����
 * @{
 */

#define  AM_ZLG600_BAUDRATE_9600      9600     /**< \brief ������ 9600   */
#define  AM_ZLG600_BAUDRATE_19200     19200    /**< \brief ������ 19200  */
#define  AM_ZLG600_BAUDRATE_28800     28800    /**< \brief ������ 28800  */
#define  AM_ZLG600_BAUDRATE_38400     38400    /**< \brief ������ 38400  */
#define  AM_ZLG600_BAUDRATE_57600     57600    /**< \brief ������ 57600  */
#define  AM_ZLG600_BAUDRATE_115200    115200   /**< \brief ������ 115200 */
#define  AM_ZLG600_BAUDRATE_172800    172800   /**< \brief ������ 172800 */
#define  AM_ZLG600_BAUDRATE_230400    230400   /**< \brief ������ 230400 */

/** @}*/

/**
 * \brief ZLG600�Զ������Ϣ�ṹ��
 */
typedef struct am_zlg600_auto_detect_info {

    /**
     * \brief ���ģʽ�����ü�⶯�����Ƿ�����жϡ�������⡢��ɶ����� #AM_ZLG600_MIFARE_CARD_AD_HALT
     */
    uint8_t        ad_mode;

    /**
     * \brief ��������ģʽ������������������һ��������ͬʱ���� #AM_ZLG600_MIFARE_CARD_TX_TX1
     */
    uint8_t        tx_mode;

    /**
     * \brief ����ģʽ��������п������п� #AM_ZLG600_MIFARE_CARD_REQ_IDLE
     */
    uint8_t        req_mode;

    /**
     * \brief ��֤ģʽ��E2��Կ��֤��ֱ����֤����֤ #AM_ZLG600_MIFARE_CARD_AUTH_E2
     */
    uint8_t        auth_mode;           /**< \brief ��֤ģʽ */

    /**
     * \brief ��Կ���ͣ�#AM_ZLG600_IC_KEY_TYPE_A �� #AM_ZLG600_IC_KEY_TYPE_B
     *        ���auth_modeѡ�����AM_ZLG600_MIFARE_CARD_AUTH_NO��
     *        ��key_type����Ϊ����ֵ
     */
    uint8_t        key_type;

    /** \brief ��Կ */
    uint8_t        key[16];

    /** \brief ��Կ���� */
    uint8_t        key_len;

    /**
     * \brief ��֤���
     *          S50�� 0��63��
     *          S70�� 0��255��
     *          PLUS CPU 2K�� 0��127��
     *          PLUS CPU 4K�� 0��255��
     */
    uint8_t        nblock;

} am_zlg600_auto_detect_info_t;

/**
 * \brief ��׼��ZLG600�豸����ṹ�嶨��
 */
typedef struct am_zlg600_serv {

    void          *p_cookie;            /**< \brief �����������ڲ�ʹ�� */

    uint32_t       timeout_ms;          /**< \brief ����ȴ�ʱ��(����) */

    uint8_t        frame_seq;           /**< \brief ��¼���� */
    uint8_t        work_mode;           /**< \brief ��ǰʹ�õĹ���ģʽ(����ģʽ) */
    uint8_t        cur_addr;            /**< \brief ��ǰ����ĵ�ַ(7bit) */

    uint8_t        auto_detect;         /**< \brief �Զ����ģʽ */
    uint8_t        auto_detect_read;    /**< \brief �Զ�������־ */
    am_pfnvoid_t   pfn_callback;        /**< \brief �ص����� */
    void          *p_arg;               /**< \brief �ص������Ĳ��� */

    am_pfnvoid_t                  pfn_cmd_timeout_set;          /**< \brief ָ�ʱʱ������ */
    am_pfnvoid_t                  pfn_frame_proc;               /**< \brief ֡������ */
    am_pfnvoid_t                  pfn_auto_detect_trigger_set;  /**< \brief �Զ���ⴥ������ */
    am_zlg600_auto_detect_info_t *p_auto_detect_info;           /**< \brief �Զ������Ϣ */

} am_zlg600_serv_t;

/**
 * \brief ZLG600��׼����handle����
 */
typedef am_zlg600_serv_t *am_zlg600_handle_t;

/** 
 * \brief ZLG600������ͨ�ţ��豸����
 */
typedef struct am_zlg600_uart_dev {

    /** \brief ZLG600 ��׼���� */
    am_zlg600_serv_t         zlg600_serv;

    /** \brief ���ڣ������������豸           */
    am_uart_rngbuf_dev_t     uart_ringbuf_dev;
    
    /** \brief ���ڣ�������������׼����handle */
    am_uart_rngbuf_handle_t  uart_ringbuf_handle;

    /** \brief ֡������ */
    am_pfnvoid_t   pfn_frame_proc;

} am_zlg600_uart_dev_t;

/** 
 * \brief ZLG600 (UARTͨ��ģʽ) ��Ϣ����
 */
typedef struct am_zlg600_uart_dev_info {

    /** \brief ���ڴ��ڽ��յĻ������������С��64����     */
    uint8_t     *p_uart_rxbuf;

    /** \brief ���ڴ��ڷ��͵Ļ������������С��64����     */
    uint8_t     *p_uart_txbuf;

    /** \brief ���ڴ��ڽ��յĻ�������С */
    uint16_t     rxbuf_size;

    /** \brief ���ڴ��ڷ��͵Ļ�������С */
    uint16_t     txbuf_size;

    /** \brief ��ZLG600ͨ�ŵĲ�����(UARTģʽ��ʹ��) */
    uint32_t     baudrate;

    /** \brief ��ʼ��ʱʹ�õ�ģʽ #AM_ZLG600_MODE_AUTO_CHECK */
    uint8_t      now_mode;

    /** \brief ZLG600�Ĵӻ���ַ(7bit) */
    uint8_t      local_addr;

} am_zlg600_uart_dev_info_t;

/**
 * \brief ZLG600��I2Cͨ�ţ��豸����
 */
typedef struct am_zlg600_i2c_dev {
    
    /** \brief ZLG600 ��׼���� */
    am_zlg600_serv_t          zlg600_serv;
 
    /** \brief I2C��׼������ */
    am_i2c_handle_t           i2c_handle;
    
    /** \brief �ж�����           */
    int                       pin;
    
    /** \brief I2C transfer �����ַ */
    am_i2c_transfer_t        *p_trans;

    /** \brief I2C transfer ���泤�� */
    uint8_t                   trans_len;

    /** \brief ���ڵȴ�I2C������� */
    am_wait_t                 wait;

    /** \brief ֡������ */
    am_pfnvoid_t   pfn_frame_proc;
 
} am_zlg600_i2c_dev_t;

/**
 * \brief ZLG600 (I2Cͨ��ģʽ) ��Ϣ����
 */
typedef struct am_zlg600_i2c_dev_info {

    /** \brief �ж����ţ�ʹ��I2Cͨ��ʱ����Ҫʹ�õ�һ���ж����� */
    int                pin;

    /** \brief ZLG600�Ĵӻ���ַ(7bit) */
    uint8_t            local_addr;

    /** \brief ��ʼ��ʱʹ�õ�ģʽ #AM_ZLG600_MODE_AUTO_CHECK */
    uint8_t            now_mode;

    /** \brief I2C transfer �����ַ */
    am_i2c_transfer_t *p_trans;

    /** \brief I2C transfer ���泤��(Ŀǰ���ָ���Ҫ9��trans) */
    uint8_t            trans_len;

} am_zlg600_i2c_dev_info_t;

/**
 * \brief ��ʼ��ZLG600��ʹ��UART��֡ͨ��ģʽ������ȡ������ZLG600�ı�׼����handle
 *
 * ��ظ���ʵ��Ӳ��ʹ�ú���ͨ�����ӷ�ʽѡ����ʹ��UART����ʹ�øú�����ʼ��
 * �Ի��handle��������ʹ��am_zlg600_i2c_init()�������handle��
 *
 * \param[in] p_dev        : ָ��ZLG600�豸��ָ��
 * \param[in] uart_handle  : ��ZLG600������UART������ʹ�ø�handle����UARTͨ��
 * \param[in] p_uart_info  : UARTͨ��ģʽ�����Ϣ
 *
 * \return ���� ZLG600 �Ĳ�������������ʼ��ʧ�ܣ��򷵻�NULL
 */ 
am_zlg600_handle_t am_zlg600_uart_old_init (am_zlg600_uart_dev_t            *p_dev,
                                            am_uart_handle_t                 uart_handle,
                                            const am_zlg600_uart_dev_info_t *p_uart_info);

/**
 * \brief ��ʼ��ZLG600��ʹ��UART��֡ͨ��ģʽ������ȡ������ZLG600�ı�׼����handle
 *
 * ��ظ���ʵ��Ӳ��ʹ�ú���ͨ�����ӷ�ʽѡ����ʹ��UART����ʹ�øú�����ʼ��
 * �Ի��handle��������ʹ��am_zlg600_i2c_init()�������handle��
 *
 * \param[in] p_dev        : ָ��ZLG600�豸��ָ��
 * \param[in] uart_handle  : ��ZLG600������UART������ʹ�ø�handle����UARTͨ��
 * \param[in] p_uart_info  : UARTͨ��ģʽ�����Ϣ
 *
 * \return ���� ZLG600 �Ĳ�������������ʼ��ʧ�ܣ��򷵻�NULL
 */
am_zlg600_handle_t am_zlg600_uart_new_init (am_zlg600_uart_dev_t            *p_dev,
                                            am_uart_handle_t                 uart_handle,
                                            const am_zlg600_uart_dev_info_t *p_uart_info);

/**
 * \brief ��ʼ��ZLG600��ʹ��I2C��֡ͨ��ģʽ������ȡ������ZLG600�ı�׼����handle
 *
 * ��ظ���ʵ��Ӳ��ʹ�ú���ͨ�����ӷ�ʽѡ����ʹ��I2C����ʹ�øú�����ʼ��
 * �Ի��handle��������ʹ��am_zlg600_uart_init()�������handle��
 *
 * \param[in] p_dev        : ָ��ZLG600�豸��ָ��
 * \param[in] i2c_handle   : ��ZLG600������I2C������ʹ�ø�handle����I2Cͨ��
 * \param[in] p_i2c_info   : I2Cͨ��ģʽ�����Ϣ
 *
 * \return ���� ZLG600 �Ĳ�������������ʼ��ʧ�ܣ��򷵻�NULL
 */ 
am_zlg600_handle_t am_zlg600_i2c_old_init (am_zlg600_i2c_dev_t            *p_dev,
                                           am_i2c_handle_t                 i2c_handle,
                                           const am_zlg600_i2c_dev_info_t *p_i2c_info);

/**
 * \brief ��ʼ��ZLG600��ʹ��I2C��֡ͨ��ģʽ������ȡ������ZLG600�ı�׼����handle
 *
 * ��ظ���ʵ��Ӳ��ʹ�ú���ͨ�����ӷ�ʽѡ����ʹ��I2C����ʹ�øú�����ʼ��
 * �Ի��handle��������ʹ��am_zlg600_uart_init()�������handle��
 *
 * \param[in] p_dev        : ָ��ZLG600�豸��ָ��
 * \param[in] i2c_handle   : ��ZLG600������I2C������ʹ�ø�handle����I2Cͨ��
 * \param[in] p_i2c_info   : I2Cͨ��ģʽ�����Ϣ
 *
 * \return ���� ZLG600 �Ĳ�������������ʼ��ʧ�ܣ��򷵻�NULL
 */
am_zlg600_handle_t am_zlg600_i2c_new_init (am_zlg600_i2c_dev_t            *p_dev,
                                           am_i2c_handle_t                 i2c_handle,
                                           const am_zlg600_i2c_dev_info_t *p_i2c_info);

/**
 * \brief ��ZLG600�Ĳ�Ʒ���汾��Ϣ���磺��ZLG600SP/T V1.00��
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] p_info     : ����װ�ػ�ȡ��Ϣ�Ļ���������СӦΪ 20 �ֽ�
 *
 * \retval AM_OK      : ��ȡ��Ϣ�ɹ�
 * \retval -AM_EINVAL : ��ȡ��Ϣʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡ��Ϣʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_info_get (am_zlg600_handle_t handle,
                        uint8_t           *p_info);

/**
 * \brief ����IC���ӿڣ�ִ�гɹ�������IC���ӿڣ�������Ĭ��֧��TypeA��
 *
 * \param[in] handle     : ZLG600�Ĳ������
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_ic_port_config (am_zlg600_handle_t handle);

/**
 * \brief �ر�IC���ӿ�
 *
 * \param[in] handle     : ZLG600�Ĳ������
 *
 * \retval AM_OK      : �رճɹ�
 * \retval -AM_EINVAL : �ر�ʧ�ܣ���������
 * \retval -AM_EIO    : �ر�ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_ic_port_close (am_zlg600_handle_t handle);
                            
/**
 * \name IC���ӿڵ�Э�飨����ģʽ��
 * @{
 */
#define  AM_ZLG600_IC_ISOTYPE_A      0x00    /**< \brief ISO14443-3A */
#define  AM_ZLG600_IC_ISOTYPE_B      0x04    /**< \brief ISO14443-3B */
/** @}*/

/**
 * \brief ����IC���ӿ�Э�飨����ģʽ��TypeA ���� TypeB
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] isotype    : IC���ӿڵ�Э�����ͣ�ʹ�����к� ��
 *                          - #AM_ZLG600_IC_ISOTYPE_A
 *                          - #AM_ZLG600_IC_ISOTYPE_B
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_ic_isotype_set (am_zlg600_handle_t handle,
                              uint8_t            isotype);
                             
/**
 * \name IC���ܳ�����
 * @{
 */

#define  AM_ZLG600_IC_KEY_TYPE_A      0x60    /**< \brief ���� A  */
#define  AM_ZLG600_IC_KEY_TYPE_B      0x61    /**< \brief ���� B  */

/** @}*/

/**
 * \brief װ��IC����Կ
 *
 * ���������Կ������ģ���ڲ���ģ���������Կ����ʧ��ZLG600SP/Tģ�鹲�ܱ���
 * A��Կ16�顢B��Կ16�顣
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] key_type   : ��Կ���ͣ�����ʹ������ֵ��
 *                          - #AM_ZLG600_IC_KEY_TYPE_A
 *                          - #AM_ZLG600_IC_KEY_TYPE_B
 * \param[in] key_sec    : ��Կ��������ţ����ɱ���16����Կ�����ţ�0 ~ 15
 * \param[in] p_key      : ��Կ������
 * \param[in] key_length : ��Կ�ĳ��ȣ�ֻ��Ϊ6��6�ֽ���Կ����16��16�ֽ���Կ��
 *
 * \retval AM_OK      : װ����Կ�ɹ�
 * \retval -AM_EINVAL : װ��ʧ�ܣ���������
 * \retval -AM_EIO    : װ��ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_ic_key_load (am_zlg600_handle_t  handle,
                           uint8_t             key_type,
                           uint8_t             key_sec,
                           uint8_t            *p_key,
                           uint8_t             key_length);

/**
 * \brief ����IC���ӿڵļĴ���ֵ
 *
 * ��������ģ���϶�д��оƬ�ڲ��ļĴ���ֵ��ͨ�����������ʵ�ֺܶ���������
 * ������ɵĹ�����
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] reg_addr   : �Ĵ�����ַ����Χ��0x00 ~ 0x3F
 * \param[in] reg_val    : ���õļĴ���ֵ
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_ic_reg_set (am_zlg600_handle_t handle,
                          uint8_t            reg_addr,
                          uint8_t            reg_val);

/**
 * \brief ��ȡIC���ӿڵļĴ���ֵ
 *
 * ��������������ģ���϶�д��оƬ�ڲ��ļĴ���ֵ��
 * ͨ�����������ʵ�ֺܶ������������ɵĹ�����
 *
 * \param[in]  handle     : ZLG600�Ĳ������
 * \param[in]  reg_addr   : �Ĵ�����ַ����Χ��0x00 ~ 0x3F
 * \param[out] p_val      : ��ȡ�Ĵ���ֵ��ָ��
 *
 * \retval AM_OK      : ��ȡ�ɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_ic_reg_get (am_zlg600_handle_t  handle,
                          uint8_t             reg_addr,
                          uint8_t            *p_val);

/**
 * \brief ���ò�����
 *
 * ������UARTͨ�Ź����иı�ͨ�ŵĲ����ʣ�����������ֵ������
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] baudrate_flag : �����ʱ�־������֧�����еĲ����ʣ�Ӧʹ�ú�
 *                            AM_ZLG600_BAUDRATE_* �������ò�����Ϊ115200��
 *                            ��ʹ�ú� #AM_ZLG600_BAUDRATE_115200
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_baudrate_set (am_zlg600_handle_t handle,
                            uint32_t           baudrate_flag);

/**
 * \name ����������ʽ
 * @{
 */

#define  AM_ZLG600_ANT_TX1_ONLY      1    /**< \brief ��TX1��������         */
#define  AM_ZLG600_ANT_TX2_ONLY      2    /**< \brief ��TX2��������         */
#define  AM_ZLG600_ANT_TX1_AND_TX2   3    /**< \brief TX1��TX2ͬʱ��������  */
#define  AM_ZLG600_ANT_NONE          0    /**< \brief ͬʱ�ر�TX1��TX2      */

/** @}*/
      
/**
 * \brief ��������������ʽ����������򿪡��ر�ĳ��������������
 *
 * \param[in] handle       : ZLG600�Ĳ������
 * \param[in] antmode_flag : ʹ�ú� AM_ZLG600_ANT_*����#AM_ZLG600_ANT_TX1_ONLY
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_ant_mode_set (am_zlg600_handle_t handle,
                            uint8_t            antmode_flag);

/**
 * \brief ����֡��ʽ�������л��¡���֡��ʽ�����óɹ�����粻��ʧ
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] flag       : ֡��ʽ���־����ʹ�����к꣺
 *                           - #AM_ZLG600_FRAME_FMT_NEW
 *                           - #AM_ZLG600_FRAME_FMT_OLD
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 *
 * \note ֡�л��ɹ�����Ҫ���µ���Ŀ��֡��ʽ�ĳ�ʼ��������
 */ 
int am_zlg600_frame_fmt_set (am_zlg600_handle_t handle,
                             uint8_t            flag);

/**
 * \brief �����豸����ģʽ�ʹӻ���ַ
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] mode       : ģ��Ĺ���ģʽ������ʹ�����к�ֵ��
 *                         - #AM_ZLG600_MODE_MASTER      ����ģʽ
 *                         - #AM_ZLG600_MODE_SLAVE       �ӻ�ģʽ ��Ĭ�ϣ�
 *                         - #AM_ZLG600_MODE_AUTO_CHECK  �Զ����ģʽ
 *                         - #AM_ZLG600_MODE_I2C         I2Cģʽ
 *                         - #AM_ZLG600_MODE_UART        UARTģʽ
 *
 * \param[in] new_addr   : ���õ�ZLG600�ӻ���ַ�����һλΪ0����Чֵ0x02 ~ 0xFE
 *
 * \retval AM_OK      : ���óɹ�,���óɹ��󣬺���Ӧ��ʹ���µĵ�ַͨ��
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_mode_addr_set (am_zlg600_handle_t handle,
                             uint8_t            mode,
                             uint8_t            new_addr);
      
/**
 * \brief ��ȡ�豸����ģʽ�ʹӻ���ַ
 *
 * \param[in]  handle     : ZLG600�Ĳ������
 * \param[out] p_mode     : ���ڻ�ȡģ�鹤��ģʽ��ָ�룬��ȡ��ֵ��λ�������£�
 *                          - bit7 ~ 4��0,�ӻ�ģʽ; 1,�Զ���⿨Ƭģʽ������ģʽ��
 *                          - bit3 ~ 0��0,�Զ����ģʽ; 1,I2Cͨ��ģʽ; 2,UARTģʽ 
 * \param[out] p_addr     : ���ڻ�ȡ��ǰ��ZLG600�Ĵӻ���ַ��ָ��
 *
 * \retval AM_OK      : ��ȡ�ɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_mode_addr_get (am_zlg600_handle_t  handle,
                             uint8_t            *p_mode,
                             uint8_t            *p_addr);
                             
/**
 * \brief װ���û���Կ��ģ�������ṩ��2��16�ֽڵĴ洢�ռ����ڱ����û���Կ��
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] key_sec    : ��Կ��������ţ����ɱ���2���û���Կ�����ţ�0 ~ 1
 * \param[in] p_key      : ��Կ����������Կ�ĳ��ȹ̶�Ϊ16�ֽ�
 *
 * \retval AM_OK      : װ����Կ�ɹ�
 * \retval -AM_EINVAL : װ��ʧ�ܣ���������
 * \retval -AM_EIO    : װ��ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_user_key_load (am_zlg600_handle_t handle,
                             uint8_t            key_sec,
                             uint8_t           *p_key);
                              
/**
 * \brief дEEPROM��ģ���ڲ�ӵ��һ��256Byte��EEPROM
 *
 * \param[in] handle      : ZLG600�Ĳ������
 * \param[in] eeprom_addr : EEPROM��Ƭ�ڵ�ַ��0 ~ 255
 * \param[in] p_buf       : д�����ݵĻ�����
 * \param[in] nbytes      : д�����ݵ��ֽ��������247�ֽ�
 *
 * \retval AM_OK      : д�����ݳɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_eeprom_write (am_zlg600_handle_t handle,
                            uint8_t            eeprom_addr,
                            uint8_t           *p_buf,
                            uint8_t            nbytes);

/**
 * \brief ��EEPROM��ģ���ڲ�ӵ��һ��256Byte��EEPROM
 *
 * \param[in]  handle      : ZLG600�Ĳ������
 * \param[in]  eeprom_addr : EEPROM��Ƭ�ڵ�ַ��0 ~ 255
 * \param[out] p_buf       : �������ݵĻ�����
 * \param[in]  nbytes      : �������ݵ��ֽ��������249�ֽ�
 *
 * \retval AM_OK      : ��ȡ���ݳɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_eeprom_read (am_zlg600_handle_t handle,
                           uint8_t            eeprom_addr,
                           uint8_t           *p_buf,
                           uint8_t            nbytes);

/**
 * \name Mifare������ģʽ
 * @{
 */

#define AM_ZLG600_MIFARE_CARD_REQ_IDLE 0x26 /**< \brief IDLEģʽ,������еĿ� */
#define AM_ZLG600_MIFARE_CARD_REQ_ALL  0x52 /**< \brief ALLģʽ,�������еĿ�  */

/** @}*/ 

/**
 * \brief Mifare���������
 *
 *  �ú�����Ϊ�������������ֻҪ����ISO14443A��׼�Ŀ���Ӧ�ܷ�����Ӧ��
 *
 * \param[in] handle      : ZLG600�Ĳ������
 * \param[in] req_mode    : ����ģʽ����ʹ�����к꣺
 *                           - #AM_ZLG600_MIFARE_CARD_REQ_IDLE
 *                           - #AM_ZLG600_MIFARE_CARD_REQ_ALL
 * \param[in] p_atq       : ��ȡ����Ӧ����Ϣ��ATQ����ָ�룬��ֵΪ16λ����ͬ��
 *                          ���ͷ��ص���Ϣ��ͬ,�������ͷ��ص�ATQ���£�
 *
 *            Mifare1 S50    | Mifare1 S70 | Mifare1 Light | Mifare0 UltraLight 
 *       --------------------|-------------|---------------|-------------------
 *              0x0004       |    0x0002   |    0x0010     |      0x0044 
 *       ----------------------------------------------------------------------
 *          Mifare3 DESFire  |   SHC1101   |    SHC1102    |      11RF32
 *       --------------------|-------------|---------------|-------------------
 *               0x0344      |    0x0004   |    0x3300     |      0x0004
 *
 * \retval AM_OK      : ����ɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 *
 * \note ���������ߺ󣬴���Ƶ���л�ȡ�������Ӷ��õ縴λ����λ�󿨴���IDLEģʽ��
 * ����������ģʽ����һ������ʱ����ʱ�Ŀ�������Ӧ������ĳһ�ſ��ɹ������˹���
 * ������Halt�����DeSelect������������Haltģʽ����ʱ�Ŀ�ֻ��ӦALL��0x52��
 * ģʽ�����󣬳��ǽ����뿪���߸�Ӧ�����ٽ��롣
 */ 
int am_zlg600_mifare_card_request (am_zlg600_handle_t handle,
                                   uint8_t            req_mode,
                                   uint16_t          *p_atq);

/**
 * \name Mifare������ײ�ȼ�
 * @{
 */
#define AM_ZLG600_MIFARE_CARD_ANTICOLL_1  0x93  /**< \brief ��һ������ײ  */
#define AM_ZLG600_MIFARE_CARD_ANTICOLL_2  0x95  /**< \brief �ڶ�������ײ  */
#define AM_ZLG600_MIFARE_CARD_ANTICOLL_3  0x97  /**< \brief ����������ײ  */
/** @}*/ 

/**
 * \brief Mifare���ķ���ײ����
 *
 *  ��Ҫ�ɹ�ִ��һ�������������������ɹ������ܽ��з���ײ���������򷵻ش���
 *
 * \param[in] handle         : ZLG600�Ĳ������
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_1
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_2
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_3
 *
 * \param[in] know_uid : ��֪�Ŀ����к�
 * \param[in] nbit_cnt : λ������������֪�����к�uid��λ������ֵС��32��
 *                       - ��nbit_cntֵΪ0,�����û����֪���кţ����кŵ�����λ
 *                         ��Ҫ�ӱ�������á�
 *                       - ��nbit_cnt��Ϊ0�������к�������֪�����кŵ�ֵ����ʾ
 *                         ���кŵ�ǰnbit_cntλΪ��֪���к�����ʾǰnbit_cntλ��
 *                         ֵ������λ��Ҫ��������á�
 * \param[in] *p_uid   : ����ײ���ȡ���Ŀ����к�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note  ����ISO14443A��׼�������кŶ���ȫ��Ψһ�ģ���������Ψһ�ԣ�����ʵ�ַ�
 * ��ײ���㷨�߼������������ſ�ͬʱ�����߸�Ӧ��������������ܹ��ҵ�һ�����кŽ�
 * ��Ŀ���������
 */ 
int am_zlg600_mifare_card_anticoll (am_zlg600_handle_t handle,
                                    uint8_t            anticoll_level,
                                    uint32_t           know_uid,
                                    uint8_t            nbit_cnt,
                                    uint32_t          *p_uid);
                       
/**
 * \brief Mifare����ѡ�����
 *
 *  ��Ҫ�ɹ�ִ��һ�η���ײ��������سɹ������ܽ��п�ѡ����������򷵻ش���
 *
 * \param[in] handle         : ZLG600�Ĳ������
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_1
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_2
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_3
 * \param[in] uid   : ǰһ������ײ������ȡ��UID
 * \param[in] p_sak : ���ص���Ϣ����bit2Ϊ1�������UID������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note  �������кų��������֣�4�ֽڡ�7�ֽں�10�ֽڡ� 4�ֽڵ�ֻҪ��һ��ѡ�񼴿�
 * �õ����������кţ���Mifare1 S50/S70�ȣ�7�ֽڵ�Ҫ�ö���ѡ����ܵõ�����������
 * �ţ�ǰһ�����õ������кŵ�����ֽ�Ϊ������־0x88�������к���ֻ�к�3�ֽڿ��ã�
 * ��һ��ѡ���ܵõ�4�ֽ����кţ����߰�˳�����Ӽ�Ϊ7�ֽ����кţ���UltraLight
 * ��DesFire�ȣ�10�ֽڵ��Դ����ƣ�������δ���ִ��࿨��
 */ 
int am_zlg600_mifare_card_select (am_zlg600_handle_t handle,
                                  uint8_t            anticoll_level,
                                  uint32_t           uid,
                                  uint8_t           *p_sak);

/**
 * \brief Mifare���Ĺ��������ʹ��ѡ��Ŀ�����HALT״̬
 *
 *  ��HALT״̬�£���������Ӧ������������IDLEģʽ�����󣬳��ǽ�����λ���뿪���߸�
 *  Ӧ�����ٽ��롣��������Ӧ������������ALL����
 *
 * \param[in] handle         : ZLG600�Ĳ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_mifare_card_halt (am_zlg600_handle_t handle);

                               
/**
 * \brief Mifare��E2��Կ��֤
 *
 *     ��ģ���ڲ��Ѵ������Կ�뿨����Կ������֤��ʹ�ø�����ǰӦ���á�װ��IC����Կ��
 * ��������Կ�ɹ�����ģ���ڡ����⣬��Ҫ��֤�Ŀ��������Ų�����ģ������Կ������ȡ�
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] key_type   : ��Կ���ͣ�����ʹ������ֵ��
 *                          - #AM_ZLG600_IC_KEY_TYPE_A
 *                          - #AM_ZLG600_IC_KEY_TYPE_B
 * \param[in] p_uid      : �����кţ�4�ֽ�
 * \param[in] key_sec    : ��Կ���ţ�0 ~ 7
 * \param[in] nblock     : ��Ҫ��֤�Ŀ���ţ�ȡֵ��Χ�뿨�����йأ�
 *                         - S50��0 ~ 63
 *                         - S70��0 ~ 255
 *                         - PLUS CPU 2K��0 ~ 127
 *                         - PLUS CPU 4K��0 ~ 255
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 * 
 * \note PLUS CPUϵ�еĿ��Ŀ�����4�ֽں�7�ֽ�֮�֣�����7�ֽڿ��ŵĿ���
 *       ֻ��Ҫ�����ŵĸ�4�ֽڣ��ȼ�2����ײ�õ��Ŀ��ţ���Ϊ��֤�Ŀ��ż��ɡ�
 */
int am_zlg600_mifare_card_e2_authent (am_zlg600_handle_t  handle,
                                      uint8_t             key_type,
                                      uint8_t            *p_uid,
                                      uint8_t             key_sec,
                                      uint8_t             nblock);

/**
 * \brief Mifare��ֱ����Կ��֤
 *
 *    �����������Ϊ�������ݣ�����ڴ�֮ǰ�����á�װ��IC����Կ���������ǰ��
 * ΪPLUS CPU���ĵȼ�2��ȼ�3�������������ֻ��6�ֽڣ���ģ���Զ������������
 * ����2�Σ�ȡǰ16�ֽ���Ϊ��ǰ��֤��Կ��
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] key_type   : ��Կ���ͣ�����ʹ������ֵ��
 *                          - #AM_ZLG600_IC_KEY_TYPE_A
 *                          - #AM_ZLG600_IC_KEY_TYPE_B
 * \param[in] p_uid      : �����кţ�4�ֽ�
 * \param[in] p_key      : ��Կ������
 * \param[in] key_len    : ��Կ�ĳ��ȣ�ֻ��Ϊ6��6�ֽ���Կ����16��16�ֽ���Կ��
 * \param[in] nblock     : ��Ҫ��֤�Ŀ���ţ�ȡֵ��Χ�뿨�����йأ�
 *                         - S50��0 ~ 63
 *                         - S70��0 ~ 255
 *                         - PLUS CPU 2K��0 ~ 127
 *                         - PLUS CPU 4K��0 ~ 255
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 * 
 * \note PLUS CPUϵ�еĿ��Ŀ�����4�ֽں�7�ֽ�֮�֣�����7�ֽڿ��ŵĿ���
 *       ֻ��Ҫ�����ŵĸ�4�ֽڣ��ȼ�2����ײ�õ��Ŀ��ţ���Ϊ��֤�Ŀ��ż��ɡ�
 */
int am_zlg600_mifare_card_direct_authent (am_zlg600_handle_t  handle,
                                          uint8_t             key_type,
                                          uint8_t            *p_uid,
                                          uint8_t            *p_key,
                                          uint8_t             key_len,
                                          uint8_t             nblock);
          
/**
 * \brief Mifare�����ݶ�ȡ
 *
 *     ����֤�ɹ�֮�󣬲��ܶ���Ӧ�Ŀ����ݣ�����֤�Ŀ�������ű�����ͬһ�������ڣ�
 * Mifare1���ӿ��0��ʼ��˳��ÿ4����1����������Ҫ��һ�ſ��еĶ���������в�������
 * ��ĳһ����������Ϻ󣬱������һ����������ܶ���һ������ֱ�ӽ�����֤�������
 * ���������ʼ����������PLUS CPU��������һ������������Կ�͵�ǰ��������Կ��ͬ��
 * ����Ҫ�ٴ���֤��Կ��ֱ�Ӷ����ɡ�
 *
 * \param[in]  handle     : ZLG600�Ĳ������
 * \param[in]  nblock     : ��ȡ���ݵĿ��
 *                          - S50��0 ~ 63
 *                          - S70��0 ~ 255
 *                          - PLUS CPU 2K��0 ~ 127
 *                          - PLUS CPU 4K��0 ~ 255
 * \param[out] p_buf      : ��Ŷ�ȡ�����ݣ���СΪ 16
 *
 * \retval AM_OK      : ��ȡ�ɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_read (am_zlg600_handle_t  handle,
                                uint8_t             nblock,
                                uint8_t            *p_buf);

/**
 * \brief Mifare��д����,д֮ǰ����ɹ�������Կ��֤��
 *
 *      �Կ���ĳһ�������֤�ɹ��󣬼��ɶ�ͬһ�����ĸ�������д������ֻҪ��������������
 *  ���а���λ������β������飬���Ǹ��������Ψһ����������PLUS CPU���ȼ�2��3��AES��
 *  Կ����������λ���޸���Կ��
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] nblock     : ��ȡ���ݵĿ��
 *                         - S50��0 ~ 63
 *                         - S70��0 ~ 255
 *                         - PLUS CPU 2K��0 ~ 127
 *                         - PLUS CPU 4K��0 ~ 255
 * \param[in] p_buf      : д�����ݻ���������С����Ϊ 16
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_write (am_zlg600_handle_t  handle,
                                 uint8_t             nblock,
                                 uint8_t            *p_buf);
                                
/**
 * \brief Mifare��д����
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] nblock     : ��ȡ���ݵĿ��, 1 ~ 15
 * \param[in] p_buf      : д�����ݻ���������С����Ϊ 4
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 *
 * ������ֻ��UltraLight����Ч����UltraLight�����ж�������Mifare1��һ����
 */
int am_zlg600_ultralight_card_write (am_zlg600_handle_t  handle,
                                     uint8_t             nblock,
                                     uint8_t            *p_buf);

/**
 * \name Mifare��ֵ����ģʽ
 * @{
 */

#define AM_ZLG600_MIFARE_CARD_VALUE_ADD  0xC1  /**< \brief ��  */
#define AM_ZLG600_MIFARE_CARD_VALUE_SUB  0xC0  /**< \brief ��  */

/** @}*/

/**
 * \brief Mifareֵ��������Mifare����ֵ����мӼ�����
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] mode       : ֵ������ģʽ�������Ǽӻ����ʹ�����к꣺
 *                          - AM_ZLG600_MIFARE_CARD_VALUE_ADD
 *                          - AM_ZLG600_MIFARE_CARD_VALUE_SUB
 * \param[in] nblock     : ����ֵ�����Ŀ��
 *                           - S50��0 ~ 63
 *                            - S70��0 ~ 255
 *                            - PLUS CPU 2K��0 ~ 127
 *                            - PLUS CPU 4K��0 ~ 255
 * \param[in] ntransblk  : �����ţ�������ֵ��ŵĿ��
 * \param[in] value      : 4�ֽ��з�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 *
 * \note Ҫ���д�������������ݱ���Ҫ��ֵ��ĸ�ʽ���ɲο�NXP������ĵ���������
 * ���봫������ͬ���򽫲�����Ľ��д��ԭ���Ŀ��ڣ���������봫���Ų���ͬ��
 * �򽫲�����Ľ��д�봫����ڣ����������ڵ����ݱ����ǣ�ԭ���ڵ�ֵ���䡣
 * ���ڵȼ�2��PLUS CPU����֧��ֵ��������ȼ�1��3֧�֡�
 */
int am_zlg600_mifare_card_val_operate (am_zlg600_handle_t  handle,
                                       uint8_t             mode,
                                       uint8_t             nblock,
                                       uint8_t             ntransblk,
                                       int32_t             value);

/**
 * \brief Mifare����λ��ͨ�����ز��źŹر�ָ����ʱ�䣬�ٿ�����ʵ�ֿ�Ƭ��λ��
 * 
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] time_ms    : �رյ�ʱ�䣨��λ:ms����0Ϊһֱ�ر�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note �ú����������źŹر������룬��һֱ�رգ���ȵ�ִ��һ����������ʱ�򿪡�
 */
int am_zlg600_mifare_card_reset (am_zlg600_handle_t  handle,
                                 uint8_t             time_ms);

/**
 * \brief Mifare������ú������ڼ��Ƭ�������󡢷���ײ��ѡ�������������ϡ�
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] req_mode   : ����ģʽ����ʹ�����к꣺
 *                           - #AM_ZLG600_MIFARE_CARD_REQ_IDLE
 *                           - #AM_ZLG600_MIFARE_CARD_REQ_ALL
 * \param[in] p_atq      : ����Ӧ��
 * \param[in] p_saq      : ���һ��ѡ��Ӧ��SAK
 * \param[in] p_len      : ���кŵ�ʵ�ʳ��ȣ�4�ֽڡ�7�ֽڻ�10�ֽ�
 * \param[in] p_uid      : ���кŻ�����������Ӧ�������кų��ȱ���һ�£�
 *                         �粻ȷ����������ʹ����󳤶�10��
 * \param[in]  uid_len   �� p_uid ��ָ�������ĳ���
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_active (am_zlg600_handle_t  handle,
                                  uint8_t             req_mode,
                                  uint16_t           *p_atq,
                                  uint8_t            *p_saq,
                                  uint8_t            *p_len,
                                  uint8_t            *p_uid,
                                  uint8_t             uid_len);

/**
 * \brief Mifareֵ����������ֵ���ֵ
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] nblock     : ��ȡ���ݵ�ֵ���ַ
 * \param[in] value      : ���õ�ֵ
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_val_set (am_zlg600_handle_t  handle,
                                   uint8_t             nblock,
                                   int32_t             value);
               
/**
 * \brief Mifareֵ��������ȡֵ���ֵ
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] nblock     : ��ȡ���ݵ�ֵ���ַ
 * \param[in] p_value    : ��ȡֵ��ָ��
 *
 * \retval AM_OK      : ��ȡ�ɹ�
 * \retval -AM_EINVAL : ��ȡʧ�ܣ���������
 * \retval -AM_EIO    : ��ȡʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_val_get (am_zlg600_handle_t  handle,
                                   uint8_t             nblock,
                                   int32_t            *p_value);

/**
 * \brief �����
 *
 *     �ú�������ģ����չ���ܣ�����ģ����Ƭ�������ⳤ����ϵ����ݴ����������
 * NXP���Ƴ���NTAG213F������Ultralight Cϵ�п�Ƭ�����Ǹÿ�Ƭ�����������������
 * ��д��Կ�������ܡ��������Կ��֤��������ô��������亯����ʵ�֡�
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] p_tx_buf   : �������ݵĻ�����
 * \param[in] tx_nbytes  : �����ֽ���
 * \param[in] p_rx_buf   : �������ݵĻ�����
 * \param[in] rx_nbytes  : �����ֽ���
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_cmd_trans (am_zlg600_handle_t  handle,
                                     uint8_t            *p_tx_buf,
                                     uint8_t             tx_nbytes,
                                     uint8_t            *p_rx_buf,
                                     uint8_t             rx_nbytes);

/**
 * \brief ���ݽ���
 *
 * �������ö�д���뿨Ƭ�����ݽ�����ͨ���ú�������ʵ�ֶ�д���������й��ܡ�
 *
 * \param[in]  handle     : ZLG600�Ĳ������
 * \param[in]  p_data_buf : ��Ҫ�������͵�����
 * \param[in]  len        : �������ݵĳ���
 * \param[in]  wtxm_crc   : b7~b2,wtxm��b1,RFU(0); b0,0,CRC��ֹ�ܣ�1,CRCʹ�ܡ�
 * \param[in]  fwi        : ��ʱ�ȴ�ʱ�����, ��ʱʱ��=����0x01 << fwi*302us��
 * \param[out] p_rx_buf   : ���ݽ�����Ӧ֡��Ϣ
 * \param[in]  buf_size   : ���ջ�Ӧ��Ϣ�Ļ�������С
 * \param[in]  p_real_len : ���ڻ�ȡʵ�ʽ��յ���Ϣ���ȣ������������СС��ʵ����
 *                         Ϣ���ȣ�����ಿ�ֽ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_data_exchange (am_zlg600_handle_t  handle,
                                         uint8_t            *p_data_buf,
                                         uint8_t             len,
                                         uint8_t             wtxm_crc,
                                         uint8_t             fwi,
                                         uint8_t            *p_rx_buf,
                                         uint8_t             buf_size,
                                         uint16_t           *p_real_len);

/**
 * \name Mifare�����ģʽ
 * @{
 */

/** \brief ִ����һ���Զ�����ִ��Halt����  */
#define AM_ZLG600_MIFARE_CARD_AD_HALT  0x08

/** @}*/

/**
 * \name Mifare����������ģʽ
 * @{
 */

#define AM_ZLG600_MIFARE_CARD_TX_IN_TURN   0x00 /**< \brief TX1��TX2�������� */
#define AM_ZLG600_MIFARE_CARD_TX_TX1       0x01 /**< \brief ��TX1���� */
#define AM_ZLG600_MIFARE_CARD_TX_TX2       0x02 /**< \brief ��TX2���� */
#define AM_ZLG600_MIFARE_CARD_TX_ALL       0x03 /**< \brief TX1��TX2ͬʱ���� */

/** @}*/

/**
 * \name Mifare����Կ��֤ģʽ
 * @{
 */

#define AM_ZLG600_MIFARE_CARD_AUTH_E2      0x45 /**< \brief E2��Կ��֤(E) */
#define AM_ZLG600_MIFARE_CARD_AUTH_DIRECT  0x46 /**< \brief ֱ����Կ��֤(F) */
#define AM_ZLG600_MIFARE_CARD_AUTH_NO      0x00 /**< \brief ����֤ */

/** @}*/

/**
 * \brief ����Mifare���Զ����
 * \note ���Զ�����ڼ䣬�����������κγ����Զ����������ģ������ݳ���С��3
 *       ��������˳��Զ����ģʽ��������am_zlg600_mifare_card_active()
 *       ����ڴ��ڼ䣬ģ�齫���������ݳ��ȴ���2������
 *
 * \param[in] handle    : ZLG600�Ĳ������
 * \param[in] p_adinfo  : �Զ������Ϣ
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_auto_detect_start (am_zlg600_handle_t                  handle,
                                             const am_zlg600_auto_detect_info_t *p_adinfo);

/**
 * \brief �ر�Mifare���Զ����
 *
 * \param[in] handle  : ZLG600�Ĳ������
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_auto_detect_stop (am_zlg600_handle_t handle);

/**
 * \brief Mifare���Զ����ص���������
 *
 * \param[in] handle       : ZLG600�Ĳ������
 * \param[in] pfn_callback : �ص�����ָ��
 * \param[in] p_arg        : �ص�������ڲ���
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_auto_detect_cb_set (am_zlg600_handle_t  handle,
                                              am_pfnvoid_t        pfn_callback,
                                              void               *p_arg);

/**
 * \name Mifare�����Զ�����ʶ
 * @{
 */

#define AM_ZLG600_MIFARE_CARD_AD_READ_CANCEL    0x00  /**< \brief ȡ����� */
#define AM_ZLG600_MIFARE_CARD_AD_READ_CONTINUE  0x01  /**< \brief ������� */

/** @} */

/**
 * \brief Mifare��Ƭ��Ϣ
 */
typedef struct am_zlg600_mifare_card_info {
    uint8_t     tx_mode;        /**< \brief ��������ģʽ */
    uint8_t     uid_len;        /**< \brief UID(��Ψһ���к�)���ȣ�4��7��10 */
    uint8_t     uid[10];        /**< \brief UID */
    uint8_t     card_data[16];  /**< \brief ��Ƭ���� */
} am_zlg600_mifare_card_info_t;

/**
 * \brief Mifare����ȡ�Զ������������
 *
 * \param[in]  handle      : ZLG600�Ĳ������
 * \param[out] p_card_info : ָ���ſ�Ƭ���ݵ�ָ��
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_mifare_card_auto_detect_read (am_zlg600_handle_t            handle,
                                            am_zlg600_mifare_card_info_t *p_card_info);

/**
 * \name IC����λ��Ĳ�����
 *
 *      ע�⣬�ò����ʲ���������ZLG600��ͨ�Ų����ʣ�����ָZLG600ģ����Ӵ�ʽIC
 *  ����ͨ�Ų����ʡ�
 *
 * @{
 */
#define  AM_ZLG600_CICC_RST_BAUDRATE_9600   0x11  /**< \brief ������ 9600   */
#define  AM_ZLG600_CICC_RST_BAUDRATE_38400  0x13  /**< \brief ������ 38400  */

/** @}*/

/**
 * \brief �Ӵ�ʽIC����λ���Զ�����PPS��
 *
 *     �ú������临λ��ִ�гɹ�����Զ�����IC���ĸ�λ��Ϣ��ִ��PPS���Ȼ����
 * ѡ��am_zlg600_cicc_tpdu()����ʹ�õĴ���Э�飨T = 0 ��T = 1����
 * 
 * \param[in]  handle        : ZLG600�Ĳ������
 * \param[in]  baudrate_flag : IC����λ��Ĳ����ʣ�ʹ�����к꣺
 *                             - AM_ZLG600_CICC_RST_BAUDRATE_9600
 *                             - AM_ZLG600_CICC_RST_BAUDRATE_38400
 * \param[out] p_rx_buf      : ��Ÿ�λ��Ϣ�Ļ�����
 * \param[in]  rx_bufsize    : �������ĳ���
 * \param[out] p_rx_len      : ��ȡ��λ��Ϣ���ȵ�ָ�룬������ջ������ĳ���С��
 *                            ʵ�ʳ��ȣ�����ಿ�ֶ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_cicc_reset (am_zlg600_handle_t  handle,
                          uint8_t             baudrate_flag,
                          uint8_t            *p_rx_buf,
                          uint8_t             rx_bufsize,
                          uint16_t           *p_rx_len);

/**
 * \brief �Ӵ�ʽIC������Э��
 *
 *     ��������ݽӴ�ʽIC���ĸ�λ��Ϣ���Զ�ѡ��T = 0��T = 1����Э�飬��������
 * ����Ҫʹ���߸�Ԥ�����������ڴ���APDU��������
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] p_tx_buf      : ���ͻ�����
 * \param[in] tx_bufsize    : ���ͻ������ĳ��ȣ� 1 ~ 272
 * \param[in] p_rx_buf      : ���ջ�����
 * \param[in] rx_bufsize    : ���ջ������ĳ���
 * \param[in] p_rx_len      : ���ڻ�ȡʵ�ʽ�����Ϣ���ȵ�ָ�룬������ջ�����
 *                            �ĳ���С��ʵ�ʳ��ȣ�����ಿ�ֶ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_cicc_tpdu (am_zlg600_handle_t  handle,
                         uint8_t            *p_tx_buf,
                         uint16_t            tx_bufsize,
                         uint8_t            *p_rx_buf,
                         uint8_t             rx_bufsize,
                         uint16_t           *p_rx_len);
                        
/**
 * \brief �Ӵ�ʽIC���临λ
 *
 *     �ú������临λ��ִ���˽Ӵ�ʽIC���ϵ�ʱ��ִ�гɹ�����Զ�����IC���ĸ�λ
 * ��Ϣ��ѡ��am_zlg600_cicc_tpdu()����ʹ�õĴ���Э�飨T = 0 ��T = 1�����ú���û
 * ���Զ�ִ��PPS�����Ҫ�û����ݸ�λ��Ϣ���ж��Ƿ�ʹ��am_zlg600_cicc_pps()��
 * �޸�Э��Ͳ�����
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] baudrate_flag : IC����λ��Ĳ����ʣ�ʹ�����к꣺
 *                             - AM_ZLG600_CICC_RST_BAUDRATE_9600
 *                             - AM_ZLG600_CICC_RST_BAUDRATE_38400
 * \param[in] p_rx_buf      : ��Ÿ�λ��Ϣ�Ļ�����
 * \param[in] rx_bufsize    : �������ĳ���
 * \param[in] p_rx_len      : ��ȡ��λ��Ϣ���ȵ�ָ�룬������ջ������ĳ���С��
 *                            ʵ�ʳ��ȣ�����ಿ�ֶ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_cicc_coldreset (am_zlg600_handle_t  handle,
                              uint8_t             baudrate_flag,
                              uint8_t            *p_rx_buf,
                              uint8_t             rx_bufsize,
                              uint16_t           *p_rx_len);
                        
/**
 * \brief �Ӵ�ʽIC���ȸ�λ
 *
 *    �ú������ȸ�λ��û��ִ���˽Ӵ�ʽIC���ϵ�ʱ��ִ�гɹ�����Զ�����IC����
 * ��λ��Ϣ��ѡ��am_zlg600_cicc_tpdu()����ʹ�õĴ���Э�飨T = 0 ��T = 1����
 * �ȸ�λ���临λΨһ��������û��ִ��IC���ϵ��������Ҫ�û����ݸ�λ��Ϣ���ж�
 * �Ƿ�ʹ��am_zlg600_cicc_pps()���޸�Э��Ͳ������ú���������IC��ʱ�Ӻ͵�Դ��
 * ��Ч������²���ִ�С�
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] baudrate_flag : IC����λ��Ĳ����ʣ�ʹ�����к꣺
 *                             - AM_ZLG600_CICC_RST_BAUDRATE_9600
 *                             - AM_ZLG600_CICC_RST_BAUDRATE_38400
 * \param[in] p_rx_buf      : ��Ÿ�λ��Ϣ�Ļ�����
 * \param[in] rx_bufsize    : �������ĳ���
 * \param[in] p_rx_len      : ��ȡ��λ��Ϣ���ȵ�ָ�룬������ջ������ĳ���С��
 *                            ʵ�ʳ��ȣ�����ಿ�ֶ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_cicc_warmreset (am_zlg600_handle_t  handle,
                              uint8_t             baudrate_flag,
                              uint8_t            *p_rx_buf,
                              uint8_t             rx_bufsize,
                              uint16_t           *p_rx_len);

/**
 * \brief �Ӵ�ʽIC��ͣ��رսӴ�ʽIC���ĵ�Դ��ʱ��
 *
 * \param[in] handle        : ZLG600�Ĳ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_cicc_deactive (am_zlg600_handle_t  handle);

/**
 * \brief �Ӵ�ʽIC��Э��Ͳ���ѡ��
 *
 *     �ú������临λ���ȸ�λ֮���ұ�������ִ�У�Э��ģʽ����Ҫִ�У�ר��ģʽ
 * ����Ҫִ�У������ԽӴ�ʽIC�����˽⣬����ʹ��am_zlg600_cicc_reset()���и�λ��
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] p_pps      : PPS��������������Сһ��Ϊ4�ֽ�
 *                         - PPS[0] bit 3 ~ bit0 �� bit7����
 *                         - PPS[0] bit 4��1 �� PPS1���ڣ�0 �� PPS1������
 *                         - PPS[0] bit 5��1 �� PPS2���ڣ�0 �� PPS2������
 *                         - PPS[0] bit 6��1 �� PPS3���ڣ�0 �� PPS3������
                           - PPS[1] ��F/D
                           - PPS[2] ��N
                           - PPS[3] ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_cicc_pps (am_zlg600_handle_t  handle,
                        uint8_t            *p_pps);

/**
 * \brief �Ӵ�ʽIC������Э�飨T = 0��
 *
 *     ����������T = 0����Э�顣���Ӵ�ʽIC���Ĵ���Э��ΪT = 0���ú�����ͬ��
 * am_zlg600_cicc_tpdu()��
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] p_tx_buf      : ���ͻ�����
 * \param[in] tx_bufsize    : ���ͻ������ĳ��ȣ� 1 ~ 272
 * \param[in] p_rx_buf      : ���ջ�����
 * \param[in] rx_bufsize    : ���ջ������ĳ���
 * \param[in] p_rx_len      : ���ڻ�ȡʵ�ʽ�����Ϣ���ȵ�ָ�룬������ջ�����
 *                            �ĳ���С��ʵ�ʳ��ȣ�����ಿ�ֶ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_cicc_tpdu_tp0 (am_zlg600_handle_t  handle,
                             uint8_t            *p_tx_buf,
                             uint16_t            tx_bufsize,
                             uint8_t            *p_rx_buf,
                             uint8_t             rx_bufsize,
                             uint16_t           *p_rx_len);

/**
 * \brief �Ӵ�ʽIC������Э�飨T = 1��
 *
 *     ����������T = 1����Э�顣���Ӵ�ʽIC���Ĵ���Э��ΪT = 1���ú�����ͬ��
 * am_zlg600_cicc_tpdu()��
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] p_tx_buf      : ���ͻ�����
 * \param[in] tx_bufsize    : ���ͻ������ĳ��ȣ� 1 ~ 272
 * \param[in] p_rx_buf      : ���ջ�����
 * \param[in] rx_bufsize    : ���ջ������ĳ���
 * \param[in] p_rx_len      : ���ڻ�ȡʵ�ʽ�����Ϣ���ȵ�ָ�룬������ջ�����
 *                            �ĳ���С��ʵ�ʳ��ȣ�����ಿ�ֶ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_cicc_tpdu_tp1 (am_zlg600_handle_t  handle,
                             uint8_t            *p_tx_buf,
                             uint16_t            tx_bufsize,
                             uint8_t            *p_rx_buf,
                             uint8_t             rx_bufsize,
                             uint16_t           *p_rx_len);

/**
 * \name PICCA������ģʽ
 * @{
 */
#define AM_ZLG600_PICCA_REQ_IDLE 0x26 /**< \brief IDLEģʽ,������еĿ� */
#define AM_ZLG600_PICCA_REQ_ALL  0x52 /**< \brief ALLģʽ,�������еĿ�  */
/** @}*/ 

/**
 * \brief PICCA���������
 *
 *  �ú�����Ϊ�������������ֻҪ����ISO14443A��׼�Ŀ���Ӧ�ܷ�����Ӧ��
 *
 * \param[in] handle      : ZLG600�Ĳ������
 * \param[in] req_mode    : ����ģʽ����ʹ�����к꣺
 *                           - #AM_ZLG600_PICCA_REQ_IDLE
 *                           - #AM_ZLG600_PICCA_REQ_ALL
 * \param[in] p_atq       : ��ȡ����Ӧ����Ϣ��ATQ����ָ�룬��ֵΪ16λ����ͬ��
 *                          ���ͷ��ص���Ϣ��ͬ,�������ͷ��ص�ATQ���£�
 *
 *            Mifare1 S50    | Mifare1 S70 | Mifare1 Light | Mifare0 UltraLight 
 *       --------------------|-------------|---------------|-------------------
 *              0x0004       |    0x0002   |    0x0010     |      0x0044 
 *       ----------------------------------------------------------------------
 *          Mifare3 DESFire  |   SHC1101   |    SHC1102    |      11RF32
 *       --------------------|-------------|---------------|-------------------
 *               0x0344      |    0x0004   |    0x3300     |      0x0004
 *
 * \retval AM_OK      : ����ɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 *
 * \note ���������ߺ󣬴���Ƶ���л�ȡ�������Ӷ��õ縴λ����λ�󿨴���IDLEģʽ��
 * ����������ģʽ����һ������ʱ����ʱ�Ŀ�������Ӧ������ĳһ�ſ��ɹ������˹���
 * ������Halt�����DeSelect������������Haltģʽ����ʱ�Ŀ�ֻ��ӦALL��0x52��
 * ģʽ�����󣬳��ǽ����뿪���߸�Ӧ�����ٽ��롣
 */ 
int am_zlg600_picca_request (am_zlg600_handle_t handle,
                             uint8_t            req_mode,
                             uint16_t          *p_atq);

/**
 * \name PICCA������ײ�ȼ�
 * @{
 */
#define AM_ZLG600_PICCA_ANTICOLL_1  0x93  /**< \brief ��һ������ײ  */
#define AM_ZLG600_PICCA_ANTICOLL_2  0x95  /**< \brief �ڶ�������ײ  */
#define AM_ZLG600_PICCA_ANTICOLL_3  0x97  /**< \brief ����������ײ  */
/** @}*/ 

/**
 * \brief PICCA���ķ���ײ����
 *
 *  ��Ҫ�ɹ�ִ��һ�������������������ɹ������ܽ��з���ײ���������򷵻ش���
 *
 * \param[in] handle         : ZLG600�Ĳ������
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_1
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_2
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_3
 *
 * \param[in] know_uid : ��֪�Ŀ����к�
 * \param[in] nbit_cnt : λ������������֪�����к�uid��λ������ֵС��32��
 *                       - ��nbit_cntֵΪ0,�����û����֪���кţ����кŵ�����λ
 *                         ��Ҫ�ӱ�������á�
 *                       - ��nbit_cnt��Ϊ0�������к�������֪�����кŵ�ֵ����ʾ
 *                         ���кŵ�ǰnbit_cntλΪ��֪���к�����ʾǰnbit_cntλ��
 *                         ֵ������λ��Ҫ��������á�
 * \param[in] *p_uid   : ����ײ���ȡ���Ŀ����к�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note  ����ISO14443A��׼�������кŶ���ȫ��Ψһ�ģ���������Ψһ�ԣ�����ʵ�ַ�
 * ��ײ���㷨�߼������������ſ�ͬʱ�����߸�Ӧ��������������ܹ��ҵ�һ�����кŽ�
 * ��Ŀ���������
 */ 
int am_zlg600_picca_anticoll (am_zlg600_handle_t handle,
                              uint8_t            anticoll_level,
                              uint32_t           know_uid,
                              uint8_t            nbit_cnt,
                              uint32_t          *p_uid);
                       
/**
 * \brief PICC A����ѡ�����
 *
 *  ��Ҫ�ɹ�ִ��һ�η���ײ��������سɹ������ܽ��п�ѡ����������򷵻ش���
 *
 * \param[in] handle         : ZLG600�Ĳ������
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_1
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_2
 *                             - #AM_ZLG600_MIFARE_CARD_ANTICOLL_3
 * \param[in] uid   : ǰһ������ײ������ȡ��UID
 * \param[in] p_sak : ���ص���Ϣ����bit2Ϊ1�������UID������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note  �������кų��������֣�4�ֽڡ�7�ֽں�10�ֽڡ� 4�ֽڵ�ֻҪ��һ��ѡ�񼴿�
 * �õ����������кţ���Mifare1 S50/S70�ȣ�7�ֽڵ�Ҫ�ö���ѡ����ܵõ�����������
 * �ţ�ǰһ�����õ������кŵ�����ֽ�Ϊ������־0x88�������к���ֻ�к�3�ֽڿ��ã�
 * ��һ��ѡ���ܵõ�4�ֽ����кţ����߰�˳�����Ӽ�Ϊ7�ֽ����кţ���UltraLight
 * ��DesFire�ȣ�10�ֽڵ��Դ����ƣ�������δ���ִ��࿨��
 */ 
int am_zlg600_picca_select (am_zlg600_handle_t handle,
                            uint8_t            anticoll_level,
                            uint32_t           uid,
                            uint8_t           *p_sak);

/**
 * \brief PICCA���Ĺ��������ʹ��ѡ��Ŀ�����HALT״̬
 *
 *  ��HALT״̬�£���������Ӧ������������IDLEģʽ�����󣬳��ǽ�����λ���뿪���߸�
 *  Ӧ�����ٽ��롣��������Ӧ������������ALL����
 *
 * \param[in] handle         : ZLG600�Ĳ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_picca_halt (am_zlg600_handle_t handle);

/**
 * \brief PICC TypeA��RATS��request for answer to select��
 *
 *     RATS��request for answer to select����ISO14443-4Э������ģ�鷢��RATS��
 * ��Ƭ����ATS��answer to select����ΪRATS��Ӧ����ִ�и�����ǰ�������Ƚ���һ��
 * ��ѡ���������ִ�й�һ��RATS��������ٴ�ִ��RATS��������Ƚ�����
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] cid        : ����ʶ����card IDentifier��ȡֵ��Χ0x00��0x0E��
 * \param[in] p_ats_buf  : ���ڽ��ջ�Ӧ����Ϣ����ͬ�����ֽ������в�ͬ
 * \param[in] bufsize    : ��������С
 * \param[in] p_rx_len   : ���ڻ�ȡʵ�ʽ��յ���Ϣ���ȣ������������СС��ʵ����
 *                         Ϣ���ȣ�����ಿ�ֽ�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_picca_rats (am_zlg600_handle_t  handle,
                          uint8_t             cid,
                          uint8_t            *p_ats_buf,
                          uint8_t             bufsize,
                          uint16_t           *p_rx_len);

/**
 * \brief PICC TypeA��PPS��request for answer to select��
 *
 *     PPS��protocal and parameter selection����ISO14443-4Э���������ڸı���
 * �ص�ר��Э�������������Ǳ���ģ�����ֻ֧��Ĭ�ϲ�������������Ĳ�������Ϊ
 * 0���ɡ���ִ�и�����ǰ�������ȳɹ�ִ��һ��RATS���
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] dsi_dri    : ģ���뿨ͨ�Ų�����,����Ϊ0��Ĭ�ϣ�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_picca_pps (am_zlg600_handle_t  handle,
                         uint8_t             dsi_dri);
                         
/**
 * \brief PICC TypeA���������
 *
 *   ��������ISO14443-4Э���������ڽ���Ƭ��Ϊ����HALT��״̬�����ڹ���
 *��HALT��״̬�Ŀ������á���������������ΪALL�������¼����ֻ��ִ�С�RATS��
 * ����Ŀ����ø����
 *
 * \param[in] handle     : ZLG600�Ĳ������
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_picca_deselect (am_zlg600_handle_t  handle);
                             
/**
 * \brief PICC��T=CL
 *
 *     T=CL�ǰ�˫�����鴫��Э�飬ISO14443-4Э��������ڶ�д���뿨Ƭ֮�������
 * ������һ�����ISO14443Э���CPU�����ø�Э�����д��ͨ�š����ø�����ʱֻ��Ҫ
 * ��CPU��COS�����������Ϊ���뼴�ɣ���������������͡�����ʶ��CID��֡�ȴ�ʱ��
 * FWT���ȴ�ʱ����չ��������WTXM��waiting time extensionmultiplier�����ȵ��ɸ�
 * �����Զ���ɡ�
 *
 * \param[in] handle      : ZLG600�Ĳ������
 * \param[in] p_cos_buf   : COS����
 * \param[in] cos_bufsize ��COS����ĳ���
 * \param[in] p_res_buf   : ���ڽ��ջ�Ӧ����Ϣ����ͬCOS����ֽ������в�ͬ
 * \param[in] res_bufsize : ���ջ�Ӧ��Ϣ�Ļ�������С
 * \param[in] p_rx_len    : ���ڻ�ȡʵ�ʽ��յ���Ϣ���ȣ������������СС��ʵ����
 *                          Ϣ���ȣ�����ಿ�ֽ�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_picc_tpcl (am_zlg600_handle_t  handle,
                         uint8_t            *p_cos_buf,
                         uint8_t             cos_bufsize,
                         uint8_t            *p_res_buf,
                         uint8_t             res_bufsize,
                         uint16_t           *p_rx_len);

/**
 * \brief ���ݽ���
 *
 * �������ö�д���뿨Ƭ�����ݽ�����ͨ���ú�������ʵ�ֶ�д���������й��ܡ�
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] p_data_buf : ��Ҫ�������͵����ݣ���������ʵ��ʹ�õĿ��йأ�
 * \param[in] len        : �������ݵĳ���
 * \param[in] wtxm_crc   : b7~b2,wtxm��b1,RFU(0); b0,0-CRC��ֹ�ܣ�1-CRCʹ�ܡ�
 * \param[in] fwi        : ��ʱ�ȴ�ʱ�����, ��ʱʱ��=����0x01 << fwi*302us��
 * \param[in] p_rx_buf   : ���ݽ�����Ӧ֡��Ϣ
 * \param[in] bufsize    : ���ջ�Ӧ��Ϣ�Ļ�������С
 * \param[in] p_rx_len   : ���ڻ�ȡʵ�ʽ��յ���Ϣ���ȣ������������СС��ʵ����
 *                         Ϣ���ȣ�����ಿ�ֽ�����
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_picc_data_exchange (am_zlg600_handle_t  handle,
                                  uint8_t            *p_data_buf,
                                  uint8_t             len,
                                  uint8_t             wtxm_crc,
                                  uint8_t             fwi,
                                  uint8_t            *p_rx_buf,
                                  uint8_t             bufsize,
                                  uint16_t           *p_rx_len);

/**
 * \brief PICC A����λ��ͨ�����ز��źŹر�ָ����ʱ�䣬�ٿ�����ʵ�ֿ�Ƭ��λ��
 * 
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] time_ms    : �رյ�ʱ�䣨��λ:ms����0Ϊһֱ�ر�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note �ú����������źŹر������룬��һֱ�رգ���ȵ�ִ��һ����������ʱ�򿪡�
 */
int am_zlg600_picca_reset(am_zlg600_handle_t  handle,
                          uint8_t             time_ms);
                          
/**
 * \brief PICC A������ú������ڼ��Ƭ�������󡢷���ײ��ѡ�������������ϡ�
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] req_mode   : ����ģʽ����ʹ�����к꣺
 *                           - #AM_ZLG600_PICCA_REQ_IDLE
 *                           - #AM_ZLG600_PICCA_REQ_ALL
 * \param[in] p_atq      : ����Ӧ��
 * \param[in] p_saq      : ���һ��ѡ��Ӧ��SAK
 * \param[in] p_len      : ���кų��ȣ�4�ֽڻ�7�ֽ�
 * \param[in] p_uid      : ���кŻ�����������Ӧ�������кų��ȱ���һ��
 * \param[in] uid_len    : p_uid ��ָ�������ĳ���
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_picca_active (am_zlg600_handle_t  handle,
                            uint8_t             req_mode,
                            uint16_t           *p_atq,
                            uint8_t            *p_saq,
                            uint8_t            *p_len,
                            uint8_t            *p_uid,
                            uint8_t             uid_len);

/**
 * \name PICCB������ģʽ
 * @{
 */

#define AM_ZLG600_PICCB_REQ_IDLE 0x00 /**< \brief IDLEģʽ,������еĿ� */
#define AM_ZLG600_PICCB_REQ_ALL  0x08 /**< \brief ALLģʽ,�������еĿ�  */

/** @}*/ 

/**
 * \brief PICC B������
 *
 *    �ڵ��øú���ǰ����Ҫȷ��IC����ģʽ�Ѿ�����ΪTypeBģʽ��
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] req_mode   : ����ģʽ����ʹ�����к꣺
 *                           - #AM_ZLG600_PICCB_REQ_IDLE
 *                           - #AM_ZLG600_PICCB_REQ_ALL
 * \param[in] p_uid      : UID�����Ϣ������Ϊ12
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_piccb_active (am_zlg600_handle_t  handle,
                            uint8_t             req_mode,
                            uint8_t            *p_uid);

/**
 * \brief PICC B����λ��ͨ�����ز��źŹر�ָ����ʱ�䣬�ٿ�����ʵ�ֿ�Ƭ��λ��
 * 
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] time_ms    : �رյ�ʱ�䣨��λ:ms����0Ϊһֱ�ر�
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 *
 * \note �ú����������źŹر������룬��һֱ�رգ���ȵ�ִ��һ����������ʱ�򿪡�
 */
int am_zlg600_piccb_reset (am_zlg600_handle_t  handle,
                           uint8_t             time_ms);

/**
 * \brief PICCA���������
 *
 *  �ú�����Ϊ�������������ֻҪ����ISO14443A��׼�Ŀ���Ӧ�ܷ�����Ӧ��
 *
 * \param[in] handle      : ZLG600�Ĳ������
 * \param[in] req_mode    : ����ģʽ����ʹ�����к꣺
 *                           - #AM_ZLG600_PICCB_REQ_IDLE
 *                           - #AM_ZLG600_PICCB_REQ_ALL
 * \param[in] slot_time   : ʱ϶������0 ~ 4
 * \param[in] p_uid       : ���ص�UID�����Ϣ������Ϊ12
 *
 * \retval AM_OK      : ����ɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ���������
 * \retval -AM_EIO    : ����ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_piccb_request (am_zlg600_handle_t  handle,
                             uint8_t             req_mode,
                             uint8_t             slot_time,
                             uint8_t            *p_uid);

/**
 * \brief PICC B ���ķ���ײ����
 *
 * \param[in] handle      : ZLG600�Ĳ������
 * \param[in] slot_flag   : ʱ϶��ǣ�2 ~ 16���ò���ֵ�����������ʱ϶�����й�
 *                          ϵ���������������ʱ϶����Ϊn�����ʱ϶���N < 2^n
 * \param[in] p_uid       : ���ص�UID�����Ϣ������Ϊ12
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_piccb_anticoll (am_zlg600_handle_t  handle,
                              uint8_t             slot_flag,
                              uint8_t            *p_uid);
                             
/**
 * \brief PICC B���Ĺ��������ʹ��ѡ��Ŀ�����HALT״̬
 *
 *     �ú�������B�Ϳ�������ִ�й�������ǰ��������ִ�гɹ���һ���������ִ��
 * ��������ɹ��󣬿�Ƭ���ڹ���״̬��ģ�����ͨ��ALL��ʽ����Ƭ����������IDLE��
 * ʽ����
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] p_pupi     : PUPI,��СΪ4�ֽڵı�ʶ��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_piccb_halt (am_zlg600_handle_t handle,
                          uint8_t            *p_pupi);
 
/**
 * \brief �޸�B���Ĵ�������
 *
 *     �ú�������B�Ϳ�������ִ�й�������ǰ��������ִ�гɹ���һ���������ִ��
 * ��������ɹ��󣬿�Ƭ���ڹ���״̬��ģ�����ͨ��ALL��ʽ����Ƭ����������IDLE��
 * ʽ����
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] p_pupi     : PUPI,��СΪ4�ֽڵı�ʶ��
 * \param[in] cid        : ȡֵ��ΧΪ 0 - 14, ����֧��CID��������Ϊ0
 * \param[in] protype    : ֧�ֵ�Э��
 *                          - bit3 : 1-PCD��ֹ��PICC����ͨ��,0-PCD��PICC����ͨ��
 *                          - bit2 ~ bit1 : 
 *                              - 11 : 10 etu + 512 / fs
 *                              - 10 : 10 etu + 256 / fs
 *                              - 01 : 10 etu + 128 / fs
 *                              - 00 : 10 etu + 32 / fs
 *                          - bit0 : 1-��ѭISO14443-4,0-����ѭISO14443-4
 *                                   (�������֤�����λ����Ϊ1)
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */ 
int am_zlg600_piccb_attrib_set (am_zlg600_handle_t handle,
                                uint8_t           *p_pupi,
                                uint8_t            cid,
                                uint8_t            protype);

/**
 * \brief PLUS CPU�����˻���������
 *
 *     ����������SL0��Security Level 0����ȫ�ȼ�0����PLUS CPU�����˻���PLUS CPU
 * ������ʱ�İ�ȫ�ȼ�ΪSL0���õȼ��£�����Ҫ�κ���֤�Ϳ�������д���ݣ�д�����
 * ������Ϊ������ȫ�ȼ��ĳ�ʼֵ�����磺��SL0��0x0003��д�룺0xA0 0xA1 0xA2 0xA3 
 * 0xA4 0xA5 0xFF 0x07 0x80 0x69 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF������Ƭ������SL1
 * ������0��A��ԿΪ0xA0 0xA1 0xA2 0xA3 0xA4 0xA5��������Ĭ�ϵ�0xFF 0xFF 0xFF 
 * 0xFF 0xFF 0xFF����������SL0�޸Ŀ�Ƭ��Ĭ�����ݺ���Կ��
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] sector_addr   : PLUS CPU���洢����ַ
 * \param[in] p_buf         : ���ͻ�����,���ݸ���Ϊȷ��16��
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_pluscpu_persotcl_write (am_zlg600_handle_t  handle,
                                      uint16_t            sector_addr,
                                      uint8_t            *p_buf);

/**
 * \brief PLUS CPU���ύ���˻�
 *
 *  am_zlg600_pluscpu_persotcl_write()����ֻ�Ǹ��¿��е����ݣ������ݻ�δ��Ч��
 * �ύ�����ݲ���Ч��ִ�и������PLUS CPU���İ�ȫ�ȼ���ߵ�SL1����SL3
 * ������֧��SL1�Ŀ�����ִ�и������Ƭ��ȫ�ȼ���ߵ�SL1������ֻ֧��SL0��SL3��
 * ������ִ�и������Ƭ��ȫ�ȼ���ߵ�SL3����
 * ע�⣺��SL0�У�ֻ���޸������µ�ַ����ִ���ύ������
 * ?- 0x9000��������Կ��
 *   - 0x9001�����ÿ���Կ��
 *   - 0x9002��SL2������Կ��ֻ��֧��SL2�Ŀ����и���Կ��
 *   - 0x9003��SL3������Կ��ֻ��֧��SL3�Ŀ����и���Կ��
 *
 * \param[in] handle        : ZLG600�Ĳ������
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_pluscpu_persotcl_commit (am_zlg600_handle_t  handle);


/**
 * \brief PLUS CPU���״���֤��ֱ����Կ��֤��
 *
 * \param[in] handle       : ZLG600�Ĳ������
 * \param[in] authent_addr : ����֤��16λ��Կ��ַ
 * \param[in] p_key        : ��Կ����������СΪ16�ֽ�
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 *
 * \note PLUS CPU������ԿA/B��ͨ����ַ����ż�������֣�AES����Կ��ַ�����ݿ��
 * ������ϵ��Ӧ����:
 * ��ԿA��ַ=0x4000 + ���� �� 2
 * ��ԿB��ַ=0x4000 + ���� �� 2 + 1
 * ��ˣ�����֤1��������ԿA������Կ��ַΪ��0x4002
 */
int am_zlg600_pluscpu_sl3_first_direct_authent (am_zlg600_handle_t  handle,
                                                uint16_t            authent_addr,
                                                uint8_t            *p_key);

/**
 * \brief PLUS CPU���״���֤��E2��Կ��֤������֤����Կ����ģ���ڲ������粻��ʧ
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] authent_addr  : ����֤��16λ��Կ��ַ
 * \param[in] key_sector    : ��Կ��������
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_pluscpu_sl3_first_e2_authent (am_zlg600_handle_t  handle,
                                            uint16_t            authent_addr,
                                            uint8_t             key_sector);

/**
 * \brief PLUS CPU��������֤��ֱ����Կ��֤��
 *
 *     �ú�������SL3 PLUS CPU���ĸ�����Կ��֤����֤����Կ�������������ֻ��ִ��
 * �����״���֤������ɹ������ʹ�ø����������֤����������ʹ�õ�ʱ�䲻ͬ��
 * ���״���֤������Ҫ��ʱ��ȡ�������֤����ʱ��Ҫ��Щ��
 *
 * \param[in] handle       : ZLG600�Ĳ������
 * \param[in] authent_addr : ����֤��16λ��Կ��ַ
 * \param[in] p_key        : ��Կ����������СΪ16�ֽ�
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 *
 */
int am_zlg600_pluscpu_sl3_follow_direct_authent (am_zlg600_handle_t  handle,
                                                 uint16_t            authent_addr,
                                                 uint8_t            *p_key);

/**
 * \brief PLUS CPU��������֤��E2��Կ��֤��,��֤����Կ����ģ���ڲ������粻��ʧ
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] authent_addr  : ����֤��16λ��Կ��ַ
 * \param[in] key_sector    : ��Կ��������
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_pluscpu_sl3_follow_e2_authent (am_zlg600_handle_t  handle,
                                             uint16_t            authent_addr,
                                             uint8_t             key_sector);

/**
 * \brief PLUS CPU��SL3��λ��֤��E2��Կ��֤��,��֤����Կ����ģ���ڲ������粻��ʧ
 *
 *  ����������PLUS CPU��ͨ���״���֤���ʹ�ù����У���λ��д����������֤����Ϣ��
 *
 * \param[in] handle        : ZLG600�Ĳ������
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_pluscpu_sl3_reset_authent (am_zlg600_handle_t  handle);

/**
 * \name PLUS CPU�������ݵ�ģʽ
 * @{
 */
 
/** \brief ������MAC����������(CIPHER)����Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_READMODE_M_C_NM    0x30

/** \brief ������MAC����������(CIPHER)����Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_READMODE_M_C_M     0x31

/** \brief ������MAC���������ģ���Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_READMODE_M_NC_NM   0x32

/** \brief ������MAC���������ģ���Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_READMODE_M_NC_M    0x33

/** \brief ������MAC���������ģ���Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_READMODE_NM_C_NM   0x34

/** \brief ������MAC���������ģ���Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_READMODE_NM_C_M    0x35

/** \brief ������MAC���������ģ���Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_READMODE_NM_NC_NM  0x36

/** \brief ������MAC���������ģ���Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_READMODE_NM_NC_M   0x37

/** @}*/

/**
 * \brief PLUS CPU��SL3�����ݿ�
 *
 *  �ú������ڶ�ȡSL3�����ݿ飬�ڶ����ݿ�֮ǰ����ɹ�ִ��һ����Կ��֤��
 *
 * \param[in]  handle        : ZLG600�Ĳ������
 * \param[in]  read_mode     : ������ģʽ��ʹ�ú� AM_ZLG600_PLUSCPU_SL3_READMODE_*
 *                             (#AM_ZLG600_PLUSCPU_SL3_READMODE_M_C_M)
 * \param[in]  start_block   : �����ݵ���ʼ���
 * \param[in]  block_num     : ���Ŀ�����1 ~ 3
 * \param[out] p_buf         : ��ȡ�����ݴ�Ż���������СӦ��Ϊ��block_num * 16
 *
 * \retval AM_OK      : ��֤�ɹ�
 * \retval -AM_EINVAL : ��֤ʧ�ܣ���������
 * \retval -AM_EIO    : ��֤ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_pluscpu_sl3_read (am_zlg600_handle_t  handle,
                                uint8_t             read_mode,
                                uint16_t            start_block,
                                uint8_t             block_num,
                                uint8_t            *p_buf);

/**
 * \name PLUS CPU��д���ݵ�ģʽ
 * @{
 */
 
/** \brief ������MAC����������(CIPHER)����Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_WRITEMODE_M_C_NM     0xA0

/** \brief ������MAC����������(CIPHER)����Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_WRITEMODE_M_C_M      0xA1

/** \brief ������MAC���������ģ���Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_WRITEMODE_M_NC_NM    0xA2

/** \brief ������MAC���������ģ���Ӧ��MAC */
#define  AM_ZLG600_PLUSCPU_SL3_WRITEMODE_M_NC_M     0xA3

/** @}*/

/**
 * \brief PLUS CPU��SL3д���ݿ�
 *
 *  �ú�������дSL3�����ݿ飬��д���ݿ�֮ǰ����ɹ�ִ��һ����Կ��֤��
 *
 * \param[in] handle        : ZLG600�Ĳ������
 * \param[in] write_mode    : д����ģʽ��ʹ�ú�AM_ZLG600_PLUSCPU_SL3_WRITEMODE_*
 *                            (#AM_ZLG600_PLUSCPU_SL3_WRITEMODE_M_C_NM)
 * \param[in] start_block   : д���ݵ���ʼ���
 * \param[in] block_num     : д�Ŀ�����1 ~ 3
 * \param[in] p_buf         : д�����ݴ�Ż���������СӦ��Ϊ��block_num * 16
 *
 * \retval AM_OK      : �ɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 * \retval -AM_EIO    : ʧ�ܣ�����ͨ�ų���
 */
int am_zlg600_pluscpu_sl3_write (am_zlg600_handle_t  handle,
                                 uint8_t             write_mode,
                                 uint16_t            start_block,
                                 uint8_t             block_num,
                                 uint8_t            *p_buf);

/**
 * \name PLUS CPU ��ֵ����ģʽ
 * @{
 */
#define AM_ZLG600_PLUSCPU_VALUE_ADD  0xB7  /**< \brief ��  */
#define AM_ZLG600_PLUSCPU_VALUE_SUB  0xB9  /**< \brief ��  */
/** @}*/     
                                
/**
 * \brief PLUS CPU��ֵ�����
 *
 * \param[in] handle     : ZLG600�Ĳ������
 * \param[in] mode       : ֵ������ģʽ�������Ǽӻ����ʹ�����к꣺
 *                          - AM_ZLG600_PLUSCPU_VALUE_ADD
 *                          - AM_ZLG600_PLUSCPU_VALUE_SUB
 * \param[in] src_block  : ����ֵ�����������Դ���
 * \param[in] dst_block  : ֵ��������������ݴ�ŵ�Ŀ�Ŀ��
 * \param[in] value      : 4�ֽ��з�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 *
 * \note Ҫ���д�������������ݱ���Ҫ��ֵ��ĸ�ʽ���ɲο�NXP������ĵ���������
 * ���봫������ͬ���򽫲�����Ľ��д��ԭ���Ŀ��ڣ���������봫���Ų���ͬ��
 * �򽫲�����Ľ��д�봫����ڣ����������ڵ����ݱ����ǣ�ԭ���ڵ�ֵ���䡣
 * ���ڵȼ�2��PLUS CPU����֧��ֵ��������ȼ�1��3֧�֡�
 */
int am_zlg600_pluscpu_val_operate (am_zlg600_handle_t  handle,
                                   uint8_t             mode,
                                   uint16_t            src_block,
                                   uint16_t            dst_block,
                                   int32_t             value);

/**
 * \brief ��ȡ���֤��Ϣ
 *
 * \param[in]  handle   : ZLG600�Ĳ������
 * \param[in]  req_mode : ����ģʽ����ʹ�����к꣺
 *                           - #AM_ZLG600_PICCB_REQ_IDLE
 *                           - #AM_ZLG600_PICCB_REQ_ALL
 * \param[out] p_info : ���֤��Ϣ����������СӦΪ8�ֽڣ�
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_EINVAL : д��ʧ�ܣ���������
 * \retval -AM_EIO    : д��ʧ�ܣ�����ͨ�ų���
 *
 * \note Ҫ���ж����֤��Ϣ���������ȵ��� am_zlg600_ic_isotype_set �ӿڽ�����������ΪB��,
 *       ��ȡ���֮��Ӧ����������� am_zlg600_ic_isotype_set �������ͻ�ԭ�򲻻�ԭ��
 */
int am_zlg600_id_card_info_get (am_zlg600_handle_t handle, uint8_t req_mode, uint8_t *p_info);

/**
 * \brief ָ�ʱʱ������
 *
 * \param[in]  handle     : ZLG600�Ĳ������
 * \param[in]  timeout_ms : ָ�ʱʱ�䣨���룩
 *
 * \retval AM_OK : ���óɹ�
 * \retval ����     : ����ʧ��
 */
int am_zlg600_cmd_timeout_set (am_zlg600_handle_t handle, uint32_t timeout_ms);

/** 
 * @}
 */
 
#endif /* __AM_ZLG600_H */

/* end of file */
