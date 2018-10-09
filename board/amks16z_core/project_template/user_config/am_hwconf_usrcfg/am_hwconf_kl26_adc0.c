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
 * \brief FSL ADC �û������ļ���
 * \sa am_kl26_hwconfig_adc0.c
 *
 * \internal
 * \par Modification history
 * - 1.00 16-10-09  mkr, first implementation.
 * \endinternal
 */
#include "hw/amhw_fsl_adc.h"
#include "hw/amhw_kl26_sim.h"
#include "am_fsl_adc.h"
#include "am_kl26.h"
#include "am_gpio.h"
#include "kl26_pin.h"

/**
 * \brief ADC ģʽ���ã�Ĭ�Ͽ����������
 *
 * \note һ��ֻ�ܿ�������һ��ģʽ����Ҫʹ������ģʽ��ֻ�轫��ӦADCģʽ��ע�ͷ�ȥ�����ɡ�
 *       ���ʹ��Ӳ������ģʽ����Ӧ����ƽ̨��ʼ��������ѡ��Ӳ������Դ���������ʼ����Ӧ��Ӳ����
 * 		  ���ͬʱ����������ģʽ����Ϊ���������ģʽ����������ģʽ��û��������Ϊ���������ģʽ��
 */
#define AM_FSL_ADC_SW_TRG           /**< \brief ADC �������  */
//#define AM_FSL_ADC_HW_TRG           /**< \brief ADC Ӳ������ */

/**
 * \name ADC ��������
 * @{
 */
//#define AM_FSL_ADC_FUN_CMP_EN       /**< \brief ʹ�ܱȽϹ��� */
//#define AM_FSL_ADC_FUN_AVG_EN       /**< \brief ʹ��Ӳ��ƽ������  */
//#define AM_FSL_ADC_FUN_DIF_EN       /**< \brief ʹ�ܲ�ֹ��� */

/** @} */

/**
 * \addtogroup am_kl26_if_hwconfig_src_adc0
 * \copydoc am_kl26_hwconfig_adc0.c
 * @{
 */

/**
 * \brief ADC ƽ̨��ʼ����
 *
 * \note ���ĳ������֧�ֲ��ģʽ����ô�����������Ź����⣬��Ҫѡ��ʹ��Aͨ������Bͨ����
 */
static void __fsl_plfm_adc0_init (void)
{
    /* ʹ��ADCʱ�ӡ���ADC��ؼĴ����Ĳ���һ��Ҫ��ʹ��ADCʱ��֮�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_ADC0);

#ifdef AM_FSL_ADC_FUN_DIF_EN
    /* ����PIOE_20ΪADC0_DP0���� */
    am_gpio_pin_cfg(PIOE_20, PIOE_20_ADC0_DP0);

    /* ����PIOE_21ΪADC0_DM0���� */
    am_gpio_pin_cfg(PIOE_21, PIOE_21_ADC0_DM0);
#else
    /* ����PIOE_29ΪADC0_SE0���� */
    am_gpio_pin_cfg(PIOE_29, PIOE_29_ADC0_SE4B);

	/**\brief ѡ��ͨ��B */
	amhw_fsl_adc_seq_set(KL26_ADC0, AMHW_FSL_ADC_MUXSEL_B);

#endif
    /* ��ADC����У׼                */
    amhw_fsl_adc_calibrate(KL26_ADC0, CLK_BUS);

    /**
     * \note
     * ������Ҫ���ò�����ͨ����
     * ADCͨ��4~7�ֱ��Ӧ�������͵�ͨ�����ֱ�Ϊa��b��
     * ������Ҫ���������muxsel��ϵͳĬ�������ʹ�õ���aͨ����
     * ����Ҫʹ��bͨ��ʱ����Ҫ���������������䣬����bͨ��
     * ����Ҫʹ��PIOD_6ͨ����ΪADCͨ��7��Bͨ��ʹ��ʱ�������������£�
     *
     * am_gpio_pin_cfg (PIOD_6, PIOD_6_ADC0_SE7B);
     *
     * amhw_fsl_adc_seq_set((amhw_fsl_adc_t *)KL26_ADC0, AMHW_FSL_ADC_MUXSEL_B);
     */

#if defined(AM_FSL_ADC_HW_TRG)

    /**
     * ʹ��ADCӲ����ѡ����Դ��ѡ��TPM2�������
     * ʹ�ö�ʱ����Ҫ���г�ʼ�����ã���Ϊʹ��TPM2��Ϊ�����ʱ����
     * �ڳ�ʼ�������ʱ��ʱ�������TPM2��ʱ���ĳ�ʼ��
     */
    amhw_kl26_sim_adc0_alter_trigger_enable();
    amhw_kl26_sim_adc0_trigger_set(KL26_SIM_ADC0_TRIGGER_TPM2);

#endif

}

