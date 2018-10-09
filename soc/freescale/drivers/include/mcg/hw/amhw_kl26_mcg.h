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
 * \brief ϵͳʱ��Դѡ��Ϳ���
 *
 * \internal
 * \par History
 * - 1.00 16-09-13  ari, first implementation.
 * \endinternal
 */

#ifndef __KL26_TPM2_H
#define __KL26_TPM2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "../../../../kl26/kl26_periph_map.h"

/**
 * \addtogroup amhw_kl26_if_mcg
 * \copydoc amhw_kl26_mcg.h
 * @{
 */

/*******************************************************************************
* defines
*******************************************************************************/

/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef struct amhw_kl26_mcg {
    __IO uint8_t c1;             /**< \brief  MCG���ƼĴ��� 1 */
    __IO uint8_t c2;             /**< \brief  MCG���ƼĴ��� 2 */
    __IO uint8_t c3;             /**< \brief  MCG���ƼĴ��� 3 */
    __IO uint8_t c4;             /**< \brief  MCG���ƼĴ��� 4 */
    __IO uint8_t c5;             /**< \brief  MCG���ƼĴ��� 5 */
    __IO uint8_t c6;             /**< \brief  MCG���ƼĴ��� 6 */
    __IO uint8_t s;              /**< \brief  MCG״̬�Ĵ���   */
    __I  uint8_t reserved0[1];   /**< \brief  ����            */
    __IO uint8_t sc;             /**< \brief  MCG״̬/���ƼĴ���  */
    __I  uint8_t reserved1[1];   /**< \brief  ����            */
    __IO uint8_t atcvh;          /**< \brief  MCG�Ƚ�ֵ��λ   */
    __IO uint8_t atcvl;          /**< \brief  MCG�Ƚ�ֵ��λ   */
    __IO uint8_t reserved2[1];   /**< \brief  ����            */
    __IO uint8_t c8;             /**< \brief  MCG���ƼĴ��� 8 */
    __I  uint8_t c9;             /**< \brief  MCG���ƼĴ��� 9 */
    __I  uint8_t c10;            /**< \brief  MCG���ƼĴ��� 10 */
} amhw_kl26_mcg_t;

/**
  * \brief �����Ĵ�����ṹ��
  */
typedef struct amhw_kl26_osc {
    __IO uint8_t cr;            /**< \brief  OSC���ƼĴ��� 1 */
} amhw_kl26_osc_t;

/**
 * \brief MCGOUTCLKʱ��Դ
 */
typedef enum amhw_kl26_mcg_outclk_src {
    KL26_TPM2_OUTCLK_SRC_PLLS = 0,    /**< \brief FLL��PLL,��PLLS���� */
    KL26_TPM2_OUTCLK_SRC_IRC  = 1,    /**< \brief IRC�ڲ��ο�ʱ��  */
    KL26_TPM2_OUTCLK_SRC_ERC  = 2     /**< \brief ERC�ⲿ�ο�ʱ��  */
} amhw_kl26_mcg_outclk_src_t;

/**
 * \brief MCGOUTCLKʱ��״̬
 */
typedef enum amhw_kl26_mcg_outclk_stat {
    KL26_TPM2_OUTCLK_SATA_FLL = 0,    /**< \brief FLLʱ�� */
    KL26_TPM2_OUTCLK_SATA_IRC = 1,    /**< \brief IRC�ڲ��ο�ʱ��  */
    KL26_TPM2_OUTCLK_SATA_ERC = 2,    /**< \brief ERC�ⲿ�ο�ʱ��  */
    KL26_TPM2_OUTCLK_SATA_PLL = 3     /**< \brief PLLʱ��  */
} amhw_kl26_mcg_outclk_stat_t;

/**
 * \brief PLLSʱ��Դ
 */
typedef enum amhw_kl26_mcg_plls_src {
    KL26_TPM2_PLLS_SRC_FLL = 0,    /**< \brief FLL */
    KL26_TPM2_PLLS_SRC_PLL = 1     /**< \brief PLL */
} amhw_kl26_mcg_plls_src_t;

/**
 * \brief FLLʱ��Դ
 */
