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
 * \brief ts10x��ָ����ģ�飩�ӿں���
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-12  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_TS10X_H
#define __AM_TS10X_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_i2c.h"
#include "am_softimer.h"
#include "am_uart_rngbuf.h"

/**
 * @addtogroup am_if_ts10x
 * @copydoc am_ts10x.h
 * @{
 */

/**
 * \name ִ�н����״̬
 *
 *     ��ЩֵΪ������ص�������status�������ܵ�ֵ�� ���������Ϊ  AM_TS10X_SUCCESS ʱ��
 * �ű���ִ�гɹ���
 * @{
 */

#define AM_TS10X_SUCCESS       0x00   /**< \brief ִ�гɹ�               */
#define AM_TS10X_FAIL          0x01   /**< \brief ִ��ʧ��               */
#define AM_TS10X_FULL          0x04   /**< \brief ���ݿ���               */
#define AM_TS10X_NOUSER        0x05   /**< \brief û������û�     */
#define AM_TS10X_USER_EXIST    0x07   /**< \brief �û��Ѵ���           */
#define AM_TS10X_TIMEOUT       0x08   /**< \brief ͼ��ɼ���ʱ      */
#define AM_TS10X_BREAK         0x18   /**< \brief ��ǰ��������ֹ */
#define AM_TS10X_IMAGEFAIL     0x84   /**< \brief ͼ�񲻺ϸ�           */

/** @} */

/**
 * \brief TS10X�����ص�����
 *
 * \param[in] p_arg    : �û��Զ������
 * \param[in] status   : ����ִ�е�״̬
 *
 *
 * \note status��ֵ��Ϊ0����ʾ�����ɹ�ִ����ɡ���Ϊ������Ϊָ�����Զ��������Ϣ��
 * ��  AM_TS10X_USER_EXIST����Ϊ������ΪAMetalƽ̨�Զ���Ĵ�����Ϣ����  -AM_ENOMEM��
 * һ�����������ûص�����ʱ������ʾ������ɣ����Լ���ִ����һ�β���������أ�����
 * �û�ע�������am_ts10x_user_register_*����������Ҫ��ΰ�ѹ��ÿ�ΰ�ѹ����Ҫ��
 * ָ̧����ٴΰ�ѹ����������£�ÿ�ΰ�ѹ�����󶼻���ûص�������������Ҫ������ѹ
 * �Ա�ע�ᣬ��ʱ, status��ֵΪ -AM_EINPROGRESS����ʾ�������ڼ���ִ���С�ֻҪ������
 * ע����̽���ʱ��status��ֵ�Ų�Ϊ -AM_EINPROGRESS��
 */
typedef void (*am_ts10x_process_cb_t) (void *p_arg, int status);

/**
 * \brief ts10x�豸�ṹ�嶨��
 */
