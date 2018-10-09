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
 * \brief I2SӲ��������ӿ�
 *
 * 1. ֧��1����������ͨ���ķ��������ж�����λʱ�Ӻ�֡ͬ����
 * 2. ֧��1����������ͨ���Ľ��������ж�����λʱ�Ӻ�֡ͬ����
 * 3. ���֡��С֧��2���֣�
 * 4. �ֵ�λ���ȿ���������8bits��32bits֮�䣻
 * 5. ֡�ĵ�һ���ֺ����µ��ֿ��Էֿ����ã�
 * 6. ���ͺͽ���ͨ������һ��32bit��FIFO��
 * 7. FIFO�����֧������������
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 2016-09-27  mkr, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FSL_I2S_H
#define __AMHW_FSL_I2S_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_fsl_if_i2s
 * \copydoc amhw_fsl_i2s.h
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

 /**
 * \name I2S ���Ϳ��ƼĴ���TCSR��Ӧ��λ���붨��
 * @{
 */

#define AMHW_FSL_I2S_TCSR_TE_MASK       (1UL << 31)  /**< \brief ����ʹ��            */
#define AMHW_FSL_I2S_TCSR_STOPE_MASK    (1UL << 30)  /**< \brief ֹͣģʽ�·���ʹ�� */
#define AMHW_FSL_I2S_TCSR_DBGE_MASK     (1UL << 29)  /**< \brief ����ģʽ�·���ʹ�� */
#define AMHW_FSL_I2S_TCSR_BCE_MASK      (1UL << 28)  /**< \brief λʱ��ʹ��          */
#define AMHW_FSL_I2S_TCSR_FR_MASK       (1UL << 25)  /**< \brief FIFO ��λ��ֻд     */
#define AMHW_FSL_I2S_TCSR_SR_MASK       (1UL << 24)  /**< \brief �����λ            */
#define AMHW_FSL_I2S_TCSR_WSF_MASK      (1UL << 20)  /**< \brief �ֿ�ʼ��־��д1��� */
#define AMHW_FSL_I2S_TCSR_SEF_MASK      (1UL << 19)  /**< \brief ֡ͬ�������־��д1��� */
#define AMHW_FSL_I2S_TCSR_FWF_MASK      (1UL << 17)  /**< \brief FIFO �ձ�־��ֻ��   */
#define AMHW_FSL_I2S_TCSR_FEF_MASK      (1UL << 18)  /**< \brief FIFO �����־��д1��� */
#define AMHW_FSL_I2S_TCSR_WSIE_MASK     (1UL << 12)  /**< \brief �ֿ�ʼ�ж�ʹ��      */
#define AMHW_FSL_I2S_TCSR_SEIE_MASK     (1UL << 11)  /**< \brief ͬ�������ж�ʹ��    */
#define AMHW_FSL_I2S_TCSR_FEIE_MASK     (1UL << 10)  /**< \brief FIFO ����ж�ʹ��   */
#define AMHW_FSL_I2S_TCSR_FWIE_MASK     (1UL << 9)   /**< \brief FIFO �����ж�ʹ��   */
#define AMHW_FSL_I2S_TCSR_FWDE_MASK     (1UL << 1)   /**< \brief FIFO ����ʱDMA����  */
/** @} */

/**
 * \name I2S �������üĴ���TCR2��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_TCR2_SYNC_MASK        (3UL << 30)   /**< \brief ����ͬ��ģʽ���� */
#define AMHW_FSL_I2S_TCR2_SYNC_DISABLE     (0UL << 30)   /**< \brief �����첽ģʽ     */
#define AMHW_FSL_I2S_TCR2_SYNC_SELF_RX     (1UL << 30)   /**< \brief �������RXͬ��   */
#define AMHW_FSL_I2S_TCR2_SYNC_ANOTHER_TX  (2UL << 30)   /**< \brief ����һ��TXͬ��   */
#define AMHW_FSL_I2S_TCR2_SYNC_ANOTHER_RX  (3UL << 30)   /**< \brief ����һ��RXͬ��   */
#define AMHW_FSL_I2S_TCR2_BCS_MASK         (1UL << 29)   /**< \brief ����λʱ�ӽ���   */
#define AMHW_FSL_I2S_TCR2_BCI_MASK         (1UL << 28)   /**< \brief ����λʱ������   */
#define AMHW_FSL_I2S_TCR2_MSEL_MASK        (3UL << 26)   /**< \brief ����λʱ��Դ     */
#define AMHW_FSL_I2S_TCR2_BCP_MASK         (1UL << 25)   /**< \brief ����λʱ�Ӽ���   */
#define AMHW_FSL_I2S_TCR2_BCD_MASK         (1UL << 24)   /**< \brief ����λʱ�ӷ���   */
#define AMHW_FSL_I2S_TCR2_DIV_MASK         (0xffUL)      /**< \brief ����λʱ�ӷ�Ƶ�� */
/** @} */

/**
 * \name I2S ���Ϳ��ƼĴ���TCR3��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_TCR3_TCE_MASK      (1UL << 16)  /**< \brief ����ͨ��ʹ��       */
#define AMHW_FSL_I2S_TCR3_WDFL_MASK     (1UL << 0)   /**< \brief �ֱ�־����         */
/** @} */

/**
 * \name I2S ���Ϳ��ƼĴ���TCR4��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_TCR4_FRSZ_MASK    (1UL << 16)    /**< \brief ����֡��С      */
