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
 * \brief GPIO����������GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  zcb,first implementation
 * \endinternal
 */

#include "am_zlg217_gpio.h"
#include "am_gpio_util.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_bitops.h"
#include "am_zlg217_gpio_util.h"
#include "amhw_zlg217_afio.h"
#include "amhw_zlg217_exti.h"
#include "zlg217_pin.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define AM_ZLG217_GPIO_INVALID_PIN_MAP    0xFF

/** \brief ����ָ��GPIO�豸��Ϣ��ָ�� */
#define __GPIO_DEVINFO_DECL(p_gpio_devinfo, p_dev)  \
        const am_zlg217_gpio_devinfo_t *p_gpio_devinfo = p_dev->p_devinfo

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
am_zlg217_gpio_dev_t *__gp_gpio_dev;

/*******************************************************************************
  ��������
*******************************************************************************/

static int __am_zlg217_peripheral_remap_clear(int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_zlg217_afio_remap_peripheral_t peripheral;
    amhw_zlg217_afio_t                  *p_hw_afio;
    uint8_t i = 0;

    if (NULL == p_gpio_devinfo) {
        return -AM_ENXIO;
    }

    p_hw_afio  = (amhw_zlg217_afio_t *)p_gpio_devinfo->afio_regbase;
    peripheral = p_gpio_devinfo->p_remap[pin];

    if (peripheral == AMHW_ZLG217_NO_REMAP) {
        return -AM_ENXIO;
    }

    /* JATG / SWD ����ѡ���Թر� */
    if (peripheral != AMHW_ZLG217_SWJ_CFG) {

        /*
         * ��������GPIO����ӳ��ĸ�������ȫ������ΪAMHW_ZLG217_NO_REMAP
         * ������������������û����ӳ��
         */

        for (i = 0 ; i < p_gpio_devinfo->pin_count ; i++) {
            if (p_gpio_devinfo->p_remap[i] == peripheral) {
                p_gpio_devinfo->p_remap[i] = AMHW_ZLG217_NO_REMAP;
            }
        }

    } else {
        /*
         * JTMS/SWDIO -- PA13   JTCK/SWCLK    -- PA14
         * JTDI       -- PA15   JTDO/TRACESWO -- PB3
         * JNTRST     -- PB4
         *
         * 0  --  �޿�������
         * 1  --  PB4
         * 2  --  PB3/PB4/PA15
         * 7  --  PB3/PB4/PA15/PA14/PA13
         */
        if ((PIOA_13 == pin) || (PIOA_14 == pin)) {

            amhw_zlg217_afio_swj_cfg_remap_mode_set(p_hw_afio, AMHW_ZLG217_AFIO_SWJ_CFG_7);

            /* ���������ӳ����Ϣ */
            for (i = PIOA_13 ; i < PIOB_5 ; i++) {
                if (p_gpio_devinfo->p_remap[i] == AMHW_ZLG217_SWJ_CFG) {
                    p_gpio_devinfo->p_remap[i] = AMHW_ZLG217_NO_REMAP;
                }
            }

            /* ���ʹ��A15/B3 ��ģʽ����λ��7 */
        } else if (((PIOA_15 == pin) || (PIOB_3 == pin)) &&
                 (p_gpio_devinfo->p_remap[PIOA_13] != AMHW_ZLG217_NO_REMAP)){

            amhw_zlg217_afio_swj_cfg_remap_mode_set(p_hw_afio, AMHW_ZLG217_AFIO_SWJ_CFG_2);

            /* ���������ӳ����Ϣ */
            p_gpio_devinfo->p_remap[PIOB_3]  = AMHW_ZLG217_NO_REMAP;
            p_gpio_devinfo->p_remap[PIOB_4]  = AMHW_ZLG217_NO_REMAP;
            p_gpio_devinfo->p_remap[PIOA_15] = AMHW_ZLG217_NO_REMAP;

        } else if ((PIOB_4 == pin) &&
                 (p_gpio_devinfo->p_remap[PIOB_3] != AMHW_ZLG217_NO_REMAP)) {

            amhw_zlg217_afio_swj_cfg_remap_mode_set(p_hw_afio, AMHW_ZLG217_AFIO_SWJ_CFG_1);

            /* ���������ӳ����Ϣ */
            p_gpio_devinfo->p_remap[PIOB_4]  = AMHW_ZLG217_NO_REMAP;
        }
    }

    /* �ر�������ӳ�� */
    switch (peripheral) {

    case AMHW_ZLG217_SPI1_REMAP:
        amhw_zlg217_afio_spi1_pin_remap_disable(p_hw_afio);
        break;

    case AMHW_ZLG217_I2C1_REMAP:
        amhw_zlg217_afio_i2c1_pin_remap_disable(p_hw_afio);
        break;

    case AMHW_ZLG217_UART1_REMAP:
        amhw_zlg217_afio_uart_pin_remap_disable(p_hw_afio, 1);
        break;

    case AMHW_ZLG217_UART3_REMAP:
        amhw_zlg217_afio_uart_pin_remap_disable(p_hw_afio, 3);
        break;

    case AMHW_ZLG217_TIM1_REMAP:
        amhw_zlg217_afio_tim1_pin_remap_disable(p_hw_afio);
        break;

    case AMHW_ZLG217_PD01_REMAP:
        amhw_zlg217_afio_pd01_pin_remap_disable(p_hw_afio);
        break;

    case AMHW_ZLG217_TIM2_REMAP:
        amhw_zlg217_afio_tim2_remap_mode_set(p_hw_afio, AMHW_ZLG217_AFIO_TIM2_REMAP_NO);
        break;

    case AMHW_ZLG217_TIM3_REMAP:
        amhw_zlg217_afio_tim3_remap_mode_set(p_hw_afio ,AMHW_ZLG217_AFIO_TIM3_REMAP_NO);
        break;

    case AMHW_ZLG217_CAN_REMAP:
        amhw_zlg217_afio_can_remap_mode_set(p_hw_afio ,AMHW_ZLG217_AFIO_CAN_RX_PA11_TX_PA12);
        break;

    case AMHW_ZLG217_SWJ_CFG:
        break;

    default:
        return -AM_ENOTSUP;
    }

    return AM_OK;
}

