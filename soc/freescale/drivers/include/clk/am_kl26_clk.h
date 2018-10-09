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
 * \brief CLK������ʱ�ӱ�׼����ӿ�ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  ari, first implementation.
 * \endinternal
 */
 
#ifndef __AM_KL26_CLK_H
#define __AM_KL26_CLK_H

#include "ametal.h"
#include "am_clk.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_kl26_if_clk
 * \copydoc am_kl26_clk.h
 * @{
 */


/**
  * \brief ʱ�ӹ���ģʽ
  */
typedef enum am_kl26_clk_mode {
    AM_KL26_CLK_MODE_FEI   = 0,   /**< \brief FEI  */
    AM_KL26_CLK_MODE_FBI   = 1,   /**< \brief FBI  */
    AM_KL26_CLK_MODE_BLPI  = 2,   /**< \brief BLPI */
    AM_KL26_CLK_MODE_FEE   = 3,   /**< \brief FEE  */
    AM_KL26_CLK_MODE_FBE   = 4,   /**< \brief FBE  */
    AM_KL26_CLK_MODE_BLPE  = 5,   /**< \brief BLPE */
    AM_KL26_CLK_MODE_PBE   = 6,   /**< \brief PBE  */
    AM_KL26_CLK_MODE_PEE   = 7,   /**< \brief PEE  */
    AM_KL26_CLK_MODE_STOP  = 8,   /**< \brief STOP  */
    AM_KL26_CLK_MODE_ERROR = 9    /**< \brief ERROR  */
} am_kl26_clk_mode_t;

/**
 * \brief CLK �豸��Ϣ�����ṹ��
 */

typedef struct am_kl26_clk_devinfo {
    /** \brief ʱ�ӹ���ģʽ */
    am_kl26_clk_mode_t clk_mode;

    /** \brief �ⲿ����Ƶ�� */
    uint32_t xtal_rate;

    /* �ں�ʱ��core_clk��Ƶϵ��(1-16),
     * core_clk = MCGOUTCLK / outdiv1 ,core_clk upto 48MHz
     */
    uint8_t core_clk_div;

    /** \brief ƽ̨��ʼ���������������ŵȹ��� */
    void  (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void  (*pfn_plfm_deinit)(void);

} am_kl26_clk_devinfo_t;

/**
 * \brief CLK �豸�ṹ��
 */
typedef struct am_kl26_clk_dev {

    /** \brief ָ��CLK �豸��Ϣ��ָ��   */
    const am_kl26_clk_devinfo_t *p_devinfo;

    /* PLL��Ƶϵ���� ʹ��PLL ����Ƶ����2-4MHz ��*/
    uint8_t pll_div;

    /* PLL��Ƶϵ����MCGPLLCLK = 2MHz * (24 + pll_div), MCGPLLCLK upto 100MHz*/
    uint8_t pll_mul;

    /* FLL��Ƶϵ����ʹ��FLL ����Ƶ����32.768K ���� */
    uint8_t fll_div;

    /* FLL��ƵƵ�ʣ�MCGFLLCLK = 24MHz��48MHz��72MHz��96MHz */
    uint32_t fll_rate;

    /* �ں�ʱ��core_clk��Ƶϵ��(1-16),
    * core_clk = MCGOUTCLK / outdiv1 ,core_clk upto 48MHz
    */
    uint8_t outdiv1;
    /* ����ʱ��bus_clk��Ƶϵ��(2-8)��
    * bus_clk = core_clk / outdiv4, bus_clk upto 24MHz
    */
    uint8_t outdiv4;
} am_kl26_clk_dev_t;

/**
 * \brief CLK ��ʼ��
 *
 * \param[in] p_dev     : ָ��CLK�豸��ָ��
 * \param[in] p_devinfo : ָ��CLK�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_kl26_clk_init (am_kl26_clk_dev_t           *p_dev,
                      const am_kl26_clk_devinfo_t *p_devinfo);

/**
 * \brief �õ�core/platform/systemʱ��Ƶ��
 * \return core/platform/systemʱ��Ƶ��
 */
uint32_t am_kl26_clk_core_clkrate_get(void);

/**
 * \brief �õ�bus/flashʱ��Ƶ��
 * \return bus/flashʱ��Ƶ��
 */
uint32_t am_kl26_clk_bus_clkrate_get(void);

/**
 * \brief �õ����������Ƶ��
 *
 * \param[in] p_periph : ָ������ļĴ�����
 *
 * \return ���������Ƶ��
 */
uint32_t am_kl26_clk_periph_rate_get(void *p_periph);

/**
 * \brief ��ȡʱ�ӹ���ģʽ
 */
am_kl26_clk_mode_t am_kl26_clk_mode_get (void);

/**
 * \brief ����ʱ�ӹ���ģʽPEE��BLPEģʽ���͹���ģʽ��
 * \return ��
 * \note BLPEģʽ��CORE_CLK = 4MHZ
 *                 BUS_CLK = 1MHZ
 */
int am_kl26_clk_mode_pee2blpe (void);

/**
 * \brief ����ʱ�ӹ���ģʽBLPE��PEEģʽ
 * \return ��
 * \note PEEģʽ,CORE_CLK = 48MHZ
 *               BUS_CLK = 24MHZ
 */
int am_kl26_clk_mode_blpe2pee (void);

/**
 * \brief ����ʱ�ӹ���ģʽPBE��PEEģʽ
 * \return ��
 * \note PEEģʽ,CORE_CLK = 48MHZ
 *               BUS_CLK = 24MHZ
 */
int am_kl26_clk_mode_pbe2pee(void);

/**
 * \brief ����ʱ�ӹ���ģʽFEI��BLPIģʽ���͹���ģʽ��
 * \return ��
 * \note BLPIģʽ,
 *       Core clock = 4MHz
 *       Bus clock  = 1MHz
 */
int am_kl26_clk_mode_fei2blpi (void);

/**
 * \brief ����ʱ�ӹ���ģʽBLPI��FEIģʽ
 * \return ��
 * \note FBIģʽ
 *       Core clock = 20.97152MHz
 *       Bus clock  = 20.97152MHz
 */
int am_kl26_clk_mode_blpi2fei (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_KL26_CLK_H */

/* end of file */
