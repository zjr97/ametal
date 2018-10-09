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
 * \brief ʱ��ѡ��Ϳ��ƽӿ�
 *
 * \internal
 * \par Modification history
 * - 1.02 15-11-23  lnk, modified
 * - 1.01 15-07-21  win, add function amhw_lpc82x_clk_clkout_update() and
 *                       amhw_lpc82x_clk_clkout_update_chk().
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC82X_CLK_H
#define __AMHW_LPC82X_CLK_H

#include "ametal.h"
#include "hw/amhw_lpc82x_syscon.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc82x_if_clk
 * \copydoc amhw_lpc82x_clk.h
 * @{
 */

/**
 * \name Ƶ��ֵ����
 *
 * ���ʹ�����ⲿ�ܽţ�PIO0_22����Ϊʱ������ܽţ�����Ҫ��
 * AMHW_LPC82X_CLK_FREQ_CLKIN ����Ϊ��ȷ��Ƶ��ֵ.
 *
 * @{
 */

/** \brief �ڲ�IRCƵ��         */
#define AMHW_LPC82X_CLK_FREQ_IRC      12000000UL  
/** \brief �ⲿ�ܽŵ�����Ƶ��  */
#define AMHW_LPC82X_CLK_FREQ_CLKIN    12000000UL   
/** \brief �ⲿ����Ƶ��        */
#define AMHW_LPC82X_CLK_FREQ_XTAL     12000000UL   

/** @} */

/**
 * \brief ϵͳ������ʱ�ӱ��
 */
typedef enum amhw_lpc82x_clk_periph {
    AMHW_LPC82X_CLK_SYS = 0,           /**< \brief System ʱ��         */
    AMHW_LPC82X_CLK_ROM,               /**< \brief ROM ʱ��            */
    AMHW_LPC82X_CLK_SRAM0_1,           /**< \brief SRAM0 SRAM1 ʱ��    */
    AMHW_LPC82X_CLK_FLASHREG,          /**< \brief FLASH�Ĵ����ӿ�ʱ�� */
    AMHW_LPC82X_CLK_FLASH,             /**< \brief FLASH ʱ��          */
    AMHW_LPC82X_CLK_I2C0,              /**< \brief I2C0ʱ��            */
    AMHW_LPC82X_CLK_GPIO,              /**< \brief GPIO ʱ��           */
    AMHW_LPC82X_CLK_SWM,               /**< \brief SWM ʱ��            */
    AMHW_LPC82X_CLK_SCT,               /**< \brief SCT ʱ��            */
    AMHW_LPC82X_CLK_WKT,               /**< \brief WKT ʱ��            */
    AMHW_LPC82X_CLK_MRT,               /**< \brief MRTʱ��             */
    AMHW_LPC82X_CLK_SPI0,              /**< \brief SPI0 ʱ��           */
    AMHW_LPC82X_CLK_SPI1,              /**< \brief SPI1 ʱ��           */
    AMHW_LPC82X_CLK_CRC,               /**< \brief CRC ʱ��            */
    AMHW_LPC82X_CLK_UART0,             /**< \brief UART0 ʱ��          */
    AMHW_LPC82X_CLK_UART1,             /**< \brief UART1 ʱ��          */
    AMHW_LPC82X_CLK_UART2,             /**< \brief UART2 ʱ��          */
    AMHW_LPC82X_CLK_WWDT,              /**< \brief WWDT ʱ��           */
    AMHW_LPC82X_CLK_IOCON,             /**< \brief IOCON ʱ��          */
    AMHW_LPC82X_CLK_ACMP,              /**< \brief ACMP ʱ��           */
    AMHW_LPC82X_CLK_I2C1 = 21,         /**< \brief I2C1 ʱ��           */
    AMHW_LPC82X_CLK_I2C2,              /**< \brief I2C2 ʱ��           */
    AMHW_LPC82X_CLK_I2C3,              /**< \brief I2C3 ʱ��           */
    AMHW_LPC82X_CLK_ADC0,              /**< \brief ADC ʱ��            */
    AMHW_LPC82X_CLK_MTB = 26,          /**< \brief MTB ʱ��            */
    AMHW_LPC82X_CLK_DMA = 29           /**< \brief DMA ʱ��            */
} amhw_lpc82x_clk_periph_t;

/**
 * \brief PLL ����ʱ��Դ
 */
typedef enum amhw_lpc82x_pllinclk_src {
    AMHW_LPC82X_CLK_PLLIN_SRC_IRC = 0,   /**< \brief �ڲ�IRC           */
    AMHW_LPC82X_CLK_PLLIN_SRC_SYSOSC,    /**< \brief ϵͳ����        */
    AMHW_LPC82X_CLK_PLLIN_SRC_CLKIN = 3  /**< \brief �ⲿ��������ʱ��  */
} amhw_lpc82x_pllinclk_src_t;                                          
                                                                       
/**                                                                    
 * \brief ��ʱ��Դ                                                     
 */                                                                    
typedef enum amhw_lpc82x_clk_main_src {                                
    AMHW_LPC82X_CLK_MAIN_SRC_IRC = 0,    /**< \brief �ڲ�IRC           */
    AMHW_LPC82X_CLK_MAIN_SRC_PLLIN,      /**< \brief PLL input         */
    AMHW_LPC82X_CLK_MAIN_SRC_WDTOSC,     /**< \brief ���Ź�����      */
    AMHW_LPC82X_CLK_MAIN_SRC_PLLOUT      /**< \brief PLL Output        */
} amhw_lpc82x_clk_main_src_t;                                          
                                                                       
/**                                                                    
 * \brief CLKOUT ���ŵ�ʱ��Դ                                          
 */                                                                    
typedef enum amhw_lpc82x_clk_clkout_src {                              
    AMHW_LPC82X_CLK_CLKOUT_SRC_IRC = 0,  /**< \brief �ڲ�IRC           */
    AMHW_LPC82X_CLK_CLKOUT_SRC_SYSOSC,   /**< \brief ϵͳ����        */
    AMHW_LPC82X_CLK_CLKOUT_SRC_WDTOSC,   /**< \brief ���Ź�����      */
    AMHW_LPC82X_CLK_CLKOUT_SRC_MAINCLK   /**< \brief ��ʱ��            */
} amhw_lpc82x_clk_clkout_src_t;

/**
 * \brief IOCON ʱ�ӷ�Ƶѡ��
 */ 
typedef enum amhw_lpc82x_clk_iocon_div_t {
    AMHW_LPC82X_CLK_IOCON_CLKDIV0 = 0,   /**< \brief IOCON ʱ�ӷ�Ƶ��0 */
    AMHW_LPC82X_CLK_IOCON_CLKDIV1,       /**< \brief IOCON ʱ�ӷ�Ƶ��1 */
    AMHW_LPC82X_CLK_IOCON_CLKDIV2,       /**< \brief IOCON ʱ�ӷ�Ƶ��2 */
    AMHW_LPC82X_CLK_IOCON_CLKDIV3,       /**< \brief IOCON ʱ�ӷ�Ƶ��3 */
    AMHW_LPC82X_CLK_IOCON_CLKDIV4,       /**< \brief IOCON ʱ�ӷ�Ƶ��4 */
    AMHW_LPC82X_CLK_IOCON_CLKDIV5,       /**< \brief IOCON ʱ�ӷ�Ƶ��5 */
    AMHW_LPC82X_CLK_IOCON_CLKDIV6,       /**< \brief IOCON ʱ�ӷ�Ƶ��6 */
} amhw_lpc82x_clk_iocon_div_t;

/**
 * \brief �õ��ڲ�IRCʱ��Ƶ��
 *
 * \return �ڲ�IRCʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_lpc82x_clk_irc_rate_get (void)
{
    return AMHW_LPC82X_CLK_FREQ_IRC;
}

/**
 * \brief �õ��ⲿXTALʱ��Ƶ��
 *
 * \return �ⲿXTALʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_lpc82x_clk_xtal_rate_get (void)
{
    return AMHW_LPC82X_CLK_FREQ_XTAL;
}

/**
 * \brief �õ��ⲿ�ܽ�����ʱ��Ƶ��
 *
 * \return �ⲿ�ܽ�����ʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_lpc82x_clk_clkin_rate_get (void)
{
    return AMHW_LPC82X_CLK_FREQ_CLKIN;
}


/**
 * \brief �õ�WDT������ʱ��Ƶ��
 *
 * \return  WDT������ʱ��Ƶ�ʣ���λ��Hz��
 *
 * \note ���Ƶ�ʾ���������40%�����
 */
uint32_t amhw_lpc82x_clk_wdt_rate_get (void);

/**
 * \brief PLL ���ƼĴ�������
 *
 * \param[in] msel : ������Ƶ����ֵ
 * \param[in] psel : �󱳷�Ƶ����ֵ
 *
 * \return ��
 * \note  M = msel + 1
 *        P = 2^(psel)
 *        PLLOUT = M * PLLIN;
 *        FCCO = 2 * P * PLLOUT;
 *        PLLIN��������Ƶ��10MHz��25MHz������M��ֵʹ��PLLOUT���Ƶ�ʵ���100MHz,
 *        ����P��ֵʹFCCOƵ����156MHz��320MHz
 */
am_static_inline
void amhw_lpc82x_clk_pllctrl_set (uint8_t msel, uint8_t psel)
{
    LPC82X_SYSCON->syspllctrl = AM_SBF(psel, 5) | msel;
}

/**
 * \brief PLLʱ��Դѡ��
 *
 * \param[in] src : PLLʱ��Դ
 * 
 * \return ��
 *
 */
am_static_inline
void amhw_lpc82x_clk_pll_src_set (amhw_lpc82x_pllinclk_src_t src)
{
    LPC82X_SYSCON->syspllclksel = (uint32_t)src;
    
    /* ����PLLʱ�� */
    LPC82X_SYSCON->syspllclkuen = 0x00;
    LPC82X_SYSCON->syspllclkuen = 0x01;
}    

/**
 * \brief ʹ��ָ����ϵͳ������ʱ��
 *
 * \param[in] clk : ָ���Ĵ�ʹ�ܵ�ϵͳ������ʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_clk_periph_enable (amhw_lpc82x_clk_periph_t clk)
{
    AM_BIT_SET(LPC82X_SYSCON->sysahbclkctrl, clk);
}

/**
 * \brief ����ָ����ϵͳ������ʱ��
 *
 * \param[in] clk : ָ���Ĵ����ܵ�ϵͳ������ʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_clk_periph_disable (amhw_lpc82x_clk_periph_t clk)
{
    AM_BIT_CLR(LPC82X_SYSCON->sysahbclkctrl, clk);
}

/**
 * \brief ��ȡϵͳPLL���ʱ��Ƶ��
 *
 * \return PLL���ʱ��Ƶ��
 */
uint32_t amhw_lpc82x_clk_pllout_rate_get (void);

/**
 * \brief ��ȡϵͳPLL����ʱ��Ƶ��
 *
 * \return PLL����ʱ��Ƶ��
 */
uint32_t amhw_lpc82x_clk_pllin_rate_get (void);

/**
 * \brief �ж�PLL�Ƿ�����
 *
 * \return AM_TRUE  ����
 *          AM_FALSE δ����
 */
am_static_inline
am_bool_t amhw_lpc82x_clk_pll_locked_chk (void)
{
    return (am_bool_t)(LPC82X_SYSCON->syspllstat & 0x01);
}

/**
 * \brief ϵͳ������·����ʹ��/����
 *
 * \param[in] bypass : ��·ϵͳ����  AM_FALSE-����,TURE-ʹ��
 * \param[in] highfr : ����Ƶ�ʷ�Χ  AM_FALSE: 1-20MHz TRUE:15-25MHz
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_clk_pll_bypass_set (am_bool_t bypass, am_bool_t highfr)
{
    if (bypass) {
        AM_BIT_SET(LPC82X_SYSCON->sysoscctrl, 0);
    } else {
        AM_BIT_CLR(LPC82X_SYSCON->sysoscctrl, 0);
    }
    
    if (highfr) {
        AM_BIT_SET(LPC82X_SYSCON->sysoscctrl, 1);
    } else {
        AM_BIT_CLR(LPC82X_SYSCON->sysoscctrl, 1);
    }
}

/**
 * \brief ���� main ʱ��Դ
 *
 * \param[in] src : mainʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_clk_main_src_set (amhw_lpc82x_clk_main_src_t src)
{
    LPC82X_SYSCON->mainclksel = (uint32_t)src;
    
    /* ����mainʱ�� */
    LPC82X_SYSCON->mainclkuen = 0x00;
    LPC82X_SYSCON->mainclkuen = 0x01;
}