typedef struct am_ts10x_dev {

    am_softimer_t    timer;       /**< \brief The Timer for timeout */
    am_uart_handle_t uart_handle; /**< \brief The UART handle       */

    am_bool_t        cmd_ack_complete;   /**< \brief cmd/ack is complete?     */

    uint8_t   data[4];            /**< \brief The data for first packet       */
    uint8_t   cmd_ack_type;       /**< \brief The type of this cmd            */
    uint8_t   is_send_sec;        /**< \brief there is second packet to send? */
    uint8_t   send_sec_num;       /**< \brief the buffer num for the second   */
    uint8_t   is_recv_sec;        /**< \brief there is second packet to recv? */
    uint8_t   recv_sec_num;       /**< \brief the buffer num for the second   */
    uint8_t   chk_value;          /**< \brief the check value for send/recv   */

    int       int_pin;            /**< \brief The int pin                     */
    int       complete_status;    /**< \brief The status for complete         */

    uint32_t  timeout_val;        /**< \brief timeout val for recv now        */
    uint32_t  timeout_expect_val; /**< \brief timeout expect value            */

    size_t    max_length;         /**< \brief The max length of sec data      */
    size_t    data_index;         /**< \brief The data index for now          */
    size_t    sec_buf_index;      /**< \brief The buffer index for sec pack   */


    /** \brief The data buffer info for send second packet */
    struct {
        const uint8_t  *p_buf;
        size_t          expect_len;
    } send_sec_buf_info[3];

    /** \brief The data buffer info for receive second packet */
    struct {
        uint8_t  *p_buf;
        size_t    expect_len;
    } recv_sec_buf_info[3];

    /** \brief private callback   */
     void                       (*pfn_private_cb) (struct am_ts10x_dev *, int);

    /** \brief user callback  */
     am_ts10x_process_cb_t        pfn_process_cb;

    /** \brief The argument for user callback */
    void                         *p_process_arg;

    /** \brief user callback  */
    am_pfnvoid_t                  pfn_int_pin_cb;

    /** \brief The argument for user callback */
    void                         *p_int_pin_arg;

    /** \brief �������ڲ�ʹ��                 */
    const void                   *p_tx_state;

    /** \brief �������ڲ�ʹ��                 */
    const void                   *p_rx_state;

    /** \brief ���ʼ�������յ�ACK��һ���ַ��ĳ�ʱʱ��  */
    uint32_t                      timeout_cmd_start;

    /** \brief The data use internel only */
    union {
        struct {
            volatile  size_t   *p_info_len;
        } version_info_get;

        struct {
            volatile uint16_t *p_user_count;
        } user_count_get;

        struct {
            volatile uint8_t  *p_user_role;
        } user_role_get;

        struct {
            volatile uint16_t  *p_user_id;
              volatile uint8_t   *p_user_role;
        } compare_1_n;

        struct {
            volatile uint16_t  *p_user_id;
        } unused_user_id_get;

        struct {
            volatile uint32_t   baudrate;
        } baudrate_set;

        struct {
            volatile size_t   *p_actual_len;
        } image_data_get;

        struct {
            volatile uint8_t   *p_old_level;
        } compare_level_set;

        struct {
              uint8_t   user_number[2];
              uint16_t *p_user_count;
        } user_all_id_role_get;

        struct {
              am_bool_t *p_allow_same;
        } register_mode_get;

        struct {
              uint8_t  user_id_role[3];
        } add_user_with_feature;

        struct {
              uint8_t  user_id_role[3];
        } compare_feature_with_one_user;

        struct {
              uint16_t  *p_user_id;
        } compare_feature_with_all_user;

        struct {
              uint8_t  data[3];
        } zero_data;

        struct {
               uint16_t  *p_user_id;
               uint8_t    user_role;
               void     (*pfn_continue) (struct am_ts10x_dev *);
        } register_data;

    } private_data;

} am_ts10x_dev_t;


/** \brief ����ts10x�������  */
typedef struct am_ts10x_dev *am_ts10x_handle_t;

/**
 * \brief ts10x��ʼ������
 *
 * ʹ��ts10xǰ��Ӧ�����ȵ��øó�ʼ���������Ի�ȡ����ts10x��handle��
 *
 * \param[in] p_dev       : ָ��ts10xʵ����ָ��
 * \param[in] int_pin     : ��TS10X�ж����������ӵ�MCU���ź�
 * \param[in] uart_handle : UART��׼����������
 *
 * \return ����ts10x��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 *
 * \note �豸ָ��p_devָ����豸ֻ��Ҫ���壬����Ҫ�ڵ��ñ�����ǰ��ʼ����
 */
am_ts10x_handle_t am_ts10x_init (am_ts10x_dev_t           *p_dev,
                                 int                       int_pin,
                                 am_uart_handle_t          uart_handle);

/**
 * \brief ts10x ���ʼ��
 * \param[in] handle  : TS10X��ʵ�����
 * \return AM_OK�����ʼ���ɹ�������ֵ�����ʼ��ʧ�ܡ�
 */
int am_ts10x_deinit (am_ts10x_handle_t handle);

