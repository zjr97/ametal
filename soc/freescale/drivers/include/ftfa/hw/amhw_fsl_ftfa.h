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

#ifndef __AMHW_FSL_FTFA_H
#define __AMHW_FSL_FTFA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "am_common.h"

/**
 * \addtogroup amhw_fsl_if_ftfa
 * \copydoc amhw_fsl_ftfa.h
 * @{
 */

/******************************************************************************
    ״̬�Ĵ���������غ궨��
******************************************************************************/

/** \brief ��������жϱ�־λ */
#define AMHW_FSL_FTFA_CCIF     (1UL << 7)

/** \brief FLASH��ȡ��ͻ�����־λ */
#define AMHW_FSL_FTFA_RDCOLERR (1UL << 6)

/** \brief FLASH����Ȩ�޴����־λ */
#define AMHW_FSL_FTFA_ACCERR   (1UL << 5)

/** \brief �������ֱ�������FLASH��־λ */
#define AMHW_FSL_FTFA_FPVIOL   (1UL << 4)

/** \brief FLASH�������״̬��־λ */
#define AMHW_FSL_FTFA_MGSTAT0  (1UL << 0)


/******************************************************************************
    ���üĴ���������غ�
******************************************************************************/

/** \brief ��������ж�ʹ��λ */
#define AMHW_FSL_FTFA_CCIE       (1UL << 7)

/** \brief ��ȡ��ͻ�����ж�ʹ��λ */
#define AMHW_FSL_FTFA_RDCOLLIE   (1UL << 6)

/** \brief ����ȫ����������λ */
#define AMHW_FSL_FTFA_ERSAREQ    (1UL << 5)

/** \brief ��ǰ������������λ */
#define AMHW_FSL_FTFA_ERSSUSP    (1UL << 4)

/**
 *  \brief FLASH����
 */
typedef enum amhw_fsl_ftfa_cmd {
    amhw_fsl_ftfa_rd1sec  = 0x01,    /**< \brief ��������Ƿ�Ϊȫ1        */
    amhw_fsl_ftfa_pgmchk  = 0x02,    /**< \brief ��̽ṹ����             */
    amhw_fsl_ftfa_rdrsrc  = 0x03,    /**< \brief ��ȡ���������FLASH����  */
    amhw_fsl_ftfa_pgm4    = 0x06,    /**< \brief ���һ����(4�ֽ�)��FLASH */
    amhw_fsl_ftfa_ersscr  = 0x09,    /**< \brief ����FLASH����            */
    amhw_fsl_ftfa_rd1all  = 0x40,    /**< \brief ������������Ƿ�Ϊȫ1    */
    amhw_fsl_ftfa_rdonce  = 0x41,    /**< \brief ��ȡһ�α������FLASH    */
    amhw_fsl_ftfa_pgmonce = 0x43,    /**< \brief ���һ�α����           */
    amhw_fsl_ftfa_ersall  = 0x44,    /**< \brief ������������             */
    amhw_fsl_ftfa_vfykey  = 0x45,    /**< \brief ��֤������Կ             */
}
amhw_fsl_ftfa_cmd_t;

/**
 *  \brief FTFA �Ĵ����ṹ�嶨��
 */
