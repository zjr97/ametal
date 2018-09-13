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
 * \brief AFIO hardware operation interface
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-21  zcb, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG217_AFIO_H
#define __AMHW_ZLG217_AFIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "ametal.h"

/**
 * \addtogroup amhw_zlg217_if_afio
 * \copydoc amhw_zlg217_afio.h
 * @{
 */

/**
 * \brief GPIO �˿ڼĴ����ṹ��
 */
typedef struct amhw_zlg217_afio {
          uint32_t reserve;      /**< \brief ���� */
    __IO  uint32_t mapr;         /**< \brief ������ӳ��͵���I/O���üĴ��� */
    __IO  uint32_t exticr[4];    /**< \brief �ⲿ�ж����üĴ��� */
} amhw_zlg217_afio_t;

/**
 * \brief ����ӳ���������
 */
typedef enum {
    AMHW_ZLG217_SPI1_REMAP = 0,     /**< \brief SPI1 */
    AMHW_ZLG217_I2C1_REMAP,         /**< \brief I2C1 */
    AMHW_ZLG217_UART1_REMAP,        /**< \brief UART1 */
    AMHW_ZLG217_UART3_REMAP = 4,    /**< \brief UART3 */
    AMHW_ZLG217_TIM1_REMAP = 6,     /**< \brief TIM1 */
    AMHW_ZLG217_TIM2_REMAP = 8,     /**< \brief TIM2 */
    AMHW_ZLG217_TIM3_REMAP = 10,    /**< \brief TIM3 */
    AMHW_ZLG217_CAN_REMAP  = 13,    /**< \brief CAN */
    AMHW_ZLG217_PD01_REMAP = 15,    /**< \brief PD01 */
    AMHW_ZLG217_SWJ_CFG,            /**< \brief SWJ_CFG */
    AMHW_ZLG217_NO_REMAP,           /**< \brief û����ӳ���� */
}amhw_zlg217_afio_remap_peripheral_t;

/**
 * \name  ��ӳ��λ����
 * @{
 */

/** \brief SPI1��ӳ�� SCK/PB3��MISO/PB4��MOSI/PB5 */
#define AMHW_ZLG217_AFIO_MAPR_SPI1    (0u)

/** \brief I2C1��ӳ�� SCL/PB8��SDA/PB9 */
#define AMHW_ZLG217_AFIO_MAPR_I2C1    (1u)

/** \brief UART1��ӳ�� TX/PB6��RX/PB7 */
#define AMHW_ZLG217_AFIO_MAPR_UART1   (2u)

/** \brief UART3������ӳ�� TX/PC10��RX/PC11 */
#define AMHW_ZLG217_AFIO_MAPR_UART3   (4u)

/** \brief
 * TIM1������ӳ��
 * ETR/PA12��
 * CH1/PA8��CH2/PA9��CH3/PA10��CH4/PA11��
 * BAKIN/PA6��
 * CH1N/PA7��CH2N/PB0��CH3N/PB1
 */
#define AMHW_ZLG217_AFIO_MAPR_TIM1    (6u)

/** \brief TIM2��ӳ�� */
#define AMHW_ZLG217_AFIO_MAPR_TIM2    (8u)

typedef enum {

    /** \brief CH1/ETR/PA0��CH2/PA1��CH3/PA2��CH4/PA3 */
    AMHW_ZLG217_AFIO_TIM2_REMAP_NO = 0,
    /** \brief CH1/ETR/PA15��CH2/PB3��CH3/PA2��CH4/PA3 */
    AMHW_ZLG217_AFIO_TIM2_REMAP_PART1,
    /** \brief CH1/ETR/PA0��CH2/PA1��CH3/PB10��CH4/PB11 */
    AMHW_ZLG217_AFIO_TIM2_REMAP_PART2,
    /** \brief CH1/ETR/PA15��CH2/PB3��CH3/PB10��CH4/PB11 */
    AMHW_ZLG217_AFIO_TIM2_REMAP_ALL
}amhw_zlg217_afio_tim2_remap_mode_t;

/** \brief TIM3��ӳ�� */
#define AMHW_ZLG217_AFIO_MAPR_TIM3    (10u)