/**
 * \brief �õ� main ʱ��Դ
 *
 * \return main ʱ��Դ
 */
am_static_inline
amhw_lpc82x_clk_main_src_t amhw_lpc82x_clk_main_src_get (void)
{
    return (amhw_lpc82x_clk_main_src_t)(LPC82X_SYSCON->mainclksel);
}

/**
 * \brief �õ� main ʱ��Ƶ��
 *
 * \return  main ʱ��Ƶ�ʣ���λ:Hz��
 */
uint32_t amhw_lpc82x_clk_main_clkrate_get (void);


/**
 * \brief ���� CLKOUT ʱ��Դ�ͷ�Ƶֵ
 *
 * \param[in] src : CLKOUT��ʱ��Դ
 * \param[in] div : ��CLKOUTʱ��Դ�ķ�Ƶ
 *
 * \return ��
 *
 * \note ��ƵֵΪ0ʱ������CLKOUT�������������ЧֵΪ1~255. 
 *       ����CLKOUT�ܽ������ʱ��Ƶ��ΪCLKOUTʱ��Դ��Ƶ�ʳ��Է�Ƶϵ����
 */
void amhw_lpc82x_clk_clkout_config (amhw_lpc82x_clk_clkout_src_t src,  
                                    uint32_t                     div);