/**
 * \brief ���Ź�������
 *
 * \param[in] pin   : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] flags : ���Ź���
 *
 * \return AM_OK �����óɹ�
 */
int am_gpio_pin_cfg (int pin, uint32_t flags)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_zlg217_gpio_t     *p_hw_gpio  = NULL;
    amhw_zlg217_afio_t     *p_hw_afio  = NULL;
    amhw_zlg217_gpiomode_t  pin_mode   = AMHW_ZLG217_GPIO_MODE_AIN;
    uint32_t                func = 0, mode = 0;
    /* IO�ڷ��� */
    uint8_t dir = 0;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (AM_FALSE == __gp_gpio_dev->valid_flg) {
        return -AM_ENODEV;
    }

    p_hw_gpio  = (amhw_zlg217_gpio_t *)p_gpio_devinfo->gpio_regbase;
    p_hw_afio  = (amhw_zlg217_afio_t *)p_gpio_devinfo->afio_regbase;

    func = AM_GPIO_COM_FUNC_GET(flags);
    mode = AM_GPIO_COM_MODE_GET(flags);

    /* ��׼����� */
    if (0 != func) {

        /* ʹ�ñ�׼��ǰ���˻�����ΪGPIOģʽ */
        __am_zlg217_peripheral_remap_clear(pin);

        switch (func) {

        case AM_GPIO_INPUT_VAL:
            /* ���÷���Ϊ���� */
            amhw_zlg217_gpio_pin_dir_input(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_HIGH_VAL:
            /* �������ģʽ����û��������Ĭ��Ϊ50Mhz */
            if (0 == (flags & AM_ZLG217_GPIO_OUTRES_RATE)) {
                amhw_zlg217_gpio_pin_dir_output(p_hw_gpio,
                                                AMHW_ZLG217_GPIO_SPEED_50MHz,
                                                pin);
            } else {
                amhw_zlg217_gpio_pin_dir_output(
                    p_hw_gpio,
                    (amhw_zlg217_gpio_speed_mode_t)AM_ZLG217_GPIO_OUTRES_RATE_GET(flags),
                    pin);
            }
            /* ����ߵ�ƽ */
            amhw_zlg217_gpio_pin_out_high(p_hw_gpio, pin);
            /* ������� */
            amhw_zlg217_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_ZLG217_GPIO_MODE_OUT_PP,
                                          pin);
            break;

        case AM_GPIO_OUTPUT_INIT_LOW_VAL:
            /* �������ģʽ����û��������Ĭ��Ϊ50Mhz */
            if (0 == (flags & AM_ZLG217_GPIO_OUTRES_RATE)) {
                amhw_zlg217_gpio_pin_dir_output(p_hw_gpio,
                                                AMHW_ZLG217_GPIO_SPEED_50MHz,
                                                pin);
            } else {
                amhw_zlg217_gpio_pin_dir_output(
                    p_hw_gpio,
                    (amhw_zlg217_gpio_speed_mode_t)AM_ZLG217_GPIO_OUTRES_RATE_GET(flags),
                    pin);
            }
            /* ����͵�ƽ */
            amhw_zlg217_gpio_pin_out_low(p_hw_gpio, pin);
            /* ������� */
            amhw_zlg217_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_ZLG217_GPIO_MODE_OUT_PP,
                                          pin);
            break;

        default:
            return -AM_ENOTSUP;
        }
    }

    if (mode != 0x00) {

        /* ��ȡ����������� */
        dir = amhw_zlg217_gpio_pin_dir_get(p_hw_gpio, pin);

        switch (mode) {

        case AM_GPIO_PULL_UP_VAL:
            if (dir != 1) {

                /* ʹODλ��Ϊ1, ���������� */
                amhw_zlg217_gpio_pin_out_high(p_hw_gpio, pin);

                pin_mode = AMHW_ZLG217_GPIO_MODE_IPU;
            } else {

                /* ���û������ģʽ������Ϊ����ģʽ */
                pin_mode = AMHW_ZLG217_GPIO_MODE_OUT_PP;
            }
            break;

        case AM_GPIO_PULL_DOWN_VAL:
            if (dir != 1) {

                /* ʹODλ��Ϊ0, ���������� */
                amhw_zlg217_gpio_pin_out_low(p_hw_gpio, pin);
                pin_mode = AMHW_ZLG217_GPIO_MODE_IPD;
            } else {

                /* ���û������ģʽ������Ϊ����ģʽ */
                pin_mode = AMHW_ZLG217_GPIO_MODE_OUT_PP;
            }
            break;

        case AM_GPIO_FLOAT_VAL:
            if (dir != 1) {
                pin_mode = AMHW_ZLG217_GPIO_MODE_IN_FLOATING;
            } else {

                /* ���û�и���ģʽ������Ϊ��©ģʽ */
                pin_mode = AMHW_ZLG217_GPIO_MODE_OUT_OD;
            }
            break;

        case AM_GPIO_OPEN_DRAIN_VAL:
            if (dir == 0) {
                /* ����û�п�©ģʽ������Ϊ���� */
                pin_mode = AMHW_ZLG217_GPIO_MODE_IN_FLOATING;
            } else {
                pin_mode = AMHW_ZLG217_GPIO_MODE_OUT_OD;
            }
            break;

        case AM_GPIO_PUSH_PULL_VAL:
            if (dir == 0) {
                /* ����û������ģʽ������Ϊ���� */
                pin_mode = AMHW_ZLG217_GPIO_MODE_IPU;
            } else {
                pin_mode = AMHW_ZLG217_GPIO_MODE_OUT_PP;
            }
            break;

        default:
            return -AM_ENOTSUP;
        }

        amhw_zlg217_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /* ƽ̨��� */
    if (0 != (flags & AM_ZLG217_GPIO_MODE)) {

        /* ���������Ӧģʽ���� */

        switch (AM_ZLG217_GPIO_MODE_GET(flags)) {

        case 0:
            /* ����Ϊ���� */
            amhw_zlg217_gpio_pin_dir_input(p_hw_gpio, pin);
            pin_mode = AMHW_ZLG217_GPIO_MODE_AIN;
            break;

        case 1:
            /* ����Ϊ���� */
            amhw_zlg217_gpio_pin_dir_input(p_hw_gpio, pin);
            pin_mode = AMHW_ZLG217_GPIO_MODE_IN_FLOATING;
            break;

        case 2:
            /* ʹODλ��Ϊ0, ���������� */
            amhw_zlg217_gpio_pin_out_low(p_hw_gpio, pin);
            /* ����Ϊ���� */
            amhw_zlg217_gpio_pin_dir_input(p_hw_gpio, pin);
            pin_mode = AMHW_ZLG217_GPIO_MODE_IPD;
            break;

        case 3:
            /* ʹODλ��Ϊ1, ���������� */
            amhw_zlg217_gpio_pin_out_high(p_hw_gpio, pin);
            /* ����Ϊ���� */
            amhw_zlg217_gpio_pin_dir_input(p_hw_gpio, pin);
            pin_mode = AMHW_ZLG217_GPIO_MODE_IPU;
            break;

        case 4:
            /* ����Ϊ�����������ӦƵ�ʣ�Ĭ��Ϊ50Mhz */
            if (0 != (flags & AM_ZLG217_GPIO_OUTRES_RATE)) {
                amhw_zlg217_gpio_pin_dir_output(
                    p_hw_gpio,
                    (amhw_zlg217_gpio_speed_mode_t)AM_ZLG217_GPIO_OUTRES_RATE_GET(flags),
                    pin);
            } else {
                amhw_zlg217_gpio_pin_dir_output(p_hw_gpio,
                                                AMHW_ZLG217_GPIO_SPEED_50MHz,
                                                pin);
            }
            pin_mode = AMHW_ZLG217_GPIO_MODE_OUT_PP;
            break;

        case 5:
            /* ����Ϊ�����������ӦƵ�ʣ�Ĭ��Ϊ50Mhz */
            if (0 != (flags & AM_ZLG217_GPIO_OUTRES_RATE)) {
                amhw_zlg217_gpio_pin_dir_output(
                    p_hw_gpio,
                    (amhw_zlg217_gpio_speed_mode_t)AM_ZLG217_GPIO_OUTRES_RATE_GET(flags),
                    pin);
            } else {
                amhw_zlg217_gpio_pin_dir_output(p_hw_gpio,
                                                AMHW_ZLG217_GPIO_SPEED_50MHz,
                                                pin);
            }
            pin_mode = AMHW_ZLG217_GPIO_MODE_OUT_OD;
            break;

        case 6:
            /* ����Ϊ�����������ӦƵ�ʣ�Ĭ��Ϊ50Mhz */
            if (0 != (flags & AM_ZLG217_GPIO_OUTRES_RATE)) {
                amhw_zlg217_gpio_pin_dir_output(
                    p_hw_gpio,
                    (amhw_zlg217_gpio_speed_mode_t)AM_ZLG217_GPIO_OUTRES_RATE_GET(flags),
                    pin);
            } else {
                amhw_zlg217_gpio_pin_dir_output(p_hw_gpio,
                                AMHW_ZLG217_GPIO_SPEED_50MHz, pin);
            }
            pin_mode = AMHW_ZLG217_GPIO_MODE_AF_PP;
            break;

        case 7:
            /* ����Ϊ�����������ӦƵ�ʣ�Ĭ��Ϊ50Mhz */
            if (0 != (flags & AM_ZLG217_GPIO_OUTRES_RATE)) {
                amhw_zlg217_gpio_pin_dir_output(
                    p_hw_gpio,
                    (amhw_zlg217_gpio_speed_mode_t)AM_ZLG217_GPIO_OUTRES_RATE_GET(flags),
                    pin);
            } else {
                amhw_zlg217_gpio_pin_dir_output(p_hw_gpio,
                                AMHW_ZLG217_GPIO_SPEED_50MHz, pin);
            }
            pin_mode = AMHW_ZLG217_GPIO_MODE_AF_OD;
            break;

        default:
            return -AM_ENOTSUP;
        }

        amhw_zlg217_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /* ��ӳ������ */
    if (0 != (flags & AM_ZLG217_GPIO_REMAP)) {

        /* ����ӳ���뵱ǰ��ӳ�񲻵ȣ� NO -> ������ӳ�� �� ������ӳ�� -> NO �� ����1 -> ����2 */
        if (AM_ZLG217_GPIO_REMAP_PERIPHERAL_GET(flags) !=
                                               p_gpio_devinfo->p_remap[pin]) {

            /* NO -> ������ӳ�񣬵�ǰ��������ӳ��ɲ����κδ��� */
            if (p_gpio_devinfo->p_remap[pin] == AMHW_ZLG217_NO_REMAP) {

                /* ���浱ǰ������ӳ����Ϣ */
                p_gpio_devinfo->p_remap[pin] =
                                     (amhw_zlg217_afio_remap_peripheral_t)
                                     AM_ZLG217_GPIO_REMAP_PERIPHERAL_GET(flags);

            } else if (AM_ZLG217_GPIO_REMAP_PERIPHERAL_GET(flags) == AMHW_ZLG217_NO_REMAP) {

                /*
                 * ������ӳ�� -> NO
                 * �����ǰ���Ŷ�Ӧ�������ӳ��ģʽ�������轫����������������Ҫ��������
                 * ���������ӳ��ģʽ��Ҫ����Ӱ�������GPIO��ӳ����Ϣ��д
                 */

                /* ����������ӳ�񣬲�����Ӱ���GPIO��ʼ�� */
                __am_zlg217_peripheral_remap_clear(pin);

                /* ���浱ǰ������ӳ����Ϣ */
                p_gpio_devinfo->p_remap[pin] = AMHW_ZLG217_NO_REMAP;

                return AM_OK;
            } else {

                /*
                 * ����1 -> ����2
                 * �����ǰ���Ŷ�Ӧ�������ӳ��ģʽ�������µ���ӳ��
                 * ���������ӳ��ģʽ��Ҫ����Ӱ�������GPIO��ӳ����Ϣ��д
                 */

                /* ����������ӳ�񣬲�����Ӱ���GPIO��ʼ�� */
                __am_zlg217_peripheral_remap_clear(pin);

                /* ���浱ǰ������ӳ����Ϣ */
                p_gpio_devinfo->p_remap[pin] =
                                     (amhw_zlg217_afio_remap_peripheral_t)
                                     AM_ZLG217_GPIO_REMAP_PERIPHERAL_GET(flags);
            }
        } else {

            /* ����ӳ���뵱ǰ��ӳ����ȣ�����������д����Ӧ��Ӧ��ӳ��ǰ��Ҫ���ǰǰ��ӳ��Ӱ���GPIO */
            if (p_gpio_devinfo->p_remap[pin] != AMHW_ZLG217_NO_REMAP) {

                __am_zlg217_peripheral_remap_clear(pin);
            }
        }

        /* ������������ӳ��ģʽ */
        switch (AM_ZLG217_GPIO_REMAP_PERIPHERAL_GET(flags)) {

        case AMHW_ZLG217_SPI1_REMAP:
            if (1 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_spi1_pin_remap_enable(p_hw_afio);
            } else if (0 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_spi1_pin_remap_disable(p_hw_afio);
            }
            break;

        case AMHW_ZLG217_I2C1_REMAP:
            if (1 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_i2c1_pin_remap_enable(p_hw_afio);
            } else if (0 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_i2c1_pin_remap_disable(p_hw_afio);
            }
            break;

        case AMHW_ZLG217_UART1_REMAP:
            if (1 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_uart_pin_remap_enable(p_hw_afio, 1);
            } else if (0 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_uart_pin_remap_disable(p_hw_afio, 1);
            }
            break;

        case AMHW_ZLG217_UART3_REMAP:
            if (1 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_uart_pin_remap_enable(p_hw_afio, 3);
            } else if (0 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_uart_pin_remap_disable(p_hw_afio, 3);
            }
            break;

        case AMHW_ZLG217_TIM1_REMAP:
            if (1 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_tim1_pin_remap_enable(p_hw_afio);
            } else if (0 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_tim1_pin_remap_disable(p_hw_afio);
            }
            break;

        case AMHW_ZLG217_TIM2_REMAP:
            amhw_zlg217_afio_tim2_remap_mode_set(
                p_hw_afio,
                (amhw_zlg217_afio_tim2_remap_mode_t)AM_ZLG217_GPIO_REMAP_MODE_GET(flags));
            break;

        case AMHW_ZLG217_TIM3_REMAP:
            amhw_zlg217_afio_tim3_remap_mode_set(
                p_hw_afio,
                (amhw_zlg217_afio_tim3_remap_mode_t)AM_ZLG217_GPIO_REMAP_MODE_GET(flags));
            break;

        case AMHW_ZLG217_CAN_REMAP:
            amhw_zlg217_afio_can_remap_mode_set(
                p_hw_afio,
                (amhw_zlg217_afio_can_remap_mode_t)AM_ZLG217_GPIO_REMAP_MODE_GET(flags));
            break;

        case AMHW_ZLG217_PD01_REMAP:
            if (1 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_pd01_pin_remap_enable(p_hw_afio);
            } else if (0 == AM_ZLG217_GPIO_REMAP_MODE_GET(flags)) {

                amhw_zlg217_afio_pd01_pin_remap_disable(p_hw_afio);
            }
            break;

        case AMHW_ZLG217_SWJ_CFG:
            amhw_zlg217_afio_swj_cfg_remap_mode_set(
                p_hw_afio,
                (amhw_zlg217_afio_swj_cfg_mode_t)AM_ZLG217_GPIO_REMAP_MODE_GET(flags));
            break;

        case AMHW_ZLG217_NO_REMAP:
            break;

        default:
            return -AM_ENOTSUP;
        }
    }

    return AM_OK;
}

/**
 * \brief ��ȡGPIO����״̬
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \return ����״̬
 */
int am_gpio_get (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_zlg217_gpio_t     *p_hw_gpio  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_zlg217_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (amhw_zlg217_gpio_pin_dir_get(p_hw_gpio, pin)) {
        return amhw_zlg217_gpio_pin_output_get(p_hw_gpio, pin);
    } else {
        return amhw_zlg217_gpio_pin_input_get(p_hw_gpio, pin);
    }
}

/**
 * \brief �����������״̬
 *
 * \param[in] pin   : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] value : ����״̬���μ�
 *                    \ref grp_am_gpio_pin_level
 *
 * \retval  AM_OK   : �����ɹ�
 */
int am_gpio_set (int pin, int value)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_zlg217_gpio_t     *p_hw_gpio  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_zlg217_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (value == 0) {
        amhw_zlg217_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_zlg217_gpio_pin_out_high(p_hw_gpio, pin);
    }

    return AM_OK;
}

