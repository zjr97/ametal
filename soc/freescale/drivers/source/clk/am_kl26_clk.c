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
 * \brief CLK implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  ari, first implementation.
 * \endinternal
 */
 
#include "ametal.h"
#include "am_clk.h"
#include "hw/amhw_kl26_mcg.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_fsl_lptmr.h"
#include "hw/amhw_fsl_rtc.h"
#include "am_kl26_clk.h"
#include "../../../kl26/kl26_clk.h"


/**
 * \name Ƶ��ֵ����
 * @{
 */

#define __AM_KL26_CLK_RATE_LPO         1000UL    /**< \brief PMC���LPOƵ��        */
#define __AM_KL26_CLK_RATE_IRC_SLOW    32768UL   /**< \brief �ڲ�����IRCƵ��       */
#define __AM_KL26_CLK_RATE_IRC_FAST    4000000UL /**< \brief �ڲ�����IRCƵ��       */
#define __AM_KL26_CLK_RATE_RTC_CLKIN   32768UL   /**< \brief RTC�ⲿʱ���������ʹ��32768UL */
/** @} */


/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \brief ָ��GPIO�豸��ָ�� */
am_kl26_clk_dev_t *__gp_clk_dev;

/**
 * \brief �õ�MCGIRCLKʱ��Ƶ��
 * \return MCGIRCLKʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_mcgirclk_rate_get (void)
{
    uint32_t fcrdiv = 0;
    uint32_t clk = 0;

    if (amhw_kl26_mcg_irc_src_get() == KL26_TPM2_IRC_SRC_SLOW) {
        /** \brief  �ڲ�����ʱ�� */
        clk = __AM_KL26_CLK_RATE_IRC_SLOW;
    } else {
        /** \brief  �ڲ�����ʱ�� */
        fcrdiv = amhw_kl26_mcg_irc_fast_div_get();
        clk = __AM_KL26_CLK_RATE_IRC_FAST / (1UL << fcrdiv);
    }

    return clk;
}

/**
 * \brief �õ�OSCCLK/OSCERCLKʱ��Ƶ��
 * \return OSCCLK/OSCERCLKʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_oscclk_rate_get (void)
{
    uint32_t clk = 0;

    if (amhw_kl26_mcg_osc_src_get() == KL26_TPM2_OSC_SRC_OSC) {
        /** \brief  ����ʱ������ */
        clk = __gp_clk_dev->p_devinfo->xtal_rate;
    } else {
        /** \brief  �ⲿʱ���������� */
        clk = __gp_clk_dev->p_devinfo->xtal_rate;
    }

    return clk;
}

/**
 * \brief �õ�MCGFLLCLKʱ��Ƶ��
 * \return MCGFLLCLKʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_mcgfllclk_rate_get (void)
{
    uint32_t frdiv  = 0;
    uint32_t dcodiv = 0;
    uint32_t clk = 0;

    switch (amhw_kl26_mcg_fll_dco_div_get()) {

    case KL26_TPM2_DOC_DIV_640:  /**< \brief ref:31-39KHZ,out:20-25MHZ */
        dcodiv = 640;
        break;
    case KL26_TPM2_DOC_DIV_732:  /**< \brief ref:32KHZ,out:24MHZ */
        dcodiv = 732;
        break;
    case KL26_TPM2_DOC_DIV_1280: /**< \brief ref:31-39KHZ,out:40-50MHZ  */
        dcodiv = 1280;
        break;
    case KL26_TPM2_DOC_DIV_1464: /**< \brief ref:32KHZ out:48MHZ */
        dcodiv = 1464;
        break;
    case KL26_TPM2_DOC_DIV_1920: /**< \brief ref:31-39KHZ,out:60-75MHZ */
        dcodiv = 1920;
        break;
    case KL26_TPM2_DOC_DIV_2197: /**< \brief ref:32.768KHZ,out:72MHZ */
        dcodiv = 2197;
        break;
    case KL26_TPM2_DOC_DIV_2560: /**< \brief ref:31-39KHZ,out:80-100MHZ */
        dcodiv = 2560;
        break;
    case KL26_TPM2_DOC_DIV_2929: /**< \brief ref:32KHZ,out:96MHZ  */
        dcodiv = 2929;
        break;
    default : break;
    }

    if (amhw_kl26_mcg_fll_src_get() == KL26_TPM2_FLL_SRC_IRC_SLOW) {
        /** \brief  �ڲ�����ʱ����FLLʱ��Դ */
        clk = __AM_KL26_CLK_RATE_IRC_SLOW * dcodiv;
    } else {
        /** \brief  �ⲿʱ����FLLʱ��Դ */
        frdiv = amhw_kl26_mcg_fll_erc_div_get();

        if (amhw_kl26_mcg_osc_range_get() == KL26_TPM2_OSC_RANGE_LOW) {
            clk   = am_kl26_clk_oscclk_rate_get() / (1UL << frdiv) * dcodiv;
        } else {
            clk = am_kl26_clk_oscclk_rate_get() / (32UL << frdiv) * dcodiv;
        }
    }

    return clk;
}

