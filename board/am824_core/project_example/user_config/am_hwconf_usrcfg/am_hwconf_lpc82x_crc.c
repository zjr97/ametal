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
 * \brief LPC82X CRC �û������ļ�
 * \sa am_hwconf_lpc82x_crc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-08  sss, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc_crc.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_crc
 * \copydoc am_hwconf_lpc82x_crc.c
 * @{
 */

/**
 * \brief CRC ƽ̨��ʼ��
 */
am_local void __lpc82x_crc_plfm_init (void)
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_CRC);
}

/**
 * \brief CRC ƽ̨���ʼ��
 */
am_local void __lpc82x_crc_plfm_deinit (void)
{
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_CRC);
}

/** \brief CRC �豸��Ϣ */
am_local am_const am_lpc_crc_devinfo_t __g_lpc82x_crc_devinfo = {
    LPC82X_CRC_BASE,                /* CRC �Ĵ������ַ */
    __lpc82x_crc_plfm_init,         /* ƽ̨��ʼ������ */
    __lpc82x_crc_plfm_deinit        /* ƽ̨���ʼ������ */
};

/** \brief CRC �豸ʵ�� */
am_local am_lpc_crc_dev_t __g_lpc82x_crc_dev;

/**
 * \brief CRC ʵ����ʼ��
 */
am_crc_handle_t am_lpc82x_crc_inst_init (void)
{
    return am_lpc_crc_init(&__g_lpc82x_crc_dev, &__g_lpc82x_crc_devinfo);
}

/**
 * \brief CRC ʵ�����ʼ��
 */
void am_lpc82x_crc_inst_deinit (void)
{
    am_lpc_crc_deinit();
}

/**
 * @}
 */

/* end of file */
