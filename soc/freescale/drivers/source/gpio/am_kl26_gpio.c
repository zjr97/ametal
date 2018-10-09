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
 * \brief GPIO implementation
 *
 * \internal
 * \par Modification history
 * - 1.01 16-09-15  nwt, make some changes about Macro definition.
 * - 1.00 15-10-21  wxj, first implementation.
 * \endinternal
 */

#include "am_gpio.h"
#include "am_gpio_util.h"
#include "am_int.h"
#include "am_kl26_gpio.h"
#include "am_kl26_gpio_util.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ             */
#define AM_KL26_GPIO_INVALID_PIN_MAP    0xFF

/** \brief δ�����������ܱ�ʶ         */
#define AM_KL26_GPIO_NO_FUNC            0xFF

/** \brief ����ָ��GPIO�豸��Ϣ��ָ�� */
#define __GPIO_DEVINFO_DECL(p_gpio_devinfo, p_dev)  \
        const am_kl26_gpio_devinfo_t *p_gpio_devinfo = p_dev->p_devinfo

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \brief ָ��GPIO�豸��ָ�� */
am_kl26_gpio_dev_t *__gp_gpio_dev = NULL;

/*******************************************************************************
  ��������
*******************************************************************************/

/**
 * \brief ��������
 */
int am_gpio_pin_cfg (int pin, uint32_t flags)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_kl26_port_t *p_hw_port = p_gpio_devinfo->p_hw_port;
    amhw_kl26_gpio_t *p_hw_gpio = p_gpio_devinfo->p_hw_gpio;

    uint32_t func, mode;

    /* ��ȡ��׼�㶨�����Ϣ */
    func = AM_GPIO_COM_FUNC_GET(flags);
    mode = AM_GPIO_COM_MODE_GET(flags);

    /*
     * ���й������ã����ȼ��ߣ�
     */
    if (func != 0x00) {

        switch (func) {

        /* Ĭ�Ϲܽ�ΪGPIO���� */
        case AM_GPIO_INPUT:           
            amhw_kl26_gpio_pin_dir_input(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_HIGH:
            amhw_kl26_gpio_pin_dir_output(p_hw_gpio, pin);
            amhw_kl26_gpio_pin_init_out_high(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_LOW:
            amhw_kl26_gpio_pin_dir_output(p_hw_gpio, pin);
            amhw_kl26_gpio_pin_init_out_low(p_hw_gpio, pin);
            break;

        default:
            break;
        }
    }
	
    /* �ܽ�Ĭ��ΪGPIO���� */
    amhw_kl26_port_pin_func_cfg(p_hw_port, pin, KL26_PORT_GPIO);	

    if (mode != 0x00) {

        if (mode == AM_GPIO_FLOAT_VAL) {                    /* ����/���� */
            amhw_kl26_port_pin_pull_disable(p_hw_port, pin);

        } else if (mode == AM_GPIO_PULL_UP_VAL) {           /* ��������ģʽ */
            amhw_kl26_port_pin_pull_enable(p_hw_port, pin);
            amhw_kl26_port_pin_pull_up(p_hw_port, pin);

        } else if (mode == AM_GPIO_PULL_DOWN_VAL) {         /* ��������ģʽ */
            amhw_kl26_port_pin_pull_enable(p_hw_port, pin);
            amhw_kl26_port_pin_pull_down(p_hw_port, pin);

        } else {
            return -AM_ENOTSUP;
        }
    }

    /* ƽ̨�������� */

    /* ��Ҫ�������Ź��� */
    if ((flags & AM_KL26_PORT_FUNEN) != 0) {
        amhw_kl26_port_pin_func_cfg(p_hw_port, pin, AM_KL26_GPIO_FUNC_GET(flags));
    }

    /* �������ŵ�������ģʽ */
    if ((flags & AM_KL26_PORT_PULLEN) != 0) {
        if (AM_KL26_GPIO_PE_GET(flags) == 0) {
            amhw_kl26_port_pin_pull_disable(p_hw_port, pin);
        }
    }

    /* �������ŵ�����ģʽ */
    if ((flags & AM_KL26_PORT_PULLUP) != 0) {
        /* ʹ�����ŵ�����ģʽ */
        if (AM_KL26_GPIO_PULL_GET(flags) == 1) {
            amhw_kl26_port_pin_pull_enable(p_hw_port, pin);
            amhw_kl26_port_pin_pull_up(p_hw_port, pin);

        } else {        /* �������ŵ�����ģʽ */
            amhw_kl26_port_pin_pull_disable(p_hw_port, pin);
            amhw_kl26_port_pin_pull_down(p_hw_port, pin);

        }
    }

    /* ��Ҫ�������ŵ�ת������     */
    if ((flags & AM_KL26_PORT_SLEWSLOW) != 0) {
        /* ����ת�����ʵ� */
        if (AM_KL26_GPIO_SRE_GET(flags) == 1) {
            amhw_kl26_port_pin_slew_slow(p_hw_port, pin);

        } else {      /* ����ת�����ʸ� */
            amhw_kl26_port_pin_slew_fast(p_hw_port, pin);

        }
    }

    /* ��Ҫ�����˲��� */
    if ((flags & AM_KL26_PORT_FILTEREN) != 0) {
        /* ʹ����Դ�˲��� */
        if (AM_KL26_GPIO_PFE_GET(flags) == 1) {
            amhw_kl26_port_pin_filter_enable(p_hw_port, pin);

        } else {     /* ������Դ�˲��� */
            amhw_kl26_port_pin_filter_disable(p_hw_port, pin);

        }
    }

    /* ��Ҫ��������������  */
    if ((flags & AM_KL26_PORT_DRIVERHIGH) != 0) {
        /* �������Ÿ��������� */
        if (AM_KL26_GPIO_DSE_GET(flags) == 1) {
            amhw_kl26_port_pin_drive_high(p_hw_port, pin);

        } else {     /* �������������������� */
            amhw_kl26_port_pin_drive_low(p_hw_port, pin);
        }
    }

    return AM_OK;
}

/**
 * \brief ��ȡ����״̬
 */
int am_gpio_get (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_kl26_gpio_t *p_hw_gpio = p_gpio_devinfo->p_hw_gpio;

    return (int)amhw_kl26_gpio_pin_input_get(p_hw_gpio, pin);
}

/**
 * \brief �����������״̬
 */
int am_gpio_set (int pin, int value)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_kl26_gpio_t *p_hw_gpio = p_gpio_devinfo->p_hw_gpio;

    if (value == 0) {
        amhw_kl26_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_kl26_gpio_pin_out_high(p_hw_gpio, pin);
    }

    return AM_OK;
}

