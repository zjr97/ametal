/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief MiniPort-Key �����ļ�
 * \sa am_hwconf_miniport_key.c
 *
 * ����ʹ�� Miniport-KEY ʱʹ�ø��ļ��ṩ��ʵ����ʼ������
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  tee, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_key_matrix_gpio.h"
#include "am_input.h"
#include "lpc82x_pin.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_key
 * \copydoc am_hwconf_miniport_key.c
 * @{
 */

/*******************************************************************************
   ��������Ϣ
*******************************************************************************/

static const int __g_key_codes[]    = {
    KEY_0, KEY_1,
    KEY_2, KEY_3
};

/*******************************************************************************
   ����GPIO��������
*******************************************************************************/
static const int __g_key_pins_row[] = {PIO0_6,  PIO0_7};

/*******************************************************************************
   ����GPIO��������
*******************************************************************************/
static const int __g_key_pins_col[] = {PIO0_17, PIO0_23};

/*******************************************************************************
   Public functions
*******************************************************************************/

/* MiniPort-Key ����ʹ��ʵ����ʼ�� */
int am_miniport_key_inst_init (void)
{
    static am_key_matrix_gpio_softimer_t             miniport_key;
    static const am_key_matrix_gpio_softimer_info_t  miniport_key_info = {
        {
            {
                2,                           /* 2�а��� */
                2,                           /* 2�а��� */
                __g_key_codes,               /* ��������Ӧ�ı��� */
                AM_TRUE,                     /* �����͵�ƽ��Ϊ���� */
                AM_KEY_MATRIX_SCAN_MODE_COL, /* ɨ�跽ʽ������ɨ�裨�����������Ÿ��ã� */
            },
            __g_key_pins_row,
            __g_key_pins_col,
        },
        5,                                   /* ɨ��ʱ������5ms */
    };

    return am_key_matrix_gpio_softimer_init(&miniport_key, &miniport_key_info);
}

/**
 * @}
 */

/* end of file */
