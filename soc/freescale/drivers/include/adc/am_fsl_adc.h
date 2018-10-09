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
 * \brief ADC����������ADC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-14  mkr, first implementation.
 * \endinternal
 */

#ifndef  __AM_FSL_ADC_H
#define  __AM_FSL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_adc.h"
#include "am_clk.h"
#include "hw/amhw_fsl_adc.h"

/**
 * \addtogroup am_fsl_if_adc
 * \copydoc am_fsl_adc.h
 * @{
 */
#define AM_FSL_ADC_AVG_DIS     0    /**< \brief ��ʹ��Ӳ��ƽ������ */
#define AM_FSL_ADC_AVG_EN      1    /**< \brief ʹ��Ӳ��ƽ������ */
#define AM_FSL_ADC_CMP_DIS     0    /**< \brief ��ʹ�ñȽϹ��� */
#define AM_FSL_ADC_CMP_EN      1    /**< \brief ʹ�ñȽϹ��� */

/**
 * \name ADC �������ñ�־
 * \anchor grp_am_fsl_adc_diff
 * @{
 */
#define AM_FSL_ADC_DIFF_EN      AM_TRUE    /**< \brief ʹ�ò������ģʽ */
#define AM_FSL_ADC_DIFF_DIS     AM_FALSE   /**< \brief ʹ�õ�������ģʽ */
/** @} */

/**
 * \name ADC ����ģʽ���ñ�־
 * \anchor grp_am_fsl_adc_mode_trg
 * @{
 */
#define AM_FSL_ADC_MODE_TRG_SF      0    /**< \brief �������ģʽ��־ */
#define AM_FSL_ADC_MODE_TRG_HW      1    /**< \brief Ӳ������ģʽ���� */
/** @} */

/**
 * \name ADC ״̬���ƼĴ���3λ����
 * \anchor grp_am_fsl_cmp_mode
 * @{
 */
/** \brief �Ƚ�����Ϊ "res < cmp_val1" */
#define AM_FSL_ADC_CMP_MODE_1   0

/** \brief �Ƚ�����Ϊ "res >= cmp_val1" */
#define AM_FSL_ADC_CMP_MODE_2   1

/** \brief �Ƚ�����Ϊ "res < a" ����  "res > b" ��a=min(cmp_val1, cmp_val2),b=max(cmp_val1, cmp_val2)��*/
#define AM_FSL_ADC_CMP_MODE_3   2

/** \brief �Ƚ�����Ϊ " a < res < b" ��a=min(cmp_val1, cmp_val2),b=max(cmp_val1, cmp_val2)��*/
#define AM_FSL_ADC_CMP_MODE_4   3

/** \brief �Ƚ�����Ϊ " a <= res <= b" ��a=min(cmp_val1, cmp_val2),b=max(cmp_val1, cmp_val2)��*/
#define AM_FSL_ADC_CMP_MODE_5   4

/** \brief �Ƚ�����Ϊ "res <= a" ����  "res >= b" ��a=min(cmp_val1, cmp_val2),b=max(cmp_val1, cmp_val2)��*/
#define AM_FSL_ADC_CMP_MODE_6   5
/** @} */

/**
 * \brief ADC Ӳ��ƽ��������Ϣ�ṹ��
 */
typedef struct am_fsl_adc_avg_info {
    /** \brief Ӳ��ƽ��ʹ�ܱ�־ */
    uint8_t         enable;
    /** \brief ƽ���Ĳ���ֵ���� */
    amhw_fsl_adc_avgs_t avgs_num;
} am_fsl_adc_avg_info_t;

/**
 * \brief ADC �ȽϹ�����Ϣ�ṹ��
 */
typedef struct am_fsl_adc_cmp_info {
    /** \brief �ȽϹ���ʹ�ܱ�־ */
    uint8_t  enable;

    /** \brief �Ƚ�ģʽ */
    uint16_t cmp_mode;

    /** \brief �ȽϹ�����ֵ1 */
    uint16_t cmp_val1;

    /** \brief �ȽϹ�����ֵ2 */
    uint16_t cmp_val2;

} am_fsl_adc_cmp_info_t;

