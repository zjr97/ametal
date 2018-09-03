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
 * \brief USB interfaces for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-18  sdq, first implementation
 * \endinternal
 */
#ifndef __AMHW_ZLG217_USB_H
#define __AMHW_ZLG217_USB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_types.h"
#include "amhw_zlg217_periph_map.h"

/**
 * \addtogroup amhw_zlg217_if_usbd
 * \copydoc amhw_zlg217_usbd.h
 * @{
 */

/**
 *  \brief USB �Ĵ����ṹ�嶨��
 */
typedef struct amhe_zlg217_usb{
    __IO  uint16_t top;              /* �ж�״̬�Ĵ�����ƫ�Ƶ�ַ0x00 */
          uint16_t reserve0;         /* ����λ */
    __IO  uint16_t int_state;        /* �ж�״̬�Ĵ�����ƫ�Ƶ�ַ0x04 */
          uint16_t reserve1;         /* ����λ */
    __IO  uint16_t ep_int_state;     /* �˵��ж�״̬�Ĵ�����ƫ�Ƶ�ַ0x08 */
          uint16_t reserve2;         /* ����λ */
    __IO  uint16_t ep0_int_state;    /* �˵�0�ж�״̬�Ĵ�����ƫ�Ƶ�ַ0xc0 */
          uint16_t reserve3;         /* ����λ */
    __IO  uint16_t int_en;           /* �ж�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x10 */
          uint16_t reserve4;         /* ����λ */
    __IO  uint16_t ep_int_en;        /* �˵��ж�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x14 */
          uint16_t reserve5;         /* ����λ */
    __IO  uint16_t ep0_int_en;       /* �˵�0�ж�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x18 */
          uint16_t reserve6[3];      /* ����λ */
    struct {
    __IO  uint16_t epx_int_state;
          uint16_t reserved6;
    }epx_int_state_arr[4];                 /* �˵�x�ж�״̬�Ĵ�����ƫ�Ƶ�ַ0x20-0x2c */
          uint16_t reserve7[8];            /* ����λ */
    struct {
    __IO  uint16_t epx_int_en;
          uint16_t reserved8;
    } epx_int_en_arr[4];                   /* �˵�x�ж�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x40-0x4c */
          uint16_t  reserve9[8];           /* ����λ */
    __IO  uint16_t addr;                   /* usb��ַ�Ĵ�����ƫ�Ƶ�ַ0x60 */
          uint16_t reserve10;              /* ����λ */
    __IO  uint16_t ep_en;                  /* usb�˵�ʹ�ܼĴ�����ƫ�Ƶ�ַ0x64 */
          uint16_t reserve11[9];           /* ����λ */
    __IO  uint16_t tog_crl1_4;             /* ���ݷ�ת���ƼĴ�����ƫ�Ƶ�ַ0x78 */
          uint16_t  reserve12[3];          /* ����λ */
    struct {
    __IO  uint16_t stupx;
          uint16_t reserved13;
    }stupx_arr[8];                         /* ���ð����ݼĴ�����ƫ�Ƶ�ַ0x80-0x9c */
    __IO  uint16_t packet_size;            /* �������С�Ĵ�����ƫ�Ƶ�ַ0xa0 */
          uint16_t reserve14[47];          /* ����λ */
    struct {
    __IO  uint16_t epx_avai;
          uint16_t reserved15;
    }epx_avail_arr[5];                     /* �˵�x��Ч���ݼĴ�����ƫ�Ƶ�ַ0x100-0x110 */
          uint16_t  reserve16[22];         /* ����λ */
    struct {
    __IO  uint16_t epx_ctrl;
          uint16_t reserved17;
    }epx_ctrl_arr[5];                      /* �˵�x���ƼĴ�����ƫ�Ƶ�ַ0x140-0x150 */
          uint16_t reserve18[6];           /* ����λ */
    struct {
    __IO  uint16_t epx_fifo;
          uint16_t reserved19;
    }epx_fifo_arr[5];                      /* �˵�x fifo�Ĵ�����ƫ�Ƶ�ַ0x160-0x170 */
          uint16_t reserve20[8];           /* ����λ */
    __IO  uint16_t ep_dma;                 /* �˵�dmaʹ�ܼĴ�����ƫ�Ƶ�ַ0x184 */
          uint16_t reserve21;              /* ����λ */
    __IO  uint16_t ep_halt;                /* �˵��ݴ�Ĵ�����ƫ�Ƶ�ַ0x188 */
          uint16_t reserve22[27];          /* ����λ */
    __IO  uint16_t power;                  /* ���ļĴ�����ƫ�Ƶ�ַ0x1c0 */
}amhw_zlg217_usb_t;

/*******************  Bit definition for USB_TOP register  *******************/
#define  __USB_TOP_SPEED        0
#define  __USB_TOP_CONNECT      1
#define  __USB_TOP_RESET        3
#define  __USB_TOP_SUSPEND      4
#define  __USB_TOP_DP_DM_STATE  5
#define  __USB_TOP_ACTIVE       7

