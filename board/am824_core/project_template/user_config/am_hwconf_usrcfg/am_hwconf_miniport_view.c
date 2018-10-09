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
 * \brief MiniPort-View �û������ļ�
 * \sa am_hwconf_miniport_view.c
 *
 * MiniPort-View ���Ե���ʹ�ã�Ҳ���Ժ� MiniPort-595 ����ʹ�ã��Խ�ʡ��������
 *
 * ��ǰ֧�ֵ��÷��У�
 * 1. MiniPort-View                : am_miniport_view_inst_init();
 * 2. MiniPort-View + MiniPort-595 : am_miniport_view_595_inst_init();
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-25  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_input.h"
#include "am_key_matrix_gpio.h"
#include "am_key_matrix_softimer.h"
#include "am_miniport_view_key.h"
#include "am_miniport_view_key_595.h"
#include "am_digitron_scan_gpio.h"
#include "am_digitron_scan_hc595_gpio.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_view
 * \copydoc am_hwconf_miniport_view.c
 * @{
 */

/** \brief ��ʾ���棬��СΪ����ܸ������� 2 */
am_local uint8_t __g_miniport_view_disp_buf[2];

/** \brief ɨ�軺�棬ÿ�ν���ɨ��һ������ܣ���˴�СΪ 1 */
am_local uint8_t __g_miniport_view_scan_buf[1];

/** \brief MiniPort-View ����ܶ�ѡ���� */
am_local am_const int __g_miniport_view_seg_pins[] = {
    PIO0_8,     /* SEG A ���� */
    PIO0_9,     /* SEG B ���� */
    PIO0_10,    /* SEG C ���� */
    PIO0_11,    /* SEG D ���� */
    PIO0_12,    /* SEG E ���� */
    PIO0_13,    /* SEG F ���� */
    PIO0_14,    /* SEG G ���� */
    PIO0_15     /* SEG DP ���� */
};

/** \brief MiniPort-View �����λѡ���� */
am_local am_const int __g_miniport_view_com_pins[] = {
    PIO0_17,    /* COM 0 ���� */
    PIO0_23     /* COM 1 ���� */
};

/*******************************************************************************
  MiniPort-View ����ʹ��
*******************************************************************************/

/** \brief MiniPort-View �豸��Ϣ */
am_local am_const am_digitron_scan_gpio_info_t __g_miniport_view_devinfo = {
    {
        {
            0,                         /* ����ܶ�Ӧ���������ʾ�� ID Ϊ 0 */
        },
        50,                            /* ɨ��Ƶ�ʣ� 50Hz */
        500,                           /* ��˸ʱ����ʱ����500ms */
        500,                           /* ��˸ʱ���ʱ����500ms */
        __g_miniport_view_disp_buf,    /* ��ʾ���� */
        __g_miniport_view_scan_buf,    /* ɨ�軺�� */
    },
    {
        8,                             /* 8 ������� */
        1,                             /* ����������� */
        2,                             /* ��������� */
        AM_DIGITRON_SCAN_MODE_COL,     /* ɨ�跽ʽ������ɨ�� */
        AM_TRUE,                       /* ����͵�ƽ��Ч */
        AM_TRUE,                       /* λѡ�͵�ƽ��Ч */
    },
    __g_miniport_view_seg_pins,        /* ����ܶ�ѡ���� */
    __g_miniport_view_com_pins,        /* �����λѡ���� */
};

/** \brief MiniPort-View �豸ʵ�� */
am_local am_digitron_scan_gpio_dev_t __g_miniport_view_dev;

/**
 * \brief MiniPort-View ʵ����ʼ��������ʹ�ã�
 */
int am_miniport_view_inst_init (void)
{
    return am_digitron_scan_gpio_init(&__g_miniport_view_dev,
                                      &__g_miniport_view_devinfo);
}

/*******************************************************************************
  MiniPort-View �� MiniPort-595 ����ʹ��
*******************************************************************************/

/** \brief MiniPort-595 + MiniPort-View �豸��Ϣ */
am_local am_const
am_digitron_scan_hc595_gpio_info_t __g_miniport_view_595_devinfo = {
    {
        {
            0,                         /* ����ܶ�Ӧ���������ʾ�� ID Ϊ 0 */
        },
        50,                            /* ɨ��Ƶ�ʣ� 50Hz */
        500,                           /* ��˸ʱ����ʱ����500ms */
        500,                           /* ��˸ʱ���ʱ����500ms */
        __g_miniport_view_disp_buf,    /* ��ʾ���� */
        __g_miniport_view_scan_buf,    /* ɨ�軺�� */
    },
    {
        8,                             /* 8 ������� */
        1,                             /* ����������� */
        2,                             /* ��������� */
        AM_DIGITRON_SCAN_MODE_COL,     /* ɨ�跽ʽ������ɨ�� */
        AM_TRUE,                       /* ����͵�ƽ��Ч */
        AM_TRUE,                       /* λѡ�͵�ƽ��Ч */
    },
    __g_miniport_view_com_pins,        /* �����λѡ���� */
};

/** \brief MiniPort-595 + MiniPort-View �豸ʵ�� */
am_local am_digitron_scan_hc595_gpio_dev_t __g_miniport_view_595_dev;

/**
 * \brief MiniPort-595 + MiniPort-View ʵ����ʼ��
 */
int am_miniport_view_595_inst_init (void)
{
    return am_digitron_scan_hc595_gpio_init(&__g_miniport_view_595_dev,
                                            &__g_miniport_view_595_devinfo,
                                             am_miniport_595_inst_init());
}

/**
 * @}
 */

/* end of file */