/**
 * \brief �õ�MCGPLLCLKʱ��Ƶ��
 * \return MCGPLLCLKʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_mcgpllclk_rate_get (void)
{
    uint32_t prdiv  = 0;
    uint32_t vcodiv = 0;
    uint32_t clk    = 0;

    prdiv  = amhw_kl26_mcg_pll_erc_div_get();
    vcodiv = amhw_kl26_mcg_pll_vco_div_get();

    clk = am_kl26_clk_oscclk_rate_get() / (prdiv + 1) * (vcodiv + 24);

    return clk;
}

/**
 * \brief �õ�MCGOUTCLKʱ��Ƶ��
 * \return MCGOUTCLKʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_mcgoutclk_rate_get (void)
{
    uint32_t clk = 0;

    if (amhw_kl26_mcg_outclk_src_get() == KL26_TPM2_OUTCLK_SRC_IRC) {
        /** \brief  �ڲ�IRCʱ����MCGOUTCLKʱ��Դ */
        clk = am_kl26_clk_mcgirclk_rate_get();
    } else if (amhw_kl26_mcg_outclk_src_get() == KL26_TPM2_OUTCLK_SRC_ERC) {
        /** \brief  �ⲿOSCʱ����MCGOUTCLKʱ��Դ */
        clk = am_kl26_clk_oscclk_rate_get();
    } else {
        /** \brief  MCGPLLCLK/MCGFLLCLK��MCGOUTCLKʱ��Դ */
        if (amhw_kl26_mcg_plls_src_get() == KL26_TPM2_PLLS_SRC_FLL) {
            clk = am_kl26_clk_mcgfllclk_rate_get();
        } else {
            clk = am_kl26_clk_mcgpllclk_rate_get();
        }
    }

    return clk;
}

/**
 * \brief �õ�ERCLK32Kʱ��Ƶ��
 * \return ERCLK32Kʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_erclk32k_rate_get (void)
{
    uint32_t clk = 0;

    if (amhw_kl26_sim_ercclk32k_src_get() == KL26_SIM_OSC32KSEL_CLKIN) {
        /** \brief  �ⲿRTC_CLKIN������ERCLK32K��ʱ��Դ */
        clk = __AM_KL26_CLK_RATE_RTC_CLKIN;
    } else if (amhw_kl26_sim_ercclk32k_src_get() == KL26_SIM_OSC32KSEL_LPO) {
        /** \brief  LPO���ʱ����ERCLK32K��ʱ��Դ */
        clk = __AM_KL26_CLK_RATE_LPO;
    } else {
        /** \brief  OSCCLK32Kʱ����ERCLK32K��ʱ��Դ */
        if (amhw_kl26_mcg_osc_range_get() == KL26_TPM2_OSC_RANGE_LOW &&
            amhw_kl26_mcg_osc_gain_get() == KL26_TPM2_OSC_GAIN_LOW) {
            /** \brief  ����RANGE=0,HCG0 = 0ʱ��OSCCLK32K��Ч */
            clk = am_kl26_clk_oscclk_rate_get();
        }
    }

    return clk;
}

/**
 * \brief �õ�RTC_CLKOUTʱ��Ƶ��
 * \return RTC_CLKOUTʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_rtc_clkout_rate_get (void)
{
    uint32_t clk = 0;

    if (amhw_kl26_sim_rtc_clkout_get() == KL26_SIM_RTC_CLKOUT_OSCERCLK) {
        /** \brief  OSCERCLK��RTC_OUTʱ��Դ */
        clk = am_kl26_clk_oscclk_rate_get();
    } else {
        /** \brief  RTC OUT 1HZ */
        clk = 1UL;
    }

    return clk;
}


/**
 * \brief �õ�core/platform/systemʱ��Ƶ��
 * \return core/platform/systemʱ��Ƶ��
 */
uint32_t am_kl26_clk_core_clkrate_get(void)
{
    uint32_t outdiv1 = 0;
    uint32_t clk     = 0;

    outdiv1 = amhw_kl26_sim_clkdiv1_outdiv1_get();
    clk = am_kl26_clk_mcgoutclk_rate_get() / (1 + outdiv1);

    return clk;
}

/**
 * \brief �õ�bus/flashʱ��Ƶ��
 * \return bus/flashʱ��Ƶ��
 */
uint32_t am_kl26_clk_bus_clkrate_get(void)
{
    uint32_t outdiv4 = 0;
    uint32_t clk     = 0;



    outdiv4 = amhw_kl26_sim_clkdiv1_outdiv4_get();


    clk = am_kl26_clk_core_clkrate_get() / (1 + outdiv4);

    return clk;
}

/**
 * \brief �õ�TPM��ʱ��Ƶ��
 * \return  TPM��ʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_tpm_rate_get (void)
{
    uint32_t clk = 0;

    if (amhw_kl26_sim_tpm_src_get() == KL26_SIM_TPMSRC_DISABLED) {
        /** \brief TPMʱ�ӽ��� */
    } else if (amhw_kl26_sim_tpm_src_get() == KL26_SIM_TPMSRC_MCGIRCLK) {
        /** \brief  MCGIRCLK��TPMʱ��Դ */
        clk = am_kl26_clk_mcgirclk_rate_get();
    } else if (amhw_kl26_sim_tpm_src_get() == KL26_SIM_TPMSRC_OSCERCLK) {
        /** \brief  OSCERCLK��TPMʱ��Դ */
        clk = am_kl26_clk_oscclk_rate_get();
    } else {
        /** \brief  MCGPLLCLK/MCGFLLCLK��TPMʱ��Դ */
        if (amhw_kl26_sim_pllfll_sel_get() == KL26_SIM_PLLFLLSEL_FLL) {
            clk = am_kl26_clk_mcgfllclk_rate_get();
        } else {
            clk = am_kl26_clk_mcgpllclk_rate_get() / 2;
        }
    }

    return clk;
}

