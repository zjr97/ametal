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
 * \brief TPM����������PWM��׼�ӿ�
 *
 * 1. TPM֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���PWM��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. �ڱ������У�TPM�����Դʹ�����£�
 *    - ƥ��Ĵ���0���ڲ���PWM���ڣ����¼�0�����
 *    - ƥ��Ĵ���1���ڲ���PWM���ͨ��0(TPM_OUT0)������
 *    - ƥ��Ĵ���2���ڲ���PWM���ͨ��1(TPM_OUT1)������
 *    - ƥ��Ĵ���3���ڲ���PWM���ͨ��2(TPM_OUT2)������
 *    - ƥ��Ĵ���4���ڲ���PWM���ͨ��3(TPM_OUT3)������
 *    - ƥ��Ĵ���5���ڲ���PWM���ͨ��4(TPM_OUT4)������
 *    - ƥ��Ĵ���6���ڲ���PWM���ͨ��5(TPM_OUT5)������
 *    - ƥ��Ĵ���7���ڲ���PWM���ͨ��6(TPM_OUT6)������
 *    - ƥ��Ĵ���8���ڲ���PWM���ͨ��7(TPM_OUT7)������
 *
 * \note һ��TPM���������PWM��������ֵ��Ҳ����˵����TPM���������PWM������ͬ��
 *       Ƶ����ͬ
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */


#ifndef __AM_FSL_TPM_PWM_H
#define __AM_FSL_TPM_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "hw/amhw_fsl_tpm.h"

/**
 * \addtogroup am_fsl_if_tpm_pwm
 * \copydoc am_fsl_tpm_pwm.h
 * @{
 */

/**
 * \brief TPM PWM���������ص�GPIO��Ϣ
 */
typedef struct am_fsl_tpm_pwm_ioinfo {
    uint32_t gpio;              /**< \brief PWM ���õ�GPIO                    */
    uint32_t func;              /**< \brief PWM���ܵ�GPIO��������ֵ           */
    uint32_t dfunc;             /**< \brief ����PWMģʽ��Ĭ��GPIO��������ֵ */
} am_fsl_tpm_pwm_ioinfo_t;

/**
 * \brief TPM PWM���������ص��豸��Ϣ
 */
typedef struct am_fsl_tpm_pwm_devinfo {
    amhw_fsl_tpm_t           *p_hw_tpm;     /**< \brief ָ��TPM�Ĵ������ָ��    */
    uint8_t                   channels_num; /**< \brief ʹ�õ�ͨ���������Ϊ8    */
    uint32_t                  clk_id;       /**< \brief ʱ�Ӻ�  */
    am_fsl_tpm_pwm_ioinfo_t  *p_ioinfo;     /**< \brief ָ��PWM����ܽ���Ϣ�ṹ��*/

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_tpm_pwm_devinfo_t;
 
/**
 * \brief TPM PWM��������豸�ṹ��
 */
typedef struct am_fsl_tpm_pwm_dev {
    
    am_pwm_serv_t                    pwm_serv; /**< \brief ��׼PWM����           */
    
    /** \brief ָ��TPM(PWM�������)�豸��Ϣ������ָ�� */
    const am_fsl_tpm_pwm_devinfo_t  *p_devinfo;

} am_fsl_tpm_pwm_dev_t;

/**
 * \brief ��ʼ��TPMΪPWM�������
 *
 * \param[in] p_dev     : ָ��TPM(PWM�������)�豸��ָ��
 * \param[in] p_devinfo : ָ��TPM(PWM�������)�豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t am_fsl_tpm_pwm_init (am_fsl_tpm_pwm_dev_t           *p_dev,
                                     const am_fsl_tpm_pwm_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��TPM PWM�������ʱ�����ʼ��TPM PWM������ܣ��ͷ������Դ
 * \param[in] handle : am_fsl_tpm_pwm_init() ��ʼ��������õ�PWM������
 * \return ��
 */
void am_fsl_tpm_pwm_deinit (am_pwm_handle_t handle);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_FSL_TPM_PWM_H */

/* end of file */
