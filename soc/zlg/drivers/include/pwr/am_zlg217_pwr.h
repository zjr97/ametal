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
 * \brief PWR �����ӿ�����
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-18  nwt, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG217_PWR_H
#define __AM_ZLG217_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "amhw_zlg_pwr.h"
#include "amhw_zlg217_bkp.h"

/**
 * \addtogroup am_zlg217_if_pwr
 * \copydoc am_zlg217_pwr.h
 * @{
 */

/**
 * \brief PWR ģʽ
 */
typedef enum am_zlg217_pwr_mode {
    AM_ZLG217_PWR_MODE_RUN = 0,      /**< \brief ����ģʽ */
    AM_ZLG217_PWR_MODE_SLEEP,        /**< \brief ˯��ģʽ */
    AM_ZLG217_PWR_MODE_STOP,         /**< \brief ֹͣģʽ */
    AM_ZLG217_PWR_MODE_STANBY,       /**< \brief ����ģʽ */
} am_zlg217_pwr_mode_t;

/** \brief PWR PVD ����ѹ��Ϣ���� */
typedef struct am_zlg217_pwr_pvd_info {
	amhw_zlg_pvd_lever_set_t pvd_v_level; /**< \brief PVD ����ѹѡ�� */

    /**
     *  \brief PVD ����ѹģʽ����.
     *   0����ʾ��ѹ�Ӹ��½��������趨��ֵʱ�����ж�
     *   1����ʾ��ѹ�ӵ������������趨��ֵʱ�����жϣ�
     *   2����ʾ��ѹ�������½�Խ���趨��ֵʱ�������ж�
     */
    uint8_t                     pvd_mode;

    am_bool_t                   enable;      /**< \brief �Ƿ�ʹ�� PVD ��ѹ��� */
} am_zlg217_pwr_pvd_info_t;

/**
 * \brief PWR ģʽ����������
 */
typedef struct am_zlg217_pwr_mode_init {
    am_zlg217_pwr_mode_t  pwr_mode; /**< \brief ָ�� PWR �Ĵ������ָ�� */
    int                   pin;      /**< \brief �������� */
} am_zlg217_pwr_mode_init_t;

/**
 * \brief PWR �豸��Ϣ�ṹ��
 */
typedef struct am_zlg217_pwr_devinfo {

    uint32_t  pwr_regbase;                   /**< \brief PWR �Ĵ������ַ */

    uint32_t  bkp_regbase;                   /**< \brief BKP �Ĵ������ַ */

    int       ahb_clk_num;                   /**< \brief AHB ʱ�� ID */
    int       apb1_clk_num;                  /**< \brief APB1 ʱ�� ID */
    int       apb2_clk_num;                  /**< \brief APB2 ʱ�� ID */

    uint8_t   inum;                          /**< \brief PVD �жϺ� */

    am_zlg217_pwr_mode_init_t *p_pwr_mode;   /**< \brief ָ�� PWR ģʽ�����ָ�� */

    am_zlg217_pwr_pvd_info_t  *p_pvd_info;   /**< \brief ָ�� PVD ��ѹ�����Ϣ��ָ�� */

    void (*pfn_plfm_init)(void);             /**< \brief ƽ̨��ʼ������ */

    void (*pfn_plfm_deinit)(void);           /**< \brief ƽ̨ȥ��ʼ������ */

} am_zlg217_pwr_devinfo_t;

/**
 * \brief PWR �豸�ṹ��
 */
typedef struct am_zlg217_pwr_dev {

    /** \brief ָ�� PWR �豸��Ϣָ�� */
    const am_zlg217_pwr_devinfo_t *p_pwrdevinfo;

    /** \brief PWR ģʽ */
    am_zlg217_pwr_mode_t           pwr_mode;

} am_zlg217_pwr_dev_t;

/** \brief PWR �豸����������Ͷ��� */
typedef am_zlg217_pwr_dev_t *am_zlg217_pwr_handle_t;

/**
 * \brief PWR ��ʼ��
 *
 * \param[in] p_dev     ָ�� PWR �豸�ṹ���ָ��
 * \param[in] p_devinfo ָ�� PWR �豸��Ϣ�ṹ�峣����ָ��
 *
 * \return ���� am_zlg217_pwr_handle_t ���͵ľ��
 */
am_zlg217_pwr_handle_t
am_zlg217_pwr_init (am_zlg217_pwr_dev_t           *p_dev,
                    const am_zlg217_pwr_devinfo_t *p_devinfo);

/**
 * \brief PWR ȥ��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void am_zlg217_pwr_deinit (void);

/**
 * \brief ��ȡϵͳģʽ
 *
 * \param[in] mode         PWR ģʽ���壬ֵΪ am_zlg217_pwr_mode_t ��һö������
 * \param[in] pfn_callback ���ѻص�����
 * \param[in] p_arg        ���ѻص����� ����
 *
 * \return ��
 *
 * \note ������ѵ����õ� PWR ģʽ������ am_zlg217_pwr_mode_into ������ѡ�� PWR
 *       ģʽ��ͬ���� AM_ZLG217_PWR_MODE_STANBY ģʽ�£����ѻḴλ��ע���жϻ���
 *       �����ص�������������
 */
void am_zlg217_wake_up_cfg (am_zlg217_pwr_mode_t mode,
                            am_pfnvoid_t         pfn_callback,
                            void                *p_arg);

/**
 * \brief ���� PWR ģʽ
 *
 * \param[in] mode PWR ģʽ����
 *
 * \retval  AM_OK      ģʽ�л���Ч
 * \retval  AM_ERROR   ģʽ�л�����
 * \retval -AM_EINVAL  ʽ��������
 * \retval -AM_ENOTSUP WAKE_UP Ϊ�ߵ�ƽ�����ܽ������ģʽ
 *
 * \note 1. ֻ���� WKUP Ϊ�͵�ƽ��ʱ����ܽ������ģʽ�� �Ҵ���ģʽ���Ѻ�ִ�и�λ����
 *       2. ���� PWR ģʽΪ AM_ZLG217_PWR_MODE_STANBY ʧ�ܺ�WKUP ���Żᱻ����Ϊ����
 *          ����ģʽ
 */
int am_zlg217_pwr_mode_into (am_zlg217_pwr_mode_t mode);

/**
 * \brief ��ȡ PWR ģʽ
 *
 * \param[in] ��
 *
 * \return am_zlg217_pwr_mode_t ��һö�����͵�ֵ
 */
am_zlg217_pwr_mode_t am_zlg217_pwr_mode_get (void);

/**
 * \brief ���� PVD ��ѹ�����Ϣ
 *
 * \param[in] pwr_handle   PWR ��Դ�����豸���
 * \param[in] pfn_callback ��ѹ���ص�����
 * \param[in] p_arg        ��ѹ���ص���������
 *
 * \retval AM_OK �������óɹ�
 */
int am_zlg217_pwr_pvd_cfg (am_zlg217_pwr_handle_t pwr_handle,
                           am_pfnvoid_t           pfn_callback,
                           void                  *p_arg);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG217_PWR_H */

/* end of file */