/**************************  USB_TOP Configuration  ***************************/
#define  __USB_SPEED            (1UL << __USB_TOP_SPEED)
#define  __USB_CONNECT          (1UL << __USB_TOP_CONNECT)
#define  __USB_RESET            (1UL << __USB_TOP_RESET)
#define  __USB_SUSPEND          (1UL << __USB_TOP_SUSPEND)
#define  __USB_DP_DM_STATE      (3UL << __USB_TOP_DP_DM_STATE)
#define  __USB_ACTIVE           (1UL << __USB_TOP_ACTIVE)

/**
 * \brief USB����ö��
 */
typedef enum {
    AMHW_ZLG217_USB_SPEED_FULL,   /* ȫ�ٴ��� */
    AMHW_ZLG217_USB_SPEED_LOW     /* ���ٴ��� */
}amhw_zlg217_usb_speed_t;

/**
 *  \brief ����usb���ʺ���
 *
 *  \param[in] speed  usb����
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_speed_set (amhw_zlg217_usb_speed_t speed)
{
    if (speed == AMHW_ZLG217_USB_SPEED_FULL)
        AMHW_ZLG217_USB->top &= (~__USB_SPEED);
    else if (speed == AMHW_ZLG217_USB_SPEED_LOW)
        AMHW_ZLG217_USB->top |= (__USB_SPEED);
}

/**
 *  \brief ���usb���ʺ���
 *
 *  \return usb����
 */
am_static_inline
uint16_t amhw_zlg217_usb_speed_get (void)
{
    return ((AMHW_ZLG217_USB->top & __USB_SPEED) >> __USB_TOP_SPEED);
}

/**
 * \brief USB����״̬ö��
 */
typedef enum {
    AMHW_ZLG217_USB_DISCONNECT,   /* �Ͽ����� */
    AMHW_ZLG217_USB_CONNECT       /* ���� */
}amhw_zlg217_usb_connect_t;

/**
 *  \brief ����usb����״̬����
 *
 *  \param[in] connect  usb����״̬
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_connect_set (amhw_zlg217_usb_connect_t connect)
{
    if (connect == AMHW_ZLG217_USB_DISCONNECT)
        AMHW_ZLG217_USB->top &= (~__USB_CONNECT);
    else if (connect == AMHW_ZLG217_USB_CONNECT)
        AMHW_ZLG217_USB->top |= (__USB_CONNECT);
}

/**
 *  \brief ���usb����״̬����
 *
 *  \return usb����״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_connect_get (void)
{
    return ((AMHW_ZLG217_USB->top & __USB_CONNECT) >> __USB_TOP_CONNECT);
}

/**
 * \brief USB��λ״̬ö��
 */
typedef enum {
    AMHW_ZLG217_USB_NORESET,   /* ����λ */
    AMHW_ZLG217_USB_RESET      /* ��λ */
}amhw_zlg217_usb_reset_t;

/**
 *  \brief ����usb��λ����
 *
 *  \param[in] reset  usb��λ״̬
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_reset_set (amhw_zlg217_usb_reset_t reset)
{
    if(reset == AMHW_ZLG217_USB_NORESET)
        AMHW_ZLG217_USB->top &= (~__USB_RESET);
    else if(reset == AMHW_ZLG217_USB_RESET)
        AMHW_ZLG217_USB->top |= (__USB_RESET);
}

/**
 *  \brief ���usb��λ����
 *
 *  \return usb��λ״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_reset_get (void)
{
    return ((AMHW_ZLG217_USB->top & __USB_RESET) >> __USB_TOP_RESET);
}

/**
 * \brief USB suspend״̬ö��
 */
typedef enum {
    AMHW_ZLG217_USB_SUSPEND_WORK,     /* ����״̬ */
    AMHW_ZLG217_USB_SUSPEND_PENDING   /* ����״̬ */
}amhw_zlg217_usb_suspend_t;

/**
 *  \brief ���usb suspend״̬����
 *
 *  \return usb suspend״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_suspend_get (void)
{
    return ((AMHW_ZLG217_USB->top & __USB_SUSPEND) >> __USB_TOP_SUSPEND);
}

/**
 *  \brief ���usb dp/dm��״̬����
 *
 *  \return usb dp/dm״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_dp_dm_get (void)
{
    return ((AMHW_ZLG217_USB->top & __USB_DP_DM_STATE) >> __USB_TOP_DP_DM_STATE);
}

/**
 * \brief USB ���߻�Ծ״̬
 */
typedef enum {
    AMHW_ZLG217_USB_INACTIVE,     /* ���߲���Ծ */
    AMHW_ZLG217_USB_ACTIVE        /* ���߻�Ծ */
}amhw_zlg217_usb_active_t;

