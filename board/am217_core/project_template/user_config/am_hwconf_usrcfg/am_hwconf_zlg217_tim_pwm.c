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
 * \brief TIM����PWM��� �û������ļ�
 * \sa am_hwconf_zlg217_tim_pwm.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-28  zcb, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg217.h"
#include "am_gpio.h"
#include "am_zlg_tim_pwm.h"
#include "am_clk.h"
#include "am_zlg217_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_tim_pwm
 * \copydoc am_hwconf_zlg217_tim_pwm.c
 * @{
 */

/*******************************************************************************
  TIM1 ����
*******************************************************************************/

/** \brief TIM1����PWM��� ƽ̨��ʼ�� */
void __zlg217_plfm_tim1_pwm_init (void)
{
    am_clk_enable(CLK_TIM1);
    am_zlg217_clk_reset(CLK_TIM1);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
void __zlg217_plfm_tim1_pwm_deinit (void)
{
    am_zlg217_clk_reset(CLK_TIM1);
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1����PWM���ܵ�����������Ϣ�б� */
am_zlg_tim_pwm_ioinfo_t __g_tim1_pwm_ioinfo_list[] = {
    {PIOA_8,  PIOA_8_TIM1_CH1_REMAP0  | PIOA_8_AF_PP,  PIOA_8_GPIO  | PIOA_8_INPUT_FLOAT},   /**< \brief ͨ��1 */
    {PIOA_9,  PIOA_9_TIM1_CH2_REMAP0  | PIOA_9_AF_PP,  PIOA_9_GPIO  | PIOA_9_INPUT_FLOAT},   /**< \brief ͨ��2 */
    {PIOA_10, PIOA_10_TIM1_CH3_REMAP0 | PIOA_10_AF_PP, PIOA_10_GPIO | PIOA_10_INPUT_FLOAT},  /**< \brief ͨ��3 */
    {PIOA_11, PIOA_11_TIM1_CH4_REMAP0 | PIOA_11_AF_PP, PIOA_11_GPIO | PIOA_11_INPUT_FLOAT},  /**< \brief ͨ��4 */
};

/** \brief TIM1����PWM�豸��Ϣ */
const am_zlg_tim_pwm_devinfo_t  __g_tim1_pwm_devinfo = {
    ZLG217_TIM1_BASE,                    /**< \brief TIM1�Ĵ�����Ļ���ַ */
    CLK_TIM1,                            /**< \brief TIM1ʱ��ID */
    4,                                   /**< \brief 4��PWM���ͨ�� */
    AMHW_ZLG_TIM_PWM_MODE2,           /**< \brief PWM���ģʽ2 */
    0,                                   /**< \brief PWM����ߵ�ƽ��Ч */
    &__g_tim1_pwm_ioinfo_list[0],
    AMHW_ZLG_TIM_TYPE0,               /**< \brief ��ʱ������ */
    __zlg217_plfm_tim1_pwm_init,         /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_tim1_pwm_deinit        /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM1����PWM�豸���� */
am_zlg_tim_pwm_dev_t __g_tim1_pwm_dev;

/** \brief tim1 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_zlg217_tim1_pwm_inst_init (void)
{
    return am_zlg_tim_pwm_init(&__g_tim1_pwm_dev,
                                  &__g_tim1_pwm_devinfo);
}

/** \brief tim1 pwm ʵ�����ʼ�� */
void am_zlg217_tim1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_zlg_tim_pwm_deinit(handle);
}

/*******************************************************************************
  TIM2 ����
*******************************************************************************/

/** \brief TIM2����PWM��� ƽ̨��ʼ�� */
void __zlg217_plfm_tim2_pwm_init (void)
{
    am_clk_enable(CLK_TIM2);
    am_zlg217_clk_reset(CLK_TIM2);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
void __zlg217_plfm_tim2_pwm_deinit (void)
{
    am_zlg217_clk_reset(CLK_TIM2);
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2����PWM���ܵ�����������Ϣ�б� */
am_zlg_tim_pwm_ioinfo_t __g_tim2_pwm_ioinfo_list[] = {
    {PIOA_15, PIOA_15_TIM2_CH1_ETR_REMAP1 | PIOA_15_AF_PP, PIOA_15_GPIO | PIOA_15_INPUT_FLOAT},  /**< \brief ͨ��1 */
    {PIOB_3, PIOB_3_TIM2_CH2_REMAP1     | PIOB_3_AF_PP, PIOB_3_GPIO | PIOB_3_INPUT_FLOAT},  /**< \brief ͨ��2 */
    {PIOB_10, PIOB_10_TIM2_CH3_REMAP2     | PIOB_10_AF_PP, PIOB_10_GPIO | PIOB_10_INPUT_FLOAT},  /**< \brief ͨ��3 */
    {PIOB_11, PIOB_11_TIM2_CH4_REMAP2     | PIOB_11_AF_PP, PIOB_11_GPIO | PIOB_11_INPUT_FLOAT},  /**< \brief ͨ��4 */
};

/** \brief TIM2����PWM�豸��Ϣ */
const am_zlg_tim_pwm_devinfo_t  __g_tim2_pwm_devinfo = {
    ZLG217_TIM2_BASE,                    /**< \brief TIM2�Ĵ�����Ļ���ַ */
    CLK_TIM2,                            /**< \brief TIM2ʱ��ID */
    4,                                   /**< \brief 4��PWM���ͨ�� */
    AMHW_ZLG_TIM_PWM_MODE2,           /**< \brief PWM���ģʽ2 */
    0,                                   /**< \brief PWM����ߵ�ƽ��Ч */
    &__g_tim2_pwm_ioinfo_list[0],
    AMHW_ZLG_TIM_TYPE1,               /**< \brief ��ʱ������ */
    __zlg217_plfm_tim2_pwm_init,         /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_tim2_pwm_deinit        /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM2 ����PWM�豸���� */
am_zlg_tim_pwm_dev_t  __g_tim2_pwm_dev;

/** \brief tim2 pwmʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_zlg217_tim2_pwm_inst_init (void)
{
    return am_zlg_tim_pwm_init(&__g_tim2_pwm_dev,
                                  &__g_tim2_pwm_devinfo);
}

/** \brief tim2 pwmʵ�����ʼ�� */
void am_zlg217_tim2_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_zlg_tim_pwm_deinit(handle);
}

/*******************************************************************************
  TIM3 ����
*******************************************************************************/

/** \brief TIM3����PWM��� ƽ̨��ʼ�� */
void __zlg217_plfm_tim3_pwm_init (void)
{
    am_clk_enable(CLK_TIM3);
    am_zlg217_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3 PWMƽ̨��ʼ�� */
void __zlg217_plfm_tim3_pwm_deinit (void)
{
    am_zlg217_clk_reset(CLK_TIM3);
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3����PWM���ܵ�����������Ϣ�б� */
am_zlg_tim_pwm_ioinfo_t __g_tim3_pwm_ioinfo_list[] = {
    {PIOA_6, PIOA_6_TIM3_CH1_REMAP0 | PIOA_6_AF_PP, PIOA_6_GPIO | PIOA_6_INPUT_FLOAT},  /**< \brief ͨ��1 */
    {PIOA_7, PIOA_7_TIM3_CH2_REMAP0 | PIOA_7_AF_PP, PIOA_7_GPIO | PIOA_7_INPUT_FLOAT},  /**< \brief ͨ��2 */
    {PIOC_8, PIOC_8_TIM3_CH3_REMAP3 | PIOC_8_AF_PP, PIOC_8_GPIO | PIOC_8_INPUT_FLOAT},  /**< \brief ͨ��3 */
    {PIOB_1, PIOB_1_TIM3_CH4_REMAP0 | PIOB_1_AF_PP, PIOB_1_GPIO | PIOB_1_INPUT_FLOAT},  /**< \brief ͨ��4 */
};

/** \brief TIM3����PWM�豸��Ϣ */
const am_zlg_tim_pwm_devinfo_t  __g_tim3_pwm_devinfo = {
    ZLG217_TIM3_BASE,                    /**< \brief TIM3�Ĵ�����Ļ���ַ */
    CLK_TIM3,                            /**< \brief TIM3ʱ��ID */
    4,                                   /**< \brief 4��PWM���ͨ�� */
    AMHW_ZLG_TIM_PWM_MODE2,           /**< \brief PWM���ģʽ2 */
    0,                                   /**< \brief PWM����ߵ�ƽ��Ч */
    &__g_tim3_pwm_ioinfo_list[0],
    AMHW_ZLG_TIM_TYPE1,               /**< \brief ��ʱ������ */
    __zlg217_plfm_tim3_pwm_init,         /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_tim3_pwm_deinit        /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM3����PWM�豸���� */
am_zlg_tim_pwm_dev_t __g_tim3_pwm_dev;

/** \brief tim3 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zlg217_tim3_pwm_inst_init (void)
{
    return am_zlg_tim_pwm_init(&__g_tim3_pwm_dev,
                                  &__g_tim3_pwm_devinfo);
}

/** \brief tim3 pwm ʵ�����ʼ�� */
void am_zlg217_tim3_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_zlg_tim_pwm_deinit(handle);
}

/*******************************************************************************
  TIM4����
*******************************************************************************/

/** \brief TIM4����PWM��� ƽ̨��ʼ�� */
void __zlg217_plfm_tim4_pwm_init (void)
{
    am_clk_enable(CLK_TIM4);
    am_zlg217_clk_reset(CLK_TIM4);
}

/** \brief ���TIM4 PWMƽ̨��ʼ�� */
void __zlg217_plfm_tim4_pwm_deinit (void)
{
    am_zlg217_clk_reset(CLK_TIM4);
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4����PWM���ܵ�����������Ϣ�б� */
am_zlg_tim_pwm_ioinfo_t __g_tim4_pwm_ioinfo_list[] = {
    {PIOB_6,  PIOB_6_TIM4_CH1 | PIOB_6_AF_PP, PIOB_6_GPIO | PIOB_6_INPUT_FLOAT},  /**< \brief ͨ��1 */
    {PIOB_7,  PIOB_7_TIM4_CH2 | PIOB_7_AF_PP, PIOB_7_GPIO | PIOB_7_INPUT_FLOAT},  /**< \brief ͨ��2 */
    {PIOB_8,  PIOB_8_TIM4_CH3 | PIOB_8_AF_PP, PIOB_8_GPIO | PIOB_8_INPUT_FLOAT},  /**< \brief ͨ��3 */
    {PIOB_9,  PIOB_9_TIM4_CH4 | PIOB_9_AF_PP, PIOB_9_GPIO | PIOB_9_INPUT_FLOAT},  /**< \brief ͨ��4 */
};

/** \brief TIM4����PWM�豸��Ϣ */
const am_zlg_tim_pwm_devinfo_t  __g_tim4_pwm_devinfo = {
    ZLG217_TIM4_BASE,                   /**< \brief TIM4�Ĵ�����Ļ���ַ */
    CLK_TIM4,                           /**< \brief TIM4ʱ��ID */
    4,                                  /**< \brief 4��PWM���ͨ�� */
    AMHW_ZLG_TIM_PWM_MODE2,          /**< \brief PWM���ģʽ2 */
    0,                                  /**< \brief PWM����ߵ�ƽ��Ч */
    &__g_tim4_pwm_ioinfo_list[0],
    AMHW_ZLG_TIM_TYPE1,              /**< \brief ��ʱ������ */
    __zlg217_plfm_tim4_pwm_init,        /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_tim4_pwm_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM4����PWM�豸���� */
am_zlg_tim_pwm_dev_t  __g_tim4_pwm_dev;

/** \brief tim4 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zlg217_tim4_pwm_inst_init (void)
{
    return am_zlg_tim_pwm_init(&__g_tim4_pwm_dev,
                                  &__g_tim4_pwm_devinfo);
}

/** \brief tim4 pwmʵ�����ʼ�� */
void am_zlg217_tim4_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_zlg_tim_pwm_deinit(handle);
}

/**
 * @}
 */

/* end of file */
