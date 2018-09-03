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
 * \brief �������豸����
 *
 * \internal
 * \par Modification history
 * - 1.01 17-07-17  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_BUZZER_DEV_H
#define __AM_BUZZER_DEV_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"
#include "am_softimer.h"
    
/**
 * \addtogroup am_if_buzzer_dev
 * \copydoc am_buzzer_dev.h
 * @{
 */

/**
 * \brief ��������������
 */
typedef struct am_buzzer_drv_funcs {

    /* �򿪻�رշ����� */
    int (*pfn_buzzer_set) (void *p_cookie, am_bool_t on);

} am_buzzer_drv_funcs_t;

/**
 *  \brief �������豸
 */
typedef struct am_buzzer_dev {
    const am_buzzer_drv_funcs_t     *p_funcs;   /**< \brief ��������      */
    void                            *p_cookie;  /**< \brief ������������  */
    am_softimer_t                    timer;     /**< \brief �����ʱ��  */
} am_buzzer_dev_t;

/**
 * \brief ע��������豸����ǰ��֧�ֵ����������豸
 * \param[in] p_dev �� ע����豸
 * \return AM_OK : ע��ɹ�
 */
int am_buzzer_dev_register (am_buzzer_dev_t             *p_dev,
                            const am_buzzer_drv_funcs_t *p_funcs,
                            void                        *p_cookie);

/** 
 * @}  
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_BUZZER_DEV_H */

/* end of file */
