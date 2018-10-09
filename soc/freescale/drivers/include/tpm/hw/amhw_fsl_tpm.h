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
 * \brief ��ʱ��/PWMģ�飨TPM�������ӿ�
 *
 * 1. TPM��ʱ��ģʽ�ǿ�ѡ�ģ�
 *    -�ܹ���ÿ���첽����ʱ�����ϲ�������
 *    -�ܹ����ⲿʱ������ͬ�����첽ʱ�Ӽ�������������������
 * 2. Ԥ��Ƶ����Ƶ���ӿ�ѡ1,2,4,8,16,32,64��128;
 * 3. TPM����һ��16λ�ļ�������
 *    -������һ���������еļ�������ģ������
 *    -�������ó����ϼ��������������¼���
 * 4. ����6��ͨ����ÿ��ͨ����������λ���벶������Ƚϻ���ض���PWMģʽ��
 *    -�����벶��ģʽ�У����������Է����������ء��½��ػ�������/�½���
 *    -������Ƚ�ģʽ�У�ƥ��ʱ����ʹ����ź���λ�����㡢������߷�ת
 *    -����ͨ���������ó����Ķ���PWMģʽ
 * 5. ÿ��ͨ��֧�ֲ����жϺ�DMA����;
 * 6. �����������ʱ֧�ֲ����жϺ�DMA����;
 * 7. ֧�ֿ�ѡ��Ĵ�����������λ���ߵ��¼������������ӣ�
 *    -�����������ʱ����ѡ��ֹͣ����
 * 8. �����������ʱ��֧�ֲ���Ӳ������;
 *
 *            TPMģʽ�����ء���ƽ���ñ�(stat_ctl�Ĵ�����ͨ��stat_ctl�Ĵ���)
 * ==========================================================================
 * | CPWMS | MSnB:MSnA | ELSnB:ELSnA |      Mode        |       ����
 * ==========================================================================
 * |   x   |     00    |      00     |      None        |     ͨ����ֹ
 * --------------------------------------------------------------------------
 * |   x   |     01    |      00     | Software compare |      ������
 * --------------------------------------------------------------------------
 * |       |           |      01     |                  |  ֻ����������
 * -       -           ---------------                  ---------------------
 * |       |     00    |      10     |  input capture   |  ֻ�����½���
 * -       -           ---------------                  ---------------------
 * |       |           |      11     |                  |  ��������\�½���
 * -       ------------------------------------------------------------------
 * |       |           |      01     |                  |  ƥ��ʱ�����ת
 * -       -           ---------------                  ---------------------
 * |   0   |     01    |      10     |  output compare  |  ƥ��ʱ���Ϊ��
 * -       -           ---------------                  ---------------------
 * |       |           |      11     |                  |  ƥ��ʱ���Ϊ��
 * -       ------------------------------------------------------------------
 * |       |           |      10     |                  |  High-true����
 * -       -     10    --------------- Edge-aligned PWM ---------------------
 * |       |           |      X1     |                  |  Low-true����
 * -       ------------------------------------------------------------------
 * |       |           |      10     |                  |  ƥ��ʱ�������Ϊ��
 * -       -     11    --------------- Output compare   ---------------------
 * |       |           |      01     |                  |  ƥ��ʱ�������Ϊ��
 * --------------------------------------------------------------------------
 * |       |           |      10     |                  |  High-true����
 * -   1   -     10    --------------- Edge-aligned PWM ---------------------
 * |       |           |      01     |                  |  Low-true����
 * --------------------------------------------------------------------------
 */

/*
 * \internal
 * \par Modification History
 * - 1.00 16-09-13  sdy, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_TPM_H
#define __AMHW_FSL_TPM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

/**
 * \addtogroup amhw_fsl_if_tpm
 * \copydoc amhw_fsl_tpm.h
 * @{
 */

/* ʹ������������ν��� */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif


/**
 * \brief TPMͨ����
 */
#define AMHW_FSL_TPM_CHANNELS_NUM      (6)

/**
 * \brief TPMͨ��ID,���ڲ��������ĳ��ͨ����
 * ��Ч��Χ��0 ~ (AMHW_FSL_TPM_CHANNELS_NUM - 1)
 */
