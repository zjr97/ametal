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
 * \brief NVIC �û������ļ�
 * \sa am_hwconf_arm_nvic.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-05  cyl, modify the namespace.
 * - 1.00 15-01-29  hbt, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg217.h"
#include "am_arm_nvic.h"

/**
 * \addtogroup am_if_src_hwconf_arm_nvic
 * \copydoc am_hwconf_arm_nvic.c
 * @{
 */

/**
 * \brief ISR ��Ϣ����
 *        ������Ĭ�϶���Ϊ MCU ��֧�ֵ���������жϸ�����
 *        �û����Ը���Ӧ����ʵ������Ҫ�õ����жϸ���
 *        ���޸ĸú�ֵ���Դﵽ���ٲ���Ҫ���ڴ��˷ѵ�Ŀ�ġ�
 */
#define __ISRINFO_COUNT    INUM_INTERNAL_COUNT

/**
 * \brief �洢�û��жϻص���Ϣ
 */
static struct am_arm_nvic_isr_info __nvic_isr_infor[__ISRINFO_COUNT];

/**
 * \brief �洢�жϱ�������Ӧ�� __nvic_isr_infor �жϻص���Ϣ��
 *        λ�õ�ӳ�䣬�����Сһ����MCU��֧�ֵ���������жϸ�����ȡ�
 */
static uint8_t __nvic_isr_map[INUM_INTERNAL_COUNT];

/** \brief �豸��Ϣ */
static const am_arm_nvic_devinfo_t __g_nvic_devinfo =
{
    {
        INUM_INTERNAL_MIN, /**< \brief �ж���ʼ�� */
        INUM_INTERNAL_MAX  /**< \brief �ж�ĩβ�� */
    },

    AM_ARM_NVIC_CORE_M3,   /**< \brief �ں� */
    4,                     /**< \brief ���ȼ�λ�� */
    16,                    /**< \brief �������ж� */
    INUM_INTERNAL_COUNT,   /**< \brief ���ж����� */
    __nvic_isr_map,        /**< \brief ISR ��Ϣӳ��(��С�� input_cnt һ��) */
    __ISRINFO_COUNT,       /**< \brief ISR ��Ϣ���� */
    __nvic_isr_infor,      /**< \brief ISR ��Ϣӳ���ڴ�(��С�� isrinfo_cnt һ��) */

    NULL,                  /**< \brief ����ƽ̨��ʼ�� */
    NULL                   /**< \brief ����ƽ̨ȥ��ʼ�� */
};

/** \brief �豸ʵ�� */
static am_arm_nvic_dev_t __g_nvic_dev;

/**
 * \brief �ж�ʵ����ʼ������ʼ���ж�����
 */
int am_zlg217_nvic_inst_init (void)
{
    return am_arm_nvic_init(&__g_nvic_dev, &__g_nvic_devinfo);
}

/**
 * \brief �ж�ʵ�����ʼ��
 */
void am_zlg217_nvic_inst_deinit (void)
{
    am_arm_nvic_deinit();
}

/**
 * @}
 */

/* end of file */
