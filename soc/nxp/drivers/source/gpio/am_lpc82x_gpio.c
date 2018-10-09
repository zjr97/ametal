/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief GPIO implementation
 * 
 * - GPIO�����ܹ�ͨ���������Ϊ������������
 * - ��λ������GPIO����Ĭ���������ҹر��жϣ�
 * - ���żĴ����������ŵ������á�
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-27  mem,modified.
 * - 1.01 15-07-28  zxl,modified.
 * - 1.00 15-07-10  zxl, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_gpio_util.h"
#include "am_lpc82x.h"
#include "am_lpc82x_gpio.h"
#include "am_lpc82x_gpio_util.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "hw/amhw_lpc82x_gpio.h"
#include "hw/amhw_lpc82x_iocon.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_swm.h"
#include "lpc82x_pin.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define __GPIO_INVALID_PIN_MAP    0xFF

/** \brief δ���ÿ����ù��ܱ�ʶ */
#define __GPIO_NO_MOVED_FUNC      0xFF

/** \brief ����ָ��GPIO�豸��Ϣ��ָ�� */
#define __GPIO_DEVINFO_DECL(p_devinfo, p_dev)  \
        const am_lpc82x_gpio_devinfo_t *p_devinfo = p_dev->p_devinfo

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
am_lpc82x_gpio_dev_t *__gp_gpio_dev = NULL;

/*******************************************************************************
  ��������
*******************************************************************************/

/**
 * \brief ���Ź�������
 *
 * \param[in] pin   : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] flags : �����룬Ϊam_gpio.h,lpc8xx_pin.h�ĺ궨��
 *
 */
