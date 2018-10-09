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
 * \brief kl26 UART0 �û������ļ�
 * \sa am_kl26_hwconfig_uart0.c
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-15  nwt, make some changes.
 * - 1.00 15-10-21  xym, first implementation.
 * \endinternal
 */

#include "kl26_periph_map.h"
#include "kl26_pin.h"
#include "am_gpio.h"
#include "am_fsl_uart.h"
#include "hw/amhw_fsl_uart.h"
#include "hw/amhw_kl26_sim.h"
#include "kl26_inum.h"
#include "kl26_clk.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_uart0
 * \copydoc am_kl26_hwconfig_uart0.c
 * @{
 */

/**< \brief ����RS485�������Ʒ�������ţ�ʹ��485������ƺ�������Ч�� */
#define AM_KL26_UART0_485_DIR_PIN   PIOB_18

/**< \brief �������� */
static const am_fsl_uart_devinfo_t __g_uart0_devinfo;

/** \brief uart0 485 ����/���շ������ */
static void __uart0_int_485_send_cfg (am_bool_t flag)
{
    if (flag) {
        am_gpio_set(AM_KL26_UART0_485_DIR_PIN, 1);
    } else {
        am_gpio_set(AM_KL26_UART0_485_DIR_PIN, 0);
    }
}

/** \brief ����0ƽ̨��ʼ�� */
static void __kl26_plfm_uart0_init (void)
{
    /* ���ų�ʼ��      PIOA_1_UART0_RX  PIOA_2_UART0_TX   */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_UART0_RX);
    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART0_TX);

    /* UART0ʱ��Դѡ��                  */
    amhw_kl26_sim_uart0_src_set(  KL26_SIM_UART0SRC_PLLFLLCLK );
    /* ����UART0ʱ��                  */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART0);
    
    if (__g_uart0_devinfo.uart_int_485_send != NULL) {
        /* 485 ����/���շ���������� */
        am_gpio_pin_cfg(AM_KL26_UART0_485_DIR_PIN, AM_GPIO_OUTPUT_INIT_LOW | AM_GPIO_PULLDOWN);
        __uart0_int_485_send_cfg(AM_FALSE);
    }
}

/** \brief �������0ƽ̨��ʼ�� */
static void __kl26_plfm_uart0_deinit (void)
{
    /* �ر�UART0ʱ��                  */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_UART0);

    am_gpio_pin_cfg(PIOA_1, PIOA_1_GPIO);
    am_gpio_pin_cfg(PIOA_2, PIOA_2_GPIO);
}

/** \brief ����0�豸��Ϣ */
static const am_fsl_uart_devinfo_t __g_uart0_devinfo = {

    KL26_UART0,                 /**< \brief ����0           */
    INUM_UART0,                      /**< \brief ����0���жϱ��.    */
	AM_FSL_UART_VER0,                /**< \brief ���������İ汾��.   */
	CLK_UART0,                       /**< \brief ����0��ʱ�Ӻ�.     */
    AMHW_FSL_UART_C1_M_8BIT      |   /**< \brief 8λ����.          */
    AMHW_FSL_UART_C1_PARITY_NO   |   /**< \brief �޼���.           */
    AMHW_FSL_UART_BDH_SBNS_STOP_1,   /**< \brief 1��ֹͣλ.         */

    115200,                          /**< \brief ���õĲ�����.       */

    0,                               /**< \brief �������ж�.         */

    NULL,                            /**< \brief USART0��ʹ��RS485   */
    __kl26_plfm_uart0_init,          /**< \brief USART0��ƽ̨��ʼ��.  */
    __kl26_plfm_uart0_deinit,        /**< \brief USART0��ƽ̨ȥ��ʼ��. */

};

static am_fsl_uart_dev_t  __g_uart0_dev;   /**< \brief ���崮��0 �豸.*/

/** \brief UART0ʵ����ʼ�������uart0��׼������ */
am_uart_handle_t am_kl26_uart0_inst_init (void)
{
    return am_fsl_uart_init(&__g_uart0_dev, &__g_uart0_devinfo);
}

/** \brief UART0ʵ�����ʼ�� */
void am_kl26_uart0_inst_deinit (am_uart_handle_t handle)
{
    am_fsl_uart_deinit((am_fsl_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */



