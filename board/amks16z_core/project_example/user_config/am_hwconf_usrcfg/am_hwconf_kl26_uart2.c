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
 * \brief kl26 UART2 �û������ļ�
 * \sa am_kl26_hwconfig_uart2.c
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-15  nwt, make some changes.
 * - 1.00 15-10-21  xym, first implementation.
 * \endinternal
 */

#include "am_gpio.h"
#include "am_fsl_uart.h"
#include "hw/amhw_fsl_uart.h"
#include "hw/amhw_kl26_sim.h"

#include "../../../../../soc/freescale/kl26/kl26_clk.h"
#include "../../../../../soc/freescale/kl26/kl26_inum.h"
#include "../../../../../soc/freescale/kl26/kl26_periph_map.h"
#include "../../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_uart2
 * \copydoc am_kl26_hwconfig_uart2.c
 * @{
 */

/** \brief ����2ƽ̨��ʼ�� */
static void __kl26_plfm_uart2_init (void)
{
    /* ���ų�ʼ��      PIOD_4_UART2_RX  PIOD_5_UART2_TX     */
     am_gpio_pin_cfg(PIOD_4, PIOD_4_UART2_RX);
     am_gpio_pin_cfg(PIOD_5, PIOD_5_UART2_TX);

     /* ����UART2ʱ��                  */
     amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART2);
}

/** \brief �������2 ƽ̨��ʼ�� */
static void __kl26_plfm_uart2_deinit (void)
{
    /* �ر�UART2ʱ��                  */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_UART2);

    am_gpio_pin_cfg(PIOD_4, PIOD_4_GPIO);
    am_gpio_pin_cfg(PIOD_5, PIOD_5_GPIO);
}

/** \brief ����2 �豸��Ϣ */
static const am_fsl_uart_devinfo_t __g_uart2_devinfo = {

    KL26_UART2,                      /**< \brief ����2           */
    INUM_UART2,                      /**< \brief ����2���жϱ��.    */
	AM_FSL_UART_VER1,                /**< \brief ���������İ汾��.     */
	CLK_UART2,                       /**< \brief ����2��ʱ�Ӻ�.     */
    AMHW_FSL_UART_C1_M_8BIT      |  /**< \brief 8λ����.          */
    AMHW_FSL_UART_C1_PARITY_NO   |  /**< \brief �޼���.           */
    AMHW_FSL_UART_BDH_SBNS_STOP_1,  /**< \brief 1��ֹͣλ .        */


    115200,                          /**< \brief ���õĲ�����.       */

    0,                               /**< \brief �������ж�.         */
    
    NULL,        /**< \brief USART2��ʹ��RS485   */
    __kl26_plfm_uart2_init,          /**< \brief USART2��ƽ̨��ʼ��.  */
    __kl26_plfm_uart2_deinit,        /**< \brief USART2��ƽ̨ȥ��ʼ��. */
};

static am_fsl_uart_dev_t  __g_uart2_dev;   /**< \brief ���崮��2�豸. */

/** \brief UART2ʵ����ʼ�������uart2��׼������ */
am_uart_handle_t am_kl26_uart2_inst_init (void)
{
    return am_fsl_uart_init(&__g_uart2_dev, &__g_uart2_devinfo);
}

/** \brief UART2ʵ�����ʼ�� */
void am_kl26_uart2_inst_deinit (am_uart_handle_t handle)
{
    am_fsl_uart_deinit((am_fsl_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */



