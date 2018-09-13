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
 * \brief
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG217_RCC_H
#define __AMHW_ZLG217_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "zlg217_periph_map.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_zlg217_if_rcc
 * \copydoc amhw_zlg217_rcc.h
 * @{
 */

/**
 * \brief CRC�Ĵ�����ṹ��
 */
typedef struct amhw_zlg217_rcc {
  __IO uint32_t cr;        /**< \brief ʱ�ӿ��ƼĴ��� */
  __IO uint32_t cfgr;      /**< \brief ʱ�����üĴ��� */
  __IO uint32_t cir;       /**< \brief ʱ���жϼĴ��� */
  __IO uint32_t apb2rstr;  /**< \brief APB2���踴λ�Ĵ��� */
  __IO uint32_t apb1rstr;  /**< \brief APB1���踴λ�Ĵ��� */
  __IO uint32_t ahbenr;    /**< \brief AHB����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t apb2enr;   /**< \brief APB2����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t apb1enr;   /**< \brief APB1����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t bdcr;      /**< \brief ���ݿ��ƼĴ��� */
  __IO uint32_t csr;       /**< \brief ����״̬�Ĵ��� */
  __I  uint32_t reserve[7];/**< \brief ���� */
  __IO uint32_t syscfg;    /**< \brief ϵͳ���üĴ��� */
} amhw_zlg217_rcc_t;

/**
 * \brief ϵͳʱ��Դ
 */
typedef enum {
    AMHW_ZLG217_SYSCLK_HSI_DIV6,  /**< \brief HSI ����  6 ��Ƶ��Ϊϵͳʱ�� */
    AMHW_ZLG217_SYSCLK_HSE,       /**< \brief HSE ��Ϊϵͳʱ�� */
    AMHW_ZLG217_SYSCLK_PLL,       /**< \brief PLL �����Ϊϵͳʱ�� */
    AMHW_ZLG217_SYSCLK_LSI,       /**< \brief LSI �����Ϊϵͳʱ�� */
}amhw_zlg217_sys_clk_src;

/**
 * \brief RTCʱ��Դ
 */
typedef enum {
    AMHW_ZLG217_RTCCLK_LSE = 1,       /**< \brief PLL �����Ϊϵͳʱ�� */
    AMHW_ZLG217_RTCCLK_LSI = 2,       /**< \brief HSI ����  6 ��Ƶ��Ϊϵͳʱ�� */
    AMHW_ZLG217_RTCCLK_HSE_DIV128 =3, /**< \brief HSE ��Ϊϵͳʱ�� */
}amhw_zlg217_rtc_clk_src;

/**
 * \brief PLLʱ��Դ
 */
typedef enum {
    AMHW_ZLG217_PLLCLK_HSI_DIV4,  /**< \brief HSI ����  4 ��Ƶ��ΪPLL����ʱ�� */
    AMHW_ZLG217_PLLCLK_HSE,       /**< \brief HSE ��ΪPLL����ʱ�� */
}amhw_zlg217_pll_clk_src;

/**
 * \brief ʱ���жϱ�־
 */
typedef enum {
    AMHW_ZLG217_CLKINT_INDEX_LSI = 0,  /**< \brief LSI��־ */
    AMHW_ZLG217_CLKINT_INDEX_LSE = 1,  /**< \brief LSE��־ */
    AMHW_ZLG217_CLKINT_INDEX_HSI,      /**< \brief HSI��־ */
    AMHW_ZLG217_CLKINT_INDEX_HSE,      /**< \brief HSE��־ */
    AMHW_ZLG217_CLKINT_INDEX_PLL,      /**< \brief PLL��־ */
    AMHW_ZLG217_CLKINT_INDEX_CSSF = 7, /**< \brief CSSF(ʱ�Ӱ�ȫϵͳ�ж�)��־ */
}amhw_zlg217_clk_int_index;

/**
 * \brief APB2����ö��
 */
typedef enum {
    AMHW_ZLG217_RCC_APB2_AFIO   = 0,  /**< \brief AFIO */
    AMHW_ZLG217_RCC_APB2_IOPA   = 2,  /**< \brief IOPA */
    AMHW_ZLG217_RCC_APB2_IOPB   = 3,  /**< \brief IOPB */
    AMHW_ZLG217_RCC_APB2_IOPC   = 4,  /**< \brief IOPC */
    AMHW_ZLG217_RCC_APB2_IOPD   = 5,  /**< \brief IOPD */
    AMHW_ZLG217_RCC_APB2_IOPE   = 6,  /**< \brief IOPE */
    AMHW_ZLG217_RCC_APB2_ADC1   = 9,  /**< \brief ADC1 */
    AMHW_ZLG217_RCC_APB2_ADC2   = 10, /**< \brief ADC2 */
    AMHW_ZLG217_RCC_APB2_TIM1   = 11, /**< \brief TIM1 */
    AMHW_ZLG217_RCC_APB2_SPI1   = 12, /**< \brief SPI1 */
    AMHW_ZLG217_RCC_APB2_UART1  = 14, /**< \brief UART1 */
}amhw_zlg217_apb2_peripheral;

/**
 * \brief APB1����ö��
 */
typedef enum {
    AMHW_ZLG217_RCC_APB1_TIM2   = 0,   /**< \brief TIM2��ʱ�� */
    AMHW_ZLG217_RCC_APB1_TIM3   = 1,   /**< \brief TIM3��ʱ�� */
    AMHW_ZLG217_RCC_APB1_TIM4   = 2,   /**< \brief TIM4��ʱ�� */
    AMHW_ZLG217_RCC_APB1_WWDG   = 11,  /**< \brief WWDG���ڿ��Ź� */
    AMHW_ZLG217_RCC_APB1_SPI2   = 14,  /**< \brief SPI2 */
    AMHW_ZLG217_RCC_APB1_UART2  = 17,  /**< \brief UART2 */
    AMHW_ZLG217_RCC_APB1_UART3  = 18,  /**< \brief UART3 */
    AMHW_ZLG217_RCC_APB1_I2C1   = 21,  /**< \brief I2C1 */
    AMHW_ZLG217_RCC_APB1_I2C2   = 22,  /**< \brief I2C2 */
    AMHW_ZLG217_RCC_APB1_USB    = 23,  /**< \brief USB */
    AMHW_ZLG217_RCC_APB1_CAN    = 25,  /**< \brief CAN */
    AMHW_ZLG217_RCC_APB1_BKP    = 27,  /**< \brief BKP */
    AMHW_ZLG217_RCC_APB1_PWR    = 28,  /**< \brief ��Դ�ӿ� */
    AMHW_ZLG217_RCC_APB1_DAC    = 29,  /**< \brief DAC */
}amhw_zlg217_apb1_peripheral;

/**
 * \brief AHB����ö��
 */
typedef enum {
    AMHW_ZLG217_RCC_AHB_DMA   = 0,   /**< \brief DMA */
    AMHW_ZLG217_RCC_AHB_SRAM  = 2,   /**< \brief SRAM */
    AMHW_ZLG217_RCC_AHB_FLITF = 4,   /**< \brief FLITF */
    AMHW_ZLG217_RCC_AHB_CRC   = 6,   /**< \brief CRC */
    AMHW_ZLG217_RCC_AHB_AES   = 7,   /**< \brief AES */
}amhw_zlg217_ahb_peripheral;

/**
 * \brief ��λ��־ö��
 */
typedef enum {
    AMHW_ZLG217_RCC_CSR_PINRSTF   = (1ul << 26), /**< \brief NRST�ܽŸ�λ��־ */
    AMHW_ZLG217_RCC_CSR_PORRSTF   = (1ul << 27), /**< \brief �ϵ�/���縴λ��־ */
    AMHW_ZLG217_RCC_CSR_SFTRSTF   = (1ul << 28), /**< \brief �����λ��־ */
    AMHW_ZLG217_RCC_CSR_IWDGRSTF  = (1ul << 29), /**< \brief �������Ź���λ��־ */
    AMHW_ZLG217_RCC_CSR_WWDGRSTF  = (1ul << 30), /**< \brief ���ڿ��Ź���λ��־ */
    AMHW_ZLG217_RCC_CSR_LPWRRSTF  = (int)(1ul << 31), /**< \brief �͹��Ĺ���λ��־ */
}amhw_zlg217_reset_flag_t;

/**
 * \brief ϵͳ���üĴ���ö��
 */
typedef enum{
    AMHW_ZLG217_RCC_SYSCFG_0  =0,
    AMHW_ZLG217_RCC_SYSCFG_1  =1,
}amhw_zlg217_syscfg_peripheral;

/**
 * \brief �ڲ�����ʱ��ʹ��
 *
 * \return ��
 *
 */
am_static_inline
void amhw_zlg217_rcc_hsion_enable (void)
{
    ZLG217_RCC->cr |= 1ul;
}

/**
 * \brief �ڲ�����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ڲ� 8MHzʱ��û�о���
 * \retval FALSE : �ڲ� 8MHzʱ�Ӿ���
 */
am_static_inline
am_bool_t amhw_zlg217_rcc_hsirdy_read (void)
{
    return (am_bool_t)((ZLG217_RCC->cr & 0x2ul) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ��(HSE ����)ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_hseon_enable (void)
{
    ZLG217_RCC->cr |= (1ul << 16);
}

/**
 * \brief �ⲿ����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ⲿʱ��û�о���
 * \retval FALSE : �ⲿʱ�Ӿ���
 */
am_static_inline
am_bool_t amhw_zlg217_rcc_hserdy_read (void)
{
    return (am_bool_t)((ZLG217_RCC->cr & (1ul << 17)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ����·ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_hsebyp_enable (void)
{
    ZLG217_RCC->cr |= (1ul << 18);
}

/**
 * \brief ʱ�Ӱ�ȫϵͳʹ��
 *
 * \details ����ⲿ 8-24MHz����������ʱ�Ӽ����������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_ccson_enable (void)
{
    ZLG217_RCC->cr |= (1ul << 19);
}

/**
 * \brief PLL��Ƶϵ������
 *
 * \param[in]  div ����Ƶֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_plldm_set (uint8_t div)
{
    ZLG217_RCC->cr = ((div & 0x7ul) << 20) |
                            (ZLG217_RCC->cr & ~(0x7ul << 20));
}

/**
 * \brief PLL��Ƶϵ������
 *
 * \param[in]  mul ����Ƶֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_plldn_set (uint8_t mul)
{

    ZLG217_RCC->cr = ((mul & 0x3ful) << 26) |
                            (ZLG217_RCC->cr & ~(0x3ful << 26));
}

/**
 * \brief PLL ʹ��
 *
 * \details �����������ֹͣģʽʱ����λ��Ӳ�����㡣
 *          �� PLL ʱ�ӱ�������ѡ��Ҫ��Ϊϵͳʱ��ʱ,
 *          ��λ���ܱ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_pll_enable (void)
{
    ZLG217_RCC->cr |= (1ul << 24);
}

/**
 * \brief PLL ����
 *
 * \details �����������ֹͣģʽʱ����λ��Ӳ�����㡣
 *          �� PLL ʱ�ӱ�������ѡ��Ҫ��Ϊϵͳʱ��ʱ,
 *          ��λ���ܱ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_pll_disable (void)
{
    ZLG217_RCC->cr &= ~(1ul << 24);
}

/**
 * \brief PLL ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : PLL δ����
 * \retval FALSE : PLL ����
 */
am_static_inline
am_bool_t amhw_zlg217_rcc_pllrdy_read (void)
{
    return (am_bool_t)((ZLG217_RCC->cr & (1ul << 25)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ϵͳʱ���л�
 *
 * \param[in]  src ��ϵͳʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_sys_clk_set (amhw_zlg217_sys_clk_src src)
{

    ZLG217_RCC->cfgr = ((src & 0x3ul) << 0) |
                              (ZLG217_RCC->cfgr & ~(0x3ul << 0));
}

/**
 * \brief ��ǰϵͳʱ�ӻ�ȡ
 *
 * \return ��ǰϵͳʱ��Դ
 */
am_static_inline
amhw_zlg217_sys_clk_src amhw_zlg217_rcc_sys_clk_get (void)
{

    return (amhw_zlg217_sys_clk_src)((ZLG217_RCC->cfgr >> 2ul) & 0x3ul);
}

/**
 * \brief ����AHB Ԥ��Ƶ
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-7 �� ����Ƶ
 *       - 8   �� 2��Ƶ
 *       - 9   �� 4��Ƶ
 *       - 10  �� 8��Ƶ
 *       - 11  �� 16��Ƶ
 *       - 12  �� 64��Ƶ
 *       - 13  �� 128��Ƶ
 *       - 14  �� 256��Ƶ
 *       - 15  �� 512��Ƶ
 *
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_ahb_div_set (uint8_t div)
{

    ZLG217_RCC->cfgr = ((div & 0xful) << 4) |
                              (ZLG217_RCC->cfgr & ~(0xful << 4));
}

/**
 * \brief ���� ���� APB Ԥ��Ƶ��APB1��
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb1_div_set (uint8_t div)
{

    ZLG217_RCC->cfgr = ((div & 0x7ul) << 8) |
                              (ZLG217_RCC->cfgr & ~(0x7ul << 8));
}

/**
 * \brief ��ȡ ���� APB Ԥ��Ƶ��APB1��
 *
 * \return Ԥ��Ƶֵ
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 */
am_static_inline
uint8_t amhw_zlg217_rcc_apb1_div_get (void)
{

    return (uint8_t)((ZLG217_RCC->cfgr >> 8) & 0x7ul);
}

/**
 * \brief ���� ���� APB Ԥ��Ƶ��APB2��
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb2_div_set (uint8_t div)
{

    ZLG217_RCC->cfgr = ((div & 0x7ul) << 11) |
                              (ZLG217_RCC->cfgr & ~(0x7ul << 11));
}

/**
 * \brief ��ȡ ���� APB Ԥ��Ƶ��APB2��
 *
 * \return Ԥ��Ƶֵ
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 */
am_static_inline
uint8_t amhw_zlg217_rcc_apb2_div_get (void)
{

    return (uint8_t)((ZLG217_RCC->cfgr >> 11) & 0x7ul);
}

/**
 * \brief PLL����ʱ��ѡ��
 *
 * \param[in]  src ��PLL����ʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_pll_clk_set (amhw_zlg217_pll_clk_src src)
{

    ZLG217_RCC->cfgr = ((src & 0x3ul) << 16) |
                              (ZLG217_RCC->cfgr & ~(0x3ul << 16));
}

/**
 * \brief ��ǰPLL����ʱ�ӻ�ȡ
 *
 * \return ��ǰPLL����ʱ��Դ
 */
am_static_inline
amhw_zlg217_pll_clk_src amhw_zlg217_rcc_pll_clk_get (void)
{

    return (amhw_zlg217_pll_clk_src)((ZLG217_RCC->cfgr >> 16ul) & 0x3ul);
}

/**
 * \brief ѡ�� HSE ��Ƶ����Ϊ PLL ����
 *
 * \param[in]  div ����Ƶֵ
 *
 *      - 0  �� ����Ƶ
 *      - 1  �� 2��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_hseforpll_set (uint8_t div)
{

    ZLG217_RCC->cfgr = ((div & 0x1ul) << 17) |
                              (ZLG217_RCC->cfgr & ~(0x1ul << 17));
}

/**
 * \brief ѡ�� USB Ԥ��Ƶ
 *
 * \param[in]  div ����Ƶֵ
 *
 *      - 0  �� PLL ʱ��ֱ����Ϊ USB ʱ��
 *      - 1  �� PLL ʱ��2 ��Ƶ��Ϊ USBʱ��
 *      - 2  �� PLL ʱ��3 ��Ƶ��Ϊ USBʱ��
 *      - 3  �� PLL ʱ��4 ��Ƶ��Ϊ USBʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_pllforusb_set (uint8_t div)
{

    ZLG217_RCC->cfgr = ((div & 0x3ul) << 22) |
                              (ZLG217_RCC->cfgr & ~(0x3ul << 22));
}

/**
 * \brief USB Ԥ��Ƶ��ȡ
 *
 * \retval  0  �� PLL ʱ��ֱ����Ϊ USB ʱ��
 * \retval  1  �� PLL ʱ��2 ��Ƶ��Ϊ USBʱ��
 * \retval  2  �� PLL ʱ��3 ��Ƶ��Ϊ USBʱ��
 * \retval  3  �� PLL ʱ��4 ��Ƶ��Ϊ USBʱ��
 */
am_static_inline
uint8_t amhw_zlg217_rcc_pllforusb_get (void)
{

    return (uint8_t)((ZLG217_RCC->cfgr >> 22ul) & 0x3ul);
}

/**
 * \brief ΢������ʱ�����ѡ��
 *
 * \details 1.��ʱ��������������л� MCO ʱ��Դʱ���ܻᱻ�ض�,
 *          2.��ϵͳʱ����Ϊ����� MCO �ܽ�ʱ���뱣֤���ʱ��Ƶ
 *            �ʲ����� 50MHz��IO�����Ƶ�ʣ�
 *
 * \param[in]  src ��ʱ��Դ
 *
 *      - 0-1 �� û��ʱ�����
 *      - 2   �� LSI ʱ�����
 *      - 3   �� ����
 *      - 4   �� ϵͳʱ�ӣ�SYSCLK�����
 *      - 5   �� HSI ʱ�����
 *      - 6   �� HSE ʱ�����
 *      - 7   �� PLL ʱ��2 ��Ƶ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_mco_src_set (uint8_t src)
{

    ZLG217_RCC->cfgr = ((src & 0x7ul) << 24ul) |
                              (ZLG217_RCC->cfgr & ~(0x7ul << 24ul));
}

/**
 * \brief �����ж�ʹ��
 *
 * \param[in]  index ��������־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_clkint_enable (amhw_zlg217_clk_int_index index)
{

    ZLG217_RCC->cir |= ((index & 0x1ful) << 8);
}

/**
 * \brief �����жϽ���
 *
 * \param[in]  index ��������־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_clkint_disable (amhw_zlg217_clk_int_index index)
{

    ZLG217_RCC->cir &= ~((index & 0x1ful) << 8);
}

/**
 * \brief ��ȡ�жϱ�־
 *
 * \return �жϱ�־
 */
am_static_inline
amhw_zlg217_clk_int_index amhw_zlg217_rcc_clkint_flag_read (void)
{

    return (amhw_zlg217_clk_int_index)(ZLG217_RCC->cir & 0x9ful);
}

/**
 * \brief ����жϱ�־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_clkint_flag_clear (amhw_zlg217_clk_int_index index)
{

    ZLG217_RCC->cir |= ((index & 0x9ful) << 16);
}

/**
 * \brief ��λAPB2����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb2_reset (amhw_zlg217_apb2_peripheral reset)
{

    ZLG217_RCC->apb2rstr |= (1ul << reset);
}

/**
 * \brief ֹͣ��λAPB2����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb2_reset_stop (amhw_zlg217_apb2_peripheral reset)
{

    ZLG217_RCC->apb2rstr &= ~(1ul << reset);
}

/**
 * \brief ��λAPB1����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb1_reset (amhw_zlg217_apb1_peripheral reset)
{

    ZLG217_RCC->apb1rstr |= (1ul << reset);
}

/**
 * \brief ֹͣ��λAPB1����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb1_reset_stop (amhw_zlg217_apb1_peripheral reset)
{

    ZLG217_RCC->apb1rstr &= ~(1ul << reset);
}

/**
 * \brief ʹ��APB1����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb1_enable (amhw_zlg217_apb1_peripheral peri)
{

    ZLG217_RCC->apb1enr |= (1ul << peri);
}

/**
 * \brief ����APB1����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb1_disable (amhw_zlg217_apb1_peripheral peri)
{

    ZLG217_RCC->apb1enr &= ~(1ul << peri);
}

/**
 * \brief ʹ��APB2����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb2_enable (amhw_zlg217_apb2_peripheral peri)
{

    ZLG217_RCC->apb2enr |= (1ul << peri);
}

/**
 * \brief ����APB2����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_apb2_disable (amhw_zlg217_apb2_peripheral peri)
{

    ZLG217_RCC->apb2enr &= ~(1ul << peri);
}

/**
 * \brief ʹ��AHB����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
void amhw_zlg217_rcc_ahb_enable (amhw_zlg217_ahb_peripheral peri);

/**
 * \brief ����AHB����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
void amhw_zlg217_rcc_ahb_disable (amhw_zlg217_ahb_peripheral peri);

/**
 * \brief ʹ��LSI
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_lsi_enable (void)
{

    ZLG217_RCC->csr |= (1ul << 0);
}

/**
 * \brief ����LSI
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_lsi_disable (void)
{

    ZLG217_RCC->csr &= ~(1ul << 0);
}

/**
 * \brief �ڲ�����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ڲ� 40kHz ����ʱ�Ӿ���
 * \retval FALSE : �ڲ� 40kHz ����ʱ��δ����
 */
am_static_inline
am_bool_t amhw_zlg217_rcc_lsirdy_read (void)
{
    return (am_bool_t)((ZLG217_RCC->csr & (1ul << 1)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ��ȡ��λ��־
 *
 * \return ��λ��־
 */
am_static_inline
amhw_zlg217_reset_flag_t amhw_zlg217_rcc_reset_flag (void)
{

    return (amhw_zlg217_reset_flag_t)(ZLG217_RCC->csr & 0xfc000000);
}

/**
 * \brief �����λ��־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_reset_flag_clear (void)
{

    ZLG217_RCC->csr |= (1ul << 24);
}
/**
 * \brief �ⲿ��������ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_bdcr_lseon_enable (void)
{

    ZLG217_RCC->bdcr |= (1ul << 0);
}
/**
 * \brief �ⲿ������������
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_bdcr_lseon_disable (void)
{
    ZLG217_RCC->bdcr &= ~(1ul << 0);
}
/**
 * \brief �ⲿ��������������־��ȡ
 *
 * \retval TRUE  : �ڲ� 32MHzʱ��û�о���
 * \retval FALSE : �ڲ� 32MHzʱ�Ӿ���
 */
am_static_inline
am_bool_t amhw_zlg217_rcc_bdcr_lserdy_read (void)
{
    return (am_bool_t)((ZLG217_RCC->bdcr & 0x2ul) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ����·״̬
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_bdcr_lsebyp_set (uint32_t lsebyp)
{
    ZLG217_RCC->bdcr |= (lsebyp << 2);
}
/**
 * \brief �ⲿ����ʱ����·״̬
 *
 * \retval TRUE  : LSE ʱ�ӱ���·
 * \retval FALSE : LSE ʱ��δ����·
 */
am_static_inline
am_bool_t amhw_zlg217_rcc_bdcr_lsebyp_get (void)
{
    return (am_bool_t)((ZLG217_RCC->bdcr & 0x4ul) ? AM_TRUE : AM_FALSE);
}
/**
 * \brief RTC����ʱ��ѡ��
 *
 * \param[in]  src ��RTC����ʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_bdcr_rtc_clk_set (amhw_zlg217_rtc_clk_src src)
{

    ZLG217_RCC->bdcr = ((src & 0x3ul) << 8) |
                              (ZLG217_RCC->bdcr & ~(0x3ul << 8));
}

/**
 * \brief RTC����ʱ�ӻ�ȡ
 *
 * \retval  rtcʱ��Դ��ȡ
 */
am_static_inline
amhw_zlg217_rtc_clk_src amhw_zlg217_rcc_bdcr_rtc_clk_get (void)
{
    return (amhw_zlg217_rtc_clk_src)((ZLG217_RCC->bdcr >> 8) & 0x3ul);
}

/**
 * \brief RTCʱ��ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_bdcr_rtc_enable (void)
{

    ZLG217_RCC->bdcr |= (1ul << 15);
}
/**
 * \brief RTCʱ�ӽ���
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_bdcr_rtc_disable (void)
{

    ZLG217_RCC->bdcr &= ~(1ul << 15);
}

/**
 * \brief �����������λ
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_bdcr_bdrst_reset (void)
{

    ZLG217_RCC->bdcr |= (1ul << 16);
}
/**
 * \brief �����������λ����
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_bdcr_bdrst_reset_end (void)
{

    ZLG217_RCC->bdcr &= ~(1ul << 16);
}
/**
 * \brief ϵͳ���üĴ���flash����
 *
 * \param[in] flag flashҳ����ʱ�����Ĵ�С 1��1K�ֽ� 0��512�ֽ�
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_syscfg_erasure (uint32_t flag)
{

    ZLG217_RCC->syscfg &= (flag << 0);
}
/**
 * \brief ϵͳ���üĴ���flash���
 *
 * \param[in] flag flashҳ����ʱ�Ƿ��� 1����� 0�������
 * \return ��
 */
am_static_inline
void amhw_zlg217_rcc_syscfg_checkout (uint32_t flag)
{

    ZLG217_RCC->syscfg &= (flag << 1);
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __ZLG217_RCC_H */

#endif

/* end of file */
