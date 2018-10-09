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
 * \brief DAC����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-26  mkr, first implementation.
 * \endinternal
 */

#include "am_fsl_dac.h"
#include "am_int.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

#define __FSL_DAC_HW_DECL(p_hw_dac, p_drv)    \
             amhw_fsl_dac_t *p_hw_dac =       \
            ((am_fsl_dac_dev_t *)p_drv)->p_devinfo->p_hw_dac

#define __FSL_DAC_BITS_GET(p_drv)             \
        (((am_fsl_dac_dev_t *)p_drv)->p_devinfo->bits)

#define __FSL_DAC_VREF_GET(p_drv)             \
        (((am_fsl_dac_dev_t *)p_drv)->p_devinfo->vref)

/*******************************************************************************
* ��������
*******************************************************************************/
static uint32_t __fsl_dac_get_bits (void *p_drv);

static uint32_t __fsl_dac_get_vref (void *p_drv);

static int __fsl_dac_val_set (void *p_drv, int chan, uint32_t value);

static int __fsl_dac_enable (void *p_drv, int chan );

static int __fsl_dac_disable (void *p_drv, int chan );

/**
 * \brief DAC������
 */
static const struct am_dac_drv_funcs __g_dac_drvfuncs = {
       __fsl_dac_get_bits,
       __fsl_dac_get_vref,
       __fsl_dac_val_set,
       __fsl_dac_enable,
       __fsl_dac_disable
};

/******************************************************************************/
/**
 * \brief ��ȡDACת�����ȡ�
 */
static uint32_t __fsl_dac_get_bits (void *p_drv)
{
    return (uint32_t)__FSL_DAC_BITS_GET(p_drv);
}

/**
 * \brief ��ȡDAC�ο���ѹ��
 */
static uint32_t __fsl_dac_get_vref (void *p_drv)
{
    return (uint32_t)__FSL_DAC_VREF_GET(p_drv);
}

/**
 * \brief ����ͨ����DACת��ֵ��
 */
int __fsl_dac_val_set (void *p_drv, int chan, uint32_t value)
{
    __FSL_DAC_HW_DECL(p_hw_dac, p_drv);
    am_fsl_dac_dev_t *p_dev = (am_fsl_dac_dev_t *)p_drv;

    if (p_dev == NULL ) {
        return -AM_EINVAL;
    }

    if (chan != 0) {
        return -AM_ENXIO;       /* ��Ч��ͨ��ֵ      */
    }

    p_dev->chan = chan;
    amhw_fsl_dac_dat_set(p_hw_dac, AMHW_FSL_DAC_DAT_0, value);

    return AM_OK;
}

/**
 * \brief ����DACת��
 */
static int __fsl_dac_enable (void *p_drv, int chan )
{
    __FSL_DAC_HW_DECL(p_hw_dac, p_drv);
    am_fsl_dac_dev_t *p_dev = (am_fsl_dac_dev_t *)p_drv;

    if (p_dev == NULL ) {
        return -AM_EINVAL;
    }

    if (chan != 0) {
        return -AM_ENXIO;       /* ��Ч��ͨ��ֵ       */
    }

    p_dev->chan = chan;

    amhw_fsl_dac_enable(p_hw_dac);  /* ʹ��DAC     */

    return AM_OK;
}

/**
 * \brief ��ֹDACת��
 */
static int __fsl_dac_disable (void *p_drv, int chan )
{
    __FSL_DAC_HW_DECL(p_hw_dac, p_drv);
    am_fsl_dac_dev_t *p_dev = (am_fsl_dac_dev_t *)p_drv;

    if (p_dev == NULL ) {
        return -AM_EINVAL;
    }

    if (chan != 0) {
        return -AM_ENXIO;         /* ��Ч��ͨ��ֵ */
    }

    p_dev->chan = chan;

    amhw_fsl_dac_disable(p_hw_dac);  /* ����DAC        */

    return AM_OK;
}

/**
 * \brief DAC��ʼ��
 */
am_dac_handle_t am_fsl_dac_init (am_fsl_dac_dev_t           *p_dev,
                                  const am_fsl_dac_devinfo_t *p_devinfo)
{

    if ((p_devinfo == NULL) || (p_dev == NULL)) {
        return NULL;
    }

    p_dev->p_devinfo         = p_devinfo;
    p_dev->dac_serve.p_funcs = &__g_dac_drvfuncs;
    p_dev->dac_serve.p_drv   = p_dev;

    p_dev->chan              = AMHW_FSL_DAC0_CHAN_0;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /*
     * ����DAC��ع���
     */
    amhw_fsl_dac_c0_cfg(p_devinfo->p_hw_dac,
                         AMHW_FSL_DAC_C0_VREF_SEL(p_devinfo->vref_source) |
                         AMHW_FSL_DAC_C0_TRG_SOFT_EN                      |
                         AMHW_FSL_DAC_C0_POWER_SEL(AMHW_FSL_DAC_POWER_LOW));
    amhw_fsl_dac_disable(p_devinfo->p_hw_dac);

    return (am_dac_handle_t)(&(p_dev->dac_serve));
}

/**
 * \brief DACȥ��ʼ��
 */
void am_fsl_dac_deinit (am_dac_handle_t handle)
{
    am_fsl_dac_dev_t *p_dev = (am_fsl_dac_dev_t *)handle;

    p_dev->dac_serve.p_funcs = NULL;
    p_dev->dac_serve.p_drv   = NULL;

    amhw_fsl_dac_disable(p_dev->p_devinfo->p_hw_dac);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
