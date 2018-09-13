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
 * \brief TIM ���ڲ����ܵ��û������ļ�
 * \sa am_hwconf_zlg217_tim_cap.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-28  zcb, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg217.h"
#include "am_zlg_tim_cap.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg217_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_tim_cap
 * \copydoc am_hwconf_zlg217_tim_cap.c
 * @{
 */

/*******************************************************************************
  TIM1 ����
*******************************************************************************/

/** \brief TIM1���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg217_plfm_tim1_cap_init (void)
{
    am_clk_enable(CLK_TIM1);
    am_zlg217_clk_reset(CLK_TIM1);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
void __zlg217_plfm_tim1_cap_deinit (void)
{
    am_zlg217_clk_reset(CLK_TIM1);
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim1_cap_ioinfo_list[] = {
    {PIOA_8,  PIOA_8_TIM1_CH1_REMAP0  | PIOA_8_INPUT_FLOAT,  PIOA_8_GPIO  | PIOA_8_INPUT_FLOAT},   /**< \brief ͨ��1 */
    {PIOA_9,  PIOA_9_TIM1_CH2_REMAP0  | PIOA_9_INPUT_FLOAT,  PIOA_9_GPIO  | PIOA_9_INPUT_FLOAT},   /**< \brief ͨ��2 */
    {PIOA_10, PIOA_10_TIM1_CH3_REMAP0 | PIOA_10_INPUT_FLOAT, PIOA_10_GPIO | PIOA_10_INPUT_FLOAT},  /**< \brief ͨ��3 */
    {PIOA_11, PIOA_11_TIM1_CH4_REMAP0 | PIOA_11_INPUT_FLOAT, PIOA_11_GPIO | PIOA_11_INPUT_FLOAT},  /**< \brief ͨ��4 */
};

/** \brief TIM1���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim1_cap_devinfo = {
    ZLG217_TIM1_BASE,                   /**< \brief TIM1�Ĵ�����Ļ���ַ */
    INUM_TIM1_CC,                       /**< \brief TIM1�жϱ�� */
    CLK_TIM1,                           /**< \brief TIM1ʱ��ID */
    4,                                  /**< \brief 4������ͨ�� */
    &__g_tim1_cap_ioinfo_list[0],
    AMHW_ZLG_TIM_TYPE0,              /**< \brief ��ʱ������ */
    __zlg217_plfm_tim1_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_tim1_cap_deinit       /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM1���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim1_cap_dev;

/** \brief tim1 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg217_tim1_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim1_cap_dev,
                                  &__g_tim1_cap_devinfo);
}

/** \brief tim1 capʵ�����ʼ�� */
void am_zlg217_tim1_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
  TIM2 ����
*******************************************************************************/

/** \brief TIM2���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg217_plfm_tim2_cap_init (void)
{
    am_clk_enable(CLK_TIM2);
    am_zlg217_clk_reset(CLK_TIM2);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
void __zlg217_plfm_tim2_cap_deinit (void)
{
    am_zlg217_clk_reset(CLK_TIM2);
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim2_cap_ioinfo_list[] = {
    {PIOA_15, PIOA_15_TIM2_CH1_ETR_REMAP1 | PIOA_15_INPUT_FLOAT, PIOA_15_GPIO | PIOA_15_INPUT_FLOAT},  /**< \brief ͨ��1 */
    {PIOB_3, PIOB_3_TIM2_CH2_REMAP1       | PIOB_3_INPUT_FLOAT, PIOB_3_GPIO   | PIOB_3_INPUT_FLOAT},   /**< \brief ͨ��2 */
    {PIOB_10, PIOB_10_TIM2_CH3_REMAP2     | PIOB_10_INPUT_FLOAT, PIOB_10_GPIO | PIOB_10_INPUT_FLOAT},  /**< \brief ͨ��3 */
    {PIOB_11, PIOB_11_TIM2_CH4_REMAP2     | PIOB_11_INPUT_FLOAT, PIOB_11_GPIO | PIOB_11_INPUT_FLOAT},  /**< \brief ͨ��4 */
};

/** \brief TIM2���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim2_cap_devinfo = {
    ZLG217_TIM2_BASE,                   /**< \brief TIM2�Ĵ�����Ļ���ַ */
    INUM_TIM2,                          /**< \brief TIM2�жϱ�� */
    CLK_TIM2,                           /**< \brief TIM2ʱ��ID */
    4,                                  /**< \brief 4������ͨ�� */
    &__g_tim2_cap_ioinfo_list[0],
    AMHW_ZLG_TIM_TYPE1,              /**< \brief ��ʱ������ */
    __zlg217_plfm_tim2_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_tim2_cap_deinit       /**< \brief ƽ̨���ʼ������ */

};