/**
 *  \brief ����usb���߻�Ծ״̬����
 *
 *  \param[in] active  usb ���߻�Ծ״̬
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_active_set(amhw_zlg217_usb_active_t active)
{
    if (active == AMHW_ZLG217_USB_INACTIVE)
        AMHW_ZLG217_USB->top &= (~__USB_ACTIVE);
    else if (active == AMHW_ZLG217_USB_ACTIVE)
        AMHW_ZLG217_USB->top |= (__USB_ACTIVE);
}

/**
 *  \brief ���usb���߻�Ծ״̬����
 *
 *  \return usb ���߻�Ծ״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_active_get (void)
{
    return ((AMHW_ZLG217_USB->top & __USB_ACTIVE) >> __USB_TOP_ACTIVE);
}

/***********************  USB_INT_STATE Configuration  ************************/
#define  AMHW_ZLG217_USB_INT_STATE_RSTF      (1UL << 0)   /* ���߸�λ���� */
#define  AMHW_ZLG217_USB_INT_STATE_SUSPENDF  (1UL << 1)   /* ���߹��� */
#define  AMHW_ZLG217_USB_INT_STATE_RESUMF    (1UL << 2)   /* ���߻��� */
#define  AMHW_ZLG217_USB_INT_STATE_SOFF      (1UL << 3)   /* ��⵽SOF */
#define  AMHW_ZLG217_USB_INT_STATE_EPINTF    (1UL << 4)   /* �˵��ж� */
#define  AMHW_ZLG217_USB_INT_STATE_ALL        0X0F
/**
 *  \brief usb�ж�״̬�Ĵ����������
 *
 *  \param[in] state  usb �ж�״̬�Ĵ���״̬λö��
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_int_state_clear (uint16_t state)
{
    AMHW_ZLG217_USB->int_state |= (state & AMHW_ZLG217_USB_INT_STATE_ALL);
}

/**
 *  \brief ���usb�ж�״̬�Ĵ���״̬����
 *
 *  \return usb �ж�״̬�Ĵ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_int_state_get (void)
{
    return AMHW_ZLG217_USB->int_state;
}

/************************  EP_INT_STATE Configuration  ************************/
#define  AMHW_ZLG217_EP_INT_STATE_EP0F        (1UL << 0)
#define  AMHW_ZLG217_EP_INT_STATE_EP1F        (1UL << 1)
#define  AMHW_ZLG217_EP_INT_STATE_EP2F        (1UL << 2)
#define  AMHW_ZLG217_EP_INT_STATE_EP3F        (1UL << 3)
#define  AMHW_ZLG217_EP_INT_STATE_EP4F        (1UL << 4)
#define  AMHW_ZLG217_EP_INT_STATE_EP_ALL       0X1F

/**
 *  \brief ���usb�˵��ж�״̬�Ĵ���״̬����
 *
 *  \return usb �ж�״̬�Ĵ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_ep_int_state_get (void)
{
    return AMHW_ZLG217_USB->ep_int_state;
}

/**
 *  \brief ���usb�˵��ж�״̬
 *
 *  \param[in] ep Ҫ����Ķ˵�
 */
am_static_inline
uint16_t amhw_zlg217_ep_int_state_clear (uint16_t ep)
{
    return AMHW_ZLG217_USB->ep_int_state |= ep;
}

/************************  EP0_INT_STATE Configuration  ***********************/
#define  AMHW_ZLG217_EP0_INT_STATE_SETUP          (1UL << 0)  /* ���յ�SETUP�� */
#define  AMHW_ZLG217_EP0_INT_STATE_END            (1UL << 1)  /* �˵㴫����� */
#define  AMHW_ZLG217_EP0_INT_STATE_IN_NACK        (1UL << 2)
#define  AMHW_ZLG217_EP0_INT_STATE_IN_ACK         (1UL << 3)
#define  AMHW_ZLG217_EP0_INT_STATE_IN_STALL       (1UL << 4)
#define  AMHW_ZLG217_EP0_INT_STATE_OUT_NACK       (1UL << 5)
#define  AMHW_ZLG217_EP0_INT_STATE_OUT_ACK        (1UL << 6)
#define  AMHW_ZLG217_EP0_INT_STATE_OUT_STALL      (1UL << 7)
#define  AMHW_ZLG217_EP0_INT_STATE_ALL             0XFF

/**
 *  \brief ���usb�˵�0�ж�״̬�Ĵ���״̬����
 *
 *  \return usb �ж�״̬�Ĵ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_ep0_int_state_get (void)
{
    return AMHW_ZLG217_USB->ep0_int_state;
}

/**
 *  \brief usb�˵�0�ж�״̬�Ĵ����������
 *
 *  \param[in] state  usb �ж�״̬�Ĵ���״̬λ
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_ep0_int_state_clear (uint16_t state)
{
    AMHW_ZLG217_USB->ep0_int_state |= state;
}

/************************  USB_INT_EN Configuration  ***********************/
#define AMHW_ZLG217_USB_INT_EN_RSTIE       (1ul << 0)  /* USB ���߸�λ�ж�ʹ��λ */
#define AMHW_ZLG217_USB_INT_EN_SUSPENDIE   (1ul << 1)  /* USB ���߹����ж�ʹ��λ */
#define AMHW_ZLG217_USB_INT_EN_RESUMIE     (1ul << 2)  /* �����ж�ʹ��λ */
#define AMHW_ZLG217_USB_INT_EN_SOFIE       (1ul << 3)  /* SOF ����ж�ʹ��λ */
#define AMHW_ZLG217_USB_INT_EN_EPIE        (1ul << 4)  /* �˵��ж�ʹ��λ */
#define AMHW_ZLG217_USB_INT_EN_ALL          0X1F