#define AMHW_FSL_TPM_CH(n)             ((n) < AMHW_FSL_TPM_CHANNELS_NUM ? (n) : 0)


/**
 * \brief TPM�Ĵ�����ṹ��
 */
typedef struct amhw_fsl_tpm {
    __IO uint32_t stat_ctl;             /**< \brief ״̬�Ϳ��� */
    __IO uint32_t counter;              /**< \brief ����ֵ */
    __IO uint32_t modulo;               /**< \brief ģ�� */

    struct {
        __IO uint32_t stat_ctl;         /**< \brief ͨ������ */
        __IO uint32_t value;            /**< \brief ͨ��ֵ */
    } chan_ctl[6];                      /**< \brief tpmͨ������ */

    __I  uint32_t reserved_0[5];        /**< \brief ���� */
    __IO uint32_t status;               /**< \brief ״̬�Ĵ��� */
    __I  uint32_t reserved_1[12];       /**< \brief ���� */
    __IO uint32_t config;               /**< \brief ���üĴ��� */

} amhw_fsl_tpm_t;


/**
 * \name ״̬�Ϳ��ƼĴ���λ����(R/W)
 * @{
 */

#define AMHW_FSL_TPM_SC_MASK       (0x1FFu)           /**< \brief ״̬�Ϳ������� */
#define AMHW_FSL_TPM_SC_DMA_EN     (1UL << 8)         /**< \brief DMAʹ�ܣ������ */
#define AMHW_FSL_TPM_SC_TO_FLAG    (1UL << 7)         /**< \brief ��ʱ�������־ */
#define AMHW_FSL_TPM_SC_TOI_EN     (1UL << 6)         /**< \brief ��ʱ������ж�ʹ�� */
#define AMHW_FSL_TPM_SC_CPWM_MODE  (1UL << 5)         /**< \brief TPM ����ģʽ */
#define AMHW_FSL_TPM_SC_CM_SEL(s)  (((s) & 0x3) << 3) /**< \brief ʱ��ģʽѡ�� */
#define AMHW_FSL_TPM_SC_PS_SEL(s)  (((s) & 0x7) << 0) /**< \brief Ԥ��Ƶ����ѡ�� */

/** @} */

/**
 * \brief TPMʱ��ģʽѡ��
 * \note ��λ�򱻱�������������������ֹʱ�ſ�д��
 */
typedef enum amhw_fsl_tpm_clock_mode {
    AMHW_FSL_TPM_CLK_SRC_NONE     = 0x0,         /**< \brief ����ģ����� */
    AMHW_FSL_TPM_CLK_SRC_MODULE   = 0x1,         /**< \brief ѡ��ģ��ʱ�Ӳ�ʹ�� */
    AMHW_FSL_TPM_CLK_SRC_EXTERNAL = 0x2,         /**< \brief �ⲿʱ�� */
} amhw_fsl_tpm_clock_mode_t;

/**
 * \brief TPM����ģʽ
 */
typedef enum amhw_fsl_tpm_counting_mode {
    AMHW_FSL_TPM_COUNTING_UP      = 0x0,         /**< \brief ���ϼ���������ģʽ */
    AMHW_FSL_TPM_COUNTING_UP_DOWN = 0x1,         /**< \brief ����-���¼��������Ķ��� */
} amhw_fsl_tpm_counting_mode_t;

/**
 * \brief TPM Ԥ��Ƶ����ѡ��
 * \note ��λ�򱻱�������������������ֹʱ�ſ�д��
 */