/**
 * \brief �õ�RTC��ʱ��Ƶ��
 * \return  RTC��ʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_rtc_rate_get (void)
{
    return am_kl26_clk_erclk32k_rate_get();
}

/**
 * \brief �õ�UART0��ʱ��Ƶ��
 * \return  UART0��ʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_uart0_rate_get (void)
{
    uint32_t clk = 0;

    if (amhw_kl26_sim_uart0_src_get() == KL26_SIM_UART0SRC_DISABLED) {
        /** \brief TPMʱ�ӽ��� */
    } else if (amhw_kl26_sim_uart0_src_get() == KL26_SIM_UART0SRC_MCGIRCLK) {
        /** \brief  MCGIRCLK��TPMʱ��Դ */
        clk = am_kl26_clk_mcgirclk_rate_get();
    } else if (amhw_kl26_sim_uart0_src_get() == KL26_SIM_UART0SRC_OSCERCLK) {
        /** \brief  OSCERCLK��TPMʱ��Դ */
        clk = am_kl26_clk_oscclk_rate_get();
    } else {
        /** \brief  MCGPLLCLK/MCGFLLCLK��TPMʱ��Դ */
        if (amhw_kl26_sim_pllfll_sel_get() == KL26_SIM_PLLFLLSEL_FLL) {
            clk = am_kl26_clk_mcgfllclk_rate_get();
        } else {
            clk = am_kl26_clk_mcgpllclk_rate_get() / 2;
        }
    }

    return clk;
}

/**
 * \brief �õ�wdt��ʱ��Ƶ��
 * \return  wdt��ʱ��Ƶ�ʣ���λ��Hz��
 */
uint32_t am_kl26_clk_wdt_rate_get (void)
{
    uint32_t clk = 0;
    if (amhw_kl26_sim_cop_src_get() == KL26_SIM_COP_CLK_INTERNAL) {
        clk = __AM_KL26_CLK_RATE_LPO;
    } else {
        clk = am_kl26_clk_bus_clkrate_get();
    }

    return clk;
}

uint32_t __lptmr_periph_rate_get (void)
{
	uint32_t clk_src = amhw_fsl_lptmr_clock_get(KL26_LPTMR);

	uint32_t frq = 0;

	switch (clk_src) {
	case AMHW_FSL_LPTMR_CLOCK_SRC_MCGIRCLK:
		frq = am_kl26_clk_mcgirclk_rate_get();
		break;

	case AMHW_FSL_LPTMR_CLOCK_SRC_LPOCLK:

		frq = __AM_KL26_CLK_RATE_LPO;
		break;

	case AMHW_FSL_LPTMR_CLOCK_SRC_ER32KCLK:

		frq = am_kl26_clk_erclk32k_rate_get();
		break;

	case AMHW_FSL_LPTMR_CLOCK_SRC_OSCERCLK:

		frq =  am_kl26_clk_oscclk_rate_get();

		break;

	default :

		frq = 0;
		break;
	}

	return frq;

}

/**
 * \brief ��ȡlptmrʱ��Դ��С
 * \param[in] p_hw_lptmr : ָ��LPTMR�Ĵ������ָ��
 * \return ʱ��Դ��С
 */
uint32_t am_kl26_clk_lptmr_rate_get (void)
{
    uint32_t clk;
    amhw_fsl_lptmr_clock_src_t lptmr_clk;

    lptmr_clk = (amhw_fsl_lptmr_clock_src_t)
                (amhw_fsl_lptmr_ps_reg_get(KL26_LPTMR) & 0x3);

    switch (lptmr_clk) {

    case AMHW_FSL_LPTMR_CLOCK_SRC_MCGIRCLK:
        clk = am_kl26_clk_mcgirclk_rate_get();
        break;
    case AMHW_FSL_LPTMR_CLOCK_SRC_LPOCLK:
        clk = __AM_KL26_CLK_RATE_LPO;
        break;
    case AMHW_FSL_LPTMR_CLOCK_SRC_ER32KCLK:
        clk = am_kl26_clk_erclk32k_rate_get();
        break;
    case AMHW_FSL_LPTMR_CLOCK_SRC_OSCERCLK:
        clk = am_kl26_clk_oscclk_rate_get();
        break;
    default:
        clk = 0;
        break;
    }

    return clk;
}
/**
 * \brief ��ȡʱ��Ƶ��
 */
