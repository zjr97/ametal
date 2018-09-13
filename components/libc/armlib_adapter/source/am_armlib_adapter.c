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
 * \brief ARM LIB ������
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-23  pea, first implementation.
 * \endinternal
 */

#ifndef __MICROLIB

/** \brief ��ֹʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

/** \brief ʹ��heap2 */
#pragma import(__use_realtime_heap)

/*******************************************************************************
  ͷ�ļ�����
*******************************************************************************/
#include "ametal.h"
#include "am_mem.h"
#include "am_armlib_adapter.h"
#include <stdio.h>
#include <errno.h>
#include <rt_sys.h>
#include <rt_locale.h>
#include <rt_misc.h>
#include <time.h>

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief ARM LIB�������ṹ */
typedef struct am_armlib_adapter {
    const am_armlib_adapter_ops_t *p_ops; /** < \brief �������� */
    void                          *p_arg; /** < \brief ������������ */
} am_armlib_adapter_t;

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

static am_armlib_adapter_t __g_adapter; /**< \brief ARM LIB������ */

const char __stdin_name[]  = ":tt";     /**< \brief ����stdin���ļ��� */
const char __stdout_name[] = ":tt";     /**< \brief ����stdout���ļ��� */
const char __stderr_name[] = ":tt";     /**< \brief ����stderr���ļ��� */

/*******************************************************************************
  ���غ�������
*******************************************************************************/

/** 
 * \brief ���һ���ַ�
 *
 * \param[in] ch       ��Ҫ������ַ�
 * \param[in] p_stream ָ��FILE�����ָ��
 *
 * \return ���û�з������󣬷��ر�������ַ������򷵻�EOF
 */
int fputc (int ch, FILE *p_stream) 
{
    if ((p_stream->handle >= 0) && (p_stream->handle < 3)) {
        if(__g_adapter.p_ops && __g_adapter.p_ops->pfn_putc) {
            return __g_adapter.p_ops->pfn_putc(__g_adapter.p_arg, (char)ch);
        }
    }

    return EOF;
}

/** 
 * \brief ����һ���ַ�
 *
 * \param[in] p_stream ָ��FILE�����ָ��
 *
 * \return ���û�з������󣬷���������ַ������򷵻�EOF
 */
int fgetc (FILE *p_stream)
{        
    if ((p_stream->handle >= 0) && (p_stream->handle < 3)) {
        if (__g_adapter.p_ops && __g_adapter.p_ops->pfn_getc) {
            return __g_adapter.p_ops->pfn_getc(__g_adapter.p_arg);
        }
    }
        
    return EOF;
};

/** 
 * \brief ���ϴζ�ȡ���ַ����ص�FILE����
 *
 * \param[in] p_stream ָ��FILE�����ָ��
 *
 * \retval 0   �ɹ�
 * \retval EOF ʧ��
 */
int __backspace (FILE *p_stream)
{
    return EOF;
}

/** 
 * \brief ARM LIB�˳����������ɷ���
 *
 * \param[in] return_code ���øú����ķ���ֵ
 *
 * \return ��
 */
void _sys_exit (int return_code)
{
    AM_FOREVER;
}

/** 
 * \brief ����ʧ�ܴ�����
 *
 * \param[in] p_expr ���ʽ
 * \param[in] p_file �ļ���
 * \param[in] line   �к�
 *
 * \return ��
 */
void __aeabi_assert (const char *p_expr, const char *p_file, int line)
{
    printf("*** assertion failed: %s, %s, %d\r\n", p_expr, p_file, line);

    abort();
}

/** 
 * \brief ���ļ�
 *
 * \param[in] p_name   �ļ���
 * \param[in] openmode ��ģʽ
 *
 * \return �ɹ������ļ������ʧ�ܷ���-1
 */
FILEHANDLE _sys_open (const char *p_name, int openmode)
{
    return 1;
}

/** 
 * \brief �ر��ļ�
 *
 * \param[in] fh �ļ����
 *
 * \return �ɹ�����0��ʧ�ܷ��ظ�ֵ
 */
int _sys_close (FILEHANDLE fh)
{
    return -1;
}

/** 
 * \brief д�ļ�
 *
 * \param[in] fh    �ļ����
 * \param[in] p_buf ��������ַ
 * \param[in] len   ��д���ֽ���
 * \param[in] mode  ģʽ(��Ϊ��ʷԭ�������������)
 *
 * \return �ɹ�����0��ʧ�ܷ��ظ�ֵ�Ҵ�СΪд��ʧ�ܵ��ֽ���
 */
int _sys_write (FILEHANDLE           fh, 
                const unsigned char *p_buf,
                unsigned             len, 
                int                  mode)
{
    return -1;
}