typedef enum amhw_fsl_tpm_prescale {
    AMHW_FSL_TPM_DIVIDED_BY_1   = 0x0,              /**< \brief Ԥ��Ƶ����Ϊ1 */
    AMHW_FSL_TPM_DIVIDED_BY_2   = 0x1,              /**< \brief Ԥ��Ƶ����Ϊ2 */
    AMHW_FSL_TPM_DIVIDED_BY_4   = 0x2,              /**< \brief Ԥ��Ƶ����Ϊ4 */
    AMHW_FSL_TPM_DIVIDED_BY_8   = 0x3,              /**< \brief Ԥ��Ƶ����Ϊ8 */
    AMHW_FSL_TPM_DIVIDED_BY_16  = 0x4,              /**< \brief Ԥ��Ƶ����Ϊ16 */
    AMHW_FSL_TPM_DIVIDED_BY_32  = 0x5,              /**< \brief Ԥ��Ƶ����Ϊ32 */
    AMHW_FSL_TPM_DIVIDED_BY_64  = 0x6,              /**< \brief Ԥ��Ƶ����Ϊ64 */
    AMHW_FSL_TPM_DIVIDED_BY_128 = 0x7,              /**< \brief Ԥ��Ƶ����Ϊ128 */
} amhw_fsl_tpm_prescale_t;

/**
 * \brief ״̬�Ϳ����趨
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_TPM_SC_* ��ֵ����
 *                       AMHW_FSL_TPM_SC_*��� ��OR��ֵ(#AMHW_FSL_TPM_SC_DMA_EN)
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_ctrl_set (amhw_fsl_tpm_t *p_hw_tpm, uint32_t flags)
{
    p_hw_tpm->stat_ctl |= (flags & AMHW_FSL_TPM_SC_MASK);
}

/**
 * \brief ״̬�Ϳ������
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_TPM_SC_* ��ֵ����
 *                       AMHW_FSL_TPM_SC_*��� ��OR��ֵ(#AMHW_FSL_TPM_SC_DMA_EN)
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_ctrl_clear (amhw_fsl_tpm_t *p_hw_tpm, uint32_t flags)
{
    p_hw_tpm->stat_ctl &= ~(flags & AMHW_FSL_TPM_SC_MASK);
}

/**
 * \brief ʱ��ģʽ
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] mode     : AMHW_FSL_TPM_SC_* ��ֵ����
 *                       AMHW_FSL_TPM_SC_*��� ��OR��ֵ(#AMHW_FSL_TPM_SC_DMA_EN)
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_clock_mode (amhw_fsl_tpm_t            *p_hw_tpm,
                               amhw_fsl_tpm_clock_mode_t  mode)
{
    AM_BITS_SET(p_hw_tpm->stat_ctl, 3, 2, mode);
}

/**
 * \brief Ԥ��Ƶ����
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] prescale : Ԥ��Ƶֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_prescale_set (amhw_fsl_tpm_t          *p_hw_tpm,
                                amhw_fsl_tpm_prescale_t  prescale)
{
    AM_BITS_SET(p_hw_tpm->stat_ctl, 0, 3, prescale);
}

/**
 * \brief Ԥ��Ƶ��ȡ
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \return Ԥ��Ƶֵ��ö������amhw_tpm_prescale_t��Ա
 */
am_static_inline
amhw_fsl_tpm_prescale_t amhw_tpm_prescale_get (amhw_fsl_tpm_t *p_hw_tpm)
{
    return (amhw_fsl_tpm_prescale_t)AM_BITS_GET(p_hw_tpm->stat_ctl, 0, 3);
}

/**
 * \brief ״̬�Ϳ��ƻ�ȡ
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \return ״̬�Ϳ��ƣ��ο�AMHW_FSL_TPM_SC_#��
 */
am_static_inline
uint32_t amhw_fsl_tpm_ctrl_get (amhw_fsl_tpm_t *p_hw_tpm)
{
    return p_hw_tpm->stat_ctl;
}

/**
 * \name �����Ĵ�������
 * @{
 */

#define AMHW_FSL_TPM_CNT_MASK       (0xFFFFu)           /**< \brief ����ֵ���� */

/** @} */

/**
 * \brief �������ֵ��д���κ�ֵ��������
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_count_clear (amhw_fsl_tpm_t *p_hw_tpm)
{
    p_hw_tpm->counter = 0x00;
}

/**
 * \brief ��ȡ������ֵ
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \return ����ֵ
 */
am_static_inline
uint16_t amhw_fsl_tpm_count_get (amhw_fsl_tpm_t *p_hw_tpm)
{
    return p_hw_tpm->counter;
}