typedef struct amhw_fsl_ftfa {
    __IO uint8_t fstat;  /**< \brief FLASH״̬�Ĵ���      */
    __IO uint8_t fcnfg;  /**< \brief FLASH���üĴ���      */
    __I  uint8_t fsec;   /**< \brief FLASH��ȫ�Ĵ���      */
    __I  uint8_t fopt;   /**< \brief FLASHѡ��Ĵ���      */
    __IO uint8_t fccob3; /**< \brief FLASH�������Ĵ���3 */
    __IO uint8_t fccob2; /**< \brief FLASH�������Ĵ���2 */
    __IO uint8_t fccob1; /**< \brief FLASH�������Ĵ���1 */
    __IO uint8_t fccob0; /**< \brief FLASH�������Ĵ���0 */
    __IO uint8_t fccob7; /**< \brief FLASH�������Ĵ���7 */
    __IO uint8_t fccob6; /**< \brief FLASH�������Ĵ���6 */
    __IO uint8_t fccob5; /**< \brief FLASH�������Ĵ���5 */
    __IO uint8_t fccob4; /**< \brief FLASH�������Ĵ���4 */
    __IO uint8_t fccobb; /**< \brief FLASH�������Ĵ���b */
    __IO uint8_t fccoba; /**< \brief FLASH�������Ĵ���a */
    __IO uint8_t fccob9; /**< \brief FLASH�������Ĵ���9 */
    __IO uint8_t fccob8; /**< \brief FLASH�������Ĵ���8 */
    __IO uint8_t fprot3; /**< \brief FLASH��̱����Ĵ���3 */
    __IO uint8_t fprot2; /**< \brief FLASH��̱����Ĵ���2 */
    __IO uint8_t fprot1; /**< \brief FLASH��̱����Ĵ���1 */
    __IO uint8_t fprot0; /**< \brief FLASH��̱����Ĵ���0 */
} amhw_fsl_ftfa_t;

/**
 *  \brief ��ȡ����������
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \retval 0 ��������ִ��
 *  \retval AMHW_FSL_FTFA_CCIF ����ִ�����
 */
am_static_inline
uint8_t amhw_fsl_ftfa_cmd_is_complete (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    return p_hw_ftfa->fstat & AMHW_FSL_FTFA_CCIF;
}

/**
 *  \brief ���CCIFλ��ִ��FLASH����
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \return ��
 *
 *  \details Details
 */
am_static_inline
void amhw_fsl_ftfa_cmd_lanch (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fstat = AMHW_FSL_FTFA_CCIF;
}

/**
 *  \brief ��ȡ��ȡ��ͻ����״̬
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \retval 0 û�ж�ȡ��ͻ����
 *  \retval AMHW_FSL_FTFA_RDCOLERR ��⵽��ȡ��ͻ����
 */
am_static_inline
uint8_t amhw_fsl_ftfa_read_collision_get (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    return p_hw_ftfa->fstat & AMHW_FSL_FTFA_RDCOLERR;
}

/**
 *  \brief �����ȡ��ͻ�����־λ
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_read_collision_clr (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fstat = AMHW_FSL_FTFA_RDCOLERR;
}

/**
 *  \brief �Ƿ�Ȩ�޲���״̬��ȡ
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \retval 0 û�з����Ƿ�Ȩ�޲���
 *  \retval AMHW_FSL_FTFA_ACCERR �����˷Ƿ�Ȩ�޲���
 */
am_static_inline
uint8_t amhw_fsl_ftfa_access_err_get (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    return p_hw_ftfa->fstat & AMHW_FSL_FTFA_ACCERR;
}

/**
 *  \brief ����Ƿ�Ȩ�޲���״̬��־
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_access_err_clr (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fstat = AMHW_FSL_FTFA_ACCERR;
}

/**
 *  \brief ������������״̬��ȡ
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \retval 0 û�б�����������
 *  \retval AMHW_FSL_FTFA_FPVIOL �������������
 */
am_static_inline
uint8_t amhw_fsl_ftfa_protection_violation_get (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    return p_hw_ftfa->fstat & AMHW_FSL_FTFA_FPVIOL;
}

/**
 *  \brief ������������״̬��־���
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_protection_violation_clr (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fstat = AMHW_FSL_FTFA_FPVIOL;
}

/**
 *  \brief �������״̬��ȡ
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \retval 0 ����˳�����
 *  \retval AMHW_FSL_FTFA_MGSTAT0 ���������
 */
am_static_inline
uint8_t amhw_fsl_ftfa_cmd_completion_status_get (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    return p_hw_ftfa->fstat & AMHW_FSL_FTFA_MGSTAT0;
}

/**
 *  \brief �������״̬��־���
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  return ��
 */
am_static_inline
void amhw_fsl_ftfa_cmd_completion_status_clr (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fstat = AMHW_FSL_FTFA_MGSTAT0;
}

