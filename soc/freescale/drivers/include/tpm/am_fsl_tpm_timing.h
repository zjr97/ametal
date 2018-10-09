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
 * \brief TPM����������Timer������ʵ��
 *
 * 1. TPM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���Timer��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-14  sdy, first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_TPM_TIMING_H
#define __AM_FSL_TPM_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "hw/amhw_fsl_tpm.h"

/**
 * \addtogroup am_fsl_if_tpm_timing
 * \copydoc am_fsl_tpm_timing.h
 * @{
 */

/**
 * \brief TPM��ʱ������ص��豸��Ϣ
 */
typedef struct am_fsl_tpm_timing_devinfo {

    amhw_fsl_tpm_t   *p_hw_tpm;    /**< \brief ָ��TPM�Ĵ������ָ�� */
    uint8_t           inum;        /**< \brief TPM�жϺ�  */
    uint32_t          clk_id;      /**< \brief ʱ�Ӻ�  */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_tpm_timing_devinfo_t;
    
/**
 * \brief TPM��ʱ�����豸
 */
typedef struct am_fsl_tpm_timing_dev {

    am_timer_serv_t   timer_serv;       /**< \brief ��׼��ʱ(Timer)���� */

    void (*pfn_callback)(void *);       /**< \brief �ص����� */
    void *p_arg;                        /**< \brief �ص��������û����� */
    
    /** \brief ָ��TPM(��ʱ����)�豸��Ϣ������ָ�� */
    const am_fsl_tpm_timing_devinfo_t  *p_devinfo;

} am_fsl_tpm_timing_dev_t;

/**
 * \brief ��ʼ��TPMΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��TPM(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��TPM(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t am_fsl_tpm_timing_init (am_fsl_tpm_timing_dev_t            *p_dev,
                                          const am_fsl_tpm_timing_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��TPM��ʱ����ʱ�����ʼ��TPM��ʱ���ܣ��ͷ������Դ
 * \param[in] handle : am_fsl_tpm_timing_init() ��ʼ��������õ�Timer������
 * \return ��
 */
void am_fsl_tpm_timing_deinit (am_timer_handle_t handle);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_FSL_TPM_TIMING_H */

/* end of file */
