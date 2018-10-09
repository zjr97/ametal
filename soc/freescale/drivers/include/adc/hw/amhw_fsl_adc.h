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
 * \brief ADC Ӳ�������ӿ�
 *
 * 1. 16λ��αƽ�����ģת������
 * 2. �ߴ�4�Բ�����룬24������ģ�����룻
 * 3. ���λ�����ת����ת������Զ���Χ����״̬��
 * 4. �����ò���ʱ�䣬ת���ٶȻ򹦺ģ�
 * 5. ��ѡ���/����ֵ�ȽϺ�Ӳ��ƽ����
 * 6. ת����ɻ�Ӳ��ƽ������ж�����
 * 7. �ĸ���ѡʱ��Դ��
 * 8. �Դ��¶ȴ�������
 * 9. ��ѡ�Ĳο���ѹԴ��
 * 10. Ӳ��У��ģʽ;
 * 11. 2������������ת�����У�
 * 12. ֧�����ģʽ�У�
 *     ---16λ��13λ��11λ��9λ�������ģʽ
 *     ---16λ��12λ��10λ��8λ��������ģʽ
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-14  mkr, first implementation.
 * \endinternal
 */
#ifndef  __AMHW_FSL_ADC_H
#define  __AMHW_FSL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif
#include "am_types.h"
#include "am_clk.h"

/**
 * \addtogroup amhw_fsl_if_adc
 * \copydoc amhw_fsl_adc.h
 * @{
 */

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */


/**
 * \brief ADC �Ĵ�����ṹ��
 */
typedef struct amhw_fsl_adc {
    union {
        __IO uint32_t sc1[2];      /**< \brief ADC ״̬���ƼĴ���1      */
        struct {
            __IO uint32_t sc1_a;   /**< \brief ADC ����A���ƼĴ���     */
            __IO uint32_t sc1_b;   /**< \brief ADC ����B���ƼĴ���     */
        };
    };
    __IO uint32_t cfg1;           /**< \brief ADC ���üĴ���1     */
    __IO uint32_t cfg2;           /**< \brief ADC ���üĴ���2     */

    union {
        __I uint32_t dat[2];       /**< \brief ADC ���ݼĴ���      */
        struct {
            __I uint32_t dat_a;    /**< \brief ADC ����A���ݼĴ���     */
            __I uint32_t dat_b;    /**< \brief ADC ����B���ݼĴ���2     */
        };
    };
    union {
        __IO uint32_t cv[2];      /**< \brief ADC ��ֵ�Ĵ���      */
        struct {
            __IO uint32_t cv_1;    /**< \brief ADC ��ֵ1�Ĵ���     */
            __IO uint32_t cv_2;    /**< \brief ADC ��ֵ2�Ĵ���     */
        };
    };
    __IO uint32_t sc2;      /**< \brief ADC ״̬���ƼĴ���2      */
    __IO uint32_t sc3;      /**< \brief ADC ״̬���ƼĴ���3      */

    __IO uint32_t ofs;      /**< \brief ADC ƫ�ƽ����Ĵ���      */
    __IO uint32_t pg;      /**< \brief ADC Plus-Side����Ĵ���      */
    __IO uint32_t mg;      /**< \brief ADC Minus-Side���ƼĴ���      */

    union {
        __IO uint32_t clp[7];      /**< \brief ADC Plus-Side����ֵ�Ĵ���  */
        struct {
            __IO uint32_t clp_d;    /**< \brief ADC Plus-Side����ֵ�Ĵ���D */
            __IO uint32_t clp_s;    /**< \brief ADC Plus-Side����ֵ�Ĵ���S */
            __IO uint32_t clp_4;    /**< \brief ADC Plus-Side����ֵ�Ĵ���4 */
            __IO uint32_t clp_3;    /**< \brief ADC Plus-Side����ֵ�Ĵ���3 */
            __IO uint32_t clp_2;    /**< \brief ADC Plus-Side����ֵ�Ĵ���2 */
            __IO uint32_t clp_1;    /**< \brief ADC Plus-Side����ֵ�Ĵ���1 */
            __IO uint32_t clp_0;    /**< \brief ADC Plus-Side����ֵ�Ĵ���0 */
        };
    };
    union {
        __IO uint32_t clm[7];      /**< \brief ADC Minus-Side����ֵ�Ĵ���  */
        struct {
            __IO uint32_t clm_d;    /**< \brief ADC Minus-Side����ֵ�Ĵ���D */
            __IO uint32_t clm_s;    /**< \brief ADC Minus-Side����ֵ�Ĵ���S */
            __IO uint32_t clm_4;    /**< \brief ADC Minus-Side����ֵ�Ĵ���4 */
            __IO uint32_t clm_3;    /**< \brief ADC Minus-Side����ֵ�Ĵ���3 */
            __IO uint32_t clm_2;    /**< \brief ADC Minus-Side����ֵ�Ĵ���2 */
            __IO uint32_t clm_1;    /**< \brief ADC Minus-Side����ֵ�Ĵ���1 */
            __IO uint32_t clm_0;    /**< \brief ADC Minus-Side����ֵ�Ĵ���0 */
        };
    };
} amhw_fsl_adc_t;


/**
 * \brief ADC ���мĴ�������
 * \anchor grp_amhw_adc_chan
 */
