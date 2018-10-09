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
 * \brief  I2SӲ����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-27  mkr, first implementation.
 * \endinternal
 */

#include "hw/amhw_fsl_i2s.h"

/**
 * \brief I2S��ʱ�ӷ�Ƶ����
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] mclk     : i2s��ʱ��Ƶ��
 * \param[in] src_clk  : ��ʱ��ʹ�õ�ʱ��ԴƵ��
 *
 * \return  ��
 */
void amhw_fsl_i2s_mclk_divider_cfg (amhw_fsl_i2s_t *p_hw_i2s,
                                     uint32_t         mclk,
                                     uint32_t         src_clk)
{
    uint32_t freq    = src_clk;
    uint16_t fract, divide;
    uint32_t remaind = 0;
    uint32_t current_remainder = 0xffffffff;
    uint16_t current_fract     = 0;
    uint16_t current_divide    = 0;
    uint32_t mul_freq          = 0;
    uint32_t max_fract         = 256;

    /* ��ֹ��� */
    freq /= 100;
    mclk /= 100;

    max_fract = mclk * 4096 / freq + 1;

    if(max_fract > 256) {
        max_fract = 256;
    }

    /* Ѱ����ӽ���Ƶ�� */
    for (fract = 1; fract < max_fract; fract ++) {
        mul_freq = freq * fract;
        remaind  = mul_freq % mclk;
        divide   = mul_freq / mclk;

        /* �ҵ���ȷ��Ƶ�� */
        if (remaind == 0) {
            current_fract  = fract;
            current_divide = mul_freq / mclk;
            break;
        }

        /* ����Ļ���һ�� */
        if (remaind > mclk/2) {
            remaind = mclk - remaind;
            divide += 1;
        }

        /* ���·�Ƶϵ��  */
        if (remaind < current_remainder) {
            current_fract = fract;
            current_divide = divide;
            current_remainder = remaind;
        }
    }

    amhw_fsl_i2s_mclk_div_set(p_hw_i2s, current_divide - 1);

    /* �ȴ���Ƶ������Ƶ�� */
    while(amhw_fsl_i2s_mclk_duf_get(p_hw_i2s)) {
    }

    amhw_fsl_i2s_mclk_fract_set(p_hw_i2s, current_fract - 1);

    /* �ȴ���Ƶ������Ƶ�� */
    while(amhw_fsl_i2s_mclk_duf_get(p_hw_i2s)) {
    }
}

/**
 * \brief I2S���ͼĴ�����ʼ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_init (amhw_fsl_i2s_t *p_hw_i2s)
{
    /** \brief ��λI2S������,�����λ��FIFO��λ */
    amhw_fsl_i2s_tcsr_set(p_hw_i2s, AMHW_FSL_I2S_TCSR_SR_MASK);
    amhw_fsl_i2s_tcsr_set(p_hw_i2s, AMHW_FSL_I2S_TCSR_FR_MASK);

    /** \brief ���I2S������ؼĴ��� */
    p_hw_i2s->tcsr = 0;
    p_hw_i2s->tcr2 = 0;
    p_hw_i2s->tcr3 = 0;
    p_hw_i2s->tcr4 = 0;
    p_hw_i2s->tcr5 = 0;
//    p_hw_i2s->tdr  = 0;
    p_hw_i2s->tmr  = 0;
}

/**
 * \brief I2S���ռĴ�����ʼ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \return  ��
 */
void amhw_fsl_i2s_rx_init (amhw_fsl_i2s_t *p_hw_i2s)
{
    /** \brief ��λI2S������,�����λ��FIFO��λ */
    amhw_fsl_i2s_rcsr_set(p_hw_i2s, AMHW_FSL_I2S_RCSR_SR_MASK);
    amhw_fsl_i2s_rcsr_set(p_hw_i2s, AMHW_FSL_I2S_RCSR_FR_MASK);

    /** \brief ���I2S���н�����ؼĴ��� */
    p_hw_i2s->rcsr = 0;
    p_hw_i2s->rcr2 = 0;
    p_hw_i2s->rcr3 = 0;
    p_hw_i2s->rcr4 = 0;
    p_hw_i2s->rcr5 = 0;
    p_hw_i2s->rmr = 0;
}

