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
 * \brief ������Ϣ����ӿ�
 *
 * \internal
 * \par modification history:
 * - 1.00 15-12-08  tee, first implementation from AWorks
 * \endinternal
 */

#ifndef __AM_KOUTPUT_H
#define __AM_KOUTPUT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name am_koutput
 * @{
 */

/** \brief �������Ϊ kputc �� kputs�����ĵڶ������� */
extern void  *gp_kout_file;

/** 
 * \biref ȫ�ֺ���ָ�룬ָ�����һ���ַ��ĺ���
 *
 * ʹ��am_kprintf����ǰ��Ӧȷ����ָ�뱻��ȷ��ֵ
 */ 
extern int  (*gpfunc_kputc)(const char  c, void *fil);
    
/** 
 * \biref ȫ�ֺ���ָ�룬ָ�����һ���ַ����ĺ���
 *
 * ʹ��am_kprintf����ǰ��Ӧȷ����ָ�뱻��ȷ��ֵ
 */ 
extern int  (*gpfunc_kputs)(const char *s, void *fil);

/** 
 * \biref ������Ϣ���ʹ�õ��ַ�����������ַ����������
 *
 * \param[in] fil     :  �������Ϊ f_putc �� f_puts �����ĵڶ�������
 * \param[in] f_putc  :  ����ָ�룬ָ��ĺ����������һ���ַ�
 * \param[in] f_puts  :  ����ָ�룬ָ��ĺ����������һ���ַ���
 *
 * \return �� 
 */ 
void am_koutput_set (void  *fil,
                     int  (*f_putc) (const char  c, void *fil),
                     int  (*f_puts) (const char *s, void *fil));

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_K_OUTPUT_H */

/* end of file */