int am_gpio_pin_cfg (int pin, uint32_t flags)
{
    uint32_t func, mode;
    uint32_t iocon_cfg;
    
    const am_lpc82x_gpio_devinfo_t *p_devinfo  = NULL;
    amhw_lpc82x_gpio_t             *p_hw_gpio  = NULL; 
    amhw_lpc82x_iocon_t            *p_hw_iocon = NULL;
    amhw_lpc82x_swm_t              *p_hw_swm   = NULL;
    
    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }
    
    p_devinfo  = __gp_gpio_dev->p_devinfo;
    p_hw_gpio  = (amhw_lpc82x_gpio_t*)p_devinfo->gpio_regbase; 
    p_hw_iocon = (amhw_lpc82x_iocon_t*)p_devinfo->iocon_regbase;
    p_hw_swm   = (amhw_lpc82x_swm_t*)p_devinfo->swm_regbase;
            
    /* ��ȡԭIOCON���� */
    iocon_cfg = amhw_lpc82x_iocon_pio_get(p_hw_iocon, pin);
    
    /* ��ȡ��׼�㶨�����Ϣ */
    func = AM_GPIO_COM_FUNC_GET(flags);
    mode = AM_GPIO_COM_MODE_GET(flags);

    /**
     * \brief ���й������ã����ȼ��ߣ�
     */
    if (func != 0x00) {
        
        /* ��������LPC8xx���й��� */
        AM_BIT_CLR_MASK(flags, AM_LPC82X_GPIO_FUNC_MASK);
            
        /* ����������GPIO״̬ */
        
        /* ���֮ǰ�������õĿ�ת�ƹ��ܣ���ȡ�� */
        if (__gp_gpio_dev->pin_moved_func[pin] != __GPIO_NO_MOVED_FUNC) {

            amhw_lpc82x_swm_moved_func_cfg(p_hw_swm,
                                          (amhw_lpc82x_swm_moved_func_t)\
                                          (__gp_gpio_dev->pin_moved_func[pin]),
                                          __GPIO_NO_MOVED_FUNC);

            /* ��¼����ǰ����û�����ÿ����ù��� */
            __gp_gpio_dev->pin_moved_func[pin] = __GPIO_NO_MOVED_FUNC;
        }
        
        amhw_lpc82x_swm_pin_fixed_func_disable(p_hw_swm, pin);

        switch (func) {

        case AM_GPIO_INPUT:
            amhw_lpc82x_gpio_pin_dir_input(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_HIGH:
            amhw_lpc82x_gpio_pin_out_high(p_hw_gpio, pin);
            amhw_lpc82x_gpio_pin_dir_output(p_hw_gpio, pin);
            
            break;

        case AM_GPIO_OUTPUT_INIT_LOW:
            amhw_lpc82x_gpio_pin_out_low(p_hw_gpio, pin);
            amhw_lpc82x_gpio_pin_dir_output(p_hw_gpio, pin);

            break;

        default:
            break;
        }
    }

    if (mode != 0x00) {
        
        if (mode < AM_GPIO_OPEN_DRAIN_VAL) {
            
            /* �����м�ģʽ */
            AM_BIT_CLR_MASK(flags, AM_LPC82X_GPIO_REP_MASK);
            
            /* �����©ģʽ */
            AM_BIT_CLR(iocon_cfg, 10);
            
            AM_BIT_CLR_MASK(iocon_cfg, AM_SBF(0x3, 3));
            iocon_cfg |= (((~mode) & 0x3) << 3);

          /* ���ÿ�©ģʽ */
        } else if (mode == AM_GPIO_OPEN_DRAIN_VAL) {
            AM_BIT_SET(iocon_cfg, 10);

          /* ����ģʽ��֧��  */
        } else if (mode > AM_GPIO_OPEN_DRAIN_VAL) {
            return -AM_ENOTSUP;
        }
    }

    /**
     * \brief ƽ̨��������
     */

    /* ��Ҫ�������Ź��� */
    if ((flags & AM_LPC82X_GPIO_FUNC_MASK) != 0) {
        
        /* ���֮ǰ�������õĿ�ת�ƹ��ܣ���ȡ�� */
        if (__gp_gpio_dev->pin_moved_func[pin] != __GPIO_NO_MOVED_FUNC) {
            amhw_lpc82x_swm_moved_func_cfg(
                                       p_hw_swm,
                                       (amhw_lpc82x_swm_moved_func_t)(
                                       __gp_gpio_dev->pin_moved_func[pin]),
                                       __GPIO_NO_MOVED_FUNC);    
            
            __gp_gpio_dev->pin_moved_func[pin] = __GPIO_NO_MOVED_FUNC;
        }
        
        amhw_lpc82x_swm_pin_fixed_func_disable(p_hw_swm, pin);

        /* ���⹦������ */
        if (AM_LPC82X_GPIO_FUNC_GET(flags) > 
            AM_LPC82X_GPIO_FUNC_GET(AM_LPC82X_GPIO_FUNC_GPIO)) {

            amhw_lpc82x_swm_pin_fixed_func_enable(
                p_hw_swm, 
                pin, 
                AM_LPC82X_GPIO_FUNC_CODE(AM_LPC82X_GPIO_FUNC_GET(flags)));

        /* ��ת�ƹ��� */
        }else if (AM_LPC82X_GPIO_FUNC_GET(flags) <
                  AM_LPC82X_GPIO_FUNC_GET(AM_LPC82X_GPIO_FUNC_GPIO)) {
            
            /* �洢��ǰ�������õĹ��� */
            __gp_gpio_dev->pin_moved_func[pin] = AM_LPC82X_GPIO_FUNC_GET(flags);

            amhw_lpc82x_swm_moved_func_cfg(
                p_hw_swm,
                (amhw_lpc82x_swm_moved_func_t)AM_LPC82X_GPIO_FUNC_GET(flags), 
                pin);
        }
    }

    /* ��Ҫ����Ϊ�м�ģʽ */
    if ((flags & AM_LPC82X_GPIO_REP_MASK) != 0) {
             AM_BIT_SET_MASK(iocon_cfg, AM_SBF(0x3, 3));
    }

    /* ��Ҫ�������ų��� */
    if ((flags & AM_LPC82X_GPIO_HYS_MASK) != 0) {
        AM_BIT_CLR(iocon_cfg, 5);
        AM_BIT_SET_MASK(iocon_cfg, AM_SBF(AM_LPC82X_GPIO_HYS_GET(flags), 5));
    }

    /* ��Ҫ�����������뷴ת */
    if ((flags & AM_LPC82X_GPIO_INV_MASK) != 0) {
        AM_BIT_CLR(iocon_cfg, 6);
        AM_BIT_SET_MASK(iocon_cfg, AM_SBF(AM_LPC82X_GPIO_INV_GET(flags), 6));
    }

    /* ��Ҫ��������I2Cģʽ  */
    if ((flags & AM_LPC82X_GPIO_I2C_MASK) != 0) {
        AM_BIT_CLR_MASK(iocon_cfg, AM_SBF(0x3, 8));
        AM_BIT_SET_MASK(iocon_cfg ,AM_SBF(AM_LPC82X_GPIO_I2C_GET(flags), 8));
    }

    /* ��Ҫ���������˲����� */
    if ((flags & AM_LPC82X_GPIO_FIL_CYC_MASK) != 0) {
        AM_BIT_CLR_MASK(iocon_cfg, AM_SBF(0x7, 11));
        AM_BIT_SET_MASK(iocon_cfg,
                        AM_SBF(AM_LPC82X_GPIO_FIL_CYC_GET(flags), 
                        11));
    }

    /* ��Ҫ���������˲���Ƶ */
    if ((flags & AM_LPC82X_GPIO_FIL_DIV_MASK) != 0) {
        AM_BIT_CLR_MASK(iocon_cfg, AM_SBF(0xF, 13));
        AM_BIT_SET_MASK(iocon_cfg, 
                        AM_SBF(AM_LPC82X_GPIO_FIL_DIV_GET(flags),
                        13));
    }

    /* ����ICON��Ϣ */
    amhw_lpc82x_iocon_pio_cfg(p_hw_iocon, pin, iocon_cfg);

    return AM_OK;
}