#define AMHW_FSL_I2S_TCR4_SYWD_MASK    (0x1fUL << 8)  /**< \brief ����֡ͬ������  */
#define AMHW_FSL_I2S_TCR4_MF_MASK      (1UL << 4)     /**< \brief ��������MSB��ǰ */
#define AMHW_FSL_I2S_TCR4_FSE_MASK     (1UL << 3)     /**< \brief ֡ͬ����ǰ      */
#define AMHW_FSL_I2S_TCR4_FSP_MASK     (1UL << 1)     /**< \brief ֡ͬ������      */
#define AMHW_FSL_I2S_TCR4_FSD_MASK     (1UL << 0)     /**< \brief ֡ͬ������      */
/** @} */

/**
 * \name I2S ���Ϳ��ƼĴ���TCR5��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_TCR5_WNW_MASK    (0x1fUL << 24)  /**< \brief ������Nλ��  */
#define AMHW_FSL_I2S_TCR5_W0W_MASK    (0x1fUL << 16)  /**< \brief ������0λ��  */
#define AMHW_FSL_I2S_TCR5_FBT_MASK    (0x1fUL << 8)   /**< \brief ������λ��λ */
/** @} */

/**
 * \name I2S ��������Ĵ���TMR��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_TMR_TWM_MASK    (0x03UL << 0)  /**< \brief ���������� */
/** @} */

/**
 * \name I2S ���տ��ƼĴ���RCSR��Ӧ��λ���붨��
 * @{
 */

#define AMHW_FSL_I2S_RCSR_RE_MASK   (1UL << 31)  /**< \brief ����ʹ��                     */
#define AMHW_FSL_I2S_RCSR_STOPE     (1UL << 30)  /**< \brief ֹͣģʽ�½���ʹ��  */
#define AMHW_FSL_I2S_RCSR_DBGE_MASK (1UL << 29)  /**< \brief ����ģʽ�½���ʹ��  */
#define AMHW_FSL_I2S_RCSR_BCE_MASK  (1UL << 28)  /**< \brief λʱ��ʹ��                 */
#define AMHW_FSL_I2S_RCSR_FR_MASK   (1UL << 25)  /**< \brief FIFO ��λ��ֻд    */
#define AMHW_FSL_I2S_RCSR_SR_MASK   (1UL << 24)  /**< \brief �����λ                      */
#define AMHW_FSL_I2S_RCSR_WSF_MASK  (1UL << 20)  /**< \brief �ֿ�ʼ��־��д1��� */
#define AMHW_FSL_I2S_RCSR_SEF_MASK  (1UL << 19)  /**< \brief ֡ͬ�������־��д1���     */
#define AMHW_FSL_I2S_RCSR_FEF_MASK  (1UL << 18)  /**< \brief FIFO �����־��д1���  */
#define AMHW_FSL_I2S_RCSR_FWF_MASK  (1UL << 17)  /**< \brief FIFO ����־��ֻ�� */
#define AMHW_FSL_I2S_RCSR_WSIE_MASK (1UL << 12)  /**< \brief �ֿ�ʼ�ж�ʹ��            */
#define AMHW_FSL_I2S_RCSR_SEIE_MASK (1UL << 11)  /**< \brief ͬ�������ж�ʹ��         */
#define AMHW_FSL_I2S_RCSR_FEIE_MASK (1UL << 10)  /**< \brief FIFO ����ж�ʹ��   */
#define AMHW_FSL_I2S_RCSR_FWIE_MASK (1UL << 9)   /**< \brief FIFO �����ж�ʹ��   */
#define AMHW_FSL_I2S_RCSR_FWDE_MASK (1UL << 1)   /**< \brief FIFO ����ʱDMA����  */
/** @} */

/**
 * \name I2S ���տ��ƼĴ���RCR2��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_RCR2_SYNC_MASK        (3UL << 30)  /**< \brief ����ͬ��ģʽ   */
#define AMHW_FSL_I2S_RCR2_SYNC_DISABLE     (0UL << 30)  /**< \brief �����첽ģʽ   */
#define AMHW_FSL_I2S_RCR2_SYNC_SELF_TX     (1UL << 30)  /**< \brief �������RXͬ�� */
#define AMHW_FSL_I2S_RCR2_SYNC_ANOTHER_RX  (2UL << 30)  /**< \brief ����һ��TXͬ�� */
#define AMHW_FSL_I2S_RCR2_SYNC_ANOTHER_TX  (3UL << 30)  /**< \brief ����һ��RXͬ�� */
#define AMHW_FSL_I2S_RCR2_BCS_MASK         (1UL << 29)  /**< \brief ����λʱ�ӽ��� */
#define AMHW_FSL_I2S_RCR2_BCI_MASK         (1UL << 28)  /**< \brief ����λʱ������ */
#define AMHW_FSL_I2S_RCR2_MSEL_MASK        (1UL << 26)  /**< \brief ����λʱ��Դ   */
#define AMHW_FSL_I2S_RCR2_BCP_MASK         (1UL << 25)  /**< \brief ����λʱ�Ӽ��� */
#define AMHW_FSL_I2S_RCR2_BCD_MASK         (1UL << 24)  /**< \brief ����λʱ�ӷ��� */
#define AMHW_FSL_I2S_RCR2_DIV_MASK         (0xffUL)     /**< \brief ����λʱ�ӷ�Ƶϵ�� */
/** @} */

/**
 * \name I2S ���տ��ƼĴ���RCR3��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_RCR3_RCE_MASK      (1UL << 16)  /**< \brief ����ͨ��ʹ��  */
#define AMHW_FSL_I2S_RCR3_WDFL_MASK     (1UL << 0)   /**< \brief �ֱ�־����    */
/** @} */