typedef enum amhw_kl26_mcg_fll_src {
    KL26_TPM2_FLL_SRC_ERC = 0,      /**< \brief ERC�ⲿ�ο�ʱ��   */
    KL26_TPM2_FLL_SRC_IRC_SLOW = 1  /**< \brief ���٣�32KHZ���ڲ��ο�ʱ��  */
} amhw_kl26_mcg_fll_src_t;

/**
 * \brief IRC�ڲ��ο�ʱ��Դ
 */
typedef enum amhw_kl26_mcg_irc_src {
    KL26_TPM2_IRC_SRC_SLOW = 0,   /**< \brief ���٣�32KHZ���ڲ��ο�ʱ��  */
    KL26_TPM2_IRC_SRC_FAST = 1    /**< \brief ���٣�4MHZ���ڲ��ο�ʱ��  */
} amhw_kl26_mcg_irc_src_t;

/**
 * \brief IRC�ڲ��ο�ʱ��״̬
 */
typedef enum amhw_kl26_mcg_irc_stat {
    KL26_TPM2_IRC_SATA_SLOW = 0,   /**< \brief ���٣�32KHZ���ڲ��ο�ʱ��  */
    KL26_TPM2_IRC_SATA_FAST = 1    /**< \brief ���٣�4MHZ���ڲ��ο�ʱ��  */
} amhw_kl26_mcg_irc_stat_t;

/**
 * \brief OSCER�ⲿ�ο�ʱ��Դ
 */
typedef enum amhw_kl26_mcg_osc_src {
    KL26_TPM2_OSC_SRC_CLKIN = 0,   /**< \brief �ⲿʱ����������  */
    KL26_TPM2_OSC_SRC_OSC   = 1    /**< \brief ��������ʱ��    */
} amhw_kl26_mcg_osc_src_t;

/**
 * \brief OSC����Ƶ�ʷ�Χ
 */
typedef enum amhw_kl26_mcg_osc_range {
    KL26_TPM2_OSC_RANGE_LOW       = 0,   /**< \brief 1K~32.768KHZ */
    KL26_TPM2_OSC_RANGE_HIGH      = 1,   /**< \brief 3~8MHZ       */
    KL26_TPM2_OSC_RANGE_VERYHIGH  = 2,   /**< \brief 8~32MHZ      */
    KL26_TPM2_OSC_RANGE_VERYHIGH1 = 3    /**< \brief 8~32MHZ      */
} amhw_kl26_mcg_osc_range_t;

/**
 * \brief OSC��������ѡ��
 */
typedef enum amhw_kl26_mcg_osc_gain {
    KL26_TPM2_OSC_GAIN_LOW  = 0,   /**< \brief �͹���ģʽ */
    KL26_TPM2_OSC_GAIN_HIGH = 1    /**< \brief ������     */
} amhw_kl26_mcg_osc_gain_t;

/**
 * \brief OSC�����ڲ����ص���
 */
typedef enum amhw_kl26_mcg_osc_cap {
    KL26_TPM2_OSC_CAP_DISABLED = 0,    /**< \brief diabled   */
    KL26_TPM2_OSC_CAP_2PF      = 8,    /**< \brief 2PF       */
    KL26_TPM2_OSC_CAP_4PF      = 4,    /**< \brief 4PF       */
    KL26_TPM2_OSC_CAP_8PF      = 2,    /**< \brief 8PF       */
    KL26_TPM2_OSC_CAP_16PF     = 1     /**< \brief 16PF      */
} amhw_kl26_mcg_osc_cap_t;

/**
 * \brief OSC�������ģʽ
 */
typedef enum amhw_kl26_mcg_osc_monitor_mode {
    KL26_TPM2_OSC_MONITOR_INT   = 0,   /**< \brief ʱ�Ӷ�ʧʱ�����ж� */
    KL26_TPM2_OSC_MONITOR_RESET = 1    /**< \brief ʱ�Ӷ�ʧʱ��λ     */
} amhw_kl26_mcg_osc_monitor_mode_t;

/**
 * \brief FLL DCO�����Ƶϵ��F
 */
