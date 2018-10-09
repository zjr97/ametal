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
 * \brief DMA Ӳ�������ӿڡ�
 *
 * 1. DMA��18 ��ͨ��, ÿ��ͨ�����ӹ̶������裬�ɽ�����������
 *    ����ֱ���USART,SPI��I2C�ȣ�
 * 2. Ƭ�ڻ�Ƭ���¼����ܴ���DMA���У�ÿ��DMAͨ������ѡ��9��Ӳ�����봥��Դ�е�һ����
 *    Ҳ�����������DMA���У�
 * 3. ÿ��ͨ�������趨���ȼ����������ȼ��ٲã�
 * 4. ÿ��ͨ����ͨ���������������ӣ���Ӳ���Զ����������������ݣ�
 * 5. ���δ������ɴ�1024�֣������ַ��������
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-27  mem,modified.
 * - 1.00 15-07-07  win, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC82X_DMA_H
#define __AMHW_LPC82X_DMA_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc82x_if_dma
 * \copydoc amhw_lpc82x_dma.h
 * @{
 */

/** \brief DMA ͨ������ */
#define AMHW_LPC82X_DMA_CHAN_CNT     18
    
/**
 * \brief DMA ͨ���Ĵ����ṹ��
 */
typedef struct amhw_lpc82x_dma_chan {
    __IO  uint32_t  cfg;            /**< \brief DMA ͨ�����üĴ���            */
    __I   uint32_t  ctlstat;        /**< \brief DMA ͨ�����ƺ�״̬�Ĵ���      */
    __IO  uint32_t  xfercfg;        /**< \brief DMA �������üĴ���            */
    __I   uint32_t  reserved;       /**< \brief ����                          */
} amhw_lpc82x_dma_chan_t;

/**
 * \brief DMA �������Ĵ�����ṹ�� 
 */
typedef struct amhw_lpc82x_dma {
    __IO  uint32_t  ctrl;           /**< \brief DMA ���ƼĴ���                */
    __I   uint32_t  intstat;        /**< \brief DMA �ж�״̬�Ĵ���            */
    __IO  uint32_t  srambase;       /**< \brief DMA ͨ�������б��SRAM��ַ    */
    __IO  uint32_t  reserved0[5];   /**< \brief ����                          */
    __IO  uint32_t  enableset0;     /**< \brief ��������DMAͨ��ʹ�ܼĴ���     */
    __IO  uint32_t  reserved1;      /**< \brief ����                          */
    __IO  uint32_t  enableclr0;     /**< \brief ���DMAͨ��ʹ�ܼĴ���         */
    __IO  uint32_t  reserved2;      /**< \brief ����                          */
    __I   uint32_t  active0;        /**< \brief DMAͨ����Ч״̬�Ĵ���         */
    __IO  uint32_t  reserved3;      /**< \brief ����                          */
    __I   uint32_t  busy0;          /**< \brief DMAͨ��busy״̬�Ĵ���         */
    __I   uint32_t  reserved4;      /**< \brief ����                          */
    __IO  uint32_t  errint0;        /**< \brief DMA ͨ�������ж�״̬�Ĵ���    */
    __I   uint32_t  reserved5;      /**< \brief ����                          */
    __IO  uint32_t  intenset0;      /**< \brief ��������DMAͨ���ж�ʹ�ܼĴ��� */
    __I   uint32_t  reserved6;      /**< \brief ����                          */
    __IO  uint32_t  intenclr0;      /**< \brief ���DMAͨ���ж�ʹ�ܼĴ���     */
    __I   uint32_t  reserved7;      /**< \brief ����                          */
    __IO  uint32_t  inta0;          /**< \brief DMA A�жϱ�־�Ĵ���           */
    __I   uint32_t  reserved8;      /**< \brief ����                          */
    __IO  uint32_t  intb0;          /**< \brief DMA B�жϱ�־�Ĵ���           */
    __I   uint32_t  reserved9;      /**< \brief ����                          */
    __IO  uint32_t  setvalid0;      /**< \brief DMAͨ����Ч�ȴ�����λ�Ĵ���   */
    __I   uint32_t  reserved10;     /**< \brief ����                          */
    __IO  uint32_t  settrig0;       /**< \brief DMAͨ����������λ�Ĵ���       */
    __I   uint32_t  reserved11;     /**< \brief ����                          */
    __IO  uint32_t  abort0;         /**< \brief DMAͨ���������λ�Ĵ���       */
    
    __I   uint32_t  reserved12[225]; /**< \brief ����                         */

    /** \brief DMAͨ���Ĵ���    */
    amhw_lpc82x_dma_chan_t chan[AMHW_LPC82X_DMA_CHAN_CNT];
    
} amhw_lpc82x_dma_t;

/**
 * \name �ж�״̬
 * \anchor grp_amhw_lpc82x_dma_intstat
 * @{
 */

/** \brief ����һ��ʹ���жϹ��� */
#define AMHW_LPC82X_DMA_INTSTAT_ACTIVEINT     AM_BIT(1)

/** \brief ����һ�������жϹ��� */
#define AMHW_LPC82X_DMA_INTSTAT_ACTIVEERRINT  AM_BIT(2)

/** @}*/

/**
 * \name ͨ�����ò���
 * \anchor grp_amhw_lpc82x_dma_chan_flags
 * @{
 */

/** \brief ʹ������DMA���� */
#define AMHW_LPC82X_DMA_CHAN_PERIPH_REQ_EN    AM_BIT(0)

/** \brief ʹ��Ӳ������ */
#define AMHW_LPC82X_DMA_CHAN_HWTRIG_EN        AM_BIT(1)

/** \brief Ӳ���������½������� */
#define AMHW_LPC82X_DMA_CHAN_HWTRIG_FALL      AM_BIT(1)

/** \brief Ӳ������������������ */
#define AMHW_LPC82X_DMA_CHAN_HWTRIG_RISE     (AM_BIT(1) | AM_BIT(4))

/** \brief Ӳ���������͵�ƽ���� */
#define AMHW_LPC82X_DMA_CHAN_HWTRIG_LOW      (AM_BIT(1) | AM_BIT(5))

/** \brief Ӳ���������ߵ�ƽ���� */
#define AMHW_LPC82X_DMA_CHAN_HWTRIG_HIGH     (AM_BIT(1) | AM_BIT(4) | AM_BIT(5))

/** \brief ʹ��ͻ��ģʽ */
#define AMHW_LPC82X_DMA_CHAN_BURST_EN         AM_BIT(6)

/** \brief ÿ�α���ͻ�������СΪ 1    */
#define AMHW_LPC82X_DMA_CHAN_BURST_1          AM_SBF(0,  8)

/** \brief ÿ�α���ͻ�������СΪ 2    */
#define AMHW_LPC82X_DMA_CHAN_BURST_2          AM_SBF(1,  8)

/** \brief ÿ�α���ͻ�������СΪ 4    */
#define AMHW_LPC82X_DMA_CHAN_BURST_4          AM_SBF(2,  8)

/** \brief ÿ�α���ͻ�������СΪ 8    */
#define AMHW_LPC82X_DMA_CHAN_BURST_8          AM_SBF(3,  8)

/** \brief ÿ�α���ͻ�������СΪ 16   */
#define AMHW_LPC82X_DMA_CHAN_BURST_16         AM_SBF(4,  8)

/** \brief ÿ�α���ͻ�������СΪ 32   */
#define AMHW_LPC82X_DMA_CHAN_BURST_32         AM_SBF(5,  8)

/** \brief ÿ�α���ͻ�������СΪ 64   */
#define AMHW_LPC82X_DMA_CHAN_BURST_64         AM_SBF(6,  8)

/** \brief ÿ�α���ͻ�������СΪ 128  */
#define AMHW_LPC82X_DMA_CHAN_BURST_128        AM_SBF(7,  8)

/** \brief ÿ�α���ͻ�������СΪ 256  */
#define AMHW_LPC82X_DMA_CHAN_BURST_256        AM_SBF(8,  8)

/** \brief ÿ�α���ͻ�������СΪ 512  */
#define AMHW_LPC82X_DMA_CHAN_BURST_512        AM_SBF(9,  8)

/** \brief ÿ�α���ͻ�������СΪ 1024 */
#define AMHW_LPC82X_DMA_CHAN_BURST_1024       AM_SBF(10, 8)

/** \brief Դ��ַͻ������     */
#define AMHW_LPC82X_DMA_CHAN_SRC_BURST_WRAP   AM_BIT(14)

/** \brief Ŀ���ַͻ������   */
#define AMHW_LPC82X_DMA_CHAN_DST_BURST_WRAP   AM_BIT(15)

/** \brief ͨ�����ȼ� 0 (���) */
#define AMHW_LPC82X_DMA_CHAN_PRIO_0           AM_SBF(0, 16)

/** \brief ͨ�����ȼ� 1  */
#define AMHW_LPC82X_DMA_CHAN_PRIO_1           AM_SBF(1, 16)

/** \brief ͨ�����ȼ� 2  */
#define AMHW_LPC82X_DMA_CHAN_PRIO_2           AM_SBF(2, 16)

/** \brief ͨ�����ȼ� 3  */
#define AMHW_LPC82X_DMA_CHAN_PRIO_3           AM_SBF(3, 16)

/** @} */

/**
 * \name �������������ò���
 * \anchor grp_amhw_lpc82x_dma_xfercfg_flags
 * @{
 */
 
/** \brief ������������Ч */
#define AMHW_LPC82X_DMA_XFER_VALID           AM_BIT(0)

/** \brief �������������ʱ���Զ������µ�ͨ�������� */
#define AMHW_LPC82X_DMA_XFER_RELOAD           AM_BIT(1)

/** \brief ��������DMA�������� */
#define AMHW_LPC82X_DMA_XFER_SWTRIG           AM_BIT(2)

/** \brief �������������ʱ�����������־ */
#define AMHW_LPC82X_DMA_XFER_CLRTRIG          AM_BIT(3)

/** \brief �������������ʱ������A�ж� */
#define AMHW_LPC82X_DMA_XFER_SETINTA          AM_BIT(4)

/** \brief �������������ʱ������B�ж� */
#define AMHW_LPC82X_DMA_XFER_SETINTB          AM_BIT(5)

/** \brief Դ��ַ������ */
#define AMHW_LPC82X_DMA_XFER_WIDTH_8BIT       AM_SBF(0, 8)

/** \brief �������ݿ��Ϊ16 bit */
#define AMHW_LPC82X_DMA_XFER_WIDTH_16BIT      AM_SBF(1, 8)

/** \brief �������ݿ��Ϊ32 bit */
#define AMHW_LPC82X_DMA_XFER_WIDTH_32BIT      AM_SBF(2, 8)

/** \brief ÿ�δ���Դ��ַ������ */
#define AMHW_LPC82X_DMA_XFER_SRCINC_NOINC     AM_SBF(0, 12)

/** \brief Դ��ַ����Ϊ1�����ݿ�� */
#define AMHW_LPC82X_DMA_XFER_SRCINC_1X        AM_SBF(1, 12)

/** \brief Դ��ַ����Ϊ2�����ݿ�� */
#define AMHW_LPC82X_DMA_XFER_SRCINC_2X        AM_SBF(2, 12)

/** \brief Դ��ַ����Ϊ4�����ݿ�� */
#define AMHW_LPC82X_DMA_XFER_SRCINC_4X        AM_SBF(3, 12)

/** \brief Ŀ���ַ���� */
#define AMHW_LPC82X_DMA_XFER_DSTINC_NOINC     AM_SBF(0, 14)

/** \brief Ŀ���ַ����Ϊ1�����ݿ�� */
#define AMHW_LPC82X_DMA_XFER_DSTINC_1X        AM_SBF(1, 14)

/** \brief Ŀ���ַ����Ϊ2�����ݿ�� */
#define AMHW_LPC82X_DMA_XFER_DSTINC_2X        AM_SBF(2, 14)

/** \brief Ŀ���ַ����Ϊ3�����ݿ�� */
#define AMHW_LPC82X_DMA_XFER_DSTINC_4X        AM_SBF(3, 14)

/** \brief �����ܴ���������Ϊ1��  */
#define AMHW_LPC82X_DMA_XFERCOUNT(n)          AM_SBF(n, 16)

/** @} */

/**
 * \brief ʹ��DMA������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_enable (amhw_lpc82x_dma_t *p_hw_dma)
{
    p_hw_dma->ctrl = 1UL;
}

/**
 * \brief ����DMA������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_disable (amhw_lpc82x_dma_t *p_hw_dma)
{
    p_hw_dma->ctrl = 0UL;
}

/**
 * \brief ��ȡDMA�ж�״̬
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return �ж�״̬
 */
am_static_inline
uint32_t amhw_lpc82x_dma_int_stat_get (amhw_lpc82x_dma_t *p_hw_dma)
{
    return (p_hw_dma->intstat & 0x06);
}

/**
 * \brief ����SRAM����ַ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] addr     : ͨ���������б����ʼ��ַ
 *
 * \return ��
 *
 * \note �б����ʼ��ַ������512�ֽڶ���
 */
am_static_inline
void amhw_lpc82x_dma_sram_addr_set (amhw_lpc82x_dma_t *p_hw_dma, 
                                    uint32_t           addr)
{
    p_hw_dma->srambase = AM_BIT_CLR_MASK(addr, 0x1FF);
}

/**
 * \brief ��ȡSRAM����ַ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return ͨ���������б����ʼ��ַ���õ�ַ512�ֽڶ���
 */
am_static_inline
uint32_t amhw_lpc82x_dma_sram_addr_get (amhw_lpc82x_dma_t *p_hw_dma)
{
    return p_hw_dma->srambase;
}

/**
 * \brief ��ȡͨ����������ַ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ͨ����������ַ
 */
am_static_inline
uint32_t amhw_lpc82x_dma_chan_desc_addr_get (amhw_lpc82x_dma_t *p_hw_dma,
                                             uint8_t            chan)
{
    return (amhw_lpc82x_dma_sram_addr_get(p_hw_dma) + (chan << 4));
}

/**
 * \brief ʹ��DMAͨ��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_enable (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    p_hw_dma->enableset0 = AM_BIT(chan);
}

/**
 * \brief ����DMAͨ��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_disable (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    p_hw_dma->enableclr0 = AM_BIT(chan);
}

/**
 * \brief �ж�ָ��ͨ���Ƿ��ڻ״̬
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * 
 * \retval AM_TRUE  : ͨ�����ڻ״̬
 * \retval AM_FALSE : ͨ�����ڷǻ״̬
 *
 * \note ����DMA��ͨ�����ڻ�Ծ״̬��DMAȫ��������ɣ�ͨ�����ڷǻ�Ծ״̬
 */
am_static_inline
am_bool_t amhw_lpc82x_dma_chan_isactive (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    return ((p_hw_dma->active0 & AM_BIT(chan)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ж�ָ��ͨ���Ƿ�busy
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * 
 * \retval AM_TRUE  : ͨ�� busy
 * \retval AM_FALSE : ͨ�� unbusy
 *
 * \note DMAͨ���ڴ�������б�������ܣ����ô˺����ж��Ƿ����abort��ֹ
 */
am_static_inline
am_bool_t amhw_lpc82x_dma_chan_isbusy (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    return ((p_hw_dma->busy0 & AM_BIT(chan)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ��ȡȫ�������־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return �����жϱ�־, bit[17:0] �Ǵ����־λ��Bit n ��Ӧͨ�� n
 */
am_static_inline
uint32_t amhw_lpc82x_dma_error_flags_get (amhw_lpc82x_dma_t *p_hw_dma)
{
    return (p_hw_dma->errint0 & 0x3FFFF);
}

/**
 * \brief ͨ��������������жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] mask     : bit[17:0] ��ӦDMAͨ�� n�� 
 *                       �����λ������ ERRINT ���Ӧ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_error_flags_clr (amhw_lpc82x_dma_t *p_hw_dma, 
                                      uint32_t           mask)
{
    p_hw_dma->errint0 = mask;
}

/**
 * \brief �ж�ָ��ͨ���Ĵ����־�Ƿ���λ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ�롣
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \retval AM_TRUE  : ͨ����������
 * \retval AM_FALSE : ͨ��û�з�������
 */
am_static_inline
am_bool_t amhw_lpc82x_dma_chan_iserror (amhw_lpc82x_dma_t *p_hw_dma,
                                        uint8_t            chan)
{
    return ((p_hw_dma->errint0 & AM_BIT(chan)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ���ָ��ͨ���Ĵ����־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_error_clr (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    p_hw_dma->errint0 = AM_BIT(chan);
}

/**
 * \brief ʹ��DMAͨ���ж�
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_int_enable (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    p_hw_dma->intenset0 = AM_BIT(chan);
}

/**
 * \brief ����DMAͨ���ж�
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_int_disable (amhw_lpc82x_dma_t *p_hw_dma, 
                                       uint8_t            chan)
{
    p_hw_dma->intenclr0 = AM_BIT(chan);
}

/**
 * \brief ��ȡ����ͨ��A�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return A�жϱ�־��bit[17:0] ��DMAͨ����A�жϱ�־��Bit n ��ӦDMAͨ�� n 
 */
am_static_inline
uint32_t amhw_lpc82x_dma_inta_flags_get (amhw_lpc82x_dma_t *p_hw_dma)
{
    return (p_hw_dma->inta0 & 0x3FFFF);
}

/**
 * \brief ͨ���������A�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] mask     : bit[17:0] ��ӦDMAͨ�� n, �ñ����Ϊ������ INTA ���Ӧ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_inta_flags_clr (amhw_lpc82x_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->inta0 = mask;
}

/**
 * \brief �ж�ָ��ͨ���ж�A��־�Ƿ���λ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * 
 * \retval AM_TRUE  : ͨ����A�жϱ�־��λ
 * \retval AM_FALSE : ͨ����A�жϱ�־û�б���λ
 */
am_static_inline
am_bool_t amhw_lpc82x_dma_chan_inta_isactive (amhw_lpc82x_dma_t *p_hw_dma,
                                              uint8_t            chan)
{
    return ((p_hw_dma->inta0 & AM_BIT(chan)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ���ָ��ͨ����A�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_inta_clr (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    p_hw_dma->inta0 = AM_BIT(chan);
}

/**
 * \brief ��ȡȫ��ͨ����B�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return B�жϱ�־��bit[17:0] ��DMAͨ����B�жϱ�־��Bit n ��ӦDMAͨ�� n
 */
am_static_inline
uint32_t amhw_lpc82x_dma_intb_flags_get (amhw_lpc82x_dma_t *p_hw_dma)
{
    return (p_hw_dma->intb0 & 0x3FFFF);
}

/**
 * \brief ͨ���������B�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] mask     : bit[17:0] ��ӦDMAͨ�� n,�ñ����Ϊ������ INTB ���Ӧ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_intb_flags_clr (amhw_lpc82x_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->intb0 = mask;
}

/**
 * \brief �ж�ָ��ͨ����B�жϱ�־�Ƿ���λ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \retval AM_TRUE  : ͨ����B�жϱ�־��λ
 * \retval AM_FALSE : ͨ����B�жϱ�־û�б���λ
 */
am_static_inline
am_bool_t amhw_lpc82x_dma_chan_intb_isactive (amhw_lpc82x_dma_t *p_hw_dma,
                                              uint8_t            chan)
{
    return ((p_hw_dma->intb0 & AM_BIT(chan)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ���ָ��ͨ����B�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_intb_clr (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    p_hw_dma->intb0 = AM_BIT(chan);
}

/**
 * \brief ����ָ��ͨ��������������Ч
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_xferdesc_valid_set (amhw_lpc82x_dma_t *p_hw_dma,
                                              uint8_t            chan)
{
    p_hw_dma->setvalid0 = AM_BIT(chan);
}

/**
 * \brief ����ָ��ͨ������������������Ч
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_xferdesc_trig_set (amhw_lpc82x_dma_t *p_hw_dma,
                                             uint8_t            chan)
{
    p_hw_dma->settrig0 = AM_BIT(chan);
}

/**
 * \brief ��ֹDMAͨ��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 *
 * \note ��ֹDMAͨ��ǰ��Ӧ�Ƚ���ͨ����Ȼ��ȴ�ͨ��un busy�������ֹͨ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_abort (amhw_lpc82x_dma_t *p_hw_dma, uint8_t chan)
{
    p_hw_dma->abort0 = AM_BIT(chan);
}

/**
 * \brief DMA ͨ����������, ��LPC5410X��am_lpc5410x_dma_chan_setupЧ��һ��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * \param[in] flags    : ���ò���
 *                       \ref grp_amhw_lpc82x_dma_chan_flags
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_cfg_set (amhw_lpc82x_dma_t *p_hw_dma,
                                   uint8_t            chan,
                                   uint32_t           flags)
{
    p_hw_dma->chan[chan].cfg = flags;
}

/**
 * \brief DMA ͨ����������ʹ�� 
 * 
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * 
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_periph_enable (amhw_lpc82x_dma_t *p_hw_dma,
                                         uint8_t            chan)
{
    AM_BIT_SET(p_hw_dma->chan[chan].cfg, 0);
}


/**
 * \brief ��ѯ��ӦDMAͨ���������Ƿ�����ʹ��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return AM_TRUE: ����ʹ��; AM_FALSE: ����ʹ��
 */
am_static_inline
am_bool_t amhw_lpc82x_dma_chan_periph_is_enable (amhw_lpc82x_dma_t *p_hw_dma,
                                                 uint8_t            chan)
{
    return ((p_hw_dma->chan[chan].cfg & 1ul)? AM_TRUE : AM_FALSE);

}


/**
 * \brief DMA ͨ������������� 
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_periph_disable (amhw_lpc82x_dma_t *p_hw_dma,
                                          uint8_t            chan)
{
    AM_BIT_CLR(p_hw_dma->chan[chan].cfg, 0);
}

/**
 * \brief Ӳ��������ʽ����
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * \param[in] flags    : Ӳ��������ʽ��AMHW_LPC82X_DMA_CHAN_HWTRIG_*��ֵ
 *                       (#AMHW_LPC82X_DMA_CHAN_HWTRIG_FALL)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_hwtrig_set (amhw_lpc82x_dma_t *p_hw_dma,
                                      uint8_t            chan,
                                      uint32_t           flags)
{
    AM_BIT_CLR_MASK(p_hw_dma->chan[chan].cfg, (AM_BIT(1) | AM_SBF(0x3, 4)));
    AM_BIT_SET_MASK(p_hw_dma->chan[chan].cfg, flags);
}

/**
 * \brief ����Ӳ�������Ĵ���ģʽ(���δ����ͻ������)
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * \param[in] flags    : ͻ�����������ֵ��AMHW_LPC82X_DMA_CHAN_BURST_*��ֵ
 *                       (#AMHW_LPC82X_DMA_CHAN_BURST_EN)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_burst_set (amhw_lpc82x_dma_t *p_hw_dma,
                                     uint8_t            chan,
                                     uint32_t           flags)
{
    AM_BIT_CLR_MASK(p_hw_dma->chan[chan].cfg, (AM_BIT(6) | AM_SBF(0xf, 8)));
    AM_BIT_SET_MASK(p_hw_dma->chan[chan].cfg, flags);
}

/**
 * \brief ʹ��Դ��ͻ������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_src_burst_wrap_enable (amhw_lpc82x_dma_t *p_hw_dma,
                                                 uint8_t            chan)
{
    AM_BIT_SET(p_hw_dma->chan[chan].cfg, 14);
}

/**
 * \brief ����Դ��ͻ������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_src_burst_wrap_disable (amhw_lpc82x_dma_t *p_hw_dma,
                                                  uint8_t            chan)
{
    AM_BIT_CLR(p_hw_dma->chan[chan].cfg, 14);
}

/**
 * \brief ʹ��Ŀ���ͻ������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_dst_burst_wrap_enable (amhw_lpc82x_dma_t *p_hw_dma,
                                                 uint8_t            chan)
{
    AM_BIT_SET(p_hw_dma->chan[chan].cfg, 15);
}

/**
 * \brief ����Ŀ���ͻ������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_dst_burst_wrap_disable (amhw_lpc82x_dma_t *p_hw_dma,
                                                  uint8_t            chan)
{
    AM_BIT_CLR(p_hw_dma->chan[chan].cfg, 15);
}

/**
 * \brief ����ͨ�����ȼ�
 *
 * \param[in] p_hw_dma  : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan      : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * \param[in] prio_flag : ͨ�����ȼ���AMHW_LPC82X_DMA_CHAN_PRIO_*��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_priority_set (amhw_lpc82x_dma_t *p_hw_dma,
                                        uint8_t            chan,
                                        uint32_t           prio_flag)
{
    AM_BIT_CLR_MASK(p_hw_dma->chan[chan].cfg, AM_SBF(7, 16));
    AM_BIT_SET_MASK(p_hw_dma->chan[chan].cfg, prio_flag);
}

/**
 * \brief �ж�ָ��ͨ��������������Ч��־�Ƿ���λ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \retval AM_TRUE  : ������������Ч��־��λ
 * \retval AM_FALSE : ������������Ч��־û����λ
 */
am_static_inline
am_bool_t amhw_lpc82x_dma_chan_xferdesc_isvalid (amhw_lpc82x_dma_t *p_hw_dma,
                                                 uint8_t            chan)
{
    return ((p_hw_dma->chan[chan].ctlstat & AM_BIT(0)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ж�ָ��ͨ������������������־�Ƿ���λ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \retval AM_TRUE  : ��ǰͨ����������λ
 * \retval  AM_FALSE : ��ǰͨ������δ����λ
 */
am_static_inline
am_bool_t amhw_lpc82x_dma_chan_xferdesc_istriggered (amhw_lpc82x_dma_t *p_hw_dma,
                                                     uint8_t            chan)
{
    return ((p_hw_dma->chan[chan].ctlstat & AM_BIT(2)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ��ȡָ��ͨ������������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 *
 * \return DMA�������ò���
 */
am_static_inline
uint32_t amhw_lpc82x_dma_chan_xfercfg_get (amhw_lpc82x_dma_t *p_hw_dma,
                                            uint8_t            chan)
{
    return (uint32_t)(p_hw_dma->chan[chan].xfercfg);
}

/**
 * \brief ����ָ��ͨ���Ĵ���������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ţ�DMA_CHAN_*��ֵ (#DMA_CHAN_0)
 * \param[in] flags    : �������ò�����
 *                       \ref grp_amhw_lpc82x_dma_xfercfg_flags
 *
 * \return ��
 */
am_static_inline
void amhw_lpc82x_dma_chan_xfercfg_set (amhw_lpc82x_dma_t *p_hw_dma,
                                       uint8_t            chan,
                                       uint32_t           flags)
{
    p_hw_dma->chan[chan].xfercfg = flags;
}

/**
 * @} amhw_lpc82x_if_dma
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_LPC82X_DMA_H */

/* end of file */
