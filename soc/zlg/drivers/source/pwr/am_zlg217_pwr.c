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
 * \brief PWR drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-18  nwt, first implementation
 * \endinternal
 */
#include "am_int.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_arm_nvic.h"
#include "am_zlg217_pwr.h"
#include "am_zlg217_clk.h"
#include "amhw_zlg217_exti.h"
#include "amhw_zlg217_rcc.h"
#include "amhw_zlg_uart.h"
#include "amhw_zlg_flash.h"

#if   defined ( __CC_ARM )
  #define __ASM            __asm         /*!< asm keyword for ARM Compiler */
  #define __INLINE         __inline      /*!< inline keyword for ARM Compiler */
  #define __STATIC_INLINE  static __inline

#endif
#if defined ( __GNUC__ )
  #define __ASM            __asm         /*!< asm keyword for GNU Compiler */
  #define __INLINE         inline        /*!< inline keyword for GNU Compiler */
  #define __STATIC_INLINE  static inline

#endif
#include "core_cmInstr.h"

#define    __LSI_CLK    (40000UL)

/** \brief ָ�� PWR ��Դ�����豸��ָ�� */
am_zlg217_pwr_dev_t *__gp_pwr_dev;

/* �ں�˯�ߺ��� */
static void __pwr_cpu_wif (am_bool_t deep)
{
    if (deep) {
        AMHW_ARM_SCB->scr |= 0x04;
    } else {
        AMHW_ARM_SCB->scr &= ~0x04;
    }

    AMHW_ARM_SCB->scr &= ~0x02;

#ifdef __CC_ARM
    __ASM("WFI");
#endif

#ifdef __GNUC__
    __WFI();
#endif

}

/**
 * \brief Ĭ�ϵ��жϷ�����
 */
static void __dummy_isr (void *p_arg)
{
    ; /* VOID */
}

#if 0

/**
 * \brief ����AHB Ԥ��Ƶ
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-7 �� ����Ƶ
 *       - 8   �� 2��Ƶ
 *       - 9   �� 4��Ƶ
 *       - 10  �� 8��Ƶ
 *       - 11  �� 16��Ƶ
 *       - 12  �� 64��Ƶ
 *       - 13  �� 128��Ƶ
 *       - 14  �� 256��Ƶ
 *       - 15  �� 512��Ƶ
 *
 * \return ����AHB��Ƶֵ
 *
 */
static uint8_t ___zlg217_rcc_ahb_div_get (void)
{
    return (uint8_t)((AMHW_ZLG217_RCC->cfgr >> 4) & 0xful);
}
#endif /* 0 */

/*
 * \brief AHB ����ʱ��Ƶ�ʸ���
 */
static void __sys_clk_ahbfrq_update (int clk_id, uint32_t clk)
{
    uint32_t div = 0;

    div = am_zlg217_div_get(clk_id);

    if (div < 8)  {
        am_zlg217_clk_update(clk_id, clk / 1);

    } else if (div == 8){
        am_zlg217_clk_update(clk_id, clk / 2);

    } else if(div == 9){
        am_zlg217_clk_update(clk_id, clk / 4);

    } else if (div == 10) {
        am_zlg217_clk_update(clk_id, clk / 8);
    } else if (div == 11) {
        am_zlg217_clk_update(clk_id, clk / 16);
    } else if (div == 12) {
        am_zlg217_clk_update(clk_id, clk / 64);
    } else if (div == 13) {
        am_zlg217_clk_update(clk_id, clk / 128);
    } else if (div == 14) {
        am_zlg217_clk_update(clk_id, clk / 256);
    } else {
        am_zlg217_clk_update(clk_id, clk / 512);
    }
}

/**
 * \brief ��ͬ����ģʽ��ʱ��ת�䣬֧��ֹͣģʽ������ģʽ�� PLL ʱ��Դ��ת��
 */
