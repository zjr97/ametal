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
 * \brief ADC Ӳ�������ӿ�����
 *
 * 1. 12λ��αƽ�����ģת������
 * 2. ģ���������Ŷ��12����
 * 3. 2������������ת�����У�
 * 4. ��ѡ���/����ֵ�ȽϺ͡���㴩Խ����⣻
 * 5. ֧�ֵ���ģʽ�͵͹���ģʽ��
 * 6. ��ѹ������Χ�� Vrefn �� Vrefp (����ֵΪ 3V; ���ɳ��� VDD �ĵ�ѹֵ)��
 * 7. 12λ��ת�����ʸߴ� 1.2 MHz�������ʣ�
 * 8. ͻ��ת��ģʽ֧�ֵ�ͨ�����ͨ�����룻
 * 9. ֧��DMAģʽ��
 * 10. Ӳ��У��ģʽ��
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-25  hgo, modify macro definition.
 * - 1.00 15-07-15  bob, first implementation.
 * \endinternal
 */
#ifndef  __AMHW_LPC82X_ADC_H
#define  __AMHW_LPC82X_ADC_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc82x_if_adc
 * \copydoc amhw_lpc82x_adc.h
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
typedef struct amhw_lpc82x_adc {
    __IO uint32_t ctrl;                 /**< \brief ADC ���ƼĴ���          */
    __IO uint32_t reserved1;            /**< \brief ����                    */
    union {
        __IO uint32_t seq_ctrl[2];      /**< \brief ADC ���п��ƼĴ���      */
        struct {
            __IO uint32_t seqa_ctrl;    /**< \brief ADC ����A���ƼĴ���     */
            __IO uint32_t seqb_ctrl;    /**< \brief ADC ����B���ƼĴ���     */
        };
    };
    union {
        __IO uint32_t seq_gdat[2];      /**< \brief ADC ����ȫ�����ݼĴ���  */
        struct {
            __IO uint32_t seqa_gdat;    /**< \brief ADC ����Aȫ�����ݼĴ��� */
            __IO uint32_t seqb_gdat;    /**< \brief ADC ����Bȫ�����ݼĴ��� */
        };
    };
    __IO uint32_t reserved2[2];         /**< \brief ����                    */
    union {
        __I uint32_t dat[12];           /**< \brief ADC ͨ�����ݼĴ���      */
        struct {
            __I uint32_t dat0;          /**< \brief ADC ͨ��0���ݼĴ���     */
            __I uint32_t dat1;          /**< \brief ADC ͨ��1���ݼĴ���     */
            __I uint32_t dat2;          /**< \brief ADC ͨ��2���ݼĴ���     */
            __I uint32_t dat3;          /**< \brief ADC ͨ��3���ݼĴ���     */
            __I uint32_t dat4;          /**< \brief ADC ͨ��4���ݼĴ���     */
            __I uint32_t dat5;          /**< \brief ADC ͨ��5���ݼĴ���     */
            __I uint32_t dat6;          /**< \brief ADC ͨ��6���ݼĴ���     */
            __I uint32_t dat7;          /**< \brief ADC ͨ��7���ݼĴ���     */
            __I uint32_t dat8;          /**< \brief ADC ͨ��8���ݼĴ���     */
            __I uint32_t dat9;          /**< \brief ADC ͨ��9����a�Ĵ���    */
            __I uint32_t dat10;         /**< \brief ADC ͨ��10���ݼĴ���    */
            __I uint32_t dat11;         /**< \brief ADC ͨ��11���ݼĴ���    */
        };
    };
    union {
        __IO uint32_t thr_low[2];       /**< \brief ADC ����ֵ�Ĵ���        */
        struct {
            __IO uint32_t thr0_low;     /**< \brief ADC ����ֵ�Ĵ��� 0      */
            __IO uint32_t thr1_low;     /**< \brief ADC ����ֵ�Ĵ��� 1      */
        };
    };
    union {
        __IO uint32_t thr_high[2];      /**< \brief ADC ����ֵ�Ĵ���        */
        struct {
            __IO uint32_t thr0_high;    /**< \brief ADC ����ֵ�Ĵ��� 0      */
            __IO uint32_t thr1_high;    /**< \brief ADC ����ֵ�Ĵ��� 1      */
        };
    };
    __IO uint32_t chan_thrsel;          /**< \brief ADC ͨ����ֵѡ��Ĵ���  */
    __IO uint32_t inten;                /**< \brief ADC �ж�ʹ�ܼĴ���      */
    __IO uint32_t flags;                /**< \brief ADC �ж������־�Ĵ���  */
    __IO uint32_t trim;                 /**< \brief ADC �����Ĵ���          */
} amhw_lpc82x_adc_t;