typedef enum amhw_kl26_mcg_dco_div {
    KL26_TPM2_DOC_DIV_640  = 0,  /**< \brief ref:31.25-39.0625KHZ,out:20-25MHZ */
    KL26_TPM2_DOC_DIV_732  = 4,  /**< \brief ref:32.768KHZ,out:24MHZ */
    KL26_TPM2_DOC_DIV_1280 = 1,  /**< \brief ref:31.25-39.0625KHZ,out:40-50MHZ  */
    KL26_TPM2_DOC_DIV_1464 = 5,  /**< \brief ref:32.768KHZ out:48MHZ */
    KL26_TPM2_DOC_DIV_1920 = 2,  /**< \brief ref:31.25-39.0625KHZ,out:60-75MHZ */
    KL26_TPM2_DOC_DIV_2197 = 6,  /**< \brief ref:32.768KHZ,out:72MHZ */
    KL26_TPM2_DOC_DIV_2560 = 3,  /**< \brief ref:31.25-39.0625KHZ,out:80-100MHZ */
    KL26_TPM2_DOC_DIV_2929 = 7   /**< \brief ref:32.768KHZ,out:96MHZ  */
} amhw_kl26_mcg_dco_div_t;

/**
 * \brief ATM����ʱ��Դ
 */
typedef enum amhw_kl26_mcg_atm_src {
    KL26_TPM2_ATM_SRC_32KHZ = 0,   /**< \brief OSCCLK         */
    KL26_TPM2_ATM_SRC_4MHZ  = 1    /**< \brief 32KHZ RTC OSC  */
} amhw_kl26_mcg_atm_src_t;

/*******************************************************************************
* API
*******************************************************************************/

/**
 * \brief STOPģʽ�£��ڲ��ο�ʱ��ʹ��
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_irc_stop_enable (void)
{
    KL26_MCG->c1 |= (1UL << 0);
}

/**
 * \brief STOPģʽ�£��ڲ��ο�ʱ�ӽ���
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_irc_stop_disable (void)
{
    KL26_MCG->c1 &= ~(1UL << 0);
}

/**
 * \brief MCGIRCLKʱ��ʹ��
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_irc_enable (void)
{
    KL26_MCG->c1 |= (1UL << 1);
}

/**
 * \brief MCGIRCLKʱ�ӽ���
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_irc_disable (void)
{
    KL26_MCG->c1 &= ~(1UL << 1);
}

/**
 * \brief �ڲ��ο�ʱ��Դѡ��
 * \param[in] src : �ڲ��ο�ʱ��Դ
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_irc_src_set (amhw_kl26_mcg_irc_src_t src)
{
    KL26_MCG->c2 = (KL26_MCG->c2 & (~(1UL << 0))) |
                        (src << 0);
}

/**
 * \brief �ڲ��ο�ʱ��Դ��ȡ
 * \return �ڲ��ο�ʱ��Դ
 * \note
 */
am_static_inline
amhw_kl26_mcg_irc_src_t amhw_kl26_mcg_irc_src_get (void)
{
    return (amhw_kl26_mcg_irc_src_t) ((KL26_MCG->c2 >> 0) & 0x01);
}

/**
 * \brief �ڲ��ο�ʱ��״̬��ȡ
 * \return �ڲ��ο�ʱ��ʹ�õ�Դ
 * \note
 */
am_static_inline
amhw_kl26_mcg_irc_stat_t amhw_kl26_mcg_irc_stat_get (void)
{
    return (amhw_kl26_mcg_irc_stat_t) (KL26_MCG->s & 0x01);
}

/**
 * \brief FCRDIV�����ڲ��ο�ʱ�ӷ�Ƶϵ������
 * \param[in] div : FCRDIV��Ƶϵ��0~7
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_irc_fast_div_set (uint32_t div)
{
    KL26_MCG->sc = (KL26_MCG->sc & (~(7UL << 1))) |
                        (div << 1);
}

/**
 * \brief ��ȡFCRDIV�����ڲ��ο�ʱ�ӷ�Ƶϵ��
 * \return  FCRDIV��Ƶϵ��0~7
 */
am_static_inline
uint32_t amhw_kl26_mcg_irc_fast_div_get (void)
{
    return ((KL26_MCG->sc >> 1) & 0x07);
}

/**
 * \brief �����ڲ��ο�ʱ����������
 * \return ��
 * \note ��λʱ�Զ�����,
 */
