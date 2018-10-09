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
 * \brief MiniPort-KEY �û������ļ�
 * \sa am_hwconf_miniport_key.c
 *
 * ����ʹ�� MiniPort-KEY ʱʹ�ø��ļ��ṩ��ʵ����ʼ������
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_input.h"
#include "am_key_matrix_gpio.h"
#include "am_lpc82x.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_key
 * \copydoc am_hwconf_miniport_key.c
 * @{
 */

/** \brief MiniPort-KEY ����������Ϣ */
am_local am_const int __g_miniport_key_codes[] = {
    KEY_0,    /* ���� KEY0 �ļ�ֵ */
    KEY_1,    /* ���� KEY1 �ļ�ֵ */
    KEY_2,    /* ���� KEY2 �ļ�ֵ */
    KEY_3     /* ���� KEY3 �ļ�ֵ */
};

/** \brief MiniPort-KEY ������������ */
am_local am_const int __g_miniport_key_pins_row[] = {
    PIO0_6,    /* �� 0 ������ */
    PIO0_7     /* �� 1 ������ */
};

/** \brief MiniPort-KEY ������������ */
am_local am_const int __g_miniport_key_pins_col[] = {
    PIO0_17,    /* �� 0 ������ */
    PIO0_23     /* �� 1 ������ */
};

/** \brief MiniPort-KEY �豸��Ϣ */
am_local am_const
am_key_matrix_gpio_softimer_info_t __g_miniport_key_devinfo = {
    {
        {
            2,                           /* 2 �а��� */
            2,                           /* 2 �а��� */
            __g_miniport_key_codes,      /* ��������Ӧ�ı��� */
            AM_TRUE,                     /* �����͵�ƽ��Ϊ���� */
            AM_KEY_MATRIX_SCAN_MODE_COL, /* ɨ�跽ʽ������ɨ�裨�����������Ÿ��ã� */
        },
        __g_miniport_key_pins_row,       /* ������������ */
        __g_miniport_key_pins_col,       /* ������������ */
    },
    5,                                   /* ɨ��ʱ������5ms */
};

/** \brief MiniPort-KEY �豸ʵ�� */
am_local am_key_matrix_gpio_softimer_t __g_miniport_key_dev;

/**
 * \brief MiniPort-KEY ʵ����ʼ��������ʹ�ã�
 */
int am_miniport_key_inst_init (void)
{
    return am_key_matrix_gpio_softimer_init(&__g_miniport_key_dev,
                                            &__g_miniport_key_devinfo);
}

/**
 * @}
 */

/* end of file */
