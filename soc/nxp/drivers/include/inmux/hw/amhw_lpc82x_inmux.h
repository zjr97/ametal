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
 * \brief ���븴�� (INMUX) Ӳ�������ӿ�
 *
 * 1. ����DMAͨ����Ӳ������Դ;
 * 2. ����DMAͨ�������������;
 * 3. ����SCT���봥��Դ��
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem, modified.
 * - 1.00 15-07-09  zxl, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_LPC82X_INMUX_H
#define __AMHW_LPC82X_INMUX_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

 /** 
 * \addtogroup amhw_lpc82x_if_inmux
 * \copydoc amhw_lpc82x_inmux.h
 * @{
 */


/**
 * \brief  ���븴�üĴ�����ṹ��
 */
typedef struct amhw_lpc82x_inmux {
    __IO uint32_t dma_inmux[18];      /**< \brief DMA ����Դѡ��Ĵ���        */
    __I  uint32_t reserved[4078];     /**< \brief ����                        */  
    __IO uint32_t dma_mux[2];         /**< \brief DMA ������üĴ���          */
    __I  uint32_t reserved2[6];       /**< \brief ����                        */ 
    __IO uint32_t sct0_inmux[4];      /**< \brief SCT ����ѡ��Ĵ���          */ 
} amhw_lpc82x_inmux_t;


/** \brief DMA ͨ������Դ */
typedef enum amhw_lpc82x_inmux_dma_trig_src {
    AMHW_LPC82X_INMUX_DMA_TRIG_ADC0_SEQA_IRQ = 0, /**< \brief ADC0 ����A�ж�  */
    AMHW_LPC82X_INMUX_DMA_TRIG_ADC0_SEQB_IRQ,     /**< \brief ADC0 ����B�ж�  */
    AMHW_LPC82X_INMUX_DMA_TRIG_SCT0_DMA0,         /**< \brief SCT0 DMA0 ����  */
    AMHW_LPC82X_INMUX_DMA_TRIG_SCT0_DMA1,         /**< \brief SCT1 DMA1 ����  */
    AMHW_LPC82X_INMUX_DMA_TRIG_ACMP_O,            /**< \brief ACMP �Ƚ������ */
    AMHW_LPC82X_INMUX_DMA_TRIG_PININT0,           /**< \brief �����ж� 0      */
    AMHW_LPC82X_INMUX_DMA_TRIG_PININT1,           /**< \brief �����ж� 1      */
    AMHW_LPC82X_INMUX_DMA_TRIG_DMA_MUX0,          /**< \brief DMA ���ô��� 0  */
    AMHW_LPC82X_INMUX_DMA_TRIG_DMA_MUX1,          /**< \brief DMA ���ô��� 1  */
} amhw_lpc82x_inmux_dma_trig_src_t;

/** \brief SCT ���봥��Դ */
typedef enum amhw_lpc82x_inmux_sct_trig_src {
    AMHW_LPC82X_INMUX_SCTTRIG_SCT_PIN0 = 0,    /**< \brief SCT_PIN0.          */
    AMHW_LPC82X_INMUX_SCTTRIG_SCT_PIN1,        /**< \brief SCT_PIN1.          */
    AMHW_LPC82X_INMUX_SCTTRIG_SCT_PIN2,        /**< \brief SCT_PIN2.          */
    AMHW_LPC82X_INMUX_SCTTRIG_SCT_PIN3,        /**< \brief SCT_PIN3.          */
    AMHW_LPC82X_INMUX_SCTTRIG_ADC_THCMP_IRQ,   /**< \brief ADC_THCMP_IRQ      */
    AMHW_LPC82X_INMUX_SCTTRIG_ACMP_O,          /**< \brief ACMP_O             */
    AMHW_LPC82X_INMUX_SCTTRIG_ARM_TXEV,        /**< \brief ARM_TXEV           */
    AMHW_LPC82X_INMUX_DEBUG_HALTED,            /**< \brief DEBUG_HALTED       */
} amhw_lpc82x_inmux_sct_trig_src_t;

/**
 * \brief ����ָ��DMAͨ������Դ
 *
 * \param[in] p_hw_inmux : ָ�����븴�üĴ������ָ��
 * \param[in] chan       : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] trig       : ����Դ
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_inmux_dma_trig_set (amhw_lpc82x_inmux_t            *p_hw_inmux,
                                     uint8_t                         chan,
                                    amhw_lpc82x_inmux_dma_trig_src_t trig)
{
    p_hw_inmux->dma_inmux[chan] = trig;
}

/**
 * \brief ����DMA����������ӵ�DAMͨ��
 *
 * \param[in] p_hw_inmux : ָ�����븴�üĴ������ָ��
 * \param[in] dma_mux    : inmuxͨ��0����1����ӦֵΪ0����1 
 * \param[in] chan       : DMAͨ����ֵΪ DMA_CHAN_*(#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_inmux_dma_mux_set (amhw_lpc82x_inmux_t *p_hw_inmux,
                                    uint8_t              dma_mux,
                                    uint8_t              chan)
{
    p_hw_inmux->dma_mux[dma_mux] = chan;
}

/**
 * \brief ����SCT���봥��Դ
 *
 * \param[in] p_hw_inmux : ָ�����븴�üĴ������ָ��
 * \param[in] chan       : SCTͨ��
 * \param[in] trig       : ����Դ
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_inmux_sct_trig_set (amhw_lpc82x_inmux_t            *p_hw_inmux,
                                     uint8_t                         chan,
                                    amhw_lpc82x_inmux_sct_trig_src_t trig)
{
    p_hw_inmux->sct0_inmux[chan] = trig;
}

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC82X_INMUX_H */

/* end of file */
