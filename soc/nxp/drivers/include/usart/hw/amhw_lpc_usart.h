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
 * \brief ���ڣ�USART�������ӿ�
 *
 * 1. ֧��7��8��9�������ݿ�ȣ�֧��1λ��2λֹͣλ��
 * 2. ����ģʽ�ʹӻ�ģʽ��֧��ͬ��ģʽ���䣬����������λѡ�������ʱ��ѡ�
 * 3. ������ģʽ(9λ����λ)֧�������ַƥ�䣻
 * 4. ֧��RS-485 �շ������ʹ�ܣ�
 * 5. ��żУ��Ĳ����ͼ�飺֧����У�顢żУ�����У�飻
 * 6. ���첽ģʽ�£�����ɱ�̹�����ʱ������֧��5 ~ 16ʱ�Ӳ�����
 * 7. һ���������ݻ�������һ���������ݻ�������
 * 8. �����Զ������Ƶ� RTS/CTS Ӳ���źţ�ͨ������ CTS ��⡢���ͽ��ÿ����Լ���Ϊ
      RTS ��������� GPIO �ɽ�����������ƣ�
 * 9. ���յ����ݺ�״̬����ѡ���Եشӵ����Ĵ����ж�ȡ��
 * 10. ��ֹ��������⣻
 * 11. �������ݲ���2~3�β�����һ����Ʒ��ͬ״̬��λ��
 * 12. �ڽ������ʲ�������֧���Զ����������ԣ�
 * 13. һ��С����Ƶ���������еĴ��ڣ����ڲ������߾��ȵĲ����ʣ�
 * 14. �ж�(Interrupt)֧��: ����׼�������� ����׼�����������տ��У����նϵ��
 *     �⵽�仯��֡������żУ����������Ƿ�أ����� CTS ��⣬���ղ�������
 *     ��⣻
 * 15. ��·ģʽ�����ڲ������ݺ������ƣ�
 * 16. USART ���ͺͽ��տ���ʹ��DMA��������
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-03  bob, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC_USART_H
#define __AMHW_LPC_USART_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc_if_usart
 * \copydoc amhw_lpc_usart.h
 * @{
 */

/**
 * \brief USART �Ĵ�����ṹ��
 */
typedef struct amhw_lpc_usart {
    __IO uint32_t cfg;         /**< \brief USART ���üĴ���             */
    __IO uint32_t ctl;         /**< \brief USART ���ƼĴ���             */
    __IO uint32_t stat;        /**< \brief USART ״̬�Ĵ���             */
    __IO uint32_t intenset;    /**< \brief �ж�ʹ�ܼĴ���               */
    __O  uint32_t intenclr;    /**< \brief �ж�ʹ��λ����Ĵ���         */
    __I  uint32_t rxdat;       /**< \brief �������ݼĴ���.              */
    __I  uint32_t rxdatstat;   /**< \brief �������ݺ�״̬�Ĵ���         */
    __IO uint32_t txdat;       /**< \brief �������ݼĴ���               */
    __IO uint32_t brg;         /**< \brief �����ʲ����Ĵ���             */
    __I  uint32_t intstat;     /**< \brief �ж�״̬�Ĵ���               */
    __IO uint32_t osr;         /**< \brief ������ѡ��Ĵ���             */
    __IO uint32_t addr;        /**< \brief ��ַ�Ĵ���                   */
} amhw_lpc_usart_t;


/**
 * \name USART �������üĴ���λ����
 * \anchor grp_amhw_lpc_usart_cfg
 * @{
 */

/** \brief USARTʹ��      */
#define AMHW_LPC_USART_CFG_ENABLE       AM_BIT(0)      

/** \brief 7λ���ݳ���    */
#define AMHW_LPC_USART_CFG_7BIT         AM_SBF(0UL, 2) 

/** \brief 8λ���ݳ���    */
#define AMHW_LPC_USART_CFG_8BIT         AM_SBF(1UL, 2) 

/** \brief 9λ���ݳ���    */
#define AMHW_LPC_USART_CFG_9BIT         AM_SBF(2UL, 2) 

/** \brief ��ʹ����żУ�� */
#define AMHW_LPC_USART_CFG_PARITY_NO    AM_SBF(0UL, 4) 

/** \brief żУ��         */
#define AMHW_LPC_USART_CFG_PARITY_EVEN  AM_SBF(2UL, 4) 

 /** \brief ��У��         */
#define AMHW_LPC_USART_CFG_PARITY_ODD   AM_SBF(3UL, 4)

/** \brief 1λֹͣλ      */
#define AMHW_LPC_USART_CFG_STOP_1       AM_SBF(0UL, 6) 

/** \brief 2λֹͣλ      */
#define AMHW_LPC_USART_CFG_STOP_2       AM_SBF(1UL, 6) 

/** \brief Use 32KHz RTC clock, the asynchronous clock source is RTC clock */
#define AMHW_LPC_USART_CFG_MODE32K      AM_BIT(7)

/** \brief ʹ��Ӳ�������� */
#define AMHW_LPC_USART_CFG_HWFLOW       AM_BIT(9)   
  
/** \brief ʹ���첽ģʽ   */
#define AMHW_LPC_USART_CFG_AYNMODE      AM_SBF(0UL, 11) 

/** \brief ʹ��ͬ��ģʽ   */
#define AMHW_LPC_USART_CFG_SYNMODE      AM_SBF(1UL, 11) 

/**
 * \brief ����ͬ��ģʽ�����ݲ�����SCLK���½��� 
 *        (������ #AMHW_LPC_USART_CFG_SYNMODE ��һ��ʹ�ã����ɵ���ʹ��)
 */
#define AMHW_LPC_USART_CFG_FALLING      AM_SBF(0UL, 12)

/**
 * \brief ����ͬ��ģʽ�����ݲ�����SCLK�������� 
 *        (������ #AMHW_LPC_USART_CFG_SYNMODE ��һ��ʹ�ã����ɵ���ʹ��)
 */
#define AMHW_LPC_USART_CFG_RISING       AM_SBF(1UL, 12)

/**
 * \brief ����ͬ��ģʽ�����ڹ���������ģʽ
 *        (������ #AMHW_LPC_USART_CFG_SYNMODE ��һ��ʹ�ã����ɵ���ʹ��)
 */
#define AMHW_LPC_USART_CFG_MASTER       AM_SBF(1UL, 14)

/**
 * \brief ����ͬ��ģʽ�����ڹ����ڴӻ�ģʽ        
 *        (������ #AMHW_LPC_USART_CFG_SYNMODE ��һ��ʹ�ã����ɵ���ʹ��)
 */
#define AMHW_LPC_USART_CFG_SLAVE        AM_SBF(0UL, 14)

/** \brief ���ڽ������ڻ�·ģʽ(LoopBack mode) */
#define AMHW_LPC_USART_CFG_LOOPBACK     AM_SBF(1UL, 15)

/**
 * \brief ����RS-485ģʽ: ���ʹ��ʧЧ(De-assertion)�źŽ������ӳ�һ���ַ�ʱ�䣬
 *        ��Ҫ�� #AMHW_LPC_USART_CFG_OESEL ��һ��ʹ��
 */
#define AMHW_LPC_USART_CFG_OETA         AM_SBF(1UL, 18)

/**
 * \brief �Զ���ַƥ��ʹ�ܣ�����ַƥ��ģʽ��ʹ�ܺ�#AMHW_LPC_USART_CTL_ADDRDET����
 *        ��ַƥ��ͨ��Ӳ����ɣ�ʹ�õ�ַ�Ĵ����е�ֵ��ɵ�ַƥ��
 */
#define AMHW_LPC_USART_CFG_AUTOADDR     AM_SBF(1UL, 19)

/**
 * \brief ����RS-485ģʽ: RTS ���ڿ���RS-485�շ��������ʹ��
 */
#define AMHW_LPC_USART_CFG_OESEL        AM_SBF(1UL, 20)

/**
 * \brief ����RS-485ģʽ: ���ʹ���źŸߵ�ƽ��Ч������Ĭ��������ǵ͵�ƽ��Ч
 */
#define AMHW_LPC_USART_CFG_OEPOLHIGH    AM_SBF(1UL, 21)

/**
 * \brief ��ת�������ݹܽŵĵ�ƽ����
 */
#define AMHW_LPC_USART_CFG_RXPOL        AM_SBF(1UL, 22)

/**
 * \brief ��ת�������ݹܽŵĵ�ƽ����
 */
#define AMHW_LPC_USART_CFG_TXPOL        AM_SBF(1UL, 23)

/** @} */


/**
 * \name USART���Ʊ�־����Щ��־���ں��� #amhw_lpc_usart_control()
 * \anchor grp_amhw_lpc_usart_ctl
 * @{
 */

/** \brief ����breakģʽ        */
#define AMHW_LPC_USART_CTL_TXBRKEN    AM_BIT(1)

/** \brief ʹ�ܵ�ַƥ��ģʽ     */
#define AMHW_LPC_USART_CTL_ADDRDET    AM_BIT(2)

/** \brief ���ͽ���             */
#define AMHW_LPC_USART_CTL_TXDIS      AM_BIT(6)

/** \brief ����ʱ�Ӳ���         */
#define AMHW_LPC_USART_CTL_CC         AM_BIT(8)

/** \brief �յ�һ���ַ����CCλ */
#define AMHW_LPC_USART_CTL_CLRCCONRX  AM_BIT(9)

/** \brief �Զ�������ʹ��       */
#define AMHW_LPC_USART_CTL_AUTOBAUD   AM_BIT(16)

/** @} */

/**
 * \name USART״̬��־����ͨ��amhw_lpc_usart_stat_get������ȡUSART״̬
 * \anchor grp_amhw_lpc_usart_stat
 * @{
 */

/** \brief ����׼������        */
#define AMHW_LPC_USART_STAT_RXRDY      AM_BIT(0)

/** \brief ���տ���            */
#define AMHW_LPC_USART_STAT_RXIDLE     AM_BIT(1)

/** \brief ����׼������        */
#define AMHW_LPC_USART_STAT_TXRDY      AM_BIT(2)

/** \brief ���Ϳ���            */
#define AMHW_LPC_USART_STAT_TXIDLE     AM_BIT(3)

/** \brief ʵʱCTS�ź�״̬     */
#define AMHW_LPC_USART_STAT_CTS        AM_BIT(4)

/** \brief CTS�����仯,����    */
#define AMHW_LPC_USART_STAT_DELTACTS   AM_BIT(5)

/** \brief ���ͽ���״̬��־    */
#define AMHW_LPC_USART_STAT_TXDIS      AM_BIT(6)

/** \brief ��������־        */
#define AMHW_LPC_USART_STAT_OVR        AM_BIT(8)

/** \brief �����жϱ�־        */
#define AMHW_LPC_USART_STAT_RXBRK      AM_BIT(10)

/** \brief ��������ֹ״̬�仯 */
#define AMHW_LPC_USART_STAT_DELTARXBRK AM_BIT(11)

/** \brief ���ռ�⵽��ʼλ   */
#define AMHW_LPC_USART_STAT_START      AM_BIT(12)

/** \brief ֡�����־         */
#define AMHW_LPC_USART_STAT_FRMERR     AM_BIT(13)

/** \brief ��żУ������־   */
#define AMHW_LPC_USART_STAT_PARERR     AM_BIT(14)

/** \brief ����������־       */
#define AMHW_LPC_USART_STAT_RXNOISE    AM_BIT(15)

/** \brief �Զ������ʴ����־ */
#define AMHW_LPC_USART_STAT_ABAUDERR   AM_BIT(16)

/** @} */

/**
 * \name �����ж�Դ����,��ͨ��amhw_lpc_usart_int_enable��
 *       amhw_lpc_usart_int_disableʹ�ܻ����
 * \anchor grp_amhw_lpc_usart_int
 * @{
 */

/** \brief ����׼������        */
#define AMHW_LPC_USART_INT_RXRDY      AM_BIT(0)

/** \brief ����׼������        */  
#define AMHW_LPC_USART_INT_TXRDY      AM_BIT(2)  

/** \brief ���Ϳ���            */
#define AMHW_LPC_USART_INT_TXIDLE     AM_BIT(3)  

/** \brief CTS�źŷ����仯     */
#define AMHW_LPC_USART_INT_DELTACTS   AM_BIT(5) 

/** \brief ��������ֹ�ж�      */
#define AMHW_LPC_USART_INT_TXDIS      AM_BIT(6)  

/** \brief ����ж�            */
#define AMHW_LPC_USART_INT_OVR        AM_BIT(8) 

/** \brief ����break״̬�仯   */ 
#define AMHW_LPC_USART_INT_DELTARXBRK AM_BIT(11) 

/** \brief �����������ʼλ    */
#define AMHW_LPC_USART_INT_START      AM_BIT(12) 

/** \brief ֡�����ж�          */
#define AMHW_LPC_USART_INT_FRMERR     AM_BIT(13) 

/** \brief ��żУ������ж�    */
#define AMHW_LPC_USART_INT_PARERR     AM_BIT(14)
 
/** \brief ���������ж�        */
#define AMHW_LPC_USART_INT_RXNOISE    AM_BIT(15) 

/** \brief �Զ������ʴ����ж�  */
#define AMHW_LPC_USART_INT_ABAUDERR   AM_BIT(16) 

/** \brief �����ж�            */
#define AMHW_LPC_USART_INT_ALL        (0x1F96D) 

/** @} */

/**
 * \name USART�����ж�״̬��־������ͨ������amhw_lpc_usart_intstat_get()
 *       ��ȡ�ж�״̬
 * \anchor grp_amhw_lpc_usart_intstat
 * @{
 */
 
/** \brief ����׼������       */
#define AMHW_LPC_USART_INTSTAT_RXRDY      AM_BIT(0)

/** \brief ����׼������       */
#define AMHW_LPC_USART_INTSTAT_TXRDY      AM_BIT(2)

/** \brief ���Ϳ���           */
#define AMHW_LPC_USART_INTSTAT_TXIDLE     AM_BIT(3)

/** \brief CTS�źŷ����仯    */
#define AMHW_LPC_USART_INTSTAT_DELTACTS   AM_BIT(5)

/** \brief ���ͽ����жϱ�־   */
#define AMHW_LPC_USART_INTSTAT_TXDIS      AM_BIT(6)

/** \brief ����жϱ�־       */
#define AMHW_LPC_USART_INTSTAT_OVR        AM_BIT(8)

/** \brief ����break״̬�仯  */
#define AMHW_LPC_USART_INTSTAT_DELTARXBRK AM_BIT(11)

/** \brief ��������⵽��ʼλ */
#define AMHW_LPC_USART_INTSTAT_START      AM_BIT(12)

/** \brief ֡�����ж�         */
#define AMHW_LPC_USART_INTSTAT_FRMERR     AM_BIT(13)

/** \brief ��żУ������ж�   */
#define AMHW_LPC_USART_INTSTAT_PARERR     AM_BIT(14)

/** \brief ���������ж�       */
#define AMHW_LPC_USART_INTSTAT_RXNOISE    AM_BIT(15)

/** \brief �Զ������ʴ����ж� */
#define AMHW_LPC_USART_INTSTAT_ABAUDERR   AM_BIT(16)

/** @} interrupt state */

/**
 * \name USART���ڽ������Ĵ�����RXDATASTAT����־λ����
 * \anchor grp_amhw_lpc_usart_rxstat
 * @{
 */
 
/** \brief ��֡�����־     */
#define AMHW_LPC_USART_RXSTAT_FRAMERR    AM_BIT(13) 

/** \brief ��żУ������־ */
#define AMHW_LPC_USART_RXSTAT_PARITYERR  AM_BIT(14) 

/** \brief ����������־     */
#define AMHW_LPC_USART_RXSTAT_RXNOISE    AM_BIT(15) 

/** @} rx register state */


/**
 * \brief ���ô���
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] cfg_flags  : AMHW_LPC_USART_CFG_*��ֵ������Ļ�ֵ
 *                         (#AMHW_LPC_USART_CFG_HWFLOW)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_config (amhw_lpc_usart_t *p_hw_usart, 
                            uint32_t          cfg_flags)
{
    p_hw_usart->cfg = cfg_flags;
}

/**
 * \brief ��ȡ��������
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
uint32_t amhw_lpc_usart_config_get (amhw_lpc_usart_t *p_hw_usart)
{
    return p_hw_usart->cfg;
}

/**
 * \brief �������üĴ���λ����
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] cfg_flags  : AMHW_LPC_USART_CFG_*��ֵ������Ļ�ֵ
 *                         (#AMHW_LPC_USART_CFG_HWFLOW)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_cfg_set (amhw_lpc_usart_t *p_hw_usart,
                             uint32_t          cfg_flags)
{
    AM_BIT_SET_MASK(p_hw_usart->cfg, cfg_flags);
}

/**
 * \brief �������üĴ���λ���
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] cfg_flags  : AMHW_LPC_USART_CFG_*��ֵ������Ļ�ֵ
 *                         (#AMHW_LPC_USART_CFG_HWFLOW)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_cfg_clr (amhw_lpc_usart_t *p_hw_usart,
                             uint32_t          cfg_flags)
{
    AM_BIT_CLR_MASK(p_hw_usart->cfg, cfg_flags);
}

/**
 * \brief ���ô��ڿ��ƼĴ���ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] ctl_flags  :  AMHW_LPC_USART_CTL_*��ֵ������Ļ�ֵ
 *                         (#AMHW_LPC_USART_CTL_ADDRDET)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_control (amhw_lpc_usart_t *p_hw_usart, 
                             uint32_t          ctl_flags)
{
    p_hw_usart->ctl = ctl_flags;
}

/**
 * \brief ��ȡ���ڿ��ƼĴ���ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *                         (#AMHW_LPC_USART_CTL_ADDRDET)
 *
 * \return ���ڿ��ƼĴ���ֵ
 */
am_static_inline
uint32_t amhw_lpc_usart_ctl_get (amhw_lpc_usart_t *p_hw_usart)
{
    return p_hw_usart->ctl;
}

/**
 * \brief ���ÿ��ƼĴ�����λ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] ctl_flags  : AMHW_LPC_USART_CTL_*��ֵ������Ļ�ֵ
 *                         (#AMHW_LPC_USART_CTL_ADDRDET),δ���õ�λ����Ӱ�졣
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_ctl_set (amhw_lpc_usart_t *p_hw_usart, 
                             uint32_t          ctl_flags)
{
    AM_BIT_SET_MASK(p_hw_usart->ctl, ctl_flags);
}

/**
 * \brief ������ƼĴ���λ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] ctl_flags  : AMHW_LPC_USART_CTL_*��ֵ������Ļ�ֵ
 *                         (#AMHW_LPC_USART_CTL_ADDRDET),δ�����λ����Ӱ�졣
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_ctl_clr (amhw_lpc_usart_t *p_hw_usart, 
                             uint32_t          ctl_flags)
{
    AM_BIT_CLR_MASK(p_hw_usart->ctl, ctl_flags);
}

/**
 * \brief ��ȡ����״̬
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return AMHW_LPC_USART_INTSTAT_*��ֵ������Ļ�ֵ
 *         (#AMHW_LPC_USART_INTSTAT_RXRDY)
 */
am_static_inline
uint32_t amhw_lpc_usart_stat_get (amhw_lpc_usart_t *p_hw_usart)
{
    return p_hw_usart->stat;
}

/**
 * \brief �������״̬��־
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] stat_flags : AMHW_LPC_USART_STAT_*��ֵ������Ļ�ֵ
 *                         (#AMHW_LPC_USART_STAT_START)
 *
 * \return ��
 *
 * \note �������־���Զ����.�ٲ��ֱ�־����Ҫ������:
 *       #AMHW_LPC_USART_STAT_DELTACTS, #AMHW_LPC_USART_STAT_OVR,
 *       #AMHW_LPC_USART_STAT_DELTARXBRK, #AMHW_LPC_USART_STAT_START,
 *       #AMHW_LPC_USART_STAT_FRMERR, #AMHW_LPC_USART_STAT_PARERR
 *       #AMHW_LPC_USART_STAT_RXNOISE, #AMHW_LPC_USART_STAT_ABAUDERR
 */
am_static_inline
void amhw_lpc_usart_stat_clr (amhw_lpc_usart_t *p_hw_usart, 
                              uint32_t          stat_flags)
{
    p_hw_usart->stat = stat_flags;
}

/**
 * \brief �õ������ж�״̬
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return AMHW_LPC_USART_INTSTAT_*��ֵ������Ļ�ֵ
 *         (#AMHW_LPC_USART_INTSTAT_RXRDY)
 */
am_static_inline
uint32_t amhw_lpc_usart_intstat_get (amhw_lpc_usart_t *p_hw_usart)
{
    return p_hw_usart->intstat;
}

/**
 * \brief ��ȡ���ڽ������ݣ�ͬʱ�����������״̬
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��ȡ����ֵ
 *          - bit0 ~ bit8 : ���յ�������
 *          - bit13       : ֡����״̬
 *          - bit14       : ��żУ�����״̬
 *          - bit15       : ��������
 */
am_static_inline
uint32_t amhw_lpc_usart_rxdata_stat_read (amhw_lpc_usart_t *p_hw_usart)
{
     return p_hw_usart->rxdatstat;
}

/**
 * \brief ʹ��ָ���Ĵ����ж�
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] int_enable : AMHW_LPC_USART_INT_* ��ֵ������Ļ�ֵ
 *                         (#AMHW_LPC_USART_INT_RXRDY)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_int_enable (amhw_lpc_usart_t *p_hw_usart, 
                                uint32_t          int_enable)
{
    AM_BIT_SET_MASK(p_hw_usart->intenset, int_enable);
}

/**
 * \brief ����ָ���Ĵ����ж�
 *
 * \param[in] p_hw_usart  : ָ�򴮿ڼĴ������ָ��
 * \param[in] int_disable : AMHW_LPC_USART_INT_* ��ֵ������Ļ�ֵ
 *                          (#AMHW_LPC_USART_INT_RXRDY)
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_int_disable (amhw_lpc_usart_t *p_hw_usart, 
                                 uint32_t          int_disable)
{
     p_hw_usart->intenclr = int_disable;
}

/**
 * \brief д���ڷ��ͼĴ���ֵ������һ�����ݣ�
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] data       : ���͵�����
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_txdata_write (amhw_lpc_usart_t *p_hw_usart,
                                  uint32_t          data)
{
     p_hw_usart->txdat = data;
}

/**
 * \brief ��ȡ���ڽ�������
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ���ڽ��յ�������
 */
am_static_inline
uint32_t amhw_lpc_usart_rxdata_read (amhw_lpc_usart_t *p_hw_usart)
{
     return p_hw_usart->rxdat;
}

/**
 * \brief ��ȡ���ڽ������ݣ������ܱ�־λ��
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ���ڽ��յ������ݼ����ܱ�־��Ϣ
 */
am_static_inline
uint32_t amhw_lpc_usart_rxdatstat_read (amhw_lpc_usart_t *p_hw_usart)
{
     return p_hw_usart->rxdatstat;
}

/**
 * \brief ���ô��ڲ����ʲ����Ĵ���ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] brg_val    : ��Ƶֵ������ʱ�ӽ���brg_val��Ƶ(0~0xffff)
 *
 * \return ��
 * 
 * \note ���ڲ����ʷ�Ƶֵ���Ĵ���ֵ0��0xFFFF,ʵ��ֵ1~65536
 */
am_static_inline
void amhw_lpc_usart_brg_set (amhw_lpc_usart_t *p_hw_usart, 
                             uint32_t          brg_val)
{
    p_hw_usart->brg = brg_val & 0xffff;
}

/**
 * \brief ���ù�����ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] osr_val    : ���ͺͽ���ÿλʹ��osr_val��ʱ�ӽ��в���
 *                         
 *
 * \return ��
 *
 * \note �첽ģʽ�µĹ�����ֵ��Ĭ��0xF,�Ĵ���ֵ0x3��0xF,ʵ��ֵ4��16
 */
am_static_inline
void amhw_lpc_usart_osr_set (amhw_lpc_usart_t *p_hw_usart, 
                             uint8_t           osr_val)
{
    p_hw_usart->osr = osr_val;
}

/**
 * \brief ���õ�ַ�Ĵ�����ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] addr_val   : 8λ�ĵ�ֵַ
 *
 * \return ��
 *
 * \note �ڵ�ַƥ��ģʽ�У����ʹ���˵�ַ�Զ�ƥ��ģʽ����õ�ַ�Ĵ��������ŵĵ�
 *       ֵַ����Ӳ����ַƥ�䡣
 */
am_static_inline
void amhw_lpc_usart_addr_set (amhw_lpc_usart_t *p_hw_usart, 
                              uint8_t           addr_val)
{
    p_hw_usart->addr = addr_val;
}

/**
 * \brief ��ȡ��ַ�Ĵ�����ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] addr_val   : 8λ�ĵ�ֵַ
 *
 * \return 8λ��ַ
 *
 * \note �ڵ�ַƥ��ģʽ�У����ʹ���˵�ַ�Զ�ƥ��ģʽ����õ�ַ�Ĵ��������ŵĵ�
 *       ֵַ����Ӳ����ַƥ�䡣
 */
am_static_inline
uint8_t amhw_lpc_usart_addr_get (amhw_lpc_usart_t *p_hw_usart, 
                                 uint8_t              addr_val)
{
    return (0xff & p_hw_usart->addr);
}

/**
 * \brief ʹ�ܴ���
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_enable (amhw_lpc_usart_t *p_hw_usart)
{
    AM_BIT_SET_MASK(p_hw_usart->cfg, AMHW_LPC_USART_CFG_ENABLE);
}

/**
 * \brief ���ܴ���
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_disable (amhw_lpc_usart_t *p_hw_usart)
{
    AM_BIT_CLR_MASK(p_hw_usart->cfg, AMHW_LPC_USART_CFG_ENABLE);
}

/**
 * \brief ��ȡCTS״̬������Ӳ�����ط����жϣ�
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return cts����״̬��0��ʾ�͵�ƽ����0��ʾ�ߵ�ƽ��
 */
am_static_inline
uint32_t amhw_lpc_usart_cts_stat_read (amhw_lpc_usart_t *p_hw_usart)
{
    return (p_hw_usart->stat & AMHW_LPC_USART_STAT_CTS);
}

/**
 * \brief �ȴ����ڷ��Ϳ���
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc_usart_wait_idle (amhw_lpc_usart_t *p_hw_usart)
{
    while ((p_hw_usart->stat & AMHW_LPC_USART_STAT_TXIDLE) == 0);
}

/**
 * \brief ���ڲ����ʻ�ȡ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] u_clk      : ���ڻ���ʱ��
 *
 * \return ���ڲ�����
 */
uint32_t amhw_lpc_usart_baudrate_get (amhw_lpc_usart_t *p_hw_usart,
                                      uint32_t          u_clk);

/**
 * \brief ���ڲ���������
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] u_clk      : ���ڵ�����ʱ��Ƶ��
 * \param[in] baudrate   : �������õĴ��ڲ�����
 *
 * \return ʵ�ʵĲ����ʣ�С��0��������ʧ�ܣ�
 */
int amhw_lpc_usart_baudrate_set (amhw_lpc_usart_t *p_hw_usart,
                                 uint32_t          u_clk,
                                 uint32_t          baudrate);

/**
 * \brief USART���ݷ���(��ѯģʽ)
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] p_txbuf    : �������ݻ�����
 * \param[in] nbytes     : �������ݸ���
 *
 * \return �ɹ����͵����ݸ���
 */
int amhw_lpc_usart_poll_send (amhw_lpc_usart_t  *p_hw_usart,
                              const uint8_t   *p_txbuf,
                              uint32_t           nbytes);

/**
 * \brief USART���ݽ���(��ѯģʽ)
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] p_rxbuf    : �������ݻ�����
 * \param[in] nbytes     : �������ݸ���
 *
 * \return �ɹ����յ����ݸ���
 */
int amhw_lpc_usart_poll_receive (amhw_lpc_usart_t *p_hw_usart,
                                 uint8_t          *p_rxbuf,
                                 uint32_t          nbytes);

/**
 * @} amhw_lpc_if_usart
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC_USART_H */

/* end of file */
