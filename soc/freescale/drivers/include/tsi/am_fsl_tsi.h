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
 * \brief TSI������
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-26  nwt, make some changes.
 * - 1.00 15-10-21  wxj, first implementation.
 * \endinternal
 */

#ifndef __AM_FSL_TSI_H
#define __AM_FSL_TSI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_fsl_tsi.h"
#include "am_int.h"

/**
 * \addtogroup am_fsl_if_tsi
 * \copydoc am_fsl_tsi.h
 * @{
 */

/**
 * \brief TSI �豸��Ϣ�ṹ��
 */
typedef struct am_fsl_tsi_devinfo {

    amhw_fsl_tsi_t  *p_hw_tsi;  /**< \brief ָ��TSI�Ĵ������ָ�� */
    am_bool_t           lp_mode;    /**< \brief �͹��Ļ���MCU���� */

    /** \brief TSI�жϺ� */
    uint8_t    inum;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_tsi_devinfo_t;

/**
 * \brief TSI�豸ʵ��
 */
typedef struct am_fsl_tsi_dev {

    /** \brief ָ��TSI�豸��Ϣ��ָ�� */
    const am_fsl_tsi_devinfo_t *p_devinfo;

} am_fsl_tsi_dev_t;

/**
 * \brief TSI��������
 *
 * \param[in] chan      : TSI ͨ����
 * \param[in] work_mode : TSI ����ģʽ
 * \param[in] trig_mode : TSI ɨ�败��ģʽ
 *
 * \return �������ò����ɹ�
 */
int am_fsl_tsi_fun_cfg (amhw_fsl_tsi_channel_t    chan,
                         amhw_fsl_tsi_mode_t       work_mode,
                         amhw_fsl_tsi_trig_mode_t  trig_mode);

/**
 * \brief TSI�жϴ���ģʽ
 *
 * \param[in] flag  : �жϴ���ģʽ
 *
 * \return ��ȡ��ת��ֵ
 */
void am_fsl_tsi_trigger_cfg (amhw_fsl_tsi_irq_mode_t flag);

/**
 * \brief TSI�ж�ʹ��
 *
 * \return ��
 */
void am_fsl_tsi_int_enable (void);

/**
 * \brief TSI�жϽ���
 *
 * \return ��
 */
void am_fsl_tsi_int_disable (void);

/**
 * \brief TSI�жϷ���������
 *
 * \param[in] pfn_callback  : �жϷ������ӿ�
 *
 * \return ��
 */
int am_fsl_tsi_trigger_connect (am_pfnvoid_t pfn_callback);

 /**
 * \brief TSI ����������
 *
 * \param[in] val   : ������ֵ
 *
 * \return ��
 */
void am_fsl_tsi_sens_set (uint16_t val);

/**
 * \brief TSI��ʼ��
 *
 * \param[in] p_dev     : ָ��TSI�豸��ָ��
 * \param[in] p_devinfo : ָ��TSI�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_fsl_tsi_init (am_fsl_tsi_dev_t *p_dev, const am_fsl_tsi_devinfo_t *p_devinfo);

/**
 * \brief TSI ���ʼ��
 *
 * \param[in] p_dev : ָ��TSE�豸��ָ��
 *
 * \return ��
 */
void am_fsl_tsi_deinit (am_fsl_tsi_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_FSL_TSI_H */

/* end of file */
