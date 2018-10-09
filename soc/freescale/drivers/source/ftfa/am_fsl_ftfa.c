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
 * \brief FTFAģ���������ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

#include "am_types.h"
#include "am_bitops.h"
#include "ametal.h"
#include "am_fsl_ftfa.h"
#include "hw/amhw_fsl_ftfa.h"


#define SECTOR_SIZE (1024UL / 4)     /**< \brief ������С ����(32bit)Ϊ��λ     */

#define FLASH_SIZE  (1024*128UL)      /**< \brief flash�Ĵ�С ���ֽ�(8bit)Ϊ��λ */

/******************************************************************************
*   ��������
******************************************************************************/

/**
 *  \brief FTFAģ���ʼ��
 *
 *  \return ��
 */
void am_fsl_ftfa_init (void)
{
    amhw_fsl_ftfa_func_copy();
    return;
}

/**
 *  \brief ��������
 *
 *  \param start_addr ��������ʼ��ַ
 *
 *  \return >0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_fsl_ftfa_sector_erase (amhw_fsl_ftfa_t * AMHW_FSL_FTFA,uint32_t start_addr)
{
    if (FLASH_SIZE < start_addr)
    {
        return -AM_EINVAL;
    }
    return amhw_fsl_ftfa_sector_erase(AMHW_FSL_FTFA, start_addr);
}

/**
 *  \brief ��������̻򲿷��������
 *
 *  \param dst_addr д�뵽flash����ʼ��ַ
 *  \param p_src Ҫд�뵽flash�е����ݵ���ʼ��ַ
 *  \param size д����(32bit)�ĸ���
 *
 *  \retval >=0 ʵ�ʳɹ�д�������
 *  \retval -AM_EINVAL �����д����������
 *  \retval -AM_EINVAL ָ�����������δ��������
 *  \retval -AM_EAGAIN ���̵�flash��δ�����������������
 *  \retval -AM_ERROR  δ֪����
 */
int32_t am_fsl_ftfa_flash_program (amhw_fsl_ftfa_t * AMHW_FSL_FTFA,
									uint32_t  dst_addr,
                                    uint32_t *p_src,
                                    uint32_t  size)
{
    uint32_t status;
    int      i;

    /** size���ܴ��������Ĵ�С */
    if (size > SECTOR_SIZE || dst_addr >= FLASH_SIZE) {
        return -AM_EINVAL;
    }

    /** ��֤flash�Ѳ��� */
    status = amhw_fsl_ftfa_1s_read(AMHW_FSL_FTFA,
                                    dst_addr,
                                    size,
                                    0);

    /** ��flash��� */
    if (0 == status) {
        for (i = 0; i < size; i++) {

            /** ���1���� */
            status = amhw_fsl_ftfa_word_program(AMHW_FSL_FTFA,
                                                 dst_addr + (i*4),
                                                 p_src[i]);

            if (0 != status) {
                break;
            }

            /** ���д����Ƿ���ȷ */
            status = amhw_fsl_ftfa_program_check(AMHW_FSL_FTFA,
                                                  dst_addr + i*4,
                                                  p_src[i],
                                                  0x01);

            if (0 != status) {
                break;
            }

        }

        if (i <= size && i > 0) {
            return i;          /** ����д��ɹ����� i           */
        }

        if (0 == i) {
            return -AM_EAGAIN; /** ��ȫû��д�� ���� -AM_EAGAIN */
        }
    } else {                   /** ����У����� ���� -AM_EAGAIN */
        return -AM_EAGAIN;
    }
    return -AM_ERROR;
}

/**
 *  \brief ������������
 *
 *  \return ִ�н��
 *
 */
uint32_t am_fsl_ftfa_all_sector_erase (amhw_fsl_ftfa_t * AMHW_FSL_FTFA)
{
    return amhw_fsl_ftfa_all_blocks_erase(AMHW_FSL_FTFA);
}