/**
 * \name I2S ���տ��ƼĴ���RCR4��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_RCR4_FRSZ_MASK    (1UL << 16)    /**< \brief ����֡��С      */
#define AMHW_FSL_I2S_RCR4_SYWD_MASK    (0x1fUL << 8)  /**< \brief ����֡ͬ������  */
#define AMHW_FSL_I2S_RCR4_MF_MASK      (1UL << 4)     /**< \brief ��������MSB��ǰ */
#define AMHW_FSL_I2S_RCR4_FSE_MASK     (1UL << 3)     /**< \brief ֡ͬ����ǰ      */
#define AMHW_FSL_I2S_RCR4_FSP_MASK     (1UL << 1)     /**< \brief ֡ͬ������      */
#define AMHW_FSL_I2S_RCR4_FSD_MASK     (1UL << 0)     /**< \brief ֡ͬ������      */
/** @} */

/**
 * \name I2S ���Ϳ��ƼĴ���RCR5��Ӧ��λ���붨��
 * @{
 */
#define AMHW_FSL_I2S_RCR5_WNW_MASK    (0x1fUL << 24)  /**< \brief ������Nλ��  */
#define AMHW_FSL_I2S_RCR5_W0W_MASK    (0x1fUL << 16)  /**< \brief ������0λ��  */
#define AMHW_FSL_I2S_RCR5_FBT_MASK    (0x1fUL << 8)   /**< \brief ������λ��λ */
/** @} */

/**
  * \brief I2S�Ĵ�����ṹ��
  */
typedef struct amhw_fsl_i2s {
    __IO uint32_t tcsr;              /**< \brief SAI���Ϳ��ƼĴ���1  */
    __I  uint32_t reserved0[1];      /**< \brief ����                              */
    __IO uint32_t tcr2;              /**< \brief SAI���Ϳ��ƼĴ���2  */
    __IO uint32_t tcr3;              /**< \brief SAI���Ϳ��ƼĴ���3  */
    __IO uint32_t tcr4;              /**< \brief SAI���Ϳ��ƼĴ���4  */
    __IO uint32_t tcr5;              /**< \brief SAI���Ϳ��ƼĴ���5  */
    __I  uint32_t reserved1[2];      /**< \brief ����                              */
    __O  uint32_t tdr;               /**< \brief SAI�������ݼĴ���   */
    __I  uint32_t reserved2[15];     /**< \brief ����                              */
    __IO uint32_t tmr;               /**< \brief SAI��������Ĵ���   */
    __I  uint32_t reserved3[7];      /**< \brief ����                              */
    __IO uint32_t rcsr;              /**< \brief SAI���տ��ƼĴ���1  */
    __I  uint32_t reserved4[1];      /**< \brief ����                              */
    __IO uint32_t rcr2;              /**< \brief SAI���տ��ƼĴ���2  */
    __IO uint32_t rcr3;              /**< \brief SAI���տ��ƼĴ���3  */
    __IO uint32_t rcr4;              /**< \brief SAI���տ��ƼĴ���4  */
    __IO uint32_t rcr5;              /**< \brief SAI���տ��ƼĴ���5  */
    __I  uint32_t reserved5[2];      /**< \brief ����                              */
    __I  uint32_t rdr;               /**< \brief SAI�������ݼĴ���   */
    __I  uint32_t reserved6[15];     /**< \brief ����                              */
    __IO uint32_t rmr;               /**< \brief SAI��������Ĵ���   */
    __I  uint32_t reserved7[7];      /**< \brief ����                              */
    __IO uint32_t mcr;               /**< \brief SAI MCLK���ƼĴ���   */
    __IO uint32_t mdr;               /**< \brief SAI MCLK��Ƶ�Ĵ���   */
} amhw_fsl_i2s_t;

/**
 * \brief ����ʹ�õ�I2SЭ��
 */
typedef enum amhw_fsl_i2s_protocol {
    AMHW_FSL_I2S_PROTOCOL_LEFT      = 0, /**< \brief ����� */
    AMHW_FSL_I2S_PROTOCOL_RIGHET    = 1, /**< \brief �Ҷ��� */
    AMHW_FSL_I2S_PROTOCOL_TYPE      = 2, /**< \brief ����I2S */
    AMHW_FSL_I2S_PROTOCOL_PCMA      = 3, /**< \brief PCMA */
    AMHW_FSL_I2S_PROTOCOL_PCMB      = 4  /**< \brief PCMB */
} amhw_fsl_i2s_protocol_t;

/**
  * \brief ��������ģʽ
  */
typedef enum amhw_fsl_i2s_mode {
    AMHW_FSL_I2S_MODE_MASTER = 0,   /**< \brief ����ģʽ */
    AMHW_FSL_I2S_MODE_SLAVE  = 1    /**< \brief �ӻ���ģʽ */
} amhw_fsl_i2s_mode_t;

/**
  * \brief ����ͨ��ģʽ
  */
typedef enum amhw_fsl_i2s_channel_mode {
    AMHW_FSL_I2S_CHANNEL_MODE_MONO   = 0,  /**< \brief 1��ͨ��1֡ */
    AMHW_FSL_I2S_CHANNEL_MODE_STEREO = 1   /**< \brief 2��ͨ��1֡ */
} amhw_fsl_i2s_channel_mode_t;

/**
  * \brief ����ͬ��ģʽ
  */
