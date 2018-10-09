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
 * \brief LPC82X DMA �û������ļ�
 * \sa am_hwconf_lpc82x_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-08  mem,modified.
 * - 1.00 15-07-12  win, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "lpc82x_regbase.h"
#include "am_lpc82x_dma.h"
#include "hw/amhw_lpc82x_dma.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_dma
 * \copydoc am_hwconf_lpc82x_dma.c
 * @{
 */

/**
 * \brief ʹ�õ�DMAͨ������
 *
 *        Ĭ��ʹ�����е�DMAͨ�����û����Ը���ʵ��ʹ��ͨ������
 *        ���Ĵ�ֵ������DMA�ڴ��ռ��
 * \note  �����Ҫʹ��DMA,���ֵ����Ӧ��Ϊ1������DMA��ʼ�����ɹ�
 */
#define __DMA_CHAN_USE_COUNT    AMHW_LPC82X_DMA_CHAN_CNT

 /**
 * \brief DMA ƽ̨��ʼ��
 */
static void __lpc82x_dma_plfm_init (void)
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_DMA);
}

/**
 * \brief DMA ƽ̨���ʼ��
 */
static void __lpc82x_dma_plfm_deinit (void)
{
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_DMA);
}

/** \brief ������ӳ��� */
static uint8_t __g_dam_controller_map[AMHW_LPC82X_DMA_CHAN_CNT];

/** \brief �������ڴ� */
static am_lpc82x_dma_controller_t __g_dma_controller[__DMA_CHAN_USE_COUNT];


/** \brief DMA ͨ���������б�����512�ֽڶ��� */
static __attribute__((aligned(512))) am_lpc82x_dma_xfer_desc_t \
                                __g_dma_xfer_tab[AMHW_LPC82X_DMA_CHAN_CNT];

/** \brief DMA �豸��Ϣ */
static const am_lpc82x_dma_devinfo_t __g_dma_devinfo = {
    LPC82X_DMA_BASE,               /**< \brief DMA�Ĵ�����Ļ�ַ             */
    LPC82X_INMUX_BASE,             /**< \brief INMUX�Ĵ�����Ļ�ַ           */
    &__g_dam_controller_map[0],    /**< \brief ָ�������ӳ����ָ��        */
    &__g_dma_controller[0],        /**< \brief ָ��������ڴ��ָ��          */
    &__g_dma_xfer_tab[0],          /**< \brief ��������������ַ��512�ֽڶ��� */
    __DMA_CHAN_USE_COUNT,          /**< \brief ʹ�õ�DMAͨ������             */
    INUM_DMA,                      /**< \brief DMA�жϺ�                     */

    __lpc82x_dma_plfm_init,        /**< \brief ƽ̨��ʼ������                */
    __lpc82x_dma_plfm_deinit,      /**< \brief ƽ̨���ʼ������              */
};

/** \brief DMA�豸ʵ�� */
static am_lpc82x_dma_dev_t __g_dma_dev;

/** \brief DMA ʵ����ʼ�� */
int am_lpc82x_dma_inst_init (void)
{
    return am_lpc82x_dma_init(&__g_dma_dev, &__g_dma_devinfo);
}

/** \brief DMA ʵ�����ʼ�� */
void am_lpc82x_dma_inst_deinit (void)
{
    am_lpc82x_dma_deinit();
}

/**
 * @}
 */

/* end of file */