/**
 *  \brief ʹ��USB�ж�
 *
 *  \param[in] int_en               Ҫʹ�ܵ�USB�ж�
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_int_enable (uint16_t int_en)
{
    AMHW_ZLG217_USB->int_en |= int_en;
}

/**
 *  \brief ����USB�ж�
 *
 *  \param[in] int_dis              Ҫ���ܵ�USB�ж�
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_int_disable (uint16_t int_dis)
{
    AMHW_ZLG217_USB->int_en &= ~int_dis;
}

/**
 *  \brief ���usb�˵�0�ж�״̬�Ĵ���״̬����
 *
 *  \return usb �ж�״̬�Ĵ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_int_en_get (void)
{
    return AMHW_ZLG217_USB->int_en;
}

/**************************  EP_INT_EN Configuration  ************************/
#define  AMHW_ZLG217_EP_INT_EN_EP0IE          (1UL << 0)
#define  AMHW_ZLG217_EP_INT_EN_EP1IE          (1UL << 1)
#define  AMHW_ZLG217_EP_INT_EN_EP2IE          (1UL << 2)
#define  AMHW_ZLG217_EP_INT_EN_EP3IE          (1UL << 3)
#define  AMHW_ZLG217_EP_INT_EN_EP4IE          (1UL << 4)
#define  AMHW_ZLG217_EP_INT_EN_ALL             0X1F

/**
 *  \brief ���usb�˵��ж�ʹ�ܼĴ���״̬
 *
 *  \return usb �˵��ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_ep_int_en_get (void)
{
    return AMHW_ZLG217_USB->ep_int_en;
}

/**
 *  \brief usb�˵��ж�ʹ��
 *
 *  \brief epx  Ҫʹ�ܵĶ˵�
 */
am_static_inline
void amhw_zlg217_ep_int_enable (uint16_t epx)
{
    AMHW_ZLG217_USB->ep_int_en |= epx;
}

/**
 *  \brief usb�˵��жϽ���
 *
 *  \brief epx  Ҫ���ܵĶ˵�
 */
am_static_inline
void amhw_zlg217_ep_int_disable (uint16_t epx)
{
    AMHW_ZLG217_USB->ep_int_en &= ~epx;
}

/**************************  EP0_INT_EN Configuration  ************************/
#define  AMHW_ZLG217_EP0_INT_EN_SETUPIE        (1UL << 0) /* ���յ� SETUP �� */
#define  AMHW_ZLG217_EP0_INT_EN_ENDIE          (1UL << 1) /* ������� */
#define  AMHW_ZLG217_EP0_INT_EN_IN_NACKIE      (1UL << 2) /* IN ��Ӧ�� NACK */
#define  AMHW_ZLG217_EP0_INT_EN_IN_ACKIE       (1UL << 3) /* IN ��Ӧ�� ACK */
#define  AMHW_ZLG217_EP0_INT_EN_IN_STALLIE     (1UL << 4) /* IN ��Ӧ�� STALL */
#define  AMHW_ZLG217_EP0_INT_EN_OUT_NACKIE     (1UL << 5) /* OUT ��Ӧ�� NACK */
#define  AMHW_ZLG217_EP0_INT_EN_OUT_ACKIE      (1UL << 6) /* OUT ��Ӧ�� ACK */
#define  AMHW_ZLG217_EP0_INT_EN_OUT_STALLIE    (1UL << 7) /* OUT ��Ӧ�� STALL */
#define  AMHW_ZLG217_EP0_INT_EN_ALL            0XFF

/**
 *  \brief ���usb�˵�0�ж�ʹ�ܼĴ���״̬
 *
 *  \return usb �˵�0�ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_ep0_int_en_get (void)
{
    return AMHW_ZLG217_USB->ep0_int_en;
}

/**
 *  \brief ���usb�˵�0�ж�ʹ��
 *
 *  \param   enable  Ҫʹ�ܵ��ж�����
 */
am_static_inline
void amhw_zlg217_ep0_int_enable (uint16_t enable)
{
    AMHW_ZLG217_USB->ep0_int_en |= enable;
}

/**
 *  \brief ���usb�˵�0�жϽ���
 *
 *  \param   disable  Ҫ���ܵ��ж�����
 */
