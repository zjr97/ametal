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
 * \brief PIT����������Timer������ʵ��
 *
 * 1. PIT֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���Timer��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-18  sdy, first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_PIT_TIMING_H
#define __AM_FSL_PIT_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "hw/amhw_fsl_pit.h"

/**
 * \addtogroup am_fsl_if_pit_timing
 * \copydoc am_fsl_pit_timing.h
 * @{
 */

/** \brief PIT������1��64λ��ʱ��ģʽ, �����ṩ1����ʱ��ͨ��    */
#define AM_FSL_PIT_TIMING_1_64BIT      1

/** \brief PIT������2��32λ��ʱ��ģʽ, ���ṩ2����ʱ��ͨ��      */
#define AM_FSL_PIT_TIMING_2_32BIT      2

/**
 * \brief PIT��ʱ������ص��豸��Ϣ
 */
typedef struct am_fsl_pit_timing_devinfo {
    amhw_fsl_pit_t    *p_hw_pit;    /**< \brief ָ��PIT�Ĵ������ָ�� */
    uint8_t            flag;        /**< \brief PIT���ñ�־(1-64bit ���� 2-32bit)  */
    uint8_t            inum;        /**< \brief PIT�жϺ�  */
    uint32_t           clk_id;      /**< \brief PITʱ�Ӻ�  */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_pit_timing_devinfo_t;
    
/**
 * \brief PIT��ʱ�����豸
 */
typedef struct am_fsl_pit_timing_dev {

    am_timer_serv_t   timer_serv;           /**< \brief ��׼��ʱ(Timer)���� */

    void (*pfn_ch1_callback)(void *);       /**< \brief �ص����� */
    void *p_arg_ch1;                        /**< \brief �ص��������û����� */
    
    void (*pfn_ch2_callback)(void *);       /**< \brief �ص����� */
    void *p_arg_ch2;                        /**< \brief �ص��������û����� */
    
    /** \brief ָ��PIT(��ʱ����)�豸��Ϣ������ָ�� */
    const am_fsl_pit_timing_devinfo_t  *p_devinfo;

} am_fsl_pit_timing_dev_t;

/**
 * \brief ��ʼ��PITΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��PIT(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��PIT(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t am_fsl_pit_timing_init (am_fsl_pit_timing_dev_t            *p_dev,
                                          const am_fsl_pit_timing_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��PIT��ʱ����ʱ�����ʼ��PIT��ʱ���ܣ��ͷ������Դ
 * \param[in] handle : am_fsl_pit_timing_init() ��ʼ��������õ�Timer������
 * \return ��
 */
void am_fsl_pit_timing_deinit (am_timer_handle_t handle);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_FSL_PIT_TIMING_H */

/* end of file */