/**
 * \brief ��תGPIO�������״̬
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_toggle (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_zlg217_gpio_t     *p_hw_gpio  = NULL;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio  = (amhw_zlg217_gpio_t *)p_gpio_devinfo->gpio_regbase;

    amhw_zlg217_gpio_pin_out_toggle(p_hw_gpio, pin);

    return AM_OK;
}

/**
 * \brief �ⲿ�ж���0�жϺ���
 */
static void __port_exit0_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 0;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zlg217_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zlg217_exti_t   *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zlg217_exti_pr_read(p_hw_exti,
                                 (amhw_zlg217_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zlg217_exti_pending_clear(p_hw_exti,
                                   (amhw_zlg217_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���1�жϺ���
 */
static void __port_exit1_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 1;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zlg217_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zlg217_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zlg217_exti_pr_read(p_hw_exti,
                                 (amhw_zlg217_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zlg217_exti_pending_clear(p_hw_exti,
                                   (amhw_zlg217_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���2�жϺ���
 */
static void __port_exit2_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 2;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zlg217_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zlg217_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zlg217_exti_pr_read(p_hw_exti,
                                 (amhw_zlg217_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zlg217_exti_pending_clear(p_hw_exti,
                                   (amhw_zlg217_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���2�жϺ���
 */
static void __port_exit3_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 3;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zlg217_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zlg217_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zlg217_exti_pr_read(p_hw_exti,
                                 (amhw_zlg217_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zlg217_exti_pending_clear(p_hw_exti,
                                   (amhw_zlg217_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���4�жϺ���
 */
static void __port_exit4_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t  slot = 4;

    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;

    amhw_zlg217_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zlg217_exti_t *)p_gpio_devinfo->exti_regbase;

    /* ��ȡ�йػص����������� */
    pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

    if (amhw_zlg217_exti_pr_read(p_hw_exti,
                                 (amhw_zlg217_line_num_t)(1ul << slot))) {
        if (pfn_isr != NULL) {
            pfn_isr(p_arg_tmp);
        }
    }

    /* ���жϱ�־ */
    amhw_zlg217_exti_pending_clear(p_hw_exti,
                                   (amhw_zlg217_line_num_t)(1ul << slot));
}

/**
 * \brief �ⲿ�ж���9_5�жϺ���
 */
static void __port_exit9_5_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    am_pfnvoid_t pfn_isr    = NULL;
    void         *p_arg_tmp = NULL;
    uint8_t      slot       = 5;

    amhw_zlg217_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zlg217_exti_t   *)p_gpio_devinfo->exti_regbase;

    for (slot = 5 ; slot < 10 ; slot++) {
        if (amhw_zlg217_exti_pr_read(p_hw_exti,
                                     (amhw_zlg217_line_num_t)(1ul << slot))) {

            pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

            if (NULL != pfn_isr) {
                pfn_isr(p_arg_tmp);
            }

            amhw_zlg217_exti_pending_clear(p_hw_exti,
                                         (amhw_zlg217_line_num_t)(1ul << slot));

            break;
        }
    }
}

/**
 * \brief �ⲿ�ж���5_10�жϺ���
 */
static void __port_exit15_10_int_isr (void * p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    am_pfnvoid_t pfn_isr    = NULL;
    void         *p_arg_tmp = NULL;
    uint8_t      slot       = 10;

    amhw_zlg217_exti_t   *p_hw_exti   = NULL;

    p_hw_exti   = (amhw_zlg217_exti_t   *)p_gpio_devinfo->exti_regbase;

    for (slot = 10 ; slot < 16 ; slot++) {
        if (amhw_zlg217_exti_pr_read(p_hw_exti,
                                     (amhw_zlg217_line_num_t)(1ul << slot))) {

            pfn_isr   = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
            p_arg_tmp = p_gpio_devinfo->p_triginfo[slot].p_arg;

            if (NULL != pfn_isr) {
                pfn_isr(p_arg_tmp);
            }

            amhw_zlg217_exti_pending_clear(p_hw_exti,
                                         (amhw_zlg217_line_num_t)(1ul << slot));

            break;
        }
    }
}

/**
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_zlg217_gpio_init (am_zlg217_gpio_dev_t           *p_dev,
                         const am_zlg217_gpio_devinfo_t *p_devinfo)
{
    uint8_t i = 0;

    if (NULL == p_dev || NULL == p_devinfo) {
        return -AM_EINVAL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;

    if ((p_devinfo->p_remap == NULL) || (p_devinfo->inum_pin == NULL) ||
        (p_devinfo->p_infomap == NULL) || (p_devinfo->p_triginfo == NULL)) {
        p_dev->valid_flg = AM_FALSE;
        return -AM_EINVAL;
    }

    for (i = 0 ; i < p_devinfo->pin_count ; i++) {
        if ((i == PIOA_13) || (i == PIOA_14) || (i == PIOA_15) ||
             (i == PIOB_3) || (i == PIOB_4)) {
            p_devinfo->p_remap[i] = AMHW_ZLG217_SWJ_CFG;
        } else {
            p_devinfo->p_remap[i] = AMHW_ZLG217_NO_REMAP;
        }
    }

    for (i = 0 ; i < p_devinfo->exti_num_max ; i++) {
        p_devinfo->p_infomap[i] = AM_ZLG217_GPIO_INVALID_PIN_MAP;
        p_devinfo->p_triginfo[i].p_arg = NULL;
        p_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

    am_int_connect(p_devinfo->inum_pin[0], __port_exit0_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[1], __port_exit1_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[2], __port_exit2_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[3], __port_exit3_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[4], __port_exit4_int_isr, NULL);

    am_int_connect(p_devinfo->inum_pin[5], __port_exit9_5_int_isr, NULL);
    am_int_connect(p_devinfo->inum_pin[6], __port_exit15_10_int_isr, NULL);

    am_int_enable(p_devinfo->inum_pin[0]);
    am_int_enable(p_devinfo->inum_pin[1]);
    am_int_enable(p_devinfo->inum_pin[2]);
    am_int_enable(p_devinfo->inum_pin[3]);
    am_int_enable(p_devinfo->inum_pin[4]);
    am_int_enable(p_devinfo->inum_pin[5]);
    am_int_enable(p_devinfo->inum_pin[6]);

    p_dev->valid_flg = AM_TRUE;

    __gp_gpio_dev = p_dev;

    return AM_OK;
}

/**
 * \brief GPIOȥ��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void am_zlg217_gpio_deinit (void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t i;

    if (p_gpio_devinfo->pfn_plfm_deinit) {
        p_gpio_devinfo->pfn_plfm_deinit();
    }

    if (__gp_gpio_dev->valid_flg == AM_FALSE) {
        return;
    }

    for (i = 0 ; i < p_gpio_devinfo->pin_count ; i++) {
        if ((i == PIOA_13) || (i == PIOA_14) || (i == PIOA_15) ||
             (i == PIOB_3) || (i == PIOB_4)) {
            p_gpio_devinfo->p_remap[i] = AMHW_ZLG217_SWJ_CFG;
        } else {
            p_gpio_devinfo->p_remap[i] = AMHW_ZLG217_NO_REMAP;
        }
    }

    for (i = 0 ; i < p_gpio_devinfo->exti_num_max ; i++) {
        p_gpio_devinfo->p_infomap[i] = AM_ZLG217_GPIO_INVALID_PIN_MAP;
        p_gpio_devinfo->p_triginfo[i].p_arg = NULL;
        p_gpio_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

    am_int_disable(p_gpio_devinfo->inum_pin[0]);
    am_int_disable(p_gpio_devinfo->inum_pin[1]);
    am_int_disable(p_gpio_devinfo->inum_pin[2]);
    am_int_disable(p_gpio_devinfo->inum_pin[3]);
    am_int_disable(p_gpio_devinfo->inum_pin[4]);
    am_int_disable(p_gpio_devinfo->inum_pin[5]);
    am_int_disable(p_gpio_devinfo->inum_pin[6]);

    am_int_disconnect(p_gpio_devinfo->inum_pin[0], __port_exit0_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[1], __port_exit1_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[2], __port_exit2_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[3], __port_exit3_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[4], __port_exit4_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[5], __port_exit9_5_int_isr, NULL);
    am_int_disconnect(p_gpio_devinfo->inum_pin[6], __port_exit15_10_int_isr, NULL);

    __gp_gpio_dev = NULL;
}

/**
 * \brief ����GPIO���Ŵ�������
 *
 * \param[in] pin  : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] flag : ���ò������μ�
 *                   \ref grp_am_gpio_pin_trigger_function
 *
 * \retval AM_OK   : ���óɹ�
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_zlg217_gpio_t     *p_hw_gpio  = NULL;
    amhw_zlg217_exti_t     *p_hw_exti  = NULL;
    amhw_zlg217_afio_t     *p_hw_afio  = NULL;
    uint8_t                 slot       = pin & 0x0f;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_gpio = (amhw_zlg217_gpio_t *)p_gpio_devinfo->gpio_regbase;
    p_hw_exti = (amhw_zlg217_exti_t *)p_gpio_devinfo->exti_regbase;
    p_hw_afio = (amhw_zlg217_afio_t *)p_gpio_devinfo->afio_regbase;

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    if (p_gpio_devinfo->p_infomap[slot] != pin) {
        return -AM_EINVAL;
    }

    /* ʹ��GPIO���� */
    __am_zlg217_peripheral_remap_clear(pin);

    /* ���ùܽ�Ϊ���뷽�� */
    amhw_zlg217_gpio_pin_dir_input(p_hw_gpio, pin);

    /* �ܽ�Ϊ����/����ģʽ */
    amhw_zlg217_gpio_pin_mode_set(p_hw_gpio, AMHW_ZLG217_GPIO_MODE_IPD, pin);
    /*
     * �ж���0ֻ����һ���˿ڱ��Ϊ0��GPIO���ţ�����˵��PIOA_0���ӵ����ж���0��
     * PIOB_0��PIOC_0��PIOD_0�Ͳ��������ж���0, ����ʱPIOA_1�������ӵ��ж���1��
     */
    amhw_zlg217_afio_exti_pin_set(p_hw_afio, pin);

    /* ����ж������� */
    amhw_zlg217_exti_imr_clear(p_hw_exti,
                               (amhw_zlg217_line_num_t)(1ul << slot));
    amhw_zlg217_exti_emr_clear(p_hw_exti,
                               (amhw_zlg217_line_num_t)(1ul << slot));

    /* ����ж��ߴ�����ʽ���� */
    amhw_zlg217_exti_rtsr_clear(p_hw_exti,
                                (amhw_zlg217_line_num_t)(1ul << slot));
    amhw_zlg217_exti_ftsr_clear(p_hw_exti,
                                (amhw_zlg217_line_num_t)(1ul << slot));

    switch (flag) {

    case AM_GPIO_TRIGGER_OFF:
        break;

    case AM_GPIO_TRIGGER_RISE:
        /* ʹODλ��Ϊ0, ���������� */
        amhw_zlg217_gpio_pin_out_low(p_hw_gpio, pin);
        amhw_zlg217_exti_rtsr_set(p_hw_exti,
                                  (amhw_zlg217_line_num_t)(1ul << slot));
        break;

    case AM_GPIO_TRIGGER_FALL:
        /* ʹODλ��Ϊ1, ���������� */
        amhw_zlg217_gpio_pin_out_high(p_hw_gpio, pin);
        /* falling  edge */
        amhw_zlg217_exti_ftsr_set(p_hw_exti,
                                  (amhw_zlg217_line_num_t)(1ul << slot));
        break;

    case AM_GPIO_TRIGGER_BOTH_EDGES:
        /* ʹODλ��Ϊ1, ���������� */
        amhw_zlg217_gpio_pin_out_high(p_hw_gpio, pin);
        /* falling  edge */
        amhw_zlg217_exti_ftsr_set(p_hw_exti,
                                  (amhw_zlg217_line_num_t)(1ul << slot));
        amhw_zlg217_exti_rtsr_set(p_hw_exti,
                                  (amhw_zlg217_line_num_t)(1ul << slot));
        break;

    default:
        return -AM_ENOTSUP;
    }

    return AM_OK;
}

/**
 * \brief ���ӻص�����������
 *
 * \param[in] pin          : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] pfn_callback : �ص�����ָ��
 * \param[in] p_arg        : �ص���������ڲ���
 *
 * \retval  AM_OK          : �����ɹ�
 */
int am_gpio_trigger_connect(int           pin,
                            am_pfnvoid_t  pfn_callback,
                            void         *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t                  slot        = pin & 0x0f;
    int key;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (AM_FALSE == __gp_gpio_dev->valid_flg) {
        return -AM_ENODEV;
    }

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    key = am_int_cpu_lock();

    if (p_gpio_devinfo->p_infomap[slot] == AM_ZLG217_GPIO_INVALID_PIN_MAP) {

        p_gpio_devinfo->p_infomap[slot] = pin;
        p_gpio_devinfo->p_triginfo[slot].p_arg = p_arg;
        p_gpio_devinfo->p_triginfo[slot].pfn_callback = pfn_callback;

    } else {

        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }

    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief ɾ�����ӵ����ŵĻص�����
 *
 * \param[in] pin          : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] pfn_callback : �ص�����ָ��
 * \param[in] p_arg        : �ص���������ڲ���
 *
 * \retval  AM_OK          : �����ɹ�
 */
int am_gpio_trigger_disconnect(int           pin,
                               am_pfnvoid_t  pfn_callback,
                               void         *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    uint8_t                  slot        = pin & 0x0f;
    int key;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    key = am_int_cpu_lock();

    if (p_gpio_devinfo->p_infomap[slot] == pin) {

        p_gpio_devinfo->p_infomap[slot] = AM_ZLG217_GPIO_INVALID_PIN_MAP;
        p_gpio_devinfo->p_triginfo[slot].p_arg = NULL;
        p_gpio_devinfo->p_triginfo[slot].pfn_callback = NULL;

    } else {
        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }

    am_int_cpu_unlock(key);

    return AM_OK;
}

/**
 * \brief ʹ�����Ŵ����ж�
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_trigger_on(int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_zlg217_exti_t *p_hw_exti  = NULL;
    uint8_t             slot       = pin & 0x0f;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    if (slot > (p_gpio_devinfo->exti_num_max - 1)) {
        return -AM_ENOSPC;
    }

    p_hw_exti = (amhw_zlg217_exti_t *)p_gpio_devinfo->exti_regbase;

    if (p_gpio_devinfo->p_infomap[slot] == pin) {

        amhw_zlg217_exti_pending_clear(p_hw_exti,
                                       (amhw_zlg217_line_num_t)(1ul << slot));
        amhw_zlg217_exti_imr_set(p_hw_exti,
                                 (amhw_zlg217_line_num_t)(1ul << slot));

    } else {
        return -AM_ENXIO;
    }

    return AM_OK;
}

/**
 * \brief �������Ŵ����ж�
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_trigger_off(int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    amhw_zlg217_exti_t *p_hw_exti  = NULL;
    uint8_t             slot       = pin & 0x0f;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }

    p_hw_exti = (amhw_zlg217_exti_t *)p_gpio_devinfo->exti_regbase;

    if (p_gpio_devinfo->p_infomap[slot] == pin) {

        amhw_zlg217_exti_imr_clear(p_hw_exti,
                                   (amhw_zlg217_line_num_t)(1ul << slot));
        amhw_zlg217_exti_emr_clear(p_hw_exti,
                                   (amhw_zlg217_line_num_t)(1ul << slot));

    } else {
        return -AM_ENXIO;
    }

    return AM_OK;
}

/* end of file */
