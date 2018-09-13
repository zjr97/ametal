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
 * \brief Micro LIB ������
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-17  pea, first implementation.
 * \endinternal
 */
 
#ifdef __MICROLIB

/** \brief ��ֹʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

/*******************************************************************************
  ͷ�ļ�����
*******************************************************************************/
#include "ametal.h"
#include "am_mem.h"
#include "am_microlib_adapter.h"
#include <stdio.h>
#include <errno.h>

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief Micro LIB�������ṹ */
typedef struct am_microlib_adapter {
    const am_microlib_adapter_ops_t *p_ops; /** < \brief �������� */
    void                            *p_arg; /** < \brief ������������ */
} am_microlib_adapter_t;

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief Micro LIB������ */
static am_microlib_adapter_t __g_adapter;

#ifdef __MICROLIB

/** \brief ��׼�����ļ� */
FILE __stdin  = {0};

/** \brief ��׼����ļ� */
FILE __stdout = {1};

/** \brief ��׼�����ļ� */
FILE __stderr = {2};

#endif /* __MICROLIB */

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
int am_microlib_adapter_init (const am_microlib_adapter_ops_t *p_ops,
                              void                            *p_arg)
{
    __g_adapter.p_ops = p_ops;
    __g_adapter.p_arg = p_arg;

    return AM_OK;
}

#endif /* __MICROLIB */

/* end of file */
