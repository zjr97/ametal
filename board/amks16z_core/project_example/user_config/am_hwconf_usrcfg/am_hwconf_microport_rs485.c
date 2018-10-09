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
 * \brief MicroPort RS485 �û������ļ�
 * \sa am_hwconf_microport_rs485.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-16  pea, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"

#include "am_gpio.h"
#include "am_fsl_uart.h"
#include "hw/amhw_fsl_uart.h"
#include "hw/amhw_kl26_sim.h"

#include "../../../../../soc/freescale/kl26/am_kl26.h"
#include "../../../../../soc/freescale/kl26/kl26_clk.h"
#include "../../../../../soc/freescale/kl26/kl26_inum.h"
#include "../../../../../soc/freescale/kl26/kl26_periph_map.h"
#include "../../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \addtogroup am_if_src_hwconf_microport_rs485
 * \copydoc am_hwconf_microport_rs485.c
 * @{
 */

/** \brief RS485����������� */
#define __MICROPORT_RS485_DIR_PIN    PIOA_12

/**
 * \brief RS485 ������ƺ���
 *
 * \param[in] is_txmode AM_TRUE: ����ģʽ�� AM_FALSE: ����ģʽ
 */
void __microport_rs485_dir (am_bool_t is_txmode)
{
	am_gpio_set(__MICROPORT_RS485_DIR_PIN, (int)is_txmode);
}

/** \brief MicroPort RS485ƽ̨��ʼ�� */
am_local void __microport_rs485_plfm_init (void)
{
    /* ���ų�ʼ��      PIOA_1_UART0_RX  PIOA_2_UART0_TX   */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_UART0_RX);
    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART0_TX);

    /* UART0ʱ��Դѡ��                  */
    amhw_kl26_sim_uart0_src_set(  KL26_SIM_UART0SRC_PLLFLLCLK );
    /* ����UART0ʱ��                  */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART0);

    /* 485 ����/���շ���������� */
    am_gpio_pin_cfg(__MICROPORT_RS485_DIR_PIN, AM_GPIO_OUTPUT_INIT_LOW | AM_GPIO_PULLDOWN);
    __microport_rs485_dir(AM_FALSE);
}

/** \brief ��� MicroPort RS485 ƽ̨��ʼ�� */
am_local void __microport_rs485_plfm_deinit (void)
{
    /* �ر�UART0ʱ��                  */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_UART0);

    am_gpio_pin_cfg(PIOA_1, PIOA_1_GPIO);
    am_gpio_pin_cfg(PIOA_2, PIOA_2_GPIO);
}

/** \brief ����0�豸��Ϣ */
static const am_fsl_uart_devinfo_t __g_microport_rs485_devinfo = {

    KL26_UART0,                      /**< \brief ����0           */
    INUM_UART0,                      /**< \brief ����0���жϱ��.    */
	AM_FSL_UART_VER0,                /**< \brief ���������İ汾��.     */
	CLK_UART0,                       /**< \brief ����0��ʱ�Ӻ�.     */
    AMHW_FSL_UART_C1_M_8BIT      |   /**< \brief 8λ����.          */
    AMHW_FSL_UART_C1_PARITY_NO   |   /**< \brief �޼���.           */
    AMHW_FSL_UART_BDH_SBNS_STOP_1,   /**< \brief 1��ֹͣλ.         */

    115200,                          /**< \brief ���õĲ�����.       */

    0,                               /**< \brief �������ж�.         */

	__microport_rs485_dir,           /**< \brief USART0ʹ��RS485   */
	__microport_rs485_plfm_init,     /**< \brief USART0��ƽ̨��ʼ��.  */
	__microport_rs485_plfm_deinit,   /**< \brief USART0��ƽ̨ȥ��ʼ��. */
};

/** \brief ����MicroPort RS485 �豸 */
static am_fsl_uart_dev_t  __g_microport_rs485_dev;   /**< \brief ���崮��0 �豸.*/

/** \brief MicroPort RS485 ʵ����ʼ������� USART0 ��׼������ */
am_uart_handle_t am_microport_rs485_inst_init (void)
{
	return am_fsl_uart_init(&__g_microport_rs485_dev, &__g_microport_rs485_devinfo);
}

/** \brief MicroPort RS485 ʵ�����ʼ�� */
void am_microport_rs485_inst_deinit (am_uart_handle_t handle)
{
	am_fsl_uart_deinit((am_fsl_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
