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
 * \brief ZLG DAC �û������ļ�
 * \sa am_hwconf_zlg217_dac.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "am_zlg217.h"
#include "am_zlg_dac.h"
#include "am_gpio.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_dac
 * \copydoc am_hwconf_zlg217_dac.c
 * @{
 */

/**
 * \brief DAC1 ƽ̨��ʼ��
 */
void __zlg217_plfm_dac1_init (void)
{

    /* ����PIOA_4ΪDAC1_OUT���� */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_DAC1_OUT);

    /* ����DACʱ�� */
    am_clk_enable(CLK_DAC);
}

/**
 * \brief DAC2 ƽ̨ȥ��ʼ��
 */
void __zlg217_plfm_dac1_deinit (void)
{
    /* �ر�DACʱ�� */
    am_clk_disable(CLK_DAC);
}

/** \brief DAC1 �豸��Ϣ */
static const am_zlg_dac_devinfo_t __g_dac1_devinfo =
{
    ZLG217_DAC_BASE,                  /**< \brief ָ��DAC�Ĵ������ָ�� */
    12,                               /**< \brief DACת������ */
    3270,                             /**< \brief DAC�ο���ѹ����λ��mV */
    __zlg217_plfm_dac1_init,
    __zlg217_plfm_dac1_deinit,
};

/** \brief DAC1�豸ʵ�� */
static am_zlg_dac_dev_t __g_dac1_dev;

/** \brief DAC1 ʵ����ʼ�������DAC��׼������ */
am_dac_handle_t am_zlg217_dac1_inst_init (void)
{
    return am_zlg_dac_init(&__g_dac1_dev, &__g_dac1_devinfo);
}

/** \brief DAC1 ʵ�����ʼ�� */
void am_zlg217_dac1_inst_deinit (am_dac_handle_t handle)
{
    am_zlg_dac_deinit(handle);
}

/**
 * \brief DAC2 ƽ̨��ʼ��
 */
void __zlg217_plfm_dac2_init (void)
{
    /* ����PIOA_5ΪDAC2_OUT���� */
    am_gpio_pin_cfg (PIOA_5,PIOA_5_DAC2_OUT);

    /* ����DACʱ�� */
    am_clk_enable(CLK_DAC);
}

/**
 * \brief DAC2 ƽ̨ȥ��ʼ��
 */
void __zlg217_plfm_dac2_deinit (void)
{
    /* �ر�DACʱ�� */
    am_clk_disable(CLK_DAC);
}

/** \brief DAC2 �豸��Ϣ */
static const am_zlg_dac_devinfo_t __g_dac2_devinfo =
{
    ZLG217_DAC_BASE,                  /**< \brief ָ��DAC�Ĵ������ָ�� */
    12,                               /**< \brief DACת������ */
    3270,                             /**< \brief DAC�ο���ѹ����λ��mV */
    __zlg217_plfm_dac2_init,
    __zlg217_plfm_dac2_deinit,
};

/** \brief DAC2�豸ʵ�� */
static am_zlg_dac_dev_t __g_dac2_dev;

/** \brief DAC2 ʵ����ʼ�������DAC��׼������ */
am_dac_handle_t am_zlg217_dac2_inst_init (void)
{
    return am_zlg_dac_init(&__g_dac2_dev, &__g_dac2_devinfo);
}

/** \brief DAC2 ʵ�����ʼ�� */
void am_zlg217_dac2_inst_deinit (am_dac_handle_t handle)
{
    am_zlg_dac_deinit(handle);
}

/**
 * @}
 */

/* end of file */
