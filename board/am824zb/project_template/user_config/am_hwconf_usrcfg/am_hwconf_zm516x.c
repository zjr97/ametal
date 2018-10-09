/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ZM516X zigbee�����ļ�
 * \sa am_hwconf_zm516x.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  win, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "am_zm516x.h"
#include "am_lpc82x.h"

/**
 * \addtogroup am_if_src_hwconf_zm516x
 * \copydoc am_hwconf_zm516x.c
 * @{
 */

static uint8_t __g_zm516x_txbuf[256];
static uint8_t __g_zm516x_rxbuf[256];

/* ���� ZM516X ʵ�� */
static am_zm516x_dev_t __g_zm516x_dev;

/* ���� ZM516X ʵ����Ϣ */
static const am_zm516x_dev_info_t __g_zm516x_devinfo = {
    PIO0_28,                        /**< \brief ��λ���� */
    PIO0_25,                        /**< \brief ACK ���� */
    10,                             /**< \brief ACK ��ʱʱ�䣬��λΪ���� */
    __g_zm516x_txbuf,               /**< \brief ���ͻ��� */
    sizeof(__g_zm516x_txbuf),       /**< \brief ���ͻ��泤�� */
    __g_zm516x_rxbuf,               /**< \brief ���ջ��� */
    sizeof(__g_zm516x_rxbuf)        /**< \brief ���ջ��泤�� */
};

/**
 * \brief  ZM516Xʵ����ʼ�������ZM516Xģ���׼����������
 *
 * \return  ZM516Xģ���׼����������
 */
am_zm516x_handle_t am_zm516x_inst_init (void)
{
    return am_zm516x_init(&__g_zm516x_dev, &__g_zm516x_devinfo, am_lpc82x_usart1_inst_init());
}

/**
 * @}
 */

/* end of file */