/**
 * \name ADC ͨ�����
 * \anchor grp_amhw_lpc82x_adc_chan
 * @{
 */

#define AMHW_LPC82X_ADC_CHAN_0          0          /**< \brief ADC ͨ�� 0   */
#define AMHW_LPC82X_ADC_CHAN_1          1          /**< \brief ADC ͨ�� 1   */
#define AMHW_LPC82X_ADC_CHAN_2          2          /**< \brief ADC ͨ�� 2   */
#define AMHW_LPC82X_ADC_CHAN_3          3          /**< \brief ADC ͨ�� 3   */
#define AMHW_LPC82X_ADC_CHAN_4          4          /**< \brief ADC ͨ�� 4   */
#define AMHW_LPC82X_ADC_CHAN_5          5          /**< \brief ADC ͨ�� 5   */
#define AMHW_LPC82X_ADC_CHAN_6          6          /**< \brief ADC ͨ�� 6   */
#define AMHW_LPC82X_ADC_CHAN_7          7          /**< \brief ADC ͨ�� 7   */
#define AMHW_LPC82X_ADC_CHAN_8          8          /**< \brief ADC ͨ�� 8   */
#define AMHW_LPC82X_ADC_CHAN_9          9          /**< \brief ADC ͨ�� 9   */
#define AMHW_LPC82X_ADC_CHAN_10         10         /**< \brief ADC ͨ�� 10  */
#define AMHW_LPC82X_ADC_CHAN_11         11         /**< \brief ADC ͨ�� 11  */

/** @} */

#define AMHW_LPC82X_ADC_CHAN_CNT        12         /**< \brief ADC ͨ������ */

/**
 * \brief ADC ���мĴ�������
 */
typedef enum amhw_lpc82x_adc_seq_index {
    AMHW_LPC82X_ADC_SEQ_A = 0,                     /**< \brief ����A����    */
    AMHW_LPC82X_ADC_SEQ_B = 1,                     /**< \brief ����B����    */
} amhw_lpc82x_adc_seq_index_t;


/**
 * \brief ADC ��ֵ�Ƚ�����
 */
typedef enum amhw_lpc82x_adc_comp_thre_index {
    AMHW_LPC82X_ADC_COMP_THRE_0 = 0,               /**< \brief ��ֵ�Ƚ�0���� */
    AMHW_LPC82X_ADC_COMP_THRE_1 = 1,               /**< \brief ��ֵ�Ƚ�1���� */
} amhw_lpc82x_adc_comp_thre_index_t;


/**
 * \name ADC ���ƼĴ���λ����
 * \anchor grp_amhw_lpc82x_adc_ctrl
 * @{
 */
 
/** \brief ����ʱ�ӷ�Ƶֵ           */
#define AMHW_LPC82X_ADC_CTRL_CLK_DIV(x)  AM_SBF((x) & 0xFF, 0)

/** \brief �͹���ģʽʹ��           */
#define AMHW_LPC82X_ADC_CTRL_LPWRMODE    AM_SBF(1UL, 10)

/** \brief У��ʹ��                 */
#define AMHW_LPC82X_ADC_CTRL_CALMODE     AM_SBF(1UL, 30)

/** @} */

/**
 * \name ADC ���п��ƼĴ���λ����
 * \anchor grp_amhw_lpc82x_adc_seq_ctrl
 * @{
 */
 
/** \brief ����ѡ��Ϊ�������       */
#define AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_SW        AM_SBF(0UL, 12)

/** \brief ����ѡ��ΪADC_PINTRG0    */
#define AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_PIN0      AM_SBF(1UL, 12)

/** \brief ����ѡ��ΪADC_PINTRG1    */
#define AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_PIN1      AM_SBF(2UL, 12)

/** \brief ����ѡ��ΪSCT_OUT3       */
#define AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_SCT       AM_SBF(3UL, 12)