/**
 * \brief I2S��Э������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] protocol : ʹ�õ�I2SЭ��
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_protocol_set (amhw_fsl_i2s_t          *p_hw_i2s,
                                    amhw_fsl_i2s_protocol_t  protocol)
{
    switch (protocol) {

    case AMHW_FSL_I2S_PROTOCOL_LEFT:
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_BCP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_MF_MASK);
        amhw_fsl_i2s_tcr4_clr(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSE_MASK);
        amhw_fsl_i2s_tcr4_clr(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FRSZ_MASK);
        amhw_fsl_i2s_tcr3_clr(p_hw_i2s, AMHW_FSL_I2S_TCR3_WDFL_MASK);
        break;

    case AMHW_FSL_I2S_PROTOCOL_RIGHET:
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_BCP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_MF_MASK);
        amhw_fsl_i2s_tcr4_clr(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSE_MASK);
        amhw_fsl_i2s_tcr4_clr(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FRSZ_MASK);
        amhw_fsl_i2s_tcr3_clr(p_hw_i2s, AMHW_FSL_I2S_TCR3_WDFL_MASK);
        break;

    case AMHW_FSL_I2S_PROTOCOL_TYPE:
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_BCP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_MF_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSE_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FRSZ_MASK);
        amhw_fsl_i2s_tcr3_clr(p_hw_i2s, AMHW_FSL_I2S_TCR3_WDFL_MASK);
        break;

    case AMHW_FSL_I2S_PROTOCOL_PCMA:
        amhw_fsl_i2s_tcr2_clr(p_hw_i2s, AMHW_FSL_I2S_TCR2_BCP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_MF_MASK);
        amhw_fsl_i2s_tx_sywd_set(p_hw_i2s, 0u);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSE_MASK);
        amhw_fsl_i2s_tcr4_clr(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FRSZ_MASK);
        amhw_fsl_i2s_tcr3_clr(p_hw_i2s, AMHW_FSL_I2S_TCR3_WDFL_MASK);
        break;

    case AMHW_FSL_I2S_PROTOCOL_PCMB:
        amhw_fsl_i2s_tcr2_clr(p_hw_i2s, AMHW_FSL_I2S_TCR2_BCP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_MF_MASK);
        amhw_fsl_i2s_tcr4_clr(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSE_MASK);
        amhw_fsl_i2s_tx_sywd_set(p_hw_i2s, 0u);
        amhw_fsl_i2s_tcr4_clr(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSP_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FRSZ_MASK);
        amhw_fsl_i2s_tcr3_clr(p_hw_i2s, AMHW_FSL_I2S_TCR3_WDFL_MASK);
        break;

    default:
        break;
    }
}

/**
 * \brief I2S����Э������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] protocol : ʹ�õ�I2SЭ��
 * \return  ��
 */
void amhw_fsl_i2s_rx_protocol_set (amhw_fsl_i2s_t *p_hw_i2s, amhw_fsl_i2s_protocol_t protocol)
{
    switch (protocol)
    {
        case AMHW_FSL_I2S_PROTOCOL_LEFT:
            amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_BCP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_MF_MASK);
            amhw_fsl_i2s_rcr4_clr(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSE_MASK);
            amhw_fsl_i2s_rcr4_clr(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FRSZ_MASK);
            amhw_fsl_i2s_rcr3_clr(p_hw_i2s, AMHW_FSL_I2S_RCR3_WDFL_MASK);
            break;

        case AMHW_FSL_I2S_PROTOCOL_RIGHET:
            amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_BCP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_MF_MASK);
            amhw_fsl_i2s_rcr4_clr(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSE_MASK);
            amhw_fsl_i2s_rcr4_clr(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FRSZ_MASK);
            amhw_fsl_i2s_rcr3_clr(p_hw_i2s, AMHW_FSL_I2S_RCR3_WDFL_MASK);
            break;

        case AMHW_FSL_I2S_PROTOCOL_TYPE:
            amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_BCP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_MF_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSE_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FRSZ_MASK);
            amhw_fsl_i2s_rcr3_clr(p_hw_i2s, AMHW_FSL_I2S_RCR3_WDFL_MASK);
            break;

        case AMHW_FSL_I2S_PROTOCOL_PCMA:
            amhw_fsl_i2s_rcr2_clr(p_hw_i2s, AMHW_FSL_I2S_RCR2_BCP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_MF_MASK);
            amhw_fsl_i2s_rx_sywd_set(p_hw_i2s, 0u);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSE_MASK);
            amhw_fsl_i2s_rcr4_clr(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FRSZ_MASK);
            amhw_fsl_i2s_rcr3_clr(p_hw_i2s, AMHW_FSL_I2S_RCR3_WDFL_MASK);
            break;

        case AMHW_FSL_I2S_PROTOCOL_PCMB:
            amhw_fsl_i2s_rcr2_clr(p_hw_i2s, AMHW_FSL_I2S_RCR2_BCP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_MF_MASK);
            amhw_fsl_i2s_rcr4_clr(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSE_MASK);
            amhw_fsl_i2s_rx_sywd_set(p_hw_i2s, 0u);
            amhw_fsl_i2s_rcr4_clr(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSP_MASK);
            amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FRSZ_MASK);
            amhw_fsl_i2s_rcr3_clr(p_hw_i2s, AMHW_FSL_I2S_RCR3_WDFL_MASK);
            break;

        default:
            break;
        }
}


