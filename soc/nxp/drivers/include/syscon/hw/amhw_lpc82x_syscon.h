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
 * \brief ϵͳ���ƽӿ�
 *
 * 1. ʱ�ӿ���
 *    - ����ϵͳ PLL ��
 *    - ����ϵͳ�����Ϳ��Ź�������
 *    - ʹ��������ڴ�ʱ�ӣ�
 *    - ����ʱ�������
 *    - ����ʱ�ӷ�Ƶ���������˲���ʱ�Ӻ� USART ������ʱ�ӣ�
 * 2. ���Ӻ͸�λ���裻
 * 3. ѡ�������ⲿ�жϺ�ģʽƥ�����棻
 * 4. ���õ͹���ģʽ��
 * 5. ���ѿ��ƣ�
 * 6. �����⣨BOD�����ã�
 * 7. MTB ����������ֹͣ��
 * 8. �ж���ʱ���ƣ�
 * 9. ѡ�� NMI Դ��
 * 10. У׼ϵͳʱ�Ӷ�ʱ����
 *
 * \internal
 * \par History
 * - 1.02 15-07-17  win, modify the file brief.
 * - 1.01 15-07-13  zxl, modified.
 * - 1.00 15-06-21  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC82X_SYSCON_H
#define __AMHW_LPC82X_SYSCON_H