typedef enum amhw_fsl_i2s_sync_mode {
    AMHW_FSL_I2S_SYNC_DISABLED   = 0,  /**< \brief  �첽ģʽ           */
    AMHW_FSL_I2S_SYNC_SELF       = 1,  /**< \brief  ��������/������ͬ��   */
    AMHW_FSL_I2S_SYNC_ANOTHER_TX = 2,  /**< \brief  ����һ��SAI������ͬ�� */
    AMHW_FSL_I2S_SYNC_ANOTHER_RX = 3   /**< \brief  ����һ��SAI������ͬ�� */
} amhw_fsl_i2s_sync_mode_t;

/**
  * \brief MCLK��ʱ��ʱ��Դ
  */
typedef enum amhw_fsl_i2s_mclk_src {
    AMHW_FSL_I2S_MCLK_SRC_SYSCLK  = 0, /**< \brief system clock            */
    AMHW_FSL_I2S_MCLK_SRC_SELECT1 = 1, /**< \brief OSCERCLK                 */
    AMHW_FSL_I2S_MCLK_SRC_SELECT2 = 2, /**< \brief Not Supported            */
    AMHW_FSL_I2S_MCLK_SRC_SELECT3 = 3  /**< \brief MCGPLLCLK/2 or MCGFLLCLK */
} amhw_fsl_i2s_mclk_src_t;

/**
  * \brief ����λʱ��Դ
  */
typedef enum amhw_fsl_i2s_bclk_src {
    AMHW_FSL_I2S_BCLK_SRC_BUS    = 0,  /**< \brief  bus_clk����ʱ��    */
    AMHW_FSL_I2S_BCLK_SRC_MCLK   = 1,  /**< \brief  mclk��ʱ��                */
    AMHW_FSL_I2S_BCLK_SRC_OTHER0 = 2,  /**< \brief  Not Supported */
    AMHW_FSL_I2S_BCLK_SRC_OTHER1 = 3   /**< \brief  Not Supported */
} amhw_fsl_i2s_bclk_src_t;

/**
  * \brief I2S�ж�����ʹ��λ
  */
typedef enum amhw_fsl_i2s_int_request {
    AMHW_FSL_I2S_INT_REQ_WORD_START = 1UL    << 12, /**< \brief  ����ʼ�ж�            */
    AMHW_FSL_I2S_INT_REQ_SYNC_ERROR = 1UL    << 11, /**< \brief  ͬ�������ж�         */
    AMHW_FSL_I2S_INT_REQ_FIFO_ERROR = 1UL    << 10, /**< \brief  FIFO�����ж�     */
    AMHW_FSL_I2S_INT_REQ_FIFO_WARN  = 1UL    << 9,  /**< \brief  FIFO�����ж�     */
    AMHW_FSL_I2S_INT_REQ_ALL        = 0x0FUL << 9,  /**< \brief  ���������ж����� */
} amhw_fsl_i2s_int_request_t;

/**
  * \brief I2S״̬��־
  */
typedef enum amhw_fsl_i2s_state_flag {
    AMHW_FSL_I2S_STATE_FLAG_WORD_START   = 1UL << 20,  /**< \brief ����ʼ��־       */
    AMHW_FSL_I2S_STATE_FLAG_SYNC_ERROR   = 1UL << 19,  /**< \brief ͬ�������־  */
    AMHW_FSL_I2S_STATE_FLAG_FIFO_ERROR   = 1UL << 18,  /**< \brief FIFO�����־ */
    AMHW_FSL_I2S_STATE_FLAG_FIFO_WARNING = 1UL << 17,  /**< \brief FIFO�����־ */
    AMHW_FSL_I2S_STATE_FLAG_SOFT_RESET   = 1UL << 24,  /**< \brief �����λ��־  */
    AMHW_FSL_I2S_STATE_FLAG_ALL          = 0x11E0000UL /**< \brief ���и�λ��־  */
} amhw_fsl_i2s_state_flag_t;

/**
  * \brief I2S��λ����
  */
typedef enum amhw_fsl_i2s_reset_type {
    AMHW_FSL_I2S_RESET_TYPE_SORFWARE = 1UL << 24, /**< \brief  �����λ      */
    AMHW_FSL_I2S_RESET_TYPE_FIFO     = 1UL << 25, /**< \brief  FIFO��λ     */
    AMHW_FSL_I2S_RESET_ALL           = 3UL << 24, /**< \brief  �����FIFO����λ      */
} amhw_fsl_i2s_reset_type_t;

/**
  * \brief I2S����ģʽ
  */
typedef enum amhw_fsl_i2s_run_mode {
    AMHW_FSL_I2S_RUN_MODE_DEBUG = 0, /**< \brief  ����ģʽ������  */
    AMHW_FSL_I2S_RUN_MODE_STOP  = 1  /**< \brief  ֹͣģʽ������  */
} amhw_fsl_i2s_run_mode_t;

/**
  * \brief I2Sʱ������
  */
typedef struct amhw_fsl_i2s_clock_cfg {
    amhw_fsl_i2s_mclk_src_t mclk_src; /**< \brief  ��ʱ��Դ            */
    amhw_fsl_i2s_bclk_src_t bclk_src; /**< \brief  λʱ��Դ            */
    uint32_t mclk_src_freq;            /**< \brief  ��ʱ��ԴƵ��  */
    uint32_t mclk;                     /**< \brief  ��ʱ��Ƶ��       */
    uint32_t bclk;                     /**< \brief  λʱ��Ƶ��       */
    uint32_t bclk_src_freq;            /**< \brief  λʱ��ԴƵ��  */
} amhw_fsl_i2s_clock_cfg_t;

/*******************************************************************************
 * �������Ĵ�������
 ******************************************************************************/