/**
 * \brief ���� ts10x ��������ص�����
 *
 * �������й�����صĽӿں���������ʼ�������ͽ��ʼ�������⣩�������첽ִ�еģ�����
 * ���������أ����������һ���׶�ʱ�������ô˴����õ�������ص�������
 *
 * \param[in] handle         : TS10X��ʵ�����
 * \param[in] pfn_process_cb : ������ص�����
 * \param[in] p_arg          : �ص���������
 *
 * \return ����ts10x��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 */
int am_ts10x_process_cb_set (am_ts10x_handle_t        handle,
                             am_ts10x_process_cb_t    pfn_process_cb,
                             void                    *p_arg);

/**
 * \brief ���� ts10x �ж����Żص�����
 *
 * ������ָ��ѹָ����ʱ���ж����Ž�����ߵ�ƽ����ʱ�������ô˴����õ��ж����Żص�
 * ����
 *
 * \param[in] handle         : ָ��ts10xʵ����ָ��
 * \param[in] pfn_int_pin_cb : �ж����Żص�����
 * \param[in] p_arg          : �ص���������
 *
 * \return ����ts10x��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 */
int am_ts10x_int_pin_cb_set (am_ts10x_handle_t  handle,
                             am_pfnvoid_t       pfn_int_pin_cb,
                             void              *p_arg);

/**
 * \name ע���û�ʹ�õ�ע�᷽ʽ
 *
 * �û�ע�Ṳ��4��������ע�᷽ʽ����1C3R�� 2C2R�� 3C3R�� MOFN(Ĭ�ϵı�׼�汾��1C3R��
 * ģʽ)��aCbR����˼�������˷���a��Command��ģ��˷���b��Return��������a������b��
 * ���أ�����2C2RҲ����1C3R�� MOFN����˼��M-N�ΰ�ѹע�ᣬ����M�Σ����N�Σ�N�λ�ע
 * �᲻�ɹ����ش���
 *
 * �ض���ָ����һ��ֻ֧���ض���һ��ע�᷽����ʹ��  am_ts10x_user_register() ��������
 * �û�ע��ʱ��Ӧ��ȷ��ʹ����ȷ��ע�᷽ʽ��
 *
 * @{
 */

#define AM_TS10X_USER_REG_METHOD_1C3R      1    /**< \brief 1C3R ע�᷽ʽ   */
#define AM_TS10X_USER_REG_METHOD_2C2R      2    /**< \brief 2C2R ע�᷽ʽ   */
#define AM_TS10X_USER_REG_METHOD_3C3R      3    /**< \brief 3C3R ע�᷽ʽ   */
#define AM_TS10X_USER_REG_METHOD_MOFN      4    /**< \brief MOFN ע�᷽ʽ   */

/** @} */