static void __sys_clk_change (uint8_t pwr_mode)
{
    const am_zlg217_clk_dev_t *p_clk_dev = am_zlg217_clk_devinfo_get();

    uint32_t apb1_div = 0, apb2_div = 0;
    uint32_t i = 0;

    /* ���� APB1 ʱ��Ƶ�� */
    apb1_div = 1;
    for (i = 0; i < (p_clk_dev->p_devinfo->apb1_div & 0x7); i++) {
        apb1_div = apb1_div << 1;
    }

    /* ���� APB2 ʱ��Ƶ�� */
    apb2_div = 1;
    for (i = 0; i < (p_clk_dev->p_devinfo->apb2_div & 0x7); i++) {
        apb2_div = apb2_div << 1;
    }

    if (pwr_mode == AM_ZLG217_PWR_MODE_STOP) {

        /* ͣ��ģʽʹ�� LSI ��Ϊϵͳʱ�� */
        amhw_zlg217_rcc_lsi_enable();

        /* �ȴ� LSI ʱ�Ӿ��� */
        while (amhw_zlg217_rcc_lsirdy_read() == AM_FALSE);

        /* �л�ʱ�� */
        amhw_zlg217_rcc_sys_clk_set(AMHW_ZLG217_SYSCLK_LSI);

        /* ���� AHB��APB1��APB2 �����ŵ�ʱ��Ƶ�� */
        __sys_clk_ahbfrq_update(__gp_pwr_dev->p_pwrdevinfo->ahb_clk_num, __LSI_CLK);
        am_zlg217_clk_update(__gp_pwr_dev->p_pwrdevinfo->apb1_clk_num, p_clk_dev->ahb_clk  / apb1_div);
        am_zlg217_clk_update(__gp_pwr_dev->p_pwrdevinfo->apb2_clk_num, p_clk_dev->ahb_clk  / apb2_div);
    }

    if (pwr_mode == AM_ZLG217_PWR_MODE_RUN) {

        if (p_clk_dev->p_devinfo->pllin_src == AMHW_ZLG217_PLLCLK_HSE) {
            amhw_zlg217_rcc_hseon_enable ();
            while (amhw_zlg217_rcc_hserdy_read () == AM_FALSE);
        } else {
            amhw_zlg217_rcc_hsion_enable();
            while (amhw_zlg217_rcc_hsirdy_read () == AM_FALSE);
        }

        amhw_zlg217_rcc_pll_enable();
        while (amhw_zlg217_rcc_pllrdy_read() == AM_FALSE);

        /* ϵͳʱ��ѡΪ PLL */
        amhw_zlg217_rcc_sys_clk_set(AMHW_ZLG217_SYSCLK_PLL);

        /* ������ģʽ�½��� LSI ��Ϊϵͳʱ�� */
        amhw_zlg217_rcc_lsi_disable();

        /* ���� AHB��APB1��APB2 �����ŵ�ʱ��Ƶ�� */
        __sys_clk_ahbfrq_update(__gp_pwr_dev->p_pwrdevinfo->ahb_clk_num, p_clk_dev->pllout_clk);
        am_zlg217_clk_update(__gp_pwr_dev->p_pwrdevinfo->apb1_clk_num, p_clk_dev->ahb_clk  / apb1_div);
        am_zlg217_clk_update(__gp_pwr_dev->p_pwrdevinfo->apb2_clk_num, p_clk_dev->ahb_clk  / apb2_div);
    }

    if (pwr_mode == AM_ZLG217_PWR_MODE_STANBY) {

        /* ����ģʽʹ�� HSI ��Ϊϵͳʱ�� */
        amhw_zlg217_rcc_hsion_enable();

        /* �ȴ� HSI ʱ�Ӿ��� */
        while (amhw_zlg217_rcc_hsirdy_read() == AM_FALSE);

        /* ϵͳʱ��ѡΪ HSI */
        amhw_zlg217_rcc_sys_clk_set(AMHW_ZLG217_SYSCLK_HSI_DIV6);

        /* ʧ�� PLL */
        amhw_zlg217_rcc_pll_disable();

        /* ʧ�� LSI */
        amhw_zlg217_rcc_lsi_disable();

        /* ���� AHB��APB1��APB2 �����ŵ�ʱ��Ƶ�� */
        __sys_clk_ahbfrq_update(__gp_pwr_dev->p_pwrdevinfo->ahb_clk_num,
                                p_clk_dev->ahb_clk);
        am_zlg217_clk_update(__gp_pwr_dev->p_pwrdevinfo->apb1_clk_num,
                               p_clk_dev->ahb_clk / p_clk_dev->p_devinfo->apb1_div);
        am_zlg217_clk_update(__gp_pwr_dev->p_pwrdevinfo->apb2_clk_num,
                               p_clk_dev->ahb_clk / p_clk_dev->p_devinfo->apb2_div);
    }
}