/** 
 * \brief ���ļ�
 *
 * \param[in]  fh    �ļ����
 * \param[out] p_buf ��������ַ
 * \param[in]  len   ��д���ֽ���
 * \param[in]  mode  ģʽ(��Ϊ��ʷԭ�������������)
 *
 * \return �ɹ�����0������ȡ���ļ�ĩβʱ����EOF
 *         ֻ�ɹ���ȡ��������ʱ������δ��ȡ���ֽ���
 *         ���ļ�ĩβ��ʼ��ȡ��ֻ�ɹ���ȡ��������ʱ������δ��ȡ���ֽ����ҽ����λ��λ
 *         ʧ�ܷ���-1
 */
int _sys_read (FILEHANDLE     fh, 
               unsigned char *p_buf,
               unsigned       len, 
               int            mode)
{
    return -1;
}

/** 
 * \brief ���ն����һ���ַ�
 *
 * \param[in] ch ��������ַ�
 *
 * \return ��
 */
void _ttywrch (int ch)
{
    fputc(ch, stdout);
}

/** 
 * \brief �ж�һ���ļ�����Ƿ�Ϊ�ն�
 *
 * \param[in] fh �ļ����
 *
 * \return ���ն˷��ط�0�������ն˷���0
 */
int _sys_istty (FILEHANDLE fh)
{
    return 0;
}

/** 
 * \brief �ƶ��ļ�ָ��
 *
 * \param[in] fh  �ļ����
 * \param[in] pos ���ƶ�����λ��(���0��ַƫ��)
 *
 * \return �ɹ�����>=0, ʧ�ܷ���<0
 */
int _sys_seek (FILEHANDLE fh, long pos)
{
    return -1;
}

/** 
 * \brief Flush����������
 *
 * \param[in] fh �ļ����
 *
 * \return �ɹ�����>=0, ʧ�ܷ���<0
 */
int _sys_ensure(FILEHANDLE fh)
{
    return -1;
}

/** 
 * \brief �����ļ�����
 *
 * \param[in] fh �ļ����
 *
 * \return �ɹ������ļ�����, ʧ�ܷ���<0
 */
long _sys_flen (FILEHANDLE fh)
{
    return -1;
}

/** 
 * \brief ��ȡʱ��
 *
 * \param ��
 *
 * \return ʱ����
 */
clock_t clock (void)
{
    return (clock_t)-1;
}

/** 
 * \brief ʱ�ӳ�ʼ��
 */
void _clock_init (void)
{
    /* VOID */
}

/**
 * \brief ����һ���ڴ�ռ䣨�ڴ�ռ�ᱻ��ʼ��Ϊ0��
 *
 * \param[in] nmemb Ԫ�ظ���
 * \param[in] size  һ��Ԫ�صĴ�С�������ڴ�ռ�Ĵ�С��Ϊ nmemb * size
 *
 * \return ����ռ���׵�ַ��NULL��������ʧ��
 *
 * \note ������ڴ�ռ�ᱻ��ʼ��Ϊ0
 */
void *calloc (size_t nmemb, size_t size)
{
    return am_mem_calloc(nmemb, size);
}

/**
 * \brief �ͷ��ѷ�����ڴ�ռ�
 *
 * \param[in] ptr �ѷ�����ڴ�ռ���׵�ַ
 *
 * \return ��
 */
void free (void *ptr)
{
    am_mem_free(ptr);
}

/**
 * \brief ����һ���ڴ�ռ�
 *
 * \param[in] size ����ռ�Ĵ�С
 *
 * \return ����ռ���׵�ַ��NULL��������ʧ��
 */
void *malloc (size_t size)
{
    return am_mem_alloc(size);
}

/**
 * \brief ��̬�ڴ�������ı��ѷ���ռ�Ĵ�С
 *
 * \param[in] ptr  �ѷ���ռ���׵�ַ
 * \param[in] size ���·���Ŀռ�Ĵ�С
 *
 * \return ���·���ռ���׵�ַ��NULL��������ʧ��
 *
 * \note �������жϵ�ǰ��ָ���Ƿ����㹻�������ռ䣬����У����� ptr ָ���ַ��
 * �ռ䣬ֱ�ӽ�ptr��ֵ���ء�����ռ䲻�����Ȱ���sizeָ���Ĵ�С����ռ䣬��
 * ԭ�����ݴ�ͷ��β�������·�����ڴ����򣬶����ͷ�ԭ��ptr��ָ�ڴ�����ԭ��
 * ָ���Զ��ͷţ�����Ҫ am_memheap_free()����ͬʱ�����·�����ڴ�������׵�ַ��
 */
void *realloc (void *ptr, size_t size)
{
    return am_mem_realloc(ptr, size);
}

/*******************************************************************************
  �ⲿ��������
*******************************************************************************/

/**
 * \brief ��������ʼ��
 *
 * \param[in] p_ops ��������
 * \param[in] p_arg ������������
 *
 * \return AM_OK
 */
int am_armlib_adapter_init (const am_armlib_adapter_ops_t *p_ops,
                            void                          *p_arg)
{
    __g_adapter.p_ops = p_ops;
    __g_adapter.p_arg = p_arg;

    return AM_OK;
}

#endif /* __MICROLIB */

/* end of file */