int am_clk_rate_get (am_clk_id_t clk_id)
{
    uint32_t clk = 0;
    

    switch (clk_id) {
    
    case CLK_SLOW_IRC:
        clk = __AM_KL26_CLK_RATE_IRC_SLOW;
        break;

    case CLK_FAST_IRC:
        clk = __AM_KL26_CLK_RATE_IRC_FAST;
        break;

    case CLK_XTAL:
        clk = __gp_clk_dev->p_devinfo->xtal_rate;
        break;

    case CLK_CLKIN:
        clk = __gp_clk_dev->p_devinfo->xtal_rate;
        break;

    case CLK_CORE:
    case CLK_SYSTEM:
        clk = am_kl26_clk_core_clkrate_get();
        break;

    case CLK_BUS:
    case CLK_FLASH:
    case CLK_PERIPH:
        clk = am_kl26_clk_bus_clkrate_get();
        break;

    case CLK_SYSTICK:
        clk = am_kl26_clk_core_clkrate_get();
        break;

    case CLK_OSC32K:
        clk = am_kl26_clk_erclk32k_rate_get();
        break;

    case CLK_OSCERC:
        clk = am_kl26_clk_oscclk_rate_get();
        break;

    case CLK_RTCOUT:
        clk = am_kl26_clk_rtc_clkout_rate_get();
        break;

    case CLK_MCGFLL:
        clk = am_kl26_clk_mcgfllclk_rate_get();
        break;

    case CLK_MCGPLL:
        clk = am_kl26_clk_mcgpllclk_rate_get();
        break;

    case CLK_MCGEXT:
        clk = am_kl26_clk_oscclk_rate_get();
        break;

    case CLK_MCGIRC:
        clk = am_kl26_clk_mcgirclk_rate_get();
        break;

    case CLK_MCGOUT:
        clk = am_kl26_clk_mcgoutclk_rate_get();
        break;

    case CLK_LPO:
        clk = __AM_KL26_CLK_RATE_LPO;
        break;

    case CLK_WDT:
        clk = am_kl26_clk_wdt_rate_get();
        break;

#if 1
    /* Device clk */
    case CLK_TPM0:
    case CLK_TPM1:
    case CLK_TPM2:
        clk = am_kl26_clk_tpm_rate_get();
        break;

    case CLK_UART0:
        clk = am_kl26_clk_uart0_rate_get();
        break;

    case CLK_I2C1:
    case CLK_SPI1:
    case CLK_DMA:
        clk = am_kl26_clk_core_clkrate_get();
        break;

    case CLK_RTC:
        clk = am_kl26_clk_rtc_rate_get();
        break;

    case CLK_LPTMR:
        clk = am_kl26_clk_lptmr_rate_get();
        break;

    case CLK_PORTA:
    case CLK_PORTB:
    case CLK_PORTC:
    case CLK_PORTD:
    case CLK_PORTE:
    case CLK_UART1:
    case CLK_UART2:
    case CLK_SPI0:
    case CLK_I2C0:
    case CLK_CMP:
    case CLK_FTF:
    case CLK_DMAMUX:
    case CLK_PIT:
    case CLK_ADC0:
    case CLK_DAC0:
    case CLK_TSI:
        clk = am_kl26_clk_bus_clkrate_get();
        break;

    case CLK_I2S:
    /* I2S ʱ����I2Sģ���ڲ���Ƶ */
        clk = 0;
        break;

#endif

    default : 
        clk = 0;
        break;  
    }
    
    return clk;
}

/**
 * \brief ʹ��ָ����ϵͳ������ʱ��
 */
int am_clk_enable (am_clk_id_t clk_id)
{
    if ((clk_id < CLK_PERIPH_ID_MIN) ||
        (clk_id > CLK_PERIPH_ID_MAX)) {

        /* ʱ��ID���ڷ�Χ��*/
        return -AM_ENXIO;
    }
    
    amhw_kl26_sim_periph_clock_enable((amhw_kl26_sim_scgc_periph_t) (clk_id));
    
    return AM_OK;
}

/**
 * \brief ����ָ����ϵͳ������ʱ��
 */
int am_clk_disable (am_clk_id_t clk_id)
{
    if ((clk_id < CLK_PERIPH_ID_MIN) ||
        (clk_id > CLK_PERIPH_ID_MAX)) {

        /* ʱ��ID���ڷ�Χ��*/
        return -AM_ENXIO;
    }
        
    amhw_kl26_sim_periph_clock_disable ((amhw_kl26_sim_scgc_periph_t) (clk_id));
    
    return AM_OK;
}

/** \brief get the fll_div
 *
 * \param clk 8-32MHz
 *
 * \return the fll_div
 * \note  31250< clk /(31250 << fll_div) < 390625
 * */
uint32_t __fll_div_get (uint32_t clk)
{
    uint8_t div = 0;

    for (div = 0; (clk >>(5 + div) > 390625); div++);

    return div;
}

