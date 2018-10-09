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
 * \brief RCM Ӳ�������ӿ�
 * 
 * 1. ��ȡ��λԭ��
 * 2. ���ø�λ�����˲�������
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-14  mkr, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_RCM_H
#define __AMHW_FSL_RCM_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
#include "am_bitops.h"
/**
 * \addtogroup amhw_fsl_if_rcm
 * \copydoc amhw_fsl_rcm.h
 * @{
 */

/**
 * \brief RCM�Ĵ�����ṹ��
 */
typedef struct amhw_fsl_rcm {
    __I  uint16_t srs;            /**< \brief RCM ��λ״̬�Ĵ���0        */
    __IO uint8_t  rpfc;           /**< \brief RCM ��λ�˲����ƼĴ���     */
    __IO uint8_t  rpfw;           /**< \brief RCM ��λ�˲���ȼĴ���     */
} amhw_fsl_rcm_t;

/**
 * \name ��λԭ���־
 * @{
 */

#define AMHW_FSL_RCM_RESTFLAG_SACKERR AM_BIT(13)  /**< \brief ֹͣģʽ�������λ */
#define AMHW_FSL_RCM_RESTFLAG_MDM_AP  AM_BIT(11)  /**< \brief ���Ը�λ             */
#define AMHW_FSL_RCM_RESTFLAG_SW      AM_BIT(10)  /**< \brief �����λ             */
#define AMHW_FSL_RCM_RESTFLAG_LOCKUP  AM_BIT(9)   /**< \brief �ں�Lockup�¼���λ   */
#define AMHW_FSL_RCM_RESTFLAG_POR     AM_BIT(7)   /**< \brief �ϵ縴λ             */
#define AMHW_FSL_RCM_RESTFLAG_PIN     AM_BIT(6)   /**< \brief REST���Ÿ�λ         */
#define AMHW_FSL_RCM_RESTFLAG_WDOG    AM_BIT(5)   /**< \brief ���Ź���λ           */
#define AMHW_FSL_RCM_RESTFLAG_LOL     AM_BIT(3)   /**< \brief ���໷�쳣           */
#define AMHW_FSL_RCM_RESTFLAG_LOC     AM_BIT(2)   /**< \brief ʱ�Ӷ�ʧ��λ         */
#define AMHW_FSL_RCM_RESTFLAG_LVD     AM_BIT(1)   /**< \brief �͵�ѹ��⸴λ       */
#define AMHW_FSL_RCM_RESTFLAG_WAKEUP  AM_BIT(0)   /**< \brief ���Ѹ�λ             */

/** @} */

/**
 * \name ֹͣģʽ����λ���ŵ��˲�ʱ��ѡ��
 * @{
 */

/** \brief ֹͣģʽ���Ը�λ�����˲� */
#define AMHW_FSL_RCM_RESPIN_FILT_STOP_DISABLE    0

 /** \brief ֹͣģʽʹ�ø���LPOʱ�ӶԸ�λ�����˲� */
#define AMHW_FSL_RCM_RESPIN_FILT_STOP_LPO     AM_BIT(2)

/** @} */

/**
 * \name ���к͵ȴ�ģʽ����λ�����˲�ʱ��ѡ��
 * @{
 */
 
/** \brief ���к͵ȴ�ģʽ���Ը�λ�����˲� */
#define AMHW_FSL_RCM_RESPIN_FILT_RUNW_DISABLE   00

/** \brief ���к͵ȴ�ģʽʹ��LPOʱ�ӶԸ�λ�����˲� */
#define AMHW_FSL_RCM_RESPIN_FILT_RUNW_LPO      0x01

/** \brief ���к͵ȴ�ģʽʹ��BUSʱ�Ӹ�λ�����˲� */
#define AMHW_FSL_RCM_RESPIN_FILT_RUNW_BUS      0x10

/** @} */

/**
 * \brief ��ȡ��λԭ���־
 * \param[in] p_hw_rcm : ָ��PMC�Ĵ������ָ��
 * \return ��λԭ���־
 */
am_static_inline
uint16_t amhw_fsl_rcm_rest_flags_get (amhw_fsl_rcm_t *p_hw_rcm)
{
    return p_hw_rcm->srs;
}

/**
 * \brief ���ø�λ����ֹͣģʽ�˲�ʱ��ѡ��
 *
 * \param[in] p_hw_rcm : ָ��PMC�Ĵ������ָ��
 * \param[in] flag     : �˲�ʱ������ѡ�AMHW_FSL_RCM_RESPIN_FILT_STOP_*��ֵ
 *                       (#AMHW_FSL_RCM_RESPIN_FILT_STOP_LPO)
 * \return ��
 *
 * \note ���LPOʱ��û�п�������ô�˲�����
 */
am_static_inline
void amhw_fsl_rcm_respin_filt_stop_cfg (amhw_fsl_rcm_t *p_hw_rcm, uint8_t flag)
{
    p_hw_rcm->rpfc = flag | (p_hw_rcm->rpfc & (~0x4));
}

/**
 * \brief ���ø�λ�������к͵ȴ�ģʽ�˲�ʱ��ѡ��
 *
 * \param[in] p_hw_rcm : ָ��PMC�Ĵ������ָ��
 * \param[in] flag     : �˲�ʱ������ѡ�AMHW_FSL_RCM_RESPIN_FILT_RUNW_*��ֵ
 *                      (#AMHW_FSL_RCM_RESPIN_FILT_RUNW_BUS)
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_rcm_respin_filt_runw_cfg (amhw_fsl_rcm_t *p_hw_rcm, uint8_t flag)
{
    p_hw_rcm->rpfc = flag | (p_hw_rcm->rpfc & (~0x03));
}

/**
 * \brief ���ø�λ��������ģʽ�˲�BUSʱ�Ӹ���
 *
 * \param[in] p_hw_rcm : ָ��PMC�Ĵ������ָ��
 * \param[in] count    : BUSʱ�ӵĸ���(1-32)
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_rcm_respin_filt_busc_cfg (amhw_fsl_rcm_t *p_hw_rcm, uint8_t count)
{
    p_hw_rcm->rpfw = (count - 1) & 0x1F;
}

/** 
 * @} amhw_if_fsl_rcm
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_RCM_H */

/*end of file */