/** \brief ��ȡ����״̬ */
int am_gpio_get (int pin)
{
    amhw_lpc82x_gpio_t *p_hw_gpio  = NULL;
    
    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }
    
    p_hw_gpio = (amhw_lpc82x_gpio_t*)__gp_gpio_dev->p_devinfo->gpio_regbase;
    
    return amhw_lpc82x_gpio_pin_level_get(p_hw_gpio, pin);
}

/** \brief �����������״̬ */
int am_gpio_set (int pin, int value)
{
    amhw_lpc82x_gpio_t *p_hw_gpio  = NULL;
        
    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio = (amhw_lpc82x_gpio_t*)__gp_gpio_dev->p_devinfo->gpio_regbase;
    amhw_lpc82x_gpio_pin_out_set(p_hw_gpio, pin, value);

    return AM_OK;
}

/** \brief �������״̬��ת */
int am_gpio_toggle (int pin)
{
    amhw_lpc82x_gpio_t *p_hw_gpio  = NULL;
    
    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio = (amhw_lpc82x_gpio_t*)__gp_gpio_dev->p_devinfo->gpio_regbase;
    amhw_lpc82x_gpio_pin_out_tog(p_hw_gpio, pin);

    return AM_OK;
}

/**
 * \brief ���Ŵ�����ʽѡ��
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{   
    int i;
    int slot = -1;
    
    const am_lpc82x_gpio_devinfo_t *p_devinfo  = NULL;
    amhw_lpc82x_pint_t             *p_hw_pint  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_devinfo = __gp_gpio_dev->p_devinfo;
    p_hw_pint = (amhw_lpc82x_pint_t *)p_devinfo->pint_regbase; 
    
    for (i = 0; i < p_devinfo->pint_count; i++) {
        if ((p_devinfo->p_infomap)[i] == pin) {
            slot = i;
            break;
        }
    }

    if (slot == -1) {
        return -AM_ENXIO;
    }

    /* ��������ŵ��������½��ؼ�� */
    amhw_lpc82x_pint_edge_dec_clr(p_hw_pint, slot);

    switch (flag) {
        
    case AM_GPIO_TRIGGER_OFF:          /* �رմ��� */
        amhw_lpc82x_pint_trigger_set(p_hw_pint, 
                                          slot, 
                                          AMHW_LPC82X_PINT_TRIGGER_OFF);
        break;

    case AM_GPIO_TRIGGER_HIGH:         /* �ߵ�ƽ���� */
        amhw_lpc82x_pint_trigger_set(p_hw_pint, 
                                          slot, 
                                          AMHW_LPC82X_PINT_TRIGGER_HIGH);
        break;

    case AM_GPIO_TRIGGER_LOW:          /* �͵�ƽ���� */
        amhw_lpc82x_pint_trigger_set(p_hw_pint, 
                                          slot, 
                                          AMHW_LPC82X_PINT_TRIGGER_LOW);
        break;

    case AM_GPIO_TRIGGER_RISE:         /* �����ش��� */
        amhw_lpc82x_pint_trigger_set(p_hw_pint, 
                                          slot, 
                                          AMHW_LPC82X_PINT_TRIGGER_RISE);
        break;

    case AM_GPIO_TRIGGER_FALL:         /* �½��ش��� */
        amhw_lpc82x_pint_trigger_set(p_hw_pint, 
                                          slot, 
                                          AMHW_LPC82X_PINT_TRIGGER_FALL);
        break;

    case AM_GPIO_TRIGGER_BOTH_EDGES:   /* ˫���ش��� */
        amhw_lpc82x_pint_trigger_set(p_hw_pint, 
                                          slot, 
                                     AMHW_LPC82X_PINT_TRIGGER_BOTH_EDGES);
        break;

    default:
        break;
    }

    return AM_OK;
}

