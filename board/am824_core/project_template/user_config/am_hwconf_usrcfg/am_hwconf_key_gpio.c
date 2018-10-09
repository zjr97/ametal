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
 * \brief �����û������ļ���GPIO ������
 * \sa am_hwconf_key_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_input.h"
#include "am_key_gpio.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_key_gpio
 * \copydoc am_hwconf_key_gpio.c
 * @{
 */

/** \brief �������ź� */
am_local am_const int __g_key_pins[] = {
    PIO0_1    /* KEY/RES �������� */
};

/** \brief �������� */
am_local am_const int __g_key_codes[] = {
    KEY_KP0    /* KEY/RES �������� */
};

/** \brief �����豸��Ϣ */
am_local am_const am_key_gpio_info_t __g_key_gpio_devinfo = {
    __g_key_pins,               /* �������ź� */
    __g_key_codes,              /* ����������Ӧ�ı��루�ϱ��� */
    AM_NELEMENTS(__g_key_pins), /* ������Ŀ */
    AM_TRUE,                    /* �Ƿ�͵�ƽ�������Ϊ�͵�ƽ�� */
    10                          /* ����ɨ��ʱ������һ��Ϊ 10ms */
};

/** \brief �����豸ʵ�� */
am_local am_key_gpio_t __g_key_gpio_dev;

/**
 * \brief ����ʵ����ʼ����GPIO ������
 */
int am_key_gpio_inst_init (void)
{
    return am_key_gpio_init(&__g_key_gpio_dev, &__g_key_gpio_devinfo);
}

/**
 * @}
 */

/* end of file */