/**
 * \brief I2S����ʱ������
 * \param[in] p_hw_i2s   : ָ��I2S�Ĵ������ָ��
 * \param[in] clk_config : i2s����ʱ�����ò���
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_clock_setup (amhw_fsl_i2s_t           *p_hw_i2s,
                                  amhw_fsl_i2s_clock_cfg_t *clk_config)
{
    uint32_t bclk_div;

    bclk_div = clk_config->bclk_src_freq / clk_config->bclk;
    amhw_fsl_i2s_tx_bclk_src_set(p_hw_i2s, clk_config->bclk_src);
    amhw_fsl_i2s_tx_bclk_div_set(p_hw_i2s, (bclk_div / 2 - 1));

    /* ���λʱ��Դ��MCLK, ����MCLKʱ�ӷ�Ƶ */
    if (clk_config->bclk_src == AMHW_FSL_I2S_BCLK_SRC_MCLK) {
        /* ʹ�� MCLK */
        amhw_fsl_i2s_mclk_enable(p_hw_i2s);

        /* ���� MCLK ʱ��Դ*/
        amhw_fsl_i2s_mclk_src_set(p_hw_i2s, clk_config->mclk_src);

        /* ���� MCLK ��Ƶ�� */
        amhw_fsl_i2s_mclk_divider_cfg(p_hw_i2s,
                                      clk_config->mclk,
                                      clk_config->mclk_src_freq);
    }
}

/**
 * \brief I2S����ʱ������
 * \param[in] p_hw_i2s   : ָ��I2S�Ĵ������ָ��
 * \param[in] clk_config : i2s����ʱ�����ò���
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_clock_setup (amhw_fsl_i2s_t *p_hw_i2s,
                              amhw_fsl_i2s_clock_cfg_t *clk_config)
{
    uint32_t bclk_div;

    bclk_div = clk_config->bclk_src_freq / clk_config->bclk;
    amhw_fsl_i2s_rx_bclk_src_set(p_hw_i2s, clk_config->bclk_src);
    amhw_fsl_i2s_rx_bclk_div_set(p_hw_i2s, (bclk_div / 2 - 1));

    /* ���λʱ��Դ��MCLK, ����MCLKʱ�ӷ�Ƶ */
    if (clk_config->bclk_src == AMHW_FSL_I2S_BCLK_SRC_MCLK) {
        /* ʹ�� MCLK */
        amhw_fsl_i2s_mclk_enable(p_hw_i2s);

        /* ���� MCLK ʱ��Դ*/
        amhw_fsl_i2s_mclk_src_set(p_hw_i2s, clk_config->mclk_src);

        /* ���� MCLK ��Ƶ�� */
        amhw_fsl_i2s_mclk_divider_cfg(p_hw_i2s,
                                       clk_config->mclk,
                                       clk_config->mclk_src_freq);
    }
}