/** \brief ����ѡ��Ϊģ��Ƚ������ */
#define AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_ACMP      AM_SBF(4UL, 12)

/** \brief ����ѡ��ΪARM_TXEV       */
#define AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_ARM_TXEV  AM_SBF(5UL, 12)

/** \brief ��������                 */
#define AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_POL_NEG   AM_SBF(0UL, 18)

/** \brief ��������                 */
#define AMHW_LPC82X_ADC_SEQ_CTRL_TRIG_POL_POS   AM_SBF(1UL, 18)

/** \brief ����ͬ������             */
#define AMHW_LPC82X_ADC_SEQ_CTRL_BYPASS_SYNC    AM_SBF(1UL, 19)

/** \brief ʹ��ͻ��ת��ģʽ         */
#define AMHW_LPC82X_ADC_SEQ_CTRL_MODE_BURST    (AM_SBF(1UL, 27) |\
                                                AM_SBF(0UL, 26))

/** \brief ʹ�ܵ���ת��ģʽ         */
#define AMHW_LPC82X_ADC_SEQ_CTRL_MODE_SINGLE    AM_SBF(1UL, 28)

/** \brief ����A�����ȼ�            */
#define AMHW_LPC82X_ADC_SEQ_CTRL_SEQA_PIRO_HIGH AM_SBF(1UL, 29)

/** \brief ת����ɲ����¼�         */
#define AMHW_LPC82X_ADC_SEQ_CTRL_MODE_EOC       AM_SBF(0UL, 30)

/** \brief ����ת����ɲ����¼�     */
#define AMHW_LPC82X_ADC_SEQ_CTRL_MODE_EOS       AM_SBF(1UL, 30)

/** \brief ���п��ƼĴ���ʹ��       */
#define AMHW_LPC82X_ADC_SEQ_CTRL_ENA            AM_SBF(1UL, 31)

/** \brief ʹ��ADCͨ��              */
#define AMHW_LPC82X_ADC_SEQ_CTRL_ENABLE_CH(ch)  AM_SBF(1UL, (ch) & 0xFF)

/** @} */


/**
 * \name ���ݼĴ���λ����
 * \anchor grp_amhw_lpc82x_adc_data_reg
 * @{
 */

/** \brief ��ȡADCת��ֵ            */
#define AMHW_LPC82X_ADC_DR_RESULT(n)        AM_BITS_GET(n, 4, 12)

/** \brief ��ֵ��Խ�ȽϽ��         */
#define AMHW_LPC82X_ADC_DR_THCMPRANGE(n)    AM_BITS_GET(n, 16, 2)

/** \brief ��ֵ��Χ�ȽϽ��         */
#define AMHW_LPC82X_ADC_DR_THCMPCROSS(n)    AM_BITS_GET(n, 18, 2)

/** \brief ��ǰת����ͨ����         */
#define AMHW_LPC82X_ADC_DR_CHANNEL(n)       AM_BITS_GET(n, 26, 4)

/** \brief �����־λ               */
#define AMHW_LPC82X_ADC_DR_OVERRUN          AM_SBF(1UL, 30)

/** \brief ������Чλ               */
#define AMHW_LPC82X_ADC_DR_DATAVALID        AM_SBF(1UL, 31)

/** @} */


/**
 * \name ADC�ж�ʹ�ܼĴ���λ����
 * \anchor grp_amhw_lpc82x_adc_inten
 * @{
 */

/** \brief ����A�ж�ʹ��λ          */
#define AMHW_LPC82X_ADC_INTEN_SEQA_ENABLE       AM_SBF(1UL, 0)

/** \brief ����B�ж�ʹ��λ          */
#define AMHW_LPC82X_ADC_INTEN_SEQB_ENABLE       AM_SBF(1UL, 1)

/** \brief ����ж�ʹ��λ           */
#define AMHW_LPC82X_ADC_INTEN_OVRRUN_ENABLE     AM_SBF(1UL, 2)

/** \brief ������ֵ�Ƚ��ж�         */
#define AMHW_LPC82X_ADC_INTEN_CMP_DISABLE(ch)   AM_SBF(0UL, AM_SBF(ch, 1) + 3)

