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
 * \brief I2C����������I2C��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-09-19  ari , first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_I2C_H
#define __AM_FSL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_int.h"
#include "am_i2c.h"
#include "hw/amhw_fsl_i2c.h"
#include "am_list.h"
#include "am_softimer.h"

/**
 * \addtogroup am_fsl_if_i2c
 * \copydoc am_fsl_i2c.h
 * @{
 */

/**
 * \brief I2C �豸��Ϣ�����ṹ��
 */
typedef struct am_fsl_i2c_devinfo {
    struct amhw_fsl_i2c  *p_hw_i2c;    /**< \brief ָ��I2C�Ĵ������ַָ��     */
    uint32_t               bus_speed;  /**< \brief I2C ��ʼ������ʱ��     */
    uint16_t               inum;       /**< \brief I2C ���������жϺ�  */
    uint32_t               clk_id;     /**< \brief I2C ʱ�Ӻ� */
    uint16_t               timeout_ms; /**< \brief I2C ��ʱʱ������  */
    void  (*pfn_plfm_init)(void);      /**< \brief ƽ̨��ʼ���������������ŵȹ��� */

    void  (*pfn_plfm_deinit)(void);    /**< \brief ƽ̨���ʼ������ */

} am_fsl_i2c_devinfo_t;

/**
 * \brief I2C �豸�ṹ��
 */
typedef struct am_fsl_i2c_dev {
    /** \brief ��׼I2C����           */
    am_i2c_serv_t                 i2c_serv;

    /** \brief I2C ��������Ϣ���� */
    struct am_list_head           msg_list;

    /** \brief ָ��I2C����ṹ���ָ�룬ͬһʱ��ֻ�ܴ���һ������           */
    am_i2c_transfer_t            *p_cur_trans;

    /** \brief ��ǰ���ڴ������Ϣ   */
    am_i2c_message_t             *p_cur_msg;

    /** \brief �������ݵĴ������   */
    uint32_t                      data_ptr;

    /** \brief I2Cģ��æ��ʶ          */
    am_bool_t                        busy;

    /** \brief I2Cģ�鵱ǰ״̬      */
    uint8_t                       state;

    /** \brief I2Cģ�������ȡ��־      */
    uint8_t                       dummy_rx_flg;

    /** \brief STOP�źŲ�����־      */
    am_bool_t                     stop_signal;

    /** \brief ��ʱ�����ʱ�� */
    am_softimer_t                 softimer;

    /** \brief ָ��I2C�豸��Ϣָ��   */
    const am_fsl_i2c_devinfo_t  *p_devinfo;
} am_fsl_i2c_dev_t;

/**
 * \brief I2C ��ʼ������
 *
 * \param[in] p_dev     : ָ��I2C�豸�ṹ��ָ��
 * \param[in] p_devinfo : ָ��I2C�豸��Ϣ�ṹ��ָ��
 *
 * \return  I2C ��׼����������
 */
am_i2c_handle_t am_fsl_i2c_init(am_fsl_i2c_dev_t           *p_dev,
                                 const am_fsl_i2c_devinfo_t *p_devinfo);

/**
 * \brief I2C ���ʼ������
 * \param[in] handle : ָ��I2C��׼����������
 *
 * \return ��
 */
void am_fsl_i2c_deinit(am_i2c_handle_t handle);

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* __AM_FSL_I2C_H */
/* end of file */
