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
 * \brief DMA Ӳ�������ӿڡ�
 *
 * 1. 4�������ɱ�̵�DMA����ͨ����
 * 2. ˫��ַ����ͨ��32λ�������ӵ�ϵͳ�����ϡ�
 * 3. 8��16��32λ�Ŀ����ݴ��䡣
 * 4. ֧�ֿɱ�̵�Դ��ַ��Ŀ�ĵ�ַ�Լ������ֽ�����
 * 5. ��ѡ�ĵ�/˫ͨ�����ӡ�
 * 6. ��ѡ�ķ���Դ��ַ��Ŀ���ַ�ľ���
 * 7. �ڴ���߽�ʹ�ù̶����ȼ�������ͨ���ٲá�
 * 8. ֧��Դ��ַ��Ŀ�ĵ�ַ���Զ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-16  mkr, first implementation.
 * \endinternal
 */

#ifndef __KL26_DMA_H
#define __KL26_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_common.h"

/**
 * \addtogroup amhw_kl26_if_dma
 * \copydoc amhw_kl26_dma.h
 * @{
 */

#define KL26_DMA_CHAN_CNT       4     /**< \brief DMA ͨ������ */

/******************************************************************************/
/**
 * \brief DMA ͨ���Ĵ����ṹ��
 */
typedef struct amhw_kl26_dmamux {
    __IO  uint8_t  chcfg[4];            /**< \brief DMA ͨ�����üĴ���           */
} amhw_kl26_dmamux_t;

/**
 * \brief DMA �������Ĵ�����ṹ��
 */
typedef struct amhw_kl26_dma_chan {
    __IO uint32_t  dma_sar;             /**< \brief DMA Դ��ַ���üĴ���       */
    __IO uint32_t  dma_dar;             /**< \brief DMA Ŀ�ĵ�ַ���üĴ���  */
    __IO uint32_t  dma_dsr_bcr;         /**< \brief DMA ״̬�Ĵ���                      */
    __IO uint32_t  dma_dcr;             /**< \brief DMA ���ƼĴ���                      */
} amhw_kl26_dma_chan_t;

#define  KL26_DMA_TRIGGER_ENABLE           (1UL << 6)       /**< \brief DMA ����ʹ��                  */
#define  KL26_DMA_TRIGGER_DISABLE          (0UL << 6)       /**< \brief DMA ��������                  */

#define  KL26_DMA_ADDRESS_VALUE_ALLOWED_1  (0x000UL << 20)  /**< \brief DMA ��Ч��ַģʽ1  */
#define  KL26_DMA_ADDRESS_VALUE_ALLOWED_2  (0x1FFUL << 20)  /**< \brief DMA ��Ч��ַģʽ2  */
#define  KL26_DMA_ADDRESS_VALUE_ALLOWED_3  (0x200UL << 20)  /**< \brief DMA ��Ч��ַģʽ3  */
#define  KL26_DMA_ADDRESS_VALUE_ALLOWED_4  (0x400UL << 20)  /**< \brief DMA ��Ч��ַģʽ4  */

/**
 * \brief DMA ͨ��ѡ��ṹ��
 */
typedef struct amhw_kl26_dma {
    amhw_kl26_dma_chan_t    dma_chan[4];     /**< \brief DMA ͨ������                            */
} amhw_kl26_dma_t;

/**
 * \brief DMA ģʽѡ��
 */
typedef enum amhw_kl26_dma_transfer_type {
    KL26_DMA_PER_TO_MER,     /**< \brief DMA ���赽�ڴ�                            */
    KL26_DMA_MER_TO_PER,     /**< \brief DMA �ڴ浽����                            */
    KL26_DMA_MER_TO_MER,     /**< \brief DMA �ڴ浽�ڴ�                            */
    KL26_DMA_PER_TO_PER      /**< \brief DMA ���赽����                            */
} amhw_kl26_dma_transfer_type_t;

#define  KL26_DMA_DCR_INTERRUTP_DISABLE         (0UL << 31)   /**< \brief DMA�жϽ���              */
#define  KL26_DMA_DCR_INTERRUTP_ENABLE          (1UL << 31)   /**< \brief DMA�ж�ʹ��              */

#define  KL26_DMA_DCR_PER_REQUEST_DISABLE       (0UL << 30)   /**< \brief DMA��������ʹ��    */
#define  KL26_DMA_DCR_PER_REQUEST_ENABLE        (1UL << 30)   /**< \brief DMA�����������    */