am_static_inline
void amhw_zlg217_ep0_int_disable (uint16_t disable)
{
    AMHW_ZLG217_USB->ep0_int_en &= ~disable;
}

/*************************  EPX_INT_STATE Configuration  **********************/
#define  AMHW_ZLG217_EPX_INT_STATE_ENDIE       (1UL << 1) /* ������� */
#define  AMHW_ZLG217_EPX_INT_STATE_IN_NACKIE   (1UL << 2) /* IN ��Ӧ�� NACK */
#define  AMHW_ZLG217_EPX_INT_STATE_IN_ACKIE    (1UL << 3) /* IN ��Ӧ�� ACK */
#define  AMHW_ZLG217_EPX_INT_STATE_IN_STALLIE  (1UL << 4) /* IN ��Ӧ�� STALL */
#define  AMHW_ZLG217_EPX_INT_STATE_OUT_NACKIE  (1UL << 5) /* OUT ��Ӧ�� NACK */
#define  AMHW_ZLG217_EPX_INT_STATE_OUT_ACKIE   (1UL << 6) /* OUT ��Ӧ�� ACK */
#define  AMHW_ZLG217_EPX_INT_STATE_OUT_STALLIE (1UL << 7) /* OUT ��Ӧ�� STALL */
#define  AMHW_ZLG217_EPX_INT_STATE_ALL          0XFE

/**
 * \brief USB �˵�
 */
typedef enum {
    AMHW_ZLG217_USB_EP1,
    AMHW_ZLG217_USB_EP2,
    AMHW_ZLG217_USB_EP3,
    AMHW_ZLG217_USB_EP4
}amhw_zlg217_usb_epx_t;

/**
 *  \brief ���usb�˵�X�ж�״̬
 *
 *  \param[in] epx                  Ҫ��ȡ�Ķ˵�
 *
 *  \return usb �˵�X�ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_epx_int_state_get (amhw_zlg217_usb_epx_t epx)
{
    return AMHW_ZLG217_USB->epx_int_state_arr[epx].epx_int_state;
}

/**
 *  \brief usb�˵�X�ж�״̬���
 *
 *  \param[in] epx                  Ҫ����Ķ˵�
 *  \param[in] clear                Ҫ�����λ��״̬��
 *  \return ��
 */
am_static_inline
void amhw_zlg217_epx_int_state_clear (amhw_zlg217_usb_epx_t epx,
                                      uint16_t clear)
{
    AMHW_ZLG217_USB->epx_int_state_arr[epx].epx_int_state |= clear;
}

/**************************  EPX_INT_EN Configuration  ************************/
#define  AMHW_ZLG217_EPX_INT_EN_ENDIE       (1UL << 1) /* ������� */
#define  AMHW_ZLG217_EPX_INT_EN_IN_NACKIE   (1UL << 2) /* IN ��Ӧ�� NACK */
#define  AMHW_ZLG217_EPX_INT_EN_IN_ACKIE    (1UL << 3) /* IN ��Ӧ�� ACK */
#define  AMHW_ZLG217_EPX_INT_EN_IN_STALLIE  (1UL << 4) /* IN ��Ӧ�� STALL */
#define  AMHW_ZLG217_EPX_INT_EN_OUT_NACKIE  (1UL << 5) /* OUT ��Ӧ�� NACK */
#define  AMHW_ZLG217_EPX_INT_EN_OUT_ACKIE   (1UL << 6) /* OUT ��Ӧ�� ACK */
#define  AMHW_ZLG217_EPX_INT_EN_OUT_STALLIE (1UL << 7) /* OUT ��Ӧ�� STALL */
#define  AMHW_ZLG217_EPX_INT_EN_ALL          0XFE

/**
 *  \brief ���usb�˵�X�ж�ʹ�ܼĴ���״̬
 *
 *  \param[in] epx                  Ҫ��ȡ�Ķ˵�
 *
 *  \return usb �˵�X�ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_epx_int_en_get (amhw_zlg217_usb_epx_t epx)
{
    return AMHW_ZLG217_USB->epx_int_en_arr[epx].epx_int_en;
}

/**
 *  \brief usb�˵�X�ж�ʹ��
 *
 *  \param[in] epx                  �˵�
 *  \param[in] enable               Ҫʹ�ܵ�λ
 *  \return ��
 */
am_static_inline
void amhw_zlg217_epx_int_enable (amhw_zlg217_usb_epx_t epx,
                                 uint16_t enable)
{
    AMHW_ZLG217_USB->epx_int_en_arr[epx].epx_int_en |= enable;
}

/**
 *  \brief usb�˵�X�жϽ���
 *
 *  \param[in] epx                  �˵�
 *  \param[in] disable              Ҫ���ܵ�λ
 *  \return ��
 */
am_static_inline
void amhw_zlg217_epx_int_disable (amhw_zlg217_usb_epx_t epx,
                                  uint16_t disable)
{
    AMHW_ZLG217_USB->epx_int_en_arr[epx].epx_int_en &= ~disable;
}