/**
 * \name ģ���Ĵ�������(R/W)
 * @{
 */

#define AMHWV_TPM_MOD_MASK       (0xFFFFu)           /**< \brief ģ������ */

/** @} */

/**
 * \brief �趨ģ��ֵ
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] value    : ��Ҫ�趨��ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_mod_set (amhw_fsl_tpm_t *p_hw_tpm, uint16_t value)
{
    p_hw_tpm->modulo = value;
}

/**
 * \brief ��ȡģ��ֵ
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \return ģ��ֵ
 */
am_static_inline
uint16_t amhw_fsl_tpm_mod_get (amhw_fsl_tpm_t *p_hw_tpm)
{
    return p_hw_tpm->modulo;
}

/**
 * \name ͨ��״̬�Ϳ���(R/W)
 * @{
 */

#define AMHW_FSL_TPM_CnSC_MASK      (0xFFu)             /**< \brief ģ������ */
#define AMHW_FSL_TPM_CHSC_FLAG      (1UL << 7)          /**< \brief ͨ����־  -1:ͨ���¼��ѷ��� */
#define AMHW_FSL_TPM_CHSC_IE        (1UL << 6)          /**< \brief ͨ���ж�ʹ�� */
#define AMHW_FSL_TPM_CHSC_MS(s)     (((s) & 0x3) << 4)  /**< \brief ͨ��ģʽѡ�� */
#define AMHW_FSL_TPM_CHSC_EL_SEL(s) (((s) & 0x3) << 2)  /**< \brief ���ػ��ƽѡ�� */
#define AMHW_FSL_TPM_CHSC_MODE_MASK (0xFu << 2)
#define AMHW_FSL_TPM_CHSC_DMA_EN    (1UL << 0)          /**< \brief DMA����ʹ�ܣ�ͨ���� */

/** @} */

/**
 * \brief ͨ�������趨
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_FSL_TPM_CH(n)
 * \param[in] flags    : AMHW_FSL_TPM_CHSC_* ��ֵ����
 *                       AMHW_FSL_TPM_CHSC_*��� ��OR��ֵ(#AMHW_FSL_TPM_CHSC_DMA_EN)
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_ch_sc_set (amhw_fsl_tpm_t *p_hw_tpm,
                              uint8_t          chan,
                              uint32_t         flags)
{
    p_hw_tpm->chan_ctl[chan].stat_ctl |= flags & AMHW_FSL_TPM_CnSC_MASK;
}

/**
 * \brief ͨ����������
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_FSL_TPM_CH(n)
 * \param[in] flags    : AMHW_FSL_TPM_CHSC_* ��ֵ����
 *                       AMHW_FSL_TPM_CHSC_*��� ��OR��ֵ(#AMHW_FSL_TPM_CHSC_DMA_EN)
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_ch_sc_clear (amhw_fsl_tpm_t *p_hw_tpm,
                                uint8_t          chan,
                                uint32_t         flags)
{
    p_hw_tpm->chan_ctl[chan].stat_ctl &= ~(flags & AMHW_FSL_TPM_CnSC_MASK);
}

/**
 * \brief ͨ��ģʽ����
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_FSL_TPM_CH(n)
 * \param[in] cnt_mode : ����ģʽ�����¼�����������-���¼���
 * \param[in] mode     : ���벶������Ƚ�ģʽ��PWM��ģʽ���ã��ο����ñ��
 *
 * \return ��
 * \note �ο����ñ��
 */
am_static_inline
void amhw_fsl_tpm_ch_mode (amhw_fsl_tpm_t              *p_hw_tpm,
                            uint8_t                       chan,
                            amhw_fsl_tpm_counting_mode_t cnt_mode,
                            uint32_t                      mode)
{
    if ((uint8_t)cnt_mode) {
        amhw_fsl_tpm_ctrl_set(p_hw_tpm, AMHW_FSL_TPM_SC_CPWM_MODE);
    } else {
        amhw_fsl_tpm_ctrl_clear(p_hw_tpm, AMHW_FSL_TPM_SC_CPWM_MODE);
    }
    amhw_fsl_tpm_ch_sc_clear(p_hw_tpm, chan, AMHW_FSL_TPM_CHSC_MODE_MASK);
    amhw_fsl_tpm_ch_sc_set(p_hw_tpm, chan, mode);
}

