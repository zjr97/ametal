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
 * \brief MiniPort-View �����ļ�
 * \sa am_hwconf_miniport_view.c
 *
 * �����Ե���ʹ�ã�Ҳ���Ժ� MiniPort-595 ����ʹ�ã��Խ�ʡ�������š�
 *
 * ��ǰ֧�ֵ��÷��У�
 * 1. MiniPort-View                : am_miniport_view_inst_init();
 * 2. MiniPort-View + MiniPort-595 : am_miniport_view_595_inst_init();
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-25  tee, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_kl26_inst_init.h"
#include "am_key_matrix_gpio.h"
#include "am_key_matrix_softimer.h"
#include "am_digitron_scan_gpio.h"
#include "am_digitron_scan_hc595_gpio.h"
#include "am_miniport_view_key.h"
#include "am_input.h"
#include "am_miniport_view_key_595.h"
#include "../../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_view
 * \copydoc am_hwconf_miniport_view.c
 * @{
 */

/*******************************************************************************
   �����ɨ�������Ϣ ��am_digitron_scan_devinfo_t���ͣ�
*******************************************************************************/

/* ��ʾ���棬8������ܣ�����Ϊuint8_t�������СΪ����ܸ�������2 */
static uint8_t __g_disp_buf[2];

/* ɨ�軺�棬8������ܣ�����Ϊuint8_t��ÿ�ν���ɨ��һ������ܣ���˴�СΪ1 */
static uint8_t __g_scan_buf[1];

/*******************************************************************************
   �����GPIO���������Ϣ
*******************************************************************************/
static const int __g_digitron_seg_pins[] = {
    PIOB_1, PIOB_0, PIOB_17, PIOD_5, PIOB_3, PIOB_16, PIOD_4, PIOB_2
};

/*******************************************************************************
   �����GPIOλ�������Ϣ
*******************************************************************************/
static const int __g_digitron_com_pins[] = {
    PIOE_21, PIOE_20
};

/*******************************************************************************
   Public functions
*******************************************************************************/

/* MiniPort-View ����ʹ��ʵ����ʼ�� */
int am_miniport_view_inst_init (void)
{
    static am_digitron_scan_gpio_dev_t         miniport_view;
    static const am_digitron_scan_gpio_info_t  miniport_view_info = {
        {
            {
                0,                       /* ����ܶ�Ӧ���������ʾ��IDΪ0 */
            },
            50,                          /* ɨ��Ƶ�ʣ� 50Hz */
            500,                         /* ��˸ʱ����ʱ����500ms */
            500,                         /* ��˸ʱ���ʱ����500ms */
            __g_disp_buf,                /* ��ʾ���� */
            __g_scan_buf,                /* ɨ�軺�� */
        },
        {
            8,                           /* 8������� */
            1,                           /* ����������� */
            2,                           /* ��������� */
            AM_DIGITRON_SCAN_MODE_COL,   /* ɨ�跽ʽ������ɨ�� */
            AM_TRUE,                     /* ����͵�ƽ��Ч */
            AM_TRUE,                     /* λѡ�͵�ƽ��Ч */
        },
        __g_digitron_seg_pins,
        __g_digitron_com_pins,
    };

    return am_digitron_scan_gpio_init(&miniport_view, &miniport_view_info);
}

/******************************************************************************/

/* MiniPort-View ��  MiniPort-595 ����ʹ��ʵ����ʼ�� */
int am_miniport_view_595_inst_init (void)
{
    static am_digitron_scan_hc595_gpio_dev_t         miniport_view_595;
    static const am_digitron_scan_hc595_gpio_info_t  miniport_view_595_info = {
        {
            {
                0,                       /* ����ܶ�Ӧ���������ʾ��IDΪ0 */
            },
            50,                          /* ɨ��Ƶ�ʣ� 50Hz */
            500,                         /* ��˸ʱ����ʱ����500ms */
            500,                         /* ��˸ʱ���ʱ����500ms */
            __g_disp_buf,                /* ��ʾ���� */
            __g_scan_buf,                /* ɨ�軺�� */
        },
        {
            8,                           /* 8������� */
            1,                           /* ����������� */
            2,                           /* ��������� */
            AM_DIGITRON_SCAN_MODE_COL,   /* ɨ�跽ʽ������ɨ�� */
            AM_TRUE,                     /* ����͵�ƽ��Ч */
            AM_TRUE,                     /* λѡ�͵�ƽ��Ч */
        },
        __g_digitron_com_pins,
    };

    return am_digitron_scan_hc595_gpio_init(&miniport_view_595,
                                            &miniport_view_595_info,
                                            am_miniport_595_inst_init());
}

/**
 * @}
 */

/* end of file */