/**
 * \brief PWR ��ʼ��
 */
am_zlg217_pwr_handle_t am_zlg217_pwr_init (am_zlg217_pwr_dev_t           *p_dev,
                                           const am_zlg217_pwr_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
           return NULL;
    }

    /* PWR ƽ̨��ʼ�� */
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_pwrdevinfo = p_devinfo;

    /* ȡ�õ�ǰ�� PWR ģʽ����ʼ��Ĭ��Ϊ����ģʽ */
    p_dev->pwr_mode  = AM_ZLG217_PWR_MODE_RUN;

    __gp_pwr_dev = p_dev;

    return p_dev;
}

/**
 * \brief ��� PWR ��ʼ��
 */
void am_zlg217_pwr_deinit (void)
{
    const am_zlg217_pwr_devinfo_t *p_pwr_devinfo = __gp_pwr_dev->p_pwrdevinfo;

    if (__gp_pwr_dev == NULL || p_pwr_devinfo== NULL) {
        return;
    }

    __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_RUN;
    __gp_pwr_dev->p_pwrdevinfo = NULL;

    __gp_pwr_dev = NULL;

    /* PWR ƽ̨���ʼ�� */
    if (p_pwr_devinfo->pfn_plfm_deinit) {
        p_pwr_devinfo->pfn_plfm_deinit();
    }
}

/**
 * \brief ����ϵͳģʽ
 *
 * \note ������ѵ����õ� PWR ģʽ������ am_zlg217_pwr_mode_into ������ѡ�� PWR
 *       ģʽ��ͬ���� AM_ZLG217_PWR_MODE_STANBY ģʽ�£����ѻḴλ��ע���жϻ���
 *       �����ص�������������
 */
void am_zlg217_wake_up_cfg (am_zlg217_pwr_mode_t mode,
                            am_pfnvoid_t         pfn_callback,
                            void                *p_arg)
{
    am_zlg217_pwr_mode_t cur_mode = am_zlg217_pwr_mode_get();

    if (cur_mode == mode) {
        return ;
    }

    switch (mode) {

    case AM_ZLG217_PWR_MODE_RUN:    /* ����ģʽ */

        __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_RUN;

        break;

    case AM_ZLG217_PWR_MODE_SLEEP:  /* ˯������ģʽ */

        if (pfn_callback != NULL) {

            /* ���������жϷ����� */
            am_gpio_trigger_connect(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin,
                                    pfn_callback,
                                    p_arg);

            /* ���������жϴ�����ʽ */
            am_gpio_trigger_cfg(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin,
                                AM_GPIO_TRIGGER_RISE);

            /* ʹ�����Ŵ����ж� */
            am_gpio_trigger_on(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin);

        }

        break;

    case AM_ZLG217_PWR_MODE_STOP:  /* ֹͣģʽ */

        if (pfn_callback != NULL) {

            /* ���������жϷ����� */
            am_gpio_trigger_connect(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin,
                                    pfn_callback,
                                    p_arg);

            /* ���������жϴ�����ʽ */
            am_gpio_trigger_cfg(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin,
                                AM_GPIO_TRIGGER_RISE);

            /* ʹ�����Ŵ����ж� */
            am_gpio_trigger_on(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin);

        }

        break;

    case AM_ZLG217_PWR_MODE_STANBY:  /* ����ģʽ */

        if (-1 == __gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin) {
            break;
        }

        /* ���������жϷ����� */
        am_gpio_trigger_connect(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin,
                                __dummy_isr,
                                p_arg);

        /* ���������жϴ�����ʽ */
        am_gpio_trigger_cfg(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin,
                            AM_GPIO_TRIGGER_RISE);

        /* ʹ�����Ŵ����ж� */
        am_gpio_trigger_on(__gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin);

        break;

    default:
        break;
    }
}

/**
 * \brief ����ϵͳģʽ
 */
