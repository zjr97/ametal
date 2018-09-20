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
 * \brief SC16IS7XX �����ļ�
 * \sa am_hwconf_sc16is7xx.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-13  yrz, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_sc16is7xx.h"
#include "am_zlg116_inst_init.h"
#include "zlg116_pin.h"

/**
 * \addtogroup am_if_src_hwconf_sc16is7xx
 * \copydoc am_hwconf_sc16is7xx.c
 * @{
 */


/** \brief �豸��Ϣ */
am_local am_const am_sc16is7xx_devinfo_t __g_sc16is7xx_devinfo = {
    1,
    0X4C,
    -1,
    -1,
    12000000,
    115200,
    8,
    0,
    1,
    NULL,
    NULL,
    NULL
};

/*******************************************************************************
  SC16IS7XX ʵ����ʼ��
*******************************************************************************/

/** \brief �豸���� */
am_local am_sc16is7xx_dev_t __g_sc16is7xx_dev;

/** \brief ʵ����ʼ�� */
am_sc16is7xx_handle_t am_sc16is7xx_inst_init (void)
{
    /* ��ȡ I2C ʵ����� */
    am_i2c_handle_t i2c_handle =  am_zlg116_i2c1_inst_init();

    return am_sc16is7xx_init (&__g_sc16is7xx_dev, 
                              &__g_sc16is7xx_devinfo,
                              i2c_handle);   
}

/**
 * @}
 */

/* end of file */
