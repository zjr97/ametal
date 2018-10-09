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
 * \brief LPC82X SCT �û������ļ�
 * \sa am_hwconf_lpc82x_sct0.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  hgo, first implementation.
 * \endinternal
 */
#include "am_lpc_sct.h"
#include "ametal.h"
#include "am_lpc82x.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc_sct.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_sct0
 * \copydoc am_hwconf_lpc82x_sct0.c
 * @{
 */

/**
 * \brief SCT�¼�ISR ��Ϣ����
 *        �û����Ը���Ӧ����ʵ������Ҫ�õ����¼��жϸ�����������֧��8��
 *        ���޸ĸú�ֵ���Դﵽ����Ҫ���ڴ��˷ѵ�Ŀ�ġ�
 */
#define __SCT_EVT_ISRINFO_COUNT    8

/**
 * \brief SCT���ͨ������
 */
#define __SCT_OUTPUT_COUNT    6

/**
 * \brief SCT DAM����ͨ������
 */
#define __SCT_DMA_REQ_COUNT    2

/**
 * \brief �洢�û��жϻص���Ϣ
 */
static struct am_lpc_sct_evt_isr_info __sct_evt_isr_info[__SCT_EVT_ISRINFO_COUNT];

/**
 * \brief �洢�жϱ�������Ӧ��__sct_evt_isr_info�жϻص���Ϣ��
 *        λ�õ�ӳ�䣬�����Сһ����SCT��֧�ֵ�����¼�������  __SCT_EVT_ISRINFO_COUNT ��ȡ�
 */
static uint8_t __sct_evt_isr_map[__SCT_EVT_ISRINFO_COUNT];

/** \brief SCT0 ƽ̨��ʼ�� */
static void __lpc82x_sct0_plfm_init (void)
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SCT);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);
}

/** \brief ���SCT0ƽ̨��ʼ�� */
static void __lpc82x_sct0_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SCT);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SCT);
}

/** \brief SCT �豸��Ϣ */
static const am_lpc_sct_devinfo_t  __g_sct0_devinfo = {
    LPC82X_SCT0_BASE,               /**< \brief SCT0�Ĵ�����Ļ���ַ */
    INUM_SCT0,                      /**< \brief SCT0�жϱ�� */
    CLK_SCT,                        /**< \brief SCT0ʱ�ӱ�� */
    __SCT_EVT_ISRINFO_COUNT,        /**< \brief ���ж����� */
    __sct_evt_isr_map,              /**< \brief ISR��Ϣӳ���ڴ�(��С�� evt_isr_cntһ��) */
    __SCT_EVT_ISRINFO_COUNT,        /**< \brief ISR��Ϣ���� */
    __sct_evt_isr_info,             /**< \brief ISR��Ϣ�ڴ�(��С�� isrinfo_cntһ��) */

    __SCT_OUTPUT_COUNT,             /**< \brief 8��ͨ����� */
    __SCT_DMA_REQ_COUNT,            /**< \brief 2��DMA����ͨ�� */
    __lpc82x_sct0_plfm_init,        /**< \brief ƽ̨��ʼ������ */
    __lpc82x_sct0_plfm_deinit,      /**< \brief ƽ̨���ʼ������ */
};

/** \brief SCT�豸���� */
static am_lpc_sct_dev_t  __g_sct0_dev;

/** \brief SCT0 ʵ����ʼ�������SCT��׼������ */
am_lpc_sct_handle_t am_lpc82x_sct0_inst_init (void)
{
    return am_lpc_sct_init(&__g_sct0_dev, &__g_sct0_devinfo);
}

/** \brief SCT0 ʵ�����ʼ�� */
void am_lpc82x_sct0_inst_deinit (am_lpc_sct_handle_t handle)
{
    am_lpc_sct_deinit(handle);
}
/**
 * @}
 */

/* end of file */
