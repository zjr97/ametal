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
 * - 1.00 17-08-22  zcb,first implementation
 * \endinternal
 */

#ifndef __AM_ZLG217_GPIO_H
#define __AM_ZLG217_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "amhw_zlg217_gpio.h"
#include "am_zlg217_gpio_util.h"
#include "amhw_zlg217_afio.h"

/**
 * \addtogroup am_zlg217_if_gpio
 * \copydoc am_zlg217_gpio.h
 * @{
 */

/**
 * \brief ���ŵĴ�����Ϣ
 */
struct am_zlg217_gpio_trigger_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
};

/**
 * \brief GPIO �豸��Ϣ
 */
typedef struct am_zlg217_gpio_devinfo {

    /** \brief GPIO�Ĵ������ַ */
    uint32_t      gpio_regbase;

    /** \brief EXTI�Ĵ������ַ */
    uint32_t      exti_regbase;

    /** \brief AFIO�Ĵ������ַ */
    uint32_t      afio_regbase;

    /** \brief EXIT�жϺ��б� */
    const int8_t  inum_pin[7];

    /** \brief GPIO�������� */
    const uint8_t pin_count;

    /** \brief GPIOʹ�õ�����ⲿ�ж��߱��+1 */
    const uint8_t exti_num_max;

    /** \brief ������Ϣӳ�� */
    uint8_t      *p_infomap;

    /** \brief ������ӳ��������Ϣ */
    amhw_zlg217_afio_remap_peripheral_t  *p_remap;

    /** \brief ָ�����Ŵ�����Ϣ��ָ�� */
    struct am_zlg217_gpio_trigger_info   *p_triginfo;

    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������ */

} am_zlg217_gpio_devinfo_t;

/**
 * \brief GPIO�豸ʵ��
 */
typedef struct am_zlg217_gpio_dev {

    /** \brief ָ��GPIO�豸��Ϣ��ָ�� */
    const am_zlg217_gpio_devinfo_t *p_devinfo;

    /** \brief ������Ч��־ */
    am_bool_t                         valid_flg;

} am_zlg217_gpio_dev_t;

/**
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zlg217_gpio_init (am_zlg217_gpio_dev_t           *p_dev,
                         const am_zlg217_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIO���ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void am_zlg217_gpio_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG217_GPIO_H */

/* end of file */