typedef enum {

    /** \brief CH1/PA6��CH2/PA7��CH3/PB0��CH4/PB1 */
    AMHW_ZLG217_AFIO_TIM3_REMAP_NO = 0,
    /** \brief CH1 /PB4��CH2/PB5��CH3/PB0��CH4/PB1 */
    AMHW_ZLG217_AFIO_TIM3_REMAP_PART = 2,
    /** \brief CH1/PC6��CH2/PC7��CH3/PC8��CH4/PC9 */
    AMHW_ZLG217_AFIO_TIM3_REMAP_ALL
}amhw_zlg217_afio_tim3_remap_mode_t;

/** \brief CAN��ӳ�� */
#define AMHW_ZLG217_AFIO_MAPR_CAN     (13u)

typedef enum {
    AMHW_ZLG217_AFIO_CAN_RX_PA11_TX_PA12 = 0,
    AMHW_ZLG217_AFIO_CAN_RX_PB8_TX_PB9  = 2,
    AMHW_ZLG217_AFIO_CAN_RX_PD0_PD1  = 3,
}amhw_zlg217_afio_can_remap_mode_t;

/** \brief PD01��ӳ�� PD0ӳ��OSC_IN��PD1ӳ��OSC_OUT */
#define AMHW_ZLG217_AFIO_MAPR_PD01    (15u)

/** \brief ������JTAG���� */
#define AMHW_ZLG217_AFIO_SWJ_CFG      (24u)

typedef enum {
    /**
     * \brief ��ȫSWJ��JTAG-DP + SW-DP������λ״̬
     *
     * PIOA13:I/0������   PIOA14:I/0������   PIOA15:I/0������
     * PIOB3 :I/0������   PIOB4 :I/0������
     */
    AMHW_ZLG217_AFIO_SWJ_CFG_0 = 0,

    /**
     * \brief ��ȫSWJ��JTAG-DP + SW-DP����û��JNTRST
     *
     * PIOA13:I/0������   PIOA14:I/0������   PIOA15:I/0������
     * PIOB3 :I/0������   PIOB4 :I/0����
     */
    AMHW_ZLG217_AFIO_SWJ_CFG_1,

    /**
     * \brief �ر�JTAG-DP������SW-DP
     *
     * PIOA13:I/0������   PIOA14:I/0������   PIOA15:I/0����
     * PIOB3 :I/0����   PIOB4 :I/0����
     */
    AMHW_ZLG217_AFIO_SWJ_CFG_2,

    /**
     * \brief �ر�JTAG-DP���ر�SW-DP
     *
     * PIOA13:I/0����   PIOA14:I/0����   PIOA15:I/0����
     * PIOB3 :I/0����   PIOB4 :I/0����
     */
    AMHW_ZLG217_AFIO_SWJ_CFG_7 = 7,
}amhw_zlg217_afio_swj_cfg_mode_t;

/** @} */

