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
 * \brief KL26 WDT �û������ļ�
 * \sa am_kl26_hwconfig_wdt.c
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-30  mkr, first implementation.
 * \endinternal
 */
#include "am_kl26_wdt.h"

#include "../../../../../soc/freescale/kl26/kl26_periph_map.h"
/**
 * \addtogroup am_kl26_if_hwconfig_src_wdt
 * \copydoc am_kl26_hwconfig_wdt.c
 * @{
 */

/** \brief WDT ƽ̨��ʼ�� */
static void __kl26_wdt_plfm_init (void)
{
    /* ����Ҫ���������� */
}

/** \brief ���WDT ƽ̨��ʼ�� */
static void __kl26_wdt_plfm_deinit (void)
{
    /* ����Ҫ���������� */
}

/** \brief WDT �豸��Ϣ */
static const am_kl26_wdt_devinfo_t  __g_wdt_devinfo = {
		KL26_SIM,  /* ָ��SIM�Ĵ������ָ�� */

		__kl26_wdt_plfm_init,

		__kl26_wdt_plfm_deinit,

};

/** \brief WDT�豸ʵ��  */
static am_kl26_wdt_dev_t            __g_wdt_dev;

/**
 * \brief  WDT ʵ����ʼ�������WDT��׼������
 *
 * \return WDT���ֵ
 */
am_wdt_handle_t am_kl26_wdt_inst_init (void)
{
    return am_kl26_wdt_init(&__g_wdt_dev, &__g_wdt_devinfo);
}

/**
 * \brief WDT ʵ�����ʼ��
 *
 * \param[in] handle : WDT���Ź����ֵ
 */
void am_kl26_wdt_inst_deinit (am_wdt_handle_t handle)
{
	am_kl26_wdt_deinit(handle);
}


/**
 * @}
 */

/* end of file */
