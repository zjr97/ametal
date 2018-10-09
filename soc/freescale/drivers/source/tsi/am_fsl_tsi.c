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
 * \brief TSI implementation
 *
 * 1. �缫��Ƶ�ʼ��㹫ʽ��
 *                        I(�㶨����)
 *      F(elec) = ---------------------------------
 *                  2 * C(�缫����) * V(��ѹ����)
 *
 * 2. �ο���Ƶ�ʼ��㹫ʽ��
 *                        I(�ο��㶨����)
 *      F(ref)  = --------------------------------------
 *                  2 * C(�ڲ��ο�����) * V(��ѹ����)
 *
 * 3. ����ʱ����㹫ʽ��
 *                 2 * PS(��Ƶ��) * NSCN(ɨ�����) * C(�缫����) * V(��ѹ����)
 *      T(samp) = -----------------------------------------------------------------
 *                                  I(�㶨����)
 * \internal
 * \par Modification history
 * - 1.01 16-09-26  nwt, make some changes.
 * - 1.00 15-10-21  wxj, first implementation.
 * \endinternal
 */

#include "am_fsl_tsi.h"

/** \brief ����ָ��TSI��Ϣ��ָ�� */
#define __TSI_DEVINFO_DECL(p_tsi_devinfo, p_dev)  \
        const am_fsl_tsi_devinfo_t *p_tsi_devinfo = p_dev->p_devinfo


/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief ָ��TSI�豸��ָ�� */
am_fsl_tsi_dev_t *__gp_tsi_dev;

/*******************************************************************************
  �ڲ���������
*******************************************************************************/

static uint16_t __am_fsl_tsi_basevale_get (void);
static void __am_fsl_tsi_thresh_set (uint16_t val_h, uint16_t val_l);

/**
 * \brief TSI����ͨ���ϡ����޷�ֵ
 */
void __am_fsl_tsi_thresh_set (uint16_t val_h, uint16_t val_l)
{
    __TSI_DEVINFO_DECL(p_tsi_devinfo, __gp_tsi_dev);

    amhw_fsl_tsi_wake_chan_thresholdh_write(p_tsi_devinfo->p_hw_tsi, val_h);
    amhw_fsl_tsi_wake_chan_thresholdl_write(p_tsi_devinfo->p_hw_tsi, val_l);
}

/**
 * \brief TSI �Զ���⣬��ȡ��ǰ������δ����ʱ�ļ��ֵ
 */
uint16_t __am_fsl_tsi_basevale_get ()
{
    uint16_t trigger_backup;    /* ���津����ʽ */
    uint16_t calib_val[10];     /* ���10�μ��ֵ */
    uint16_t base_val = 0;      /* ��ŵ�ǰ�����µĻ���ֵ */
    uint16_t i = 0;             /* ѭ������ */
    
    __TSI_DEVINFO_DECL(p_tsi_devinfo, __gp_tsi_dev);

    /* ��ȡ���õĴ�����ʽ */
    if(amhw_fsl_tsi_scan_trig_get(p_tsi_devinfo->p_hw_tsi)) {
        trigger_backup = AM_TRUE;          /* Ӳ������ */
    } else {
        trigger_backup = AM_FALSE;         /* ������� */
    }
    
    /* ���ɨ�������־ */
    amhw_fsl_tsi_eosf_clr(p_tsi_devinfo->p_hw_tsi);

    /* ����Ϊ�������ɨ�� */
    amhw_fsl_tsi_scan_trig_set(p_tsi_devinfo->p_hw_tsi,AMHW_FSL_TSI_TRIG_SOFTWARE);

    for (i = 0; i<10; i++) {

        /* �����������ɨ�� */
        amhw_fsl_tsi_soft_tirg_start(p_tsi_devinfo->p_hw_tsi);

        /* ��ȡɨ�������־,�ȴ�ɨ����� */
        while ( !amhw_fsl_tsi_eosf_get(p_tsi_devinfo->p_hw_tsi));

        /* ��ȡû�д���ʱ��ֵ */
        calib_val[i] = amhw_fsl_tsi_convert_value_get(p_tsi_devinfo->p_hw_tsi);

        base_val = base_val + calib_val[i];

        /* ��ɨ�������־ */
        amhw_fsl_tsi_eosf_clr(p_tsi_devinfo->p_hw_tsi);
    }
      
    /* �ָ�Ϊ���õĴ�����ʽ */
    if (trigger_backup == AM_TRUE) {
        amhw_fsl_tsi_scan_trig_set(p_tsi_devinfo->p_hw_tsi, AMHW_FSL_TSI_TRIG_HAEDWARE);
    } 
    
    /* ���ػ���ƽ��ֵ */
    return (base_val / 10);
}

/**
 * \brief TSI ����������
 */
void am_fsl_tsi_sens_set (uint16_t val)
{

    uint16_t base_val;                      /* ��Ż�����ֵ */
    uint16_t tshd_val, tsld_val;            /* ������õ���/���޷�ֵ */
    
    base_val = __am_fsl_tsi_basevale_get();   /* ��ȡ����ת��ֵ */
    
    tshd_val = val + base_val;              /* ����Ϊ����ֵ�ӻ���ֵ */
    tsld_val = base_val - base_val / 2;     /* ����Ϊ����ֵ��һ�� */

    /* д����/����ֵ */
    __am_fsl_tsi_thresh_set(tshd_val,tsld_val);
}

/**
 * \brief TSI�жϴ���ģʽ
 */