/**
 * \brief SPI1������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_spi1_pin_remap_enable (amhw_zlg217_afio_t *p_hw_afio)
{
    p_hw_afio->mapr |= 1 << AMHW_ZLG217_AFIO_MAPR_SPI1;
}

/**
 * \brief SPI1������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_spi1_pin_remap_disable (amhw_zlg217_afio_t *p_hw_afio)
{
    p_hw_afio->mapr &= ~(1 << AMHW_ZLG217_AFIO_MAPR_SPI1);
}

/**
 * \brief I2C1������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_i2c1_pin_remap_enable (amhw_zlg217_afio_t *p_hw_afio)
{
    p_hw_afio->mapr |= 1 << AMHW_ZLG217_AFIO_MAPR_I2C1;
}

/**
 * \brief I2C1������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_i2c1_pin_remap_disable (amhw_zlg217_afio_t *p_hw_afio)
{
    p_hw_afio->mapr &= ~(1 << AMHW_ZLG217_AFIO_MAPR_I2C1);
}

/**
 * \brief UART1������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 * \param[in] num       ���ںţ�0��2
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_uart_pin_remap_enable (amhw_zlg217_afio_t *p_hw_afio,
                                             int                 num)
{
    if (num == 1) {
        p_hw_afio->mapr |= 1 << AMHW_ZLG217_AFIO_MAPR_UART1;
    } else if (num == 3) {
        p_hw_afio->mapr |= 1 << AMHW_ZLG217_AFIO_MAPR_UART3;
    }
}

/**
 * \brief UART1������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 * \param[in] num       ���ںţ�0��2
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_uart_pin_remap_disable (amhw_zlg217_afio_t *p_hw_afio,
                                              int num)
{
    if (num == 1) {
        p_hw_afio->mapr &= ~(1 << AMHW_ZLG217_AFIO_MAPR_UART1);
    } else if (num == 3) {
        p_hw_afio->mapr &= ~(1 << AMHW_ZLG217_AFIO_MAPR_UART3);
    }
}

/**
 * \brief TIM1������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_tim1_pin_remap_enable (amhw_zlg217_afio_t *p_hw_afio)
{
    p_hw_afio->mapr |= 1 << AMHW_ZLG217_AFIO_MAPR_TIM1;
}

/**
 * \brief TIM1������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_tim1_pin_remap_disable (amhw_zlg217_afio_t *p_hw_afio)
{
    p_hw_afio->mapr &= ~(1 << AMHW_ZLG217_AFIO_MAPR_TIM1);
}

/**
 * \brief TIM2������ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg217_afio_tim2_remap_modeö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_tim2_remap_mode_set (amhw_zlg217_afio_t *p_hw_afio,
                                           amhw_zlg217_afio_tim2_remap_mode_t mode)
{
    p_hw_afio->mapr &= ~(0x3 << AMHW_ZLG217_AFIO_MAPR_TIM2);
    p_hw_afio->mapr |= (mode & 0x3) << AMHW_ZLG217_AFIO_MAPR_TIM2;
}

/**
 * \brief TIM3������ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg217_afio_tim3_remap_modeö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_tim3_remap_mode_set (amhw_zlg217_afio_t *p_hw_afio,
                                           amhw_zlg217_afio_tim3_remap_mode_t mode)
{
    p_hw_afio->mapr &= ~(0x3 << AMHW_ZLG217_AFIO_MAPR_TIM3);
    p_hw_afio->mapr |= (mode & 0x3) << AMHW_ZLG217_AFIO_MAPR_TIM3;
}

/**
 * \brief CAN������ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg217_afio_can_remap_modeö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_can_remap_mode_set (amhw_zlg217_afio_t *p_hw_afio,
                                          amhw_zlg217_afio_can_remap_mode_t mode)
{
    p_hw_afio->mapr &= ~(0x3 << AMHW_ZLG217_AFIO_MAPR_CAN);
    p_hw_afio->mapr |= (mode & 0x3) << AMHW_ZLG217_AFIO_MAPR_CAN;
}

/**
 * \brief PD01������ӳ��ʹ��
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_pd01_pin_remap_enable (amhw_zlg217_afio_t *p_hw_afio)
{
    p_hw_afio->mapr |= 1 << AMHW_ZLG217_AFIO_MAPR_PD01;
}

/**
 * \brief PD01������ӳ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_pd01_pin_remap_disable (amhw_zlg217_afio_t *p_hw_afio)
{
    p_hw_afio->mapr &= ~(1 << AMHW_ZLG217_AFIO_MAPR_PD01);
}

/**
 * \brief SWJ_CFG��ӳ��ģʽ����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 * \param[in] mode      ��ӳ��ģʽ��amhw_zlg217_afio_swj_cfg_mode_tö�ٵĺ�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_swj_cfg_remap_mode_set (amhw_zlg217_afio_t *p_hw_afio,
                                              amhw_zlg217_afio_swj_cfg_mode_t mode)
{
    uint32_t flags = p_hw_afio->mapr;

    flags &= ~(0x7 << AMHW_ZLG217_AFIO_SWJ_CFG);
    flags |= (mode & 0x7) << AMHW_ZLG217_AFIO_SWJ_CFG;

    p_hw_afio->mapr |= flags;
}

/**
 * \brief �ⲿ�жϺ�����
 *
 * \param[in] p_hw_afio ָ�� amhw_zlg217_afio_t �ṹ��ָ��
 * \param[in] pin       ���ź�
 *
 * \return ��
 */
am_static_inline
void amhw_zlg217_afio_exti_pin_set (amhw_zlg217_afio_t *p_hw_afio, int pin)
{
    p_hw_afio->exticr[(pin >> 2) & 0x3] |=
                                     ((pin >> 4) & 0x3) << ((pin & 0x3) << 2);
}

/**
 * @} amhw_zlg217_if_afio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG217_AFIO_H */

/* end of file */
