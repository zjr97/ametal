/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC����������ADC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.02 18-04-24  pea, update standard interface
 * - 1.01 15-12-09  hgo, modified.
 * - 1.00 15-07-15  bob, first implementation.
 * \endinternal
 */
 
#ifndef  __am_lpc82x_adc_int_H
#define  __am_lpc82x_adc_int_H

#include "ametal.h"
#include "am_adc.h"
#include "am_lpc82x_dma.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \addtogroup am_lpc82x_if_adc
 * \copydoc am_lpc82x_adc_int.h
 * @{
 */

/**
 * \name ADC����ģʽ���ú�
 * 
 * \note ADC�ṩDMA����ģʽ���жϹ���ģʽ
 * \anchor grp_am_lpc82x_adc_int_work_mode
 * @{
 */

/** \brief DMA����ģʽ */
#define am_lpc82x_adc_int_WORK_MODE_DMA          0

/** \brief �жϹ���ģʽ */
#define am_lpc82x_adc_int_WORK_MODE_INT         -1
    
/** @} */


/**
 * \brief ADC �豸��Ϣ 
 */
typedef struct am_lpc82x_adc_int_devinfo {
    
    /** \brief ADC�Ĵ�����Ļ���ַ */
    uint32_t   adc_regbase;
    
    /** \brief ADC clk id */
    uint32_t   clk_id;

    /**
     * \brief ADC�ο���ѹ����λ��mV
     *
     * ���� LPC82x, �ο���ѹ Vref = (Vrefp - Vrefn)  Ϊ��������������ʱ
     * �ȶ�����ADC��ȷ����VREFP = VDDA Vrefn ����ֵΪ�� Vss �� Vssa ��
     *
     * \note �òο���ѹ�ɾ���ĵ�·����
     *
     */
    uint32_t   vref;

    /** \brief ADC����A�жϺ�      */
    int16_t    inum_seqa;

    /** \brief ADC��������жϺ�   */
    int16_t    inum_ovr;

    /** \brief ƽ̨��ʼ�����������ʱ�ӣ��������ŵȹ��� */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_lpc82x_adc_int_devinfo_t;

/**
 * \brief ADC�豸ʵ��
 */
typedef struct am_lpc82x_adc_int_dev {

    /** \brief ADC��׼���� */
    am_adc_serv_t                       adc_serve;

    /** \brief ָ��ADC�豸��Ϣ��ָ�� */
    const am_lpc82x_adc_int_devinfo_t  *p_devinfo;

    /** \brief ����û�����ת����Ļص����� */
    am_adc_seq_cb_t                     pfn_callback;

    /** \brief �û������ص������Ļص��������� */
    void                               *p_arg;

    /** \brief ��ǰת����ͨ�� */
    uint32_t                            chan;

    /** \brief ��ǰת�������������������׵�ַ */
    am_adc_buf_desc_t                  *p_desc;

    /** \brief ��ǰת������������������ */
    uint32_t                            desc_num;

    /** \brief ת���Ĵ��� */
    uint32_t                            count;

    /** \brief ת����־ */
    uint32_t                            flags;

    /** \brief �Ե�ǰ�����������Ѿ������Ĵ��� */
    uint32_t                            conv_cnt;

    /** \brief ����ִ�е�ǰ���������������� */
    uint32_t                            desc_index;

    /** \brief ����������ת����ɵĴ��� */
    uint32_t                            seq_cnt;

    /** \brief adc�Ƿ���� */
    am_bool_t                           is_idle;

} am_lpc82x_adc_int_dev_t;

/**
 * \brief ADC��ʼ�� 
 *
 * Ĭ�ϳ�ʼ������A 
 *
 * \param[in] p_dev     : ָ��ADC�豸��ָ�� 
 * \param[in] p_devinfo : ָ��ADC�豸��Ϣ��ָ�� 
 *
 * \return ADC��׼���������� ���Ϊ NULL��������ʼ��ʧ�� 
 */
am_adc_handle_t am_lpc82x_adc_int_init (am_lpc82x_adc_int_dev_t     *p_dev,
                              const am_lpc82x_adc_int_devinfo_t *p_devinfo);

/**
 * \brief ADCȥ��ʼ�� 
 *
 * Ĭ��ȥ��ʼ������A 
 *
 * \param[in] handle : am_lpc82x_adc_int_init() ��ʼ��������õ�ADC������
 *
 * \return �� 
 */
void am_lpc82x_adc_int_deinit (am_adc_handle_t handle);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /*__am_lpc82x_adc_int_H  */

/* end of file */