/**
 * \brief ����I2S ���Ϳ���/״̬�Ĵ���TCSR��Ӧ��λΪ1
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCSR_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_tcsr_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tcsr |= flags;
}

/**
 * \brief ���I2S ���Ϳ���/״̬�Ĵ���TCSR��Ӧ��λΪ0
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCSR_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_tcsr_clr (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tcsr &= ~flags;
}

/**
 * \brief ��ȡI2S ���Ϳ���/״̬�Ĵ���TCSR��ֵ
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return ���Ϳ��ƼĴ���TCSR��ֵ
 */
am_static_inline
uint32_t amhw_fsl_i2s_tcsr_get (amhw_fsl_i2s_t *p_hw_i2s)
{
    return (p_hw_i2s->tcsr);
}

/**
 * \brief ����I2S �������üĴ���TCR2��Ӧ��λΪ1
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCR2_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_tcr2_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tcr2 |= flags;
}

/**
 * \brief ���I2S �������üĴ���TCR2��Ӧ��λΪ0
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCR2_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_tcr2_clr (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tcr2 &= ~flags;
}

/**
 * \brief ����I2S �������üĴ���TCR3��Ӧ��λΪ1
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCR3_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_tcr3_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tcr3 |= flags;
}

/**
 * \brief ���I2S �������üĴ���TCR3��Ӧ��λΪ0
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCR3_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_tcr3_clr (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tcr3 &= ~flags;
}

/**
 * \brief ����I2S �������üĴ���TCR4��Ӧ��λΪ1
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCR4_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_tcr4_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tcr4 |= flags;
}

/**
 * \brief ���I2S �������üĴ���TCR4��Ӧ��λΪ0
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCR4_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_tcr4_clr (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tcr4 &= ~flags;
}

/**
 * \brief ����I2S ����λʱ�ӷ�Ƶϵ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] div      : MCLKʱ�ӷ�Ƶϵ��
 *
 * \note ʵ�ʷ�Ƶ���� (DIV + 1) * 2
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_bclk_div_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t div)
{
    p_hw_i2s->tcr2 = (p_hw_i2s->tcr2 & (~0xff)) | div;
}

/**
 * \brief ����I2S ����λʱ��Դ
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] src      : I2S����λʱ��Դ
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_bclk_src_set (amhw_fsl_i2s_t          *p_hw_i2s,
                                    amhw_fsl_i2s_bclk_src_t  src)
{
    p_hw_i2s->tcr2 = (p_hw_i2s->tcr2 & (~(3UL << 26))) | (src << 26);
}

/**
 * \brief ����I2S ����֡��С
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] size     : ֡�ֽڴ�С��0:һ���ִ�С��1:�����ִ�С
 *
 * \note ����֡��������֡��СΪ2����
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_frame_size_set (amhw_fsl_i2s_t *p_hw_i2s,
                                      uint32_t         size)
{
    p_hw_i2s->tcr4 = (p_hw_i2s->tcr4 & (~(1UL << 16))) | (size << 16);
}

/**
 * \brief ����I2S ����֡ͬ��λʱ�ӳ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] width    : ֡ͬ��λʱ�ӿ��
 *                       ֵΪ0ʱ��ʾͬ������Ϊ1��λʱ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_sywd_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t width)
{
    p_hw_i2s->tcr4 = ((p_hw_i2s->tcr4 & (~(0x1f << 8))) |
                     ((width & 0x1f) << 8));
}

/**
 * \brief ����I2S ����֡�г���һ��������ֵ�λ��С
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] width    : �ֵ�λ��С
 *
 * \note set= width +1
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_wnw_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t width)
{
    p_hw_i2s->tcr5 = (p_hw_i2s->tcr5 & (~(0x1f << 24))) |
                     ((width & 0x1f) << 24);
}

/**
 * \brief ����I2S ����֡�е�һ����λ��С
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] width   : �ֵ�λ��С
 *
 * \note �������ֵĳ���С��8bits���ֵ�ʵ��λ����= width + 1
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_w0w_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t width)
{
    p_hw_i2s->tcr5 = (p_hw_i2s->tcr5 & (~(0x1f << 16))) |
                     ((width & 0x1f) << 16);
}

/**
 * \brief ����I2S ����֡���ֵ�λƽ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] shift    : ƽ��λ��
 *
 * \note �뷢���ֵ�MSB������أ�������MSBʱ��λ��ֵ = ������λ����-1
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_fbt_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t shift)
{
    p_hw_i2s->tcr5 = (p_hw_i2s->tcr5 & (~(0x1f << 8))) |
                     ((shift & 0x1f) << 8);
}

/**
 * \brief I2S����һ������
 * \param[in] p_hw_i2s : set
 * \param[in] data     : ���͵�����
 *
 * \note �������ݻ����дFIFO����������Ҫ��֤����ͨ��ʹ�ܺ�FIFO���к��޴�
 * \return ��
 */
am_static_inline
void amhw_fsl_i2s_txdata_write (amhw_fsl_i2s_t *p_hw_i2s, uint32_t data)
{
    p_hw_i2s->tdr = data;
}

/**
 * \brief ����I2S ������������Ĵ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_FSL_I2S_TCR3_*��ֵ
 *
 * \note ֡�ж�Ӧ��������ʹ�ܺ�ʹ�������Ÿ���̬�������ȡFIFO����
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_mask_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->tmr = flags;
}

/*******************************************************************************
 * �������Ĵ�������
 ******************************************************************************/

/**
 * \brief ����I2S ���տ���/״̬�Ĵ���RCSR��Ӧ��λΪ1
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCSR_*��ֵ
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_rcsr_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rcsr |= flags;
}

/**
 * \brief ���I2S ���տ���/״̬�Ĵ���RCSR��Ӧ��λΪ0
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCSR_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_rcsr_clr (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rcsr &= ~flags;
}

/**
 * \brief ��ȡI2S ���տ���/״̬�Ĵ���RCSR��ֵ
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return ���տ��ƼĴ���RCSR��ֵ
 */
