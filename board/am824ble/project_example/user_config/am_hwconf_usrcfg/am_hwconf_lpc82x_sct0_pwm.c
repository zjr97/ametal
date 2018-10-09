/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC82X SCT0 PWM �û������ļ�
 * \sa am_hwconf_lpc82x_sct0_pwm.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-19  hgo, add annotations.
 * - 1.00 15-07-25  oce, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc_sct_pwm.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_sct0_pwm
 * \copydoc am_hwconf_lpc82x_sct0_pwm.c
 * @{
 */

/** \brief SCT0 ���� PWM ������������Ϣ�б�PWM ���������Ϊ 6 �� */
am_local am_lpc_sct_pwm_ioinfo_t __g_sct0_pwm_ioinfo_list[] = {
    {PIO0_23, PIO_FUNC_SCT_OUT0, PIO0_23_GPIO | PIO0_23_GPIO_INPUT}, /* ͨ�� 0 */
    {PIO0_2, PIO_FUNC_SCT_OUT1, PIO0_2_GPIO | PIO0_2_GPIO_INPUT},    /* ͨ�� 1 */
    {PIO0_25, PIO_FUNC_SCT_OUT2, PIO0_25_GPIO | PIO0_25_GPIO_INPUT}, /* ͨ�� 2 */
    {PIO0_26, PIO_FUNC_SCT_OUT3, PIO0_26_GPIO | PIO0_26_GPIO_INPUT}, /* ͨ�� 3 */
    {PIO0_27, PIO_FUNC_SCT_OUT4, PIO0_27_GPIO | PIO0_27_GPIO_INPUT}, /* ͨ�� 4 */
    {PIO0_15, PIO_FUNC_SCT_OUT5, PIO0_15_GPIO | PIO0_15_GPIO_INPUT}, /* ͨ�� 5 */
};

/**
 * \brief SCT0 PWM ƽ̨��ʼ��
 */
am_local void __lpc82x_sct0_pwm_plfm_init ()
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SCT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);
}

/**
 * \brief SCT0 ƽ̨���ʼ��
 */
am_local void __lpc82x_sct0_pwm_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SCT);
}

/** \brief SCT0 PWM �豸��Ϣ */
am_local am_const am_lpc_sct_pwm_devinfo_t __g_lpc82x_pwm_devinfo = {
    LPC82X_SCT0_BASE,                 /* SCT0 �Ĵ��������ַ */
    CLK_SCT,                          /* SCT0 ʱ�Ӻ� */
    6,                                /* 6 �� PWM ���ͨ�� */
    &__g_sct0_pwm_ioinfo_list[0],     /* ���� PWM ����������Ϣ�����׵�ַ�������� */
    __lpc82x_sct0_pwm_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc82x_sct0_pwm_plfm_deinit,    /* ƽ̨���ʼ������ */
};

/** \brief SCT0 PWM �豸ʵ�� */
am_local am_lpc_sct_pwm_dev_t __g_lpc82x_pwm_dev;

/**
 * \brief SCT0 PWM ʵ����ʼ��
 */
am_pwm_handle_t am_lpc82x_sct0_pwm_inst_init (void)
{
    return am_lpc_sct_pwm_init(&__g_lpc82x_pwm_dev, &__g_lpc82x_pwm_devinfo);
}

/**
 * \brief SCT0 PWM ʵ�����ʼ��
 */
void am_lpc82x_sct0_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_lpc_sct_pwm_deinit((am_lpc_sct_pwm_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