/***************************  USB_ADDR Configuration  *************************/
#define __USB_ADDR_MASK     0X7F
/**
 *  \brief ����USB�ĵ�ַ
 *
 *  \param[in] addr                 Ҫ���õĵ�ַ
 *
 *  \return usb �˵�X�ж�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_addr_set (uint8_t addr)
{
    return AMHW_ZLG217_USB->addr = (addr & __USB_ADDR_MASK);
}

/**
 *  \brief ���USB�ĵ�ַ
 *
 *  \return usb USB��ַ
 */
am_static_inline
uint16_t amhw_zlg217_usb_addr_get (void)
{
    return AMHW_ZLG217_USB->addr;
}

/******************************  EP_EN Configuration  *************************/
#define  AMHW_ZLG217_USB_EP0EN       (1UL << 0)
#define  AMHW_ZLG217_USB_EP1EN       (1UL << 1)
#define  AMHW_ZLG217_USB_EP2EN       (1UL << 2)
#define  AMHW_ZLG217_USB_EP3EN       (1UL << 3)
#define  AMHW_ZLG217_USB_EP4EN       (1UL << 4)
#define  AMHW_ZLG217_USB_EP_ALL       0X1F

/**
 *  \brief ���USB�˵�ʹ�ܼĴ���״̬
 *
 *  \return usb USB�˵�ʹ�ܼĴ���״̬
 */
am_static_inline
uint16_t amhw_zlg217_ep_en_get (void)
{
    return AMHW_ZLG217_USB->ep_en;
}

/**
 *  \brief usb�˵�ʹ��
 *
 *  \param[in] enable               Ҫʹ�ܵĶ˵�
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_ep_enable (uint16_t enable)
{
    AMHW_ZLG217_USB->ep_en |= enable;
}

/**
 *  \brief usb�˵����
 *
 *  \param[in] disable              Ҫ���ܵĶ˵�
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_ep_disable (uint16_t disable)
{
    AMHW_ZLG217_USB->ep_en &= ~disable;
}

/****************************  TOG_CTRL Configuration  ************************/
/**< \brief �˵����ݷ�ת */
#define  AMHW_ZLG217_USB_DTOG_MASK    0X55
#define  AMHW_ZLG217_USB_DTOG1       (1UL << 0)
#define  AMHW_ZLG217_USB_DTOG2       (1UL << 2)
#define  AMHW_ZLG217_USB_DTOG3       (1UL << 4)
#define  AMHW_ZLG217_USB_DTOG4       (1UL << 6)

/**< \brief �˵����ݷ�תʹ��λ */
#define  AMHW_ZLG217_USB_DTOGEN_MASK  0XAA
#define  AMHW_ZLG217_USB_DTOG1EN     (1UL << 1)
#define  AMHW_ZLG217_USB_DTOG2EN     (1UL << 3)
#define  AMHW_ZLG217_USB_DTOG3EN     (1UL << 5)
#define  AMHW_ZLG217_USB_DTOG4EN     (1UL << 7)

/**
 *  \brief ����USB�˵�������ΪDATA0
 *
 *  \param[in] ep  Ҫ���õĶ˵��
 *
 *  \note �˵�Ų��ɰ�λ�򣬶˵�ŷ�ΧΪ1~4����˵�1~4
 */
am_static_inline
void amhw_zlg217_usb_dtog_data0 (uint16_t ep)
{
    if (ep >= 1 && ep <= 4) {
        AMHW_ZLG217_USB->tog_crl1_4 &=  ~(1 << ((ep - 1) * 2));
    }
}

/**
 *  \brief ����USB�˵�������ΪDATA1
 *
 *  \param[in] ep   Ҫ���õĶ˵�ţ����ɰ�λ��
 *
 *  \note �˵�Ų��ɰ�λ�򣬶˵�ŷ�ΧΪ1~4����˵�1~4
 */
am_static_inline
void amhw_zlg217_usb_dtog_data1 (uint16_t ep)
{
    if (ep >= 1 && ep <= 4) {
        AMHW_ZLG217_USB->tog_crl1_4 |=  (1 << ((ep - 1) * 2));
    }
}

/**
 *  \brief ���USB�˵����ݷ�ת״̬
 *
 *  \return usb USB�˵����ݷ�תʹ��״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_dtog_get (void)
{
    return AMHW_ZLG217_USB->tog_crl1_4 & AMHW_ZLG217_USB_DTOG_MASK;
}

/**
 *  \brief usb�˵����ݷ�תʹ��
 *
 *  \param[in] ep     Ҫʹ�ܷ�ת�Ķ˵�
 *
 *  \note �˵�Ų��ɰ�λ�򣬶˵�ŷ�ΧΪ1~4����˵�1~4
 */
am_static_inline
void amhw_zlg217_usb_dtog_enable (uint16_t ep)
{
    if (ep >= 1 && ep <= 4) {
        AMHW_ZLG217_USB->tog_crl1_4 |=  (1 << ((ep - 1) * 2 + 1));
    }
}