/**
 * \brief ���������ת
 */
int am_gpio_toggle (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_kl26_gpio_t *p_hw_gpio = p_gpio_devinfo->p_hw_gpio;

    amhw_kl26_gpio_pin_out_toggle(p_hw_gpio, pin);

    return AM_OK;
}

/**
 * \brief ���Ŵ�����ʽ����
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_kl26_port_t *p_hw_port = p_gpio_devinfo->p_hw_port;
//    amhw_kl26_gpio_t *p_hw_gpio = p_gpio_devinfo->p_hw_gpio;

    int          port = 0;
    int          slot = -1;
    port = pin >> 5;
    if ((port == 1) || (port > 3)) {
        return -AM_EINVAL;
    }

    if (port == 0) {
        slot = pin;
    } else {
        slot = pin - 32;
    }

    /* ������Ӹ��ж���������ΪGPIO���ܵĺ������� */
    amhw_kl26_port_pin_func_cfg(p_hw_port, pin, KL26_PORT_GPIO);
//
//    /* ���ùܽ�Ϊ���뷽�� */
//    amhw_kl26_gpio_pin_dir_input(p_hw_gpio, pin);
//
//    /* �ܽ���/����ʹ�� */
//    amhw_kl26_port_pin_pull_enable(p_hw_port, pin);
//
//    /* ������������ */
//    amhw_kl26_port_pin_pull_up(p_hw_port, pin);

    switch (flag) {

    case AM_GPIO_TRIGGER_OFF:           /* �رմ��� */
        amhw_kl26_port_pin_irq_disable(p_hw_port, pin);
        break;

    case AM_GPIO_TRIGGER_HIGH:          /* �ߵ�ƽ���� */
        p_gpio_devinfo->p_infomap[slot] = AMHW_KL26_INT_HIGH;
        break;

    case AM_GPIO_TRIGGER_LOW:           /* �͵�ƽ���� */
        p_gpio_devinfo->p_infomap[slot] = AMHW_KL26_INT_LOW;
        break;

    case AM_GPIO_TRIGGER_RISE:          /* �����ش��� */
        p_gpio_devinfo->p_infomap[slot] = AMHW_KL26_INT_RISING;
        break;

    case AM_GPIO_TRIGGER_FALL:          /* �½��ش��� */
        p_gpio_devinfo->p_infomap[slot] = AMHW_KL26_INT_FALLING;
        break;

    case AM_GPIO_TRIGGER_BOTH_EDGES:    /* ˫���ش��� */
        p_gpio_devinfo->p_infomap[slot] = AMHW_KL26_PINT_EITHER;
        break;

    default:
        break;
    }

    /* �������жϱ�־λ */
    amhw_kl26_port_pin_isf_clr(p_hw_port, pin);

    return AM_OK;
}