am_static_inline
void amhw_kl26_mcg_irc_trim_set (void)
{
    if ( *((uint8_t*) 0x03FFU) != 0xFFU) {
        KL26_MCG->c3 = *((uint8_t*) 0x03FFU);
        KL26_MCG->c4 = (KL26_MCG->c4 & 0xFEU)      |
        		            ((*((uint8_t*) 0x03FEU)) & 0x01U);
  }
}

/**
 * \brief ��ȡATM״̬
 * \retval 0 : ATM�����������
 * \retval 1 : ATM����ʧ��
 * \note
 */
am_static_inline
uint32_t amhw_kl26_mcg_atm_status_get (void)
{
    return (KL26_MCG->sc & (1UL << 5));
}

/**
 * \brief ATM�Զ�����ʱ��Դ����
 * \param[in] src ��ATMʱ��Դ
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_atm_src_set (amhw_kl26_mcg_atm_src_t src)
{
    KL26_MCG->sc = (KL26_MCG->sc & (~(1UL << 6))) |
                        (src << 6);
}

/**
 * \brief ATM�Զ���������ʹ��
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_atm_enable (void)
{
    KL26_MCG->sc |= (1UL << 7);
}

/**
 * \brief ATM�Զ��������ƽ���
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_atm_disable (void)
{
    KL26_MCG->sc &= ~(1UL << 7);
}

/**
 * \brief ATM�Զ������Ƚ�ֵ����
 * \param[in] value ��ATM�Ƚ�ֵ16bits
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_atm_value_set (uint32_t value)
{
    KL26_MCG->atcvh = (value >> 8) & 0xff;
    KL26_MCG->atcvl = value & 0xff;
}

/**
 * \brief FLL�ο�ʱ��Դѡ��
 * \param[in] src : FLL�ο�ʱ��Դ
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_fll_src_set (amhw_kl26_mcg_fll_src_t src)
{
    KL26_MCG->c1 = (KL26_MCG->c1 & (~(1UL << 2))) |
                        (src << 2);
}

/**
 * \brief FLL�ο�ʱ��Դѡ��
 * \return FLL�ο�ʱ��Դ
 */
am_static_inline
amhw_kl26_mcg_fll_src_t amhw_kl26_mcg_fll_src_get (void)
{
    return (amhw_kl26_mcg_fll_src_t)((KL26_MCG->c1 >> 2) & 0x01);
}

/**
 * \brief ��ȡFLLʱ��״̬
 * \retval 0 : �ⲿ�ο�ʱ����FLL�ο�ʱ��
 * \retval 1 : �ڲ��ο�ʱ����FLL�ο�ʱ��
 */
am_static_inline
am_bool_t amhw_kl26_mcg_fll_stat_get (void)
{
    return (am_bool_t)((KL26_MCG->s & (1ul << 4)));
}

/**
 * \brief FRDIV��Ƶϵ������
 * \param[in] div : FRDIV��Ƶϵ����0��7��
 * \return ��
 * \note FLLʹ���ⲿʱ��ʱ�������Ƶ��31.25 kHz to 39.0625 kHz֮��
 */
am_static_inline
void amhw_kl26_mcg_fll_erc_div_set (uint32_t div)
{
    KL26_MCG->c1 = (KL26_MCG->c1 & (~(7UL << 3))) |
                        (div << 3);
}

/**
 * \brief FRDIV��Ƶϵ����ȡ
 * \return FRDIV��Ƶϵ��
 */
am_static_inline
uint32_t amhw_kl26_mcg_fll_erc_div_get (void)
{
    return ((KL26_MCG->c1 >> 3) & 0x07);
}

/**
 * \brief FLL DCO�����Ƶϵ������
 * \param[in] div : DCO��Ƶϵ��
 * \return ��
 * \note  ���ڲ��ο�ʱ��32.7768KHZ�Ļ�����Ƶ
 */
am_static_inline
void amhw_kl26_mcg_fll_dco_div_set (amhw_kl26_mcg_dco_div_t div)
{
    KL26_MCG->c4 = (KL26_MCG->c4 & (~(7UL << 5))) |
                        (div << 5);
}

/**
 * \brief FLL DCO�����Ƶϵ����ȡ
 * \return ��
 */
am_static_inline
amhw_kl26_mcg_dco_div_t amhw_kl26_mcg_fll_dco_div_get (void)
{
    return (amhw_kl26_mcg_dco_div_t)((KL26_MCG->c4 >> 5) & 0x07);
}