void am_fsl_tsi_trigger_cfg (amhw_fsl_tsi_irq_mode_t flag)
{
    __TSI_DEVINFO_DECL(p_tsi_devinfo, __gp_tsi_dev);

    amhw_fsl_tsi_int_mode_set (p_tsi_devinfo->p_hw_tsi, flag);
}

/**
 * \brief TSI�ж�ʹ��
 */
void am_fsl_tsi_int_enable (void)
{
    __TSI_DEVINFO_DECL(p_tsi_devinfo, __gp_tsi_dev);

    /* TSI�ж�ʹ�� */
    amhw_fsl_tsi_int_enable(p_tsi_devinfo->p_hw_tsi);

    /* ϵͳ�ж�ʹ�� */
    am_int_enable(p_tsi_devinfo->inum);
}

/**
 * \brief TSI�н���
 */
void am_fsl_tsi_int_disable (void)
{
    __TSI_DEVINFO_DECL(p_tsi_devinfo, __gp_tsi_dev);

    /* TSI �жϽ��� */
    amhw_fsl_tsi_int_disable(p_tsi_devinfo->p_hw_tsi);
    
    /* ϵͳ�жϽ��� */
    am_int_enable(p_tsi_devinfo->inum);
}

/**
 * \brief �����жϻص�����
 */
int am_fsl_tsi_trigger_connect (am_pfnvoid_t pfn_callback)
{
    __TSI_DEVINFO_DECL(p_tsi_devinfo, __gp_tsi_dev);
    int key;

    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();

    /* ���ӻص����� */
    am_int_connect(p_tsi_devinfo->inum, pfn_callback, NULL);

    /* ���ж� */
    am_int_cpu_unlock(key);

     return AM_OK;
}

/**
 * \brief TSI ��������
 */
int am_fsl_tsi_fun_cfg (amhw_fsl_tsi_channel_t    chan,
                         amhw_fsl_tsi_mode_t       work_mode,
                         amhw_fsl_tsi_trig_mode_t  trig_mode)
{
    __TSI_DEVINFO_DECL(p_tsi_devinfo, __gp_tsi_dev);

    /* ʹ��TSIͨ�� */
    amhw_fsl_tsi_chan_set(p_tsi_devinfo->p_hw_tsi, chan);

    /* ����TSI����ģʽ */
    amhw_fsl_tsi_mode_set(p_tsi_devinfo->p_hw_tsi, work_mode);

    /* ���ô���ɨ��ģʽ */
    amhw_fsl_tsi_scan_trig_set(p_tsi_devinfo->p_hw_tsi, trig_mode);

    /* �͹��Ļ��ѹ��� */
    if(p_tsi_devinfo->lp_mode == AM_TRUE) {
        amhw_fsl_tsi_lowpower_enable(p_tsi_devinfo->p_hw_tsi);
    }

    /* ���õ�ѹ����Ϊ600mV(Vp - Vm) */
    amhw_fsl_tsi_dvolt_set (p_tsi_devinfo->p_hw_tsi, AMHW_FSL_TSI_DV073);

    /* ɨ��Ԥ��Ƶ����Ϊ2��Ƶ */
    amhw_fsl_tsi_oscfreq_div_set(p_tsi_devinfo->p_hw_tsi, AMHW_FSL_TSI_OSCFRQ_DIV_2);

    /* ���õ缫ɨ�����Ϊ16 */
    amhw_fsl_tsi_scan_num_set(p_tsi_devinfo->p_hw_tsi, 16);

    /* �����ⲿ�����㶨����Ϊ16uA */
    amhw_fsl_tsi_extchrg_val_set(p_tsi_devinfo->p_hw_tsi, AMHW_FSL_TSI_EXTCHRG_16UA);

    /* ���òο������㶨����ԴΪ12uA ,��ο�ʱ��Ϊ10MHz*/
    amhw_fsl_tsi_refchrg_val_set(p_tsi_devinfo->p_hw_tsi, AMHW_FSL_TSI_REFCHRG_32UA);

    return AM_OK;
}

/**
 * \brief TSI��ʼ��
 */
int am_fsl_tsi_init (am_fsl_tsi_dev_t *p_dev, const am_fsl_tsi_devinfo_t *p_devinfo)
{

    if (p_devinfo == NULL || p_devinfo->p_hw_tsi == NULL) {
        return -AM_EINVAL;
    }

    p_dev->p_devinfo = p_devinfo;

    __gp_tsi_dev = p_dev;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    if (p_devinfo->lp_mode != AM_FALSE) {
        /* ��ӵ͹���ģʽ�¼����������� */
        amhw_fsl_tsi_lowpower_enable(p_devinfo->p_hw_tsi);
    }

    /* �жϽ��� */
    amhw_fsl_tsi_int_disable(p_devinfo->p_hw_tsi);

    /* ʹ��TSIģ�� */
    amhw_fsl_tsi_mode_enable(p_devinfo->p_hw_tsi);

    return AM_OK;
}

/**
 * \brief TSI ���ʼ��
 */
void am_fsl_tsi_deinit (am_fsl_tsi_dev_t *p_dev)
{
    amhw_fsl_tsi_t *p_hw_tsi = p_dev->p_devinfo->p_hw_tsi;

    const am_fsl_tsi_devinfo_t *p_devinfo = p_dev->p_devinfo;

    if (p_devinfo->pfn_plfm_deinit) {
        p_devinfo->pfn_plfm_deinit();
    }

    /* �жϽ��� */
    amhw_fsl_tsi_int_disable(p_hw_tsi);

    /* ����TSIģ�� */
    amhw_fsl_tsi_mode_disable(p_hw_tsi);
}


/* end of file */