/** \brief ʹ���ⲿ��ֵ�Ƚ��ж�     */
#define AMHW_LPC82X_ADC_INTEN_CMP_OUTSIDETH(ch) AM_SBF(1UL, AM_SBF(ch, 1) + 3)

/** \brief ʹ�ܴ�Խ��ֵ�Ƚ��ж�     */
#define AMHW_LPC82X_ADC_INTEN_CMP_CROSSTH(ch)   AM_SBF(2UL, AM_SBF(ch, 1) + 3)

/** \brief ���������ж�     */
#define AMHW_LPC82X_ADC_INTEN_ALL_DISABLE       (0)
/** @} */


/**
 * \name ADC ��־�Ĵ���λ����
 * \anchor grp_amhw_lpc82x_adc_flags
 * @{
 */

/** \brief ͨ����ֵ�Ƚϱ�־         */
#define AMHW_LPC82X_ADC_FLAGS_THCMP_MASK(ch)    AM_SBF(1UL, ch)

/** \brief ͨ�������־             */
#define AMHW_LPC82X_ADC_FLAGS_OVRRUN_MASK(ch)   AM_SBF(1UL, 12 + (ch))

/** \brief ����A�����־            */
#define AMHW_LPC82X_ADC_FLAGS_SEQA_OVRRUN_MASK  AM_SBF(1UL, 24)

/** \brief ����B�����־            */
#define AMHW_LPC82X_ADC_FLAGS_SEQB_OVRRUN_MASK  AM_SBF(1UL, 25)

/** \brief ����A�жϱ�־            */
#define AMHW_LPC82X_ADC_FLAGS_SEQA_INT_MASK     AM_SBF(1UL, 28)

/** \brief ����B�жϱ�־            */
#define AMHW_LPC82X_ADC_FLAGS_SEQB_INT_MASK     AM_SBF(1UL, 29)

/** \brief ��ֵ�Ƚ��жϱ�־         */
#define AMHW_LPC82X_ADC_FLAGS_THCMP_INT_MASK    AM_SBF(1UL, 30)

/** \brief ����жϱ�־             */
#define AMHW_LPC82X_ADC_FLAGS_OVRRUN_INT_MASK   AM_SBF(1UL, 31)

/** @} */

/**
 * \name ADC �����Ĵ���λ����
 * \anchor grp_amhw_lpc82x_adc_trim
 * @{
 */

/** \brief �ߵ�ѹ������2.7~3.6V��   */
#define AMHW_LPC82X_ADC_TRIM_VRANGE_HIGHT   AM_SBF(0UL, 5)

/** \brief �͵�ѹ������2.4~2.7V��   */
#define AMHW_LPC82X_ADC_TRIM_VRANGE_LOW     AM_SBF(1UL, 5)

/** @} */


/**
 * \brief ADC ʱ�ӷ�Ƶ����
 *
 * \param[in] p_hw_adc       : ָ��ADC�Ĵ������ָ��
 * \param[in] clkdiv         : ��Ƶϵ��(0~255)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_adc_clkdiv_set (amhw_lpc82x_adc_t *p_hw_adc, uint8_t clkdiv)
{
    AM_BITS_SET(p_hw_adc->ctrl, 0, 8, clkdiv);
}

/**
 * \brief ADC ʱ�ӷ�Ƶ��ȡ
 *
 * \param[in] p_hw_adc       : ָ��ADC�Ĵ������ָ��
 *
 * \return ADCʱ�ӷ�Ƶϵ��
 */
am_static_inline
uint8_t amhw_lpc82x_adc_clkdiv_get (amhw_lpc82x_adc_t *p_hw_adc)
{
    return (p_hw_adc->ctrl & 0xFF);
}

/**
 * \brief ADC У��
 *
 * \param[in] p_hw_adc       : ָ��ADC�Ĵ������ָ��
 * \param[in] sysclk_freq    : ϵͳʱ��
 *
 * \return ��
 */
void amhw_lpc82x_adc_calibrate (amhw_lpc82x_adc_t *p_hw_adc,
                                uint32_t           sysclk_freq);

/**
 * \brief ADC ��������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] flags    : �������ò������μ�
 *                       \ref grp_amhw_lpc82x_adc_ctrl
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_adc_config (amhw_lpc82x_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->ctrl = flags;
}

/**
 * \brief ��ȡ ADC ���ƼĴ���״̬ 
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 *
 * \return ���ƼĴ���״̬ 
 */