/**
 * \brief GPIO �жϷ�����Ӧ������
 * \param[in] p_arg : ��ǰ�ж�ӳ���š�
 */
static void __gpio_eint_isr (void *p_arg)
{
    int          slot      = (int)p_arg;
    am_pfnvoid_t pfn_isr   = NULL;
    
    const am_lpc82x_gpio_devinfo_t *p_devinfo  = NULL;
    amhw_lpc82x_pint_t             *p_hw_pint  = NULL;
    
    if (__gp_gpio_dev == NULL) {
        return;
    }
    
    p_devinfo = __gp_gpio_dev->p_devinfo;
    p_hw_pint = (amhw_lpc82x_pint_t *)p_devinfo->pint_regbase; 

    /* ����Ǳ������д�����������ؼ�� */
    if ((p_hw_pint->isel & AM_BIT(slot)) == 0) {
        p_hw_pint->ist = AM_BIT(slot); 
    }

    /* ��ȡ�йػص����������� */
    pfn_isr = p_devinfo->p_triginfo[slot].pfn_callback;
    p_arg   = p_devinfo->p_triginfo[slot].p_arg;

    if (pfn_isr != NULL) {
        pfn_isr(p_arg);
    }
}

/**
 * \brief ���������жϻص�����
 */
int am_gpio_trigger_connect (int           pin,
                             am_pfnvoid_t  pfn_callback,
                             void         *p_arg)
{
    int          key;
    int          i;
    int          slot      = -1;
    int          err       = AM_OK;
    am_bool_t    already   = AM_FALSE;

    const am_lpc82x_gpio_devinfo_t *p_devinfo  = NULL;
    
    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }
    
    p_devinfo = __gp_gpio_dev->p_devinfo;
    
    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();
    
    for (i = 0; i < p_devinfo->pint_count; i++) {
        if ((p_devinfo->p_infomap)[i] == __GPIO_INVALID_PIN_MAP) {
            slot = i;
            break;
        }
        if (p_devinfo->p_infomap[i] == pin) {
            already = AM_TRUE;
            break;
        }
    }

    if (already) {

        /* ��CPU�ж� */
        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }

    if (-1 != slot) {
        err = am_int_connect((p_devinfo->inum_pin)[slot],
                             (am_pfnvoid_t)__gpio_eint_isr,
                             (void *)slot);

        /*  ���津�����ż��ص����� */
        if (AM_OK == err) {
            (p_devinfo->p_infomap)[slot]               = pin;
            (p_devinfo->p_triginfo)[slot].pfn_callback = pfn_callback;
            (p_devinfo->p_triginfo)[slot].p_arg        = p_arg;
        }

        amhw_lpc82x_syscon_pint_sel(slot, pin);

        /* ��CPU�ж� */
        am_int_cpu_unlock(key);
    }

    /* ��CPU�ж� */
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
    int key;
    int i;
    int slot = -1;
    
    const am_lpc82x_gpio_devinfo_t *p_devinfo  = NULL;
        
    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_devinfo = __gp_gpio_dev->p_devinfo;
    
    /* �ر�CPU�ж� */  
    key = am_int_cpu_lock();
    
    for (i = 0; i < p_devinfo->pint_count; i++) {
        if ((p_devinfo->p_infomap)[i] == pin) {
            slot = i;
            break;
        }
    }

    if (slot == -1 || 
       ((p_devinfo->p_triginfo)[slot].pfn_callback != pfn_callback)) {

        /* ��CPU�ж� */ 
        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }

    am_int_disconnect((p_devinfo->inum_pin)[slot],
                      (am_pfnvoid_t)__gpio_eint_isr,
                      (void *)slot);

    (p_devinfo->p_infomap)[slot]               = __GPIO_INVALID_PIN_MAP;
    (p_devinfo->p_triginfo)[slot].pfn_callback = NULL;

    /* ��CPU�ж� */ 
    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief ʹ�������ж�
 */
