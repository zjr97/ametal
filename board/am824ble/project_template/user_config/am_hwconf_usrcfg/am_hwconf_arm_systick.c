/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ARM Systick �û������ļ�
 * \sa am_hwconf_arm_systick.c
 *
 * \internal
 * \par Modification History
 * - 1.00 15-08-01  win, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_arm_systick.h"
#include "am_lpc82x.h"
#include "hw/amhw_arm_systick.h"

/**
 * \addtogroup am_if_src_hwconf_arm_systick
 * \copydoc am_hwconf_arm_systick.c
 * @{
 */

/**
 * \brief Systick �豸��Ϣ
 *
 * \note ʱ��Դ��Ϊϵͳʱ�� (#AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM) ��ϵͳ
 *       ʱ�ӵ� 1/2 (#AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM_HALF)
 */
am_local am_const am_arm_systick_devinfo_t __g_arm_systick_devinfo = {
    LPC82X_SYSTICK_BASE,                      /* ָ�� Systick �Ĵ�����ָ�� */
    CLK_SYSTEM,                               /* Systick ʱ�Ӻţ���Դ����ʱ�� */
    AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM,    /* Systick ʱ��ѡ��ϵͳʱ�� */
    NULL,                                     /* ����ƽ̨��ʼ������ */
    NULL                                      /* ����ƽ̨���ʼ������ */
};

/** \brief Systick �豸ʵ�� */
am_local am_arm_systick_dev_t __g_arm_systick_dev;

/**
 * \brief Systick ʵ����ʼ��
 */
am_timer_handle_t am_arm_systick_inst_init (void)
{
    return am_arm_systick_init(&__g_arm_systick_dev, &__g_arm_systick_devinfo);
}

/**
 * \brief Systick ʵ�����ʼ��
 */
void am_arm_systick_inst_deinit (am_timer_handle_t handle)
{
    am_arm_systick_deinit(handle);
}

/**
 * @}
 */

/* end of file */