/**
 * \brief ADC �豸��Ϣ
 */
typedef struct am_fsl_adc_devinfo {

    /** \brief ָ��ADC�Ĵ������ָ�� */
	amhw_fsl_adc_t *p_hw_adc;

    /**
     * \brief ADC�ο���ѹ����λ��mV
     *
     * �ο���ѹ Vref = (Vrefh - Vrefl)  Ϊ��������������ʱ
     * �ȶ�����ADC��ȷ����Vrefh = 1.13~VDDA��Vrefl����ֵΪ�� Vss�� Vssa
     *
     * \note �òο���ѹ�ɾ���ĵ�·����
     *
     */
    uint32_t   vref;

    /** \brief �������ȣ���is_diff=AM_TRUE��ȡֵΪ[9,11,13,16], ����ȡֵΪ[8,10,12,16]�� */
    uint8_t    bits;

    /** \brief �Ƿ�ʹ�ò��ģʽ��/ref grp_amdr_adc_diff, ��chan > 3,��ֵ����ԣ�*/
    uint8_t    is_diff;

    /** \brief ADC�ж������� */
    uint8_t    inum;

    /** \brief ����ģʽ �ο�/ref grp_amdr_adc_mode_trg */
    uint8_t    mode_trg;

    /** \brief ʹ�õ����� */
    amhw_fsl_adc_seq_index_t  seq;

    /** \brief DMA����ͨ����,��DMA_CHAN_0����Ϊ-1ָ��ʹ��DMA���� */
    int       dma_chan;

    /**< \brief ADC���ص�ʱ��Դ */
    int       clk_id;

    /** \brief ָ��Ӳ��ƽ����Ϣ�ṹ��ָ�� */
    const am_fsl_adc_avg_info_t *p_adc_avg_info;

    /** \brief ָ��ȽϹ�����Ϣ�ṹ��ָ�� */
    const am_fsl_adc_cmp_info_t *p_adc_cmp_info;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_adc_devinfo_t;

/**
 * \brief ADC�豸ʵ��
 */
typedef struct am_fsl_adc_dev {

    /** \brief ADC��׼���� */
    am_adc_serv_t             adc_serv;

    /** \brief ָ��ADC�豸��Ϣ��ָ�� */
    const am_fsl_adc_devinfo_t *p_devinfo;

    /** \brief ����û�����ת����Ļص����� */
    am_adc_seq_cb_t    pfn_callback;

    /** \brief �û������ص������Ļص��������� */
    void                    *p_arg;

    /** \brief ��ǰת�������������������׵�ַ */
    am_adc_buf_desc_t       *p_desc;

    /** \brief ��ǰת������������������ */
    uint32_t                desc_num;

    /** \brief ת���Ĵ��� */
    uint32_t                count;

    /** \brief ת����־   */
    uint32_t                flags;

    /** \brief ��ǰת����ͨ�� */
    uint32_t                chan;

    /** \brief ָ��������   */
    uint32_t                desc_pos;

    /** \brief ָ��ǰ�������ݵ�λ�� */
    uint32_t                index;

    /** \brief ��ǰת������ */
    uint32_t                count_pos;

} am_fsl_adc_dev_t;

/**
 * \brief ADC��ʼ��
 *
 * Ĭ�ϳ�ʼ������A
 *
 * \param[in] p_dev     : ָ��ADC�豸��ָ��
 * \param[in] p_devinfo : ָ��ADC�豸��Ϣ��ָ��
 *
 * \return ADC��׼���������� ���Ϊ NULL��������ʼ��ʧ��
 * \note   Ĭ������100KHz�����ʣ���bus����ʱ���㹻��
 */
am_adc_handle_t am_fsl_adc_init(am_fsl_adc_dev_t           *p_dev,
                              const am_fsl_adc_devinfo_t *p_devinfo);

/**
 * \brief ADCȥ��ʼ��
 *
 * Ĭ��ȥ��ʼ������A
 *
 * \param[in] handle : ָ��ADC�豸�ľ��ֵ
 *
 * \return ��
 */
void am_fsl_adc_deinit(am_adc_handle_t handle);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMDR_FSL_ADC_H  */

/* end of file */