typedef enum amhw_fsl_adc_chan {
    AMHW_FSL_ADC_CHAN_0       = 0 ,         /**< \brief ADC ͨ�� 0   */
    AMHW_FSL_ADC_CHAN_1       = 1 ,         /**< \brief ADC ͨ�� 1   */
    AMHW_FSL_ADC_CHAN_2       = 2 ,         /**< \brief ADC ͨ�� 2   */
    AMHW_FSL_ADC_CHAN_3       = 3 ,         /**< \brief ADC ͨ�� 3   */
    AMHW_FSL_ADC_CHAN_4       = 4 ,         /**< \brief ADC ͨ�� 4   */
    AMHW_FSL_ADC_CHAN_5       = 5 ,         /**< \brief ADC ͨ�� 5   */
    AMHW_FSL_ADC_CHAN_6       = 6 ,         /**< \brief ADC ͨ�� 6   */
    AMHW_FSL_ADC_CHAN_7       = 7 ,         /**< \brief ADC ͨ�� 7   */
    AMHW_FSL_ADC_CHAN_8       = 8 ,         /**< \brief ADC ͨ�� 8   */
    AMHW_FSL_ADC_CHAN_9       = 9 ,         /**< \brief ADC ͨ�� 9   */
    AMHW_FSL_ADC_CHAN_10      = 10,         /**< \brief ADC ͨ�� 10  */
    AMHW_FSL_ADC_CHAN_11      = 11,         /**< \brief ADC ͨ�� 11  */
    AMHW_FSL_ADC_CHAN_12      = 12,         /**< \brief ADC ͨ�� 12  */
    AMHW_FSL_ADC_CHAN_13      = 13,         /**< \brief ADC ͨ�� 13  */
    AMHW_FSL_ADC_CHAN_14      = 14,         /**< \brief ADC ͨ�� 14  */
    AMHW_FSL_ADC_CHAN_15      = 15,         /**< \brief ADC ͨ�� 15  */
    AMHW_FSL_ADC_CHAN_16      = 16,         /**< \brief ADC ͨ�� 16  */
    AMHW_FSL_ADC_CHAN_17      = 17,         /**< \brief ADC ͨ�� 17  */
    AMHW_FSL_ADC_CHAN_18      = 18,         /**< \brief ADC ͨ�� 18  */
    AMHW_FSL_ADC_CHAN_19      = 19,         /**< \brief ADC ͨ�� 19  */
    AMHW_FSL_ADC_CHAN_20      = 20,         /**< \brief ADC ͨ�� 20  */
    AMHW_FSL_ADC_CHAN_21      = 21,         /**< \brief ADC ͨ�� 21  */
    AMHW_FSL_ADC_CHAN_22      = 22,         /**< \brief ADC ͨ�� 22  */
    AMHW_FSL_ADC_CHAN_23      = 23,         /**< \brief ADC ͨ�� 23  */
    AMHW_FSL_ADC_CHAN_TEMP    = 26,         /**< \brief ADC ͨ�� 11  */
    AMHW_FSL_ADC_CHAN_BANDGAP = 27,         /**< \brief ADC ͨ������ */
    AMHW_FSL_ADC_CHAN_VREFSH  = 29,         /**< \brief ADC ͨ������ */
    AMHW_FSL_ADC_CHAN_VREFSL  = 30,         /**< \brief ADC ͨ������ */
    AMHW_FSL_ADC_CHAN_CLOSE   = 31,         /**< \brief ADC ͨ������ */
} amhw_fsl_adc_chan_t;
/**
 * \brief ADC ���мĴ�������
 */
typedef enum amhw_fsl_adc_seq_index {
    AMHW_FSL_ADC_SEQ_A = 0,                      /**< \brief ����A����    */
    AMHW_FSL_ADC_SEQ_B = 1,                      /**< \brief ����B����    */
} amhw_fsl_adc_seq_index_t;


/**
 * \name ADC ���ƼĴ���λ����
 * \anchor grp_amhw_fsl_adc_sc1
 * @{
 */
#define AMHW_FSL_ADC_SC1_COCO_MASK   (1UL << 7)      /**< \brief ת����ɱ�־���� */
#define AMHW_FSL_ADC_SC1_INT_MASK    (1UL << 6)      /**< \brief �ж�ʹ������ */
#define AMHW_FSL_ADC_SC1_DIFF_MASK   (1UL << 5)      /**< \brief �������ʹ������ */
#define AMHW_FSL_ADC_SC1_CHAN_MASK   (0x1FUL)        /**< \brief ͨ������ */

#define AMHW_FSL_ADC_SC1_INT_EN_CFG  (1UL << 6)      /**< \brief �ж�ʹ������ */
#define AMHW_FSL_ADC_SC1_DIFF_EN_CFG (1UL << 5)      /**< \brief �������ʹ������ */
/** \brief ͨ��ѡ������ */
#define AMHW_FSL_ADC_SC1_CHAN_SEL_CFG(x) ((x) & AMHW_FSL_ADC_SC1_CHAN_MASK)
/** @} */