am_static_inline
uint32_t amhw_lpc82x_adc_ctrl_get (amhw_lpc82x_adc_t *p_hw_adc)
{
    return p_hw_adc->ctrl;
}

/**
 * \brief ADC ת����������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 * \param[in] flags    : �������ò������μ�
 *                       \ref grp_amhw_lpc82x_adc_seq_ctrl
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_adc_seq_config (amhw_lpc82x_adc_t           *p_hw_adc,
                                 amhw_lpc82x_adc_seq_index_t  index,
                                 uint32_t                     flags)
{
    p_hw_adc->seq_ctrl[index] = flags;
}

/**
 * \brief ��ȡ ADC ����ת������״̬
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 *
 * \return ADC ����ת������״̬
 */
am_static_inline
uint32_t amhw_lpc82x_adc_seq_ctrl_get (amhw_lpc82x_adc_t           *p_hw_adc,
                                       amhw_lpc82x_adc_seq_index_t  index)
{
    return p_hw_adc->seq_ctrl[index];
}

/**
 * \brief ����ADC����ת��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_adc_seq_start (amhw_lpc82x_adc_t           *p_hw_adc,
                                amhw_lpc82x_adc_seq_index_t  index)
{
    AM_BIT_SET(p_hw_adc->seq_ctrl[index], 26);
}

/**
 * \brief ֹͣADC����ת��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_adc_seq_stop (amhw_lpc82x_adc_t           *p_hw_adc,
                               amhw_lpc82x_adc_seq_index_t  index)
{
    AM_BIT_CLR(p_hw_adc->seq_ctrl[index], 26);
}

/**
 * \brief ʹ��ADCת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_adc_seq_enable (amhw_lpc82x_adc_t           *p_hw_adc,
                                 amhw_lpc82x_adc_seq_index_t  index)
{
    AM_BIT_SET(p_hw_adc->seq_ctrl[index], 31);
}

/**
 * \brief ����ADCת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_adc_seq_disable (amhw_lpc82x_adc_t           *p_hw_adc,
                                  amhw_lpc82x_adc_seq_index_t  index)
{
    AM_BIT_CLR(p_hw_adc->seq_ctrl[index], 31);
}

/**
 * \brief ADCת������ʹ�ܺ�����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 *
 * \return ��
 */
am_static_inline  
void amhw_lpc82x_adc_seq_start_and_enable (amhw_lpc82x_adc_t           *p_hw_adc,
                                           amhw_lpc82x_adc_seq_index_t  index)
{
    AM_BIT_SET_MASK(p_hw_adc->seq_ctrl[index] , AM_BIT(31) | AM_BIT(26));
}

/**
 * \brief ʹ��ADCת�����е�ͨ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 * \param[in] chan     : ADC ͨ��, �μ�
 *                       \ref grp_amhw_lpc82x_adc_chan
 * \return ��
 */
am_static_inline  
void amhw_lpc82x_adc_seq_chan_set (amhw_lpc82x_adc_t           *p_hw_adc,
                                   amhw_lpc82x_adc_seq_index_t  index,
                                   int                          chan)
{
    AM_BIT_CLR     (p_hw_adc->seq_ctrl[index], 31);
    AM_BIT_SET_MASK(p_hw_adc->seq_ctrl[index], AM_BIT(31) | AM_BIT(chan));
}

/**
 * \brief ��ͨ�����ݼĴ�����ȡADCת��ֵ
 *
 * ����ֵ�� \ref grp_amhw_lpc82x_adc_data_reg �е� 'n'
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] chan     : ADC ͨ��, �μ�
 *                       \ref grp_amhw_lpc82x_adc_chan
 *
 * \return ADCת��ֵ
 */
am_static_inline
uint32_t amhw_lpc82x_adc_chan_data_get (amhw_lpc82x_adc_t *p_hw_adc, int chan)
{
    return p_hw_adc->dat[chan];
}

/**
 * \brief ��ȫ�����ݼĴ�����ȡADCת��ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_LPC82X_ADC_SEQ_A) �� (#AMHW_LPC82X_ADC_SEQ_B)
 *
 * \return ADCת��ֵ
 */
