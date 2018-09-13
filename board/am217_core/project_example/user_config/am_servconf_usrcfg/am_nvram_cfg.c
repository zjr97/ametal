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
 * \brief NVRAM ��׼����洢�ζ���
 *
 * ��ʹ��NVRAM��׼�ӿڽ��з���ʧ���ݵĴ洢���ȡʱ���� \sa am_nvram_set() ��
 * \sa am_nvram_get()���ӿڵ���ϸ������� \sa am_nvram.h��
 *
 * �洢�ε�����name�͵�Ԫ��unit���ڸ��ļ��ж��壬�����û�����ϵͳ�����еķ���ʧ
 * �洢�Ρ�
 *
 * \internal
 * \par modification history
 * - 1.00 15-01-19  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_nvram.h"
#include "am_nvram_cfg.h"

/*******************************************************************************
  NVRAM �洢���б�
*******************************************************************************/

/*
 * ϵͳ���еĴ洢�ξ�����������У��洢���б��βӦ�ô���һ���յĴ洢��
 * {NULL, 0, 0, 0, NULL, 0}
 *
 * һ���洢�ΰ����ĸ���Ϣ��
 * ��������Ԫ�ţ��ڴ洢���е���ʼ��ַ�� ���������ֽ�������ʵ�ʴ洢�豸������
 *
 * ʵ�ʴ洢�豸��������ʵ��Ӳ����أ���ʹ��FM24C02�ṩNVRAM�洢������
 * ���ֿ���Ϊ�� "fm24c02" ��ʵ������������Ӧ�����������ļ��ж���ġ�
 * �綨�����¼����洢�Σ�
 *  static const am_nvram_segment_t __g_nvram_segs[] = {
 *      {"ip",         0,  0,  4,   "fm24c02"},
 *      {"ip",         1,  4,  4,   "fm24c02"},
 *      {"temp_limit", 0,  8,  4,   "fm24c02"},
 *      {"system",     0,  12, 50,  "fm24c02"},
 *      {"test",       0,  62, 178, "fm24c02"},
 *      {NULL,         0,   0,   0,      NULL}      // �մ洢�Σ����뱣��
 */
static const am_nvram_segment_t __g_nvram_segs[] = {
    {"microport_eeprom", 0, 0, 256, "microport_eeprom"},
    {NULL,               0, 0, 0,   NULL}         /* �մ洢�Σ����뱣�� */
};

/*******************************************************************************
  NVRAM �����ʼ��
*******************************************************************************/
void am_nvram_inst_init (void)
{
    /* ��ʼ��ʱ��ָ��Ӧ�ó���Ĵ洢�� */
    am_nvram_init(&__g_nvram_segs[0]);
}

/* end of file */
