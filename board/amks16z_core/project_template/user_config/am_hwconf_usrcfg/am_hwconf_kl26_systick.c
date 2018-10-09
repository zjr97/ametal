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
 * \brief KL26 SYSTICK �û����ÿ��ļ�
 * \sa am_kl26_hwconfig_systick.c
 *
 * \internal
 * \par Modification History
 * - 1.00 15-08-  win, first implementation.
 * \endinternal
 */

#include "am_arm_systick.h"
#include "am_kl26.h"
#include "hw/amhw_arm_systick.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_systick
 * \copydoc am_kl26_hwconfig_systick.c
 * @{
 */

/**
 * \brief SYSTICK �豸��Ϣ
 * \note ʱ��Դ��Ϊϵͳʱ�ӣ�#AMHW_KL26_SYSTICK_CONFIG_CLKSRC_SYSTEM����ϵͳʱ�ӵ�1/2
 *       ��#AMHW_KL26_SYSTICK_CONFIG_CLKSRC_SYSTEM_HALF��
 */
static const am_arm_systick_devinfo_t __g_systick_devinfo = {
    KL26_SYSTICK_BASE,                        /**< \brief ָ��SYSTICK�Ĵ�����ָ�� */
    CLK_SYSTICK,                              /**< \brief SYSTICKʱ��ID, ��Դ����ʱ��*/
    AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM,    /**< \brief SYSTICKʱ��ѡ��ϵͳʱ��*/
    
    NULL,                                     /**< \brief ����ƽ̨��ʼ�� */
    NULL                                      /**< \brief ����ƽ̨ȥ��ʼ�� */
};

/** \brief SYSTICK �豸 */
static am_arm_systick_dev_t __g_systick_dev;


/** \brief SYSTICK ʵ����ʼ�������systick��׼������ */
am_timer_handle_t am_kl26_systick_inst_init (void)
{
    return am_arm_systick_init(&__g_systick_dev, &__g_systick_devinfo);
}

/** \brief SYSTICK ʵ�����ʼ�� */
void am_kl26_systick_inst_deinit (am_timer_handle_t handle)
{
    am_arm_systick_deinit(handle);
}

/**
 * @}
 */

/* end of file */