/**
 *  \brief ��������ж�ʹ��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_cmd_complete_int_enable (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fcnfg |= AMHW_FSL_FTFA_CCIE;
}

/**
 *  \brief ��������жϳ���
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_cmd_complete_int_disable (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fcnfg &= ~AMHW_FSL_FTFA_CCIE;
}

/**
 *  \brief ��ȡ��ͻ�ж�ʹ��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_read_collision_int_enable (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fcnfg |= AMHW_FSL_FTFA_RDCOLLIE;
}

/**
 *  \brief ��ȡ��ͻ�жϳ���
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_read_collision_int_disable (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fcnfg &= ~AMHW_FSL_FTFA_RDCOLLIE;
}

/**
 *  \brief ����ǰFLASH������������
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_flash_erase_suspend (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fcnfg |= AMHW_FSL_FTFA_ERSSUSP;
}

/**
 *  \brief ����FLASH������������
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_flash_erase_resume (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    if ((p_hw_ftfa->fcnfg & AMHW_FSL_FTFA_ERSSUSP)) {
        p_hw_ftfa->fstat = AMHW_FSL_FTFA_CCIF;
    }
}

/**
 *  \brief ��ֹFLASH������������
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��
 */
am_static_inline
void amhw_fsl_ftfa_flash_erase_abort (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    p_hw_ftfa->fcnfg &= AMHW_FSL_FTFA_ERSSUSP;
}

/**
 *  \brief FLASH��ȫ״̬��ȡ
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ��ȫ���üĴ���
 */
am_static_inline
uint8_t amhw_fsl_ftfa_flash_security_get (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    return p_hw_ftfa->fsec;
}

/**
 *  \brief FLASHѡ��Ĵ�����ȡ
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return ѡ��Ĵ���
 */
am_static_inline
uint8_t amhw_fsl_ftfa_flash_option_get (amhw_fsl_ftfa_t *p_hw_ftfa)
{
    return p_hw_ftfa->fopt;
}

/**
 *  \brief ��FLASH�ĵ�n/32�������Ϊ��̱���
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param n ��n/32������,  n = 0~31
 *
 *  \retval AM_ERROR FLASH��������ִ�У�������д��FPROT�Ĵ���
 *  \retval AM_OK    ���óɹ�
 */
am_static_inline
int amhw_fsl_ftfa_program_protection_add (amhw_fsl_ftfa_t *p_hw_ftfa, uint8_t n)
{
    uint32_t field = 0;
    field |= p_hw_ftfa->fprot0 << 24;
    field |= p_hw_ftfa->fprot1 << 16;
    field |= p_hw_ftfa->fprot2 << 8;
    field |= p_hw_ftfa->fprot3 << 0;

    field &= ~(1ul << n);
    if(0 == (p_hw_ftfa->fstat | AMHW_FSL_FTFA_CCIF)) {
        p_hw_ftfa->fprot0 = (field >> 24) & (0xff);
        p_hw_ftfa->fprot1 = (field >> 16) & (0xff);
        p_hw_ftfa->fprot2 = (field >> 8 ) & (0xff);
        p_hw_ftfa->fprot3 = (field >> 0 ) & (0xff);
        return AM_OK;
    } else {
        return AM_ERROR;
    }

}

/**
 *  \brief ��FLASH�ĵ�n/32����ӱ�̱�����ȡ��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param n ��n/32������
 *
 *  return ��
 */
am_static_inline
void amhw_fsl_ftfa_program_protection_sub (amhw_fsl_ftfa_t *p_hw_ftfa, uint8_t n)
{
    uint32_t field = 0;
    field |= p_hw_ftfa->fprot0 << 24;
    field |= p_hw_ftfa->fprot1 << 16;
    field |= p_hw_ftfa->fprot2 << 8;
    field |= p_hw_ftfa->fprot3 << 0;

    field |= (1ul << n);

    p_hw_ftfa->fprot0 = (field >> 24) & (0xff);
    p_hw_ftfa->fprot1 = (field >> 16) & (0xff);
    p_hw_ftfa->fprot2 = (field >> 8 ) & (0xff);
    p_hw_ftfa->fprot3 = (field >> 0 ) & (0xff);
}
/**
 *  \brief ��amhw_fsl_ftfa_cmd_launch ����������RAM��
 *
 *  \return ��
 *
 *  \note FLASH���������޸�flashʱ������Ҫ��RAM������
 */
