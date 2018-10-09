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
 * \brief KL26 RTC �û������ļ�
 * \sa am_kl26_hwconfig_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-19  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "am_fsl_rtc.h"
#include "../../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_rtc
 * \copydoc am_kl26_hwconfig_rtc.c
 * @{
 */

/**
 *  \brief RTC ƽ̨��ʼ��
 *  \return ��
 */
void __kl26_plfm_rtc_init(void)
{
    /** RTC ʱ��Դѡ��Ϊ�ⲿRTCʱ��Դ */
    amhw_kl26_sim_ercclk32k_src_set(KL26_SIM_OSC32KSEL_CLKIN);

    /** RTC ģ��ʱ��ʹ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_RTC);

    /** PORTC ʱ������ʹ�� */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_PORTC);

    /** PTC1 ����λ RTC_CLK_INPUT */
    amhw_kl26_port_pin_func_cfg(KL26_PORT, PIOC_1, 1);
}

/**
 *  \brief ��� RTC ƽ̨��ʼ��
 *  \return ��
 */
void __kl26_plfm_rtc_deinit(void)
{
    /** RTC ģ��ʱ��ʹ�� */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_RTC);
}

/** \brief RTC�豸��Ϣ */
const struct am_fsl_rtc_devinfo __g_rtc_devinfo = {
    KL26_RTC,
    __kl26_plfm_rtc_init,
    __kl26_plfm_rtc_deinit
};

/** \brief RTC�豸     */
am_fsl_rtc_dev_t __g_rtc_dev;

/** \brief rtc ʵ����ʼ�������rtc��׼������ */
am_rtc_handle_t am_kl26_rtc_inst_init (void)
{
    return am_fsl_rtc_init(&__g_rtc_dev, &__g_rtc_devinfo);
}

/**
 * \brief rtc ʵ�����ʼ��
 * \param[in] handle : rtc���ֵ
 */
void am_kl26_rtc_inst_deinit (am_rtc_handle_t handle)
{
    am_fsl_rtc_deinit(handle);
}

/**
 * @}
 */

/** end of file */