/**
 * \brief �ı�ʱ��ģʽʱ��FLL�˲���Ƶ�ʱ���ʹ��
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_fll_fitprsrv_enable (void)
{
    KL26_MCG->sc |= 1UL << 4;
}

/**
 * \brief �ı�ʱ��ģʽʱ��FLL�˲���Ƶ�ʱ�������
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_fll_fitprsrv_disable (void)
{
    KL26_MCG->sc &= ~(1UL << 4);
}

/**
 * \brief MCGOUTCLKʱ��Դ����
 * \param[in] src : MCGOUTCLKʱ��Դ
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_outclk_src_set (amhw_kl26_mcg_outclk_src_t src)
{
    KL26_MCG->c1 = (KL26_MCG->c1 & (~(3UL << 6))) |
                        (src << 6);
}

/**
 * \brief MCGOUTCLKʱ��Դ��ȡ
 * \return MCGOUTCLKʱ��Դ
 * \note
 */
am_static_inline
amhw_kl26_mcg_outclk_src_t amhw_kl26_mcg_outclk_src_get (void)
{
    return (amhw_kl26_mcg_outclk_src_t) ((KL26_MCG->c1 >> 6) & 0x03);
}

/**
 * \brief MCGOUTCLKʱ��Դ��ȡ
 * \return MCGOUTCLKʱ��Դ
 * \note
 */
am_static_inline
amhw_kl26_mcg_outclk_stat_t amhw_kl26_mcg_outclk_stat_get (void)
{
    return (amhw_kl26_mcg_outclk_stat_t) ((KL26_MCG->s >> 2) & 0x03);
}

/**
 * \brief OSC�ⲿ�ο�ʱ��Դѡ��
 * \param[in] src : OSC�ⲿ�ο�ʱ��Դ
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_osc_src_set (amhw_kl26_mcg_osc_src_t src)
{
    KL26_MCG->c2 = (KL26_MCG->c2 & (~(1UL << 2))) |
                        (src << 2);
}

/**
 * \brief OSC�ⲿ�ο�ʱ��Դ��ȡ
 * \return OSC�ⲿ�ο�ʱ��Դ
 * \note
 */
am_static_inline
amhw_kl26_mcg_osc_src_t amhw_kl26_mcg_osc_src_get (void)
{
    return (amhw_kl26_mcg_osc_src_t)((KL26_MCG->c2 >> 2) & 0x01);
}

/**
 * \brief OSC����ģʽѡ��
 * \param[in] mode : OSC����ģʽ
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_osc_gain_set (amhw_kl26_mcg_osc_gain_t mode)
{
    KL26_MCG->c2 = (KL26_MCG->c2 & (~(1UL << 3))) |
                        (mode << 3);
}

/**
 * \brief ��ȡOSC����ģʽ
 * \return OSC����ģʽ
 * \note
 */
am_static_inline
amhw_kl26_mcg_osc_gain_t amhw_kl26_mcg_osc_gain_get (void)
{
    return (amhw_kl26_mcg_osc_gain_t)((KL26_MCG->c2 >> 3)& 0x01);
}

/**
 * \brief OSC����Ƶ�ʷ�Χ����
 * \param[in] range : OSC����Ƶ�ʷ�Χ
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_osc_range_set (amhw_kl26_mcg_osc_range_t range)
{
    KL26_MCG->c2 = (KL26_MCG->c2 & (~(3UL << 4))) |
                        (range << 4);
}

/**
 * \brief ��ȡOSC����Ƶ�ʷ�Χ
 * \return OSC����Ƶ�ʷ�Χ
 * \note
 */
am_static_inline
amhw_kl26_mcg_osc_range_t amhw_kl26_mcg_osc_range_get (void)
{
    return (amhw_kl26_mcg_osc_range_t)((KL26_MCG->c2 >> 4) & 0x03);
}

