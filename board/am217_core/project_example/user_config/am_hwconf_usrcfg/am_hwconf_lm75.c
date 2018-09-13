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
 * \brief LM75 �û������ļ�
 * \sa am_hwconf_lm75.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_temp_lm75.h"
#include "zlg217_pin.h"
#include "am_zlg217_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_lm75
 * \copydoc am_hwconf_lm75.c
 * @{
 */

/** \brief �豸ʵ�� */
static am_temp_lm75_t  __g_temp_lm75;

/** \brief �豸��Ϣ */
static const am_temp_lm75_info_t __g_temp_lm75_info = {
    0x48
};

/** \brief ʵ����ʼ������ */
am_temp_handle_t am_temp_lm75_inst_init (void)
{
    return  am_temp_lm75_init(&__g_temp_lm75,
                              &__g_temp_lm75_info,
                              am_zlg217_i2c1_inst_init());
}

/**
 * @}
 */

/* end of file */
