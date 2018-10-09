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
 * \brief GPIOƽ̨�������ߺ�
 *
 * ���ļ��������� \sa ks16xx_pin.h. �䶨����GPIOƽ̨���ŵĸ������ܡ�
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-15  nwt, make some changes about Macro definition.
 * - 1.00 15-10-18  wangxiaojian, first implementation.
 * \endinternal
 */

#ifndef __AM_KL26_GPIO_UTIL_H
#define __AM_KL26_GPIO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup am_kl26_if_gpio_util
 * \copydoc am_kl26_gpio_util.h
 * @{
 */

/*
 * bit[11:6] ����
 * bit[31:12] ����ƽ̨����
 *
 */

/**
 * \name PORT_PCRn ����λ��
 * @{
 */

#define AM_KL26_PORT_PULLUP               AM_BIT(12) /**< \brief �ܽ�ѡ���ڲ�����ʹ�� */
#define AM_KL26_PORT_PULLEN               AM_BIT(13) /**< \brief �ܽ��ڲ���/����ʹ�� */
#define AM_KL26_PORT_SLEWSLOW             AM_BIT(14) /**< \brief �ܽŵ�ת���� */
#define AM_KL26_PORT_FILTEREN             AM_BIT(15) /**< \brief ��Դ�����˲���ʹ�� */
#define AM_KL26_PORT_DRIVERHIGH           AM_BIT(16) /**< \brief �ܽŸ������� */
#define AM_KL26_PORT_FUNEN                AM_BIT(17) /**< \brief �ܽŸ��ù���ʹ�� */
#define AM_KL26_PORT_DIR                  AM_BIT(18) /**< \brief �ܽŷ��� */

/*******************************************************************************/

/** \brief ��/����λƫ�� */
#define AM_KL26_GPIO_PULL_OFFSET          18

/** \brief ����/����ģʽ�� */
#define AM_KL26_GPIO_PULL_CODE(a)        (AM_SBF((a), AM_KL26_GPIO_PULL_OFFSET) | \
                                               AM_KL26_PORT_PULLUP)

/** \brief ��ȡ��/����ģʽ�� */
#define AM_KL26_GPIO_PULL_GET(data)       AM_BIT_GET((data), AM_KL26_GPIO_PULL_OFFSET)

/** \brief ��/��ʹ��λƫ�� */
#define AM_KL26_GPIO_PE_OFFSET            19

/** \brief ����/����ģʽ������ */
#define AM_KL26_GPIO_PE_CODE(a)          (AM_SBF((a), AM_KL26_GPIO_PE_OFFSET) | \
                                               AM_KL26_PORT_PULLEN)

/** \brief ��ȡ��/����ģʽ������ */
#define AM_KL26_GPIO_PE_GET(data)         AM_BIT_GET((data), AM_KL26_GPIO_PE_OFFSET)

/*******************************************************************************/

/** \brief ת����λƫ�� */
#define AM_KL26_GPIO_SRE_OFFSET           20

/** \brief ��ת������ */
#define AM_KL26_GPIO_SRE_CODE(a)         (AM_SBF((a), AM_KL26_GPIO_SRE_OFFSET) | \
                                               AM_KL26_PORT_SLEWSLOW)

/** \brief ��ȡת������ */
#define AM_KL26_GPIO_SRE_GET(data)        AM_BIT_GET((data), AM_KL26_GPIO_SRE_OFFSET)

/*******************************************************************************/

/** \brief ��Դ�˲���λƫ�� */
#define AM_KL26_GPIO_PFE_OFFSET           21

/** \brief ����Դ�˲����� */
#define AM_KL26_GPIO_PFE_CODE(a)         (AM_SBF((a), AM_KL26_GPIO_PFE_OFFSET) | \
                                               AM_KL26_PORT_FILTEREN)

/** \brief ��ȡ��Դ�˲����� */
#define AM_KL26_GPIO_PFE_GET(data)        AM_BIT_GET((data), AM_KL26_GPIO_PFE_OFFSET)

/*******************************************************************************/

/** \brief ��������λƫ�� */
#define AM_KL26_GPIO_DSE_OFFSET           22

/** \brief ������������ */
#define AM_KL26_GPIO_DSE_CODE(a)         (AM_SBF((a), AM_KL26_GPIO_DSE_OFFSET) | \
                                               AM_KL26_PORT_DRIVERHIGH)

/** \brief ��ȡ���������� */
#define AM_KL26_GPIO_DSE_GET(data)        AM_BIT_GET((data), AM_KL26_GPIO_DSE_OFFSET)

/*******************************************************************************/

#define AM_KL26_GPIO_FUNC_BITS_START      23  /**< \brief �ܽŸ��ù�����ʼλ */
#define AM_KL26_GPIO_FUNC_BITS_LEN        3   /**< \brief �ܽŸ��ù����볤�� */

/** \brief �ùܽŸ��ù����� */
#define AM_KL26_GPIO_FUNC_CODE(a)         (AM_SBF((a), AM_KL26_GPIO_FUNC_BITS_START) | \
                                                AM_KL26_PORT_FUNEN)

/** \brief ��ȡ�ܽŸ��ù����� */
#define AM_KL26_GPIO_FUNC_GET(data)       (AM_BITS_GET((data), AM_KL26_GPIO_FUNC_BITS_START, \
                                                AM_KL26_GPIO_FUNC_BITS_LEN))

/*******************************************************************************/

/** \brief ����λƫ�� */
#define AM_KL26_GPIO_DIRBIT_OFFSET        26

/** \brief �÷����� */
#define AM_KL26_GPIO_DIR_CODE(data)       (AM_SBF((data), AM_KL26_GPIO_DIRBIT_OFFSET) | \
                                                AM_KL26_PORT_DIR)

/** \brief ��ȡ������ */
#define AM_KL26_GPIO_DIR_GET(data)          AM_BIT_GET((data), AM_KL26_GPIO_DIRBIT_OFFSET)

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_KL26_GPIO_UTIL_H */

/* end of file */