/**
 * \brief OSC�����ڲ����ص�������
 * \param[in] value ���ڲ����ص��ݴ�С
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_osc_cap_cfg (amhw_kl26_mcg_osc_cap_t value)
{
	KL26_OSC->cr = (KL26_OSC->cr & (~(0x0f << 0))) |
                   (value << 0);
}

/**
 * \brief OSC0ʱ�Ӽ��ʹ��
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_osc_monitor_enable (amhw_kl26_mcg_osc_monitor_mode_t mode)
{
    KL26_MCG->c2 = ((KL26_MCG->c2 & (~(1ul << 7))) | (mode << 7));
    KL26_MCG->c6 |= (1UL << 5);
}

/**
 * \brief OSC0ʱ�Ӽ�ؽ���
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_osc_monitor_disable (void)
{
    KL26_MCG->c2 = KL26_MCG->c2 & (~(1ul << 7));
    KL26_MCG->c6 &= ~(1UL << 5);
}

/**
 * \brief ��ȡOSCʧ��״̬
 * \retval 0 : ʧ��û�з���
 * \retval 1 : ʧ������
 * \note
 */
am_static_inline
am_bool_t amhw_kl26_mcg_osc_losslock_stat_get (void)
{
    return (am_bool_t)(KL26_MCG->sc & 0x01);
}

/**
 * \brief ��ȡOSC�ȶ�״̬
 * \retval 0 : OSCδ�ȶ�
 * \retval 1 : OSC�ȶ�
 * \note
 */
am_static_inline
am_bool_t amhw_kl26_mcg_osc_stable_stat_get (void)
{
    return (am_bool_t)(KL26_MCG->s & (1ul << 1));
}

/**
 * \brief MCGPLLCLKʱ��ʹ��
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_pll_enable (void)
{
    KL26_MCG->c5 |= (1UL << 6);
}

/**
 * \brief MCGPLLCLKʱ�ӽ���
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_pll_disable (void)
{
    KL26_MCG->c5 &= ~(1UL << 6);
}

/**
 * \brief STOPģʽ�£�PLLʱ��ʹ��
 * \return ��
 * \note ����PEE��PBEģʽ��PLLʱ��Ҫʹ��
 */
am_static_inline
void amhw_kl26_mcg_pll_stopmode_enable (void)
{
    KL26_MCG->c5 |= (1UL << 5);
}

/**
 * \brief STOPģʽ�£�PLLʱ�ӽ���
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_pll_stopmode_disable (void)
{
    KL26_MCG->c5 &= ~(1UL << 5);
}



/**
 * \brief PLL ERC����ϵ����PRDIV0������
 * \param[in] div :  PRDIV0����ϵ�� 0~24
 * \return ��
 * \note  pll�����ʱ�ӱ����Ƶ�� 2 �C 4 MHz
 */
am_static_inline
void amhw_kl26_mcg_pll_erc_div_set (uint32_t div)
{
    KL26_MCG->c5 = (KL26_MCG->c5 & (~(0x1f << 0))) |
                        (div << 0);
}

/**
 * \brief PLL ERC����ϵ����PRDIV0����ȡ
 * \return PRDIV0����ϵ�� 0~24
 */
am_static_inline
uint32_t amhw_kl26_mcg_pll_erc_div_get (void)
{
    return ((KL26_MCG->c5 >> 0) & 0x1f);
}

/**
 * \brief PLL VCO��Ƶϵ������
 * \param[in] div :  VCO����ϵ����0��31��Ӧ��Ƶֵ24��55��
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_pll_vco_div_set (uint32_t div)
{
    KL26_MCG->c6 = (KL26_MCG->c6 & (~(0x1f << 0))) |
                        (div << 0);
}

/**
 * \brief PLL VCO��Ƶϵ����ȡ
 * \return VCO��Ƶϵ��
 * \note ʵ�ʱ�Ƶ(24 + VCODIV)��
 */
am_static_inline
uint32_t amhw_kl26_mcg_pll_vco_div_get (void)
{
    return ((KL26_MCG->c6 >> 0) & 0x1f);
}

/**
 * \brief PLLʧ���ж�ʹ��
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_pll_losslock_int_enable (void)
{
    KL26_MCG->c6 |= (1UL << 7);
}

/**
 * \brief PLLʧ���жϽ���
 * \return ��
 * \note
 */
am_static_inline
void amhw_kl26_mcg_pll_losslock_int_disable (void)
{
    KL26_MCG->c6 &= ~(1UL << 7);
}