/**
 *  \brief usb�˵����ݷ�ת����
 *
 *  \param[in] ep   Ҫ���ܷ�ת�Ķ˵�
 *
 *  \note �˵�Ų��ɰ�λ�򣬶˵�ŷ�ΧΪ1~4����˵�1~4
 */
am_static_inline
void amhw_zlg217_usb_dtog_disable (uint16_t ep)
{
    if (ep >= 1 && ep <= 4) {
        AMHW_ZLG217_USB->tog_crl1_4 &=  ~(1 << ((ep - 1) * 2 + 1));
    }
}

/*****************************  SETUPX Configuration  *************************/
/**
 *  \brief ��ȡUSB���ݰ����ݣ��������
 *
 *  \param[out] p_data              USB���ݰ��е�����
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_setupdata_get (uint8_t *p_data)
{
    int i = 0;

    for (i = 0; i < 8; i++) {
        p_data[i] = AMHW_ZLG217_USB->stupx_arr[i].stupx;
    }
}

/**************************  PACKET_SIZE Configuration  ***********************/

/**
 *  \brief ����USB������Ĵ�С
 *
 *  \param[in] size                 USB������Ĵ�С
 *
 *  \return ��
 *
 *  \note ����������64�ֽ�
 */
am_static_inline
void amhw_zlg217_usb_packet_size_set (uint8_t size)
{
    if (size > 64)
        size = 64;

    AMHW_ZLG217_USB->packet_size = size;
}

/**
 *  \brief ��ȡUSB������Ĵ�С
 *
 *  \return USB������Ĵ�С
 */
am_static_inline
uint8_t amhw_zlg217_usb_packet_size_get (void)
{
    return AMHW_ZLG217_USB->packet_size;
}

/***************************  EPX_AVAIL Configuration  ************************/
/**
 * \brief USB �˵�
 */
typedef enum {
    AMHW_ZLG217_USB_EPX0,
    AMHW_ZLG217_USB_EPX1,
    AMHW_ZLG217_USB_EPX2,
    AMHW_ZLG217_USB_EPX3,
    AMHW_ZLG217_USB_EPX4
}amhw_zlg217_usb_epx2_t;  /* ��amhw_zlg217_usb_epx_t ���� */

/**
 *  \brief ���USB�˵�X FIFO��Ч���ݸ���
 *
 *  \return USB�˵�X FIFO��Ч���ݸ���
 */
am_static_inline
uint8_t amhw_zlg217_usb_epx_avail_size_get (amhw_zlg217_usb_epx2_t epx)
{
    return AMHW_ZLG217_USB->epx_avail_arr[epx].epx_avai;
}

/****************************  EPX_CTRL Configuration  ************************/
#define AMHW_ZLG217_USB_EPX_TRANCOUNT_MASK    0X7F

#define AMHW_ZLG217_USB_EPX_TRANEN    (1 << 7)    /* ʹ�ܴ��� */

/**
 *  \brief ���ö˵�X�����ݴ����������������
 *
 *  \param[in] epx                  Ҫ���д���Ķ˵�
 *  \param[in] count                Ҫ��������ݸ���
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_epx_transfer (amhw_zlg217_usb_epx2_t epx,
                                   uint8_t count)
{
    AMHW_ZLG217_USB->epx_ctrl_arr[epx].epx_ctrl = AMHW_ZLG217_USB_EPX_TRANEN | count;
}

/**
 *  \brief �ж϶˵�X��USB�����Ƿ������
 *
 *  \param[in] epx                  Ҫ���д���Ķ˵�
 *
 *  \return ������ɷ���1��δ��ɷ���0
 */
am_static_inline
uint8_t amhw_zlg217_usb_transfer_end(amhw_zlg217_usb_epx2_t epx)
{
    if (AMHW_ZLG217_USB->epx_ctrl_arr[epx].epx_ctrl & AMHW_ZLG217_USB_EPX_TRANEN)
        return 0;
    return 1;
}

/****************************  EPX_FIFO Configuration  ************************/
/**
 *  \brief ��USB�˵�X��fifo��д������
 *
 *  \param[in] epx                  Ҫ���õĶ˵�
 *  \param[in] data                 Ҫд�������
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_epx_fifo_write (amhw_zlg217_usb_epx2_t epx,
                                     uint8_t data)
{
    AMHW_ZLG217_USB->epx_fifo_arr[epx].epx_fifo = data;
}

/**
 *  \brief ��USB�˵�X��fifo�ж�������
 *
 *  \param[in] epx                  Ҫ���õĶ˵�
 *
 *  \return fifo�е�����
 */
am_static_inline
uint8_t amhw_zlg217_usb_epx_fifo_read (amhw_zlg217_usb_epx2_t epx)
{
    return AMHW_ZLG217_USB->epx_fifo_arr[epx].epx_fifo;
}