#define  KL26_DMA_DCR_CYCLE_TRANSFERS           (0UL << 29)   /**< \brief DMAѭ������              */
#define  KL26_DMA_DCR_SINGLE_TRANSFERS          (1UL << 29)   /**< \brief DMA���δ���              */

#define  KL26_DMA_DCR_AUTO_ALIGN_DISABLE        (0UL << 28)   /**< \brief DMA�Զ��������    */
#define  KL26_DMA_DCR_AUTO_ALIGN_ENABLE         (1UL << 28)   /**< \brief DMA�Զ�����ʹ��    */

#define  KL26_DMA_DCR_SOURCE_INCR_DISABLE       (0UL << 22)   /**< \brief Դ��ַ��������        */
#define  KL26_DMA_DCR_SOURCE_INCR_ENABLE        (1UL << 22)   /**< \brief Դ��ַ����ʹ��        */

#define  KL26_DMA_DCR_SOURCE_SIZE_32_BIT        (0x0UL << 20) /**< \brief 32λ����                       */
#define  KL26_DMA_DCR_SOURCE_SIZE_8_BIT         (0x1UL << 20) /**< \brief 8 λ����                       */
#define  KL26_DMA_DCR_SOURCE_SIZE_16_BIT        (0x2UL << 20) /**< \brief 16λ����                       */

#define  KL26_DMA_DCR_DESTINATION_INCR_DISABLE  (0UL << 19)   /**< \brief Ŀ�ĵ�ַ����ʹ��    */
#define  KL26_DMA_DCR_DESTINATION_INCR_ENABLE   (1UL << 19)   /**< \brief Ŀ�ĵ�ַ����ʹ��    */

#define  KL26_DMA_DCR_DESTINATION_SIZE_32_BIT   (0x0UL << 17) /**< \brief 32λ����                        */
#define  KL26_DMA_DCR_DESTINATION_SIZE_8_BIT    (0x1UL << 17) /**< \brief 8 λ����                        */
#define  KL26_DMA_DCR_DESTINATION_SIZE_16_BIT   (0x2UL << 17) /**< \brief 16λ����                        */

#define  KL26_DMA_DCR_START_DISABLE             (0x0UL << 16) /**< \brief �����������              */
#define  KL26_DMA_DCR_START_ENABLE              (0x1UL << 16) /**< \brief �������ʹ��              */

#define KL26_DMA_DCR_REQUEST_NO_AFFECTED        (0x0UL << 7)  /**< \brief ����ûӰ��                   */
#define KL26_DMA_DCR_REQUEST_AFFECTED           (0x1UL << 7)  /**< \brief ������Ӱ��                   */

/** \brief û��ͨ������      */
#define  KL26_DMA_DCR_NO_LINKING                (0x0UL << 4)

/** \brief ÿ�����ں����ӵ�LCH1����BCR��0�����ӵ�LCH2 */
#define  KL26_DMA_DCR_LCH1_TO_LCH2              (0x1UL << 4)

/** \brief ÿ�����ڽ������ӵ�LCH1  */
#define  KL26_DMA_DCR_EACH_CYCLE_TO_LCH1        (0x2UL << 4)

/** \brief BCR��0���ӵ�LCH1  */
#define  KL26_DMA_DCR_BCR_ZERO_TO_LCH1          (0x3UL << 4)

#define  KL26_DMA_DCR_LCH1_CHAN0                (0x0UL << 2)  /**< \brief LCH1ӳ�䵽ͨ��0 */
#define  KL26_DMA_DCR_LCH1_CHAN1                (0x1UL << 2)  /**< \brief LCH1ӳ�䵽ͨ��1 */
#define  KL26_DMA_DCR_LCH1_CHAN2                (0x2UL << 2)  /**< \brief LCH1ӳ�䵽ͨ��2 */
#define  KL26_DMA_DCR_LCH1_CHAN3                (0x3UL << 2)  /**< \brief LCH1ӳ�䵽ͨ��3 */

#define  KL26_DMA_DCR_LCH2_CHAN0                (0x0UL)       /**< \brief LCH2ӳ�䵽ͨ��0 */
#define  KL26_DMA_DCR_LCH2_CHAN1                (0x1UL)       /**< \brief LCH2ӳ�䵽ͨ��1 */
#define  KL26_DMA_DCR_LCH2_CHAN2                (0x2UL)       /**< \brief LCH2ӳ�䵽ͨ��2 */
#define  KL26_DMA_DCR_LCH2_CHAN3                (0x3UL)       /**< \brief LCH2ӳ�䵽ͨ��3 */

