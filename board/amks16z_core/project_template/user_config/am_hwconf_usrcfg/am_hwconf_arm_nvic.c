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
 * \brief The KL26 interrupt user configure
 * \sa am_hwconf_arm_nvic.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-29  hbt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_kl26.h"
#include "am_arm_nvic.h"

/**
 * \addtogroup am_if_hwconf_arm_src_nvic
 * \copydoc am_hwconf_arm_nvic.c
 * @{
 */

/** \brief ISR information count */
#define __ISRINFO_COUNT    INUM_INTERNAL_COUNT

/** \brief Support interrupt count */
static struct am_arm_nvic_isr_info __nvic_isr_infor[__ISRINFO_COUNT];


/** \brief Interrupt map */
uint8_t __nvic_isr_map[INUM_INTERNAL_COUNT];


/** \brief Interrupt device information */
const am_arm_nvic_devinfo_t __g_nvic_devinfo =
{
    {
        INUM_INTERNAL_MIN,  /**< \brief Interrupt start number */
        INUM_INTERNAL_MAX   /**< \brief Interrupt end number   */
    },

	AM_ARM_NVIC_CORE_M0PLUS,

#ifdef AM_CORTEX_M4
    /* ���������ȼ���3λ�������ȼ���0λ */
    3,                      /**< \brief ���ȼ�λ�� */
    4,                      /**< \brief �������ж� */
#endif

#ifdef AM_CORTEX_M0
    /*���������ȼ����������ȼ���2λ */
    2,                      /**< \brief ���ȼ�λ�� */
    0,                      /**< \brief �������ж� */
#endif

    INUM_INTERNAL_COUNT,    /**< \brief ���ж����� */
    __nvic_isr_map,         /**< \brief ISR information map(size equal to input_cnt) */
    __ISRINFO_COUNT,        /**< \brief ISR information count */
    __nvic_isr_infor,       /**< \brief ISR information map memory(size equal to isrinfo_cnt) */

    NULL,                   /**< \brief ����ƽ̨��ʼ�� */
    NULL                    /**< \brief ����ƽ̨ȥ��ʼ�� */
};

/** \brief Interrupt device */
static am_arm_nvic_dev_t __g_nvic_dev;

/**
 * \brief  �ж�ʵ����ʼ������ʼ���ж�����
 */
int am_kl26_nvic_inst_init (void)
{
    return am_arm_nvic_init(&__g_nvic_dev, &__g_nvic_devinfo);
}

/**
 * \brief  �ж�ʵ�����ʼ��
 */
void am_kl26_nvic_inst_deinit (void)
{
    am_arm_nvic_deinit();
}


/**
 * @}
 */

/* end of file */
