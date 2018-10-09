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
 * \brief PMU�����ӿ�����
 *
 *  1. ϵͳģʽ�л���
 *  2. ���������ã�
 *  3. LLWU����Դ���ü�LLWU�ж����ӣ�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-14  ari, first implementation.
 * \endinternal
 */

#ifndef __AM_KL26_PMU_H
#define __AM_KL26_PMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"
#include "hw/amhw_fsl_smc.h"
#include "hw/amhw_fsl_pmc.h"
#include "hw/amhw_fsl_smc.h"
#include "hw/amhw_fsl_rcm.h"
#include "hw/amhw_fsl_llwu.h"


/**
 * \addtogroup am_kl26_if_pmu
 * \copydoc am_kl26_pmu.h
 * @{
 */

/**
 * \name PMU�豸��ʼ������
 *  
 * ���ڳ�ʼ���豸��Ϣ��flags����
 * @{
 */

/*
 *  bit[ 0 ] : ��λ����stopģʽLPO�˲�ʹ��
 *  bit[1-5] : ��λ����run��waitģʽ�˲�ʱ�Ӹ�����BUSʱ�ӣ���0-32��
 *  bit[ 6 ] : VLPxģʽ�Ƿ�ʹ���ܴ�϶
 *  bit[ 7 ] : �Ƿ�ʹ���ܴ�϶����
 *  bit[ 8 ] : VLSS0ģʽ�Ƿ����POR
 */

/** \brief ��λ����stopģʽLPO�˲�ʹ�� */
#define AM_KL26_PMU_ARG_REST_PIN_STOP_FILT_ENABLE    AM_BIT(0)

/** \brief ��λ����runģʽ�˲�ʱ������ */
#define AM_KL26_PMU_ARG_REST_PIN_RUN_FILT_C(count)   AM_SBF((count),1

/** \brief VLPxģʽ�ܴ�϶ʹ�� */
#define AM_KL26_PMU_ARG_VLPx_BANDGAP_ENABLE          AM_BIT(6)

/** \brief �ܴ�϶�����Ƿ�ʹ�� */
#define AM_KL26_PMU_ARG_BANDGAP_BUF_ENABLE           AM_BIT(7)

/** \brief VLSS0ģʽ����POR�����͹��� */
#define AM_KL26_PMU_ARG_VLLS0_POR_DISABLE            AM_BIT(8)

/** \brief �Ƿ����LLWU���Ѹ�λ��ACK��־(����������ͷ�) */
#define AM_KL26_PMU_ARG_VLLSx_ISOACK_CLEAR           AM_BIT(9)

/** @}*/

/**
 * \brief PMU �豸��Ϣ�ṹ��
 */
