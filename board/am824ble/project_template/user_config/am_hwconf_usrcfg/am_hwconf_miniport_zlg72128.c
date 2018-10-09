/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief MiniPort-ZLG72128 �û������ļ�
 * \sa am_hwconf_miniport_zlg72128.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_input.h"
#include "am_zlg72128_std.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_zlg72128
 * \copydoc am_hwconf_miniport_zlg72128.c
 * @{
 */

/** \brief MiniPort-ZLG72128 ����������Ϣ */
am_local am_const int __g_miniport_zlg72128_codes[] = {
    KEY_0,    /* ���� KEY0 �ļ�ֵ */
    KEY_1,    /* ���� KEY1 �ļ�ֵ */
    KEY_2,    /* ���� KEY2 �ļ�ֵ */
    KEY_3     /* ���� KEY3 �ļ�ֵ */
};

/** \brief MiniPort-ZLG72128 �豸��Ϣ */
am_local am_const am_zlg72128_std_devinfo_t __g_miniport_zlg72128_devinfo = {
    {
        PIO0_6,                     /* ��λ���� */
        AM_TRUE,                    /* ʹ���ж����� */
        PIO0_1,                     /* �ж����� */
        5                           /* ��ѯʱ������ʹ���ж�����ʱ����ֵ������ */
    },
    {
        0                           /* �������ʾ���ı�� */
    },
    500,                            /* һ����˸�����ڣ�������ʱ��Ϊ 500ms */
    500,                            /* һ����˸�����ڣ�Ϩ���ʱ��Ϊ 500ms */
    AM_ZLG72128_STD_KEY_ROW_0 | AM_ZLG72128_STD_KEY_ROW_3, /* ʵ��ʹ�õ��б�־ */
    AM_ZLG72128_STD_KEY_COL_0 | AM_ZLG72128_STD_KEY_COL_1, /* ʵ��ʹ�õ��б�־ */
    __g_miniport_zlg72128_codes,    /* ����������Ϣ */
    2                               /* ����ܸ���Ϊ 2 */
};

/** \brief MiniPort-ZLG72128 �豸ʵ�� */
am_local am_zlg72128_std_dev_t __g_miniport_zlg72128_dev;

/**
 * \brief MiniPort-ZLG72128 ʵ����ʼ��
 */
int am_miniport_zlg72128_inst_init (void)
{
    return am_zlg72128_std_init(&__g_miniport_zlg72128_dev,
                                &__g_miniport_zlg72128_devinfo,
                                 am_lpc82x_i2c2_inst_init());
}

/**
 * @}
 */

/* end of file */
