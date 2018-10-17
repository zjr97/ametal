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
 * \brief Real-Time Clock(RTC) drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.01 18-06-14  pea, fix bug
 * - 1.00 17-08-28  lqy, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_zlg217.h"
#include "am_zlg217_rtc.h"
#include "amhw_zlg217_rtc.h"
#include "amhw_zlg217_rcc.h"
#include "amhw_zlg_pwr.h"
#include "amhw_zlg217_bkp.h"
#include "zlg217_periph_map.h"
#include <time.h>
#include <string.h>

/*******************************************************************************
  ���غ�������
*******************************************************************************/

/**
 * \brief ���õ�ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_set (void *p_drv, am_tm_t *p_tm);

/**
 * \brief ��ȡ��ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_get (void *p_drv, am_tm_t *p_tm);

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief ���� RTC ��׼�ӿ���Ҫ�ĺ��� */
am_local am_const struct am_rtc_drv_funcs __g_rtc_drv_funcs = {
    __rtc_time_set,  /* ���õ�ǰ��ϸ��ʱ�� */
    __rtc_time_get,  /* ��ȡ��ǰ��ϸ��ʱ�� */
};

/*******************************************************************************
  ���غ�������
*******************************************************************************/

/**
 * \brief �ȴ� RTC �Ĵ���ͬ��
 */
am_local void __sync_wait (amhw_zlg217_rtc_t *p_hw_rtc)
{
    while (amhw_zlg217_rtc_crl_read_statu(p_hw_rtc, AMHW_ZLG217_RTC_RSF) == 0);
}

/**
 * \brief �ȴ� RTC �������
 */
am_local void __operation_wait (amhw_zlg217_rtc_t *p_hw_rtc)
{
    while (amhw_zlg217_rtc_crl_read_statu(p_hw_rtc, AMHW_ZLG217_RTC_RTOFF) == 0);
}

/**
 * \brief ��ת��Ϊ am_tm_t ʱ������
 * 
 * \param[in]  seconds ������
 * \param[out] p_time  ָ�� am_tm_t ʱ�����ݵ�ָ��
 *
 * \return ��
 */
am_local void __sec2tm (uint32_t sec, am_tm_t *p_time)
{
    time_t     second = sec;
    struct tm *p_tm   = NULL;

    p_tm = localtime(&second);

    if ((NULL != p_time) && (NULL != p_tm)) {
        memcpy(p_time, p_tm, sizeof(am_tm_t));
    }
}

/**
 * \brief ��ȡ��ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_get (void *p_drv, am_tm_t *p_tm)
{
    am_zlg217_rtc_dev_t *p_dev    = (am_zlg217_rtc_dev_t *)p_drv;
    amhw_zlg217_rtc_t   *p_hw_rtc = (amhw_zlg217_rtc_t  *)p_dev->p_devinfo->rtc_regbase;
    uint32_t             sec;

    if ((NULL == p_tm) || (NULL == p_tm)) {
        return -AM_EINVAL;
    }

    __sync_wait(p_hw_rtc); /* �ȴ� RTC �Ĵ���ͬ�� */

    if (AM_OK != am_zlg217_rtc_cnt_get(&p_dev->rtc_serv, &sec)) {
        return -AM_EINVAL;
    }

    /* ����ת����ʱ����Ϣ */
    __sec2tm(sec, p_tm);

    return AM_OK;
}

/**
 * \brief ���õ�ǰ��ϸ��ʱ��
 */
am_local int __rtc_time_set (void *p_drv, am_tm_t *p_tm)
{
    am_zlg217_rtc_dev_t *p_dev = (am_zlg217_rtc_dev_t *)p_drv;
    uint32_t             sec;

    if ((NULL == p_tm) || (NULL == p_tm)) {
        return -AM_EINVAL;
    }

    sec = mktime((struct tm *)p_tm);

    am_zlg217_rtc_cnt_set(&p_dev->rtc_serv, sec);

    return AM_OK;
}