int am_zlg217_pwr_mode_into (am_zlg217_pwr_mode_t mode)
{
    amhw_zlg_pwr_t   *p_hw_pwr = NULL;
    am_zlg217_pwr_mode_t cur_mode = am_zlg217_pwr_mode_get();

    int wkup_pin = __gp_pwr_dev->p_pwrdevinfo->p_pwr_mode[mode - 1].pin;

    if (cur_mode == mode) {
        return AM_OK;
    }

    p_hw_pwr = (amhw_zlg_pwr_t *)__gp_pwr_dev->p_pwrdevinfo->pwr_regbase;

    switch (mode) {

    case AM_ZLG217_PWR_MODE_RUN:    /* ����ģʽ */

        __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_RUN;

        break;

    case AM_ZLG217_PWR_MODE_SLEEP:  /* ˯��ģʽ */
        if (cur_mode != AM_ZLG217_PWR_MODE_RUN) {
            return -AM_EPERM;
        }
        __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_SLEEP;

        AM_DBG_INFO("enter sleep!\r\n");

        /* �ȴ����ڷ������ */
        while((ZLG217_UART1->csr & AMHW_ZLG_UART_TX_COMPLETE_FALG) == AM_FALSE);

        __pwr_cpu_wif(AM_FALSE);

        /* ��������ģʽ */
        __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_RUN;

        break;

    case AM_ZLG217_PWR_MODE_STOP:  /* ֹͣģʽ */
        if (cur_mode != AM_ZLG217_PWR_MODE_RUN) {
            return -AM_EPERM;
        }
        __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_STOP;

        /* ע�⣺ ��ѹ���������ܿ���������ͣ��״̬��û�й�ͣ */
        amhw_zlg_pwr_pdds_mode_set(p_hw_pwr, AM_ZLG_PDDS_STOP_MODE);

        AM_DBG_INFO("enter deepsleep!\r\n");

        /* �ȴ����ڷ������ */
        while((ZLG217_UART1->csr & AMHW_ZLG_UART_TX_COMPLETE_FALG) == AM_FALSE);

        /* CPU�������˯��ģʽ */
        __pwr_cpu_wif(AM_TRUE);

        /* ֹͣģʽ���Ѻ�ָ�ʱ�� */
        __sys_clk_change(AM_ZLG217_PWR_MODE_RUN);

        /* ��������ģʽ */
        __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_RUN;

        break;

    case AM_ZLG217_PWR_MODE_STANBY:  /* ����ģʽ */
        if (cur_mode != AM_ZLG217_PWR_MODE_RUN) {
            return -AM_EPERM;
        }
        __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_STANBY;

        /* �������ģʽ֮ǰ WKUP ���ű���Ϊ�͵�ƽ */
        if (wkup_pin != -1) {

            /* ʧ�� WKUP ���� */
            amhw_zlg_wake_up_enable(p_hw_pwr, AM_ZLG_WAKEUP_DISABLE);

            /* �� WKUP ����Ϊ���룬������Ƿ�Ϊ�ߵ�ƽ */
            am_gpio_pin_cfg(wkup_pin, AM_GPIO_INPUT | AM_GPIO_PULLDOWN);
            if (am_gpio_get(wkup_pin)) {
                return -AM_ENOTSUP;
            }

            /* ʹ�� WAKE_UP ���� */
            amhw_zlg_wake_up_enable(p_hw_pwr, AM_ZLG_WAKEUP_ENABLE);
        }

        amhw_zlg_pwr_stauts_flag_clear(p_hw_pwr, AM_ZLG_WAKEUP_FLAG_CLEAR);

        amhw_zlg_pwr_pdds_mode_set(p_hw_pwr, AM_ZLG_PDDS_STANDBY_MODE);

        AM_DBG_INFO("enter standby!\r\n");

        /* �ȴ����ڷ������ */
        while((ZLG217_UART1->csr & AMHW_ZLG_UART_TX_COMPLETE_FALG) == AM_FALSE);

        /* ����ģʽʹ�� HSI ��Ϊϵͳʱ�� */
        __sys_clk_change(AM_ZLG217_PWR_MODE_STANBY);

        /* CPU �������ģʽ */
        __pwr_cpu_wif(AM_TRUE);

        /* �ָ�ʱ��Դ����Ӧ��ִ�е������Ϊ����ģʽ����֮��оƬ��ֱ�Ӹ�λ */
        __sys_clk_change(AM_ZLG217_PWR_MODE_RUN);

        /* ��������ģʽ */
        __gp_pwr_dev->pwr_mode = AM_ZLG217_PWR_MODE_RUN;

        break;

    default:

        break;
    }

    return AM_OK;
}

