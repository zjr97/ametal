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
 * \brief LPTMR����������Timer������ʵ��
 *
 * 1. LPTMRֻ֧���ṩ"��ʱ"��׼���񣬱������ṩ���Ƿ���"��ʱ"��׼�����������
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_LPTMR_TIMING_H
#define __AM_FSL_LPTMR_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "hw/amhw_fsl_lptmr.h"

/**
 * \addtogroup am_fsl_if_lptmr_timing
 * \copydoc am_fsl_lptmr_timing.h
 * @{
 */

/**
 * \brief LPTMR��ʱ������ص��豸��Ϣ
 */
typedef struct am_fsl_lptmr_timing_devinfo {
    amhw_fsl_lptmr_t   *p_hw_lptmr;    /**< \brief ָ��LPTMR�Ĵ������ָ�� */
    uint8_t             inum;          /**< \brief LPTMR�жϺ�  */
    uint32_t            clk_id;        /**< \brief LPTMRʱ�Ӻ�  */

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_lptmr_timing_devinfo_t;
    
/**
 * \brief LPTMR��ʱ�����豸
 */
typedef struct am_fsl_lptmr_timing_dev {

    am_timer_serv_t   timer_serv;       /**< \brief ��׼��ʱ(Timer)���� */

    void (*pfn_callback)(void *);       /**< \brief �ص����� */
    void *p_arg;                        /**< \brief �ص��������û����� */
    
    /** \brief ָ��LPTMR(��ʱ����)�豸��Ϣ������ָ�� */
    const am_fsl_lptmr_timing_devinfo_t  *p_devinfo;

} am_fsl_lptmr_timing_dev_t;

/**
 * \brief ��ʼ��LPTMRΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��LPTMR(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��LPTMR(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t am_fsl_lptmr_timing_init (am_fsl_lptmr_timing_dev_t            *p_dev,
                                            const am_fsl_lptmr_timing_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��LPTMR��ʱ����ʱ�����ʼ��LPTMR��ʱ���ܣ��ͷ������Դ
 * \param[in] handle : am_fsl_lptmr_timing_init() ��ʼ��������õ�Timer������
 * \return ��
 */
void am_fsl_lptmr_timing_deinit (am_timer_handle_t handle);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_FSL_LPTMR_TIMING_H */

/* end of file */
