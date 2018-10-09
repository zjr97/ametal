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
 * \brief FLASH �ڴ�ģ��Ӳ����ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

#include "hw/amhw_fsl_ftfa.h"
#include "ametal.h"

/**
 *  brief amhw_fsl_ftfa_cmd_launch������������ݿ���
 *  ��RAM��Ҫ�Ŀռ��С ���԰��� 16bit �ƣ�
 */
#define CMD_LAUNCH_FUNC_SIZE    (40)

static uint16_t amhw_fsl_ftfa_cmd_launch_ram_context[CMD_LAUNCH_FUNC_SIZE];

static uint32_t (* amhw_fsl_ftfa_cmd_launch_ram) (amhw_fsl_ftfa_t *);

/**
 *  \brief ִ��flash����
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
static uint32_t amhw_fsl_ftfa_cmd_launch (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    /** �ȴ�֮ǰ�Ĳ�����ɻ��߳�ʱ */
    while (!(p_hw_ftfa->fstat & AMHW_FSL_FTFA_CCIF)) {
        ;
    }

    /** ��������־ */
    p_hw_ftfa->fstat = AMHW_FSL_FTFA_FPVIOL  |
                       AMHW_FSL_FTFA_ACCERR  |
                       AMHW_FSL_FTFA_RDCOLERR;

    p_hw_ftfa->fstat = AMHW_FSL_FTFA_CCIF;

    /** ������� */
    while (!(p_hw_ftfa->fstat & AMHW_FSL_FTFA_CCIF)) {
        ;
    }

    return p_hw_ftfa->fstat & (~AMHW_FSL_FTFA_CCIF);
}

/**
 *  \brief ��amhw_fsl_ftfa_cmd_launch ����������RAM��
 *
 *  \return ��
 *
 *  \note FLASH���������޸�flashʱ������Ҫ��RAM������
 */
