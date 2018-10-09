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
 * \brief LPC82X DMA ͨ�������ò������� 
 *
 * ���ļ�������DMAͨ����ź�DMAͨ�����ò�����
 * - ͨ�����: DMA_CHAN_* ָ��������DMAͨ����
 * - ͨ��������DAM_CHAN_OPT_*  �� #am_lpc82x_dma_controller_get() ����Ϊ�ڶ����������롣
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-30  mem, modified.
 * - 1.00 15-07-10  win, first implementation.
 * \endinternal
 */

#ifndef __LPC82X_DMA_CHAN_H
#define __LPC82X_DMA_CHAN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup lpc82x_if_dma_chan
 * \copydoc lpc82x_dma_chan.h
 * @{
 */

/**
 * \name DMA ͨ�����
 * \anchor grp_dma_chan
 * @{
 */

#define DMA_CHAN_0                    0           /**< \brief DMAͨ��0  */
#define DMA_CHAN_1                    1           /**< \brief DMAͨ��1  */
#define DMA_CHAN_2                    2           /**< \brief DMAͨ��2  */
#define DMA_CHAN_3                    3           /**< \brief DMAͨ��3  */
#define DMA_CHAN_4                    4           /**< \brief DMAͨ��4  */
#define DMA_CHAN_5                    5           /**< \brief DMAͨ��5  */
#define DMA_CHAN_6                    6           /**< \brief DMAͨ��6  */
#define DMA_CHAN_7                    7           /**< \brief DMAͨ��7  */
#define DMA_CHAN_8                    8           /**< \brief DMAͨ��8  */
#define DMA_CHAN_9                    9           /**< \brief DMAͨ��9  */
#define DMA_CHAN_10                   10          /**< \brief DMAͨ��10 */
#define DMA_CHAN_11                   11          /**< \brief DMAͨ��11 */
#define DMA_CHAN_12                   12          /**< \brief DMAͨ��12 */
#define DMA_CHAN_13                   13          /**< \brief DMAͨ��13 */
#define DMA_CHAN_14                   14          /**< \brief DMAͨ��14 */
#define DMA_CHAN_15                   15          /**< \brief DMAͨ��15 */
#define DMA_CHAN_16                   16          /**< \brief DMAͨ��16 */
#define DMA_CHAN_17                   17          /**< \brief DMAͨ��17 */
                                      
/** @} */

/**
 * \name �����DMA����ͨ��(��ͨ�������ͬ)
 * \anchor grp_dma_chan_peripheral
 *
 *  �ò�����ͨ�������ͬ��ÿ�����������Ӧһ��DMAͨ��
 *
 * \note ���DMA���ݴ����ٶ���Ҫ�Ͷ�Ӧ������ͬ����Ӧ��ʹ����������; \n
 *       û����������ĵ����ݴ������ʹ���κ�һ��ͨ����
 *
 * @{
 */

#define DMA_CHAN_USART0_RX_REQ    DMA_CHAN_0     /**< \brief UART0 RX ����   */
#define DMA_CHAN_USART0_TX_REQ    DMA_CHAN_1     /**< \brief UART0 TX ����   */
#define DMA_CHAN_USART1_RX_REQ    DMA_CHAN_2     /**< \brief UART1 RX ����   */
#define DMA_CHAN_USART1_TX_REQ    DMA_CHAN_3     /**< \brief UART1 TX ����   */
#define DMA_CHAN_USART2_RX_REQ    DMA_CHAN_4     /**< \brief UART2 RX ����   */
#define DMA_CHAN_USART2_TX_REQ    DMA_CHAN_5     /**< \brief UART2 TX ����   */
#define DMA_CHAN_SPI0_RX_REQ      DMA_CHAN_6     /**< \brief SPI0 RX ����    */
#define DMA_CHAN_SPI0_TX_REQ      DMA_CHAN_7     /**< \brief SPI0 TX ����    */
#define DMA_CHAN_SPI1_RX_REQ      DMA_CHAN_8     /**< \brief SPI1 RX ����    */
#define DMA_CHAN_SPI1_TX_REQ      DMA_CHAN_9     /**< \brief SPI1 TX ����    */
#define DMA_CHAN_I2C0_SLV_REQ     DMA_CHAN_10    /**< \brief I2C0 �ӻ�����   */
#define DMA_CHAN_I2C0_MST_REQ     DMA_CHAN_11    /**< \brief I2C0 ��������   */
#define DMA_CHAN_I2C1_SLV_REQ     DMA_CHAN_12    /**< \brief I2C1 �ӻ�����   */
#define DMA_CHAN_I2C1_MST_REQ     DMA_CHAN_13    /**< \brief I2C1 ��������   */
#define DMA_CHAN_I2C2_SLV_REQ     DMA_CHAN_14    /**< \brief I2C2 �ӻ�����   */
#define DMA_CHAN_I2C2_MST_REQ     DMA_CHAN_15    /**< \brief I2C2 ��������   */
#define DMA_CHAN_I2C3_SLV_REQ     DMA_CHAN_16    /**< \brief I2C3 �ӻ�����   */
#define DMA_CHAN_I2C3_MST_REQ     DMA_CHAN_17    /**< \brief I2C3 ��������   */

/** @} */

/******************************************************************************/

/**
 * \name DMA ͨ���������ȼ�(Ĭ��ֵ��DMA_CHAN_OPT_PRIO_0)
 * \anchor grp_dma_chan_opt_prio
 *
 * \note DMA_CHAN_OPT_PRIO_0Ϊ������ȼ�
 * @{
 */

#define DMA_CHAN_OPT_PRIO_0        AM_SBF(0, 16)    /**< \brief �������ȼ�0  */
#define DMA_CHAN_OPT_PRIO_1        AM_SBF(1, 16)    /**< \brief �������ȼ�1  */
#define DMA_CHAN_OPT_PRIO_2        AM_SBF(2, 16)    /**< \brief �������ȼ�2  */
#define DMA_CHAN_OPT_PRIO_3        AM_SBF(3, 16)    /**< \brief �������ȼ�3  */

/** @} */

/**
 * \name DMA��������ʹ��(Ĭ�ϲ�ʹ��)
 * \anchor grp_dma_chan_opt_periph_req_en
 * 
 * ÿ�����������Ӧһ��DMAͨ����ʹ��ͨ����������󣬴����ٶȺ��������󱣳�һ��
 *
 * - ���ڴ���ģʽΪ�ڴ浽����(����ͨ�����������)�������贫���ڴ棬
 *   Ӧ��ʹ�����������磺ʹ��ͨ��0����UART0_RX���ݵ��ڴ棬Ӧʹ����������
 *   
 * - ���ں���������û����ϵ�����ݴ��䣬Ӧ�ر���������(Ĭ��)��
 *   ʹ�������ٶȴ��䣬�磺�ڴ浽�ڴ����ݴ��䡣
 *   
 * \note ���ܲ������������ʹ��DMA��������ʱ��ҲӦ�ر�ͨ������������ \n
 *       ��: ADC�ɼ����ݵ��ڴ棬Ӧ�ر���������ʹ��ÿ�δ��䲻��ͨ���������
 *
 * @{
 */
 
/** \brief DMA��������ʹ�� */
#define DMA_CHAN_OPT_PERIPH_REQ_EN  AM_BIT(0)

/** @} */

/**
 * \name DMA Ӳ����������(Ĭ��: ����ҪӲ����������ʼ����)
 * \anchor grp_dma_chan_opt_hwtrig_mode
 * 
 *   ������Ӳ��������ֻ��Ӳ������Դ���㴥���������Żᴥ��DMA���䣬
 *   ͨ��Ӳ���������Կ���DMA�����������
 *
 * - ���ش�����DMA����Ĵ�С���Ƿ�ʹ��ͻ��ģʽ������ \n
 *   �����ʹ��ͻ��ģʽ(Ĭ��)��һ�δ������ȫ�����ݣ� \n
 *   ���ʹ��ͻ��ģʽ����ÿ��Ӳ��������������ݸ���ͻ����С���þ�����
 *
 * - ��ƽ������DMA����Ĵ�С���Ƿ�ʹ��ͻ��ģʽ������ \n
 *   �����ʹ��ͻ��ģʽ(Ĭ��)��һ�δ������ȫ�����ݣ� \n
 *   ���ʹ��ͻ��ģʽ�����ݴ��䱣�ֵ���ƽ��Ч����������ȫ��������ϡ�
 *
 * \note #am_lpc82x_dma_transfer() Ĭ�ϲ���ҪӲ���������Ϳ��Խ���DMA����
 *
 * @{
 */
 
/** \brief Ӳ���½��ش��� */
#define DMA_CHAN_OPT_HWTRIG_MODE_FALL    AM_BIT(1)

/** \brief Ӳ�������ش��� */
#define DMA_CHAN_OPT_HWTRIG_MODE_RISE    (AM_BIT(1) | AM_BIT(4))

/** \brief Ӳ���͵�ƽ���� */
#define DMA_CHAN_OPT_HWTRIG_MODE_LOW     (AM_BIT(1) | AM_BIT(5))

/** \brief Ӳ���ߵ�ƽ���� */
#define DMA_CHAN_OPT_HWTRIG_MODE_HIGH    (AM_BIT(1) | AM_BIT(4) | AM_BIT(5))

/** @} */

/**
 * \name DMA ͨ����Ӳ������Դ
 * \anchor grp_dma_chan_opt_hwtrig_src
 * 
 * \note ֻ��������Ӳ�������������ò�������Ч
 *
 * @{
 */
 
/** \brief ADC0 ����A�ж�     */
#define DMA_CHAN_OPT_HWTRIG_SRC_ADC0_SEQA_IRQ AM_SBF(0, 19)

/** \brief ADC0 ����B�ж�     */
#define DMA_CHAN_OPT_HWTRIG_SRC_ADC0_SEQB_IRQ AM_SBF(1, 19) 

/** \brief SCT0 DMA0 ����     */
#define DMA_CHAN_OPT_HWTRIG_SRC_SCT0_DMA0     AM_SBF(2, 19) 

/** \brief SCT1 DMA1 ����     */
#define DMA_CHAN_OPT_HWTRIG_SRC_SCT0_DMA1     AM_SBF(3, 19) 

/** \brief ACMP �Ƚ������    */
#define DMA_CHAN_OPT_HWTRIG_SRC_ACMP_O        AM_SBF(4, 19) 

/** \brief �����ж� 0         */
#define DMA_CHAN_OPT_HWTRIG_SRC_PININT0       AM_SBF(5, 19) 

/** \brief �����ж� 1         */
#define DMA_CHAN_OPT_HWTRIG_SRC_PININT1       AM_SBF(6, 19) 

/** \brief DMA ���ô��� 0     */
#define DMA_CHAN_OPT_HWTRIG_SRC_DMA_MUX0      AM_SBF(7, 19) 

/** \brief DMA ���ô��� 1     */
#define DMA_CHAN_OPT_HWTRIG_SRC_DMA_MUX1      AM_SBF(8, 19) 

/** @} */

/**
 * \name DMA ͻ��ģʽʹ��(Ĭ��: ��ʹ��ͻ��ģʽ)
 * \anchor grp_dma_chan_opt_hwtrig_burst_en
 *
 * \note ֻ��������Ӳ�������������ò�������Ч��
 *       ʹ��ͻ��ģʽ��Ӳ�����ش���������ÿ�δ������ݴ�С��
 *
 * @{
 */

/** \brief ͻ��ģʽʹ��   */ 
#define DMA_CHAN_OPT_HWTRIG_BURST_EN   AM_BIT(6)

/** @} */


/**
 * \name DMA ͻ��ģʽ��ַ����(Ĭ��: ��ʹ�õ�ַ����)
 * \anchor grp_dma_chan_opt_hwtrig_burst_wrap
 *
 * \note ֻ��ʹ����ͻ��ģʽ���ò�������Ч
 *
 * @{
 */

/** \brief ͻ������ʱ��Դ��ַ��ͻ����С��Χ�ڸı�   */ 
#define DMA_CHAN_OPT_HWTRIG_BURST_SRC_WRAP   AM_BIT(14)

/** \brief ͻ������ʱ��Ŀ�ĵ�ַ��ͻ����С��Χ�ڸı� */
#define DMA_CHAN_OPT_HWTRIG_BURST_DST_WRAP   AM_BIT(15)

/** @} */


/**
 * \name DMA ���ش�������ͻ�������С��Ĭ��ֵ��DMA_CHAN_OPT_HWTRIG_BURST_1��
 * \anchor grp_dma_chan_opt_hwtrig_burst_count
 *
 * \note ֻ��Ӳ�����ش��������£������ò���Ч
 *
 * @{
 */
 
 /** \brief ͻ�������СΪ   1    */
#define DMA_CHAN_OPT_HWTRIG_BURST_1    AM_SBF(0, 8)

/** \brief Ӳͻ�������СΪ 2    */
#define DMA_CHAN_OPT_HWTRIG_BURST_2    AM_SBF(1, 8)

/** \brief Ӳͻ�������СΪ 4    */
#define DMA_CHAN_OPT_HWTRIG_BURST_4    AM_SBF(2, 8)

/** \brief Ӳͻ�������СΪ 8    */
#define DMA_CHAN_OPT_HWTRIG_BURST_8    AM_SBF(3, 8)

/** \brief Ӳͻ�������СΪ 16   */
#define DMA_CHAN_OPT_HWTRIG_BURST_16   AM_SBF(4, 8)

/** \brief Ӳͻ�������СΪ 32   */
#define DMA_CHAN_OPT_HWTRIG_BURST_32   AM_SBF(5, 8)

/** \brief Ӳͻ�������СΪ 64   */
#define DMA_CHAN_OPT_HWTRIG_BURST_64   AM_SBF(6, 8)

/** \brief Ӳͻ�������СΪ 128  */
#define DMA_CHAN_OPT_HWTRIG_BURST_128  AM_SBF(7, 8)

/** \brief Ӳͻ�������СΪ 256  */
#define DMA_CHAN_OPT_HWTRIG_BURST_256  AM_SBF(8, 8)

/** \brief Ӳͻ�������СΪ 512  */
#define DMA_CHAN_OPT_HWTRIG_BURST_512  AM_SBF(9, 8)

/** \brief Ӳͻ�������СΪ 1024 */
#define DMA_CHAN_OPT_HWTRIG_BURST_1024 AM_SBF(10, 8)

/** @} */

/**
 * \name DMA ���ɴ���Դ
 * \anchor grp_dma_chan_opt_trig_out
 * 
 * \note ���ɵĴ���ͨ��DMA MUX ��Ϊ����ͨ���Ĵ������룬�������ͨ����ǰ�����ã�
 *       ���ᱻ����
 *
 * @{
 */
 
/** \brief DMA�����������0 */
#define DMA_CHAN_OPT_TRIG_OUT_MUX0 AM_SBF(1, 23)

/** \brief DMA�����������1 */
#define DMA_CHAN_OPT_TRIG_OUT_MUX1 AM_SBF(2, 23) 

/** @} */


/**
 * @} lpc82x_if_dma_chan
 */

#ifdef __cplusplus
}
#endif


#endif /* __LPC82X_DMA_CHAN_H */

/* end of file */
