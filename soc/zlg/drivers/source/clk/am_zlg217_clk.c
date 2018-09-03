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
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#include "am_zlg217_clk.h"

#include "ametal.h"
#include "amhw_zlg_flash.h"
#include "zlg217_periph_map.h"
#include "amhw_zlg217_rcc.h"
#include "zlg217_clk.h"

am_zlg217_clk_dev_t *__gp_dev = NULL;

#define __HSI_CLK    48000000ul
#define __LSI_CLK    40000ul

static void __pllin_hse_init (void)
{
    amhw_zlg217_rcc_hseon_enable();

    while (amhw_zlg217_rcc_hserdy_read () == AM_FALSE);

//    amhw_zlg217_rcc_hseforpll_set (0);

    __gp_dev->pllin_clk = __gp_dev->p_devinfo->hse_osc;
}

static void __pllin_hsi_init (void)
{
    amhw_zlg217_rcc_hsion_enable();

    while (amhw_zlg217_rcc_hsirdy_read() == AM_FALSE);

//  amhw_zlg217_rcc_hsiten_enable();

    __gp_dev->pllin_clk = __HSI_CLK / 4;
}

static int __apb2_peri_clk (int peri)
{
    int clk = 0;

    switch (peri) {

    case AMHW_ZLG217_RCC_APB2_TIM1:

        if (amhw_zlg217_rcc_apb2_div_get() < 4) {
            clk = __gp_dev->apb2_clk;
        } else {
            clk = __gp_dev->apb2_clk << 1;
        }
        break;

    case AMHW_ZLG217_RCC_APB2_ADC1: /* ADC�ڲ��з�Ƶ�� */

    case AMHW_ZLG217_RCC_APB2_ADC2: /* ADC�ڲ��з�Ƶ�� */
        clk = __gp_dev->apb2_clk;
        break;

    default :
        clk = __gp_dev->apb2_clk;
        break;
    }

    return clk;
}

static int __apb1_peri_clk (int peri)
{
    int clk = 0;

    switch (peri) {

    case AMHW_ZLG217_RCC_APB1_TIM2:

    case AMHW_ZLG217_RCC_APB1_TIM3:

    case AMHW_ZLG217_RCC_APB1_TIM4:
        if (amhw_zlg217_rcc_apb1_div_get() < 4) {
            clk = __gp_dev->apb1_clk;
        } else {
            clk = __gp_dev->apb1_clk << 1;
        }
        break;

    case AMHW_ZLG217_RCC_APB1_USB:
        clk = __gp_dev->usb_clk;
        break;

    default :
        clk = __gp_dev->apb1_clk;
        break;
    }

    return clk;
}