/**
 * \brief ͨ��״̬���ж�ͨ���Ƿ����¼�
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_FSL_TPM_CH(n)
 *
 * \retval  AM_TRUE  : ͨ���¼��ѷ���
 * \retval  AM_FALSE : ͨ���¼�δ����
 */
am_static_inline
am_bool_t amhw_fsl_tpm_ch_even_flag_chk (amhw_fsl_tpm_t *p_hw_tpm, uint8_t chan)
{
    return (am_bool_t)(p_hw_tpm->chan_ctl[chan].stat_ctl & AMHW_FSL_TPM_CHSC_FLAG);
}

/**
 * \name ͨ�������Ĵ�������(R/W)
 * @{
 */

#define AMHW_FSL_TPM_CH_VALUE_MASK       (0xFFFFu)         /**< \brief ������ֵ���� */

/** @} */

/**
 * \brief ͨ���������趨
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_FSL_TPM_CH(n)
 * \param[in] value    : ����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_ch_value_set (amhw_fsl_tpm_t *p_hw_tpm,
                                 uint8_t          chan,
                                 uint16_t         value)
{
    p_hw_tpm->chan_ctl[chan].value = value;
}

/**
 * \brief ͨ����������ȡ
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ͨ������ֵ
 */
am_static_inline
uint16_t amhw_fsl_tpm_ch_value_get (amhw_fsl_tpm_t *p_hw_tpm,
                                     uint8_t          chan)
{
    return p_hw_tpm->chan_ctl[chan].value;
}

/**
 * \name ״̬�Ĵ������壨д1���㣩
 * @{
 */

#define AMHW_FSL_TPM_STATUS            (0x13Fu)        /**< \brief ����Ƚ�״̬���� */
#define AMHW_FSL_TPM_STAT_OV_FLAG      (1UL << 8)      /**< \brief �����־ */
#define AMHW_FSL_TPM_STAT_CH5_FLAG     (1UL << 5)      /**< \brief CH5ͨ���¼���־ */
#define AMHW_FSL_TPM_STAT_CH4_FLAG     (1UL << 4)      /**< \brief CH4ͨ���¼���־ */
#define AMHW_FSL_TPM_STAT_CH3_FLAG     (1UL << 3)      /**< \brief CH3ͨ���¼���־ */
#define AMHW_FSL_TPM_STAT_CH2_FLAG     (1UL << 2)      /**< \brief CH2ͨ���¼���־ */
#define AMHW_FSL_TPM_STAT_CH1_FLAG     (1UL << 1)      /**< \brief CH1ͨ���¼���־ */
#define AMHW_FSL_TPM_STAT_CH0_FLAG     (1UL << 0)      /**< \brief CH0ͨ���¼���־ */

#define AMHW_FSL_TPM_STAT_FLAG(n)      (1UL << n)      /** \brief CHnͨ���¼���־ */

/** @} */

/**
 * \brief TPM״̬��־��ȡ
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \return TPM״̬��־,�μ� AMHW_FSL_TPM_STAT_* �궨��
 */
am_static_inline
uint32_t amhw_fsl_tpm_stat_flag_get (amhw_fsl_tpm_t *p_hw_tpm)
{
    return p_hw_tpm->status;
}

/**
 * \brief TPM״̬��־���
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_TPM_STAT_* ��ֵ����
 *                       AMHW_FSL_TPM_STAT_*��� ��OR��ֵ(#AMHW_FSL_TPM_STAT_CH0_FLAG)
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_stat_flag_clear (amhw_fsl_tpm_t *p_hw_tpm, uint32_t flags)
{
    p_hw_tpm->status = flags;
}

/**
 * \name ���üĴ������壨R/W��
 * @{
 */