/**
 * \brief ��������С����ö����
 */
typedef enum amhw_kl26_dma_buffer_size_set {
    KL26_DMA_BUFFER_DISABLE = 0,    /**< \brief �޻�����                  */
    KL26_DMA_BUFFER_16_BYTES,       /**< \brief 16�ֽڻ�����        */
    KL26_DMA_BUFFER_32_BYTES,       /**< \brief 32�ֽڻ�����        */
    KL26_DMA_BUFFER_64_BYTES,       /**< \brief 64�ֽڻ�����        */
    KL26_DMA_BUFFER_128_BYTES,      /**< \brief 128�ֽڻ�����      */
    KL26_DMA_BUFFER_256_BYTES,      /**< \brief 256�ֽڻ�����      */
    KL26_DMA_BUFFER_512_BYTES,      /**< \brief 512�ֽڻ�����      */
    KL26_DMA_BUFFER_1_KB,           /**< \brief 1KB������                */
    KL26_DMA_BUFFER_2_KB,           /**< \brief 2KB������                */
    KL26_DMA_BUFFER_4_KB,           /**< \brief 4KB������                */
    KL26_DMA_BUFFER_8_KB,           /**< \brief 8KB������                 */
    KL26_DMA_BUFFER_16_KB,          /**< \brief 16KB������              */
    KL26_DMA_BUFFER_32_KB,          /**< \brief 32KB������              */
    KL26_DMA_BUFFER_64_KB,          /**< \brief 64KB������              */
    KL26_DMA_BUFFER_128_KB,         /**< \brief 128KB������            */
    KL26_DMA_BUFFER_256_KB,         /**< \brief 256KB������            */
} amhw_kl26_dma_buffer_size_set_t;


/**
 * \brief DMA ����������
 */
typedef struct amhw_kl26_dma_xfer_desc {
    volatile uint32_t          xfercfg;        /**< \brief ��������                     */
    volatile uint32_t          src_addr;       /**< \brief Դ���ݵ�ַ                */
    volatile uint32_t          dst_addr;       /**< \brief Ŀ�����ݵ�ַ           */
    volatile uint32_t          nbytes;         /**< \brief ���������ֽ���      */
} amhw_kl26_dma_xfer_desc_t;

/**
 * \brief ʹ��DMAͨ��
 *
 * \param[in] p_hw_dmamux : ָ��DMAͨ���������Ĵ������ָ��
 * \param[in] chan        : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_chan_enable (amhw_kl26_dmamux_t *p_hw_dmamux,
                                uint8_t             chan)
{
    p_hw_dmamux->chcfg[chan] |=(1UL<<7);
}

/**
 * \brief ����DMAͨ��
 *
 * \param[in] p_hw_dmamux : ָ��DMAͨ���������Ĵ������ָ��
 * \param[in] chan        : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_chan_disable (amhw_kl26_dmamux_t *p_hw_dmamux,
                                 uint8_t             chan)
{
    p_hw_dmamux->chcfg[chan] &= ~(1UL<<7);
}

/**
 * \brief ʹ��DMAͨ��������
 *
 * \param[in] p_hw_dmamux : ָ��DMAͨ���������Ĵ������ָ��
 * \param[in] chan        : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_trig_enable (amhw_kl26_dmamux_t *p_hw_dmamux,
                                uint8_t             chan)
{
    p_hw_dmamux->chcfg[chan] &= ~(1UL << 6);
    p_hw_dmamux->chcfg[chan] |=  (1UL << 6);
}

/**
 * \brief ����DMAͨ��������
 *
 * \param[in] p_hw_dmamux : ָ��DMAͨ���������Ĵ������ָ��
 * \param[in] chan        : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_trig_disable (amhw_kl26_dmamux_t *p_hw_dmamux,
                                 uint8_t             chan)
{
    p_hw_dmamux->chcfg[chan] &= ~(1UL << 6);
}

/**
 * \brief DMA ͨ��Դѡ��
 *
 * \param[in] p_hw_dmamux : ָ��DMAͨ���������Ĵ������ָ��
 * \param[in] source      : DMA����Դ���ã��������ļ�����ض���
 * \param[in] chan        : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_chan_source_set (amhw_kl26_dmamux_t *p_hw_dmamux,
                                    uint8_t             source,
                                    uint8_t             chan)
{
    p_hw_dmamux->chcfg[chan] &= ~(0x3f);
    p_hw_dmamux->chcfg[chan] |= source ;
}

/**
 * \brief DMA Դ��ַ����
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] address   : д���Ӧ��Դ��ַ
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_source_address_set (amhw_kl26_dma_t *p_hw_dma,
                                       uint32_t         address,
                                       uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_sar = address;
}

/**
 * \brief DMA Ŀ�ĵ�ַ����
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] address   : д���Ӧ��Ŀ�ĵ�ַ
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_destination_address_set (amhw_kl26_dma_t *p_hw_dma,
                                            uint32_t         address,
                                            uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dar = address;
}

/**
 * \brief DMA ���ô��󷵻�
 *
 * \param[in] p_hw_dma : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan     : ��Ӧ��ͨ��
 *
 * \retval  AM_TRUE       : ���ô�����
 * \retval  AM_FALSE      : û�����ô�����
 */
