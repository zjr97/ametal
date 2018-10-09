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
 * \brief DAC����������DAC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  mkr, first implementation.
 * \endinternal
 */

#ifndef  __AM_FSL_DAC_H
#define  __AM_FSL_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_dac.h"
#include "hw/amhw_fsl_dac.h"

/**
 * \addtogroup am_fsl_if_dac
 * \copydoc am_fsl_dac.h
 * @{
 */
/**
 * \brief DAC �豸��Ϣ
 */
typedef struct am_fsl_dac_devinfo {

    /** \brief ָ��DAC�Ĵ������ָ�� */
    amhw_fsl_dac_t *p_hw_dac;

    /** \brief DAC�жϺ� */
    uint8_t    inum;

    /** \brief DACת������ */
    uint8_t    bits;

    /**
     * \brief DAC�ο���ѹ����λ��mV
     *
     * \note �òο���ѹ�ɾ���ĵ�·����
     *
     */
    uint32_t    vref;

    /**
     * \brief DAC�ο���ѹԴѡ��
     *
     * \note �òο���ѹ�ɾ���ĵ�·����
     *
     */
    amhw_fsl_dac_vref_sel_t    vref_source;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_dac_devinfo_t;

/**
 * \brief DAC�豸ʵ��
 */
typedef struct am_fsl_dac_dev {

    /** \brief DAC��׼���� */
    am_dac_serv_t             dac_serve;

    /** \brief ָ��DAC�豸��Ϣ��ָ�� */
    const am_fsl_dac_devinfo_t *p_devinfo;

    /** \brief ��ǰת����ͨ�� */
    uint32_t                 chan;

} am_fsl_dac_dev_t;

/**
 * \brief DAC��ʼ��
 *
 * Ĭ�ϳ�ʼ������A
 *
 * \param[in] p_dev     : ָ��DAC�豸��ָ��
 * \param[in] p_devinfo : ָ��DAC�豸��Ϣ��ָ��
 *
 * \return DAC��׼���������� ���Ϊ NULL��������ʼ��ʧ��
 */
am_dac_handle_t am_fsl_dac_init(am_fsl_dac_dev_t           *p_dev,
                                 const am_fsl_dac_devinfo_t *p_devinfo);

/**
 * \brief DACȥ��ʼ��
 *
 * Ĭ��ȥ��ʼ������A
 *
 * \param[in] handle : DAC�豸�ľ��ֵ
 *
 * \return ��
 */
void am_fsl_dac_deinit(am_dac_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__AM_FSL_DAC_H  */

/* end of file */