#define AMHW_FSL_TPM_CFG_MASK       (0xF0703E0u)         /**< \brief ����Ƚ�״̬���� */
#define AMHW_FSL_TPM_CFG_TRG_SEL(s) (((s) & 0xf) << 24)  /**< \brief ����ѡ�� */
#define AMHW_FSL_TPM_CFG_CROT       (1UL << 18)          /**< \brief ����ʱ���������� */
#define AMHW_FSL_TPM_CFG_CSOO       (1UL << 17)          /**< \brief ���ʱ������ֹͣ */
#define AMHW_FSL_TPM_CFG_CSOT       (1UL << 16)          /**< \brief ����ʱ��������ʼ */
#define AMHW_FSL_TPM_CFG_GTBEEN     (1UL << 9)           /**< \brief ȫ�ֶ�ʱ��ʹ�� */
#define AMHW_FSL_TPM_CFG_DGBMODE(s) (((s) & 0x3) << 6)   /**< \brief ����ģʽ */
#define AMHW_FSL_TPM_CFG_DOZEEN     (1UL << 5)           /**< \brief ˯��ģʽ�¼�����ֹͣ */

/** @} */

/**
 * \brief TPM ����Դѡ��
 */
typedef enum amhw_fsl_tpm_trigger_src {
    AMHW_FSL_TPM_TRG_SRC_EXT_PIN     = 0x0,         /**< \brief �ⲿ�������� */
    AMHW_FSL_TPM_TRG_SRC_CMP0_OUT    = 0x1,         /**< \brief CMP0 ��� */
    AMHW_FSL_TPM_TRG_SRC_PIT_TRG0    = 0x4,         /**< \brief PIT0 */
    AMHW_FSL_TPM_TRG_SRC_PIT_TRG1    = 0x5,         /**< \brief PIT1 */
    AMHW_FSL_TPM_TRG_SRC_TPM0_OV     = 0x8,         /**< \brief TPM0 ��� */
    AMHW_FSL_TPM_TRG_SRC_TPM1_OV     = 0x9,         /**< \brief TPM1 ��� */
    AMHW_FSL_TPM_TRG_SRC_TPM2_OV     = 0xA,         /**< \brief TPM2 ��� */
    AMHW_FSL_TPM_TRG_SRC_RTC_ALARM   = 0xC,         /**< \brief RTC ���� */
    AMHW_FSL_TPM_TRG_SRC_RTC_SEC     = 0xD,         /**< \brief RTC �� */
    AMHW_FSL_TPM_TRG_SRC_LPTMR_TRG   = 0xE,         /**< \brief LPTMR */
} amhw_fsl_tpm_trigger_src_t;

/**
 * \brief TPM����ģʽ
 */
typedef enum amhw_fsl_tpm_dbg_mode {
    AMHW_FSL_TPM_DBG_PAUSED    = 0x0,      /**< \brief ����ģʽ����ͣ������Դ�����벶�񱻺��� */
    AMHW_FSL_TPM_DBG_CONTINUES = 0x3,      /**< \brief ����ģʽ�¼������� */
} amhw_fsl_tpm_dbg_mode_t;

/**
 * \brief TPM�����趨
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_TPM_CFG_* ��ֵ����
 *                       AMHW_FSL_TPM_CFG_*��� ��OR��ֵ(#AMHW_FSL_TPM_CFG_DOZEEN)
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_cfg_set (amhw_fsl_tpm_t *p_hw_tpm, uint32_t flags)
{
    p_hw_tpm->status |= flags & AMHW_FSL_TPM_CFG_MASK;
}

/**
 * \brief TPM�����趨
 *
 * \param[in] p_hw_tpm : ָ��TPM�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_TPM_CFG_* ��ֵ����
 *                       AMHW_FSL_TPM_CFG_*��� ��OR��ֵ(#AMHW_FSL_TPM_CFG_DOZEEN)
 * \return ��
 */
am_static_inline
void amhw_fsl_tpm_cfg_clear (amhw_fsl_tpm_t *p_hw_tpm, uint32_t flags)
{
    p_hw_tpm->status &= ~(flags & AMHW_FSL_TPM_CFG_MASK);
}


/* ʹ������������ν��� */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

  /* ��������������ʹ�� */
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/**
 * @} amhw_fsl_if_tpm
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_TPM_H */

/* end of file */