/** \brief clk fei mode init */
uint32_t __clk_fei_init(void)
{
    /* Ĭ�Ϲر�ATM�ڲ��ο�ʱ���������� */
    amhw_kl26_mcg_atm_disable();

    /* ʹ���ڲ��ο�ʱ�� �ر�osc��� */
    amhw_kl26_mcg_osc_monitor_disable();

    /* CLKDIV */
    amhw_kl26_sim_clkdiv1_outdiv1_set(__gp_clk_dev->outdiv1);
    amhw_kl26_sim_clkdiv1_outdiv4_set(__gp_clk_dev->outdiv4);

    /* ���������MCGPLLCLK/MCGFLLCLKʱ��Դ  */
    amhw_kl26_sim_pllfll_sel_set(KL26_SIM_PLLFLLSEL_FLL);

    /* ����FLL��ʱ��ԴΪ�ڲ���Դ */
    amhw_kl26_mcg_fll_src_set(KL26_TPM2_FLL_SRC_IRC_SLOW);
    
    /* enable MCGIRCLKʱ�� */
    amhw_kl26_mcg_irc_src_set(KL26_TPM2_IRC_SRC_SLOW);

    amhw_kl26_mcg_irc_enable();

    /* ���FLLʱ��Դ */
    while (amhw_kl26_mcg_fll_stat_get() == 0x00U);

    /* fll mul */
    amhw_kl26_mcg_fll_dco_div_set((amhw_kl26_mcg_dco_div_t)__gp_clk_dev->fll_rate);

    amhw_kl26_mcg_outclk_src_set(KL26_TPM2_OUTCLK_SRC_PLLS);
    
    /* ģʽ��� */
    while (amhw_kl26_mcg_outclk_stat_get() != KL26_TPM2_OUTCLK_SATA_FLL);

    return AM_OK;
}

/** \brief clk pee mode init */
uint32_t __clk_pee_init(void)
{
    /* Ĭ�Ϲر�ATM�ڲ��ο�ʱ���������� */
    amhw_kl26_mcg_atm_disable();

    /* CLKDIV */
    amhw_kl26_sim_clkdiv1_outdiv1_set(__gp_clk_dev->outdiv1);
    amhw_kl26_sim_clkdiv1_outdiv4_set(__gp_clk_dev->outdiv4);

    /* OSC32KSEL */
    amhw_kl26_sim_ercclk32k_src_set(KL26_SIM_OSC32KSEL_LPO);

    /* ����MCGPLLCLK/MCGFLLCLKʱ��Դ  */
    amhw_kl26_sim_pllfll_sel_set(KL26_SIM_PLLFLLSEL_PLL);

    /** \brief  ����FCRDIV */
    amhw_kl26_mcg_irc_fast_div_set(0);

    /* OSCERCLKʱ������ */
    amhw_kl26_mcg_osc_monitor_disable();
    amhw_kl26_mcg_osc_range_set(KL26_TPM2_OSC_RANGE_VERYHIGH);
    amhw_kl26_mcg_osc_src_set(KL26_TPM2_OSC_SRC_OSC);
    amhw_kl26_mcg_erc_enable();

    /* ����FLL */
    amhw_kl26_mcg_fll_src_set(KL26_TPM2_FLL_SRC_ERC);
    amhw_kl26_mcg_fll_erc_div_set(__gp_clk_dev->fll_div);

    /* enable MCGIRCLKʱ�� */
    amhw_kl26_mcg_irc_src_set(KL26_TPM2_IRC_SRC_SLOW);
    amhw_kl26_mcg_irc_enable();

    /* mcgooutclk use erc*/
    amhw_kl26_mcg_outclk_src_set(KL26_TPM2_OUTCLK_SRC_ERC);

    /* �ȴ��ⲿ�����ȶ� */
    while (AM_FALSE == amhw_kl26_mcg_osc_stable_stat_get());

    /** \brief  ���FLLʱ��Դ */
    while (amhw_kl26_mcg_fll_stat_get() != 0x00U);

    /* fll mul */
    amhw_kl26_mcg_fll_dco_div_set((amhw_kl26_mcg_dco_div_t)__gp_clk_dev->fll_rate);

    /* PEEģʽ�� PLL */
    amhw_kl26_mcg_pll_disable();
    amhw_kl26_mcg_pll_erc_div_set(__gp_clk_dev->pll_div);
    amhw_kl26_mcg_pll_vco_div_set(__gp_clk_dev->pll_mul);

    /* PLL en*/
    amhw_kl26_mcg_pll_enable();

    /** \brief  FBE-->PBE*/
    amhw_kl26_mcg_plls_src_set(KL26_TPM2_PLLS_SRC_PLL);

    /** \brief  �ȴ�PLL���� */
    while (AM_FALSE == amhw_kl26_mcg_pll_locked_stat_get());

    /** \brief  FBE-->PBE*/
    amhw_kl26_mcg_outclk_src_set(KL26_TPM2_OUTCLK_SRC_PLLS);

    /** \brief  PEEģʽ��� */
    while (amhw_kl26_mcg_outclk_stat_get() != KL26_TPM2_OUTCLK_SATA_PLL);

    return AM_OK;
}

/** \brief 32.768�ⲿ�����ʼ����������ģʽ */
void __clk_32k_osc_init(void)
{
	/* MCG config */
    amhw_kl26_mcg_osc_src_set(KL26_TPM2_OSC_SRC_OSC);       /* extern ref src select */
    amhw_kl26_mcg_osc_range_set(KL26_TPM2_OSC_RANGE_LOW);   /* RANGE = 0 */
    amhw_kl26_mcg_osc_gain_set(KL26_TPM2_OSC_GAIN_LOW);     /* HGO   = 0 */

    /* RTC moudle osc config */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_RTC);  /* RTC periph clock */

    amhw_fsl_rtc_osc_enable(KL26_RTC);                    /* 32.768k oscillator enable */


    /* sim ERCCLK32K select */
    amhw_kl26_sim_ercclk32k_src_set(KL26_SIM_OSC32KSEL_SYS);
    
}