am_static_inline
am_bool_t amhw_kl26_dma_configuration_error_get (amhw_kl26_dma_t *p_hw_dma,
                                              uint8_t          chan)
{
    return (am_bool_t)(p_hw_dma->dma_chan[chan].dma_dsr_bcr & (0x1UL << 30));
}

/**
 * \brief DMA Դ���ߴ��󷵻�
 *
 * \param[in] p_hw_dma : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan     : ��Ӧ��ͨ��
 *
 * \retval  AM_TRUE       : Դ���ߴ�����
 * \retval  AM_FALSE      : û��Դ���ߴ�����
 */
am_static_inline
am_bool_t amhw_kl26_dma_source_bus_error_get (amhw_kl26_dma_t *p_hw_dma,
                                           uint8_t          chan)
{
    return (am_bool_t)(p_hw_dma->dma_chan[chan].dma_dsr_bcr & (0x1UL << 29));
}

/**
 * \brief DMA Ŀ�����ߴ��󷵻�
 *
 * \param[in] p_hw_dma : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan     : ��Ӧ��ͨ��
 *
 * \retval  AM_TRUE       : Ŀ�����ߴ�����
 * \retval  AM_FALSE      : û��Ŀ�����ߴ�����
 */
am_static_inline
am_bool_t amhw_kl26_dma_destination_bus_error_get (amhw_kl26_dma_t *p_hw_dma,
                                                uint8_t          chan)
{
    return (am_bool_t)(p_hw_dma->dma_chan[chan].dma_dsr_bcr & (0x1UL << 28));
}

/**
 * \brief DMA ͨ�����󷵻�
 *
 * \param[in] p_hw_dma : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan     : ��Ӧ��ͨ��
 *
 * \retval  AM_TRUE       : ͨ�����ڴ�������
 * \retval  AM_FALSE      : û��ͨ������
 */
am_static_inline
am_bool_t amhw_kl26_dma_request_status_get (amhw_kl26_dma_t *p_hw_dma,
                                         uint8_t          chan)
{
    return (am_bool_t)(p_hw_dma->dma_chan[chan].dma_dsr_bcr & (0x1UL << 26));
}

/**
 * \brief DMA ͨ��״̬����
 *
 * \param[in] p_hw_dma : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan     : ��Ӧ��ͨ��
 *
 * \retval  AM_TRUE       : ͨ����ʼ����ʹ��
 * \retval  AM_FALSE      : ͨ������Ծ
 */
am_static_inline
am_bool_t amhw_kl26_dma_busy_status_get (amhw_kl26_dma_t *p_hw_dma,
                                      uint8_t          chan)
{
    return (am_bool_t)(p_hw_dma->dma_chan[chan].dma_dsr_bcr & (0x1UL << 25));
}

/**
 * \brief DMA ������ɷ���
 *
 * \param[in] p_hw_dma : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan     : ��Ӧ��ͨ��
 *
 * \retval  AM_TRUE       : �������
 * \retval  AM_FALSE      : ����û�����
 */
am_static_inline
am_bool_t amhw_kl26_dma_complete_ststus_get (amhw_kl26_dma_t *p_hw_dma,
                                          uint8_t          chan)
{
    return (p_hw_dma->dma_chan[chan].dma_dsr_bcr & (0x1UL << 24)) ? AM_TRUE : AM_FALSE;
}