/**
 * \brief ʹ��ADCת������ж�
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_int_enable (amhw_fsl_adc_t           *p_hw_adc,
                               amhw_fsl_adc_seq_index_t  index)
{
    p_hw_adc->sc1[index] |= AMHW_FSL_ADC_SC1_INT_EN_CFG;
}

/**
 * \brief ����ADCת������ж�
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_int_disable (amhw_fsl_adc_t           *p_hw_adc,
                                amhw_fsl_adc_seq_index_t  index)
{
    p_hw_adc->sc1[index] &= ~AMHW_FSL_ADC_SC1_INT_EN_CFG;
}
/**
 * \brief ʹ�ܲ������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_diff_enable (amhw_fsl_adc_t           *p_hw_adc,
                                amhw_fsl_adc_seq_index_t  index)
{
    p_hw_adc->sc1[index] |= AMHW_FSL_ADC_SC1_DIFF_EN_CFG;
}

/**
 * \brief ���ܲ�����룬ʹ�õ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_diff_disable (amhw_fsl_adc_t           *p_hw_adc,
                                 amhw_fsl_adc_seq_index_t  index)
{
    p_hw_adc->sc1[index] &= ~AMHW_FSL_ADC_SC1_DIFF_EN_CFG;
}

/**
 * \brief ����ͨ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \param[in] chan     : ADCͨ�� �� /ref grp_amhw_fsl_adc_chan
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_chan_set (amhw_fsl_adc_t          *p_hw_adc,
                             amhw_fsl_adc_seq_index_t index,
                             amhw_fsl_adc_chan_t      chan)
{
    p_hw_adc->sc1[index] &= ~AMHW_FSL_ADC_SC1_CHAN_MASK;
    p_hw_adc->sc1[index] |= chan;
}

/**
 * \brief ��ȡͨ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \return ADCͨ�� /ref grp_amhw_fsl_adc_chan
 */
am_static_inline
uint32_t amhw_fsl_adc_chan_get (amhw_fsl_adc_t          *p_hw_adc,
                                 amhw_fsl_adc_seq_index_t index)
{
    return p_hw_adc->sc1[index] & AMHW_FSL_ADC_SC1_CHAN_MASK;
}

/**
 * \brief ��ȡADCת����ɱ�־λ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 *
 * \retval AM_TRUE  : ת����ɱ�־λ��λ
 * \retval AM_FALSE : ת����ɱ�־λδ��λ
 *
 */