/**
 * \brief I2S�����ֳ�������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] protocol : ʹ�õ�I2SЭ��
 * \param[in] bits     : λ����
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_word_width_cfg (amhw_fsl_i2s_t          *p_hw_i2s,
                                      amhw_fsl_i2s_protocol_t  protocol,
                                      uint32_t                  bits)
{
    if ((protocol == AMHW_FSL_I2S_PROTOCOL_LEFT)   ||
        (protocol == AMHW_FSL_I2S_PROTOCOL_RIGHET) ||
        (protocol == AMHW_FSL_I2S_PROTOCOL_TYPE)) {
        amhw_fsl_i2s_tx_sywd_set(p_hw_i2s, bits - 1);
    }

    amhw_fsl_i2s_tx_w0w_set(p_hw_i2s, bits - 1);
    amhw_fsl_i2s_tx_wnw_set(p_hw_i2s, bits - 1);
    amhw_fsl_i2s_tx_fbt_set(p_hw_i2s, bits - 1);
}

/**
 * \brief I2S�����ֳ�������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] protocol : ʹ�õ�I2SЭ��
 * \param[in] bits     : λ����
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_word_width_cfg (amhw_fsl_i2s_t          *p_hw_i2s,
                                      amhw_fsl_i2s_protocol_t  protocol,
                                      uint32_t                  bits)
{
    if ((protocol == AMHW_FSL_I2S_PROTOCOL_LEFT)   ||
        (protocol == AMHW_FSL_I2S_PROTOCOL_RIGHET) ||
        (protocol == AMHW_FSL_I2S_PROTOCOL_TYPE)) {
        amhw_fsl_i2s_rx_sywd_set(p_hw_i2s, bits - 1);
    }

    amhw_fsl_i2s_rx_w0w_set(p_hw_i2s, bits - 1);
    amhw_fsl_i2s_rx_wnw_set(p_hw_i2s, bits - 1);
    amhw_fsl_i2s_rx_fbt_set(p_hw_i2s, bits - 1);
}

/**
 * \brief I2S����ͨ��ģʽ���ã�����������������
 * \param[in] p_hw_i2s     : ָ��I2S�Ĵ������ָ��
 * \param[in] channel_mode : ����ͨ��ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_channel_mode_set (amhw_fsl_i2s_t              *p_hw_i2s,
                                        amhw_fsl_i2s_channel_mode_t  channel_mode)
{
    if (channel_mode == AMHW_FSL_I2S_CHANNEL_MODE_MONO) {
        amhw_fsl_i2s_tx_mask_set(p_hw_i2s, 2);
    } else {
        amhw_fsl_i2s_tx_mask_set(p_hw_i2s, 0);
    }
}

/**
 * \brief I2S����ͨ��ģʽ���ã�����������������
 * \param[in] p_hw_i2s     : ָ��I2S�Ĵ������ָ��
 * \param[in] channel_mode : ����ͨ��ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_channel_mode_set (amhw_fsl_i2s_t              *p_hw_i2s,
                                        amhw_fsl_i2s_channel_mode_t  channel_mode)
{
    if (channel_mode == AMHW_FSL_I2S_CHANNEL_MODE_MONO) {
        amhw_fsl_i2s_rx_mask_set(p_hw_i2s, 2);
    } else {
        amhw_fsl_i2s_rx_mask_set(p_hw_i2s, 0);
    }
}

/**
 * \brief I2S��������ģʽ����
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] tx_mode  : ����ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_mode_set (amhw_fsl_i2s_t      *p_hw_i2s,
                                amhw_fsl_i2s_mode_t  tx_mode)

{
    if (tx_mode == AMHW_FSL_I2S_MODE_MASTER) {
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_BCD_MASK);
        amhw_fsl_i2s_tcr4_set(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSD_MASK);
        amhw_fsl_i2s_mclk_enable(p_hw_i2s);
    } else {
        amhw_fsl_i2s_tcr2_clr(p_hw_i2s, AMHW_FSL_I2S_TCR2_BCD_MASK);
        amhw_fsl_i2s_tcr4_clr(p_hw_i2s, AMHW_FSL_I2S_TCR4_FSD_MASK);
        amhw_fsl_i2s_mclk_disable(p_hw_i2s);
    }
}

/**
 * \brief I2S��������ģʽ����
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] rx_mode  : ����ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_mode_set (amhw_fsl_i2s_t *p_hw_i2s,
                                amhw_fsl_i2s_mode_t rx_mode)

{
    if (rx_mode == AMHW_FSL_I2S_MODE_MASTER) {
        amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_BCD_MASK);
        amhw_fsl_i2s_rcr4_set(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSD_MASK);
        amhw_fsl_i2s_mclk_enable(p_hw_i2s);
    } else {
        amhw_fsl_i2s_rcr2_clr(p_hw_i2s, AMHW_FSL_I2S_RCR2_BCD_MASK);
        amhw_fsl_i2s_rcr4_clr(p_hw_i2s, AMHW_FSL_I2S_RCR4_FSD_MASK);
        amhw_fsl_i2s_mclk_disable(p_hw_i2s);
    }
}

/**
 * \brief I2S����ͬ����ģʽ����
 * \param[in] p_hw_i2s  : ָ��I2S�Ĵ������ָ��
 * \param[in] sync_mode : ����ͬ����ģʽ
 * \return  ��
 */
