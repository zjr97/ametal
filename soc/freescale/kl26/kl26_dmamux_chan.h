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
 * \brief Kl26 DMA ͨ����Ŷ���
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-16  mkr, first implementation.
 * \endinternal
 */

#ifndef __KL26_DMAMUX_CHAN_H
#define __KL26_DMAMUX_CHAN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup kl26_if_dma_chan
 * \copydoc kl26_dmamux_chan.h
 * @{
 */


/**
 * \name KL26 DMA ͨ�����
 * @{
 */
#define DMA_CHAN_0                0               /**< \brief DMAͨ��0  */
#define DMA_CHAN_1                1               /**< \brief DMAͨ��1  */
#define DMA_CHAN_2                2               /**< \brief DMAͨ��2  */
#define DMA_CHAN_3                3               /**< \brief DMAͨ��3  */

/** @} */


/**
 * \name �����DMA����Դ���
 * @{
 */

#define DMA_REQUEST_MUX0_DISABLE        0      /**< \brief ������ ����Դ        */

#define DMA_REQUEST_MUX0_UART0RX        2      /**< \brief UART0 RX ����     */
#define DMA_REQUEST_MUX0_UART0TX        3      /**< \brief UART0 TX ����     */
#define DMA_REQUEST_MUX0_UART1RX        4      /**< \brief UART1 RX ����     */
#define DMA_REQUEST_MUX0_UART1TX        5      /**< \brief UART1 TX ����     */
#define DMA_REQUEST_MUX0_UART2RX        6      /**< \brief UART2 RX ����     */
#define DMA_REQUEST_MUX0_UART2TX        7      /**< \brief UART2 TX ����     */

#define DMA_REQUEST_MUX0_I2S0RX         14     /**< \brief I2S0 RX ����       */
#define DMA_REQUEST_MUX0_I2S0TX         15     /**< \brief I2S0 TX ����       */

#define DMA_REQUEST_MUX0_SPI0RX         16     /**< \brief SPI0 RX ����       */
#define DMA_REQUEST_MUX0_SPI0TX         17     /**< \brief SPI0 TX ����       */
#define DMA_REQUEST_MUX0_SPI1RX         18     /**< \brief SPI1 RX ����       */
#define DMA_REQUEST_MUX0_SPI1TX         19     /**< \brief SPI1 TX ����       */

#define DMA_REQUEST_MUX0_I2C0           22     /**< \brief I2C0    ����       */
#define DMA_REQUEST_MUX0_I2C1           23     /**< \brief I2C1    ����       */

#define DMA_REQUEST_MUX0_TPM0_CHANNEL0  24     /**< \brief TPM0ͨ��0 ����   */
#define DMA_REQUEST_MUX0_TPM0_CHANNEL1  25     /**< \brief TPM0ͨ��1 ����   */
#define DMA_REQUEST_MUX0_TPM0_CHANNEL2  26     /**< \brief TPM0ͨ��2 ����   */
#define DMA_REQUEST_MUX0_TPM0_CHANNEL3  27     /**< \brief TPM0ͨ��3 ����   */
#define DMA_REQUEST_MUX0_TPM0_CHANNEL4  28     /**< \brief TPM0ͨ��4 ����   */
#define DMA_REQUEST_MUX0_TPM0_CHANNEL5  29     /**< \brief TPM0ͨ��5 ����   */
#define DMA_REQUEST_MUX0_TPM1_CHANNEL0  32     /**< \brief TPM1ͨ��0 ����   */
#define DMA_REQUEST_MUX0_TPM1_CHANNEL1  33     /**< \brief TPM1ͨ��1 ����   */
#define DMA_REQUEST_MUX0_TPM2_CHANNEL0  34     /**< \brief TPM2ͨ��0 ����   */
#define DMA_REQUEST_MUX0_TPM2_CHANNEL1  35     /**< \brief TPM2ͨ��1 ����   */

#define DMA_REQUEST_MUX0_ADC0           40     /**< \brief ADC0 ����                */

#define DMA_REQUEST_MUX0_CMP0           42     /**< \brief CMP0 ����                */

#define DMA_REQUEST_MUX0_DAC0           45     /**< \brief DAC0 ����                */

#define DMA_REQUEST_MUX0_PORTA          49     /**< \brief PORTA ����              */
#define DMA_REQUEST_MUX0_PORTC          51     /**< \brief PORTC ����              */
#define DMA_REQUEST_MUX0_PORTD          52     /**< \brief PORTD ����              */

#define DMA_REQUEST_MUX0_TPM0_OVERFLOW  54     /**< \brief TPM0���  ����        */
#define DMA_REQUEST_MUX0_TPM1_OVERFLOW  55     /**< \brief TPM0���  ����        */
#define DMA_REQUEST_MUX0_TPM2_OVERFLOW  56     /**< \brief TPM0���  ����        */

#define DMA_REQUEST_MUX0_TSI            57     /**< \brief TSI ����                     */

#define DMA_REQUEST_MUX0_ALWAYSON0      60     /**< \brief �߽��0 ����           */
#define DMA_REQUEST_MUX0_ALWAYSON1      61     /**< \brief �߽��1 ����           */
#define DMA_REQUEST_MUX0_ALWAYSON2      62     /**< \brief �߽��2 ����           */
#define DMA_REQUEST_MUX0_ALWAYSON3      63     /**< \brief �߽��3 ����           */

/** @} */


/**
 * @} amhw_if_kl26_dma_chan
 */

#ifdef __cplusplus
}
#endif


#endif /* __KL26_DMAMUX_CHAN_H */

/* end of file */
