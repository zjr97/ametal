/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief I2C drivers for standard interface 
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-10  jon, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC_I2C_H
#define __AM_LPC_I2C_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_int.h"
#include "am_list.h"
#include "am_i2c.h"
#include "hw/amhw_lpc_i2c.h"

/**
 * \addtogroup am_lpc_if_i2c
 * \copydoc am_lpc_i2c.h
 * @{
 */


/**
 * \brief I2C controller configure parameter 
 */
typedef struct am_lpc_i2c_devinfo {
   
    /** \brief I2C bus speed rate */
    uint32_t   bus_speed;

    uint32_t   i2c_regbase;            /**< \brief Pointer to the I2C register base addr */

    uint16_t   inum;                   /**< \brief I2C interrupt number    */
    uint32_t   clk_id;                 /**< \brief I2C clk id              */

    /**
     * \brief ��ʱʱ��ֵ
     *
     * I2C���������ݴ����ڼ䣬���˶�ʱ����ʱ�������κ���Ӧ,����Ϊ��ʱ��
     * ������ǰ���䲢��λ�ڲ��߼�
     */
    uint32_t  timeout_ms;

    void (*pfn_plfm_init)(void);       /**< \brief plfm init  fuc  */

    void (*pfn_plfm_deinit)(void);     /**< \brief plfm deinit fuc */

} am_lpc_i2c_devinfo_t;

/** \brief For the file of am_i2c.h used */
typedef am_lpc_i2c_devinfo_t am_i2c_devinfo_hw_t;

/**
 * \brief I2C device
 */
typedef struct am_lpc_i2c_dev {
    
     /** \brief The standard serve functions for I2C */
    am_i2c_serv_t            i2c_serv;

    /** \brief I2C ��������Ϣ���� */
    struct am_list_head       msg_list;

    /** \brief ָ��I2C����ṹ���ָ�룬ͬһʱ��ֻ�ܴ���һ������           */
    am_i2c_transfer_t        *p_cur_trans;

    /** \brief ��ǰ���ڴ������Ϣ   */
    am_i2c_message_t         *p_cur_msg;

    /** \brief �������ݽ���/���ͼ���   */
    uint32_t                  data_ptr;

    /** \brief I2Cʱ�ӣ�ʹ��DIV��Ƶ���ʱ��Ƶ�� */
    uint32_t                  i2c_clkrate;

    /** \brief æ��ʶ                 */
    am_bool_t                 busy;

    /** \brief ״̬                   */
    uint8_t                   state;
    
    /** \brief I2C controller configure parameter */
    const am_lpc_i2c_devinfo_t *p_devinfo;

} am_lpc_i2c_dev_t;

/** \brief For the file of am_i2c.h used */
typedef am_lpc_i2c_dev_t am_i2c_dev_hw_t;



/**
 * \brief Initialize the I2C
 *
 * \param[in] p_dev     : Pointer to the I2C device
 * \param[in] p_devinfo : Pointer to the I2C device information to initialize
 *
 * \return The handle for standard I2C port.if NULL,Indicate that INIT failed
 */
am_i2c_handle_t am_lpc_i2c_init(am_lpc_i2c_dev_t           *p_dev,
                              const am_lpc_i2c_devinfo_t *p_devinfo);

/**
 * \brief De-Initialize the I2C
 * \param[in] handle     : The handle for standard I2C
 * \return None
 */
void am_lpc_i2c_deinit (am_i2c_handle_t handle);



/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC_I2C_H */

/* end of file */