am_static_inline
uint32_t amhw_fsl_adc_complete_is (amhw_fsl_adc_t          *p_hw_adc,
                                    amhw_fsl_adc_seq_index_t index)
{
    return (p_hw_adc->sc1[index] & AMHW_FSL_ADC_SC1_COCO_MASK) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief ����״̬���ƼĴ���1
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \param[in] cfg      : ���ò��� �� /ref grp_amhw_fsl_adc_sc1
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_sc1_cfg (amhw_fsl_adc_t          *p_hw_adc,
                            amhw_fsl_adc_seq_index_t index,
                            uint32_t                  cfg)
{
    p_hw_adc->sc1[index] = cfg;
}

/**
 * \brief ��ȡ����״̬���ƼĴ���1
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \return  ����״̬���ƼĴ���1
 */
am_static_inline
uint32_t amhw_fsl_adc_sc1_get (amhw_fsl_adc_t          *p_hw_adc,
                                amhw_fsl_adc_seq_index_t index)
{
    return p_hw_adc->sc1[index] ;
}
/**
 * \brief ADC ʱ�ӷ�Ƶϵ��
 */
typedef enum amhw_fsl_adc_clk_div {
    AMHW_FSL_ADC_CLK_DIV_1 = 0,                      /**< \brief ��Ƶϵ��Ϊ1    */
    AMHW_FSL_ADC_CLK_DIV_2 = 1,                      /**< \brief ��Ƶϵ��Ϊ2    */
    AMHW_FSL_ADC_CLK_DIV_4 = 2,                      /**< \brief ��Ƶϵ��Ϊ4    */
    AMHW_FSL_ADC_CLK_DIV_8 = 3,                      /**< \brief ��Ƶϵ��Ϊ8    */
} amhw_fsl_adc_clk_div_t;

/**
 * \brief ADC ʱ��Դ
 */
typedef enum amhw_fsl_adc_clk_src {
    AMHW_FSL_ADC_CLK_SRC_BUS     = 0,            /**< \brief bus����ʱ��    */
    AMHW_FSL_ADC_CLK_SRC_ALTCLK2 = 1,            /**< \brief bus/2    */
    AMHW_FSL_ADC_CLK_SRC_ALTCLK  = 2,            /**< \brief ��ѡʱ��    */
    AMHW_FSL_ADC_CLK_SRC_ADACK   = 3,            /**< \brief �첽ʱ��    */
} amhw_fsl_adc_clk_src_t;

/**
 * \name ADC �ֱ��ʶ���
 * \anchor grp_amhw_fsl_adc_resolution
 * @{
 */
#define AMHW_FSL_ADC_BITS_8    0                      /**< \brief 8λ    */
#define AMHW_FSL_ADC_BITS_9    0                      /**< \brief 9λ    */
#define AMHW_FSL_ADC_BITS_10   2                      /**< \brief 10λ    */
#define AMHW_FSL_ADC_BITS_11   2                      /**< \brief 11λ    */
#define AMHW_FSL_ADC_BITS_12   1                      /**< \brief 12λ    */
#define AMHW_FSL_ADC_BITS_13   1                      /**< \brief 13λ    */
#define AMHW_FSL_ADC_BITS_16   3                      /**< \brief 16λ    */
/** @} */

/**
 * \name ADC ���üĴ���1λ����
 * \anchor grp_amhw_fsl_adc_cfg1
 * @{
 */
#define AMHW_FSL_ADC_CFG1_LPC_MASK   (1UL << 7)      /**< \brief �͹���ʹ������ */
#define AMHW_FSL_ADC_CFG1_DIV_MASK   (3UL << 5)      /**< \brief ʱ�ӷ�Ƶ���� */
#define AMHW_FSL_ADC_CFG1_LSMP_MASK  (1UL << 4)      /**< \brief ������ʱ������ */
#define AMHW_FSL_ADC_CFG1_MODE_MASK  (3UL << 2)      /**< \brief �ֱ������� */
#define AMHW_FSL_ADC_CFG1_ICLK_MASK  (3UL << 0)      /**< \brief ����ʱ������ */

#define AMHW_FSL_ADC_CFG1_LPC_EN_CFG  (1UL << 7)      /**< \brief �͹���ʹ������ */
/** \brief ��Ƶϵ������             */
#define AMHW_FSL_ADC_CFG1_DIV_CFG(x)  (((x) << 5) & AMHW_FSL_ADC_CFG1_DIV_MASK)
/** \brief ������ʱ��ʹ������ */
#define AMHW_FSL_ADC_CFG1_LSMP_EN_CFG (1UL << 4)
/** \brief �ֱ�������                 */
#define AMHW_FSL_ADC_CFG1_MODE_CFG(x) (((x) << 2) & AMHW_FSL_ADC_CFG1_MODE_MASK)
/** \brief ����ʱ������              */
#define AMHW_FSL_ADC_CFG1_ICLK_CFG(x) (((x) << 0) & AMHW_FSL_ADC_CFG1_ICLK_MASK)
/** @} */

/**
 * \brief ʹ�ܵ͹���ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_lowpower_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->cfg1 |= AMHW_FSL_ADC_CFG1_LPC_EN_CFG;
}

/**
 * \brief ���ܵ͹���ģʽ��������������ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_lowpower_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->cfg1 &= ~AMHW_FSL_ADC_CFG1_LPC_EN_CFG;
}

/**
 * \brief ����ʱ�ӷ�Ƶϵ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] div      : ʱ�ӷ�Ƶϵ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_clkdiv_set (amhw_fsl_adc_t          *p_hw_adc,
                               amhw_fsl_adc_clk_div_t   div)
{
    p_hw_adc->cfg1 &= ~AMHW_FSL_ADC_CFG1_DIV_MASK;
    p_hw_adc->cfg1 |= AMHW_FSL_ADC_CFG1_DIV_CFG(div);
}

/**
 * \brief ��ȡʱ�ӷ�Ƶϵ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ʱ�ӷ�Ƶϵ��
 */
am_static_inline
uint32_t amhw_fsl_adc_clkdiv_get (amhw_fsl_adc_t *p_hw_adc)
{
    return ((p_hw_adc->cfg1 & AMHW_FSL_ADC_CFG1_DIV_MASK) >> 5);
}

/**
 * \brief  ʹ�ܳ�����ʱ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_lsmp_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->cfg1 |= AMHW_FSL_ADC_CFG1_LSMP_MASK;
}

/**
 * \brief ���ܳ�����ʱ�䣬����̲���ʱ��ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_lsmp_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->cfg1 &= ~AMHW_FSL_ADC_CFG1_LSMP_MASK;
}

/**
 * \brief ���÷ֱ���ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] res      : �ֱ��ʣ�/ref grp_amhw_fsl_adc_resolution
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_mode_set (amhw_fsl_adc_t *p_hw_adc, uint32_t res)
{
    p_hw_adc->cfg1 &= ~AMHW_FSL_ADC_CFG1_MODE_MASK;
    p_hw_adc->cfg1 |= AMHW_FSL_ADC_CFG1_MODE_CFG(res);
}

/**
 * \brief ��ȡ�ֱ���ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return �ֱ��ʣ�/ref grp_amhw_fsl_adc_resolution
 */
am_static_inline
uint32_t amhw_fsl_adc_mode_get (amhw_fsl_adc_t *p_hw_adc)
{
    return ((p_hw_adc->cfg1 & AMHW_FSL_ADC_CFG1_MODE_MASK) >> 2);
}

/**
 * \brief ����ģ��ʱ��Դ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] src      : ʱ��Դ
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_clksrc_set (amhw_fsl_adc_t         *p_hw_adc,
                               amhw_fsl_adc_clk_src_t  src)
{
    p_hw_adc->cfg1 &= ~AMHW_FSL_ADC_CFG1_ICLK_MASK;
    p_hw_adc->cfg1 |= AMHW_FSL_ADC_CFG1_ICLK_CFG(src);
}

/**
 * \brief ��ȡģ��ʱ��Դ
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ʱ��Դ
 */
am_static_inline
uint32_t amhw_fsl_adc_clksrc_get (amhw_fsl_adc_t *p_hw_adc)
{
    return ((p_hw_adc->cfg1 & AMHW_FSL_ADC_CFG1_ICLK_MASK));
}

/**
 * \brief �������üĴ���1
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] cfg      : ���ò��� �� /ref grp_amhw_fsl_adc_cfg1
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cfg1_cfg (amhw_fsl_adc_t *p_hw_adc, uint32_t cfg)
{
    p_hw_adc->cfg1 = cfg;
}

/**
 * \brief ��ȡ���üĴ���1
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ���üĴ���1
 */
am_static_inline
uint32_t amhw_fsl_adc_cfg1_get (amhw_fsl_adc_t *p_hw_adc)
{
    return p_hw_adc->cfg1;
}

/**
 * \brief ADC ������ʱ��ѡ��
 */
typedef enum amhw_fsl_adc_lsts {
    AMHW_FSL_ADC_LSTS_20ADCK  = 0,            /**< \brief ����20��ADCKʱ��    */
    AMHW_FSL_ADC_LSTS_12ADCK  = 1,            /**< \brief ����12��ADCKʱ��    */
    AMHW_FSL_ADC_LSTS_6ADCK   = 2,            /**< \brief ����6��ADCKʱ��    */
    AMHW_FSL_ADC_LSTS_2ADCK   = 3,            /**< \brief ����2��ADCKʱ��    */
} amhw_fsl_adc_lsts_t;

/**
 * \brief ͨ��a/bѡ��
 */
typedef enum amhw_fsl_adc_muxsel {
    AMHW_FSL_ADC_MUXSEL_A = 0,               /**< \brief ѡ��ADxxaͨ�� */
    AMHW_FSL_ADC_MUXSEL_B = 1,               /**< \brief ѡ��ADxxbͨ�� */
} amhw_fsl_adc_muxsel_t;

/**
 * \name ADC ���üĴ���1λ����
 * \anchor grp_amhw_fsl_adc_cfg2
 * @{
 */
#define AMHW_FSL_ADC_CFG2_MUXSEL_MASK  (1UL << 4)  /**< \brief ����ʹ������ */
#define AMHW_FSL_ADC_CFG2_ACK_MASK     (1UL << 3)  /**< \brief �첽ʱ�����ʹ������ */
#define AMHW_FSL_ADC_CFG2_HSC_MASK     (1UL << 2)  /**< \brief ����ת���������� */
#define AMHW_FSL_ADC_CFG2_LSTS_MASK    (3UL << 0)  /**< \brief ������ʱ���������� */


#define AMHW_FSL_ADC_CFG2_MUXSEL_CFG(x)  ((x) << 4) /**< \brief ����Bʹ������ */
#define AMHW_FSL_ADC_CFG2_ACK_EN_CFG     (1UL << 3) /**< \brief �첽ʱ�����ʹ������ */
#define AMHW_FSL_ADC_CFG2_HSC_EN_CFG     (1UL << 2) /**< \brief ����ת��ʹ������ */
/** \brief ������ʱ��ѡ������ */
#define AMHW_FSL_ADC_CFG2_LSTS_CFG(x)    ((x) & AMHW_FSL_ADC_CFG2_LSTS_MASK)
/** @} */

/**
 * \brief ����ѡ��ͨ��a/b
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_seq_set (amhw_fsl_adc_t        *p_hw_adc,
                            amhw_fsl_adc_muxsel_t  index)
{
    p_hw_adc->cfg2 &= ~AMHW_FSL_ADC_CFG2_MUXSEL_MASK;
    p_hw_adc->cfg2 |= AMHW_FSL_ADC_CFG2_MUXSEL_CFG(index);
}

/**
 * \brief ��ȡ��Ч������ͨ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return  ʹ�õ�ͨ���ţ�a����b
 */
am_static_inline
uint32_t amhw_fsl_adc_seq_get (amhw_fsl_adc_t *p_hw_adc)
{
    return ((p_hw_adc->cfg2 & AMHW_FSL_ADC_CFG2_MUXSEL_MASK) >> 4) ;
}

/**
 * \brief  ʹ���첽ʱ�����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_ack_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->cfg2 |= AMHW_FSL_ADC_CFG2_ACK_MASK;
}

/**
 * \brief �����첽ʱ�����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_ack_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->cfg2 &= ~AMHW_FSL_ADC_CFG2_ACK_MASK;
}
/**
 * \brief  ʹ�ܸ���ת��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_hsc_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->cfg2 |= AMHW_FSL_ADC_CFG2_HSC_MASK;
}

/**
 * \brief ���ܸ���ת��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_hsc_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->cfg2 &= ~AMHW_FSL_ADC_CFG2_HSC_MASK;
}

/**
 * \brief ���ó�����ʱ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] time     : ��ʱ����
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_lsts_set (amhw_fsl_adc_t *p_hw_adc, amhw_fsl_adc_lsts_t time)
{
    p_hw_adc->cfg2 &= ~AMHW_FSL_ADC_CFG2_LSTS_MASK;
    p_hw_adc->cfg2 |= AMHW_FSL_ADC_CFG2_LSTS_CFG(time);
}

/**
 * \brief ��ȡ������ʱ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return  ��������
 */
am_static_inline
uint32_t amhw_fsl_adc_lsts_get (amhw_fsl_adc_t *p_hw_adc)
{
    return ((p_hw_adc->cfg2 & AMHW_FSL_ADC_CFG2_LSTS_MASK));
}

/**
 * \brief �������üĴ���2
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] cfg      : ���ò��� �� /ref grp_amhw_fsl_adc_cfg2
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cfg2_cfg (amhw_fsl_adc_t *p_hw_adc, uint32_t cfg)
{
    p_hw_adc->cfg2 = cfg;
}

/**
 * \brief ��ȡ���üĴ���2
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ���üĴ���2
 */
am_static_inline
uint32_t amhw_fsl_adc_cfg2_get (amhw_fsl_adc_t *p_hw_adc)
{
    return p_hw_adc->cfg2;
}

/**
 * \brief ��ȡ���ݼĴ�����ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ��������
 *
 * \return ADCת��������
 *
 * \note �ǲ��ģʽ������Ϊ�Ҷ���
 */
am_static_inline
uint16_t amhw_fsl_adc_dat_get (amhw_fsl_adc_t          *p_hw_adc,
                                amhw_fsl_adc_seq_index_t index)
{
    return (uint16_t)(p_hw_adc->dat[index] & 0xffff);
}

/**
 * \brief ������ֵ1�Ĵ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] dat      : ��������
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cv1_set (amhw_fsl_adc_t *p_hw_adc, uint16_t dat)
{
    p_hw_adc->cv_1 = dat;
}

/**
 * \brief ��ȡ��ֵ1�Ĵ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
uint16_t amhw_fsl_adc_cv1_get (amhw_fsl_adc_t *p_hw_adc)
{
    return (uint16_t)(p_hw_adc->cv_1 & 0xffff);
}

/**
 * \brief ������ֵ2�Ĵ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] dat      : ��������
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cv2_set (amhw_fsl_adc_t *p_hw_adc, uint16_t dat)
{
    p_hw_adc->cv_2 = dat;
}

/**
 * \brief ��ȡ��ֵ2�Ĵ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
uint16_t amhw_fsl_adc_cv2_get (amhw_fsl_adc_t *p_hw_adc)
{
    return (uint16_t)(p_hw_adc->cv_2 & 0xffff);
}


/**
 * \brief ADC ������ʱ��ѡ��
 */
typedef enum amhw_fsl_adc_ref {
    AMHW_FSL_ADC_REF_VREFHL = 0,     /**< \brief VREFH��VREFL���ο���ѹ */
    AMHW_FSL_ADC_REF_ALTHL  = 1,     /**< \brief VALTH��VALTL���ο���ѹ    */
} amhw_fsl_adc_ref_t;

/**
 * \name ADC ״̬���ƼĴ���2λ����
 * \anchor grp_amhw_fsl_adc_sc2
 * @{
 */
#define AMHW_FSL_ADC_SC2_ACT_MASK      (1UL << 7)   /**< \brief ����ת����־���� */
#define AMHW_FSL_ADC_SC2_HWTRG_MASK    (1UL << 6)   /**< \brief ������ʽ��־���� */
#define AMHW_FSL_ADC_SC2_CMP_MASK      (1UL << 5)   /**< \brief �ȽϹ��ܱ�־���� */
#define AMHW_FSL_ADC_SC2_CMPGT_MASK    (1UL << 4)   /**< \brief �ȽϹ��ܴ������� */
#define AMHW_FSL_ADC_SC2_CMPR_MASK     (1UL << 3)   /**< \brief �ȽϹ��ܷ�Χ���� */
#define AMHW_FSL_ADC_SC2_DMA_MASK      (1UL << 2)   /**< \brief DMA��������        */
#define AMHW_FSL_ADC_SC2_REF_MASK      (3UL << 0)   /**< \brief �ο���ѹѡ������ */

#define AMHW_FSL_ADC_SC2_HWTRG_EN_CFG  (1UL << 6)   /**< \brief Ӳ������ʹ������ */
#define AMHW_FSL_ADC_SC2_CMP_EN_CFG    (1UL << 5)   /**< \brief �ȽϹ���ʹ������ */
#define AMHW_FSL_ADC_SC2_CMPGT_EN_CFG  (1UL << 4)   /**< \brief �ȽϹ��ܴ������� */
#define AMHW_FSL_ADC_SC2_CMPR_EN_CFG   (1UL << 3)   /**< \brief �ȽϹ��ܷ�Χ���� */
#define AMHW_FSL_ADC_SC2_DMA_EN_CFG    (1UL << 2)   /**< \brief ʹ��DMA�������� */
#define AMHW_FSL_ADC_SC2_REF_CFG(x) ((x) & AMHW_FSL_ADC_SC2_REF_MASK) /**< \brief �ο���ѹѡ������ */
/** @} */

/**
 * \brief �Ƿ�����ת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 *
 * \retval AM_TRUE  : ����ת��
 * \retval AM_FALSE : ����
 *
 */
am_static_inline
uint32_t amhw_fsl_adc_busy_is (amhw_fsl_adc_t *p_hw_adc)
{
    return ((p_hw_adc->sc2 & AMHW_FSL_ADC_SC2_ACT_MASK) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief  ʹ��Ӳ������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_hwtrg_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 |= AMHW_FSL_ADC_SC2_HWTRG_MASK;
}

/**
 * \brief ����Ӳ��������ʹ���������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_hwtrg_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 &= ~AMHW_FSL_ADC_SC2_HWTRG_MASK;
}

/**
 * \brief  ʹ�ܱȽϹ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cmp_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 |= AMHW_FSL_ADC_SC2_CMP_MASK;
}

/**
 * \brief ���ܱȽϹ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cmp_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 &= ~AMHW_FSL_ADC_SC2_CMP_MASK;
}

/**
 * \brief ʹ�ܴ��ڱȽϹ���
 * \note ��CV1���ڻ���ڱȽϣ���CV2С�ڱȽϣ����������Χ�ȽϵĻ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cmpgt_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 |= AMHW_FSL_ADC_SC2_CMPGT_MASK;
}

/**
 * \brief ���ܴ��ڱȽϹ���
 * \note  ��CV1С�ڱȽϣ���CV2���ڻ���ڱȽϣ����������Χ�ȽϵĻ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cmpgt_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 &= ~AMHW_FSL_ADC_SC2_CMPGT_MASK;
}

/**
 * \brief  ʹ�ܷ�Χ�Ƚ�
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cmpr_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 |= AMHW_FSL_ADC_SC2_CMPR_MASK;
}

/**
 * \brief ���ܷ�Χ�Ƚ�
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cmpr_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 &= ~AMHW_FSL_ADC_SC2_CMPR_MASK;
}

/**
 * \brief  ʹ��DMA����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_dma_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 |= AMHW_FSL_ADC_SC2_DMA_MASK;
}

/**
 * \brief ����DMA����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_dma_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc2 &= ~AMHW_FSL_ADC_SC2_DMA_MASK;
}

/**
 * \brief ���òο���ѹ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] ref      : �ο���ѹѡ����
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_ref_set (amhw_fsl_adc_t *p_hw_adc, amhw_fsl_adc_ref_t ref)
{
    p_hw_adc->sc2 &= ~AMHW_FSL_ADC_SC2_REF_MASK;
    p_hw_adc->sc2 |= AMHW_FSL_ADC_SC2_REF_CFG(ref);
}

/**
 * \brief ��ȡ�ο���ѹ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return �ο���ѹѡ����
 */
am_static_inline
amhw_fsl_adc_ref_t amhw_fsl_adc_ref_get (amhw_fsl_adc_t *p_hw_adc)
{
    return (amhw_fsl_adc_ref_t)(p_hw_adc->sc2 & AMHW_FSL_ADC_SC2_REF_MASK);
}

/**
 * \brief ����״̬���ƼĴ���2
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] cfg      : ���ò��� �� /ref grp_amhw_fsl_adc_sc2
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_sc2_cfg (amhw_fsl_adc_t *p_hw_adc, uint32_t cfg)
{
    p_hw_adc->sc2 = cfg;
}

/**
 * \brief ADC Ӳ��ƽ������
 */
typedef enum amhw_fsl_adc_avgs {
    AMHW_FSL_ADC_AVGS_4  = 0,     /**< \brief 4������ֵ��ƽ�� */
    AMHW_FSL_ADC_AVGS_8  = 1,     /**< \brief 8������ֵ��ƽ��    */
    AMHW_FSL_ADC_AVGS_16 = 2,     /**< \brief 16������ֵ��ƽ��    */
    AMHW_FSL_ADC_AVGS_32 = 3,     /**< \brief 32������ֵ��ƽ��    */
} amhw_fsl_adc_avgs_t;

/**
 * \name ADC ״̬���ƼĴ���3λ����
 * \anchor grp_amhw_fsl_adc_sc3
 * @{
 */
#define AMHW_FSL_ADC_SC3_CAL_MASK      (1UL << 7)    /**< \brief ������־���� */
#define AMHW_FSL_ADC_SC3_CALF_MASK     (1UL << 6)    /**< \brief ����ʧ������ */
#define AMHW_FSL_ADC_SC3_CONT_MASK     (1UL << 3)    /**< \brief ����ת����־���� */
#define AMHW_FSL_ADC_SC3_AVG_MASK      (1UL << 2)    /**< \brief Ӳ��ƽ������ */
#define AMHW_FSL_ADC_SC3_AVGS_MASK     (3UL << 0)    /**< \brief Ӳ��ƽ���������� */

#define AMHW_FSL_ADC_SC3_CAL_EN_CFG    (1UL << 7)   /**< \brief ����ʹ������ */
#define AMHW_FSL_ADC_SC3_CONT_EN_CFG   (1UL << 3)   /**< \brief ����ת��ʹ������ */
#define AMHW_FSL_ADC_SC3_AVG_EN_CFG    (1UL << 2)   /**< \brief Ӳ��ƽ��ʹ������ */
#define AMHW_FSL_ADC_SC3_AVGS_CFG(x) ((x) & AMHW_FSL_ADC_SC3_AVGS_MASK) /**< \brief Ӳ��ƽ���������� */
/** @} */

/**
 * \brief  ʹ�ܽ���������������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cal_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc3 |= AMHW_FSL_ADC_SC3_CAL_MASK;
}

/**
 * \brief ���ܽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_cal_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc3 &= ~AMHW_FSL_ADC_SC3_CAL_MASK;
}

/**
 * \brief �Ƿ��ڽ�����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 *
 * \retval AM_TRUE  : ���ڽ���
 * \retval AM_FALSE : �������
 *
 */
am_static_inline
uint32_t amhw_fsl_adc_cal_get (amhw_fsl_adc_t *p_hw_adc)
{
    return ((p_hw_adc->sc3 & AMHW_FSL_ADC_SC3_CAL_MASK) ? AM_TRUE : AM_FALSE) ;
}

/**
 * \brief �����Ƿ�ʧ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 *
 * \retval AM_TRUE  : ����ʧ��
 * \retval AM_FALSE : �����������
 *
 */
am_static_inline
uint32_t amhw_fsl_adc_cal_fail_is (amhw_fsl_adc_t *p_hw_adc)
{
    return ((p_hw_adc->sc3 & AMHW_FSL_ADC_SC3_CALF_MASK) ? AM_TRUE : AM_FALSE) ;
}

/**
 * \brief  �������ʧ�ܱ�־λ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_calf_clr (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc3 |= AMHW_FSL_ADC_SC3_CALF_MASK;
}

/**
 * \brief  ʹ������ת��ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_continue_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc3 |= AMHW_FSL_ADC_SC3_CONT_MASK;
}

/**
 * \brief ��������ת��ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_continue_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc3 &= ~AMHW_FSL_ADC_SC3_CONT_MASK;
}

/**
 * \brief  ʹ��Ӳ��ƽ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_avg_enable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc3 |= AMHW_FSL_ADC_SC3_AVG_MASK;
}

/**
 * \brief ����Ӳ��ƽ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_avg_disable (amhw_fsl_adc_t *p_hw_adc)
{
    p_hw_adc->sc3 &= ~AMHW_FSL_ADC_SC3_AVG_MASK;
}

/**
 * \brief ����Ӳ��ƽ���Ĳ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] avgs     : ƽ���Ĳ�������
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_avgs_set (amhw_fsl_adc_t *p_hw_adc, amhw_fsl_adc_avgs_t avgs)
{
    p_hw_adc->sc3 &= ~AMHW_FSL_ADC_SC3_AVGS_MASK;
    p_hw_adc->sc3 |= AMHW_FSL_ADC_SC3_AVGS_CFG(avgs);
}

/**
 * \brief ��ȡӲ��ƽ���Ĳ�������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ƽ���Ĳ�������
 */
am_static_inline
amhw_fsl_adc_avgs_t amhw_fsl_adc_avgs_get (amhw_fsl_adc_t *p_hw_adc)
{
    return (amhw_fsl_adc_avgs_t)(p_hw_adc->sc3 & AMHW_FSL_ADC_SC3_AVGS_MASK);
}

/**
 * \brief ����״̬���ƼĴ���3
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] cfg      : ���ò��� �� /ref grp_amhw_fsl_adc_sc3
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_sc3_cfg (amhw_fsl_adc_t *p_hw_adc, uint32_t cfg)
{
    p_hw_adc->sc3 = cfg;
}


/**
 * \brief ����ƫ��������ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] val      : ƫ�����ֵ
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_ofs_set (amhw_fsl_adc_t *p_hw_adc, uint16_t val)
{
    p_hw_adc->ofs = val;
}

/**
 * \brief ��ȡƫ��������ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return  ƫ�����ֵ
 */
am_static_inline
uint16_t amhw_fsl_adc_ofs_get (amhw_fsl_adc_t *p_hw_adc)
{
    return (uint16_t)(p_hw_adc->ofs);
}

/**
 * \brief ����Plus-Side����Ĵ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] val      : ����ֵ
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_pg_set (amhw_fsl_adc_t *p_hw_adc, uint16_t val)
{
    p_hw_adc->pg = val;
}

/**
 * \brief ��ȡPlus-Side����Ĵ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return  ����ֵ
 */
am_static_inline
uint16_t amhw_fsl_adc_pg_get (amhw_fsl_adc_t *p_hw_adc)
{
    return (uint16_t)(p_hw_adc->pg);
}

/**
 * \brief ����Minus-Side����Ĵ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] val      : ����ֵ
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_mg_set (amhw_fsl_adc_t *p_hw_adc, uint16_t val)
{
    p_hw_adc->mg = val;
}

/**
 * \brief ��ȡMinus-Side����Ĵ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return  ����ֵ
 */
am_static_inline
uint16_t amhw_fsl_adc_mg_get (amhw_fsl_adc_t *p_hw_adc)
{
    return (uint16_t)(p_hw_adc->mg);
}

/**
 * \brief ����Plus-Side����Ĵ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : �����Ĵ�������ֵ
 * \param[in] val      : ����ֵ
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_clp_set (amhw_fsl_adc_t *p_hw_adc, uint8_t index, uint16_t val)
{
    if (index < 7) {
        p_hw_adc->clp[index] = val;
    }
}

/**
 * \brief ��ȡPlus-Side����Ĵ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : �����Ĵ�������ֵ��ֵ��ΧΪ[0,6]֮��
 *
 * \return  ����ֵ
 */
am_static_inline
uint16_t amhw_fsl_adc_clp_get (amhw_fsl_adc_t *p_hw_adc, uint8_t index)
{
    return (uint16_t)(p_hw_adc->clp[index]);
}

/**
 * \brief ����Minus-Side�Ĵ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : �����Ĵ�������ֵ��ֵ��ΧΪ[0,6]֮��
 * \param[in] val      : ����ֵ
 * \return ��
 */
am_static_inline
void amhw_fsl_adc_clm_set (amhw_fsl_adc_t *p_hw_adc, uint8_t index, uint16_t val)
{
    if (7 > index) {
        p_hw_adc->clm[index] = val;
    }
}

/**
 * \brief ��ȡMinus-Side�Ĵ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : �����Ĵ�������ֵ��ֵ��ΧΪ[0,6]֮��
 * \return  ����ֵ
 */
am_static_inline
uint16_t amhw_fsl_adc_clm_get (amhw_fsl_adc_t *p_hw_adc, uint8_t index)
{
    return (uint16_t)(p_hw_adc->clm[index]);
}


/**
 * \brief ADC У��, Ĭ�Ͻ���ʱ��Ƶ��Ϊ2M
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] clk_id   : ADC��ʹ�õ�ʱ��Դ
 * \retval AM_TRUE  : �����ɹ�
 * \retval AM_FALSE : ����ʧ��
 */
uint8_t amhw_fsl_adc_calibrate (amhw_fsl_adc_t *p_hw_adc, am_clk_id_t clk_id);

/**
 * \brief ʹ������������ν���
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

  /* ��������������ʹ�� */
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif
/** @} */


/**
 *@}
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMHW_FSL_ADC_H */

/* end of file */
