/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USART����������UART��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-03  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC_USART_H
#define __AM_LPC_USART_H

#include "ametal.h"
#include "am_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_lpc_if_usart
 * \copydoc am_lpc_usart.h
 * @{
 */

/**
 * \brief �û�ָ���������жϷ���
 */
#define AM_LPC_UART_ERRCODE_USART_OTHER_INT  2
 
/**
 * \brief ����������ص�XON�ַ����壬Ĭ��0x11
 */ 
#define AM_LPC_UART_XON       0x11
  
/**
 * \brief ����������ص�XOFF�ַ����壬Ĭ��0x13
 */ 
#define AM_LPC_UART_XOFF      0x13


/**
 * \brief �����豸��Ϣ�ṹ�壬���豸��Ϣ���ڴ��ڳ�ʼ��
 */
typedef struct am_lpc_usart_devinfo {

    uint32_t usart_regbase;        /**< \brief USART�Ĵ�����ַ */

    uint8_t  inum;                 /**< \brief �����жϺ� */
  
  uint32_t  clk_id;               /**< \brief ����ʱ��ID */
    
    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨���ʼ������ */

    /** \brief RS485������ƺ���, AM_TRUE: ����ģʽ�� AM_FALSE: ����ģʽ */
    void  (*pfn_rs485_dir) (am_bool_t is_txmode);
    
} am_lpc_usart_devinfo_t;

/**
 * \brief �����豸�ṹ�嶨��
 */
typedef struct am_lpc_usart_dev {

    /** \brief ��׼UART����                 */
    am_uart_serv_t       uart_serv;

    /** \brief ָ���û�ע���txchar_get���� */
    am_uart_txchar_get_t pfn_txchar_get;

    /** \brief ָ���û�ע���rxchar_put���� */
    am_uart_rxchar_put_t pfn_rxchar_put;
 
    /** \brief ָ���û�ע��Ĵ���ص�����   */
    am_uart_err_t        pfn_err;

    /** \brief txchar_get��������           */
    void     *p_txget_arg;

    /** \brief rxchar_put��������           */
    void     *p_rxput_arg;

    /** \brief ����ص������û�����         */
    void     *p_err_arg;
  
    /** \brief �Ƿ�ʹ���� 485ģʽ          */
    am_bool_t rs485_en;

    /** \brief ����ģʽ���ޣ������Ӳ����   */
    uint8_t   flowctl_mode;                   

    /** \brief ���ط�����״̬�����������أ� */
    uint8_t   flowctl_tx_stat;                

    /** \brief ����ģʽ �ж�/��ѯ           */
    uint8_t   channel_mode; 

    /** \brief ���ڲ�����                   */
    uint32_t  baud_rate; 

    /** \brief Ӳ������ѡ��                 */
    uint16_t  options;                        

    /** \brief ָ��ʹ�ܵ������ж�           */
    uint32_t  other_int_enable;
 
    /** \brief ָ���豸��Ϣ������ָ��       */
    const am_lpc_usart_devinfo_t *p_devinfo;

} am_lpc_usart_dev_t;

/**
 * \brief ��ʼ��USART������UART��׼����������
 *
 * \param[in] p_dev     : ָ�򴮿��豸��ָ��
 * \param[in] p_devinfo : ָ�򴮿��豸��Ϣ������ָ��
 *
 * \return UART��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_uart_handle_t am_lpc_usart_init (am_lpc_usart_dev_t           *p_dev,
                                    const am_lpc_usart_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��USARTʱ�����ʼ��USART���ͷ������Դ
 *
 * \param[in] handle : UART��׼����������
 *
 * \return ��
 */
void am_lpc_usart_deinit (am_uart_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC_USART_H */

/* end of file */