void amhw_fsl_i2s_tx_sync_mode_set (amhw_fsl_i2s_t           *p_hw_i2s,
                                     amhw_fsl_i2s_sync_mode_t  sync_mode)
{
    switch (sync_mode) {

    case AMHW_FSL_I2S_SYNC_DISABLED:
        amhw_fsl_i2s_tcr2_clr(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_MASK);
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_DISABLE);
        break;

    case AMHW_FSL_I2S_SYNC_SELF:
        amhw_fsl_i2s_tcr2_clr(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_MASK);
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_SELF_RX);
        /* ���������빤�����첽ģʽ */
        amhw_fsl_i2s_rcr2_clr(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_MASK);
        amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_DISABLE);
        break;

    case AMHW_FSL_I2S_SYNC_ANOTHER_TX:
        amhw_fsl_i2s_tcr2_clr(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_MASK);
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_ANOTHER_TX);
        break;

    case AMHW_FSL_I2S_SYNC_ANOTHER_RX:
        amhw_fsl_i2s_tcr2_clr(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_MASK);
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_ANOTHER_RX);
        break;

    default:
        break;
    }
}

/**
 * \brief I2S����ͬ����ģʽ����
 * \param[in] p_hw_i2s  : ָ��I2S�Ĵ������ָ��
 * \param[in] sync_mode : ����ͬ����ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_sync_mode_set (amhw_fsl_i2s_t *p_hw_i2s,
                                amhw_fsl_i2s_sync_mode_t sync_mode)
{
    switch (sync_mode) {

    case AMHW_FSL_I2S_SYNC_DISABLED:
        amhw_fsl_i2s_rcr2_clr(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_MASK);
        amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_DISABLE);
        break;

    case AMHW_FSL_I2S_SYNC_SELF:
        amhw_fsl_i2s_rcr2_clr(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_MASK);
        amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_SELF_TX);
        /* ���������빤�����첽ģʽ */
        amhw_fsl_i2s_tcr2_clr(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_MASK);
        amhw_fsl_i2s_tcr2_set(p_hw_i2s, AMHW_FSL_I2S_TCR2_SYNC_DISABLE);
        break;

    case AMHW_FSL_I2S_SYNC_ANOTHER_TX:
        amhw_fsl_i2s_rcr2_clr(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_MASK);
        amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_ANOTHER_TX);
        break;

    case AMHW_FSL_I2S_SYNC_ANOTHER_RX:
        amhw_fsl_i2s_rcr2_clr(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_MASK);
        amhw_fsl_i2s_rcr2_set(p_hw_i2s, AMHW_FSL_I2S_RCR2_SYNC_ANOTHER_RX);
        break;

    default:
        break;
    }
}

/**
 * \brief I2S �������״̬��־
 * \param[in] p_hw_i2s  : ָ��I2S�Ĵ������ָ��
 * \param[in] flag_mask : ״̬��־����
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_state_flag_clr (amhw_fsl_i2s_t            *p_hw_i2s,
                                     amhw_fsl_i2s_state_flag_t  flag_mask)
{
    /* FIFO���治����� */
    if (flag_mask & AMHW_FSL_I2S_STATE_FLAG_FIFO_WARNING) {
        flag_mask &= (uint32_t)(~AMHW_FSL_I2S_STATE_FLAG_FIFO_WARNING);
    }

    /* ����Ƿ�Ҫ��������λ */
    if (flag_mask & AMHW_FSL_I2S_STATE_FLAG_SOFT_RESET) {
        flag_mask &= (uint32_t)(~AMHW_FSL_I2S_STATE_FLAG_SOFT_RESET);
        amhw_fsl_i2s_tcsr_clr(p_hw_i2s, AMHW_FSL_I2S_TCSR_SR_MASK);
    }

    /* д1�������״̬��־ */
    amhw_fsl_i2s_tcsr_set(p_hw_i2s, flag_mask);
}