am_static_inline
uint32_t amhw_fsl_i2s_rcsr_get (amhw_fsl_i2s_t *p_hw_i2s)
{
    return (p_hw_i2s->rcsr);
}

/**
 * \brief ����I2S �������üĴ���RCR2��Ӧ��λΪ1
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCR2_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_rcr2_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rcr2 |= flags;
}

/**
 * \brief ���I2S �������üĴ���RCR2��Ӧ��λΪ0
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCR2_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_rcr2_clr (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rcr2 &= ~flags;
}

/**
 * \brief ����I2S �������üĴ���RCR3��Ӧ��λΪ1
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCR3_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_rcr3_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rcr3 |= flags;
}

/**
 * \brief ���I2S �������üĴ���RCR3��Ӧ��λΪ0
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCR3_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_rcr3_clr (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rcr3 &= ~flags;
}

/**
 * \brief ����I2S �������üĴ���RCR4��Ӧ��λΪ1
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCR4_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_rcr4_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rcr4 |= flags;
}

/**
 * \brief ���I2S �������üĴ���RCR4��Ӧ��λΪ0
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCR4_*��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_rcr4_clr (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rcr4 &= ~flags;
}

/**
 * \brief ����I2S ����λʱ�ӷ�Ƶϵ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] div      : MCLKʱ�ӷ�Ƶϵ��
 *
 * \note ʵ�ʷ�Ƶ���� (DIV + 1) * 2
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_bclk_div_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t div)
{
    p_hw_i2s->rcr2 = ((p_hw_i2s->rcr2 & (~0xff)) | div);
}

/**
 * \brief ����I2S ����λʱ��Դ
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] src      : I2S����λʱ��Դ
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_bclk_src_set (amhw_fsl_i2s_t          *p_hw_i2s,
                                    amhw_fsl_i2s_bclk_src_t  src)
{
    p_hw_i2s->rcr2 = ((p_hw_i2s->rcr2 & (~(3UL << 26))) | (src << 26));
}

/**
 * \brief ����I2S ����֡��С
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] size     : ֡�ֽڴ�С��0��һ���ִ�С��1:�����ִ�С
 *
 * \note ����֡��������֡��СΪ2����
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_frame_size_set (amhw_fsl_i2s_t *p_hw_i2s,
                                      uint32_t         size)
{
    p_hw_i2s->rcr4 = ((p_hw_i2s->rcr4 & (~(1UL << 16))) | (size << 16));
}

/**
 * \brief ����I2S ����֡ͬ��λʱ�ӳ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] width    : ֡ͬ��λʱ�ӿ��
 *                       ֵΪ0ʱ��ʾͬ������Ϊ1��λʱ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_sywd_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t width)
{
    p_hw_i2s->rcr4 = ((p_hw_i2s->rcr4 & (~(0x1f << 8))) |
                     ((width & 0x1f) << 8));
}

/**
 * \brief ����I2S ����֡�г���һ��������ֵ�λ��С
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] width    : �ֵ�λ��С
 *
 * \note set = width +1
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_wnw_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t width)
{
    p_hw_i2s->rcr5 = ((p_hw_i2s->rcr5 & (~(0x1f << 24))) |
                     ((width & 0x1f) << 24));
}

/**
 * \brief ����I2S ����֡�е�һ����λ��С
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] width    : �ֵ�λ��С
 *
 * \note �������ֵĳ���С��8bits���ֵ�ʵ��λ���� = width +1
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_w0w_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t width)
{
    p_hw_i2s->rcr5 = ((p_hw_i2s->rcr5 & (~(0x1f << 16))) |
                     ((width & 0x1f) << 16));
}

/**
 * \brief ����I2S ����֡���ֵ�λƽ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] shift    : ƽ��λ��
 *
 * \note ������ֵ�MSB������أ�������MSBʱ��λ��ֵ = ������λ����-1
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_fbt_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t shift)
{
    p_hw_i2s->rcr5 = ((p_hw_i2s->rcr5 & (~(0x1f << 8))) |
                     ((shift & 0x1f) << 8));
}

/**
 * \brief I2S����һ������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return ���յ�����
 */
am_static_inline
uint32_t amhw_fsl_i2s_rxdata_read (amhw_fsl_i2s_t *p_hw_i2s)
{
    return (p_hw_i2s->rdr);
}

/**
 * \brief ����I2S ������������Ĵ���
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2S_RCR3_*��ֵ
 *
 * \note ֡�ж�Ӧ��������ʹ�ܺ�ʹ�������Ÿ���̬�������ȡFIFO����
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_mask_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t flags)
{
    p_hw_i2s->rmr = flags;
}

/*******************************************************************************
* ��ʱ������
*******************************************************************************/

/**
 * \brief MCLK��Ƶʱ������Դѡ��
 * \param[in] p_hw_i2s : ָ��i2s�Ĵ������ָ��
 * \param[in] src      : MCLK��Ƶʱ������Դ
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_mclk_src_set (amhw_fsl_i2s_t          *p_hw_i2s,
                                 amhw_fsl_i2s_mclk_src_t  src)
{
    p_hw_i2s->mcr = (p_hw_i2s->mcr & (~(3UL << 24))) | (src << 24);
}

/**
 * \brief MCLKʱ�����ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_mclk_enable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->mcr |= 1 << 30;
}

/**
 * \brief MCLKʱ���������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \note MCLKʱ���������ʱ����Ƶ���رգ�������ΪMCLK����
 * \return    ��
 */