/**
 * \brief CLK ��ʼ��
 */
int am_kl26_clk_init (am_kl26_clk_dev_t           *p_dev,
                      const am_kl26_clk_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return -AM_EINVAL;
    }

    /* CLKƽ̨��ʼ��������ʱ������ */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    if (p_devinfo->clk_mode == AM_KL26_CLK_MODE_PEE) {
        /* �ⲿʱ��Ƶ�ʲ���ȷ*/
        if ((p_devinfo->xtal_rate < 8000000) ||
            (p_devinfo->xtal_rate > 32000000)) {
            return -AM_EINVAL;
        }
    }

    p_dev->p_devinfo  = p_devinfo;

    /* PLLIN = 2MHz, PLLOUT = 96MHz*/
    p_dev->pll_div = (p_dev->p_devinfo->xtal_rate / 2000000UL) -1;
    p_dev->pll_mul = (96000000 / 2000000) - 24;

    /* FLLIN = 32.768KHz, FLLOUT = 40-50MHz */
    p_dev->fll_div = __fll_div_get(p_dev->p_devinfo->xtal_rate);
    p_dev->fll_rate = KL26_TPM2_DOC_DIV_1280;

    /* outdiv1 = 1, outdiv4 = 1,
     * CORE_CLK = MCGOUTCLK / (1 + OUTDIV1) = 96MHz / (1+1)=48MHz
     * BUS_CLK = CORE_CLK / (1 + OUTDIV4) = 48MHz / (1+1) = 24MHz
     */
    p_dev->outdiv1 = p_devinfo->core_clk_div - 1;
    p_dev->outdiv4 = 1;

    __gp_clk_dev = p_dev;

    /* PEE MODE */
    if (p_devinfo->clk_mode == AM_KL26_CLK_MODE_PEE) {
        return __clk_pee_init();
    }
    
    /* FEI MODE */
    if (p_devinfo->clk_mode == AM_KL26_CLK_MODE_FEI) {

        p_dev->fll_rate = KL26_TPM2_DOC_DIV_1464;

        return __clk_fei_init();
    }

    return AM_OK;
}


/**
 * \brief ��ȡʱ�ӹ���ģʽ
 */
am_kl26_clk_mode_t am_kl26_clk_mode_get (void)
{
    am_kl26_clk_mode_t          mode   = AM_KL26_CLK_MODE_ERROR;
    amhw_kl26_mcg_outclk_stat_t clkst  = amhw_kl26_mcg_outclk_stat_get();
    amhw_kl26_mcg_fll_src_t     irefst = amhw_kl26_mcg_fll_src_get();
    am_bool_t                      lp     = amhw_kl26_mcg_lp_plls_get();
    am_bool_t                      pllst  = amhw_kl26_mcg_plls_stat_get();

    switch (clkst) {

        case KL26_TPM2_OUTCLK_SATA_FLL:
            if (!pllst) {
                if (KL26_TPM2_FLL_SRC_ERC == irefst) {
                    mode = AM_KL26_CLK_MODE_FEE;
                } else {
                    mode = AM_KL26_CLK_MODE_FEI;
                }
            }
        break;

        case KL26_TPM2_OUTCLK_SATA_IRC:
            if ((KL26_TPM2_FLL_SRC_IRC_SLOW == irefst) && (!pllst)) {
                if (!lp) {
                    mode = AM_KL26_CLK_MODE_FBI;
                } else {
                    mode = AM_KL26_CLK_MODE_BLPI;
                }
            }
        break;

        case KL26_TPM2_OUTCLK_SATA_ERC:
            if (KL26_TPM2_FLL_SRC_ERC == irefst) {
                if (!lp) {
                    if (pllst) {
                        mode = AM_KL26_CLK_MODE_PBE;
                    } else {
                        mode = AM_KL26_CLK_MODE_FBE;
                    }
                } else {
                    mode = AM_KL26_CLK_MODE_BLPE;
                }
            }
        break;

        case KL26_TPM2_OUTCLK_SATA_PLL:
            if ((KL26_TPM2_FLL_SRC_ERC == irefst) && pllst) {
                mode = AM_KL26_CLK_MODE_PEE;
            }
            break;

        default:
        break;
    }

    return mode;
}

/**
 * \brief ����ʱ�ӹ���ģʽPEE��BLPEģʽ���͹���ģʽ��
 * \return ��
 * \note BLPEģʽ��CORE_CLK = 4MHZ
 *                 BUS_CLK = 1MHZ
 */