/**
 * \brief �û�ע��
 *
 * \param[in]     handle     : ts10xʵ�����
 * \param[in,out] p_user_id  : ���룺����ע���û���ID ����Чֵ��1 ~ 10000����Ϊ0ʱ
 *                                   ���Զ�����һ��δ��ʹ�õ�ID
 *                             �����ʵ��ע���û���ID��������ֵΪ0ʱ����ֵ��Ϊ�Զ�
 *                                   ������û�ID��
 *
 * \param[in]     user_role  : �û�Ȩ�ޣ���Чֵ1 ~ 3�������ֵ�ĺ����û��Զ���
 * \param[in]     reg_method : ע�᷽ʽ���磺#AM_TS10X_USER_REG_METHOD_1C3R
 *
 * \retval AM_OK            : �û�ע��ɹ�
 * \retval -AM_EINPROGRESS  : ����ע���У�ע����ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_register (am_ts10x_handle_t  handle,
                            uint16_t          *p_user_id,
                            uint8_t            user_role,
                            uint8_t            reg_method);

/**
 * \brief ɾ��һ���ض��û�
 *
 * \param[in]  handle       : ts10xʵ�����
 * \param[in]  user_id      : ��ɾ�����û� ID
 *
 * \retval AM_OK            : ɾ���û��ɹ�
 * \retval -AM_EINPROGRESS  : ����ɾ���У�ɾ����ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_one_del (am_ts10x_handle_t  handle, uint16_t user_id);

/**
 * \brief ɾ�������û�
 *
 * \param[in]  handle       : ts10xʵ�����
 *
 * \retval AM_OK            : ɾ���û��ɹ�
 * \retval -AM_EINPROGRESS  : ����ɾ���У�ɾ����ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_all_del (am_ts10x_handle_t  handle);


/**
 * \brief ��ȡ��ǰ�û�����
 *
 * \param[in]  handle       : ts10xʵ�����
 * \param[out] p_user_count : ��ȡ�û�������ָ��
 *
 * \retval AM_OK            : ��ȡ�û������ɹ�
 * \retval -AM_EINPROGRESS  : ���ڻ�ȡ�У���ȡ��ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_count_get (am_ts10x_handle_t handle, uint16_t *p_user_count);

/**
 * \brief ��ȡָ���û���Ȩ��
 *
 * \param[in]  handle      : ts10xʵ�����
 * \param[in]  user_id     : �û�ID
 * \param[out] p_user_role : ��ȡ�û�Ȩ�޵�ָ��
 *
 * \retval AM_OK            : ��ȡ�û�Ȩ�޳ɹ�
 * \retval -AM_EINPROGRESS  : ���ڻ�ȡ�У���ȡ��ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_role_get (am_ts10x_handle_t handle,
                            uint16_t          user_id,
                            uint8_t          *p_user_role);

/**
 * \brief ��ȡһ��δ��ʹ�õ��û�ID
 *
 * \param[in]  handle      : ts10xʵ�����
 * \param[out] p_user_id   : ���ڻ�ȡδʹ�õ��û�ID��ָ��
 *
 * \retval AM_OK            : ��ȡ�ɹ�
 * \retval -AM_EINPROGRESS  : ���ڻ�ȡ�У���ȡ��ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_id_unused_get (am_ts10x_handle_t  handle,
                                 uint16_t          *p_user_id);

/**
 * \brief ���ò����ʣ�ÿ�θ�λ����ָ�115200��
 *
 * \param[in]  handle        : ts10xʵ�����
 * \param[out] baudrate      : ʹ�õĲ����ʡ�
 *                             ָ���ǽ�֧�֣�9600��19200��38400��57600 �� 115200
 *
 * \retval AM_OK            : ��ȡ�ɹ�
 * \retval -AM_EINPROGRESS  : ���ڻ�ȡ�У���ȡ��ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note ʹ�øú������ò�����ʱ����Ҫȷ��UART����֧�ָò�����
 */
int am_ts10x_baudrate_set (am_ts10x_handle_t  handle,
                           uint32_t           baudrate);

/**
 * \brief �ɼ�ָ��ͼ��,��ȡָ��ͼ�������ֵ��494�ֽڣ�
 *
 * \param[in]  handle     : ts10xʵ�����
 * \param[out] p_data_buf : �����ȡ������ֵ�Ļ�����
 * \param[in]  buf_len    : ���������ȣ���������ֵ����Ϊ494�ֽڣ���˸�ֵΪ 494
 *
 * \retval AM_OK            : ��ȡ�ɹ�
 * \retval -AM_EINPROGRESS  : ������ȡ�У���ȡ��ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note ִ�иú�����ָ���ǽ���ɼ�ָ��״̬����Ҫ��8s�ڰ�ѹָ�ƣ��Ա�ɼ���
 */
int am_ts10x_collect_image_feature_get (am_ts10x_handle_t  handle,
                                        uint8_t           *p_data_buf,
                                        size_t             buf_len);

