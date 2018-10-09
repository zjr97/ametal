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
 * \brief MiniPort-View �� MiniPort-KEY ���ʹ�ã��Ը���λѡ����
 * \sa am_hwconf_miniport_view_key.c
 *
 * ��ǰ֧�ֵ��÷��У�
 * 1. MiniPort-KEY + MiniPort-View                : am_miniport_view_key_inst_init();
 * 2. MiniPort-595 + MiniPort-View + MiniPort-KEY : am_miniport_view_key_595_inst_init();
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-25  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_input.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"
#include "am_miniport_view_key.h"
#include "am_miniport_view_key_595.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_view_key
 * \copydoc am_hwconf_miniport_view_key.c
 * @{
 */

/** \brief ��ʾ���棬��СΪ����ܸ������� 2 */
am_local uint8_t __g_miniport_view_key_disp_buf[2];

/** \brief ɨ�軺�棬ÿ�ν���ɨ��һ������ܣ���˴�СΪ 1 */
am_local uint8_t __g_miniport_view_key_scan_buf[1];

/** \brief MiniPort-View ����ܶ�ѡ���� */
am_local am_const int __g_miniport_view_key_seg_pins[8] = {
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
am_local am_const int __g_miniport_view_key_com_pins[] = {
    PIO0_17,    /* COM 0 ���� */
    PIO0_23     /* COM 1 ���� */
};

/** \brief MiniPort-KEY ����������Ϣ */
am_local am_const int __g_miniport_view_key_codes[]    = {
    KEY_0,    /* ���� KEY0 �ļ�ֵ */
    KEY_1,    /* ���� KEY1 �ļ�ֵ */
    KEY_2,    /* ���� KEY2 �ļ�ֵ */
    KEY_3     /* ���� KEY3 �ļ�ֵ */
};

/** \brief MiniPort-KEY ������������ */
am_local am_const int __g_miniport_view_pins_row[] = {
    PIO0_6,    /* �� 0 ������ */
    PIO0_7     /* �� 1 ������ */
};

/*******************************************************************************
  MiniPort-KEY �� MiniPort-View ����ʹ��
*******************************************************************************/

/** \brief MiniPort-KEY + MiniPort-View �豸��Ϣ */
am_local am_const am_miniport_view_key_info_t __g_miniport_view_key_devinfo = {
    {
        {
            {
                0,                          /* ����ܶ�Ӧ���������ʾ�� ID Ϊ 0 */
            },
            50,                             /* ɨ��Ƶ�ʣ�50Hz */
            500,                            /* ��˸ʱ����ʱ����500ms */
            500,                            /* ��˸ʱ���ʱ����500ms */
            __g_miniport_view_key_disp_buf, /* ��ʾ���� */
            __g_miniport_view_key_scan_buf, /* ɨ�軺�� */
        },
        {
            8,                              /* 8 ������� */
            1,                              /* ����������� */
            2,                              /* ��������� */
            AM_DIGITRON_SCAN_MODE_COL,      /* ɨ�跽ʽ������ɨ�� */
            AM_TRUE,                        /* ����͵�ƽ��Ч */
            AM_TRUE,                        /* λѡ�͵�ƽ��Ч */
        },
        __g_miniport_view_key_seg_pins,     /* ����ܶ�ѡ���� */
        __g_miniport_view_key_com_pins,     /* �����λѡ���� */
    },
    {
        2,                                  /* 2 �а��� */
        2,                                  /* 2 �а��� */
        __g_miniport_view_key_codes,        /* ����������Ϣ */
        AM_TRUE,                            /* ��������Ϊ�͵�ƽ */
        AM_KEY_MATRIX_SCAN_MODE_COL,        /* ɨ�跽ʽ������ɨ�裨�����������Ÿ��ã� */
    },
    __g_miniport_view_pins_row,             /* ������������ */
};

/** \brief MiniPort-KEY + MiniPort-View �豸ʵ�� */
am_local am_miniport_view_key_dev_t __g_miniport_view_key_dev;

/**
 * \brief MiniPort-KEY + MiniPort-View ʵ����ʼ��
 */
int am_miniport_view_key_inst_init (void)
{
    return am_miniport_view_key_init(&__g_miniport_view_key_dev,
                                     &__g_miniport_view_key_devinfo);
}


/*******************************************************************************
  MiniPort-595 �� MiniPort-KEY �� MiniPort-View ����ʹ��
*******************************************************************************/

/** \brief MiniPort-595 + MiniPort-KEY + MiniPort-View �豸��Ϣ */
am_local am_const
am_miniport_view_key_595_info_t __g_miniport_view_key_595_devinfo = {
    {
        {
            {
                0,                          /* ����ܶ�Ӧ���������ʾ�� ID Ϊ 0 */
            },
            50,                             /* ɨ��Ƶ�ʣ� 50Hz */
            500,                            /* ��˸ʱ����ʱ����500ms */
            500,                            /* ��˸ʱ���ʱ����500ms */
            __g_miniport_view_key_disp_buf, /* ��ʾ���� */
            __g_miniport_view_key_scan_buf, /* ɨ�軺�� */
        },
        {
            8,                              /* 8 ������� */
            1,                              /* ����������� */
            2,                              /* ��������� */
            AM_DIGITRON_SCAN_MODE_COL,      /* ɨ�跽ʽ������ɨ�� */
            AM_TRUE,                        /* ����͵�ƽ��Ч */
            AM_TRUE,                        /* λѡ�͵�ƽ��Ч */
        },
        __g_miniport_view_key_com_pins,     /* �����λѡ���� */
    },
    {
        2,                                  /* 2 �а��� */
        2,                                  /* 2 �а��� */
        __g_miniport_view_key_codes,        /* ����������Ϣ */
        AM_TRUE,                            /* ��������Ϊ�͵�ƽ */
        AM_KEY_MATRIX_SCAN_MODE_COL,        /* ɨ�跽ʽ������ɨ�裨�����������Ÿ��ã� */
    },
    __g_miniport_view_pins_row,             /* ������������ */
};

/** \brief MiniPort-595 + MiniPort-KEY + MiniPort-View �豸ʵ�� */
am_local am_miniport_view_key_595_dev_t __g_miniport_view_key_595_dev;

/**
 * \brief MiniPort-595 + MiniPort-KEY + MiniPort-View ʵ����ʼ��
 */
int am_miniport_view_key_595_inst_init (void)
{
    return am_miniport_view_key_595_init(&__g_miniport_view_key_595_dev,
                                         &__g_miniport_view_key_595_devinfo,
                                          am_miniport_595_inst_init());
}

/**
 * @}
 */

/* end of file */