/*****************************  EP_DMA Configuration  *************************/
/**< \brief �˵�DMAʹ��λ��ֻ֧�ֶ˵�1�Ͷ˵�2�� */
#define  AMHW_ZLG217_USB_DMA1EN     (1UL << 0)
#define  AMHW_ZLG217_USB_DMA2EN     (1UL << 1)

/**
 *  \brief ʹ�ܶ˵�DMA
 *
 *  \param[in] dma_epx              Ҫʹ��DMA�Ķ˵�
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_ep_dma_enable (uint16_t dma_epx)
{
    AMHW_ZLG217_USB->ep_dma |= dma_epx;
}

/**
 *  \brief ���ܶ˵�DMA
 *
 *  \param[in] dma_epx              Ҫ����DMA�Ķ˵�
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_ep_dma_disable (uint16_t dma_epx)
{
    AMHW_ZLG217_USB->ep_dma &= ~dma_epx;
}

/**
 *  \brief ��ȡ�˵�DMA��ʹ��״̬
 *
 *  \return ��
 */
am_static_inline
uint8_t amhw_zlg217_usb_ep_dma_get (void)
{
    return AMHW_ZLG217_USB->ep_dma;
}

/*****************************  EP_HALT Configuration  ************************/
/**< \brief �˵���ͣλ */
/**< \brief ����λ��Ϊ��1�����豸���� IN/OUT ������Զ���Ӧ STALL�������յ����ư�ʱ��λ�ᱻӲ���Զ����� */
#define  AMHW_ZLG217_USB_EP_HALT0     (1UL << 0)
#define  AMHW_ZLG217_USB_EP_HALT1     (1UL << 1)
#define  AMHW_ZLG217_USB_EP_HALT2     (1UL << 2)
#define  AMHW_ZLG217_USB_EP_HALT3     (1UL << 3)
#define  AMHW_ZLG217_USB_EP_HALT4     (1UL << 4)
#define  AMHW_ZLG217_USB_EP_HALT_ALL   0X1F

/**
 *  \brief ���ö˵���ͣ
 *
 *  \param[in] halt                 Ҫ��ͣ��λ
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_ep_halt_set (uint16_t halt)
{
    AMHW_ZLG217_USB->ep_halt |= halt;
}

/**
 *  \brief ����˵���ͣ������ͣ��
 *
 *  \param[in] halt   Ҫ�������ͣλ
 *
 *  \return ��
 */
am_static_inline
void amhw_zlg217_usb_ep_halt_reset (uint16_t halt)
{
    AMHW_ZLG217_USB->ep_halt &= ~halt;
}

/**
 *  \brief ��ȡ�˵���ͣ״̬
 *
 *  \return �˵���ͣ״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_ep_halt_get (void)
{
    return AMHW_ZLG217_USB->ep_halt;
}

/*****************************  USB_POWER Configuration  **********************/
#define  AMHW_ZLG217_USB_POWER_SUSPEN     (1UL << 0)
#define  AMHW_ZLG217_USB_POWER_SUSP       (1UL << 1)
#define  AMHW_ZLG217_USB_POWER_WKUP       (1UL << 3)

/**< \brief ������ƺ� */
/**< \brief ����ʹ�ܹ���� */
#define  AMHW_ZLG217_USB_SUSPDIS    0         /**< \brief �ɿ����������Ƿ���� */
#define  AMHW_ZLG217_USB_SUSPEN    (1 << 0)   /**< \brief ���ݹ���ģʽ��λ����꣩�����Ƿ���� */

/**< \brief λ����� */
#define  AMHW_ZLG217_USB_SUSP       0         /**< \brief ����ģʽ */
#define  AMHW_ZLG217_USB_NORMAL    (1 << 1)   /**< \brief ��������ģʽ */

/**
 *  \brief ����USB����״̬
 *
 *  \param[in] susp �����ֵӦ����һ�� λ����� �� һ������ʹ�ܹ�������
 *
 *  \retval ����1��ʾ������������������ģʽ������0��ʾ���������ڹ���ģʽ
 */
am_static_inline
void amhw_zlg217_usb_susp_set (uint16_t susp)
{
    AMHW_ZLG217_USB->power |= (susp & (~AMHW_ZLG217_USB_POWER_WKUP));
}

/**
 *  \brief ��ȡUSB����״̬
 *
 *  \retval ���ص����ݰ��������Ƿ�ʹ���Լ�����״̬
 */
am_static_inline
uint16_t amhw_zlg217_usb_susp_get (void)
{
    return (AMHW_ZLG217_USB->power & ~AMHW_ZLG217_USB_POWER_WKUP);
}

/**
 *  \brief ���������ӹ���״̬����
 */
am_static_inline
void amhw_zlg217_usb_wakeup (void)
{
    AMHW_ZLG217_USB->power |= AMHW_ZLG217_USB_POWER_WKUP;
}

/**
 * @}if_amhw_zlg217_usbd
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG217_USBD_H */

/* end of file */