void amhw_fsl_ftfa_func_copy (void);

/**
 *  \brief �����ж������Ƿ�Ϊȫ1����
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param start_addr ������ʼ��ַ
 *  \param n_words ��(32bit)�ĸ���
 *  \param margin ����ѡ��
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����:��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_1s_read (amhw_fsl_ftfa_t *p_hw_ftfa,
                            uint32_t     start_addr,
                            uint16_t     n_words,
                            uint8_t      margin);

/**
 *  \brief ��(32bit)��̽����ȷ�����ж�
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param addr Ҫ�жϵĵ�ַ
 *  \param context ��������������
 *  \param margin ����ѡ��
 *          - ��ѡ 0x01, 0x02
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����:��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_program_check (amhw_fsl_ftfa_t *p_hw_ftfa,
                                 uint32_t     addr,
                                 uint32_t     context,
                                 uint8_t      margin);

/**
 *  \brief ��ȡ���⹦����FLASH
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param addr flash��ַ
 *  \param p_context ָ�򻺴��ȡ���ݵĻ�������ָ��
 *  \param resrc_select ��Դѡ��
 *          - 0x00 Program Flash 0 IFR
 *          - 0x01 Version ID
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����:��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_resrc_read (amhw_fsl_ftfa_t *p_hw_ftfa,
                               uint32_t     addr,
                               uint32_t    *p_context,
                               uint8_t      resrc_select);

/**
 *  \brief ��һ���ֱ��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param addr FLASH�ֵ�ַ
 *  \param word д���ֵ�����
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����:��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_word_program (amhw_fsl_ftfa_t *p_hw_ftfa,
                                 uint32_t     addr,
                                 uint32_t     word);

/**
 *  \brief ��������
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param addr ������ʼ��ַ
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����:��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_sector_erase (amhw_fsl_ftfa_t *p_hw_ftfa,
                                 uint32_t     addr);

/**
 *  \brief �ж����������Ƿ�Ϊȫ1
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param margin ����ѡ��
 *          ��ѡ���� 0x0 - 0x2
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����:��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_all_blocks_1s_read (amhw_fsl_ftfa_t *p_hw_ftfa,
                                       uint8_t      margin);

/**
 *  \brief ��ȡ64�ֽڱ������е�һ����
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param index ������� 0x00-0x0f
 *  \param p_value ָ���ȡ��������ָ��
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����: ��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_once_read (amhw_fsl_ftfa_t *p_hw_ftfa,
                              uint8_t      index,
                              uint32_t    *p_value);

/**
 *  \brief �Ա�������һ���ֽ���һ���Ա��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param index ������� 0x00-0x0f
 *  \param value ϣ��д���ֵ
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����: ��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_once_program (amhw_fsl_ftfa_t *p_hw_ftfa,
                                 uint8_t      index,
                                 uint32_t     value);

/**
 *  \brief ������������
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *
 *  \return 0: ��ʾ����ɹ�ִ�У�����:��ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_all_blocks_erase (amhw_fsl_ftfa_t *p_hw_ftfa);

/**
 *  \brief ��֤������ԿȨ��
 *
 *  \param p_hw_ftfa ָ��Ĵ����ṹ���ָ��
 *  \param key ��Կ����
 *
 *  \return 0 ��ʾ����ɹ�ִ�У�������ʾ����û�гɹ�ִ��
 */
uint32_t amhw_fsl_ftfa_backdoor_access_key_verify (amhw_fsl_ftfa_t *p_hw_ftfa,
        uint8_t      key[8]);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AMHW_FSL_FTFA_H */