/**
 * \brief ADC ƽ̨ȥ��ʼ����
 */
static void __plfm_adc0_deinit (void)
{
    /* �ر�ADCģ���ϵ�                */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_ADC0);
}

/**
 * \brief ADC �豸��Ϣ�ṹ��
 * @{
 */

#ifdef AM_FSL_ADC_FUN_AVG_EN
/** \brief ADC Ӳ��ƽ������������Ϣ�ṹ�� */
static const am_fsl_adc_avg_info_t __g_adc0_avg_info = {
    AM_FSL_ADC_AVG_EN,          /* ����Ӳ��ƽ������ */
    AMHW_FSL_ADC_AVGS_32,       /* ÿ��ƽ��32������ֵ */
};
#endif

#ifdef AM_FSL_ADC_FUN_CMP_EN
/** \brief ADC �ȽϹ���������Ϣ�ṹ�� */
static const am_fsl_adc_cmp_info_t __g_adc0_cmp_info = {
    AM_FSL_ADC_CMP_EN,          /* �����Ƚ� */
    AM_FSL_ADC_CMP_MODE_6,      /* �Ƚ�����Ϊ "res <= a" ����  "res >= b" */
    ((1 << 16) - 1) / 3,         /* �ο��ĵ�ѹ��1/3�� */
    (((1 << 16) - 1) << 1) / 3,  /* �ο��ĵ�ѹ��2/3�� */
};
#endif

/** \brief ADC �豸��Ϣ  */
static const am_fsl_adc_devinfo_t __g_adc0_devinfo =
{
    KL26_ADC0,                /**< \brief ָ��ADC0�Ĵ������ָ�� */
    2500,                          /**< \brief ADC�ο���ѹ����λ��mV  */
    16,                            /**< \brief ADC��������(λ��)   */

	/* ѡ���ֻ��ߵ���ģʽ */
#ifdef AM_FSL_ADC_DIF_EN
	AM_FSL_ADC_DIFF_EN,            /**< \brief ADC0���ģʽ        */
#else
    AM_FSL_ADC_DIFF_DIS,           /**< \brief ADC0����ģʽ        */
#endif

    INUM_ADC0,                     /**< \brief ADC�ж�������  */

	/* ѡ���������Ӳ������ģʽ */
#ifdef AM_FSL_ADC_SW_TRG
    AM_FSL_ADC_MODE_TRG_SF,        /**< \brief ADC�������ģʽ      */
#elif defined(AM_FSL_ADC_HW_TRG)
	AM_FSL_ADC_MODE_TRG_HW,        /**< \brief ADCӲ������ģʽ      */
#else
	AM_FSL_ADC_MODE_TRG_SF,
#endif

    AMHW_FSL_ADC_SEQ_A,            /**< \brief ADC��������            */
    DMA_CHAN_0,                    /**< \brief DMAͨ��0���䣬ֵΪ-1ʱ��ʹ��DMA */
    CLK_BUS,                       /**< \brief ADC��ʱ��Դ ��һ�㶼��BUS�� */

	/* ѡ���Ƿ�ʹ��Ӳ��ƽ������ */
#ifdef AM_FSL_ADC_FUN_AVG_EN
	&__g_adc0_avg_info,
#else
    NULL,                          /**< \brief ��ʹ��Ӳ��ƽ������       */
#endif

	/* ѡ���Ƿ�ʹ�ñȽϹ��� */
#ifdef AM_FSL_ADC_FUN_CMP_EN
	&__g_adc0_cmp_info,
#else
    NULL,                          /**< \brief ��ʹ�ñȽϹ���       */
#endif
    __fsl_plfm_adc0_init,

    __plfm_adc0_deinit,

};


/** @} */

/** \brief ADC0�豸ʵ�� */
static am_fsl_adc_dev_t __g_adc0_dev;

/**
 * \brief ADC0 ʵ����ʼ�������ADC��׼������
 *
 * \return ��
 */
am_adc_handle_t am_kl26_adc0_inst_init (void)
{
    return am_fsl_adc_init(&__g_adc0_dev, &__g_adc0_devinfo);
}

/**
 * \brief ADC0 ʵ�����ʼ��
 * \param[in] handle : ADC0���ֵ
 *
 * \return ��
 */
void am_kl26_adc0_inst_deinit (am_adc_handle_t handle)
{
    am_fsl_adc_deinit(handle);
}


/**
 * @}
 */

/* end of file */