/** \brief TIM2���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim2_cap_dev;

/** \brief tim2 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg217_tim2_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim2_cap_dev,
                                  &__g_tim2_cap_devinfo);
}

/** \brief tim2 capʵ�����ʼ�� */
void am_zlg217_tim2_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
  TIM3 ����
*******************************************************************************/

/** \brief TIM3���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg217_plfm_tim3_cap_init (void)
{
    am_clk_enable(CLK_TIM3);
    am_zlg217_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3ƽ̨��ʼ�� */
void __zlg217_plfm_tim3_cap_deinit (void)
{
    am_zlg217_clk_reset(CLK_TIM3);
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim3_cap_ioinfo_list[] = {
    {PIOA_6, PIOA_6_TIM3_CH1_REMAP0 | PIOA_6_INPUT_FLOAT, PIOA_6_GPIO | PIOA_6_INPUT_FLOAT},  /**< \brief ͨ��1 */
    {PIOA_7, PIOA_7_TIM3_CH2_REMAP0 | PIOA_7_INPUT_FLOAT, PIOA_7_GPIO | PIOA_7_INPUT_FLOAT},  /**< \brief ͨ��2 */
    {PIOB_0, PIOB_0_TIM3_CH3_REMAP0 | PIOB_0_INPUT_FLOAT, PIOB_0_GPIO | PIOB_0_INPUT_FLOAT},  /**< \brief ͨ��3 */
    {PIOB_1, PIOB_1_TIM3_CH4_REMAP0 | PIOB_1_INPUT_FLOAT, PIOB_1_GPIO | PIOB_1_INPUT_FLOAT},  /**< \brief ͨ��4 */
};

/** \brief TIM3���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim3_cap_devinfo = {
    ZLG217_TIM3_BASE,                   /**< \brief TIM3�Ĵ�����Ļ���ַ */
    INUM_TIM3,                          /**< \brief TIM3�жϱ�� */
    CLK_TIM3,                           /**< \brief TIM3ʱ��ID */
    4,                                  /**< \brief 4������ͨ�� */
    &__g_tim3_cap_ioinfo_list[0],
    AMHW_ZLG_TIM_TYPE1,              /**< \brief ��ʱ������ */
    __zlg217_plfm_tim3_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_tim3_cap_deinit       /**< \brief ƽ̨���ʼ������ */

};

/** \brief TIM3���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim3_cap_dev;

/** \brief tim3 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg217_tim3_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim3_cap_dev,
                                  &__g_tim3_cap_devinfo);
}

/** \brief tim3 capʵ�����ʼ�� */
void am_zlg217_tim3_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
  TIM4 ����
*******************************************************************************/

/** \brief TIM4���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg217_plfm_tim4_cap_init (void)
{
    am_clk_enable(CLK_TIM4);
    am_zlg217_clk_reset(CLK_TIM4);
}

/** \brief ���TIM4ƽ̨��ʼ�� */
void __zlg217_plfm_tim4_cap_deinit (void)
{
    am_zlg217_clk_reset(CLK_TIM4);
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim4_cap_ioinfo_list[] = {
    {PIOB_6,  PIOB_6_TIM4_CH1 | PIOB_6_INPUT_FLOAT, PIOB_6_GPIO | PIOB_6_INPUT_FLOAT},  /**< \brief ͨ��1 */
    {PIOB_7,  PIOB_7_TIM4_CH2 | PIOB_7_INPUT_FLOAT, PIOB_7_GPIO | PIOB_7_INPUT_FLOAT},  /**< \brief ͨ��2 */
    {PIOB_8,  PIOB_8_TIM4_CH3 | PIOB_8_INPUT_FLOAT, PIOB_8_GPIO | PIOB_8_INPUT_FLOAT},  /**< \brief ͨ��3 */
    {PIOB_9,  PIOB_9_TIM4_CH4 | PIOB_9_INPUT_FLOAT, PIOB_9_GPIO | PIOB_9_INPUT_FLOAT},  /**< \brief ͨ��4 */
};

/** \brief TIM4���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim4_cap_devinfo = {
    ZLG217_TIM4_BASE,                   /**< \brief TIM4�Ĵ�����Ļ���ַ */
    INUM_TIM4,                          /**< \brief TIM4�жϱ�� */
    CLK_TIM4,                           /**< \brief TIM4ʱ��ID */
    4,                                  /**< \brief 4������ͨ�� */
    &__g_tim4_cap_ioinfo_list[0],
    AMHW_ZLG_TIM_TYPE1,              /**< \brief ��ʱ������ */
    __zlg217_plfm_tim4_cap_init,        /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_tim4_cap_deinit       /**< \brief ƽ̨���ʼ������ */

};

/** \brief TIM4���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim4_cap_dev;

/** \brief tim4 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zlg217_tim4_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim4_cap_dev,
                                  &__g_tim4_cap_devinfo);
}

/** \brief tim4 capʵ�����ʼ�� */
void am_zlg217_tim4_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/**
 * @}
 */

/* end of file */