/**
 * \brief �ɼ�ָ��ͼ��,����ָ��ͼ���λͼ����
 *
 * \param[in]  handle       : ts10xʵ�����
 * \param[out] p_data_buf   : ���ͼ��ֵ�Ļ�����
 * \param[in]  buf_len      : ���������ȣ�Ӧ����ʵ�ʵ�ͼ�����ݳ���һ�£�ʵ��
 *                            ͼ�����ݵĳ����봫�����ֱ�����أ�
 *                            Ϊ��width * 64 + Height / 4
 *
 * \param[out] p_actual_len : ʵ��λͼ���ݵĳ���
 *
 * \retval AM_OK            : ��ȡ�ɹ�
 * \retval -AM_EINPROGRESS  : ������ȡ�У���ȡ��ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note ִ�иú�����ָ���ǽ���ɼ�ָ��״̬����Ҫ��8s�ڰ�ѹָ�ƣ��Ա�ɼ���
 * һ��أ�����ʹ�õ�ָ���Ǵ������ķֱ���Ϊ 176 * 176����ʱ��ͼ�����ݵĴ�СΪ��
 * 176 * 64 + 176 / 4 = 11308 �ֽڡ���Լ 11K��ʹ�øú���ʱ������Ҫһ��11K��
 * ����������ϵͳRAM��С�ĳ��ϣ�����ʹ�øú���ֱ�ӻ�ȡͼ�����ݣ�ֻ��Ҫ��ȡ����ֵ
 * �Ϳ����ˡ�
 */
int am_ts10x_collect_image_data_get (am_ts10x_handle_t  handle,
                                     uint8_t           *p_data_buf,
                                     size_t             buf_len,
                                     size_t            *p_actual_len);

/**
 * \brief ��ȡָ��ģ��İ汾��Ϣ���ַ�����
 *
 *  ��ȡģ��汾��Ϣ�����а����˳���汾�����������͡�ע�᷽ʽ������ʱ�����Ϣ��
 *
 *  ���磬��д����������ʱ����ȡ������ϢΪ���漸�е��ַ���������Ϊ140�ַ�����
 *   Version:  7V33.35_stdrl_024
 *   Sensor:TS1060
 *   RegMode:1C3R
 *   MaxUser:394
 *   Time:Jul  4-15:50:02
 *   Tooan Co.ltd. All rights reserved.
 *
 * \param[in]  handle       : ts10xʵ�����
 * \param[in]  p_buf        : ��Ű汾��Ϣ�Ļ�����
 * \param[in]  buf_size     : ����������
 * \param[out] p_info_size  : ʵ����Ϣ�ĳ���
 *
 * \retval AM_OK            : ��ȡ�汾��Ϣ�ɹ�
 * \retval -AM_EINPROGRESS  : ���ڴ����У�������ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_version_info_get (am_ts10x_handle_t  handle,
                               uint8_t           *p_buf,
                               size_t             buf_size,
                               size_t            *p_info_size);
/**
 * \brief ���ñȶԵȼ�
 *
 *  �ȶԵȼ���������Ϊ 0-3��Ĭ�ϵ��ǹ�ѧ/TS10X1����1���뵼��1060����3���ȶԵȼ�Խ�ߣ�
 *  ����Խ�ϸ�ģ���������ָ���Ĭ��ֵ��
 *
 * \param[in]  handle       : ts10xʵ�����
 * \param[in]  new_level    : �����õıȶԵȼ�
 * \param[out] p_old_level  : ��ȡ֮ǰʹ�õıȶԵȼ�
 *
 * \retval AM_OK            : ���ñȶԵȼ��ɹ�
 * \retval -AM_EINPROGRESS  : ���ڴ����У�������ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_compare_level_set (am_ts10x_handle_t  handle,
                                uint8_t            new_level,
                                uint8_t           *p_old_level);
/**
 * \brief ��ȡ����ע���û���ID��Ȩ����Ϣ
 *
 * \param[in]  handle       : ts10xʵ�����
 * \param[out] p_user_count : ��ǰʵ���û���Ŀ
 * \param[out] p_buf        : ����û�ID��Ȩ����Ϣ�Ļ�������ÿ������ռ�������ֽڣ�
 *                             user_id(��8λ) �� user_id (��8λ)��role
 *
 * \param[in]  buf_len      : ���������ȣ�Ӧ��Ϊ���û���Ŀ * 3 ���ֽ�����
 *
 * \retval AM_OK            : ��ȡ�ɹ�
 * \retval -AM_EINPROGRESS  : ���ڻ�ȡ�У���ȡ��ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_all_id_role_get (am_ts10x_handle_t   handle,
                                   uint16_t           *p_user_count,
                                   uint8_t            *p_buf,
                                   size_t              buf_len);

/**
 * \brief ����ע��ģʽ���Ƿ������ظ�ע���Ѿ����ڵ��û���
 *
 * \param[in] handle      : ts10xʵ�����
 * \param[in] allow_same  : �Ƿ������ظ�ע���Ѿ����ڵ��û���AM_TRUE������AM_FALSE��������
 *
 * \retval AM_OK            : ���óɹ�
 * \retval -AM_EINPROGRESS  : ���������У�������ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note Ĭ��Ϊ�����ظ�ע���Ѿ����ڵ��û���ÿ���ϵ����ָ���Ĭ��ֵ
 */
