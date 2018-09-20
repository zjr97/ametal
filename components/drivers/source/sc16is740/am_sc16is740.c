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
 * \brief SC16IS740�����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-13  wk, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_spi.h"
#include "am_sc16is740.h"


/*****************************************************************************
 * �궨��
 ****************************************************************************/

/*
 * \brief �Ĵ�����ַ
 */
#define __SC16IS740_REG_RHRTHR               0X00    /* ���ա����ͱ��ּĴ��� */
#define __SC16IS740_REG_IER                  0X01    /* �ж�ʹ�ܼĴ��� */
#define __SC16IS740_REG_FCRIIR               0X02    /* FIFO���ơ��ж�ʶ��Ĵ��� */
#define __SC16IS740_REG_LCR                  0X03    /* ��·���ƼĴ��� */
#define __SC16IS740_REG_MCR                  0X04    /* ���ƽ�������ƼĴ��� */
#define __SC16IS740_REG_LSR                  0X05    /* ��·״̬�Ĵ��� */
#define __SC16IS740_REG_MSR                  0X06    /* ���ƽ����״̬�Ĵ��� */
#define __SC16IS740_REG_SPR                  0X07    /*  */

#define __SC16IS740_REG_TXLVL                0X08    /* ����FIFO����Ĵ��� */
#define __SC16IS740_REG_RXLVL                0X09    /* ����FIFO����Ĵ��� */
#define __SC16IS740_REG_IODir                0X0A    /* I/O���ŷ���Ĵ��� */
#define __SC16IS740_REG_IOState              0X0B    /* I/O����״̬�Ĵ��� */
#define __SC16IS740_REG_IOIntEna             0X0C    /* I/O�ж�ʹ�ܼĴ��� */

#define __SC16IS740_REG_IOControl            0X0E    /* I/O���ſ��ƼĴ��� */
#define __SC16IS740_REG_EFCR                 0X0F    /* ���⹦�ܼĴ��� */


#define __SC16IS740_REG_DLL                  0X00    /* ����������LSB */
#define __SC16IS740_REG_DLH                  0X01    /* ����������MSB */
#define __SC16IS740_REG_EFR                  0X02    /* ��ǿ���ܼĴ��� */

#define __SC16IS740_REG_XON1                 0X04
#define __SC16IS740_REG_XON2                 0X05
#define __SC16IS740_REG_XOFF1                0X06
#define __SC16IS740_REG_XOFF2                0X07

#define __SC16IS740_REG_TCR                  0X06    /* ������ƼĴ��� */
#define __SC16IS740_REG_TLR                  0X07    /* ������ƽ�Ĵ��� */