/**
 * \name  WDTOSC��ѡƵ�ʶ���
 * \anchor grp_amhw_lpc82x_clk_wdtosc_rate
 *  @{
 */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_0_6MHZ     1   /**< \brief 0.6MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_1_05MHZ    2   /**< \brief 1.05MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_1_4MHZ     3   /**< \brief 1.4MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_1_75MHZ    4   /**< \brief 1.75MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_2_1MHZ     5   /**< \brief 2.1MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_2_4MHZ     6   /**< \brief 2.4MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_2_7MHZ     7   /**< \brief 2.7MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_3_0MHZ     8   /**< \brief 3.0MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_3_25MHZ    9   /**< \brief 3.25MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_3_5MHZ     10  /**< \brief 3.5MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_3_75MHZ    11  /**< \brief 3.75MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_4_0MHZ     12  /**< \brief 4.0MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_4_2MHZ     13  /**< \brief 4.2MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_4_4MHZ     14  /**< \brief 4.4MHz */
#define AMHW_LPC82X_CLK_WDTOSC_RATE_4_6MHZ     15  /**< \brief 4.6MHz */

/** @} */

/**
 * \brief WDTOSC ���ƼĴ�������
 *
 * \param[in] rate : ѡ���Ź��������Ƶ��, 
 *                   �μ� \ref grp_amhw_lpc82x_clk_wdtosc_rate
 * \param[in] div  : ΪFclkanaѡ���Ƶϵ��, 2 - 64֮���ż��
 *
 * \return ��
 * 
 * \note  ���Ź�����Ƶ���ڸ�λ����Ҫ��������
 */