int am_ts10x_register_mode_set (am_ts10x_handle_t   handle,
                                am_bool_t           allow_same);

/**
 * \brief ��ȡ��ǰ��ע��ģʽ���Ƿ������ظ�ע���Ѿ����ڵ��û���
 *
 * \param[in] handle        : ts10xʵ�����
 * \param[out] p_allow_same : ��ȡ��ǰ��ע��ģʽ��AM_TRUE������AM_FALSE��������
 *
 * \retval AM_OK            : ��ȡ�ɹ�
 * \retval -AM_EINPROGRESS  : ���� ��ȡ�У�������ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_register_mode_get (am_ts10x_handle_t   handle,
                                am_bool_t          *p_allow_same);

/**
 * \brief ��ȡָ���û���ָ������ֵ
 *
 * \param[in]  handle      : ts10xʵ�����
 * \param[in]  user_id     : �û�ID
 * \param[out] p_user_role : ��ȡ�û�Ȩ�޵�ָ��
 * \param[out] p_buf       : �����ȡ������ֵ�Ļ�����
 * \param[in]  buf_len     : ���������ȣ���������ֵ����Ϊ494�ֽڣ���˸�ֵΪ 494
 *
 * \retval AM_OK            : ��ȡ�ɹ�
 * \retval -AM_EINPROGRESS  : ���� ��ȡ�У�������ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_feature_get (am_ts10x_handle_t   handle,
                               uint16_t            user_id,
                               uint8_t            *p_user_role,
                               uint8_t            *p_buf,
                               size_t              buf_len);

/**
 * \brief �´��û�ָ������ֵ���洢��ָ��ģ���У����һ���û���
 *
 * \param[in] handle      : ts10xʵ�����
 * \param[in] user_id     : �������ָ������ֵ���û� ID
 * \param[in] user_role   : ���û���Ȩ����Ϣ����Чֵ 1 ~ 3����ֵ�����û��Զ���
 * \param[in] p_feature   : �洢ָ������ֵ�ռ���׵�ַ
 * \param[in] feature_len : ָ������ֵ�ĳ��ȣ��ֽ�����������Ϊ 494
 *
 * \retval AM_OK            : ɾ���û��ɹ�
 * \retval -AM_EINPROGRESS  : ���ڴ����У�������ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 */
int am_ts10x_user_add_with_feature (am_ts10x_handle_t  handle,
                                    uint16_t           user_id,
                                    uint8_t            user_role,
                                    const uint8_t     *p_feature,
                                    size_t             feature_len);

/**
 * \brief �ɼ�ָ��ͼ�񣬽��� 1 �� 1 �ȶԣ���ָ�ƿ�ָ��ID�û����бȽϣ�
 *
 * \param[in] handle  : ts10xʵ�����
 * \param[in] user_id : �û�ID������ָ�����ڱȽϵ��û�
 *
 * \retval AM_OK            : �ȶԳɹ�
 * \retval -AM_EINPROGRESS  : ���ڱȶ��У��ȶ���ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note ִ�иú�����ָ���ǽ���ɼ�ָ��״̬����Ҫ��8s�ڰ�ѹָ�ƣ��Ա�ɼ���
 */
int am_ts10x_compare_collect_with_one_user (am_ts10x_handle_t handle,
                                            uint16_t          user_id);