/**
 * \brief PLLʧ����λʹ��
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_pll_losslock_rest_enable (void)
{
    KL26_MCG->c8 |= 1UL << 6;
}

/**
 * \brief PLLʧ����λ����
 * \return ��
 * \note ��λ����ʱ�����ж�����Ҫ��PLLʧ���ж�ʹ��
 */
am_static_inline
void amhw_kl26_mcg_pll_losslock_rest_disable (void)
{
    KL26_MCG->c8 &= ~(1UL << 6);
}

/**
 * \brief PLLʧ��״̬��ȡ
 * \retval 0: PLLû��ʧ��
 * \retval 1: PLL�Ѿ�ʧ��
 * \note
 */
am_static_inline
am_bool_t amhw_kl26_mcg_pll_losslock_stat_get (void)
{
    return (am_bool_t)(KL26_MCG->s & (1ul << 7));
}

/**
 * \brief PLL����״̬
 * \retval 0: PLLû����
 * \retval 1: PLL����
 * \note
 */
am_static_inline
am_bool_t amhw_kl26_mcg_pll_locked_stat_get (void)
{
    return (am_bool_t)(KL26_MCG->s & (1ul << 6));
}

/**
 * \brief ����PLLS��ʱ��Դ
 * \param[in] src : PLLSʱ��Դ
 * \return ��
 * \note ������MCGOUTCLKʱ��ԴΪPLLS
 */
am_static_inline
void amhw_kl26_mcg_plls_src_set (amhw_kl26_mcg_plls_src_t src)
{
    KL26_MCG->c6 = (KL26_MCG->c6 & (~(1UL << 6))) |
                        (src << 6);
}

/**
 * \brief ��ȡPLLS��ʱ��Դ
 * \return PLLSʱ��Դ
 */
am_static_inline
amhw_kl26_mcg_plls_src_t amhw_kl26_mcg_plls_src_get (void)
{
    return (amhw_kl26_mcg_plls_src_t)((KL26_MCG->c6 >> 6) & 0x01);
}

/**
 * \brief ��ȡPLLSʱ�ӵ�״̬
 * \retval 0 : MCGFLLCLK ��Ϊ MCGOUTCLK���
 * \retval 1 : MCGPLLCLK ��Ϊ MCGOUTCLK���
 */
am_static_inline
am_bool_t amhw_kl26_mcg_plls_stat_get (void)
{
    return (am_bool_t)(KL26_MCG->s & (1ul << 5));
}

/**
 * \brief �͹���ģʽ��FLL/PLLʹ��
 * \return ��
 * \note ��FBE,PBE,BLPI,BLPEģʽ����Ч
 */
am_static_inline
void amhw_kl26_mcg_lp_plls_enable (void)
{
    KL26_MCG->c2 &= ~(1UL << 1);
}

/**
 * \brief �͹���ģʽ��FLL/PLL����
 * \return ��
 * \note ��FBE,PBE,BLPI,BLPEģʽ����Ч
 */
am_static_inline
void amhw_kl26_mcg_lp_plls_disable (void)
{
    KL26_MCG->c2 |= 1UL << 1;
}

/**
 * \brief �͹���ģʽ��FLL/PLL״̬
 * \retval 0��FLL/PLL ʹ��
 * \retval 1��FLL/PLL ����
 */
am_static_inline
am_bool_t amhw_kl26_mcg_lp_plls_get (void)
{
    return (am_bool_t) ((KL26_MCG->c2 >> 1) & 0x01);
}

/**
 * \brief STOPģʽ�£�OSCERCLKʱ��ʹ��
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_erc_stop_enable (void)
{
	KL26_OSC->cr |= (1UL << 5);
}

/**
 * \brief STOPģʽ�£�OSCERCLKʱ�ӽ���
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_erc_stop_disable (void)
{
	KL26_OSC->cr &= ~(1UL << 5);
}

/**e
 * \brief OSCERCLKʱ��ʹ��
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_erc_enable (void)
{
	KL26_OSC->cr |= (1UL << 7);
}

/**
 * \brief OSCERCLKʱ�ӽ���
 * \return ��
 */
am_static_inline
void amhw_kl26_mcg_erc_disable (void)
{
	KL26_OSC->cr &= ~(1UL << 7);
}


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __KL26_TPM2_H */

/* end of file */
