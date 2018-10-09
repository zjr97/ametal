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
 * \brief TPM����������CAP��׼�ӿ�
 *
 * 1. TPM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ��񡰲��񡱱�׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. TPM0������6������ͨ����TPM1��TPM2������2������ͨ����
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_TPM_CAP_H
#define __AM_FSL_TPM_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "hw/amhw_fsl_tpm.h"

/**
 * \addtogroup am_fsl_if_tpm_cap
 * \copydoc am_fsl_tpm_cap.h
 * @{
 */

/**
 * \brief TPM��������ص�GPIO��Ϣ
 */
typedef struct am_fsl_tpm_cap_ioinfo {
    uint32_t gpio;           /**< \brief ��Ӧ��GPIO�ܽ�                       */
    uint32_t func;           /**< \brief Ϊ������ʱ��GPIO��������           */
    uint32_t dfunc;          /**< \brief ���ܹܽŲ�����ʱ��Ĭ��GPIO�������� */
} am_fsl_tpm_cap_ioinfo_t;

/**
 * \brief TPM��������ص��豸��Ϣ
 */
typedef struct am_fsl_tpm_cap_devinfo {
    amhw_fsl_tpm_t           *p_hw_tpm;      /**< \brief ָ��TPM�Ĵ������ָ��  */
    uint8_t                   inum;          /**< \brief TPM��Ӧ���жϺ� */
    uint8_t                   channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ6 */
    uint32_t                  clk_id;        /**< \brief ʱ�Ӻ�  */
    am_fsl_tpm_cap_ioinfo_t  *p_ioinfo;      /**< \brief ָ�򲶻�ܽ���Ϣ�ṹ�� */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
} am_fsl_tpm_cap_devinfo_t;

/**
 * \brief TPM�������豸
 */
typedef struct am_fsl_tpm_cap_dev {
    am_cap_serv_t          cap_serv;      /**< \brief ��׼CAP����            */

    struct {
        am_cap_callback_t  callback_func; /**< \brief �ص�����                    */
        void              *p_arg;         /**< \brief �ص��������û�����          */
    } callback_info[6];                   /**< \brief �洢���6ͨ���Ļص�������Ϣ */

    /** \brief ָ��TPM(������)�豸��Ϣ������ָ�� */
    const am_fsl_tpm_cap_devinfo_t *p_devinfo;

} am_fsl_tpm_cap_dev_t;

/**
 * \brief ��ʼ��TPMΪ������
 *
 * \param[in] p_dev     : ָ��TPM(������)�豸��ָ��
 * \param[in] p_devinfo : ָ��TPM(������)�豸��Ϣ������ָ��
 *
 * \return CAP��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_cap_handle_t am_fsl_tpm_cap_init (am_fsl_tpm_cap_dev_t           *p_dev,
                                     const am_fsl_tpm_cap_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��TPM������ʱ�����ʼ��TPM�����ܣ��ͷ������Դ
 * \param[in] handle : am_fsl_tpm_cap_init() ��ʼ��������õ�cap������
 * \return ��
 */
void am_fsl_tpm_cap_deinit (am_cap_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_FSL_TPM_CAP_H */

/* end of file */