int am_kl26_clk_mode_pee2blpe (void)
{
    volatile uint32_t i = 0;

    uint32_t xtal_rate = __gp_clk_dev->p_devinfo->xtal_rate;

    /** \brief ��鵱ǰģʽ�Ƿ���PEEģʽ */
    if (am_kl26_clk_mode_get() != AM_KL26_CLK_MODE_PEE) {
        return AM_ERROR;
    }

    /** \brief  ѡ��ERC��ΪMCGOUTCLKʱ��Դ (PEE->PBE)*/
    amhw_kl26_mcg_outclk_src_set(KL26_TPM2_OUTCLK_SRC_ERC);

    /** \brief  �ȴ���ΪPBEģʽ */
    for (i = 0; i < 2000; i++) {
        if (KL26_TPM2_OUTCLK_SATA_ERC == amhw_kl26_mcg_outclk_stat_get()) {
            break;
        }
    }
    if (KL26_TPM2_OUTCLK_SATA_ERC != amhw_kl26_mcg_outclk_stat_get()) {
        return AM_ERROR;
    }

    /** \brief �ر�PLL/FLLģ�� (PBE->BLPE) */
    amhw_kl26_mcg_lp_plls_disable();

    /** \brief �ⲿ�ο�ʱ��Ƶ�ʷ�Ƶ��sysyclk=4MHz,��4��Ƶ��flashclk=1MHz */
    amhw_kl26_sim_clkdiv1_outdiv1_set(xtal_rate /(4*1000*1000) - 1);
    amhw_kl26_sim_clkdiv1_outdiv4_set(3);

    return AM_OK;
}

/**
 * \brief ����ʱ�ӹ���ģʽBLPE��PEEģʽ
 * \return ��
 * \note PEEģʽ,CORE_CLK = 48MHZ
 *               BUS_CLK = 24MHZ
 */
int am_kl26_clk_mode_blpe2pee (void)
{
    volatile uint32_t i = 0;

    /** \brief ��鵱ǰģʽ�Ƿ���BLPEģʽ */
    if (am_kl26_clk_mode_get() != AM_KL26_CLK_MODE_BLPE) {
        return AM_ERROR;
    }

    amhw_kl26_mcg_pll_erc_div_set(__gp_clk_dev->pll_div);
    amhw_kl26_mcg_pll_vco_div_set(__gp_clk_dev->pll_mul);

    /** \brief ��PLL/FLLģ�� (BLPE-PBE) */
    amhw_kl26_mcg_lp_plls_enable();

    /** \brief �ȴ�PLLSʱ��ԴΪPLL��� */
    for (i = 0; i < 2000; i++) {
        if (AM_TRUE == amhw_kl26_mcg_plls_stat_get()) {
            break;
        }
    }
    if (AM_TRUE != amhw_kl26_mcg_plls_stat_get()) {
        return AM_ERROR;
    }

    /** \brief �ȴ�PLL���� */
    for (i = 0; i < 2000; i++) {
        if (AM_TRUE == amhw_kl26_mcg_pll_locked_stat_get()) {
            break;
        }
    }
    if (AM_TRUE != amhw_kl26_mcg_pll_locked_stat_get()) {
        return AM_ERROR;
    }

    /** \brief  ѡ��PLLS��ΪMCGOUTCLKʱ��Դ (PBE->PEE)*/
    amhw_kl26_mcg_outclk_src_set(KL26_TPM2_OUTCLK_SRC_PLLS);

    /** \brief  �ȴ���ΪPEEģʽ */
    for (i = 0; i < 2000; i++) {
        if (KL26_TPM2_OUTCLK_SATA_PLL == amhw_kl26_mcg_outclk_stat_get()) {
            break;
        }
    }
    if (KL26_TPM2_OUTCLK_SATA_PLL != amhw_kl26_mcg_outclk_stat_get()) {
        return AM_ERROR;
    }

    /** \brief OUTCLKʱ��Ƶ��96MHz,��Ƶ��sysyclk�ͷ�Ƶ��flashclk */
    amhw_kl26_sim_clkdiv1_outdiv1_set(__gp_clk_dev->outdiv1);
    amhw_kl26_sim_clkdiv1_outdiv4_set(__gp_clk_dev->outdiv4);

    return AM_OK;
}

/**
 * \brief ����ʱ�ӹ���ģʽPBE��PEEģʽ
 * \return ��
 * \note PEEģʽ,CORE_CLK = 48MHZ
 *               BUS_CLK = 24MHZ
 */
int am_kl26_clk_mode_pbe2pee(void)
{
    volatile uint32_t i = 0;

    /** \brief ��鵱ǰģʽ�Ƿ���PBEģʽ */
    if (am_kl26_clk_mode_get() != AM_KL26_CLK_MODE_PBE) {
       return AM_ERROR;
    }
    /** \brief  ѡ��PLLS��ΪMCGOUTCLKʱ��Դ (PBE->PEE)*/
    amhw_kl26_mcg_outclk_src_set(KL26_TPM2_OUTCLK_SRC_PLLS);

    /** \brief  �ȴ���ΪPEEģʽ */
    for (i = 0; i < 2000; i++) {
       if (KL26_TPM2_OUTCLK_SATA_PLL == amhw_kl26_mcg_outclk_stat_get()) {
           break;
       }
    }
    if (KL26_TPM2_OUTCLK_SATA_PLL != amhw_kl26_mcg_outclk_stat_get()) {
       return AM_ERROR;
    }

    /** \brief OUTCLKʱ��Ƶ��96MHz,��Ƶ��sysyclk�ͷ�Ƶ��flashclk */
    amhw_kl26_sim_clkdiv1_outdiv1_set(__gp_clk_dev->outdiv1);
    amhw_kl26_sim_clkdiv1_outdiv4_set(__gp_clk_dev->outdiv4);

    return AM_OK;
}
/**
 * \brief ����ʱ�ӹ���ģʽFEI��BLPIģʽ���͹���ģʽ��
 * \return ��
 * \note BLPIģʽ,
 *       Core clock = 4MHz
 *       Bus clock  = 1MHz
 */