am_static_inline
void amhw_fsl_i2s_mclk_disable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->mcr &= ~(1 << 30);
}

/**
 * \brief ��ȡI2S MCLK��Ƶ������״̬��־
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \note ����MCLK��Ƶ��״̬Ϊ0ʱ���������÷�Ƶֵ
 * \retval 0: MCLK ��ƵƵ��δ����
 * \retval 1: MCLK ��ƵƵ���Ѿ�����
 */
am_static_inline
am_bool_t amhw_fsl_i2s_mclk_duf_get (amhw_fsl_i2s_t *p_hw_i2s)
{
    return ((am_bool_t)((p_hw_i2s->mcr >> 31) & 0x01));
}

/**
 * \brief ����I2S MCLKʱ�ӷ�Ƶ�ķ���ֵ
 *        MCLK output = MCLK input * ( (FRACT + 1) / (DIVIDE + 1) ).
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] fract    : MCLKʱ�ӷ�Ƶ�ķ���ֵ0~127
 *
 * \note MCLKʱ�ӷ�Ƶ��FRACTֵ����С�ڻ����DIV
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_mclk_fract_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t fract)
{
    p_hw_i2s->mdr = (p_hw_i2s->mdr & (~(0xff << 12))) | ((fract & 0xff) << 12);
}

/**
 * \brief ����I2S MCLKʱ��С����Ƶ�ķ�ĸֵ
 *        MCLK output = MCLK input * ( (FRACT + 1) / (DIVIDE + 1) ).
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] div      : MCLKʱ�ӷ�Ƶ�ķ�ĸֵ
 *
 * \note MCLKʱ�ӷ�Ƶ��FRACTֵ����С�ڻ����DIV
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_mclk_div_set (amhw_fsl_i2s_t *p_hw_i2s, uint32_t div)
{
    p_hw_i2s->mdr = (p_hw_i2s->mdr & (~0xfff)) | (div & 0xfff);
}

/*******************************************************************************
*  API
*******************************************************************************/

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
                                     uint32_t         src_clk);

/**
 * \brief I2S���ͼĴ�����ʼ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_init (amhw_fsl_i2s_t *p_hw_i2s);

/**
 * \brief I2S���ռĴ�����ʼ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
void amhw_i2s_rx_init (amhw_fsl_i2s_t *p_hw_i2s);

/**
 * \brief I2S��Э������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] protocol : ʹ�õ�I2SЭ��
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_protocol_set (amhw_fsl_i2s_t          *p_hw_i2s,
                                    amhw_fsl_i2s_protocol_t  protocol);

/**
 * \brief I2S����Э������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] protocol : ʹ�õ�I2SЭ��
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_protocol_set (amhw_fsl_i2s_t          *p_hw_i2s,
                                    amhw_fsl_i2s_protocol_t  protocol);

/**
 * \brief I2S����ʱ������
 * \param[in] p_hw_i2s   : ָ��I2S�Ĵ������ָ��
 * \param[in] clk_config : i2s����ʱ�����ò���
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_clock_setup (amhw_fsl_i2s_t           *p_hw_i2s,
                                   amhw_fsl_i2s_clock_cfg_t *clk_config);

/**
 * \brief I2S����ʱ������
 * \param[in] p_hw_i2s   : ָ��I2S�Ĵ������ָ��
 * \param[in] clk_config : i2s����ʱ�����ò���
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_clock_setup (amhw_fsl_i2s_t           *p_hw_i2s,
                                   amhw_fsl_i2s_clock_cfg_t *clk_config);

/**
 * \brief I2S�����ֳ�������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] protocol : ʹ�õ�I2SЭ��
 * \param[in] bits : λ����
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_word_width_cfg (amhw_fsl_i2s_t         *p_hw_i2s,
                                      amhw_fsl_i2s_protocol_t protocol,
                                      uint32_t                 bits);

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
                                      uint32_t                  bits);

/**
 * \brief I2S����ͨ��ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_channel_enable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->tcr3 |= AMHW_FSL_I2S_TCR3_TCE_MASK;
}

/**
 * \brief I2S����ͨ��ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_channel_enable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->rcr3 |= AMHW_FSL_I2S_RCR3_RCE_MASK;
}

/**
 * \brief I2S����ͨ��ģʽ���ã�����������������
 * \param[in] p_hw_i2s     : ָ��I2S�Ĵ������ָ��
 * \param[in] channel_mode : ����ͨ��ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_channel_mode_set (amhw_fsl_i2s_t              *p_hw_i2s,
                                        amhw_fsl_i2s_channel_mode_t  channel_mode);

/**
 * \brief I2S����ͨ��ģʽ���ã�����������������
 * \param[in] p_hw_i2s     : ָ��I2S�Ĵ������ָ��
 * \param[in] channel_mode : ����ͨ��ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_channel_mode_set (amhw_fsl_i2s_t              *p_hw_i2s,
                                        amhw_fsl_i2s_channel_mode_t  channel_mode);

/**
 * \brief I2S��������ģʽ����
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] tx_mode  : ����ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_mode_set (amhw_fsl_i2s_t      *p_hw_i2s,
                                amhw_fsl_i2s_mode_t  tx_mode);

/**
 * \brief I2S��������ģʽ����
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] tx_mode  : ����ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_mode_set (amhw_fsl_i2s_t      *p_hw_i2s,
                                amhw_fsl_i2s_mode_t  tx_mode);

/**
 * \brief I2S����ͬ����ģʽ����
 * \param[in] p_hw_i2s  : ָ��I2S�Ĵ������ָ��
 * \param[in] sync_mode : ����ͬ����ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_sync_mode_set (amhw_fsl_i2s_t           *p_hw_i2s,
                                     amhw_fsl_i2s_sync_mode_t  sync_mode);

/**
 * \brief I2S����ͬ����ģʽ����
 * \param[in] p_hw_i2s  : ָ��I2S�Ĵ������ָ��
 * \param[in] sync_mode : ����ͬ����ģʽ
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_sync_mode_set (amhw_fsl_i2s_t           *p_hw_i2s,
                                     amhw_fsl_i2s_sync_mode_t  sync_mode);

/**
 * \brief I2S �����ж�����ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] int_req  : �ж����������
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_int_enable (amhw_fsl_i2s_t             *p_hw_i2s,
                                  amhw_fsl_i2s_int_request_t  int_req)
{
    p_hw_i2s->tcsr |= int_req;
}

/**
 * \brief I2S �����ж�����ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] int_req  : �ж����������
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_int_enable (amhw_fsl_i2s_t *p_hw_i2s,
                                  amhw_fsl_i2s_int_request_t int_req)
{
    p_hw_i2s->rcsr |= int_req;
}

/**
 * \brief I2S �����ж��������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] int_req : �ж����������
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_int_disable (amhw_fsl_i2s_t *p_hw_i2s,
                                   amhw_fsl_i2s_int_request_t int_req)
{
    p_hw_i2s->tcsr &= ~int_req;
}

/**
 * \brief I2S �����ж��������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] int_req  : �ж����������
 *
 * \return  ��
 */