void amhw_fsl_ftfa_func_copy (void)
{
    uint16_t *p;
    uint32_t i;

    /** ��������ַ����Ϊ2�ֽڶ��룬��ǿ��ת��Ϊ (uint16_t *) */
    p = (uint16_t *)(((uint32_t)&amhw_fsl_ftfa_cmd_launch) & (~0x1));

    /** ��������ָ�����RAM�� */
    for (i = 0; i < CMD_LAUNCH_FUNC_SIZE; i++) {
        amhw_fsl_ftfa_cmd_launch_ram_context[i] = *p;
        p++;
    }

    /** ��RAM�к�������ʼ��ַ�� amhw_fsl_ftfa_cmd_launch_ram
     *  ����Cortex M0+ ֻ֧�� thumbָ��
     *  ���� amhw_fsl_ftfa_cmd_launch_ram �����λΪ 1
     */
    amhw_fsl_ftfa_cmd_launch_ram
        = (uint32_t (*) (amhw_fsl_ftfa_t *))       /** ǿ��ת��Ϊ����ָ�� */
          (
           (uint32_t)                          /** ǿ��ת��Ϊ���ͱ������� */
           amhw_fsl_ftfa_cmd_launch_ram_context | 0x01
          );
}
/**
 *  \brief �����ж������Ƿ�Ϊȫ1����
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param start_addr ������ʼ��ַ
 *  \param n_words ��(32bit)�ĸ���
 *  \param margin ����ѡ��
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_1s_read (amhw_fsl_ftfa_t *p_hw_ftfa,
                                 uint32_t          start_addr,
                                 uint16_t          n_words,
                                 uint8_t           margin)
{
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_rd1sec;
    p_hw_ftfa->fccob1 = (start_addr >> 16) & 0xff;
    p_hw_ftfa->fccob2 = (start_addr >> 8 ) & 0xff;
    p_hw_ftfa->fccob3 = (start_addr >> 0 ) & 0xff;
    p_hw_ftfa->fccob4 = (n_words    >> 8 ) & 0xff;
    p_hw_ftfa->fccob5 = (n_words    >> 0 ) & 0xff;
    p_hw_ftfa->fccob6 = margin;

    return amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);
}

/**
 *  \brief ��(32bit)��̽����ȷ�����ж�
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param addr Ҫ�жϵĵ�ַ
 *  \param context ��������������
 *  \param margin ����ѡ��
 *          #��ѡ 0x01, 0x02
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_program_check (amhw_fsl_ftfa_t *p_hw_ftfa,
                                       uint32_t          addr,
                                       uint32_t          context,
                                       uint8_t           margin)
{
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_pgmchk;
    p_hw_ftfa->fccob1 = (addr >> 16) & 0xff;
    p_hw_ftfa->fccob2 = (addr >> 8 ) & 0xff;
    p_hw_ftfa->fccob3 = (addr >> 0 ) & 0xff;
    p_hw_ftfa->fccob4 = margin;
    p_hw_ftfa->fccob8 = (context >> 24) & 0xff;
    p_hw_ftfa->fccob9 = (context >> 16) & 0xff;
    p_hw_ftfa->fccoba = (context >> 8 ) & 0xff;
    p_hw_ftfa->fccobb = (context >> 0 ) & 0xff;

    return amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);
}

/**
 *  \brief ��ȡ���⹦����FLASH
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \parma addr flash��ַ
 *  \param p_context ָ�򻺴��ȡ���ݵĻ�������ָ��
 *  \param resrc_select ��Դѡ��
 *          - 0x00 Program Flash 0 IFR
 *          - 0x01 Version ID
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����: ��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_resrc_read (amhw_fsl_ftfa_t *p_hw_ftfa,
                                    uint32_t          addr,
                                    uint32_t         *p_context,
                                    uint8_t           resrc_select)
{
    uint8_t status;
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_rdrsrc;
    p_hw_ftfa->fccob1 = (addr >> 16) & 0xff;
    p_hw_ftfa->fccob2 = (addr >> 8 ) & 0xff;
    p_hw_ftfa->fccob3 = (addr >> 0 ) & 0xff;
    p_hw_ftfa->fccob8 = resrc_select;

    status = amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);

    if (status != 0) {
        return status;
    }

    *p_context = 0;
    *p_context |= p_hw_ftfa->fccob4 << 24;
    *p_context |= p_hw_ftfa->fccob5 << 16;
    *p_context |= p_hw_ftfa->fccob6 << 8;
    *p_context |= p_hw_ftfa->fccob7 << 0;
    return status;
}

/**
 *  \brief ��һ���ֱ��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param addr FLASH�ֵ�ַ
 *  \param word д���ֵ�����
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_word_program (amhw_fsl_ftfa_t *p_hw_ftfa,
                                      uint32_t          addr,
                                      uint32_t          word)
{
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_pgm4;
    p_hw_ftfa->fccob1 = (addr >> 16) & 0xff;
    p_hw_ftfa->fccob2 = (addr >> 8 ) & 0xff;
    p_hw_ftfa->fccob3 = (addr >> 0 ) & 0xff;

    p_hw_ftfa->fccob4 = (word >> 24) & 0xff;
    p_hw_ftfa->fccob5 = (word >> 16) & 0xff;
    p_hw_ftfa->fccob6 = (word >> 8 ) & 0xff;
    p_hw_ftfa->fccob7 = (word >> 0 ) & 0xff;

    return amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);
}

/**
 *  \brief ��������
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param addr ������ʼ��ַ
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_sector_erase (amhw_fsl_ftfa_t *p_hw_ftfa,
                                      uint32_t          addr)
{
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_ersscr;
    p_hw_ftfa->fccob1 = (addr >> 16) & 0xff;
    p_hw_ftfa->fccob2 = (addr >> 8 ) & 0xff;
    p_hw_ftfa->fccob3 = (addr >> 0 ) & 0xff;

    return amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);
}

/**
 *  \brief �ж����������Ƿ�Ϊȫ1
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param margin ����ѡ��
 *          ��ѡ���� 0x0 - 0x2
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_all_blocks_1s_read (amhw_fsl_ftfa_t *p_hw_ftfa,
                                            uint8_t           margin)
{
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_rd1all;
    p_hw_ftfa->fccob1 = margin;

    return amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);
}

/**
 *  \brief ��ȡ64�ֽڱ������е�һ����
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param index ������� 0x00-0x0f
 *  \param p_value ָ���ȡ��������ָ��
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_once_read (amhw_fsl_ftfa_t *p_hw_ftfa,
                                   uint8_t           index,
                                   uint32_t         *p_value)
{
    uint8_t status;
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_rdonce;
    p_hw_ftfa->fccob1 = index;

    status = amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);

    if (0 != status) {
        return status;
    }

    *p_value = 0;
    *p_value |= p_hw_ftfa->fccob4 >> 24;
    *p_value |= p_hw_ftfa->fccob5 >> 16;
    *p_value |= p_hw_ftfa->fccob6 >> 8;
    *p_value |= p_hw_ftfa->fccob7 >> 0;

    return status;
}

/**
 *  \brief �Ա�����һ���ֽ���һ���Ա��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param index ������� 0x00-0x0f
 *  \param value ϣ��д���ֵ
 *
 *  \return 0 ��ʾ����ɹ�ִ�У����� ��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_once_program (amhw_fsl_ftfa_t *p_hw_ftfa,
                                      uint8_t           index,
                                      uint32_t          value)
{
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_pgmonce;
    p_hw_ftfa->fccob1 = index;

    p_hw_ftfa->fccob4 = (value >> 24) & 0xff;
    p_hw_ftfa->fccob5 = (value >> 16) & 0xff;
    p_hw_ftfa->fccob6 = (value >> 8 ) & 0xff;
    p_hw_ftfa->fccob7 = (value >> 0 ) & 0xff;

    return amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);
}

/**
 *  \brief ������������
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_all_blocks_erase (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_ersall;

    return amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);
}

/**
 *  \brief ��֤������ԿȨ��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param key ��Կ����
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t
amhw_fsl_ftfa_backdoor_access_key_verify (amhw_fsl_ftfa_t *p_hw_ftfa,
                                           uint8_t           key[8])
{
    p_hw_ftfa->fccob0 = amhw_fsl_ftfa_vfykey;

    p_hw_ftfa->fccob4 = key[0];
    p_hw_ftfa->fccob5 = key[1];
    p_hw_ftfa->fccob6 = key[2];
    p_hw_ftfa->fccob7 = key[3];
    p_hw_ftfa->fccob8 = key[4];
    p_hw_ftfa->fccob9 = key[5];
    p_hw_ftfa->fccoba = key[6];
    p_hw_ftfa->fccobb = key[7];

    return amhw_fsl_ftfa_cmd_launch_ram(p_hw_ftfa);
}


