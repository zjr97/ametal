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
 * \brief FTFA������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-20  sdy, first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_FTFA_H
#define __AM_FSL_FTFA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "hw/amhw_fsl_ftfa.h"
/**
 * \addtogroup am_fsl_if_ftfa
 * \copydoc am_fsl_ftfa.h
 * @{
 */

/**
 *  \brief FTFAģ���ʼ��
 *
 *  \return ��
 */
void am_fsl_ftfa_init (void);

/**
 *  \brief ��������
 *
 *  \param start_addr ��������ʼ��ַ
 *
 *  \return >0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_fsl_ftfa_sector_erase (amhw_fsl_ftfa_t * AMHW_FSL_FTFA,uint32_t start_addr);

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
                                    uint32_t  size);

/**
 *  \brief ������������
 *
 *  \return ִ�н��
 *
 */
uint32_t am_fsl_ftfa_all_sector_erase (amhw_fsl_ftfa_t * AMHW_FSL_FTFA);



/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AM_FSL_FTFA_H */