int am_gpio_trigger_on (int pin)
{
    int key;
    int i;
    int slot = -1;
    
    const am_lpc82x_gpio_devinfo_t *p_devinfo  = NULL;
    
    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }
    
    p_devinfo = __gp_gpio_dev->p_devinfo;
    
    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();

    for (i = 0; i < p_devinfo->pint_count; i++) {
        if ((p_devinfo->p_infomap)[i] == pin) {
            slot = i;
            break;
        }
    }

    /* ��CPU�ж�t */ 
    am_int_cpu_unlock(key);

    if (slot == -1) {
        return -AM_ENXIO;
    }

    return am_int_enable((p_devinfo->inum_pin)[slot]);
}

/**
 * \brief ���������ж�
 */
int am_gpio_trigger_off (int pin)
{
    int key;
    int i;
    int slot = -1;

    const am_lpc82x_gpio_devinfo_t *p_devinfo  = NULL;
    
    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }
    
    p_devinfo = __gp_gpio_dev->p_devinfo;

    /* �ر�CPU�ж� */ 
    key = am_int_cpu_lock();
    
    for (i = 0; i < p_devinfo->pint_count; i++) {
        if ((p_devinfo->p_infomap)[i] == pin) {
            slot = i;
            break;
        }
    }

    /* ��CPU�ж� */
    am_int_cpu_unlock(key);

    if (slot == -1) {
        return -AM_ENXIO;
    }

    return am_int_disable((p_devinfo->inum_pin)[slot]);
}

/**
 * \brief GPIO��ʼ��
 */
int am_lpc82x_gpio_init (am_lpc82x_gpio_dev_t           *p_dev, 
                         const am_lpc82x_gpio_devinfo_t *p_devinfo)
{
    int i;

    if (p_dev == NULL || p_devinfo == NULL) {
        return -AM_EINVAL;
    }
    
    if (__gp_gpio_dev != NULL) {
        return -AM_EPERM;
    }
    
    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo  = p_devinfo;
    __gp_gpio_dev     = p_dev;
    p_dev->valid_flg  = AM_TRUE;

    if ((p_devinfo->p_triginfo == NULL) ||
        (p_devinfo->p_infomap == NULL)) {
        p_dev->valid_flg = AM_FALSE;
    }

    if (p_dev->valid_flg) {
        for (i = 0; i < p_devinfo->pint_count; i++) {
            (p_devinfo->p_infomap)[i]               = __GPIO_INVALID_PIN_MAP;
            (p_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

    /* ��ʼ�����Ź��ܱ� */
    for (i = 0; i < LPC82X_PIN_NUM; i++) {
        p_dev->pin_moved_func[i] = __GPIO_NO_MOVED_FUNC;
    }

    return AM_OK;
}

/**
 * \brief GPIOȥ��ʼ��
 */
void am_lpc82x_gpio_deinit (void)
{
    int i;
    const am_lpc82x_gpio_devinfo_t *p_devinfo = NULL;
        
    if (__gp_gpio_dev == NULL) {
        return;
    }
    
    p_devinfo = __gp_gpio_dev->p_devinfo;
    
    if (__gp_gpio_dev->valid_flg) {
        for (i = 0; i < p_devinfo->pint_count; i++) {
            (p_devinfo->p_infomap)[i]               = 0;
            (p_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

    for (i = 0; i < p_devinfo->pint_count; i++) {
        am_int_disable((p_devinfo->inum_pin)[i]);
    }
    
    for (i = 0; i < LPC82X_PIN_NUM; i++) {
        __gp_gpio_dev->pin_moved_func[i] = __GPIO_NO_MOVED_FUNC;
    }

    /* �ָ����ؾ���Ĵ������� */
    amhw_lpc82x_swm_reset(LPC82X_SWM);
    
    if (__gp_gpio_dev->p_devinfo->pfn_plfm_deinit) {
        __gp_gpio_dev->p_devinfo->pfn_plfm_deinit();
    }
    __gp_gpio_dev = NULL;
}

/* end of file */