typedef struct am_kl26_pmu_devinfo {

    amhw_fsl_smc_t  *p_hw_smc;   /**< \brief ָ��SMC�Ĵ������ָ��  */
    amhw_fsl_pmc_t  *p_hw_pmc;   /**< \brief ָ��PMC�Ĵ������ָ��  */

    amhw_fsl_rcm_t  *p_hw_rcm;   /**< \brief ָ��RCM�Ĵ������ָ��  */
    amhw_fsl_llwu_t *p_hw_llwu;  /**< \brief ָ��LLWU�Ĵ������ָ�� */
    uint32_t          flags;      /**< \brief ��ʼ�����ò���         */

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    void  (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void  (*pfn_plfm_deinit)(void);
} am_kl26_pmu_devinfo_t;

/**
 * \brief PMU �豸�ṹ��
 */
typedef struct am_kl26_pmu_dev {

    /** \brief ָ��PMU�豸��Ϣָ�� */
    const am_kl26_pmu_devinfo_t *p_devinfo;

    /** \brief �����жϻص�����ָ�� */
    am_pfnvoid_t                 p_warn_func;

    /** \brief �����жϻص��������� */
    void                        *p_warn_arg;
} am_kl26_pmu_dev_t;

/**
 * \brief PMU ϵͳģʽ
 *
 *        RUN <--> VPLRʱ��ģʽ�л���PEE <--> BLPE
 *                                FEI <--> BLPI
 */
typedef enum am_kl26_pmu_mode {
    AM_KL26_PMU_MODE_RUN = 0,       /**< \brief ����ģʽ          */
    AM_KL26_PMU_MODE_VLPR,          /**< \brief ���͹�������ģʽ  */
    AM_KL26_PMU_MODE_WAIT,          /**< \brief �ȴ�ģʽ          */
    AM_KL26_PMU_MODE_VLPW,          /**< \brief ���͹��ĵȴ�ģʽ  */
    AM_KL26_PMU_MODE_STOP2,         /**< \brief ֹͣģʽ2 */
    AM_KL26_PMU_MODE_STOP1,         /**< \brief ֹͣģʽ1 */
    AM_KL26_PMU_MODE_STOP,          /**< \brief ����ֹͣģʽ      */
    AM_KL26_PMU_MODE_VLPS,          /**< \brief ���͹���ֹͣģʽ  */
    AM_KL26_PMU_MODE_LLS,           /**< \brief ��©��ֹͣģʽ    */
    AM_KL26_PMU_MODE_VLLS3,         /**< \brief ����©��ֹͣģʽ3 */
    AM_KL26_PMU_MODE_VLLS1,         /**< \brief ����©��ֹͣģʽ1 */
    AM_KL26_PMU_MODE_VLLS0          /**< \brief ����©��ֹͣģʽ0 */
} am_kl26_pmu_mode_t;

/** \brief ���籨����ѹ��ֵ��������ѹ���ڸ�λ��ѹ�� */
typedef enum amhw_kl26_pmu_warn_v_sel {
    AM_KL26_PMU_WARN_V1 = 0,              /**< \brief ѡ�񱨾���ֵ1(1.8v)\(2.7V) */
    AM_KL26_PMU_WARN_V2,                  /**< \brief ѡ�񱨾���ֵ2(1.9V)\(2.8V) */
    AM_KL26_PMU_WARN_V3,                  /**< \brief ѡ�񱨾���ֵ3(2.0V)\(2.9V) */
    AM_KL26_PMU_WARN_V4                   /**< \brief ѡ�񱨾���ֵ4(2.1V)\(3.0V) */
} amhw_kl26_pmu_warn_v_sel_t;

/** \brief ���縴λ��ѹ��ֵ */
typedef enum am_kl26_pmu_rest_v_sel {
    AM_KL26_PMU_REST_VL = 0,              /**< \brief ѡ�����ֵ���(1.6V ) */
    AM_KL26_PMU_REST_VH                   /**< \brief ѡ�����ֵ���(2.56V) */
} am_kl26_pmu_rest_v_sel_t;

/** \brief PMU ������Ϣ���� */
typedef struct am_kl26_pmu_brownout_info {
    amhw_kl26_pmu_warn_v_sel_t  warn_v;      /**< \brief ������ѹѡ�� */
    am_kl26_pmu_rest_v_sel_t    rest_v;      /**< \brief ��λ��ѹѡ�� */
    am_pfnvoid_t                p_callfunc;  /**< \brief �����ص����� */
    void                       *p_arg;       /**< \brief �ص�����     */
    am_bool_t                      enable;      /**< \brief �Ƿ�ʹ��     */
} am_kl26_pmu_brownout_info_t;

/** \brief LLWU����Դ��Ϣ
 *  
 * Ӧʹ�ú���am_kl26_pmu_llwu_src_x_mkinfo()��ʼ���ýṹ��
 */
typedef struct am_kl26_pmu_llwu_src_info {
    uint32_t src;         /**< \brief ����Դ         */
    uint32_t extra_info;  /**< \brief ����Դ������Ϣ */
} am_kl26_pmu_llwu_src_info_t;

/**
 * \brief PMU��ʼ��
 *
 * \param[in] p_dev     : ָ��PMU�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��PMU�豸��Ϣ�ṹ�峣����ָ��
 *
 * \retval AM_OK      : ��ʼ���ɹ�
 * \retval -AM_EINVAL : ��������
 */
int am_kl26_pmu_init (am_kl26_pmu_dev_t *p_dev, const am_kl26_pmu_devinfo_t *p_devinfo);

/**
 * \brief PMUȥ��ʼ��
 * \param[in] p_dev     : ָ��PMU�豸�ṹ���ָ��
 * \return ��
 */
void am_kl26_pmu_deinit (am_kl26_pmu_dev_t *p_dev);

/**
 * \brief ����ϵͳģʽ
 *
 *  1.ģʽ�л����������ģ��磺VLPR��WAIT��Ӧ���л���RUNģʽ�����л���WAITģʽ\n
 *  2.���ģʽ�л��ȴ���ֹͣģʽ�����ڴ˺����ڲ�ֹͣ���Ǹ�λ���Ѻ���˳�
 *    ������AM_OK;\n
 *  3.���ģʽ�л����ɹ���������󣬸ú����᷵��-AM_EINVAL��AM_ERROR��
 *    ����ʱ���ö����ж���\n
 *  4.VLLSxģʽ���Ѻ�ִ�и�λ������
 *
 * \param[in] mode : ϵͳģʽ����
 *
 * \retval AM_OK      ��ģʽ�л���Ч
 * \retval AM_ERROR   ��ģʽ�л�����
 * \retval -AM_EINVAL ��ģʽ��������
 */
int am_kl26_pmu_mode_into (am_kl26_pmu_mode_t mode);

/**
 * \brief ��ȡϵͳģʽ
 * \retval AM_KL26_PMU_MODE_RUN  : ����ģʽ
 * \retval AM_KL26_PMU_MODE_VLPR : �͹�������ģʽ
 */
am_kl26_pmu_mode_t am_kl26_pmu_mode_get (void);

/**
 * \brief ���õ�������Ϣ
 *
 * \param[in] p_info : ָ�������Ϣ�ṹ��ָ��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_EINVAL : ��������
 * \retval AM_ERROR   : ����ʧ��
 *
 * \note VLPx,LLS��VLLSxģʽ��֧�ֵ����⣬����AM_ERROR
 */
int am_kl26_pmu_brownout_cfg (am_kl26_pmu_brownout_info_t *p_info);

/**
 * \brief �����������Ϣ�ṹ��
 *
 * \param[in] p_info : ָ�������Ϣ�ṹ��ָ��
 * \param[in] warn_v : ������ѹ
 * \param[in] rest_v : ��λ��ѹ��������ѹ���ڸ�λ��ѹ��
 * \param[in] p_func : �����ص�����
 * \param[in] p_arg  : �ص���������
 * \param[in] enable : �Ƿ�ʹ��
 *      \arg TURE  : ���������жϺ͸�λʹ��
 *      \arg AM_FALSE : ��ʹ�õ����⹦��
 *
 * \retval AM_OK ����ɹ�
 */
am_static_inline
int am_kl26_pmu_brownout_mkinfo (am_kl26_pmu_brownout_info_t *p_info,
                                 amhw_kl26_pmu_warn_v_sel_t   warn_v,
                                 am_kl26_pmu_rest_v_sel_t     rest_v,
                                 am_pfnvoid_t                 p_func,
                                 void                        *p_arg,
                                 am_bool_t                       enable)
{
    p_info->warn_v     = warn_v;
    p_info->rest_v     = rest_v;
    p_info->p_callfunc = p_func;
    p_info->p_arg      = p_arg;
    p_info->enable     = enable;

    return AM_OK;
}

/**
 * \brief ����LLWU����Դ��Ϣ
 * \param[in] p_info : ָ������Ϣ�ṹ��ָ��
 * \retval AM_OK ����ɹ�
 */
int am_kl26_pmu_llwu_src_cfg (am_kl26_pmu_llwu_src_info_t *p_info);
        
/**
 * \brief �������ŵĻ�����Ϣ�ṹ��
 *
 * \param[in] p_info : ָ������Ϣ�ṹ��ָ��
 * \param[in] pin    : ��������
 * \param[in] arg    : ���Ų���
 *
 * \retval AM_OK ����ɹ�
 *
 * \note ��������Ӧ����Ϊ����ģʽ���ܲ�������
 */
am_static_inline
int am_kl26_pmu_llwu_src_pin_mkinfo (am_kl26_pmu_llwu_src_info_t *p_info,
                                     amhw_fsl_llwu_pin_t         pin,
                                     amhw_fsl_llwu_pin_arg_t     arg)
{
    p_info->src        = pin | AM_SBF(0x00, 24);
    p_info->extra_info = arg;

    return AM_OK;
}

/**
 * \brief ��������ģ��Ļ�����Ϣ�ṹ��
 *
 * \param[in] p_info : ָ������Ϣ�ṹ��ָ��
 * \param[in] module : ����ģ��
 * \param[in] arg    : ģ�����
 *
 * \retval AM_OK ����ɹ�
 */
am_static_inline
int am_kl26_pmu_llwu_src_module_mkinfo (am_kl26_pmu_llwu_src_info_t *p_info,
                                        amhw_fsl_llwu_module_t      module,
                                        amhw_fsl_llwu_module_arg_t  arg)
{
    p_info->src        = module | AM_SBF(0x01, 24);
    p_info->extra_info = arg;

    return AM_OK;
}

/**
 * \brief �����˲�ͨ���Ļ�����Ϣ�ṹ��
 *
 * \param[in] p_info : ָ������Ϣ�ṹ��ָ��
 * \param[in] chan   : �˲�ͨ��
 * \param[in] pin    : ��������
 * \param[in] arg    : ͨ������
 *
 * \retval AM_OK ����ɹ�
 */
am_static_inline
int am_kl26_pmu_llwu_src_filt_mkinfo (am_kl26_pmu_llwu_src_info_t   *p_info,
                                      amhw_fsl_llwu_filt_chan_t     chan,
                                      amhw_fsl_llwu_pin_t           pin,
                                      amhw_fsl_llwu_filt_chan_arg_t arg)
{
    p_info->src         = chan | AM_SBF(0x02, 24);
    p_info->extra_info  = pin;
    p_info->extra_info |= arg << 16;

    return AM_OK;
}

/**
 * \brief LLWU�жϴ�����
 *
 * ��ȡ����Դ��־���������Դ��־���ú������жϵ���
 *
 * \retval ��
 */
void am_kl26_pmu_llwu_irq_handle (void);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_KL26_PMU_H */

/*end of file */