static int __other_clk (am_clk_id_t clk_id)
{
    int clk = 0;

    switch (clk_id) {

    case CLK_PLLIN:
        clk = __gp_dev->pllin_clk;
        break;

    case CLK_PLLOUT:
        clk = __gp_dev->pllout_clk;
        break;

    case CLK_AHB:
        clk = __gp_dev->ahb_clk;
        break;

    case CLK_APB1:
        clk = __gp_dev->apb1_clk;
        break;

    case CLK_APB2:
        clk = __gp_dev->apb2_clk;
        break;

    case CLK_HSEOSC:
        clk = __gp_dev->p_devinfo->hse_osc;
        break;

    case CLK_LSEOSC:
        clk = __gp_dev->p_devinfo->lse_osc;
                break;

    case CLK_LSI:

        if (amhw_zlg217_rcc_lsirdy_read()) {
            clk = __LSI_CLK;
        } else {
            clk = 0;
        }

        break;

    case CLK_HSI:
        clk = __HSI_CLK;
        break;

    default :
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
    int clk = 0;
    int peri, num;
    amhw_zlg217_sys_clk_src sys_clk_src;
    amhw_zlg217_rtc_clk_src rtc_clk_src;

    num  = (clk_id & 0xff00) >> 8;
    peri = clk_id & 0xff;

    switch (num) {

    case 1:
        clk = __apb1_peri_clk(peri);
        break;

    case 2:
        clk = __apb2_peri_clk(peri);
        break;

    case 3:
        clk = __gp_dev->ahb_clk;
        break;

    case 4:
        clk = __other_clk(clk_id);
        break;

    case 5:
        switch (peri) {
        case 0:
            sys_clk_src = amhw_zlg217_rcc_sys_clk_get();

            switch (sys_clk_src) {
            case AMHW_ZLG217_SYSCLK_HSI_DIV6:
                clk = am_clk_rate_get(CLK_HSI) / 6;
                break;

            case AMHW_ZLG217_SYSCLK_HSE:
                clk = am_clk_rate_get(CLK_HSEOSC);
                break;

            case AMHW_ZLG217_SYSCLK_PLL:
               clk = am_clk_rate_get(CLK_PLLOUT);
                break;

            case AMHW_ZLG217_SYSCLK_LSI:
               clk = am_clk_rate_get(CLK_LSI);
                break;
            }
            break;

        case 1:
           rtc_clk_src = amhw_zlg217_rcc_bdcr_rtc_clk_get();
           switch (rtc_clk_src) {
           case AMHW_ZLG217_RTCCLK_LSE:
               clk = am_clk_rate_get(CLK_LSEOSC);
               break;
           case AMHW_ZLG217_RTCCLK_LSI:
               clk = am_clk_rate_get(CLK_LSI);
               break;
           case AMHW_ZLG217_RTCCLK_HSE_DIV128:
               clk = am_clk_rate_get(CLK_HSEOSC) / 128;
               break;
           }
        }

        break;

    default :
        break;
    }
    return clk;
}

/**
 * \brief ʹ��ָ����ϵͳ������ʱ��
 */
int am_clk_enable (am_clk_id_t clk_id)
{
    int peri, num;

    num  = (clk_id & 0xff00) >> 8;
    peri = clk_id & 0xff;

    switch (num) {

    case 1:
        amhw_zlg217_rcc_apb1_enable((amhw_zlg217_apb1_peripheral)peri);
        break;

    case 2:
        amhw_zlg217_rcc_apb2_enable((amhw_zlg217_apb2_peripheral)peri);
        break;

    case 3:
        amhw_zlg217_rcc_ahb_enable((amhw_zlg217_ahb_peripheral)peri);
        break;

    default :
        break;
    }

    return AM_OK;
}

/**
 * \brief ����ָ����ϵͳ������ʱ��
 */
int am_clk_disable (am_clk_id_t clk_id)
{
    int peri, num;

    num  = (clk_id & 0xff00) >> 8;
    peri = clk_id & 0xff;

    switch (num) {

    case 1:
        amhw_zlg217_rcc_apb1_disable((amhw_zlg217_apb1_peripheral)peri);
        break;

    case 2:
        amhw_zlg217_rcc_apb2_disable((amhw_zlg217_apb2_peripheral)peri);
        break;

    case 3:
        amhw_zlg217_rcc_ahb_disable((amhw_zlg217_ahb_peripheral)peri);
        break;

    default :
            break;
    }

    return AM_OK;
}

int am_zlg217_clk_reset (am_clk_id_t clk_id)
{
    int peri, num;

    num  = (clk_id & 0xff00) >> 8;
    peri = clk_id & 0xff;

    switch (num) {

    case 1:
        amhw_zlg217_rcc_apb1_reset((amhw_zlg217_apb1_peripheral)peri);
        amhw_zlg217_rcc_apb1_reset_stop((amhw_zlg217_apb1_peripheral)peri);
        break;

    case 2:
        amhw_zlg217_rcc_apb2_reset((amhw_zlg217_apb2_peripheral)peri);
        amhw_zlg217_rcc_apb2_reset_stop((amhw_zlg217_apb2_peripheral)peri);
        break;

    default :
            break;
    }

    return AM_OK;
}

int am_zlg217_clk_update (am_clk_id_t clk_id, int clk)
{
    switch (clk_id) {

    case CLK_AHB:
        __gp_dev->ahb_clk = clk;
        break;

    case CLK_APB1:
        __gp_dev->apb1_clk = clk;
        break;

    case CLK_APB2:
        __gp_dev->apb2_clk = clk;
        break;

    default:
        break;
    }

    return AM_OK;
}

const am_zlg217_clk_dev_t *am_zlg217_clk_devinfo_get (void)
{
    if (__gp_dev == NULL)  {
        return NULL;
    }

    return __gp_dev;
}

int am_zlg217_div_get (am_clk_id_t clk_id)
{
    int div = 0;

    if (__gp_dev == NULL)  {
        return -AM_EINVAL;
    }

    switch (clk_id) {

    case CLK_AHB:
        div =  __gp_dev->p_devinfo->ahb_div;
        break;

    case CLK_APB1:
        div =  __gp_dev->p_devinfo->apb1_div;
        break;

    case CLK_APB2:
        div =  __gp_dev->p_devinfo->apb2_div;
        break;

    case CLK_USB:
        div =  __gp_dev->p_devinfo->usb_div;
        break;

    default:
        break;
    }

    return div;
}

/**
 * \brief CLK ��ʼ��
 */
int am_zlg217_clk_init (am_zlg217_clk_dev_t           *p_dev,
                        const am_zlg217_clk_devinfo_t *p_devinfo)

{
    uint8_t i = 0,div = 1;

    if (p_dev == NULL || p_devinfo == NULL) {
        return -AM_EINVAL;
    }

    p_dev->p_devinfo  = p_devinfo;
    __gp_dev          = p_dev;

    ZLG217_RCC->apb2enr |= 0xc;

    if (p_devinfo->pllin_src == AMHW_ZLG217_PLLCLK_HSE) {

        /* CLKƽ̨��ʼ��������ʱ������ */
        if (p_devinfo->pfn_plfm_init) {
            p_devinfo->pfn_plfm_init();
        }
        __pllin_hse_init();
    } else {
        __pllin_hsi_init();
    }

    p_dev->pllout_clk = p_dev->pllin_clk   *
                        p_devinfo->pll_mul /
                        p_devinfo->pll_div;

    /* ����AHBʱ��Ƶ�� */
    if (p_devinfo->ahb_div < 12) {
        for (i = 0; i < p_devinfo->ahb_div - 7; i++) {
            div = div << 1;
        }
    } else {
        div = 64;
        for (i = 0; i < (p_devinfo->ahb_div & 0xf) - 12; i++) {
            div = div << 1;
        }
    }
    p_dev->ahb_clk = p_dev->pllout_clk / div;
    p_dev->usb_clk = p_dev->pllout_clk / (p_dev->p_devinfo->usb_div + 1);

    /* ����APB1ʱ��Ƶ�� */
    div = 1;
    for (i = 0; i < (p_devinfo->apb1_div & 0x7); i++) {
        div = div << 1;
    }
    p_dev->apb1_clk = p_dev->ahb_clk / div;

    /* ����APB2ʱ��Ƶ�� */
    div = 1;
    for (i = 0; i < (p_devinfo->apb2_div & 0x7); i++) {
        div = div << 1;
    }
    p_dev->apb2_clk = p_dev->ahb_clk / div;

    ZLG217_FLASH->acr |= 0x38;

    amhw_zlg_flash_latency_set(ZLG217_FLASH,
                                ((p_dev->pllout_clk - 1) / 24000000));

    amhw_zlg217_rcc_ahb_div_set(p_devinfo->ahb_div);

    amhw_zlg217_rcc_apb2_div_set(p_devinfo->apb2_div + 3);

    amhw_zlg217_rcc_apb1_div_set(p_devinfo->apb1_div + 3);

    amhw_zlg217_rcc_plldm_set(p_devinfo->pll_div - 1);
    amhw_zlg217_rcc_plldn_set(p_devinfo->pll_mul - 1);

    amhw_zlg217_rcc_pll_clk_set(p_devinfo->pllin_src);

    amhw_zlg217_rcc_pll_enable();

    while (amhw_zlg217_rcc_pllrdy_read() == AM_FALSE); /* �ȴ�pll���� */

    amhw_zlg217_rcc_sys_clk_set(AMHW_ZLG217_SYSCLK_PLL);

    amhw_zlg217_rcc_pllforusb_set(p_devinfo->usb_div);

    ZLG217_RCC->apb2enr &= ~0xc;

    return AM_OK;
}

/* end of file */