am_static_inline
void amhw_lpc82x_clk_wdtoscc_cfg (uint8_t rate, 
                                  uint8_t div)
{                                          
    LPC82X_SYSCON->wdtoscctrl = AM_SBF((uint8_t) (rate), 5) |
                                     ((div >> 1) - 1);
}

/**
 * \brief ����ϵͳʱ�ӷ�Ƶֵ
 *
 * \param[in] div : ϵͳʱ�ӷ�Ƶֵ
 *
 * \return ��
 *
 * \note ��ƵֵΪ0ʱ������ϵͳʱ�ӣ�������ЧֵΪ1~255.
 *       ϵͳʱ��Ƶ��Ϊ��ʱ��Ƶ�ʳ��Ըô����õ�ϵͳʱ�ӷ�Ƶֵ��
 */
am_static_inline
void amhw_lpc82x_clk_system_clkdiv_set (uint8_t div)
{
    LPC82X_SYSCON->sysahbclkdiv = div;
}

/**
 * \brief �õ�ϵͳʱ�ӷ�Ƶֵ
 *
 * \return ϵͳʱ�ӷ�Ƶֵ
 */
am_static_inline
uint8_t amhw_lpc82x_clk_system_clkdiv_get (void)
{
    return LPC82X_SYSCON->sysahbclkdiv & 0xFF;
}

