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
 * \brief ARM NVIC �û������ļ�
 * \sa am_hwconf_arm_nvic.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-29  hbt, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_arm_nvic.h"

/**
 * \addtogroup am_if_src_hwconf_arm_nvic
 * \copydoc am_hwconf_arm_nvic.c
 * @{
 */

/** \brief �ж���Ϣ���� */
#define __ISRINFO_COUNT    INUM_INTERNAL_COUNT

/** \brief �ж���Ϣӳ�� */
am_local uint8_t __nvic_isr_map[INUM_INTERNAL_COUNT];

/** \brief �ж���Ϣӳ���ڴ� */
am_local struct am_arm_nvic_isr_info __nvic_isr_infor[__ISRINFO_COUNT];

/** \brief �ж��豸��Ϣ */
am_local am_const am_arm_nvic_devinfo_t __g_arm_nvic_devinfo =
{
    {
        INUM_INTERNAL_MIN,   /* ��ʼ�жϺ� */
        INUM_INTERNAL_MAX    /* ĩβ�жϺ� */
    },

    AM_ARM_NVIC_CORE_M0PLUS, /* Cortex-M0+ �ں� */

    2,                       /* ���������ȼ����������ȼ��� 2 λ */
    0,                       /* ���ж� */

    INUM_INTERNAL_COUNT,     /* ���ж����� */
    __nvic_isr_map,          /* �ж���Ϣӳ�� */
    __ISRINFO_COUNT,         /* �ж���Ϣ���� */
    __nvic_isr_infor,        /* �ж���Ϣӳ���ڴ� */

    NULL,                    /* ����ƽ̨��ʼ������ */
    NULL                     /* ����ƽ̨���ʼ������ */
};

/** \brief �ж��豸ʵ�� */
am_local am_arm_nvic_dev_t __g_arm_nvic_dev;

/**
 * \brief �ж�ʵ����ʼ������ʼ���ж�����
 */
int am_arm_nvic_inst_init (void)
{
    return am_arm_nvic_init(&__g_arm_nvic_dev, &__g_arm_nvic_devinfo);
}

/**
 * \brief �ж�ʵ�����ʼ��
 */
void am_arm_nvic_inst_deinit (void)
{
    am_arm_nvic_deinit();
}

/**
 * @}
 */

/* end of file */