/**
 * \brief ��ȡ PWR ģʽ
 */
am_zlg217_pwr_mode_t am_zlg217_pwr_mode_get (void)
{

    /* �͹�������ģʽ */
    return __gp_pwr_dev->pwr_mode;
}

/**
 * \brief ���� PVD ��ѹ�����Ϣ
 */
int am_zlg217_pwr_pvd_cfg (am_zlg217_pwr_handle_t pwr_handle,
                           am_pfnvoid_t           pfn_callback,
                           void                  *p_arg)
{
    amhw_zlg_pwr_t   *p_hw_pwr = NULL;
    am_zlg217_pwr_mode_t cur_mode = am_zlg217_pwr_mode_get();

    if(pwr_handle == NULL) {
        return -AM_EINVAL;
    }

    /* ����ģʽ��ֹͣģʽ�� CPU �ں�ֹͣ��֧�� PVD ��ѹ��� */
    if (cur_mode == AM_ZLG217_PWR_MODE_STOP  ||
        cur_mode == AM_ZLG217_PWR_MODE_STANBY ) {

        return AM_ERROR;
    }

    p_hw_pwr = (amhw_zlg_pwr_t *)__gp_pwr_dev->p_pwrdevinfo->pwr_regbase;

    if (pwr_handle->p_pwrdevinfo->p_pvd_info->enable) {

        amhw_zlg_pwr_pvd_detect_enable(p_hw_pwr, AM_ZLG_PVDE_ENABLE);
        amhw_zlg_pvd_lever_set(p_hw_pwr, pwr_handle->p_pwrdevinfo->p_pvd_info->pvd_v_level);

        /* ����ж������ã�PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
        amhw_zlg217_exti_imr_clear(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);
        amhw_zlg217_exti_emr_clear(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);

        /* ����ж��ߴ�����ʽ���ã�PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
        amhw_zlg217_exti_rtsr_clear(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);
        amhw_zlg217_exti_ftsr_clear(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);

        if (pwr_handle->p_pwrdevinfo->p_pvd_info->pvd_mode == 0) {

            /* �����ش���(��ʾ��ѹ�Ӹ��½��������趨��ֵʱ�����ж�)��PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
            amhw_zlg217_exti_rtsr_set(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);
        } else if (pwr_handle->p_pwrdevinfo->p_pvd_info->pvd_mode == 1) {

            /* �½��ش���(��ʾ��ѹ�ӵ������������趨��ֵʱ�����ж�)��PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
            amhw_zlg217_exti_ftsr_set(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);
        } else {

            /* ˫���ش���(��ʾ��ѹ�������½�Խ���趨��ֵʱ�������ж�)��PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
            amhw_zlg217_exti_rtsr_set(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);
            amhw_zlg217_exti_ftsr_set(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);
        }

        /* �� PVD �ж��߱�־λ��PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
        amhw_zlg217_exti_pending_clear(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);

        /* ���ÿ����ж������� , PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
        amhw_zlg217_exti_imr_set(ZLG217_EXTI,  AMHW_ZLG217_LINE_NUM16);

        /*
         * �����û�ע����жϻص�����
         */
        if (pfn_callback != NULL) {

            /* �ж����Ӳ�ʹ�� */
            am_int_connect(__gp_pwr_dev->p_pwrdevinfo->inum, pfn_callback, (void *)p_arg);
            am_int_enable(__gp_pwr_dev->p_pwrdevinfo->inum);

        }

    } else {

        /* �� PVD �ж��߱�־λ��PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
        amhw_zlg217_exti_pending_clear(ZLG217_EXTI, AMHW_ZLG217_LINE_NUM16);

        /* ���ý�ֹ�ж������� , PVD ��Ӧ�� AMHW_ZLG217_LINE_NUM16 */
        amhw_zlg217_exti_imr_clear(ZLG217_EXTI,  AMHW_ZLG217_LINE_NUM16);

        /* ���� NVIC �ж� */
        am_int_disable(__gp_pwr_dev->p_pwrdevinfo->inum);
    }

    return AM_OK;
}

/* end of file */
