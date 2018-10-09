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
 * \brief MiniPort-View �� MiniPort-Key���ʹ�ã��Ը���λѡ����
 * \sa am_hwconf_miniport_view_key.c
 *
 * �����Ե���ʹ�ã�Ҳ���Ժ� MiniPort-595 ����ʹ�ã��Խ�ʡ�������š�
 *
 * ��ǰ֧�ֵ��÷��У�
 * 1. MiniPort-Key + MiniPort-View                : am_miniport_view_key_inst_init();
 * 2. MiniPort-595 + MiniPort-View + MiniPort-Key : am_miniport_view_key_595_inst_init();
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-25  tee, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "lpc82x_pin.h"
#include "am_input.h"
#include "am_miniport_view_key.h"
#include "am_miniport_view_key_595.h"
#include "am_hwconf_miniport_595.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_view_key
 * \copydoc am_hwconf_miniport_view_key.c
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
    PIO0_8, PIO0_9, PIO0_10, PIO0_11, PIO0_12, PIO0_13, PIO0_14, PIO0_15
};

/*******************************************************************************
   �����GPIOλ�������Ϣ
*******************************************************************************/
static const int __g_digitron_com_pins[] = {
    PIO0_17, PIO0_23
};

/*******************************************************************************
   ����������Ϣ��am_key_matrix_base_info_t��
*******************************************************************************/

static const int __g_key_codes[]    = {
    KEY_0, KEY_1,
    KEY_2, KEY_3
};


/*******************************************************************************
   ����GPIO��������
*******************************************************************************/
static const int __g_key_pins_row[] = {PIO0_6,  PIO0_7};


/* MiniPort-View �� MiniPort-Key ����ʹ��ʵ����ʼ�� */
int am_miniport_view_key_inst_init (void)
{
    static am_miniport_view_key_dev_t         miniport_view_key;
    static const am_miniport_view_key_info_t  miniport_view_key_info = {
        {
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
        },
        {
            2,                               /* 2�а��� */
            2,                               /* 2�а��� */
            __g_key_codes,                   /* ��������Ӧ�ı��� */
            AM_TRUE,                         /* �����͵�ƽ��Ϊ���� */
            AM_KEY_MATRIX_SCAN_MODE_COL,     /* ɨ�跽ʽ������ɨ�裨�����������Ÿ��ã� */
        },
        __g_key_pins_row,
    };

    return am_miniport_view_key_init(&miniport_view_key,
                                     &miniport_view_key_info);
}

int am_miniport_view_key_595_inst_init (void)
{
    static am_miniport_view_key_595_dev_t         miniport_view_key_595;
    static const am_miniport_view_key_595_info_t  miniport_view_key_595_info = {
        {
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
        },
        {
            2,                               /* 2�а��� */
            2,                               /* 2�а��� */
            __g_key_codes,                   /* ��������Ӧ�ı��� */
            AM_TRUE,                         /* �����͵�ƽ��Ϊ���� */
            AM_KEY_MATRIX_SCAN_MODE_COL,     /* ɨ�跽ʽ������ɨ�裨�����������Ÿ��ã� */
        },
        __g_key_pins_row,
    };

    return am_miniport_view_key_595_init(&miniport_view_key_595,
                                         &miniport_view_key_595_info,
                                          am_miniport_595_inst_init());
}

/**
 * @}
 */

/* end of file */