am_static_inline
uint32_t amhw_lpc82x_adc_glo_data_get (amhw_lpc82x_adc_t           *p_hw_adc,
                                       amhw_lpc82x_adc_seq_index_t  index)
{
    return p_hw_adc->seq_gdat[index];
}

/**
 * \brief ����ADC�ͱȽ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADC��ֵ�Ƚϣ�
 *                       (#AMHW_LPC82X_ADC_COMP_THRE_0) ��
 *                       (#AMHW_LPC82X_ADC_COMP_THRE_1)
 * \param[in] value    : ���õĵ���ֵ
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_adc_thr_low_set (amhw_lpc82x_adc_t                 *p_hw_adc,
                                  amhw_lpc82x_adc_comp_thre_index_t  index,
                                  uint32_t                           value)
{
    p_hw_adc->thr_low[index] = AM_SBF(value & 0xFFF, 4); 
}

/**
 * \brief ����ADC�߱Ƚ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADC��ֵ�Ƚϣ�
 *                       (#AMHW_LPC82X_ADC_COMP_THRE_0) ��
 *                       (#AMHW_LPC82X_ADC_COMP_THRE_1)
 * \param[in] value    : ���õĸ���ֵ
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_adc_thr_high_set (amhw_lpc82x_adc_t                 *p_hw_adc,
                                   amhw_lpc82x_adc_comp_thre_index_t  index,
                                   uint32_t                           value)
{
    p_hw_adc->thr_high[index] = AM_SBF(value & 0xFFF, 4);
}

/**
 * \brief ��ֵ�Ƚ�0ѡ��ͨ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] chan     : ADC ͨ��, �μ�
 *                       \ref grp_amhw_lpc82x_adc_chan
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_adc_thr0_sel (amhw_lpc82x_adc_t *p_hw_adc, int chan)
{ 
    AM_BIT_CLR(p_hw_adc->chan_thrsel, chan);
}

/**
 * \brief ��ֵ�Ƚ�1ѡ��ͨ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] chan     : ADC ͨ��, �μ�
 *                       \ref grp_amhw_lpc82x_adc_chan
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_adc_thr1_sel (amhw_lpc82x_adc_t *p_hw_adc, int chan)
{
    AM_BIT_SET(p_hw_adc->chan_thrsel, chan);
}

/**
 * \brief ADC �ж�ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] flags    : �ж����ò������μ�
 *                       \ref grp_amhw_lpc82x_adc_inten
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_adc_int_enable (amhw_lpc82x_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->inten = flags;
}

/**
 * \brief ADC �жϽ���
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] flags    : �ж����ò������μ�
 *                       \ref grp_amhw_lpc82x_adc_inten
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_adc_int_disable (amhw_lpc82x_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->inten &= ~flags;
}

/**
 * \brief ��ȡ�жϱ�־
 * 
 * �� \ref grp_amhw_lpc82x_adc_flags �Ĳ��������������ȡ����״̬
 *
 * \par ʾ��
 * \code 
 * if (amhw_lpc82x_adc_flags_get(p_hw_adc)&AMHW_LPC82X_ADC_FLAGS_SEQA_INT_MASK){
 * // do something.
 * }
 * \endcode
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 *
 * \return �жϱ�־.
 */
am_static_inline 
uint32_t amhw_lpc82x_adc_flags_get (amhw_lpc82x_adc_t *p_hw_adc)
{
    return p_hw_adc->flags;
}

/**
 * \brief ����жϱ�־
 * 
 * �� \ref grp_amhw_lpc82x_adc_flags �Ĳ��������������ȡ����״̬
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] flags    : �жϱ�־����, �μ� \ref grp_amhw_lpc82x_adc_flags
 * 
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_adc_flags_clr (amhw_lpc82x_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->flags = flags;
}

/**
 * \brief ADC ������ѹѡ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] flag     : ������ѹ����
 *                       \ref grp_amhw_lpc82x_adc_inten
 *
 * \return ��
 */
am_static_inline 
void amhw_lpc82x_adc_trim_voltage_set (amhw_lpc82x_adc_t *p_hw_adc,
                                       uint32_t           flag)
{
    p_hw_adc->trim = flag;
}


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

#endif /*__AMHW_LPC82X_ADC_H */

/* end of file */