/**
 * \brief �ɼ�ָ��ͼ�񣬽��� 1 ��  N �ȶԣ���ָ�ƿ��������û����бȽϣ�
 *
 * \param[in]  handle      : ts10xʵ�����
 * \param[out] p_user_id   : ���ȶԳɹ�����ָ��ɻ�ȡ���ȶԳɹ����û�ID
 * \param[out] p_user_role : ���ȶԳɹ�����ָ��ɻ�ȡ���ȶԳɹ����û�Role
 *
 *
 * \retval AM_OK            : �ȶԳɹ�
 * \retval -AM_EINPROGRESS  : ���ڱȶ��У��ȶ���ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note ִ�иú�����ָ���ǽ���ɼ�ָ��״̬����Ҫ��8s�ڰ�ѹָ�ƣ��Ա�ɼ���
 */
int am_ts10x_compare_collect_with_all_user (am_ts10x_handle_t  handle,
                                            uint16_t          *p_user_id,
                                            uint8_t           *p_user_role);


/**
 * \brief �ɼ�ָ��ͼ����ָ����ָ������ֵ�ȶ�
 *
 * \param[in] handle      : ts10xʵ�����
 * \param[in] p_feature   : �洢ָ������ֵ�ռ���׵�ַ
 * \param[in] feature_len : ָ������ֵ�ĳ��ȣ��ֽ�����������Ϊ 494
 *
 * \retval AM_OK            : �ȶԳɹ�
 * \retval -AM_EINPROGRESS  : ���ڱȶ��У��ȶ���ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note ִ�иú�����ָ���ǽ���ɼ�ָ��״̬����Ҫ��8s�ڰ�ѹָ�ƣ��Ա�ɼ���
 */
int am_ts10x_compare_collect_with_feature (am_ts10x_handle_t  handle,
                                           const uint8_t     *p_feature,
                                           size_t             feature_len);


/**
 * \brief ��ָ��������ֵ��ָ�����û�����ֵ���бȶ�
 *
 * \param[in] handle      : ts10xʵ�����
 * \param[in] p_feature   : �洢ָ������ֵ�ռ���׵�ַ
 * \param[in] feature_len : ָ������ֵ�ĳ��ȣ��ֽ�����������Ϊ 494
 * \param[in] user_id     : �û�ID������ָ�����ڱȶԵ��û�
 * \param[in] user_role   : ָ�����ڱȶԵ��û���Ȩ��ֵ
 *
 * \retval AM_OK            : �ȶԳɹ�
 * \retval -AM_EINPROGRESS  : ���ڱȶ��У��ȶ���ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note ִ�иú�����ָ���ǽ���ɼ�ָ��״̬����Ҫ��8s�ڰ�ѹָ�ƣ��Ա�ɼ���
 */
int am_ts10x_compare_feature_with_one_user (am_ts10x_handle_t  handle,
                                            const uint8_t     *p_feature,
                                            size_t             feature_len,
                                            uint16_t           user_id,
                                            uint8_t            user_role);

/**
 * \brief ��ָ��������ֵ�������û�����ֵ���бȽ�
 *
 * \param[in] handle      : ts10xʵ�����
 * \param[in] p_feature   : �洢ָ������ֵ�ռ���׵�ַ
 * \param[in] feature_len : ָ������ֵ�ĳ��ȣ��ֽ�����������Ϊ 494
 * \param[in] p_user_id   : �û�ID��ָ��
 *
 * \retval AM_OK            : �ȶԳɹ�
 * \retval -AM_EINPROGRESS  : ���ڱȶ��У��ȶ���ɺ󽫵��ûص�����
 * \retval -AM_EBUSY        : �豸æ
 *
 * \note ִ�иú�����ָ���ǽ���ɼ�ָ��״̬����Ҫ��8s�ڰ�ѹָ�ƣ��Ա�ɼ���
 */
int am_ts10x_compare_feature_with_all_user (am_ts10x_handle_t  handle,
                                            const uint8_t     *p_feature,
                                            size_t             feature_len,
                                            uint16_t          *p_user_id);

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_TS10X_H */

/* end of file */
