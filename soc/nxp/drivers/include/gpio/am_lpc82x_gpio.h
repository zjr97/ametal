/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief GPIO����������GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-08  zxl, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC82X_GPIO_H
#define __AM_LPC82X_GPIO_H

#include "ametal.h"
#include "lpc82x_pin.h"
#include "hw/amhw_lpc82x_pint.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * \addtogroup am_lpc82x_if_gpio
 * \copydoc am_lpc82x_gpio.h
 * @{
 */

/**
 * \brief ���ŵĴ�����Ϣ 
 */
struct am_lpc82x_gpio_trigger_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void *p_arg;
};

/**
 * \brief GPIO �豸��Ϣ
 */
typedef struct am_lpc82x_gpio_devinfo {
    
    /** \brief SWM�Ĵ������ַ */
    uint32_t  swm_regbase;
    
    /** \brief GPIO�Ĵ������ַ */
    uint32_t  gpio_regbase;
    
    /** \brief IOCON�Ĵ������ַ */
    uint32_t iocon_regbase;

    /** \brief �����жϼĴ������ַ */
    uint32_t  pint_regbase;

    /** \brief GPIO�����жϺ��б� */
    const int8_t inum_pin[AMHW_LPC82X_PINT_CHAN_NUM];

    /** \brief GPIO֧�ֵ������жϺ����� */
    size_t       pint_count;

    /** \brief ������Ϣӳ�� */
    uint8_t     *p_infomap;

    /** \brief ָ�����Ŵ�����Ϣ��ָ�� */
    struct am_lpc82x_gpio_trigger_info *p_triginfo;
    
    /** \brief ƽ̨��ʼ������ */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
    
} am_lpc82x_gpio_devinfo_t;

/**
 * \brief GPIO�豸ʵ�� 
 */
typedef struct am_lpc82x_gpio_dev {
    
    /** \brief ָ��GPIO�豸��Ϣ��ָ�� */
    const am_lpc82x_gpio_devinfo_t *p_devinfo;

    /** \brief ������Ч��־ */
    am_bool_t                      valid_flg;

    /** \brief ���ſ����ù��ܱ��洢��ǰ�����õĹ��ܱ�� */
    uint8_t                         pin_moved_func[LPC82X_PIN_NUM];

} am_lpc82x_gpio_dev_t;

/**
 * \brief GPIO��ʼ�� 
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ�� 
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ�� 
 *
 * \retval AM_OK : �����ɹ� 
 */
int am_lpc82x_gpio_init (am_lpc82x_gpio_dev_t           *p_dev,
                         const am_lpc82x_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIOȥ��ʼ��
 * \return �� 
 */
void am_lpc82x_gpio_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC82X_GPIO_H */

/* end of file */