/**
 * \brief ����״̬�Ĵ���ת��Ϊ�жϺ�
 */
static int __get_inum (uint32_t int_status)
{
    int i = 0;
    if (int_status == 0) {
        return -AM_EINVAL;
    }

    for (i = 0; i < 32; ++i)  {
        if (int_status == 1) {
            break;
        }
        int_status >>= 1;
    }
    return i;
}

/**
 * \brief GPIO �жϷ�����Ӧ������
 * \param[in] p_arg : ��ǰ�ж�ӳ���š�
 * \return ��
 */
static void __port_a_int_isr (void *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_kl26_port_t *p_hw_port = p_gpio_devinfo->p_hw_port;
    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    int         pin_inum=0;

    /* ����ж����ź� */
    pin_inum = __get_inum(p_hw_port->port[0].port_isfr);

    /* ��ȡ�йػص����������� */
    pfn_isr = p_gpio_devinfo->p_triginfo[pin_inum].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[pin_inum].p_arg;

    /* ���жϱ�־ */
    amhw_kl26_port_pin_isf_clr(p_hw_port, pin_inum);

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}


static void __port_cd_int_isr (void *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    am_pfnvoid_t pfn_isr   = NULL;
    amhw_kl26_port_t *p_hw_port = p_gpio_devinfo->p_hw_port;
    void        *p_arg_tmp = NULL;

    int         pin_inum=0;

    pin_inum = __get_inum(p_hw_port->port[2].port_isfr);
    if (pin_inum == -AM_EINVAL) {
        pin_inum = __get_inum(p_hw_port->port[3].port_isfr);
        pin_inum += 32;
    }
    pin_inum += 32;
    /* ��ȡ�йػص����������� */
    pfn_isr = p_gpio_devinfo->p_triginfo[pin_inum].pfn_callback;
    p_arg_tmp   = p_gpio_devinfo->p_triginfo[pin_inum].p_arg;

    /* ���жϱ�־ */
    amhw_kl26_port_pin_isf_clr(p_hw_port, pin_inum + 32);

    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

#if CRP_ENABLE
#include "awbl_stack_overflow_check.h"
#endif

/**
 * \brief ���������жϻص�����
 */
int am_gpio_trigger_connect (int           pin,
                             am_pfnvoid_t  pfn_callback,
                             void         *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    uint32_t     port;
    int          key;
    int          slot      = -1;

#if CRP_ENABLE
    if (0 != awbl_stack_overflow_check() ) {
        volatile int *p = (int *)am_gpio_trigger_connect;
        *p = 0;
    }
#endif

    /** \brief ������Ŷ�Ӧ�����Ŷ˺� */
    port = pin >> 5;
    if ((port == 1) || (port > 3)) {        /*�жϹܽŲ�����*/
        return -AM_EINVAL;
    }

    if (port == 0) {       /* A port*/
        slot = pin;
    } else {
        slot = pin - 32;
    }
    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();

    /*  ���津�����ż��ص����� */
    (p_gpio_devinfo->p_triginfo)[slot].pfn_callback = pfn_callback;
    (p_gpio_devinfo->p_triginfo)[slot].p_arg        = p_arg;

    /* ���ж� */
    am_int_cpu_unlock(key);
    return AM_OK;
}


/**
 * \brief ɾ�������жϻص���������
 */
int am_gpio_trigger_disconnect (int           pin,
                                am_pfnvoid_t  pfn_callback,
                                void         *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int key;
    int slot = -1;
    int port = 0;

    port = pin >> 5;

    if ((port == 1) || (port > 3)) {        /*�жϹܽŲ�����*/
        return -AM_EINVAL;
    }

    if (port == 0) {       /* A port*/
        slot = pin;
    } else {
        slot = pin - 32;
    }

    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();

    (p_gpio_devinfo->p_triginfo)[slot].pfn_callback = NULL;

    /* ��CPU�ж� */
    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief ʹ�������жϡ�
 */
int am_gpio_trigger_on (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    int slot = -1;

    uint32_t port;

    /** \brief ������Ŷ�Ӧ�����Ŷ˺� */
    port = pin >> 5;

    if ((port == 1) || (port > 3)) {    /*�жϹܽŲ�����*/
        return -AM_EINVAL;
    }

    if (port == 0) {       /* A port*/
        slot = pin;
    } else {
        slot = pin - 32;
    }
    amhw_kl26_port_pin_irq_cfg(p_gpio_devinfo->p_hw_port,
                               pin,
                               p_gpio_devinfo->p_infomap[slot]);
    return AM_OK;
}

/**
 * \brief ���������жϡ�
 */
int am_gpio_trigger_off (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_kl26_port_pin_irq_disable(p_gpio_devinfo->p_hw_port, pin);

    return AM_OK;
}

/**
 * \brief GPIO��ʼ��
 */
int am_kl26_gpio_init (am_kl26_gpio_dev_t           *p_dev,
                       const am_kl26_gpio_devinfo_t *p_devinfo)
{
    int i = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return -AM_EINVAL;
    }

    p_dev->p_devinfo  = p_devinfo;
    __gp_gpio_dev     = p_dev;
    p_dev->valid_flg  = AM_TRUE;

    if ((p_devinfo->p_triginfo == NULL) ||
        (p_devinfo->p_infomap == NULL)) {
        p_dev->valid_flg = AM_FALSE;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* �жϱ���� */
    if (p_dev->valid_flg) {
        for (i = 0; i < p_devinfo->pint_count; i++) {
            (p_devinfo->p_infomap)[i]               = AM_KL26_GPIO_INVALID_PIN_MAP;
            (p_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

    am_int_connect((p_devinfo->inum_pin)[0], /* д���жϺ� */
                   (am_pfnvoid_t)__port_a_int_isr,
                   (void *)p_devinfo);
    am_int_connect((p_devinfo->inum_pin)[1], /* д���жϺ� */
                   (am_pfnvoid_t)__port_cd_int_isr,
                   (void *)p_devinfo);

    am_int_enable(p_devinfo->inum_pin[0]);
    am_int_enable(p_devinfo->inum_pin[1]);

    return AM_OK;
}

/**
 * \brief GPIOȥ��ʼ��
 */
void am_kl26_gpio_deinit (void)
{
    int i = 0;

    const am_kl26_gpio_devinfo_t *p_gpio_devinfo = NULL;

    if (__gp_gpio_dev == NULL) {
        return;
    }

    p_gpio_devinfo = __gp_gpio_dev->p_devinfo;

    if (__gp_gpio_dev->valid_flg) {
        for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
            (p_gpio_devinfo->p_infomap)[i]               = AM_KL26_GPIO_INVALID_PIN_MAP;
            (p_gpio_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

    for (i = 0; i < 2; i++) {
        am_int_disable((p_gpio_devinfo->inum_pin)[i]);
    }

    am_int_disconnect((p_gpio_devinfo->inum_pin)[0], /* д���жϺ� */
                   (am_pfnvoid_t)__port_a_int_isr,
                   (void *)p_gpio_devinfo);
    am_int_disconnect((p_gpio_devinfo->inum_pin)[1], /* д���жϺ� */
                   (am_pfnvoid_t)__port_cd_int_isr,
                   (void *)p_gpio_devinfo);

    if (p_gpio_devinfo->pfn_plfm_deinit) {
        p_gpio_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
