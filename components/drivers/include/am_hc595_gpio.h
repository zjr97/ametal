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
 * \brief HC595��׼�豸ʵ�֣�GPIO������
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-23  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_HC595_GPIO_H
#define __AM_HC595_GPIO_H

#include "am_common.h"
#include "am_errno.h"
#include "am_hc595.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief GPIO����HC595���豸��Ϣ
 *
 * δʹ�õ����ţ���OE���̶�Ϊ�͵�ƽʱ�����Խ� oe���ŵ�ֵ����Ϊ -1
 */
typedef struct am_hc595_gpio_info {
    int data_pin;            /**< \brief ��������                            */
    int clk_pin;             /**< \brief ��λʱ������                        */
    int lock_pin;            /**< \brief ������������                        */
    int oe_pin;              /**< \brief ���ʹ�����ţ�δʹ��ʱ������Ϊ -1�� */

    /**
     * \brief HC595���ݷ����Ƿ����λ�ȷ��ͣ�Ĭ�ϸ�λ�ȷ��ͣ�
     *
     *  ��ֵΪ AM_TRUE �� ���λ�ȷ��ͣ� ���λ���ͳ��� Q7λ��
     *  ��ֵΪ AM_FALSE �� ���λ�ȷ��ͣ� ���λ���ͳ��� Q7λ��
     *
     *  ���磺
     *  - ��Q0 ������� 'a'�����ӣ��� ���� LSB Ӧ���ȷ���
     *  - ��Q7 �� 'a'�����ӣ��� ���� MSB Ӧ���ȷ���
     */
    am_bool_t  lsb_first;

    /** ��λʱ�� �͵�ƽ����ʱʱ��  (��λus) */
    uint16_t clk_low_udelay;

    /** ��λʱ�� �ߵ�ƽ����ʱʱ��  (��λus) */
    uint16_t clk_high_udelay;

} am_hc595_gpio_info_t;

/**
 * \brief GPIO����HC595���豸
 */
typedef struct am_hc595_gpio_dev {
    am_hc595_dev_t                isa;       /**< \brief ��׼��HC595����    */
    const am_hc595_gpio_info_t   *p_info;    /**< \brief �豸��Ϣ           */
} am_hc595_gpio_dev_t;


/**
 * \brief  GPIO����HC595���豸��ʼ��
 *
 * \param[in] p_dev  : GPIO������ HC595�豸
 * \param[in] p_info : GPIO������ HC595�豸��Ϣ
 *
 * \return hc595����������ΪNULL��������ʼ��ʧ��
 */
am_hc595_handle_t am_hc595_gpio_init (am_hc595_gpio_dev_t        *p_dev,
                                      const am_hc595_gpio_info_t *p_info);

/**
 * \brief  GPIO����HC595���豸���ʼ��
 * \param[in] p_dev  : GPIO������ HC595�豸
 * \return AM_OK�����ʼ���ɹ�������ֵ�����ʼ��ʧ��
 */
int am_hc595_gpio_deinit (am_hc595_gpio_dev_t *p_dev);

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC595_H */
