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
 * \brief GPIO����������GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-15  nwt, make some changes.
 * - 1.00 15-10-21  wxj, first implementation.
 * \endinternal
 */

#ifndef __AM_KL26_GPIO_H
#define __AM_KL26_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "../../../kl26/kl26_pin.h"
#include "hw/amhw_kl26_gpio.h"
#include "hw/amhw_kl26_pinctrl.h"

/**
 * \addtogroup am_kl26_if_gpio
 * \copydoc am_kl26_gpio.h
 * @{
 */

/**
 * \brief ���ŵĴ�����Ϣ
 */
struct am_kl26_gpio_trigger_info {

    /** \brief �����ص�����   */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
};

/**
 * \brief GPIO �豸��Ϣ
 */
typedef struct am_kl26_gpio_devinfo {

    /** \brief ָ��PORT�Ĵ������ָ��.  */
    amhw_kl26_port_t    *p_hw_port;

    /** \brief ָ��GPIO�Ĵ������ָ��.  */
    amhw_kl26_gpio_t    *p_hw_gpio;

    /** \brief GPIO�����жϺ��б�.     */
    const int8_t    inum_pin[2];

    /** \brief GPIO֧�ֵ������жϺ�����. */
    size_t    pint_count;

    /** \brief ������ʽӳ��.           */
    uint8_t  *p_infomap;

    /** \brief ָ�����Ŵ�����Ϣ��ָ��.   */
    struct am_kl26_gpio_trigger_info  *p_triginfo;

    /** \brief ƽ̨��ʼ������.  */
    void (*pfn_plfm_init)(void);

    /** \brief ƽ̨ȥ��ʼ������. */
    void (*pfn_plfm_deinit)(void);

} am_kl26_gpio_devinfo_t;

/**
 * \brief GPIO�豸ʵ��
 */
typedef struct am_kl26_gpio_dev {

    /** \brief ָ��GPIO�豸��Ϣ��ָ��         */
    const am_kl26_gpio_devinfo_t *p_devinfo;

    /** \brief ������Ч��־                   */
    am_bool_t  valid_flg;

} am_kl26_gpio_dev_t;

/**
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_kl26_gpio_init(am_kl26_gpio_dev_t           *p_dev,
                      const am_kl26_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIOȥ��ʼ��
 *
 * \return ��
 */
void am_kl26_gpio_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_KL26_GPIO_H */

/* end of file */
