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
 * \brief �����ʵʱ��ʾ�¶�����
 *
 * ��Ӧ����Ҫʹ�õ���λ����ܣ�����ʾ�¶��������֣���ָ�����������ʾ����������
 * ������λ�����
 *
 * - ��������
 *   1. ������ں���������ָ�����������ʾ����ź��¶ȴ��������
 *
 * - ʵ������
 *   1. ���Կ����������ʾ��ǰ�¶�
 *
 * \par Դ����
 * \snippet demo_std_digitron_temp.c src_std_digitron_temp
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_digitron_temp
 * \copydoc demo_std_digitron_temp.c
 */

/** [src_std_digitron_temp] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "am_temp.h"

/**
 * \brief ������� 
 */
void demo_std_digitron_temp_entry (int32_t id, am_temp_handle_t temp_handle)
{
    int32_t temp;

    /* ��ʼ��������8��ASCII���� */
    am_digitron_disp_decode_set(id, am_digitron_seg8_ascii_decode);

    /* ��ȡ�¶ȣ�������1000��,����ֻ����������ܣ�ֻ��ʾ�������� */
    am_temp_read(temp_handle, &temp);

    am_digitron_disp_char_at(id, 1, '0' + (temp / 1000) % 10);       /* ��λ�������ʾ�ַ� */
    am_digitron_disp_char_at(id, 0, '0' + (temp / 1000) / 10 % 10);  /* ʮλ�������ʾ�ַ� */

    while(1) {

        am_mdelay(500);

        /* ��ȡ�¶ȣ������� 1000 ��,����ֻ����������ܣ�ֻ��ʾ�������� */
        am_temp_read(temp_handle, &temp);

        am_digitron_disp_char_at(id, 1, '0' + (temp / 1000) % 10);       /* ��λ�������ʾ�ַ� */
        am_digitron_disp_char_at(id, 0, '0' + (temp / 1000) / 10 % 10);  /* ʮλ�������ʾ�ַ� */
    }
}
/** [src_std_digitron_temp] */

/* end of file */