int am_kl26_clk_mode_fei2blpi (void)
{
    volatile uint32_t i = 0;

    /** \brief ��鵱ǰģʽ�Ƿ���PEIģʽ */
    if (am_kl26_clk_mode_get() != AM_KL26_CLK_MODE_FEI) {
        return AM_ERROR;
    }
    /**< \brief  ����IRCCLKʱ��ԴΪ�ڲ����ٲο�ʱ�� */
    amhw_kl26_mcg_irc_fast_div_set(0);
    amhw_kl26_mcg_irc_src_set(KL26_TPM2_IRC_SRC_FAST);

    /** \brief  ѡ��IRC��ΪMCGOUTCLKʱ��Դ (FEI->FBI)*/
    amhw_kl26_mcg_outclk_src_set(KL26_TPM2_OUTCLK_SRC_IRC);

    /** \brief  �ȴ���ΪFBIģʽ */
    for (i = 0; i < 2000; i++) {
        if (KL26_TPM2_OUTCLK_SATA_IRC == amhw_kl26_mcg_outclk_stat_get()) {
            break;
        }
    }

    if (KL26_TPM2_OUTCLK_SATA_IRC != amhw_kl26_mcg_outclk_stat_get()) {
        return AM_ERROR;
    }

    /** \brief �ر�PLL/FLLģ�� (FBI->BLPI) */
    amhw_kl26_mcg_lp_plls_disable();

    /** \brief �ڲ��ο�ʱ��Ƶ����4MHz,1��Ƶ��sysyclk��5��Ƶ��bus/flashclk�����ܳ���800KHz */
    amhw_kl26_sim_clkdiv1_outdiv1_set(0);
    amhw_kl26_sim_clkdiv1_outdiv4_set(4);

    return AM_OK;
}

/**
 * \brief ����ʱ�ӹ���ģʽBLPI��FEIģʽ
 * \return ��
 * \note FBIģʽ
 *       Core clock = 20.97152MHz
 *       Bus clock  = 20.97152MHz
 */
int am_kl26_clk_mode_blpi2fei (void)
{
    volatile uint32_t i = 0;

    /** \brief ��鵱ǰģʽ�Ƿ���BLPIģʽ */
    if (am_kl26_clk_mode_get() != AM_KL26_CLK_MODE_BLPI) {
        return AM_ERROR;
    }

    /** \brief  ����FLL */
    amhw_kl26_mcg_fll_erc_div_set(0);
    amhw_kl26_mcg_fll_dco_div_set(KL26_TPM2_DOC_DIV_640);

    /** \brief ��PLL/FLLģ�� (BLPI->FBI) */
    amhw_kl26_mcg_lp_plls_enable();

    /** \brief  ѡ��FLL��ΪMCGOUTCLKʱ��Դ (FBI->FEI)*/
    amhw_kl26_mcg_outclk_src_set(KL26_TPM2_OUTCLK_SRC_PLLS);

    /** \brief  �ȴ���ΪFBIģʽ */
    for (i = 0; i < 2000; i++) {
        if (KL26_TPM2_OUTCLK_SATA_FLL == amhw_kl26_mcg_outclk_stat_get()) {
            break;
        }
    }
    if (KL26_TPM2_OUTCLK_SATA_FLL != amhw_kl26_mcg_outclk_stat_get()) {
        return AM_ERROR;
    }
    /** \brief MCGOUTʱ��Ƶ����20.97152MHz,1��Ƶ��sysyclk��2��Ƶ��busclk */
    amhw_kl26_sim_clkdiv1_outdiv1_set(__gp_clk_dev->outdiv1);

    /* flashʱ�Ӳ��ܳ���24M*/
    amhw_kl26_sim_clkdiv1_outdiv4_set(__gp_clk_dev->outdiv4);

    return AM_OK;
}

/** \brief �õ����������Ƶ�� */
uint32_t am_kl26_clk_periph_rate_get(void *p_periph)
{
    uint32_t base_addr = (uint32_t)(p_periph);

    if ( (base_addr == KL26_UART1_BASE) ||
         (base_addr == KL26_UART2_BASE) ||
         (base_addr == KL26_SPI0_BASE)  ||
         (base_addr == KL26_I2C0_BASE) ) {
        return am_kl26_clk_bus_clkrate_get();

    } else if ( (base_addr == KL26_GPIO_BASE) ||
                (base_addr == KL26_SPI1_BASE) ||
                (base_addr == KL26_I2C1_BASE) ){
        return am_kl26_clk_core_clkrate_get();

    } else if (base_addr == KL26_UART0_BASE) {
        return am_kl26_clk_uart0_rate_get();

    } else if ( (base_addr == KL26_TPM0_BASE) ||
                (base_addr == KL26_TPM1_BASE) ||
                (base_addr == KL26_TPM2_BASE) ){
        return am_kl26_clk_tpm_rate_get();
          
    } else if (base_addr == KL26_LPTMR_BASE) {

    	return __lptmr_periph_rate_get();
        
    } else {
        return am_kl26_clk_bus_clkrate_get();
    }
}


/* end of file */