am_static_inline
void amhw_i2s_rx_int_disable (amhw_fsl_i2s_t             *p_hw_i2s,
                              amhw_fsl_i2s_int_request_t  int_req)
{
    p_hw_i2s->rcsr &= ~int_req;
}

/**
 * \brief I2S ����DMA����ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_dma_request_enable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->tcsr |= AMHW_FSL_I2S_TCSR_FWDE_MASK;
}

/**
 * \brief I2S ����DMA����ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_dma_request_enable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->rcsr |= AMHW_FSL_I2S_TCSR_FWDE_MASK;
}

/**
 * \brief I2S ����DMA�������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_dma_request_disable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->tcsr &= ~AMHW_FSL_I2S_TCSR_FWDE_MASK;
}

/**
 * \brief I2S ����DMA�������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_dma_request_disable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->tcsr &= ~AMHW_FSL_I2S_TCSR_FWDE_MASK;
}

/**
 * \brief I2S �������״̬��־
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] flag_mask : ״̬�ı�־
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_state_flag_clr (amhw_fsl_i2s_t            *p_hw_i2s,
                                      amhw_fsl_i2s_state_flag_t  flag_mask);

/**
 * \brief I2S �������״̬��־
 * \param[in] p_hw_i2s  : ָ��I2S�Ĵ������ָ��
 * \param[in] flag_mask : ״̬�ı�־
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_state_flag_clr (amhw_fsl_i2s_t            *p_hw_i2s,
                                      amhw_fsl_i2s_state_flag_t  flag_mask);

/**
 * \brief I2S��������λ
 * \param[in] p_hw_i2s   : ָ��I2S�Ĵ������ָ��
 * \param[in] reset_mask : ��λ������
 *
 * \return  ��
 */
void amhw_fsl_i2s_tx_reset_set (amhw_fsl_i2s_t            *p_hw_i2s,
                                 amhw_fsl_i2s_reset_type_t  reset_mask);

/**
 * \brief I2S��������λ
 * \param[in] p_hw_i2s   : ָ��I2S�Ĵ������ָ��
 * \param[in] reset_mask : ��λ������
 *
 * \return  ��
 */
void amhw_fsl_i2s_rx_reset_set (amhw_fsl_i2s_t            *p_hw_i2s,
                                 amhw_fsl_i2s_reset_type_t  reset_mask);

/**
 * \brief I2S ������ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_enable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->tcsr |= AMHW_FSL_I2S_TCSR_BCE_MASK;
    p_hw_i2s->tcsr |= AMHW_FSL_I2S_TCSR_TE_MASK;
}

/**
 * \brief I2S ������ʹ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_enable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->rcsr |= AMHW_FSL_I2S_RCSR_BCE_MASK;
    p_hw_i2s->rcsr |= AMHW_FSL_I2S_RCSR_RE_MASK;
}

/**
 * \brief I2S ����������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_tx_disable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->tcsr &= ~AMHW_FSL_I2S_TCSR_BCE_MASK;
    p_hw_i2s->tcsr &= ~AMHW_FSL_I2S_TCSR_TE_MASK;
}

/**
 * \brief I2S ����������
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  ��
 */
am_static_inline
void amhw_fsl_i2s_rx_disable (amhw_fsl_i2s_t *p_hw_i2s)
{
    p_hw_i2s->rcsr &= ~AMHW_FSL_I2S_RCSR_BCE_MASK;
    p_hw_i2s->rcsr &= ~AMHW_FSL_I2S_RCSR_RE_MASK;
}

/**
 * \brief I2S�������ݣ���ѯģʽ��
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] txBuff   : ָ��Ҫ���ͻ�������ָ��
 * \param[in] size     : Ҫ�������ݵĳ���
 *
 * \return  ��
 */
void amhw_fsl_i2s_senddata_polling (amhw_fsl_i2s_t *p_hw_i2s,
                                     uint32_t        *txBuff,
                                     uint32_t         size);

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
                                        uint32_t         size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FSL_I2S_H */

/* end of file */
