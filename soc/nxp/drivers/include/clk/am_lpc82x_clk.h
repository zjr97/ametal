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
 * \brief CLK������ʱ�ӱ�׼����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-01  lnk, first implementation.
 * \endinternal
 */
 
#ifndef __AM_LPC82X_CLK_H
#define __AM_LPC82X_CLK_H

#include "ametal.h"
#include "am_clk.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_lpc82x_if_clk
 * \copydoc am_lpc82x_clk.h
 * @{
 */

/**
 * \brief CLK �豸��Ϣ�����ṹ��
 *
 *  PLLƵ�ʿ���
 *
 *  M = pll_msel + 1
 *  P = 2^(pll_psel)
 *
 *  PLLOUT = M * PLLIN;
 *  FCCO = 2 * P * PLLOUT;
 */

typedef struct am_lpc82x_clk_devinfo {

    /** \brief PLL ʱ��Դѡ��  */
    uint8_t pllin_src;

    /** 
     * \brief PLL ���ƼĴ���MSEL��ʹFCLKOUT �ڷ�Χ 100MHz��
     *        FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 5 = 60 MHz
     */
    uint8_t pll_msel;

    /** 
     * \brief PLL ���ƼĴ���PSEL ,ʹFCCO �ڷ�Χ 156 - 320MHz
     *        FCCO = FCLKOUT * 2 * 2^(PSEL) = 60MHz * 2 * 2 = 240MHz
     */
    uint8_t pll_psel;

    /** \brief MAIN ʱ��Դѡ�� */
    uint8_t main_src;
    
    /** \brief ϵͳʱ�ӷ�Ƶ�������� 1- 255 ֮����ֵ */
    uint8_t sysclk_div;

    /**
     * \brief WDTOSCƵ�ʷ�Ƶϵ�������� 2 - 64 ֮���ż��
     *       
     */
    uint8_t wdtosc_div;

    /**
     * \brief WDTOSCƵ��ѡ�񣬲μ� \ref grp_amhw_lpc82x_clk_wdtosc_rate 
     */
    uint8_t wdtosc_freq;

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    void  (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void  (*pfn_plfm_deinit)(void);

} am_lpc82x_clk_devinfo_t;

/**
 * \brief CLK �豸�ṹ��
 */
typedef struct am_lpc82x_clk_dev {

    /** \brief ָ��CLK �豸��Ϣ��ָ��   */
    const am_lpc82x_clk_devinfo_t *p_devinfo;

    /** \brief ��ʱ��ԴƵ��*/
    uint32_t main_clkrate;

    /** \brief ϵͳʱ��ԴƵ��*/
    uint32_t system_clkrate;

} am_lpc82x_clk_dev_t;

/**
 * \brief CLK ��ʼ��
 *
 * \param[in] p_dev     : ָ��CLK�豸��ָ��
 * \param[in] p_devinfo : ָ��CLK�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_lpc82x_clk_init (am_lpc82x_clk_dev_t           *p_dev,
                        const am_lpc82x_clk_devinfo_t *p_devinfo);

/**
 * \brief ����ʱ��Ƶ��
 *
 * \param[in] clk_id  ʱ�� ID (��ƽ̨����)
 * \param[in] rate    ʱ��Ƶ��
 *
 * \retval  AM_OK   �ɹ�
 * \retval -AM_ENXIO   ʱ��Ƶ��ID������
 * \retval -AM_ENOTSUP ��֧��Ҫ����Ƶ��
 */
int am_lpc82x_clk_rate_set (am_clk_id_t clk_id, uint32_t rate);


/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_CLK_H */

/* end of file */
