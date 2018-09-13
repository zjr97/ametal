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
 * \brief ZLG217 SYSTICK �û������ļ�
 * \sa am_hwconf_zlg217_systick.c
 *
 * \internal
 * \par Modification History
 * - 1.00 17-12-04  pea, first implementation
 * \endinternal
 */

#include "am_arm_systick.h"
#include "am_zlg217.h"
#include "amhw_arm_systick.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_systick
 * \copydoc am_hwconf_zlg217_systick.c
 * @{
 */

/**
 * \brief �豸��Ϣ
 * \note ʱ��Դ��Ϊϵͳʱ�ӣ�#AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM����ϵͳʱ��
 *       �� 1/2��#AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM_HALF��
 */
static const am_arm_systick_devinfo_t __g_systick_devinfo = {
    ZLG217_SYSTICK,                        /**< \brief ָ�� SYSTICK �Ĵ�����ָ�� */
    CLK_SYS,                               /**< \brief SYSTICK ʱ�� ID */
    AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM, /**< \brief SYSTICK ʱ��ѡ��ϵͳʱ�� */

    NULL,                                  /**< \brief ����ƽ̨��ʼ�� */
    NULL                                   /**< \brief ����ƽ̨ȥ��ʼ�� */
};

/** \brief �豸ʵ�� */
static am_arm_systick_dev_t __g_systick_dev;

/** \brief SYSTICK ʵ����ʼ������� TIMER ��׼������ */
am_timer_handle_t am_zlg217_systick_inst_init (void)
{
    return am_arm_systick_init(&__g_systick_dev, &__g_systick_devinfo);
}

/** \brief SYSTICK ʵ�����ʼ�� */
void am_zlg217_systick_inst_deinit (am_timer_handle_t handle)
{
    am_arm_systick_deinit(handle);
}

/**
 * @}
 */

/* end of file */
