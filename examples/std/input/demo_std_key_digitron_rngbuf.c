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
 * \brief �������̣�ʹ�������ʵʱ��ʾ��ǰ���µİ����������¼����浽���λ������У�
 *
 *  ��Ӧ����Ҫʹ�õ���λ����ܣ�ָ�����������ʾ���������ٰ�����λ����ܡ�ͬʱ��
 *  ʹ�õ�4�������� 4��������Ӧ�İ�������̶�Ϊ��KEY_0��KEY_1��KEY_2��KEY_3��
 *  ���и�����ʱ��Ӧȷ��ϵͳ��4�������������Ƕ�Ӧ�İ�������Ϊ��KEY_0 ~ KEY_4
 * 
 *  �����ص�ͨ�����жϻ��������У���ˣ��������ڰ����ص���������Ĵ����ر���
 *  һЩ��ʱ�ϳ��Ĵ�����ʱ�����Խ��������浽���λ������У���main()������������
 *  ����
 * 
 * - ��������
 *   1. ������ں���
 *
 * - ʵ������
 *   1. ����һ����������λ�������ʾ������� 0 ~ 4��
 *   2. ż�����ʱ���������˸���������ʱ������ܲ���˸��
 *
 * \par Դ����
 * \snippet demo_std_key_digitron_rngbuf.c src_std_key_digitron_rngbuf
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-03  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_key_digitron_rngbuf
 * \copydoc demo_std_key_digitron_rngbuf.c
 */

/** [src_std_key_digitron_rngbuf] */
#include "ametal.h"
#include "am_input.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "am_rngbuf.h"
 
static char             __g_key_buf[256];              /* ���� 256 �ֽڵĻ��� */
static struct am_rngbuf __g_key_rngbuf;                /* ���廷�λ�����ʵ��  */
 
static void __digitron_disp_key_code (int id, int code)
{
    am_digitron_disp_char_at(id, 0, '0' + code / 10);  /* ʮλ                */
    am_digitron_disp_char_at(id, 1, '0' + code % 10);  /* ��λ                */
 
    if ((code & 0x01) == 0) {                          /* ż��ʱ�������˸    */
        am_digitron_disp_blink_set(id, 0, AM_TRUE);
        am_digitron_disp_blink_set(id, 1, AM_TRUE);
    } else {
        am_digitron_disp_blink_set(id, 0, AM_FALSE);
        am_digitron_disp_blink_set(id, 1, AM_FALSE);
    }
}
  
/* ����ʵ�ʴ����� */
static void __input_key_proc (int id, int key_code, int key_state)
{
    switch (key_code) {

    case KEY_0:
        __digitron_disp_key_code(id, 0);
        break;

    case KEY_1:
        __digitron_disp_key_code(id, 1);
        break;

    case KEY_2:
        __digitron_disp_key_code(id, 2);
        break;

    case KEY_3:
        __digitron_disp_key_code(id, 3);
        break;

    default :
        break;
    }
}

/* �����ص����� */
static void __input_key_cb (void *p_arg, int key_code, int key_state)
{
    if (am_rngbuf_freebytes(&__g_key_rngbuf) < (sizeof(int) * 2)) {
        
        /* ʣ��ռ䲻�ܴ���°����¼��� �����¼����� */
        AM_DBG_INFO("Buffer full, the key event discard!\r\n");
        
    } else {
        
        am_rngbuf_put(&__g_key_rngbuf, (char *)&key_code, sizeof(int));
        am_rngbuf_put(&__g_key_rngbuf, (char *)&key_state, sizeof(int));
    }
}

/**
 * \brief �������
 */
void demo_std_key_digitron_rngbuf_entry (int32_t id)
{
    static am_input_key_handler_t key_handler;

    /* ��ʼ�������� 8 �� ASCII ���� */
    am_digitron_disp_decode_set(id, am_digitron_seg8_ascii_decode);
    
    /* ��ʼ�ް������£���ʾ -- */
    am_digitron_disp_char_at(id, 0, '-');
    am_digitron_disp_char_at(id, 1, '-');

    am_input_key_handler_register(&key_handler, __input_key_cb, NULL);

    am_rngbuf_init(&__g_key_rngbuf, __g_key_buf, sizeof(__g_key_buf));
	
    AM_FOREVER {

        int key_code;
        int key_state;
        
        /* key_code �� int ����
         *
         * ֻҪ���泬�� 2 �� int ��ռ�ֽ�����key_state �� key_code��
         * �������ڰ����¼� 
         */
        if (am_rngbuf_nbytes(&__g_key_rngbuf) >= (sizeof(int) * 2)) {
            
            am_rngbuf_get(&__g_key_rngbuf, (char *)&key_code, sizeof(int));
            am_rngbuf_get(&__g_key_rngbuf, (char *)&key_state, sizeof(int));
            
            __input_key_proc(id, key_code, key_state);
        }
    }
}
/** [src_std_key_digitron_rngbuf] */

/* end of file */