/**
 * \brief �õ�ϵͳʱ��Ƶ��
 *
 * \return ϵͳʱ��Ƶ��
 */
uint32_t amhw_lpc82x_clk_system_clkrate_get (void);

/**
 * \brief ����ʱ�ӷ�Ƶ
 *
 * \param[in] div : ��Ƶ��ֵ�趨
 *
 * \return ��
 *
 * \note ��ƵֵΪ0ʱ�����ܴ���ʱ�ӣ�������ЧֵΪ1~255.
 *       ����ʱ��Ƶ��Ϊ��ʱ��Ƶ�ʳ��Ըô����õĴ���ʱ�ӷ�Ƶֵ��
 */
am_static_inline
void amhw_lpc82x_syscon_uartclkdiv_set(uint8_t div)
{
    LPC82X_SYSCON->uartclkdiv = div;
}

/**
 * \brief ���ô���С����Ƶ����ֵ
 *
 * \param[in] fmul : С����Ƶ���ı�����
 * \param[in] fdiv : С����Ƶ���ĳ��� (������0xFF)
 *
 * \return ��
 *
 * \note    U_PCLK = UARTCLKDIV / (1 + MULT/DIV)
 */
am_static_inline
void amhw_lpc82x_syscon_usart_frgctrl_set (uint8_t fmul, uint8_t fdiv)
{
    LPC82X_SYSCON->uartfrgdiv  = fdiv;
    LPC82X_SYSCON->uartfrgmult = fmul;
}

/**
 * \brief ��ȡ���ڻ�������Ƶ�ʣ�ͨ��FRG��
 *
 * \return ���ڻ�������Ƶ��ֵ
 */
uint32_t amhw_lpc82x_clk_usart_baseclkrate_get (void);

/**
 * \brief ���ô��ڻ�������Ƶ��
 *
 * \param[in] rate : �����Ĵ��ڻ�������Ƶ������ֵ������С��ϵͳʱ��Ƶ�ʣ�
 *
 * \retval   AM_OK     : �����ɹ�
 * \retval  -AM_EINVAL : ��Ч����
 *
 * \note ʵ�ʵĴ��ڻ�������Ƶ��ֵ������������ֵ����ƫ��
 */
int amhw_lpc82x_clk_usart_baseclkrate_set (uint32_t rate);

/**
 * \brief ���� IOCON ʱ�ӷ�Ƶ
 *
 * \param[in] divider : ��Ҫ���õ�IOCON��Ƶ��
 * \param[in] div     : ��Ƶֵ
 *
 * \return ��
 * \note ���÷�Ƶֵ0ʹ�رգ�������Ƶֵ0-255
 */
am_static_inline
void amhw_lpc82x_clk_iocon_div_set (amhw_lpc82x_clk_iocon_div_t divider, 
                                    uint8_t                     div)
{
    int t_divider = AMHW_LPC82X_CLK_IOCON_CLKDIV6 - divider;

    LPC82X_SYSCON->ioconclkdiv[t_divider] = div;
}

/**
 * \brief ��ȡIOCON ʱ��Ƶ��
 *
 * \param[in] divider : ��Ҫ��ȡ��IOCON��Ƶ��
 *
 * \return ��ӦIOCON�����˲���Ƶ��
 */
am_static_inline
uint32_t 
amhw_lpc82x_clk_iocon_rate_get (amhw_lpc82x_clk_iocon_div_t divider)
{
    int32_t div = LPC82X_SYSCON->ioconclkdiv[divider] & 0xFF;

    return (div == 0)? (0) : (amhw_lpc82x_clk_main_clkrate_get() / div);
}

/**
 * \brief �õ����������Ƶ��
 *
 * \param[in] p_periph : ָ������ļĴ������ָ��
 *
 * \return ���������Ƶ��
 *
 */
uint32_t amhw_lpc82x_clk_periph_freq_get (void *p_periph);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_LPC82X_CLK_H */

/* end of file */