/**
 * \brief DMA ״̬���
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_status_clear (amhw_kl26_dma_t *p_hw_dma,
                                 uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dsr_bcr |=  (1UL << 24);
}

/**
 * \brief DMA ���ֽ���д��
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] num       : ������ֽ���
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_bcr_set (amhw_kl26_dma_t *p_hw_dma,
                            uint32_t         num,
                            uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dsr_bcr &= ~(0xffffff);
    p_hw_dma->dma_chan[chan].dma_dsr_bcr |=  (num);
}

/**
 * \brief DMA ���ֽ�����ȡ
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
uint32_t amhw_kl26_dma_bcr_get (amhw_kl26_dma_t *p_hw_dma,
                                uint8_t          chan)
{
    return (p_hw_dma->dma_chan[chan].dma_dsr_bcr & 0xffffff);
}

/**
 * \brief DMA ����ж�ʹ��
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_intterupt_enable (amhw_kl26_dma_t *p_hw_dma,
                                     uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr |=  (1UL<<31);
}

/**
 * \brief DMA ����жϽ���
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_intterupt_disable (amhw_kl26_dma_t *p_hw_dma,
                                      uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(1UL<<31);
}

/**
 * \brief DMA �ⲿ�豸����ʹ��
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_per_resquest_enable (amhw_kl26_dma_t *p_hw_dma,
                                        uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr |= (1UL<<30);
}

/**
 * \brief DMA �ⲿ�豸�������
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_per_resquest_disable (amhw_kl26_dma_t *p_hw_dma,
                                         uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(1UL<<30);
}

/**
 * \brief DMA �첽����ʹ��
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_asy_request_enable (amhw_kl26_dma_t *p_hw_dma,
                                       uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(1UL<<23);
    p_hw_dma->dma_chan[chan].dma_dcr |=  (1UL<<23);
}

/**
 * \brief DMA �첽�������
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_asy_resquest_disable (amhw_kl26_dma_t *p_hw_dma,
                                         uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(1UL<<23);
}

/**
 * \brief DMA ��ʼ����ʹ��
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_transfer_start (amhw_kl26_dma_t *p_hw_dma,
                                   uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(1UL << 16);
    p_hw_dma->dma_chan[chan].dma_dcr |=  (1UL << 16);
}

/**
 * \brief DMA ����ֹͣ
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_transfer_stop (amhw_kl26_dma_t *p_hw_dma ,
                                  uint8_t     chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(1UL << 16);
}

/**
 * \brief DMA ����ģʽ����
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] mode      : DMAģʽ���ã��ж�Ӧ�ĺ궨��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_transfer_mode_set (amhw_kl26_dma_t *p_hw_dma,
                                      uint32_t         mode,
                                      uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(0xf0ffffbf);
    p_hw_dma->dma_chan[chan].dma_dcr |= (mode);
}

/**
 * \brief DMA Դ��ַ��������С����
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] mode      : ��������С����ö����
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_source_buffer_set (amhw_kl26_dma_t                 *p_hw_dma,
                                      amhw_kl26_dma_buffer_size_set_t  mode,
                                      uint8_t                          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(0xf << 12);
    p_hw_dma->dma_chan[chan].dma_dcr |=  (mode << 12);
}

/**
 * \brief DMA Ŀ�ĵ�ַ��������С����
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] mode      : ��������С����ö����
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_destination_buffer_set (amhw_kl26_dma_t                 *p_hw_dma,
                                           amhw_kl26_dma_buffer_size_set_t  mode,
                                           uint8_t                          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(0xf << 8);
    p_hw_dma->dma_chan[chan].dma_dcr |=  (mode << 8);
}

/**
 * \brief DMA ����ͨ��ģʽ����
 *
 * \param[in] p_hw_dma  : ָ��DMA���ƼĴ������ָ��
 * \param[in] mode      : DMAģʽ���ã��ж�Ӧ�ĺ궨��
 * \param[in] chan      : ��Ӧ��ͨ��
 *
 * \return    ��
 */
am_static_inline
void amhw_kl26_dma_link_mode_set (amhw_kl26_dma_t *p_hw_dma,
                                  uint32_t         mode,
                                  uint8_t          chan)
{
    p_hw_dma->dma_chan[chan].dma_dcr &= ~(0x3f);
    p_hw_dma->dma_chan[chan].dma_dcr |=  (mode);
}

/**
 * @} amhw_if_kl26_dma
 */

#ifdef __cplusplus
}
#endif

#endif  /* __KL26_DMA_H */

/* end of file */