/**
 * \brief I2S �������״̬��־
 * \param[in] p_hw_i2s  : ָ��I2S�Ĵ������ָ��
 * \param[in] flag_mask : ״̬��־����
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_state_flag_clr (amhw_fsl_i2s_t            *p_hw_i2s,
                                      amhw_fsl_i2s_state_flag_t  flag_mask)
{
    /* FIFO���治����� */
    if (flag_mask & AMHW_FSL_I2S_STATE_FLAG_FIFO_WARNING) {
        flag_mask &= (uint32_t)(~AMHW_FSL_I2S_STATE_FLAG_FIFO_WARNING);
    }

    /* ����Ƿ�Ҫ��������λ */
    if (flag_mask & AMHW_FSL_I2S_STATE_FLAG_SOFT_RESET) {
        flag_mask &= (uint32_t)(~AMHW_FSL_I2S_STATE_FLAG_SOFT_RESET);
        amhw_fsl_i2s_rcsr_clr(p_hw_i2s, AMHW_FSL_I2S_RCSR_SR_MASK);
    }

    /* д1�������״̬��־ */
    amhw_fsl_i2s_rcsr_set(p_hw_i2s, flag_mask);
}

/**
 * \brief I2S��������λ
 * \param[in] p_hw_i2s   : ָ��I2S�Ĵ������ָ��
 * \param[in] reset_mask : ��λ������
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_reset_set (amhw_fsl_i2s_t            *p_hw_i2s,
                                 amhw_fsl_i2s_reset_type_t  reset_mask)
{
    amhw_fsl_i2s_tcsr_set(p_hw_i2s, reset_mask);
}

/**
 * \brief I2S��������λ
 * \param[in] p_hw_i2s   : ָ��I2S�Ĵ������ָ��
 * \param[in] reset_mask : ��λ������
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_reset_set (amhw_fsl_i2s_t            *p_hw_i2s,
                                amhw_fsl_i2s_reset_type_t  reset_mask)
{
    amhw_fsl_i2s_rcsr_set(p_hw_i2s, reset_mask);
}

/**
 * \brief I2S�������ݣ���ѯģʽ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] txBuff   : ָ��Ҫ���ͻ�������ָ��
 * \param[in] size     : Ҫ�������ݵĳ���
 *
 * \return  ��
 */
void amhw_fsl_i2s_senddata_polling (amhw_fsl_i2s_t  *p_hw_i2s,
                                    uint32_t        *txbuff,
                                    uint32_t         size)
{
    while (size--) {
        /* ���FIFO ���� */
        if ((amhw_fsl_i2s_tcsr_get(p_hw_i2s) & AMHW_FSL_I2S_TCSR_FEF_MASK)) {
            amhw_fsl_i2s_tx_reset_set(p_hw_i2s, AMHW_FSL_I2S_RESET_TYPE_FIFO);
            amhw_fsl_i2s_tx_state_flag_clr(p_hw_i2s, AMHW_FSL_I2S_STATE_FLAG_FIFO_ERROR);
        }

        /* �ȴ�FIFO Ϊ�� */
        while (!(amhw_fsl_i2s_tcsr_get(p_hw_i2s) & AMHW_FSL_I2S_TCSR_FWF_MASK)) {
            if ((amhw_fsl_i2s_tcsr_get(p_hw_i2s) & AMHW_FSL_I2S_TCSR_FEF_MASK)) {
                amhw_fsl_i2s_tx_reset_set(p_hw_i2s, AMHW_FSL_I2S_RESET_TYPE_FIFO);
                amhw_fsl_i2s_tx_state_flag_clr(p_hw_i2s, AMHW_FSL_I2S_STATE_FLAG_FIFO_ERROR);
            }
        }

        amhw_fsl_i2s_txdata_write(p_hw_i2s, *txbuff);
        txbuff++;
    }

}

/**
 * \brief I2S�������ݣ���ѯģʽ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] rxBuff   : ָ��Ҫ���ջ�������ָ��
 * \param[in] size     : Ҫ�������ݵĳ���
 *
 * \return  ��
 */
void amhw_fsl_i2s_receivedata_polling (amhw_fsl_i2s_t *p_hw_i2s,
                                       uint8_t         *rxBuff,
                                       uint32_t         size)
{
    while (size --) {
        /* ���FIFO�����־  */
        if ((amhw_fsl_i2s_rcsr_get(p_hw_i2s) & AMHW_FSL_I2S_RCSR_FEF_MASK)) {
            amhw_fsl_i2s_rx_state_flag_clr(p_hw_i2s, AMHW_FSL_I2S_STATE_FLAG_FIFO_ERROR);
        }

        /* �ȴ�FIFO Ϊ�� */
        while (!(amhw_fsl_i2s_rcsr_get(p_hw_i2s) & AMHW_FSL_I2S_RCSR_FWF_MASK)) {
        }

        *rxBuff = amhw_fsl_i2s_rxdata_read(p_hw_i2s);
         rxBuff++;
    }
}

/* end of file */