/**
 * \brief RTC �жϷ�����
 */
am_local void __rtc_sec_isr (void *p_arg)
{
    am_zlg217_rtc_dev_t *p_dev = (am_zlg217_rtc_dev_t *)p_arg;
    amhw_zlg217_rtc_t   *p_hw_rtc = NULL;

    p_hw_rtc =(amhw_zlg217_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    /* ���ж� */
    if (amhw_zlg217_rtc_crl_read_statu(p_hw_rtc, AMHW_ZLG217_RTC_SECF)) {
        amhw_zlg217_rtc_clr_status_clear(p_hw_rtc, AMHW_ZLG217_RTC_SECF);
        if (p_dev->pfn_callback[0]) {
            p_dev->pfn_callback[0](p_dev->p_arg[0]);
        }
    }

    /* �����ж� */
    if (amhw_zlg217_rtc_crl_read_statu(p_hw_rtc, AMHW_ZLG217_RTC_ALRF)) {
        amhw_zlg217_rtc_clr_status_clear(p_hw_rtc, AMHW_ZLG217_RTC_ALRF);
        if (p_dev->pfn_callback[1]) {
            p_dev->pfn_callback[1](p_dev->p_arg[1]);
        }
    }

    /* ����ж� */
    if (amhw_zlg217_rtc_crl_read_statu(p_hw_rtc, AMHW_ZLG217_RTC_OWF)) {
        amhw_zlg217_rtc_clr_status_clear(p_hw_rtc, AMHW_ZLG217_RTC_OWF);
        if (p_dev->pfn_callback[2]) {
            p_dev->pfn_callback[2](p_dev->p_arg[2]);
        }
    }
}

/*******************************************************************************
  �ⲿ��������
*******************************************************************************/

/**
 * \brief RTC ״̬��ȡ�����������жϱ�������ǰ���������Ƿ�ϵ�
 */
am_bool_t am_zlg217_rtc_state_get (am_rtc_handle_t handle)
{
    am_zlg217_rtc_dev_t *p_dev    = NULL;

    if (NULL == handle) {
        return AM_FALSE;
    }

    p_dev = (am_zlg217_rtc_dev_t *)AM_CONTAINER_OF(handle, am_zlg217_rtc_dev_t, rtc_serv);

    return p_dev->rtc_continue;
}

/**
 * \brief RTC ͬ����־��λ���� APB1 ��������ֹ������Ҫ���ô˽ӿ�
 */
am_err_t am_zlg217_rtc_apb1_reflush (am_rtc_handle_t handle)
{
    am_zlg217_rtc_dev_t *p_dev    = NULL;
    amhw_zlg217_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev = (am_zlg217_rtc_dev_t *)AM_CONTAINER_OF(handle, am_zlg217_rtc_dev_t, rtc_serv);
    p_hw_rtc =(amhw_zlg217_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    amhw_zlg217_rtc_clr_status_clear(p_hw_rtc, AMHW_ZLG217_RTC_RSF);

    return AM_OK;
}

/**
 * \brief ��ȡ RTC ������ֵ
 */
am_err_t am_zlg217_rtc_cnt_get (am_rtc_handle_t handle, uint32_t *p_cnt)
{
    am_zlg217_rtc_dev_t *p_dev    = NULL;
    amhw_zlg217_rtc_t   *p_hw_rtc = NULL;

    if ((NULL == handle) || (NULL == p_cnt)) {
        return -AM_EINVAL;
    }

    p_dev = (am_zlg217_rtc_dev_t *)AM_CONTAINER_OF(handle, am_zlg217_rtc_dev_t, rtc_serv);
    p_hw_rtc =(amhw_zlg217_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    __sync_wait(p_hw_rtc); /* �ȴ� RTC �Ĵ���ͬ�� */

    *p_cnt = (amhw_zlg217_rtc_cnth_get(p_hw_rtc) << 16) +
             amhw_zlg217_rtc_cntl_get(p_hw_rtc);

    return AM_OK;
}

/**
 * \brief ���� RTC ������ֵ
 */
am_err_t am_zlg217_rtc_cnt_set (am_rtc_handle_t handle, uint32_t cnt)
{
    am_zlg217_rtc_dev_t *p_dev    = NULL;
    amhw_zlg217_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev = (am_zlg217_rtc_dev_t *)AM_CONTAINER_OF(handle, am_zlg217_rtc_dev_t, rtc_serv);
    p_hw_rtc = (amhw_zlg217_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    __operation_wait(p_hw_rtc);                            /* �ȴ� RTC ������� */
    amhw_zlg217_rtc_clr_status_clear(p_hw_rtc,             /* ������� RSF ��־λ */
                                     AMHW_ZLG217_RTC_RSF);
    amhw_zlg217_rtc_crl_cnf_enter(p_hw_rtc);               /* �������� */
    amhw_zlg217_rtc_cnth_set(p_hw_rtc, cnt >> 16);         /* д��� 16 λ */
    amhw_zlg217_rtc_cntl_set(p_hw_rtc, cnt & 0xffff);      /* д��� 16 λ */
    amhw_zlg217_rtc_crl_cnf_out(p_hw_rtc);                 /* ���ø��� */
    __operation_wait(p_hw_rtc);                            /* �ȴ� RTC ������� */

    return AM_OK;
}

/**
 * \brief ���� RTC ����ֵ
 */
am_err_t am_zlg217_rtc_alr_set (am_rtc_handle_t handle, uint32_t alr)
{
    am_zlg217_rtc_dev_t *p_dev    = NULL;
    amhw_zlg217_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev = (am_zlg217_rtc_dev_t *)AM_CONTAINER_OF(handle, am_zlg217_rtc_dev_t, rtc_serv);
    p_hw_rtc =(amhw_zlg217_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    __operation_wait(p_hw_rtc);                       /* �ȴ� RTC ������� */
    amhw_zlg217_rtc_crl_cnf_enter(p_hw_rtc);          /* �������� */
    amhw_zlg217_rtc_alrh_set(p_hw_rtc, alr >> 16);    /* д��� 16 λ */
    amhw_zlg217_rtc_alrl_set(p_hw_rtc, alr & 0xFFFF); /* д��� 16 λ */
    amhw_zlg217_rtc_crl_cnf_out(p_hw_rtc);            /* ���ø��� */
    __operation_wait(p_hw_rtc);                       /* �ȴ� RTC ������� */

    return AM_OK;
}

/**
 * \brief ���� RTC ����ʱ��
 */
am_err_t am_zlg217_rtc_alarm_set (am_rtc_handle_t handle, am_tm_t *p_tm)
{
    uint32_t sec = 0;

    if ((NULL == handle) || (NULL == p_tm)) {
        return -AM_EINVAL;
    }

    sec = mktime((struct tm *)p_tm);

    am_zlg217_rtc_alr_set(handle, sec);

    return AM_OK;
}

/**
 * \brief ���� RTC �жϻص�
 */
am_err_t am_zlg217_rtc_callback_set (am_rtc_handle_t handle,
                                     uint8_t         type,
                                     am_pfnvoid_t    pfn_callback,
                                     void           *p_arg)
{
    am_zlg217_rtc_dev_t *p_dev = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev = (am_zlg217_rtc_dev_t *)AM_CONTAINER_OF(handle, am_zlg217_rtc_dev_t, rtc_serv);

    if (AM_ZLG217_RTC_CALLBACK_SECOND == type) {
        p_dev->pfn_callback[0] = pfn_callback;
        p_dev->p_arg[0] = p_arg;
    } else if (AM_ZLG217_RTC_CALLBACK_ALARM == type) {
        p_dev->pfn_callback[1] = pfn_callback;
        p_dev->p_arg[1] = p_arg;
    } else if (AM_ZLG217_RTC_CALLBACK_OVER == type) {
        p_dev->pfn_callback[2] = pfn_callback;
        p_dev->p_arg[2] = p_arg;
    } else {
        return -AM_EINVAL;
    }

    return AM_OK;
}

/**
 * \brief RTC �ж�ʹ��
 */
am_err_t am_zlg217_rtc_int_enable (am_rtc_handle_t handle,
                                   uint8_t         type)
{
    am_zlg217_rtc_dev_t *p_dev    = NULL;
    amhw_zlg217_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev = (am_zlg217_rtc_dev_t *)AM_CONTAINER_OF(handle, am_zlg217_rtc_dev_t, rtc_serv);
    p_hw_rtc =(amhw_zlg217_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    __operation_wait(p_hw_rtc); /* �ȴ� RTC ������� */

    if (AM_ZLG217_RTC_CALLBACK_SECOND == type) {
        amhw_zlg217_rtc_crh_allow_int(p_hw_rtc, AMHW_ZLG217_RTC_SECIE);
        p_dev->int_state |= AM_ZLG217_RTC_CALLBACK_SECOND;
    } else if (AM_ZLG217_RTC_CALLBACK_ALARM == type) {
        amhw_zlg217_rtc_crh_allow_int(p_hw_rtc, AMHW_ZLG217_RTC_ALRIE);
        p_dev->int_state |= AM_ZLG217_RTC_CALLBACK_ALARM;
    } else if (AM_ZLG217_RTC_CALLBACK_OVER == type) {
        amhw_zlg217_rtc_crh_allow_int(p_hw_rtc, AMHW_ZLG217_RTC_OWIE);
        p_dev->int_state |= AM_ZLG217_RTC_CALLBACK_OVER;
    } else {
        return -AM_EINVAL;
    }

    am_int_enable(p_dev->p_devinfo->rtc_inum);

    return AM_OK;
}

/**
 * \brief RTC �ж�ʧ��
 */
am_err_t am_zlg217_rtc_int_disable (am_rtc_handle_t handle,
                                    uint8_t         type)
{
    am_zlg217_rtc_dev_t *p_dev    = NULL;
    amhw_zlg217_rtc_t   *p_hw_rtc = NULL;

    if (NULL == handle) {
        return -AM_EINVAL;
    }

    p_dev = (am_zlg217_rtc_dev_t *)AM_CONTAINER_OF(handle, am_zlg217_rtc_dev_t, rtc_serv);
    p_hw_rtc =(amhw_zlg217_rtc_t *)p_dev->p_devinfo->rtc_regbase;

    __operation_wait(p_hw_rtc); /* �ȴ� RTC ������� */

    if (AM_ZLG217_RTC_CALLBACK_SECOND == type) {
        amhw_zlg217_rtc_crh_forbid_int(p_hw_rtc, AMHW_ZLG217_RTC_SECIE);
        p_dev->int_state &= ~AM_ZLG217_RTC_CALLBACK_SECOND;
    } else if (AM_ZLG217_RTC_CALLBACK_ALARM == type) {
        amhw_zlg217_rtc_crh_forbid_int(p_hw_rtc, AMHW_ZLG217_RTC_ALRIE);
        p_dev->int_state &= ~AM_ZLG217_RTC_CALLBACK_ALARM;
    } else if (AM_ZLG217_RTC_CALLBACK_OVER == type) {
        amhw_zlg217_rtc_crh_forbid_int(p_hw_rtc, AMHW_ZLG217_RTC_OWIE);
        p_dev->int_state &= ~AM_ZLG217_RTC_CALLBACK_OVER;
    } else {
        return -AM_EINVAL;
    }

    if (0 == p_dev->int_state) {
        am_int_disable(p_dev->p_devinfo->rtc_inum);
    }

    return AM_OK;
}

/**
 * \brief ��ʼ�� RTC
 */
am_rtc_handle_t am_zlg217_rtc_init (am_zlg217_rtc_dev_t           *p_dev,
                                    const am_zlg217_rtc_devinfo_t *p_devinfo)
{
    uint32_t           prl_val  = 0;
    uint32_t           rtc_clk  = 0 ;
    amhw_zlg217_rtc_t *p_hw_rtc = NULL;
    amhw_zlg_pwr_t *p_hw_pwr = NULL;
    amhw_zlg217_bkp_t *p_hw_bkp = NULL;

    if ((NULL == p_dev) || (NULL == p_devinfo)) {
        return NULL;
    }

    p_hw_rtc                = (amhw_zlg217_rtc_t *)p_devinfo->rtc_regbase;
    p_hw_pwr                = (amhw_zlg_pwr_t *)p_devinfo->pwr_regbase;
    p_hw_bkp                = (amhw_zlg217_bkp_t *)p_devinfo->bkp_regbase;
    p_dev->rtc_serv.p_funcs = (struct am_rtc_drv_funcs *)&__g_rtc_drv_funcs;
    p_dev->rtc_serv.p_drv   = p_dev;
    p_dev->int_state        = 0;
    p_dev->rtc_continue     = AM_FALSE;
    p_dev->pfn_callback[0]  = NULL;
    p_dev->pfn_callback[1]  = NULL;
    p_dev->pfn_callback[2]  = NULL;
    p_dev->p_devinfo        = p_devinfo;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    amhw_zlg217_rcc_apb1_enable(AMHW_ZLG217_RCC_APB1_PWR); /* ʹ�ܵ�Դʱ�� */
    amhw_zlg217_rcc_apb1_enable(AMHW_ZLG217_RCC_APB1_BKP); /* ʹ�ܱ���ʱ�� */
    amhw_zlg_pwr_bkp_access_enable(p_hw_pwr, 1);           /* ȡ���������д���� */

    /* ����ӱ��ݼĴ����ж�����ֵ������Ԥ�ڣ���Ҫ���³�ʼ�� */
    if (0x5A5A != amhw_zlg217_bkp_dr_read(p_hw_bkp, 0)) {

        amhw_zlg217_rcc_bdcr_bdrst_reset();     /* �������������λ */
        amhw_zlg217_rcc_bdcr_bdrst_reset_end(); /* �����������λ���� */

        /* ��ȡ RTC ʱ��Դ��ʹ��ʱ�Ӳ�����Ԥ��Ƶֵ */
        switch (p_dev->p_devinfo->rtc_clk_sour){

            case AMHW_ZLG217_RTCCLK_LSE:

                /* ʹ�� LSE */
                amhw_zlg217_rcc_bdcr_lseon_enable();
                while (!amhw_zlg217_rcc_bdcr_lserdy_read());

                prl_val = 32768 - 1;
                break;

            case AMHW_ZLG217_RTCCLK_LSI:

                /* ʹ�� LSI */
                amhw_zlg217_rcc_lsi_enable();
                while (!amhw_zlg217_rcc_lsirdy_read());

                prl_val = 40000 - 1;
                break;

            case AMHW_ZLG217_RTCCLK_HSE_DIV128:

                /* ʹ�� HSE */
                amhw_zlg217_rcc_hseon_enable();
                while (!amhw_zlg217_rcc_hserdy_read());

                rtc_clk = am_clk_rate_get(CLK_HSEOSC) / 128;
                prl_val = rtc_clk - 1;
                break;

            default:
               break;
        }

        /* RTC ʱ��Դѡ�� */
        amhw_zlg217_rcc_bdcr_rtc_clk_set((amhw_zlg217_rtc_clk_src)p_devinfo->rtc_clk_sour);

        /* RTC ʱ��ʹ�� */
        amhw_zlg217_rcc_bdcr_rtc_enable();

        amhw_zlg217_rtc_clr_status_clear(p_hw_rtc, AMHW_ZLG217_RTC_RSF);
        __sync_wait(p_hw_rtc); /* �ȴ� RTC �Ĵ���ͬ�� */

        __operation_wait(p_hw_rtc); /* �ȴ� RTC ������� */
        amhw_zlg217_rtc_clr_status_clear(p_hw_rtc, AMHW_ZLG217_RTC_RSF);
        amhw_zlg217_rtc_crl_cnf_enter(p_hw_rtc); /* �������� RTC */
        amhw_zlg217_rtc_prlh_div_write(p_hw_rtc, prl_val >> 16);
        amhw_zlg217_rtc_prll_div_write(p_hw_rtc, prl_val & 0xffff);
        amhw_zlg217_rtc_crl_cnf_out(p_hw_rtc);   /* ���ø��� */
        __operation_wait(p_hw_rtc); /* �ȴ� RTC ������� */

        amhw_zlg217_bkp_dr_write(ZLG217_BKP, 0, 0x5A5A);

        p_dev->rtc_continue = AM_FALSE;
    } else {
        if (AMHW_ZLG217_RTCCLK_LSI == p_dev->p_devinfo->rtc_clk_sour) {

            /* ʹ�� LSI */
            amhw_zlg217_rcc_lsi_enable();
            while (!amhw_zlg217_rcc_lsirdy_read());
        } else if (AMHW_ZLG217_RTCCLK_HSE_DIV128 == p_dev->p_devinfo->rtc_clk_sour) {

            /* ʹ�� HSE */
            amhw_zlg217_rcc_hseon_enable();
            while (!amhw_zlg217_rcc_hserdy_read());
        }
        amhw_zlg217_rtc_clr_status_clear(p_hw_rtc, AMHW_ZLG217_RTC_RSF);
        __sync_wait(p_hw_rtc); /* �ȴ� RTC �Ĵ���ͬ�� */
        __operation_wait(p_hw_rtc); /* �ȴ� RTC ������� */

        p_dev->rtc_continue = AM_TRUE;
    }

    /* �����ж� */
    am_int_connect(p_devinfo->rtc_inum, __rtc_sec_isr, p_dev);
    am_int_disable(p_devinfo->rtc_inum);

    return &p_dev->rtc_serv;
}

/**
 * \brief ���ʼ�� RTC
 */
void am_zlg217_rtc_deinit (am_rtc_handle_t handle)
{
    am_zlg217_rtc_dev_t *p_dev    = (am_zlg217_rtc_dev_t *)handle;
    amhw_zlg_pwr_t   *p_hw_pwr    = NULL;

    if ((NULL == p_dev) || (NULL == p_dev->p_devinfo)) {
        return;
    }

    p_hw_pwr = (amhw_zlg_pwr_t *)p_dev->p_devinfo->pwr_regbase;

    p_dev->pfn_callback[0]  = NULL;
    p_dev->pfn_callback[1]  = NULL;
    p_dev->pfn_callback[2]  = NULL;
    p_dev->p_devinfo        = NULL;
    p_dev->rtc_serv.p_funcs = NULL;
    p_dev->rtc_serv.p_drv   = NULL;
    p_dev                   = NULL;

    amhw_zlg217_bkp_dr_write(ZLG217_BKP, 0, 0);             /* ������ */
    amhw_zlg217_rcc_apb1_disable(AMHW_ZLG217_RCC_APB1_PWR); /* ���ܵ�Դʱ�� */
    amhw_zlg217_rcc_apb1_disable(AMHW_ZLG217_RCC_APB1_BKP); /* ���ܱ���ʱ�� */
    amhw_zlg_pwr_bkp_access_enable(p_hw_pwr, 0);            /* �������д���� */
    amhw_zlg217_rcc_bdcr_rtc_disable();                     /* RTC ʱ��ʧ�� */

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/** end of file */
