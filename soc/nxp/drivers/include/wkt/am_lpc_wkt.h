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
 * \brief WKT����������Timer��׼�ӿ�
 *
 * ������ʵ����WKT�Ķ�ʱ����
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-02  sky, modified.
 * - 1.00 15-09-22  zxl, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC_WKT_H
#define __AM_LPC_WKT_H

#include "am_timer.h"
#include "hw/amhw_lpc_wkt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_lpc_if_wkt
 * \copydoc am_lpc_wkt.h
 * @{
 */

/**
 * \brief WKT�豸��Ϣ�ṹ��
 */
typedef struct am_lpc_wkt_devinfo {
    uint32_t                      wkt_regbase;  /**< \brief WKT�Ĵ�����Ļ���ַ */
    uint8_t                       inum;         /**< \brief WKT�жϺ� */
    uint8_t                       channel_nums; /**< \brief ֧�ֵ�ͨ���������Ϊ1 */
    amhw_lpc_wkt_clksel_str_t  clksel_str;   /**< \brief ѡ��WKTʱ��Դ */

    /** \brief WKTʹ���ⲿʱ��Ƶ�ʣ�û��ʹ��WKT�ⲿʱ��������Ϊ0�� */
    uint32_t                      wkt_ext_clock_freq;

    /** \brief WKTƽ̨ʱ�ӳ�ʼ������*/
    void     (*pfn_plfm_clk_init)(const struct am_lpc_wkt_devinfo * p_devinfo);

    /** \brief WKTƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief WKTƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_lpc_wkt_devinfo_t;


/**
 * \brief WKT�豸
 */
typedef struct am_lpc_wkt_dev {
    am_timer_serv_t                timer_serv; /**< \brief ��׼��ʱ(Timer)���� */
    struct {
        void (*pfn_callback)(void *);          /**< \brief �ص����� */
        void *p_arg;                           /**< \brief �ص��������û����� */
    } callback_info;                           /**< \brief �ص�������Ϣ */

    /** \brief ָ��WKT�豸��Ϣ������ָ�� */
    const am_lpc_wkt_devinfo_t *p_devinfo;
} am_lpc_wkt_dev_t;


/**
 * \brief ��ʼ��WKTΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��WKT�豸��ָ��
 * \param[in] p_devinfo : ָ��WKT�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t am_lpc_wkt_init (am_lpc_wkt_dev_t     *p_dev,
                                const am_lpc_wkt_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��WKTʱ�����ʼ��WKT���ͷ������Դ
 * \param[in] handle : ��ʱ����׼����������
 * \return ��
 */
void am_lpc_wkt_deinit (am_timer_handle_t handle);

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC_WKT_H */