#include "ametal.h"
#include "am_lpc82x.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc82x_if_syscon
 * \copydoc amhw_lpc82x_syscon.h
 * @{
 */

/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef struct amhw_lpc82x_syscon {
    __IO uint32_t sysmemremap;     /**< \brief ϵͳ�ڴ��ض���Ĵ���          */
    __IO uint32_t presetctrl;      /**< \brief ���踴λ����                  */
    __IO uint32_t syspllctrl;      /**< \brief PLL���ƼĴ���                 */
    __IO uint32_t syspllstat;      /**< \brief PLL״̬�Ĵ���                 */
    __I  uint32_t reserved0[4];    /**< \brief ����λ                        */
    __IO uint32_t sysoscctrl;      /**< \brief ϵͳʱ��Դ���ƼĴ���          */
    __IO uint32_t wdtoscctrl;      /**< \brief ���Ź�ʱ��Դ���ƼĴ���        */
    __IO uint32_t ircctrl;         /**< \brief IRC���ƼĴ���(����LPC82X��Ч) */
    __I  uint32_t reserved1[1];    /**< \brief ����λ                        */
    __IO uint32_t sysrststat;      /**< \brief ϵͳ��λ״̬�Ĵ���            */
    __I  uint32_t reserved2[3];    /**< \brief ����λ                        */
    __IO uint32_t syspllclksel;    /**< \brief ϵͳʱ��Դѡ��Ĵ���          */
    __IO uint32_t syspllclkuen;    /**< \brief ϵͳPLLʱ�Ӹ���ʹ�ܼĴ���     */
    __I  uint32_t reserved3[10];   /**< \brief ����λ                        */
    __IO uint32_t mainclksel;      /**< \brief ��ʱ��Դѡ��                  */
    __IO uint32_t mainclkuen;      /**< \brief ��ʱ�Ӹ���ʹ��                */
    __IO uint32_t sysahbclkdiv;    /**< \brief ϵͳAHBʱ�ӷ�Ƶ               */
    __I  uint32_t reserved4[1];    /**< \brief ����λ                        */
    __IO uint32_t sysahbclkctrl;   /**< \brief ϵͳAHBʱ�ӿ��ƼĴ���         */
    __I  uint32_t reserved5[4];    /**< \brief ����λ                        */
    __IO uint32_t uartclkdiv;      /**< \brief ����ʱ�ӷ�Ƶ��                */
    __I  uint32_t reserved6[18];   /**< \brief ����λ                        */
    __IO uint32_t clkoutsel;       /**< \brief CLKOUTʱ��Դѡ��              */
    __IO uint32_t clkoutuen;       /**< \brief CLKOUTʱ�Ӹ���ʹ��            */
    __IO uint32_t clkoutdiv;       /**< \brief CLKOUT ʱ�ӷ�Ƶ�Ĵ���         */
    __I  uint32_t reserved7;       /**< \brief ����λ                        */
    __IO uint32_t uartfrgdiv;      /**< \brief ����С��ʱ�ӷ�Ƶ����SUB��     */
    __IO uint32_t uartfrgmult;     /**< \brief ����С��ʱ�ӷ�Ƶ����ADD��)    */
    __I  uint32_t reserved8[1];    /**< \brief ����λ                        */
    __IO uint32_t exttracecmd;     /**< \brief �ⲿ׷��BUFFER����Ĵ���      */
    __IO uint32_t pioporcap0;      /**< \brief ����ɣ�״̬                  */
    __I  uint32_t reserved9[12];   /**< \brief ����λ                        */
    __IO uint32_t ioconclkdiv[7];  /**< \brief ICON ʱ�ӷ�Ƶ                 */
    __IO uint32_t bodctrl;         /**< \brief BOD���ƼĴ���                 */
    __IO uint32_t systckcal;       /**< \brief ϵͳ�δ�������̶ȶ���        */
    __I  uint32_t reserved10[6];   /**< \brief ����λ                        */
    __IO uint32_t irqlatency;      /**< \brief IRQ��ʱ�Ĵ���                 */
    __IO uint32_t nmisrc;          /**< \brief NMI���ƼĴ���                 */
    __IO uint32_t pintsel[8];      /**< \brief �����ж�ѡ��Ĵ���            */
    __I  uint32_t reserved11[27];  /**< \brief ����λ                        */
    __IO uint32_t starterp0;       /**< \brief ʹ�ܻ��ѼĴ���0               */
    __I  uint32_t reserved12[3];   /**< \brief ����λ                        */
    __IO uint32_t starterp1;       /**< \brief ʹ�ܻ��ѼĴ���01              */
    __I  uint32_t reserved13[6];   /**< \brief ����λ                        */
    __IO uint32_t pdsleepcfg;      /**< \brief �������˯�����üĴ���        */
    __IO uint32_t pdawakecfg;      /**< \brief �������üĴ���                */
    __IO uint32_t pdruncfg;        /**< \brief �������üĴ���                */
    __I  uint32_t reserved14[111]; /**< \brief ����λ                        */
    __I  uint32_t deviceid;        /**< \brief �豸ID                        */
} amhw_lpc82x_syscon_t;

/**
 * \brief ϵͳ�ڴ���ӳ�䣬������ӳ���ж�������
 */
typedef enum amhw_lpc82x_syscon_bootmode_remap {

    /** \brief bootlaoder Mode �ж���������ӳ��������ROM�� */
    AM_SYSYCON_REMAP_BOOTROM_MODE = 0,

    /** \brief User RAM Mode �ж���������ӳ����SRAM�� */
    AM_SYSYCON_REMAP_SRAM_MODE,

    /** \brief User Flash Mode �ж���������ӳ�䣬������FLASH�� */
    AM_SYSYCON_REMAP_FLASH_MODE
} amhw_lpc82x_syscon_bootmode_remap_t;

/**
 * \brief ��ӳ���ж�������
 *
 * \param[in] remap : ѡ����ӳ���������ڴ���
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_remap_set (amhw_lpc82x_syscon_bootmode_remap_t remap)
{
    LPC82X_SYSCON->sysmemremap = (uint32_t)remap;
}

/**
 * \brief ��ȡ�ж����������ӳ��ֵ
 *
 * \return �ж����������ӳ��ֵ
 */
am_static_inline
amhw_lpc82x_syscon_bootmode_remap_t amhw_lpc82x_syscon_remap_get (void)
{
    return (amhw_lpc82x_syscon_bootmode_remap_t)LPC82X_SYSCON->sysmemremap;
}

/**
 * \brief ����Systick��У׼ֵ
 *
 * \param[in] systickcal_val : Systick��У׼ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_systickcal_set (uint32_t systickcal_val)
{
    LPC82X_SYSCON->systckcal = systickcal_val;
}


/**
 * \brief �õ�Systick��У׼ֵ
 *
 * \return Systick��У׼ֵ
 */
am_static_inline
uint32_t amhw_lpc82x_syscon_systickcal_get (void)
{
    return LPC82X_SYSCON->systckcal;
}

/**
 * \name ϵͳ��λ״ֵ̬
 * \anchor grp_amhw_lpc82x_syscon_rststat
 * @{
 */

#define AMHW_LPC82X_SYSCON_RSTSTAT_POR    AM_BIT(0) /**< \brief �ϵ縴λ     */
#define AMHW_LPC82X_SYSCON_RSTSTAT_EXTRST AM_BIT(1) /**< \brief �ⲿ�ܽŸ�λ */
#define AMHW_LPC82X_SYSCON_RSTSTAT_WDT    AM_BIT(2) /**< \brief ���Ź���λ   */
#define AMHW_LPC82X_SYSCON_RSTSTAT_BOD    AM_BIT(3) /**< \brief �����⸴λ */
#define AMHW_LPC82X_SYSCON_RSTSTAT_SYSRST AM_BIT(4) /**< \brief �����λ     */

/** @} */

/**
 * \brief ��ȡϵͳ��λ״̬
 *
 * \return ���AMHW_LPC82X_SYSCON_RSTSTAT_*��Ļ�OR��ֵ��
 *         �μ� \ref grp_amhw_lpc82x_syscon_rststat
 */
am_static_inline
uint32_t amhw_lpc82x_syscon_rst_stat_get (void)
{
    return LPC82X_SYSCON->sysrststat;
}

/**
 * \brief ���ϵͳ��λ״̬
 *
 * \param[in] reset : ���AMHW_LPC82X_SYSCON_RSTSTAT_*��Ļ�OR��ֵ��
 *                    �μ� \ref grp_amhw_lpc82x_syscon_rststat
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_rst_stat_clr (uint32_t reset)
{
    LPC82X_SYSCON->sysrststat = reset;
}

/**
 * \brief �������踴λ��ö��ֵ
 */
typedef enum amhw_lpc82x_syscon_periph_reset {
    AMHW_LPC82X_RESET_SPI0 = 0,           /**< \brief SPI0         */
    AMHW_LPC82X_RESET_SPI1,               /**< \brief SPI1         */
    AMHW_LPC82X_RESET_UARTFRG ,           /**< \brief UARTFRG      */
    AMHW_LPC82X_RESET_UART0,              /**< \brief UART0        */
    AMHW_LPC82X_RESET_UART1,              /**< \brief UART1        */
    AMHW_LPC82X_RESET_UART2,              /**< \brief UART2        */
    AMHW_LPC82X_RESET_I2C0,               /**< \brief I2C0         */
    AMHW_LPC82X_RESET_MRT,                /**< \brief MRT          */
    AMHW_LPC82X_RESET_SCT,                /**< \brief SCT          */
    AMHW_LPC82X_RESET_WKT,                /**< \brief WKT          */
    AMHW_LPC82X_RESET_GPIO,               /**< \brief GPIO         */
    AMHW_LPC82X_RESET_FLASH,              /**< \brief FLASH        */
    AMHW_LPC82X_RESET_ACMP,               /**< \brief ACMP         */
    AMHW_LPC82X_RESET_I2C1 = 14,          /**< \brief I2C1         */
    AMHW_LPC82X_RESET_I2C2,               /**< \brief I2C2         */
    AMHW_LPC82X_RESET_I2C3,               /**< \brief I2C3         */
    AMHW_LPC82X_RESET_ADC = 24,           /**< \brief ADC          */
    AMHW_LPC82X_RESET_DMA = 29            /**< \brief DMA          */
} amhw_lpc82x_syscon_periph_reset_t;

/**
 * \brief ��λһ������
 *
 * \param[in] periph : ��Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_periph_reset (amhw_lpc82x_syscon_periph_reset_t periph)
{
    AM_BIT_CLR(LPC82X_SYSCON->presetctrl, periph);
    AM_BIT_SET(LPC82X_SYSCON->presetctrl, periph);
}

/**
 * \brief FLASH����ʱ�䶨��
 */
typedef enum amhw_lpc82x_syscon_flashtim {
    AMHW_LPC82X_SYSCON_FLASH_1CYCLE = 0, /**< \brief Flash ����ʹ��1��CPUʱ�� */
    AMHW_LPC82X_SYSCON_FLASH_2CYCLE      /**< \brief Flash ����ʹ��2��CPUʱ�� */
} amhw_lpc82x_syscon_flashtim_t;

/**
 * \brief ����ϵͳ�ж���ʱ
 *
 * \param[in] latency : ��ʱʱ�Ӹ���
 *
 * \return    ��
 *
 * \note   ��ʱʱ������0-255��ʱ��֮�䣬С��ֵ������õ��ӳ�
 *
 */
am_static_inline
void amhw_lpc82x_syscon_setirqlatency(uint32_t latency)
{
    LPC82X_SYSCON->irqlatency = latency;
}

/**
 * \brief ��ȡϵͳ�ж���ʱֵ
 *
 * \return ϵͳ�ж���ʱʱ�Ӹ���
 */
am_static_inline
uint32_t amhw_lpc82x_syscon_getirqlatency(void)
{
    return (LPC82X_SYSCON->irqlatency & 0xFF);
}

/**
 * \brief ���ò��������ж�Դ
 *
 * \param[in] intsrc : ����NMI���жϺţ�IRQ number��
 *
 * \return ��
 *
 * \note NMI�ж�Դ��ʱ���Ǵ��ڽ�ֹ״̬�ģ������ж�Դ��Ӧʹ��
 *       amhw_lpc82x_syscon_nmisrc_enable()����ʹ������NMI�ж�Դ
 */
am_static_inline
void amhw_lpc82x_syscon_nmisrc_set(uint32_t intsrc)
{
    /* �����NMIʹ��λ����д��ʱ��Դ */
    AM_BIT_CLR(LPC82X_SYSCON->nmisrc, 31);
    LPC82X_SYSCON->nmisrc  = intsrc;
}

/**
 * \brief ʹ��NMI�ж�Դ���ж�
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_nmisrc_enable (void)
{
    AM_BIT_SET(LPC82X_SYSCON->nmisrc, 31);
}

/**
 * \brief ����NMI�ж�Դ���ж�
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_nmisrc_disable (void)
{
    AM_BIT_CLR(LPC82X_SYSCON->nmisrc, 31);
}

/**
 * \brief ö��ֵ������ʹ�ܻ��߽��������жϵĻ���Դ
 *  
 *  ���ʹ����ĳ����Ļ���Դ������ж��ܹ���оƬ�����˯��ģʽ�͵���ģʽ����
 */
typedef enum amhw_lpc82x_syscon_wakeup {
    AMHW_LPC82X_SYSCON_STARTER_PINT0,           /**< \brief PINT0      */
    AMHW_LPC82X_SYSCON_STARTER_PINT1,           /**< \brief PINT1      */
    AMHW_LPC82X_SYSCON_STARTER_PINT2,           /**< \brief PINT2      */
    AMHW_LPC82X_SYSCON_STARTER_PINT3,           /**< \brief PINT3      */
    AMHW_LPC82X_SYSCON_STARTER_PINT4,           /**< \brief PINT4      */
    AMHW_LPC82X_SYSCON_STARTER_PINT5,           /**< \brief PINT5      */
    AMHW_LPC82X_SYSCON_STARTER_PINT6,           /**< \brief PINT6      */
    AMHW_LPC82X_SYSCON_STARTER_PINT7,           /**< \brief PINT7      */
    AMHW_LPC82X_SYSCON_STARTER_SPI0  = 32 + 0,  /**< \brief SPI0       */
    AMHW_LPC82X_SYSCON_STARTER_SPI1,            /**< \brief SPI1       */
    AMHW_LPC82X_SYSCON_STARTER_UART0 = 32 + 3,  /**< \brief UART0      */
    AMHW_LPC82X_SYSCON_STARTER_UART1,           /**< \brief UART1      */
    AMHW_LPC82X_SYSCON_STARTER_UART2,           /**< \brief UART2      */
    AMHW_LPC82X_SYSCON_STARTER_I2C1  = 32 + 7,  /**< \brief I2C1       */
    AMHW_LPC82X_SYSCON_STARTER_I2C0,            /**< \brief I2C0       */
    AMHW_LPC82X_SYSCON_STARTER_WWDT  = 32 + 12, /**< \brief WWDT       */
    AMHW_LPC82X_SYSCON_STARTER_BOD,             /**< \brief BOD        */
    AMHW_LPC82X_SYSCON_STARTER_WKT   = 32 + 15, /**< \brief WKT        */
    AMHW_LPC82X_SYSCON_STARTER_I2C2  = 32 + 21, /**< \brief I2C2       */
    AMHW_LPC82X_SYSCON_STARTER_I2C3             /**< \brief I2C3       */
} amhw_lpc82x_syscon_wakeup_t;

/**
 * \brief ʹ������Ļ���Դ
 *
 * \param[in] pid : �����жϵĻ���Դ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_wakeup_enable (amhw_lpc82x_syscon_wakeup_t pid)
{
    if (pid < 32) {
        AM_BIT_SET(LPC82X_SYSCON->starterp0, pid);
    } else {
        AM_BIT_SET(LPC82X_SYSCON->starterp1, pid - 32);
    }
}

/**
 * \brief ��������Ļ���Դ
 *
 * \param[in] pid : �����жϵĻ���Դ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_wakeup_disable (amhw_lpc82x_syscon_wakeup_t pid)
{
    if (pid < 32) {
        AM_BIT_CLR(LPC82X_SYSCON->starterp0, pid);
    } else {
        AM_BIT_CLR(LPC82X_SYSCON->starterp1, pid - 32);
    }
}

/**
 * \name ��Դ����λ����(0 = powered, 1 = powered down)
 * \anchor grp_amhw_lpc82x_syscon_pd
 * @{
 */

#define AMHW_LPC82X_SYSCON_PD_IRC_OUT AM_BIT(0)  /**< \brief IRC �������   */
#define AMHW_LPC82X_SYSCON_PD_IRC     AM_BIT(1)  /**< \brief IRC ����       */
#define AMHW_LPC82X_SYSCON_PD_FLASH   AM_BIT(2)  /**< \brief Flash            */
#define AMHW_LPC82X_SYSCON_PD_BOD     AM_BIT(3)  /**< \brief ������         */
#define AMHW_LPC82X_SYSCON_PD_ADC0    AM_BIT(4)  /**< \brief ADC              */
#define AMHW_LPC82X_SYSCON_PD_SYS_OSC AM_BIT(5)  /**< \brief ϵͳ�����Դ     */
#define AMHW_LPC82X_SYSCON_PD_WDT_OSC AM_BIT(6)  /**< \brief ���Ź�������Դ */
#define AMHW_LPC82X_SYSCON_PD_SYS_PLL AM_BIT(7)  /**< \brief SYS PLL          */
#define AMHW_LPC82X_SYSCON_PD_ACMP    AM_BIT(15) /**< \brief ģ��Ƚ�������   */

/** @} */

/**
 * \brief ��Deep_sleepģʽ������Դʹ��
 *
 * \param[in] flags ��AMHW_LPC82X_SYSCON_PD_BOD �� AMHW_LPC82X_SYSCON_PD_WDT_OSC
 *
 * \return ��
 *
 * \note Deep_sleepģʽ�£�ֻ����BOD��WDT����
 */
am_static_inline
void amhw_lpc82x_syscon_deepsleep_enable (uint32_t flags)
{
    AM_BIT_CLR_MASK(LPC82X_SYSCON->pdsleepcfg, flags);
}

/**
 * \brief ��Deep_sleepģʽ������Դ����
 *
 * \param[in] flags ��AMHW_LPC82X_SYSCON_PD_BOD �� AMHW_LPC82X_SYSCON_PD_WDT_OSC
 *
 * \return ��
 *
 * \note Deep_sleepģʽ�£�ֻ����BOD��WDT����
 */
am_static_inline
void amhw_lpc82x_syscon_deepsleep_disable (uint32_t flags)
{
    AM_BIT_SET_MASK(LPC82X_SYSCON->pdsleepcfg, flags);
}

/**
 * \brief ����ʱ�ɿ��������ĵ�Դ����
 *
 * \param[in] flags : �ɿ��������ĵ�Դ������� #amhw_lpc82x_syscon_powerstat_get()
 *
 * \return ��
 * 
 * \note ˯��ǰ��ʹ�� amhw_lpc82x_syscon_powerstat_get()��ȡ�ڼ�״̬��
 *       ����ʱ��ʹ�øĺ�������֮ǰ��״̬
 */
am_static_inline
void amhw_lpc82x_syscon_deepwakeup_cfg (uint32_t flags)
{
    LPC82X_SYSCON->pdawakecfg = flags;
}

/**
 * \brief deep ����ʱ�������ϵ�ʹ��
 *
 * \param[in] wakeupflags : AMHW_LPC82X_SYSCON_PD_* ��ֵ���� ��� ��OR��ֵ��
 *                          �μ� \ref grp_amhw_lpc82x_syscon_pd
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_deepwakeup_enable (uint32_t wakeupflags)
{
    AM_BIT_CLR_MASK(LPC82X_SYSCON->pdawakecfg, wakeupflags);
}

/**
 * \brief deep ����ʱ�������ϵ����
 *
 * \param[in] wakeupflags : AMHW_LPC82X_SYSCON_PD_* ��ֵ������� ��OR��ֵ��
 *                          �μ� \ref grp_amhw_lpc82x_syscon_pd
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_deepwakeup_disable (uint32_t wakeupflags)
{
    AM_BIT_SET_MASK(LPC82X_SYSCON->pdawakecfg, wakeupflags);
}

/**
 * \brief �õ���ǰ�ĵ�Դ���ƼĴ���״̬
 *
 * \return  AMHW_LPC82X_SYSCON_PD_* ��ֵ������� ��OR��ֵ��
 *          �μ� \ref grp_amhw_lpc82x_syscon_pd
 *
 * \note  ��ӦλΪ�ߵ�ƽ����������δ���磬�͵�ƽ��������
 */
am_static_inline
uint32_t amhw_lpc82x_syscon_powerstat_get (void)
{
    return LPC82X_SYSCON->pdruncfg;
}

/**
 * \brief �ر������Դ
 *
 * \param[in] powerdownmask ��AMHW_LPC82X_SYSCON_PD_* ��ֵ������Ļ�OR��ֵ,
 *                            �μ� \ref grp_amhw_lpc82x_syscon_pd
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_powerdown (uint32_t powerdownmask)
{
    AM_BIT_SET_MASK(LPC82X_SYSCON->pdruncfg, powerdownmask);
}

/**
 * \brief �������Դ    
 *
 * \param[in] powerupmask ��AMHW_LPC82X_SYSCON_PD_* ��ֵ������Ļ�OR��ֵ,
 *                          �μ� \ref grp_amhw_lpc82x_syscon_pd
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_powerup (uint32_t powerupmask)
{
    AM_BIT_CLR_MASK(LPC82X_SYSCON->pdruncfg, powerupmask);
}

/**
 * \brief ���ָ�������Ƿ��ϵ�
 *
 * \param[in] powermask : AMHW_LPC82X_SYSCON_PD_* ��ֵ��
 *                        �μ� \ref grp_amhw_lpc82x_syscon_pd
 *
 * \retval    AM_TRUE      : �������ϵ�
 * \retval     AM_FALSE     : ����δ�ϵ�
 */
am_static_inline
am_bool_t amhw_lpc82x_syscon_power_check (uint32_t powermask)
{
    return (am_bool_t)((LPC82X_SYSCON->pdruncfg & powermask) == 0);
}

/**
 * \brief ��ȡ�豸ID 0
 *
 * \return �豸ID 0
 */
am_static_inline
uint32_t amhw_lpc82x_syscon_deviceid0_get (void)
{
    return LPC82X_SYSCON->deviceid;
}


/**
 * \brief �����ж�ͨ��ѡ������
 *
 * \param[in] pint_sel : �ж�ͨ����ţ�#AMHW_LPC82X_PINT_CHAN_0��
 * \param[in] pin      : ���ű��(#PIO0_0)
 *
 * \return  ��
 */
am_static_inline
void amhw_lpc82x_syscon_pint_sel (int pint_sel, int pin)
{                         
    LPC82X_SYSCON->pintsel[pint_sel] = pin;
}



/**
 * \brief �����⸴λ�ĵ�Դ��ѹ�ȼ�
 */
typedef enum amhw_lpc82x_syscon_bod_rst_level {
    AMHW_LPC82X_SYSCON_BODRSTLVL_0,                /**< \brief �ȼ�0��1.46V */
    AMHW_LPC82X_SYSCON_BODRSTLVL_1_46V = AMHW_LPC82X_SYSCON_BODRSTLVL_0,
    AMHW_LPC82X_SYSCON_BODRSTLVL_1,                /**< \brief �ȼ�1��2.05V */
    AMHW_LPC82X_SYSCON_BODRSTLVL_2_05V = AMHW_LPC82X_SYSCON_BODRSTLVL_1,
    AMHW_LPC82X_SYSCON_BODRSTLVL_2,                /**< \brief �ȼ�2��2.34V */
    AMHW_LPC82X_SYSCON_BODRSTLVL_2_34V = AMHW_LPC82X_SYSCON_BODRSTLVL_2,
    AMHW_LPC82X_SYSCON_BODRSTLVL_3,                /**< \brief �ȼ�3��2.63V */
    AMHW_LPC82X_SYSCON_BODRSTLVL_2_63V = AMHW_LPC82X_SYSCON_BODRSTLVL_3
} amhw_lpc82x_syscon_bod_rst_level_t;


/**
 * \brief �������жϵĵ�Դ��ѹ�ȼ�
 */
typedef enum amHW_syscon_bod_int_level {
    AMHW_LPC82X_SYSCON_BODINTLVL_0,                /**< \brief �ȼ�0������ */
    AMHW_LPC82X_SYSCON_BODINTLVL_1,                /**< \brief �ȼ�1��2.25V */
    AMHW_LPC82X_SYSCON_BODINTLVL_2_25V = AMHW_LPC82X_SYSCON_BODINTLVL_1,
    AMHW_LPC82X_SYSCON_BODINTLVL_2,                /**< \brief �ȼ�2��2.54V */
    AMHW_LPC82X_SYSCON_BODINTLVL_2_54V = AMHW_LPC82X_SYSCON_BODINTLVL_2,
    AMHW_LPC82X_SYSCON_BODINTLVL_3,                /**< \brief �ȼ�3��2.85V */
    AMHW_LPC82X_SYSCON_BODINTLVL_2_85V = AMHW_LPC82X_SYSCON_BODINTLVL_3
} amhw_lpc82x_syscon_bod_int_level_t;


/**
 * \brief ���õ������жϺ͵����⸴λ�ĵ�Դ��ѹ�ȼ�
 *
 * \param[in] rstlvl : �����⸴λ��ѹ�ȼ�
 * \param[in] intlvl : �������жϵ�ѹ�ȼ�
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_bod_level_set (amhw_lpc82x_syscon_bod_rst_level_t rstlvl,
                                       amhw_lpc82x_syscon_bod_int_level_t intlvl)
{
    LPC82X_SYSCON->bodctrl = ((uint32_t)rstlvl) | AM_SBF(intlvl, 2);
}

/**
 * \brief ʹ�ܵ����⸴λ
 * \param[in] : ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_bod_rst_enable (void)
{
    AM_BIT_SET(LPC82X_SYSCON->bodctrl, 4);
}

/**
 * \brief ���ܵ����⸴λ
 * \param[in] : ��
 * \return ��
 */
am_static_inline
void amhw_lpc82x_syscon_bod_rst_disable (void)
{
    AM_BIT_CLR(LPC82X_SYSCON->bodctrl, 4);
}


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC82X_SYSCON_H */

/* end of file */
