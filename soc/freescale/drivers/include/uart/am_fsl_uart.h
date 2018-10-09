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
 * \brief UART����������UART��׼�ӿ�
 *        ����������485ģʽʱ����Ҫ���ж�ģʽ��ʹ��
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-15  nwt, make some changes.
 * - 1.00 15-10-19  xym, first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_UART_H
#define __AM_FSL_UART_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"
#include "hw/amhw_fsl_uart.h"
/**
 * \addtogroup am_fsl_if_uart
 * \copydoc am_fsl_uart.h
 * @{
 */

/**
 * \name �������ţ�����ص�������code���������������ݸ��û���ָ����ǰ�Ĵ�������
 *
 *  ����ص������Ĳ���ԭ�ͣ�\n
 *  int uart_err(void *p_arg, int code, void *p_data, int size);
 *  p_arg���û�ע����û�������p_data��size��ͬ�Ĵ������Ͱ�������Ϣ������ͬ��
 *  ����ʹ��am_uart_callback_set() �������ô��ڴ���ص�������
 * @{
 */

/**
 * \brief �û�ָ���������жϷ���,p_data������Ϊuint32_t��ֵΪ���ڵ��ж�״̬����
 *        ���û��жϾ�����ж�Դ��sizeΪ1��
 */
#define AM_FSL_UART_ERRCODE_UART_OTHER_INT  2

/** @} */

/**
 * \brief 485ģʽ������/���տ������ŷ����������ж�ģʽ�£�
 * \param[in] flag  AM_TRUE:����ģʽ AM_FALSE: ����ģʽ
 */
typedef void (*pfn_uart_int_485_send_t) (am_bool_t flag);

/**
 * \brief ���������İ汾��
 *  ��ͬ�İ汾�ţ����ò����ʵĺ�������ȡ�ж�״̬�Ⱥ���Ҳ��ͬ
 *  AM_FSL_UART_VER0 S1�Ĵ�����5λ��д������ƥ���ַ�Ĺ��ܣ�������MA1��MA2��C5�Ĵ�����
 *  AM_FSL_UART_VER0 S1�Ĵ�����5λ����д ,��ƥ���ַ�Ĺ��ܡ�
 */

# define AM_FSL_UART_VER0 0
# define AM_FSL_UART_VER1 1
/**
 * \brief �����豸��Ϣ�ṹ�壬���豸��Ϣ���ڴ��ڳ�ʼ��
 */
typedef struct am_fsl_uart_devinfo {

    amhw_fsl_uart_t *p_hw_uart;     /**< \brief ָ��UART�Ĵ������ָ��. */

    uint8_t      inum;              /**< \brief �����жϺ�.           */

    uint8_t      ver;               /**< \brief ���������İ汾��.           */

    uint32_t     clk_id;            /**< \brief uart ʱ�Ӻ� */

    /**
     * \brief �������ñ�־��AMHW_FSL_UART_C1_M_*���AMHW_FSL_UART_C1_PARITY_*��
     *        ��AMHW_UART_BDH_SBNS_STOP_*�Ļ�ֵ
     *        (�磺AMHW_FSL_UART_C1_M_8BIT|AMHW_FSL_UART_C1_PARITY_NO
     *                                    |AMHW_FSL_UART_BDH_SBNS_STOP_1)
     */
    uint8_t     cfg_flags;


    uint32_t     baud_rate;           /**< \brief ��ʼ��������.         */

    /**
     * \brief ָ��ʹ�ܵ������ж�,AMHW_FSL_UART_INT_*��ֵ����AMHW_FSL_UART_INT_*���
     *        ��ֵ������(#AMHW_FSL_UART_INT_C2_TCIE),(#AMHW_FSL_UART_INT_C2_IRIE),
     *        (#AMHW_FSL_UART_INT_C2_ILIE)��(#AMHW_FSL_UART_INT_C2_TIE)���ĸ��жϡ�
     */
    uint32_t     other_int_enable;

    /** \brief 485ģʽ�·���/�������ſ��ƣ������ж�ģʽ */
    pfn_uart_int_485_send_t uart_int_485_send;

    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������.  */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������. */

} am_fsl_uart_devinfo_t;

/**
 * \brief �����豸�ṹ�嶨��
 */
typedef struct am_fsl_uart_dev {

    am_uart_serv_t  uart_serv;             /**< \brief ��׼UART����          */

    /** \brief ָ���û�ע���txchar_get���� */
    int (*pfn_txchar_get)(void *, char *);  
    
    /** \brief ָ���û�ע���rxchar_put���� */
    int (*pfn_rxchar_put)(void *, char);   

    /** \brief ָ���û�ע��Ĵ���ص�����   */    
    int (*pfn_err)(void *, int, void *, int); 

    void     *txget_arg;                   /**< \brief txchar_get��������    */
    void     *rxput_arg;                   /**< \brief rxchar_put��������    */
    void     *err_arg;                     /**< \brief ����ص������û�����  */
    
    uint8_t   channel_mode;                /**< \brief ����ģʽ �ж�/��ѯ    */
    uint32_t  baud_rate;                   /**< \brief ���ڲ�����            */
    uint16_t  options;                     /**< \brief Ӳ������ѡ��          */

    uint32_t  other_int_enable;            /**< \brief ָ��ʹ�ܵ������ж�    */

    const am_fsl_uart_devinfo_t *p_devinfo;  /**< \brief ָ���豸��Ϣ������ָ��*/

} am_fsl_uart_dev_t;

/**
 * \brief ��ʼ��UART������UART��׼����������
 *
 * \param[in] p_dev     : ָ�򴮿��豸��ָ��
 * \param[in] p_devinfo : ָ�򴮿��豸��Ϣ������ָ��
 *
 * \return UART��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_uart_handle_t am_fsl_uart_init(am_fsl_uart_dev_t           *p_dev,
                                   const am_fsl_uart_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��UARTʱ�����ʼ��UART���ͷ������Դ
 * \param[in] p_dev : ָ�򴮿��豸��ָ��
 */
void am_fsl_uart_deinit(am_fsl_uart_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_FSL_UART_H */

/* end of file */
